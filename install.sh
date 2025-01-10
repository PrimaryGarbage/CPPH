#!/bin/sh

unameOut="$(uname -s)"
case $unameOut in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    MSYS_NT*)   machine=MSys;;
    *)          machine="UNKNOWN:${unameOut}"
esac

echo "Installing for \"${machine}\""

case $machine in 
    Linux | Max | Cygwin)    sudo cp ./bin/cpph /usr/local/bin/;;
    MinGw | MSys)            sudo cp ./bin/cpph.exe ~/bin/;;
    *)                       echo "Unable to install for this machine. Machine: ${machine}"
esac

echo "Done"
