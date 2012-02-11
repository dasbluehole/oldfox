#!/bin/bash
#script to extract ip address from traceroute command

traceroute $1|awk '!/traceroute/ {print}'|cut -d"(" -f2|cut -d")" -f1|awk '!/'*'/ {print}'>$2

