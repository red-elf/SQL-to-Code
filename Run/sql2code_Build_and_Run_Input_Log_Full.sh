#!/bin/bash

if [ -z "$1" ]; then

    echo "ERROR: SQL file path not provided"
    exit 1
fi

SQL_FILE="$1"

if ! test -e "$SQL_FILE"; then

    echo "ERROR: File not found $SQL_FILE" && pwd
    exit 1
fi

sh Versionable/versionable_build.sh Application .. && Application/Build/sql2code -i "$SQL_FILE" -t cpp -l -o ./Work