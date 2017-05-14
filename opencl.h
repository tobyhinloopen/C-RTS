#ifndef OPENCL_H
#define OPENCL_H

#ifdef __APPLE__
#include "OpenCL/opencl.h"
#else
#include "CL/cl.h"
#endif

void opencl_print_platform_info(cl_platform_id platform_id);
void opencl_print_device_info(cl_device_id device_id);

#endif
