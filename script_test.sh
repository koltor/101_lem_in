#!/bin/bash

make

echo "test maps invalides"
./lem-in -d ./maps/unvalid_map/map_non_valid00 >> file
./lem-in -d ./maps/unvalid_map/map_non_valid01 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid02 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid03 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid04 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid05 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid06 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid07 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid08 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid09 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid10 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid11 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid12 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid13 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid14 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid15 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid16 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid17 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid18 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid19 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid20 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid21 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid22 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid23 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid24 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid25 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid26 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid27 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid28 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid29 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid30 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid31 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid32 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid33 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid34 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid35 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid36 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid37 >> file

./lem-in -d ./maps/unvalid_map/map_non_valid38 >> file


cat file | grep "Aucune erreur" | grep segfault
