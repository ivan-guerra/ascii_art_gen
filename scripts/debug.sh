#!/bin/bash

# This script runs the ASCII Art Generator executable under the GNU debugger.
# debug.sh forwards any script arguments over to the debugger. For example,
# ./debug.sh -a -b B_ARG is the same as running gdb --args asciigen -a -b B_ARG
# Note, you need to run the build.sh script with the -g option in order to have
# the debug symbols available for debugging!

source config.sh

Main()
{
    pushd $AAG_BIN_DIR > /dev/null
        gdb --args asciigen $@
    popd > /dev/null
}

Main $@
