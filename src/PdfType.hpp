//---------------------------------------------------------------------------//
//!
//! \file   Distribution.hpp
//! \author Alex Robinson
//! \brief  Distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef DISTRIBUTION_HPP
#define DISTRIBUTION_HPP

// FACEMC Includes
#include "DistributionType.hpp"

namespace FACEMC{

//! Distribution base class
class Distribution
{
  
public: 

  //! Constructor
  Distribution()
  { /* ... */ }

  //! Destructor
  virtual ~Distribution()
  { /* ... */ }

  //! Return the value of the distribution at the desired point
  virtual double getDistributionValue( const double point ) const = 0;

  //! Return a random sample from the distribution
  virtual double getRandomSample() const = 0;

  //! Return the maximum point at which the distribution is non-zero
  virtual double getUpperBoundOfIndepVar() const = 0;

  //! Return the minimum point at which the distribution is non-zero
  virtual double getLowerBoundOfIndepVar() const = 0;

  //! Return the distribution type
  virtual DistributionType getType() const = 0;
};

} // end FACEMC namespace

#endif // end DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Distribution.hpp
//---------------------------------------------------------------------------//
