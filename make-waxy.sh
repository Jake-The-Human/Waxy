!/bin/bash

if [[ $1 == "run" ]]; then
    ./Builds/LinuxMakefile/build/Waxy
else
    (
        cd ./Builds/LinuxMakefile || exit
        bear -- make -j4 "$1"
    )
    cp ./Builds/LinuxMakefile/compile_commands.json .
fi
