# VZOne - Casio VZ-1 Synthesizer Emulation

A virtual instrument plugin that emulates the Casio VZ-1 synthesizer, built with the JUCE framework for cross-platform compatibility.

## Overview

VZOne is a software emulation of the legendary Casio VZ-1 phase distortion synthesizer from the late 1980s. This plugin aims to recreate the unique sound characteristics and synthesis capabilities that made the VZ-1 a distinctive instrument in its era.

## Features

- **Phase Distortion Synthesis**: Emulates the VZ-1's innovative phase distortion synthesis engine
- **Cross-Platform Support**:
  - Windows: VST3 plugin format
  - Linux: LV2 plugin format
- **Built with JUCE**: Leverages the industry-standard JUCE framework for audio plugin development

## Technical Details

The emulation uses wavetable synthesis with multiple waveforms to recreate the VZ-1's characteristic phase distortion sound. The implementation includes:

- 6 distinct waveforms stored in wavetables
- 2048-sample resolution per wavetable
- Custom phase distortion algorithm using saw wave interpolation
- JUCE Synthesiser architecture with custom voice and sound classes

## Building from Source

### Prerequisites

- JUCE framework (version 8 or later)
- C++17 compatible compiler
- CMake or Projucer (JUCE's project management tool)
- Windows: Visual Studio 2019 or later
- Linux: GCC or Clang with LV2 development libraries

### Build Instructions

1. Clone the repository with JUCE submodule:

   ```bash
   git clone --recurse-submodules <repository-url>
   ```

2. Open the project in Projucer or configure with CMake

3. Build the plugin for your target platform:
   - **Windows**: Build the VST3 target
   - **Linux**: Build the LV2 target

## Installation

### Windows (VST3)
Copy the built `.vst3` file to your VST3 plugins directory:
```
C:\Program Files\Common Files\VST3\
```

### Linux (LV2)
Copy the built `.lv2` bundle to your LV2 plugins directory:
```
~/.lv2/
```
or
```
/usr/lib/lv2/
```

## Related Projects

This project draws inspiration from the [Casio VZ Virtual Instrument](https://github.com/matthias-wolff/Casio-VZ-virtual-instrument) project by Matthias Wolff, which provides additional technical information about the VZ-1's synthesis architecture.

## Current Status

This project is in active development. The core synthesis engine is implemented with basic waveform generation and phase distortion capabilities.

## License

This project is licensed under the GNU General Public License v3.0 (GPLv3) - see the [LICENSE](LICENSE) file for details.

This means:
- ✅ You can freely use, modify, and distribute this software
- ✅ You can use it for commercial purposes
- ✅ Source code must be made available when distributing
- ✅ Modified versions must also be licensed under GPLv3
- ✅ Changes must be documented

**Note**: This project uses the JUCE framework, which is dual-licensed under GPLv3 and a commercial license. If you want to distribute a closed-source version of this plugin, you'll need to obtain a JUCE commercial license.

## Acknowledgments

- Casio for the original VZ-1 synthesizer design
- [Matthias Wolff](https://github.com/matthias-wolff) for the VZ virtual instrument research
- JUCE framework developers for the excellent audio plugin framework

## Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

By contributing to this project, you agree that your contributions will be licensed under the GPLv3 license.

## Contact

- **GitHub Issues**: For bug reports and feature requests, please use the [GitHub Issues](https://github.com/borg16/VZOne/issues) page
- **Discussions**: For questions and general discussion, use [GitHub Discussions](https://github.com/borg16/VZOne/discussions)
- **Repository**: [https://github.com/borg16/VZOne](https://github.com/borg16/VZOne)

