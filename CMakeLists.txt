# Set env variables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(SOURCES src/main.cpp src/snake.cpp src/block.cpp)
# set(HEADERS include/Snake.h)
set(PROJECT snake)

cmake_minimum_required(VERSION 3.16)
project(${PROJECT} LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

# Include libraries
include_directories(include)


add_executable(${PROJECT} ${SOURCES}) 

target_link_libraries(${PROJECT} PRIVATE sfml-graphics)
target_compile_features(${PROJECT} PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${PROJECT}>
        VERBATIM)
endif()

install(TARGETS ${PROJECT})