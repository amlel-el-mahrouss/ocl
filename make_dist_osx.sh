#! /bin/sh

outputDir=dist/

mkdir -p $outputDir

for f in include/ocl/*/*.hpp; do
baseName=`echo $f | cut -d "." -f 1`
echo "RUN:" ditto $baseName.hpp $outputDir$baseName'.hpp'
ditto $baseName.hpp $outputDir$baseName'.hpp'
done

for f in tools/*.py; do
baseName=`echo $f | cut -d "." -f 1`
echo "RUN:" ditto $baseName.py $outputDir$baseName
ditto $baseName.py $outputDir$baseName'.py'
done
