#!/bin/bash

HERE="$(pwd)"

cd "$HERE" &&
    sh Run/Sql2code/build_and_Run_Multiple_Inputs_Log_Full.sh Assets/documents.sql Assets/chats.sql Assets/times.sql Assets/main.2.sql