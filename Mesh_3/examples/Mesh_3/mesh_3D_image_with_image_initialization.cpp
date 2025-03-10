#include "random_labeled_image.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

#include <CGAL/Mesh_triangulation_3.h>
#include <CGAL/Mesh_complex_3_in_triangulation_3.h>
#include <CGAL/Mesh_criteria_3.h>

#include <CGAL/Mesh_3/Construct_initial_points_labeled_image.h>

#include <CGAL/Labeled_mesh_domain_3.h>
#include <CGAL/make_mesh_3.h>
#include <CGAL/Image_3.h>

#include <CGAL/IO/File_medit.h>

// Domain
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Labeled_mesh_domain_3<K> Mesh_domain;

#ifdef CGAL_CONCURRENT_MESH_3
typedef CGAL::Parallel_tag Concurrency_tag;
#else
typedef CGAL::Sequential_tag Concurrency_tag;
#endif

// Triangulation
typedef CGAL::Mesh_triangulation_3<Mesh_domain,CGAL::Default,Concurrency_tag>::type Tr;

typedef CGAL::Mesh_complex_3_in_triangulation_3<Tr> C3t3;

// Criteria
typedef CGAL::Mesh_criteria_3<Tr> Mesh_criteria;

namespace params = CGAL::parameters;

int main()
{
  /// [Create_the_image]
  CGAL::Image_3 image = random_labeled_image();
  /// [Create_the_image]

  // Domain
  Mesh_domain domain = Mesh_domain::create_labeled_image_mesh_domain(image);

  // Mesh criteria
  Mesh_criteria criteria(params::facet_angle(30).facet_size(3).facet_distance(1)
                         .cell_radius_edge_ratio(3).cell_size(3));

  /// [Meshing]
  // Mesh generation with a custom initialization that places points
  // on the surface of each connected component of the image.
  CGAL::Construct_initial_points_labeled_image<C3t3, Mesh_domain> img_pts_generator(image, domain);

  C3t3 c3t3 = CGAL::make_mesh_3<C3t3>(domain, criteria,
                                      params::initial_points_generator(img_pts_generator));
  /// [Meshing]

  // Output
  std::ofstream medit_file("out.mesh");
  CGAL::IO::write_MEDIT(medit_file, c3t3);
  medit_file.close();

  return 0;
}
