<div align="center">

![Logo](https://www.dotemu.com/wp-content/uploads/2016/08/r_type_logo.png)

![Static Badge](https://img.shields.io/badge/r--type-game_engine-blue)
![GitHub issues](https://img.shields.io/github/issues/legolas-tek/r-type)
![GitHub Workflow Status (with event)](https://img.shields.io/github/actions/workflow/status/legolas-tek/r-type/github-actions-compile.yml)
![GitHub Workflow Status (with event)](https://img.shields.io/github/actions/workflow/status/legolas-tek/r-type/github-actions-win64-compile.yml?label=windows%20build)
![GitHub top language](https://img.shields.io/github/languages/top/legolas-tek/r-type)

Here you will find an R-Type game, also a complete networking system but mostly, <br/>**a complete open source game engine (ECS)** 🫨
<div/>

<hr/>

<div align="left">

# PELAB's R-Type and Game Engine 🚀

This repository contain an open-source ECS developped in C++, this engine is completly modular and who's waiting for you're contribution.

Also, there are a plenty of work to do concerning the other features of the R-Type:

- The network protocol, as any other protocol let space for improvement
- The R-Type game implementation can always be added some more features
- Any other game could be developped using the ECS game engine

And many other things...


## Needed dependencies ⚠️
<hr/>

This project will use some dependencies of different kinds 

Some are basics and fondamentals dependencies that you should have on you're computer

Others are more specific, that's why our cmake build env will install them for you

You can install them with this command:


For Ubuntu

```bash
sudo apt install git cmake clang

```


For Fedora

```bash
sudo dnf install git cmake clang

```

For ArchLinux

```bash
sudo pacman install git cmake clang
```

For macOs

```bash
brew install git cmake

```

## Build the project 🛠️
<hr/>

After installing the necessary dependencies, in order to build the project, use cmake.

Clone the project

```bash
  git clone https://link-to-project
```

Go to the project directory

```bash
  cd my-project
```

Build using cmake

```bash
cmake -Bbuild \
-DCMAKE_BUILD_TYPE=Release \
-DDEBUG_NETWORK=0  
```

If you specifically wants to build for you're platform, use the right preset.

### For Linux:
```bash
cmake -Bbuild \
--preset linux-amd64
-DCMAKE_BUILD_TYPE=Debug
```

### For Windows:
```bash
cmake -Bbuild \
--preset x64-debug
-DCMAKE_BUILD_TYPE=Debug
```

### For macOs:
```bash
cmake -Bbuild \
--preset macos-arm64
-DCMAKE_BUILD_TYPE=Debug
```


Then, you can  finally build

```bash
cmake --build build
```


## Documentation 📚
<hr/>

Added to the developper documentation, some other documentation is available on our Github Wiki.

- [Loby Network Protocol](https://github.com/legolas-tek/r-type/wiki/Lobby-Network-Protocol)
- [Game Network Protocol](https://github.com/legolas-tek/r-type/wiki/Game-Network-Protocol)
- [System list] (https://github.com/legolas-tek/r-type/wiki/Systems-list)
- [Component List] (https://github.com/legolas-tek/r-type/wiki/Component-list)

And some more available on the wiki...


## Contributing 👨‍🔧
<hr/>

Contributions are always welcome!

See `contributing.md` for ways to get started.

Please adhere to this project's `code of conduct`.


<div/>
