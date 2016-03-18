#pragma once

enum eThreadState {
    ThreadStateIdle,
    ThreadStateRunning,
    ThreadStateKilled,
    ThreadState3,
    ThreadState4,
};

namespace rage {
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
}

class NativeContext :
    public rage::scrNativeCallContext {
private:
    // Configuration
    enum {
        MaxNativeParams = 16,
        ArgSize = 8,
    };

    // Anything temporary that we need
    UINT8 m_TempStack[MaxNativeParams * ArgSize];

public:
    inline NativeContext() {
        m_pArgs = &m_TempStack;
        m_pReturn = &m_TempStack;		// It's okay to point both args and return at
        // the same pointer. The game should handle this.
        m_nArgCount = 0;
        m_nDataCount = 0;
    }

    template <typename T>
    inline void Push(T value) {
        if (sizeof(T) > ArgSize) {
            throw "Argument has an invalid size";
        }
        else if (sizeof(T) < ArgSize) {
            // Ensure we don't have any stray data
            *reinterpret_cast<uintptr_t*>(m_TempStack + ArgSize * m_nArgCount) = 0;
        }

        *reinterpret_cast<T*>(m_TempStack + ArgSize * m_nArgCount) = value;
        m_nArgCount++;
    }

    inline void Reverse() {
        uintptr_t tempValues[MaxNativeParams];
        uintptr_t* args = (uintptr_t*) m_pArgs;

        for (UINT32 i = 0; i < m_nArgCount; i++) {
            int target = m_nArgCount - i - 1;

            tempValues[target] = args[i];
        }

        memcpy(m_TempStack, tempValues, sizeof(m_TempStack));
    }

    template <typename T>
    inline T GetResult() {
        return *reinterpret_cast<T*>(m_TempStack);
    }
};

typedef void(__cdecl * NativeHandler)(rage::scrNativeCallContext* context);

struct NativeRegistration {
    NativeRegistration* nextRegistration;
    NativeHandler handlers[7];
    UINT32 numEntries;
    UINT64 hashes[7];
};

struct pass {
    template<typename ...T> pass(T...) {}
};

class NativeInvoke {
private:
    static void Invoke(NativeContext *cxt, UINT64 hash);

public:

    template<typename R, typename... Args>
    static inline R Invoke(UINT64 Hash, Args... args) {
        NativeContext cxt;

        pass{ ([&] () {
            cxt.Push(args);
        }(), 1)... };

        // reverse the order of the list since the pass method pushes in reverse
        cxt.Reverse();

        Invoke(&cxt, Hash);

        return cxt.GetResult<R>();
    }
};

struct scrVector {
    float x;

private:
    UINT32 pad;

public:
    float y;

private:
    UINT32 pad2;

public:
    float z;

private:
    UINT32 pad3;
};

class GtaThread : public rage::scrThread {
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

//static_assert(sizeof(GtaThread) == 0x158, "GtaThread size mismatch");

typedef struct {
public:
    void(*Deconstructor)(GtaThread* This);
    eThreadState(*Reset)(GtaThread* This, UINT32 scriptHash, void* pArgs, UINT32 argCount);
    eThreadState(*Run)(GtaThread* This);
    eThreadState(*Tick)(GtaThread* This, UINT32 opsToExecute);
    void(*Kill)(GtaThread* This);
    void(*unk001)(); // this shouldn't even exist, frankly
} GtaThread_VTable;

class scriptHandlerMgr {
public:
    virtual ~scriptHandlerMgr() = 0;
    virtual void Padding001() = 0;
    virtual void Padding002() = 0;
    virtual void Padding003() = 0;
    virtual void Padding004() = 0;
    virtual void Padding005() = 0;
    virtual void Padding006() = 0;
    virtual void Padding007() = 0;
    virtual void Padding008() = 0;
    virtual void Padding009() = 0;
    virtual void AttachScript(GtaThread_VTable* thread) = 0;
};