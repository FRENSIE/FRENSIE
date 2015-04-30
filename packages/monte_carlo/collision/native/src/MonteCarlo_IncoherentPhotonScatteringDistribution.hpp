//---------------------------------------------------------------------------//
//! 
//! \file   MonteCarlo_IncoherentPhotonScatteringDistribution.hpp
//! \author Alex Robinson
//! \brief  The incoherent photon scattering distribution declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP
#define MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

// Boost Includes
#include <boost/function.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ArrayView.hpp>

// FRENSIE Includes
#include "MonteCarlo_KleinNishinaPhotonScatteringDistribution.hpp"
#include "MonteCarlo_ComptonProfileSubshellConverter.hpp"
#include "Utility_TabularOneDDistribution.hpp"

namespace MonteCarlo{

//! The incoherent photon scattering distribution class
class IncoherentPhotonScatteringDistribution : public KleinNishinaPhotonScatteringDistribution
{

public:

  //! The electron momentum distribution array (Compton Profiles)
  typedef Teuchos::Array<Teuchos::RCP<const Utility::TabularOneDDistribution> >
  ElectronMomentumDistArray;
  
  //! Constructor without Doppler broadening
  IncoherentPhotonScatteringDistribution(
    const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function );

  //! Constructor for Doppler broadening
  IncoherentPhotonScatteringDistribution( 
     const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function,
     const Teuchos::Array<double>& subshell_binding_energies,
     const Teuchos::Array<double>& subshell_occupancies,
     const Teuchos::Array<SubshellType>& subshell_order,
     const Teuchos::RCP<ComptonProfileSubshellConverter>& subshell_converter,
     const ElectronMomentumDistArray& electron_momentum_dist_array );

  //! Destructor
  ~IncoherentPhotonScatteringDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  double evaluate( const double incoming_energy,
		   const double scattering_angle_cosine ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double incoming_energy,
		      const double scattering_angle_cosine ) const;

  //! Evaluate the integrated cross section (cm^2)
  double evaluateIntegratedCrossSection( const double incoming_energy,
					 const double precision ) const;

  //! Sample an outgoing energy and direction from the distribution
  void sample( const double incoming_energy,
	       double& outgoing_energy,
	       double& scattering_angle_cosine,
	       SubshellType& shell_of_interaction ) const;

  //! Sample an outgoing energy and direction and record the number of trials
  void sampleAndRecordTrials( const double incoming_energy,
			      double& outgoing_energy,
			      double& scattering_angle_cosine,
			      SubshellType& shell_of_interaction,
			      unsigned& trials ) const;

  //! Randomly scatter the photon
  void scatterPhoton( PhotonState& photon,
		      ParticleBank& bank,
		      SubshellType& shell_of_interaction ) const;

protected:
  
  //! Evaluate the scattering function
  double evaluateScatteringFunction( 
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const;

private:

  // Ignore Doppler broadening
  double returnComptonLine( const double initial_energy,
			    const double compton_line_energy,
			    const double scattering_angle_cosine,
			    SubshellType& shell_of_interaction ) const;

  // Doppler broaden a compton line
  double dopplerBroadenComptonLine( const double initial_energy, 
				    const double compton_line_energy,
				    const double scattering_angle_cosine,
				    SubshellType& shell_of_interaction ) const;

  // Doppler broaden a compton line using the old method
  double dopplerBroadenComptonLineOld( 
				    const double initial_energy, 
				    const double compton_line_energy,
				    const double scattering_angle_cosine,
				    SubshellType& shell_of_interaction ) const;

  // The scattering function
  Teuchos::RCP<const Utility::OneDDistribution> d_scattering_function;

  // The binding energy and shell interaction probabilities
  Teuchos::RCP<const Utility::TabularOneDDistribution> 
  d_subshell_occupancy_distribution;

  // The subshell binding energy
  Teuchos::Array<double> d_subshell_binding_energy;

  // The subshell ordering
  Teuchos::Array<SubshellType> d_subshell_order;

  // The Compton profile subshell converter
  Teuchos::RCP<ComptonProfileSubshellConverter> d_subshell_converter;

  // The electron momentum dist array
  // Note: Every electron shell should have a momentum distribution array
  ElectronMomentumDistArray d_electron_momentum_distribution;

  // The Doppler broadening function pointer
  boost::function<double (double, double, double, SubshellType&)> 
  d_doppler_broadening_func;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_INCOHERENT_PHOTON_SCATTERING_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentPhotonScatteringDistribution.hpp
//---------------------------------------------------------------------------//
