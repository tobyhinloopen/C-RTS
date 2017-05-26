#ifndef CL_UNIT_H
#define CL_UNIT_H

#include "opencl.h"

#define POOL_COLLECTION_SIZE 256
#define POOL_CAPACITY 1024
#define POOL32_CAPACITY (POOL_CAPACITY * 32)

struct cl_unit {
  cl_float2 position;
  cl_float2 target_position;
  cl_uchar team_id;
};

struct cl_rect_container {
  cl_float2 tl;
  cl_float2 br;
  cl_uchar team_id;
}

struct cl_unit_pool {
  struct cl_uint alive[POOL_CAPACITY];
  struct cl_unit units[POOL32_CAPACITY];
};

struct cl_unit_pool_collection {
  struct cl_unit_pool pools[POOL_COLLECTION_SIZE];
};

#endif
