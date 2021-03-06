/*!
 * Copyright (c) 2017-present, SeetaTech, Co.,Ltd.
 *
 * Licensed under the BSD 2-Clause License.
 * You should have received a copy of the BSD 2-Clause License
 * along with the software. If not, See,
 *
 *      <https://opensource.org/licenses/BSD-2-Clause>
 *
 * ------------------------------------------------------------
 */

#ifndef DRAGON_OPERATORS_ACTIVATION_SIGMOID_OP_HPP
#define DRAGON_OPERATORS_ACTIVATION_SIGMOID_OP_HPP

#include "core/operator.h"

namespace dragon {

template <class Context>
class SigmoidOp : public Operator<Context> {
 public:
    SIMPLE_CTOR_DTOR(SigmoidOp);
    USE_OPERATOR_FUNCTIONS;

    void RunOnDevice() override;
    template <typename T> void RunImpl();
};

template <class Context>
class SigmoidGradientOp : public Operator<Context> {
 public:
    SIMPLE_CTOR_DTOR(SigmoidGradientOp);
    USE_OPERATOR_FUNCTIONS;

    void RunOnDevice() override;
    template <typename T> void RunImpl();
};

#ifdef WITH_CUDNN

template <class Context>
class CuDNNSigmoidOp final : public SigmoidOp<Context> {
public:
    CuDNNSigmoidOp(const OperatorDef& def, Workspace* ws)
        : SigmoidOp<Context>(def, ws) {
        CuDNNCreateTensorDesc(&input_desc_);
        CUDNN_CHECK(cudnnCreateActivationDescriptor(&act_desc_));
        CUDNN_CHECK(cudnnSetActivationDescriptor(
            act_desc_,
            CUDNN_ACTIVATION_SIGMOID,
            CUDNN_PROPAGATE_NAN, 0
        ));
    }
    USE_OPERATOR_FUNCTIONS;

    ~CuDNNSigmoidOp() {
        CuDNNDestroyTensorDesc(&input_desc_);
        CUDNN_CHECK(cudnnDestroyActivationDescriptor(act_desc_));
    }

    void RunOnDevice() override;
    template <typename T> void RunImpl();

 protected:
    cudnnTensorDescriptor_t input_desc_;
    cudnnActivationDescriptor_t act_desc_;
};

template <class Context>
class CuDNNSigmoidGradientOp final : public SigmoidGradientOp<Context> {
 public:
    CuDNNSigmoidGradientOp(const OperatorDef& def, Workspace* ws)
        : SigmoidGradientOp<Context>(def, ws) {
        CUDNN_CHECK(cudnnCreateTensorDescriptor(&input_desc_));
        CUDNN_CHECK(cudnnCreateActivationDescriptor(&act_desc_));
        CUDNN_CHECK(cudnnSetActivationDescriptor(
            act_desc_,
            CUDNN_ACTIVATION_SIGMOID,
            CUDNN_PROPAGATE_NAN, 0
        ));
    }
    USE_OPERATOR_FUNCTIONS;

    ~CuDNNSigmoidGradientOp() {
        CUDNN_CHECK(cudnnDestroyTensorDescriptor(input_desc_));
        CUDNN_CHECK(cudnnDestroyActivationDescriptor(act_desc_));
    }

    void RunOnDevice() override;
    template <typename T> void RunImpl();

 protected:
    cudnnTensorDescriptor_t input_desc_;
    cudnnActivationDescriptor_t act_desc_;
};

#endif  // WITH_CUDNN

}  // namespace dragon

#endif  // DRAGON_OPERATORS_ACTIVATION_SIGMOID_OP_HPP