//---------------------------------------------------------------------------//
//!
//! \file   Utility_KleinNishinaDistribution.hpp
//! \author Alex Robinson
//! \brief  Klein-Nishina distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_KLEIN_NISHINA_DISTRIBUTION_HPP
#define UTILITY_KLEIN_NISHINA_DISTRIBUTION_HPP

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"

namespace Utility{

/*! Klein-Nishina distribution class
 * \details The Klein-Nishina distribution is a function of two coupled
 * variables: the outgoing photon energy and the outgoing photon scattering
 * angle. Because of the one-to-one correspondence between the outgoing photon
 * energy and the outgoing photon angle, the function can be reduced to a
 * function of a single variable - the energy gain ratio 
 * (x = 1 + alpha*(1-mu)). This variable x will be sampled from the
 * distribution.
 */
class KleinNishinaDistribution : public OneDDistribution
{

private:

  // Typedef for Teuchos Scalar Traits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Get the koblinger cutoff energy
  static double getKoblingerCutoffEnergy();

  //! Evaluate the integrated Klein-Nishina cross section
  static double evaluateIntegratedKleinNishinaCrossSection( 
							  const double alpha );

  //! Evaluate the approximate integrated Klein-Nishina cross section
  static double evaluateApproximateIntegratedKleinNishinaCrossSection(
							  const double alpha );

  //! Return a sample from the distribution using the optimal method
  static double sampleOptimal( const double energy );

  //! Return a sample using Kahn's rejection method
  static double sampleKleinNishinaUsingKahnsMethod( 
						  const double alpha,
						  unsigned& number_of_trials );

  //! Return a sample using Koblinger's exact method
  static double sampleKleinNishinaUsingKoblingersMethod( 
						  const double alpha,
						  unsigned& number_of_trials );

  //! Default constructor
  KleinNishinaDistribution();

  //! Constructor
  KleinNishinaDistribution( const double energy,
			    const bool use_kahn_sampling_only = false,
			    const bool use_exact_integrated_cross_sec = true );

  //! Copy constructor
  KleinNishinaDistribution( const KleinNishinaDistribution& dist_instance );

  //! Assignment operator
  KleinNishinaDistribution& operator=( 
			       const KleinNishinaDistribution& dist_instance );

  //! Destructor
  ~KleinNishinaDistribution()
  { /* ... */ }

  //! Set the energy (MeV)
  void setEnergy( const double energy );

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const;

  //! Return a random sample from the distribution
  double sample();

  //! Return a sample from the distribution
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
  
  // The Klein-Nishina cross section multiplier
  static const double cross_section_multiplier;

  // The Koblinger cutoff dimensionless energy
  static const double koblinger_cutoff_alpha;

  // The distribution type
  static const OneDDistributionType distribution_type = 
    KLEIN_NISHINA_DISTRIBUTION;

  // The dimensionless energy
  double d_alpha;

  // The number of trials
  unsigned d_trials;

  // The number of samples
  unsigned d_samples;

  // The high-energy sampling function
  boost::function<double (double, unsigned&)> d_high_energy_sampling_function;

  // The normalization function
  boost::function<double (double)> d_norm_function;
};

} // end Utility namespace

#endif // end UTILITY_KLEIN_NISHINA_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_KleinNishinaDistribution.hpp
//---------------------------------------------------------------------------//
