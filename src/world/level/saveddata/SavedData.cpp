#include "SavedData.h"

#include <type_traits>
#include <utility>

SavedData::SavedData(const std::wstring& id) : id(id) { dirty = false; }

void SavedData::setDirty() { setDirty(true); }

void SavedData::setDirty(bool dirty) { this->dirty = dirty; }

bool SavedData::isDirty() { return dirty; }
