#include "DLCLocalisationFile.h"

#include <cstddef>

#include "platform/localisation/StringTable.h"

#include "DLCFile.h"
#include "DLCManager.h"

DLCLocalisationFile::DLCLocalisationFile(const std::wstring& path)
: DLCFile(DLCManager::e_DLCType_LocalisationData, path) {
    m_strings = NULL;
}

void DLCLocalisationFile::addData(PBYTE pbData, DWORD dwBytes) {
    m_strings = new StringTable(pbData, dwBytes);
}
