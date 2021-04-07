//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HybridElasticDistribution.hpp
//! \author Luke Kersting
//! \brief  Hybrid elastic distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_HYBRID_ELASTIC_HPP
#define MONTE_CARLO_HYBRID_ELASTIC_HPP

// FRENSIE Includes
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Tuple.hpp"

namespace MonteCarlo{

/*! The hybrid elastic distribution class declaration
 * \ingroup one_d_distributions
 */
template<typename InterpolationPolicy,
         typename IndependentUnit,
         typename DependentUnit>
class UnitAwareHybridElasticDistribution : public Utility::UnitAwareTabularUnivariateDistribution<IndependentUnit,DependentUnit>
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
  typedef UnitAwareHybridElasticDistribution<InterpolationPolicy,IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Default constructor
  UnitAwareHybridElasticDistribution();

  //! Basic constructor (potentially dangerous)
  UnitAwareHybridElasticDistribution(
                    const std::vector<double>& independent_cutoff_values,
                    const std::vector<double>& dependent_cutoff_values,
                    const std::vector<double>& independent_discrete_values,
                    const std::vector<double>& dependent_discrete_values,
                    const double cutoff_angle_cosine,
                    const double cutoff_cross_section_ratio );

  //! Constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareHybridElasticDistribution(
        const std::vector<InputIndepQuantity>& independent_cutoff_values,
        const std::vector<InputDepQuantity>& dependent_cutoff_values,
        const std::vector<InputIndepQuantity>& independent_discrete_values,
        const std::vector<InputDepQuantity>& dependent_discrete_values,
        const InputIndepQuantity& cutoff_angle_cosine,
        const double cutoff_cross_section_ratio );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareHybridElasticDistribution( const UnitAwareHybridElasticDistribution<InterpolationPolicy,InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareHybridElasticDistribution fromUnitlessDistribution( const UnitAwareHybridElasticDistribution<InterpolationPolicy,void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareHybridElasticDistribution& operator=(
                           const UnitAwareHybridElasticDistribution& dist_instance );

  //! Destructor
  ~UnitAwareHybridElasticDistribution()
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
  Utility::UnivariateDistributionType getDistributionType() const override;

  //! Return the cutoff cross section ratio for the distribution
  double getCutoffCrossSectionRatio() const;

  //! Test if the distribution is continuous
  bool isContinuous() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

  //! Equality comparison operator
  bool operator==( const UnitAwareHybridElasticDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareHybridElasticDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareHybridElasticDistribution( const UnitAwareHybridElasticDistribution<InterpolationPolicy,void,void>& unitless_dist_instance, int );

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
  void initializeDistributionsFromRawData(
                    const std::vector<double>& independent_cutoff_values,
                    const std::vector<double>& dependent_cutoff_values,
                    const std::vector<double>& independent_discrete_values,
                    const std::vector<double>& dependent_discrete_values );

  // Initialize the distribution
  template<typename InputIndepQuantity, typename InputDepQuantity>
  void initializeCutoffDistribution(
                  const std::vector<InputIndepQuantity>& independent_values,
                  const std::vector<InputDepQuantity>& dependent_values );

  // Initialize the distribution
  template<typename InputIndepQuantity, typename InputDepQuantity>
  void initializeDiscreteDistribution(
                  const std::vector<InputIndepQuantity>& independent_values,
                  const std::vector<InputDepQuantity>& dependent_values );

  // Reconstruct original distributions
  void reconstructOriginalDistributions(
                 std::vector<IndepQuantity>& independent_cutoff_values,
                 std::vector<DepQuantity>& dependent_cutoff_values,
                 std::vector<IndepQuantity>& independent_discrete_values,
                 std::vector<DepQuantity>& dependent_discrete_values ) const;

  // Reconstruct original distributions w/o units
  void reconstructOriginalUnitlessDistributions(
                      std::vector<double>& independent_cutoff_values,
                      std::vector<double>& dependent_cutoff_values,
                      std::vector<double>& independent_discrete_values,
                      std::vector<double>& dependent_discrete_values ) const;

  // Convert the unitless values to the correct units
  template<typename Quantity>
  static void convertUnitlessValues(
                                 const std::vector<double>& unitless_values,
                                 std::vector<Quantity>& quantities );

  // Return a random sample using the random number and record the bin index
  IndepQuantity sampleImplementation( double random_number,
                                      size_t& sampled_bin_index ) const;

  // Return a random sample of the moment preserving discrete distribution using the random number and record the bin index
  IndepQuantity sampleDiscrete( double random_number,
                                size_t& sampled_bin_index ) const;

  // Return a random sample of the cutoff tabular distribution using the random number and record the bin index
  IndepQuantity sampleCutoff( double random_number,
                              size_t& sampled_bin_index ) const;

  // Verify that the values are valid
  template<typename InputIndepQuantity, typename InputDepQuantity>
  static void verifyValidValues(
           const std::vector<InputIndepQuantity>& independent_cutoff_values,
           const std::vector<InputDepQuantity>& dependent_cutoff_values,
           const std::vector<InputIndepQuantity>& independent_discrete_values,
           const std::vector<InputDepQuantity>& dependent_discrete_values,
           const InputIndepQuantity cutoff_angle_cosine,
           const double cutoff_cross_section_ratio);
  
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
  friend class UnitAwareHybridElasticDistribution;

  // The distribution type
  static const Utility::UnivariateDistributionType distribution_type =
    Utility::HYBRID_ELASTIC_DISTRIBUTION;

  // The distribution (first = indep_var, second = cdf, third = pdf,
  // fourth = pdf slope): both the pdf and cdf are left unnormalized to
  // prevent altering the grid with log interpolation
  typedef std::vector<std::tuple<IndepQuantity,UnnormCDFQuantity,DepQuantity,SlopeQuantity> > DistributionArray;
  DistributionArray d_cutoff_distribution;

  // The distribution (first = independent value, second = CDF)
  std::vector<std::pair<IndepQuantity,double> > d_discrete_distribution;

  // The discrete normalization constant
  DistNormQuantity d_discrete_norm_constant;

  // The cutoff normalization constant
  DistNormQuantity d_cutoff_norm_constant;

  // The unnormalized CDF value a the cutoff angle cosine
  UnnormCDFQuantity d_max_cutoff_cdf;

  // The cutoff angle cosine between the tabular and discrete distributions
  IndepQuantity d_cutoff_mu;

  // The ratio of the cutoff cross section to the total cross section at the energy of the distribution
  double d_cutoff_cross_section_ratio;

  /* Parameter for rescaling the random number to sample the
   * moment preserving discrete peak ( 1/(1 - cutoff_cs_ratio) )
   */
  double d_scaling_parameter;
};

/*! The hybrid elastic distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
template<typename InterpolationPolicy> using HybridElasticDistribution =
  UnitAwareHybridElasticDistribution<InterpolationPolicy,void,void>;

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS3_VERSION( UnitAwareHybridElasticDistribution, MonteCarlo, 0 );

#define BOOST_SERIALIZATION_HYBRID_ELASTIC_DISRIBUTION_EXPORT_STANDARD_KEY()   \
  BOOST_SERIALIZATION_CLASS3_EXPORT_STANDARD_KEY( UnitAwareHybridElasticDistribution, MonteCarlo ) \
  BOOST_SERIALIZATION_TEMPLATE_CLASS_EXPORT_KEY_IMPL(                   \
    UnitAwareHybridElasticDistribution, MonteCarlo,                                \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( std::string( "HybridElasticDistribution<" ) + Utility::typeName<InterpPolicy>() + ">" ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( typename InterpPolicy ), \
    __BOOST_SERIALIZATION_FORWARD_AS_SINGLE_ARG__( InterpPolicy, void, void ) )

BOOST_SERIALIZATION_HYBRID_ELASTIC_DISRIBUTION_EXPORT_STANDARD_KEY();

//---------------------------------------------------------------------------//
// Template includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_HybridElasticDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_HYBRID_ELASTIC_ONE_D_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_HybridElasticDistribution.hpp
//---------------------------------------------------------------------------//
