//---------------------------------------------------------------------------//
//!
//! \file   Utility_ElasticElectronDistribution.hpp
//! \author Luke Kersting
//! \brief  Tabular distribution for elastic electron scattering class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ELASTIC_ELECTRON_DISTRIBUTION_HPP
#define UTILITY_ELASTIC_ELECTRON_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_Vector.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

//! The interpolated distribution class declaration
template<typename InterpolationPolicy>
class ElasticElectronDistribution : public TabularOneDDistribution
{

public:

  //! Default constructor
  ElasticElectronDistribution();

  //! Constructor for ENDL tables data
  ElasticElectronDistribution( const std::vector<double>& independent_values,
		               const std::vector<double>& dependent_values,
                               const double moliere_screening_constant,
                               const double screened_rutherford_normalization_constant );

  //! Constructor for ACE tables data
  ElasticElectronDistribution( const std::vector<double>& independent_values,
		               const std::vector<double>& dependent_values,
                               const double energy,
                               const int atomic_number );

  //! Copy constructor
  ElasticElectronDistribution(
	       const ElasticElectronDistribution<InterpolationPolicy>& dist_instance );

  //! Assignment operator
  ElasticElectronDistribution<InterpolationPolicy>& operator=(
	       const ElasticElectronDistribution<InterpolationPolicy>& dist_instance );

  //! Evaluate the distribution
  double evaluate( const double indep_var_value ) const override;

  //! Evaluate the PDF
  double evaluatePDF( const double indep_var_value ) const override;

  //! Evaluate the CDF
  double evaluateCDF( const double indep_var_value ) const override;

  //! Return a random sample from the distribution
  double sample() const override;

  //! Return a random sample and record the number of trials
  double sampleAndRecordTrials( DistributionTraits::Counter& trials ) const override;

  //! Return a random sample and bin index from the distribution
  double sampleAndRecordBinIndex( unsigned& sampled_bin_index ) const override;

  //! Return a random sample from the distribution at the given CDF value
  double sampleWithRandomNumber( const double random_number ) const override;

  //! Return a random sample from the distribution in a subrange
  double sampleInSubrange( const double max_indep_var ) const override;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  double sampleWithRandomNumberInSubrange( const double random_number,
					   const double max_indep_var ) const override;

  //! Return the upper bound of the distribution independent variable
  double getUpperBoundOfIndepVar() const override;

  //! Return the lower bound of the distribution independent variable
  double getLowerBoundOfIndepVar() const override;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const override;

  //! Test if the distribution is continuous
  bool isContinuous() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is, const std::string& delims ) override;

  //! Method for initializing the object from an input stream
  using IStreamableObject::fromStream;

  //! Method for converting the type to a property tree
  Utility::PropertyTree toPropertyTree( const bool inline_data ) const override;

  //! Method for converting the type to a property tree
  using PropertyTreeCompatibleObject::toPropertyTree;

  //! Method for initializing the object from a property tree node
  void fromPropertyTree( const Utility::PropertyTree& node,
                         std::vector<std::string>& unused_children ) override;

  //! Equality comparison operator
  bool operator==( const ElasticElectronDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const ElasticElectronDistribution& other ) const;

  //! Return Moliere's screening constant
  double getMoliereScreeningConstant() const;

  //! Return the normalization constant for the screened Rutherford component of the distribution
  double getScreenedRutherfordNormalizationConstant() const;

protected:

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const;

  //! Test if the independent variable is compatible with Lin processing
  bool isIndepVarCompatibleWithProcessingType(
                                        const LinIndepVarProcessingTag ) const;
  
  //! Test if the independent variable is compatible with Log processing
  bool isIndepVarCompatibleWithProcessingType(
                                        const LogIndepVarProcessingTag ) const;

  //! Test if the dependent variable is compatible with Lin processing
  bool isDepVarCompatibleWithProcessingType(
                                          const LinDepVarProcessingTag ) const;

  //! Test if the dependent variable is compatible with Log processing
  bool isDepVarCompatibleWithProcessingType(
                                          const LogDepVarProcessingTag ) const;

private:

  // Initialize the distribution for ACE tables data
  void initializeDistributionACE(
        const std::vector<double>& independent_values,
        const std::vector<double>& dependent_values,
        const double energy,
        const double atomic_number );

  // Initialize the distribution for ENDL tables data
  void initializeDistributionENDL(
        const std::vector<double>& independent_values,
        const std::vector<double>& dependent_values );

  // Return a random sample using the random number and record the bin index
  double sampleImplementation( double random_number,
			       unsigned& sampled_bin_index ) const;

  // Set the first two PDF values
  void setFirstTwoPDFs( const double first_cdf,
                        const double second_cdf,
                        const double energy,
                        const double atomic_number );

  // Verify that the distribution type is elastic electron
  static void verifyDistributionType( const Utility::Variant& type_data );

  // Set the independent values
  void extractIndependentValues( const Utility::Variant& indep_data,
                                 std::vector<double>& independent_values );

  // Set the dependent values
  void extractDependentValues( const Utility::Variant& dep_data,
                               std::vector<double>& dependent_values );

  // Set the moliere screening constant
  void extractMoliereScreeningConstant( const Utility::Variant& dep_data );

  // Set the screened rutherford normalization constant
  void extractScreenedRutherfordNormalizationConstant( const Utility::Variant& dep_data );

  // Verify that the values are valid
  static void verifyValidValues( const std::vector<double>& independent_values,
                                 const std::vector<double>& dependent_values );

  // The distribution type
  static const OneDDistributionType distribution_type =
                                        ELASTIC_ELECTRON_DISTRIBUTION;

  // The distribution (first = indep_var, second = cdf, third = pdf,
  // fourth = slope)
  typedef std::vector<std::tuple<double,double,double,double> > DistributionArray;
  DistributionArray d_distribution;

  // The normalization constant
  double d_norm_constant;

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
