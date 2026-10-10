/* Copyright 2022 the SumatraPDF project authors (see AUTHORS file).
   License: GPLv3 */

#include "base/Base.h"
#include "base/File.h"

#include "gui/UIModels.h"

#include "Settings.h"
#include "AppSettings.h"
#include "Translations.h"
#include "DisplayMode.h"
#include "DocController.h"
#include "EngineBase.h"
#include "Annotation.h"
#include "FormFields.h"
#include "Theme.h"
#include "SumatraPDF.h"
#include "MainWindow.h"
#include "AppHelpersCommon.h"

// One-off helpers that orig and ng both need and that have no shared file of
// their own module: each is a few lines used by one dialog or panel.

void FreeTabGroup(TabGroup* group) {
    if (!group) {
        return;
    }
    str::Free(group->name);
    if (group->tabFiles) {
        for (auto* tf : *group->tabFiles) {
            str::Free(tf->path);
            free(tf);
        }
        delete group->tabFiles;
    }
    free(group);
}

Str ScrollbarModeDisplayName(int idx) {
    if (idx == kScrollbarSmart) {
        return Tr("Smart Overlay");
    }
    if (idx == kScrollbarOverlay) {
        return Tr("Overlay");
    }
    if (idx == kScrollbarHidden) {
        return Tr("Hidden");
    }
    return Tr("Windows");
}

// list index of the match starting at (page, glyph), or -1 if there is none
int FindMatchIndex(MainWindow* win, int page, int glyph) {
    int n = len(win->findMatches);
    for (int i = 0; i < n; i++) {
        const FindMatch& fm = win->findMatches[i];
        if (fm.startPage == page && fm.startGlyph == glyph) {
            return i;
        }
    }
    return -1;
}

// the field's on-screen font height in pixels: the /DA font size (PDF points)
// scaled to the page's current zoom, or a height-derived fallback for
// auto-sized (/DA size 0) fields.
int FieldFontPx(Annotation* widget, Rect rc) {
    float daSize = GetWidgetFontSize(widget);
    float pageDy = widget->bounds.dy; // field height in page (PDF) units
    if (daSize > 0 && pageDy > 0) {
        float scale = (float)rc.dy / pageDy; // screen px per PDF unit
        return std::max(8, (int)(daSize * scale));
    }
    return std::max(8, (int)((float)rc.dy * 0.7f));
}

int DecimalDigits(int n) {
    int digits = 1;
    while (n >= 10) {
        n /= 10;
        digits++;
    }
    return digits;
}

// find existing Shortcut entry for CmdScreenshot, or nullptr
Shortcut* FindScreenshotShortcutEntry() {
    for (Shortcut* sc : *gSettings->shortcuts) {
        if (str::EqI(sc->cmd, StrL("CmdScreenshot"))) {
            return sc;
        }
    }
    return nullptr;
}

TempStr FavoritePromptTemp(Str pageLabel) {
    int chapter = 0, page = 0;
    if (str::Parse(pageLabel, "%d/%d%$", &chapter, &page)) {
        return fmt(Tr("Name for chapter %d page %d (optional):").s, chapter, page);
    }
    return fmt(Tr("Name for page %s (optional):").s, pageLabel);
}

bool AnnotationHasText(Annotation* annot) {
    if (!AnnotationIsLive(annot)) {
        return false;
    }
    return len(Contents(annot)) > 0;
}

// the text stays readable on a tab that carries a color of its own
Color TabTextColorForBackground(Color text, Color tabBg) {
    if (abs((int)GetLightness(text) - (int)GetLightness(tabBg)) >= 80) {
        return text;
    }
    return IsLightColor(tabBg) ? kColBlack : kColWhite;
}

// cameFrom when it is a direct child of dir (so Back / Forward select it), else empty
Str SelectIfChildOf(Str cameFrom, Str dir) {
    if (len(cameFrom) == 0 || len(dir) == 0) {
        return {};
    }
    if (!path::IsSame(path::GetDirTemp(cameFrom), dir)) {
        return {};
    }
    return cameFrom;
}
