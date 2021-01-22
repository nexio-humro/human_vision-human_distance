cmake_minimum_required(VERSION 3.0.2)
project(human_distance)

#add_compile_options(-std=c++11)
add_definitions(-std=c++14)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  zed_nodelets
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

FILE(GLOB_RECURSE SRC_FILES src/*.c*)
FILE(GLOB_RECURSE TEST_SRC_FILES test_src/*.c*)
FILE(GLOB_RECURSE HDR_FILES include/*.h*)

catkin_package(
   CATKIN_DEPENDS roscpp std_msgs zed_nodelets
)

include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${HDR_FILES} ${SRC_FILES} main_src/main.cpp)
add_executable(${PROJECT_NAME}_tests ${HDR_FILES} ${SRC_FILES} ${TEST_SRC_FILES})

target_link_libraries(${PROJECT_NAME}
                        ${catkin_LIBRARIES})

target_link_libraries(${PROJECT_NAME}_tests
                        ${catkin_LIBRARIES})
