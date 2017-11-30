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
#include "Utility_OneDDistribution.hpp"
#include "Utility_OneDDistributionPropertyTreeConverter.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_Vector.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace Utility{

/*! Polynomial distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit>
class UnitAwarePolynomialDistribution : public UnitAwareOneDDistribution<IndependentUnit,DependentUnit>,
                                        private OneDDistributionPropertyTreeConverter<UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>,UnitAwareOneDDistribution<IndependentUnit,DependentUnit> >
{
  // Typedef for base type
  typedef UnitAwareOneDDistribution<IndependentUnit,DependentUnit> BaseType;
  
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

  //! Default constructor
  UnitAwarePolynomialDistribution();

  //! Constructor ( sum_(i=0)^(N-1) c_i*x^i : x in (a,b) )
  template<typename InputIndepQuantity>
  UnitAwarePolynomialDistribution( const std::vector<double>& coefficients,
				   const InputIndepQuantity min_indep_limit,
				   const InputIndepQuantity max_indep_limit );

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
  OneDDistributionType getDistributionType() const override;

  //! Return the distribution type name
  static std::string typeName( const bool verbose_name,
                               const bool use_template_params = false,
                               const std::string& delim = std::string() );

  //! Test if the distribution is continuous
  bool isContinuous() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

  //! Method for initializing the object from an input stream
  using IStreamableObject::fromStream;

  //! Method for converting the type to a property tree
  Utility::PropertyTree toPropertyTree( const bool inline_data ) const override;

  //! Method for converting the type to a property tree
  using PropertyTreeCompatibleObject::toPropertyTree;

  //! Method for initializing the object from a property tree
  void fromPropertyTree( const Utility::PropertyTree& node,
                         std::vector<std::string>& unused_children ) override;

  //! Method for converting to a property tree
  using PropertyTreeCompatibleObject::fromPropertyTree;

  //! Equality comparison operator
  bool operator==( const UnitAwarePolynomialDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwarePolynomialDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwarePolynomialDistribution( const UnitAwarePolynomialDistribution<void,void>& unitless_dist_instance, int );

  //! Return the distribution type name
  std::string getTypeNameImpl( const bool verbose_name ) const override;

  //! Process the data that was extracted the stream
  void fromStreamImpl( VariantList& distribution_data ) override;

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const override;

private:

  // Initialize the distribution
  void initializeDistribution( const IndepQuantity min_indep_limit,
			       const IndepQuantity max_indep_limit );

  // Test if the distribution can be used for sampling (each term must be a
  // positive function
  static bool isValidSamplingDistribution(
                                       const std::vector<double>& coefficients,
                                       const IndepQuantity min_indep_limit,
                                       const IndepQuantity max_indep_limit );

  // Verify that the distribution data is valid
  static void verifyValidDistributionData(
                                       const std::vector<double>& coefficients,
                                       const IndepQuantity min_indep_limit,
                                       const IndepQuantity max_indep_limit );
  
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
  static const OneDDistributionType distribution_type =
    POLYNOMIAL_DISTRIBUTION;

  // The coefficient values key (used in property trees)
  static const std::string s_coefficient_values_key;

  // The coefficient values min match string (used in property trees)
  static const std::string s_coefficient_values_min_match_string;

  // The lower limit value key (used in property trees)
  static const std::string s_lower_limit_value_key;

  // The lower limit min match string (used in property trees)
  static const std::string s_lower_limit_value_min_match_string;

  // The upper limit value key (used in property trees)
  static const std::string s_upper_limit_value_key;

  // The upper limit min match string (used in property trees)
  static const std::string s_upper_limit_value_min_match_string;

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
 * \ingroup one_d_distributions
 */
  typedef UnitAwarePolynomialDistribution<void,void> PolynomialDistribution;

/*! Partial specialization of Utility::TypeNameTraits for unit aware
 * polynomial distribution
 * \ingroup one_d_distributions
 * \ingroup type_name_traits
 */
template<typename IndependentUnit,typename DependentUnit>
struct TypeNameTraits<UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit> >
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  {
    return UnitAwarePolynomialDistribution<IndependentUnit,DependentUnit>::typeName( true, true  );
  }
};

/*! Specialization of Utility::TypeNameTraits for polynomial distribution
 * \ingroup one_d_distributions
 * \ingroup type_name_traits
 */
template<>
struct TypeNameTraits<PolynomialDistribution>
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return PolynomialDistribution::typeName( true, false ); }
};
  
} // end Utility namespace

BOOST_DISTRIBUTION_CLASS_VERSION( UnitAwarePolynomialDistribution, 0 );
BOOST_DISTRIBUTION_CLASS_EXPORT_KEY2( PolynomialDistribution );

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//

#include "Utility_PolynomialDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_POLYNOMIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_PolynomialDistribution.hpp
//---------------------------------------------------------------------------//
