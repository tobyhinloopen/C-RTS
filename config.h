#ifndef CONFIG_H
#define CONFIG_H

// #define CONFIG_PRINT_PERFORMANCE_ENABLED
#define CONFIG_TEST_ENABLED
#define CONFIG_BENCHMARK_ENABLED
// #define CONFIG_GAME_ENABLED

#define CONFIG_SCALABLE_GRID_ENABLED

#ifdef CONFIG_SCALABLE_GRID_ENABLED
#define CONFIG_SCALABLE_GRID_SIZE 16
#define CONFIG_SCALABLE_GRID_QUICK_SHORT_RANGE_ENEMY_SEARCH 128
#define CONFIG_SCALABLE_GRID_INITIAL_CAPACITY 4096
#endif

#define SPAWN_OFFSET 0.1
#define SPAWN_DISTANCE 0.04

#define SIZE_X 4096
#define SIZE_Y 4096
#define TEAM_COUNT 5
#define FACTORY_ROWS 2
#define FACTORY_COLS 4
#define SPAWN_POINTS_COUNT ((TEAM_COUNT - 1) * FACTORY_ROWS * FACTORY_COLS)

#define BENCHMARK_INTERVAL_MS 0x0010
#define BENCHMARK_DURATION_MS 0x8000

#define INITIAL_WINDOW_WIDTH 1280
#define INITIAL_WINDOW_HEIGHT 540
#define INITIAL_CAMERA_X -768
#define INITIAL_CAMERA_Y 0
#define INITIAL_CAMERA_Z 4

#endif
