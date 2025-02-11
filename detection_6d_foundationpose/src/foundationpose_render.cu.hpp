// SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
// Copyright (c) 2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#ifndef NVIDIA_ISAAC_ROS_EXTENSIONS_FOUNDATIONPOSE_RENDER_CUDA_HPP_
#define NVIDIA_ISAAC_ROS_EXTENSIONS_FOUNDATIONPOSE_RENDER_CUDA_HPP_

#include <cstdint>
#include <limits>

#include "cuda.h"
#include "cuda_runtime.h"
#include "foundationpose_utils.hpp"

#include "nvdiffrast/common/common.h"
#include "nvdiffrast/common/cudaraster/CudaRaster.hpp"
#include "nvdiffrast/common/interpolate.h"
#include "nvdiffrast/common/rasterize.h"
#include "nvdiffrast/common/texture.h"

namespace foundationpose_render {


void clamp(cudaStream_t stream, float* input, float min_value, float max_value, int N);

void threshold_and_downscale_pointcloud(
    cudaStream_t stream, float* pointcloud_input, float* pose_array_input, int N, int n_points, float downscale_factor,
    float min_depth, float max_depth);

void concat(cudaStream_t stream, float* input_a, float* input_b, float* output, int N, int H, int W, int C1, int C2);

void rasterize(
    cudaStream_t stream, CR::CudaRaster* cr, float* pos_ptr, int32_t* tri_ptr, float* out, int pos_count, int tri_count,
    int H, int W, int C);

void interpolate(
    cudaStream_t stream, float* attr_ptr, float* rast_ptr, int32_t* tri_ptr, float* out, int num_vertices,
    int num_triangles, int attr_dim, int H, int W, int C);
    
void texture(
    cudaStream_t stream, float* tex_ptr, float* uv_ptr, float* out, int tex_height, int tex_width, int tex_channel,
    int tex_depth, int H, int W, int N);
    
}   // namespace foundationpose_render

#endif  // NVIDIA_ISAAC_ROS_EXTENSIONS_FOUNDATIONPOSE_RENDER_CUDA_HPP_