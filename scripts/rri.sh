#!/bin/bash

basedir=$(dirname $0)
rscript=$basedir/rri.R

usage_fct(){
  echo "Usage : $0 [options] <folding-directory>"
  echo "Options:"
  echo "-h --help: Print help"
  exit 2
}

if [ -f "rri.R" ]
then
rscript=rri.R
elif [[ ! -f "$rscript" ]]
then
if [[ -f "${RRI_PATH}/rri.R" ]]
then
rscript=${RRI_PATH}/rri.R
else
echo "The required R script rri.R has not been found. Set the environment variable RRI_PATH to the directory that contains it. Leaving..."
exit 1
fi
fi
#No arguments
if [ $# -eq 0 ]
then
usage_fct
fi
#Test arguments
if [ $1 = "-h" ] || [ $1 = "--help" ]
then
usage_fct
shift
fi
if [ ! -d $1 ]
then
echo "$1 is not a valid directory"
usage_fct
fi
input_dir=$1
for input_file in $input_dir/*.callerdata
do
RRI-bin $input_file
return_code=$?
if [[ $return_code -eq 0 ]]
then
output_dir=${input_file%.callerdata}
R --vanilla --args $output_dir $output_dir < $rscript
else
echo "Nan value detected, skipping this iteration"
fi
done


