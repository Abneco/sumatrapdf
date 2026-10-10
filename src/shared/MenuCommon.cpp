/* Copyright 2022 the SumatraPDF project authors (see AUTHORS file).
   License: GPLv3 */

#include "base/Base.h"
#include "base/File.h"
#include "gui/UIModels.h"
#include "Settings.h"
#include "AppSettings.h"
#include "DisplayMode.h"
#include "DocController.h"
#include "EngineBase.h"
#include "base/GuessFileType.h"
#include "EngineAll.h"
#include "DisplayModel.h"
#include "FileHistory.h"
#include "Theme.h"
#include "Annotation.h"
#include "AnnotTextPopup.h"
#include "SumatraConfig.h"
#include "SumatraPDF.h"
#include "MainWindow.h"
#include "WindowTab.h"
#include "Commands.h"
#include "ExternalViewers.h"
#include "Favorites.h"
#include "Translations.h"
#include "PagePosition.h"
#include "Accelerators.h"
#include "ImageSaveCropResize.h"
#include "GoogleLens.h"
#include "CommandAvailability.h"
#include "ReadAloud.h"
#include "ReadingAutoScroll.h"
#include "ReadingBar.h"
#include "Menu.h"
#include "MenuCommon.h"

bool ShowDebugMenu() {
    return gIsDebugBuild || gIsPreReleaseBuild;
}

// A recent file is a CmdFileHistory command carrying the path as an argument.
// Custom commands live until the settings are re-read, so reuse the one already
// made for a path instead of making one per menu rebuild. One pass over the
// commands serves all the entries.
void SetFileHistoryCmdIds(Vec<FileHistoryEntry>& files) {
    Vec<CustomCommand*> cmds;
    GetCommandsWithOrigId(cmds, CmdFileHistory);
    for (CustomCommand* cmd : cmds) {
        Str path = GetCommandStringArg(cmd, kCmdArgFilePath, {});
        for (FileHistoryEntry& fe : files) {
            if (fe.cmdId == 0 && str::EqI(path, fe.path)) {
                fe.cmdId = cmd->id;
                break;
            }
        }
    }

    for (FileHistoryEntry& fe : files) {
        if (fe.cmdId != 0) {
            continue;
        }
        CommandArg* arg = NewStringArg(kCmdArgFilePath, fe.path);
        fe.cmdId = CreateCustomCommand(StrL("CmdFileHistory"), CmdFileHistory, arg)->id;
    }
}

// s could be in format "file://path.pdf#page=1" or "mailto:foo@bar.com"
// We only want the "path.pdf" / "foo@bar.com"
TempStr CleanupURLForClipbardCopyTemp(Str s) {
    Str slice = s;
    str::TrimPrefix(slice, StrL("file:"));
    str::TrimPrefix(slice, StrL("mailto:"));
    return str::DupTemp(slice);
}

// Remove Win32's '&' accelerator markup and remember the first character that
// needs an underline. A doubled ampersand is a literal one.
MenuAccelText ParseMenuAccelTextTemp(Str s) {
    MenuAccelText res;
    if (!str::Contains(s, StrL("&"))) {
        res.display = s;
        return res;
    }
    char* buf = AllocArrayTemp<char>(len(s) + 1);
    int out = 0;
    for (int i = 0; i < len(s); i++) {
        if (s.s[i] != '&') {
            buf[out++] = s.s[i];
            continue;
        }
        if (i + 1 >= len(s)) {
            break;
        }
        if (s.s[i + 1] == '&') {
            buf[out++] = '&';
            i++;
            continue;
        }
        if (res.underlineOff < 0) {
            res.underlineOff = out;
            int remain = len(s) - i - 1;
            int n = utf8RuneLen((const u8*)(s.s + i + 1));
            res.underlineLen = std::min(std::max(n, 1), remain);
        }
    }
    buf[out] = 0;
    res.display = Str(buf, out);
    return res;
}
