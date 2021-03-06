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

#ifndef DRAGON_OPERATORS_ARRAY_REPEAT_OP_H_
#define DRAGON_OPERATORS_ARRAY_REPEAT_OP_H_

#include "core/operator.h"

namespace dragon {

template <class Context>
class RepeatOp final : public Operator<Context> {
 public:
    RepeatOp(const OperatorDef& def, Workspace* ws)
        : Operator<Context>(def, ws),
          axis_(OpArg<int64_t>("axis", INT_MAX)) {
        GET_ARG_WITH_DESC(int64_t, repeats, 1);
    }
    USE_OPERATOR_FUNCTIONS;

    void RunOnDevice() override;
    template<typename T> void RunImpl();

 protected:
    int64_t axis_, axis_dim_;
    int64_t outer_dim_, inner_dim_;
    DECLARE_ARG_WITH_DESC(int64_t, repeats);
};

template <class Context>
class RepeatGradientOp final : public Operator<Context> {
 public:
    RepeatGradientOp(const OperatorDef& def, Workspace* ws)
        : Operator<Context>(def, ws),
          axis_(OpArg<int64_t>("axis", INT_MAX)) {
        GET_ARG_WITH_DESC(int64_t, repeats, 1);
    }
    USE_OPERATOR_FUNCTIONS;

    void RunOnDevice() override;
    template<typename T> void RunImpl();

 protected:
    int64_t axis_, axis_dim_;
    int64_t outer_dim_, inner_dim_;
    DECLARE_ARG_WITH_DESC(int64_t, repeats);
};

DEFINE_ARG_WITH_DESC(int64_t, RepeatOp, repeats);
DEFINE_ARG_WITH_DESC(int64_t, RepeatGradientOp, repeats);

}  // namespace dragon

#endif  // DRAGON_OPERATORS_ARRAY_REPEAT_OP_H_