/*
 * Copyright (c) 2020 Mieszko Mazurek <mimaz@gmx.com>
 */

#pragma once

#include "opencl-stub.h"

/*
 * TODO alias CL functions to adequate pointers
 *
 * exclude clGetPlatformIDs as it's extern call is required
 * to load all the symbols first
 */
#define clGetPlatformInfo s_clGetPlatformInfo
