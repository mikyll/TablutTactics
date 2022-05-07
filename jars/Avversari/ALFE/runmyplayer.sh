#!/bin/bash
player=$(echo ${1} | tr '[:upper:]' '[:lower:]')
timeout=${2}
ip=${3}
if [[ ${player} == "white" ]]
then
	echo WHITE
	java -jar ALFEwhite.jar  ${timeout}  ${ip}
fi
if [[ ${player} == "black" ]]
then
	echo BLACK
	java -jar ALFEblack.jar  ${timeout}  ${ip}
fi
