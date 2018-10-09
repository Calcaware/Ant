#!/bin/bash

iter=1;

while [ true ]; do
	echo "Generating $iter..."
	./ant 64 $iter true 1 > Img/$iter.pbm
	convert Img/$iter.pbm Out/$iter.png
	iter=$((iter+1))
done
