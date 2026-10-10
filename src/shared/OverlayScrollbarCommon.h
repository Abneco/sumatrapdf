/* Copyright 2026 the SumatraPDF project authors (see AUTHORS file).
   License: GPLv3 */

// --- shared by OverlayScrollbarCommon.cpp and each app's OverlayScrollbar.cpp ---

Color ThemeTrackColor();
Color ThemeThumbColor();
Color ThemeThumbHoverColor();
using State = OverlayScrollbar::State;
bool IsThick(OverlayScrollbar* sb);
bool IsVisible(OverlayScrollbar* sb);
bool IsActive(OverlayScrollbar* sb);
int ScaledWidth(OverlayScrollbar* sb, bool thick);
bool IsVert(OverlayScrollbar* sb);

Rect GetTrackRect(OverlayScrollbar* sb);
Rect GetArrowTopRect(OverlayScrollbar* sb);
Rect GetArrowBottomRect(OverlayScrollbar* sb);
void ShowScrollbarWindow(OverlayScrollbar* sb, bool thick);
void HideScrollbarWindow(OverlayScrollbar* sb);

// implemented by each app
bool IsAlwaysThickMode(OverlayScrollbar* sb);
Rect ClientRect(OverlayScrollbar* sb);
void SetState(OverlayScrollbar* sb, State newState);
