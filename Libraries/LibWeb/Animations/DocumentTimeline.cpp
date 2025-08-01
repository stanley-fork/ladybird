/*
 * Copyright (c) 2023, Matthew Olsson <mattco@serenityos.org>.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibGC/Heap.h>
#include <LibJS/Runtime/Realm.h>
#include <LibWeb/Animations/DocumentTimeline.h>
#include <LibWeb/Bindings/DocumentTimelinePrototype.h>
#include <LibWeb/DOM/Document.h>
#include <LibWeb/HTML/Window.h>
#include <LibWeb/HighResolutionTime/Performance.h>
#include <LibWeb/HighResolutionTime/TimeOrigin.h>
#include <LibWeb/WebIDL/ExceptionOr.h>

namespace Web::Animations {

GC_DEFINE_ALLOCATOR(DocumentTimeline);

GC::Ref<DocumentTimeline> DocumentTimeline::create(JS::Realm& realm, DOM::Document& document, HighResolutionTime::DOMHighResTimeStamp origin_time)
{
    auto timeline = realm.create<DocumentTimeline>(realm, document, origin_time);
    auto current_time = document.last_animation_frame_timestamp();
    if (!current_time.has_value()) {
        // The document hasn't processed an animation frame yet, we use the navigation start time, which is either the time
        // that the previous document started to be unloaded or the creation time of the current document.
        current_time = HighResolutionTime::relative_high_resolution_time(document.load_timing_info().navigation_start_time, realm.global_object());
    }
    timeline->set_current_time(current_time);
    return timeline;
}

// https://www.w3.org/TR/web-animations-1/#dom-documenttimeline-documenttimeline
WebIDL::ExceptionOr<GC::Ref<DocumentTimeline>> DocumentTimeline::construct_impl(JS::Realm& realm, DocumentTimelineOptions options)
{
    // Creates a new DocumentTimeline. The Document with which the timeline is associated is the Document associated
    // with the Window that is the current global object.
    auto& window = as<HTML::Window>(realm.global_object());
    return create(realm, window.associated_document(), options.origin_time);
}

// https://www.w3.org/TR/web-animations-1/#ref-for-timeline-time-to-origin-relative-time
Optional<double> DocumentTimeline::convert_a_timeline_time_to_an_origin_relative_time(Optional<double> timeline_time)
{
    // To convert a timeline time, timeline time, to an origin-relative time for a document timeline, timeline, return
    // the sum of the timeline time and timeline’s origin time. If timeline is inactive, return an unresolved time
    // value.
    if (is_inactive() || !timeline_time.has_value())
        return {};
    return timeline_time.value() + m_origin_time;
}

// https://drafts.csswg.org/web-animations-1/#document-timeline
void DocumentTimeline::set_current_time(Optional<double> current_time)
{
    // A document timeline is a type of timeline that is associated with a document and whose current time is calculated
    // as a fixed offset from the now timestamp provided each time the update animations and send events procedure is
    // run. This fixed offset is equal to the current time of the default document timeline when this timeline’s current
    // time was zero, and is thus referred to as the document timeline’s origin time.
    if (!current_time.has_value())
        Base::set_current_time({});
    else
        Base::set_current_time(current_time.value() - m_origin_time);

    // https://drafts.csswg.org/web-animations-1/#ref-for-active-timeline
    // After a document timeline becomes active, it is monotonically increasing.
    if (!m_is_monotonically_increasing && !is_inactive())
        m_is_monotonically_increasing = true;
}

// https://www.w3.org/TR/web-animations-1/#document-timelines
bool DocumentTimeline::is_inactive() const
{
    // A document timeline that is associated with a Document which is not an active document is also considered to be
    // inactive.
    return Base::is_inactive() || !associated_document()->is_active();
}

DocumentTimeline::DocumentTimeline(JS::Realm& realm, DOM::Document& document, HighResolutionTime::DOMHighResTimeStamp origin_time)
    : AnimationTimeline(realm)
    , m_origin_time(origin_time)
{
    set_associated_document(document);
}

void DocumentTimeline::initialize(JS::Realm& realm)
{
    WEB_SET_PROTOTYPE_FOR_INTERFACE(DocumentTimeline);
    Base::initialize(realm);
}

}
