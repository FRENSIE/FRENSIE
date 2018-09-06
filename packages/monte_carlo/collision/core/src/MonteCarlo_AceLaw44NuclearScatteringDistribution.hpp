//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AceLaw44NuclearScatteringDistribution.hpp
//! \author Alex Bennett, Alex Robinson
//! \brief  The law 44 scattering distribution class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_44_NUCLEAR_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ACE_LAW_44_NUCLEAR_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "MonteCarlo_AceLaw44ARDistribution.hpp"
#include "MonteCarlo_LabSystemConversionPolicy.hpp"
#include "Utility_DesignByContract.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

/*! The law 44 scattering energy distribution class (Ace Law 44)
 * \details The system conversion policy will convert the sampled energy and
 * scattering angle cosine from the current system to the lab system.
 * \ingroup ace_laws
 */
template<typename IncomingParticleType,
	 typename OutgoingParticleType,
	 typename SystemConversionPolicy = LabSystemConversionPolicy>
class AceLaw44NuclearScatteringDistribution : public NuclearScatteringDistribution<IncomingParticleType,OutgoingParticleType>
{

public:

  //! Typedef for the distribution
  typedef std::vector<std::shared_ptr<const AceLaw44ARDistribution> >
  ARDistributions;

  //! Constructor
  AceLaw44NuclearScatteringDistribution(
             const double atomic_weight_ratio,
             const std::shared_ptr<const NuclearScatteringEnergyDistribution>&
             energy_scattering_distribution,
             const ARDistributions& ar_distributions );

  //! Destructor
  ~AceLaw44NuclearScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the particle
  void scatterParticle( const IncomingParticleType& incoming_particle,
			OutgoingParticleType& outgoing_particle,
			const double temperature ) const override;

private:

  // The energy distribution (only a law 4 distribution should be stored)
  std::shared_ptr<const NuclearScatteringEnergyDistribution>
  d_energy_scattering_distribution;

  // The AR distributions
  ARDistributions d_ar_distributions;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AceLaw44NuclearScatteringDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ACE_LAW_44_NUCLEAR_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw44NuclearScatteringDistribution.hpp
//---------------------------------------------------------------------------//

