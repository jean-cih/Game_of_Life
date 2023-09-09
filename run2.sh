#!/bin/bash
gcc project.c -Wall -Werror -Wextra -o life.out 
read -r file < "cannon.txt" 
echo "$file" | ./life.out