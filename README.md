# Merge log

Scroll down for the original README.md!

Base revision: 64694b0f114e4709ccb3e9b62ff061518fe8cca9

|Pull Request|Commit|Title|Author|Merged?|
|----|----|----|----|----|
|[6](https://github.com/citra-emu/citra-canary/pull/6)|[d9c3e53](https://github.com/citra-emu/citra-canary/pull/6/files/)|Canary Base (MinGW Test)|[liushuyu](https://github.com/liushuyu)|Yes|
|[5273](https://github.com/citra-emu/citra/pull/5273)|[03145e3](https://github.com/citra-emu/citra/pull/5273/files/)|[WIP] Update FPS to roughly match the actual 3DS rate|[xperia64](https://github.com/xperia64)|Yes|
|[5272](https://github.com/citra-emu/citra/pull/5272)|[f96970b](https://github.com/citra-emu/citra/pull/5272/files/)|[WIP] Decrease maximum circle pad range|[xperia64](https://github.com/xperia64)|Yes|
|[5266](https://github.com/citra-emu/citra/pull/5266)|[a0e8255](https://github.com/citra-emu/citra/pull/5266/files/)|[WIP] Adjust audio_frame_ticks|[xperia64](https://github.com/xperia64)|Yes|
|[5264](https://github.com/citra-emu/citra/pull/5264)|[9d75206](https://github.com/citra-emu/citra/pull/5264/files/)|gl_shader_gen: Make use of fmt where applicable|[lioncash](https://github.com/lioncash)|Yes|
|[5257](https://github.com/citra-emu/citra/pull/5257)|[ed03c38](https://github.com/citra-emu/citra/pull/5257/files/)|Improve core timing accuracy|[B3n30](https://github.com/B3n30)|Yes|
|[5231](https://github.com/citra-emu/citra/pull/5231)|[6783289](https://github.com/citra-emu/citra/pull/5231/files/)|Fix Address Arbiter serialization|[hamish-milne](https://github.com/hamish-milne)|Yes|
|[5230](https://github.com/citra-emu/citra/pull/5230)|[922a5f7](https://github.com/citra-emu/citra/pull/5230/files/)|Add flag to disable seperable shaders for osx Intel GPUs. |[B3n30](https://github.com/B3n30)|Yes|
|[5207](https://github.com/citra-emu/citra/pull/5207)|[0ec6e54](https://github.com/citra-emu/citra/pull/5207/files/)|Services/APT: Implemented PrepareToStartApplication and StartApplication|[Subv](https://github.com/Subv)|Yes|
|[5163](https://github.com/citra-emu/citra/pull/5163)|[44426bd](https://github.com/citra-emu/citra/pull/5163/files/)|input: allow mapping buttons to touchscreen|[z87](https://github.com/z87)|Yes|


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
