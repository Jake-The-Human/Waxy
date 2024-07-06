#!/bin/bash
cd ./Builds/LinuxMakefile
bear -- make -j4 $1
cd -
cp ./Builds/LinuxMakefile/compile_commands.json .
