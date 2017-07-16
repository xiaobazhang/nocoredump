
project(nocoredump)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst ${CMAKE_SOURCE_DIR}/,,$(abspath $<))\"'")
add_definitions("-DLINUX -g -O0")
include_directories(/usr/local/include)
aux_source_directory(./base DATA_STRUCTURE_SRCS)
aux_source_directory(./srv DATA_STRUCTURE_SRCS)
add_executable(nocoredump main.cpp)
target_link_libraries(nocoredump pthread)
