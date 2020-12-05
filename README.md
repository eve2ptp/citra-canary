# Merge log

Scroll down for the original README.md!

Base revision: 6f45b402e751ba7bcaed6ee5c7afbd79f7f4f875

|Pull Request|Commit|Title|Author|Merged?|
|----|----|----|----|----|
|[5620](https://github.com/citra-emu/citra/pull/5620)|[24d79f7ae](https://github.com/citra-emu/citra/pull/5620/files/)|Merge ARM64 Dynarmic|[xperia64](https://github.com/xperia64)|Yes|
|[5609](https://github.com/citra-emu/citra/pull/5609)|[eca33d2de](https://github.com/citra-emu/citra/pull/5609/files/)|Enable fdk decoder for flatpak version|[gal20](https://github.com/gal20)|Yes|
|[5573](https://github.com/citra-emu/citra/pull/5573)|[e31ffecd5](https://github.com/citra-emu/citra/pull/5573/files/)|Port yuzu-emu/yuzu#4722: "cubeb_sink: Use static_cast instead of reinterpret_cast in DataCallback()"|[FearlessTobi](https://github.com/FearlessTobi)|Yes|
|[5572](https://github.com/citra-emu/citra/pull/5572)|[3ad593350](https://github.com/citra-emu/citra/pull/5572/files/)|Port yuzu-emu/yuzu#4721: "codec: Make lookup table static constexpr"|[FearlessTobi](https://github.com/FearlessTobi)|Yes|
|[5571](https://github.com/citra-emu/citra/pull/5571)|[73840c3c7](https://github.com/citra-emu/citra/pull/5571/files/)|Port yuzu-emu/yuzu#4700: "game_list: Eliminate redundant argument copies"|[FearlessTobi](https://github.com/FearlessTobi)|Yes|
|[5528](https://github.com/citra-emu/citra/pull/5528)|[47c7457db](https://github.com/citra-emu/citra/pull/5528/files/)|Port yuzu-emu/yuzu#4565: "microprofile: Don't memset through std::atomic types"|[FearlessTobi](https://github.com/FearlessTobi)|Yes|
|[5509](https://github.com/citra-emu/citra/pull/5509)|[6b92a3373](https://github.com/citra-emu/citra/pull/5509/files/)|Look at direction of analog axis travel instead of instantaneous sample|[xperia64](https://github.com/xperia64)|Yes|
|[5448](https://github.com/citra-emu/citra/pull/5448)|[134bcccc8](https://github.com/citra-emu/citra/pull/5448/files/)|Implement basic rerecording features|[zhaowenlan1779](https://github.com/zhaowenlan1779)|Yes|
|[5411](https://github.com/citra-emu/citra/pull/5411)|[e8c9328b9](https://github.com/citra-emu/citra/pull/5411/files/)|dumping/ffmpeg_backend: Various fixes|[zhaowenlan1779](https://github.com/zhaowenlan1779)|Yes|
|[5382](https://github.com/citra-emu/citra/pull/5382)|[b34ceb89c](https://github.com/citra-emu/citra/pull/5382/files/)|service/nwm_uds: Various improvements/corrections|[zhaowenlan1779](https://github.com/zhaowenlan1779)|Yes|
|[5331](https://github.com/citra-emu/citra/pull/5331)|[7c6898fdd](https://github.com/citra-emu/citra/pull/5331/files/)|NWM_UDS: implement disconnect_reason and EjectClient|[B3n30](https://github.com/B3n30)|Yes|
|[5278](https://github.com/citra-emu/citra/pull/5278)|[2c0cf5106](https://github.com/citra-emu/citra/pull/5278/files/)|Port yuzu-emu/yuzu#3791: "configuration: Add Restore Default and Clear options to hotkeys"|[FearlessTobi](https://github.com/FearlessTobi)|Yes|


End of merge log. You can find the original README.md below the break.

------

**BEFORE FILING AN ISSUE, READ THE RELEVANT SECTION IN THE [CONTRIBUTING](https://github.com/citra-emu/citra/wiki/Contributing#reporting-issues) FILE!!!**

Citra
==============
[![GitHub Actions Build Status](https://github.com/citra-emu/citra/workflows/citra-ci/badge.svg)](https://github.com/citra-emu/citra/actions)
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

If you want to contribute to the user interface translation, please check out the [citra project on transifex](https://www.transifex.com/citra/citra). We centralize the translation work there, and periodically upstream translations.

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
