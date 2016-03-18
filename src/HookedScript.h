#pragma once
#include <vector>
#include "BaseScript.h"
class HookedScript : public BaseScript {
public:

    void Start(HMODULE hInstance);

    void Shutdown();

    static HookedScript * GetInstance() {
        if (!m_Instance) {
            m_Instance = new HookedScript();
        }
        return m_Instance;
    }

private:

    static HookedScript *m_Instance;

    HookedScript() {}
};
