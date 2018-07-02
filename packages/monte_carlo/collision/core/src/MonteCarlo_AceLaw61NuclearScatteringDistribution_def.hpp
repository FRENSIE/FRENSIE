//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw61NuclearScatteringDistribution_def.hpp
//! \author Eli Moll
//! \brief  The law 61 scattering distribution class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_61_NUCLEAR_SCATTERING_DISTRIBUTION_DEF_HPP
#define MONTE_CARLO_ACE_LAW_61_NUCLEAR_SCATTERING_DISTRIBUTION_DEF_HPP

// Std Lib Includes
#include <math.h>

// FRENSIE Includes
#include "MonteCarlo_AceLaw61NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "Utility_3DCartesianVectorHelpers.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
template<typename IncomingParticleType,
         typename OutgoingParticleType,
         typename SystemConversionPolicy>
AceLaw61NuclearScatteringDistribution<
              IncomingParticleType,
              OutgoingParticleType,
              SystemConversionPolicy>::AceLaw61NuclearScatteringDistribution( 
              const double atomic_weight_ratio,
              const std::shared_ptr<const NuclearScatteringEnergyDistribution>&
              energy_scattering_distribution,
              const AngleDistributions& angle_distributions )
  : NuclearScatteringDistribution<IncomingParticleType,OutgoingParticleType>( atomic_weight_ratio ),
     d_energy_scattering_distribution( energy_scattering_distribution ),
     d_angle_distributions( angle_distributions )
{
  // Make sure the energy distribution pointer is valid
  testPrecondition(  energy_scattering_distribution.get() );
}

// Randomly scatter the particle
template<typename IncomingParticleType,
         typename OutgoingParticleType,
         typename SystemConversionPolicy>
void AceLaw61NuclearScatteringDistribution<IncomingParticleType,
					   OutgoingParticleType,
					   SystemConversionPolicy>::scatterParticle(
				const IncomingParticleType& incoming_particle,
                                OutgoingParticleType& outgoing_particle,
				const double temperature ) const
{
  size_t outgoing_bin_index, incoming_bin_index;
  
  double energy_prime;
  
  // Sample the energy of the outgoing particle
  double outgoing_sys_energy = d_energy_scattering_distribution->sampleEnergy(
    incoming_particle.getEnergy(),
    incoming_bin_index,
    outgoing_bin_index,
    energy_prime );
    
  double sys_scattering_angle_cosine = d_angle_distributions[incoming_bin_index]->sampleCoupledAngle(
    outgoing_bin_index,
    energy_prime );
  
  // convert the outgoing energy from this system to the lab system
  double outgoing_energy = 
    SystemConversionPolicy::convertToLabEnergy( incoming_particle.getEnergy(),
						outgoing_sys_energy,
						sys_scattering_angle_cosine,
						this->getAtomicWeightRatio() );

  // convert the scattering angle cosine from this system to the lab system
  double scattering_angle_cosine = 
    SystemConversionPolicy::convertToLabAngleCosine( 
						incoming_particle.getEnergy(),
						outgoing_sys_energy,
						outgoing_energy,
						sys_scattering_angle_cosine,
						this->getAtomicWeightRatio() );

  // Rotate the direction through the sampled angles
  outgoing_particle.rotateDirection( scattering_angle_cosine,
				     this->sampleAzimuthalAngle() );

  // Set the new energy
  outgoing_particle.setEnergy( outgoing_energy );
}

class NeutronState;
class PhotonState;

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AceLaw61NuclearScatteringDistribution<NeutronState,NeutronState,CMSystemConversionPolicy> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AceLaw61NuclearScatteringDistribution<NeutronState,NeutronState,LabSystemConversionPolicy> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AceLaw61NuclearScatteringDistribution<NeutronState,PhotonState,CMSystemConversionPolicy> );
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AceLaw61NuclearScatteringDistribution<NeutronState,PhotonState,LabSystemConversionPolicy> );

EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( AceLaw61NuclearScatteringDistribution<PhotonState,NeutronState,LabSystemConversionPolicy> );
  
} // End MonteCarlo namespace

#endif // end MONTE_CARLO_ACE_LAW_61_NUCLEAR_SCATTERING_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw61NuclearScatteringDistribution_def.hpp
//---------------------------------------------------------------------------//
