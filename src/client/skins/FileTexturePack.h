#pragma once

#include <mss.h>

#include "AbstractTexturePack.h"

class File;
class TexturePack;

class FileTexturePack : public AbstractTexturePack {
private:
    // ZipFile *zipFile;

public:
    FileTexturePack(DWORD id, File* file, TexturePack* fallback);

    //@Override
    void unload(Textures* textures);

protected:
    InputStream*
    getResourceImplementation(const std::wstring& name); // throws IOException

public:
    //@Override
    bool hasFile(const std::wstring& name);

private:
    void loadZipFile(); // throws IOException

public:
    bool isTerrainUpdateCompatible();
};
