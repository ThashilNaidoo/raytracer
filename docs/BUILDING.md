# Building, running and testing

All commands run from the repository root.

## Requirements

- CMake 3.21 or later
- Ninja
- A C++20 compiler: GCC 13+, Clang 16+ or MSVC 19.36+
- clang-format (for the formatting check)

On Ubuntu or WSL:

```bash
sudo apt install build-essential cmake ninja-build clang clangd clang-format gdb
```

## Presets

The project uses CMake presets. Each preset builds into its own folder under `build/`, so switching between them never forces a full rebuild.

| Preset | Build type | Use it for |
| --- | --- | --- |
| `release` | Release, `-march=native` | Day-to-day work and **all benchmark numbers** |
| `debug` | Debug | Stepping through code in a debugger |
| `asan` | RelWithDebInfo + AddressSanitizer + UBSan | Catching memory errors and undefined behaviour |
| `ci` | Release, portable (no `-march=native`) | GitHub Actions |

## First-time setup

```bash
cmake --preset release
```

Re-run this whenever you edit a `CMakeLists.txt`, including after adding a new `.cpp` file to a source list.

## Everyday loop

```bash
cmake --build --preset release                  # build
./build/release/raytracer output/render.png     # run the renderer
ctest --preset release                          # run all tests
```

All three in one line (each step runs only if the previous one succeeded):

```bash
cmake --build --preset release && ctest --preset release && ./build/release/raytracer output/render.png
```

The renderer writes to `output/`, which is git-ignored. Copy images you want to keep into `docs/images/`.

## Running tests

```bash
ctest --preset release                                  # summary of every test
./build/release/tests/rt_tests                          # full doctest output
./build/release/tests/rt_tests -tc="Vec3*"              # only tests whose names match
./build/release/tests/rt_tests --list-test-cases        # list test names
./build/release/tests/rt_tests --help                   # all doctest options
```

To add a test file, create it in `tests/`, add it to the `add_executable(rt_tests ...)` list in `tests/CMakeLists.txt`, and re-run `cmake --preset release`.

## Sanitizer check

Run this before considering any feature finished.

```bash
cmake --preset asan                                      # first time only
cmake --build --preset asan && ctest --preset asan
./build/asan/raytracer output/asan.png                   # also run the renderer itself
```

## Debug build

```bash
cmake --preset debug
cmake --build --preset debug
gdb ./build/debug/raytracer
```

Never quote timings from a Debug or ASan build. They can be 10–50× slower than Release.

## Formatting

```bash
shopt -s globstar                                                  # once per shell (add to ~/.bashrc)
clang-format --dry-run src/**/*.hpp src/**/*.cpp tests/*.cpp       # report problems
clang-format -i src/**/*.hpp src/**/*.cpp tests/*.cpp              # fix them in place
```

VSCode formats on save with the settings in `.vscode/settings.json`.

## Cleaning

```bash
rm -rf build output                 # remove everything generated
cmake --preset release              # then configure again
```

## Troubleshooting

**`'concepts' file not found` (or another standard header) in VSCode, but the build works.**
clangd uses the highest-numbered GCC folder in `/usr/lib/gcc/x86_64-linux-gnu/`. If that folder has no C++ headers, install them, then restart clangd (Ctrl+Shift+P, "clangd: Restart language server"):

```bash
ls /usr/lib/gcc/x86_64-linux-gnu/          # e.g. shows 13 and 14
sudo apt install libstdc++-14-dev          # match the highest number shown
```

**clangd reports errors on C++20 features, or can't find project headers.**
clangd reads `build/release/compile_commands.json`, which only exists after `cmake --preset release`.

**A new test file isn't being run.**
Check that it's listed in `tests/CMakeLists.txt`, then re-run `cmake --preset release`.

**Thread-scaling numbers look wrong under WSL.**
Check that `nproc` matches your CPU's thread count. If it doesn't, raise `processors=` in `C:\Users\<you>\.wslconfig` and run `wsl --shutdown`.