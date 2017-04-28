//---------------------------------------------------------------------------//
//!
//! \file   Utility_ElasticElectronDistribution_def.hpp
//! \author Luke Kersting
//! \brief  Tabular distribution for elastic electron scattering class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ELASTIC_ELECTRONDISTRIBUTION_DEF_HPP
#define UTILITY_ELASTIC_ELECTRONDISTRIBUTION_DEF_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>

// FRENSIE Includes
#include "Utility_DataProcessor.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_KinematicHelpers.hpp"

namespace Utility{

// The cutoff angle above which the screened Rutherford distribution is sampled
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::s_sr_angle = 1.0e-6;

// Default constructor
template<typename InterpolationPolicy>
ElasticElectronDistribution<InterpolationPolicy>::ElasticElectronDistribution()
{ /* ... */ }

// Constructor for ENDL tables data given as PDF
/*! \details The independent values, x, are the scattering angle in units of pi
 * ie: x = (1 - mu), where mu is the scattering angle cosine.
 * They range from 0 (forward scattering) to 2 (backscattering) ( 0 <= x <= 2 )
 * They are assumed to be sorted (lowest to highest).
 */
template<typename InterpolationPolicy>
ElasticElectronDistribution<InterpolationPolicy>::ElasticElectronDistribution(
                       const Teuchos::Array<double>& independent_values,
		               const Teuchos::Array<double>& dependent_values,
                       const double moliere_screening_constant,
                       const double screened_rutherford_normalization_constant )
  : d_moliere_screening_constant( moliere_screening_constant ),
    d_screened_rutherford_normalization_constant( screened_rutherford_normalization_constant ),
    d_distribution( independent_values.size() ),
    d_norm_constant( 0.0 )
{
  // Make sure the screened_rutherford_normalization_constant
  testPrecondition( screened_rutherford_normalization_constant > 0 );
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that for n bin boundaries there are n bin values
  testPrecondition( independent_values.size() == dependent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
			       independent_values.end() ) );
  // Make sure that the independent_values are valid
  testPrecondition( independent_values.front() >= 0.0 );
  testPrecondition( independent_values.back() <= 2.0 );
  // Make sure that the dependent values are valid
  testPrecondition( dependent_values.front() >= 0.0 );

  initializeDistributionENDL( independent_values, dependent_values );
}


// Constructor for ACE tables data given as CDF
  /*! \details For ACE tables data the independent values must be changed from
   * the angle cosine (mu) to angle (x) in units of pi ( x = 1 - mu )
   * The dependent values must also be changed to be in reverse ascending order
   * where: cdf(x) = 1 - cdf(mu)
   */
template<typename InterpolationPolicy>
ElasticElectronDistribution<InterpolationPolicy>::ElasticElectronDistribution(
			      const Teuchos::Array<double>& independent_values,
			      const Teuchos::Array<double>& dependent_values,
                  const double energy,
                  const int atomic_number )
  : d_energy( energy ),
    d_atomic_number( atomic_number ),
    d_Z_two_thirds_power( pow( atomic_number, 2.0/3.0 ) ),
    d_distribution( independent_values.size() ),
    d_norm_constant( 0.0 )
{
  // Make sure the energy is valid
  testPrecondition( energy > 0 );
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0u );
  testPrecondition( atomic_number <= 100u );
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that for n bin boundaries there are n bin values
  testPrecondition( independent_values.size() == dependent_values.size() );
  // Make sure that the bins are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
			       independent_values.end() ) );
  // Make sure that the bin values are sorted
  testPrecondition( Sort::isSortedAscending( dependent_values.begin(),
			        dependent_values.end() ) );
  // Make sure that the independent values are valid
  testPrecondition( independent_values.front() >= -1.0 );
  testPrecondition( independent_values.back() <= 1.0 );
  // Make sure that the dependent values are valid
  testPrecondition( dependent_values.front() >= 0.0 );
  testPrecondition( dependent_values.back() <= 1.0 );

  initializeDistributionACE( independent_values, dependent_values );
}

// Copy constructor
template<typename InterpolationPolicy>
ElasticElectronDistribution<InterpolationPolicy>::ElasticElectronDistribution(
		const ElasticElectronDistribution<InterpolationPolicy>& dist_instance )
  : d_distribution( dist_instance.d_distribution ),
    d_norm_constant( dist_instance.d_norm_constant )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );
}

// Assignment operator
template<typename InterpolationPolicy>
ElasticElectronDistribution<InterpolationPolicy>&
ElasticElectronDistribution<InterpolationPolicy>::operator=(
		const ElasticElectronDistribution<InterpolationPolicy>& dist_instance )
{
  // Make sure the distribution is valid
  testPrecondition( dist_instance.d_distribution.size() > 0 );

  if( this != &dist_instance )
  {
    d_distribution = dist_instance.d_distribution;
    d_norm_constant = dist_instance.d_norm_constant;
  }

  return *this;
}

// Evaluate the distribution
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::evaluate(
					   const double indep_var_value ) const
{
  return evaluatePDF( indep_var_value );
}

// Evaluate the PDF
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::evaluatePDF(
					   const double indep_var_value ) const
{
  if( indep_var_value < 0.0 )
    return 0.0;
  else if( indep_var_value < s_sr_angle )
  {
    return d_screened_rutherford_normalization_constant/(
            ( indep_var_value + d_moliere_screening_constant )*
            ( indep_var_value + d_moliere_screening_constant ) );
  }
  else if( indep_var_value > Utility::get<0>( d_distribution.back() ) )
    return 0.0;
  else if( indep_var_value == Utility::get<0>( d_distribution.back() ) )
    return Utility::get<2>( d_distribution.back() );
  else
  {
    DistributionArray::const_iterator start, end, lower_bin_boundary,
      upper_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							  end,
							  indep_var_value );

    upper_bin_boundary = lower_bin_boundary;
    ++upper_bin_boundary;

    double lower_indep_value = Utility::get<0>( *lower_bin_boundary );
    double lower_pdf_value = Utility::get<2>( *lower_bin_boundary );
    double upper_indep_value = Utility::get<0>( *upper_bin_boundary );
    double upper_pdf_value = Utility::get<2>( *upper_bin_boundary );

    return InterpolationPolicy::interpolate( lower_indep_value,
					     upper_indep_value,
					     indep_var_value,
					     lower_pdf_value,
					     upper_pdf_value );
  }
}

// Evaluate the CDF
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::evaluateCDF(
					   const double indep_var_value ) const
{
  if( indep_var_value < 0.0 )
    return 0.0;
  else if( indep_var_value < s_sr_angle )
  {
    return indep_var_value*d_screened_rutherford_normalization_constant/(
            d_moliere_screening_constant*
            ( indep_var_value + d_moliere_screening_constant ) )*
            d_norm_constant;
  }
  else if( indep_var_value > Utility::get<0>( d_distribution.back() ) )
    return 1.0;
  else
  {
    DistributionArray::const_iterator start, end, lower_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary = Search::binaryLowerBound<FIRST>( start,
							  end,
							  indep_var_value );

    double indep_diff =
      indep_var_value - Utility::get<0>( *lower_bin_boundary );

    return Utility::get<1>( *lower_bin_boundary ) +
      indep_diff*Utility::get<2>( *lower_bin_boundary ) +
      indep_diff*indep_diff/2.0 * Utility::get<3>( *lower_bin_boundary );
  }
}

// Return a random sample from the distribution
template<typename InterpolationPolicy>
inline double ElasticElectronDistribution<InterpolationPolicy>::sample() const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample and record the number of trials
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::sampleAndRecordTrials(
						       DistributionTraits::Counter& trials ) const
{
  ++trials;

  return this->sample();
}

// Return a random sample and bin index from the distribution
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::sampleAndRecordBinIndex(
					    unsigned& sampled_bin_index ) const
{
  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleImplementation( random_number, sampled_bin_index );
}

// Return a sample from the distribution at the given CDF value
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::sampleWithRandomNumber(
					     const double random_number ) const
{
  unsigned dummy_index;

  return this->sampleImplementation( random_number, dummy_index );
}

// Return a random sample from the corresponding CDF in a subrange
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::sampleInSubrange(
					     const double max_indep_var ) const
{
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );

  double random_number = RandomNumberGenerator::getRandomNumber<double>();

  return this->sampleWithRandomNumberInSubrange( random_number,
						 max_indep_var );
}

// Return a random sample from the distribution at the given CDF value in a subrange
template<typename InterpolationPolicy>
inline double ElasticElectronDistribution<InterpolationPolicy>::sampleWithRandomNumberInSubrange(
					     const double random_number,
					     const double max_indep_var ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );
  // Make sure the maximum indep var is valid
  testPrecondition( max_indep_var >= this->getLowerBoundOfIndepVar() );

  // Calculate a scaled random number
  double scaled_random_number =
    random_number*this->evaluateCDF( max_indep_var );

  unsigned dummy_index;

  return this->sampleImplementation( scaled_random_number, dummy_index );
}

// Return a random sample using the random number and record the bin index
/*! !\details If the screened Rutherford portion is sampled a bin index of 0
 *  will be returned
 */
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::sampleImplementation(
					    double random_number,
					    unsigned& sampled_bin_index ) const
{
  // Make sure the random number is valid
  testPrecondition( random_number >= 0.0 );
  testPrecondition( random_number <= 1.0 );

  // Calculate the sampled independent value
  double sample;

  if ( random_number >= d_screened_rutherford_cutoff_cdf )
  {
    DistributionArray::const_iterator start, end, lower_bin_boundary;
    start = d_distribution.begin();
    end = d_distribution.end();

    lower_bin_boundary = Search::binaryLowerBound<SECOND>( start,
                                                           end,
                                                           random_number );

    // Calculate the sampled bin index
    sampled_bin_index = std::distance(d_distribution.begin(),lower_bin_boundary);

    double indep_value = Utility::get<0>( *lower_bin_boundary );
    double cdf_diff = random_number - Utility::get<1>( *lower_bin_boundary );
    double pdf_value = Utility::get<2>( *lower_bin_boundary );
    double slope = Utility::get<3>( *lower_bin_boundary );

    // x = x0 + [sqrt(pdf(x0)^2 + 2m[cdf(x)-cdf(x0)]) - pdf(x0)]/m
    if( slope != 0.0 )
    {
      sample = indep_value +
        (sqrt( pdf_value*pdf_value + 2*slope*cdf_diff ) - pdf_value)/slope;
    }
    // x = x0 + [cdf(x)-cdf(x0)]/pdf(x0) => L'Hopital's rule
    else
      sample =  indep_value + cdf_diff/pdf_value;
  }
  else if ( random_number > 0.0 )
  {
    sampled_bin_index = 0.0;
    sample = random_number*
              d_moliere_screening_constant*d_moliere_screening_constant/
            ( d_screened_rutherford_normalization_constant -
              d_moliere_screening_constant*random_number );
  }
  else
  {
    sampled_bin_index = 0.0;
    sample = 0.0;
  }

  // Make sure the sample is valid
  testPostcondition( !Teuchos::ScalarTraits<double>::isnaninf( sample ) );
  // Make sure the random number is valid
  testPrecondition( sample >= 0.0 );
  testPrecondition( sample <= 2.0 );

  return sample;
}

// Return the upper bound of the distribution independent variable
template<typename InterpolationPolicy>
double
ElasticElectronDistribution<InterpolationPolicy>::getUpperBoundOfIndepVar() const
{
  return Utility::get<0>( d_distribution.back() );
}

// Return the lower bound of the distribution independent variable
template<typename InterpolationPolicy>
double
ElasticElectronDistribution<InterpolationPolicy>::getLowerBoundOfIndepVar() const
{
  return 0.0;
}

// Return the distribution type
template<typename InterpolationPolicy>
OneDDistributionType
ElasticElectronDistribution<InterpolationPolicy>::getDistributionType() const
{
  return ElasticElectronDistribution<InterpolationPolicy>::distribution_type;
}

// Test if the distribution is continuous
template<typename InterpolationPolicy>
bool ElasticElectronDistribution<InterpolationPolicy>::isContinuous() const
{
  return true;
}

// Method for placing the object in an output stream
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::toStream(
						       std::ostream& os ) const
{
  Teuchos::Array<double> independent_values( d_distribution.size() );
  Teuchos::Array<double> dependent_values( d_distribution.size() );

  for( unsigned i = 0u; i < d_distribution.size(); ++i )
  {
    independent_values[i] = Utility::get<0>( d_distribution[i] );
    dependent_values[i] = Utility::get<2>( d_distribution[i] );
  }

  os << "{" << independent_values << "," << dependent_values << "}";
}

// Method for initializing the object from an input stream
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::fromStream( std::istream& is )
{
  // Read the initial '{'
  std::string start_bracket;
  std::getline( is, start_bracket, '{' );
  start_bracket = Teuchos::Utils::trimWhiteSpace( start_bracket );

  TEST_FOR_EXCEPTION( start_bracket.size() != 0,
		      InvalidDistributionStringRepresentation,
		      "Error: the input stream is not a valid elastic electron "
		      "distribution representation!" );

  std::string independent_values_rep;
  std::getline( is, independent_values_rep, '}' );
  independent_values_rep += "}";

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( independent_values_rep );
    ArrayString::locateAndReplaceIntervalOperator( independent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the elastic electron distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  Teuchos::Array<double> independent_values;
  try{
    independent_values =
      Teuchos::fromStringToArray<double>( independent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the elastic electron distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( !Sort::isSortedAscending( independent_values.begin(),
						independent_values.end() ),
		      InvalidDistributionStringRepresentation,
		      "Error: the elastic electron distribution cannot be constructed "
		      "because the bin boundaries "
		      << independent_values_rep << " are not sorted!" );

  // Read the ","
  std::string separator;
  std::getline( is, separator, ',' );

  std::string dependent_values_rep;
  std::getline( is, dependent_values_rep, '}' );
  dependent_values_rep += "}";

  // Parse special characters
  try{
    ArrayString::locateAndReplacePi( dependent_values_rep );
    ArrayString::locateAndReplaceIntervalOperator( dependent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
			      InvalidDistributionStringRepresentation,
			      "Error: the elastic electron distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  Teuchos::Array<double> dependent_values;
  try{
    dependent_values =
      Teuchos::fromStringToArray<double>( dependent_values_rep );
  }
  EXCEPTION_CATCH_RETHROW_AS( Teuchos::InvalidArrayStringRepresentation,
			      InvalidDistributionStringRepresentation,
			      "Error: the elastic electron distribution cannot be "
			      "constructed because the representation is not "
			      "valid (see details below)!\n" );

  TEST_FOR_EXCEPTION( independent_values.size() != dependent_values.size(),
		      InvalidDistributionStringRepresentation,
		      "Error: the elastic electron distribution "
		      "{" << independent_values_rep << "},{"
		      << dependent_values_rep << "} "
		      "cannot be constructed because the number of "
		      "independent values does not equal the number of "
		      "dependent values" );

  initializeDistributionENDL( independent_values, dependent_values );
}

// Method for testing if two objects are equivalent
template<typename InterpolationPolicy>
bool ElasticElectronDistribution<InterpolationPolicy>::isEqual(
		  const ElasticElectronDistribution<InterpolationPolicy>& other ) const
{
  return d_distribution == other.d_distribution &&
    d_norm_constant == other.d_norm_constant;
}

// Return Moliere's screening constant
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::getMoliereScreeningConstant() const
{
  return d_moliere_screening_constant;
}

// Return the normalization constant for the screened Rutherford component of the distribution
template<typename InterpolationPolicy>
double ElasticElectronDistribution<InterpolationPolicy>::getScreenedRutherfordNormalizationConstant() const
{
  return d_screened_rutherford_normalization_constant;
}

// Initialize the distribution for ACE
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::initializeDistributionACE(
			      const Teuchos::Array<double>& independent_values,
			      const Teuchos::Array<double>& dependent_values )
{
  unsigned size = independent_values.size();

  // Resize the distribution
  d_distribution.resize( size );

  // Set the first two data bins
  Utility::get<0>( d_distribution[0] ) = 1.0 - independent_values[size-1];
  Utility::get<1>( d_distribution[0] ) = 1.0 - dependent_values[size-1];
  Utility::get<0>( d_distribution[1] ) = 1.0 - independent_values[size-2];
  Utility::get<1>( d_distribution[1] ) = 1.0 - dependent_values[size-2];
  setFirstTwoPDFs( 1.0-dependent_values[size-1],
                   1.0-dependent_values[size-2] );

  d_screened_rutherford_cutoff_cdf =  Utility::get<2>( d_distribution[1] );

  // Assign the distribution
  for( int i = 2; i < size; ++i )
  {
    Utility::get<0>( d_distribution[i] ) = 1.0 - independent_values[size-i-1];
    Utility::get<1>( d_distribution[i] ) = 1.0 - dependent_values[size-i-1];

    // Use Lin-Lin interpolation for the pdf and quadratic for the cdf
    if( Utility::get<1>( d_distribution[i-1] ) != Utility::get<1>( d_distribution[i] ) )
    {
      // Calculate the pdf from the cdf
      Utility::get<2>( d_distribution[i] ) =
        -Utility::get<2>( d_distribution[i-1] ) + 2.0 *
        (Utility::get<1>( d_distribution[i] ) - Utility::get<1>( d_distribution[i-1] ))/
        (Utility::get<0>( d_distribution[i] ) - Utility::get<0>( d_distribution[i-1] ));
    }
    else // If the cdf does not change inbetween angular bins, set the pdf to zero
    {
      Utility::get<2>( d_distribution[i] ) = 0.0;
    }
  }

  // Set normalization constant
  d_norm_constant = Utility::get<1>( d_distribution.back() );

  // Verify that the CDF is normalized (in event of round-off errors)
  if( dependent_values.back() != 1.0 )
  {
    for( unsigned j = 0; j < d_distribution.size(); ++j )
    {
      Utility::get<1>( d_distribution[j] ) /= d_norm_constant;
      Utility::get<2>( d_distribution[j] ) /= d_norm_constant;
    }
  }

  // Calculate the slopes of the PDF
  DataProcessor::calculateSlopes<FIRST,THIRD,FOURTH>( d_distribution );
}

// Initialize the distribution for ENDL
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::initializeDistributionENDL(
			      const Teuchos::Array<double>& independent_values,
			      const Teuchos::Array<double>& dependent_values )
{
  // Make sure that at least two points of the distribution are specified
  testPrecondition( independent_values.size() > 1 );
  // Make sure that the independent values are sorted
  testPrecondition( Sort::isSortedAscending( independent_values.begin(),
					     independent_values.end() ) );
  // Make sure that every independent value has a dependent value
  testPrecondition( independent_values.size() == dependent_values.size() );

  // Resize the distribution
  d_distribution.resize( independent_values.size() );

  // Assign the raw distribution data
  for( unsigned i = 0; i < independent_values.size(); ++i )
  {
    Utility::get<0>( d_distribution[i] ) = independent_values[i];
    Utility::get<2>( d_distribution[i] ) = dependent_values[i];
  }

  // Create a CDF from the raw distribution data
  double max_tabular_cdf =
    DataProcessor::calculateContinuousCDF<FIRST,THIRD,SECOND>(d_distribution);

  // The cutoff angle above which the screened Rutherford distribution is sampled
  d_screened_rutherford_cutoff_cdf =
    ( s_sr_angle*d_screened_rutherford_normalization_constant )/
    ( d_moliere_screening_constant*( s_sr_angle+d_moliere_screening_constant ) );

  /* Normalize the CDF by:
    (the max cutoff cdf) +
    (the ratio of the screened Ruthreford to the cutoff distribution ) */
  d_norm_constant = max_tabular_cdf + d_screened_rutherford_cutoff_cdf;

  // Normalized the CDF to screened Rutherford peak
  for( unsigned j = 0; j < d_distribution.size(); ++j )
  {
    Utility::get<1>( d_distribution[j] ) /= d_norm_constant;
  }


  // Calculate the slopes of the PDF
  DataProcessor::calculateSlopes<FIRST,THIRD,FOURTH>( d_distribution );
}

// Set the first two PDF values
template<typename InterpolationPolicy>
void ElasticElectronDistribution<InterpolationPolicy>::setFirstTwoPDFs(
        const double& first_cdf,
        const double& second_cdf )
{
  // get size of array
  unsigned size = d_distribution.size();

  // get the momentum**2 of the electron in units of electron_rest_mass_energy
  double electron_momentum_squared =
           Utility::calculateDimensionlessRelativisticMomentumSquared(
                          Utility::PhysicalConstants::electron_rest_mass_energy,
                          d_energy );

  // get the velocity of the electron divided by the speed of light beta = v/c
  double beta_squared = Utility::calculateDimensionlessRelativisticSpeedSquared(
           Utility::PhysicalConstants::electron_rest_mass_energy,
           d_energy );

  // The fine structure constant squared
  double fine_structure_const_squared=
        Utility::PhysicalConstants::fine_structure_constant*
        Utility::PhysicalConstants::fine_structure_constant;

  double screening_param1 = fine_structure_const_squared/( 2.0*0.885*0.885 );

  double screening_param2 = 3.76*fine_structure_const_squared*
                            d_atomic_number*d_atomic_number;

  double screening_param3 = 1.0/beta_squared*sqrt( d_energy/
          ( d_energy + Utility::PhysicalConstants::electron_rest_mass_energy) );

  // Calculate Moliere's atomic screening constant
  d_moliere_screening_constant =
            screening_param1 * 1.0/electron_momentum_squared *
            d_Z_two_thirds_power * ( 1.13 + screening_param2*screening_param3 );

  double var = (s_sr_angle + d_moliere_screening_constant);

  // Calculate the normalization constant
  d_screened_rutherford_normalization_constant =
            ( second_cdf -first_cdf )*
            d_moliere_screening_constant*var/s_sr_angle;

  Utility::get<2>( d_distribution[1] ) =
    d_screened_rutherford_normalization_constant/( var*var );
  Utility::get<2>( d_distribution[0] ) =
    d_screened_rutherford_normalization_constant/
    ( d_moliere_screening_constant*d_moliere_screening_constant );
/*
std::cout << std::setprecision(20)<<"d_moliere_screening_constant =\t"<<d_moliere_screening_constant<<std::endl;
std::cout << std::setprecision(20)<<"d_screened_rutherford_normalization_constant =\t"<<d_screened_rutherford_normalization_constant<<std::endl;*/
}

// Test if the dependent variable can be zero within the indep bounds
template<typename InterpolationPolicy>
inline bool ElasticElectronDistribution<InterpolationPolicy>::canDepVarBeZeroInIndepBounds() const
{
  bool possible_zero = false;

  for( size_t i = 0; i < d_distribution.size(); ++i )
  {
    if( Utility::get<2>( d_distribution[i] ) == 0.0 )
    {
      possible_zero = true;

      break;
    }
  }

  return possible_zero;
}

// Test if the independent variable is compatible with Lin processing
template<typename InterpolationPolicy>
inline bool ElasticElectronDistribution<InterpolationPolicy>::isIndepVarCompatibleWithProcessingType(
                                         const LinIndepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LinIndepVarProcessingTag>::value;
}
  
// Test if the independent variable is compatible with Log processing
template<typename InterpolationPolicy>
inline bool ElasticElectronDistribution<InterpolationPolicy>::isIndepVarCompatibleWithProcessingType(
                                         const LogIndepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::IndepVarProcessingTag,LogIndepVarProcessingTag>::value;
}

// Test if the dependent variable is compatible with Lin processing
template<typename InterpolationPolicy>
inline bool ElasticElectronDistribution<InterpolationPolicy>::isDepVarCompatibleWithProcessingType(
                                           const LinDepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LinDepVarProcessingTag>::value;
}

// Test if the dependent variable is compatible with Log processing
template<typename InterpolationPolicy>
bool ElasticElectronDistribution<InterpolationPolicy>::isDepVarCompatibleWithProcessingType(
                                           const LogDepVarProcessingTag ) const
{
  return boost::is_same<typename InterpolationPolicy::DepVarProcessingTag,LogDepVarProcessingTag>::value;
}

} // end Utility namespace

#endif // end Utility_ElasticElectronDistribution_def.hpp

//---------------------------------------------------------------------------//
// end Utility_ElasticElectronDistribution_def.hpp
//---------------------------------------------------------------------------//
