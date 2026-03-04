#pragma once

#include "platform/tutorial/FullTutorialMode.h"

class ClientConnection;
class Minecraft;

class TrialMode : public FullTutorialMode {
public:
    TrialMode(int iPad, Minecraft* minecraft, ClientConnection* connection);

    virtual bool isImplemented() { return true; }
};
