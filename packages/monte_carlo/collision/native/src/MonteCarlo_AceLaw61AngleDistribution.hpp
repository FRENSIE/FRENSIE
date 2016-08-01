//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw61AngleDistribution.hpp
//! \author Eli Moll
//! \brief  The law 61 angle distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_61_ANGLE_DISTRIBUTION_HPP
#define MONTE_CARLO_ACE_LAW_61_ANGLE_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

/*! The law 61 angle distribution base class
 * \ingroup ace_laws
 */
class AceLaw61AngleDistribution
{

public: 

  //! Constructor
  AceLaw61AngleDistribution( 
    const Teuchos::ArrayView<const double>& outgoing_energy_grid,
    const Teuchos::Array<Teuchos::RCP<Utility::OneDDistribution> >& cosine_distributions );
    
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
  Teuchos::Array<double> d_outgoing_energy_grid;
  
  // The array of cosine distributions
  Teuchos::Array<Teuchos::RCP<Utility::OneDDistribution> > d_cosine_distributions;

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
