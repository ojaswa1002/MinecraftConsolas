#include "I18n.h"

#include <type_traits>
#include <utility>

#include "Language.h"

Language*    I18n::lang = Language::getInstance();
std::wstring I18n::get(const std::wstring& id, ...) {
#ifdef __PSVITA__ // 4J - vita doesn't like having a reference type as the last
                  // parameter passed to va_start - we shouldn't need this
                  // method anyway
    return L"";
#elif _MSC_VER >= 1930 // VS2022+ also disallows va_start with reference types
    return id;
#else
    va_list va;
    va_start(va, id);
    return I18n::get(id, va);
#endif
}

std::wstring I18n::get(const std::wstring& id, va_list args) {
    return lang->getElement(id, args);
}
