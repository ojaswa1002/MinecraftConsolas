#pragma once

#include <string>

class ConsoleInputSource;

class ConsoleInput {
public:
    std::wstring        msg;
    ConsoleInputSource* source;

    ConsoleInput(const std::wstring& msg, ConsoleInputSource* source);
};
