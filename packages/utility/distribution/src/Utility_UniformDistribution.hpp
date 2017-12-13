//---------------------------------------------------------------------------//
//!
//! \file   Utility_UniformDistribution.hpp
//! \author Alex Robinson
//! \brief  Uniform distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIFORM_DISTRIBUTION_HPP
#define UTILITY_UNIFORM_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularUnivariateDistribution.hpp"
#include "Utility_QuantityTraits.hpp"

namespace Utility{

/*! The unit-aware uniform distribution class
 * \ingroup univariate_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareUniformDistribution : public UnitAwareTabularUnivariateDistribution<IndependentUnit,DependentUnit>
{

private:

  // Typedef for base type
  typedef UnitAwareTabularUnivariateDistribution<IndependentUnit,DependentUnit> BaseType;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename BaseType::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename BaseType::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename BaseType::DepQuantity> DQT;

public:

  //! This distribution type
  typedef UnitAwareUniformDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Constructor
  template<typename InputIndepQuantity = IndepQuantity,
           typename InputDepQuantity = DepQuantity>
  UnitAwareUniformDistribution(
                          const InputIndepQuantity& min_independent_value =
                          ThisType::getDefaultLowerBound<InputIndepQuantity>(),
                          const InputIndepQuantity& max_independent_value =
                          ThisType::getDefaultUpperBound<InputIndepQuantity>(),
                          const InputDepQuantity& dependent_value =
                          ThisType::getDefaultDepValue<InputDepQuantity>() );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit, typename Dummy=void>
  UnitAwareUniformDistribution( const UnitAwareUniformDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareUniformDistribution fromUnitlessDistribution( const UnitAwareUniformDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareUniformDistribution& operator=( const UnitAwareUniformDistribution& dist_instance );

  //! Destructor
  ~UnitAwareUniformDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the CDF
  double evaluateCDF( const IndepQuantity indep_var_value ) const override;

  //! Return a random sample from the distribution
  IndepQuantity sample() const override;

  //! Return a random sample from the distribution
  static IndepQuantity sample( const IndepQuantity min_independent_value,
			       const IndepQuantity max_independent_value );

  //! Return a random sample from the corresponding CDF and record the number of trials
  IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const override;

  //! Return a random sample from the distribution and record the number of trials
  static IndepQuantity sampleAndRecordTrials(
			        const IndepQuantity min_independent_value,
			        const IndepQuantity max_independent_value,
				DistributionTraits::Counter& trials );

  //! Return a random sample from the distribution at the given CDF value
  IndepQuantity sampleWithRandomNumber( const double random_number ) const override;

  //! Return a random sample from the distribution at the given CDF value
  static IndepQuantity sampleWithRandomNumber(
				const IndepQuantity min_independent_value,
				const IndepQuantity max_independent_value,
				const double random_number );

  //! Return a random sample and sampled index from the corresponding CDF
  IndepQuantity sampleAndRecordBinIndex( size_t& sampled_bin_index ) const override;

  //! Return a random sample from the corresponding CDF in a subrange
  IndepQuantity sampleInSubrange( const IndepQuantity max_indep_var ) const override;

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

  // Test if the distribution is continuous
  bool isContinuous() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

  //! Equality comparison operator
  bool operator==( const UnitAwareUniformDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareUniformDistribution& other ) const;
  
protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareUniformDistribution( const UnitAwareUniformDistribution<void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const override;

  //! Get the default lower bound
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultLowerBound()
  { return Utility::QuantityTraits<InputIndepQuantity>::zero(); }

  //! Get the default upper bound
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultUpperBound()
  { return Utility::QuantityTraits<InputIndepQuantity>::one(); }

  //! Get the default dependent value
  template<typename InputDepQuantity>
  static InputDepQuantity getDefaultDepValue()
  { return Utility::QuantityTraits<InputDepQuantity>::one(); }

private:

  // Verify that the shape parameters are valid
  static void verifyValidShapeParameters(
                                         const IndepQuantity& min_indep_value,
                                         const IndepQuantity& max_indep_value,
                                         const DepQuantity& multiplier );

  // Calculate the PDF value
  void calculatePDFValue();

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
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareUniformDistribution;

  // The distribution type
  static const UnivariateDistributionType distribution_type = UNIFORM_DISTRIBUTION;

  // The min independent value
  IndepQuantity d_min_independent_value;

  // The max independent value
  IndepQuantity d_max_independent_value;

  // The uniform distribution dependent value
  DepQuantity d_dependent_value;

  // The uniform distribution PDF value
  InverseIndepQuantity d_pdf_value;
};

/*! The uniform distribution (unit-agnostic)
 * \ingroup univariate_distributions
 */
typedef UnitAwareUniformDistribution<void,void> UniformDistribution;

} // end Utility namespace

BOOST_SERIALIZATION_DISTRIBUTION2_VERSION( UnitAwareUniformDistribution, 0 );
BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_STANDARD_KEY( UniformDistribution );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_UniformDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_UNIFORM_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_UniformDistribution.hpp
//---------------------------------------------------------------------------//
