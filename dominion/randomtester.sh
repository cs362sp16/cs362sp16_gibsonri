#!/usr/bin/env bash
make randomtestadventurer
echo "Testing adventurer card..."
for i in `seq 1 1000`;
do
	./randomtestadventurer $((RANDOM))
done

echo "Testing smithy card..."
make randomtestcard1
for i in `seq 1 1000`;
do
	./randomtestcard1 $((RANDOM))
done

echo "Testing salvager card..."
make randomtestcard2
for i in `seq 1 1000`;
do
	r=$((RANDOM))
	echo ${r}
	./randomtestcard2 ${r}
done
