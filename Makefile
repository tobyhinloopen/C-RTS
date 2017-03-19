#
# 'make depend' uses makedepend to automatically generate dependencies
#               (dependencies are added to end of Makefile)
# 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc

# define any compile-time flags
CFLAGS = -Wall -g -std=c99

# define any directories containing header files other than /usr/include
#
INCLUDES = -I/usr/local/include -D_THREAD_SAFE

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -lm -L/usr/local/lib

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lSDL2 -framework OpenGL

# define the C source files
SRCS = $(wildcard **/*.c *.c)

# define the C object files
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:.c=.o)

# define the executable file
MAIN = main

#
# The following part of the makefile is generic; it can be used to
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean

all: $(MAIN)
	mkdir -p C-RTS.app/Contents/MacOS
	cp main C-RTS.app/Contents/MacOS
	cp resources/Info.plist C-RTS.app/Contents

$(MAIN): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file)
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) **/*.o *.o *~ $(MAIN)
	rm -rf C-RTS.app

depend: $(SRCS)
	makedepend $(INCLUDES) $^
# DO NOT DELETE

unit/behavior.o: unit/behavior.h vector.h unit.h vector.h world.h unit.h
unit/behavior.o: projectile.h pi.h
unit/behavior_test.o: unit/behavior_test.h unit/behavior.h vector.h unit.h
unit/behavior_test.o: vector.h world.h unit.h projectile.h pi.h
camera.o: camera.h vector3.h /usr/local/include/SDL2/SDL.h
camera.o: /usr/local/include/SDL2/SDL_main.h
camera.o: /usr/local/include/SDL2/SDL_stdinc.h
camera.o: /usr/local/include/SDL2/SDL_config.h
camera.o: /usr/local/include/SDL2/SDL_platform.h
camera.o: /usr/local/include/SDL2/begin_code.h
camera.o: /usr/local/include/SDL2/close_code.h
camera.o: /usr/local/include/SDL2/SDL_assert.h
camera.o: /usr/local/include/SDL2/SDL_atomic.h
camera.o: /usr/local/include/SDL2/SDL_audio.h
camera.o: /usr/local/include/SDL2/SDL_error.h
camera.o: /usr/local/include/SDL2/SDL_endian.h
camera.o: /usr/local/include/SDL2/SDL_mutex.h
camera.o: /usr/local/include/SDL2/SDL_thread.h
camera.o: /usr/local/include/SDL2/SDL_rwops.h
camera.o: /usr/local/include/SDL2/SDL_clipboard.h
camera.o: /usr/local/include/SDL2/SDL_cpuinfo.h
camera.o: /usr/local/include/SDL2/SDL_events.h
camera.o: /usr/local/include/SDL2/SDL_video.h
camera.o: /usr/local/include/SDL2/SDL_pixels.h
camera.o: /usr/local/include/SDL2/SDL_rect.h
camera.o: /usr/local/include/SDL2/SDL_surface.h
camera.o: /usr/local/include/SDL2/SDL_blendmode.h
camera.o: /usr/local/include/SDL2/SDL_keyboard.h
camera.o: /usr/local/include/SDL2/SDL_keycode.h
camera.o: /usr/local/include/SDL2/SDL_scancode.h
camera.o: /usr/local/include/SDL2/SDL_mouse.h
camera.o: /usr/local/include/SDL2/SDL_joystick.h
camera.o: /usr/local/include/SDL2/SDL_gamecontroller.h
camera.o: /usr/local/include/SDL2/SDL_quit.h
camera.o: /usr/local/include/SDL2/SDL_gesture.h
camera.o: /usr/local/include/SDL2/SDL_touch.h
camera.o: /usr/local/include/SDL2/SDL_filesystem.h
camera.o: /usr/local/include/SDL2/SDL_haptic.h
camera.o: /usr/local/include/SDL2/SDL_hints.h
camera.o: /usr/local/include/SDL2/SDL_loadso.h
camera.o: /usr/local/include/SDL2/SDL_log.h
camera.o: /usr/local/include/SDL2/SDL_messagebox.h
camera.o: /usr/local/include/SDL2/SDL_power.h
camera.o: /usr/local/include/SDL2/SDL_render.h
camera.o: /usr/local/include/SDL2/SDL_system.h
camera.o: /usr/local/include/SDL2/SDL_timer.h
camera.o: /usr/local/include/SDL2/SDL_version.h
game.o: game.h world.h unit.h projectile.h vector.h renderer.h vector3.h
game.o: /usr/local/include/SDL2/SDL.h /usr/local/include/SDL2/SDL_main.h
game.o: /usr/local/include/SDL2/SDL_stdinc.h
game.o: /usr/local/include/SDL2/SDL_config.h
game.o: /usr/local/include/SDL2/SDL_platform.h
game.o: /usr/local/include/SDL2/begin_code.h
game.o: /usr/local/include/SDL2/close_code.h
game.o: /usr/local/include/SDL2/SDL_assert.h
game.o: /usr/local/include/SDL2/SDL_atomic.h
game.o: /usr/local/include/SDL2/SDL_audio.h
game.o: /usr/local/include/SDL2/SDL_error.h
game.o: /usr/local/include/SDL2/SDL_endian.h
game.o: /usr/local/include/SDL2/SDL_mutex.h
game.o: /usr/local/include/SDL2/SDL_thread.h
game.o: /usr/local/include/SDL2/SDL_rwops.h
game.o: /usr/local/include/SDL2/SDL_clipboard.h
game.o: /usr/local/include/SDL2/SDL_cpuinfo.h
game.o: /usr/local/include/SDL2/SDL_events.h
game.o: /usr/local/include/SDL2/SDL_video.h
game.o: /usr/local/include/SDL2/SDL_pixels.h
game.o: /usr/local/include/SDL2/SDL_rect.h
game.o: /usr/local/include/SDL2/SDL_surface.h
game.o: /usr/local/include/SDL2/SDL_blendmode.h
game.o: /usr/local/include/SDL2/SDL_keyboard.h
game.o: /usr/local/include/SDL2/SDL_keycode.h
game.o: /usr/local/include/SDL2/SDL_scancode.h
game.o: /usr/local/include/SDL2/SDL_mouse.h
game.o: /usr/local/include/SDL2/SDL_joystick.h
game.o: /usr/local/include/SDL2/SDL_gamecontroller.h
game.o: /usr/local/include/SDL2/SDL_quit.h
game.o: /usr/local/include/SDL2/SDL_gesture.h
game.o: /usr/local/include/SDL2/SDL_touch.h
game.o: /usr/local/include/SDL2/SDL_filesystem.h
game.o: /usr/local/include/SDL2/SDL_haptic.h
game.o: /usr/local/include/SDL2/SDL_hints.h
game.o: /usr/local/include/SDL2/SDL_loadso.h
game.o: /usr/local/include/SDL2/SDL_log.h
game.o: /usr/local/include/SDL2/SDL_messagebox.h
game.o: /usr/local/include/SDL2/SDL_power.h
game.o: /usr/local/include/SDL2/SDL_render.h
game.o: /usr/local/include/SDL2/SDL_system.h
game.o: /usr/local/include/SDL2/SDL_timer.h
game.o: /usr/local/include/SDL2/SDL_version.h opengl.h camera.h test.h pi.h
game.o: unit/behavior.h vector.h unit.h world.h
main.o: test.h game.h world.h unit.h projectile.h vector.h renderer.h
main.o: vector3.h /usr/local/include/SDL2/SDL.h
main.o: /usr/local/include/SDL2/SDL_main.h
main.o: /usr/local/include/SDL2/SDL_stdinc.h
main.o: /usr/local/include/SDL2/SDL_config.h
main.o: /usr/local/include/SDL2/SDL_platform.h
main.o: /usr/local/include/SDL2/begin_code.h
main.o: /usr/local/include/SDL2/close_code.h
main.o: /usr/local/include/SDL2/SDL_assert.h
main.o: /usr/local/include/SDL2/SDL_atomic.h
main.o: /usr/local/include/SDL2/SDL_audio.h
main.o: /usr/local/include/SDL2/SDL_error.h
main.o: /usr/local/include/SDL2/SDL_endian.h
main.o: /usr/local/include/SDL2/SDL_mutex.h
main.o: /usr/local/include/SDL2/SDL_thread.h
main.o: /usr/local/include/SDL2/SDL_rwops.h
main.o: /usr/local/include/SDL2/SDL_clipboard.h
main.o: /usr/local/include/SDL2/SDL_cpuinfo.h
main.o: /usr/local/include/SDL2/SDL_events.h
main.o: /usr/local/include/SDL2/SDL_video.h
main.o: /usr/local/include/SDL2/SDL_pixels.h
main.o: /usr/local/include/SDL2/SDL_rect.h
main.o: /usr/local/include/SDL2/SDL_surface.h
main.o: /usr/local/include/SDL2/SDL_blendmode.h
main.o: /usr/local/include/SDL2/SDL_keyboard.h
main.o: /usr/local/include/SDL2/SDL_keycode.h
main.o: /usr/local/include/SDL2/SDL_scancode.h
main.o: /usr/local/include/SDL2/SDL_mouse.h
main.o: /usr/local/include/SDL2/SDL_joystick.h
main.o: /usr/local/include/SDL2/SDL_gamecontroller.h
main.o: /usr/local/include/SDL2/SDL_quit.h
main.o: /usr/local/include/SDL2/SDL_gesture.h
main.o: /usr/local/include/SDL2/SDL_touch.h
main.o: /usr/local/include/SDL2/SDL_filesystem.h
main.o: /usr/local/include/SDL2/SDL_haptic.h
main.o: /usr/local/include/SDL2/SDL_hints.h
main.o: /usr/local/include/SDL2/SDL_loadso.h
main.o: /usr/local/include/SDL2/SDL_log.h
main.o: /usr/local/include/SDL2/SDL_messagebox.h
main.o: /usr/local/include/SDL2/SDL_power.h
main.o: /usr/local/include/SDL2/SDL_render.h
main.o: /usr/local/include/SDL2/SDL_system.h
main.o: /usr/local/include/SDL2/SDL_timer.h
main.o: /usr/local/include/SDL2/SDL_version.h opengl.h
projectile.o: projectile.h vector.h
renderer.o: /usr/local/include/SDL2/SDL.h /usr/local/include/SDL2/SDL_main.h
renderer.o: /usr/local/include/SDL2/SDL_stdinc.h
renderer.o: /usr/local/include/SDL2/SDL_config.h
renderer.o: /usr/local/include/SDL2/SDL_platform.h
renderer.o: /usr/local/include/SDL2/begin_code.h
renderer.o: /usr/local/include/SDL2/close_code.h
renderer.o: /usr/local/include/SDL2/SDL_assert.h
renderer.o: /usr/local/include/SDL2/SDL_atomic.h
renderer.o: /usr/local/include/SDL2/SDL_audio.h
renderer.o: /usr/local/include/SDL2/SDL_error.h
renderer.o: /usr/local/include/SDL2/SDL_endian.h
renderer.o: /usr/local/include/SDL2/SDL_mutex.h
renderer.o: /usr/local/include/SDL2/SDL_thread.h
renderer.o: /usr/local/include/SDL2/SDL_rwops.h
renderer.o: /usr/local/include/SDL2/SDL_clipboard.h
renderer.o: /usr/local/include/SDL2/SDL_cpuinfo.h
renderer.o: /usr/local/include/SDL2/SDL_events.h
renderer.o: /usr/local/include/SDL2/SDL_video.h
renderer.o: /usr/local/include/SDL2/SDL_pixels.h
renderer.o: /usr/local/include/SDL2/SDL_rect.h
renderer.o: /usr/local/include/SDL2/SDL_surface.h
renderer.o: /usr/local/include/SDL2/SDL_blendmode.h
renderer.o: /usr/local/include/SDL2/SDL_keyboard.h
renderer.o: /usr/local/include/SDL2/SDL_keycode.h
renderer.o: /usr/local/include/SDL2/SDL_scancode.h
renderer.o: /usr/local/include/SDL2/SDL_mouse.h
renderer.o: /usr/local/include/SDL2/SDL_joystick.h
renderer.o: /usr/local/include/SDL2/SDL_gamecontroller.h
renderer.o: /usr/local/include/SDL2/SDL_quit.h
renderer.o: /usr/local/include/SDL2/SDL_gesture.h
renderer.o: /usr/local/include/SDL2/SDL_touch.h
renderer.o: /usr/local/include/SDL2/SDL_filesystem.h
renderer.o: /usr/local/include/SDL2/SDL_haptic.h
renderer.o: /usr/local/include/SDL2/SDL_hints.h
renderer.o: /usr/local/include/SDL2/SDL_loadso.h
renderer.o: /usr/local/include/SDL2/SDL_log.h
renderer.o: /usr/local/include/SDL2/SDL_messagebox.h
renderer.o: /usr/local/include/SDL2/SDL_power.h
renderer.o: /usr/local/include/SDL2/SDL_render.h
renderer.o: /usr/local/include/SDL2/SDL_system.h
renderer.o: /usr/local/include/SDL2/SDL_timer.h
renderer.o: /usr/local/include/SDL2/SDL_version.h renderer.h world.h unit.h
renderer.o: projectile.h vector.h vector3.h opengl.h pi.h
renderer_test.o: renderer_test.h renderer.h world.h unit.h projectile.h
renderer_test.o: vector.h vector3.h /usr/local/include/SDL2/SDL.h
renderer_test.o: /usr/local/include/SDL2/SDL_main.h
renderer_test.o: /usr/local/include/SDL2/SDL_stdinc.h
renderer_test.o: /usr/local/include/SDL2/SDL_config.h
renderer_test.o: /usr/local/include/SDL2/SDL_platform.h
renderer_test.o: /usr/local/include/SDL2/begin_code.h
renderer_test.o: /usr/local/include/SDL2/close_code.h
renderer_test.o: /usr/local/include/SDL2/SDL_assert.h
renderer_test.o: /usr/local/include/SDL2/SDL_atomic.h
renderer_test.o: /usr/local/include/SDL2/SDL_audio.h
renderer_test.o: /usr/local/include/SDL2/SDL_error.h
renderer_test.o: /usr/local/include/SDL2/SDL_endian.h
renderer_test.o: /usr/local/include/SDL2/SDL_mutex.h
renderer_test.o: /usr/local/include/SDL2/SDL_thread.h
renderer_test.o: /usr/local/include/SDL2/SDL_rwops.h
renderer_test.o: /usr/local/include/SDL2/SDL_clipboard.h
renderer_test.o: /usr/local/include/SDL2/SDL_cpuinfo.h
renderer_test.o: /usr/local/include/SDL2/SDL_events.h
renderer_test.o: /usr/local/include/SDL2/SDL_video.h
renderer_test.o: /usr/local/include/SDL2/SDL_pixels.h
renderer_test.o: /usr/local/include/SDL2/SDL_rect.h
renderer_test.o: /usr/local/include/SDL2/SDL_surface.h
renderer_test.o: /usr/local/include/SDL2/SDL_blendmode.h
renderer_test.o: /usr/local/include/SDL2/SDL_keyboard.h
renderer_test.o: /usr/local/include/SDL2/SDL_keycode.h
renderer_test.o: /usr/local/include/SDL2/SDL_scancode.h
renderer_test.o: /usr/local/include/SDL2/SDL_mouse.h
renderer_test.o: /usr/local/include/SDL2/SDL_joystick.h
renderer_test.o: /usr/local/include/SDL2/SDL_gamecontroller.h
renderer_test.o: /usr/local/include/SDL2/SDL_quit.h
renderer_test.o: /usr/local/include/SDL2/SDL_gesture.h
renderer_test.o: /usr/local/include/SDL2/SDL_touch.h
renderer_test.o: /usr/local/include/SDL2/SDL_filesystem.h
renderer_test.o: /usr/local/include/SDL2/SDL_haptic.h
renderer_test.o: /usr/local/include/SDL2/SDL_hints.h
renderer_test.o: /usr/local/include/SDL2/SDL_loadso.h
renderer_test.o: /usr/local/include/SDL2/SDL_log.h
renderer_test.o: /usr/local/include/SDL2/SDL_messagebox.h
renderer_test.o: /usr/local/include/SDL2/SDL_power.h
renderer_test.o: /usr/local/include/SDL2/SDL_render.h
renderer_test.o: /usr/local/include/SDL2/SDL_system.h
renderer_test.o: /usr/local/include/SDL2/SDL_timer.h
renderer_test.o: /usr/local/include/SDL2/SDL_version.h opengl.h
test.o: test.h unit_test.h world_test.h vector_test.h unit/behavior_test.h
test.o: renderer_test.h
unit.o: unit.h vector.h pi.h
unit_test.o: unit_test.h unit.h pi.h
vector.o: vector.h pi.h
vector3.o: vector3.h
vector_test.o: vector_test.h vector.h pi.h
world.o: world.h unit.h projectile.h vector.h
world_test.o: world_test.h world.h unit.h projectile.h vector.h
