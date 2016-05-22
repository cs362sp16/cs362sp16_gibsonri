#!/usr/bin/env bash

make testdominion
for i in `seq 1 20`;
do
echo ${i}
echo -e \"run\nquit\n\" | gtimeout 2s ./testdominion ${i} >> /dev/null
done

gcov dominion.c
