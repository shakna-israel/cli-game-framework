#ifndef JAMES_GAME_FRAMEWORK

/* Namespaces. Because I want them.
   However, debug symbols should
   still be pretty clear.
*/
#define ns(_a, _b) _b ## _from_ ## _a ## _library

/* Dependencies */
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
/* End Dependencies */

/* Screen values */
int ns(screen, x) = 0;
int ns(screen, y) = 0;
int ns(screen, min_x) = 0;
int ns(screen, min_y) = 0;
/* End Screen values */

/* Internal Callbacks */
void ns(jgf, init)(void);
void ns(jgf, loop)(void);
void ns(jgf, exit)(void);
void ns(jgf, key)(void);
/* End Internal Callbacks */

/* User Callbacks */
void ns(game, setup)(void);
void ns(game, tick)(void);
void ns(game, cleanup)(void);
void ns(game, keydown)(int k);
/* End User Callbacks */

/* Essentials */
void ns(sys, quit)(void);
/* End Essentials */

void ns(sys, quit)(void) {
  ns(jgf, exit)();
  exit(0);
}

/* Definition for main,
   so callbacks can reference it.
*/
int main(int argc, char* argv[]);

/* Drawing functions */
#define print_from_draw_library(_x, _y, ...) mvprintw(_y, _x, __VA_ARGS__)
/* End drawing functions */

/* Sets up curses, etc */
void ns(jgf, init)(void) {
  initscr();
  noecho();
  curs_set(FALSE);
  cbreak();
  clear();
  timeout(100);

  /* User init callback */
  ns(game, setup)();
}

/* Tick the game and screen */
void ns(jgf, loop)(void) {
  /* Get the screen size */
  getmaxyx(stdscr, ns(screen, y), ns(screen, x));

  if(ns(screen, min_y) > 0 || ns(screen, min_x) > 0)
    if(ns(screen, y) < ns(screen, min_y) || ns(screen, x) < ns(screen, min_x)) {
      mvprintw(0, 0, "Terminal screen too small. Minimum: %d x %d", ns(screen, min_x), ns(screen, min_y));
      mvprintw(1, 0, "Resize terminal, or press any key to quit.");
      refresh();
      if(getch() != -1)
        ns(sys, quit)();
      return;
    }

  /* Check keyboard state */
  ns(jgf, key)();

  /* User looping callback */
  ns(game, tick)();

  /* Paint the screen */
  refresh();
}

void ns(jgf, exit)(void) {
  /* User exit callback */
  ns(game, cleanup)();

  /* Shutdown curses */
  nocbreak();
  endwin();
}

void ns(jgf, key)(void) {
  int x = getch();
  ns(game, keydown)(x);
}

int main(int argc, char* argv[]) {
  ns(jgf, init)();
  while(1)
    ns(jgf, loop)();
  ns(jgf, exit)();
}

#define JAMES_GAME_FRAMEWORK
#endif
