cmake_minimum_required(VERSION 3.10.0)
project(bulls_and_cows VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

add_executable(generate_data source/generate_data.cpp)
add_executable(bulls_and_cows source/main.cpp)

target_compile_features(bulls_and_cows PUBLIC cxx_std_23)
target_compile_options(bulls_and_cows PRIVATE -O3)

target_compile_options(generate_data PRIVATE -O3)
target_compile_features(generate_data PUBLIC cxx_std_23)

if(NOT (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/permutations.bin AND 
   EXISTS ${CMAKE_CURRENT_BINARY_DIR}/score_matrix.bin))
    
    add_custom_target(
        generate_data_files
        COMMAND generate_data
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating data files"
        VERBATIM
    )

    add_dependencies(bulls_and_cows generate_data_files)

endif()

include(CTest)
enable_testing()

