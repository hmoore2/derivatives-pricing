cmake_minimum_required(VERSION 3.0)
project(Pricing)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
# Find Eigen library
find_package(Eigen3 CONFIG REQUIRED)

# Add Eigen include directories
include_directories(${EIGEN3_INCLUDE_DIR})
set(SOURCE_FILES main.cpp)
add_executable(Pricing-Eigen_run ${SOURCE_FILES})

include_directories(Pricing-Eigen)
add_subdirectory(Pricing-Eigen)

target_link_libraries(Pricing-Eigen_run Pricing-Eigen)

# Add executable
add_executable(Pricing main.cpp
        Pricing-Eigen/MathsLib.cpp Pricing-Eigen/MathsLib.h
        Pricing-Eigen/BlackScholesModel.cpp
        Pricing-Eigen/BlackScholesModel.h
)

# Link Eigen libraries
target_link_libraries(Pricing-Eigen ${EIGEN3_LIBRARIES})

add_subdirectory(Google_tests)