#include "TrialMode.h"

#include "platform/tutorial/FullTutorial.h"
#include "platform/tutorial/FullTutorialMode.h"

class ClientConnection;
class Minecraft;

TrialMode::TrialMode(
    int               iPad,
    Minecraft*        minecraft,
    ClientConnection* connection
)
: FullTutorialMode(iPad, minecraft, connection) {
    tutorial = new FullTutorial(iPad, true);
}
