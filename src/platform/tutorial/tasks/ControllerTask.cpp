#include "ControllerTask.h"

#include <memory>
#include <unordered_map>
#include <utility>
#include <vector>

#include <4J_Input.h>

#include "client/Minecraft.h"
#include "client/multiplayer/MultiPlayerLocalPlayer.h"
#include "platform/App_enums.h"
#include "platform/tutorial/constraints/InputConstraint.h"
#include "win/Windows64_App.h"

#include "TutorialTask.h"

class Tutorial;

ControllerTask::ControllerTask(
    Tutorial*    tutorial,
    int          descriptionId,
    bool         enablePreCompletion,
    bool         showMinimumTime,
    int          mappings[],
    unsigned int mappingsLength,
    int          iCompletionMaskA[],
    int          iCompletionMaskACount,
    int          iSouthpawMappings[],
    unsigned int uiSouthpawMappingsCount
)
: TutorialTask(
      tutorial,
      descriptionId,
      enablePreCompletion,
      NULL,
      showMinimumTime
  ) {
    for (unsigned int i = 0; i < mappingsLength; ++i) {
        constraints.push_back(new InputConstraint(mappings[i]));
        completedMappings[mappings[i]] = false;
    }
    if (uiSouthpawMappingsCount > 0) m_bHasSouthpaw = true;
    for (unsigned int i = 0; i < uiSouthpawMappingsCount; ++i) {
        southpawCompletedMappings[iSouthpawMappings[i]] = false;
    }

    m_iCompletionMaskA = new int[iCompletionMaskACount];
    for (int i = 0; i < iCompletionMaskACount; i++) {
        m_iCompletionMaskA[i] = iCompletionMaskA[i];
    }
    m_iCompletionMaskACount = iCompletionMaskACount;
    m_uiCompletionMask      = 0;

    // If we don't want to be able to complete it early..then assume we want the
    // constraints active
    // if( !enablePreCompletion )
    //	enableConstraints( true );
}

ControllerTask::~ControllerTask() { delete[] m_iCompletionMaskA; }

bool ControllerTask::isCompleted() {
    if (bIsCompleted) return true;

    bool bAllComplete = true;

    Minecraft* pMinecraft = Minecraft::GetInstance();

    int iCurrent = 0;

    if (m_bHasSouthpaw
        && app.GetGameSettings(
            pMinecraft->player->GetXboxPad(),
            eGameSetting_ControlSouthPaw
        )) {
        for (auto it = southpawCompletedMappings.begin();
             it != southpawCompletedMappings.end();
             ++it) {
            bool current = (*it).second;
            if (!current) {
                // TODO Use a different pad
                if (InputManager
                        .GetValue(pMinecraft->player->GetXboxPad(), (*it).first)
                    > 0) {
                    (*it).second        = true;
                    m_uiCompletionMask |= 1 << iCurrent;
                } else {
                    bAllComplete = false;
                }
            }
            iCurrent++;
        }
    } else {
        for (auto it = completedMappings.begin(); it != completedMappings.end();
             ++it) {
            bool current = (*it).second;
            if (!current) {
                // TODO Use a different pad
                if (InputManager
                        .GetValue(pMinecraft->player->GetXboxPad(), (*it).first)
                    > 0) {
                    (*it).second        = true;
                    m_uiCompletionMask |= 1 << iCurrent;
                } else {
                    bAllComplete = false;
                }
            }
            iCurrent++;
        }
    }

    // If this has a list of completion masks then check if there is a matching
    // one to mark the task as complete
    if (m_iCompletionMaskA && CompletionMaskIsValid()) {
        bIsCompleted = true;
    } else {
        bIsCompleted = bAllComplete;
    }

    return bIsCompleted;
}

bool ControllerTask::CompletionMaskIsValid() {
    for (int i = 0; i < m_iCompletionMaskACount; i++) {
        if (m_uiCompletionMask == m_iCompletionMaskA[i]) return true;
    }

    return false;
}
void ControllerTask::setAsCurrentTask(bool active /*= true*/) {
    TutorialTask::setAsCurrentTask(active);
    enableConstraints(!active);
}
