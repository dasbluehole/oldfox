README.TXT
-----------=========|OldFox|=========-----------
FEATURES:
=========
1- OldFox is a tool written to trace the origin of ip address.
2- This Utility is meant for getting geolocation the IPv4 address 
   some information of lattitude and longitude, city, country.
3- For the purpose of collecting path traversed, "traceroute" or "mtr" is used. 
   The IPv4 address are stripped from the "traceroute" or "mtr" output.
4- The IPv4 address is matched against maxmind IPaddress database ( GeoLiteCity ). 
   from which the Latitude and longitude City and Country information is.
5- To retrive the data sqlite3 is used. 
6- The GeoLiteCity csv file is imported to sqlite3 and used as our database.


SETUP:
======
1- To compile it should be downloaded and put in a directory
2- Sqlite3-devel should be pre installed

COMPILING:
==========
1- use gcc -o oldfox oldfox.c -lsqlite3

EXECUTING:
==========
1- Currently we dont have any instalation procedure.
2- it should be executed from command prompt. ( though it can be added to desktop menu )
3- the application needs a file to be mentioend in the commandline.
4- this file contains the ip address of the hops obtained from "traceroute" or "mtr"
5- to get the file there are 2 shell scripts provided.
6- for "traceroute" based tracing execute "sh traceroute.sh <destination host name/ip address> <outputfilename>"
   the hop IPs willbe stored in the "outputfile" 
7- for "mtr" based tracing, use "sh mtrscript.sh <destination> <outputfile>"
8- then execute "oldfox outputfile", the display is in a tabular form.
9- if you want to trace the path of an e-mail then by hand pick all the ip address from origin to your mailid
10- put it in a file and execute "oldfox <filecontaining ip address>

