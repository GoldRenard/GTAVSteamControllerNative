#pragma once

class NativeContext :
    public scrNativeCallContext {
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

typedef void(__cdecl * NativeHandler)(scrNativeCallContext* context);

struct NativeRegistration {
    NativeRegistration* nextRegistration;
    NativeHandler handlers[7];
    UINT32 numEntries;
    UINT64 hashes[7];
};

struct NativeArguments {
    template<typename ...T> NativeArguments(T...) {}
};

class NativeInvoke {
private:
    static void Invoke(NativeContext *cxt, UINT64 hash);

public:

    template<typename R, typename... Args>
    static inline R Invoke(UINT64 Hash, Args... args) {
        NativeContext cxt;

        NativeArguments{ ([&] () {
            cxt.Push(args);
        }(), 1)... };

        // reverse the order of the list since the pass method pushes in reverse
        cxt.Reverse();

        Invoke(&cxt, Hash);

        return cxt.GetResult<R>();
    }
};

NativeRegistration** GetRegistrationTable();
NativeHandler GetNativeHandler(UINT64 hash);
pgPtrCollection<ScriptThread>* GetThreadCollection(BlipList*& pBlipList);