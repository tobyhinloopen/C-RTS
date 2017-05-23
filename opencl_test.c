#include "opencl_test.h"
#include "opencl_benchmark.h"
#include "opencl.h"
#include <assert.h>

static void test_opencl_platform_device(cl_device_id device_id) {
  opencl_print_device_info(device_id);
  OpenclBenchmarkResult benchmark = opencl_benchmark_device(device_id);
  opencl_print_benchmark_result(benchmark);
}

static void test_opencl_platform(cl_platform_id platform_id) {
  cl_uint device_ids_count = 0;
  assert(clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, 0, NULL, &device_ids_count) == CL_SUCCESS);

  cl_device_id * device_ids = malloc(sizeof(cl_device_id) * device_ids_count);
  assert(device_ids);
  assert(clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_GPU, device_ids_count, device_ids, &device_ids_count) == CL_SUCCESS);

  opencl_print_platform_info(platform_id);
  for (int i = 0; i < device_ids_count; i++)
    test_opencl_platform_device(device_ids[i]);

  free(device_ids);
}

void test_opencl(void) {
  opencl_prepare_benchmark();

  cl_uint platform_ids_count;
  assert(clGetPlatformIDs(0, NULL, &platform_ids_count) == CL_SUCCESS);

  cl_platform_id * platform_ids = malloc(sizeof(cl_platform_id) * platform_ids_count);
  assert(platform_ids);
  assert(clGetPlatformIDs(platform_ids_count, platform_ids, &platform_ids_count) == CL_SUCCESS);

  for (int i = 0; i < platform_ids_count; i++)
    test_opencl_platform(platform_ids[i]);

  free(platform_ids);
}
