# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build & Run (WSL Debian)

Access WSL via: `wsl -d debian`

Install the SDL2 dependency once:
```bash
sudo apt install libsdl2-dev
```

Configure and build (build dir must be on WSL filesystem, not /mnt/d):
```bash
CXX=/usr/bin/g++ cmake -S /mnt/d/HomeProjects/snake -B ~/snake-build -DCMAKE_BUILD_TYPE=Debug
cmake --build ~/snake-build
~/snake-build/snake
```

For a release build: `-DCMAKE_BUILD_TYPE=Release`

GCC 14 is available on Debian — no need to specify g++-13.

## Controls

- Arrow keys or WASD — move
- R — restart after game over
- Escape — quit

## Architecture

All game logic is SDL-free. Only `Renderer` touches SDL2.

```
src/Types.hpp       — Vec2, Direction, GameState, dirVec(), areOpposite()
src/Snake           — Body as std::deque<Vec2>; move/grow/changeDirection
src/Food            — Single Vec2; randomize() picks a cell not occupied by Snake
src/Game            — Owns Snake + Food; drives update(), handleInput(), restart()
src/Renderer        — SDL2 window/renderer; render(const Game&) is the only entry point
src/main.cpp        — SDL init, event loop, fixed-tick game update at 120ms intervals
```

`Game::update()` applies the buffered `pendingDir_` direction, moves the snake, checks wall/self collisions, and handles food consumption. `Renderer` is read-only with respect to game state — it never modifies `Game`.

Score is displayed in the window title (no font dependency).
