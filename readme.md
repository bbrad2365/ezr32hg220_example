# EZR32HG220 Example
This example project shows a slc project for the [Silicon Labs EZR32HG220F55](https://www.silabs.com/wireless/proprietary/ezr32hg220-sub-ghz-mcp/device.ezr32hg220f32r55g)

This project was generated using [slc](https://siliconlabs.github.io/slc-specification)

```Bash
slc generate --with="EZR32HG220F32R55" --project-name="example" --project-file="/opt/gecko_sdk/app/common/example/empty/empty.slcp" --export-destination="$PWD" --copy-proj-sources --copy-sdk-sources --new-project --force
```

## Setup

To build the project you can use the [Dockerfile](https://github.com/NabuCasa/silabs-firmware-builder/blob/main/Dockerfile) from the NabuCasa silabs-firmware-builder repo or use your own machine.


### Gecko SDK

```Bash
git clone --depth 1 -b gsdk_4.4 https://github.com/SiliconLabs/gecko_sdk.git /opt/gecko_sdk
```

### SLC CLI

```Bash
curl -O https://www.silabs.com/documents/login/software/slc_cli_linux.zip
unzip -d /opt slc_cli_linux.zip
```

### Simplicity Commander

```Bash
curl -O https://www.silabs.com/documents/login/software/SimplicityCommander-Linux.zip
unzip SimplicityCommander-Linux.zip
tar -C /opt -xjf SimplicityCommander-Linux/Commander_linux_x86_64_*.tar.bz
```

### ARM Toolchain

```Bash
curl -O https://developer.arm.com/-/media/Files/downloads/gnu/12.2.rel1/binrel/arm-gnu-toolchain-12.2.rel1-x86_64-arm-none-eabi.tar.xz
tar -C /opt -xJf arm-gnu-toolchain-12.2.rel1-x86_64-arm-none-eabi.tar.xz
```

### SLC Configuration

```Bash
slc configuration --sdk="/opt/gecko_sdk/"
slc signature trust --sdk "/opt/gecko_sdk/"
slc configuration --gcc-toolchain="/opt/arm-gnu-toolchain-12.2.rel1-x86_64-arm-none-eabi"
```

### SDK Extension Setup

According to the specification, slc should allow for in project extensions as well as projects in the SDK, however this is not currently the case and it fails to trust it. We instead need to link it to within the SDK folder for it to work

```Bash
ln -s $PWD/extension /opt/gecko_sdk/
slc signature trust --extension-path="/opt/gecko_sdk/extension/ezradio"

```

## Build Instructions

Generate Makefile and build

```Bash
slc generate --project-file="example.slcp" --export-destination="$PWD"
make -f example.Makefile $target
```

Where `$target` is one of
- `debug`
- `release`


If you have a system version of `arm-none-eabi-gcc` and it causes issues with the compile, you can run

```Bash
export ARM_GCC_DIR=/opt/arm-gnu-toolchain-12.2.rel1-x86_64-arm-none-eabi
```

which should fix things

## Flash

```Bash
/opt/commander/commander flash build/$target/example.s37 -d ezr32hg220f55
```

## Development

[compiledb](https://github.com/nickdiego/compiledb) can be used to generate a compile_commands.json for the project

```Bash
compiledb make -f example.Makefile $target
```

To launch a GDB server and debug with all the proper symbols you can run

```Bash
JLinkGDBServer -device EZR32HG220F32R55
```

```Bash
/opt/arm-gnu-toolchain-12.2.rel1-x86_64-arm-none-eabi/bin/arm-none-eabi-gdb -s build/debug/example.out -ex "target remote :2331"
```

For a serial console I used JLink RTT, this can be viewed with either

```Bash
/opt/commander/commander rtt connect -d ezr32hg220f55
```

or

```Bash
JLinkRTTViewerExe
```
