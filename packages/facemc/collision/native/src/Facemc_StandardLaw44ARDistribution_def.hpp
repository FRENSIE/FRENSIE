//---------------------------------------------------------------------------//
//!
//! \file   Facemc_StandardLaw44ARDistribution_def.hpp
//! \author Alex Robinson
//! \brief  The standard law 44 AR distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_STANDARD_LAW_44_AR_DISTRIBUTION_DEF_HPP
#define FACEMC_STANDARD_LAW_44_AR_DISTRIBUTION_DEF_HPP

namespace Facemc{

// Constructor
template<typename Law44InterpolationPolicy>
StandardLaw44ARDistribution<Law44InterpolationPolicy>::StandardLaw44ARDistribution( 
		   const Teuchos::ArrayRCP<const double>& outgoing_energy_grid,
		   const Teuchos::ArrayView<const double>& A_array,
		   const Teuchos::ArrayView<const double>& R_array )
  : Law44ARDistribution( outgoing_energy_grid, A_array, R_array )
{ /* ... */ }

// Sample A and R from the distribution
template<typename Law44InterpolationPolicy>
void StandardLaw44ARDistribution<Law44InterpolationPolicy>:sampleAR( 
						const unsigned outgoing_index,
						const double energy_prime,
						double& sampled_A,
						double& sampled_R ) const
{
  sampled_A = Law44InterpolationPolicy::interpolate( 
			     energy_prime,
			     getOutgoingEnergyGridPoint( outgoing_index ),
			     getOutgoingEnergyGridPoint( outgoing_index + 1u ),
			     getAValue( outgoing_index ),
			     getAValue( outgoing_index + 1u ) );

  sampled_R = Law44InterpolationPolicy::interpolate(
			     energy_prime,
			     getOutgoingEnergyGridPoint( outgoing_index ),
			     getOutgoingEnergyGridPoint( outgoing_index + 1u ),
			     getRValue( outgoing_index ),
			     getRValue( outgoing_index + 1u ) );
}

} // end Facemc namespace

#endif // end FACEMC_STANDARD_LAW_44_AR_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Facemc_StandardLaw44ARDistribution_def.hpp
//---------------------------------------------------------------------------//
