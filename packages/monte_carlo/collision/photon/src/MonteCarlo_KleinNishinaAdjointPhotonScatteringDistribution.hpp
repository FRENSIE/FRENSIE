//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_KleinNishinaAdjointPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The Klein-Nishina adjoint photon scattering distribution decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_KLEIN_NISHINA_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_KLEIN_NISHINA_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The Klein-Nishina adjoint photon scattering distribution class
class KleinNishinaAdjointPhotonScatteringDistribution : public IncoherentAdjointPhotonScatteringDistribution
{

public:

  //! The trials counter type
  typedef IncoherentAdjointPhotonScatteringDistribution::Counter Counter;

  //! Constructor
  KleinNishinaAdjointPhotonScatteringDistribution(
              const double max_energy,
              const AdjointKleinNishinaSamplingType sampling_type =
              TWO_BRANCH_REJECTION_ADJOINT_KN_SAMPLING );

  //! Destructor
  ~KleinNishinaAdjointPhotonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double max_energy,
		   const double scattering_angle_cosine ) const override;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
	       double& outgoing_energy,
	       double& scattering_angle_cosine ) const override;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      double& outgoing_energy,
			      double& scattering_angle_cosine,
			      Counter& trials ) const override;

  //! Randomly scatter the photon and return the shell that was interacted with
  void scatterAdjointPhoton( AdjointPhotonState& adjoint_photon,
			     ParticleBank& bank,
			     Data::SubshellType& shell_of_interaction ) const override;

protected:

  //! Evaluate the integrated cross section (b)
  double evaluateIntegratedCrossSectionImpl( const double incoming_energy,
                                             const double max_energy,
                                             const double precision ) const override;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_KLEIN_NISHINA_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_KleinNishinaAdjointPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
