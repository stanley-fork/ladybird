/*
 * Copyright (c) 2021, Tim Flynn <trflynn89@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibJS/Runtime/Object.h>
#include <LibJS/Runtime/PrimitiveString.h>

namespace JS {

class JS_API RegExpStringIterator final : public Object {
    JS_OBJECT(RegExpStringIterator, Object);
    GC_DECLARE_ALLOCATOR(RegExpStringIterator);

public:
    static GC::Ref<RegExpStringIterator> create(Realm&, Object& regexp_object, GC::Ref<PrimitiveString> string, bool global, bool unicode);

    virtual ~RegExpStringIterator() override = default;

    Object& regexp_object() { return m_regexp_object; }
    GC::Ref<PrimitiveString> string() const { return m_string; }
    bool global() const { return m_global; }
    bool unicode() const { return m_unicode; }

    bool done() const { return m_done; }
    void set_done() { m_done = true; }

private:
    explicit RegExpStringIterator(Object& prototype, Object& regexp_object, GC::Ref<PrimitiveString> string, bool global, bool unicode);

    virtual void visit_edges(Cell::Visitor&) override;

    GC::Ref<Object> m_regexp_object;
    GC::Ref<PrimitiveString> m_string;
    bool m_global { false };
    bool m_unicode { false };
    bool m_done { false };
};

}
