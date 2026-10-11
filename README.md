<img src="graphics/titlebg0.png" alt="drawing" width="480"/>

# 2048 Advance — Enhanced Fork

An enhanced fork of **2048 Advance**, the Game Boy Advance port of 2048 by
[Basil Termini / Paperdomo101](https://github.com/Paperdomo101/2048-GBA)
([play the original on itch.io](https://basil-termini.itch.io/2048-advance)).

This fork builds on upstream **v1.3.1** and adds new features on top of it. All credit for the
original game, its art, audio and engine goes to its author and contributors.

## Enhancements over the original

Everything this fork adds or changes compared with upstream v1.3.1:

| Area | Change |
|---|---|
| Docs | Controls reference and Windows build instructions |

See the [fork changelog](#fork-changelog) for details per release.

## Controls

| Input | Action |
|---|---|
| D-pad | Slide tiles |
| SELECT | New game |
| START | Save game (resumes where you left off on next boot) |
| A / B / START / SELECT | Continue on title, Game Over and You Win screens |

Reach the 2048 tile to win. The hi-score and saved game are stored in cartridge SRAM.

## Building

Requires [devkitPro](https://devkitpro.org/wiki/Getting_Started) with the `gba-dev` package group
(devkitARM, libtonc, maxmod, grit, mmutil, gbafix). The ROM is written to `build/2048.gba`;
run it in an emulator such as [mGBA](https://mgba.io) or on hardware via a flash cart.

### Windows

Run the CMake build from the devkitPro MSYS2 shell
(`C:\devkitPro\msys2\msys2_shell.bat`, or `C:\devkitPro\msys2\usr\bin\bash.exe -l`):
```sh
cmake -B build .
cmake --build build
```

### nob
```sh
cc -o nob nob.c 
./nob # [options]
      # -r / run:       run in emulator after build  
      # -m / multiboot: build multiboot ROM
      # -d / debug:     define _DEBUG
      # example ./nob -md run   build multiboot, debug, and run 
```

### cmake
```sh
cmake -G Ninja -B build . 
cmake --build build
```

Options: `-DMULTIBOOT=ON` builds a Multiboot ROM (`2048_mb.gba`);
`-DCMAKE_C_FLAGS=-D_DEBUG` enables debug hotkeys (L = force lose, R = force win).
When adding source, graphics or audio files, list them in `CMakeLists.txt`.

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for the code style and how to add scenes and sounds.

## Fork changelog

### Unreleased
* Added controls reference and Windows build instructions to the README

## Original changelog

Releases of the upstream project, [Paperdomo101/2048-GBA](https://github.com/Paperdomo101/2048-GBA).

### v1.3.1
* Fixed a bug allowing input when 2048 has been achieved

### v1.3
+ Added nob build system alongside CMake
+ Separated score logic out from gameplay code into [score.c](source/score.c)
+ Added contributing guidelines (CONTRIBUTING.md)
+ Added huge merge sound effect
* Updated all sound effects (except slide / spawn sounds)
* Sound effects are now declared under SFX_LIST in [global.h](include/global.h) and statically defined automatically using x macros
* Redesigned scene system with SCENE_LIST and x macros - scenes are now implemented in [source/scenes](source/scenes)
* Fixed a graphical bug causing parts of squares to vanish with OAM sorting
* Fixed scale animations freezing while sliding animation is playing
* Fixed initial full scale frame in merge animation
* Scene change now occurs at the start of the next frame instead of at the call-site
* Modified CMake graphics pipeline to work with nob setup
* Upgraded storage format to v2 with hi-score backwards compatibility
* Reverted removal of .grit graphics config files 
* Changed .gitignore to a whitelist
- Reverted L+R+Select hi-score reset and last-save return from Game Over: will move to pause menu

### v1.2 contributed by [@carstene1ns](https://github.com/carstene1ns)
+ Implemented highscore resetting with L+R+Select on title screen.
+ Allow returning to last saved game from Game Over screen.
+ Allow running as Multiboot ROM
* Fixed playfield display on Game Over/Win screen
* Save battery with better vsyncing
* Stop tally animation when out of screen

### v1.1
+ Implemented saving: press start to save and the game will resume where you left off.
* Fixed score tallying
* Fixed error in gameover check
* Fixed while-loop hang save crash
