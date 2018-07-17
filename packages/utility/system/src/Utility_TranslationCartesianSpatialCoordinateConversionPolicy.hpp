//---------------------------------------------------------------------------//
//!
//! \file   Utility_TranslationCartesianSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Translation Cartesian spatial coordinate conversion policy decl.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TRANSLATION_CARTESIAN_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP
#define UTILITY_TRANSLATION_CARTESIAN_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

// Boost Includes
#include <boost/serialization/array_wrapper.hpp>

// FRENSIE Includes
#include "Utility_CartesianSpatialCoordinateConversionPolicy.hpp"

namespace Utility{

//! The translation Cartesian coordinate conversion policy class
class TranslationCartesianSpatialCoordinateConversionPolicy : public CartesianSpatialCoordinateConversionPolicy
{

public:

  //! Constructor
  TranslationCartesianSpatialCoordinateConversionPolicy(
                                                      const double origin[3] );

  //! Destructor
  ~TranslationCartesianSpatialCoordinateConversionPolicy()
  { /* ... */ }

  //! Convert the spatial coordinates to cartesian coordinates
  void convertToCartesianSpatialCoordinates(
                                      const double primary_spatial_coord,
                                      const double secondary_spatial_coord,
                                      const double tertiary_spatial_coord,
                                      double& x_spatial_coord,
                                      double& y_spatial_coord,
                                      double& z_spatial_coord ) const override;

  //! Convert the cartesian coordinates to the spatial coordinate system
  void convertFromCartesianSpatialCoordinates(
                               const double x_spatial_coord,
                               const double y_spatial_coord,
                               const double z_spatial_coord,
                               double& primary_spatial_coord,
                               double& secondary_spatial_coord,
                               double& tertiary_spatial_coord ) const override;

  //! Convert the spatial coordinates to cartesian coordinates
  using CartesianSpatialCoordinateConversionPolicy::convertToCartesianSpatialCoordinates;

  //! Convert the cartesian coordinates to the spatial coordinate system
  using CartesianSpatialCoordinateConversionPolicy::convertFromCartesianSpatialCoordinates;

private:

  // The default constructor should not be used - if the origin corresponds to
  // the global coordinate system (0,0,0) use the basic conversion policy
  TranslationCartesianSpatialCoordinateConversionPolicy()
  { /* ... */ }

  // We have C-arrays as members - hide the copy constructor and assignment
  // operator
  TranslationCartesianSpatialCoordinateConversionPolicy( const TranslationCartesianSpatialCoordinateConversionPolicy& that );
  TranslationCartesianSpatialCoordinateConversionPolicy& operator=( const TranslationCartesianSpatialCoordinateConversionPolicy& that );

  // Save the policy to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the policy from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The origin of the local Cartesian coordinate system w.r.t. the global
  // Cartesian coordinate system
  double d_origin[3];
};

// Save the policy to an archive
template<typename Archive>
void TranslationCartesianSpatialCoordinateConversionPolicy::save( Archive& ar, const unsigned version ) const
{
  // Save the base class
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( CartesianSpatialCoordinateConversionPolicy );

  // Save the local data
  ar & boost::serialization::make_nvp( "d_origin", boost::serialization::make_array( d_origin, 3 ) );
}

// Load the policy from an archive
template<typename Archive>
void TranslationCartesianSpatialCoordinateConversionPolicy::load( Archive& ar, const unsigned version )
{
  // Load the base class
  ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( CartesianSpatialCoordinateConversionPolicy );

  // Load the local data
  ar & boost::serialization::make_nvp( "d_origin", boost::serialization::make_array( d_origin, 3 ) );
}

} // end Utility namespace

BOOST_SERIALIZATION_CLASS_VERSION( TranslationCartesianSpatialCoordinateConversionPolicy, Utility, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( TranslationCartesianSpatialCoordinateConversionPolicy, Utility );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Utility, TranslationCartesianSpatialCoordinateConversionPolicy );

#endif // end UTILITY_TRANSLATION_CARTESIAN_SPATIAL_COORDINATE_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end Utility_TranslationCartesianSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
