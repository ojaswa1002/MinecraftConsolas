#include "GuiMessage.h"

#include <type_traits>
#include <utility>

GuiMessage::GuiMessage(const std::wstring& string) {
    this->string = string;
    ticks        = 0;
}
