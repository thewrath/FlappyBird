
#pragma once
#include "orx.h"
#include "Entity.h"

class Flappy : public Entity
{
    private :
        orxVECTOR jumpSpeed = { 0, -60, 0 };
        float fallRotation = 0;
        float flyRotation = 0;

    public :
        Flappy(void);
        void update(void) override;
};

