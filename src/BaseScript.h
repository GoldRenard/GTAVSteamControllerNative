// ======================================================================
// STEAM CONTROLLER NATIVE FOR GRAND THEFT AUTO V
// Copyright (C) 2016 Ilya Egorov (goldrenard@gmail.com)

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ======================================================================

#pragma once

#include "stdafx.h"

static const WCHAR* ActionNames[] = { L"Menu", L"OnFoot", L"InVehicle", L"InFlyingVehicle" };

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

    ActionSet mCurrentActionSet = ActionSet::Menu;

private:
    void ApplyState(ActionSet dwActionSet);

    void RenderState(float x, float y, ActionSet dwActionSet);

    const WCHAR* GetActionSetName(ActionSet actionSet) {
        return ActionNames[actionSet];
    }
};