#pragma once
#include "BaseScript.h"

#define MAIN_PERSISTENT 0x5700179C

class InjectedScript : public BaseScript {
public:

    void Start(HMODULE hInstance);

    void Shutdown();

    static InjectedScript * GetInstance() {
        if (!m_Instance) {
            m_Instance = new InjectedScript();
        }
        return m_Instance;
    }

private:

    static InjectedScript *m_Instance;

    InjectedScript() {}
};
