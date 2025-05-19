#!/bin/bash
for file in $(git diff-tree --no-commit-id --name-only -r $1 $2); do
    echo "Touching file $file..."
    touch $file
done

