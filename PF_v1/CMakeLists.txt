cmake_minimum_required(VERSION 2.8)

project(ParticleFilter)

# set(CMAKE_CXX_COMPILER clang)
set(source_files 
	main.cc
	adaboostDetect.h 
	adaboostDetect.cpp
)

find_package(OpenCV REQUIRED)                             
add_executable(Hello  ${source_files})
target_link_libraries(Hello ${OpenCV_LIBS})

 


 
