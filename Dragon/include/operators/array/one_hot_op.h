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

#ifndef DRAGON_OPERATORS_ARRAY_ONE_HOT_OP_H_
#define DRAGON_OPERATORS_ARRAY_ONE_HOT_OP_H_

#include "core/operator.h"

namespace dragon {

template <class Context>
class OneHotOp final : public Operator<Context> {
 public:
    OneHotOp(const OperatorDef& def, Workspace* ws)
        : Operator<Context>(def, ws),
          depth_(OpArg<int64_t>("depth", -1)),
          on_value_(OpArg<int64_t>("on_value", 1)),
          off_value_(OpArg<int64_t>("off_value", 0)) {}
    USE_OPERATOR_FUNCTIONS;

    void RunOnDevice() override;
    template <typename T> void RunImpl();

 protected:
    int64_t depth_, on_value_, off_value_;
};

}  // namespace dragon

#endif  // DRAGON_OPERATORS_ARRAY_ONE_HOT_OP_H_