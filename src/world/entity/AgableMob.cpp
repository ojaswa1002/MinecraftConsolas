#include "AgableMob.h"

#include <cstddef>

#include "nbt/CompoundTag.h"
#include "util/java/Class.h"
#include "world/entity/player/Abilities.h"
#include "world/entity/player/Inventory.h"
#include "world/entity/player/Player.h"
#include "world/item/Item.h"
#include "world/item/ItemInstance.h"
#include "world/level/Level.h"

#include "EntityIO.h"
#include "SynchedEntityData.h"

AgableMob::AgableMob(Level* level) : PathfinderMob(level) {
    registeredBBWidth  = -1;
    registeredBBHeight = 0;
}

bool AgableMob::interact(std::shared_ptr<Player> player) {
    std::shared_ptr<ItemInstance> item = player->inventory->getSelected();

    if (item != NULL && item->id == Item::monsterPlacer_Id) {
        if (!level->isClientSide) {
            eINSTANCEOF classToSpawn = EntityIO::getClass(item->getAuxValue());
            if (classToSpawn != eTYPE_NOTSET
                && (classToSpawn & eTYPE_AGABLE_MOB) == eTYPE_AGABLE_MOB
                && classToSpawn == GetType()) // 4J Added GetType() check to
                                              // only spawn same type
            {
                std::shared_ptr<AgableMob> offspring = getBreedOffspring(
                    std::dynamic_pointer_cast<AgableMob>(shared_from_this())
                );
                if (offspring != NULL) {
                    offspring->setAge(-20 * 60 * 20);
                    offspring->moveTo(x, y, z, 0, 0);

                    level->addEntity(offspring);

                    if (!player->abilities.instabuild) {
                        item->count--;

                        if (item->count <= 0) {
                            player->inventory->setItem(
                                player->inventory->selected,
                                nullptr
                            );
                        }
                    }
                }
            }
        }
    }

    return PathfinderMob::interact(player);
}

void AgableMob::defineSynchedData() {
    PathfinderMob::defineSynchedData();
    entityData->define(DATA_AGE_ID, 0);
}

int AgableMob::getAge() { return entityData->getInteger(DATA_AGE_ID); }

void AgableMob::setAge(int age) {
    entityData->set(DATA_AGE_ID, age);
    updateSize(isBaby());
}

void AgableMob::addAdditonalSaveData(CompoundTag* tag) {
    PathfinderMob::addAdditonalSaveData(tag);
    tag->putInt(L"Age", getAge());
}

void AgableMob::readAdditionalSaveData(CompoundTag* tag) {
    PathfinderMob::readAdditionalSaveData(tag);
    setAge(tag->getInt(L"Age"));
}

void AgableMob::aiStep() {
    PathfinderMob::aiStep();

    if (level->isClientSide) {
        updateSize(isBaby());
    } else {
        int age = getAge();
        if (age < 0) {
            age++;
            setAge(age);
        } else if (age > 0) {
            age--;
            setAge(age);
        }
    }
}

bool AgableMob::isBaby() { return getAge() < 0; }

void AgableMob::updateSize(bool isBaby) {
    internalSetSize(isBaby ? .5f : 1.0f);
}

void AgableMob::setSize(float w, float h) {
    bool inited = registeredBBWidth > 0;

    registeredBBWidth  = w;
    registeredBBHeight = h;

    if (!inited) {
        internalSetSize(1.0f);
    }
}

void AgableMob::internalSetSize(float scale) {
    PathfinderMob::setSize(
        registeredBBWidth * scale,
        registeredBBHeight * scale
    );
}
