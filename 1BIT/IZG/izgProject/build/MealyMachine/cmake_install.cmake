# Install script for directory: /home/filipjanuska/Desktop/IZG/izgProject/MealyMachine

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RELEASE")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib64" TYPE STATIC_LIBRARY FILES "/home/filipjanuska/Desktop/IZG/izgProject/build/MealyMachine/libMealyMachine.a")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/MealyMachine" TYPE FILE FILES "/home/filipjanuska/Desktop/IZG/izgProject/build/MealyMachine/MealyMachine/mealymachine_export.h")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/MealyMachine" TYPE FILE FILES
    "/home/filipjanuska/Desktop/IZG/izgProject/MealyMachine/src/MealyMachine/Fwd.h"
    "/home/filipjanuska/Desktop/IZG/izgProject/MealyMachine/src/MealyMachine/MapTransitionChooser.h"
    "/home/filipjanuska/Desktop/IZG/izgProject/MealyMachine/src/MealyMachine/MealyMachine.h"
    "/home/filipjanuska/Desktop/IZG/izgProject/MealyMachine/src/MealyMachine/TransitionChooser.h"
    "/home/filipjanuska/Desktop/IZG/izgProject/MealyMachine/src/MealyMachine/Exception.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MealyMachine" TYPE FILE FILES
    "/home/filipjanuska/Desktop/IZG/izgProject/build/MealyMachine/MealyMachine/MealyMachineConfig.cmake"
    "/home/filipjanuska/Desktop/IZG/izgProject/build/MealyMachine/MealyMachine/MealyMachineConfigVersion.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MealyMachine/MealyMachineTargets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MealyMachine/MealyMachineTargets.cmake"
         "/home/filipjanuska/Desktop/IZG/izgProject/build/MealyMachine/CMakeFiles/Export/lib/cmake/MealyMachine/MealyMachineTargets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MealyMachine/MealyMachineTargets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/MealyMachine/MealyMachineTargets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MealyMachine" TYPE FILE FILES "/home/filipjanuska/Desktop/IZG/izgProject/build/MealyMachine/CMakeFiles/Export/lib/cmake/MealyMachine/MealyMachineTargets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/MealyMachine" TYPE FILE FILES "/home/filipjanuska/Desktop/IZG/izgProject/build/MealyMachine/CMakeFiles/Export/lib/cmake/MealyMachine/MealyMachineTargets-release.cmake")
  endif()
endif()

