# Create an asciigen image. This Dockerfile will build a Debian image which
# includes a build of the asciigen utility. You can launch the container and
# immediately run asciigen against the included sample image. You can use
# Docker's volume mounting feature to mount a directory on the host PC in the
# container so that you can conveniently convert images located on the host.
# See the project's README for details.

# This Dockerfile uses a multi-stage build. The first stage, builder, builds
# the asciigen binary. The second stage copies the binary from builder and adds
# some sample images for the user/tester to run against.

FROM debian:bookworm-slim AS builder

# Install all the packages needed to build asciigen.
RUN apt-get update        &&\
    apt-get install --yes   \
        build-essential     \
        cmake               \
        zlib1g-dev          \
        libpng-dev          \
        libjpeg-dev         \
        libboost-dev

# Copy the ascii_art_gen source tree.
COPY ./ /ascii_art_gen/

# Build asciigen using the build script included in the project source tree.
WORKDIR /ascii_art_gen/scripts
RUN chmod +x clean.sh &&\
    chmod +x build.sh &&\
    ./clean.sh        &&\
    ./build.sh

FROM debian:bookworm-slim

# Install all packages needed to run asciigen.
RUN apt-get update        &&\
    apt-get install --yes   \
        libpng16-16         \
        libjpeg62

# Copy the asciigen binary from the builder image to this final image.
COPY --from=builder /ascii_art_gen/bin/asciigen /usr/local/bin

# Copy over a sample image.
COPY resources/ /sample_images/

WORKDIR /sample_images
