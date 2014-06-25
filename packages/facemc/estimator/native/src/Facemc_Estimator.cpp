//---------------------------------------------------------------------------//
//!
//! \file   Facemc_Estimator.cpp
//! \author Alex Robinson
//! \brief  Estimator base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FRENSIE Includes
#include "Facemc_Estimator.hpp"

namespace Facemc{

// Initialize the number of histories run
unsigned long long Estimator::num_histories = 0ull;
double Estimator::start_time = 0.0;
double Estimator::end_time = Estimator::start_time;

// Set the number of particle histories that will be simulated
void Estimator::setNumberOfHistories( const unsigned long long num_histories )
{
  Estimator::num_histories = num_histories;
}

// Set the start time for the figure of merit calculation
void Estimator::setStartTime( const double start_time )
{
  testPrecondition( start_time >= 0.0 );
  
  Estimator::start_time = start_time;
}

// Set the end time for the figure of merit calculation
void Estimator::setEndTime( const double end_time )
{
  testPrecondition( end_time > start_time );
  
  Estimator::end_time = end_time;
}

// Constructor
  Estimator::Estimator( const Estimator::idType id,
			const double multiplier )
  : PrintableObject( "//---------------------------------------------------------------------------//" ),
    d_id( id ),
    d_multiplier( multiplier ),
    d_has_uncommitted_history_contribution( false ),
    d_response_functions( 1 )
{
  // Make sure the multiplier is valid
  testPrecondition( multiplier > 0.0 );
  
  // Set the response function
  d_response_functions[0] = ResponseFunction::default_response_function;

  // Create the default particle types set (all particle types)
  d_particle_types.insert( PHOTON );
}

// Set the response functions
void Estimator::setResponseFunctions( 
    const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions )
{
  // Make sure there is at least one response function
  testPrecondition( response_functions.size() >= 1 );

  d_response_functions = response_functions;
}

// Set the particle types
void Estimator::setParticleTypes( 
			   const Teuchos::Array<ParticleType>& particle_types )
{
  // Make sure at least one particle type is specified
  testPrecondition( particle_types.size() > 0 );
  
  d_particle_types.clear();

  for( unsigned i = 0; i < particle_types.size(); ++i )
    d_particle_types.insert( particle_types[i] );
}

// Assign bin boundaries to an estimator dimension
void Estimator::assignBinBoundaries( 
	 const Teuchos::RCP<EstimatorDimensionDiscretization>& bin_boundaries )
{
  if(d_dimension_bin_boundaries_map.count(bin_boundaries->getDimension()) == 0)
  {
    d_dimension_bin_boundaries_map[bin_boundaries->getDimension()] = 
      bin_boundaries;

    // Add the new dimension to the dimension ordering array
    d_dimension_ordering.push_back( bin_boundaries->getDimension() );

    // Calculate the index step size for the new dimension
    unsigned dimension_index_step_size = 1u;

    for( unsigned i = 0u; i < d_dimension_ordering.size()-1u; ++i )
    {
      dimension_index_step_size *= 
	d_dimension_bin_boundaries_map[d_dimension_ordering[i]]->getNumberOfBins();
    }

    d_dimension_index_step_size_map[bin_boundaries->getDimension()] = 
      dimension_index_step_size;
  }
  else
  {
    std::cerr << "Warning: The dimension requested already has bin boundaries "
	      << "set. The new boundaries will be ignored."
	      << std::endl;
  }
}

// Print the estimator response function names
void Estimator::printEstimatorResponseFunctionNames( std::ostream& os ) const
{
  os << "Response Functions: " << std::endl;
  
  for( unsigned i = 0u; i < d_response_functions.size(); ++i )
    os << "  " << i+1 << ".) " << getResponseFunctionName( i ) << std::endl;
}

// Print the estimator bins
void Estimator::printEstimatorBins( std::ostream& os ) const
{
  for( unsigned i = 0u; i < d_dimension_ordering.size(); ++i )
  {
    d_dimension_bin_boundaries_map.find(d_dimension_ordering[i])->second->print( os );
    os << std::endl;
  }
}

// Print the estimator data stored in an array
/*! \details The number of elements in the array should be equal to the
 * the number of estimator bins times the number of response functions.
 */
void Estimator::printEstimatorBinData(
			std::ostream& os,
		        const TwoEstimatorMomentsArray& estimator_moments_data,
			const double norm_constant ) const
{
  // Make sure that the estimator moment array is valid
  testPrecondition( estimator_moments_data.size() == 
		    getNumberOfBins()*getNumberOfResponseFunctions() );

  // Use this array to determine when bin indices should be printed
  Teuchos::Array<unsigned> previous_bin_indices( 
					d_dimension_ordering.size(),
					std::numeric_limits<unsigned>::max() );
  
  for( unsigned r = 0u; r < getNumberOfResponseFunctions(); ++r )
  {
    os << "Response Function: " << getResponseFunctionName( r ) << std::endl;

    for( unsigned i = 0u; i < getNumberOfBins(); ++i )
    {
      for( int d = d_dimension_ordering.size()-1; d >= 0; --d )
      {	
	const unsigned& dimension_index_step_size = 
	 d_dimension_index_step_size_map.find(d_dimension_ordering[d])->second;
	
	// Calculate the bin index for the dimension
	unsigned bin_index = (i/dimension_index_step_size)%
	  (getNumberOfBins( d_dimension_ordering[d] ));
	
	// Print the bin boundaries if the dimension index has changed
	if( bin_index != previous_bin_indices[d] )
	{
	  previous_bin_indices[d] = bin_index;
	  
	  // Add proper spacing before printing
	  for( unsigned s = 0u; s < d_dimension_ordering.size()-d; ++s )
	    os << " ";
	  
	  d_dimension_bin_boundaries_map.find(d_dimension_ordering[d])->second->printBoundariesOfBin( os, bin_index );
	  
	  // Print a new line character for all but the first dimension
	  if( d != 0 )
	    os << std::endl;
	}
      }

      // Calculate the bin index for the response function
      unsigned bin_index = i + r*getNumberOfBins();

      // Calculate the estimator bin data
      double estimator_bin_value = 
	calculateMean( estimator_moments_data[bin_index].first )*
	d_multiplier/norm_constant;
      
      double estimator_bin_rel_err = 
	calculateRelativeError( 
			       estimator_moments_data[bin_index].first,
			       estimator_moments_data[bin_index].second );

      // Print the estimator bin data
      os << " " << estimator_bin_value << " " 
	 << estimator_bin_rel_err << std::endl;
    }
  }
}

// Print the total estimator data stored in an array
/*! \details The array should have one element for each response function
 * assigned to the estimator.
 */ 
void Estimator::printEstimatorTotalData( 
		 std::ostream& os,
		 const FourEstimatorMomentsArray& total_estimator_moments_data,
		 const double norm_constant ) const
{
  // Make sure that the total estimator moments data is valid
  testPrecondition( total_estimator_moments_data.size() ==
		    getNumberOfResponseFunctions() );

   for( unsigned i = 0; i < d_response_functions.size(); ++i )
  {
    os << "Response Function: " << getResponseFunctionName( i ) << std::endl;
    
    double estimator_value = 
    calculateMean( total_estimator_moments_data[i].first )*
      d_multiplier/norm_constant;
  
    double estimator_rel_err = 
      calculateRelativeError( total_estimator_moments_data[i].first,
			      total_estimator_moments_data[i].second );
  
    double estimator_vov = 
      calculateVOV( total_estimator_moments_data[i].first,
		    total_estimator_moments_data[i].second,
		    total_estimator_moments_data[i].third,
		    total_estimator_moments_data[i].fourth );
    
    double estimator_fom = calculateFOM( estimator_rel_err );
    
    os << estimator_value << " " 
       << estimator_rel_err << " "
       << estimator_vov << " "
       << estimator_fom << std::endl;
  }
}

// Check if the point is in the estimator phase space
bool Estimator::isPointInEstimatorPhaseSpace(
		              const DimensionValueMap& dimension_values ) const
{
  // Make sure there are at least as many dimension values as dimensions
  testPrecondition( dimension_values.size() >= 
		    d_dimension_bin_boundaries_map.size() );

  bool point_in_phase_space = true;

  for( unsigned i = 0u; i < d_dimension_ordering.size(); ++i )
  {
    const Teuchos::any& dimension_value = 
      dimension_values.find(d_dimension_ordering[i])->second;

    const Teuchos::RCP<EstimatorDimensionDiscretization>& 
      dimension_bin_boundaries = d_dimension_bin_boundaries_map.find(
					     d_dimension_ordering[i] )->second;

    if( !dimension_bin_boundaries->isValueInDiscretization( dimension_value ) )
    {
      point_in_phase_space = false;

      break;
    }
  }

  return point_in_phase_space;
}

// Calculate the bin index for the desired response function
unsigned Estimator::calculateBinIndex( 
			         const DimensionValueMap& dimension_values,
			         const unsigned response_function_index ) const
{
  // Make sure there are at least as many dimension values as dimensions
  testPrecondition( dimension_values.size() >= 
		    d_dimension_bin_boundaries_map.size() );
  // Make sure the response function is valid
  testPrecondition( response_function_index < getNumberOfResponseFunctions() );
  
  unsigned long bin_index = 0u;
  
  for( unsigned i = 0u; i < d_dimension_ordering.size(); ++i )
  {
    const Teuchos::any& dimension_value = 
      dimension_values.find(d_dimension_ordering[i])->second;

    const Teuchos::RCP<EstimatorDimensionDiscretization>& 
      dimension_bin_boundaries = d_dimension_bin_boundaries_map.find(
					     d_dimension_ordering[i] )->second;

    const unsigned& dimension_index_step_size = 
      d_dimension_index_step_size_map.find( d_dimension_ordering[i] )->second;
    
    bin_index += dimension_bin_boundaries->calculateBinIndex(dimension_value)*
      dimension_index_step_size;
  }
  
  bin_index += response_function_index*getNumberOfBins();

  // Make sure the bin index calculated is valid
  testPostcondition( bin_index < 
		     getNumberOfBins()*getNumberOfResponseFunctions() );
  testPostcondition( bin_index < std::numeric_limits<unsigned>::max() );

  return bin_index;
}

// Calculate the mean of a set of contributions
double Estimator::calculateMean( const double first_moment_contributions) const
{
  // Make sure that the number of histories is valid
  testPrecondition( Estimator::num_histories > 0ull );
  // Make sure the first moment contributions are valid
  testPrecondition( !ST::isnaninf( first_moment_contributions ) );
  testPrecondition( first_moment_contributions >= 0.0 );

  double mean = first_moment_contributions/Estimator::num_histories;

  // Make sure the mean is valid
  testPostcondition( !ST::isnaninf( mean ) );
  testPostcondition( mean >= 0.0 );

  return mean;
}

// Calculate the relative error of a set of contributions
double Estimator::calculateRelativeError( 
			       const double first_moment_contributions,
			       const double second_moment_contributions ) const
{
  // Make sure that the number of histories is valid
  testPrecondition( Estimator::num_histories > 0ull );
  // Make sure the first moment contributions are valid
  testPrecondition( !ST::isnaninf( first_moment_contributions ) );
  testPrecondition( first_moment_contributions >= 0.0 );
  // Make sure the second moment contributions are valid
  testPrecondition( !ST::isnaninf( second_moment_contributions ) );
  testPrecondition( second_moment_contributions >= 0.0 );

  double relative_error;
  
  if( first_moment_contributions > 0.0 )
  {
    double argument = second_moment_contributions/
      (first_moment_contributions*first_moment_contributions) - 
      1.0/Estimator::num_histories;
    
    relative_error = ST::squareroot( argument );
  }
  else
    return relative_error = 0.0;

  // Make sure the relative error is valid
  testPostcondition( !ST::isnaninf( relative_error ) );
  testPostcondition( relative_error >= 0.0 );

  return relative_error;
}

// Calculate the variance of the variance (VOV) of a set of contributions
/* \details VOV = S^2(S^2_xbar)/S^4_xbar
 */ 
double Estimator::calculateVOV( const double first_moment_contributions,
				const double second_moment_contributions,
				const double third_moment_contributions,
				const double fourth_moment_contributions) const
{
  // Make sure that the number of histories is valid
  testPrecondition( Estimator::num_histories > 0ull );
  // Make sure the first moment contributions are valid
  testPrecondition( !ST::isnaninf( first_moment_contributions ) );
  testPrecondition( first_moment_contributions >= 0.0 );
  // Make sure the second moment contributions are valid
  testPrecondition( !ST::isnaninf( second_moment_contributions ) );
  testPrecondition( second_moment_contributions >= 0.0 );
  // Make sure the third moment contributions are valid
  testPrecondition( !ST::isnaninf( third_moment_contributions ) );
  testPrecondition( third_moment_contributions >= 0.0 );
  // Make sure the fourth moment contributions are valid
  testPrecondition( !ST::isnaninf( fourth_moment_contributions ) );
  testPrecondition( fourth_moment_contributions >= 0.0 );

  double first_moment_contributions_squared = 
    first_moment_contributions*first_moment_contributions;

  double num_histories_squared = Estimator::num_histories*
    Estimator::num_histories;

  double num_histories_cubed = num_histories_squared*Estimator::num_histories;

  double vov_numerator = fourth_moment_contributions - 
    4*first_moment_contributions*third_moment_contributions/
    Estimator::num_histories +
    8*second_moment_contributions*first_moment_contributions_squared/
    num_histories_squared -
    4*first_moment_contributions_squared*first_moment_contributions_squared/
    num_histories_cubed - 
    second_moment_contributions*second_moment_contributions/
    Estimator::num_histories;

  double vov_denominator = 
    (second_moment_contributions - first_moment_contributions_squared/
     Estimator::num_histories);
  vov_denominator *= vov_denominator;
  
  double vov;
  
  if( vov_denominator != 0.0 )
    vov = vov_numerator/vov_denominator;   
  else
    vov = 0.0;

  // Make sure the variance of the variance is valid
  testPostcondition( !ST::isnaninf( vov ) );
  testPostcondition( vov >= 0.0 );

  return vov;
}

// Calculate the figure of merit (FOM) of a set of contributions
double Estimator::calculateFOM( const double relative_error ) const
{
  // Make sure the problem time is valid
  testPrecondition( Estimator::end_time - Estimator::start_time > 0.0 );

  double problem_time = Estimator::end_time - Estimator::start_time;

  double fom;
  
  if( relative_error > 0.0 )
    fom = 1.0/(relative_error*relative_error*problem_time);
  else
    fom = 0.0;

  // Make sure the figure of merit is valid
  testPostcondition( !ST::isnaninf( fom ) );
  testPostcondition( fom >= 0.0 );
  
  return fom;
}

} // end Facemc namespace

//---------------------------------------------------------------------------//
// end Facemc_Estimator.cpp
//---------------------------------------------------------------------------//
