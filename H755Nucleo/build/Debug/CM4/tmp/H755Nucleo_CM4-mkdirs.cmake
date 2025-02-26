# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/CM4"
  "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/CM4/build"
  "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/build/Debug/CM4"
  "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/build/Debug/CM4/tmp"
  "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/build/Debug/CM4/src/H755Nucleo_CM4-stamp"
  "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/build/Debug/CM4/src"
  "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/build/Debug/CM4/src/H755Nucleo_CM4-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/build/Debug/CM4/src/H755Nucleo_CM4-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/joshuayu/Desktop/mixerFirmware/H755Nucleo/build/Debug/CM4/src/H755Nucleo_CM4-stamp${cfgdir}") # cfgdir has leading slash
endif()
