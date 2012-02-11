#!/bin/bash
# The script i use to format Maxmind database to suit my SQLite application
# Copyright(c) Ashok Shankar Das GNU GPL'd V2
###########################################################################

cat $1 | gawk 'NR > 2,EOF;'| gawk '{gsub(/\"/,"")};1' | gawk '{gsub(/,/,"|")};1' > $2

