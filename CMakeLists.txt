cmake_minimum_required(VERSION 3.6)
project(PaxEngine3)

### FLAGS ###############################################
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

### SOURCE FILES ########################################
set(SOURCE_FILES Default_main.cpp src/EngineMain.cpp src/lib/easylogging++.cc)

### SUBDIRECTORIES ######################################
add_subdirectory(src)

### EXECUTABLES #########################################
add_executable(PaxEngine3 ${SOURCE_FILES})

### LINKING #############################################
target_link_libraries(PaxEngine3 paxcore paxtest)