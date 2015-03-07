![pvper](raw.github.com/abidon/pvper/master/docs/pvper-logo.png)
===

> This is ___pvper___ `v0.1.0pre`.  
> You can use *git tags* to quickly switch between releases.


### Overview

__pvper__ is a C++ bare metal programming environment for the Raspberry Pi. It provides several ready-to-use classes which allows the developers to control the Pi's hardware and develop your softwares.

---
### Features

[Patch list](raw.github.com/abidon/pvper/master/docs/patch-list.txt)

This release introduced partial support for the C++ language (static objects only), UART/serial output and usage of GPIO pins.

---
### Requirements

__pvper__ is pretty straight forward to build. All you need is an `arm-none-eabi gcc` (cross-)compiler.  
You can refer to [this guide](http://wiki.osdev.org/GCC_Cross-Compiler) in order to build a cross compiler.

---
### Building

I provided my own build system: `bs`; which is a simple bash script.

`bs` is based on a "task" system, like makefiles do. You can execute multiple task in an unique command. The following tasks are recognized:

* `clean`: remove the files produced by the compilation
* `compile`: build the kernel and it's dependencies
* `install`: copy the kernel and required files on a bootable media (edit the path to the media by editing the `DESTINATION` variable of the `bs` script).

Typical usage of the bs command: `bs compile install clean`

> This build system isn't viable for the future and will be replaced.
> I'm bad at makefiles, but I don't want to loose time learning CMake or Scons (or any alternative) at the moment.
> Contributions are welcome! If you want to provide an alternative to `bs`, take a look at the contributing section below.

---
### Contribute

__pvper__ is a freshly new project. My primary goal is to learn OS development and the ARM architecture. I will do mistakes, so I'm open to suggestions or bug fixes. I will accept better implementations, new features (if I need them), but I will deny pull requests with a lot of code and/or breaking changes at the moment.

---
### License

__pvper__ is available through the MIT License (MIT)

Copyright (c) 2015 Aurélien Bidon &lt;bidon.aurelien [at] gmail.com&gt;

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.