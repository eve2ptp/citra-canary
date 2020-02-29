# Merge log

Scroll down for the original README.md!

Base revision: cd46e62ad4eb18a7f6472caef7d9cc15ada3613a

|Pull Request|Commit|Title|Author|Merged?|
|----|----|----|----|----|
|[6](https://github.com/citra-emu/citra-canary/pull/6)|[d9c3e53](https://github.com/citra-emu/citra-canary/pull/6/files/)|Canary Base (MinGW Test)|[liushuyu](https://github.com/liushuyu)|Yes|
|[5111](https://github.com/citra-emu/citra/pull/5111)|[cfd2ab6](https://github.com/citra-emu/citra/pull/5111/files/)|video_core: use explicit interval type in texture cache|[BreadFish64](https://github.com/BreadFish64)|Yes|
|[5106](https://github.com/citra-emu/citra/pull/5106)|[8fedd5c](https://github.com/citra-emu/citra/pull/5106/files/)|gdbstub: Ensure gdbstub doesn't drop packets crucial to initialization|[GovanifY](https://github.com/GovanifY)|Yes|
|[5103](https://github.com/citra-emu/citra/pull/5103)|[85f65dc](https://github.com/citra-emu/citra/pull/5103/files/)|[WIP] core: Add support for N3DS memory mappings|[FearlessTobi](https://github.com/FearlessTobi)|Yes|
|[5089](https://github.com/citra-emu/citra/pull/5089)|[e4af2ac](https://github.com/citra-emu/citra/pull/5089/files/)|Set render window's focus policy to Qt::StrongFocus|[vitor-k](https://github.com/vitor-k)|Yes|
|[5083](https://github.com/citra-emu/citra/pull/5083)|[a50ba71](https://github.com/citra-emu/citra/pull/5083/files/)|video_core, citra_qt: Video dumping updates|[zhaowenlan1779](https://github.com/zhaowenlan1779)|Yes|
|[5049](https://github.com/citra-emu/citra/pull/5049)|[981bdc0](https://github.com/citra-emu/citra/pull/5049/files/)|HLE Audio: Increase frame position by input buffer sample rate|[jroweboy](https://github.com/jroweboy)|Yes|
|[5025](https://github.com/citra-emu/citra/pull/5025)|[276d56c](https://github.com/citra-emu/citra/pull/5025/files/)|Add CPU Clock Frequency slider|[jroweboy](https://github.com/jroweboy)|Yes|
|[5017](https://github.com/citra-emu/citra/pull/5017)|[3eb6856](https://github.com/citra-emu/citra/pull/5017/files/)|video_core: add texture filtering|[BreadFish64](https://github.com/BreadFish64)|Yes|


End of merge log. You can find the original README.md below the break.

------

**BEFORE FILING AN ISSUE, READ THE RELEVANT SECTION IN THE [CONTRIBUTING](https://github.com/citra-emu/citra/wiki/Contributing#reporting-issues) FILE!!!**

Citra
==============
[![Travis CI Build Status](https://travis-ci.org/citra-emu/citra.svg?branch=master)](https://travis-ci.org/citra-emu/citra)
[![AppVeyor CI Build Status](https://ci.appveyor.com/api/projects/status/sdf1o4kh3g1e68m9?svg=true)](https://ci.appveyor.com/project/bunnei/citra)
[![Bitrise CI Build Status](https://app.bitrise.io/app/4ccd8e5720f0d13b/status.svg?token=H32TmbCwxb3OQ-M66KbAyw&branch=master)](https://app.bitrise.io/app/4ccd8e5720f0d13b)

Citra is an experimental open-source Nintendo 3DS emulator/debugger written in C++. It is written with portability in mind, with builds actively maintained for Windows, Linux and macOS.

Citra emulates a subset of 3DS hardware and therefore is useful for running/debugging homebrew applications, and it is also able to run many commercial games! Some of these do not run at a playable state, but we are working every day to advance the project forward. (Playable here means compatibility of at least "Okay" on our [game compatibility list](https://citra-emu.org/game).)

Citra is licensed under the GPLv2 (or any later version). Refer to the license.txt file included. Please read the [FAQ](https://citra-emu.org/wiki/faq/) before getting started with the project.

Check out our [website](https://citra-emu.org/)!

Need help? Check out our [asking for help](https://citra-emu.org/help/reference/asking/) guide.

For development discussion, please join us at #citra-dev on freenode.

### Development

Most of the development happens on GitHub. It's also where [our central repository](https://github.com/citra-emu/citra) is hosted.

If you want to contribute please take a look at the [Contributor's Guide](https://github.com/citra-emu/citra/wiki/Contributing) and [Developer Information](https://github.com/citra-emu/citra/wiki/Developer-Information). You should as well contact any of the developers in the forum in order to know about the current state of the emulator because the [TODO list](https://docs.google.com/document/d/1SWIop0uBI9IW8VGg97TAtoT_CHNoP42FzYmvG1F4QDA) isn't maintained anymore.

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
* Eventually 3D displays to get proper 3D output working

We also more than gladly accept used 3DS consoles, preferably ones with firmware 4.5 or lower! If you would like to give yours away, don't hesitate to join our IRC channel #citra on [Freenode](http://webchat.freenode.net/?channels=citra) and talk to neobrain or bunnei. Mind you, IRC is slow-paced, so it might be a while until people reply. If you're in a hurry you can just leave contact details in the channel or via private message and we'll get back to you.
