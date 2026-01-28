#!/usr/bin/env bash
set -e

python3 scripts/preprocess.py
python3 scripts/preprocess_music.py

. /opt/toolchains/dc/kos/environ.sh

make -f Makefile_dc