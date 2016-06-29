//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HexMeshTrackLengthFluxEstimator.cpp
//! \author Philip Britt
//! \brief  hex mesh flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

#include <iostream>

// moab includes
#include "moab/Core.hpp"
#include "moab/ScdInterface.hpp"

// std includes
#include <utility>

// FRENSIE Includes
#include "MonteCarlo_HexMeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_DirectionHelpers.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_MOABException.hpp"

namespace MonteCarlo{

template<typename ContributionMultiplierPolicy>
HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::HexMeshTrackLengthFluxEstimator(
	const Estimator::idType id,
	const double multiplier,
	const Teuchos::Array<double>& x_planes,
  const Teuchos::Array<double>& y_planes,
  const Teuchos::Array<double>& z_planes,
  const std::string output_mesh_file_name )
: StandardEntityEstimator<Utility::StructuredHexMesh::HexIndex>( id, multiplier ),
  d_hex_mesh( new Utility::StructuredHexMesh( x_planes, y_planes, z_planes) ),
  d_output_mesh_file_name( output_mesh_file_name )
{
  
  boost::unordered_map<Utility::StructuredHexMesh::HexIndex,
                       Utility::StructuredHexMesh::HexVolume> hex_volumes = 
                       d_hex_mesh->calculateVolumes();

  this->assignEntities( hex_volumes );

  d_hex_begin = d_hex_mesh->getStartHexIDIterator();
  d_hex_end = d_hex_mesh->getEndHexIDIterator();
}

template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::setParticleTypes( 
                const Teuchos::Array<ParticleType>& particle_types )
{
  Estimator::setParticleTypes( particle_types );
}

template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::setResponseFunctions(
                const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions)
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

template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::updateFromGlobalParticleSubtrackEndingEvent(
                const ParticleState& particle,
                const double start_point[3],
                const double end_point[3])
{

  //make sure end point isn't the same as start point
  testPrecondition( start_point[0] != end_point[0] ||
                    start_point[1] != end_point[1] ||
                    start_point[2] != end_point[2] );

  double ray[3] {end_point[0] - start_point[0],
                 end_point[1] - start_point[1],
                 end_point[2] - start_point[2]};

  double track_length = Utility::vectorMagnitude( ray[0],
                                                  ray[1],
                                                  ray[2] );
                                                  
  double direction[3] { ray[0] / track_length,
                        ray[1] / track_length,
                        ray[2] / track_length };


  if( this->isParticleTypeAssigned( particle.getParticleType() ) )
  {        
    
    Teuchos::Array<std::pair<Utility::StructuredHexMesh::HexIndex, double>> contribution_array =
      d_hex_mesh->computeTrackLengths( start_point,
                                       end_point,
                                       direction,
                                       track_length );

    if( contribution_array.size() > 0 )
    {
      EstimatorParticleStateWrapper particle_state_wrapper( particle );    
      for(unsigned i = 0; i < contribution_array.size(); ++i)
      {
        addPartialHistoryContribution( contribution_array[i].first,
                                       particle_state_wrapper,
                                       contribution_array[i].second );
      }
    }
  }

}

template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::exportData(
                    const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                    const bool process_data ) const
{

  // Export data in FRENSIE formatting for data manipulation
  StandardEntityEstimator<Utility::StructuredHexMesh::HexIndex>::exportData( hdf5_file,
                                                           process_data );

  // Set the estimator as a mesh estimator
  EstimatorHDF5FileHandler estimator_hdf5_file( hdf5_file );
  
  estimator_hdf5_file.setMeshEstimator( this->getId() );

  // Export data for visualization
  if( process_data )
  {
    //preset this value to be used with all the functions that MOAB uses
    moab::ErrorCode rval;
  
    //create pointer that points to a new instance of the moab_interface
    std::unique_ptr<moab::Interface> moab_interface (new moab::Core);
  
    //create new structured mesh interface
    std::unique_ptr<moab::ScdInterface> scdiface;
    {
      // Allow moab to create a new heap allocated object
      moab::ScdInterface* raw_scdiface;
      
      rval = moab_interface->query_interface(raw_scdiface);
      
      TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                        Utility::MOABException,
                        moab::ErrorCodeStr[rval] );
      
      //Tell the smart pointer to won the new raw pointer
      scdiface.reset( raw_scdiface);
    }

    //transform planes of mesh into moab useable interleaved coordinates;
    std::vector<double>::size_type x_coordinates_size = d_hex_mesh->getNumberOfXPlanes();
    std::vector<double>::size_type y_coordinates_size = d_hex_mesh->getNumberOfYPlanes();
    std::vector<double>::size_type z_coordinates_size = d_hex_mesh->getNumberOfZPlanes();

    //make an array called coordinates that MOAB can use to construct a structured hex mesh
    unsigned size_of_coordinates = x_coordinates_size * y_coordinates_size * z_coordinates_size;
    double coordinates [size_of_coordinates*3];
    

    
    unsigned l = 0;
    for( unsigned i = 0; i < x_coordinates_size; ++i)
    {
      for( unsigned j = 0; j < y_coordinates_size; ++j)
      {
        for( unsigned k = 0; k < z_coordinates_size; ++k)
        {
          coordinates[l] = d_hex_mesh->getXPlaneLocation(i);
          coordinates[l + 1] = d_hex_mesh->getYPlaneLocation(j);
          coordinates[l + 2] = d_hex_mesh->getZPlaneLocation(k);
          l = l + 3;
        }
      }
    }

    //set up the actual box
    std::unique_ptr<moab::ScdBox> box;
    {
      // Allow moab to create a new heap allocated object
      moab::ScdBox* raw_scdbox;

      //create the box filled with the coordinates
      rval = scdiface->construct_box( moab::HomCoord( 0, 0, 0),
                                      moab::HomCoord( x_coordinates_size - 1,
                                                      y_coordinates_size - 1,
                                                      z_coordinates_size - 1 ),
                                      coordinates,
                                      size_of_coordinates*3,
                                      raw_scdbox );
      
      TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                          Utility::MOABException,
                          moab::ErrorCodeStr[rval] );
      
      //Tell the smart pointer to own the new raw pointer
      box.reset( raw_scdbox);
    }
    std::cout << std::endl;
    for(unsigned i = 0; i < size_of_coordinates*3; i = i + 3)
    {
    
      std::cout << "COORDINATE: " << coordinates[i] << " " << coordinates[i + 1] << " " << coordinates[i + 2] << std::endl;
    
    }
    
    moab::HomCoord size = box->box_size();
    std::cout << "SIZE: " << size[0] << size[1] << size[2] << std::endl;
    
    const double* x_coordinates;
    const double* y_coordinates;
    const double* z_coordinates;
    
    rval = box->get_coordinate_arrays(x_coordinates , y_coordinates , z_coordinates );
    TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                        Utility::MOABException,
                        moab::ErrorCodeStr[rval] );

    /*for(unsigned i = 0; i < 3; ++i)
    {
      for(unsigned j = 0; j < 3; ++j)
      {
        for(unsigned k = 0; k < 3; ++k)
        {
          std::cout << "VERTEX: " << x_coordinates[i] << " " << y_coordinates[j] << " " << z_coordinates[k] << std::endl;
        }
      }
    }*/
    for(unsigned i = 0; i < 3; ++i)
    {
      std::cout << "X COORDINATES: " << x_coordinates[i] << std::endl;
    }
    
    for(unsigned j = 0; j < 3; ++j)
    {
      std::cout << "Y COORDINATES: " << y_coordinates[j] << std::endl;
    }
    
    for(unsigned k = 0; k < 3; ++k)
    {
      std::cout << "Z COORDINATES: " << z_coordinates[k] << std::endl;
    }
    
  }
}

template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::printSummary( 
						       std::ostream& os ) const
{
  // Collect some basic statistics regarding the mesh elements
  Teuchos::Array<unsigned long long> num_zero_hexes(
                                  this->getNumberOfResponseFunctions(), 0ull );
  Teuchos::Array<unsigned long long> num_hexes_lte_1pc_re( 
                                  this->getNumberOfResponseFunctions(), 0ull );
  Teuchos::Array<unsigned long long> num_hexes_lte_5pc_re( 
                                  this->getNumberOfResponseFunctions(), 0ull );
  Teuchos::Array<unsigned long long> num_hexes_lte_10pc_re(
                                  this->getNumberOfResponseFunctions(), 0ull );

  //figure out how many hex elements there are
  
  unsigned long hex_elements = (d_hex_mesh->getNumberOfXPlanes()-1)*
                               (d_hex_mesh->getNumberOfYPlanes()-1)*
                               (d_hex_mesh->getNumberOfZPlanes()-1);

  for( unsigned long i = 0; i < hex_elements; ++i )
  {
  
    const double hex_volume = this->getEntityNormConstant( i );
    
    const Estimator::FourEstimatorMomentsArray& total_hex_data = 
      this->getEntityTotalData( i );

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
        ++num_zero_hexes[i];
      
      if( relative_error <= 0.10 )
        ++num_hexes_lte_10pc_re[i];
      if( relative_error <= 0.05 )
        ++num_hexes_lte_5pc_re[i];
      if( relative_error <= 0.01)
        ++num_hexes_lte_1pc_re[i];
        
    }
  }
  
  os << "Hex mesh track-length flux estimator " << this->getId() << ": "
     << std::endl 
     << "\t Hexes: " << hex_elements << std::endl;

  // Print the percentage of tets with no hits
  os << "\t % of Hexes with no hits (per response func.): ";
    
  for( unsigned i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    os << (double)num_zero_hexes[i]/hex_elements*100.0 << " ";

  os << std::endl;

  // Print the percentage of tets with <= 10% relative error
  os << "\t % of Hexes with <= 10% RE (per response func.): ";

  for( unsigned i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    os << (double)num_hexes_lte_10pc_re[i]/hex_elements*100.0 << " ";

  os << std::endl;

  // Print the percentage of tets with <= 5% relative error
  os << "\t % of Hexes with <= 5% RE (per response func.): ";

  for( unsigned i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    os << (double)num_hexes_lte_5pc_re[i]/hex_elements*100.0 << " ";

  os << std::endl;

  // Print the percentage of tets with <= 1% relative error
  os << "\t % of Hexes with <= 1% RE (per respone func.): ";

  for( unsigned i = 0; i < this->getNumberOfResponseFunctions(); ++i )
    os << (double)num_hexes_lte_1pc_re[i]/hex_elements*100.0 << " ";

  os << std::endl;

}

template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::assignBinBoundaries(
	const Teuchos::RCP<EstimatorDimensionDiscretization>& bin_boundaries )
{

  if( bin_boundaries->getDimension() == COSINE_DIMENSION )
  {
    std::cerr << "Warning: " << bin_boundaries->getDimensionName()
    	      << " bins cannot be set for standard cell estimators. The bins "
     	      << "requested for hexahedral mesh flux estimator " << this->getId()
    	      << " will be ignored."
    	      << std::endl;
  }
  else if( bin_boundaries->getDimension() == TIME_DIMENSION )
  {
    std::cerr << "Warning: " << bin_boundaries->getDimensionName()
    	      << " bins cannot be set for standard cell estimators. The bins "
     	      << "requested for hexahedral mesh flux estimator " << this->getId()
    	      << " will be ignored."
    	      << std::endl;
  }
  else
  {
    StandardEntityEstimator<Utility::StructuredHexMesh::HexIndex>::assignBinBoundaries( 
							      bin_boundaries );
  }

}

}// end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HexMeshTrackLengthFluxEstimator_def.hpp
//---------------------------------------------------------------------------//
