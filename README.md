# C-RTS

This is a private project where a simple RTS is being made in C. This code is public for code review purposes only. All rights reserved.

This project is for fun only.


## Installation

    brew install makedepend sdl2
    make depend
    make


## Controls

  - WSAD: Move camera
  - QE: Zoom


## Intended code structure

My intent is to create a data structure representing the full game state that is being manipulated by modules.

### Multithreading

Multithreading might be achieved by defining dependencies of modules. Lets say we have 3 modules: A, B and C. Also, module B requires module A to have executed, but module C does not.

By defining this dependency of the modules, we can use a thread-pool to execute the modules. The thread-pool initializes a set of threads that executes all modules that have no dependency. Every time a module has finished executing, we can check for new modules to execute.

Manipulating the state of the game is very tricky to do in a multithreaded manner. Ideally, no writes are done concurrently on the game-data.
