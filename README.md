# RGB Analysis
This is a library to perform linear analysis on RGB channel streams and
produce graphical illustrations. Usage instructions for Linux and Windows are
given below.

## Windows
The library is distributed as a 32-bit shared library (dll) named
rgb_analysis.dll. To produce graphical illustrations, a 32-bit binary
distribution of gnuplot is provided. In order to run gnuplot correctly, dll and
gnuplot folder must be in the same folder:

folder
├── gnuplot
└── rgb_analysis.dll

Header files containing function interfaces and documentation is provided
in include directory. To read the documentation for which functions are
available, refer to doc/index.html file.

## Linux
The library is distributed as a 32-bit shared library (so) named rgb_analysis.so.
To run it, libgcc must be installed on your system. To produce graphical
representations, gnuplot must be installed on your system.

Header files containing function interfaces and documentation is provided
in include directory. To read the documentation for which functions are
available, refer to doc/index.html file.

## License
This library is distributed under MIT License. See LICENSE.md file to learn
under which conditions you can use this library.
