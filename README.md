# Logicon
*Logic gates & circuits simulator*

![logicon_promo](https://user-images.githubusercontent.com/9089004/34963682-17e7177a-fa4a-11e7-9c7a-805193857288.gif)

## Download
[All compiled packages are available in "releases" section.](https://github.com/IIUWR17/lista-11-c5/releases)

## Compile from sources

Requirements:
- Modern C++ compiler supporting C++14,
- Make and CMake,
- (Linux) `xorg-dev`,
- (Windows) [FreeGLUT](https://www.transmissionzero.co.uk/software/freeglut-devel/),
- Development version of **OpenGL** version 1.2+.
More details available in `dependencies/README.md`.

```bash
git clone "https://github.com/IIUWR17/lista-11-c5.git" logicon && cd logicon
# git checkout develop # to build development version (may be unstable)
mkdir build && cd build
cmake -H.. -B. -G "CodeBlocks - Unix Makefiles"
cmake --build . --target logicon --
make install
```

To utilize multiple cores of processor, parameter `-j X` (where X = cores to use) can be added
to improve build speed.

In project's root folder, directory `dist` will be created 
with redistributable package for your platform.

## Free port inputs/outputs reading/saving

![logicon_import_states](https://user-images.githubusercontent.com/9089004/34964042-ccf90a82-fa4b-11e7-887c-3a9a50563428.gif)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FT3sT3ro%2FLogicon.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2FT3sT3ro%2FLogicon?ref=badge_shield)

Application lets user set values on free (not connected) inputs of gates in 
circuit and read values of free outputs to/from file. These files follow format 
(and should be saved with `*.json` extension):

```json
[
    {
        "gblock_id": 1,
        "port": 0,
        "state": 1
    }
]
```

GBlock's ID and port's index can be seen when hovering desired gate and it's port.
State is 1 when ON and 0 when OFF.

## Authors
*(in alphabetical order)*
- [Mateusz Basiak (@inverb)](https://github.com/inverb)
- [Jakub Mendyk (@JMendyk)](https://github.com/JMendyk)
- [Maksymilian Polarczyk (@T3sT3ro)](https://github.com/T3sT3ro)
- [Rafał Tatarczuk (@Rufusmen)](https://github.com/Rufusmen)
- [Łukasz Wróblewski (@kralizekmd)](https://github.com/kralizekmd)


## License
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2FT3sT3ro%2FLogicon.svg?type=large)](https://app.fossa.io/projects/git%2Bgithub.com%2FT3sT3ro%2FLogicon?ref=badge_large)