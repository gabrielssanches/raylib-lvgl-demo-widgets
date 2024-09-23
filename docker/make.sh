#!/bin/bash

docker run \
    -v `pwd`:/game \
    -it \
    gabrielssanches/raylib-linux_x64:5.0 \
    /bin/bash -c "source /usr/local/bin/entrypoint.sh && make all"

docker run \
    -v `pwd`:/game \
    -it \
    gabrielssanches/raylib-wasm:5.0 \
    /bin/bash -c "source /usr/local/bin/entrypoint.sh && make all"
