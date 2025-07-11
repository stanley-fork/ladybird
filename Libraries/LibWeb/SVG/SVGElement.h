/*
 * Copyright (c) 2020, Matthew Olsson <mattco@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/DOM/Document.h>
#include <LibWeb/DOM/Element.h>
#include <LibWeb/HTML/HTMLOrSVGElement.h>
#include <LibWeb/SVG/SVGAnimatedString.h>

namespace Web::SVG {

class SVGElement
    : public DOM::Element
    , public HTML::GlobalEventHandlers
    , public HTML::HTMLOrSVGElement<SVGElement> {
    WEB_PLATFORM_OBJECT(SVGElement, DOM::Element);

public:
    virtual bool requires_svg_container() const override { return true; }

    GC::Ref<SVGAnimatedString> class_name();
    GC::Ptr<SVGSVGElement> owner_svg_element();
    GC::Ptr<SVGElement> viewport_element();

    bool should_include_in_accessibility_tree() const;
    virtual Optional<ARIA::Role> default_role() const override;

    GC::Ref<SVGAnimatedLength> svg_animated_length_for_property(CSS::PropertyID) const;

    virtual bool is_presentational_hint(FlyString const&) const override;
    virtual void apply_presentational_hints(GC::Ref<CSS::CascadedProperties>) const override;

protected:
    SVGElement(DOM::Document&, DOM::QualifiedName);

    virtual void initialize(JS::Realm&) override;
    virtual void visit_edges(Cell::Visitor&) override;

    virtual void attribute_changed(FlyString const& name, Optional<String> const& old_value, Optional<String> const& value, Optional<FlyString> const& namespace_) override;
    virtual WebIDL::ExceptionOr<void> cloned(DOM::Node&, bool) const override;
    virtual void children_changed(ChildrenChangedMetadata const*) override;
    virtual void inserted() override;
    virtual void removed_from(Node* old_parent, Node& old_root) override;

    void update_use_elements_that_reference_this();
    void remove_from_use_element_that_reference_this();

private:
    // ^HTML::GlobalEventHandlers
    virtual GC::Ptr<DOM::EventTarget> global_event_handlers_to_event_target(FlyString const&) override { return *this; }

    virtual bool is_svg_element() const final { return true; }

    GC::Ptr<SVGAnimatedString> m_class_name_animated_string;
};

}

namespace Web::DOM {

template<>
inline bool Node::fast_is<SVG::SVGElement>() const { return is_svg_element(); }

}
