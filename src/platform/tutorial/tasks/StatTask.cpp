#include "StatTask.h"

#include <cstddef>

#include <4J_Profile.h>

#include "client/Minecraft.h"
#include "stats/StatsCounter.h"

#include "TutorialTask.h"

class Tutorial;

StatTask::StatTask(
    Tutorial* tutorial,
    int       descriptionId,
    bool      enablePreCompletion,
    Stat*     stat,
    int       variance /*= 1*/
)
: TutorialTask(tutorial, descriptionId, enablePreCompletion, NULL) {
    this->stat = stat;

    Minecraft* minecraft = Minecraft::GetInstance();
    targetValue =
        minecraft->stats[ProfileManager.GetPrimaryPad()]->getTotalValue(stat)
        + variance;
}

bool StatTask::isCompleted() {
    if (bIsCompleted) return true;

    Minecraft* minecraft = Minecraft::GetInstance();
    bIsCompleted =
        minecraft->stats[ProfileManager.GetPrimaryPad()]->getTotalValue(stat)
        >= (unsigned int)targetValue;
    return bIsCompleted;
}
