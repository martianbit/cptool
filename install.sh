#!/bin/bash
SHARE_DIR_PATH=~/.local/share/cptool
rm -rf $SHARE_DIR_PATH
mkdir -p $SHARE_DIR_PATH
cp -r snippets $SHARE_DIR_PATH
install -m 644 template.cpp $SHARE_DIR_PATH
install -m 755 main.py ~/.local/bin/cptool

