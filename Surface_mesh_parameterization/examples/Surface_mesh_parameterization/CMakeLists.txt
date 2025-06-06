# This is the CMake script for compiling this folder.

cmake_minimum_required(VERSION 3.12...3.31)
project(Surface_mesh_parameterization_Examples)

find_package(CGAL REQUIRED)

find_package(Eigen3 3.1.0 QUIET) #(requires 3.1.0 or greater)
include(CGAL_Eigen3_support)
if(TARGET CGAL::Eigen3_support)
  # Executables that require Eigen 3.1

  # ------------------------------------------------------------------
  # Detect SuiteSparse libraries:
  # If not found automatically, set SuiteSparse_DIR in CMake to the
  # directory where SuiteSparse was built.
  # ------------------------------------------------------------------

  set(SuiteSparse_USE_LAPACK_BLAS ON)
  find_package(SuiteSparse QUIET NO_MODULE)# 1st: Try to locate the *config.cmake file.
  if(NOT SuiteSparse_FOUND)
    set(SuiteSparse_VERBOSE ON)
    find_package(SuiteSparse QUIET) # 2nd: Use FindSuiteSparse.cmake module
    if(SuiteSparse_FOUND)
      include_directories(${SuiteSparse_INCLUDE_DIRS})
    endif(SuiteSparse_FOUND)
  endif(NOT SuiteSparse_FOUND)

  if(SuiteSparse_FOUND)
    if(SuiteSparse_UMFPACK_FOUND OR TARGET SuiteSparse::umfpack)
      message(STATUS "SuiteSparse_LIBS: ${SuiteSparse_LIBRARIES}")
      message(STATUS "Orbifold Tutte Embeddings will use UmfPackLU")
    else()
      message(STATUS "NOTICE: Examples will be compiled without the SuiteSparse library and UmfPack. Try setting SuiteSparse_UMF_INCLUDE_DIR and at least one of SuiteSparse_UMFPACK_LIBRARY_RELEASE and SuiteSparse_UMFPACK_LIBRARY_DEBUG to you UMFPACK installation.")
    endif()
  else(SuiteSparse_FOUND)
    message(STATUS "NOTICE: Examples will not be compiled without the SuiteSparse library.")
  endif(SuiteSparse_FOUND)

  # ------------------------------------------------------------------
  #   End of SuiteSparse detection
  # ------------------------------------------------------------------

  create_single_source_cgal_program("ARAP_parameterization.cpp")
  target_link_libraries(ARAP_parameterization PRIVATE CGAL::Eigen3_support)
  create_single_source_cgal_program("discrete_authalic.cpp")
  target_link_libraries(discrete_authalic PRIVATE CGAL::Eigen3_support)
  create_single_source_cgal_program("lscm.cpp")
  target_link_libraries(lscm PRIVATE CGAL::Eigen3_support)
  create_single_source_cgal_program("orbifold.cpp")
  target_link_libraries(orbifold PRIVATE CGAL::Eigen3_support)
  create_single_source_cgal_program("seam_Polyhedron_3.cpp")
  target_link_libraries(seam_Polyhedron_3 PRIVATE CGAL::Eigen3_support)
  create_single_source_cgal_program("simple_parameterization.cpp")
  target_link_libraries(simple_parameterization PRIVATE CGAL::Eigen3_support)
  create_single_source_cgal_program("square_border_parameterizer.cpp")
  target_link_libraries(square_border_parameterizer PRIVATE CGAL::Eigen3_support)
  create_single_source_cgal_program( "iterative_authalic_parameterizer.cpp" )
  target_link_libraries(iterative_authalic_parameterizer PRIVATE CGAL::Eigen3_support)
  if(SuiteSparse_FOUND)
    target_link_libraries(ARAP_parameterization PRIVATE ${SuiteSparse_LIBRARIES})
    target_link_libraries(orbifold PRIVATE ${SuiteSparse_LIBRARIES})
    if(SuiteSparse_UMFPACK_FOUND OR TARGET SuiteSparse::umfpack)
      target_compile_definitions(ARAP_parameterization  PRIVATE EIGEN_DONT_ALIGN_STATICALLY CGAL_SMP_USE_SUITESPARSE_SOLVERS )
      target_compile_definitions(orbifold  PRIVATE EIGEN_DONT_ALIGN_STATICALLY CGAL_SMP_USE_SUITESPARSE_SOLVERS )
    endif()
  endif()

else()
  message("NOTICE: The examples require Eigen 3.1 (or greater), and will not be compiled.")
endif()
