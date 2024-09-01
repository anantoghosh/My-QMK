#!/bin/bash

time SKIP_GIT=true make -j$(nproc) --output-sync -e TARGET=lily58_right lily58:vial:uf2-split-right
