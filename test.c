#include "gf.h"

void ns(game, tick)() {
  ns(draw, print)(0, 0, "Hello, World!");
  }

void ns(game, setup)() {}

void ns(game, cleanup)() {}

void ns(game, keydown)(int key) {
  if(key == 'q') ns(sys, quit)();
}
