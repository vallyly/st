st - simple terminal
--------------------
[st is a simple terminal emulator for X which sucks less.](https://st.suckless.org/)

This (WIP) patch implements kitty's keyboard protocol for st. It solves numerous problems with console application development. Read more here:
https://sw.kovidgoyal.net/kitty/keyboard-protocol

Patching
--------

    git clone https://github.com/vallyly/st.git
    cd st
    git diff 35030fc HEAD -- ":(exclude)README*" > st-kbd.diff

Now apply st-kbd.diff to your own source tree.

Requirements
------------
In order to build st you need the Xlib header files.


Installation
------------
Edit config.mk to match your local setup (st is installed into
the /usr/local namespace by default).

Afterwards enter the following command to build and install st (if
necessary as root):

    make clean install


Running st
----------
If you did not install st with make clean install, you must compile
the st terminfo entry with the following command:

    tic -sx st.info

See the man page for additional details.

Credits
-------
Based on Aurélien APTEL <aurelien dot aptel at gmail dot com> bt source code.

