/*
 * Copyright (c) 2009 Tias Guns
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef GUI_CALIBRATOR_X11
#define GUI_CALIBRATOR_X11

#include "calibrator.hh"
#include <list>
#include <X11/Xutil.h>

/*******************************************
 * X11 class for the the calibration GUI
 *******************************************/
class GuiCalibratorX11
{
public:
    static void make_instance(Calibrator* w);
    static void give_timer_signal();

private:
    GuiCalibratorX11(Calibrator* w);
    ~GuiCalibratorX11();

    // Data
    Calibrator* calibrator;
    double X[NUM_POINTS], Y[NUM_POINTS];
    int display_width, display_height;
    int display_x, display_y;
    int time_elapsed;
    std::list<std::string> display_texts;

    // X11 vars
    Display* display;
    int screen_num;
    Window win;
    GC gc;
    XSizeHints* size_hints;
    XFontStruct* font_info;

#ifdef HAVE_TIMERFD
    int timer_fd;
#endif

    // color management
    enum { BLACK=0, WHITE=1, GRAY=2, DIMGRAY=3, RED=4, NUM_COLORS };
    static const char* colors[NUM_COLORS];
    unsigned long pixel[NUM_COLORS];

    // dicives
    static const char* geometry_by_device_prefix;

    // Signal handlers
    void on_timer_signal();
    void on_expose_event();
    void on_button_press_event(XEvent event);

    // Helper functions
    void detect_display_size(int &width, int &height);
    bool detect_device_size_and_position(const char *name, int &width, int &height, int &x, int &y);
    void set_display_size(int width, int height);
    void set_display_size_and_position(int width, int height, int x, int y);
    void redraw();
    void draw_message(const char* msg);

    static GuiCalibratorX11* instance;
};

#endif
