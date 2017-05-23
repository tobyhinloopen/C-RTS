#include "opencl_benchmark.h"
#include <assert.h>
#include <stdio.h>
#include "file.h"
#include <math.h>
#include "rand_range.h"
#include <time.h>
#include <float.h>

#define UNIT_COUNT 0xFFFF
#define VERIFY_RESULT 0

static cl_float2 units[UNIT_COUNT];
static int unit_team_ids[UNIT_COUNT];
static cl_float3 closest_enemy_units[UNIT_COUNT];
static cl_float3 closest_friendly_units[UNIT_COUNT];
static cl_float3 expected_closest_enemy_units[UNIT_COUNT];
static cl_float3 expected_closest_friendly_units[UNIT_COUNT];

File square_cl_file;
cl_int errcode;

static long microtime() {
  struct timespec time;
  clock_gettime(CLOCK_MONOTONIC, &time);
  return (1000000000L * time.tv_sec + time.tv_nsec) / 1000L;
}

static void pfn_notify(const char * errinfo, const void * private_info, size_t cb, void * user_data) {
  printf("OpenCL Error (via pfn_notify): %s\n", errinfo);
}

void opencl_prepare_benchmark() {
  RandRangeSeed seed = 0;
  for (int i = 0; i < UNIT_COUNT; i++) {
    units[i].s[0] = rand_rangef(&seed, -4096, 4096);
    units[i].s[1] = rand_rangef(&seed, -4096, 4096);
    unit_team_ids[i] = rand_rangei(&seed, 0, 3);
  }

  if (VERIFY_RESULT) {
    const long start = microtime();
    for (int x = 0; x < UNIT_COUNT; x++) {
      const int team_id = unit_team_ids[x];
      const cl_float2 unit = units[x];
      cl_float3 closest_friendly_unit = { { unit.s[0], unit.s[1], FLT_MAX } };
      cl_float3 closest_enemy_unit = { { unit.s[0], unit.s[1], FLT_MAX } };

      for (int y = 0; y < UNIT_COUNT; y++) {
        const cl_float2 current_unit = units[y];
        const float vx = current_unit.s[0] - unit.s[0];
        const float vy = current_unit.s[1] - unit.s[1];
        const float distance_sq = vx * vx + vy * vy;
        const cl_float3 current_unit_result = { { current_unit.s[0], current_unit.s[1], distance_sq } };
        const int current_team_id = unit_team_ids[y];
        if (current_team_id == team_id) {
          if (current_unit_result.s[2] < closest_friendly_unit.s[2]) {
            closest_friendly_unit = current_unit_result;
          }
        } else if(current_unit_result.s[2] < closest_enemy_unit.s[2]) {
          closest_enemy_unit = current_unit_result;
        }
      }

      expected_closest_friendly_units[x] = closest_friendly_unit;
      expected_closest_enemy_units[x] = closest_enemy_unit;
    }
    printf("OpenCL benchmark on CPU took %4.2fms\n", (microtime() - start) / 1000.0);
  }

  file_initialize(&square_cl_file);
  file_read(&square_cl_file, "benchmark.cl");
}

static void assert_success(cl_int status) {
  if (status == CL_SUCCESS)
    return;
  switch (status) {
    case CL_INVALID_COMMAND_QUEUE: printf("CL_INVALID_COMMAND_QUEUE\n"); break;
    case CL_INVALID_CONTEXT: printf("CL_INVALID_CONTEXT\n"); break;
    case CL_INVALID_MEM_OBJECT: printf("CL_INVALID_MEM_OBJECT\n"); break;
    case CL_INVALID_VALUE: printf("CL_INVALID_VALUE\n"); break;
    case CL_INVALID_EVENT_WAIT_LIST: printf("CL_INVALID_EVENT_WAIT_LIST\n"); break;
    case CL_MEM_OBJECT_ALLOCATION_FAILURE: printf("CL_MEM_OBJECT_ALLOCATION_FAILURE\n"); break;
    case CL_OUT_OF_HOST_MEMORY: printf("CL_OUT_OF_HOST_MEMORY\n"); break;
  }
  assert(0);
}

OpenclBenchmarkResult opencl_benchmark_device(cl_device_id device_id) {
  cl_context context = clCreateContext(NULL, 1, &device_id, pfn_notify, NULL, &errcode);
  assert_success(errcode);

  cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &errcode);
  assert_success(errcode);

  assert(square_cl_file.data && square_cl_file.size);
  cl_program square_cl_program = clCreateProgramWithSource(context, 1, (const char **)&square_cl_file.data, &square_cl_file.size, &errcode);
  assert_success(errcode);

  if (clBuildProgram(square_cl_program, 0, NULL, NULL, NULL, NULL) != CL_SUCCESS) {
    size_t len;
    char buffer[2048];

    printf("Error: Failed to build program executable!\n");
    clGetProgramBuildInfo(square_cl_program, device_id, CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
    printf("%s\n", buffer);
    assert(0);
  }

  cl_kernel kernel = clCreateKernel(square_cl_program, "closest_unit", &errcode);
  assert_success(errcode);

  cl_mem cl_mem_units = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(units), NULL, NULL);
  assert(cl_mem_units);
  cl_mem cl_mem_unit_team_ids = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(unit_team_ids), NULL, NULL);
  assert(cl_mem_unit_team_ids);
  cl_mem cl_mem_closest_enemy_units = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(closest_enemy_units), NULL, NULL);
  assert(cl_mem_closest_enemy_units);
  cl_mem cl_mem_closest_friendly_units = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(closest_friendly_units), NULL, NULL);
  assert(cl_mem_closest_friendly_units);

  const long start = microtime();
  assert_success(clEnqueueWriteBuffer(command_queue, cl_mem_units, CL_TRUE, 0, sizeof(units), units, 0, NULL, NULL));
  assert_success(clEnqueueWriteBuffer(command_queue, cl_mem_unit_team_ids, CL_TRUE, 0, sizeof(unit_team_ids), unit_team_ids, 0, NULL, NULL));
  const long write_end = microtime();

  {
    assert_success(clSetKernelArg(kernel, 0, sizeof(cl_mem), &cl_mem_units));
    assert_success(clSetKernelArg(kernel, 1, sizeof(cl_mem), &cl_mem_unit_team_ids));
    assert_success(clSetKernelArg(kernel, 2, sizeof(cl_mem), &cl_mem_closest_enemy_units));
    assert_success(clSetKernelArg(kernel, 3, sizeof(cl_mem), &cl_mem_closest_friendly_units));
    unsigned int unit_count = UNIT_COUNT;
    assert_success(clSetKernelArg(kernel, 4, sizeof(unit_count), &unit_count));
  }

  const size_t global_work_group_size = UNIT_COUNT;
  assert_success(clEnqueueNDRangeKernel(command_queue, kernel, 1, NULL, &global_work_group_size, NULL, 0, NULL, NULL));
  assert_success(clFinish(command_queue));
  const long finish_end = microtime();

  assert_success(clEnqueueReadBuffer(command_queue, cl_mem_closest_enemy_units, CL_TRUE, 0, sizeof(closest_enemy_units), closest_enemy_units, 0, NULL, NULL));
  assert_success(clEnqueueReadBuffer(command_queue, cl_mem_closest_friendly_units, CL_TRUE, 0, sizeof(closest_friendly_units), closest_friendly_units, 0, NULL, NULL));
  const long read_end = microtime();

  OpenclBenchmarkResult benchmark;

  benchmark.offset = 0;
  // for(int i = 0; i < (MAP_SIZE * MAP_SIZE); i++)
  //   benchmark.offset += fabs((float)output_map[i] - (float)expected_output_map[i]);
  benchmark.write_duration = write_end - start;
  benchmark.kernel_duration = finish_end - write_end;
  benchmark.read_duration = read_end - finish_end;
  benchmark.total_duration = read_end - start;

  clReleaseMemObject(cl_mem_units);
  clReleaseMemObject(cl_mem_unit_team_ids);
  clReleaseMemObject(cl_mem_closest_enemy_units);
  clReleaseMemObject(cl_mem_closest_friendly_units);
  clReleaseProgram(square_cl_program);
  clReleaseKernel(kernel);
  clReleaseCommandQueue(command_queue);
  clReleaseContext(context);

  return benchmark;
}

void opencl_print_benchmark_result(OpenclBenchmarkResult r) {
  printf("Benchmark: %4.2fms - w: %4.2fms, k: %4.2fms, r: %4.2fms",
    r.total_duration/1000.0, r.write_duration/1000.0, r.kernel_duration/1000.0, r.read_duration/1000.0);
  if (r.offset == 0)
    printf(", OK\n");
  else
    printf(", OFFSET: %f (should be 0!)\n", r.offset);
}
