//---------------------------------------------------------------------------//
//!
//! \file   Utility_TabularCDFDistribution.hpp
//! \author Luke Kersting
//! \brief  Tabular CDF distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_TABULAR_CDF_DISTRIBUTION_HPP
#define UTILITY_TABULAR_CDF_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_CosineInterpolationPolicy.hpp"
#include "Utility_ArrayView.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"

namespace Utility{

/*! The interpolated distribution class declaration
 * \ingroup one_d_distributions
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
class UnitAwareTabularCDFDistribution : public UnitAwareTabularUnivariateDistribution<IndependentUnit,DependentUnit>
{
  // Typedef for base type
  typedef UnitAwareTabularUnivariateDistribution<IndependentUnit,DependentUnit> BaseType;

  // The inverse interpolation policy
  typedef typename Utility::InverseInterpPolicy<InterpolationPolicy>::InterpPolicy InverseInterp;

  // The unnormalized cdf quantity
  typedef typename QuantityTraits<typename BaseType::DistNormQuantity>::template GetQuantityToPowerType<-1>::type UnnormCDFQuantity;

  // The slope unit traits
  typedef UnitTraits<typename UnitTraits<DependentUnit>::InverseUnit> SlopeUnitTraits;

  // The slope quantity
  typedef typename SlopeUnitTraits::template GetQuantityType<double>::type SlopeQuantity;

  // The distribution normalization quantity type
  typedef typename BaseType::DistNormQuantity DistNormQuantity;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename BaseType::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename BaseType::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename BaseType::DepQuantity> DQT;

  // Typedef for QuantityTraits<DistNormQuantity>
  typedef QuantityTraits<DistNormQuantity> DNQT;

public:

  //! This distribution type
  typedef UnitAwareTabularCDFDistribution<InterpolationPolicy,IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Default constructor
  UnitAwareTabularCDFDistribution();

  //! Basic constructor (potentially dangerous)
  UnitAwareTabularCDFDistribution(
                        const std::vector<double>& independent_values,
                        const std::vector<double>& dependent_values,
                        const bool interpret_dependent_values_as_cdf = false );

  //! Basic view constructor (potentially dangerous)
  UnitAwareTabularCDFDistribution(
                    const Utility::ArrayView<const double>& independent_values,
                    const Utility::ArrayView<const double>& dependent_values,
                    const bool interpret_dependent_values_as_cdf = false );

  //! CDF constructor
  template<typename InputIndepQuantity>
  UnitAwareTabularCDFDistribution(
              const std::vector<InputIndepQuantity>& independent_values,
              const std::vector<double>& cdf_values );

  //! CDF view constructor
  template<typename InputIndepQuantity>
  UnitAwareTabularCDFDistribution(
        const Utility::ArrayView<const InputIndepQuantity>& independent_values,
        const Utility::ArrayView<const double>& cdf_values );

  //! Constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareTabularCDFDistribution(
                  const std::vector<InputIndepQuantity>& independent_values,
                  const std::vector<InputDepQuantity>& dependent_values );

  //! View constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareTabularCDFDistribution(
        const Utility::ArrayView<const InputIndepQuantity>& independent_values,
        const Utility::ArrayView<const InputDepQuantity>& dependent_values );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareTabularCDFDistribution( const UnitAwareTabularCDFDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareTabularCDFDistribution fromUnitlessDistribution( const UnitAwareTabularCDFDistribution<InterpolationPolicy,void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareTabularCDFDistribution& operator=(
                           const UnitAwareTabularCDFDistribution& dist_instance );

  //! Destructor
  ~UnitAwareTabularCDFDistribution()
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
  IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const override;

  //! Return a random sample and bin index from the distribution
  IndepQuantity sampleAndRecordBinIndex( size_t& sampled_bin_index ) const override;

  //! Return a random sample from the distribution at the given CDF value
  IndepQuantity sampleWithRandomNumber( const double random_number ) const override;

  //! Return a random sample from the distribution in a subrange
  IndepQuantity sampleInSubrange( const IndepQuantity max_indep_var ) const;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  IndepQuantity sampleWithRandomNumberInSubrange(
                            const double random_number,
                            const IndepQuantity max_indep_var ) const override;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const override;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const override;

  //! Return the distribution type
  UnivariateDistributionType getDistributionType() const override;

  //! Return the distribution type name
  static std::string typeName( const bool verbose_name,
                               const bool use_template_params = false,
                               const std::string& delim = std::string() );

  //! Return if the distribution was continuous from a CDF
  bool wasConstructedFromCDF() const;

  //! Test if the distribution is continuous
  bool isContinuous() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

  //! Equality comparison operator
  bool operator==( const UnitAwareTabularCDFDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareTabularCDFDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareTabularCDFDistribution( const UnitAwareTabularCDFDistribution<InterpolationPolicy,void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const override;

  // //! Test if the independent variable is compatible with Lin processing
  // bool isIndepVarCompatibleWithProcessingType(
  //                                       const LinIndepVarProcessingTag ) const;

  // //! Test if the independent variable is compatible with Log processing
  // bool isIndepVarCompatibleWithProcessingType(
  //                                       const LogIndepVarProcessingTag ) const;

  //! Test if the dependent variable is compatible with Lin processing
  bool isDepVarCompatibleWithProcessingType(
                                 const LinDepVarProcessingTag ) const override;

  //! Test if the dependent variable is compatible with Log processing
  bool isDepVarCompatibleWithProcessingType(
                                 const LogDepVarProcessingTag ) const override;

private:

  // Calculate the processed slope
  SlopeQuantity calculateProcessedSlope(
                                    const IndepQuantity indep_var_0,
                                    const IndepQuantity indep_var_1,
                                    const UnnormCDFQuantity cdf_var_0,
                                    const UnnormCDFQuantity cdf_var_1 ) const;

  // Initialize the distribution
  void initializeDistributionFromRawData(
                    const Utility::ArrayView<const double>& independent_values,
                    const Utility::ArrayView<const double>& dependent_values );

  // Initialize the distribution from a cdf
  template<typename InputIndepQuantity>
  void initializeDistributionFromCDF(
        const Utility::ArrayView<const InputIndepQuantity>& independent_values,
        const Utility::ArrayView<const double>& cdf_values );

  // Initialize the distribution
  template<typename InputIndepQuantity, typename InputDepQuantity>
  void initializeDistribution(
        const Utility::ArrayView<const InputIndepQuantity>& independent_values,
        const Utility::ArrayView<const InputDepQuantity>& dependent_values );

  // Reconstruct original distribution
  void reconstructOriginalDistribution(
                         std::vector<IndepQuantity>& independent_values,
                         std::vector<DepQuantity>& dependent_values ) const;

  // Reconstruct original CDF distribution
  void reconstructOriginalCDFDistribution(
                         std::vector<IndepQuantity>& independent_values,
                         std::vector<double>& cdf_values ) const;

  // Reconstruct original distribution w/o units
  void reconstructOriginalUnitlessDistribution(
                              std::vector<double>& independent_values,
                              std::vector<double>& dependent_values ) const;

  // Convert the unitless values to the correct units
  template<typename Quantity>
  static void convertUnitlessValues(
                       const Utility::ArrayView<const double>& unitless_values,
                       std::vector<Quantity>& quantities );

  // Return a random sample using the random number and record the bin index
  IndepQuantity sampleImplementation( double random_number,
                                      size_t& sampled_bin_index ) const;

  // Verify that the values are valid
  template<typename InputIndepQuantity, typename InputDepQuantity>
  static void verifyValidValues(
        const Utility::ArrayView<const InputIndepQuantity>& independent_values,
        const Utility::ArrayView<const InputDepQuantity>& dependent_values );

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
  friend class UnitAwareTabularCDFDistribution;

  // The distribution type
  static const UnivariateDistributionType distribution_type = TABULAR_CDF_DISTRIBUTION;

  // The distribution (first = indep_var, second = cdf, third = pdf,
  // fourth = pdf slope): both the pdf and cdf are left unnormalized to
  // prevent altering the grid with log interpolation
  typedef std::vector<std::tuple<IndepQuantity,UnnormCDFQuantity,DepQuantity,SlopeQuantity> > DistributionArray;
  DistributionArray d_distribution;

  // The normalization constant
  DistNormQuantity d_norm_constant;

  // Interpret the dependent values as cdf values
  bool d_interpret_dependent_values_as_cdf;
};

/*! The tabular cdf distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
template<typename InterpolationPolicy> using TabularCDFDistribution =
  UnitAwareTabularCDFDistribution<InterpolationPolicy,void,void>;

} // end Utility namespace

BOOST_SERIALIZATION_CLASS3_VERSION( UnitAwareTabularCDFDistribution, Utility, 0 );

#define BOOST_SERIALIZATION_TABULAR_CDF_DISRIBUTION_EXPORT_STANDARD_KEY()   \
  BOOST_SERIALIZATION_CLASS3_EXPORT_STANDARD_KEY( UnitAwareTabularCDFDistribution, Utility ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_KEY_IMPL(                   \
    UnitAwareTabularCDFDistribution, Utility,                                \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( std::string( "TabularCDFDistribution<" ) + Utility::typeName<InterpPolicy>() + ">" ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename InterpPolicy ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( InterpPolicy, void, void ) )

BOOST_SERIALIZATION_TABULAR_CDF_DISRIBUTION_EXPORT_STANDARD_KEY();

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "Utility_TabularCDFDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_TABULAR_CDF_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_TabularCDFDistribution.hpp
//---------------------------------------------------------------------------//
