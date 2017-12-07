CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)
PROJECT(TestBoost)

FIND_PACKAGE(Boost REQUIRED serialization)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

# use, i.e. don't skip the full RPATH for the build tree
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)

SET(CMAKE_MACOSX_RPATH TRUE)

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY LINK_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

ADD_LIBRARY(derived SHARED polymorphic_derived2.cpp)
ADD_EXECUTABLE(test_boost test_dll_exported.cpp)

TARGET_LINK_LIBRARIES(test_boost derived boost_serialization)

ADD_CUSTOM_TARGET(run
                  COMMAND test_boost
                  DEPENDS test_boost
                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) 
SET(CMAKE_INSTALL_RPATH "${CMAKE_BINARY_DIR}")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
