//---------------------------------------------------------------------------//
//!
//! \file   Utility_PQLAQuadrature.hpp
//! \author Philip Britt
//! \brief  PQLA Direction Quadrature handler declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PQLA_QUADRATURE
#define UTILITY_PQLA_QUADRATURE

// Boost Includes
#include <boost/serialization/version.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE includes
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Array.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Utility{

struct SphericalTriangle
{
  /*! Vector that contains a tuple representing spherical triangle parameters.
   * \details First element of the tuple is an array that contains the
   * 2-norm direction representing a vertex of the triangle. 
   * Second is the length of the spherical triangle side opposite from that vertex
   * ( or angle that the 2 other vertices of the triangle make with each other ).
   * Third is the angle made from the sides of the spherical triangle from that vertex.
   * Note their order does NOT matter so long as they are consistent with the above definition
   */
  std::vector<std::tuple<std::array<double, 3>, double, double>> triangle_parameter_vector;

  //! Area of the triangle
  double area;

    //! Processes spherical triangle information
  void computeAndStoreTriangleParameters(std::vector<std::array<double, 3>>& vertex_vector);

  // Serialize the data
  template<typename Archive>
  void serialize(Archive& ar, const unsigned version)
  { 
    ar & BOOST_SERIALIZATION_NVP( triangle_parameter_vector );
    ar & BOOST_SERIALIZATION_NVP( area );
  }
};

class PQLAQuadrature
{

  public:

  //! Constructor
  PQLAQuadrature(unsigned quadrature_order);

  //! Destructor
  ~PQLAQuadrature()
  { /* ... */ }

  //! Find which triangle bin a direction vector is in
  size_t findTriangleBin(  const std::array<double, 3>& direction ) const;

  //! Find which triangle bin a direction vector is in
  size_t findTriangleBin(  const double x_direction, const double y_direction, const double z_direction ) const;

  //! Return the order of the quadrature
  unsigned getQuadratureOrder() const;

  //! Get the total number of triangles
  size_t getNumberOfTriangles() const;
  
  //! Get the area of a specific spherical triangle
  double getTriangleArea( const size_t triangle_index ) const;

  /*! Get a random direction from within a spherical triangle ( evenly distributed probability ) - reference here
   * \details reference: Stratified Sampling of Spherical Triangles, James Arvo, SIGGRAPH '95
   */
  void sampleIsotropicallyFromTriangle( std::array<double, 3>& direction_vector, 
                                       const size_t triangle_index ) const;

  const std::vector<SphericalTriangle>& getSphericalTriangleVector() const;

  private:

  //! Default constructor ( for archiving )
  PQLAQuadrature()
  { /* ... */ }

  //! Vector operation for the purpose of sampleIsotropicallyFromTriangle
  void isotropicSamplingVectorOperation( const std::array<double, 3>& vertex_1,
                                        const std::array<double, 3>& vertex_2,
                                        std::array<double, 3>& result_vector ) const;

  //! Converts direction vector to 1-norm normalized vector
  void normalizeVectorToOneNorm(  const std::array<double, 3>& direction_2_norm,
                                 std::array<double, 3>& direction_1_norm ) const;
  
  //! Converts direction vector to 1-norm normalized vector
  void normalizeVectorToOneNorm(   const double x_direction, 
                                  const double y_direction, 
                                  const double z_direction,
                                  std::array<double, 3>& direction_1_norm ) const;

  //! Take lower bounding plane indices of direction vector to form triangle index
  size_t calculatePositiveTriangleBinIndex( const unsigned i_x, const unsigned i_y, const unsigned i_z ) const;

  //! Take direction signs to calculate secondary index
  size_t findSecondaryIndex( const bool x_sign, const bool y_sign, const bool z_sign ) const;

  //! Quadrature order
  unsigned d_quadrature_order;

  //! Vector that stores POSITIVE DOMAIN spherical triangles
  std::vector<SphericalTriangle> d_spherical_triangle_vector;

  //! Serialize the data
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version );

  //! Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

};

// Serialize the data
template<typename Archive>
void PQLAQuadrature::serialize( Archive& ar, const unsigned version )
{
  // Serialize the member data
  ar & BOOST_SERIALIZATION_NVP( d_quadrature_order );
  ar & BOOST_SERIALIZATION_NVP( d_spherical_triangle_vector );
}

} // end Utility namespace

BOOST_SERIALIZATION_CLASS_VERSION( PQLAQuadrature, Utility, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( PQLAQuadrature, Utility );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( Utility, PQLAQuadrature );

#endif // end UTILITY_PQLA_QUADRATURE

//---------------------------------------------------------------------------//
// end Utility_PQLADiscetization.hpp
//---------------------------------------------------------------------------//