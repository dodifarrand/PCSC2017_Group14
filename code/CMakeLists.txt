include_directories(${CMAKE_CURRENT_SOURCE_DIR})
find_package (Eigen3 3.3 REQUIRED NO_MODULE)


set(HEADER_FILES Approximation.hpp)
add_executable(Interact_main Interact_main.cpp Approximation.cpp Points.cpp)
target_link_libraries (Interact_main Eigen3::Eigen)

add_executable(Test_Fitting Test_Fitting.cpp Approximation.cpp Points.cpp)
target_link_libraries (Test_Fitting Eigen3::Eigen)

add_executable(Test_Interpolation Test_Interpolation.cpp Approximation.cpp Points.cpp)
target_link_libraries (Test_Interpolation Eigen3::Eigen)

add_executable(Test_PieceWise Test_PieceWise.cpp Approximation.cpp Points.cpp)
target_link_libraries (Test_PieceWise Eigen3::Eigen)

add_executable(Test_PieceWiseCont Test_PieceWiseCont.cpp Approximation.cpp Points.cpp)
target_link_libraries (Test_PieceWiseCont Eigen3::Eigen)

add_executable(Approximation Approximation.cpp)
target_link_libraries (Approximation Eigen3::Eigen)


add_executable(CreateScenarios CreateScenarios.cpp FunctionApprox.cpp)

add_executable(TestFunctionApprox TestFunctionApprox.cpp FunctionApprox.cpp)

add_executable(TestEmptyConfig TestEmptyConfig.cpp Points.cpp Approximation.cpp)
target_link_libraries (TestEmptyConfig Eigen3::Eigen)