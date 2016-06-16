#!/bin/sh

make glabel
sudo mv glabel /usr/bin
mkdir /usr/share/glabel
cp -u manual.txt /usr/share/glabel
