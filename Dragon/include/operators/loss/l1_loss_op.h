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

#ifndef DRAGON_OPERATORS_LOSS_L1_LOSS_OP_H_
#define DRAGON_OPERATORS_LOSS_L1_LOSS_OP_H_

#include "core/operator.h"

namespace dragon {

template <class Context>
class L1LossOp final : public Operator<Context> {
 public:
    L1LossOp(const OperatorDef& def, Workspace* ws)
        : Operator<Context>(def, ws),
          scale_(OpArg<float>(
              "scale", 1.f)),
          reduction_(OpArg<string>(
              "reduction", "BATCH_SIZE")) {}
    USE_OPERATOR_FUNCTIONS;

    void RunOnDevice() override;
    template <typename T> void RunImpl();

 protected:
    float scale_;
    string reduction_;
};

template <class Context>
class L1LossGradientOp final : public Operator<Context> {
 public:
    L1LossGradientOp(const OperatorDef& def, Workspace* ws)
        : Operator<Context>(def, ws),
          scale_(OpArg<float>(
              "scale", 1.f)),
          reduction_(OpArg<string>(
              "reduction", "BATCH_SIZE")) {}
    USE_OPERATOR_FUNCTIONS;

    void RunOnDevice() override;
    template <typename T> void RunImpl();

 protected:
    float scale_;
    string reduction_;
};

}  // namespace dragon

#endif  // DRAGON_OPERATORS_LOSS_L1_LOSS_OP_H_