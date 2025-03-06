#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <time.h>

// Function to enforce frame rate and print achieved FPS
void enforce_frame_rate(struct timespec *start_time, int frame_rate, int *frame_count, double *elapsed_time_sum) {
    struct timespec current_time, sleep_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);

    long elapsed_nanoseconds = (current_time.tv_sec - start_time->tv_sec) * 1000000000L +
                               (current_time.tv_nsec - start_time->tv_nsec);

    long frame_duration_nanoseconds = 1000000000L / frame_rate;

    if (elapsed_nanoseconds < frame_duration_nanoseconds) {
        sleep_time.tv_sec = 0;
        sleep_time.tv_nsec = frame_duration_nanoseconds - elapsed_nanoseconds;
        nanosleep(&sleep_time, NULL);

///////////////// This section is for printing
        // Get the actual elapsed time after sleeping
        clock_gettime(CLOCK_MONOTONIC, &current_time);
        elapsed_nanoseconds = (current_time.tv_sec - start_time->tv_sec) * 1000000000L +
                               (current_time.tv_nsec - start_time->tv_nsec);
    }

    // Calculate achieved FPS
    double elapsed_seconds = (double)elapsed_nanoseconds / 1000000000.0;
    *elapsed_time_sum += elapsed_seconds;
    (*frame_count)++;

    if (*elapsed_time_sum >= 1.0) { // Print FPS every second
        double achieved_fps = (double)*frame_count / *elapsed_time_sum;
        printf("Achieved FPS: %.2f\n", achieved_fps);
        *frame_count = 0;
        *elapsed_time_sum = 0.0;
    }

    // Update start_time for the next frame
    clock_gettime(CLOCK_MONOTONIC, start_time);
///////////////////////////
}

int main() {
    Display *display;
    Window window;
    GC gc;
    XEvent event;
    int screen;

    // Open connection to the X server
    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Cannot open display\n");
        return 1;
    }

    screen = DefaultScreen(display);

    // Create a simple window
    window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, 200, 100, 0,
                                BlackPixel(display, screen), WhitePixel(display, screen));

    // Select input events
    XSelectInput(display, window, ExposureMask | KeyPressMask);

    // Create a graphics context
    gc = XCreateGC(display, window, 0, NULL);

    // Map the window
    XMapWindow(display, window);

    // Set target frame rate
    int frame_rate = 120;
    int frame_count = 0;
    double elapsed_time_sum = 0.0;
    struct timespec frame_start_time;
    clock_gettime(CLOCK_MONOTONIC, &frame_start_time); // Initialize frame_start_time

    // Main loop
    while (1) {
        // Handle events
        while (XPending(display)) {
            XNextEvent(display, &event);
            if (event.type == Expose) {
                XFillRectangle(display, window, gc, 20, 20, 100, 60);
            }
            if (event.type == KeyPress)
                goto end;
        }

        // Enforce frame rate and print FPS
        enforce_frame_rate(&frame_start_time, frame_rate, &frame_count, &elapsed_time_sum);
    }

end:
    // Clean up and close the connection to the X server
    XFreeGC(display, gc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);

    return 0;
}
