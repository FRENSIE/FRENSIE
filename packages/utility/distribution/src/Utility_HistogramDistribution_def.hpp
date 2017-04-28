//---------------------------------------------------------------------------//
//!
//! \file   Utility_HistogramDistribution_def.pp
//! \author Alex Robinson
//! \brief  Histogram distribution class definition.
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_HISTOGRAM_DISTRIBUTION_DEF_HPP
#define UTILITY_HISTOGRAM_DISTRIBUTION_DEF_HPP

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Utility{

// Explicit instantiation (extern declaration)
EXTERN_EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareHistogramDistribution<void,void> );

// Default constructor
template<typename IndependentUnit, typename DependentUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution()
{ /* ... */ }

// Basic constructor (potentially dangerous)
/*! \details The bin boundaries are assumed to be sorted (lowest to
 * highest). If cdf values are provided a pdf will be calculated. Note that
 * the first cdf value, which is always zero, should not be passed (N-1 cdf
 * values for N bin boundaries).
 */
template<typename IndependentUnit, typename DependentUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
				 const Teuchos::Array<double>& bin_boundaries,
				 const Teuchos::Array<double>& bin_values,
				 const bool interpret_dependent_values_as_cdf )
  : d_distribution( bin_boundaries.size() ),
    d_norm_constant( DNQT::one() )
{
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure the bin boundaries are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );
  // Make sure that for n bin boundaries there are n-1 bin values
  testPrecondition( bin_boundaries.size() - 1 == bin_values.size() );

  this->initializeDistribution( bin_boundaries,
				bin_values,
				interpret_dependent_values_as_cdf );
}

// CDF constructor
/*! \details The bin boundaries are assumed to be sorted (lowest to highest).
 * A pdf will be calculated from the cdf. Note that the first cdf value, which
 * is always zero, should not be passed (N-1 cdf values for N bin boundaries).
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
		      const Teuchos::Array<InputIndepQuantity>& bin_boundaries,
		      const Teuchos::Array<double>& cdf_values )
  : d_distribution( bin_boundaries.size() ),
    d_norm_constant( DNQT::one() )
{
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure the bin boundaries are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );
  // Make sure the cdf values are sorted
  testPrecondition( Sort::isSortedAscending( cdf_values.begin(),
					     cdf_values.end() ) );
  // Make sure that for n bin boundaries there are n-1 bin values
  testPrecondition( bin_boundaries.size() - 1 == cdf_values.size() );

  this->initializeDistributionFromCDF( bin_boundaries, cdf_values );
}

// Constructor
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
		      const Teuchos::Array<InputIndepQuantity>& bin_boundaries,
		      const Teuchos::Array<InputDepQuantity>& bin_values )
  : d_distribution( bin_boundaries.size() ),
    d_norm_constant( DNQT::one() )
{
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure the bin boundaries are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );
  // Make sure that for n bin boundaries there are n-1 bin values
  testPrecondition( bin_boundaries.size() - 1 == bin_values.size() );

  this->initializeDistribution( bin_boundaries, bin_values );
}

// Copy constructor
/*! \details Just like boost::units::quantity objects, the unit-aware
 * distribution can be explicitly cast to a distribution with compatible
 * units. If the units are not compatible, this function will not compile. Note
 * that this allows distributions to be scaled safely (unit conversions
 * are completely taken care of by boost::units)!
 */
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepUnit, typename InputDepUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
 const UnitAwareHistogramDistribution<InputIndepUnit,InputDepUnit>& dist_instance )
  : d_distribution(),
    d_norm_constant()
{
  // Make sure that the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  typedef typename UnitAwareHistogramDistribution<InputIndepUnit,InputDepUnit>::IndepQuantity InputIndepQuantity;

  typedef typename UnitAwareHistogramDistribution<InputIndepUnit,InputDepUnit>::DepQuantity InputDepQuantity;

  // Reconstruct the original input distribution
  Teuchos::Array<InputIndepQuantity> input_bin_boundaries;
  Teuchos::Array<InputDepQuantity> input_bin_values;

  dist_instance.reconstructOriginalDistribution( input_bin_boundaries,
						 input_bin_values );

  this->initializeDistribution( input_bin_boundaries, input_bin_values );
}

// Copy constructor (copying from unitless distribution only)
template<typename IndependentUnit, typename DependentUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::UnitAwareHistogramDistribution(
 const UnitAwareHistogramDistribution<void,void>& unitless_dist_instance, int )
  : d_distribution(),
    d_norm_constant()
{
  // Make sure that the distribution is valid
  testPrecondition( unitless_dist_instance.d_distribution.size() > 0 );

  // Reconstruct the original input distribution
  Teuchos::Array<double> input_bin_boundaries, input_bin_values;

  unitless_dist_instance.reconstructOriginalDistribution( input_bin_boundaries,
							  input_bin_values );

  this->initializeDistribution( input_bin_boundaries, input_bin_values, false );
}

// Construct distribution from a unitless dist. (potentially dangerous)
/*! \details Constructing a unit-aware distribution from a unitless
 * distribution is potentially dangerous. By forcing users to construct objects
 * using this method instead of a standard constructor we are trying to make
 * sure users are aware of the danger. This is designed to mimic the interface
 * of the boost::units::quantity, which also has to deal with this issue.
 */
template<typename IndependentUnit, typename DependentUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::fromUnitlessDistribution(
       const UnitAwareHistogramDistribution<void,void>& unitless_distribution )
{
  return ThisType( unitless_distribution, 0 );
}

// Assignment operator
template<typename IndependentUnit, typename DependentUnit>
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>&
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::operator=(
  const UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>& dist_instance )
{
  // Make sure that the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  if( this != &dist_instance )
  {
    d_distribution = dist_instance.d_distribution;
    d_norm_constant = dist_instance.d_norm_constant;
  }

  return *this;
}

// Evaluate the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::DepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::evaluate(
 const typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < Utility::get<FIRST>(d_distribution.front()) )
    return DQT::zero();
  else if( indep_var_value > Utility::get<FIRST>(d_distribution.back()) )
    return DQT::zero();
  else
  {
    typename DistributionArray::const_iterator bin =
      Search::binaryLowerBound<FIRST>( d_distribution.begin(),
                                       d_distribution.end(),
                                       indep_var_value );

    return Utility::get<SECOND>(*bin);
  }
}

// Evaluate the PDF
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::InverseIndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::evaluatePDF(
 const typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  return evaluate( indep_var_value )*d_norm_constant;
}

// Evaluate the CDF
template<typename IndependentUnit, typename DependentUnit>
double UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::evaluateCDF(
  const typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity indep_var_value ) const
{
  if( indep_var_value < Utility::get<FIRST>(d_distribution.front()) )
    return 0.0;
  else if( indep_var_value >= Utility::get<FIRST>(d_distribution.back()) )
    return 1.0;
  else
  {
    typename DistributionArray::const_iterator lower_bin =
      Search::binaryLowerBound<FIRST>( d_distribution.begin(),
                                       d_distribution.end(),
                                       indep_var_value );

    IndepQuantity indep_diff =
      indep_var_value - Utility::get<FIRST>(*lower_bin);

    return (Utility::get<THIRD>(*lower_bin) +
            Utility::get<SECOND>(*lower_bin)*indep_diff)*d_norm_constant;
  }
}

// Return a random sample from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sampleAndRecordTrials( DistributionTraits::Counter& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and bin index from the distribution
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sampleAndRecordBinIndex(
					    unsigned& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a random sample from the distribution at the given CDF value
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumber(
					     const double random_number ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sampleInSubrange(
   const typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );

  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
						 max_indep_var );
}

// Return a random sample using the random number and record the bin index
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sampleImplementation(
					    double random_number,
					    unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  UnnormCDFQuantity scaled_random_number =
    random_number*Utility::get<THIRD>(d_distribution.back());

  typename DistributionArray::const_iterator bin =
    Search::binaryLowerBound<THIRD>( d_distribution.begin(),
				     d_distribution.end(),
				     scaled_random_number );

  sampled_bin_index = std::distance( d_distribution.begin(), bin );

  return Utility::get<FIRST>(*bin) +
    IndepQuantity((scaled_random_number - Utility::get<THIRD>(*bin))/
                  Utility::get<SECOND>(*bin));
}

// Return a sample from the distribution at the given CDF value in a subrange
template<typename IndependentUnit, typename DependentUnit>
inline typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::sampleWithRandomNumberInSubrange(
  const double random_number,
  const typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );

  // Compute the scaled random number
  double scaled_random_number =
    random_number*this->evaluateCDF( max_indep_var );

  unsigned dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

// Return the upper bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::getUpperBoundOfIndepVar() const
{
  return Utility::get<FIRST>(d_distribution.back());
}

// Return the lower bound of the distribution independent variable
template<typename IndependentUnit, typename DependentUnit>
typename UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::IndepQuantity
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::getLowerBoundOfIndepVar() const
{
  return Utility::get<FIRST>(d_distribution.front());
}

// Return the distribution type
template<typename IndependentUnit, typename DependentUnit>
OneDDistributionType
UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::getDistributionType() const
{
  return UnitAwareHistogramDistribution::distribution_type;
}

//! Test if the distribution is continuous
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::toStream(
						       std::ostream& os ) const
{
  Teuchos::Array<double> bin_boundaries, bin_values;

  this->reconstructOriginalUnitlessDistribution( bin_boundaries,
						 bin_values );

  os << "{" << bin_boundaries << "," << bin_values << "}";
}

// Method for initializing the object from an input stream
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::fromStream(
							     std::istream& is )
{
  // Read the initial '{'
  std::string start_bracket;
  std::getline( is, start_bracket, '{' );
  start_bracket = Teuchos::Utils::trimWhiteSpace( start_bracket );

  TEST_FOR_EXCEPTION( start_bracket.size() != 0,
		      InvalidDistributionStringRepresentation,
		      "Error: the input stream is not a valid histogram "
		      "distribution representation!" );

  std::string bin_boundaries_rep;
  std::getline( is, bin_boundaries_rep, '}' );
  bin_boundaries_rep += "}";

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( bin_boundaries_rep );
    ArrayString::locateAndReplaceIntervalOperator( bin_boundaries_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the histogram distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  Teuchos::Array<double> bin_boundaries;
  try{
    bin_boundaries = Teuchos::fromStringToArray<double>( bin_boundaries_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the histogram distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( bin_boundaries.begin(),
						bin_boundaries.end() ),
		      InvalidDistributionStringRepresentation,
		      "Error: the histogram distribution cannot be "
		      "constructed because the bin boundaries "
		      << bin_boundaries_rep << " are not sorted!" );

  // Read the ","
  std::string separator;
  std::getline( is, separator, ',' );

  std::string bin_values_rep;
  std::getline( is, bin_values_rep, '}' );
  bin_values_rep += "}";

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( bin_values_rep );
    ArrayString::locateAndReplaceIntervalOperator( bin_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the histogram distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  Teuchos::Array<double> bin_values;
  try{
    bin_values = Teuchos::fromStringToArray<double>( bin_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the histogram distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( bin_boundaries.size()-1 != bin_values.size(),
		      InvalidDistributionStringRepresentation,
		      "Error: the histogram distribution "
		      "{" << bin_boundaries_rep << "},{"
		      << bin_values_rep << "} "
		      "cannot be constructed because the number of bin values "
		      "does not equal the number of bin boundaries - 1!" );

  this->initializeDistribution( bin_boundaries, bin_values, false );
}

// Method for testing if two objects are equivalent
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::isEqual(
 const UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>& other ) const
{
  return d_distribution == other.d_distribution &&
    d_norm_constant == other.d_norm_constant;
}

// Initialize the distribution
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
				  const Teuchos::Array<double>& bin_boundaries,
				 const Teuchos::Array<double>& bin_values,
				 const bool interpret_dependent_values_as_cdf )
{
  // Make sure that the bin boundaries are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure that for n bin boundaries there are n-1 bin values
  testPrecondition( bin_boundaries.size()-1 == bin_values.size() );

  // Convert the raw independent values to quantities
  Teuchos::Array<IndepQuantity> bin_boundary_quantities;

  this->convertUnitlessValues( bin_boundaries, bin_boundary_quantities );

  if( interpret_dependent_values_as_cdf )
  {
    this->initializeDistributionFromCDF( bin_boundary_quantities,
					 bin_values );
  }
  else
  {
    // Convert the raw bin values to quantities
    Teuchos::Array<DepQuantity> bin_quantities;

    this->convertUnitlessValues( bin_values, bin_quantities );

    this->initializeDistribution( bin_boundary_quantities,
				  bin_quantities );
  }
}

// Initialize the distribution from a cdf
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::initializeDistributionFromCDF(
		     const Teuchos::Array<InputIndepQuantity>& bin_boundaries,
		     const Teuchos::Array<double>& cdf_values )
{
  // Make sure that the bin boundaries are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );
  // Make sure that the bin values are sorted
  testPrecondition( Sort::isSortedAscending( cdf_values.begin(),
					     cdf_values.end() ) );
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure that for n bin boundaries there are n-1 bin values
  testPrecondition( bin_boundaries.size()-1 == cdf_values.size() );

  // Resize the distribution
  d_distribution.resize( bin_boundaries.size() );

  // Assign the first cdf value
  Utility::get<FIRST>(d_distribution[0]) = IndepQuantity( bin_boundaries[0] );
  setQuantity( Utility::get<THIRD>(d_distribution[0]), 0.0 );

    // Assign the distribution
    for( unsigned i = 1; i < bin_boundaries.size(); ++i )
    {
      Utility::get<FIRST>(d_distribution[i]) =
        IndepQuantity( bin_boundaries[i] );
      
      setQuantity( Utility::get<THIRD>(d_distribution[i]), cdf_values[i-1] );

      // Calculate the pdf from the cdf
      Utility::get<SECOND>(d_distribution[i-1]) =
        DepQuantity( (Utility::get<THIRD>(d_distribution[i]) -
                      Utility::get<THIRD>(d_distribution[i-1]))/
		     (Utility::get<FIRST>(d_distribution[i]) -
                      Utility::get<FIRST>(d_distribution[i-1])) );
    }

    // Last PDF value is unused and can be assigned to the second to last value
    Utility::get<SECOND>(d_distribution.back()) =
      Utility::get<SECOND>(d_distribution[d_distribution.size()-2]);

    // Set normalization constant
    d_norm_constant = 1.0/Utility::get<THIRD>(d_distribution.back());
}

// Initialize the distribution
template<typename IndependentUnit, typename DependentUnit>
template<typename InputIndepQuantity, typename InputDepQuantity>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::initializeDistribution(
		      const Teuchos::Array<InputIndepQuantity>& bin_boundaries,
		      const Teuchos::Array<InputDepQuantity>& bin_values )
{
  // Make sure that the bin boundaries are sorted
  testPrecondition( Sort::isSortedAscending( bin_boundaries.begin(),
					     bin_boundaries.end() ) );
  // Make sure there is at least one bin
  testPrecondition( bin_boundaries.size() > 1 );
  // Make sure that for n bin boundaries there are n-1 bin values
  testPrecondition( bin_boundaries.size()-1 == bin_values.size() );

  // Resize the distribution
  d_distribution.resize( bin_boundaries.size() );

  // Construct the distribution
  for( unsigned i = 0; i < bin_boundaries.size(); ++i )
  {
    // Assign the min and max bin boundaries (respectively)
    Utility::get<FIRST>(d_distribution[i]) =
      IndepQuantity( bin_boundaries[i] );

    // Assign the bin PDF value
    if( i < bin_boundaries.size() - 1 )
      Utility::get<SECOND>(d_distribution[i]) = DepQuantity( bin_values[i] );
    else
      Utility::get<SECOND>(d_distribution[i]) = DepQuantity( bin_values[i-1] );

    // Assign the discrete CDF value
    if( i > 0 )
    {
      Utility::get<THIRD>(d_distribution[i]) =
        Utility::get<THIRD>(d_distribution[i-1]);

      Utility::get<THIRD>(d_distribution[i]) += DepQuantity( bin_values[i-1] )*
        IndepQuantity( Utility::get<FIRST>(d_distribution[i]) -
                       Utility::get<FIRST>(d_distribution[i-1]) );
    }
    else
      setQuantity( Utility::get<THIRD>(d_distribution[i]), 0.0 );
  }

  // Assign the normalization constant
  d_norm_constant = 1.0/Utility::get<THIRD>(d_distribution.back());
}

// Reconstruct original distribution
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::reconstructOriginalDistribution(
			 Teuchos::Array<IndepQuantity>& bin_boundaries,
			 Teuchos::Array<DepQuantity>& bin_values ) const
{
  // Resize the arrays
  bin_boundaries.resize( d_distribution.size() );
  bin_values.resize( d_distribution.size()-1 );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    bin_boundaries[i] = Utility::get<FIRST>(d_distribution[i]);

    if( i < d_distribution.size() - 1 )
      bin_values[i] = Utility::get<SECOND>(d_distribution[i]);
  }
}

// Reconstruct original distribution w/o units
template<typename IndependentUnit, typename DependentUnit>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::reconstructOriginalUnitlessDistribution(
			      Teuchos::Array<double>& bin_boundaries,
			      Teuchos::Array<double>& bin_values ) const
{
  // Resize the arrays
  bin_boundaries.resize( d_distribution.size() );
  bin_values.resize( d_distribution.size()-1 );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    bin_boundaries[i] =
      getRawQuantity( Utility::get<FIRST>(d_distribution[i]) );

    if( i < d_distribution.size() - 1 )
    {
      bin_values[i] =
        getRawQuantity( Utility::get<SECOND>(d_distribution[i]) );
    }
  }
}

// Convert the unitless values to the correct units
template<typename IndependentUnit, typename DependentUnit>
template<typename Quantity>
void UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::convertUnitlessValues(
		                 const Teuchos::Array<double>& unitless_values,
				 Teuchos::Array<Quantity>& quantities )
{
  // Resize the quantity array
  quantities.resize( unitless_values.size() );

  // Copy the bin boundaries
  for( unsigned i = 0u; i < unitless_values.size(); ++i )
    setQuantity( quantities[i], unitless_values[i] );
}

// Test if the dependent variable can be zero within the indep bounds
template<typename IndependentUnit, typename DependentUnit>
bool UnitAwareHistogramDistribution<IndependentUnit,DependentUnit>::canDepVarBeZeroInIndepBounds() const
{
  bool possible_zero = false;
  
  for( size_t i = 0; i < d_distribution.size(); ++i )
  {
    if( Utility::get<SECOND>(d_distribution[i]) == DQT::zero() )
    {
      possible_zero = true;

      break;
    }
  }

  return possible_zero;
}

} // end Utility namespace

#endif // end UTILITY_HISTOGRAM_DISTRIBUTION_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_HistogramDistribution_def.hpp
//---------------------------------------------------------------------------//
