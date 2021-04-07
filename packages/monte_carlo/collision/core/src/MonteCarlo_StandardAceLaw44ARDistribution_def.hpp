//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardAceLaw44ARDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The standard law 44 AR distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ACE_LAW_44_AR_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_STANDARD_ACE_LAW_44_AR_DISTRIBUTION_DEF_HPP

// FRENSIE Includes
#include "MonteCarlo_StandardAceLaw44ARDistribution.hpp"

namespace MonteCarlo{

// Constructor
template<typename AceLaw44InterpolationPolicy>
StandardAceLaw44ARDistribution<AceLaw44InterpolationPolicy>::StandardAceLaw44ARDistribution(
                               const std::vector<double>& outgoing_energy_grid,
                               const std::vector<double>& A_array,
                               const std::vector<double>& R_array )
  : StandardAceLaw44ARDistribution( Utility::arrayViewOfConst( outgoing_energy_grid ),
                                    Utility::arrayViewOfConst( A_array ),
                                    Utility::arrayViewOfConst( R_array ) )
{ /* ... */ }
               
// View constructor
template<typename AceLaw44InterpolationPolicy>
StandardAceLaw44ARDistribution<AceLaw44InterpolationPolicy>::StandardAceLaw44ARDistribution(
		  const Utility::ArrayView<const double>& outgoing_energy_grid,
                  const Utility::ArrayView<const double>& A_array,
                  const Utility::ArrayView<const double>& R_array )
  : AceLaw44ARDistribution( outgoing_energy_grid, A_array, R_array )
{ /* ... */ }

// Sample A and R from the distribution
template<typename AceLaw44InterpolationPolicy>
void StandardAceLaw44ARDistribution<AceLaw44InterpolationPolicy>::sampleAR(
						const unsigned outgoing_index,
						const double energy_prime,
						double& sampled_A,
						double& sampled_R ) const
{
  sampled_A = AceLaw44InterpolationPolicy::interpolate(
			     energy_prime,
			     getOutgoingEnergyGridPoint( outgoing_index ),
			     getOutgoingEnergyGridPoint( outgoing_index + 1u ),
			     getAValue( outgoing_index ),
			     getAValue( outgoing_index + 1u ) );

  sampled_R = AceLaw44InterpolationPolicy::interpolate(
			     energy_prime,
			     getOutgoingEnergyGridPoint( outgoing_index ),
			     getOutgoingEnergyGridPoint( outgoing_index + 1u ),
			     getRValue( outgoing_index ),
			     getRValue( outgoing_index + 1u ) );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_ACE_LAW_44_AR_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardAceLaw44ARDistribution_def.hpp
//---------------------------------------------------------------------------//
