cmake_minimum_required(VERSION 3.12...3.31)
project(TDS_3_Tests)

find_package(CGAL REQUIRED)

include_directories(BEFORE "./include")

find_package(TBB QUIET)
include(CGAL_TBB_support)

create_single_source_cgal_program("test_triangulation_tds_3.cpp")
create_single_source_cgal_program("test_io_tds3.cpp")

if(TARGET CGAL::TBB_support)
  message(STATUS "Found TBB")
  target_link_libraries(test_triangulation_tds_3 PRIVATE CGAL::TBB_support)
endif()
