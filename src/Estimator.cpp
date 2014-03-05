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
#include "ContractException.hpp"

namespace FACEMC{

// Initialize the number of histories run
unsigned long long Estimator::num_histories = 0ull;

// Default constructor
Estimator::Estimator()
  : d_id( 0ull ),
    d_norm_constant( 1.0 ),
    d_multiplier( 1.0 ),
    d_output_ordering( "rectn" ),
    d_estimator_moments( 1 ),
    d_estimator_total_moments( 1 ),
    d_current_history_first_moments( 1 )
{ 
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
  d_response_function[0] = ResponseFunction::DefaultResponseFunctionPtr;
}

// Constructor
Estimator::Estimator( 
	       const unsigned long long id,
	       const double norm_constant,
	       const double multiplier )
  : d_id( id ),
    d_norm_constant( norm_constant ),
    d_multiplier( multiplier ),
    d_energy_bin_boundaries( 2 ),
    d_cosine_bin_boundaries( 2 ),
    d_time_bin_boundaries( 2 ),
    d_collision_number_bins( 1 ),
    d_response_functions( 1 ),
    d_estimator_total_moments( response_functions.size() ),
    d_current_history_first_moments( d_estimator_moments.size() )
{
  // Make sure the normalization constant is valid
  testPrecondition( !ST::isnaninf( norm_constant ) );
  testPrecondition( norm_constant > 0.0 );
  // Make sure the multiplier is valid
  testPrecondition( !ST::isnaninf( multiplier ) );
  testPrecondition( multiplier != 0.0 );
  
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
  d_response_function[0] = ResponseFunction::DefaultResponseFunctionPtr;
}

// Get the tally id
unsigned long long Estimator::getId() const
{
  return d_id;
}

// Set the energy bins
void Estimator::setEnergyBinBoundaries( 
			  const Teuchos::Array<double>& energy_bin_boundaries )
{
  // Make sure there is at least one energy bin
  testPrecondition( energy_bin_boundaries.size() >= 2 );
  // Make sure the energy bins are valid
  testPrecondition( energy_bin_boundaries[0] >= 0.0 );
  
  d_energy_bin_boundaries = energy_bin_boundaries;

  d_estimator_moments.resize( d_estimator_moments.size()*
			      (d_energy_bin_boundaries-1) );
}

// Set the cosine bin boundaries
void Estimator::setCosineBinBoundaries( 
			  const Teuchos::Array<double>& cosine_bin_boundaires )
{
  // Make sure there is at least one cosine bin
  testPrecondition( cosine_bin_boundaries.size() >= 2 );
  // Make sure the time bins are valid
  testPrecondition( cosine_bin_boundaries[0] >= -1.0 );
  testPrecondition( cosine_bin_boundaries[1] <= 1.0 );
  
  d_cosine_bin_boundaries = cosine_bin_boundaries;

  d_estimator_moments.resize( d_estimator_moments.size()*
			      (d_cosine_bin_boundaries-1) );
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

  d_estimator_moments.resize( d_estimator_moments.size()*
			      (d_time_bin_boundaries-1) );
}

// Set the collision number bins
void Estimator::setCollisionNumberBins(
			const Teuchos::Array<unsigned>& collision_number_bins )
{
  // Make sure there is at least one collision number bin
  testPrecondition( collision_number_bins.size() >= 1 );
  
  d_collision_number_bins = collision_number_bins;

  d_estimator_moments.resize( d_estimator_moments.size()*
			      d_collision_number_bins.size() );
			      
}

// Set the response functions
void Estimator::setResponseFunctions( 
		     const Teuchos::RCP<ResponseFunction>& response_functions )
{
  // Make sure there is at least one response function
  testPrecondition( response_function.size() >= 1 );

  d_response_functions = response_functions;

  d_estimator_moments.resize( d_estimator_total_moments.size()*
			      response_functions.size() );

  d_estimator_total_moments.resize( d_response_functions.size() );  
}

// Print method implementation
void Estimator::printImplementation( std::ostream& os ) const
{
  os << "Tally " << d_id << std::endl;

  // Print the binning information
  os << "\tResponse Functions: " << d_response_functions.size() << std::endl;
  
  os << "\tCollision Number Bins: ";
  
  for( unsigned i = 0; i < d_collision_number_bins.size(); ++i )
    os << d_collision_number_bins[i] << " ";

  os << std::endl;
  os << "\tTime Bin Boundaries: ";
  
  for( unsigned i = 0; i < d_time_bin_boundaries.size(); ++i )
    os << d_time_bin_boundaries[i] << " ";

  os << std::endl;
  os << "\tCosine Bin Boundaries: ";
  
  for( unsigned i = 0; i < d_cosine_bin_boundaries.size(); ++i )
    os << d_cosine_bin_boundaries[i] << " ";

  os << std::endl;
  os << "\tEnergy Bin Boundaries: ";

  for( unsigned i = 0; i < d_energy_bin_boundaries.size(); ++i )
    os << d_energy_bin_boundaries[i] << " ";

  os << std::endl;

  // Print the information in each bin
  unsigned bin_index;
  
  for( unsigned m = 0; m < d_response_functions.size(); ++m )
  {
    bin_index = m*d_collision_number_bins*
      (d_time_bin_boundaries.size()-1)*
      (d_cosine_bin_boundaries.size()-1)*
      (d_energy_bin_boundaries.size()-1);
    
    for( unsigned l = 0; l < d_collision_number_bins.size(); ++l )
    {
      bin_index += l*(d_time_bin_boundaries.size()-1)*
	(d_cosine_bin_boundaries.size()-1)*
	(d_energy_bin_boundaries.size()-1);
		      
      if( l > 0 )
      {
	if( d_collision_number_bins[i] - d_collision_number_bins[l-1] > 1 )
	  os << "Collision Bin: [" << d_collision_number_bins[l-1]+1u << ","
	     << d_collision_number_bins[l] << "]" << std::endl;
	else
	  os << "Collision Bin: "<< d_collision_number_bins[l] << std::endl;
      }
      else
	os << "Collision Bin: " << d_collision_number_bins[l] << std::endl;
      
      for( unsigned k = 0; k < d_time_bin_boundaries.size()-1; ++k )
      {
	bin_index += k*(d_cosine_bin_boundaries.size()-1)*
	  (d_energy_bin_boundaries.size()-1);
	
	os << "\tTime Bin: [" << d_time_bin_boundaries[i] << ","
	   << d_time_bin_boundaries[i+1] << "]" << std::endl;
	
	for( unsigned j = 0; j < d_cosine_bin_boundaries.size()-1; ++j )
	{
	  bin_index += j*(d_energy_bin_boundaries.size()-1);
	  
	  os << "\t\tCosine Bin: [" << d_cosine_bin_boundaries[j] << ","
	     << d_cosine_bin_boundaries[i+1] << "]" << std::endl;
	  
	  os << "\t\tEnergy:" << std::endl;
	  for( unsigned i = 0; i < d_energy_bin_boundaries.size()-1; ++i )
	  {
	    bin_index += i;
	    
	    os << d_energy_bin_boundaries[i] << " "
	       << d_energy_bin_boundaries[i+1] << " "
	       << calculateMean( bin_index ) << " "
	       << calculateRelativeError( bin_index ) << " "
	       << calculateVOV( bin_index ) << std::endl;
	  }
	}
      }
    }
  }
}

// Check if the particle state falls within the estimator phase space
bool Estimator::isParticleInEstimatorPhaseSpace( 
					    const BasicParticleState& particle,
					    const double angle_cosine ) const
{
  // Make sure that the angle cosine is valid
  testPrecondition( angle_cosine == angle_cosine );
  testPrecondition( angle_cosine >= -1.0 );
  testPrecondition( angle_cosine <= 1.0 );
  
  bool in_energy_space = false;
  if( particle.getEnergy() > d_energy_bin_boundaries.front() &&
      particle.getEnergy() <= d_energy_bin_boundaries.back() )
    in_energy_space = true;
  
  bool in_angle_space = false;
  if( angle_cosine > d_cosine_bin_boundaries.front() &&
      angle_cosine <= d_cosine_bin_boundaries.back() )
    in_angle_space = true;

  bool in_time_space = false;
  if( particle.getTime() > d_time_bin_boundaries.front() &&
      particle.getTime() <= d_time_bin_boundaries.back() )
    in_time_space = true;

  bool in_collision_number_space = false;
  if( particle.getCollisionNumber() >= 
      d_collision_number_bin_boundaries.front() &&
      particle.getCollisionNumber() <=
      d_collision_number_bin_boundaries.back() )
    in_collision_number_space = true;

  return in_energy_space && in_angle_space && in_time_space && 
    in_collision_number_space;
}

// Calculate the bin offset
unsigned Estimator::calculateBinIndex( 
				 const BasicParticleState& particle,
				 const double angle_cosine,
				 const unsigned response_function_index ) const
{
  // Make sure that the angle cosine is valid
  testPrecondition( angle_cosine == angle_cosine );
  testPrecondition( angle_cosine >= -1.0 );
  testPrecondition( angle_cosine <= 1.0 );
  // Make sure the response function index is valid
  testPrecondition( response_function_index < d_response_functions.size() );
  
  Teuchos::Array<double>::const_iterator start, end, upper_bin_boundary;
  start = d_energy_bin_boundaries.begin();
  end = d_energy_bin_boundaries.end();
  
  // Determine the energy bin
  upper_bin_boundary = binarySearchDiscreteData( start, 
						 end, 
						 particle.getEnergy() );
  
  unsigned energy_bin_offset = 
    std::distance( d_energy_bin_boundaries.begin(), 
		   upper_bin_boundary ) - 1u;
  
  // Determine the cosine bin
  start = d_cosine_bin_boundaries.begin();
  end = d_cosine_bin_boundaries.end();
  
  upper_bin_boundary = binarySearchDiscreteData( start,
						 end,
						 angle_cosine );
  
  unsigned cosine_bin_offset = 
    std::distance( d_cosine_bin_boundaries.begin(), 
		   upper_bin_boundary ) - 1u;
  
  // Determine the time bin
  start = d_time_bin_boundaries.begin();
  end = d_time_bin_boundaries.end();
  
  upper_bin_boundary = binarySearchDiscreteData( start,
						 end,
						 particle.getTime() );
  
  unsigned time_bin_offset = 
    std::distance( d_time_bin_boundaries.begin(),
		   upper_bin_boundary ) - 1u;
  
  // Determine the collision number bin
  Teuchos::Array<unsigned>::const_iterator collision_bin_start,
    collision_bin_end, collision_upper_bin_boundary;
  
  collision_bin_start = d_collision_number_bins.begin();
  collision_bin_end = d_collision_number_bins.end();
  
  collision_upper_bin_boundary = 
    binarySearchDiscreteData( collision_bin_start,
			      collision_bin_end,
			      particle.getCollisionNumber() );
  
  unsigned collision_bin_offset = 
    std::distance( d_collision_number_bins.begin(), 
		   collision_upper_bin_boundary );
  
  // Calculate the bin offset for the desired response function index
  unsigned bin_offset = energy_bin_offset +
    cosine_bin_offset*(d_energy_bin_boundaries.size()-1) +
    time_bin_offset*(d_energy_bin_boundaries.size()-1)*
    (d_cosine_bin_boundaries.size()-1) +
    collision_bin_offset*(d_energy_bin_boundaries.size()-1)*
    (d_cosine_bin_boundaries.size()-1)*
    (d_time_bin_boundaries.size()-1) +
    response_function_index*(d_energy_bin_boundaries.size()-1)*
    (d_cosine_bin_boundaries.size()-1)*
    (d_time_bin_boundaries.size()-1)*
    (d_collision_bins.size());

  // Make sure that the bin offset calculated is valid
  testPostcondition( bin_offset < d_estimator_moments.size() );

  return bin_offset;
}

// Return the number of estimator bins
unsigned Estimator::getNumberOfBins() const
{
  return d_response_functions.size()*
    d_collision_number_bins.size()*
    (d_time_bin_boundaries.size()-1)*
    (d_cosine_bin_boundaries.size()-1)*
    (d_energy_bin_boundaries.size()-1);
}

// Return the number of response functions
unsigned Estimator::getNumberOfResponseFunctions() const
{
  return d_response_functions.size();
}

// Evaluate the desired response function
double Estimator::evaluateResponseFunction( 
				 const BasicParticleState& particle,
				 const unsigned response_function_index ) const
{
  // Make sure the response function index is valid
  testPrecondition( response_function_index < d_response_functions.size() );
  
  return d_response_functions[i]->evaluate( particle );
} 

// Commit history contribution to a bin of the estimator
void Estimator::commitHistoryContributionToBin( const unsigned bin_index,
						const double contribution )
{
  // Make sure that the bin index is valid
  testPrecondition( bin_index < d_response_functions.size()*
		    d_collision_number_bins.size()*
		    (d_time_bin_boundaries.size()-1)*
		    (d_cosine_bin_boundaries.size()-1)*
		    (d_energy_bin_boundaries.size()-1) );
  // Make sure the contribution is valid
  testPrecondition( !ST::isnaninf( contribution ) );

  double moment_contribution = contribution
  d_estimator_moments[bin_index].first += moment_contribution;
  
  moment_contribution *= contribution;
  d_estimator_moments[bin_index].second += moment_contribution;

  moment_contribution *= contribution;
  d_estimator_moments[bin_index].third += moment_contribution;

  moment_contribution *= contribution;
  d_estimator_moments[bin_index].fourth += moment_contribution;
}

// Commit history contribution to the estimator total for a response function
void Estimator::commitHistoryContributionToTotal( 
				        const unsigned response_function_index,
					const double contribution )
{
  // Make sure the response function index is valid
  testPrecondition( response_function_index < d_response_functions.size() );

  double moment_contribution = contribution;
  d_estimator_total_moments[response_function_index].first
    += moment_contribution;

  moment_contribution *= contribution;
  d_estimator_total_moments[response_function_index].second
    += moment_contribution;
  
  moment_contribution *= contribution;
  d_estimator_total_moments[response_function_index].third
    += moment_contribution;

  moment_contribution *= contribution;
  d_estimator_total_moments[response_function_index].fourth
    += moment_contribution;
}

// Calculate the mean for a bin
double Estimator::calculateMean( unsigned bin_index )
{
  // Make sure that the bin index is valid
  testPrecondition( bin_index < d_response_functions.size()*
		    d_collision_number_bins.size()*
		    (d_time_bin_boundaries.size()-1)*
		    (d_cosine_bin_boundaries.size()-1)*
		    (d_energy_bin_boundaries.size()-1) );
  // Make sure that the number of histories run is valid
  testPrecondition( Estimator::num_histories > 0 );
  
  return d_estimator_moments[bin_index].first/Estimator::num_histories;
}

// Calculate the estimator value for a bin
double Estimator::calculateEstimatorValue( unsigned bin_index )
{
  return calculateMean( bin_index )*d_multiplier/d_norm_constant;
}

// Calculate the relative error for a bin
double Estimator::calculateRelativeError( unsigned bin_index )
{
  
}

// Calculate the variance of the variance (VOV) for a bin
double Estimator::calculateVOV( unsigned bin_index )
{
  
}

} // end FACEMC namespace

//---------------------------------------------------------------------------//
// end Estimator.cpp
//---------------------------------------------------------------------------//
