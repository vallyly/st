#ifndef VV_KITTY_H
#define VV_KITTY_H

#include <X11/Xlib.h>
#include <X11/keysym.h>

typedef enum {
    kitty_lvl0 =  0b00000000,  // Default behavior
    kitty_lvl1 =  0b00000001,  // Disambiguate escape codes
    kitty_lvl2 =  0b00000010,  // Report event types
    kitty_lvl3 =  0b00000100,  // Report alternate keys
    // kitty_lvl4=0b00001000,   // Report all keys as escape codes
    // kitty_lvl5=0b00010000,   // Report associated text
    kitty_max = (kitty_lvl3|kitty_lvl2|kitty_lvl1)
} kitty_kbd_t;


typedef enum {
    kitty_none =               0,
    kitty_shift     = 0b00000001,
    kitty_alt       = 0b00000010,
    kitty_ctrl      = 0b00000100,
    kitty_super     = 0b00001000,
    kitty_hyper     = 0b00010000,
    kitty_meta      = 0b00100000,
    kitty_caps_lock = 0b01000000,
    kitty_num_lock  = 0b10000000,
} kitty_kbd_mod_t;


typedef enum {
    undefined = 0,
    press = 1,
    repeat = 2,
    release = 3
} kitty_kbd_event_t;

#define KeyRepeat 1

// kitty_kbd.c
extern kitty_kbd_t stack[];
extern unsigned int stack_i;
void stack_set(kitty_kbd_t, int);
void stack_push(kitty_kbd_t);
void stack_pop(unsigned int);
kitty_kbd_mod_t   mod_x_to_kitty(int);
kitty_kbd_event_t keyev_x_to_kitty(int);
#define keyev_x_to_kitty(i) ((kitty_kbd_event_t[LASTEvent])         \
    {[KeyRepeat]=repeat, [KeyPress]=press, [KeyRelease]=release     \
    }[i])

// x.c
extern void (*handler[])(XEvent *);
extern void kpress(XEvent *);
extern void kpress_kitty(XEvent *);
extern void krelease_kitty(XEvent *);

//

typedef struct {
    KeySym k;
    // unsigned char start_omittable;
    // start_omittable is the sign bit of start_n.
    int8_t start_n;
    char s[7];
} non_textual_key_ctx;


static non_textual_key_ctx ntkeys[] = {
    {.k = XK_Escape,    .start_n =  2, .s = "27u"},
    {.k = XK_Insert,    .start_n =  1, .s = "2~"},
    {.k = XK_Delete,    .start_n =  1, .s = "3~"},
    {.k = XK_Left,      .start_n = -1, .s = "1D"},
    {.k = XK_Right,     .start_n = -1, .s = "1C"},
    {.k = XK_Up,        .start_n = -1, .s = "1A"},
    {.k = XK_Down,      .start_n = -1, .s = "1B"},
    {.k = XK_Page_Up,   .start_n =  1, .s = "5~"},
    {.k = XK_Page_Down, .start_n =  1, .s = "6~"},
    {.k = XK_Home,      .start_n = -1, .s = "1H"},
    {.k = XK_End,       .start_n = -1, .s = "1F"},
    {.k = XK_Print,     .start_n =  5, .s = "57361u"},
    {.k = XK_F1,        .start_n = -1, .s = "1P"},
    {.k = XK_F2,        .start_n = -1, .s = "1Q" },
    {.k = XK_F3,        .start_n =  2, .s = "13~"},
    {.k = XK_F4,        .start_n = -1, .s = "1S" },
    {.k = XK_F5,        .start_n =  2, .s = "15~"},
    {.k = XK_F6,        .start_n =  2, .s = "17~"},
    {.k = XK_F7,        .start_n =  2, .s = "18~"},
    {.k = XK_F8,        .start_n =  2, .s = "19~"},
    {.k = XK_F9,        .start_n =  2, .s = "20~"},
    {.k = XK_F10,       .start_n =  2, .s = "21~"},
    {.k = XK_F11,       .start_n =  2, .s = "23~"},
    {.k = XK_F12,       .start_n =  2, .s = "24~"},
};

#define start_non_negotiable(ntk) (abs(ntk.start_n) == ntk.start_n)

#endif /* !VV_KITTY_H */
