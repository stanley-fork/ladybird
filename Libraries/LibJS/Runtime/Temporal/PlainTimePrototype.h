/*
 * Copyright (c) 2021, Linus Groh <linusg@serenityos.org>
 * Copyright (c) 2024, Tim Flynn <trflynn89@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibJS/Runtime/PrototypeObject.h>
#include <LibJS/Runtime/Temporal/PlainTime.h>

namespace JS::Temporal {

class JS_API PlainTimePrototype final : public PrototypeObject<PlainTimePrototype, PlainTime> {
    JS_PROTOTYPE_OBJECT(PlainTimePrototype, PlainTime, Temporal.PlainTime);
    GC_DECLARE_ALLOCATOR(PlainTimePrototype);

public:
    virtual void initialize(Realm&) override;
    virtual ~PlainTimePrototype() override = default;

private:
    explicit PlainTimePrototype(Realm&);

    JS_DECLARE_NATIVE_FUNCTION(hour_getter);
    JS_DECLARE_NATIVE_FUNCTION(minute_getter);
    JS_DECLARE_NATIVE_FUNCTION(second_getter);
    JS_DECLARE_NATIVE_FUNCTION(millisecond_getter);
    JS_DECLARE_NATIVE_FUNCTION(microsecond_getter);
    JS_DECLARE_NATIVE_FUNCTION(nanosecond_getter);
    JS_DECLARE_NATIVE_FUNCTION(add);
    JS_DECLARE_NATIVE_FUNCTION(subtract);
    JS_DECLARE_NATIVE_FUNCTION(with);
    JS_DECLARE_NATIVE_FUNCTION(until);
    JS_DECLARE_NATIVE_FUNCTION(since);
    JS_DECLARE_NATIVE_FUNCTION(round);
    JS_DECLARE_NATIVE_FUNCTION(equals);
    JS_DECLARE_NATIVE_FUNCTION(to_string);
    JS_DECLARE_NATIVE_FUNCTION(to_locale_string);
    JS_DECLARE_NATIVE_FUNCTION(to_json);
    JS_DECLARE_NATIVE_FUNCTION(value_of);
};

}
