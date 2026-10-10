/* Copyright 2022 the SumatraPDF project authors (see AUTHORS file).
   License: GPLv3 */

#include "base/Base.h"
#include "base/GuessFileType.h"

#include "BrowserViewCommon.h"

// Small helpers of the browser-backed document view that orig's
// gui/win/BrowserDocView.cpp and ng's gui/BrowserView.cpp share.

TempStr ChmMimeFromPathTemp(Str path, Str data) {
    Str ext = str::SliceFromCharLast(path, '.');
    if (str::ContainsChar(ext, ';')) {
        Str semi = str::SliceFromChar(ext, ';');
        TempStr trimmed = str::DupTemp(Str(path.s, (int)(semi.s - path.s)));
        return ChmMimeFromPathTemp(trimmed, data);
    }

    TempStr imgExt = GfxFileExtFromDataTemp(data);
    TempStr mime = MimeTypeFromExtTemp(ext, imgExt);
    if (len(mime) == 0) {
        mime = StrL("text/html");
    }
    return mime;
}

// escape s for use inside a single-quoted JS string literal
TempStr JsEscapeTemp(Str s) {
    str::Builder buf;
    for (int i = 0; i < s.len; i++) {
        char c = s.s[i];
        switch (c) {
            case '\\':
                buf.Append(StrL("\\\\"));
                break;
            case '\'':
                buf.Append(StrL("\\'"));
                break;
            case '\n':
                buf.Append(StrL("\\n"));
                break;
            case '\r':
                buf.Append(StrL("\\r"));
                break;
            case '\t':
                buf.Append(StrL("\\t"));
                break;
            default:
                buf.AppendChar(c);
                break;
        }
    }
    return ToStrTemp(buf);
}
