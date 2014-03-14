//---------------------------------------------------------------------------//
//!
//! \file   Estimator.cpp
//! \author Alex Robinson
//! \brief  Estimator base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

// FACEMC Includes
#include "Estimator.hpp"
#include "SearchAlgorithms.hpp"

namespace FACEMC{

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
/*! \details All bins will be initialized so that any particle state will fall
 * within the estimator phase space.
 */
Estimator::Estimator( const unsigned long long id,
		      const double multiplier )
  : PrintableObject( "//---------------------------------------------------------------------------//" ),
    d_id( 0ull ),
    d_multiplier( multiplier ),
    d_energy_bin_boundaries( 2 ),
    d_cosine_bin_boundaries( 2 ),
    d_time_bin_boundaries( 2 ),
    d_collision_number_bins( 1 ),
    d_response_functions( 1 )
{
  // Make sure the multiplier is valid
  testPrecondition( multiplier > 0.0 );
  
  // Set the energy bin
  d_energy_bin_boundaries[0] = 0.0;
  d_energy_bin_boundaries[1] = std::numeric_limits<double>::infinity();

  // Set the cosine bin
  d_cosine_bin_boundaries[0] = -1.0;
  d_cosine_bin_boundaries[1] = 1.0;

  // Set the time bin
  d_time_bin_boundaries[0] = 0.0;
  d_time_bin_boundaries[1] = std::numeric_limits<double>::infinity();

  // Set the collision number bin boundaries
  d_collision_number_bins[0] = std::numeric_limits<unsigned>::max();

  // Set the response function
  d_response_functions[0] = ResponseFunction::default_response_function;

  // Create the default particle types set (all particle types)
  d_particle_types.insert( PHOTON );
}

// Set the energy bin boundaries
void Estimator::setEnergyBinBoundaries(
			  const Teuchos::Array<double>& energy_bin_boundaries )
{
  // Make sure there is at least one energy bin
  testPrecondition( energy_bin_boundaries.size() >= 2 );
  // Make sure the energy bins are valid
  testPrecondition( energy_bin_boundaries[0] >= 0.0 );
  
  d_energy_bin_boundaries = energy_bin_boundaries;
}  

// Set the cosine bin boundaries
void Estimator::setCosineBinBoundaries(
			  const Teuchos::Array<double>& cosine_bin_boundaries )
{
  // Make sure there is at least one cosine bin
  testPrecondition( cosine_bin_boundaries.size() >= 2 );
  // Make sure the time bins are valid
  testPrecondition( cosine_bin_boundaries[0] >= -1.0 );
  testPrecondition( cosine_bin_boundaries[1] <= 1.0 );
  
  d_cosine_bin_boundaries = cosine_bin_boundaries;
}

// Set the time bin boundaries
void Estimator::setTimeBinBoundaries(
			    const Teuchos::Array<double>& time_bin_boundaries )
{
  // Make sure there is at least one time bin
  testPrecondition( time_bin_boundaries.size() >= 2 );
  // Make sure the time bins are valid
  testPrecondition( time_bin_boundaries[0] >= 0.0 );
  
  d_time_bin_boundaries = time_bin_boundaries;
}

// Set the collision number bins
void Estimator::setCollisionNumberBins( 
			const Teuchos::Array<unsigned>& collision_number_bins )
{
  // Make sure there is at least one collision number bin
  testPrecondition( collision_number_bins.size() >= 1 );
  
  d_collision_number_bins = collision_number_bins;
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

// Print the estimator response function names
void Estimator::printEstimatorResponseFunctionNames( std::ostream& os ) const
{
  os << "Response Functions: " << std::endl;
  
  for( unsigned i = 0; i < d_response_functions.size(); ++i )
    os << "  " << i+1 << ".) " << getResponseFunctionName( i ) << std::endl;
}

// Print the estimator bins
void Estimator::printEstimatorBins( std::ostream& os ) const
{
  os << "Collision Number Bins: ";
  
  for( unsigned i = 0; i < d_collision_number_bins.size(); ++i )
    os << d_collision_number_bins[i] << " ";

  os << std::endl;
  os << "Time Bin Boundaries: ";
  
  for( unsigned i = 0; i < d_time_bin_boundaries.size(); ++i )
    os << d_time_bin_boundaries[i] << " ";

  os << std::endl;
  os << "Cosine Bin Boundaries: ";
  
  for( unsigned i = 0; i < d_cosine_bin_boundaries.size(); ++i )
    os << d_cosine_bin_boundaries[i] << " ";

  os << std::endl;
  os << "Energy Bin Boundaries: ";

  for( unsigned i = 0; i < d_energy_bin_boundaries.size(); ++i )
    os << d_energy_bin_boundaries[i] << " ";

  os << std::endl;
}

// Print the estimator data stored in an array
/*! \details The number of elements in the array should be equal to the
 * the number of estimator bins times the number of response functions.
 */
void Estimator::printEstimatorBinData( 
		     std::ostream& os,
		     const EstimatorMomentsArray& estimator_moments_data,
		     const double norm_constant ) const
{
  // Make sure that the estimator moment array is valid
  testPrecondition( estimator_moments_data.size() == 
		    getNumberOfBins()*getNumberOfResponseFunctions() );
  
  unsigned num_response_functions = getNumberOfResponseFunctions();
  unsigned num_bins = getNumberOfBins();
  unsigned num_collision_number_bins = getNumberOfCollisionNumberBins();
  unsigned num_time_bins = getNumberOfTimeBins();
  unsigned num_cosine_bins = getNumberOfCosineBins();
  unsigned num_energy_bins = getNumberOfEnergyBins();
  
  unsigned bin_index;
  
  for( unsigned m = 0; m < num_response_functions; ++m )
  {
    os << "Response Function: " << getResponseFunctionName( m ) << std::endl;
    
    for( unsigned l = 0; l < num_collision_number_bins; ++l )
    {
      os << " Collision Number Bin: " << getBoundariesOfCollisionNumberBin( l )
	 << std::endl;
      
      for( unsigned k = 0; k < num_time_bins; ++k )
      {
	os << "  Time Bin: " << getBoundariesOfTimeBin( k ) << std::endl;

	for( unsigned j = 0; j < num_cosine_bins; ++j )
	{
	  os << "   Cosine Bin: " << getBoundariesOfCosineBin( j ) 
	     << std::endl;

	  for( unsigned i = 0; i < num_energy_bins; ++i )
	  {
	    os << "    Energy Bin: " << getBoundariesOfEnergyBin( i ) << " ";

	    bin_index = m*num_bins + 
	      l*num_time_bins*num_cosine_bins*num_energy_bins +
	      k*num_cosine_bins*num_energy_bins +
	      j*num_energy_bins;

	    double estimator_bin_value = 
	      calculateMean( estimator_moments_data[bin_index].first )*
	      d_multiplier/norm_constant;

	    double estimator_bin_rel_err = 
	      calculateRelativeError( 
			    estimator_moments_data[bin_index].first,
			    estimator_moments_data[bin_index].second );

	    double estimator_bin_vov = 
	      calculateVOV( estimator_moments_data[bin_index].first,
			    estimator_moments_data[bin_index].second,
			    estimator_moments_data[bin_index].third,
			    estimator_moments_data[bin_index].fourth );
	       
	    double estimator_bin_fom = calculateFOM( estimator_bin_rel_err );

	    os << estimator_bin_value << " " 
	       << estimator_bin_rel_err << " "
	       << estimator_bin_vov << " "
	       << estimator_bin_fom << std::endl;
	  }
	}
      }
    }
  }
}

// Print the total estimator data stored in an array
/*! \details The array should have one element for each response function
 * assigned to the estimator.
 */ 
void Estimator::printEstimatorTotalData( 
		     std::ostream& os,
		     const EstimatorMomentsArray& total_estimator_moments_data,
		     const double norm_constant )
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

// Calculate the energy bin index for the desired energy
unsigned Estimator::calculateEnergyBinIndex( const double energy ) const
{
  // Make sure the energy is in the estimator energy space
  testPrecondition( isEnergyInEstimatorEnergySpace( energy ) );

  Teuchos::Array<double>::const_iterator start, end, upper_bin_boundary;
  
  start = d_energy_bin_boundaries.begin();
  end = d_energy_bin_boundaries.end();
  upper_bin_boundary = Search::binarySearchDiscreteData( start, end, energy);
						 
  unsigned distance = 
    std::distance( d_energy_bin_boundaries.begin(), upper_bin_boundary );

  if( distance != 0u )
    return distance-1u;
  else
    return distance;
}

// Calculate the cosine bin index for the desired angle cosine
unsigned Estimator::calculateCosineBinIndex( const double angle_cosine ) const
{
  // Make sure the angle cosine is in the estimator cosine space
  testPrecondition( isAngleCosineInEstimatorCosineSpace( angle_cosine ) );

  Teuchos::Array<double>::const_iterator start, end, upper_bin_boundary;
  
  start = d_cosine_bin_boundaries.begin();
  end = d_cosine_bin_boundaries.end();
  upper_bin_boundary = 
    Search::binarySearchDiscreteData( start, end, angle_cosine );

  unsigned distance = 
    std::distance( d_cosine_bin_boundaries.begin(), upper_bin_boundary );
  
  if( distance != 0u )
    return distance-1u;
  else
    return distance;
}

// Calculate the time bin index for the desired time
unsigned Estimator::calculateTimeBinIndex( const double time ) const
{
  // Make sure the time is in the estimator time space
  testPrecondition( isTimeInEstimatorTimeSpace( time ) );

  Teuchos::Array<double>::const_iterator start, end, upper_bin_boundary;
  
  start = d_time_bin_boundaries.begin();
  end = d_time_bin_boundaries.end();
  upper_bin_boundary =
    Search::binarySearchDiscreteData( start, end, time );

  unsigned distance = 
    std::distance( d_time_bin_boundaries.begin(), upper_bin_boundary );
  
  if( distance != 0u )
    return distance-1u;
  else
    return distance;
}

// Calculate the collision number bin for the desired collision number
unsigned Estimator::calculateCollisionNumberBinIndex( 
					  const double collision_number ) const
{
  // Make sure the collision number is in the estimator col. num. space
  testPrecondition( isCollisionNumberInEstimatorCollisionNumberSpace(
						          collision_number ) );
  
  Teuchos::Array<unsigned>::const_iterator collision_bin_start,
    collision_bin_end, collision_upper_bin_boundary;
  
  collision_bin_start = d_collision_number_bins.begin();
  collision_bin_end = d_collision_number_bins.end();
  collision_upper_bin_boundary = 
    Search::binarySearchDiscreteData( collision_bin_start, 
				      collision_bin_end,
				      collision_number );
  
  return
    std::distance( d_collision_number_bins.begin(), 
		   collision_upper_bin_boundary );
}

// Calculate the bin index for the desired response function
/*! \details The dimensions of the estimator phase space are ordered from
 * energy, angle cosine, time, collision number and finally response function 
 * (the energy variable runs the fastest in terms of the bin index). 
 */ 
unsigned Estimator::calculateBinIndex( 
				 const double energy,
				 const double angle_cosine,
				 const double time,
				 const unsigned collision_number,
				 const unsigned response_function_index ) const
{
  // Make sure the response function index is valid
  testPrecondition( response_function_index < getNumberOfResponseFunctions() );
  
  unsigned num_energy_bins = getNumberOfEnergyBins();
  unsigned num_energy_and_cosine_bins = 
    num_energy_bins*getNumberOfCosineBins();
  unsigned num_energy_cosine_and_time_bins = 
    num_energy_and_cosine_bins*getNumberOfTimeBins();
  unsigned num_bins = 
    num_energy_cosine_and_time_bins*getNumberOfCollisionNumberBins();
  
  unsigned long bin_index = calculateEnergyBinIndex( energy );
  bin_index += calculateCosineBinIndex( angle_cosine )*num_energy_bins;
  bin_index += calculateTimeBinIndex( time )*num_energy_and_cosine_bins;
  bin_index += calculateCollisionNumberBinIndex( collision_number )*
    num_energy_cosine_and_time_bins;
  bin_index += response_function_index*num_bins;
				
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


} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end Estimator.cpp
//---------------------------------------------------------------------------//
