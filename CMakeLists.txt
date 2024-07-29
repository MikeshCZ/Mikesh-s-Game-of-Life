cmake_minimum_required(VERSION 3.14)
project(Mikesh-s-Game-of-Life)

# Standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
set(SOURCES
    src/main.cpp
    src/grid.cpp
    src/intro.cpp
    src/simulation.cpp
    src/settings.cpp
)

# Add header files
set(HEADERS
    src/grid.hpp
    src/intro.hpp
    src/simulation.hpp
    src/settings.hpp
    ext/raygui-4.0/src/raygui.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Libraries
find_package(raylib)

#Link raylib to main
target_link_libraries(${PROJECT_NAME} 
    raylib
)

# Debug and release configuration settings
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    # Release configuration
    message("Building Release configuration")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2") # Adds optimization
else()
    # Debug configuration
    message("Building Debug configuration")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g") # Adds debugging information
endif()

# Copy directories
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/audio $<TARGET_FILE_DIR:${PROJECT_NAME}>/audio
)