//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_AceLaw61NuclearScatteringDistribution.hpp
//! \author Eli Moll
//! \brief  The law 61 scattering distribution class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ACE_LAW_61_NUCLEAR_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_ACE_LAW_61_NUCLEAR_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistribution.hpp"
#include "MonteCarlo_NuclearScatteringEnergyDistribution.hpp"
#include "MonteCarlo_AceLaw61AngleDistribution.hpp"
#include "MonteCarlo_LabSystemConversionPolicy.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

/*! The law 61 scattering energy distribution class (Ace Law 61)
 * \details The system conversion policy will convert the sampled energy and
 * scattering angle cosine from the current system to the lab system.
 * \ingroup ace_laws
 */
template<typename IncomingParticleType,
	 typename OutgoingParticleType,
	 typename SystemConversionPolicy = LabSystemConversionPolicy>
class AceLaw61NuclearScatteringDistribution : public NuclearScatteringDistribution<IncomingParticleType,OutgoingParticleType>
{

public:

  //! Typedef for the distribution
  typedef std::vector<std::shared_ptr<const AceLaw61AngleDistribution> > 
  AngleDistributions;
 
  //! Constructor
  AceLaw61NuclearScatteringDistribution( 
              const double atomic_weight_ratio,
              const std::shared_ptr<const NuclearScatteringEnergyDistribution>&
              energy_scattering_distribution,
              const AngleDistributions& angle_distributions );
                                              
  //! Destructor
  ~AceLaw61NuclearScatteringDistribution()
  { /* ... */ }
  
  //! Randomly scatter the particle
  void scatterParticle( const IncomingParticleType& incoming_particle,
                        OutgoingParticleType& outgoing_particle,
                        const double temperature ) const override;

private:

  // The energy distribution (only a law 4 distribution should be stored)
  std::shared_ptr<const NuclearScatteringEnergyDistribution> 
  d_energy_scattering_distribution;

  // The angle distributions
  AngleDistributions d_angle_distributions;
  
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_AceLaw61NuclearScatteringDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_ACE_LAW_61_NUCLEAR_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AceLaw61NuclearScatteringDistribution.hpp
//---------------------------------------------------------------------------//

