#!/bin/bash

#Run the training script
echo "Starting training..."
python3 train.py

# Check if training was successful
if [ $? -eq 0 ]; then
    echo "Training completed successfully."
    
    #Run the testing script
    echo "Starting testing..."
    python3 test.py
    
    #Check if testing was successful
    if [ $? -eq 0 ]; then
        echo "Testing completed successfully."
    else
        echo "Testing failed."
    fi
else
    echo "Training failed."
fi
