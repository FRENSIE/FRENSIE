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

  //! Constructor
  KleinNishinaAdjointPhotonScatteringDistribution( const double max_energy );

  //! Destructor
  ~KleinNishinaAdjointPhotonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double max_energy,
		   const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (cm^2)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double max_energy,
					 const double precision ) const;
  
  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
	       double& outgoing_energy,
	       double& scattering_angle_cosine ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      double& outgoing_energy,
			      double& scattering_angle_cosine,
			      unsigned& trials ) const;

  //! Randomly scatter the photon and return the shell that was interacted with
  void scatterAdjointPhoton( AdjointPhotonState& adjoint_photon,
			     ParticleBank& bank,
			     SubshellType& shell_of_interaction ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_KLEIN_NISHINA_ADJOINT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_KleinNishinaAdjointPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
