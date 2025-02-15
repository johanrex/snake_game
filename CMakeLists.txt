cmake_minimum_required(VERSION 3.10)

project(SnakeGame C)

set(CMAKE_C_STANDARD 99)

# Add source to this project's executable.
add_executable(SnakeGame 
    "main.c" 
    "snake.c" 
    "gfx.c" 
    "fruit.c"
)

# Set the SDL3_DIR to the path where SDL3Config.cmake is located
set(SDL3_DIR "C:/SDL3-3.2.4/cmake")

# Find SDL3 library with a specific version
find_package(SDL3 3.2.4 REQUIRED)

# Link SDL3 library
target_link_libraries(SnakeGame SDL3::SDL3)

# Enable warnings as errors for the target
if (MSVC)
    # Ensure /W4 is the first flag to prevent CMake from adding /W3 first
    target_compile_options(SnakeGame PRIVATE /WX /wd4100)
else()
    target_compile_options(SnakeGame PRIVATE -Werror -Wall -Wno-unused-parameter)
endif()

# Post-build command to copy SDL3.dll to the build directory
add_custom_command(TARGET SnakeGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying SDL3.dll..."
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "C:/SDL3-3.2.4/lib/x64/SDL3.dll" $<TARGET_FILE_DIR:SnakeGame>
    
    COMMAND ${CMAKE_COMMAND} -E echo "SDL3.dll copied to $<TARGET_FILE_DIR:SnakeGame>"
)

