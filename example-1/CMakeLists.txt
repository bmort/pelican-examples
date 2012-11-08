
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(example1 C CXX)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

find_package(Pelican REQUIRED)
find_package(Qt4 REQUIRED)

add_definitions(-O0)
add_definitions(-g)
add_definitions(-Wall)
add_definitions(-pedantic)
#add_definitions(-std=c99)

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/emulator)
include_directories(${CMAKE_SOURCE_DIR}/pipeline)
include_directories(${CMAKE_SOURCE_DIR}/server)

# Build the emulator binary.
set(name emulator)
add_executable(${name} 
    emulator/main.cpp 
    emulator/StreamDataEmulator.cpp
    emulator/ServiceDataEmulator.cpp)
target_link_libraries(${name}
    ${PELICAN_LIBRARY}
    ${PELICAN_TESTUTILS_LIBRARY}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTXML_LIBRARY}
    ${QT_QTNETWORK_LIBRARY})

set(name serviceEmulator)
add_executable(${name} 
    emulator/mainServiceEmulator.cpp 
    emulator/ServiceDataEmulator.cpp)
target_link_libraries(${name}
    ${PELICAN_LIBRARY}
    ${PELICAN_TESTUTILS_LIBRARY}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTXML_LIBRARY}
    ${QT_QTNETWORK_LIBRARY})

set(name streamEmulator)
add_executable(${name} 
    emulator/mainStreamEmulator.cpp 
    emulator/StreamDataEmulator.cpp)
target_link_libraries(${name}
    ${PELICAN_LIBRARY}
    ${PELICAN_TESTUTILS_LIBRARY}
    ${QT_QTCORE_LIBRARY}
    ${QT_QTXML_LIBRARY}
    ${QT_QTNETWORK_LIBRARY})

# Build the server binary.
set(name server)
add_executable(${name} 
    server/main.cpp 
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
    pipeline/main.cpp
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
    
# Build the direct client pipeline binary.
set(name pipeline-dc)
add_executable(${name} 
    pipeline-dc/main.cpp
    pipeline-dc/DirectDataClient.cpp
    server/StreamDataChunker.cpp
    server/ServiceDataChunker.cpp
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
    
