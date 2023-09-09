#!/bin/bash
gcc project.c -Wall -Werror -Wextra -o life.out 
read -r file < "cannons.txt" 
echo "$file" | ./life.out
rm life.out