/*
 * Copyright (c) 2023-2024, Tim Flynn <trflynn89@serenityos.org>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/Forward.h>
#include <LibURL/URL.h>

#import <Cocoa/Cocoa.h>

@class Tab;

struct TabSettings {
    BOOL should_show_line_box_borders { NO };
    BOOL scripting_enabled { YES };
    BOOL block_popups { YES };
    ByteString user_agent_name { "Disabled"sv };
    ByteString navigator_compatibility_mode { "chrome"sv };
};

@interface TabController : NSWindowController <NSWindowDelegate>

- (instancetype)init;
- (instancetype)initAsChild:(Tab*)parent
                  pageIndex:(u64)page_index;

- (void)loadURL:(URL::URL const&)url;
- (void)loadHTML:(StringView)html url:(URL::URL const&)url;

- (void)onLoadStart:(URL::URL const&)url isRedirect:(BOOL)isRedirect;

- (void)onURLChange:(URL::URL const&)url;
- (void)onBackNavigationEnabled:(BOOL)back_enabled
       forwardNavigationEnabled:(BOOL)forward_enabled;

- (void)onTitleChange:(ByteString const&)title;

- (void)onCreateNewTab;

- (void)navigateBack:(id)sender;
- (void)navigateForward:(id)sender;
- (void)reload:(id)sender;
- (void)clearHistory;

- (void)setPopupBlocking:(BOOL)block_popups;
- (void)setScripting:(BOOL)enabled;
- (void)debugRequest:(ByteString const&)request argument:(ByteString const&)argument;

- (void)focusLocationToolbarItem;

@end
