#include <stdio.h>
#include <stdlib.h>
#include <xcb/xcb.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GLES2/gl2.h>

typedef EGLDisplay (*PFNEGLGETPLATFORMDISPLAYEXTPROC)(EGLenum, void *, const EGLint *);
typedef EGLSurface (*PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC)(EGLDisplay, EGLConfig, void *, const EGLint *);

const char *vs_source =
    "attribute vec4 pos;\n"
    "attribute vec2 tc;\n"
    "varying vec2 v_tc;\n"
    "void main() {\n"
    "  gl_Position = pos;\n"
    "  v_tc = tc;\n"
    "}\n";

const char *fs_source =
    "precision mediump float;\n"
    "varying vec2 v_tc;\n"
    "uniform sampler2D tex;\n"
    "void main() {\n"
    "  gl_FragColor = texture2D(tex, v_tc);\n"
    "}\n";

/* Full-screen quad (covers entire window) */
static const GLfloat full_verts[8] = {
    -1.0f, -1.0f,
     1.0f, -1.0f,
    -1.0f,  1.0f,
     1.0f,  1.0f
};

static const GLfloat full_texcoords[8] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f
};

/* Smaller centered quad (half size) */
static const GLfloat small_verts[8] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
    -0.5f,  0.5f,
     0.5f,  0.5f
};

static const GLfloat small_texcoords[8] = {
    0.0f, 0.0f,
    1.0f, 0.0f,
    0.0f, 1.0f,
    1.0f, 1.0f
};

int main() {
    xcb_connection_t *conn = xcb_connect(NULL, NULL);
    if (xcb_connection_has_error(conn)) return 1;

    xcb_screen_t *screen = xcb_setup_roots_iterator(xcb_get_setup(conn)).data;

    xcb_window_t win = xcb_generate_id(conn);
    uint32_t mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
    uint32_t values[2] = { screen->black_pixel,
                           XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_KEY_PRESS };

    xcb_create_window(conn, XCB_COPY_FROM_PARENT, win, screen->root,
                      100, 100, 640, 480, 0,
                      XCB_WINDOW_CLASS_INPUT_OUTPUT,
                      screen->root_visual, mask, values);

    xcb_map_window(conn, win);
    xcb_flush(conn);

    PFNEGLGETPLATFORMDISPLAYEXTPROC eglGetPlatformDisplayEXT =
        (PFNEGLGETPLATFORMDISPLAYEXTPROC)eglGetProcAddress("eglGetPlatformDisplayEXT");
    PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC eglCreatePlatformWindowSurfaceEXT =
        (PFNEGLCREATEPLATFORMWINDOWSURFACEEXTPROC)eglGetProcAddress("eglCreatePlatformWindowSurfaceEXT");

    EGLDisplay dpy = eglGetPlatformDisplayEXT(EGL_PLATFORM_XCB_EXT, conn, NULL);
    eglInitialize(dpy, NULL, NULL);

    EGLint config_attribs[] = {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_NONE
    };

    EGLConfig config;
    EGLint num_configs;
    eglChooseConfig(dpy, config_attribs, &config, 1, &num_configs);

    EGLSurface surface = eglCreateWindowSurface(dpy, config, (EGLNativeWindowType)win, NULL);
    // Note: Some drivers expect &win instead of casted win; if it fails, try &win

    EGLint context_attribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
    EGLContext context = eglCreateContext(dpy, config, EGL_NO_CONTEXT, context_attribs);

    eglMakeCurrent(dpy, surface, surface, context);

    glViewport(0, 0, 640, 480);

    /* Red texture (full background) */
    GLuint tex_red;
    glGenTextures(1, &tex_red);
    glBindTexture(GL_TEXTURE_2D, tex_red);
    unsigned char red_pixel[3] = {255, 0, 0};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, red_pixel);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    /* Blue texture (smaller overlay) */
    GLuint tex_blue;
    glGenTextures(1, &tex_blue);
    glBindTexture(GL_TEXTURE_2D, tex_blue);
    unsigned char blue_pixel[3] = {0, 0, 255};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, blue_pixel);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_source, NULL);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_source, NULL);
    glCompileShader(fs);

    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glBindAttribLocation(prog, 0, "pos");
    glBindAttribLocation(prog, 1, "tc");
    glLinkProgram(prog);
    glUseProgram(prog);

    GLint tex_loc = glGetUniformLocation(prog, "tex");
    glUniform1i(tex_loc, 0);

    /* Main loop */
    while (1) {
        xcb_generic_event_t *ev = xcb_wait_for_event(conn);
        if (ev) {
            uint8_t type = ev->response_type & ~0x80;
            if (type == XCB_EXPOSE) {
                glClear(GL_COLOR_BUFFER_BIT);

                /* Draw full-screen red background */
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, tex_red);

                glEnableVertexAttribArray(0);
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, full_verts);
                glEnableVertexAttribArray(1);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, full_texcoords);

                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

                /* Draw smaller blue square in the center */
                glBindTexture(GL_TEXTURE_2D, tex_blue);

                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, small_verts);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, small_texcoords);

                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

                eglSwapBuffers(dpy, surface);
            } else if (type == XCB_KEY_PRESS) {
                free(ev);
                break;
            }
            free(ev);
        }
    }

    /* Cleanup */
    glDeleteTextures(1, &tex_red);
    glDeleteTextures(1, &tex_blue);
    glDeleteProgram(prog);
    glDeleteShader(vs);
    glDeleteShader(fs);

    eglMakeCurrent(dpy, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
    eglDestroyContext(dpy, context);
    eglDestroySurface(dpy, surface);
    eglTerminate(dpy);

    xcb_destroy_window(conn, win);
    xcb_disconnect(conn);

    return 0;
}
