#!/bin/bash

if [ -z "$1" ]; then

    echo "ERROR: SQL file paths not provided"
    exit 1
fi

SQL_FILES=("$@")
SQL_FILES_ARG=""

for SQL_FILE in "$@"
do
    if test -e "$SQL_FILE"; then
    
        SQL_FILES_ARG="$SQL_FILES_ARG $SQL_FILE"
    
    else

        echo "ERROR: File not found $SQL_FILE" && pwd
        exit 1
    fi
done

cd "$HERE" &&
    sh Versionable/versionable_build.sh Application .. && Application/Build/sql2code -i $SQL_FILES_ARG -t cpp -l -o ./Work