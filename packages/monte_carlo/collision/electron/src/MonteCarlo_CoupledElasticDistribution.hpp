//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CoupledElasticDistribution.hpp
//! \author Luke Kersting
//! \brief  Coupled elastic distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COUPLED_ELASTIC_HPP
#define MONTE_CARLO_COUPLED_ELASTIC_HPP

// FRENSIE Includes
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_CosineInterpolationPolicy.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

/*! The coupled elastic distribution class declaration
 * \ingroup one_d_distributions
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
class UnitAwareCoupledElasticDistribution : public Utility::UnitAwareTabularUnivariateDistribution<IndependentUnit,DependentUnit>
{

  // Only allow construction when the independent unit dimensionless
  RESTRICT_UNIT_TO_BOOST_DIMENSION( IndependentUnit, dimensionless_type );

  // Typedef for base type
  typedef Utility::UnitAwareTabularUnivariateDistribution<IndependentUnit,DependentUnit> BaseType;

  // The unnormalized cdf quantity
  typedef typename Utility::QuantityTraits<typename BaseType::DistNormQuantity>::template GetQuantityToPowerType<-1>::type UnnormCDFQuantity;

  // The slope unit traits
  typedef Utility::UnitTraits<typename Utility::UnitTraits<DependentUnit>::template GetMultipliedUnitType<typename Utility::UnitTraits<IndependentUnit>::InverseUnit>::type> SlopeUnitTraits;

  // The slope quantity
  typedef typename SlopeUnitTraits::template GetQuantityType<double>::type SlopeQuantity;

  // The distribution normalization quantity type
  typedef typename BaseType::DistNormQuantity DistNormQuantity;

  // Typedef for QuantityTraits<double>
  typedef Utility::QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef Utility::QuantityTraits<typename BaseType::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef Utility::QuantityTraits<typename BaseType::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef Utility::QuantityTraits<typename BaseType::DepQuantity> DQT;

  // Typedef for QuantityTraits<DistNormQuantity>
  typedef Utility::QuantityTraits<DistNormQuantity> DNQT;

  // Typedef for QuantityTraits<UnnormCDFQuantity>
  typedef Utility::QuantityTraits<UnnormCDFQuantity> UCQT;

public:

  //! This distribution type
  typedef UnitAwareCoupledElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Default constructor
  UnitAwareCoupledElasticDistribution();

  //! Basic constructor (potentially dangerous)
  UnitAwareCoupledElasticDistribution(
                    const std::vector<double>& independent_values,
                    const std::vector<double>& dependent_values,
                    const double& moliere_screening_constant,
                    const double& cutoff_cross_section_ratio );

  //! Constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareCoupledElasticDistribution(
                    const std::vector<InputIndepQuantity>& independent_values,
                    const std::vector<InputDepQuantity>& dependent_values,
                    const double& moliere_screening_constant,
                    const double& cutoff_cross_section_ratio );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareCoupledElasticDistribution( const UnitAwareCoupledElasticDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareCoupledElasticDistribution fromUnitlessDistribution( const UnitAwareCoupledElasticDistribution<InterpolationPolicy,void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareCoupledElasticDistribution& operator=(
                           const UnitAwareCoupledElasticDistribution& dist_instance );

  //! Destructor
  ~UnitAwareCoupledElasticDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the CDF
  double evaluateCDF( const IndepQuantity indep_var_value ) const override;

  //! Return a random sample from the distribution
  IndepQuantity sample() const override;

  //! Return a random sample and record the number of trials
  IndepQuantity sampleAndRecordTrials( Utility::DistributionTraits::Counter& trials ) const override;

  //! Return a random sample and bin index from the distribution
  IndepQuantity sampleAndRecordBinIndex( size_t& sampled_bin_index ) const override;

  //! Return a random sample from the distribution at the given CDF value
  IndepQuantity sampleWithRandomNumber( const double random_number ) const override;

  //! Return a random sample from the distribution in a subrange
  IndepQuantity sampleInSubrange( const IndepQuantity max_indep_var ) const override;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  IndepQuantity sampleWithRandomNumberInSubrange(
                            const double random_number,
                            const IndepQuantity max_indep_var ) const override;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const override;

  //! Return the cutoff bound of the distribution independent variable
  IndepQuantity getCutoffBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const override;

  //! Return the distribution type
  Utility::UnivariateDistributionType getDistributionType() const;

  //! Return the moliere screening constant for the distribution
  double getMoliereScreeningConstant() const;

  //! Return the cutoff cross section ratio for the distribution
  double getCutoffCrossSectionRatio() const;

  //! Test if the distribution is continuous
  bool isContinuous() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

  //! Equality comparison operator
  bool operator==( const UnitAwareCoupledElasticDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareCoupledElasticDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareCoupledElasticDistribution( const UnitAwareCoupledElasticDistribution<InterpolationPolicy,void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const override;

  // //! Test if the independent variable is compatible with Lin processing
  // bool isIndepVarCompatibleWithProcessingType(
  //                                       const LinIndepVarProcessingTag ) const;

  // //! Test if the independent variable is compatible with Log processing
  // bool isIndepVarCompatibleWithProcessingType(
  //                                       const LogIndepVarProcessingTag ) const;

  // //! Test if the dependent variable is compatible with Lin processing
  // bool isDepVarCompatibleWithProcessingType(
  //                                         const LinDepVarProcessingTag ) const;

  // //! Test if the dependent variable is compatible with Log processing
  // bool isDepVarCompatibleWithProcessingType(
  //                                         const LogDepVarProcessingTag ) const;

private:

  // Initialize the distribution
  void initializeDistributionFromRawData(
                              const std::vector<double>& independent_values,
                              const std::vector<double>& dependent_values );

  // Initialize the distribution
  template<typename InputIndepQuantity, typename InputDepQuantity>
  void initializeDistribution(
                  const std::vector<InputIndepQuantity>& independent_values,
                  const std::vector<InputDepQuantity>& dependent_values );

  // Reconstruct original distribution
  void reconstructOriginalDistribution(
                         std::vector<IndepQuantity>& independent_values,
                         std::vector<DepQuantity>& dependent_values ) const;

  // Reconstruct original distribution w/o units
  void reconstructOriginalUnitlessDistribution(
                              std::vector<double>& independent_values,
                              std::vector<double>& dependent_values ) const;

  // Convert the unitless values to the correct units
  template<typename Quantity>
  static void convertUnitlessValues(
                                 const std::vector<double>& unitless_values,
                                 std::vector<Quantity>& quantities );

  // Return a random sample using the random number and record the bin index
  IndepQuantity sampleImplementation( double random_number,
                                      size_t& sampled_bin_index ) const;

  // Return a random sample of the screened Rutherford analytical peak using the random number
  IndepQuantity sampleScreenedRutherford( double random_number ) const;

  // Return a random sample of the cutoff tabular distribution using the random number and record the bin index
  IndepQuantity sampleCutoff( double random_number,
                              size_t& sampled_bin_index ) const;

  // Verify that the values are valid
  template<typename InputIndepQuantity, typename InputDepQuantity>
  static void verifyValidValues(
                    const std::vector<InputIndepQuantity>& independent_values,
                    const std::vector<InputDepQuantity>& dependent_values,
                    const double& moliere_screening_constant,
                    const double& cutoff_cross_section_ratio );

  // Save the distribution to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the distribution from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // All possible instantiations are friends
  template<typename FriendInterpolationPolicy,
           typename FriendIndepUnit,
           typename FriendDepUnit>
  friend class UnitAwareCoupledElasticDistribution;

  // The distribution type
  static const Utility::UnivariateDistributionType distribution_type =
    Utility::COUPLED_ELASTIC_DISTRIBUTION;

  // The distribution (first = indep_var, second = cdf, third = pdf,
  // fourth = pdf slope): both the pdf and cdf are left unnormalized to
  // prevent altering the grid with log interpolation
  typedef std::vector<std::tuple<IndepQuantity,UnnormCDFQuantity,DepQuantity,SlopeQuantity> > DistributionArray;
  DistributionArray d_distribution;

  // The normalization constant
  DistNormQuantity d_norm_constant;

  // The scaled_normalization constant
  DistNormQuantity d_scaled_norm_constant;

  // The max CDF value
  UnnormCDFQuantity d_max_cdf;

  // The lower bounds of the independent variable
  IndepQuantity d_min_indep_var;

  // The upper bounds of the independent variable
  IndepQuantity d_max_indep_var;

  /* Moliere's atomic screening constant at the energy of the distribution
   * eta = 1/4 ( alpha m c / 0.885 p )**2 Z**(2/3) ( 1.13 + 3.76 [ alpha Z / beta ]**2 sqrt{ E/ (E + 1)})
   *
   * The numerical value is the same as that of Seltzer
   * (Chapter 7) in the "Orange Book"".
   */
  double d_moliere_eta;

  // The ratio of the cutoff cross section to the total cross section at the energy of the distribution
  double d_cutoff_cross_section_ratio;

  /* Parameter for rescaling the random number to sample the
   * screened Rutherford analytical peak ( 1/(1 - cutoff_cs_ratio) )
   */
  double d_scaling_parameter;

  /* Parameter for evaluating the PDF of the screened Rutherford analytical peak
   * ( cutoff_cs_ratio * cutoff_pdf * ( 1 - mu_c + eta )**2 )
   */
  DepQuantity d_pdf_parameter;

  /* Parameter for evaluating the CDF of the screened Rutherford analytical peak
   * ( (1 - cutoff_cs_ratio)*eta/mu_c )
   */
  double d_cdf_parameter;
};

/*! The coupled elastic distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
template<typename InterpolationPolicy> using CoupledElasticDistribution =
  UnitAwareCoupledElasticDistribution<InterpolationPolicy,void,void>;

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS3_VERSION( UnitAwareCoupledElasticDistribution, MonteCarlo, 0 );

#define BOOST_SERIALIZATION_COUPLED_ELASTIC_DISRIBUTION_EXPORT_STANDARD_KEY()   \
  BOOST_SERIALIZATION_CLASS3_EXPORT_STANDARD_KEY( UnitAwareCoupledElasticDistribution, MonteCarlo ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_KEY_IMPL(                   \
    UnitAwareCoupledElasticDistribution, MonteCarlo,                                \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( std::string( "CoupledElasticDistribution<" ) + Utility::typeName<InterpPolicy>() + ">" ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename InterpPolicy ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( InterpPolicy, void, void ) )

BOOST_SERIALIZATION_COUPLED_ELASTIC_DISRIBUTION_EXPORT_STANDARD_KEY();

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_CoupledElasticDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_COUPLED_ELASTIC_ONE_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CoupledElasticDistribution.hpp
//---------------------------------------------------------------------------//
