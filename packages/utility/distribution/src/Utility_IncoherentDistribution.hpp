//---------------------------------------------------------------------------//
//!
//! \file   Utility_IncoherentDistribution.hpp
//! \author Alex Robinson
//! \brief  Incoherent photon scattering distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INCOHERENT_DISTRIBUTION_HPP
#define UTILITY_INCOHERENT_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "Utility_KleinNishinaDistribution.hpp"

namespace Utility{

/*! The incoherent photon scattering distribution class
 * \details The incoherent photon scattering distribution class is a 
 * function of two coupled variables: the outgoing photon energy and the
 * outgoing photon scattering angle. Because of the one-to-one 
 * correspondence between the two variables, the function can be reduced to a
 * function of a single variable - the inverse energy loss ratio
 * (x = 1 + alpha*(1-mu)). This variable x will be sampled from the
 * distribution. Note: The scattering function independent values must be
 * in units of 1/cm and not 1/Angstrom. 
 */
class IncoherentDistribution : public KleinNishinaDistribution
{

public:

  //! Calculate the scattering angle cosine
  static double calculateScatteringAngleCosine( 
				      const double initial_unitless_energy,
			              const double inverse_energy_loss_ratio );
  
  //! Calculate the outgoing energy
  static double calculateOutgoingEnergy( 
				      const double initial_unitless_energy,
				      const double inverse_energy_loss_ratio );
  
  //! Default constructor
  IncoherentDistribution();

  //! Constructor
  IncoherentDistribution( 
	       const Teuchos::RCP<const OneDDistribution>& scattering_function,
	       const double energy,
	       const bool use_kahn_sampling_only = false,
	       const bool use_exact_integrated_cross_sec = true );

  //! Copy constructor
  IncoherentDistribution( const IncoherentDistribution& dist_instance );

  //! Assignment operator
  IncoherentDistribution& operator=( 
				 const IncoherentDistribution& dist_instance );
				    
  //! Destructor
  ~IncoherentDistribution()
  { /* ... */ }

  //! Set the energy (MeV)
  void setEnergy( const double energy );

  //! Return the integrated cross section
  double getIntegratedCrossSection() const;

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const;

  //! Return a sample from the distribution
  double sample() const;

  //! Return a random sample and record the number of trials
  double sampleAndRecordTrials( unsigned& trials ) const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

private:

  // Calculate the inverse wavelength (modifies cached value)
  void calculateInverseWavelength();

  // Calculate the scattering angle cosine
  double calculateScatteringAngleCosine( 
				const double inverse_energy_loss_ratio ) const;

  // Calculate the scattering function argument
  double calculateScatteringFunctionArgument(
				const double inverse_energy_loss_ratio ) const;

  // Calculate the scattering function value
  double calculateScatteringFunctionValue(
				const double inverse_energy_loss_ratio ) const;

  // Evaluate the integrated cross section
  void evaluateIntegratedCrossSection();

  // The distribution type
  static const OneDDistributionType distribution_type = 
    INCOHERENT_DISTRIBUTION;

  // The scattering function
  Teuchos::RCP<const OneDDistribution> d_scattering_function;

  // The cached inverse wavelength of the photon (1/cm)
  double d_inverse_wavelength;
  
  // The cached integrated cross section for the current energy
  double d_integrated_cross_section;
};

} // end Utility namespace

#endif // end UTILITY_INCOHERENT_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_IncoherentDistribution.hpp
//---------------------------------------------------------------------------//
