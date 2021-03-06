CMAKE_MINIMUM_REQUIRED(VERSION 2.8.8)
PROJECT(TestBoost)

FIND_PACKAGE(Boost REQUIRED serialization)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})

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

TARGET_LINK_LIBRARIES(derived boost_serialization)
TARGET_LINK_LIBRARIES(test_boost derived boost_serialization)

ADD_CUSTOM_TARGET(run
                  COMMAND test_boost
                  DEPENDS test_boost
                  WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

SET( CMAKE_VERBOSE_MAKEFILE on )
