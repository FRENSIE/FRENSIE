//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_DopplerBroadenedComptonLineEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The Doppler broadened Compton line energy distribution base class
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_DOPPLER_BROADENED_COMPTON_LINE_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_DOPPLER_BROADENED_COMPTON_LINE_ENERGY_DISTRIBUTION_HPP

namespace MonteCarlo{

//! The Doppler broadened Compton line energy distribution base class
class DopplerBroadenedComptonLineEnergyDistribution
{

public:

  //! Constructor
  DopplerBroadenedComptonLineEnergyDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~DopplerBroadenedComptonLineEnergyDistribution()
  { /* ... */ }

  //! Sample an outgoing energy from the differential distribution
  virtual double sampleDopplerBroadenedComptonLineEnergy( 
				const double incoming_energy,
				const double scattering_angle_cosine,
				SubshellType& shell_of_interaction ) const = 0;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_DOPPLER_BROADENED_COMPTON_LINE_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_DopplerBroadenedComptonLineEnergyDistribution.hpp
//---------------------------------------------------------------------------//
