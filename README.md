# SFML Foundation
A starting point for future SFML projects

## Guide for NixOS
Build & run:
```bash
nix develop
git submodule update --init
make -f Nix.mak clean all
cd Release
./GameName
```
tiled:
```bash
nix develop
tiled res/intro.txm
```
