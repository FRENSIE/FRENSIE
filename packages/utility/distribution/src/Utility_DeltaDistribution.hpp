//---------------------------------------------------------------------------//
//!
//! \file   Utility_DeltaDistribution.hpp
//! \author Alex Robinson
//! \brief  Delta distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DELTA_DISTRIBUTION_HPP
#define UTILITY_DELTA_DISTRIBUTION_HPP

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

/*! The unit-aware delta distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit>
class UnitAwareDeltaDistribution : public UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>,
				   public ParameterListCompatibleObject<UnitAwareDeltaDistribution<IndependentUnit,DependentUnit> >
{

private:
  
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
  typedef UnitAwareDeltaDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;

  //! Default Constructor
  UnitAwareDeltaDistribution();
  
  //! Basic constructor
  template<typename InputIndepQuantity>
  explicit UnitAwareDeltaDistribution( const InputIndepQuantity location );

  //! Advanced constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareDeltaDistribution( const InputIndepQuantity location,
			      const InputDepQuantity multiplier );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit, typename Dummy=void>
  UnitAwareDeltaDistribution( const UnitAwareDeltaDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareDeltaDistribution fromUnitlessDistribution( const UnitAwareDeltaDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareDeltaDistribution& operator=( const UnitAwareDeltaDistribution& dist_instance );

  //! Destructor
  ~UnitAwareDeltaDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const;

  //! Evaulate the CDF
  double evaluateCDF( const IndepQuantity indep_var_value ) const;

  //! Return a random sample from the corresponding CDF
  IndepQuantity sample() const;

  //! Return a random sample from the corresponding CDF and record the number of trials
  IndepQuantity sampleAndRecordTrials( unsigned& trials ) const;

  //! Return a random sample from the distribution and the sampled index 
  IndepQuantity sampleAndRecordBinIndex( unsigned& sampled_bin_index ) const;

  //! Return a random sample from the distribution at the given CDF value
  IndepQuantity sampleWithRandomNumber( const double random_number ) const;

  //! Return a random sample from the distribution in a subrange
  IndepQuantity sampleInSubrange( const IndepQuantity max_indep_var ) const;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  IndepQuantity sampleWithRandomNumberInSubrange( 
				     const double random_number,
				     const IndepQuantity max_indep_var ) const;

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
  bool isEqual( const UnitAwareDeltaDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareDeltaDistribution( const UnitAwareDeltaDistribution<void,void>& unitless_dist_instance, int );

private:

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareDeltaDistribution;

  // The distribution type
  static const OneDDistributionType distribution_type = DELTA_DISTRIBUTION;

  // The location of the delta distribution
  IndepQuantity d_location;

  // The multiplier
  DepQuantity d_multiplier;
};

/*! The delta distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareDeltaDistribution<void,void> DeltaDistribution;

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::DeltaDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::DeltaDistribution>
{
public:
  static std::string name()
  {
    return "Delta Distribution";
  }
  static std::string concreteName( const Utility::DeltaDistribution& instance )
  {
    return name();
  }
};

/*! \brief Type name traits partial specialization for the 
 * Utility::UnitAwareDeltaDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename U, typename V>
class TypeNameTraits<Utility::UnitAwareDeltaDistribution<U,V> >
{
public:
  static std::string name()
  {
    return "Unit-Aware Delta Distribution (" +
      Utility::UnitTraits<U>::symbol() + "," +
      Utility::UnitTraits<V>::symbol() + ")";
  }
  static std::string concreteName(
		     const Utility::UnitAwareDeltaDistribution<U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_DeltaDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_DELTA_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_DeltaDistribution.hpp
//---------------------------------------------------------------------------//
