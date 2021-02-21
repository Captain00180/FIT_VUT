#!/bin/sh
echo "---------------- Main ----------------"
./main

echo "--------------- Moduly ---------------"
./modulA
echo "ModulA returns: $?"
echo "ModulB nope"
./modulC
echo "ModulC returns: $?"
echo "ModulD nope"
