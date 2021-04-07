//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardAceLaw44ARDistribution.hpp
//! \author Alex Robinson
//! \brief  The standard law 44 AR distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ACE_LAW_44_AR_DISTRIBUTION_HPP
#define MONTE_CARLO_STANDARD_ACE_LAW_44_AR_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_AceLaw44ARDistribution.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! The standard law 44 AR distribution base class
 * \ingroup ace_laws
 */
template<typename AceLaw44InterpolationPolicy>
class StandardAceLaw44ARDistribution : public AceLaw44ARDistribution
{

public:

  //! Constructor
  StandardAceLaw44ARDistribution(
                               const std::vector<double>& outgoing_energy_grid,
                               const std::vector<double>& A_array,
                               const std::vector<double>& R_array );

  //! View constructor
  StandardAceLaw44ARDistribution(
		  const Utility::ArrayView<const double>& outgoing_energy_grid,
                  const Utility::ArrayView<const double>& A_array,
                  const Utility::ArrayView<const double>& R_array );

  //! Destructor
  ~StandardAceLaw44ARDistribution()
  { /* ... */ }

  //! Sample A and R from the distribution
  void sampleAR( const unsigned outgoing_index,
		 const double energy_prime,
		 double& sampled_A,
		 double& sampled_R ) const override;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardAceLaw44ARDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_ACE_LAW_44_AR_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardAceLaw44ARDistribution.hpp
//---------------------------------------------------------------------------//
