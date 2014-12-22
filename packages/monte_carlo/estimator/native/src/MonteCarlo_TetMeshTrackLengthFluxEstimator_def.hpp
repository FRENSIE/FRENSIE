//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TetMeshTrackLengthFluxEstimator.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Tet mesh flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

// Moab Includes
#include <moab/Core.hpp>

// FRENSIE Includes
#include "MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp"
#include "Utility_TetrahedronHelpers.hpp"
#include "Utility_MOABException.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Constructor
template<typename ContributionMultiplierPolicy>
TetMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::TetMeshTrackLengthFluxEstimator(
		                      const Estimator::idType id,
				              const double multiplier,
				              const std::string input_mesh_file_name,
		                      const std::string output_mesh_file_name )
  : StandardEntityEstimator<moab::EntityHandle>( id, multiplier ),
    d_moab_interface( new moab::Core ),
    d_tet_meshset,
    d_kd_tree( new moab::AdaptiveKDTree( d_moab_interface.getRawPtr() ) ),
    d_kd_tree_root(),
    d_obb_tree( new moab::OrientedBoxTreeTool( d_moab_interface.getRawPtr() )),
    d_obb_tree_root(),
    d_last_visited_tet(),
    d_last_visited_cell(),
    d_tet_barycentric_transform_matrices()
{
  // ------------------------ Load Meshset ------------------------------------

  // Create empty MOAB meshset
  moab::EntityHandle d_tet_meshset;
  moab::ErrorCode return_value = d_moab_interface->create_meshset(
					moab::MESHSET_SET, d_tet_meshset);
  
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );

  // Populate MOAB meshset with data from input file                   
  return_value = d_moab_interface->load_file(
                            input_mesh_file_name.c_str(), &d_tet_meshset);
                             
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );                
  
  // Range (domain) of all tetrahedral elements
  moab::Range all_tet_elements;

  // ---------------------- Reduce Meshset to 3D ------------------------------
  
  // Extract 3D elements from meshset
  return_value = d_moab_interface->get_entities_by_dimension(
                        d_tet_meshset, 3, all_tet_elements);
  
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
  
  // Clear the meshset                    
  return_value = d_moab_interface->clear_meshset(&d_tet_meshset, 1);
  
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
                      
  // Reconstruct the meshset using only 3D entitites                    
  return_value = d_moab_interface->add_entities(
                                         d_tet_meshset, all_tet_elements);
  
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
  
  unsigned int number_of_tets = all_tet_elements.size();
  
  for( moab::Range::const_iterator tet = all_tet_elements.begin(); 
       tet != all_tet_elements.end(); 
       ++tet )
    {
      // Extract the vertex data for the given tet
      std::vector<moab::EntityHandle> vertex_handles;
      d_moab_interface->get_connectivity( tet, 1, vertex_handles );
     
      // Test that the vertex entity contains four points
      TEST_FOR_EXCEPTION( vertex_handles.size() != 4,
			  Utility::MOABException,
			  "Error: tet found with incorrect number of vertices "
			  "(" << vertex_handles.size() << " != 4)" );
     
      moab::CartVect vertices[4];
      
      for( unsigned j = 0; j < vertex_handles.size(); ++j )
      {
	d_moab_interface->get_coords( &vertex_handles[j], 
				      1, 
				      vertices[j].array() );
      }
                                                                
      // Calculate Barycentric Matrix
      moab::Matrix3& barycentric_transform_matrix = 
	  d_tet_barycentric_transform_matrices[tet];
      
      Utility::calculateBarycentricTransformMatrix( 
						                        vertices[0],
						                        vertices[1],
						                        vertices[2],
						                        vertices[3],
                                                barycentric_transform_matrix );

      // Calculate tet volumes
      boost::unordered_map<moab::EntityHandle,double> entity_volumes;
      
      entity_volumes[*tet] = Utility::calculateTetrahedronVolume( vertices[0],
								  vertices[1],
								  vertices[2],
								  vertices[3]);

      // Assign the entity volumes
      this->assignEntities( entity_volumes );
   }
  
  // ---------------------------- KD Trees ------------------------------------
  
  int current_dimension;
  
  // Get dimension of the input set
  current_dimension = 
    d_moab_interface->dimension_from_handle(all_tet_elements[0]);
  
  moab::Range surface_triangles;
  
  // Determine the edges from the input set
  return_value = d_moab_interface->get_adjacencies( all_tet_elements, 
						    current_dimension - 1, 
						    true,
						    surface_triangles, 
						    moab::Interface::UNION );
                            
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
  
  all_tet_elements.merge( surface_triangles );
  
  const char settings[]="MESHSET_FLAGS=0x1;TAG_NAME=0";
  moab::FileOptions fileopts(settings);
  
  d_kd_tree->build_tree(all_tet_elements, &d_kd_tree_root, &fileopts);

  // Set up OBB Tree (how is this done?)
} 

// Set the response functions
template<typename ContributionMultiplierPolicy>
void TetMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::setResponseFunctions(
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions )
{
  for( unsigned i = 0; i < response_functions.size(); ++i )
  {
    if( !response_functions[i]->isSpatiallyUniform() )
    {
      std::cerr << "Warning: tetrahedral mesh track length estimators can only "
		<< "be used with spatially uniform response functions. Results from "
		<< "tetrahdedral mesh track length estimator " << getId()
		<< "will not be correct." << std::endl;
    }
  }
  StandardEntityEstimator::setResponseFunctions( response_functions );
}

// Set the particle types that can contribute to the estimator
template<typename ContributionMultiplierPolicy>
void TetMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::setParticleTypes( const Teuchos::Array<ParticleType>& particle_types )
{
  Estimator::setParticleTypes( particle_types );
}

// Add current history estimator contribution
template<typename ContributionMultiplierPolicy>
void TetMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::updateFromParticleSubtrackEndingEvent(
			      const ParticleState& particle,
			      const Geometry::ModuleTraits::InternalCellHandle,
			      const double track_length )
{

}

// Export the estimator data
template<typename ContributionMultiplierPolicy>
void TetMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::exportData(
                                           EstimatorHDF5FileHandler& hdf5_file,
					                       const bool process_data ) const
{
  // Export data in FRENSIE formatting for data manipulation
  StandardEntityEstimator::exportData();
        
  // Export data for visualization
  if( process_data )
  {
    moab::Range all_tet_elements;
    moab::ErrorCode return_value = d_moab_interface->get_entities_by_dimension(
                                       d_tet_meshset, 3, all_tet_elements);
                                       
    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                        Utility::MOABException,
                        moab::ErrorCodeStr[return_value] );
    
    // Process moments
    for ( moab::Range::const_iterator tet = all_tet_elements.begin(); 
	  tet != all_tet_elements.end(); 
	  ++tet )
    {
      double tet_volume = this->getEntityNormConstant( *tet );
      
      const Estimator::TwoEstimatorMomentsArray& tet_bin_data = 
	this->getEntityBinData( *tet );
      
      Teuchos::Array<moab::Tag> mean_tag( tet_bin_data.size() ), 
	relative_error_tag( tet_bin_data.size() );

      std::string mean_tag_prefix = "mean_";
      std::string relative_error_tag_prefix = "relative_error_";	

      for( unsigned i = 0; i < tet_bin_data.size(); ++i )
      {
	double mean, relative_error;
	
	this->processMoments( tet_bin_data[i],
			      tet_volume,
			      mean, 
			      relative_error );

	std::string bin_name = this->getBinName( i );
	std::string mean_tag_name = mean_tag_prefix + bin_name;
	std::string relative_error_tag_name = relative_error_tag_prefix +
	  bin_name;
	  
	moab::ErrorCode return_value = 
	  d_moab_interface->tag_get_handle( 
				       mean_tag_name.c_str(),
				       1,
				       moab::MB_TYPE_DOUBLE,
				       mean_tag[i],
				       moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );

	TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );

	return_value = d_moab_interface->tag_set_data( mean_tag[i], 
						       *tet,
						       1,
						       mean );

	TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
      }
    }
  }   
}

// Print the estimator data
template<typename ContributionMultiplierPolicy>
void TetMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::print( 
						       std::ostream& os ) const
{
  StandardEntityEstimator::printImplementation( os );
}

// Assign bin boundaries to an estimator dimension
template<typename ContributionMultiplierPolicy>
void TetMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::assignBinBoundaries(
	const Teuchos::RCP<EstimatorDimensionDiscretization>& bin_boundaries )
{
  // if( bin_boundaries->getDimension() != ENERGY_DIMENSION )
  // {
  //    std::cerr << "Warning: " << bin_boundaries->getDimensionName()
  // 	      << " bins cannot be set for standard cell estimators. The bins "
  // 	      << "requested for tetrahdedral mesh flux estimator " << this->getId()
  // 	      << " will be ignored."
  // 	      << std::endl;
  // }
  else
    StandardEntityEstimator<cellIdType>::assignBinBoundaries( bin_boundaries );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
