![preview](https://raw.githubusercontent.com/GoldRenard/GTAVSteamControllerNative/master/docs/steam_controller.png)

## Steam Controller Native for Grand Theft Auto V

This plugin project is an implementation of native Steam Controller IGAs (In-Game Actions) feature. It allows to switch  control layouts (Action Sets) automatically for specific gameplay modes like Portal 2 does. Following action sets are supported:
- Menu controls
- On foot controls
- In vehicle controls
- In flying vehicle controls

It is implemented as ScriptHookV ASI plugin as well as standalone injectable DLL.

### Requirements

- Grand Theft Auto V v1.0.678.1
- Steam **Beta**
- [ScriptHookV](http://www.dev-c.com/gtav/scripthookv/) or any [DLL Injector](http://lmgtfy.com/?q=DLL+Injector)

### How to use

1. Launch Steam in BigPicture Mode;
2. Create new Steam Controller template for GTA V with four action sets **in sequence**: Menu, Foot, Vehicle, Flying Vehicle. You can leave them empty for now and configure later in game, or you can use prepared configuration like described in next section;
3. Download and unpack latest [Release package](https://github.com/GoldRenard/DMOAdvancedLauncher/releases/latest);
4. Replace the original `steam_api64.dll` located in game folder with packaged one;
5. Now you have two ways depending on the method you want to use the plugin:
   - If you want use it offline with ScriptHookV, just copy `SteamControllerNative.asi` plugin to game folder;
   - If you want to use any online/offline, you must [inject](http://lmgtfy.com/?q=DLL+Injector) `SteamControllerNative.dll` to the game process.
6. Start the game. It should switch action sets automatically, you just have to configure them as you want;

### Prepared controller configuration

Instead of creating a controller configuration from scratch, you can use [prepared one](https://github.com/GoldRenard/GTAVSteamControllerNative/blob/master/controller.vdf). 

Personally, I don't want to publish this plugin-specific configuration to the Steam public list to avoid any confusion for users who don't use this plugin. So here are manual instruction:

1. Create new Steam Controller template for GTA V and save it **locally** with some unique name;
2. Switch to any other controller configuration, close BigPicture or better even Steam;
3. Steam stores all controller configurations in `<Steam>\SteamApps\workshop\content\241100\` folder. Use any notepad with 'Seach in files' feature supported to search your configuration by that unique name;
4. Replace it with [prepared one](https://github.com/GoldRenard/GTAVSteamControllerNative/blob/master/controller.vdf);
5. Start Steam, BigPicture, switch back to your configuration and it should be updated. You're done.

### FAQ

##### Why Steam Beta? / Why I can't create or modify Action Sets?

At the time of writing this manual, the user-made action sets [only available in Steam Beta](http://steamcommunity.com/groups/SteamClientBeta#announcements/detail/907845561657648981). As soon as it will be supported in the normal version, you can switch back to normal Steam. But I prefer to always use beta, I like new features ;)

##### Why we must replace `steam_api64.dll`?

GTA V out the box uses old version of Steamworks SDK with very poor Steam Controller support and there is no Action Sets API at all. `steam_api64.dll` I provided is official library taken from the latest Steamworks SDK 1.36: https://partner.steamgames.com/downloads/

##### Can I use it Online?

Technically, injectable DLL should work Online. But, you know, Rockstar Games doesn't allow to use any mods for GTA:O. Since this plugin is not made for cheating or giving the player some sort of advantage over another, it is still 3rd-party injectable code so they can punish you for using it. I'm not saying they will ban you 100%, but anyway **USE IT ONLINE ON YOUR OWN RISK. I'm responsible for bans. I'm warning you.**

### Credits

- Thanks to Alexander Blade for both the Scripthook and the asi loader.
- Thanks to m0d-s0beit-v (Redux) developers and other authors of its parts: s0biet, NTAuthority/citizenMP, gir489 `[, %DEVELOPER_NAME%]`. Injectable DLL mostly based on their codebase.
