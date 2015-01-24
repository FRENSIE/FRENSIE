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
#include "Utility_Tuple.hpp"
#include "Utility_TetrahedronHelpers.hpp"
#include "Utility_MOABException.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Compare and sort intersection data
template<typename ContributionMultiplierPolicy>
inline bool TetMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::compareIntersections(
							  const IntersectionData &a,
							  const IntersectionData &b )
{
    return a.first < b.first;
}

// Constructor
template<typename ContributionMultiplierPolicy>
TetMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::TetMeshTrackLengthFluxEstimator(
		                      const Estimator::idType id,
				              const double multiplier,
				              const std::string input_mesh_file_name,
		                      const std::string output_mesh_file_name )
  : StandardEntityEstimator<moab::EntityHandle>( id, multiplier ),
    d_moab_interface( new moab::Core ),
    d_tet_meshset(),
    d_kd_tree( new moab::AdaptiveKDTree( d_moab_interface.getRawPtr() ) ),
    d_kd_tree_root(),
    d_obb_tree( new moab::OrientedBoxTreeTool( d_moab_interface.getRawPtr() )),
    d_obb_tree_root(),
    d_last_visited_cell(),
    d_tet_barycentric_transform_matrices(),
    d_tet_reference_vertices(),
    d_output_mesh_name( output_mesh_file_name )
{
  // Create empty MOAB meshset
  moab::EntityHandle d_tet_meshset;
  moab::ErrorCode return_value = d_moab_interface->create_meshset(
					moab::MESHSET_SET, d_tet_meshset);
  
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );

  // Populate MOAB meshset with data from input file
  std::cout << "Loading tetrahedral mesh from file "
	    << input_mesh_file_name << " ... ";
  std::cout.flush();
  
  return_value = d_moab_interface->load_file(
                            input_mesh_file_name.c_str(), &d_tet_meshset);
                             
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );                
  
  // Range (domain) of all tetrahedral elements
  moab::Range all_tet_elements;
  
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
  
  boost::unordered_map<moab::EntityHandle,double> entity_volumes;
  
  for( moab::Range::const_iterator tet = all_tet_elements.begin(); 
       tet != all_tet_elements.end(); 
       ++tet )
    {
      // Extract the vertex data for the given tet
      std::vector<moab::EntityHandle> vertex_handles;
      moab::EntityHandle current_tet = *tet;
      d_moab_interface->get_connectivity( &current_tet, 1, vertex_handles );
     
      // Test that the vertex entity contains four points
      TEST_FOR_EXCEPTION( vertex_handles.size() != 4,
			  Utility::MOABException,
			  "Error: tet found with incorrect number of vertices "
			  "(" << vertex_handles.size() << " != 4)" );
     
      moab::CartVect vertices[4];

      for( unsigned j = 0; j != vertex_handles.size(); ++j )
      {
	    d_moab_interface->get_coords( &vertex_handles[j], 
				      1, 
				      vertices[j].array() );
      }
                                                                
      // Calculate Barycentric Matrix
      moab::Matrix3& barycentric_transform_matrix = 
	  d_tet_barycentric_transform_matrices[*tet];
      
      Utility::calculateBarycentricTransformMatrix( 
						                        vertices[0],
						                        vertices[1],
						                        vertices[2],
						                        vertices[3],
                                                barycentric_transform_matrix );

      // Assign reference vertices (always fourth vertex)
      d_tet_reference_vertices[*tet] = vertices[3];

      // Calculate tet volumes
      entity_volumes[*tet] = Utility::calculateTetrahedronVolume( vertices[0],
								  vertices[1],
								  vertices[2],
								  vertices[3]);
   }
   
   // Assign the entity volumes
   this->assignEntities( entity_volumes );
  
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

  std::cout << "(constructed " << entity_volumes.size() 
	    << " tetrahedrons) done." << std::endl;
    
  // Create the kd-tree
  std::cout << "Constructing kd-tree for tetrahedral mesh from file "
	    << input_mesh_file_name << " ... ";
  std::cout.flush();
    
  d_kd_tree->build_tree(all_tet_elements, &d_kd_tree_root, &fileopts);

  std::cout << "done." << std::endl;
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
void TetMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::updateFromGlobalParticleSubtrackEndingEvent( 
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] )
{
  // Calculate the track length
  double track_length = sqrt(
                (end_point[0]-start_point[0])*(end_point[0]-start_point[0]) +
                (end_point[1]-start_point[1])*(end_point[1]-start_point[1]) +
                (end_point[2]-start_point[2])*(end_point[2]-start_point[2]) );

  std::vector<double> ray_tet_intersections;
  std::vector<moab::EntityHandle> tet_surface_triangles;
                           
  moab::ErrorCode return_value = 
       d_kd_tree->ray_intersect_triangles( d_kd_tree_root,
                                           1e-6,
                                           particle.getDirection(),
                                           start_point,
                                           tet_surface_triangles,
                                           ray_tet_intersections,
                                           0,
                                           track_length );
                                           
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );

  // Account for the case where there are no intersections (entirely in tet)
  if( ray_tet_intersections.size() == 0 )
  {
    moab::EntityHandle tet = whichTetIsPointIn( start_point );
    
    if( tet != 0 )
    {
      // Add partial history contribution
      addPartialHistoryContribution( tet,
				     particle,
				     0,
				     track_length );
    }
  }
  else
  {
    // Sort all intersections of the ray with the tets
    std::vector<IntersectionData> intersection_data;
  
    // Transfer the data to ray_data structures for sorting
    for( unsigned int i = 0; i < ray_tet_intersections.size(); i++ )
    {
      IntersectionData data;
      data.first = ray_tet_intersections[i];
      data.second  = tet_surface_triangles[i];
      intersection_data.push_back( data );
    }
    
    std::sort( intersection_data.begin(), 
	       intersection_data.end(), 
	       compareIntersections );
    
    tet_surface_triangles.clear();
    ray_tet_intersections.clear();
  
    moab::CartVect hit_point;
    std::vector<moab::CartVect> array_of_hit_points;
    moab::CartVect tet_centroid;
    moab::EntityHandle tet;
    moab::CartVect start_point_cv( start_point[0], 
                                   start_point[1],
                                   start_point[2] );

    double partial_track_length;
  
    // Add the origin point of the ray to the array of points
    array_of_hit_points.push_back( start_point_cv );
  
    moab::EntityHandle next_tet_intersected = 0;
  
    for( unsigned int i = 0; i < ray_tet_intersections.size(); ++i )
    {
      // Update intersection point
      hit_point[0] = particle.getXDirection() * intersection_data[i].first
                                                            + start_point[0];
      hit_point[1] = particle.getYDirection() * intersection_data[i].first
                                                            + start_point[1];
      hit_point[2] = particle.getZDirection() * intersection_data[i].first
                                                            + start_point[2];
      
      array_of_hit_points.push_back( hit_point );
      tet_centroid = ( (array_of_hit_points[i + 1] + 
                        array_of_hit_points[i])/2.0 );
      
      tet = whichTetIsPointIn( tet_centroid.array() );
      
      if( tet > 0 )
      {
        if( i != 0)
          partial_track_length = intersection_data[i].first -
                                 intersection_data[i - 1].first;
                        
        else
          partial_track_length = intersection_data[i].first;
      
	// Add partial history contribution
	addPartialHistoryContribution( tet,
				       particle,
				       0,
				       partial_track_length );
      }
      
    }
    
    // Get any left over track length
    if ( intersection_data.back().first < track_length )
    {
      partial_track_length = track_length - intersection_data.back().first;
      
      tet = whichTetIsPointIn( end_point );
      
      // Add partial history contribution
      if( tet != 0 )
      {
	addPartialHistoryContribution( tet,
				       particle,
				       0,
				       partial_track_length );         
      }
    }
  }
}

// Determine which tet a given point is in
template<typename ContributionMultiplierPolicy>
moab::EntityHandle TetMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::whichTetIsPointIn(
	const double point[3] )
{
  // Iteration for looping over the leaves of a tree
  moab::AdaptiveKDTreeIter kd_tree_iteration;
  
  moab::ErrorCode return_value = d_kd_tree->point_search( point,
                                                          kd_tree_iteration );
                                                        
  
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS &&
		      return_value != moab::MB_ENTITY_NOT_FOUND,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );

  moab::EntityHandle tet_handle = 0;

  // The point is in the mesh
  if( return_value == moab::MB_SUCCESS )
  {
    moab::EntityHandle leaf = kd_tree_iteration.handle();
    moab::Range tets_in_leaf;
    
    return_value = d_moab_interface->get_entities_by_dimension( leaf,
								3,
								tets_in_leaf,
								false );
                                                              
    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			Utility::MOABException,
			moab::ErrorCodeStr[return_value] );     
    
    for( moab::Range::const_iterator tet = tets_in_leaf.begin(); 
                                           tet != tets_in_leaf.end();  tet++ )
    {
      if( Utility::isPointInTet( point,
				 d_tet_reference_vertices[*tet],
				 d_tet_barycentric_transform_matrices[*tet] ) )
	tet_handle = *tet;
    }
  }
  
  return tet_handle;
}

// Get all tet elements
template<typename ContributionMultiplierPolicy>
const moab::Range TetMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::getAllTetElements() const
{ 
  moab::Range all_tet_elements;
  
  moab::ErrorCode return_value = d_moab_interface->get_entities_by_dimension(
                                       d_tet_meshset, 3, all_tet_elements); 
                                       
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
                      
  return all_tet_elements;
}

// Export the estimator data
template<typename ContributionMultiplierPolicy>
void TetMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::exportData(
                                           EstimatorHDF5FileHandler& hdf5_file,
					                       const bool process_data ) const
{
  // Export data in FRENSIE formatting for data manipulation
  StandardEntityEstimator<moab::EntityHandle>::exportData( hdf5_file,
                                                           process_data );
        
  // Export data for visualization
  if( process_data )
  {
    moab::Range all_tet_elements;
    std::vector<moab::Tag> mean_tag( this->getNumberOfBins()*
                                     this->getNumberOfResponseFunctions()+
                                     this->getNumberOfResponseFunctions() ), 
                           relative_error_tag( mean_tag.size() );
    std::vector<moab::Tag> vov_tag( this->getNumberOfResponseFunctions() ), 
        fom_tag( vov_tag.size() );
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
      const double tet_volume = this->getEntityNormConstant( *tet );
      
      const Estimator::TwoEstimatorMomentsArray& tet_bin_data = 
	  this->getEntityBinData( *tet );
      
	  std::string mean_tag_prefix = "mean: ";
      std::string relative_error_tag_prefix = "relative_error: ";	
      std::string vov_tag_prefix = "vov: ";
      std::string fom_tag_prefix = "fom: ";

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
						       &(*tet),
						       1,
						       &mean );

	    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[return_value] );
        
        // Assign error tag data                    
	    return_value = d_moab_interface->tag_get_handle( 
				       relative_error_tag_name.c_str(),
				       1,
				       moab::MB_TYPE_DOUBLE,
				       relative_error_tag[i],
				       moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );

	    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			    Utility::MOABException,
			    moab::ErrorCodeStr[return_value] );

	    return_value = d_moab_interface->tag_set_data( relative_error_tag[i], 
						       &(*tet),
						       1,
						       &relative_error );

	    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[return_value] );
      }
      
      // Assign total bin data for each entity
      std::string total_tag_prefix = "total_";
      std::string total_mean_tag_name = total_tag_prefix + "mean";
      std::string total_relative_error_tag_name = total_tag_prefix +
                                                          "relative_error";
      std::string total_vov_tag_name = total_tag_prefix + "vov";
      std::string total_fom_tag_name = total_tag_prefix + "fom";
    
      const Estimator::FourEstimatorMomentsArray& total_tet_data = 
	  this->getEntityTotalData( *tet );
      
      for( unsigned i = 0; i != total_tet_data.size(); ++i )
      {
	    double mean, relative_error, vov, fom;
	
	    this->processMoments( total_tet_data[i],
			                  tet_volume,
			                  mean,
			                  relative_error,
			                  vov,
			                  fom); 
	
	    unsigned tag_index = this->getNumberOfBins() + i;
        
	    // Assign total mean tag data                    
	    moab::ErrorCode return_value = d_moab_interface->tag_get_handle( 
		                       total_mean_tag_name.c_str(),
				               1,
				               moab::MB_TYPE_DOUBLE,
				               mean_tag[tag_index],
				               moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );

	    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			        Utility::MOABException,
			        moab::ErrorCodeStr[return_value] );

	    return_value = d_moab_interface->tag_set_data( mean_tag[tag_index],
						       &(*tet),
						       1,
						       &mean );

	    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			        Utility::MOABException,
			        moab::ErrorCodeStr[return_value] );
	    
	    // Assign total relative error tag data                    
	    return_value = d_moab_interface->tag_get_handle( 
		                total_relative_error_tag_name.c_str(),
				        1,
				        moab::MB_TYPE_DOUBLE,
				        relative_error_tag[tag_index],
				        moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );

	    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			        Utility::MOABException,
			        moab::ErrorCodeStr[return_value] );
	
	    return_value = d_moab_interface->tag_set_data( 
						    relative_error_tag[tag_index],
						    &(*tet),
						    1,
						    &relative_error );

	    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			        Utility::MOABException,
			        moab::ErrorCodeStr[return_value] );
        
	    // Assign total vov tag data                    
	    return_value = d_moab_interface->tag_get_handle( 
				        total_vov_tag_name.c_str(),
				        1,
				        moab::MB_TYPE_DOUBLE,
				        vov_tag[i],
				        moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );

	    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			        Utility::MOABException,
			        moab::ErrorCodeStr[return_value] );
	
	    return_value = d_moab_interface->tag_set_data( vov_tag[i], 
						       &(*tet),
						       1,
						       &vov );

	    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			        Utility::MOABException,
			        moab::ErrorCodeStr[return_value] );
	    
	    // Assign total fom tag data                    
	    return_value = d_moab_interface->tag_get_handle( 
				       total_fom_tag_name.c_str(),
				       1,
				       moab::MB_TYPE_DOUBLE,
				       fom_tag[i],
				       moab::MB_TAG_DENSE|moab::MB_TAG_CREAT );

	    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			    Utility::MOABException,
			    moab::ErrorCodeStr[return_value] );

	    return_value = d_moab_interface->tag_set_data( fom_tag[i], 
						       &(*tet),
						       1,
						       &fom );

	    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			    Utility::MOABException,
			    moab::ErrorCodeStr[return_value] );      
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
                        
    return_value = d_moab_interface->write_file( d_output_mesh_name.c_str(),
                                                 NULL,
                                                 NULL,
                                                 &d_tet_meshset,
                                                 1,
                                                 &(output_tags[0]),
                                                 output_tags.size() );
       
    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			    Utility::MOABException,
			    moab::ErrorCodeStr[return_value] );                                               
  }   
}

// Print the estimator data
/*! \details Due to the large number of tets that are likely to be printed,
 * printing of data to the screen will not be done.
 */
template<typename ContributionMultiplierPolicy>
void TetMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::print( 
						       std::ostream& os ) const
{ /* ... */ }

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
  {
    StandardEntityEstimator<moab::EntityHandle>::assignBinBoundaries( 
							      bin_boundaries );
  }
}
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_TetMeshTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
