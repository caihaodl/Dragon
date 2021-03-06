#include "utils/cast.h"
#include "utils/op_kernel.h"
#include "utils/math_functions.h"

namespace dragon {

namespace kernel {

bool less(int a, int b) { return unsigned(a) < unsigned(b); }

/* <T = float32, Device = CPU> */

template<typename T>
void _Im2Col2dNCHW(
    const int               C,
    const int               H,
    const int               W,
    const int               out_h,
    const int               out_w,
    const int               kernel_h,
    const int               kernel_w,
    const int               stride_h,
    const int               stride_w,
    const int               pad_h,
    const int               pad_w,
    const int               dilation_h,
    const int               dilation_w,
    const T*                im,
    T*                      col) {
    int ih, iw;
    const int im_ofs = H * W;
    for (int c = 0; c < C; ++c, im += im_ofs) {
    for (int kh = 0; kh < kernel_h; ++kh) {
    for (int kw = 0; kw < kernel_w; ++kw) {
        ih = -pad_h + kh * dilation_h;
        for (int oh = 0; oh < out_h; ++oh) {
            if (!less(ih, H)) {
                for (int ow = 0; ow < out_w; ++ow)
                    *(col++) = T(0);
            } else {
                iw = -pad_w + kw * dilation_w;
                for (int ow = 0; ow < out_w; ++ow) {
                    if (!less(iw, W)) *(col++) = T(0);
                    else *(col++) = im[ih * W + iw];
                    iw += stride_w;
                }  // End ow
            }  // End if
            ih += stride_h;
        }  // End oh
    }}}  // End c && kh && kw
}

template<typename T>
void _Im2Col2dNHWC(
    const int               C,
    const int               H,
    const int               W,
    const int               out_h,
    const int               out_w,
    const int               kernel_h,
    const int               kernel_w,
    const int               stride_h,
    const int               stride_w,
    const int               pad_h,
    const int               pad_w,
    const int               dilation_h,
    const int               dilation_w,
    const T*                im,
    T*                      col) {
    int ih_start, ih, iw_start, iw;
    for (int oh = 0; oh < out_h; ++oh) {
        ih_start = oh * stride_h - pad_h;
        for (int ow = 0; ow < out_w; ++ow) {
            iw_start = ow * stride_w - pad_w;
            for (int kh = 0; kh < kernel_h; ++kh) {
                ih = ih_start + kh * dilation_h;
                if (!less(ih, H)) {
                    for (int kw = 0; kw < kernel_w; ++kw)
                        for (int c = 0; c < C; ++c) *(col++) = 0;
                } else {
                    for (int kw = 0; kw < kernel_w; ++kw) {
                        iw = iw_start + kw * dilation_w;
                        for (int c = 0; c < C; ++c) {
                            if (!less(iw, W)) *(col++) = 0;
                            else *(col++) = im[(ih * W + iw) * C + c];
                        }  // End c
                    }  // End kw
                }  // End if
            }  // End kh
        }  // End ow
    }  // End oh
}

template <> void Im2Col2d<float, CPUContext>(
    const int               C,
    const int               H,
    const int               W,
    const int               out_h,
    const int               out_w,
    const int               kernel_h,
    const int               kernel_w,
    const int               stride_h,
    const int               stride_w,
    const int               pad_h,
    const int               pad_w,
    const int               dilation_h,
    const int               dilation_w,
    const string&           data_format,
    const float*            im,
    float*                  col,
    CPUContext*             ctx) {
    if (data_format == "NCHW") {
        _Im2Col2dNCHW(
            C, H, W,
            out_h, out_w,
            kernel_h, kernel_w,
            stride_h, stride_w,
            pad_h, pad_w,
            dilation_h, dilation_w,
            im, col
        );
    } else if (data_format == "NHWC") {
        _Im2Col2dNHWC(
            C, H, W,
            out_h, out_w,
            kernel_h, kernel_w,
            stride_h, stride_w,
            pad_h, pad_w,
            dilation_h, dilation_w,
            im, col
        );
    } else {
        LOG(FATAL) << "Unknown DataFormat: " << data_format;
    }
}

/* <T = float32, Device = CPU> */

template<typename T>
void _Col2Im2dNCHW(
    const int               C,
    const int               H,
    const int               W,
    const int               out_h,
    const int               out_w,
    const int               kernel_h,
    const int               kernel_w,
    const int               stride_h,
    const int               stride_w,
    const int               pad_h,
    const int               pad_w,
    const int               dilation_h,
    const int               dilation_w,
    const T*                col,
    T*                      im) {
    int ih, iw;
    const int im_ofs= H * W;
    for (int c = 0; c < C; ++c, im += im_ofs) {
    for (int kh = 0; kh < kernel_h; ++kh) {
    for (int kw = 0; kw < kernel_w; ++kw) {
        ih = -pad_h + kh * dilation_h;
        for (int oh = 0; oh < out_h; ++oh) {
            if (!less(ih, H)) {
                col += out_w;
            } else {
                iw = -pad_w + kw * dilation_w;
                for (int ow = 0; ow < out_w; ++ow) {
                    if (less(iw, W)) im[ih * W + iw] += *col;
                    ++col; iw += stride_w;
                }  // End ow
            }  // End if
            ih += stride_h;
        }  // End oh
    }}}  // End c && kh && kw
}

template<typename T>
void _Col2Im2dNHWC(
    const int               C,
    const int               H,
    const int               W,
    const int               out_h,
    const int               out_w,
    const int               kernel_h,
    const int               kernel_w,
    const int               stride_h,
    const int               stride_w,
    const int               pad_h,
    const int               pad_w,
    const int               dilation_h,
    const int               dilation_w,
    const T*                col,
    T*                      im) {
    int ih_start, ih, iw_start, iw;
    for (int oh = 0; oh < out_h; ++oh) {
        ih_start = -pad_h + stride_h * oh;
        for (int ow = 0; ow < out_w; ++ow) {
            iw_start = -pad_w + stride_w * ow;
            for (int kh = 0; kh < kernel_h; ++kh) {
                ih = ih_start + kh * dilation_h;
                if (!less(ih, H)) {
                    col += (kernel_w * C);
                } else {
                    for (int kw = 0; kw < kernel_w; ++kw) {
                        iw = iw_start + kw * dilation_w;
                        for (int c = 0; c < C; ++c) {
                            if (less(iw, W)) {
                                im[(ih * W + iw) * C + c] += *(col);
                            }
                            ++col;
                        } // End c
                    }  // End kw
                }  // End if
            }  // End kh
        }  // End ow
    }  // End oh
}

template<> void Col2Im2d<float, CPUContext>(
    const int               C,
    const int               H,
    const int               W,
    const int               out_h,
    const int               out_w,
    const int               kernel_h,
    const int               kernel_w,
    const int               stride_h,
    const int               stride_w,
    const int               pad_h,
    const int               pad_w,
    const int               dilation_h,
    const int               dilation_w,
    const string&           data_format,
    const float*            col,
    float*                  im,
    CPUContext*             ctx) {
    math::Set(C * H * W, 0.f, im, ctx);
    if (data_format == "NCHW") {
        _Col2Im2dNCHW(
            C, H, W,
            out_h, out_w,
            kernel_h, kernel_w,
            stride_h, stride_w,
            pad_h, pad_w,
            dilation_h, dilation_w,
            col, im
        );
    } else if (data_format == "NHWC") {
        _Col2Im2dNHWC(
            C, H, W,
            out_h, out_w,
            kernel_h, kernel_w,
            stride_h, stride_w,
            pad_h, pad_w,
            dilation_h,
            dilation_w,
            col, im
        );
    } else {
        LOG(FATAL) << "Unknown DataFormat: " << data_format;
    }
}

}  // namespace kernel

}  // namepsace dragon