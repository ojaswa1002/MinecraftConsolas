#include "ThrownPotion.h"

#include <cstddef>
#include <vector>

#include "nbt/CompoundTag.h"
#include "util/SharedConstants.h"
#include "util/java/JavaMath.h"
#include "world/effect/MobEffect.h"
#include "world/effect/MobEffectInstance.h"
#include "world/entity/Mob.h"
#include "world/item/Item.h"
#include "world/item/PotionItem.h"
#include "world/level/Level.h"
#include "world/level/tile/LevelEvent.h"
#include "world/phys/AABB.h"
#include "world/phys/HitResult.h"

class Entity;

const double ThrownPotion::SPLASH_RANGE = 4.0;
const double ThrownPotion::SPLASH_RANGE_SQ =
    ThrownPotion::SPLASH_RANGE * ThrownPotion::SPLASH_RANGE;

void ThrownPotion::_init() {
    // 4J Stu - This function call had to be moved here from the Entity ctor to
    // ensure that the derived version of the function is called
    this->defineSynchedData();

    potionValue = 0;
}

ThrownPotion::ThrownPotion(Level* level) : Throwable(level) { _init(); }

ThrownPotion::ThrownPotion(
    Level*               level,
    std::shared_ptr<Mob> mob,
    int                  potionValue
)
: Throwable(level, mob) {
    _init();

    this->potionValue = potionValue;
}

ThrownPotion::ThrownPotion(
    Level* level,
    double x,
    double y,
    double z,
    int    potionValue
)
: Throwable(level, x, y, z) {
    _init();
    this->potionValue = potionValue;
}

float ThrownPotion::getGravity() { return 0.05f; }

float ThrownPotion::getThrowPower() { return 0.5f; }

float ThrownPotion::getThrowUpAngleOffset() { return -20; }

void ThrownPotion::setPotionValue(int potionValue) {
    this->potionValue = potionValue;
}

int ThrownPotion::getPotionValue() { return potionValue; }

void ThrownPotion::onHit(HitResult* res) {
    if (!level->isClientSide) {
        std::vector<MobEffectInstance*>* mobEffects =
            Item::potion->getMobEffects(potionValue);

        if (mobEffects != NULL && !mobEffects->empty()) {
            AABB* aoe = bb->grow(SPLASH_RANGE, SPLASH_RANGE / 2, SPLASH_RANGE);
            std::vector<std::shared_ptr<Entity>>* entitiesOfClass =
                level->getEntitiesOfClass(typeid(Mob), aoe);

            if (entitiesOfClass != NULL && !entitiesOfClass->empty()) {
                // for (Entity e : entitiesOfClass)
                for (auto it = entitiesOfClass->begin();
                     it != entitiesOfClass->end();
                     ++it) {
                    // std::shared_ptr<Entity> e = *it;
                    std::shared_ptr<Mob> e =
                        std::dynamic_pointer_cast<Mob>(*it);
                    double dist = distanceToSqr(e);
                    if (dist < SPLASH_RANGE_SQ) {
                        double scale = 1.0 - (sqrt(dist) / SPLASH_RANGE);
                        if (e == res->entity) {
                            scale = 1;
                        }

                        // for (MobEffectInstance effect : mobEffects)
                        for (auto itMEI = mobEffects->begin();
                             itMEI != mobEffects->end();
                             ++itMEI) {
                            MobEffectInstance* effect = *itMEI;
                            int                id     = effect->getId();
                            if (MobEffect::effects[id]->isInstantenous()) {
                                MobEffect::effects[id]->applyInstantenousEffect(
                                    this->owner,
                                    e,
                                    effect->getAmplifier(),
                                    scale
                                );
                            } else {
                                int duration =
                                    (int)(scale * (double)effect->getDuration()
                                          + .5);
                                if (duration
                                    > SharedConstants::TICKS_PER_SECOND) {
                                    e->addEffect(new MobEffectInstance(
                                        id,
                                        duration,
                                        effect->getAmplifier()
                                    ));
                                }
                            }
                        }
                    }
                }
            }
            delete entitiesOfClass;
        }
        level->levelEvent(
            LevelEvent::PARTICLES_POTION_SPLASH,
            (int)Math::round(x),
            (int)Math::round(y),
            (int)Math::round(z),
            potionValue
        );

        remove();
    }
}

void ThrownPotion::readAdditionalSaveData(CompoundTag* tag) {
    Throwable::readAdditionalSaveData(tag);

    potionValue = tag->getInt(L"potionValue");
}

void ThrownPotion::addAdditonalSaveData(CompoundTag* tag) {
    Throwable::addAdditonalSaveData(tag);

    tag->putInt(L"potionValue", potionValue);
}
