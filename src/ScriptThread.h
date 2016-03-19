#pragma once

enum eThreadState {
    ThreadStateIdle,
    ThreadStateRunning,
    ThreadStateKilled,
    ThreadState3,
    ThreadState4,
};

struct scrThreadContext {
    UINT32 ThreadId;
    UINT32 ScriptHash; // + 4 (program id)
    eThreadState State; // + 8
    UINT32 IP; // + 12
    UINT32 FrameSP; //
    UINT32 SP; // + 20, aka + 28
    UINT32 TimerA; // + 24
    UINT32 TimerB; // + 28
    UINT32 TimerC; // + 32, aka + 40
    UINT32 _mUnk1;
    UINT32 _mUnk2;
    UINT32 _f2C;
    UINT32 _f30;
    UINT32 _f34;
    UINT32 _f38;
    UINT32 _f3C;
    UINT32 _f40;
    UINT32 _f44;
    UINT32 _f48;
    UINT32 _f4C;
    UINT32 _f50; // should be +88 aka +80; stack size?

    UINT32 pad1;
    UINT32 pad2;
    UINT32 pad3;

    UINT32 _set1;

    UINT32 pad[68 / 4];
};

static_assert(sizeof(scrThreadContext) == 0xA8, "scrThreadContext size mismatch");

class scrThread {
public:
    //virtual ~scrThread() = 0;
    virtual void deconstructor() = 0;
    virtual eThreadState Reset(UINT32 scriptHash, void* pArgs, UINT32 argCount) = 0;
    virtual eThreadState Run() = 0; // This might have opsToExecute param but i didn't see it in IDA
    virtual eThreadState Tick(UINT32 opsToExecute) = 0;
    virtual void Kill() = 0;

    // There's really no
    eThreadState GetThreadState() {
        return *(eThreadState*) ((DWORD64)this + 0x10);
    }

    scrThreadContext* GetContext() {
        return &m_ctx;
    }

    scrThreadContext m_ctx;					// 0008
    void* m_pStack;							// 00B0
    void* pad;								// 00B8
    void* pad2;								// 00C0
    const char* m_pszExitMessage;			// 00C8
};

class scrNativeCallContext {
protected:
    void* m_pReturn;
    UINT32 m_nArgCount;
    void* m_pArgs;

    UINT32 m_nDataCount;

public:
    template<typename T>
    inline T GetArgument(int idx) {
        intptr_t* arguments = (intptr_t*) m_pArgs;

        return *(T*) &arguments[idx];
    }

    template<typename T>
    inline void SetResult(int idx, T value) {
        intptr_t* returnValues = (intptr_t*) m_pReturn;

        *(T*) &returnValues[idx] = value;
    }

    inline int GetArgumentCount() {
        return m_nArgCount;
    }

    template<typename T>
    inline T GetResult(int idx) {
        intptr_t* returnValues = (intptr_t*) m_pReturn;

        return *(T*) &returnValues[idx];
    }
};

class ScriptThread : public scrThread {
protected:
    char gta_pad[64];
    void* m_pScriptHandler;
    char gta_pad2[40];
    char flag1;
    char m_networkFlag;
    char gta_pad3[22];
public:
    virtual void					DoRun() = 0;

    virtual eThreadState Reset(UINT32 scriptHash, void* pArgs, UINT32 argCount) = 0;
    virtual eThreadState Run() = 0;
    virtual eThreadState Tick(UINT32 opsToExecute) = 0;
    virtual void					Kill();

    inline void* GetScriptHandler() { return m_pScriptHandler; }

    inline void SetScriptHandler(void* scriptHandler) { m_pScriptHandler = scriptHandler; }

    inline void RemoveCleanupFlag() {}
};

typedef struct {
public:
    void(*Deconstructor)(ScriptThread* This);
    eThreadState(*Reset)(ScriptThread* This, UINT32 scriptHash, void* pArgs, UINT32 argCount);
    eThreadState(*Run)(ScriptThread* This);
    eThreadState(*Tick)(ScriptThread* This, UINT32 opsToExecute);
    void(*Kill)(ScriptThread* This);
    void(*unk001)(); // this shouldn't even exist, frankly
} ScriptThread_VTable;

scrThread* GetActiveThread();
void SetActiveThread(scrThread* thread);