cmake_minimum_required(VERSION 2.4)

PROJECT(GAMEKIT)
SET(GAMEKIT 2.74)

IF (NOT CMAKE_BUILD_TYPE)
# SET(CMAKE_BUILD_TYPE "Debug")
 SET(CMAKE_BUILD_TYPE "Release")
ENDIF (NOT CMAKE_BUILD_TYPE) 

 
  
IF(COMMAND cmake_policy)
   cmake_policy(SET CMP0003 NEW)
ENDIF(COMMAND cmake_policy)
   
SUBDIRS(bullet)
SUBDIRS(irrlicht-1.4.2)
SUBDIRS(gamekit)
