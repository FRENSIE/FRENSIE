//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//! \author Alex Robinson
//! \brief  The complete Doppler broadened photon energy distribution decl.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP
#define MONTE_CARLO_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/scoped_ptr.hpp>
#include <boost/bimap.hpp>

// FRENSIE Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp"

namespace MonteCarlo{

//! The complete (all subshells) Doppler broadened photon energy dist. class
class CompleteDopplerBroadenedPhotonEnergyDistribution : public DopplerBroadenedPhotonEnergyDistribution
{

public:

  //! Constructor
  CompleteDopplerBroadenedPhotonEnergyDistribution();

  //! Destructor
  virtual ~CompleteDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Check if the distribution is complete (all subshells)
  bool isComplete() const;

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

  //! Evaluate the integrated cross section (b/mu)
  virtual double evaluateSubshellIntegratedCrossSection( 
				          const double incoming_energy,
					  const double scattering_angle_cosine,
					  const SubshellType subshell,
					  const double precision ) const = 0;
};

} // end MonteCarlo namespace

// Check if the distribution is complete (all subshells)
inline bool CompleteDopplerBroadenedPhotonEnergyDistribution::isComplete() const
{
  return true;
}

#endif // end MONTE_CARLO_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
