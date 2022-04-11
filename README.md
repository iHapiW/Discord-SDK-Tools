<div id="top"></div>

<div align="center">

  ![Contributors][contributors-shield]
  ![Forks][forks-shield]
  ![Stars][stars-shield]
  ![Issues][issues-shield]
  
</div>

<br />
<div align="center">
  
  [![DST-Circle-128][Logo]](https://github.com/iHapiW/Discord-SDK-Tools)
  <h3 align="center">Discord-SDK-Tools</h3>
  <p align="center">
    An Application to Control Discord Activity (RPC)
  </p>
</div>
<br />

## About The Project

This project interacts with Discord App with Discord Game SDK to control RPC ( Activity ) like a game. <br />
It uses %APPDATA% Env to save activities, and it can launch them whenever we want.

**Abilities** :
* Add Activity
* Remove Activity
* Modify Activity
* Show Listed Activities
* Launch Activity

## Getting Started

This tool is CLI ( Command Line Interface ) and uses color for better UI. <br />
It has issues in systems that doesn't support ANSI Colors, to fix the issue, execute this command in the Command Prompt:

```
REG ADD HKCU\CONSOLE /f /v VirtualTerminalLevel /t REG_DWORD /d 1
```

## Building

For Building the project from source, You need to have ![Nlohmann JSON](https://github.com/nlohmann/json) Library downloaded by vcpkg
and specify `CMAKE_TOOLCHAIN_FILE` while building it.

## Installation

This tool is only available for Windows because the library doesn't support linux OS.
You can use ![Releases](https://github.com/iHapiW/Discord-SDK-Tools/releases) to download binaries.

## Step by Step Usage

Before you add your activity into list. You need to create it in Discord.

Go through ![Discord Developers Portal](https://discord.com/developers/applications/), Then click "New Application" <br />
Then Enter a Name for it ( This will be shown in Title of your Activity )

Copy the "Application ID" here.

Then go to "Art Assets" tab under the "Rich Presence" <br />
![Image-Hint](https://user-images.githubusercontent.com/64321991/162828938-f1807dcf-4a53-4247-a5fb-2da4f836b8ac.png)

Upload 2 pictures:
* Big Picture
* Small Picture

**Now that im writing README Discord has some issues and wont save your pictures at first upload.** <br />
**So you need to upload your pictures first, then refresh multiple times and upload again. untill you see your pictures exist after upload**

Then go ahead open the application and go through "Add Activity" inside "Configure Activities" menu.<br />
Enter the Activity Info, then launch it.

Done, You Launched It 🌟

[contributors-shield]: https://img.shields.io/github/contributors/iHapiW/Discord-SDK-Tools.svg?style=for-the-badge
[contributors-url]: https://github.com/iHapiW/test-readme/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/iHapiW/Discord-SDK-Tools.svg?style=for-the-badge
[forks-url]: https://github.com/iHapiW/test-readme/network/members
[stars-shield]: https://img.shields.io/github/stars/iHapiW/Discord-SDK-Tools.svg?style=for-the-badge
[stars-url]: https://github.com/iHapiW/test-readme/stargazers
[issues-shield]: https://img.shields.io/github/issues/iHapiW/Discord-SDK-Tools.svg?style=for-the-badge
[issues-url]: https://github.com/iHapiW/test-readme/issues
[product-screenshot]: images/screenshot.png
[Logo]: https://user-images.githubusercontent.com/64321991/162815410-57920f86-401b-4b9e-9aaa-749249c7482d.png
