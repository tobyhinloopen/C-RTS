#include "opencl.h"
#include <assert.h>
#include <stdio.h>

#define BUFFER_SIZE 1024
static char buffer[BUFFER_SIZE];

void opencl_print_platform_info(cl_platform_id platform_id) {
  printf("Platform %p, ", platform_id);
  assert(clGetPlatformInfo(platform_id, CL_PLATFORM_VENDOR, BUFFER_SIZE, buffer, NULL) == CL_SUCCESS);
  printf("%s ", buffer);
  assert(clGetPlatformInfo(platform_id, CL_PLATFORM_NAME, BUFFER_SIZE, buffer, NULL) == CL_SUCCESS);
  printf("%s ", buffer);
  assert(clGetPlatformInfo(platform_id, CL_PLATFORM_PROFILE, BUFFER_SIZE, buffer, NULL) == CL_SUCCESS);
  printf("%s ", buffer);
  assert(clGetPlatformInfo(platform_id, CL_PLATFORM_VERSION, BUFFER_SIZE, buffer, NULL) == CL_SUCCESS);
  printf("%s\n", buffer);
}

void opencl_print_device_info(cl_device_id device_id) {
  printf("Device %p, ", device_id);
  assert(clGetDeviceInfo(device_id, CL_DEVICE_VENDOR, BUFFER_SIZE, buffer, NULL) == CL_SUCCESS);
  printf("%s ", buffer);
  assert(clGetDeviceInfo(device_id, CL_DEVICE_NAME, BUFFER_SIZE, buffer, NULL) == CL_SUCCESS);
  printf("%s, ", buffer);
  unsigned int max_cu;
  assert(clGetDeviceInfo(device_id, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(max_cu), &max_cu, NULL) == CL_SUCCESS);
  printf("%u cu, ", max_cu);
  unsigned long memory_bytes;
  assert(clGetDeviceInfo(device_id, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(memory_bytes), &memory_bytes, NULL) == CL_SUCCESS);
  double memory_gb = (double)(memory_bytes) / (1024 * 1024 * 1024);
  printf("%.1f GB\n", memory_gb);
}
