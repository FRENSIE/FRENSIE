//---------------------------------------------------------------------------//
//
// \file   MonteCarlo_HexMeshTrackLengthFluxEstimator_def.hpp
// \author Philip Britt
// \brief  Hex mesh flux estimator class definition.
//
//---------------------------------------------------------------------------//

// moab includes
#include "moab/Core.hpp"
#include "moab/ScdInterface.hpp"

// std includes
#include <utility>
#include <iterator>

// FRENSIE Includes
#include "MonteCarlo_HexMeshTrackLengthFluxEstimator.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_MOABException.hpp"

namespace MonteCarlo{

// Constructor
template<typename ContributionMultiplierPolicy>
HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::HexMeshTrackLengthFluxEstimator(
	const Estimator::idType id,
	const double multiplier,
	const std::vector<double>& x_planes,
  const std::vector<double>& y_planes,
  const std::vector<double>& z_planes,
  const std::string output_mesh_file_name )
: StandardEntityEstimator<Utility::StructuredHexMesh::HexIndex>( id, multiplier ),
  d_hex_mesh( new Utility::StructuredHexMesh( x_planes, y_planes, z_planes) ),
  d_output_mesh_file_name( output_mesh_file_name )
{
  boost::unordered_map<Utility::StructuredHexMesh::HexIndex,
                       Utility::StructuredHexMesh::HexVolume> hex_volumes = 
                       d_hex_mesh->calculateVolumes();

  this->assignEntities( hex_volumes );
}

// Set the particle types that can contribute to the estimator
template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::setParticleTypes( 
                const std::vector<ParticleType>& particle_types )
{
  if( particle_types.size() > 1 )
  {
    std::cerr << "Warning: Hex mesh estimators can only have one "
	      << "particle type contribute. All but the first particle type "
	      << "requested in estimator " << this->getId() 
	      << " will be ignored."
	      << std::endl;
    
    std::vector<ParticleType> valid_particle_types( 1 );
    valid_particle_types[0] = particle_types.front();
    
    Estimator::setParticleTypes( valid_particle_types );
  }
  else
    Estimator::setParticleTypes( particle_types );
}

// Set the response functions
template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::setResponseFunctions(
                const std::vector<std::shared_ptr<ResponseFunction> >& response_functions)
{

  for( unsigned i = 0; i < response_functions.size(); ++i )
  {
    if( !response_functions[i]->isSpatiallyUniform() )
    {
      std::cerr << "Warning: hexahedral mesh track length estimators can only "
		    << "be used with spatially uniform response functions. Results from "
		    << "hexahdedral mesh track length estimator " << getId()
		    << "will not be correct." << std::endl;
    }
  }
  StandardEntityEstimator::setResponseFunctions( response_functions );
}

// Add current history estimator contribution
template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::updateFromGlobalParticleSubtrackEndingEvent(
                const ParticleState& particle,
                const double start_point[3],
                const double end_point[3])
{

  if( this->isParticleTypeAssigned( particle.getParticleType() ) )
  {
    
    std::vector<std::pair<Utility::StructuredHexMesh::HexIndex, double>> contribution_array =
      d_hex_mesh->computeTrackLengths( start_point,
                                       end_point );
    
    if( contribution_array.size() > 0 )
    {
      EstimatorParticleStateWrapper particle_state_wrapper( particle );    
      for(unsigned i = 0; i < contribution_array.size(); ++i)
      {
        double weighted_contribution = contribution_array[i].second *
          ContributionMultiplierPolicy::multiplier( particle );
        
        this->addPartialHistoryContribution( contribution_array[i].first,
                                             particle_state_wrapper,
                                             weighted_contribution );
      }
    }
  }

}

// Get start iterator over list of hex element IDs
template<typename ContributionMultiplierPolicy>
auto HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::getStartHex() const->HexIDIterator
{

  return d_hex_mesh->getStartHexIDIterator();

}

// Get end iterator over list of hex element IDs
template<typename ContributionMultiplierPolicy>
auto HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::getEndHex() const->HexIDIterator
{

  return d_hex_mesh->getEndHexIDIterator();

}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::printSummary( 
						       std::ostream& os ) const
{
  // Collect some basic statistics regarding the mesh elements
  std::vector<unsigned long long> num_zero_hexes(
                                  this->getNumberOfResponseFunctions(), 0ull );
  std::vector<unsigned long long> num_hexes_lte_1pc_re( 
                                  this->getNumberOfResponseFunctions(), 0ull );
  std::vector<unsigned long long> num_hexes_lte_5pc_re( 
                                  this->getNumberOfResponseFunctions(), 0ull );
  std::vector<unsigned long long> num_hexes_lte_10pc_re(
                                  this->getNumberOfResponseFunctions(), 0ull );

  
  Utility::StructuredHexMesh::HexIDIterator start = this->getStartHex();
  Utility::StructuredHexMesh::HexIDIterator end = this->getEndHex();
  for( auto i = start; i != end; ++i )
  {
    const double hex_volume = this->getEntityNormConstant( std::distance(start, i) );

    const Estimator::FourEstimatorMomentsArray& total_hex_data = 
      this->getEntityTotalData( std::distance(start, i) );

    for( unsigned long j = 0; j != total_hex_data.size(); ++j )
    {
    
      double mean, relative_error, vov, fom;
     
      this->processMoments( total_hex_data[j],
                            hex_volume,
                            mean,
                            relative_error,
                            vov,
                            fom );
                            
      if( mean == 0.0 )
        ++num_zero_hexes[j];    
      if( relative_error <= 0.10 )
        ++num_hexes_lte_10pc_re[j];
      if( relative_error <= 0.05 )
        ++num_hexes_lte_5pc_re[j];
      if( relative_error <= 0.01)
        ++num_hexes_lte_1pc_re[j];
    }  
  }
  unsigned long hex_elements = std::distance(start, end);
  os << "Hex mesh track-length flux estimator " << this->getId() << ": "
     << std::endl 
     << "\t Hexes: " << hex_elements << std::endl;

  // Print the percentage of hexs with no hits
  os << "\t % of Hexes with no hits (per response func.): ";
    
  for( unsigned i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    os << (double)num_zero_hexes[i]/hex_elements*100.0 << " ";

  os << std::endl;

  // Print the percentage of hexs with <= 10% relative error
  os << "\t % of Hexes with <= 10% RE (per response func.): ";

  for( unsigned i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    os << (double)num_hexes_lte_10pc_re[i]/hex_elements*100.0 << " ";

  os << std::endl;

  // Print the percentage of hexs with <= 5% relative error
  os << "\t % of Hexes with <= 5% RE (per response func.): ";
f
  for( unsigned i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    os << (double)num_hexes_lte_5pc_re[i]/hex_elements*100.0 << " ";

  os << std::endl;

  // Print the percentage of hexs with <= 1% relative error
  os << "\t % of Hexes with <= 1% RE (per respone func.): ";

  for( unsigned i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    os << (double)num_hexes_lte_1pc_re[i]/hex_elements*100.0 << " ";

  os << std::endl;

}

// Assign bin boundaries to an estimator dimension
template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::assignBinBoundaries(
	const std::shared_ptr<EstimatorDimensionDiscretization>& bin_boundaries )
{

  if( bin_boundaries->getDimension() == COSINE_DIMENSION )
  {
    std::cerr << "Warning: " << bin_boundaries->getDimensionName()
    	      << " bins cannot be set for hex mesh track length flux "
              << "estimators. The bins requested for estimator "
              << this->getId() << " will be ignored." << std::endl;
  }
  else if( bin_boundaries->getDimension() == TIME_DIMENSION )
  {
    std::cerr << "Warning: " << bin_boundaries->getDimensionName()
    	      << " bins cannot be set for hex mesh track length flux "
              << "estimators yet. The bins requested for estimator "
              << this->getId() << " will be ignored." << std::endl;
  }
  else
  {
    StandardEntityEstimator<Utility::StructuredHexMesh::HexIndex>::assignBinBoundaries( 
							      bin_boundaries );
  }

}

}// End MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HexMeshTrackLengthFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
