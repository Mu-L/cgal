// Copyright (c) 2006,2007,2009,2010,2011 Tel-Aviv University (Israel).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
//
// $URL$
// $Id$
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
//
//
// Author(s) : Efi Fogel          <efif@post.tau.ac.il>

#ifndef CGAL_ARR_POLYHEDRAL_SGM_POLYHEDRON_3_H
#define CGAL_ARR_POLYHEDRAL_SGM_POLYHEDRON_3_H

#include <CGAL/license/Arrangement_on_surface_2.h>

/*! \file
 * Related definition of a Polyhedron_3 data structure, an instance of which
 * can be used to initialize a Arr_polyhedral_sgm data structure.
 * A user can construct a Arr_polyhedral_sgm data structure in two ways as follows:
 * 1. Providing a sequence of (geometric) points in three dimensions and a
 * sequence of indices into the points that indicate the facets of the
 * polyhedron. An index equal to -1 indicates the end of a facet. Internally,
 * a temporary Polyhedron_3 object is constructed from the input. Then, the
 * Arr_polyhedral_sgm object is constructed from the Polyhedron_3 object. Finally,
 * the temporary Polyhedron_3 object is destructed.
 * 2. Providing a Polyhedron_3 object directly. In this case, the type
 * is constrained. The user is free to define her/his own vertex, halfedge,
 * and face types, but they must derive from the types provided in this file,
 * namely:
 *   Arr_polyhedral_sgm_polyhedron_3_vertex,
 *   Arr_polyhedral_sgm_polyhedron_3_halfedge, and
 *   Arr_polyhedral_sgm_polyhedron_3_face.
 * Notice that the latter is parameterized with a Sgm type, the same type
 * as the type Arr_polyhedral_sgm that, and object of which the user intends to
 * construct.
 */

#include <CGAL/basic.h>
#include <CGAL/Polyhedron_3.h>
#include <CGAL/HalfedgeDS_vertex_base.h>
#include <CGAL/HalfedgeDS_halfedge_base.h>
#include <CGAL/HalfedgeDS_face_base.h>

namespace CGAL {

/*! The extended Polyhedron vertex type */
template <class T_Refs, class T_Point>
class Arr_polyhedral_sgm_polyhedron_3_vertex :
  public HalfedgeDS_vertex_base<T_Refs, CGAL::Tag_true, T_Point> {

private:
  using Base = HalfedgeDS_vertex_base<T_Refs, CGAL::Tag_true, T_Point>;

  /*! Indicates that the vertex has been processed already */
  bool m_processed;

  /*! Indicates whether it is a marked vertex */
  bool m_marked;

public:
  using Point = typename Base::Point;

  /*! constructs */
  Arr_polyhedral_sgm_polyhedron_3_vertex() :
    Base(), m_processed(false), m_marked(false) {}

  /*! constructs */
  Arr_polyhedral_sgm_polyhedron_3_vertex(const Point & p) :
    Base(p), m_processed(false), m_marked(false) {}

  /*! obtains the mutable (geometrical) point. Delegate */
  Point& point() { return Base::point(); }

  /*! obtains the constant (geometrical) point. Delegate */
  const Point& point () const { return Base::point(); }

  /*! Set the flag */
  void set_processed(bool processed) { m_processed = processed; }

  /*! obtains the flag */
  bool processed() const { return m_processed; }

  /*! Set the "marked" flag */
  void set_marked(bool marked) { m_marked = marked; }

  /*! obtains the "marked" flag */
  bool marked() const { return m_marked; }
};

/*! The extended Polyhedron halfedge type */
template <class T_Refs>
class Arr_polyhedral_sgm_polyhedron_3_halfedge :
  public HalfedgeDS_halfedge_base<T_Refs> {
private:
  /*! Indicates that the halfedge has been processed already */
  bool m_processed;

  /*! Indicates whether it is a marked vertex */
  bool m_marked;

public:
  /*! constructs */
  Arr_polyhedral_sgm_polyhedron_3_halfedge() :
    m_processed(false), m_marked(false) {}

  /*! sets the flag */
  void set_processed(bool processed) { m_processed = processed; }

  /*! obtains the flag */
  bool processed() const { return m_processed; }

  /*! sets the "marked" flag */
  void set_marked(bool marked) { m_marked = marked; }

  /*! obtains the "marked" flag */
  bool marked() const { return m_marked; }
};

/*! The extended Polyhedron face type */
template <class T_Refs, class T_Plane, class Sgm>
class Arr_polyhedral_sgm_polyhedron_3_face :
  public HalfedgeDS_face_base<T_Refs, CGAL::Tag_true, T_Plane> {

private:
  using Base = HalfedgeDS_face_base<T_Refs, CGAL::Tag_true, T_Plane>;
  using Arr_vertex_handle = typename Sgm::Vertex_handle;

  /*! The arrangement vertex handle of the projected normal. */
  Arr_vertex_handle m_vertex;

  /*! Indicates whether it is a marked face */
  bool m_marked;

public:
  using Plane = typename Base::Plane;

  /*! constructs */
  Arr_polyhedral_sgm_polyhedron_3_face() : m_vertex(nullptr), m_marked(false) {}

  /*! obtains the mutable plane. Delegate */
  Plane& plane() { return Base::plane(); }

  /*! obtains the constant plane. Delegate */
  const Plane& plane() const { return Base::plane(); }

  /*! obtains the vertex */
  Arr_vertex_handle vertex() { return m_vertex; }

  /*! sets the vertex */
  void set_vertex(Arr_vertex_handle vertex) { m_vertex = vertex; }

  /*! sets the "marked" flag */
  void set_marked(bool marked) { m_marked = marked; }

  /*! obtains the "marked" flag */
  bool marked() const { return m_marked; }
};

/*! The "items" type. A model of the PolyhedralSgmPolyhedronItems_3 concept,
 * which is a refinement of the PolyhedronItems_3 concept. Its base class
 * Polyhedron_items_3, a model of the latter concept, provides definitions of
 * vertices with points, halfedges, and faces with normal equations. We extend
 * the definition of each one of the three items with the necessary data
 * required to construct a Arr_polyhedral_sgm object from a
 * Polyhedron_3 object, the type of which, namely Polyhedron_3, is
 * instantiated with this extended items type.
 */
template <class Sgm>
struct Arr_polyhedral_sgm_polyhedron_items : public Polyhedron_items_3 {
  template <class T_Refs, class T_Traits>
  struct Vertex_wrapper {
    using Point_3 = typename T_Traits::Point_3;
    using Vertex = Arr_polyhedral_sgm_polyhedron_3_vertex<T_Refs, Point_3>;
  };
  template <class T_Refs, class T_Traits>
  struct Halfedge_wrapper {
    using Halfedge = Arr_polyhedral_sgm_polyhedron_3_halfedge<T_Refs>;
  };
  template <class T_Refs, class T_Traits>
  struct Face_wrapper {
    using Plane_3 = typename T_Traits::Plane_3;
    using Face = Arr_polyhedral_sgm_polyhedron_3_face<T_Refs, Plane_3, Sgm>;
  };
};

/*! The default polyhedron type. If the Arr_polyhedral_sgm object is indirectly
 * constructed from the points and the facets provided as indices, then a
 * temporary object of type Arr_polyhedral_sgm_default_polyhedron_3 is
 * constructed internally, and used to represent the polyhedron. Similarly, if
 * the user provides a reference to a polyhedron object as input for the
 * construction of the Arr_polyhedral_sgm object, and she/he has no need to
 * extend the polyhedron features, this type should be used to represent the
 * polyhedron.  However, if the user need to extend the vertex, halfedge, or
 * face of the polyhedron, she/he must extend the appropriate type(s), define a
 * new items type that is based on the extended types, and define a new
 * polyhedron type based on the new items type.
 */
template <class Sgm, class Traits>
struct Arr_polyhedral_sgm_polyhedron_3 :
  public Polyhedron_3<Traits, Arr_polyhedral_sgm_polyhedron_items<Sgm>> {
  /*! constructs */
  Arr_polyhedral_sgm_polyhedron_3() {}
};

} // namespace CGAL

//! Make the polyhedron a model of FaceGraph
#define CGAL_GRAPH_TRAITS_INHERITANCE_TEMPLATE_PARAMS \
  typename Sgm, typename Traits
#define CGAL_GRAPH_TRAITS_INHERITANCE_CLASS_NAME \
  CGAL::Arr_polyhedral_sgm_polyhedron_3<Sgm, Traits>
#define CGAL_GRAPH_TRAITS_INHERITANCE_BASE_CLASS_NAME \
  CGAL::Polyhedron_3<Traits, CGAL::Arr_polyhedral_sgm_polyhedron_items<Sgm>>
#include <CGAL/boost/graph/graph_traits_inheritance_macros.h>

#endif
