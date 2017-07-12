#!/bin/bash

rm -rf info
mkdir info
rm -rf data
mkdir data
opencv_createsamples -img $1 -bg bg.txt -info info/info.lst -pngoutput info -maxxangle 0.5 -maxyangle 0.5 -maxzangle 0.5 -num $2
echo done1
opencv_createsamples -info info/info.lst -num $2 -w 20 -h 20 -vec positives.vec
echo done2
opencv_traincascade -data data -vec positives.vec -bg bg.txt -numPos $3 -numNeg $4 -numStages $5 -w 20 -h 20


