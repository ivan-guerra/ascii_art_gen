#!/bin/bash

# This script runs the ASCII Art Generator executable. run.sh forwards any
# script arguments over to the executable. For example,
# ./run.sh -a -b B_ARG is the same as running ./asciigen -a -b B_ARG

source config.sh

Main()
{
    pushd $AAG_BIN_DIR > /dev/null
        if [ ! -f "asciigen" ]; then
            echo -e "${LRED}error: executable 'asciigen' not found${NC}"
            echo -e "${LRED}Did you forget to run build.sh?${NC}"
            exit 1
        fi
        ./asciigen $@
    popd > /dev/null
}

Main $@
