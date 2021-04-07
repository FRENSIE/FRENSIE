//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw61AngleDistribution.hpp
//! \author Eli Moll
//! \brief  The law 61 angle distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_61_ANGLE_DISTRIBUTION_HPP
#define MONTE_CARLO_ACE_LAW_61_ANGLE_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_Vector.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

/*! The law 61 angle distribution base class
 * \ingroup ace_laws
 */
class AceLaw61AngleDistribution
{

public: 

  //! Constructor
  AceLaw61AngleDistribution( 
    const Utility::ArrayView<const double>& outgoing_energy_grid,
    const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
    cosine_distributions );
    
  //! Destructor
  virtual ~AceLaw61AngleDistribution()
  { /* ... */ }
  
  //! Sample the coupled outgoing angle from the distribution
  virtual double sampleCoupledAngle( const unsigned outgoing_index,
                                     const double energy_prime ) const = 0;
              
protected:

  //! Return the outgoing energy grid
  double getOutgoingEnergyGridPoint( const unsigned outgoing_index ) const;

  // The outgoing energy grid
  std::vector<double> d_outgoing_energy_grid;
  
  // The array of cosine distributions
  std::vector<std::shared_ptr<const Utility::UnivariateDistribution> > d_cosine_distributions;

};

// Return the outgoing energy grid point
inline double AceLaw61AngleDistribution::getOutgoingEnergyGridPoint(
                const unsigned outgoing_index ) const
{
  // Make sure the outgoing index is valid
  testPrecondition( outgoing_index < d_outgoing_energy_grid.size() );
  
  return d_outgoing_energy_grid[ outgoing_index ];
}          

} // end MonteCarlo namespace

#endif // MONTE_CARLO_ACE_LAW_61_ANGLE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw61AngleDistribution.cpp
//---------------------------------------------------------------------------//
