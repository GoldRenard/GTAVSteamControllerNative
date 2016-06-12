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

enum eControl {
    ControlNextCamera = 0,
    ControlLookLeftRight = 1,
    ControlLookUpDown = 2,
    ControlLookUpOnly = 3,
    ControlLookDownOnly = 4,
    ControlLookLeftOnly = 5,
    ControlLookRightOnly = 6,
    ControlCinematicSlowMo = 7,
    ControlFlyUpDown = 8,
    ControlFlyLeftRight = 9,
    ControlScriptedFlyZUp = 10,
    ControlScriptedFlyZDown = 11,
    ControlWeaponWheelUpDown = 12,
    ControlWeaponWheelLeftRight = 13,
    ControlWeaponWheelNext = 14,
    ControlWeaponWheelPrev = 15,
    ControlSelectNextWeapon = 16,
    ControlSelectPrevWeapon = 17,
    ControlSkipCutscene = 18,
    ControlCharacterWheel = 19,
    ControlMultiplayerInfo = 20,
    ControlSprint = 21,
    ControlJump = 22,
    ControlEnter = 23,
    ControlAttack = 24,
    ControlAim = 25,
    ControlLookBehind = 26,
    ControlPhone = 27,
    ControlSpecialAbility = 28,
    ControlSpecialAbilitySecondary = 29,
    ControlMoveLeftRight = 30,
    ControlMoveUpDown = 31,
    ControlMoveUpOnly = 32,
    ControlMoveDownOnly = 33,
    ControlMoveLeftOnly = 34,
    ControlMoveRightOnly = 35,
    ControlDuck = 36,
    ControlSelectWeapon = 37,
    ControlPickup = 38,
    ControlSniperZoom = 39,
    ControlSniperZoomInOnly = 40,
    ControlSniperZoomOutOnly = 41,
    ControlSniperZoomInSecondary = 42,
    ControlSniperZoomOutSecondary = 43,
    ControlCover = 44,
    ControlReload = 45,
    ControlTalk = 46,
    ControlDetonate = 47,
    ControlHUDSpecial = 48,
    ControlArrest = 49,
    ControlAccurateAim = 50,
    ControlContext = 51,
    ControlContextSecondary = 52,
    ControlWeaponSpecial = 53,
    ControlWeaponSpecial2 = 54,
    ControlDive = 55,
    ControlDropWeapon = 56,
    ControlDropAmmo = 57,
    ControlThrowGrenade = 58,
    ControlVehicleMoveLeftRight = 59,
    ControlVehicleMoveUpDown = 60,
    ControlVehicleMoveUpOnly = 61,
    ControlVehicleMoveDownOnly = 62,
    ControlVehicleMoveLeftOnly = 63,
    ControlVehicleMoveRightOnly = 64,
    ControlVehicleSpecial = 65,
    ControlVehicleGunLeftRight = 66,
    ControlVehicleGunUpDown = 67,
    ControlVehicleAim = 68,
    ControlVehicleAttack = 69,
    ControlVehicleAttack2 = 70,
    ControlVehicleAccelerate = 71,
    ControlVehicleBrake = 72,
    ControlVehicleDuck = 73,
    ControlVehicleHeadlight = 74,
    ControlVehicleExit = 75,
    ControlVehicleHandbrake = 76,
    ControlVehicleHotwireLeft = 77,
    ControlVehicleHotwireRight = 78,
    ControlVehicleLookBehind = 79,
    ControlVehicleCinCam = 80,
    ControlVehicleNextRadio = 81,
    ControlVehiclePrevRadio = 82,
    ControlVehicleNextRadioTrack = 83,
    ControlVehiclePrevRadioTrack = 84,
    ControlVehicleRadioWheel = 85,
    ControlVehicleHorn = 86,
    ControlVehicleFlyThrottleUp = 87,
    ControlVehicleFlyThrottleDown = 88,
    ControlVehicleFlyYawLeft = 89,
    ControlVehicleFlyYawRight = 90,
    ControlVehiclePassengerAim = 91,
    ControlVehiclePassengerAttack = 92,
    ControlVehicleSpecialAbilityFranklin = 93,
    ControlVehicleStuntUpDown = 94,
    ControlVehicleCinematicUpDown = 95,
    ControlVehicleCinematicUpOnly = 96,
    ControlVehicleCinematicDownOnly = 97,
    ControlVehicleCinematicLeftRight = 98,
    ControlVehicleSelectNextWeapon = 99,
    ControlVehicleSelectPrevWeapon = 100,
    ControlVehicleRoof = 101,
    ControlVehicleJump = 102,
    ControlVehicleGrapplingHook = 103,
    ControlVehicleShuffle = 104,
    ControlVehicleDropProjectile = 105,
    ControlVehicleMouseControlOverride = 106,
    ControlVehicleFlyRollLeftRight = 107,
    ControlVehicleFlyRollLeftOnly = 108,
    ControlVehicleFlyRollRightOnly = 109,
    ControlVehicleFlyPitchUpDown = 110,
    ControlVehicleFlyPitchUpOnly = 111,
    ControlVehicleFlyPitchDownOnly = 112,
    ControlVehicleFlyUnderCarriage = 113,
    ControlVehicleFlyAttack = 114,
    ControlVehicleFlySelectNextWeapon = 115,
    ControlVehicleFlySelectPrevWeapon = 116,
    ControlVehicleFlySelectTargetLeft = 117,
    ControlVehicleFlySelectTargetRight = 118,
    ControlVehicleFlyVerticalFlightMode = 119,
    ControlVehicleFlyDuck = 120,
    ControlVehicleFlyAttackCamera = 121,
    ControlVehicleFlyMouseControlOverride = 122,
    ControlVehicleSubTurnLeftRight = 123,
    ControlVehicleSubTurnLeftOnly = 124,
    ControlVehicleSubTurnRightOnly = 125,
    ControlVehicleSubPitchUpDown = 126,
    ControlVehicleSubPitchUpOnly = 127,
    ControlVehicleSubPitchDownOnly = 128,
    ControlVehicleSubThrottleUp = 129,
    ControlVehicleSubThrottleDown = 130,
    ControlVehicleSubAscend = 131,
    ControlVehicleSubDescend = 132,
    ControlVehicleSubTurnHardLeft = 133,
    ControlVehicleSubTurnHardRight = 134,
    ControlVehicleSubMouseControlOverride = 135,
    ControlVehiclePushbikePedal = 136,
    ControlVehiclePushbikeSprint = 137,
    ControlVehiclePushbikeFrontBrake = 138,
    ControlVehiclePushbikeRearBrake = 139,
    ControlMeleeAttackLight = 140,
    ControlMeleeAttackHeavy = 141,
    ControlMeleeAttackAlternate = 142,
    ControlMeleeBlock = 143,
    ControlParachuteDeploy = 144,
    ControlParachuteDetach = 145,
    ControlParachuteTurnLeftRight = 146,
    ControlParachuteTurnLeftOnly = 147,
    ControlParachuteTurnRightOnly = 148,
    ControlParachutePitchUpDown = 149,
    ControlParachutePitchUpOnly = 150,
    ControlParachutePitchDownOnly = 151,
    ControlParachuteBrakeLeft = 152,
    ControlParachuteBrakeRight = 153,
    ControlParachuteSmoke = 154,
    ControlParachutePrecisionLanding = 155,
    ControlMap = 156,
    ControlSelectWeaponUnarmed = 157,
    ControlSelectWeaponMelee = 158,
    ControlSelectWeaponHandgun = 159,
    ControlSelectWeaponShotgun = 160,
    ControlSelectWeaponSmg = 161,
    ControlSelectWeaponAutoRifle = 162,
    ControlSelectWeaponSniper = 163,
    ControlSelectWeaponHeavy = 164,
    ControlSelectWeaponSpecial = 165,
    ControlSelectCharacterMichael = 166,
    ControlSelectCharacterFranklin = 167,
    ControlSelectCharacterTrevor = 168,
    ControlSelectCharacterMultiplayer = 169,
    ControlSaveReplayClip = 170,
    ControlSpecialAbilityPC = 171,
    ControlPhoneUp = 172,
    ControlPhoneDown = 173,
    ControlPhoneLeft = 174,
    ControlPhoneRight = 175,
    ControlPhoneSelect = 176,
    ControlPhoneCancel = 177,
    ControlPhoneOption = 178,
    ControlPhoneExtraOption = 179,
    ControlPhoneScrollForward = 180,
    ControlPhoneScrollBackward = 181,
    ControlPhoneCameraFocusLock = 182,
    ControlPhoneCameraGrid = 183,
    ControlPhoneCameraSelfie = 184,
    ControlPhoneCameraDOF = 185,
    ControlPhoneCameraExpression = 186,
    ControlFrontendDown = 187,
    ControlFrontendUp = 188,
    ControlFrontendLeft = 189,
    ControlFrontendRight = 190,
    ControlFrontendRdown = 191,
    ControlFrontendRup = 192,
    ControlFrontendRleft = 193,
    ControlFrontendRright = 194,
    ControlFrontendAxisX = 195,
    ControlFrontendAxisY = 196,
    ControlFrontendRightAxisX = 197,
    ControlFrontendRightAxisY = 198,
    ControlFrontendPause = 199,
    ControlFrontendPauseAlternate = 200,
    ControlFrontendAccept = 201,
    ControlFrontendCancel = 202,
    ControlFrontendX = 203,
    ControlFrontendY = 204,
    ControlFrontendLb = 205,
    ControlFrontendRb = 206,
    ControlFrontendLt = 207,
    ControlFrontendRt = 208,
    ControlFrontendLs = 209,
    ControlFrontendRs = 210,
    ControlFrontendLeaderboard = 211,
    ControlFrontendSocialClub = 212,
    ControlFrontendSocialClubSecondary = 213,
    ControlFrontendDelete = 214,
    ControlFrontendEndscreenAccept = 215,
    ControlFrontendEndscreenExpand = 216,
    ControlFrontendSelect = 217,
    ControlScriptLeftAxisX = 218,
    ControlScriptLeftAxisY = 219,
    ControlScriptRightAxisX = 220,
    ControlScriptRightAxisY = 221,
    ControlScriptRUp = 222,
    ControlScriptRDown = 223,
    ControlScriptRLeft = 224,
    ControlScriptRRight = 225,
    ControlScriptLB = 226,
    ControlScriptRB = 227,
    ControlScriptLT = 228,
    ControlScriptRT = 229,
    ControlScriptLS = 230,
    ControlScriptRS = 231,
    ControlScriptPadUp = 232,
    ControlScriptPadDown = 233,
    ControlScriptPadLeft = 234,
    ControlScriptPadRight = 235,
    ControlScriptSelect = 236,
    ControlCursorAccept = 237,
    ControlCursorCancel = 238,
    ControlCursorX = 239,
    ControlCursorY = 240,
    ControlCursorScrollUp = 241,
    ControlCursorScrollDown = 242,
    ControlEnterCheatCode = 243,
    ControlInteractionMenu = 244,
    ControlMpTextChatAll = 245,
    ControlMpTextChatTeam = 246,
    ControlMpTextChatFriends = 247,
    ControlMpTextChatCrew = 248,
    ControlPushToTalk = 249,
    ControlCreatorLS = 250,
    ControlCreatorRS = 251,
    ControlCreatorLT = 252,
    ControlCreatorRT = 253,
    ControlCreatorMenuToggle = 254,
    ControlCreatorAccept = 255,
    ControlCreatorDelete = 256,
    ControlAttack2 = 257,
    ControlRappelJump = 258,
    ControlRappelLongJump = 259,
    ControlRappelSmashWindow = 260,
    ControlPrevWeapon = 261,
    ControlNextWeapon = 262,
    ControlMeleeAttack1 = 263,
    ControlMeleeAttack2 = 264,
    ControlWhistle = 265,
    ControlMoveLeft = 266,
    ControlMoveRight = 267,
    ControlMoveUp = 268,
    ControlMoveDown = 269,
    ControlLookLeft = 270,
    ControlLookRight = 271,
    ControlLookUp = 272,
    ControlLookDown = 273,
    ControlSniperZoomIn = 274,
    ControlSniperZoomOut = 275,
    ControlSniperZoomInAlternate = 276,
    ControlSniperZoomOutAlternate = 277,
    ControlVehicleMoveLeft = 278,
    ControlVehicleMoveRight = 279,
    ControlVehicleMoveUp = 280,
    ControlVehicleMoveDown = 281,
    ControlVehicleGunLeft = 282,
    ControlVehicleGunRight = 283,
    ControlVehicleGunUp = 284,
    ControlVehicleGunDown = 285,
    ControlVehicleLookLeft = 286,
    ControlVehicleLookRight = 287,
    ControlReplayStartStopRecording = 288,
    ControlReplayStartStopRecordingSecondary = 289,
    ControlScaledLookLeftRight = 290,
    ControlScaledLookUpDown = 291,
    ControlScaledLookUpOnly = 292,
    ControlScaledLookDownOnly = 293,
    ControlScaledLookLeftOnly = 294,
    ControlScaledLookRightOnly = 295,
    ControlReplayMarkerDelete = 296,
    ControlReplayClipDelete = 297,
    ControlReplayPause = 298,
    ControlReplayRewind = 299,
    ControlReplayFfwd = 300,
    ControlReplayNewmarker = 301,
    ControlReplayRecord = 302,
    ControlReplayScreenshot = 303,
    ControlReplayHidehud = 304,
    ControlReplayStartpoint = 305,
    ControlReplayEndpoint = 306,
    ControlReplayAdvance = 307,
    ControlReplayBack = 308,
    ControlReplayTools = 309,
    ControlReplayRestart = 310,
    ControlReplayShowhotkey = 311,
    ControlReplayCycleMarkerLeft = 312,
    ControlReplayCycleMarkerRight = 313,
    ControlReplayFOVIncrease = 314,
    ControlReplayFOVDecrease = 315,
    ControlReplayCameraUp = 316,
    ControlReplayCameraDown = 317,
    ControlReplaySave = 318,
    ControlReplayToggletime = 319,
    ControlReplayToggletips = 320,
    ControlReplayPreview = 321,
    ControlReplayToggleTimeline = 322,
    ControlReplayTimelinePickupClip = 323,
    ControlReplayTimelineDuplicateClip = 324,
    ControlReplayTimelinePlaceClip = 325,
    ControlReplayCtrl = 326,
    ControlReplayTimelineSave = 327,
    ControlReplayPreviewAudio = 328,
    ControlVehicleDriveLook = 329,
    ControlVehicleDriveLook2 = 330,
    ControlVehicleFlyAttack2 = 331,
    ControlRadioWheelUpDown = 332,
    ControlRadioWheelLeftRight = 333,
    ControlVehicleSlowMoUpDown = 334,
    ControlVehicleSlowMoUpOnly = 335,
    ControlVehicleSlowMoDownOnly = 336,
    ControlMapPointOfInterest = 337,
};

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