#!/bin/bash

cd "${0%/*}"
cd ..

# Make gcode2img
if [ ! -f ex/gcode2img ]; then
    make clean
    make
    cp gcode2img ex/
fi

# Make jgraph
if [ ! -f ex/jgraph ]; then
    cd contrib
    if [ ! -d jgraph ]; then
        tar xf jgraph_20171128.tar
    fi
    cd jgraph
    make clean
    make jgraph
    cp jgraph ../../ex/
    cd ../../
fi

# Run examples
cd ex/
if [ ! -d examples ]; then
    mkdir examples
    tar xf examples.tar.gz -C examples
fi

echo "Running examples (this might take a minute)..."

./gcode2img examples/AI3M_Stand-in_rotor-BottomToolDRAFT.gcode -l 10 --bead-width 0.2 -s | ./jgraph -P | ps2pdf - | convert -density 300 - -quality 100 out1.png

./gcode2img examples/AI3M_ornl_leaf.gcode -l 10 --bead-width 0.2 -s | ./jgraph -P | ps2pdf - | convert -density 300 - -quality 100 out2.png

./gcode2img examples/AI3M_8in\ hexagon.gcode -l 10 --bead-width 0.2 -s | ./jgraph -P | ps2pdf - | convert -density 300 - -quality 100 out3.png

./gcode2img examples/AI3M_3DBenchy.gcode -l 150 --bead-width 0.2 -s | ./jgraph -P | ps2pdf - | convert -density 300 - -quality 100 out4.png

./gcode2img examples/AI3M_Chair_small.gcode -l 5 --bead-width 0.2 -s | ./jgraph -P | ps2pdf - | convert -density 300 - -quality 100 out5.png
