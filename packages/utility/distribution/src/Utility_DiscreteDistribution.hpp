//---------------------------------------------------------------------------//
//!
//! \file   Utility_DiscreteDistribution.hpp
//! \author Alex Robinson
//! \brief  Discrete distribution class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_DISCRETE_DISTRIBUTION_HPP
#define UTILITY_DISCRETE_DISTRIBUTION_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_TabularOneDDistribution.hpp"
#include "Utility_ParameterListCompatibleObject.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

//! The unit-aware discrete distribution class
template<typename IndependentUnit,typename DependentUnit>
class UnitAwareDiscreteDistribution : public UnitAwareTabularOneDDistribution<IndependentUnit,DependentUnit>,
				      public ParameterListCompatibleObject<UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit> >
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
  UnitAwareDiscreteDistribution();

  //! Basic Constructor (potentially dangerous)
  UnitAwareDiscreteDistribution(
			const Teuchos::Array<double>& independent_values,
			const Teuchos::Array<double>& dependent_values,
			const bool interpret_dependent_values_as_cdf = false );

  //! Hybrid Constructor (implicit unit info potentially dangerous)
  template<typename InputIndepQuantity>
  UnitAwareDiscreteDistribution( 
	      const Teuchos::Array<InputIndepQuantity>& independent_quantities,
	      const Teuchos::Array<double>& dependent_values,
	      const bool interpret_dependent_values_as_cdf = false );

  //! Constructor
  template<typename InputIndepQuantity, typename InputDepQuantity>
  UnitAwareDiscreteDistribution( 
	      const Teuchos::Array<InputIndepQuantity>& independent_quantities,
	      const Teuchos::Array<InputDepQuantity>& dependent_quantities );
			
  
  //! Copy constructor
  UnitAwareDiscreteDistribution( const UnitAwareDiscreteDistribution& dist_instance );

  //! Assignment operator
  UnitAwareDiscreteDistribution& operator=( const UnitAwareDiscreteDistribution& dist_instance );

  //! Destructor
  ~UnitAwareDiscreteDistribution()
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

  //! Return a random sample and sampled index from the distribution
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

  //! Return the lower bound of the independent variable
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
  bool isEqual( const UnitAwareDiscreteDistribution& other ) const;

private:

  // Return a random sample using the random number and record the bin index
  IndepQuantity sampleImplementation( double random_number,
				      unsigned& sampled_bin_index ) const;

  // Initialize the distribution
  template<typename InputIndepQuantity,typename InputDepQuantity>
  void initializeDistribution( 
	      const Teuchos::Array<InputIndepQuantity>& independent_quantities,
	      const Teuchos::Array<InputDepQuantity>& dependent_quantities,
	      const bool interpret_dependent_values_as_cdf );

  // Initialize the distribution independent values
  void initializeDistributionIndepValues( 
		            const Teuchos::Array<double>& independent_values );

  // Initialize the distribution independent values
  template<typename InputIndepQuantity>
  void initializeDistributionIndepValues(
	    const Teuchos::Array<InputIndepQuantity>& independent_quantities );

  // Initialize the distribution dependent values
  void initializeDistributionDepValues(
				const Teuchos::Array<double>& dependent_values,
				const bool interpret_dependent_values_as_cdf );

  // Initialize the distribution dependent values
  template<typename InputDepQuantity>
  void initializeDistributionDepValues(
		  const Teuchos::Array<InputDepQuantity>& dependent_quantities,
		  const bool interpret_dependent_values_as_cdf );

  // The distribution type
  static const OneDDistributionType distribution_type = DISCRETE_DISTRIBUTION;

  // The distribution (first = independent value, second = CDF)
  Teuchos::Array<Pair<IndepQuantity,double> > d_distribution;

  // The distribution normalization constant
  DepQuantity d_norm_constant;
};

// Return a random sample using the random number and record the bin index
template<typename IndependentUnit,typename DependentUnit>
inline typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleImplementation( 
					    double random_number,
					    unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  
  typename Teuchos::Array<Pair<IndepQuantity,double> >::const_iterator sample =
    Search::binaryUpperBound<SECOND>( d_distribution.begin(),
				      d_distribution.end(),
				      random_number );

  // Get the bin index sampled
  sampled_bin_index = std::distance( d_distribution.begin(), sample );

  return sample->first;
}

// Return a random sample from the distribution at the given CDF value in a subrange
template<typename IndependentUnit,typename DependentUnit>
inline typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange( 
   const double random_number,
   const typename UnitAwareDiscreteDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the max independent variable is valid
  testPrecondition( max_indep_var >= d_distribution.front().first );

  // Scale the random number to the cdf at the max indep var
  double scaled_random_number = 
    random_number*this->evaluateCDF( max_indep_var );

  unsigned dummy_index;
  
  return this->sampleImplementation( scaled_random_number, dummy_index );
}

//! The discrete distribution (unit-agnostic)
typedef UnitAwareDiscreteDistribution<void,void> DiscreteDistribution;

} // end Utility namespace

namespace Teuchos{

/*! Type name traits specialization for the Utility::DiscreteDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<>
class TypeNameTraits<Utility::DiscreteDistribution>
{
public:
  static std::string name()
  {
    return "Discrete Distribution";
  }
  static std::string concreteName( 
				const Utility::DiscreteDistribution& instance )
  {
    return name();
  }
};

/*! \brief Type name traits partial specialization for the 
 * Utility::UnitAwareDiscreteDistribution
 *
 * \details The name function will set the type name that must be used in
 * xml files.
 */
template<typename U,typename V>
class TypeNameTraits<Utility::UnitAwareDiscreteDistribution<U,V> >
{
public:
  static std::string name()
  {
    return "Unit-Aware Discrete Distribution (" +
      Utility::UnitTraits<U>::symbol() + "," +
      Utility::UnitTraits<V>::symbol() + ")";
  }
  static std::string concreteName(
		  const Utility::UnitAwareDiscreteDistribution<U,V>& instance )
  {
    return name();
  }
};

} // end Teuchos namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "Utility_DiscreteDistribution_def.hpp"

//---------------------------------------------------------------------------//

#endif // end UTILITY_DISCRETE_DISTRIBUTION_HPP

//---------------------------------------------------------------------------//
// end Utility_DiscreteDistribution.hpp
//---------------------------------------------------------------------------//
