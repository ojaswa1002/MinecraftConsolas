#include "ConsoleInput.h"

#include <type_traits>
#include <utility>

class ConsoleInputSource;

ConsoleInput::ConsoleInput(
    const std::wstring& msg,
    ConsoleInputSource* source
) {
    this->msg    = msg;
    this->source = source;
}
