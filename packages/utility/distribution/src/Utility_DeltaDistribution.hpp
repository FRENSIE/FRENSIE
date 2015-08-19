//---------------------------------------------------------------------------//
//!
//! \file   Utility_DeltaDistribution.hpp
//! \author Alex Robinson
//! \brief  Delta distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DELTA_DISTRIBUTION_HPP
#define UTILITY_DELTA_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"

namespace Utility{

//! The unit-aware delta distribution class
template<typename IndependentUnit,typename DependentUnit>
class UnitAwareDeltaDistribution : public UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>,
				   public ParameterListCompatibleObject<UnitAwareDeltaDistribution<IndependentUnit,DependentUnit> >
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

  //! Default Constructor
  UnitAwareDeltaDistribution();
  
  //! Constructor
  template<typename InputIndepQuantity>
  UnitAwareDeltaDistribution( const InputIndepQuantity location );

  //! Copy constructor
  UnitAwareDeltaDistribution( const UnitAwareDeltaDistribution& dist_instance );

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

private:

  // The distribution type
  static const OneDDistributionType distribution_type = DELTA_DISTRIBUTION;

  // The location of the delta distribution
  IndepQuantity d_location;
};

//! The delta distribution (unit-agnostic)
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
 * xml files
 */
template<typename U,typename V>
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
