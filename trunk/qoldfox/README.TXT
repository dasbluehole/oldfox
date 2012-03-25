README.TXT
-----------=========|qOldFox|=========-----------
FEATURES:
=========
1- qOldFox is a Graphical interface writtem in QT 4.7 for traceroute for linux.
2- This Utility is meant for graphically ploting the path of hops which provides 
   some information of lattitude and longitude.
3- For the purpose of collecting path traversed, trace route is used. The IPv4 address are stripped
   from the traceroute output.
4- The IPv4 address is matched against maxmind IPaddress database ( GeoLiteCity ). from which the 
   Latitude and longitude are taken and plotted on the world map.
5- To retrive the Latitude and Longitude sqlite3 is used. 
6- The GeoLiteCity csv file is imported to sqlite3 and used as our database.

TO DO:
======
1- Automatic database preparation from Maxmind csv files
1.1- implementing option to use Maxmind API
2- Storing previous atleast 5 traces
3- Displaying City name
4- drawing line (connecting line )
5- generating a Report with the displayed graphics and trace information with time taken
6- Replacing Traceroute and using native QT networking apis
7- calculating total distance in kilometer (from source to destination )
8- code reorganisation.
9- installer

SETUP:
======
1- To compile it should be downloaded and put in a directory
2- Sqlite3-devel should be pre installed
3- QT 4.7 and above should be installed with sql libs

COMPILING:
==========
1- use qmake qoldfox.pro to create the makefile
2- execute make

EXECUTING:
==========
1- Currently we dont have any instalation procedure.
2- it should be executed from command prompt. ( though it can be added to desktop menu )

