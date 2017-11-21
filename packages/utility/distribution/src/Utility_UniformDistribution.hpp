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
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_QuantityTraits.hpp"

namespace Utility{

/*! The unit-aware uniform distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareUniformDistribution : public UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>
                                     
{

private:

  // Typedef for base type
  typedef UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit> BaseType;

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

  //! Default constructor
  UnitAwareUniformDistribution();

  //! Constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareUniformDistribution(const InputIndepQuantity& min_independent_value,
			       const InputIndepQuantity& max_independent_value,
			       const InputDepQuantity& dependent_value );

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
  IndepQuantity sampleAndRecordBinIndex( unsigned& sampled_bin_index ) const override;

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
  OneDDistributionType getDistributionType() const override;

  //! Return the distribution type name
  static std::string typeName( const bool verbose_name,
                               const bool use_template_params = false,
                               const std::string& delim = std::string() );

  // Test if the distribution is continuous
  bool isContinuous() const override;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const override;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is, const std::string& delims ) override;

  //! Method for initializing the object from an input stream
  using IStreamableObject::fromStream;

  //! Method for converting to a property tree
  Utility::PropertyTree toPropertyTree( const bool inline_data ) const override;

  //! Method for converting to a property tree
  using PropertyTreeCompatibleObject::toPropertyTree;

  //! Method for initializing the object from a property tree
  void fromPropertyTree( const Utility::PropertyTree& node,
                         std::vector<std::string>& unused_children ) override;

  //! Method for converting to a property tree
  using PropertyTreeCompatibleObject::fromPropertyTree;

  //! Equality comparison operator
  bool operator==( const UnitAwareUniformDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareUniformDistribution& other ) const;
  
protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareUniformDistribution( const UnitAwareUniformDistribution<void,void>& unitless_dist_instance, int );

  //! Return the distribution type name
  std::string getDistributionTypeName( const bool verbose_name,
                                       const bool lowercase ) const override;

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const;

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
  static const OneDDistributionType distribution_type = UNIFORM_DISTRIBUTION;

  // The constant multiplier value key (used in property trees)
  static const std::string s_const_multiplier_value_key;

  // The constant multiplier min match string (used in property trees)
  static const std::string s_const_multiplier_value_min_match_string;

  // The lower limit value key (used in property trees)
  static const std::string s_lower_limit_value_key;

  // The lower limit min match string (used in property trees)
  static const std::string s_lower_limit_value_min_match_string;

  // The upper limit value key (used in property trees)
  static const std::string s_upper_limit_value_key;

  // The upper limit min match string (used in property trees)
  static const std::string s_upper_limit_value_min_match_string;

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
 * \ingroup one_d_distributions
 */
typedef UnitAwareUniformDistribution<void,void> UniformDistribution;

/*! Partial specialization of Utility::TypeNameTraits for unit aware
 * uniform distribution
 * \ingroup one_d_distributions
 * \ingroup type_name_traits
 */
template<typename IndependentUnit,typename DependentUnit>
struct TypeNameTraits<UnitAwareUniformDistribution<IndependentUnit,DependentUnit> >
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  {
    return UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::typeName( true, true  );
  }
};

/*! Specialization of Utility::TypeNameTraits for uniform distribution
 * \ingroup one_d_distributions
 * \ingroup type_name_traits
 */
template<>
struct TypeNameTraits<UniformDistribution>
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return UniformDistribution::typeName( true, false ); }
};

} // end Utility namespace

BOOST_DISTRIBUTION_CLASS_VERSION( UnitAwareUniformDistribution, 0 );
BOOST_DISTRIBUTION_CLASS_EXPORT_KEY2( UniformDistribution );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_UniformDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_UNIFORM_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_UniformDistribution.hpp
//---------------------------------------------------------------------------//
