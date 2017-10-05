# Install script for directory: /home/jrgunderson/Downloads/player/config

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

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "samplecfg")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/player/config" TYPE FILE FILES
    "/home/jrgunderson/Downloads/player/config/afsm.cfg"
    "/home/jrgunderson/Downloads/player/config/afsm.eps"
    "/home/jrgunderson/Downloads/player/config/amigobot.cfg"
    "/home/jrgunderson/Downloads/player/config/amigobot_tcp.cfg"
    "/home/jrgunderson/Downloads/player/config/amtecM5.cfg"
    "/home/jrgunderson/Downloads/player/config/b21r_rflex_lms200.cfg"
    "/home/jrgunderson/Downloads/player/config/cvcam.cfg"
    "/home/jrgunderson/Downloads/player/config/dummy.cfg"
    "/home/jrgunderson/Downloads/player/config/erratic.cfg"
    "/home/jrgunderson/Downloads/player/config/hokuyo_aist.cfg"
    "/home/jrgunderson/Downloads/player/config/iwspy.cfg"
    "/home/jrgunderson/Downloads/player/config/joystick.cfg"
    "/home/jrgunderson/Downloads/player/config/kinect.cfg"
    "/home/jrgunderson/Downloads/player/config/lms400.cfg"
    "/home/jrgunderson/Downloads/player/config/magellan.cfg"
    "/home/jrgunderson/Downloads/player/config/mapfile.cfg"
    "/home/jrgunderson/Downloads/player/config/mbicp.cfg"
    "/home/jrgunderson/Downloads/player/config/nomad.cfg"
    "/home/jrgunderson/Downloads/player/config/obot.cfg"
    "/home/jrgunderson/Downloads/player/config/passthrough.cfg"
    "/home/jrgunderson/Downloads/player/config/phidgetIFK.cfg"
    "/home/jrgunderson/Downloads/player/config/phidgetRFID.cfg"
    "/home/jrgunderson/Downloads/player/config/pioneer.cfg"
    "/home/jrgunderson/Downloads/player/config/pioneer_rs4euze.cfg"
    "/home/jrgunderson/Downloads/player/config/pointcloud3d.cfg"
    "/home/jrgunderson/Downloads/player/config/readlog.cfg"
    "/home/jrgunderson/Downloads/player/config/rfid.cfg"
    "/home/jrgunderson/Downloads/player/config/roomba.cfg"
    "/home/jrgunderson/Downloads/player/config/searchpattern.cfg"
    "/home/jrgunderson/Downloads/player/config/searchpattern_symbols.ps"
    "/home/jrgunderson/Downloads/player/config/segwayrmp.cfg"
    "/home/jrgunderson/Downloads/player/config/service_adv.cfg"
    "/home/jrgunderson/Downloads/player/config/simple.cfg"
    "/home/jrgunderson/Downloads/player/config/sphere.cfg"
    "/home/jrgunderson/Downloads/player/config/umass_ATRVJr.cfg"
    "/home/jrgunderson/Downloads/player/config/umass_ATRVMini.cfg"
    "/home/jrgunderson/Downloads/player/config/umass_reb.cfg"
    "/home/jrgunderson/Downloads/player/config/urglaser.cfg"
    "/home/jrgunderson/Downloads/player/config/vfh.cfg"
    "/home/jrgunderson/Downloads/player/config/wavefront.cfg"
    "/home/jrgunderson/Downloads/player/config/wbr914.cfg"
    "/home/jrgunderson/Downloads/player/config/writelog.cfg"
    "/home/jrgunderson/Downloads/player/config/wsn.cfg"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "samplecfg")

