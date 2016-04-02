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

abstract_class ISteamClient017
{
public:
    // Creates a communication pipe to the Steam client
    virtual HSteamPipe CreateSteamPipe() = 0;

    // Releases a previously created communications pipe
    virtual bool BReleaseSteamPipe(HSteamPipe hSteamPipe) = 0;

    // connects to an existing global user, failing if none exists
    // used by the game to coordinate with the steamUI
    virtual HSteamUser ConnectToGlobalUser(HSteamPipe hSteamPipe) = 0;

    // used by game servers, create a steam user that won't be shared with anyone else
    virtual HSteamUser CreateLocalUser(HSteamPipe *phSteamPipe, EAccountType eAccountType) = 0;

    // removes an allocated user
    virtual void ReleaseUser(HSteamPipe hSteamPipe, HSteamUser hUser) = 0;

    // retrieves the ISteamUser interface associated with the handle
    virtual INT_PTR GetISteamUser(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // retrieves the ISteamGameServer interface associated with the handle
    virtual INT_PTR GetISteamGameServer(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // set the local IP and Port to bind to
    // this must be set before CreateLocalUser()
    virtual void SetLocalIPBinding(uint32 unIP, uint16 usPort) = 0;

    // returns the ISteamFriends interface
    virtual INT_PTR GetISteamFriends(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // returns the ISteamUtils interface
    virtual INT_PTR GetISteamUtils(HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // returns the ISteamMatchmaking interface
    virtual INT_PTR GetISteamMatchmaking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // returns the ISteamMatchmakingServers interface
    virtual INT_PTR GetISteamMatchmakingServers(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // returns the a generic interface
    virtual void *GetISteamGenericInterface(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // returns the ISteamUserStats interface
    virtual INT_PTR GetISteamUserStats(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // returns the ISteamGameServerStats interface
    virtual INT_PTR GetISteamGameServerStats(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // returns apps interface
    virtual INT_PTR GetISteamApps(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // networking
    virtual INT_PTR GetISteamNetworking(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // remote storage
    virtual INT_PTR GetISteamRemoteStorage(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // user screenshots
    virtual INT_PTR GetISteamScreenshots(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // this needs to be called every frame to process matchmaking results
    // redundant if you're already calling SteamAPI_RunCallbacks()
    virtual void RunFrame() = 0;

    // returns the number of IPC calls made since the last time this function was called
    // Used for perf debugging so you can understand how many IPC calls your game makes per frame
    // Every IPC call is at minimum a thread context switch if not a process one so you want to rate
    // control how often you do them.
    virtual uint32 GetIPCCallCount() = 0;

    // API warning handling
    // 'int' is the severity; 0 for msg, 1 for warning
    // 'const char *' is the text of the message
    // callbacks will occur directly after the API function is called that generated the warning or message
    virtual void SetWarningMessageHook(SteamAPIWarningMessageHook_t pFunction) = 0;

    // Trigger global shutdown for the DLL
    virtual bool BShutdownIfAllPipesClosed() = 0;

    // Expose HTTP interface
    virtual INT_PTR GetISteamHTTP(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // Exposes the ISteamUnifiedMessages interface
    virtual INT_PTR GetISteamUnifiedMessages(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // Exposes the ISteamController interface
    virtual INT_PTR GetISteamController(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // Exposes the ISteamUGC interface
    virtual INT_PTR GetISteamUGC(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // returns app list interface, only available on specially registered apps
    virtual INT_PTR GetISteamAppList(HSteamUser hSteamUser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // Music Player
    virtual INT_PTR GetISteamMusic(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // Music Player Remote
    virtual INT_PTR GetISteamMusicRemote(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // html page display
    virtual INT_PTR GetISteamHTMLSurface(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // Helper functions for internal Steam usage
    virtual void Set_SteamAPI_CPostAPIResultInProcess(void(*)(SteamAPICall_t callHandle, void *, uint32 unCallbackSize, int iCallbackNum)) = 0;
    virtual void Remove_SteamAPI_CPostAPIResultInProcess(void(*)(SteamAPICall_t callHandle, void *, uint32 unCallbackSize, int iCallbackNum)) = 0;
    virtual void Set_SteamAPI_CCheckCallbackRegisteredInProcess(unsigned int(*)(int iCallbackNum)) = 0;

    // inventory
    virtual INT_PTR GetISteamInventory(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;

    // Video
    virtual INT_PTR GetISteamVideo(HSteamUser hSteamuser, HSteamPipe hSteamPipe, const char *pchVersion) = 0;
};