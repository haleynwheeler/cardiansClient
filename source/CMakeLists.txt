# This file is adapted from the one supplied by Jorgen Bodde on wiki.wxWidgets.org

# define minimum cmake version
cmake_minimum_required(VERSION 2.6.2)

# Our project is called 'cardiansClient' this is how it will be called in
# visual studio, and in our makefiles.
project(cardiansClient)

# Location where cmake first looks for cmake modules.
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}")
# set(CMAKE_MODULE_PATH "${/home/katie/Desktop/testWx}")

##---------------------------------------------------
## Please set your wxWidgets configuration here
##---------------------------------------------------

# Here you can define what libraries of wxWidgets you need for your
# application. You can figure out what libraries you need here;
# http://www.wxwidgets.org/manuals/2.8/wx_librarieslist.html
# We need the Find package for wxWidgets to work
# NOTE: if you're using aui, include aui in this required components list.

# It was noticed that when using MinGW gcc it is essential that 'core' is mentioned before 'base'.
find_package(wxWidgets COMPONENTS core base REQUIRED)

##---------------------------------------------------
## Actual config file starts here
##---------------------------------------------------

# wxWidgets include (this will do all the magic to configure everything)
include( "${wxWidgets_USE_FILE}" )

# For convenience we define the sources as a variable. You can add
# header files and cpp/c files and CMake will sort them out
# ************************ WHEN YOU ADD A SOURCE, UPDATE HERE *****************
set(SRCS main.cpp
    button.h button.cpp
    baseBackground.h baseBackground.cpp
    login.h login.cpp
    imageInsert.h imageInsert.cpp
    playArea.h playArea.cpp)

add_subdirectory(crazyEightsLogic)

set(CMAKE_C++_FLAGS "-g -Wall")

add_definitions(
  -std=c++14
)

# If we build for windows systems, we also include the resource file
# containing the manifest, icon and other resources
if(WIN32)
  set(SRCS ${SRCS} cardiansClient.rc)
endif(WIN32)

# Here we define the executable cardiansClient.exe or cardiansClient on other systems
# the above paths and defines will be used in this build
add_executable(cardiansClient WIN32 ${SRCS})

# We add to our target 'cardiansClient' the wxWidgets libraries. These are
# set for us by the find script. If you need other libraries, you
# can add them here as well.
target_link_libraries(cardiansClient ${wxWidgets_LIBRARIES})
