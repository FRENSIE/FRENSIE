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

// Used for intersection data storage and comparison
struct ray_data {
  double intersect;
  moab::EntityHandle triangle;
};

// Compare and sort intersection data
inline static bool compare(const ray_data &a, const ray_data &b)
{
    return a.intersect < b.intersect;
}

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
    d_tet_barycentric_transform_matrices(),
    d_tet_reference_vertices()
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

      // Assign reference vertices (always fourth vertex)
      // Check implementation in .hpp (I put double but should I put double[3]?)
      vertices[3] = d_tet_reference_vertices[tet];

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
  std::vector<double> ray_tet_intersections;
  std::vector<moab::EntityHandle> tet_surface_triangles;

  // Get all intersections of the ray and the tets
  moab:ErrorCode return_value = 
       d_kd_tree->ray_intersect_triangles( d_kd_tree_root,
                                           1e-6,
                                           particle.getDirection().array(),
                                           particle.getPosition().array(),
                                           tet_surface_triangles,
                                           ray_tet_intersections,
                                           0,
                                           track_length );
                                           
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
                      
  // Sort all intersections of the ray with the tets
  std::vector<ray_data> intersection_data;
  
  // Transfer the data to ray_data structures for sorting
  for( unsigned int i = 0; i < ray_tet_intersections.size(); i++ )
  {
    ray_data data;
    data.intersect = ray_tet_intersections[i];
    data.triangle  = tet_surface_triangles[i];
    intersection_data.push_back(data);
  }
  
  std::sort(intersection_data.begin(), intersection_data.end(), compare);
  
  // Transfer the data back to the previous data structures
  for( unsigned int i = 0; i < ray_tet_intersections.size(); i++ )
  {
    ray_tet_intersections[i] = intersection_data[i].intersect;
    tet_surface_triangles[i] = intersection_data[i].triangle;
  }
    
  // Account for the case where there are no intersections (entirely in tet)
  if( ray_tet_intersections.size() == 0 )
  {
    
  }
  else                  
  {
    moab::CartVect hit_point;
    std::vector<moab::CartVect> array_of_hit_points;
    moab::CartVect tet_centroid;
    moab::EntityHandle tet;
  
    // Add the origin point of the ray to the array of points
    array_of_hit_points.push_back( particle.getPosition() );
  
    moab::EntityHandle next_tet_intersected = 0;
  
    for( unsigned int i = 0; i < ray_tet_intersections.size(); i++ )
    {
      hit_point = particle.getDirection()*ray_tet_intersections[i] + 
                                                        particle.getPosition();
      array_of_hit_points.push_back(hit_point);
      tet_centroid = ( (array_of_hit_points[i+1]+array_of_hit_points[i])/2.0 );
      
      tet = whichTetIsPointIn( tet_centroid );
      
      if( tet > 0 )
      {
        if( i != 0)
          partial_track_length =
                        ray_tet_intersections[i] - ray_tet_intersections[i-1];
        else
          partial_track_length = ray_tet_intersections[i]j;
      } 
      
      // FIGURE OUT HOW TO ADD TRACK LENGTH TO MESH TALLY
      // Map of tets and contributionss
      
    }
    
    // Get any left over track length
    if ( ray_tet_intersections[ray_tet_intersections.size() -1] < track_length )
    {
      partial_track_length = track_length - 
                       ray_tet_intersections[ray_tet_intersections.size() - 1];
      
      const double final_location[3];
      
      final_location[0] = particle.getXPosition() + 
                                          particle.getXDirection*track_length;
      final_location[1] = particle.getYPosition() + 
                                          particle.getYDirection*track_length;
      final_location[2] = particle.getZPosition() + 
                                          particle.getZDirection*track_length;
      
      tet = whichTetIsPointIn( final_location );
      
      // Update the last visited tet
      d_last_visited_tet = tet;
      
      // FIGURE OUT HOW TO ADD TRACK LENGTH TO MESH TALLY
      // Map of tets and contributionss           
    }
  }
}

// Assign bin boundaries to an estimator dimension
template<typename ContributionMultiplierPolicy>
moab::EntityHandle TetMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::whichTetIsPointIn(
	const double point[3] )
{
  // Iteration for looping over the leaves of a tree
  moab::AdaptiveKDTreeIter kd_tree_iteration;
  
  moab::ErrorCode return_value = d_kd_tree->leaf_containing_point(
                                                         d_kd_tree_root,
                                                         point.array(),
                                                         kd_tree_iteration);
                                                        
  
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
                      
  moab::EntityHandle leaf = kd_tree_iteration.handle();
  moab::Range = tets_in_leaf;
  
  return_value = d_moab_interface->get_entities_by_dimension( leaf,
                                                              3,
                                                              tets_in_leaf,
                                                              false );
                                                              
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );                                                            
                                            
  for( Range::const_iterator tet = tets_in_leaf.begin(); 
                                           tet != tets_in_leaf.end();  tet++ )
  {
    if( Utility::isPointInTet( point,
                               d_tet_reference_vertices[tet]*,
                               d_tet_barycentric_transform_matrices[tet]* ) )
    {
      return tet;
    }
  }
  
  return 0;
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
      
      Teuchos::Array<moab::Tag> mean_tag( tet_bin_data.size() + 1 ), 
	  relative_error_tag( tet_bin_data.size() + 1 ),
	  vov_tag( tet_bin_data.size() + 1 ),
	  fom_tag( tet_bin_data.size() + 1 );

      std::string mean_tag_prefix = "mean_";
      std::string relative_error_tag_prefix = "relative_error_";	
      std::string vov_tag_prefix = "vov_";
      std::string fom_tag_prefix = "fom_";

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
	  
	    // Assign mean tag data
	    moab::ErrorCode return_value = d_moab_interface->tag_get_handle( 
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
        
        // Assign error tag data                    
	    moab::ErrorCode return_value = d_moab_interface->tag_get_handle( 
		                               relative_error_tag_name.c_str(),
	                                   1,
	                                   moab::MB_TYPE_DOUBLE,
				                       relative_error_tag[i],
				                       moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );

	    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[return_value] );

	    return_value = d_moab_interface->tag_set_data( relative_error_tag[i], 
		                        				       *tet,
		                        				       1,
						                               relative_error );

	    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[return_value] );
      }
      
      // Assign total bin data for each entity
      std::string total_tag_prefix = "total_";
      std::string total_mean_tag_name = total_tag_prefix + "mean"
      std::string total_relative_error_tag_name = total_tag_prefix +
                                                          "relative_error"
      std::string total_vov_tag_name = total_tag_prefix + "vov"
      std::string total_fom_tag_name = total_tag_prefix + "fom"
    
      const Estimator::FourEstimatorMomentsArray& total_tet_bin_data = 
	                                          this->getEntityTotalData( *tet );

      int end = tet_bin_data.size();
      double mean, relative_error, vov, fom;

      this->processMoments( total_tet_bin_data,
                            tet_volume,
                            mean,
                            relative_error,
                            vov,
                            fom); 

      // Assign total mean tag data                    
	  moab::ErrorCode return_value = d_moab_interface->tag_get_handle( 
		                             total_mean_tag_name.c_str(),
	                                 1,
	                                 moab::MB_TYPE_DOUBLE,
				                     mean_tag[end],
				                     moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );

	  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                          Utility::MOABException,
                          moab::ErrorCodeStr[return_value] );

	  return_value = d_moab_interface->tag_set_data( mean_tag[end], 
		                         				     *tet,
		                        				     1,
						                             mean );

	  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                          Utility::MOABException,
                          moab::ErrorCodeStr[return_value] );
                          
      // Assign total relative error tag data                    
	  moab::ErrorCode return_value = d_moab_interface->tag_get_handle( 
		                             total_relative_error_tag_name.c_str(),
	                                 1,
	                                 moab::MB_TYPE_DOUBLE,
				                     relative_error_tag[end],
				                     moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );

	  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                          Utility::MOABException,
                          moab::ErrorCodeStr[return_value] );

	  return_value = d_moab_interface->tag_set_data( relative_error_tag[end], 
		                         				     *tet,
		                        				     1,
						                             relative_error );

	  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                          Utility::MOABException,
                          moab::ErrorCodeStr[return_value] );
                          
      // Assign total vov tag data                    
	  moab::ErrorCode return_value = d_moab_interface->tag_get_handle( 
		                             total_vov_tag_name.c_str(),
	                                 1,
	                                 moab::MB_TYPE_DOUBLE,
				                     vov_tag[end],
				                     moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );

	  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                          Utility::MOABException,
                          moab::ErrorCodeStr[return_value] );

	  return_value = d_moab_interface->tag_set_data( vov_tag[end], 
		                         				     *tet,
		                        				     1,
						                             vov );

	  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                          Utility::MOABException,
                          moab::ErrorCodeStr[return_value] );                          
      
      // Assign total fom tag data                    
	  moab::ErrorCode return_value = d_moab_interface->tag_get_handle( 
		                             total_fom_tag_name.c_str(),
	                                 1,
	                                 moab::MB_TYPE_DOUBLE,
				                     fom_tag[end],
				                     moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );

	  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                          Utility::MOABException,
                          moab::ErrorCodeStr[return_value] );

	  return_value = d_moab_interface->tag_set_data( fom_tag[end], 
		                         				     *tet,
		                        				     1,
						                             fom );

	  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                          Utility::MOABException,
                          moab::ErrorCodeStr[return_value] );      
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
  if( bin_boundaries->getDimension() == COSINE_DIMENSION )
  {
    std::cerr << "Warning: " << bin_boundaries->getDimensionName()
    	      << " bins cannot be set for standard cell estimators. The bins "
     	      << "requested for tetrahdedral mesh flux estimator " << this->getId()
    	      << " will be ignored."
    	      << std::endl;
  }
  else if( bin_boundaries->getDimension() == TIME_DIMENSION )
  {
    std::cerr << "Warning: " << bin_boundaries->getDimensionName()
    	      << " bins cannot be set for standard cell estimators. The bins "
     	      << "requested for tetrahdedral mesh flux estimator " << this->getId()
    	      << " will be ignored."
    	      << std::endl;
  }
  else
    StandardEntityEstimator<cellIdType>::assignBinBoundaries( bin_boundaries );
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
