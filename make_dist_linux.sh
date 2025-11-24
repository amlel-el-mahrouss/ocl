#! /bin/sh

outputDir=dist/lib/

mkdir -p $outputDir

for f in include/ocl/*/*.hpp; do
baseName=`echo $f | cut -d "." -f 1`
echo "RUN:" cp --parents $f.hpp $outputDir$baseName
cp --parents $f.hpp $outputDir$baseName
done

for f in tools/*.py; do
baseName=`echo $f | cut -d "." -f 1`
echo "RUN:" ditto $baseName.py $outputDir$baseName
ditto $baseName.py $outputDir$baseName
done
