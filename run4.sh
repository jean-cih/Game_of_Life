#!/bin/bash
gcc project.c -Wall -Werror -Wextra -o life.out 
read -r file < "double cubes.txt" 
echo "$file" | ./life.out