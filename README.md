# gcode2img

`gcode2img` is a simple program that takes a GCode specification and generates an image based on contained geometry. Currently, the program accepts GCode generated from Cura slicer in the Marlin syntax.

### Background
[GCode](https://en.wikipedia.org/wiki/G-code) is a simple language that describes mechanical motions. It is used in a number of areas but of interest 
to us is the use in 3D printers. A slicer is a piece of software that accepts a 3D model, typically in the `.stl` format, and generates GCode that 
describes the motion of the extruder head to print the object.

This software takes the output from these slicers and does a simple visualization of any layer in the object. Currently the method for finding a layer 
and colorization based on region is based on comments left in the code by Cura slicer. It could be extended to support more syntaxes or other slicers 
in the future.

### Building
With a recent C++ compiler and make installed, simply run make:
```
$ make
g++ -g -Wall -MD -std=c++17   -c -o src/arg.o src/arg.cpp
g++ -g -Wall -MD -std=c++17   -c -o src/main.o src/main.cpp
g++ -g -Wall -MD -std=c++17   -c -o src/message.o src/message.cpp
g++ -g -Wall -MD -std=c++17   -c -o src/parse.o src/parse.cpp
g++ -g -Wall -MD -std=c++17   -c -o src/point.o src/point.cpp
g++ -g -Wall -MD -std=c++17   -c -o src/segment.o src/segment.cpp
g++  -g -Wall -MD -std=c++17 -o gcode2img src/arg.o src/main.o src/message.o src/parse.o src/point.o src/segment.o

$ ls
contrib  ex  gcode2img  img  Makefile  README.md  src
```

### Options
The program has built-in help:
```
$ gcode2img --help
Usage: gcode2img [OPTION...] <GCODE_FILE>
Simple program to generate jgraph files from a provided GCode file. Currently accepts GCode in the Marlin syntax generated from Cura. Use '-' to read from stdin.

  -a, --all-layers                      Generate jgraph files for all layers in the GCode
  -d, --output-dir=PATH                 Directory to output files. Defaults to current directory
  -l, --single-layer=LAYER              Generate jgraph files for single layers in the GCode. Can be specified multiple times
  -s, --stdout                          Output jgraph specification to stdout
  -w, --bead-width=WIDTH                Width of the segment visualization in the same units as the GCode
  -?, --help                            Give this help list
      --usage                           Give a short usage message
```

The most typical use case is the following:
```
$ gcode2img -l <layer_number> <gcode_file>
```
This will spit out a `.jgr` file that can then be put through the standard `jgraph` pipeline. By default, the file will be in your current working 
directory and named the layer that you specified. Example usage can be found in `ex/gen_example.sh`.

### Getting GCode Files
The `ex` directory has a set of example GCode files in a tarball. However if you want to run it on different geometry you will need to first slice 
the model yourself. You can do so by running the GUI version of [Cura](https://github.com/Ultimaker/Cura) or the CLI version
[CuraEngine](https://github.com/Ultimaker/CuraEngine).

### Examples
The below examples were generated using Cura and were processed by `gcode2img`. These files can be recreated by running `make ex` or 
`./ex/gen_example.sh` in the root of the repo.

<img src="https://raw.githubusercontent.com/cadkin/gcode2img/master/img/out1.png" width="400">
<img src="https://raw.githubusercontent.com/cadkin/gcode2img/master/img/out2.png" width="400">
<img src="https://raw.githubusercontent.com/cadkin/gcode2img/master/img/out3.png" width="400">
<img src="https://raw.githubusercontent.com/cadkin/gcode2img/master/img/out4.png" width="400">
<img src="https://raw.githubusercontent.com/cadkin/gcode2img/master/img/out5.png" width="400">
