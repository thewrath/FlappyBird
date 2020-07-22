#include "Flappy.h"

Flappy::Flappy(void) : Entity()
{
    {
        orxConfig_PushSection("FlappyObject");
        this->fallRotation = orxConfig_GetFloat("FallRotation");
        this->flyRotation = orxConfig_GetFloat("FlyRotation");
        orxConfig_PopSection();
    }
}

void Flappy::update(void)
{
    if (orxInput_IsActive("Jump"))
    {
        orxObject_ApplyImpulse(this->object, &this->jumpSpeed, orxNULL);
        orxObject_SetRotation(this->object, this->flyRotation);
    }
    else
    {
        orxObject_SetRotation(this->object, this->fallRotation);
    }
}
