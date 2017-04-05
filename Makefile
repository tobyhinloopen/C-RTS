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

mod/camera_update.o: mod/camera_update.h game.h world.h unit.h vector.h
mod/camera_update.o: projectile.h factory.h map.h shape.h renderer.h
mod/camera_update.o: vector3.h /usr/local/include/SDL2/SDL.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_main.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_config.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_platform.h
mod/camera_update.o: /usr/local/include/SDL2/begin_code.h
mod/camera_update.o: /usr/local/include/SDL2/close_code.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_assert.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_atomic.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_audio.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_error.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_endian.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_mutex.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_thread.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_rwops.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_events.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_video.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_pixels.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_rect.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_surface.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_keycode.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_scancode.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_mouse.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_joystick.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_quit.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_gesture.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_touch.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_haptic.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_hints.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_loadso.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_log.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_power.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_render.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_system.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_timer.h
mod/camera_update.o: /usr/local/include/SDL2/SDL_version.h opengl.h grid.h
mod/camera_update.o: kdtree.h scalable_grid.h team_id.h camera.h
mod/event.o: mod/event.h game.h world.h unit.h vector.h projectile.h
mod/event.o: factory.h map.h shape.h renderer.h vector3.h
mod/event.o: /usr/local/include/SDL2/SDL.h /usr/local/include/SDL2/SDL_main.h
mod/event.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/event.o: /usr/local/include/SDL2/SDL_config.h
mod/event.o: /usr/local/include/SDL2/SDL_platform.h
mod/event.o: /usr/local/include/SDL2/begin_code.h
mod/event.o: /usr/local/include/SDL2/close_code.h
mod/event.o: /usr/local/include/SDL2/SDL_assert.h
mod/event.o: /usr/local/include/SDL2/SDL_atomic.h
mod/event.o: /usr/local/include/SDL2/SDL_audio.h
mod/event.o: /usr/local/include/SDL2/SDL_error.h
mod/event.o: /usr/local/include/SDL2/SDL_endian.h
mod/event.o: /usr/local/include/SDL2/SDL_mutex.h
mod/event.o: /usr/local/include/SDL2/SDL_thread.h
mod/event.o: /usr/local/include/SDL2/SDL_rwops.h
mod/event.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/event.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/event.o: /usr/local/include/SDL2/SDL_events.h
mod/event.o: /usr/local/include/SDL2/SDL_video.h
mod/event.o: /usr/local/include/SDL2/SDL_pixels.h
mod/event.o: /usr/local/include/SDL2/SDL_rect.h
mod/event.o: /usr/local/include/SDL2/SDL_surface.h
mod/event.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/event.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/event.o: /usr/local/include/SDL2/SDL_keycode.h
mod/event.o: /usr/local/include/SDL2/SDL_scancode.h
mod/event.o: /usr/local/include/SDL2/SDL_mouse.h
mod/event.o: /usr/local/include/SDL2/SDL_joystick.h
mod/event.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/event.o: /usr/local/include/SDL2/SDL_quit.h
mod/event.o: /usr/local/include/SDL2/SDL_gesture.h
mod/event.o: /usr/local/include/SDL2/SDL_touch.h
mod/event.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/event.o: /usr/local/include/SDL2/SDL_haptic.h
mod/event.o: /usr/local/include/SDL2/SDL_hints.h
mod/event.o: /usr/local/include/SDL2/SDL_loadso.h
mod/event.o: /usr/local/include/SDL2/SDL_log.h
mod/event.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/event.o: /usr/local/include/SDL2/SDL_power.h
mod/event.o: /usr/local/include/SDL2/SDL_render.h
mod/event.o: /usr/local/include/SDL2/SDL_system.h
mod/event.o: /usr/local/include/SDL2/SDL_timer.h
mod/event.o: /usr/local/include/SDL2/SDL_version.h opengl.h grid.h kdtree.h
mod/event.o: scalable_grid.h team_id.h vector3.h camera.h
mod/factory_spawn.o: mod/factory_spawn.h game.h world.h unit.h vector.h
mod/factory_spawn.o: projectile.h factory.h map.h shape.h renderer.h
mod/factory_spawn.o: vector3.h /usr/local/include/SDL2/SDL.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_main.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_config.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_platform.h
mod/factory_spawn.o: /usr/local/include/SDL2/begin_code.h
mod/factory_spawn.o: /usr/local/include/SDL2/close_code.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_assert.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_atomic.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_audio.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_error.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_endian.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_mutex.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_thread.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_rwops.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_events.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_video.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_pixels.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_rect.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_surface.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_keycode.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_scancode.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_mouse.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_joystick.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_quit.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_gesture.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_touch.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_haptic.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_hints.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_loadso.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_log.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_power.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_render.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_system.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_timer.h
mod/factory_spawn.o: /usr/local/include/SDL2/SDL_version.h opengl.h grid.h
mod/factory_spawn.o: kdtree.h scalable_grid.h team_id.h world.h team_id.h
mod/factory_spawn.o: pi.h
mod/grid.o: grid.h grid.h
mod/kdtree.o: kdtree.h vector.h kdtree.h
mod/print_performance.o: mod/print_performance.h game.h world.h unit.h
mod/print_performance.o: vector.h projectile.h factory.h map.h shape.h
mod/print_performance.o: renderer.h vector3.h /usr/local/include/SDL2/SDL.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_main.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_config.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_platform.h
mod/print_performance.o: /usr/local/include/SDL2/begin_code.h
mod/print_performance.o: /usr/local/include/SDL2/close_code.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_assert.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_atomic.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_audio.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_error.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_endian.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_mutex.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_thread.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_rwops.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_events.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_video.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_pixels.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_rect.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_surface.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_keycode.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_scancode.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_mouse.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_joystick.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_quit.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_gesture.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_touch.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_haptic.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_hints.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_loadso.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_log.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_power.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_render.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_system.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_timer.h
mod/print_performance.o: /usr/local/include/SDL2/SDL_version.h opengl.h
mod/print_performance.o: grid.h kdtree.h scalable_grid.h team_id.h
mod/projectile_unit_impact.o: mod/projectile_unit_impact.h game.h world.h
mod/projectile_unit_impact.o: unit.h vector.h projectile.h factory.h map.h
mod/projectile_unit_impact.o: shape.h renderer.h vector3.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_main.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_config.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_platform.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/begin_code.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/close_code.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_assert.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_atomic.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_audio.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_error.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_endian.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_mutex.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_thread.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_rwops.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_events.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_video.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_pixels.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_rect.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_surface.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_keycode.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_scancode.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_mouse.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_joystick.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_quit.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_gesture.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_touch.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_haptic.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_hints.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_loadso.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_log.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_power.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_render.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_system.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_timer.h
mod/projectile_unit_impact.o: /usr/local/include/SDL2/SDL_version.h opengl.h
mod/projectile_unit_impact.o: grid.h kdtree.h scalable_grid.h team_id.h
mod/projectile_unit_impact.o: world.h config.h scalable_grid.h
mod/random_spawn.o: mod/random_spawn.h game.h world.h unit.h vector.h
mod/random_spawn.o: projectile.h factory.h map.h shape.h renderer.h vector3.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_main.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_config.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_platform.h
mod/random_spawn.o: /usr/local/include/SDL2/begin_code.h
mod/random_spawn.o: /usr/local/include/SDL2/close_code.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_assert.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_atomic.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_audio.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_error.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_endian.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_mutex.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_thread.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_rwops.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_events.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_video.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_pixels.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_rect.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_surface.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_keycode.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_scancode.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_mouse.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_joystick.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_quit.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_gesture.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_touch.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_haptic.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_hints.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_loadso.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_log.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_power.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_render.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_system.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_timer.h
mod/random_spawn.o: /usr/local/include/SDL2/SDL_version.h opengl.h grid.h
mod/random_spawn.o: kdtree.h scalable_grid.h team_id.h pi.h rand_range.h
mod/random_spawn.o: team_id.h
mod/render.o: mod/render.h game.h world.h unit.h vector.h projectile.h
mod/render.o: factory.h map.h shape.h renderer.h vector3.h
mod/render.o: /usr/local/include/SDL2/SDL.h
mod/render.o: /usr/local/include/SDL2/SDL_main.h
mod/render.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/render.o: /usr/local/include/SDL2/SDL_config.h
mod/render.o: /usr/local/include/SDL2/SDL_platform.h
mod/render.o: /usr/local/include/SDL2/begin_code.h
mod/render.o: /usr/local/include/SDL2/close_code.h
mod/render.o: /usr/local/include/SDL2/SDL_assert.h
mod/render.o: /usr/local/include/SDL2/SDL_atomic.h
mod/render.o: /usr/local/include/SDL2/SDL_audio.h
mod/render.o: /usr/local/include/SDL2/SDL_error.h
mod/render.o: /usr/local/include/SDL2/SDL_endian.h
mod/render.o: /usr/local/include/SDL2/SDL_mutex.h
mod/render.o: /usr/local/include/SDL2/SDL_thread.h
mod/render.o: /usr/local/include/SDL2/SDL_rwops.h
mod/render.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/render.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/render.o: /usr/local/include/SDL2/SDL_events.h
mod/render.o: /usr/local/include/SDL2/SDL_video.h
mod/render.o: /usr/local/include/SDL2/SDL_pixels.h
mod/render.o: /usr/local/include/SDL2/SDL_rect.h
mod/render.o: /usr/local/include/SDL2/SDL_surface.h
mod/render.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/render.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/render.o: /usr/local/include/SDL2/SDL_keycode.h
mod/render.o: /usr/local/include/SDL2/SDL_scancode.h
mod/render.o: /usr/local/include/SDL2/SDL_mouse.h
mod/render.o: /usr/local/include/SDL2/SDL_joystick.h
mod/render.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/render.o: /usr/local/include/SDL2/SDL_quit.h
mod/render.o: /usr/local/include/SDL2/SDL_gesture.h
mod/render.o: /usr/local/include/SDL2/SDL_touch.h
mod/render.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/render.o: /usr/local/include/SDL2/SDL_haptic.h
mod/render.o: /usr/local/include/SDL2/SDL_hints.h
mod/render.o: /usr/local/include/SDL2/SDL_loadso.h
mod/render.o: /usr/local/include/SDL2/SDL_log.h
mod/render.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/render.o: /usr/local/include/SDL2/SDL_power.h
mod/render.o: /usr/local/include/SDL2/SDL_render.h
mod/render.o: /usr/local/include/SDL2/SDL_system.h
mod/render.o: /usr/local/include/SDL2/SDL_timer.h
mod/render.o: /usr/local/include/SDL2/SDL_version.h opengl.h grid.h kdtree.h
mod/render.o: scalable_grid.h team_id.h renderer.h camera.h
mod/scalable_grid.o: scalable_grid.h grid.h vector.h scalable_grid.h config.h
mod/unit_behavior.o: mod/unit_behavior.h game.h world.h unit.h vector.h
mod/unit_behavior.o: projectile.h factory.h map.h shape.h renderer.h
mod/unit_behavior.o: vector3.h /usr/local/include/SDL2/SDL.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_main.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_config.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_platform.h
mod/unit_behavior.o: /usr/local/include/SDL2/begin_code.h
mod/unit_behavior.o: /usr/local/include/SDL2/close_code.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_assert.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_atomic.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_audio.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_error.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_endian.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_mutex.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_thread.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_rwops.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_events.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_video.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_pixels.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_rect.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_surface.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_keycode.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_scancode.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_mouse.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_joystick.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_quit.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_gesture.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_touch.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_haptic.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_hints.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_loadso.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_log.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_power.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_render.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_system.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_timer.h
mod/unit_behavior.o: /usr/local/include/SDL2/SDL_version.h opengl.h grid.h
mod/unit_behavior.o: kdtree.h scalable_grid.h team_id.h unit/behavior.h
mod/unit_behavior.o: vector.h unit.h world.h config.h grid.h kdtree.h
mod/unit_projectile_spawn.o: mod/unit_projectile_spawn.h game.h world.h
mod/unit_projectile_spawn.o: unit.h vector.h projectile.h factory.h map.h
mod/unit_projectile_spawn.o: shape.h renderer.h vector3.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_main.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_config.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_platform.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/begin_code.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/close_code.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_assert.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_atomic.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_audio.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_error.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_endian.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_mutex.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_thread.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_rwops.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_events.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_video.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_pixels.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_rect.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_surface.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_keycode.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_scancode.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_mouse.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_joystick.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_quit.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_gesture.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_touch.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_haptic.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_hints.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_loadso.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_log.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_power.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_render.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_system.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_timer.h
mod/unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_version.h opengl.h
mod/unit_projectile_spawn.o: grid.h kdtree.h scalable_grid.h team_id.h
mod/unit_projectile_spawn.o: rand_range.h
mod/world_update.o: mod/world_update.h game.h world.h unit.h vector.h
mod/world_update.o: projectile.h factory.h map.h shape.h renderer.h vector3.h
mod/world_update.o: /usr/local/include/SDL2/SDL.h
mod/world_update.o: /usr/local/include/SDL2/SDL_main.h
mod/world_update.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/world_update.o: /usr/local/include/SDL2/SDL_config.h
mod/world_update.o: /usr/local/include/SDL2/SDL_platform.h
mod/world_update.o: /usr/local/include/SDL2/begin_code.h
mod/world_update.o: /usr/local/include/SDL2/close_code.h
mod/world_update.o: /usr/local/include/SDL2/SDL_assert.h
mod/world_update.o: /usr/local/include/SDL2/SDL_atomic.h
mod/world_update.o: /usr/local/include/SDL2/SDL_audio.h
mod/world_update.o: /usr/local/include/SDL2/SDL_error.h
mod/world_update.o: /usr/local/include/SDL2/SDL_endian.h
mod/world_update.o: /usr/local/include/SDL2/SDL_mutex.h
mod/world_update.o: /usr/local/include/SDL2/SDL_thread.h
mod/world_update.o: /usr/local/include/SDL2/SDL_rwops.h
mod/world_update.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/world_update.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/world_update.o: /usr/local/include/SDL2/SDL_events.h
mod/world_update.o: /usr/local/include/SDL2/SDL_video.h
mod/world_update.o: /usr/local/include/SDL2/SDL_pixels.h
mod/world_update.o: /usr/local/include/SDL2/SDL_rect.h
mod/world_update.o: /usr/local/include/SDL2/SDL_surface.h
mod/world_update.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/world_update.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/world_update.o: /usr/local/include/SDL2/SDL_keycode.h
mod/world_update.o: /usr/local/include/SDL2/SDL_scancode.h
mod/world_update.o: /usr/local/include/SDL2/SDL_mouse.h
mod/world_update.o: /usr/local/include/SDL2/SDL_joystick.h
mod/world_update.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/world_update.o: /usr/local/include/SDL2/SDL_quit.h
mod/world_update.o: /usr/local/include/SDL2/SDL_gesture.h
mod/world_update.o: /usr/local/include/SDL2/SDL_touch.h
mod/world_update.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/world_update.o: /usr/local/include/SDL2/SDL_haptic.h
mod/world_update.o: /usr/local/include/SDL2/SDL_hints.h
mod/world_update.o: /usr/local/include/SDL2/SDL_loadso.h
mod/world_update.o: /usr/local/include/SDL2/SDL_log.h
mod/world_update.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/world_update.o: /usr/local/include/SDL2/SDL_power.h
mod/world_update.o: /usr/local/include/SDL2/SDL_render.h
mod/world_update.o: /usr/local/include/SDL2/SDL_system.h
mod/world_update.o: /usr/local/include/SDL2/SDL_timer.h
mod/world_update.o: /usr/local/include/SDL2/SDL_version.h opengl.h grid.h
mod/world_update.o: kdtree.h scalable_grid.h team_id.h world.h
unit/behavior.o: unit/behavior.h vector.h unit.h world.h pi.h
unit/behavior_test.o: unit/behavior_test.h unit/behavior.h vector.h unit.h
unit/behavior_test.o: world.h pi.h
benchmark.o: benchmark.h game.h world.h unit.h vector.h projectile.h
benchmark.o: factory.h map.h shape.h renderer.h vector3.h
benchmark.o: /usr/local/include/SDL2/SDL.h /usr/local/include/SDL2/SDL_main.h
benchmark.o: /usr/local/include/SDL2/SDL_stdinc.h
benchmark.o: /usr/local/include/SDL2/SDL_config.h
benchmark.o: /usr/local/include/SDL2/SDL_platform.h
benchmark.o: /usr/local/include/SDL2/begin_code.h
benchmark.o: /usr/local/include/SDL2/close_code.h
benchmark.o: /usr/local/include/SDL2/SDL_assert.h
benchmark.o: /usr/local/include/SDL2/SDL_atomic.h
benchmark.o: /usr/local/include/SDL2/SDL_audio.h
benchmark.o: /usr/local/include/SDL2/SDL_error.h
benchmark.o: /usr/local/include/SDL2/SDL_endian.h
benchmark.o: /usr/local/include/SDL2/SDL_mutex.h
benchmark.o: /usr/local/include/SDL2/SDL_thread.h
benchmark.o: /usr/local/include/SDL2/SDL_rwops.h
benchmark.o: /usr/local/include/SDL2/SDL_clipboard.h
benchmark.o: /usr/local/include/SDL2/SDL_cpuinfo.h
benchmark.o: /usr/local/include/SDL2/SDL_events.h
benchmark.o: /usr/local/include/SDL2/SDL_video.h
benchmark.o: /usr/local/include/SDL2/SDL_pixels.h
benchmark.o: /usr/local/include/SDL2/SDL_rect.h
benchmark.o: /usr/local/include/SDL2/SDL_surface.h
benchmark.o: /usr/local/include/SDL2/SDL_blendmode.h
benchmark.o: /usr/local/include/SDL2/SDL_keyboard.h
benchmark.o: /usr/local/include/SDL2/SDL_keycode.h
benchmark.o: /usr/local/include/SDL2/SDL_scancode.h
benchmark.o: /usr/local/include/SDL2/SDL_mouse.h
benchmark.o: /usr/local/include/SDL2/SDL_joystick.h
benchmark.o: /usr/local/include/SDL2/SDL_gamecontroller.h
benchmark.o: /usr/local/include/SDL2/SDL_quit.h
benchmark.o: /usr/local/include/SDL2/SDL_gesture.h
benchmark.o: /usr/local/include/SDL2/SDL_touch.h
benchmark.o: /usr/local/include/SDL2/SDL_filesystem.h
benchmark.o: /usr/local/include/SDL2/SDL_haptic.h
benchmark.o: /usr/local/include/SDL2/SDL_hints.h
benchmark.o: /usr/local/include/SDL2/SDL_loadso.h
benchmark.o: /usr/local/include/SDL2/SDL_log.h
benchmark.o: /usr/local/include/SDL2/SDL_messagebox.h
benchmark.o: /usr/local/include/SDL2/SDL_power.h
benchmark.o: /usr/local/include/SDL2/SDL_render.h
benchmark.o: /usr/local/include/SDL2/SDL_system.h
benchmark.o: /usr/local/include/SDL2/SDL_timer.h
benchmark.o: /usr/local/include/SDL2/SDL_version.h opengl.h grid.h kdtree.h
benchmark.o: scalable_grid.h team_id.h
camera.o: camera.h vector3.h
factory.o: factory.h vector.h unit.h
factory_test.o: factory_test.h factory.h vector.h unit.h
game.o: game.h world.h unit.h vector.h projectile.h factory.h map.h shape.h
game.o: renderer.h vector3.h /usr/local/include/SDL2/SDL.h
game.o: /usr/local/include/SDL2/SDL_main.h
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
game.o: /usr/local/include/SDL2/SDL_version.h opengl.h grid.h kdtree.h
game.o: scalable_grid.h team_id.h unit/behavior.h vector.h unit.h world.h
game.o: rand_range.h
grid.o: grid.h
grid_test.o: grid_test.h grid.h
kdtree.o: kdtree.h vector.h
kdtree_test.o: kdtree_test.h kdtree.h vector.h
main.o: game.h world.h unit.h vector.h projectile.h factory.h map.h shape.h
main.o: renderer.h vector3.h /usr/local/include/SDL2/SDL.h
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
main.o: /usr/local/include/SDL2/SDL_version.h opengl.h grid.h kdtree.h
main.o: scalable_grid.h team_id.h config.h benchmark.h mod/scalable_grid.h
main.o: game.h mod/kdtree.h mod/event.h mod/unit_projectile_spawn.h
main.o: mod/projectile_unit_impact.h mod/unit_behavior.h mod/factory_spawn.h
main.o: mod/world_update.h mod/camera_update.h mod/render.h
main.o: mod/print_performance.h
map.o: map.h vector.h shape.h
projectile.o: projectile.h vector.h
rand_range.o: rand_range.h
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
renderer.o: vector.h projectile.h factory.h vector3.h opengl.h pi.h team_id.h
renderer_test.o: renderer_test.h renderer.h world.h unit.h vector.h
renderer_test.o: projectile.h factory.h vector3.h
renderer_test.o: /usr/local/include/SDL2/SDL.h
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
scalable_grid.o: scalable_grid.h grid.h vector.h
shape.o: shape.h vector.h
shape_test.o: shape_test.h shape.h vector.h
team_id.o: team_id.h vector.h
test.o: test.h unit_test.h world_test.h vector_test.h unit/behavior_test.h
test.o: renderer_test.h shape_test.h factory_test.h grid_test.h kdtree_test.h
unit.o: unit.h vector.h pi.h
unit_test.o: unit_test.h unit.h vector.h pi.h
vector.o: vector.h pi.h
vector3.o: vector3.h
vector_test.o: vector_test.h vector.h pi.h
world.o: world.h unit.h vector.h projectile.h factory.h
world_test.o: world_test.h world.h unit.h vector.h projectile.h factory.h
