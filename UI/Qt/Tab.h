/*
 * Copyright (c) 2022, Andreas Kling <andreas@ladybird.org>
 * Copyright (c) 2022, Matthew Costa <ucosty@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <LibWeb/HTML/AudioPlayState.h>
#include <UI/Qt/FindInPageWidget.h>
#include <UI/Qt/LocationEdit.h>
#include <UI/Qt/WebContentView.h>

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMenu>
#include <QPointer>
#include <QToolBar>
#include <QToolButton>
#include <QWidget>

namespace Ladybird {

class BrowserWindow;

class HyperlinkLabel final : public QLabel {
    Q_OBJECT

public:
    explicit HyperlinkLabel(QWidget* parent = nullptr)
        : QLabel(parent)
    {
        setMouseTracking(true);
    }

    virtual void enterEvent(QEnterEvent* event) override
    {
        emit mouse_entered(event);
    }

signals:
    void mouse_entered(QEnterEvent*);
};

class Tab final : public QWidget {
    Q_OBJECT

public:
    Tab(BrowserWindow* window, RefPtr<WebView::WebContentClient> parent_client = nullptr, size_t page_index = 0);
    virtual ~Tab() override;

    WebContentView& view() { return *m_view; }

    void navigate(URL::URL const&);
    void load_html(StringView);

    void back();
    void forward();
    void reload();

    void debug_request(ByteString const& request, ByteString const& argument = "");

    void open_file();
    void update_reset_zoom_button();

    void show_find_in_page();
    void find_previous();
    void find_next();

    QIcon const& favicon() const { return m_favicon; }
    QString const& title() const { return m_title; }

    QMenu* context_menu() const { return m_context_menu; }

    void update_navigation_buttons_state();

    QToolButton* hamburger_button() const { return m_hamburger_button; }

    void update_hover_label();

    void set_block_popups(bool);
    void set_line_box_borders(bool);
    void set_scripting(bool);
    void set_content_filtering(bool);
    void set_user_agent_string(ByteString const&);
    void set_navigator_compatibility_mode(ByteString const&);

    bool url_is_hidden() const { return m_location_edit->url_is_hidden(); }
    void set_url_is_hidden(bool url_is_hidden) { m_location_edit->set_url_is_hidden(url_is_hidden); }

public slots:
    void focus_location_editor();
    void location_edit_return_pressed();

signals:
    void title_changed(int id, QString const&);
    void favicon_changed(int id, QIcon const&);
    void audio_play_state_changed(int id, Web::HTML::AudioPlayState);
    void navigation_buttons_state_changed(int id);

private:
    virtual void resizeEvent(QResizeEvent*) override;
    virtual bool event(QEvent*) override;

    void recreate_toolbar_icons();

    void open_link(URL::URL const&);
    void open_link_in_new_tab(URL::URL const&);
    void copy_link_url(URL::URL const&);

    QBoxLayout* m_layout { nullptr };
    QToolBar* m_toolbar { nullptr };
    QToolButton* m_hamburger_button { nullptr };
    QAction* m_hamburger_button_action { nullptr };
    QToolButton* m_reset_zoom_button { nullptr };
    QAction* m_reset_zoom_button_action { nullptr };
    LocationEdit* m_location_edit { nullptr };
    WebContentView* m_view { nullptr };
    FindInPageWidget* m_find_in_page { nullptr };
    BrowserWindow* m_window { nullptr };
    QString m_title;
    HyperlinkLabel* m_hover_label { nullptr };
    QIcon m_favicon;

    QMenu* m_context_menu { nullptr };

    QMenu* m_page_context_menu { nullptr };
    Optional<String> m_page_context_menu_search_text;

    QMenu* m_link_context_menu { nullptr };
    QAction* m_link_context_menu_copy_url_action { nullptr };
    URL::URL m_link_context_menu_url;

    QMenu* m_image_context_menu { nullptr };
    QAction* m_image_context_menu_copy_image_action { nullptr };
    Optional<Gfx::ShareableBitmap> m_image_context_menu_bitmap;
    URL::URL m_image_context_menu_url;

    QMenu* m_audio_context_menu { nullptr };
    QMenu* m_video_context_menu { nullptr };
    QIcon m_media_context_menu_play_icon;
    QIcon m_media_context_menu_pause_icon;
    QIcon m_media_context_menu_mute_icon;
    QIcon m_media_context_menu_unmute_icon;
    QAction* m_media_context_menu_play_pause_action { nullptr };
    QAction* m_media_context_menu_mute_unmute_action { nullptr };
    QAction* m_media_context_menu_controls_action { nullptr };
    QAction* m_media_context_menu_loop_action { nullptr };
    URL::URL m_media_context_menu_url;

    QMenu* m_select_dropdown { nullptr };

    int tab_index();

    QPointer<QDialog> m_dialog;

    bool m_can_navigate_back { false };
    bool m_can_navigate_forward { false };
};

}
