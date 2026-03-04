#include "ConsoleGameMode.h"

#include "platform/tutorial/Tutorial.h"
#include "platform/tutorial/TutorialMode.h"

class ClientConnection;
class Minecraft;

ConsoleGameMode::ConsoleGameMode(
    int               iPad,
    Minecraft*        minecraft,
    ClientConnection* connection
)
: TutorialMode(iPad, minecraft, connection) {
    tutorial = new Tutorial(iPad);
}
