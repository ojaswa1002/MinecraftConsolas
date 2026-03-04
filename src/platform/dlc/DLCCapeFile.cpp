#include "DLCCapeFile.h"

#include "win/Windows64_App.h"

#include "DLCFile.h"
#include "DLCManager.h"

DLCCapeFile::DLCCapeFile(const std::wstring& path)
: DLCFile(DLCManager::e_DLCType_Cape, path) {}

void DLCCapeFile::addData(PBYTE pbData, DWORD dwBytes) {
    app.AddMemoryTextureFile(m_path, pbData, dwBytes);
}
