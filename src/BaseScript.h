#pragma once

#include "stdafx.h"

static const char* ActionNames[] = { "Menu", "OnFoot", "InVehicle", "InFlyingVehicle" };

class BaseScript {
public:

    // Start the script execution
    virtual void Start(HMODULE hInstance) {};

    // Shutdown the script execution
    virtual void Shutdown() {};

    // Execute the script
    void Execute();

    ~BaseScript() { Shutdown(); }

protected:

    HMODULE hInstance = 0;

    ActionSet m_CurrentActionSet = ActionSet::Menu;

private:
    void ApplyState(ActionSet dwActionSet);

    void RenderState(float x, float y, ActionSet dwActionSet);

    const char* GetActionSetName(ActionSet actionSet) {
        return ActionNames[actionSet];
    }
};
