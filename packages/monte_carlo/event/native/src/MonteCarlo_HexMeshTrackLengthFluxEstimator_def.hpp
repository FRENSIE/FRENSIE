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
}

// Set the particle types that can contribute to the estimator
template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::setParticleTypes( 
                const Teuchos::Array<ParticleType>& particle_types )
{
  if( particle_types.size() > 1 )
  {
    std::cerr << "Warning: Hex mesh estimators can only have one "
	      << "particle type contribute. All but the first particle type "
	      << "requested in estimator " << this->getId() 
	      << " will be ignored."
	      << std::endl;
    
    Teuchos::Array<ParticleType> valid_particle_types( 1 );
    valid_particle_types[0] = particle_types.front();
    
    Estimator::setParticleTypes( valid_particle_types );
  }
  else
    Estimator::setParticleTypes( particle_types );
}

// Set the response functions
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

// Add current history estimator contribution
template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::updateFromGlobalParticleSubtrackEndingEvent(
                const ParticleState& particle,
                const double start_point[3],
                const double end_point[3])
{

  // Make sure end point isn't the same as start point
  testPrecondition( !( start_point[0] == end_point[0] &&
                       start_point[1] == end_point[1] &&
                       start_point[2] == end_point[2] ) );

  if( this->isParticleTypeAssigned( particle.getParticleType() ) )
  {
    
    Teuchos::Array<std::pair<Utility::StructuredHexMesh::HexIndex, double>> contribution_array =
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

// Export the estimator data
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
    // Preset this value to be used with all the functions that MOAB uses
    moab::ErrorCode rval;

    // Create pointer that points to a new instance of the moab_interface
    std::unique_ptr<moab::Interface> moab_interface (new moab::Core);
  
    // Create new structured mesh interface
    std::unique_ptr<moab::ScdInterface> scdiface;
    {

      // Allow moab to create a new heap allocated object
      moab::ScdInterface* raw_scdiface;
      
      rval = moab_interface->query_interface(raw_scdiface);
     
      TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                        Utility::MOABException,
                        moab::ErrorCodeStr[rval] );
      
      // Tell the smart pointer to won the new raw pointer
      scdiface.reset( raw_scdiface);

    }

    // Transform planes of mesh into moab useable interleaved coordinates;
    std::vector<double>::size_type x_coordinates_size = d_hex_mesh->getNumberOfXPlanes();
    std::vector<double>::size_type y_coordinates_size = d_hex_mesh->getNumberOfYPlanes();
    std::vector<double>::size_type z_coordinates_size = d_hex_mesh->getNumberOfZPlanes();


    // Make an array called coordinates that MOAB can use to construct a structured hex mesh
    unsigned long size_of_coordinates = x_coordinates_size * y_coordinates_size * z_coordinates_size;
    // This array can get very large, so allocate on the heap instead of the stack.
    double* coordinates = new double[size_of_coordinates*3];
    // Construct array for moab.
    /* 
       An array of interleaved (XYZXYZ) coordinate vectors formed from the plane 
       intersection points must be constructed in order for MOAB to correctly 
       construct the mesh. Note the order of the indices being looped over; the
       indices must be in exactly this order in order for moab to correctly
       construct the mesh. Otherwise, it will connect the points with the edges
       of the mesh in an incorrect order making a lopsided mesh. Note that MOAB
       also requires every single point of the mesh to be constructed, which means
       that plane locations must be repeated in the sequence.
    */
    unsigned l = 0;
    for( unsigned k = 0; k < z_coordinates_size; ++k)
    {
      for( unsigned j = 0; j < y_coordinates_size; ++j)
      {
        for( unsigned i = 0; i < x_coordinates_size; ++i)
        {
          coordinates[l] = d_hex_mesh->getXPlaneLocation(i);
          coordinates[l + 1] = d_hex_mesh->getYPlaneLocation(j);
          coordinates[l + 2] = d_hex_mesh->getZPlaneLocation(k);
          l += 3;
        }
      }
    }
 
    // Set up the actual box
    std::unique_ptr<moab::ScdBox> box;
    {
      // Allow moab to create a new heap allocated object
      moab::ScdBox* raw_scdbox;

      // Create the box filled with the coordinates
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

      // Tell the smart pointer to own the new raw pointer
      box.reset( raw_scdbox);
    }
    scdiface.release();
    delete[] coordinates;   
    std::vector<moab::Tag> mean_tag( this->getNumberOfBins()*
                                     this->getNumberOfResponseFunctions() +
                                     this->getNumberOfResponseFunctions() ),
                           relative_error_tag( mean_tag.size() ),
                           vov_tag( this->getNumberOfResponseFunctions() ),
                           fom_tag( vov_tag.size() );
    // Process moments    
    HexIDIterator hex;
    HexIDIterator start_hex = getStartHex();
    HexIDIterator end_hex = getEndHex();
    unsigned hex_parameter_indices[3];
    for( hex = start_hex; hex != end_hex; ++hex)
    {
      // Convert from hex index to moab entity handle
      d_hex_mesh->getHexPlaneIndices( *hex, hex_parameter_indices);
      moab::EntityHandle moab_hex = box->get_element( hex_parameter_indices[0],
                                                      hex_parameter_indices[1],
                                                      hex_parameter_indices[2] ); 

      const double hex_volume = this->getEntityNormConstant( *hex );
      
      const Estimator::TwoEstimatorMomentsArray& hex_bin_data = 
        this->getEntityBinData( *hex );
      
      std::string mean_tag_prefix = "mean: ";
      std::string relative_error_tag_prefix = "relative_error: ";	
      std::string vov_tag_prefix = "vov: ";
      std::string fom_tag_prefix = "fom: ";
      
      for( unsigned i = 0; i < hex_bin_data.size(); ++i)
      {

        double mean, relative_error;
        
        this->processMoments( hex_bin_data[i],
                              hex_volume,
                              mean,
                              relative_error);
    	  std::string bin_name = this->getBinName( i );
    	  std::string mean_tag_name = mean_tag_prefix + bin_name;
    	  std::string relative_error_tag_name = relative_error_tag_prefix +
    	    bin_name;

        // Assign mean tag data
        rval = moab_interface->tag_get_handle( mean_tag_name.c_str(),
                                               1,
                                               moab::MB_TYPE_DOUBLE,
                                               mean_tag[i],
                                               moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );
        TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[rval] );
                                                        
        rval = moab_interface->tag_set_data( mean_tag[i],
                                             &moab_hex,
                                             1,
                                             &mean );
        TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[rval] );

        // Assign error tag data
        rval = moab_interface->tag_get_handle( relative_error_tag_name.c_str(),
                                               1,
                                               moab::MB_TYPE_DOUBLE,
                                               relative_error_tag[i],
                                               moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );
        TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[rval] );
                                                        
        rval = moab_interface->tag_set_data( relative_error_tag[i],
                                             &moab_hex,
                                             1,
                                             &relative_error );
        TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[rval] );
      }
    
      // Assign total bin data for each entity
      std::string total_tag_prefix = "total_";
      std::string total_mean_tag_name = total_tag_prefix + "mean";
      std::string total_relative_error_tag_name = total_tag_prefix +
                                                          "relative_error";
      std::string total_vov_tag_name = total_tag_prefix + "vov";
      std::string total_fom_tag_name = total_tag_prefix + "fom";
      
      const Estimator::FourEstimatorMomentsArray& total_hex_data = 
        this->getEntityTotalData( *hex );
      
      for( unsigned i = 0; i < total_hex_data.size(); ++ i)
      {
        double mean, relative_error, vov, fom;
        this->processMoments( total_hex_data[i],
                              hex_volume,
                              mean,
                              relative_error,
                              vov,
                              fom);

        unsigned tag_index = this->getNumberOfBins() + i;
        
        // Assign total mean tag data
        rval = moab_interface->tag_get_handle( total_mean_tag_name.c_str(),
                                               1,
                                               moab::MB_TYPE_DOUBLE,
                                               mean_tag[tag_index],
                                               moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );
        TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[rval] );

        rval = moab_interface->tag_set_data( mean_tag[tag_index],
                                             &moab_hex,
                                             1,
                                             &mean );
                                             
        TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[rval] );

        // Assign total relative error tag data
        rval = moab_interface->tag_get_handle( total_relative_error_tag_name.c_str(),
                                               1,
                                               moab::MB_TYPE_DOUBLE,
                                               relative_error_tag[tag_index],
                                               moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );
                                               
        TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[rval] );

        rval = moab_interface->tag_set_data( relative_error_tag[tag_index],
                                             &moab_hex,
                                             1,
                                             &relative_error );
        TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[rval] );

        // Assign total vov tag data
        rval = moab_interface->tag_get_handle( total_vov_tag_name.c_str(),
                                               1,
                                               moab::MB_TYPE_DOUBLE,
                                               vov_tag[tag_index],
                                               moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );
                                               
        TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[rval] );

        rval = moab_interface->tag_set_data( vov_tag[tag_index],
                                             &moab_hex,
                                             1,
                                             &vov );
        TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[rval] );

        // Assign total fom tag data
        rval = moab_interface->tag_get_handle( total_fom_tag_name.c_str(),
                                               1,
                                               moab::MB_TYPE_DOUBLE,
                                               fom_tag[tag_index],
                                               moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );
                                               
        TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[rval] );

        rval = moab_interface->tag_set_data( fom_tag[tag_index],
                                             &moab_hex,
                                             1,
                                             &fom );
        TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[rval] );
      }
    }
    // Export the mesh
    std::vector<moab::Tag> output_tags = mean_tag;
      
    output_tags.insert( output_tags.end(),
                        relative_error_tag.begin(),
                        relative_error_tag.end() );
    output_tags.insert( output_tags.end(),
                        vov_tag.begin(),
                        vov_tag.end() );
    output_tags.insert( output_tags.end(),
                        fom_tag.begin(),
                        fom_tag.end() ); 
    rval = moab_interface->write_file( d_output_mesh_file_name.c_str() );
    TEST_FOR_EXCEPTION( rval != moab::MB_SUCCESS,
                        Utility::MOABException,
                        moab::ErrorCodeStr[rval] );
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
  Teuchos::Array<unsigned long long> num_zero_hexes(
                                  this->getNumberOfResponseFunctions(), 0ull );
  Teuchos::Array<unsigned long long> num_hexes_lte_1pc_re( 
                                  this->getNumberOfResponseFunctions(), 0ull );
  Teuchos::Array<unsigned long long> num_hexes_lte_5pc_re( 
                                  this->getNumberOfResponseFunctions(), 0ull );
  Teuchos::Array<unsigned long long> num_hexes_lte_10pc_re(
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
	const Teuchos::RCP<EstimatorDimensionDiscretization>& bin_boundaries )
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
