
namespace CGAL {

/*!
\ingroup PkgBoundingVolumesRef

The class `Min_sphere_annulus_d_traits_2` is a traits class for the \f$ d\f$-dimensional
optimization algorithms using the two-dimensional \cgal kernel.

\tparam K  must bea model for `Kernel`.
\tparam ET NT are models for `RingNumberType`. Their default type is `K::RT`.

\cgalModels{MinSphereAnnulusDTraits}

\sa `CGAL::Min_sphere_d<Traits>`
\sa `CGAL::Min_annulus_d<Traits>`
\sa `CGAL::Min_sphere_annulus_d_traits_3<K,ET,NT>`
\sa `CGAL::Min_sphere_annulus_d_traits_d<K,ET,NT>`

*/
template< typename K, typename ET, typename NT >
class Min_sphere_annulus_d_traits_2 {
public:

/// \name Types
/// @{

/*!
typedef to `K::Point_2`.
*/
typedef unspecified_type Point_d;

/*!
typedef to `K::Rep_tag`.
*/
typedef unspecified_type Rep_tag;

/*!
typedef to `K::RT`.
*/
typedef unspecified_type RT;

/*!
typedef to `K::FT`.
*/
typedef unspecified_type FT;

/*!
typedef to `K::Access_dimension_2`.
*/
typedef unspecified_type Access_dimension_d;

/*!
typedef to `K::Access_coordinates_begin_2`.
*/
typedef unspecified_type Access_coordinates_begin_d;

/*!
typedef to `K::Construct_point_2`.
*/
typedef unspecified_type Construct_point_d;

/*!
second template parameter (default is `K::RT`).
*/
typedef unspecified_type ET;

/*!
third template parameter (default is `K::RT`).
*/
typedef unspecified_type NT;

/// @}

/// \name Creation
/// @{

/*!
default constructor.
*/
Min_sphere_annulus_d_traits_2( );

/*!
copy constructor.
*/
Min_sphere_annulus_d_traits_2(
const Min_sphere_annulus_d_traits_2<K,ET,NT>&);

/// @}

/// \name Operations
/// The following functions just return the corresponding function
/// class object.
/// @{

/*!

*/
Access_dimension_d
access_dimension_d_object() const;

/*!

*/
Access_coordinates_begin_d
access_coordinates_begin_d_object() const;

/*!

*/
Construct_point_d
construct_point_d_object() const;

/// @}

}; /* end Min_sphere_annulus_d_traits_2 */
} /* end namespace CGAL */
