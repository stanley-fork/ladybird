/*
 * Copyright (c) 2023-2024, Tim Flynn <trflynn89@ladybird.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Function.h>
#include <AK/NonnullOwnPtr.h>
#include <LibCore/EventLoopImplementation.h>

namespace WebView {

class EventLoopManagerMacOS final : public Core::EventLoopManager {
public:
    virtual NonnullOwnPtr<Core::EventLoopImplementation> make_implementation() override;

    virtual intptr_t register_timer(Core::EventReceiver&, int interval_milliseconds, bool should_reload, Core::TimerShouldFireWhenNotVisible) override;
    virtual void unregister_timer(intptr_t timer_id) override;

    virtual void register_notifier(Core::Notifier&) override;
    virtual void unregister_notifier(Core::Notifier&) override;

    virtual void did_post_event() override;

    virtual int register_signal(int, Function<void(int)>) override;
    virtual void unregister_signal(int) override;
};

class EventLoopImplementationMacOS final : public Core::EventLoopImplementation {
public:
    // FIXME: This currently only manages the main NSApp event loop, as that is all we currently
    //        interact with. When we need multiple event loops, or an event loop that isn't the
    //        NSApp loop, we will need to create our own CFRunLoop.
    static NonnullOwnPtr<EventLoopImplementationMacOS> create();

    virtual int exec() override;
    virtual size_t pump(PumpMode) override;
    virtual void quit(int) override;
    virtual void wake() override;
    virtual bool was_exit_requested() const override;
    virtual void post_event(Core::EventReceiver& receiver, NonnullOwnPtr<Core::Event>&&) override;

private:
    EventLoopImplementationMacOS() = default;

    int m_exit_code { 0 };
};

}
