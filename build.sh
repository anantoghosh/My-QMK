#!/bin/bash

time SKIP_GIT=true make -j$(nproc) CONVERT_TO=promicro_rp2040 --output-sync lily58:vial
