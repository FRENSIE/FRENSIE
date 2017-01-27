//---------------------------------------------------------------------------//
//!
//! \file   Utility_EquiprobableBinDistribution.hpp
//! \author Alex Robinson
//! \brief  Equiprobable bin distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef TWO_EQUIPROBABLE_BIN_DISTRIBUTION_HPP
#define TWO_EQUIPROBABLE_BIN_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"

namespace Utility{

/*! The unit-aware equiprobable bin distribution class
 * \ingroup one_d_distributions
 */
template<typename IndependentUnit, typename DependentUnit = void>
class UnitAwareEquiprobableBinDistribution : public UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>,
					     public ParameterListCompatibleObject<UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit> >
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
  typedef UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit> ThisType;

  //! The independent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::IndepQuantity IndepQuantity;

  //! The inverse independent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity InverseIndepQuantity;

  //! The dependent quantity type
  typedef typename UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>::DepQuantity DepQuantity;

  //! Default constructor
  UnitAwareEquiprobableBinDistribution();

  //! Basic constructor (potentially dangerous)
  explicit UnitAwareEquiprobableBinDistribution( const Teuchos::Array<double>& bin_boundaries);

  //! Constructor
  template<typename InputIndepQuantity>
  explicit UnitAwareEquiprobableBinDistribution( const Teuchos::Array<InputIndepQuantity>& bin_boundaries );

  //! Copy constructor
  template<typename InputIndepUnit, typename InputDepUnit>
  UnitAwareEquiprobableBinDistribution(
      const UnitAwareEquiprobableBinDistribution<InputIndepUnit,InputDepUnit>& dist_instance );

  //! Construct distribution from a unitless dist. (potentially dangerous)
  static UnitAwareEquiprobableBinDistribution fromUnitlessDistribution( const UnitAwareEquiprobableBinDistribution<void,void>& unitless_distribution );

  //! Assignment operator
  UnitAwareEquiprobableBinDistribution& operator=(
		   const UnitAwareEquiprobableBinDistribution& dist_instance );

  //! Destructor
  ~UnitAwareEquiprobableBinDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const;

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const;

  //! Evaluate the CDF
  double evaluateCDF( const IndepQuantity indep_var_value ) const;

  //! Return a random sample from the distribution
  IndepQuantity sample() const;

  //! Return a random sample and record the number of trials
  IndepQuantity sampleAndRecordTrials( DistributionTraits::Counter& trials ) const;

  //! Return a random sample from the distribution at the given CDF value
  IndepQuantity sampleWithRandomNumber( const double random_number ) const;

  //! Return a random sample and sampled index from the corresponding CDF
  IndepQuantity sampleAndRecordBinIndex( unsigned& sampled_bin_index ) const;

  //! Return a random sample from the corresponding CDF in a subrange
  IndepQuantity sampleInSubrange( const IndepQuantity max_indep_var ) const;

  //! Return a random sample from the distribution at the given CDF value in a subrange
  IndepQuantity sampleWithRandomNumberInSubrange(
				     const double random_number,
				     const IndepQuantity max_indep_var ) const;

  //! Return the upper bound of the distribution independent variable
  IndepQuantity getUpperBoundOfIndepVar() const;

  //! Return a random sample from the distribution and the sampled index
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
  bool isEqual( const UnitAwareEquiprobableBinDistribution& other ) const;

protected:

  //! Copy constructor (copying from unitless distribution only)
  UnitAwareEquiprobableBinDistribution( const UnitAwareEquiprobableBinDistribution<void,void>& unitless_dist_instance, int );

  //! Test if the dependent variable can be zero within the indep bounds
  bool canDepVarBeZeroInIndepBounds() const;

private:

  // Return a random sample using the random number and record the bin index
  IndepQuantity sampleImplementation( double random_number,
				      unsigned& sampled_bin_index ) const;

  // Initialize the distribution
  void initializeDistribution( const Teuchos::Array<double>& bin_boundaries );

  // Initialize the distribution
  template<typename InputIndepQuantity>
  void initializeDistribution(
		    const Teuchos::Array<InputIndepQuantity>& bin_boundaries );

  // All possible instantiations are friends
  template<typename FriendIndepUnit, typename FriendDepUnit>
  friend class UnitAwareEquiprobableBinDistribution;

  // The disribution type
  static const OneDDistributionType distribution_type =
    EQUIPROBABLE_BIN_DISTRIBUTION;

  // The distribution
  Teuchos::Array<IndepQuantity> d_bin_boundaries;
};

/*! The equiprobable bin distribution (unit-agnostic)
 * \ingroup one_d_distributions
 */
typedef UnitAwareEquiprobableBinDistribution<void,void> EquiprobableBinDistribution;

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the
 * Utility::EquiprobableBinDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::EquiprobableBinDistribution>
{
public:
  static std::string name()
  {
    return "Equiprobable Bin Distribution";
  }
  static std::string concreteName(
		const Utility::EquiprobableBinDistribution& instance )
  {
    return name();
  }
};

/*! \brief Type name traits partial specialization for the
 * Utility::UnitAwareEquiprobableBinDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename U,typename V>
class TypeNameTraits<Utility::UnitAwareEquiprobableBinDistribution<U,V> >
{
public:
  static std::string name()
  {
    return "Unit-Aware Equiprobable Bin Distribution (" +
      Utility::UnitTraits<U>::symbol() + "," +
      Utility::UnitTraits<V>::symbol() + ")";
  }
  static std::string concreteName(
	   const Utility::UnitAwareEquiprobableBinDistribution<U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_EquiprobableBinDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end EQUIPROBABLE_BIN_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_EquiprobableBinDistribution.hpp
//---------------------------------------------------------------------------//
