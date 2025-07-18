/*
 * Copyright (c) 2021, Linus Groh <linusg@serenityos.org>
 * Copyright (c) 2024, Tim Flynn <trflynn89@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibJS/Runtime/PrototypeObject.h>
#include <LibJS/Runtime/Temporal/PlainDateTime.h>

namespace JS::Temporal {

class JS_API PlainDateTimePrototype final : public PrototypeObject<PlainDateTimePrototype, PlainDateTime> {
    JS_PROTOTYPE_OBJECT(PlainDateTimePrototype, PlainDateTime, Temporal.PlainDateTime);
    GC_DECLARE_ALLOCATOR(PlainDateTimePrototype);

public:
    virtual void initialize(Realm&) override;
    virtual ~PlainDateTimePrototype() override = default;

private:
    explicit PlainDateTimePrototype(Realm&);

    JS_DECLARE_NATIVE_FUNCTION(calendar_id_getter);
    JS_DECLARE_NATIVE_FUNCTION(era_getter);
    JS_DECLARE_NATIVE_FUNCTION(era_year_getter);
    JS_DECLARE_NATIVE_FUNCTION(year_getter);
    JS_DECLARE_NATIVE_FUNCTION(month_getter);
    JS_DECLARE_NATIVE_FUNCTION(month_code_getter);
    JS_DECLARE_NATIVE_FUNCTION(day_getter);
    JS_DECLARE_NATIVE_FUNCTION(hour_getter);
    JS_DECLARE_NATIVE_FUNCTION(minute_getter);
    JS_DECLARE_NATIVE_FUNCTION(second_getter);
    JS_DECLARE_NATIVE_FUNCTION(millisecond_getter);
    JS_DECLARE_NATIVE_FUNCTION(microsecond_getter);
    JS_DECLARE_NATIVE_FUNCTION(nanosecond_getter);
    JS_DECLARE_NATIVE_FUNCTION(day_of_week_getter);
    JS_DECLARE_NATIVE_FUNCTION(day_of_year_getter);
    JS_DECLARE_NATIVE_FUNCTION(week_of_year_getter);
    JS_DECLARE_NATIVE_FUNCTION(year_of_week_getter);
    JS_DECLARE_NATIVE_FUNCTION(days_in_week_getter);
    JS_DECLARE_NATIVE_FUNCTION(days_in_month_getter);
    JS_DECLARE_NATIVE_FUNCTION(days_in_year_getter);
    JS_DECLARE_NATIVE_FUNCTION(months_in_year_getter);
    JS_DECLARE_NATIVE_FUNCTION(in_leap_year_getter);
    JS_DECLARE_NATIVE_FUNCTION(with);
    JS_DECLARE_NATIVE_FUNCTION(with_plain_time);
    JS_DECLARE_NATIVE_FUNCTION(with_calendar);
    JS_DECLARE_NATIVE_FUNCTION(add);
    JS_DECLARE_NATIVE_FUNCTION(subtract);
    JS_DECLARE_NATIVE_FUNCTION(until);
    JS_DECLARE_NATIVE_FUNCTION(since);
    JS_DECLARE_NATIVE_FUNCTION(round);
    JS_DECLARE_NATIVE_FUNCTION(equals);
    JS_DECLARE_NATIVE_FUNCTION(to_string);
    JS_DECLARE_NATIVE_FUNCTION(to_locale_string);
    JS_DECLARE_NATIVE_FUNCTION(to_json);
    JS_DECLARE_NATIVE_FUNCTION(value_of);
    JS_DECLARE_NATIVE_FUNCTION(to_zoned_date_time);
    JS_DECLARE_NATIVE_FUNCTION(to_plain_date);
    JS_DECLARE_NATIVE_FUNCTION(to_plain_time);
};

}
