# voxel-engine

## Building

Follow the vcpkg documentation [here](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started?pivots=shell-powershell).

When creating a `CMakeUserPresets.json` it may be helpful to create a debug configuration that builds in debug mode. This can be accomplished by adding the following to a preset:
```
"cacheVariables": {
    "CMAKE_BUILD_TYPE": "Debug"
}
```

### extra notes
- The binary should be outputted to the source directory of the project (ie. If the project is located at `D:\dev\voxel-engine` the executable is outputted to `D:\dev\voxel-engine\voxel-engine.exe`
