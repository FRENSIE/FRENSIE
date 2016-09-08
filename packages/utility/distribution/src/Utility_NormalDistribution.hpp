//---------------------------------------------------------------------------//
//!
//! \file   Utility_NormalDistribution.hpp
//! \author Alex Robinson
//! \brief  Normal distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_NORMAL_DISTRIBUTION_HPP
#define UTILITY_NORMAL_DISTRIBUTION_HPP

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"

namespace Utility{

//! Normal distribution class
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareNormalDistribution : public UnitAwareOneDDistribution<IndependentUnit,DependentUnit>,
				    public ParameterListCompatibleObject<UnitAwareNormalDistribution<IndependentUnit,DependentUnit> >
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
  typedef UnitAwareNormalDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;

  //! Constructor ( a*exp(-[x-meam]^2/[2*sigma]^2), x E (b,c) )
  template<typename InputDepQuantity = DepQuantity,
	   typename InputIndepQuantityA = IndepQuantity,
	   typename InputIndepQuantityB = IndepQuantity,
	   typename InputIndepQuantityC = IndepQuantity>
  UnitAwareNormalDistribution(const InputIndepQuantityA mean =
                              QuantityTraits<InputIndepQuantityA>::zero(),
                              const InputIndepQuantityB standard_deviation =
                              QuantityTraits<InputIndepQuantityB>::one(),
                              const InputDepQuantity constant_multiplier =
                              QuantityTraits<InputDepQuantity>::one(),
                              const InputIndepQuantityC min_independent_value =
                              -QuantityTraits<InputIndepQuantityC>::inf(),
			      const InputIndepQuantityC max_independent_value =
                              QuantityTraits<InputIndepQuantityC>::inf() );


  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareNormalDistribution( const UnitAwareNormalDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareNormalDistribution fromUnitlessDistribution( const UnitAwareNormalDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareNormalDistribution& operator=( const UnitAwareNormalDistribution& dist_instance );

  //! Destructor
  ~UnitAwareNormalDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const;

  //! Return a random sample from the distribution
  static IndepQuantity sample( const IndepQuantity mean,
			       const IndepQuantity standard_deviation,
			       const IndepQuantity min_independent_value =
			       -QuantityTraits<IndepQuantity>::inf(),
			       const IndepQuantity max_independent_value =
			       QuantityTraits<IndepQuantity>::inf() );

  //! Return a random sample from the distribution and record the trials
  static IndepQuantity sampleAndRecordTrials(
			       unsigned& trials,
			       const IndepQuantity mean,
			       const IndepQuantity standard_deviation,
			       const IndepQuantity min_independent_value =
			       -QuantityTraits<IndepQuantity>::inf(),
			       const IndepQuantity max_independent_value =
			       QuantityTraits<IndepQuantity>::inf() );

  //! Return a random sample from the distribution
  IndepQuantity sample() const;

  //! Return a random sample from the distribution and record the trials
  IndepQuantity sampleAndRecordTrials( unsigned& trials ) const;

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
  bool isEqual( const UnitAwareNormalDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareNormalDistribution( const UnitAwareNormalDistribution<void,void>& unitless_dist_instance, int );

private:

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareNormalDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type = NORMAL_DISTRIBUTION;

  // Constant normalization factor (1/sqrt(2*pi))
  static const double constant_norm_factor;

  // The constant multiplier
  DepQuantity d_constant_multiplier;

  // The mean of the distribution
  IndepQuantity d_mean;

  // The standard deviation of the distribution
  IndepQuantity d_standard_deviation;

  // The min independent value
  IndepQuantity d_min_independent_value;

  // The max independent value
  IndepQuantity d_max_independent_value;
};

/*! The normal distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareNormalDistribution<void,void> NormalDistribution;

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::NormalDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::NormalDistribution>
{
public:
  static std::string name()
  {
    return "Normal Distribution";
  }
  static std::string concreteName(
				const Utility::NormalDistribution& instance )
  {
    return name();
  }
};

/*! \brief Type name traits partial specialization for the
 * Utility::UnitAwareNormalDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename U, typename V>
class TypeNameTraits<Utility::UnitAwareNormalDistribution<U,V> >
{
public:
  static std::string name()
  {
    return "Unit-Aware Normal Distribution (" +
      Utility::UnitTraits<U>::symbol() + "," +
      Utility::UnitTraits<V>::symbol() + ")";
  }
  static std::string concreteName(
		    const Utility::UnitAwareNormalDistribution<U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_NormalDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_NORMAL_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_NormalDistribution.hpp
//---------------------------------------------------------------------------//
