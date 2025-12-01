#!/bin/bash

read -p "Enter File 1 full path: " -r file1
if [ ! -f $file1 ]; then
	echo "file doesn't exist!"
	exit
fi
	
read -p "Enter File 2 full path: " -r file2
if [ ! -f $file1 ]; then
	echo "file doesn't exist!"
	exit
fi
	
cmp -s $file1 $file2
status=$?

if [ "$status" -eq 1 ]; then
	echo "Files are different!"
else
	echo "Files are the same!"
fi
