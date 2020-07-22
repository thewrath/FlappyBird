/**
 * @file hello.cpp
 * @date 20-Jul-2020
 */
#include <stdio.h>
#include <vector>

#include "orx.h"
#include "Flappy.cpp"
#include "Pipe.cpp"

Flappy* flappy;
std::vector<Pipe> pipes;
orxCLOCK* pipeClock;

// Functions declarations
orxSTATUS orxFASTCALL PhysicsEventHandler(const orxEVENT* _pstEvent);
orxSTATUS orxFASTCALL ObjectDeleteHandler(const orxEVENT* _pstEvent);
Pipe CreatePipeFromConfig(void);
void orxFASTCALL GeneratePipe(const orxCLOCK_INFO*, void*);

/** Update function, it has been registered to be called every tick of the core clock
 */
void orxFASTCALL Update(const orxCLOCK_INFO *_pstClockInfo, void *_pContext)
{
    // Should quit?
    if(orxInput_IsActive("Quit"))
    {
        // Send close event
        orxEvent_SendShort(orxEVENT_TYPE_SYSTEM, orxSYSTEM_EVENT_CLOSE);
    }
}

/** Init function, it is called when all orx's modules have been initialized
 */
orxSTATUS orxFASTCALL Init()
{
    // Create the viewport
    orxViewport_CreateFromConfig("MainViewport");

    // Fetch some object from config file
    orxObject_CreateFromConfig("Scene");
    flappy = new Flappy;
    flappy->setObject(orxObject_CreateFromConfig("FlappyObject"));

    // Add first pipe
    pipes.push_back(CreatePipeFromConfig());

    // register a clock to generate pipe
    pipeClock = orxClock_CreateFromConfig("PipeClock");
    orxClock_Register(pipeClock, GeneratePipe, orxNULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);

    // Handle for physics events
    orxEvent_AddHandler(orxEVENT_TYPE_PHYSICS, PhysicsEventHandler);

    // Handler for pipe deletion
    orxEvent_AddHandler(orxEVENT_TYPE_OBJECT, ObjectDeleteHandler);

    // Register the Update function to the core clock
    orxClock_Register(orxClock_Get(orxCLOCK_KZ_CORE), Update, orxNULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);

    // Done!
    return orxSTATUS_SUCCESS;
}

/** Called when physics module trigger event
*/
orxSTATUS orxFASTCALL PhysicsEventHandler(const orxEVENT* _pstEvent)
{
    // Check event type
    if (_pstEvent->eID == orxPHYSICS_EVENT_CONTACT_ADD) {
        orxOBJECT* pstRecipientObject, * pstSenderObject;

        pstSenderObject = orxOBJECT(_pstEvent->hSender);
        pstRecipientObject = orxOBJECT(_pstEvent->hRecipient);

        orxSTRING senderObjectName = (orxSTRING)orxObject_GetName(pstSenderObject);
        orxSTRING recipientObjectName = (orxSTRING)orxObject_GetName(pstRecipientObject);

        if ((orxString_Compare(senderObjectName, "FlappyObject") == 0) || (orxString_Compare(recipientObjectName, "FlappyObject") == 0)) {
            // Send close event
            orxEvent_SendShort(orxEVENT_TYPE_SYSTEM, orxSYSTEM_EVENT_CLOSE);
        }
    }
    return orxSTATUS_SUCCESS;
}

/** Called when object lifetime expire
*/
orxSTATUS orxFASTCALL ObjectDeleteHandler(const orxEVENT* _pstEvent)
{
    // Check event type
    if (_pstEvent->eID == orxOBJECT_EVENT_DELETE) {
        
    }
    return orxSTATUS_SUCCESS;
}

/** Run function, it should not contain any game logic
 */
orxSTATUS orxFASTCALL Run()
{
    flappy->update();
    for (auto &pipe : pipes)
    {
        pipe.update();
        // This is a work around "how to delete pipe when go out of the screen"
        // instead lifetime object property (from ORX) is used
        if (pipe.outOfScreen()) {
            pipes.pop_back();
        }
    }
    // Return orxSTATUS_FAILURE to instruct orx to quit
    return orxSTATUS_SUCCESS;
}

/** Exit function, it is called before exiting from orx
 */
void orxFASTCALL Exit()
{
    // Let Orx clean all our mess automatically. :)
    // Free flappy
    delete flappy;
}

/** Bootstrap function, it is called before config is initialized, allowing for early resource storage definitions
 */
orxSTATUS orxFASTCALL Bootstrap()
{
    // Add a config storage to find the initial config file
    orxResource_AddStorage(orxCONFIG_KZ_RESOURCE_GROUP, "../data/config", orxFALSE);

    // Return orxSTATUS_FAILURE to prevent orx from loading the default config file
    return orxSTATUS_SUCCESS;
}

Pipe CreatePipeFromConfig(void)
{
    Pipe newPipe;
    newPipe.setObject(orxObject_CreateFromConfig("PipeObject"));
    return newPipe;
}

void orxFASTCALL GeneratePipe(const orxCLOCK_INFO* _pstClockInfo, void* _pstContext)
{
    int space = (rand() % 400) -200; // random between -200 / 200
    Pipe pipe = CreatePipeFromConfig();
    orxVECTOR newPosition = { 0, (float) space, 0 };
    pipe.setPosition(&newPosition);
    pipes.push_back(pipe);
}

/** Main function
 */
int main(int argc, char **argv)
{
    // Set the bootstrap function to provide at least one resource storage before loading any config files
    orxConfig_SetBootstrap(Bootstrap);

    // Execute our game
    orx_Execute(argc, argv, Init, Run, Exit);

    // Done!
    return EXIT_SUCCESS;
}
