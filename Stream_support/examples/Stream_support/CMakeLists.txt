cmake_minimum_required(VERSION 3.12...3.31)
project(Stream_support_Examples)

find_package(CGAL REQUIRED)

create_single_source_cgal_program( "Point_WKT.cpp" )
create_single_source_cgal_program( "Polygon_WKT.cpp" )
create_single_source_cgal_program( "Linestring_WKT.cpp" )
create_single_source_cgal_program( "read_WKT.cpp" )
create_single_source_cgal_program( "read_xml.cpp" )

create_single_source_cgal_program( "iv2off.cpp" )
create_single_source_cgal_program( "off2iv.cpp" )
create_single_source_cgal_program( "off2off.cpp" )
create_single_source_cgal_program( "off2stl.cpp" )
create_single_source_cgal_program( "off2vrml.cpp" )
create_single_source_cgal_program( "off2wav.cpp" )
create_single_source_cgal_program( "off_bbox.cpp" )
create_single_source_cgal_program( "off_glue.cpp" )
create_single_source_cgal_program( "off_transform.cpp" )
