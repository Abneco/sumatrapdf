/* Copyright 2026 the SumatraPDF project authors (see AUTHORS file).
   License: GPLv3 */

// --- shared by MenuCommon.cpp and each app's Menu.cpp ---

bool ShowDebugMenu();
struct FileHistoryEntry {
    Str path;
    int cmdId;
};
void SetFileHistoryCmdIds(Vec<FileHistoryEntry>& files);
TempStr CleanupURLForClipbardCopyTemp(Str s);
