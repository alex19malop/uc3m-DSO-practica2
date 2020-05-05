#!/bin/dash

echo "\e[1;34m****************************************\e[0m"
echo "\e[1;34m****************************************\e[0m"
echo "\e[1;34m****************************************\e[0m"
echo "\e[1;34m****************************************\e[0m"
echo "\e[1;34m****************************************\e[0m"
clear
rm disk.dat
./create_disk 300
make clean
echo 
echo
echo "\e[1;92m******************** MAKE *******************\e[0m\n"
echo
make
echo
echo
echo "\e[1;92m******************** TEST *******************\e[0m\n"
echo
./test
echo
echo
echo "\e[1;92m****************** HEXDUMP *******************\e[0m\n"
echo
hexdump -C disk.dat
