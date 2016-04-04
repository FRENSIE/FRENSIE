//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The complete Doppler broadened photon energy distribution decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp"

namespace MonteCarlo{

//! The complete (all subshells) Doppler broadened photon energy dist. class
class CompleteDopplerBroadenedPhotonEnergyDistribution : public DopplerBroadenedPhotonEnergyDistribution
{

public:

  //! Constructor
  CompleteDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Destructor
  virtual ~CompleteDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Check if the distribution is complete (all subshells)
  bool isComplete() const;

  //! Check if the subshell is valid
  virtual bool isValidSubshell( const SubshellType subshell ) const = 0;

  //! Return the binding energy of a subshell
  virtual double getSubshellBindingEnergy( 
                                       const SubshellType subshell ) const = 0;

  //! Return the occupancy of a subshell (default is the ENDF occupacy)
  virtual double getSubshellOccupancy( const SubshellType subshell ) const = 0;

  //! Evaluate the subshell distribution
  virtual double evaluateSubshell( const double incoming_energy,
                                   const double outgoing_energy,
                                   const double scattering_angle_cosine,
                                   const SubshellType subshell ) const = 0;

  //! Evaluate the PDF
  virtual double evaluateSubshellPDF( const double incoming_energy,
                                      const double outgoing_energy,
                                      const double scattering_angle_cosine,
                                      const SubshellType subshell ) const = 0;

  //! Evaluate the integrated cross section (b/mu)
  virtual double evaluateSubshellIntegratedCrossSection( 
				          const double incoming_energy,
					  const double scattering_angle_cosine,
					  const SubshellType subshell,
					  const double precision ) const = 0;

  //! Sample an electron momentum from the subshell distribution
  virtual double sampleSubshellMomentum( 
                                       const double incoming_energy,
                                       const double scattering_angle_cosine,
                                       const SubshellType subshell ) const = 0;
};

// Check if the distribution is complete (all subshells)
inline bool CompleteDopplerBroadenedPhotonEnergyDistribution::isComplete() const
{
  return true;
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
