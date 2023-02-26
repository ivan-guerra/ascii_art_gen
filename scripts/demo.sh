#!/bin/bash

# This script allows you to run the asciigen utility from within a docker
# container. See the project README for more details.

ASCIIGEN_IMAGE="iguerra130154/asciigen"
LOCAL_IMAGE_DIR="$HOME/downloads"

docker run --rm -it \
    -u $(id -u $USER):$(id -g $USER) \
    -v $LOCAL_IMAGE_DIR:/mnt         \
    $ASCIIGEN_IMAGE bash
