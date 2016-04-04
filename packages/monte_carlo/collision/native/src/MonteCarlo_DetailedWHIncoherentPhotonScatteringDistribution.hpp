//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DetailedWHIncoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The detailed Waller-Hartree incoherent photon scat. dist. decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DETAILED_WH_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_DETAILED_WH_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Boost Includes
#include <boost/scoped_ptr.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_WHIncoherentPhotonScatteringDistribution.hpp"
#include "Utility_TabularDistribution.hpp"

namespace MonteCarlo{

/*! The detailed Waller-Hartree incoherent photon scattering distribution class
 * \details This class will sample an interaction subshell for atomic 
 * relaxation even though the Waller-Hartree model doesn't directly provide
 * that information. The subshell occupancies are used instead of the
 * more accurate subshell incoherent cross sections.
 */
class DetailedWHIncoherentPhotonScatteringDistribution : public WHIncoherentPhotonScatteringDistribution
{

public:

  //! Constructor
  DetailedWHIncoherentPhotonScatteringDistribution(
	  const std::shared_ptr<const ScatteringFunction>& scattering_function,
	  const Teuchos::Array<double>& subshell_occupancies,
	  const Teuchos::Array<SubshellType>& subshell_order,
	  const double kahn_sampling_cutoff_energy = 3.0 );

  //! Destructor
  ~DetailedWHIncoherentPhotonScatteringDistribution()
  { /* ... */ }

  //! Randomly scatter the photon and return the shell that was interacted with
  void scatterPhoton( PhotonState& photon,
		      ParticleBank& bank,
		      SubshellType& shell_of_interaction ) const;

private:

  //! Sample the subshell that is interacted with
  void sampleInteractionSubshell( SubshellType& shell_of_interaction ) const;

  // The shell interaction probabilities
  boost::scoped_ptr<const Utility::TabularOneDDistribution>
  d_subshell_occupancy_distribution;

  // The subshell ordering
  Teuchos::Array<SubshellType> d_subshell_order;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DETAILED_WH_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DetailedWHIncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//

