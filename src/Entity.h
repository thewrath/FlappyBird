
#pragma once
#include "orx.h"

class Entity
{
    protected :
        orxOBJECT* object;

    public :
        Entity(void);
        void setObject(orxOBJECT*);
        void setPosition(orxVECTOR*);
        virtual void update(void) = 0;
};

