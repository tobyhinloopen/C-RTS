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

mod/mod_camera_update.o: mod/mod_camera_update.h game.h world.h unit.h
mod/mod_camera_update.o: vector.h pi.h factory.h projectile.h map.h shape.h
mod/mod_camera_update.o: renderer.h vector3.h /usr/local/include/SDL2/SDL.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_main.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_config.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_platform.h
mod/mod_camera_update.o: /usr/local/include/SDL2/begin_code.h
mod/mod_camera_update.o: /usr/local/include/SDL2/close_code.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_assert.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_atomic.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_audio.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_error.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_endian.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_mutex.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_thread.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_rwops.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_events.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_video.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_pixels.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_rect.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_surface.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_keycode.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_scancode.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_mouse.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_joystick.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_quit.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_gesture.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_touch.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_haptic.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_hints.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_loadso.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_log.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_power.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_render.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_system.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_timer.h
mod/mod_camera_update.o: /usr/local/include/SDL2/SDL_version.h opengl.h
mod/mod_camera_update.o: game.h grid.h kdtree.h scalable_grid.h team_id.h
mod/mod_camera_update.o: config.h rand_range.h camera.h
mod/mod_closest_enemy_unit.o: mod/mod_closest_enemy_unit.h game.h world.h
mod/mod_closest_enemy_unit.o: unit.h vector.h pi.h factory.h projectile.h
mod/mod_closest_enemy_unit.o: map.h shape.h renderer.h vector3.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_main.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_config.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_platform.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/begin_code.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/close_code.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_assert.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_atomic.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_audio.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_error.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_endian.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_mutex.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_thread.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_rwops.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_events.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_video.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_pixels.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_rect.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_surface.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_keycode.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_scancode.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_mouse.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_joystick.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_quit.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_gesture.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_touch.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_haptic.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_hints.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_loadso.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_log.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_power.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_render.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_system.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_timer.h
mod/mod_closest_enemy_unit.o: /usr/local/include/SDL2/SDL_version.h opengl.h
mod/mod_closest_enemy_unit.o: game.h grid.h kdtree.h scalable_grid.h
mod/mod_closest_enemy_unit.o: team_id.h config.h rand_range.h
mod/mod_closest_factory.o: mod/mod_closest_factory.h game.h world.h unit.h
mod/mod_closest_factory.o: vector.h pi.h factory.h projectile.h map.h shape.h
mod/mod_closest_factory.o: renderer.h vector3.h /usr/local/include/SDL2/SDL.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_main.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_config.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_platform.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/begin_code.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/close_code.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_assert.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_atomic.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_audio.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_error.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_endian.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_mutex.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_thread.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_rwops.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_events.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_video.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_pixels.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_rect.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_surface.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_keycode.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_scancode.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_mouse.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_joystick.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_quit.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_gesture.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_touch.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_haptic.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_hints.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_loadso.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_log.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_power.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_render.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_system.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_timer.h
mod/mod_closest_factory.o: /usr/local/include/SDL2/SDL_version.h opengl.h
mod/mod_closest_factory.o: game.h grid.h kdtree.h scalable_grid.h team_id.h
mod/mod_closest_factory.o: config.h rand_range.h
mod/mod_closest_friendly_unit.o: mod/mod_closest_friendly_unit.h game.h
mod/mod_closest_friendly_unit.o: world.h unit.h vector.h pi.h factory.h
mod/mod_closest_friendly_unit.o: projectile.h map.h shape.h renderer.h
mod/mod_closest_friendly_unit.o: vector3.h /usr/local/include/SDL2/SDL.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_main.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_config.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_platform.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/begin_code.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/close_code.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_assert.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_atomic.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_audio.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_error.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_endian.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_mutex.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_thread.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_rwops.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_events.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_video.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_pixels.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_rect.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_surface.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_keycode.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_scancode.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_mouse.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_joystick.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_quit.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_gesture.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_touch.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_haptic.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_hints.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_loadso.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_log.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_power.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_render.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_system.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_timer.h
mod/mod_closest_friendly_unit.o: /usr/local/include/SDL2/SDL_version.h
mod/mod_closest_friendly_unit.o: opengl.h game.h grid.h kdtree.h
mod/mod_closest_friendly_unit.o: scalable_grid.h team_id.h config.h
mod/mod_closest_friendly_unit.o: rand_range.h
mod/mod_event.o: mod/mod_event.h game.h world.h unit.h vector.h pi.h
mod/mod_event.o: factory.h projectile.h map.h shape.h renderer.h vector3.h
mod/mod_event.o: /usr/local/include/SDL2/SDL.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_main.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_config.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_platform.h
mod/mod_event.o: /usr/local/include/SDL2/begin_code.h
mod/mod_event.o: /usr/local/include/SDL2/close_code.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_assert.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_atomic.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_audio.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_error.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_endian.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_mutex.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_thread.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_rwops.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_events.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_video.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_pixels.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_rect.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_surface.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_keycode.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_scancode.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_mouse.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_joystick.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_quit.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_gesture.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_touch.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_haptic.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_hints.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_loadso.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_log.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_power.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_render.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_system.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_timer.h
mod/mod_event.o: /usr/local/include/SDL2/SDL_version.h opengl.h game.h grid.h
mod/mod_event.o: kdtree.h scalable_grid.h team_id.h config.h rand_range.h
mod/mod_event.o: vector3.h camera.h
mod/mod_factory_spawn.o: mod/mod_factory_spawn.h game.h world.h unit.h
mod/mod_factory_spawn.o: vector.h pi.h factory.h projectile.h map.h shape.h
mod/mod_factory_spawn.o: renderer.h vector3.h /usr/local/include/SDL2/SDL.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_main.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_config.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_platform.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/begin_code.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/close_code.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_assert.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_atomic.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_audio.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_error.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_endian.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_mutex.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_thread.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_rwops.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_events.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_video.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_pixels.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_rect.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_surface.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_keycode.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_scancode.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_mouse.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_joystick.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_quit.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_gesture.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_touch.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_haptic.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_hints.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_loadso.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_log.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_power.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_render.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_system.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_timer.h
mod/mod_factory_spawn.o: /usr/local/include/SDL2/SDL_version.h opengl.h
mod/mod_factory_spawn.o: game.h grid.h kdtree.h scalable_grid.h team_id.h
mod/mod_factory_spawn.o: config.h rand_range.h world.h team_id.h pi.h
mod/mod_kdtree.o: mod/mod_kdtree.h game.h world.h unit.h vector.h pi.h
mod/mod_kdtree.o: factory.h projectile.h map.h shape.h renderer.h vector3.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_main.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_config.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_platform.h
mod/mod_kdtree.o: /usr/local/include/SDL2/begin_code.h
mod/mod_kdtree.o: /usr/local/include/SDL2/close_code.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_assert.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_atomic.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_audio.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_error.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_endian.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_mutex.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_thread.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_rwops.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_events.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_video.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_pixels.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_rect.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_surface.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_keycode.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_scancode.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_mouse.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_joystick.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_quit.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_gesture.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_touch.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_haptic.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_hints.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_loadso.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_log.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_power.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_render.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_system.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_timer.h
mod/mod_kdtree.o: /usr/local/include/SDL2/SDL_version.h opengl.h game.h
mod/mod_kdtree.o: grid.h kdtree.h scalable_grid.h team_id.h config.h
mod/mod_kdtree.o: rand_range.h kdtree.h
mod/mod_print_performance.o: mod/mod_print_performance.h game.h world.h
mod/mod_print_performance.o: unit.h vector.h pi.h factory.h projectile.h
mod/mod_print_performance.o: map.h shape.h renderer.h vector3.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_main.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_config.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_platform.h
mod/mod_print_performance.o: /usr/local/include/SDL2/begin_code.h
mod/mod_print_performance.o: /usr/local/include/SDL2/close_code.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_assert.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_atomic.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_audio.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_error.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_endian.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_mutex.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_thread.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_rwops.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_events.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_video.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_pixels.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_rect.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_surface.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_keycode.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_scancode.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_mouse.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_joystick.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_quit.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_gesture.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_touch.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_haptic.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_hints.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_loadso.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_log.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_power.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_render.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_system.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_timer.h
mod/mod_print_performance.o: /usr/local/include/SDL2/SDL_version.h opengl.h
mod/mod_print_performance.o: game.h grid.h kdtree.h scalable_grid.h team_id.h
mod/mod_print_performance.o: config.h rand_range.h
mod/mod_projectile_unit_impact.o: mod/mod_projectile_unit_impact.h game.h
mod/mod_projectile_unit_impact.o: world.h unit.h vector.h pi.h factory.h
mod/mod_projectile_unit_impact.o: projectile.h map.h shape.h renderer.h
mod/mod_projectile_unit_impact.o: vector3.h /usr/local/include/SDL2/SDL.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_main.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_config.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_platform.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/begin_code.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/close_code.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_assert.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_atomic.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_audio.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_error.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_endian.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_mutex.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_thread.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_rwops.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_events.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_video.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_pixels.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_rect.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_surface.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_keycode.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_scancode.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_mouse.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_joystick.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_quit.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_gesture.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_touch.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_haptic.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_hints.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_loadso.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_log.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_power.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_render.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_system.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_timer.h
mod/mod_projectile_unit_impact.o: /usr/local/include/SDL2/SDL_version.h
mod/mod_projectile_unit_impact.o: opengl.h game.h grid.h kdtree.h
mod/mod_projectile_unit_impact.o: scalable_grid.h team_id.h config.h
mod/mod_projectile_unit_impact.o: rand_range.h world.h config.h
mod/mod_projectile_unit_impact.o: scalable_grid.h
mod/mod_random_spawn.o: mod/mod_random_spawn.h game.h world.h unit.h vector.h
mod/mod_random_spawn.o: pi.h factory.h projectile.h map.h shape.h renderer.h
mod/mod_random_spawn.o: vector3.h /usr/local/include/SDL2/SDL.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_main.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_config.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_platform.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/begin_code.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/close_code.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_assert.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_atomic.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_audio.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_error.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_endian.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_mutex.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_thread.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_rwops.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_events.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_video.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_pixels.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_rect.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_surface.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_keycode.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_scancode.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_mouse.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_joystick.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_quit.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_gesture.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_touch.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_haptic.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_hints.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_loadso.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_log.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_power.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_render.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_system.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_timer.h
mod/mod_random_spawn.o: /usr/local/include/SDL2/SDL_version.h opengl.h game.h
mod/mod_random_spawn.o: grid.h kdtree.h scalable_grid.h team_id.h config.h
mod/mod_random_spawn.o: rand_range.h pi.h rand_range.h team_id.h
mod/mod_render.o: mod/mod_render.h game.h world.h unit.h vector.h pi.h
mod/mod_render.o: factory.h projectile.h map.h shape.h renderer.h vector3.h
mod/mod_render.o: /usr/local/include/SDL2/SDL.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_main.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_config.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_platform.h
mod/mod_render.o: /usr/local/include/SDL2/begin_code.h
mod/mod_render.o: /usr/local/include/SDL2/close_code.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_assert.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_atomic.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_audio.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_error.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_endian.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_mutex.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_thread.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_rwops.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_events.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_video.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_pixels.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_rect.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_surface.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_keycode.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_scancode.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_mouse.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_joystick.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_quit.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_gesture.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_touch.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_haptic.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_hints.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_loadso.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_log.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_power.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_render.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_system.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_timer.h
mod/mod_render.o: /usr/local/include/SDL2/SDL_version.h opengl.h game.h
mod/mod_render.o: grid.h kdtree.h scalable_grid.h team_id.h config.h
mod/mod_render.o: rand_range.h renderer.h camera.h
mod/mod_scalable_grid.o: mod/mod_scalable_grid.h game.h world.h unit.h
mod/mod_scalable_grid.o: vector.h pi.h factory.h projectile.h map.h shape.h
mod/mod_scalable_grid.o: renderer.h vector3.h /usr/local/include/SDL2/SDL.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_main.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_config.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_platform.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/begin_code.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/close_code.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_assert.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_atomic.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_audio.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_error.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_endian.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_mutex.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_thread.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_rwops.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_events.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_video.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_pixels.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_rect.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_surface.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_keycode.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_scancode.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_mouse.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_joystick.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_quit.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_gesture.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_touch.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_haptic.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_hints.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_loadso.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_log.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_power.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_render.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_system.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_timer.h
mod/mod_scalable_grid.o: /usr/local/include/SDL2/SDL_version.h opengl.h
mod/mod_scalable_grid.o: game.h grid.h kdtree.h scalable_grid.h team_id.h
mod/mod_scalable_grid.o: config.h rand_range.h scalable_grid.h config.h
mod/mod_unit_behavior.o: mod/mod_unit_behavior.h game.h world.h unit.h
mod/mod_unit_behavior.o: vector.h pi.h factory.h projectile.h map.h shape.h
mod/mod_unit_behavior.o: renderer.h vector3.h /usr/local/include/SDL2/SDL.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_main.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_config.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_platform.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/begin_code.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/close_code.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_assert.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_atomic.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_audio.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_error.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_endian.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_mutex.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_thread.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_rwops.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_events.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_video.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_pixels.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_rect.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_surface.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_keycode.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_scancode.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_mouse.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_joystick.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_quit.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_gesture.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_touch.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_haptic.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_hints.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_loadso.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_log.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_power.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_render.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_system.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_timer.h
mod/mod_unit_behavior.o: /usr/local/include/SDL2/SDL_version.h opengl.h
mod/mod_unit_behavior.o: game.h grid.h kdtree.h scalable_grid.h team_id.h
mod/mod_unit_behavior.o: config.h rand_range.h unit/behavior.h vector.h
mod/mod_unit_behavior.o: unit.h world.h
mod/mod_unit_projectile_spawn.o: mod/mod_unit_projectile_spawn.h game.h
mod/mod_unit_projectile_spawn.o: world.h unit.h vector.h pi.h factory.h
mod/mod_unit_projectile_spawn.o: projectile.h map.h shape.h renderer.h
mod/mod_unit_projectile_spawn.o: vector3.h /usr/local/include/SDL2/SDL.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_main.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_config.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_platform.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/begin_code.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/close_code.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_assert.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_atomic.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_audio.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_error.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_endian.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_mutex.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_thread.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_rwops.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_events.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_video.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_pixels.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_rect.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_surface.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_keycode.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_scancode.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_mouse.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_joystick.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_quit.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_gesture.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_touch.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_haptic.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_hints.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_loadso.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_log.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_power.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_render.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_system.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_timer.h
mod/mod_unit_projectile_spawn.o: /usr/local/include/SDL2/SDL_version.h
mod/mod_unit_projectile_spawn.o: opengl.h game.h grid.h kdtree.h
mod/mod_unit_projectile_spawn.o: scalable_grid.h team_id.h config.h
mod/mod_unit_projectile_spawn.o: rand_range.h rand_range.h
mod/mod_world_update.o: mod/mod_world_update.h game.h world.h unit.h vector.h
mod/mod_world_update.o: pi.h factory.h projectile.h map.h shape.h renderer.h
mod/mod_world_update.o: vector3.h /usr/local/include/SDL2/SDL.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_main.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_stdinc.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_config.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_platform.h
mod/mod_world_update.o: /usr/local/include/SDL2/begin_code.h
mod/mod_world_update.o: /usr/local/include/SDL2/close_code.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_assert.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_atomic.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_audio.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_error.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_endian.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_mutex.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_thread.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_rwops.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_clipboard.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_cpuinfo.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_events.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_video.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_pixels.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_rect.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_surface.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_blendmode.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_keyboard.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_keycode.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_scancode.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_mouse.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_joystick.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_gamecontroller.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_quit.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_gesture.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_touch.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_filesystem.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_haptic.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_hints.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_loadso.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_log.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_messagebox.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_power.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_render.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_system.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_timer.h
mod/mod_world_update.o: /usr/local/include/SDL2/SDL_version.h opengl.h game.h
mod/mod_world_update.o: grid.h kdtree.h scalable_grid.h team_id.h config.h
mod/mod_world_update.o: rand_range.h world.h
unit/behavior.o: unit/behavior.h vector.h unit.h world.h pi.h
unit/behavior_test.o: unit/behavior_test.h unit/behavior.h vector.h unit.h
unit/behavior_test.o: world.h pi.h
benchmark.o: benchmark.h game.h
bktree.o: bktree.h util.h
bktree_test.o: bktree.h bktree_test.h rand_range.h util.h
camera.o: camera.h vector3.h
factory.o: factory.h vector.h unit.h pi.h
factory_test.o: factory_test.h factory.h vector.h unit.h pi.h
game.o: game.h /usr/local/include/SDL2/SDL.h
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
game.o: /usr/local/include/SDL2/SDL_version.h unit.h vector.h pi.h factory.h
game.o: projectile.h world.h vector3.h unit/behavior.h vector.h unit.h
game.o: world.h rand_range.h
grid.o: grid.h
grid_test.o: grid_test.h grid.h
kdtree.o: kdtree.h vector.h
kdtree_test.o: kdtree_test.h kdtree.h vector.h
main.o: game.h config.h benchmark.h test.h team_id.h vector.h
main.o: mod/mod_scalable_grid.h game.h world.h unit.h pi.h factory.h
main.o: projectile.h map.h shape.h renderer.h vector3.h
main.o: /usr/local/include/SDL2/SDL.h /usr/local/include/SDL2/SDL_main.h
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
main.o: scalable_grid.h rand_range.h mod/mod_kdtree.h
main.o: mod/mod_closest_enemy_unit.h mod/mod_closest_friendly_unit.h
main.o: mod/mod_closest_factory.h mod/mod_event.h
main.o: mod/mod_unit_projectile_spawn.h mod/mod_projectile_unit_impact.h
main.o: mod/mod_unit_behavior.h mod/mod_factory_spawn.h
main.o: mod/mod_world_update.h mod/mod_camera_update.h mod/mod_render.h
main.o: mod/mod_print_performance.h
map.o: map.h vector.h shape.h
projectile.o: projectile.h vector.h
rand_range.o: rand_range.h
rand_range_test.o: rand_range_test.h rand_range.h
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
renderer.o: /usr/local/include/SDL2/SDL_version.h renderer.h vector3.h
renderer.o: opengl.h game.h world.h unit.h vector.h pi.h factory.h
renderer.o: projectile.h team_id.h config.h text_renderer.h
renderer_test.o: renderer_test.h renderer.h vector3.h
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
renderer_test.o: /usr/local/include/SDL2/SDL_version.h opengl.h game.h
renderer_test.o: vector.h
scalable_grid.o: scalable_grid.h grid.h vector.h
shape.o: shape.h vector.h
shape_test.o: shape_test.h shape.h vector.h
team_id.o: team_id.h vector.h config.h
test.o: test.h util_test.h unit_test.h world_test.h vector_test.h
test.o: unit/behavior_test.h renderer_test.h shape_test.h factory_test.h
test.o: grid_test.h kdtree_test.h rand_range_test.h bktree_test.h
text_renderer.o: text_renderer.h opengl.h
unit.o: unit.h vector.h pi.h factory.h
unit_test.o: unit_test.h unit.h vector.h pi.h factory.h
util.o: util.h
util_test.o: util_test.h util.h
vector.o: vector.h pi.h
vector3.o: vector3.h
vector_test.o: vector_test.h vector.h pi.h
world.o: world.h unit.h vector.h pi.h factory.h projectile.h
world_test.o: world_test.h world.h unit.h vector.h pi.h factory.h
world_test.o: projectile.h
