//---------------------------------------------------------------------------//
//!
//! \file   Utility_ExponentialDistribution.hpp
//! \author Alex Robinson
//! \brief  Exponential distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_EXPONENTIAL_DISTRIBUTION_HPP
#define UTILITY_EXPONENTIAL_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_TypeNameTraits.hpp"

namespace Utility{

//! The unit-aware exponential distribution class
/*! \details Only decaying exponential distributions are allowed (the
 * exponent is always assumed to be negative).
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareExponentialDistribution : public UnitAwareOneDDistribution<IndependentUnit,DependentUnit>
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

public:

  //! This distribution type
  typedef UnitAwareExponentialDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename BaseType::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename BaseType::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename BaseType::DepQuantity DepQuantity;

  //! Constructor ( a*exp(-b*x), x E (c,d) )
  template<typename InputDepQuantity = DepQuantity,
           typename InputInverseIndepQuantity = InverseIndepQuantity,
	   typename InputIndepQuantity = IndepQuantity>
  UnitAwareExponentialDistribution(
         const InputDepQuantity constant_multiplier =
         ThisType::getDefaultConstMultiplier<InputDepQuantity>(),
         const InputInverseIndepQuantity exponent_multiplier =
         ThisType::getDefaultExponentMultiplier<InputInverseIndepQuantity>(),
         const InputIndepQuantity lower_limit =
         ThisType::getDefaultLowerLimit<InputIndepQuantity>(),
         const InputIndepQuantity upper_limit =
         ThisType::getDefaultUpperLimit<InputIndepQuantity>() );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareExponentialDistribution( const UnitAwareExponentialDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareExponentialDistribution fromUnitlessDistribution( const UnitAwareExponentialDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareExponentialDistribution& operator=(
		       const UnitAwareExponentialDistribution& dist_instance );

  //! Destructor
  ~UnitAwareExponentialDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const override;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const override;

  //! Return a random sample from the distribution
  static IndepQuantity sample( const InverseIndepQuantity exponent_multiplier);

  //! Return a random sample from the distribution
  static IndepQuantity sample( const InverseIndepQuantity exponent_multiplier,
			       const IndepQuantity lower_limit,
			       const IndepQuantity upper_limit = IQT::inf() );

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
  void fromStream( std::istream& is, const std::string& delims ) override;

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
  bool operator==( const UnitAwareEvaporationDistribution& other ) const;

  //! Inequality comparison operator
  bool operator!=( const UnitAwareEvaporationDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareExponentialDistribution( const UnitAwareExponentialDistribution<void,void>& unitless_dist_instance, int );

  //! Return the distribution type name
  std::string getDistributionTypeName( const bool verbose_name,
                                       const bool lowercase ) const override;

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const;

  //! Get the default constant multiplier
  template<typename InputDepQuantity>
  static InputDepQuantity getDefaultConstMultiplier()
  { return QuantityTraits<InputDepQuantity>::one(); }

  //! Get the default exponent multiplier
  template<typename InputInverseIndepQuantity>
  static InputInverseIndepQuantity getDefaultExponentMultiplier()
  { return QuantityTraits<InputInverseIndepQuantity>::one(); }

  //! Get the default lower limit
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultLowerLimit()
  { return QuantityTraits<InputIndepQuantity>::zero(); }

  //! Get the default upper limit
  template<typename InputIndepQuantity>
  static InputIndepQuantity getDefaultUpperLimit()
  { return QuantityTraits<InputIndepQuantity>::inf(); }

private:

  // Initialize the distribution
  void initialize();

  // Extract a shape parameter from a node
  template<typename QuantityType>
  static void extractShapeParameterFromNode(
                             const Utility::PropertyTree& shape_parameter_data,
                             QuantityType& shape_parameter );

  // Extract a shape parameter
  template<typename QuantityType>
  static void extractShapeParameter(
                                  const Utility::Variant& shape_parameter_data,
                                  QuantityType& shape_parameter );

  // Verify that the shape parameters are valid
  static void verifyValidShapeParameters(
                               const DepQuantity& const_multiplier,
                               const InverseIndepQuantity& exponent_multiplier,
                               const IndepQuantity& lower_limit,
                               const IndepQuantity& upper_limit );

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
  friend class UnitAwareExponentialDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type =
    EXPONENTIAL_DISTRIBUTION;

  // The constant multiplier value key (used in property trees)
  static const std::string s_const_multiplier_value_key;

  // The constant multiplier min match string (used in property trees)
  static const std::string s_const_multiplier_value_min_match_string;

  // The exponent multiplier value key (used in property trees)
  static const std::string s_exponent_multiplier_value_key;

  // The exponent multiplier min match string (used in property trees)
  static const std::string s_exponent_multiplier_value_min_match_string;

  // The lower limit value key (used in property trees)
  static const std::string s_lower_limit_value_key;

  // The lower limit min match string (used in property trees)
  static const std::string s_lower_limit_value_min_match_string;

  // The upper limit value key (used in property trees)
  static const std::string s_upper_limit_value_key;

  // The upper limit min match string (used in property trees)
  static const std::string s_upper_limit_value_min_match_string;

  // The constant multiplier
  DepQuantity d_constant_multiplier;

  // The exponent multiplier
  InverseIndepQuantity d_exponent_multiplier;

  // The lower limit
  IndepQuantity d_lower_limit;

  // The upper limit
  IndepQuantity d_upper_limit;

  // The exponential evaluated at the lower limit (exp(-b*c))
  double d_exp_lower_limit;

  // The exponential evaluated at the upper limit (exp(-b*d))
  double d_exp_upper_limit;
};

/*! The exponential distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareExponentialDistribution<void,void> ExponentialDistribution;

/*! Partial specialization of Utility::TypeNameTraits for unit aware
 * evaporation distribution
 * \ingroup one_d_distributions
 * \ingroup type_name_traits
 */
template<typename IndependentUnit,typename DependentUnit>
struct TypeNameTraits<UnitAwareExponentialDistribution<IndependentUnit,DependentUnit> >
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  {
    return UnitAwareExponentialDistribution<IndependentUnit,DependentUnit>::typeName( true, true  );
  }
};

/*! Specialization of Utility::TypeNameTraits for evaporation distribution
 * \ingroup one_d_distributions
 * \ingroup type_name_traits
 */
template<>
struct TypeNameTraits<ExponentialDistribution>
{
  //! Check if the type has a specialization
  typedef std::true_type IsSpecialized;

  //! Get the type name
  static inline std::string name()
  { return ExponentialDistribution::typeName( true, false ); }
};
  
} // end Utility namespace

BOOST_DISTRIBUTION_CLASS_VERSION( UnitAwareExponentialDistribution, 0 );
BOOST_DISTRIBUTION_CLASS_EXPORT_KEY2( ExponentialDistribution );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_ExponentialDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_EXPONENTIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_ExponentialDistribution.hpp
//---------------------------------------------------------------------------//
