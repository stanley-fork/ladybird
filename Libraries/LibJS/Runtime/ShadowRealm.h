/*
 * Copyright (c) 2021-2022, Linus Groh <linusg@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibJS/Runtime/Completion.h>
#include <LibJS/Runtime/ExecutionContext.h>
#include <LibJS/Runtime/Object.h>
#include <LibJS/Runtime/Realm.h>

namespace JS {

class ShadowRealm final : public Object {
    JS_OBJECT(ShadowRealm, Object);
    GC_DECLARE_ALLOCATOR(ShadowRealm);

public:
    virtual ~ShadowRealm() override = default;

    [[nodiscard]] Realm const& shadow_realm() const { return *m_shadow_realm; }
    [[nodiscard]] Realm& shadow_realm() { return *m_shadow_realm; }
    void set_shadow_realm(GC::Ref<Realm> realm) { m_shadow_realm = realm; }

private:
    ShadowRealm(Object& prototype);

    virtual void visit_edges(Visitor&) override;

    // 3.5 Properties of ShadowRealm Instances, https://tc39.es/proposal-shadowrealm/#sec-properties-of-shadowrealm-instances
    GC::Ptr<Realm> m_shadow_realm; // [[ShadowRealm]]
};

ThrowCompletionOr<void> copy_name_and_length(VM&, FunctionObject& function, FunctionObject& target, Optional<StringView> prefix = {}, Optional<unsigned> arg_count = {});
ThrowCompletionOr<Value> perform_shadow_realm_eval(VM&, Value source, Realm& caller_realm, Realm& eval_realm);
ThrowCompletionOr<Value> shadow_realm_import_value(VM&, String specifier_string, String export_name_string, Realm& caller_realm, Realm& eval_realm);
ThrowCompletionOr<Value> get_wrapped_value(VM&, Realm& caller_realm, Value);
NonnullOwnPtr<ExecutionContext> get_shadow_realm_context(Realm& shadow_realm, bool strict_eval, u32 registers_and_constants_and_locals_count);

}
