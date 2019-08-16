cmake_minimum_required (VERSION 2.8.11)
project (tz_db)

add_library (tz_db SHARED
  tz_db-3.h
  tz_db-3.c
)
target_link_libraries(tz_db z)

