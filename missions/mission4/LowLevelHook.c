// Marcos Leroy Salazar Skinner
// A01039743
// Moisés Fernández Zárate
// A01197049
// Date: 24/5/2020

// Mission 4
// Low Level Hook
// Programa en el que se genera un archivo con las coordenadas de cada clic que haga el usuario en la pantalla.

#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>

int main()
{
    Display *display;
    XEvent xevent;
    Window window;

    if ((display = XOpenDisplay(NULL)) == NULL)
    {
        exit(-1);
    }

    window = DefaultRootWindow(display);
    XAllowEvents(display, AsyncBoth, CurrentTime);

    XGrabPointer(display, window, 1, PointerMotionMask | ButtonPressMask | ButtonReleaseMask, GrabModeAsync, GrabModeAsync, None, None, CurrentTime);

    FILE *output = fopen("coordinates.txt", "w");
    fprintf(output, "X | Y\n");
    fclose(output);

    while(1) {
        XNextEvent(display, &xevent);
        
        if (xevent.type == ButtonPress) {
            output = fopen("coordinates.txt", "a");
            fprintf(output, "%d %d\n", xevent.xmotion.x_root, xevent.xmotion.y_root);
            fclose(output);
        }
    }

    return 0;
}