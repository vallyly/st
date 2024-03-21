#include "kitty_kbd.h"
#include <X11/X.h>
#include <X11/Xlib.h>
#include <string.h>

/* TODO :
 * Terminals must maintain separate stacks
 * for the main and alternate screens.
 */
#define STACK_N 2
int stack[STACK_N] = {0};
int stack_i = 0;

void stack_dirty(void);
extern void die(const char *, ...);

#define valid_kbd_t(i) (i >= kitty_lvl0 && i <= kitty_max)

#define stack_popfront() \
    memmove(stack, stack + 1, sizeof(stack) - sizeof(*stack))


void stack_set(kitty_kbd_t flags, int mode) {
    switch (mode) {
        case 1: /* The value 1 means all set bits are set and all unset bits are reset. */
            break;
        case 2: /* The value 2 means all set bits are set, unset bits are left unchanged.  */
            flags |= stack[stack_i];
            break;
        case 3: /* The value 3 means all set bits are reset, unset bits are left unchanged.*/
            flags = stack[stack_i] & ~flags;
            break;
        default:
            return;
    }
    if (!valid_kbd_t(flags)) return;
    stack[stack_i] = flags;
    stack_dirty();
}


void stack_push(kitty_kbd_t flags) {
    if (!valid_kbd_t(flags)) return;
    /* If a push request is received and the stack is full,
     * the oldest entry from the stack must be evicted. */
    if (stack_i + 1 == STACK_N) {
        stack_popfront();
        stack_i--;
    }
    stack[++stack_i] = flags;
    stack_dirty();
}


void stack_pop(int n) {
    /* If a pop request is received that empties the stack,
     * all flags are reset */
    if (stack_i - n < 0) {
        stack[0] = 0;
        stack_i = 0;
    } else {
        stack_i -= n;
    }
    stack_dirty();
}


void stack_dirty(void) {
    // redundant
    if (!valid_kbd_t(stack[stack_i])) die("bad stack.\n");

    if (stack[stack_i] & kitty_lvl1)
        handler[KeyPress] = kpress_kitty;
    else
        handler[KeyPress] = kpress;


    if (stack[stack_i] & kitty_lvl2)
        handler[KeyRelease] = krelease_kitty;
    else
        handler[KeyRelease] = 0;
}

kitty_kbd_mod_t mod_x_to_kitty(int state) {
    // NOTE : add 1 to ret before writing it to the tty. (???)
    // xmodmap -pm

    kitty_kbd_mod_t ret = 0;

    if (state & ShiftMask)
        ret |= kitty_shift;
    if (state & Mod1Mask)
        ret |= kitty_alt;
    if (state & ControlMask)
        ret |= kitty_ctrl;
    if (state & Mod2Mask)
        ret |= kitty_num_lock;
    if (state & Mod4Mask)
        ret |= kitty_super;
    if (state & LockMask)
        ret |= kitty_caps_lock;
    // TODO hyper, meta ..?

    return ret;
}
