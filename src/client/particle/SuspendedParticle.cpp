#include "SuspendedParticle.h"

#include "client/Minecraft.h"
#include "platform/App_enums.h"
#include "platform/colours/ColourTable.h"
#include "util/Mth.h"
#include "util/java/JavaMath.h"
#include "util/java/Random.h"
#include "world/level/Level.h"
#include "world/level/material/Material.h"

SuspendedParticle::SuspendedParticle(
    Level* level,
    double x,
    double y,
    double z,
    double xa,
    double ya,
    double za
)
: Particle(level, x, y - 2 / 16.0f, z, xa, ya, za) {
    // 4J-JEV: Set particle colour from colour-table.
    unsigned int col = Minecraft::GetInstance()->getColourTable()->getColor(
        eMinecraftColour_Particle_Suspend
    );
    rCol = ((col >> 16) & 0xFF) / 255.0f, gCol = ((col >> 8) & 0xFF) / 255.0,
    bCol = (col & 0xFF) / 255.0;

    // rCol = 0.4f;
    // gCol = 0.4f;
    // bCol = 0.7f;

    setMiscTex(0);
    this->setSize(0.01f, 0.01f);

    size = size * (random->nextFloat() * 0.6f + 0.2f);

    xd = xa * 0.0f;
    yd = ya * 0.0f;
    zd = za * 0.0f;

    lifetime = (int)(16 / (Math::random() * 0.8 + 0.2));
}

void SuspendedParticle::tick() {
    xo = x;
    yo = y;
    zo = z;

    move(xd, yd, zd);

    if (level->getMaterial(Mth::floor(x), Mth::floor(y), Mth::floor(z))
        != Material::water)
        remove();

    if (lifetime-- <= 0) remove();
}
