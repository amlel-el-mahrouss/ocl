#! /bin/sh

outputDir=dist/include/ocl/

mkdir -p $outputDir
mkdir -p $outputDir'fix'
mkdir -p $outputDir'io'
mkdir -p $outputDir'except'
mkdir -p $outputDir'core'
mkdir -p $outputDir'logic'
mkdir -p $outputDir'memory'
mkdir -p $outputDir'net'
mkdir -p $outputDir'simd'
mkdir -p $outputDir'tests'
mkdir -p $outputDir'utility'
mkdir -p 'dist/tools'

outputDirCmd=dist/
outputDirTools=dist/

for f in include/ocl/*/*.hpp; do
baseName=`echo $f | cut -d "." -f 1`
echo "RUN:" cp $f $outputDir$baseName
cp $f $outputDirCmd$baseName
done

for f in tools/*.py; do
baseName=`echo $f | cut -d "." -f 1`
echo "RUN:" cp $baseName'.py' $outputDirTools$baseName
cp $baseName'.py' $outputDirTools$baseName'.py'
done
