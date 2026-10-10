/* Copyright 2026 the SumatraPDF project authors (see AUTHORS file).
   License: GPLv3 */

// --- shared by ImageSaveCropResizeCommon.cpp and each app's ImageSaveCropResize.cpp ---

bool ExtMatchesOriginal(Str ext, Str originalExt);
TempStr PathWithExtTemp(Str path, Str ext);

enum class DragEdge {
    None,
    Left,
    Right,
    Top,
    Bottom,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
    Move,   // only used in crop mode
    NewCrop // only used in crop mode
};
