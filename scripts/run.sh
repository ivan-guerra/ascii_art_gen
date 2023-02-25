#!/bin/bash

# This script runs the ASCII Art Generator executable. run.sh forwards any
# script arguments over to the executable. For example,
# ./run.sh -a -b B_ARG is the same as running ./asciigen -a -b B_ARG

source config.sh

Main()
{
    pushd $AAG_BIN_DIR > /dev/null
        ./asciigen $@
    popd > /dev/null
}

Main $@
