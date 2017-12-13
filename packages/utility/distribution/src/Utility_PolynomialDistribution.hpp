//---------------------------------------------------------------------------//
//!
//! \file   Utility_PolynomialDistribution.hpp
//! \author Alex Robinson
//! \brief  Polynomial distribution class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_POLYNOMIAL_DISTRIBUTION_HPP
#define UTILITY_POLYNOMIAL_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_UnivariateDistribution.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"

namespace Utility{

/*! Polynomial distribution class
 * \ingroup univariate_distributions
 */
template<typename IndependentUnit, typename DependentUnit>
class UnitAwarePolynomialDistribution : public UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit>
{
  // Typedef for base type
  typedef UnitAwareUnivariateDistribution<IndependentUnit,DependentUnit> BaseType;
  
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
  typedef UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Constructor ( sum_(i=0)^(N-1) c_i*x^i : x in (a,b) )
  template<typename InputIndepQuantity = IndepQuantity>
  UnitAwarePolynomialDistribution(
                        const std::vector<double>& coefficients =
                        ThisType::getDefaultCoefficients(),
                        const InputIndepQuantity min_indep_limit =
                        ThisType::getDefaultLowerBound<InputIndepQuantity>(),
                        const InputIndepQuantity max_indep_limit =
                        ThisType::getDefaultUpperBound<InputIndepQuantity>() );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwarePolynomialDistribution( const UnitAwarePolynomialDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwarePolynomialDistribution fromUnitlessDistribution( const UnitAwarePolynomialDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwarePolynomialDistribution& operator=(
			const UnitAwarePolynomialDistribution& dist_instance );

  //! Destructor
  ~UnitAwarePolynomialDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const override;

  //! Return a random sample from the distribution
  IndepQuantity sample() const override;

  //! Return a random sample and record the number of trials
  IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const override; 

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const override;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const override;

  //! Return the distribution type
  UnivariateDistributionType getDistributionType() const override;

  //! Test if the distribution is continuous
  bool isContinuous() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

  //! Equality comparison operator
  bool operator==( const UnitAwarePolynomialDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwarePolynomialDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwarePolynomialDistribution( const UnitAwarePolynomialDistribution<void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const override;

  //! Get the default coefficients
  static std::vector<double> getDefaultCoefficients()
  { return std::vector<double>({1.0}); }

  //! Get the default lower bound
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultLowerBound()
  { return Utility::QuantityTraits<InputIndepQuantity>::zero(); }

  //! Get the default upper bound
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultUpperBound()
  { return Utility::QuantityTraits<InputIndepQuantity>::one(); }

private:

  // Initialize the distribution
  void initializeDistribution( const IndepQuantity min_indep_limit,
			       const IndepQuantity max_indep_limit );

  // Verify that the distribution data is valid
  template<typename InputIndepQuantity>
  static void verifyValidDistributionData(
                                    const std::vector<double>& coefficients,
                                    const InputIndepQuantity min_indep_limit,
                                    const InputIndepQuantity max_indep_limit );
  
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
  friend class UnitAwarePolynomialDistribution;

  // The distribution type
  static const UnivariateDistributionType distribution_type =
    POLYNOMIAL_DISTRIBUTION;

  // The polynomial coefficients (ignore units since each will be different)
  std::vector<double> d_coefficients;

  // The sampling cdf for the probability mixing technique
  std::vector<double> d_term_sampling_cdf;

  // The min and max indep limits to the powers of each term of the series + 1
  // first = a^(i+1), second = b^(i+1)
  std::vector<std::tuple<double,double> > d_indep_limits_to_series_powers_p1;

  // The normalization constant
  DistNormQuantity d_norm_constant;
};

/*! The polynomial distribution (unit-agnostic)
 * \ingroup univariate_distributions
 */
  typedef UnitAwarePolynomialDistribution<void,void> PolynomialDistribution;

} // end Utility namespace

BOOST_SERIALIZATION_DISTRIBUTION2_VERSION( UnitAwarePolynomialDistribution, 0 );
BOOST_SERIALIZATION_DISTRIBUTION2_EXPORT_STANDARD_KEY( PolynomialDistribution );

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//

#include "Utility_PolynomialDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_POLYNOMIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_PolynomialDistribution.hpp
//---------------------------------------------------------------------------//
