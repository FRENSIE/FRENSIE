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
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! The unit-aware exponential distribution class
/*! \details Only decaying exponential distributions are allowed (the
 * exponent is always assumed to be negative).
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareExponentialDistribution : public UnitAwareOneDDistribution<IndependentUnit,DependentUnit>,
					 public ParameterListCompatibleObject<UnitAwareExponentialDistribution<IndependentUnit,DependentUnit> >
{

private:

  // The distribution normalization quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DistNormQuantity DistNormQuantity;

  // Typedef for QuantityTraits<double>
  typedef QuantityTraits<double> QT;

  // Typedef for QuantityTraits<IndepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity> IQT;

  // Typedef for QuantityTraits<InverseIndepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity> IIQT;

  // Typedef for QuantityTraits<DepQuantity>
  typedef QuantityTraits<typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity> DQT;

public:

  //! This distribution type
  typedef UnitAwareExponentialDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;

  //! Default constructor
  UnitAwareExponentialDistribution();

  //! Constructor ( a*exp(-b*x), x E (c,d) )
  template<typename InputDepQuantity,
           typename InputInverseIndepQuantity,
	   typename InputIndepQuantity = IndepQuantity>
  UnitAwareExponentialDistribution(
			   const InputDepQuantity constant_multiplier,
			   const InputInverseIndepQuantity exponent_multiplier,
			   const InputIndepQuantity lower_limit =
                           QuantityTraits<InputIndepQuantity>::zero(),
                           const InputIndepQuantity upper_limit =
                           QuantityTraits<InputIndepQuantity>::inf());

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
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const;

  //! Return a random sample from the distribution
  static IndepQuantity sample( const InverseIndepQuantity exponent_multiplier);

  //! Return a random sample from the distribution
  static IndepQuantity sample( const InverseIndepQuantity exponent_multiplier,
			       const IndepQuantity lower_limit,
			       const IndepQuantity upper_limit = IQT::inf() );

  //! Return a random sample from the distribution
  IndepQuantity sample() const;

  //! Return a random sample and record the number of trials
  IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const;

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

  //! Test if the distribution is continuous
  bool isContinuous() const;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is );

  //! Method for testing if two objects are equivalent
  bool isEqual( const UnitAwareExponentialDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareExponentialDistribution( const UnitAwareExponentialDistribution<void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const;

private:

  // Initialize the distribution
  void initialize();

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareExponentialDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type =
    EXPONENTIAL_DISTRIBUTION;

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

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::ExponentialDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::ExponentialDistribution>
{
public:
  static std::string name()
  {
    return "Exponential Distribution";
  }
  static std::string concreteName(
			     const Utility::ExponentialDistribution& instance )
  {
    return name();
  }
};

/*! \brief Type name traits partial specialization for the
 * Utility::UnitAwareExponentialDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename U, typename V>
class TypeNameTraits<Utility::UnitAwareExponentialDistribution<U,V> >
{
public:
  static std::string name()
  {
    return "Unit-Aware Exponential Distribution (" +
      Utility::UnitTraits<U>::symbol() + "," +
      Utility::UnitTraits<V>::symbol() + ")";
  }
  static std::string concreteName(
	       const Utility::UnitAwareExponentialDistribution<U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_ExponentialDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_EXPONENTIAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_ExponentialDistribution.hpp
//---------------------------------------------------------------------------//
