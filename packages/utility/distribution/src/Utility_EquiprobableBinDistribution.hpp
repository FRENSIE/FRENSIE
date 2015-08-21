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
#include "Utility_ContractException.hpp"

namespace Utility{

//! The unit-aware equiprobable bin distribution class
template<typename IndependentUnit, typename DependentUnit>
class UnitAwareEquiprobableBinDistribution : public UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>,
					     public ParameterListCompatibleObject<UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit> >
{

private:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

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
  UnitAwareEquiprobableBinDistribution(
		   const UnitAwareEquiprobableBinDistribution& dist_instance );

  //! Copy constructor (copying from unitless distribution only)
  ENABLE_UNITLESS_COPY_CONSTRUCTOR_DEFAULT( UnitAwareEquiprobableBinDistribution );

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
  IndepQuantity sampleAndRecordTrials( unsigned& trials ) const;

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

  // The disribution type
  static const OneDDistributionType distribution_type = 
    EQUIPROBABLE_BIN_DISTRIBUTION;

  // The distribution
  Teuchos::Array<IndepQuantity> d_bin_boundaries;
};

// Return a random sample using the random number and record the bin index
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sampleImplementation( 
				            double random_number,
				            unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  double bin_location = random_number*(d_bin_boundaries.size()-1);
  
  sampled_bin_index = (unsigned)floor(bin_location);
  
  return d_bin_boundaries[sampled_bin_index] + 
    (bin_location - sampled_bin_index)*(d_bin_boundaries[sampled_bin_index+1]-
					d_bin_boundaries[sampled_bin_index]);
}

// Return a random sample from the distribution at the given CDF value in a subrange
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange( 
     const double random_number,
     const typename UnitAwareEquiprobableBinDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_bin_boundaries.front() );

  // Compute the scaled random number
  double scaled_random_number = 
    random_number*this->evaluateCDF( max_indep_var );

  unsigned dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

//! The equiprobable bin distribution (unit-agnostic)
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
