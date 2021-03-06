#include "core/workspace.h"
#include "utils/op_kernel.h"
#include "utils/math_functions.h"
#include "operators/arithmetic/fundamental_op.h"

namespace dragon {

template <class Context> template <typename T>
void AddOp<Context>::EltwiseRunImpl() {
    auto* a = X(0).template data<T, Context>();
    auto* b = X(1).template data<T, Context>();
    auto* y = Y(0)->template mutable_data<T, Context>();
    math::Add(Y(0)->count(), a, b, y, ctx());
}

template <class Context> template <typename T>
void AddOp<Context>::BroadcastRunImpl(int type) {
    auto* a = X(0).template data<T, Context>();
    auto* b = X(1).template data<T, Context>();
    auto* y = Y(0)->template mutable_data<T, Context>();
    math::BroadcastAdd(rows_, cols_, type, a, b, y, ctx());
}

template <class Context>
void AddOp<Context>::RunOnDevice() {
    DECLARE_INPUT_DESC;
    Y(0)->ReshapeLike(X(0));

    if (XIsType(X(0), int8_t)) {
        DEFINE_FUNDAMENTAL_TYPED_IMPL(int8_t);
    } else if (XIsType(X(0), uint8_t)) {
        DEFINE_FUNDAMENTAL_TYPED_IMPL(uint8_t);
    } else if (XIsType(X(0), int)) {
        DEFINE_FUNDAMENTAL_TYPED_IMPL(int);
    } else if (XIsType(X(0), int64_t)) {
        DEFINE_FUNDAMENTAL_TYPED_IMPL(int64_t);
    } else if (XIsType(X(0), float16)) {
        DEFINE_FUNDAMENTAL_TYPED_IMPL(float16);
    } else if (XIsType(X(0), float)) {
        DEFINE_FUNDAMENTAL_TYPED_IMPL(float);
    } else if (XIsType(X(0), double)) {
        DEFINE_FUNDAMENTAL_TYPED_IMPL(double);
    } else {
        LOG(FATAL) << DTypeString(X(0), {
            "int8", "uint8", "int32", "int64",
            "float16", "float32", "float64",
        });
    }
}

template <class Context> template <typename T>
void AddGradientOp<Context>::EltwiseRunImpl() {
    auto* dy = X(-1).template data<T, Context>();

    if (Y(1)->name() != "NULL") {
        auto* db = Y(1)->template mutable_data<T, Context>();
        math::Copy(Y(1)->count(), dy, db, ctx());
    }

    if (Y(0)->name() != "NULL") {
        auto* da = Y(0)->template mutable_data<T, Context>();
        math::Copy(Y(0)->count(), dy, da, ctx());
    }
}

template <class Context> template <typename T>
void AddGradientOp<Context>::BroadcastRunImpl(int type) {
    DEFINE_INPUT_DESC;
    auto* dy = X(-1).template data<T, Context>();

    if (Y(1)->name() != "NULL") {
        auto* db = Y(1)->template mutable_data<T, Context>();
        vec32_t dims = { rows_, cols_ };
        vec32_t axes = { type };
        kernel::ReduceSum(
            2, dims.data(),
            1, axes.data(),
            1.f, dy,
            db, ctx()
        );
    }

    if (Y(0)->name() != "NULL") {
        auto* da = Y(0)->template mutable_data<T, Context>();
        math::Copy(Y(0)->count(), dy, da, ctx());
    }
}

template <class Context>
void AddGradientOp<Context>::RunOnDevice() {
    DEFINE_INPUT_DESC;
    Y(0)->ReshapeLike(*A);
    Y(1)->ReshapeLike(*B);

    if (XIsType(X(-1), int8_t)) {
        DEFINE_FUNDAMENTAL_TYPED_IMPL(int8_t);
    } else if (XIsType(X(-1), uint8_t)) {
        DEFINE_FUNDAMENTAL_TYPED_IMPL(uint8_t);
    } else if (XIsType(X(-1), int)) {
        DEFINE_FUNDAMENTAL_TYPED_IMPL(int);
    } else if (XIsType(X(-1), int64_t)) {
        DEFINE_FUNDAMENTAL_TYPED_IMPL(int64_t);
    } else if (XIsType(X(-1), float16)) {
        DEFINE_FUNDAMENTAL_TYPED_IMPL(float16);
    } else if (XIsType(X(-1), float)) {
        DEFINE_FUNDAMENTAL_TYPED_IMPL(float);
    } else if (XIsType(X(-1), double)) {
        DEFINE_FUNDAMENTAL_TYPED_IMPL(double);
    } else {
        LOG(FATAL) << DTypeString(X(-1), {
            "int8", "uint8", "int32", "int64",
            "float16", "float32", "float64",
        });
    }
}

DEPLOY_CPU(Add);
#ifdef WITH_CUDA
DEPLOY_CUDA(Add);
#endif

DEPLOY_CPU(AddGradient);
#ifdef WITH_CUDA
DEPLOY_CUDA(AddGradient);
#endif

OPERATOR_SCHEMA(Add)
     /* A, B */
    .NumInputs(2)
     /* Y */
    .NumOutputs(1)
     /* A => Y */
    .Inplace({ { 0, 0 } });

OPERATOR_SCHEMA(AddGradient)
     /* dY */
    .NumInputs(1)
     /* dA, dB */
    .NumOutputs(2)
     /* dY => dA */
    .Inplace({ { 0, 0 } });

namespace {

class GradientMaker : public GradientMakerBase {
 public:
    GRADIENT_MAKER_CTOR(GradientMaker);
    vector<OperatorDef> MakeDef() override {
        return SingleDef(def.type() + "Gradient", "",
            vector<string>({ GO(0) }),
            vector<string>({ GI(0), GI(1) })
        );
    }
};

}  // namespace

REGISTER_GRADIENT(Add, GradientMaker);

}  // namespace dragon