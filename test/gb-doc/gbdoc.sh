#!/bin/bash

FILES="./cpu*.txt"
regex="cpu([0|1][[:digit:]]).txt"
for f in $FILES
do
  echo "Processing $f file..."
  if [[ $f =~ $regex ]]
  then
      number="${BASH_REMATCH[1]}"
      ./gameboy-doctor "$f" cpu_instrs "$number" || true
  fi
done
