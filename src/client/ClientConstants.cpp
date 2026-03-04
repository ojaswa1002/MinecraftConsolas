#include "ClientConstants.h"

#include <type_traits>
#include <utility>

#include "platform/buildver/BuildVer.h"

const std::wstring ClientConstants::VERSION_STRING =
    std::wstring(L"Minecraft Xbox ")
    + VER_FILEVERSION_STR_W; //+ SharedConstants::VERSION_STRING;
