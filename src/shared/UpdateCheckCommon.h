/* Copyright 2026 the SumatraPDF project authors (see AUTHORS file).
   License: GPLv3 */

// --- shared by UpdateCheckCommon.cpp and each app's UpdateCheck.cpp ---

struct UpdateInfo;
extern UpdateInfo* gPendingUpdate;
static const Str kExpectedDlHost = StrL("https://www.sumatrapdfreader.org/");
bool IsTrustedUpdateDlUrl(Str dlURL);
void BuildUpdateURL(str::Builder& url, Str baseURL, UpdateCheck updateCheckType);
