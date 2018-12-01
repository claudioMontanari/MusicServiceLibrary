cmake_minimum_required(VERSION 3.12)
project(MusicLibraryService)

set(CMAKE_CXX_STANDARD 11)

add_executable(MusicLibraryService main.cpp include/BandMembers.h src/BandMembers.cpp include/MusicClipPtr.h include/ClipList.h include/ClipNode.h include/TestSuite.h src/TestSuite.cpp src/MusicClipPtr.cpp src/ClipList.cpp src/ClipNode.cpp)