#include "DLCColourTableFile.h"

#include <cstddef>

#include "client/Minecraft.h"
#include "client/skins/TexturePack.h"
#include "client/skins/TexturePackRepository.h"
#include "platform/colours/ColourTable.h"
#include "win/Windows64_App.h"

#include "DLCFile.h"
#include "DLCManager.h"

DLCColourTableFile::DLCColourTableFile(const std::wstring& path)
: DLCFile(DLCManager::e_DLCType_ColourTable, path) {
    m_colourTable = NULL;
}

DLCColourTableFile::~DLCColourTableFile() {
    if (m_colourTable != NULL) {
        app.DebugPrintf("Deleting DLCColourTableFile data\n");
        delete m_colourTable;
    }
}

void DLCColourTableFile::addData(PBYTE pbData, DWORD dwBytes) {
    ColourTable* defaultColourTable =
        Minecraft::GetInstance()->skins->getDefault()->getColourTable();
    m_colourTable = new ColourTable(defaultColourTable, pbData, dwBytes);
}
