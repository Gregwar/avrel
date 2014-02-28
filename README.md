# avrel / AVR EmuLator

avrel is a pedagigical AVR emulator. It contains a minimalistic base to
implement AVR micro-controller emulation features.

It basically contains the RAM, the ROM and some opcodes.

## Architecture

This repository contains:

* `docs`: the documentation of the instructions set and the CPU
* `firmwares`: some code to build example firmwares
    * `examples`: asm commented examples
    * `bins`: already built firmwares
* `src`: the emulator source code

## Building and using

To build the emulator, simply create a build dir, then run CMake and make:

```
mkdir build
cd build
cmake ../src
make
```

You can then run the `avrel` binary file:

```
./avrel ../firmwares/bins/blink-led.bin 
```

## License

This pedagogical material is under the MIT license
