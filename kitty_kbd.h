#ifndef VV_KITTY_H
#define VV_KITTY_H

#include <X11/Xlib.h>
#include <X11/keysym.h>

typedef enum {
    ktty_lvl0 =  0b00000000,  // Default behavior
    ktty_lvl1 =  0b00000001,  // Disambiguate escape codes
    // ktty_lvl2=0b00000010,  // Report event types
    // ktty_lvl3=0b00000100,  // Report alternate keys
    // ktty_lvl4=0b00001000,  // Report all keys as escape codes
    // ktty_lvl5=0b00010000,  // Report associated text
    ktty_last = ktty_lvl1
} kitty_kbd_t;


typedef enum {
    kitty_shift     = 0b00000001,
    kitty_alt       = 0b00000010,
    kitty_ctrl      = 0b00000100,
    kitty_super     = 0b00001000,
    kitty_hyper     = 0b00010000,
    kitty_meta      = 0b00100000,
    kitty_caps_lock = 0b01000000,
    kitty_num_lock  = 0b10000000,
} kitty_kbd_mod_t;


extern int stack[];
extern int stack_i;

// kitty_kbd.c
void stack_set(kitty_kbd_t, int);
void stack_push(kitty_kbd_t);
void stack_pop(int);
kitty_kbd_mod_t x_to_kitty(int);

// x.c
extern void (*handler[])(XEvent *);
extern void kpress(XEvent *);
extern void kpress1(XEvent *);

typedef struct {KeySym k; char * s;} kittykey;
static kittykey lvl1_no_mod[] = {
    {.k = XK_BackSpace, .s = "\x7f"},
    {.k = XK_Escape,    .s = "\033[27u"},
    {.k = XK_Insert,    .s = "\033[2~"},
    {.k = XK_Delete,    .s = "\033[3~"},
    {.k = XK_Left,      .s = "\033[D"},
    {.k = XK_Right,     .s = "\033[C"},
    {.k = XK_Up,        .s = "\033[A"},
    {.k = XK_Down,      .s = "\033[B"},
    {.k = XK_Page_Up,   .s = "\033[5~"},
    {.k = XK_Page_Down, .s = "\033[6~"},
    {.k = XK_Home,      .s = "\033[H"},
    {.k = XK_End,       .s = "\033[F"},
    {.k = XK_Print,     .s = "\033[57361u"},
    {.k = XK_F1,        .s = "\033[P"},
    {.k = XK_F2,        .s = "\033[Q"},
    {.k = XK_F3,        .s = "\033[13~"},
    {.k = XK_F4,        .s = "\033[S"},
    {.k = XK_F5,        .s = "\033[15~"},
    {.k = XK_F6,        .s = "\033[17~"},
    {.k = XK_F7,        .s = "\033[18~"},
    {.k = XK_F8,        .s = "\033[19~"},
    {.k = XK_F9,        .s = "\033[20~"},
    {.k = XK_F10,       .s = "\033[21~"},
    {.k = XK_F11,       .s = "\033[23~"},
    {.k = XK_F12,       .s = "\033[24~"},
    // TODO ...
};

// sadly this spec is only slightly less insane; the modifier can be inserted
// anywhere, a 1 can show up for no reason, theres no good way of compressing this
static kittykey lvl1_mod[] = {
    {.k = XK_BackSpace, .s = "\033[127;%uu"},
    {.k = XK_Return,    .s = "\033[13;%uu"},
    {.k = XK_space,     .s = "\033[32;%uu"},
    {.k = XK_Escape,    .s = "\033[27;%uu"},
    {.k = XK_Insert,    .s = "\033[2;%u~"},
    {.k = XK_Delete,    .s = "\033[3;%u~"},
    {.k = XK_Left,      .s = "\033[1;%uD"},
    {.k = XK_Right,     .s = "\033[1;%uC"},
    {.k = XK_Up,        .s = "\033[1;%uA"},
    {.k = XK_Down,      .s = "\033[1;%uB"},
    {.k = XK_Page_Up,   .s = "\033[%u;5~"},
    {.k = XK_Page_Down, .s = "\033[%u;6~"},
    {.k = XK_Home,      .s = "\033[1;%uH"},
    {.k = XK_End,       .s = "\033[1;%uF"},
    {.k = XK_Print,     .s = "\033[57361;%uu"},
    {.k = XK_F1,        .s = "\033[1;%uP"},
    {.k = XK_F2,        .s = "\033[1;%uQ"},
    {.k = XK_F3,        .s = "\033[13;%u~"},
    {.k = XK_F4,        .s = "\033[1;%uS"},
    {.k = XK_F5,        .s = "\033[15;%u~"},
    {.k = XK_F6,        .s = "\033[17;%u~"},
    {.k = XK_F7,        .s = "\033[18;%u~"},
    {.k = XK_F8,        .s = "\033[19;%u~"},
    {.k = XK_F9,        .s = "\033[20;%u~"},
    {.k = XK_F10,       .s = "\033[21;%u~"},
    {.k = XK_F11,       .s = "\033[23;%u~"},
    {.k = XK_F12,       .s = "\033[24;%u~"},
    // TODO ...
};

#endif /* !VV_KITTY_H */
