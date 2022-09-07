# Nano: Extending the functionalities of nanos world Scripting API

**Already done**

- Function that returns the **directories** of the specified path
- Function that returns the **files** from the specified path

**Installation**

To install this module on your server, just click here to download it and put the .dll in your server's Modules folder. Then just require it.
```Steam\steamapps\common\nanos-world\Server\Modules```

**Examples**

```lua
-- serverside only module
require('nanofile')

local dirs = Nano.ListDirectories("Packages")
for i, dir in ipairs(dirs) do
    local files = Nano.ListFiles("Packages/" .. dir)
    for i, file in ipairs(files) do
        Package.Log(file)
    end
end

```

**How to build the module**

```
mkdir build
cd build
cmake ..
cmake --build . --config Release
```
