//---------------------------------------------------------------------------//
//!
//! \file   Utility_UniformDistribution.hpp
//! \author Alex Robinson
//! \brief  Uniform distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_UNIFORM_DISTRIBUTION_HPP
#define UTILITY_UNIFORM_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! Uniform distribution class
template<typename IndependentUnit, typename DependentUnit>
class UnitAwareUniformDistribution : public UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>,
			    public ParameterListCompatibleObject<UnitAwareUniformDistribution<IndependentUnit,DependentUnit> >
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
  UnitAwareUniformDistribution();
 
  //! Constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareUniformDistribution(const InputIndepQuantity& min_independent_value,
			       const InputIndepQuantity& max_independent_value,
			       const InputDepQuantity& dependent_value );

  //! Copy constructor
  UnitAwareUniformDistribution( const UnitAwareUniformDistribution& dist_instance );

  //! Assignment operator
  UnitAwareUniformDistribution& operator=( const UnitAwareUniformDistribution& dist_instance );
  
  //! Destructor
  ~UnitAwareUniformDistribution()
  { /* ... */ }

  //! Evaluate the distribution
  DepQuantity evaluate( const IndepQuantity indep_var_value ) const;  

  //! Evaluate the PDF
  InverseIndepQuantity evaluatePDF( const IndepQuantity indep_var_value ) const;

  //! Evaluate the CDF
  double evaluateCDF( const IndepQuantity indep_var_value ) const;

  //! Return a random sample from the distribution
  IndepQuantity sample() const;

  //! Return a random sample from the corresponding CDF and record the number of trials
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

  //! Return the lower bound of the distribution independent variable
  IndepQuantity getLowerBoundOfIndepVar() const;

  //! Return the distribution type
  OneDDistributionType getDistributionType() const;

  // Test if the distribution is continuous
  bool isContinuous() const;

  //! Method for placing the object in an output stream
  void toStream( std::ostream& os ) const;

  //! Method for initializing the object from an input stream
  void fromStream( std::istream& is );

  //! Method for testing if two objects are equivalent
  bool isEqual( const UnitAwareUniformDistribution<IndependentUnit,DependentUnit>& other ) const;

private:

  // The distribution type
  static const OneDDistributionType distribution_type = UNIFORM_DISTRIBUTION;

  // The min independent value
  IndepQuantity d_min_independent_value;
  
  // The max independent value
  IndepQuantity d_max_independent_value;

  // The uniform distribution dependent value
  DepQuantity d_dependent_value;

  // The uniform distribution PDF value
  InverseIndepQuantity d_pdf_value;
};

// Return a random sample from the distribution at the given CDF value
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumber( 
					     const double random_number ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  return random_number*(d_max_independent_value - d_min_independent_value) +
    d_min_independent_value;
}

// Return a random sample from the distribution at the given CDF value in a subrange
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange( 
	    const double random_number,
	    const typename UnitAwareUniformDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the upper bound of the subrange is valid
  testPrecondition( max_indep_var <= d_max_independent_value );
  testPrecondition( max_indep_var >= d_min_independent_value );

  return random_number*(max_indep_var - d_min_independent_value) + 
    d_min_independent_value;
}

//! The unit-agnostic uniform distribution
typedef UnitAwareUniformDistribution<void,void> UniformDistribution;

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::UniformDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::UniformDistribution>
{
public:
  static std::string name()
  {
    return "Uniform Distribution";
  }
  static std::string concreteName( 
			     const Utility::UniformDistribution& instance )
  {
    return name();
  }
};

} // end Teuchos namespace 

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_UniformDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_UNIFORM_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_UniformDistribution.hpp
//---------------------------------------------------------------------------//
