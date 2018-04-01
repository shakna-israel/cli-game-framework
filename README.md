# James' CLI Game Framework

A simplistic framework for writing console games with C and ncurses.

---

# Status: Pre-Alpha

The API is subject to frequent breaking changes.

The project isn't guaranteed to build.

***Continue at your own risk.***

---

# Hello, World

```
#include "gf.h"

void ns(game, tick)() {
  ns(draw, print)(0, 0, "Hello, World!");
}

void ns(game, setup)() {}
void ns(game, cleanup)() {}
void ns(game, keydown)(int key) {}
```

We use the ```ns``` macro for some easy namespacing.

All four callbacks do need to be defined, but that's all.

---

# Documentation

Non-existant at this early stage.

---

# LICENSE

```ncurses``` is covered by it's own license, bear in mind for distribution.

However, James' CLI Game Framework is covered by the MIT License.
