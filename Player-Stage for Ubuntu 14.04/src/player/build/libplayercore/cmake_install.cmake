# Install script for directory: /home/jrgunderson/Downloads/player/libplayercore

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
    "/home/jrgunderson/Downloads/player/build/libplayercore/libplayercore.so.3.1.0-svn"
    "/home/jrgunderson/Downloads/player/build/libplayercore/libplayercore.so.3.1"
    "/home/jrgunderson/Downloads/player/build/libplayercore/libplayercore.so"
    )
  FOREACH(file
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplayercore.so.3.1.0-svn"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplayercore.so.3.1"
      "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libplayercore.so"
      )
    IF(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      IF(CMAKE_INSTALL_DO_STRIP)
        EXECUTE_PROCESS(COMMAND "/usr/bin/strip" "${file}")
      ENDIF(CMAKE_INSTALL_DO_STRIP)
    ENDIF()
  ENDFOREACH()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "pkgconfig")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "/home/jrgunderson/Downloads/player/build/libplayercore/playercore.pc")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "pkgconfig")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/player-3.1/libplayercore" TYPE FILE FILES
    "/home/jrgunderson/Downloads/player/libplayercore/configfile.h"
    "/home/jrgunderson/Downloads/player/libplayercore/device.h"
    "/home/jrgunderson/Downloads/player/libplayercore/devicetable.h"
    "/home/jrgunderson/Downloads/player/libplayercore/driver.h"
    "/home/jrgunderson/Downloads/player/libplayercore/drivertable.h"
    "/home/jrgunderson/Downloads/player/libplayercore/filewatcher.h"
    "/home/jrgunderson/Downloads/player/libplayercore/globals.h"
    "/home/jrgunderson/Downloads/player/libplayercore/message.h"
    "/home/jrgunderson/Downloads/player/libplayercore/playercore.h"
    "/home/jrgunderson/Downloads/player/libplayercore/playertime.h"
    "/home/jrgunderson/Downloads/player/libplayercore/plugins.h"
    "/home/jrgunderson/Downloads/player/libplayercore/property.h"
    "/home/jrgunderson/Downloads/player/libplayercore/wallclocktime.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "headers")

