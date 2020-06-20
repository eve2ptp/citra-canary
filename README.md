# Merge log

Scroll down for the original README.md!

Base revision: cb44e4408d5e3fd6ec4f7c39c51aa094389408ba

|Pull Request|Commit|Title|Author|Merged?|
|----|----|----|----|----|
|[6](https://github.com/citra-emu/citra-canary/pull/6)|[d9c3e53d4](https://github.com/citra-emu/citra-canary/pull/6/files/)|Canary Base (MinGW Test)|[liushuyu](https://github.com/liushuyu)|Yes|
|[5382](https://github.com/citra-emu/citra/pull/5382)|[b34ceb89c](https://github.com/citra-emu/citra/pull/5382/files/)|service/nwm_uds: Various improvements/corrections|[zhaowenlan1779](https://github.com/zhaowenlan1779)|Yes|
|[5355](https://github.com/citra-emu/citra/pull/5355)|[fa6f56d9b](https://github.com/citra-emu/citra/pull/5355/files/)|UDS: Only return beacons that have the desired wlan_comm_id|[FearlessTobi](https://github.com/FearlessTobi)|Yes|
|[5345](https://github.com/citra-emu/citra/pull/5345)|[8d1e315aa](https://github.com/citra-emu/citra/pull/5345/files/)|[WIP] NCCHContainer: support for partitions if container is NCSD|[B3n30](https://github.com/B3n30)|Yes|
|[5344](https://github.com/citra-emu/citra/pull/5344)|[01b9302a2](https://github.com/citra-emu/citra/pull/5344/files/)|game_list: Fix folder reordering|[vitor-k](https://github.com/vitor-k)|Yes|
|[5331](https://github.com/citra-emu/citra/pull/5331)|[7c6898fdd](https://github.com/citra-emu/citra/pull/5331/files/)|NWM_UDS: implement disconnect_reason and EjectClient|[B3n30](https://github.com/B3n30)|Yes|
|[5328](https://github.com/citra-emu/citra/pull/5328)|[0af8f1f9c](https://github.com/citra-emu/citra/pull/5328/files/)|APT: implement Set and GetWirelessRebootInfo|[B3n30](https://github.com/B3n30)|Yes|
|[5281](https://github.com/citra-emu/citra/pull/5281)|[35df1f4dd](https://github.com/citra-emu/citra/pull/5281/files/)|citra-qt: Add an "Alternative Speed Limit" with its hotkey|[SutandoTsukai181](https://github.com/SutandoTsukai181)|Yes|
|[5278](https://github.com/citra-emu/citra/pull/5278)|[2c0cf5106](https://github.com/citra-emu/citra/pull/5278/files/)|Port yuzu-emu/yuzu#3791: "configuration: Add Restore Default and Clear options to hotkeys"|[FearlessTobi](https://github.com/FearlessTobi)|Yes|


End of merge log. You can find the original README.md below the break.

------

**BEFORE FILING AN ISSUE, READ THE RELEVANT SECTION IN THE [CONTRIBUTING](https://github.com/citra-emu/citra/wiki/Contributing#reporting-issues) FILE!!!**

Citra
==============
[![Travis CI Build Status](https://travis-ci.com/citra-emu/citra.svg?branch=master)](https://travis-ci.com/citra-emu/citra)
[![AppVeyor CI Build Status](https://ci.appveyor.com/api/projects/status/sdf1o4kh3g1e68m9?svg=true)](https://ci.appveyor.com/project/bunnei/citra)
[![Bitrise CI Build Status](https://app.bitrise.io/app/4ccd8e5720f0d13b/status.svg?token=H32TmbCwxb3OQ-M66KbAyw&branch=master)](https://app.bitrise.io/app/4ccd8e5720f0d13b)
[![Discord](https://img.shields.io/discord/220740965957107713?color=%237289DA&label=Citra&logo=discord&logoColor=white)](https://discord.gg/FAXfZV9)

Citra is an experimental open-source Nintendo 3DS emulator/debugger written in C++. It is written with portability in mind, with builds actively maintained for Windows, Linux and macOS.

Citra emulates a subset of 3DS hardware and therefore is useful for running/debugging homebrew applications, and it is also able to run many commercial games! Some of these do not run at a playable state, but we are working every day to advance the project forward. (Playable here means compatibility of at least "Okay" on our [game compatibility list](https://citra-emu.org/game).)

Citra is licensed under the GPLv2 (or any later version). Refer to the license.txt file included. Please read the [FAQ](https://citra-emu.org/wiki/faq/) before getting started with the project.

Check out our [website](https://citra-emu.org/)!

Need help? Check out our [asking for help](https://citra-emu.org/help/reference/asking/) guide.

For development discussion, please join us on our [Discord server](https://citra-emu.org/discord/) or at #citra-dev on freenode.

### Development

Most of the development happens on GitHub. It's also where [our central repository](https://github.com/citra-emu/citra) is hosted.

If you want to contribute please take a look at the [Contributor's Guide](https://github.com/citra-emu/citra/wiki/Contributing) and [Developer Information](https://github.com/citra-emu/citra/wiki/Developer-Information). You should also contact any of the developers in the forum in order to know about the current state of the emulator because the [TODO list](https://docs.google.com/document/d/1SWIop0uBI9IW8VGg97TAtoT_CHNoP42FzYmvG1F4QDA) isn't maintained anymore.

If you want to contribute to the user interface translation, please checkout [citra project on transifex](https://www.transifex.com/citra/citra). We centralize the translation work there, and periodically upstream translation.

### Building

* __Windows__: [Windows Build](https://github.com/citra-emu/citra/wiki/Building-For-Windows)
* __Linux__: [Linux Build](https://github.com/citra-emu/citra/wiki/Building-For-Linux)
* __macOS__: [macOS Build](https://github.com/citra-emu/citra/wiki/Building-for-macOS)


### Support
We happily accept monetary donations or donated games and hardware. Please see our [donations page](https://citra-emu.org/donate/) for more information on how you can contribute to Citra. Any donations received will go towards things like:
* 3DS consoles for developers to explore the hardware
* 3DS games for testing
* Any equipment required for homebrew
* Infrastructure setup

We also more than gladly accept used 3DS consoles! If you would like to give yours away, don't hesitate to join our [Discord server](https://citra-emu.org/discord/) and talk to bunnei.
