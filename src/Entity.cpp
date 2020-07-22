#include "Entity.h"

Entity::Entity(void)
{
    this->object = nullptr;
}

void Entity::setObject(orxOBJECT* object)
{
    this->object = object;
    orxObject_SetUserData(this->object, this);
}

void Entity::setPosition(orxVECTOR* position)
{
    orxVECTOR oldPosition = orxVECTOR_0;
    orxObject_GetPosition(this->object, &oldPosition);
    orxVECTOR newPosition = orxVECTOR_0;
    orxVector_Add(&newPosition, &oldPosition, position);
    orxObject_SetPosition(this->object, &newPosition);
}
