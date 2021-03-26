cmake_minimum_required(VERSION 3.16)
project(chattools)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR TRUE)

# boost 1.71.0
find_package(Boost REQUIRED COMPONENTS program_options filesystem)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

# sqlite3 3.31.1
find_package(SQLite3 REQUIRED)
if(SQLITE3_FOUND)
  include_directories(${SQLITE3_INCLUDE_DIRS})
  #target_link_libraries (new ${SQLITE3_LIBRARIES})
  else()
  message("SQLite3 not found")
endif()


file(GLOB source_files
            "*.h"
            "*.cpp"
            #"Classes/*/*.cpp"
            #"Classes/*/*.h"
    )

# Include SOCI Library
# /home/cenicol/CLionProjects/soci/cmake-build-debug
# /home/cenicol/CLionProjects/soci/include
# /home/cenicol/CLionProjects/soci/cmake-build-debug/include
# /home/cenicol/CLionProjects/soci/include/private
# /home/cenicol/CLionProjects/soci/include/private
# /usr/include

#include_directories(
#        /home/cenicol/local/include
#        )
#message("${INCLUDE_DIRECTORIES}")
# ~/local/lib64/
# ~/local/lib64/libsoci_sqlite3.so
message("HOME $ENV{HOME}")
set(SOCI_LIB_DIR $ENV{HOME}/local/lib64/)
set(SOCI_LIBS ${SOCI_LIB_DIR}libsoci_sqlite3.so)
set(SOCI_LIBS ${SOCI_LIB_DIR}libsoci_sqlite3.so)
message("SOCI_LIBS ${SOCI_LIBS}")

# https://stackoverflow.com/questions/28597351/how-do-i-add-a-library-path-in-cmake
add_library(SociCore SHARED IMPORTED) # or STATIC instead of SHARED
set_target_properties(SociCore PROPERTIES
        IMPORTED_LOCATION "${SOCI_LIB_DIR}libsoci_core.so"
        INTERFACE_INCLUDE_DIRECTORIES "/home/cenicol/local/include"
        )
add_library(SociSql3 SHARED IMPORTED) # or STATIC instead of SHARED
set_target_properties(SociSql3 PROPERTIES
  IMPORTED_LOCATION "${SOCI_LIB_DIR}libsoci_sqlite3.so"
  INTERFACE_INCLUDE_DIRECTORIES "/home/cenicol/local/include"
)


add_executable(chattools main.cpp MkUsers.cpp MkUsers.h Utils.h)

target_link_libraries(chattools
        Boost::program_options
        Boost::filesystem
        SQLite::SQLite3
        SociCore
        SociSql3
        #${SOCI_LIBS}
        )