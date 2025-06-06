# Created by the script cgal_create_CMakeLists
# This is the CMake script for compiling a set of CGAL applications.

cmake_minimum_required(VERSION 3.12...3.31)
project(Point_set_3_Examples)

# CGAL and its components
find_package(CGAL REQUIRED OPTIONAL_COMPONENTS Qt6)

create_single_source_cgal_program("point_set.cpp")
create_single_source_cgal_program("point_set_property.cpp")
create_single_source_cgal_program("point_set_read_xyz.cpp")
create_single_source_cgal_program("point_set_advanced.cpp")
create_single_source_cgal_program("point_set_read_ply.cpp")

find_package(Eigen3 3.1.0 QUIET) #(requires 3.1.0 or greater)
include(CGAL_Eigen3_support)
if(TARGET CGAL::Eigen3_support)
  create_single_source_cgal_program("point_set_algo.cpp")
  target_link_libraries(point_set_algo PRIVATE CGAL::Eigen3_support)
else()
  message(STATUS "NOTICE: The example 'point_set_algo' requires the Eigen library, and will not be compiled.")
endif()

create_single_source_cgal_program("draw_point_set_3.cpp")
if(CGAL_Qt6_FOUND)
  target_link_libraries(draw_point_set_3 PRIVATE CGAL::CGAL_Basic_viewer)
endif()
