#ifndef GEZIRA_STDIN_KEY_EVENT
#define GEZIRA_STDIN_KEY_EVENT

#include <termios.h>

static void
gezira_stdin_set_echo (int on)
{
    struct termios t;
    tcgetattr (STDIN_FILENO, &t);
    if (on)
        t.c_lflag |= ECHO;
    else
        t.c_lflag &= !ECHO;
    tcsetattr (STDIN_FILENO, TCSANOW, &t);
}

static int
gezira_stdin_has_input ()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO (&fds);
    FD_SET (STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET (0, &fds);
}

static int
gezira_stdin_key_pressed ()
{
    struct termios oldt, newt;
    tcgetattr (STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 1;
    tcsetattr (STDIN_FILENO, TCSANOW, &newt);
    int c = gezira_stdin_has_input () ? getchar() : -1;
    tcsetattr (STDIN_FILENO, TCSANOW, &oldt);
    return c;
}

#endif
