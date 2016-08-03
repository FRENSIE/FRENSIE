//---------------------------------------------------------------------------//
//!
//! \file   Utility_ElasticElectronDistribution.hpp
//! \author Luke Kersting
//! \brief  Tabular distribution for elastic electron scattering class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ELASTIC_ELECTRON_DISTRIBUTION_HPP
#define UTILITY_ELASTIC_ELECTRON_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

//! The interpolated distribution class declaration
template<typename InterpolationPolicy>
class ElasticElectronDistribution : public TabularOneDDistribution,
	  public ParameterListCompatibleObject<ElasticElectronDistribution<InterpolationPolicy> >
{

public:

  //! Default constructor
  ElasticElectronDistribution();

  //! Constructor for ENDL tables data
  ElasticElectronDistribution( const Teuchos::Array<double>& independent_values,
		               const Teuchos::Array<double>& dependent_values,
                       const double moliere_screening_constant,
                       const double screened_rutherford_normalization_constant );

  //! Constructor for ACE tables data
  ElasticElectronDistribution( const Teuchos::Array<double>& independent_values,
		               const Teuchos::Array<double>& dependent_values,
                       const double energy,
                       const int atomic_number );

  //! Copy constructor
  ElasticElectronDistribution(
	       const ElasticElectronDistribution<InterpolationPolicy>& dist_instance );

  //! Assignment operator
  ElasticElectronDistribution<InterpolationPolicy>& operator=(
	       const ElasticElectronDistribution<InterpolationPolicy>& dist_instance );

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const;

  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const;

  //! Evaluate the CDF
  double evaluateCDF( const double indep_var_value ) const;

  //! Return a random sample from the distribution
  double sample() const;

  //! Return a random sample and record the number of trials
  double sampleAndRecordTrials( unsigned& trials ) const;

  //! Return a random sample and bin index from the distribution
  double sampleAndRecordBinIndex( unsigned& sampled_bin_index ) const;

  //! Return a random sample from the distribution at the given CDF value
  double sampleWithRandomNumber( const double random_number ) const;

  //! Return a random sample from the distribution in a subrange
  double sampleInSubrange( const double max_indep_var ) const;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  double sampleWithRandomNumberInSubrange( const double random_number,
					   const double max_indep_var ) const;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

  //! Test if the distribution is continuous
  bool isContinuous() const;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is );

  //! Method for testing if two objects are equivalent
  bool isEqual( const ElasticElectronDistribution<InterpolationPolicy>& other ) const;

  //! Return Moliere's screening constant
  double getMoliereScreeningConstant() const;

  //! Return the normalization constant for the screened Rutherford component of the distribution
  double getScreenedRutherfordNormalizationConstant() const;

private:

  // Initialize the distribution for ACE tables data
  void initializeDistributionACE(
        const Teuchos::Array<double>& independent_values,
        const Teuchos::Array<double>& dependent_values );

  // Initialize the distribution for ENDL tables data
  void initializeDistributionENDL(
        const Teuchos::Array<double>& independent_values,
        const Teuchos::Array<double>& dependent_values );

  // Return a random sample using the random number and record the bin index
  double sampleImplementation( double random_number,
			       unsigned& sampled_bin_index ) const;

  // Set the first two PDF values
  void setFirstTwoPDFs( const double& first_cdf,
                        const double& second_cdf );

  // The distribution type
  static const OneDDistributionType distribution_type =
                                        ELASTIC_ELECTRON_DISTRIBUTION;

  // The distribution (first = indep_var, second = cdf, third = pdf,
  // fourth = slope)
  typedef Teuchos::Array<Quad<double,double,double,double> > DistributionArray;
  DistributionArray d_distribution;

  // The normalization constant
  double d_norm_constant;

  // The energy of the elastic angular distribution in MeV
  double d_energy;

  // Atomic number (Z) of the target atom
  int d_atomic_number;

  // Atomic number (Z) of the target atom to the 2/3 power (Z^2/3)
  double d_Z_two_thirds_power;

  // Moliere's screening constant
  double d_moliere_screening_constant;

  // The normalization constant for the screened Rutherford component of the distribution
  double d_screened_rutherford_normalization_constant;

  // The cutoff cdf below which the screened Rutherford distribution is sampled
  double d_screened_rutherford_cutoff_cdf;

  // The cutoff angle below which the screened Rutherford distribution is sampled
  static double s_sr_angle;
};

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::ElasticElectronDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename InterpolationPolicy>
class TypeNameTraits<Utility::ElasticElectronDistribution<InterpolationPolicy> >
{
public:
  static std::string name()
  {
    std::ostringstream iss;
    iss << "Elastic Electron " << InterpolationPolicy::name() << " Distribution";

    return iss.str();
  }
  static std::string concreteName(
	    const Utility::ElasticElectronDistribution<InterpolationPolicy>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template inludes.
//---------------------------------------------------------------------------//

#include "Utility_ElasticElectronDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_ELASTIC_ELECTRON_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_ElasticElectronDistribution.hpp
//---------------------------------------------------------------------------//
