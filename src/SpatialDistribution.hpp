//---------------------------------------------------------------------------//
//!
//! \file   SpatialDistribution.hpp
//! \author Alex Robinson
//! \brief  Spatial distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef SPATIAL_DISTRIBUTION_HPP
#define SPATIAL_DISTRIBUTION_HPP

namespace FACEMC{

//! Spatial distribution base class
class SpatialDistribution
{

public:

  //! Constructor
  SpatialDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~SpatialDistribution()
  { /* ... */ }

  //! Evaluate the spatial distribution
  virtual double evaluate( const double cartesian_point[3] ) const = 0;

  //! Evaluate the spatial distribution PDF
  virtual double evaluatePDF( const double cartesian_point[3] ) const = 0;

  //! Return a random (cartesian) sample from the distribution (x, y, z)
  virtual void sample( double sampled_point[3] ) = 0;
};

} // end FACEMC namespace

#endif // end SPATIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end SpatialDistribution.hpp
//---------------------------------------------------------------------------//
