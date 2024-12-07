#!/bin/bash

#Set server details
SERVER="google.com"                     #Server to send traffic to
DURATION=300                            #Total run duration in seconds (5 minutes)

#Start Wireshark's GUI in the background with immediate capture
echo "Starting Wireshark packet capture..."
sudo wireshark -k -i any &
WIRESHARK_PID=$!

#Start httperf to send traffic to google.com
echo "Starting httperf to generate traffic to google.com..."
httperf --server "$SERVER" --num-conns 500 &
HTTPerf_PID=$!

#Wait for the specified duration
sleep $DURATION

#Stop httperf and Wireshark capture after duration
echo "Stopping httperf and Wireshark capture..."
sudo kill $HTTPerf_PID
sudo kill $WIRESHARK_PID

echo "Capture complete!"
