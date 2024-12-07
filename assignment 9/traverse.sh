#!/bin/bash

#Function to perform DFS traversal
traverse(){
    local dir="$1"

    #Traverse each item in the directory
    for item in "$dir"/*; do
        #Check if the item is a directory and is accessible
        if [ -d "$item" ] && [ -x "$item" ]; then
            #Recursive call to traverse subdirectory
            traverse "$item"
        fi
    done

    #List the contents of the current directory after traversing subdirectories
    #echo "Listing contents of $dir:"
    ls -A "$dir" 2>/dev/null
}

#Start DFS traversal from the root directory
traverse "/"

