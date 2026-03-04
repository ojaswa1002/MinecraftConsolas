#include "KeyMapping.h"

#include <type_traits>
#include <utility>

KeyMapping::KeyMapping(const std::wstring& name, int key) {
    this->name = name;
    this->key  = key;
}
