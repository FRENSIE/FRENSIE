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

// FRENSIE Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "MonteCarlo_DopplerBroadenedPhotonEnergyDistribution.hpp"
#include "MonteCarlo_SubshellType.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The complete (all subshells) Doppler broadened photon energy dist. class
class CompleteDopplerBroadenedPhotonEnergyDistribution : public DopplerBroadenedPhotonEnergyDistribution
{

public:

  //! Constructor
  CompleteDopplerBroadenedPhotonEnergyDistribution(
		  const Teuchos::Array<double>& endf_subshell_occupancies,
                  const Teuchos::Array<SubshellType>& endf_subshell_order,
                  const std::shared_ptr<const ComptonProfileSubshellConverter>&
                  subshell_converter );

  //! Destructor
  virtual ~CompleteDopplerBroadenedPhotonEnergyDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double outgoing_energy,
		   const double scattering_angle_cosine ) const;

  //! Evaluate the subshell distribution
  double evaluateSubshell( const double incoming_energy,
                           const double outgoing_energy,
                           const double scattering_angle_cosine,
                           const SubshellType subshell ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
		      const double outgoing_energy,
		      const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  double evaluateSubshellPDF( const double incoming_energy,
                              const double outgoing_energy,
                              const double scattering_angle_cosine,
                              const SubshellType subshell ) const;

  //! Evaluate the integrated cross section (b/mu)
  double evaluateSubshellIntegratedCrossSection( 
				          const double incoming_energy,
					  const double scattering_angle_cosine,
					  const SubshellType subshell,
					  const double precision ) const;

  //! Evaluate the integrated cross section (b/mu)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double scattering_angle_cosine,
					 const double precision ) const;

  //! Evaluate the integrated cross section (b/mu)
  double evaluateSubshellIntegratedCrossSection( 
				          const double incoming_energy,
					  const double scattering_angle_cosine,
					  const SubshellType subshell,
					  const double precision ) const;

protected:

  //! Evaluate the subshell distribution
  virtual double evaluateSubshell( const double incoming_energy,
                                   const double outgoing_energy,
                                   const double scattering_angle_cosine,
                                   const unsigned subshell_index ) const = 0;
  
  //! Return the subshell converter
  const ComptonProfileSubshellConverter& getSubshellConverter() const;
  
  //! Sample an ENDF subshell
  void sampleENDFInteractionSubshell( SubshellType& shell_of_interaction,
				      unsigned& shell_index ) const;

private:

  // The ENDF subshell interaction probabilities
  boost::scoped_ptr<const Utility::TabularOneDDistribution>
  d_endf_subshell_occupancy_distribution;

  // The ENDF subshell order
  Teuchos::Array<SubshellType> d_endf_subshell_order;

  // The Compton profile subshell converter
  std::shared_ptr<const ComptonProfileSubshellConverter> d_subshell_converter;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COMPLETE_DOPPLER_BROADENED_PHOTON_ENERGY_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CompleteDopplerBroadenedPhotonEnergyDistribution.hpp
//---------------------------------------------------------------------------//
