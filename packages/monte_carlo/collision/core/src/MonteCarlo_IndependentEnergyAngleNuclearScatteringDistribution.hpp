//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_IndependentEnergyAngleNuclearScatteringDistribution.hpp
//! \author Alex Robinson, Alex Bennett
//! \brief  The independent energy-angle scattering distribution class decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INDEPENDENT_ENERGY_ANGLE_NUCLEAR_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_INDEPENDENT_ENERGY_ANGLE_NUCLEAR_SCATTERING_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NuclearScatteringAngularDistribution.hpp"
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "MonteCarlo_LabSystemConversionPolicy.hpp"

namespace MonteCarlo{

//! The independent energy angle nuclear scattering distribution class
/*! \detials The system conversion policy will convert the sampled energy and
 * scattering angle cosine from the current system to the lab system.
 */
template<typename IncomingParticleType,
	 typename OutgoingParticleType,
	 typename SystemConversionPolicy = LabSystemConversionPolicy>
class IndependentEnergyAngleNuclearScatteringDistribution : public NuclearScatteringDistribution<IncomingParticleType,OutgoingParticleType>
{

public:

  //! Constructor
  IndependentEnergyAngleNuclearScatteringDistribution(
             const double atomic_weight_ratio,
             const std::shared_ptr<const NuclearScatteringEnergyDistribution>&
             energy_scattering_distribution,
             const std::shared_ptr<const NuclearScatteringAngularDistribution>&
             angular_scattering_distribution );

  //! Destructor
  ~IndependentEnergyAngleNuclearScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the particle
  void scatterParticle( const IncomingParticleType& incoming_particle,
			OutgoingParticleType& outgoing_particle,
			const double temperature ) const override;

private:

  // The energy scattering distribution
  std::shared_ptr<const NuclearScatteringEnergyDistribution>
  d_energy_scattering_distribution;

  // The angular scattering distribution
  std::shared_ptr<const NuclearScatteringAngularDistribution>
  d_angular_scattering_distribution;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_IndependentEnergyAngleNuclearScatteringDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif//end MONTE_CARLO_INDEPENDENT_ENERGY_ANGLE_NUCLEAR_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IndependentEnergyAngleNuclearScatteringDistribution.hpp
//---------------------------------------------------------------------------//
