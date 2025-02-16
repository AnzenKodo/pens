#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>
#include <stdio.h>

int main() {
    Display *dpy;
    Window root;
    XRRScreenResources *screenRes;
    XRRCrtcInfo *crtcInfo;

    dpy = XOpenDisplay(NULL);
    if (dpy == NULL) {
        fprintf(stderr, "Unable to open display\n");
        return 1;
    }

    root = DefaultRootWindow(dpy);
    screenRes = XRRGetScreenResources(dpy, root);

    for (int i = 0; i < screenRes->ncrtc; i++) {
        crtcInfo = XRRGetCrtcInfo(dpy, screenRes, screenRes->crtcs[i]);
        if (crtcInfo) {
            printf("Crtc %d: Refresh Rate: %.2f Hz\n",
                   /* crtcInfo->crtc */ 1,
                   (float)crtcInfo->mode == 0 ? 0 : (float)screenRes->modes[crtcInfo->mode].dotClock /
                   (screenRes->modes[crtcInfo->mode].hTotal * screenRes->modes[crtcInfo->mode].vTotal));
            XRRFreeCrtcInfo(crtcInfo);
        }
    }

    XRRFreeScreenResources(screenRes);
    XCloseDisplay(dpy);
    return 0;
}
