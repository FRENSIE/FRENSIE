//---------------------------------------------------------------------------//
//!
//! \file   Utility_AdjointKleinNishinaDistribution.hpp
//! \author Alex Robinson
//! \brief  Adjoint Klein-Nishina distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ADJOINT_KLEIN_NISHINA_DISTRIBUTION_HPP
#define UTILITY_ADJOINT_KLEIN_NISHINA_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"

namespace Utility{

/*! Adjoint Klein-Nishina distribution class
 * \details The adjoint Klein-Nishina distribution is a function of two 
 * coupled variables: the outgoing adjoint photon energy and the outgoing
 * adjoint photon scattering angle. Because of the one-to-one correspondence
 * between these two variables, the function can be reduced to a function
 * of a single variable - the inverse energy gain ratio (x = 1 - alpha*(1-mu)).
 * This variable x will be sampled from the distribution.
 */
class AdjointKleinNishinaDistribution : public OneDDistribution
{

private:
  
  // Typedef for Teuchos Scalar Traits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Calculate the min inverse energy gain ratio
  static double calculateMinInverseEnergyGainRatio( const double alpha,
						    const double alpha_max );

  //! Default constructor
  AdjointKleinNishinaDistribution();
  
  //! Constructor
  AdjointKleinNishinaDistribution( const double energy,
				   const double max_energy );

  //! Copy constructor
  AdjointKleinNishinaDistribution( 
			const AdjointKleinNishinaDistribution& dist_instance );

  //! Assignment operator
  AdjointKleinNishinaDistribution& operator=(
			const AdjointKleinNishinaDistribution& dist_instance );

  //! Destructor
  ~AdjointKleinNishinaDistribution()
  { /* ... */ }

  //! Set the energy (MeV)
  void setEnergy( const double energy );

  //! Return the energy (MeV)
  double getEnergy() const;

  //! Return the unitless energy
  double getAlpha() const;

  //! Return the max energy (MeV)
  double getMaxEnergy() const;

  //! Return the max unitless energy
  double getMaxAlpha() const;

  //! Evaluate the integrated adjoint Klein-Nishina cross section
  double evaluateIntegratedCrossSection() const;

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;

  //! Evaluate the PDF (dc/dx)
  double evaluatePDF( const double indep_var_value ) const;

  //! Evaluate the energy PDF (dc/dE)
  double evaluateEnergyPDF( const double outgoing_energy ) const;

  //! Return a random sample from the distribution
  double sample();

  //! Return a random sample from the distribution
  double sample() const;

  //! Return the sampling efficiency from the distribution
  double getSamplingEfficiency() const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

private:

  // Sample a value from the distribution, count the number of trials
  double sample( unsigned& number_of_trials ) const;

  // The adjoint Klein-Nishina cross section multiplier
  static const double cross_section_multiplier;

  // The distribution type
  static const OneDDistributionType distribution_type = 
    ADJOINT_KLEIN_NISHINA_DISTRIBUTION;

  // The dimensionless energy
  double d_alpha;

  // The dimensionless max energy
  double d_alpha_max;

  // The min energy loss ratio
  double d_min_inverse_energy_gain_ratio;

  // The number of trials
  unsigned d_trials;

  // The number of samples
  unsigned d_samples;
};

} // end Utility namespace

#endif // end UTILITY_ADJOINT_KLEIN_NISHINA_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_AdjointKleinNishinaDistribution.hpp
//---------------------------------------------------------------------------//
