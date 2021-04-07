//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardAceLaw61AngleDistribution.hpp
//! \author Eli Moll
//! \brief  The standard law 61 angle distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ACE_LAW_61_ANGLE_DISTRIBUTION_HPP
#define MONTE_CARLO_STANDARD_ACE_LAW_61_ANGLE_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AceLaw61AngleDistribution.hpp"

namespace MonteCarlo{

/*! The standard law 61 angle distribution base class
 * \ingroup ace_laws
 */
template<typename AceLaw61InterpolationPolicy>
class StandardAceLaw61AngleDistribution : public AceLaw61AngleDistribution
{

public: 

  //! Constructor
  StandardAceLaw61AngleDistribution( 
    const Utility::ArrayView<const double>& outgoing_energy_grid,
    const std::vector<std::shared_ptr<const Utility::UnivariateDistribution> >&
    cosine_distributions );
    
  //! Destructor
  virtual ~StandardAceLaw61AngleDistribution()
  { /* ... */ }
  
  //! Sample the coupled outgoing angle from the distribution
  double sampleCoupledAngle( const unsigned outgoing_index,
                             const double energy_prime ) const override;
              
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardAceLaw61AngleDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_ACE_LAW_61_Angle_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardAceLaw61AngleDistribution.hpp
//---------------------------------------------------------------------------//
