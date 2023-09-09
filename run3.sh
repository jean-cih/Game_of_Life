#!/bin/bash
gcc project.c -Wall -Werror -Wextra -o life.out 
read -r file < "virus.txt" 
echo "$file" | ./life.out