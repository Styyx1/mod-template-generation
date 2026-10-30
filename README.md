# SKSE Plugin Template Generator

## Usage reqs

requires xmake.lua and moddata.toml in the repo
check out [pch.h](src/pch.h) to see the xmake.lua required

moddata.toml example:

```toml
modname = "PlaceHolder"
license = "PlaceHolder"
description = "PlaceHolder"
modversion = "1.0.0"

[Configs]
rex_toml = true
use-fui = true
use-hook-utils = true
```

## Build

clone the repo and just run ``xmake``
