#!/bin/bash

# Set the Continuous Integration Build Directory
CI_BUILD_DIR=/home/software/frensie-ci/build/

##---------------------------------------------------------------------------##
## Don't modify anything below this line!
##---------------------------------------------------------------------------##

# Prevent this script from having multiple instances running
for pid in $(pidof -x $0); do
    if [ $pid != $$ ]; then
	exit 0
    fi
done

# Load the user environment variables
source $HOME/.bashrc

cd $CI_BUILD_DIR

ctest -D Continuous -E verification
