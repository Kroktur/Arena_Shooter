#This scripts will add all the cpp and h files under src and include folders, and
#assumes that your Ogre source code is in Dependencies/Ogre and that:
# In Windows you built Ogre into Dependencies/Ogre/build
# In Linux you built Release into Dependencies/Ogre/build/Release
# In Linux you built Debug into Dependencies/Ogre/build/Debug
#
# If your source code is not at "Dependencies/Ogre"; you can use "mklink /D" to create
# a symbolic link to where the source code is located on Windows.
# On Linux, you can use "ln -s"

#set( CMAKE_TOOLCHAIN_FILE CMake/iOS.cmake )

#Set Ogre Variables
set(OGRE_SOURCE $ENV{OGRE_SOURCE})
set(OGRE_BINARIES $ENV{OGRE_BINARIES})
set(OGRE_LIBRARIES $ENV{OGRE_LIBRARIES})
#Set Ogre Variables

#Set SDl Variable
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/../SDL2")
set(SDL2_INCLUDE_DIR  "${SDL2_DIR}/include")
set(SDL2_LIBRARY      "${SDL2_DIR}/lib/x64/SDL2.lib")
set(SDL2MAIN_LIBRARY  "${SDL2_DIR}/lib/x64/SDL2main.lib")
#Set SDl Variable

#Set Other Variables
set(GAME_ENGINE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../GameEngine/include")
set(VCPKG_ROOT $ENV{VCPKG_ROOT_DIR})
#Set Other Variables

# GlobalHeaderFile
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
# GlobalHeaderFile

#bin path
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}" )
#bin path


cmake_minimum_required( VERSION 3.5.1 )
project( Game )

#vcpkg
include(${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
#vcpkg
#Ogre
include( CMake/Bootstrap.cmake )
include( CMake/Dependencies/OGRE.cmake )
setupOgre( OGRE_SOURCE, OGRE_BINARIES, OGRE_LIBRARIES, FALSE, FALSE )
#Ogre

# Setup our application
set( EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}" )
if( MSVC )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
	if( NOT PLATFORM_X64 )
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /arch:SSE2")
	endif()
	add_definitions( -DUNICODE -D_UNICODE )
endif()
# Setup our application

#lib header
include_directories( "${SDL2_INCLUDE_DIR}" )
#lib header

# Copier les headers Engine
file(COPY "${GAME_ENGINE_INCLUDE_DIR}/"
     DESTINATION "${HEADER_DIR}")
# Copier les headers Engine

# Récupération automatique des fichiers
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    "${HEADER_DIR}/*.h"
    "${HEADER_DIR}/*.hpp"
)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${SOURCE_DIR}/*.cpp"
    "${SOURCE_DIR}/*.c"
)

source_group(
    TREE ${HEADER_DIR}
    PREFIX "Header Files"
    FILES ${HEADERS}
)

source_group(
    TREE ${SOURCE_DIR}
    PREFIX "Source Files"
    FILES ${SOURCES}
)
# Récupération automatique des fichiers

#Package
#Eigen
find_package(Eigen3 3.3 REQUIRED NO_MODULE)
#Package

# add executable
add_executable( ${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${SOURCES} ${HEADERS} ${RESOURCES} )

#TargetInclude
target_include_directories(${PROJECT_NAME} PUBLIC ${HEADER_DIR})
#TargetInclude

#TargetLib
target_link_libraries( ${PROJECT_NAME} ${OGRE_LIBRARIES} )
target_link_libraries(${PROJECT_NAME} "${SDL2_LIBRARY}" "${SDL2MAIN_LIBRARY}")
target_link_libraries( ${PROJECT_NAME} Eigen3::Eigen )
#TargetLib

#Copy Dll
file(COPY "${CMAKE_SOURCE_DIR}/../SDL2/lib/x64/SDL2.dll"
     DESTINATION "${EXECUTABLE_OUTPUT_PATH}/Debug")
file(COPY "${CMAKE_SOURCE_DIR}/../SDL2/lib/x64/SDL2.dll"
     DESTINATION "${EXECUTABLE_OUTPUT_PATH}/Release")
#Copy Dll

# Définit le répertoire de travail pour le débogueur Visual Studio
set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY 
        "$<IF:$<CONFIG:Debug>,${EXECUTABLE_OUTPUT_PATH}/Debug,${EXECUTABLE_OUTPUT_PATH}/Release>"
)

# Définit le répertoire de travail pour le débogueur Visual Studio