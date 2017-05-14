#ifndef OPENCL_BENCHMARK_H
#define OPENCL_BENCHMARK_H

#include "opencl.h"
#include <time.h>

typedef struct {
  unsigned long write_duration;
  unsigned long kernel_duration;
  unsigned long read_duration;
  unsigned long total_duration;
  float offset;
} OpenclBenchmarkResult;

void opencl_prepare_benchmark();
OpenclBenchmarkResult opencl_benchmark_device(cl_device_id device_id);
void opencl_print_benchmark_result(OpenclBenchmarkResult benchmark_result);

#endif
