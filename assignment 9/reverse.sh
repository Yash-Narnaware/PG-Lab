#!/bin/bash

#Check if a filename is provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 filename"
    exit 1
fi

filename="$1"

#Using pr to add line numbers, sort to reverse by those numbers, and cut to remove numbers
pr -T -n -m "$filename" | sort -r -k 1,1 | cut -f2-

