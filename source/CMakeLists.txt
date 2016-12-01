cmake_minimum_required(VERSION 3.3)
if(CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_CONFIGURATION_TYPES Debug Release)
  set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
    "Set the configurations to what we need" FORCE
    )
endif()
project(cardiansClient)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}) # Findexternpro.cmake
set(externpro_REV 16.10.3)
if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif()
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
endif()
find_package(externpro REQUIRED)
xpCommonFlags()

add_subdirectory(GameLogic)
add_subdirectory(Networking)

xpGetExtern(externIncs externLibs PUBLIC boost wxWidgets)
include_directories(${externIncs} ${CMAKE_SOURCE_DIR})

add_executable(cardiansClient main.cpp
    button.h button.cpp
    baseBackground.h baseBackground.cpp
    login.h login.cpp
    imageInsert.cpp imageInsert.h
    newUser.cpp newUser.h
    playArea.cpp playArea.h
    playerCard.cpp playerCard.h
    heartsArea.cpp heartsArea.h
    Simple.cpp Simple.h
    mainMenu.cpp mainMenu.h
    clientInfo.cpp clientInfo.h)

target_link_libraries(cardiansClient GameLogic Networking ${externLibs})
