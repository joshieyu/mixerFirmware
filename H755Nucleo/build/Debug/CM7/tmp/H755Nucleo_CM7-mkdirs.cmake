# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/CM7"
  "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/CM7/build"
  "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/build/Debug/CM7"
  "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/build/Debug/CM7/tmp"
  "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/build/Debug/CM7/src/H755Nucleo_CM7-stamp"
  "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/build/Debug/CM7/src"
  "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/build/Debug/CM7/src/H755Nucleo_CM7-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/build/Debug/CM7/src/H755Nucleo_CM7-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/build/Debug/CM7/src/H755Nucleo_CM7-stamp${cfgdir}") # cfgdir has leading slash
endif()
