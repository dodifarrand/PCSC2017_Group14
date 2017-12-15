include_directories(${CMAKE_CURRENT_SOURCE_DIR})
find_package (Eigen3 3.3 REQUIRED NO_MODULE)


set(HEADER_FILES Approximation.hpp)
add_executable(New_main New_main.cpp Config.cpp Approximation.cpp Points.cpp)
target_link_libraries (New_main Eigen3::Eigen)

add_executable(main_approx_test main_approx_test.cpp Approximation.cpp Points.cpp)
target_link_libraries (main_approx_test Eigen3::Eigen)

add_executable(Config Config.cpp)

add_executable(Approximation Approximation.cpp)
target_link_libraries (Approximation Eigen3::Eigen)


add_executable(CreateScenarios CreateScenarios.cpp FuctionApprox.cpp)

