#pragma once

#include "platform/tutorial/TutorialEnum.h"

#include "TutorialHint.h"

class Tutorial;

class TakeItemHint : public TutorialHint {
private:
    int*         m_iItems;
    unsigned int m_iItemsCount;

public:
    TakeItemHint(
        eTutorial_Hint id,
        Tutorial*      tutorial,
        int            items[],
        unsigned int   itemsLength
    );
    ~TakeItemHint();

    virtual bool onTake(std::shared_ptr<ItemInstance> item);
};
