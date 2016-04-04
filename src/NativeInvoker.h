#pragma once

typedef DWORD Void;
typedef DWORD Any;
typedef DWORD uint;
typedef DWORD Hash;
typedef DWORD ScrHandle;
typedef int Entity;
typedef int Player;
typedef int FireId;
typedef int Ped;
typedef int Vehicle;
typedef int Cam;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int Blip;

#define MAX_PLAYERS 31

class NativeContext {
protected:
    void* m_pReturn;
    UINT32 m_nArgCount;
    void* m_pArgs;

    UINT32 m_nDataCount;

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

typedef void(__cdecl * NativeHandler)(NativeContext* context);

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