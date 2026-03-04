#include "FullTutorialMode.h"

#include "client/Minecraft.h"

#include "FullTutorial.h"
#include "FullTutorialMode.h"
#include "Tutorial.h"
#include "TutorialMode.h"

class ClientConnection;

FullTutorialMode::FullTutorialMode(
    int               iPad,
    Minecraft*        minecraft,
    ClientConnection* connection
)
: TutorialMode(iPad, minecraft, connection) {
    tutorial = new FullTutorial(iPad);
    minecraft->playerStartedTutorial(iPad);
}

bool FullTutorialMode::isTutorial() {
    return !tutorial->m_fullTutorialComplete;
}
