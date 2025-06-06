// Copyright (c) 2016
// Utrecht University (The Netherlands),
// ETH Zurich (Switzerland),
// INRIA Sophia-Antipolis (France),
// Max-Planck-Institute Saarbruecken (Germany),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org)
//
// $URL$
// $Id$
// SPDX-License-Identifier: LGPL-3.0-or-later OR LicenseRef-Commercial
//
//
// Author(s)     : Mariette Yvinec, Sylvain Pion

#ifndef CGAL_WEIGHTED_POINT_2_H
#define CGAL_WEIGHTED_POINT_2_H

#include <CGAL/Origin.h>
#include <CGAL/representation_tags.h>
#include <CGAL/assertions.h>
#include <CGAL/Kernel/Return_base_tag.h>
#include <CGAL/Bbox_2.h>
#include <CGAL/Dimension.h>
#include <CGAL/Point_2.h>

namespace CGAL {

template <class R_>
class Weighted_point_2 : public R_::Kernel_base::Weighted_point_2
{
  typedef typename R_::FT                             FT;
  typedef typename R_::FT                             RT;

  typedef Weighted_point_2<R_>                        Self;
  static_assert(std::is_same<Self, typename R_::Weighted_point_2>::value);

public:
  typedef Dimension_tag<2>                            Ambient_dimension;
  typedef Dimension_tag<0>                            Feature_dimension;

  typedef typename R_::Kernel_base::Weighted_point_2  Rep;
  typedef typename R_::Cartesian_const_iterator_2     Cartesian_const_iterator;
  typedef typename R_::Point_2                        Point_2;
  typedef typename R_::Aff_transformation_2           Aff_transformation_2;

  typedef Point_2                                     Point;
  typedef FT                                          Weight;
  typedef          R_                                 R;

  const Rep& rep() const
  {
    return *this;
  }

  Rep& rep()
  {
    return *this;
  }

  Weighted_point_2() {}

  Weighted_point_2(const Origin& o)
    : Rep(typename R::Construct_weighted_point_2()(Return_base_tag(), o))
  {}

  Weighted_point_2(const Rep& p)
      : Rep(p) {}

  Weighted_point_2(Rep&& p)
      : Rep(std::move(p)) {}

  explicit
  Weighted_point_2(const Point_2& p)
    : Rep(typename R::Construct_weighted_point_2()(Return_base_tag(), p, 0))
  {}

  Weighted_point_2(const Point_2& p, const Weight& w)
    : Rep(typename R::Construct_weighted_point_2()(Return_base_tag(), p, w))
  {}

  Weighted_point_2(const FT& x, const FT& y)
    : Rep(typename R::Construct_weighted_point_2()(Return_base_tag(), x, y))
  {}

  decltype(auto)
  point() const
  {
    return typename R::Construct_point_2()(*this);
  }

  decltype(auto)
  weight() const
  {
    return typename R::Compute_weight_2()(*this);
  }


  decltype(auto)
  x() const
  {
    return typename R::Compute_x_2()(point());
  }

  decltype(auto)
  y() const
  {
    return typename R::Compute_y_2()(point());
  }

  decltype(auto)
  hx() const
  {
    return R().compute_hx_2_object()(point());
  }

  decltype(auto)
  hy() const
  {
    return R().compute_hy_2_object()(point());
  }

  decltype(auto)
  hw() const
  {
    return R().compute_hw_2_object()(point());
  }

  decltype(auto)
  cartesian(int i) const
  {
    CGAL_kernel_precondition( (i == 0) || (i == 1) );
    if (i==0) return x();
    return y();
  }

  RT
  homogeneous(int i) const
  {
    CGAL_kernel_precondition( (i >= 0) || (i <= 2) );
    if (i==0) return hx();
    if (i==1) return hy();
    return hw();
  }

  decltype(auto)
  operator[](int i) const
  {
      return cartesian(i);
  }

  Cartesian_const_iterator cartesian_begin() const
  {
    return typename R::Construct_cartesian_const_iterator_2()(point());
  }

  Cartesian_const_iterator cartesian_end() const
  {
    return typename R::Construct_cartesian_const_iterator_2()(point(),3);
  }

  int dimension() const
  {
      return 2;
  }

  Bbox_2 bbox() const
  {
    return R().construct_bbox_2_object()(point());
  }

  Weighted_point_2 transform(const Aff_transformation_2 &t) const
  {
    return Weighted_point_2(t.transform(point()),weight());
  }

};

template <class R >
std::ostream&
insert(std::ostream& os, const Weighted_point_2<R>& p,const Cartesian_tag&)
{
    switch(IO::get_mode(os)) {
    case IO::ASCII :
        return os << p.point() << ' ' << p.weight();
    case IO::BINARY :
        write(os, p.x());
        write(os, p.y());
        write(os, p.weight());
        return os;
    default:
      return os << "Weighted_pointC2(" << p.x() << ", " << p.y() << ", " << p.weight()<< ')';
    }
}

template <class R >
std::ostream&
insert(std::ostream& os, const Weighted_point_2<R>& p,const Homogeneous_tag&)
{
  switch(IO::get_mode(os))
  {
    case IO::ASCII :
      return os << p.point() << ' ' << p.weight();
    case IO::BINARY :
      os << p.point();
      write(os, p.weight());
      return os;
    default:
      return os << "Weighted_pointH2("
                << p.hx() << ", "
                << p.hy() << ", "
                << p.hw() << ", "
                << p.weight() << ')';
  }
}

template < class R >
std::ostream&
operator<<(std::ostream& os, const Weighted_point_2<R>& p)
{
  return insert(os, p, typename R::Kernel_tag() );
}


template <class R >
std::istream&
extract(std::istream& is, Weighted_point_2<R>& p, const Cartesian_tag&)
{
  typename R::FT x, y, weight;
    switch(IO::get_mode(is)) {
    case IO::ASCII :
      is >> IO::iformat(x) >> IO::iformat(y) >> IO::iformat(weight);
        break;
    case IO::BINARY :
        read(is, x);
        read(is, y);
        read(is, weight);
        break;
    default:
        std::cerr << "" << std::endl;
        std::cerr << "Stream must be in ASCII or binary mode" << std::endl;
        break;
    }
    if (is)
      p = Weighted_point_2<R>(typename R::Point_2(x, y),weight);
    return is;
}


template <class R >
std::istream&
extract(std::istream& is, Weighted_point_2<R>& p, const Homogeneous_tag&)
{
  typename R::RT hx, hy, hw;
  typename R::FT weight;
  switch(IO::get_mode(is))
  {
    case IO::ASCII :
      is >> hx >> hy >> hw >> weight;
        break;
    case IO::BINARY :
        read(is, hx);
        read(is, hy);
        read(is, hw);
        read(is, weight);
        break;
    default:
        std::cerr << "" << std::endl;
        std::cerr << "Stream must be in ASCII or binary mode" << std::endl;
        break;
  }
  if (is)
    p = Weighted_point_2<R>(typename R::Point_2(hx, hy, hw),weight);
  return is;
}

template < class R >
std::istream&
operator>>(std::istream& is, Weighted_point_2<R>& p)
{
  return extract(is, p, typename R::Kernel_tag() );
}

} //namespace CGAL

#endif // CGAL_WEIGHTED_POINT_2_H
