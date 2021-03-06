/*!
 * Copyright (c) 2017-present, SeetaTech, Co.,Ltd.
 *
 * Licensed under the BSD 2-Clause License.
 * You should have received a copy of the BSD 2-Clause License
 * along with the software. If not, See,
 *
 *      <https://opensource.org/licenses/BSD-2-Clause>
 *
 * Codes are based on:
 *
 *    <https://github.com/pytorch/pytorch/blob/master/caffe2/utils/math_utils.h>
 *
 * ------------------------------------------------------------
 */

#ifndef DRAGON_UTILS_MATH_UTILS_H_
#define DRAGON_UTILS_MATH_UTILS_H_

#include "core/context.h"
#include "core/context_cuda.h"

#ifdef WITH_CUDA
#define MATH_UTILS_DECL inline __host__ __device__
#else
#define MATH_UTILS_DECL inline
#endif

namespace dragon {

namespace utils {

namespace math {

template <typename T>
MATH_UTILS_DECL T Cube(const T x) {
    return x * x * x;
}

template <typename T>
inline void ArgPartition(
    const int                   count,
    const int                   kth,
    const bool                  descend,
    const T*                    v,
    vec64_t&                    indices) {
    indices.resize(count);
    std::iota(indices.begin(), indices.end(), 0);
    if (descend) {
        std::nth_element(
            indices.begin(),
            indices.begin() + kth,
            indices.end(),
            [&v](int64_t i1, int64_t i2) {
                return v[i1] > v[i2]; 
            }
        );
    } else {
        std::nth_element(
            indices.begin(),
            indices.begin() + kth,
            indices.end(),
            [&v](int64_t i1, int64_t i2) { 
                return v[i1] < v[i2];
            }
        );
    }
}

}  // namespace math

void IncreaseIndexInDims(
    const int               ndims,
    const int*              dims,
    int*                    index);

bool IsRowwiseBroadcast(
    const vec64_t&          A_dims,
    const vec64_t&          B_dims,
    int*                    rows,
    int*                    cols);

bool IsColwiseBroadcast(
    const vec64_t&          A_dims,
    const vec64_t&          B_dims,
    int*                    rows,
    int*                    cols);

bool IsRowwiseReduce(
    const int               ndims,
    const int*              A_dims,
    const int*              B_dims,
    int*                    rows,
    int*                    cols);

bool IsColwiseReduce(
    const int               ndims,
    const int*              A_dims,
    const int*              B_dims,
    int*                    rows,
    int*                    cols);

void ComputeTransposedAxesForReduce(
    const int               ndims,
    const int               naxes,
    const int*              reduce_axes,
    int*                    transpose_axes);

void ComputeTransposedStrides(
    const int               ndims,
    const int*              dims,
    const int*              axes,
    int*                    strides);

}  // namespace utils

}  // namespace dragon

#endif  // DRAGON_UTILS_MATH_UTILS_H_