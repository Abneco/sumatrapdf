/* Copyright 2026 the SumatraPDF project authors (see AUTHORS file).
   License: GPLv3 */

// one-off helpers shared by orig and ng; see AppHelpersCommon.cpp

struct TabGroup;
struct MainWindow;
struct Annotation;
struct Shortcut;

void FreeTabGroup(TabGroup* group);
Str ScrollbarModeDisplayName(int idx);
int FindMatchIndex(MainWindow* win, int page, int glyph);
int FieldFontPx(Annotation* widget, Rect rc);
int DecimalDigits(int n);
Shortcut* FindScreenshotShortcutEntry();
TempStr FavoritePromptTemp(Str pageLabel);
bool AnnotationHasText(Annotation* annot);
Color TabTextColorForBackground(Color text, Color tabBg);
Str SelectIfChildOf(Str cameFrom, Str dir);
