#!/bin/bash
#script to extract IP address from mtr (traceroute) program.

mtr --report-cycle 1 --no-dns --split $1 |cut -d" " -f2>$2

