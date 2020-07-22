
#pragma once
#include "orx.h"
#include "Entity.cpp"

class Pipe : public Entity
{
    private :
        orxVECTOR speed = orxVECTOR_0;

    public :
        Pipe(void);
        void update(void) override;
        bool outOfScreen(void);
};

