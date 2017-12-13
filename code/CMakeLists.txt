include_directories(${CMAKE_CURRENT_SOURCE_DIR})
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(test_eig test_eigen.cpp)
target_link_libraries (test_eig Eigen3::Eigen)

add_executable(leastsquares leastsquares.cpp)
target_link_libraries (leastsquares Eigen3::Eigen)


add_executable(New_main New_main.cpp Testing.cpp ReadPointCoord.cpp Config.cpp DataFitting.cpp Points.cpp DataInterpolation.cpp)
target_link_libraries (New_main Eigen3::Eigen)
set(HEADER_FILES Approximation.hpp)


add_executable(main_approx main_approx.cpp)
target_link_libraries (main_approx Eigen3::Eigen)
add_executable(main_approx_test main_approx_test.cpp DataInterpolation.cpp Points.cpp DataFitting.cpp)
target_link_libraries (main_approx_test Eigen3::Eigen)

add_executable(Config Config.cpp)

