#pragma once

#include <string>

#include <windows.h>

#include <rrcore.h>

class UITTFFont {
private:
    PBYTE pbData;
    // DWORD dwDataSize;

public:
    UITTFFont(const std::string& path, S32 fallbackCharacter);
    ~UITTFFont();
};
