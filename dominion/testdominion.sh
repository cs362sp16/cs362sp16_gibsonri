#!/usr/bin/env bash

if [ -x "$(command -v timeout)" ]; then
    TIMEOUT=timeout
else
    TIMEOUT=gtimeout
fi

make testdominion
for i in `seq 1 20`;
do
echo "Testing with seed of ${i}"
echo -e \"run\nquit\n\" | ${TIMEOUT} 2s ./testdominion ${i} >> /dev/null
done

gcov dominion.c
