//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ComptonProfile.hpp
//! \author Alex Robinson
//! \brief  The Compton profile declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COMPTON_PROFILE_HPP
#define MONTE_CARLO_COMPTON_PROFILE_HPP

// Boost Includes
#include <boost/units/quantity.hpp>

// FRENSIE Includes
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_InverseMeCMomentumUnit.hpp"

namespace MonteCarlo{

//! The Compton profile class
class ComptonProfile
{
   
public:

  //! The Compton profile independent quantity type
  typedef boost::units::quantity<Utility::Units::MeCMomentum> MomentumQuantity;

  //! The Compton profile dependent quantity type
  typedef boost::units::quantity<Utility::Units::InverseMeCMomentum> ProfileQuantity;

  //! Default Constructor
  ComptonProfile()
  { /* ... */ }

  //! Destructor
  virtual ~ComptonProfile()
  { /* ... */ }

  //! Evaluate the Compton profile
  virtual ProfileQuantity evaluate( const MomentumQuantity momentum ) const = 0;

  //! Sample from the Compton profile
  virtual MomentumQuantity sample() const = 0;

  //! Sample from the Compton profile in a subrange
  virtual MomentumQuantity sampleInSubrange( const MomentumQuantity momentum ) const = 0;

  //! Return the lower bound of the momentum
  virtual MomentumQuantity getLowerBoundOfMomentum() const = 0;

  //! Return the upper bound of the momentum
  virtual MomentumQuantity getUpperBoundOfMomentum() const = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COMPTON_PROFILE_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ComptonProfile.hpp
//---------------------------------------------------------------------------//
