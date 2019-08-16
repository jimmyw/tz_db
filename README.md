# Overview
CCTZ is a very good timezone library for C++. Unfortunately, it's not very portable, and it won't for example work on windows unless you install timezone files into a specific directory you link to. Some embedded platforms might not even have this timezone files, and it will obviously not work for them.

This project aims to generate a c file, that embeds all IANA official timezone database into the binary in a portable way. If compressed this will add 200kb to your binary size.

## tz_db

In the tz_db directory, you find a script called update_to_latest_tz_db.sh, this script will download the last zonedb from IANA, and extract all your zonefiles. After this is done, it will use generate.py to generate a c-file with the database embedded.

There are different versions of the generated format, the last version 3, is compressed using libz. If you are missing this library, use version 1 or 2 but your binary size will grow by up to 1 MB. 

## cctz

In this folder you can find an example of how to implement these zone-files into CCTZ, just add this cpp file into cctz, and you are ready to go.


Note. If you find working with timezones hard, you are not alone.
