#include <stdio.h>
#include <stdlib.h>

#include <EGL/egl.h>
#include <GL/gl.h>
#include <X11/Xlib.h>

static struct {
  Display* display;
  Window root_window;
  Window window;
} x11;

static struct {
  EGLConfig config;
  EGLContext context;
  EGLDisplay display;
  EGLSurface window_surface;
} egl;

static void die(void) {
  exit(1);
}

int main(void) {
  x11.display = XOpenDisplay(NULL);
  if (x11.display == NULL) die();

  x11.root_window = DefaultRootWindow(x11.display);

  x11.window = XCreateWindow(x11.display, x11.root_window, 0, 0, 1280, 720, 0,
      CopyFromParent, InputOutput, CopyFromParent, 0, NULL);

  egl.display = eglGetDisplay(x11.display);
  if (egl.display == EGL_NO_DISPLAY) die();

  if (!eglInitialize(egl.display, NULL, NULL)) die();

  {
    static const EGLint attributes[] = {
      EGL_SURFACE_TYPE,     EGL_WINDOW_BIT,
      EGL_RED_SIZE,         8,
      EGL_GREEN_SIZE,       8,
      EGL_BLUE_SIZE,        8,
      EGL_RENDERABLE_TYPE,  EGL_OPENGL_BIT,
      EGL_NONE
    };

    EGLint config_count;
    if (!eglChooseConfig(egl.display, attributes, &egl.config, 1, &config_count)) die();
    if (config_count != 1) die();
  }

  if (!eglBindAPI(EGL_OPENGL_API)) die();

  egl.window_surface =
    eglCreateWindowSurface(egl.display, egl.config, x11.window, NULL);
  if (egl.window_surface == EGL_NO_SURFACE) die();

  {
    static const EGLint attributes[] = {
      EGL_CONTEXT_MAJOR_VERSION, 4,
      EGL_CONTEXT_MINOR_VERSION, 6,
      EGL_NONE
    };

    egl.context = eglCreateContext(egl.display, egl.config, EGL_NO_CONTEXT, attributes);
    if (egl.context == EGL_NO_CONTEXT) die();
  }

  if (!eglMakeCurrent(egl.display, egl.window_surface, egl.window_surface, egl.context)) die();

  // https://stackoverflow.com/questions/27873784/when-do-i-need-to-use-an-opengl-function-loader
  printf("GL_VERSION %s\n", (char*)glGetString(GL_VERSION));

  eglMakeCurrent(egl.display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
  eglDestroySurface(egl.display, egl.window_surface);
  eglDestroyContext(egl.display, egl.context);
  eglTerminate(egl.display);
  eglReleaseThread();

  XDestroyWindow(x11.display, x11.window);
  XSync(x11.display, False);
  XCloseDisplay(x11.display);

  return 0;
}
