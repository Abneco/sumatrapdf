/* Copyright 2022 the SumatraPDF project authors (see AUTHORS file).
   License: GPLv3 */

#if defined(SUMATRA_NG)
#include "gui/GpuiBridge.h"
#else
#include "base/Base.h"
#endif
#include "gui/Dpi.h"
#include "Theme.h"
#include "OverlayScrollbar.h"
#include "OverlayScrollbarCommon.h"

// Derive scrollbar colors from current theme
Color ThemeTrackColor() {
    Color bg = ThemeControlBackgroundColor();
    return bg;
}

Color ThemeThumbColor() {
    Color bg = ThemeControlBackgroundColor();
    return AccentColor(bg, 100);
}

Color ThemeThumbHoverColor() {
    Color bg = ThemeControlBackgroundColor();
    return AccentColor(bg, 140);
}

bool IsThick(OverlayScrollbar* sb) {
    return sb->state == State::SmartThick || sb->state == State::AlwaysThick;
}

bool IsVisible(OverlayScrollbar* sb) {
    return sb->state == State::SmartThin || sb->state == State::SmartThick || sb->state == State::AlwaysThick;
}

// scrollbar is active: shown or auto-hidden but ready to appear
bool IsActive(OverlayScrollbar* sb) {
    return sb->state != State::Hidden;
}

int ScaledWidth(OverlayScrollbar* sb, bool thick) {
    return thick ? sb->thickWidth : sb->thinWidth;
}

bool IsVert(OverlayScrollbar* sb) {
    return sb->type == OverlayScrollbar::Type::Vert;
}

// returns true if scrollbar is visible (thin, thick, or always thick)
bool IsOverlayScrollbarVisible(OverlayScrollbar* sb) {
    return sb && IsVisible(sb);
}
