#include "Pipe.h"

Pipe::Pipe(void) : Entity()
{
    {
        orxConfig_PushSection("PipeObject");
        orxConfig_GetVector("Speed", &this->speed);
        orxConfig_PopSection();
    }
}

void Pipe::update(void)
{
    // Move pipe to the left 
    orxVECTOR oldPosition = orxVECTOR_0;
    orxObject_GetPosition(this->object, &oldPosition);
    orxVECTOR newPosition = orxVECTOR_0;
    orxVector_Add(&newPosition, &oldPosition, &this->speed);
    orxObject_SetPosition(this->object, &newPosition);

}

bool Pipe::outOfScreen(void)
{
    orxVECTOR position = orxVECTOR_0;
    orxObject_GetPosition(this->object, &position);
    return false;
}
