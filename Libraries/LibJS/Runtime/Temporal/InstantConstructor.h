/*
 * Copyright (c) 2021-2022, Linus Groh <linusg@serenityos.org>
 * Copyright (c) 2024, Tim Flynn <trflynn89@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibJS/Runtime/NativeFunction.h>

namespace JS::Temporal {

class JS_API InstantConstructor final : public NativeFunction {
    JS_OBJECT(InstantConstructor, NativeFunction);
    GC_DECLARE_ALLOCATOR(InstantConstructor);

public:
    virtual void initialize(Realm&) override;
    virtual ~InstantConstructor() override = default;

    virtual ThrowCompletionOr<Value> call() override;
    virtual ThrowCompletionOr<GC::Ref<Object>> construct(FunctionObject& new_target) override;

private:
    explicit InstantConstructor(Realm&);

    virtual bool has_constructor() const override { return true; }

    JS_DECLARE_NATIVE_FUNCTION(from);
    JS_DECLARE_NATIVE_FUNCTION(from_epoch_milliseconds);
    JS_DECLARE_NATIVE_FUNCTION(from_epoch_nanoseconds);
    JS_DECLARE_NATIVE_FUNCTION(compare);
};

}
