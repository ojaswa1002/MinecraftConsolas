#pragma once

#include "platform/tutorial/TutorialEnum.h"
#include "util/java/Class.h"

#include "TutorialHint.h"

class Tutorial;

class LookAtEntityHint : public TutorialHint {
private:
    eINSTANCEOF m_type;
    int         m_titleId;

public:
    LookAtEntityHint(
        eTutorial_Hint id,
        Tutorial*      tutorial,
        int            descriptionId,
        int            titleId,
        eINSTANCEOF    type
    );
    ~LookAtEntityHint();

    virtual bool onLookAtEntity(eINSTANCEOF type);
};
