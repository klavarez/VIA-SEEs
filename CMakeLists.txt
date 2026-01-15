#----------------------------------------------------------------------------
# Setup the project
#
cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(AS)

#----------------------------------------------------------------------------
# Find Geant4 package, activating all available UI and Vis drivers by default
# You can set WITH_GEANT4_UIVIS to OFF via the command line or ccmake/cmake-gui
# to build a batch mode only executable
#
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

#----------------------------------------------------------------------------
# Setup Geant4 include directories and compile definitions
# Setup include directory for this project
#
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

#----------------------------------------------------------------------------
#find_package(ROOT)

#I would also change include_directories(/usr/include/root/) to
#include_directories(${ROOT_INCLUDE_DIR})

#Both ROOT_LIBRARIES and ROOT_INCLUDE_DIR are set if the FindROOT macro finds package ROOT.

#ROOT_LIBRARIES only holds a couple of most used root libs, so in case you need to add some specific libs, (e.g. Eve), use:
#set(ROOT_LIBRARIES ${ROOT_LIBRARIES} -lEve)



# This allows CMake to find your module
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR} ${CMAKE_MODULE_PATH})

# Find ROOT
find_package(ROOT)

# Add ROOTs header paths
include_directories(${ROOT_INCLUDE_DIR})
include_directories(/opt/homebrew/Cellar/root/6.30.06/include/root)

# Build your executable
#add_executable(MyExe MyExe.cpp)

# Link executable to ROOT libraries


#----------------------------------------------------------------------------
# Locate sources and headers for this project
# NB: headers are included so they will show up in IDEs
#
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#----------------------------------------------------------------------------
# Add the executable, and link it to the Geant4 libraries
#
execute_process(COMMAND root-config --libs OUTPUT_VARIABLE ROOT_LD_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ROOT_LD_FLAGS}")
execute_process(COMMAND root-config --cflags OUTPUT_VARIABLE ROOT_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ROOT_CXX_FLAGS}")

add_executable(SimpleDet2 SimpleDet.cc ${sources} ${headers})
target_link_libraries(SimpleDet2 ${Geant4_LIBRARIES} ${ROOT_LIBRARIES})
#target_link_libraries(SimpleDet ${ROOT_LIBRARIES})

target_link_libraries(SimpleDet2 ${ROOT_LIBRARIES})
target_link_libraries(SimpleDet2 /opt/homebrew/Cellar/root/6.32.02/lib/root)
target_link_libraries(SimpleDet2 ${Geant4_LIBRARIES} /opt/homebrew/Cellar/root/6.32.02/lib/root)

#----------------------------------------------------------------------------
# Copy all scripts to the build directory, i.e. the directory in which we
# build SimpleDet. This is so that we can run the executable directly because it
# relies on these scripts being in the current working directory.
#
set(SimpleDet_SCRIPTS
  vis.mac
  )

foreach(_script ${SimpleDet_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

#----------------------------------------------------------------------------
# For internal Geant4 use - but has no effect if you build this
# example standalone
#
add_custom_target(AS DEPENDS SimpleDet2)

#----------------------------------------------------------------------------
# Install the executable to 'bin' directory under CMAKE_INSTALL_PREFIX
#
install(TARGETS SimpleDet2 DESTINATION bin)


