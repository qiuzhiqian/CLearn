#!/usr/bin/bash

prjcnt=10
echo $#
if [ $# -eq 1 ];then
    project="lesson"$1
    if [ -d ./${project} ];then
        if [ -f ./${project}/${project}".c" ];then
            gcc ./${project}/${project}".c" -o ./${project}/${project}
        fi
    fi
fi