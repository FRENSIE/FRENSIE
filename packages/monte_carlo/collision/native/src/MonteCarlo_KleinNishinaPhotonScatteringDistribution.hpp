//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_KleinNishinaPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The Klein-Nishina photon scattering distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_KLEIN_NISHINA_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_KLEIN_NISHINA_PHOTON_SCATTERING_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_IncoherentPhotonScatteringDistribution.hpp"

namespace MonteCarlo{

//! The Klein-Nishina photon scattering distribution class
class KleinNishinaPhotonScatteringDistribution : public IncoherentPhotonScatteringDistribution
{

public:
  
  //! Default Constructor
  KleinNishinaPhotonScatteringDistribution();

  //! Constructor
  KleinNishinaPhotonScatteringDistribution( 
				    const double kahn_sampling_cutoff_energy );

  //! Destructor
  virtual ~KleinNishinaPhotonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the integrated cross section (cm^2)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double precision ) const;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_KLEIN_NISHINA_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_KleinNishinaPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
