
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(example1 C CXX)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

find_package(Pelican REQUIRED)
find_package(Qt4 REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})

# Build the emulator binary.
set(name emulator)
add_executable(${name} 
    emulator/emulatorMain.cpp 
    emulator/StreamDataEmulator.cpp
    emulator/ServiceDataEmulator.cpp)
target_link_libraries(${name}
    ${PELICAN_LIBRARY}
    ${PELICAN_TESTUTILS_LIBRARY}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTXML_LIBRARY}
    ${QT_QTNETWORK_LIBRARY})

# Build the server binary.
set(name server)
add_executable(${name} 
    server/serverMain.cpp 
    server/StreamDataChunker.cpp
    server/ServiceDataChunker.cpp)
target_link_libraries(${name}
    ${PELICAN_LIBRARY}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTXML_LIBRARY}
    ${QT_QTNETWORK_LIBRARY})

# Build the pipeline binary.
set(name pipeline)
add_executable(${name} 
    pipeline/pipelineMain.cpp
    pipeline/ServiceData.cpp
    pipeline/ServiceDataAdapter.cpp
    pipeline/StreamData.cpp
    pipeline/StreamDataAdapter.cpp
    pipeline/Pipeline.cpp
)
target_link_libraries(${name}
    ${PELICAN_LIBRARY}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTXML_LIBRARY}
    ${QT_QTNETWORK_LIBRARY})
    
    
