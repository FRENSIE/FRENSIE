//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TetMeshTrackLengthFluxEstimator.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Tet mesh flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

// Moab Includes
#include <moab/Core.hpp>
#include <moab/BoundBox.hpp>

// FRENSIE Includes
#include "MonteCarlo_HexMeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_HexahedronHelpers.hpp"
#include "Utility_MOABException.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace MonteCarlo{

// Initialize static member data
template<typename ContributionMultiplierPolicy>
const double 
HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::s_tol = 1e-6;

// Constructor
template<typename ContributionMultiplierPolicy>
HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::HexMeshTrackLengthFluxEstimator(
		                      const Estimator::idType id,
				      const double multiplier,
				      const std::string input_mesh_file_name,
		                      const std::string output_mesh_file_name )
  : StandardEntityEstimator<moab::EntityHandle>( id, multiplier ),
    d_moab_interface( new moab::Core ),
    d_hex_meshset(),
    d_kd_tree( new moab::AdaptiveKDTree( d_moab_interface.getRawPtr() ) ),
    d_kd_tree_root(),
    d_hex_face_normals(), 
    d_output_mesh_name( output_mesh_file_name )
{
  // Create empty MOAB meshset
  moab::EntityHandle d_hex_meshset;
  moab::ErrorCode return_value = d_moab_interface->create_meshset(
					moab::MESHSET_SET, d_hex_meshset);
  
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );

  // Populate MOAB meshset with data from input file
  std::cout << "Loading hexahedral mesh from file "
	    << input_mesh_file_name << " ... ";
  std::cout.flush();
  
  return_value = d_moab_interface->load_file(
                            input_mesh_file_name.c_str(), &d_hex_meshset);
                             
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );                
  
  // Range (domain) of all hexahedral elements
  moab::Range all_hex_elements;
  
  // Extract 3D elements from meshset
  return_value = d_moab_interface->get_entities_by_dimension(
                        d_hex_meshset, 3, all_hex_elements);
  
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
  
  // Clear the meshset                    
  return_value = d_moab_interface->clear_meshset(&d_hex_meshset, 1);
  
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
                      
  // Reconstruct the meshset using only 3D entitites                    
  return_value = d_moab_interface->add_entities(
                                         d_hex_meshset, all_hex_elements);
  
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
  
  unsigned int number_of_hexs = all_hex_elements.size();
  
  boost::unordered_map<moab::EntityHandle,double> entity_volumes;
  
  for( moab::Range::const_iterator hex = all_hex_elements.begin(); 
       hex != all_hex_elements.end(); 
       ++hex )
  {
    // Make sure the hex is valid
    TEST_FOR_EXCEPTION( *hex == 0,
			Utility::MOABException,
			moab::ErrorCodeStr[return_value] );
      
    // Extract the vertex data for the given hex
    std::vector<moab::EntityHandle> vertex_handles;
    moab::EntityHandle current_hex = *hex;
    d_moab_interface->get_connectivity( &current_hex, 1, vertex_handles );
    
    // Test that the vertex entity contains eight points
    TEST_FOR_EXCEPTION( vertex_handles.size() != 8,
			Utility::MOABException,
			"Error: hex found with incorrect number of vertices "
			"(" << vertex_handles.size() << " != 8)" );
     
    moab::CartVect vertices[8];
    
    for( unsigned j = 0; j != vertex_handles.size(); ++j )
    {
      d_moab_interface->get_coords( &vertex_handles[j], 
				    1, 
				    vertices[j].array() );
    }
    
    // Calculate hex cell's face's normal 
    Teuchos::TwoDArray<double>& hex_face_normals = d_hex_face_normals[*hex];
    
    Utility::calculateFaceNormals( vertices, hex_face_normals );
    
    // Calculate hex volumes
    entity_volumes[*hex] = Utility::calculateHexahedronVolume(vertices);
  }
  
  // Assign the entity volumes
  this->assignEntities( entity_volumes );
  
  int current_dimension;
  
  // Get dimension of the input set
  current_dimension = 
    d_moab_interface->dimension_from_handle(all_hex_elements[0]);
  
  moab::Range surface_quadrilaterals;
  
  // Determine the edges from the input set
  return_value = d_moab_interface->get_adjacencies( all_hex_elements, 
						    current_dimension - 1, 
						    true,
						    surface_quadrilaterals, 
						    moab::Interface::UNION );
                            
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
  
  all_hex_elements.merge( surface_quadrilaterals );
  
  const char settings[]="MESHSET_FLAGS=0x1;TAG_NAME=0";
  moab::FileOptions fileopts(settings);

  std::cout << "(constructed " << entity_volumes.size() 
	    << " hexahedrons) done." << std::endl;
    
  // Create the kd-tree
  std::cout << "Constructing kd-tree for hexahedral mesh from file "
	    << input_mesh_file_name << " ... ";
  std::cout.flush();
    
  d_kd_tree->build_tree(all_hex_elements, &d_kd_tree_root, &fileopts);

  std::cout << "done." << std::endl;
} 

// Set the response functions
template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::setResponseFunctions(
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions )
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

// Set the particle types that can contribute to the estimator
template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::setParticleTypes( const Teuchos::Array<ParticleType>& particle_types )
{
  Estimator::setParticleTypes( particle_types );
}

// Add current history estimator contribution
template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::updateFromGlobalParticleSubtrackEndingEvent( 
						 const ParticleState& particle,
						 const double start_point[3],
						 const double end_point[3] )
{
  if( this->isParticleTypeAssigned( particle.getParticleType() ) )
  {
    // Calculate the track length
    double track_length = sqrt(
                (end_point[0]-start_point[0])*(end_point[0]-start_point[0]) +
                (end_point[1]-start_point[1])*(end_point[1]-start_point[1]) +
                (end_point[2]-start_point[2])*(end_point[2]-start_point[2]) );

    std::vector<double> ray_hex_intersections;
    std::vector<moab::EntityHandle> hex_surface_quadrilaterals;
                           
    moab::ErrorCode return_value = 
       d_kd_tree->ray_intersect_triangles( d_kd_tree_root,
                                           s_tol,
                                           particle.getDirection(),
                                           start_point,
                                           hex_surface_triangles,
                                           ray_hex_intersections,
                                           0,
                                           track_length );

    // Clear the moab surface triangle entity handles - not used
    hex_surface_triangles.clear();
    
    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			Utility::MOABException,
			moab::ErrorCodeStr[return_value] );
    
    if( ray_hex_intersections.size() > 0 )
    {
      // Sort all intersections of the ray with the hexs
      std::sort( ray_hex_intersections.begin(),
		 ray_hex_intersections.end() );
  
      // Calculate the hex intersection points and partial track lengths
      std::vector<moab::CartVect> array_of_hit_points;
        
      // Add the origin point
      {
	moab::CartVect start_point_cv( start_point[0], 
				       start_point[1], 
				       start_point[2] );
	
	array_of_hit_points.push_back( start_point_cv );
      }
      
      for( unsigned i = 0; i < ray_hex_intersections.size(); ++i )
      {
	moab::CartVect hit_point;

	hit_point[0] = particle.getXDirection() * ray_hex_intersections[i]
	  + start_point[0];
	hit_point[1] = particle.getYDirection() * ray_hex_intersections[i]
	  + start_point[1];
	hit_point[2] = particle.getZDirection() * ray_hex_intersections[i]
	  + start_point[2];
	
	array_of_hit_points.push_back( hit_point );      
      }
      
      // Add the end point if it doesn't lie on an intersection point
      if( track_length > ray_hex_intersections.back() )
      {
	moab::CartVect end_point_cv(end_point[0], end_point[1], end_point[2]);
	
	array_of_hit_points.push_back( end_point_cv );
	
	ray_hex_intersections.push_back( track_length );
      }
      
      // Compute and add the partial history contribution to appropriate hex
      for( unsigned int i = 0; i < ray_hex_intersections.size(); ++i )
      {
	moab::CartVect hex_centroid = ( (array_of_hit_points[i+1] + 
					 array_of_hit_points[i])/2.0 );
      
	// Check that the centroid falls in the mesh - if the mesh
	// is concave its possible that it falls outside
	if( this->isPointInMesh( hex_centroid.array() ) )
	{
	  moab::EntityHandle hex = whichHexIsPointIn( hex_centroid.array() );
	
	  // Make sure a hex was found (tolerance issues may prevent this)
	  if( hex == 0 )
	    continue;
	  
	  double partial_track_length;
	  
	  if( i != 0)
	  { 
	    partial_track_length = ray_hex_intersections[i] - 
	      ray_hex_intersections[i-1];
	  }
	  else
	    partial_track_length = ray_hex_intersections[i];
	  
	  // Handle the special case where the first point is on a mesh surface
	  if( partial_track_length > 0.0 )
	  {	
	    // Add partial history contribution
	    addPartialHistoryContribution( hex,
					   particle,
					   0,
					   partial_track_length );
	  }
	}
      }
    }
    // Account for the cases where there are no intersections
    else
    {
      // case 1: track is entirely in one hex
      if( this->isPointInMesh( start_point ) )
      {
	moab::EntityHandle hex = whichHexIsPointIn( start_point );
      	
	// Add partial history contribution if hex was found (tolerance
	// issues may prevent this)
	if( hex != 0 )
	  addPartialHistoryContribution( hex, particle, 0, track_length );
      }
      // case 2: track entirely misses mesh - do nothing
    }
  }
}

// Test if a point is in the mesh
template<typename ContributionMultiplierPolicy>
bool 
HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::isPointInMesh( 
						        const double point[3] )
{
  bool point_in_mesh = false;

  // Find the leaf that the point is in (if there is one)
  moab::AdaptiveKDTreeIter kd_tree_iteration;
  
  moab::ErrorCode return_value = 
    d_kd_tree->point_search( point, kd_tree_iteration );

  // Check that the leaf actually contains the point (concave mesh)
  if( return_value == moab::MB_SUCCESS && kd_tree_iteration.handle() != 0 )
  {  
    moab::EntityHandle leaf_node = kd_tree_iteration.handle();

    moab::Range hexs_in_leaf;
    
    return_value = d_moab_interface->get_entities_by_dimension( leaf_node,
								3,
								hexs_in_leaf,
								false );
    
    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			Utility::MOABException,
			moab::ErrorCodeStr[return_value] );

    // Quickly check if the point is likely in one of the hexs
    for( moab::Range::const_iterator hex = hexs_in_leaf.begin();
	 hex != hexs_in_leaf.end();
	 ++hex )
    {
      if( Utility::isPointInHex( 
		  point,
		  d_hex_reference_vertices.find( *hex )->second,
		  d_hex_barycentric_transform_matrices.find( *hex )->second,
		  s_tol ) )
      {
	point_in_mesh = true;

	break;
      }
    }
  }
  // The point is outside the mesh bounding box
  else 
    point_in_mesh = false;
  
  return point_in_mesh;
}

// Determine which hex a given point is in
/*! \details This function should only be called after testing if the point
 * is in the mesh. If the point is in the mesh, it is still possible that
 * this function will not be able to find the correct hex due to numerical
 * precision. In that event the return value will be zero. It is therefore
 * important to test that the return value from this function is not zero
 * before using it. 
 */
template<typename ContributionMultiplierPolicy>
moab::EntityHandle HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::whichHexIsPointIn(
	                                                const double point[3] )
{
  // Make sure the point is in the mesh
  testPrecondition( this->isPointInMesh( point ) );
  
  // Find the kd-tree leaf that contains the point
  moab::AdaptiveKDTreeIter kd_tree_iterator;
  
  moab::ErrorCode return_value = d_kd_tree->point_search( point,
                                                          kd_tree_iterator );
                                                        
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );

  TEST_FOR_EXCEPTION( kd_tree_iterator.handle() == 0,
		      Utility::MOABException,
		      moab::ErrorCodeStr[return_value] );

  moab::EntityHandle leaf = kd_tree_iterator.handle();
  moab::Range hexs_in_leaf;
    
  return_value = d_moab_interface->get_entities_by_dimension( leaf,
							      3,
							      hexs_in_leaf,
							      false );
                                                              
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
		      Utility::MOABException,
		      moab::ErrorCodeStr[return_value] );     
    
  // A hex must be found since a leaf was found - failure to find a hex
  // indicates a tolerance issue usually
  moab::EntityHandle hex_handle = 0;
    
  for( moab::Range::const_iterator hex = hexs_in_leaf.begin(); 
       hex != hexs_in_leaf.end();  
       ++hex )
  {
    if( Utility::isPointInHex( 
		  point,
		  d_hex_reference_vertices.find( *hex )->second,
		  d_hex_barycentric_transform_matrices.find( *hex )->second,
		  s_tol ) )
    {
      hex_handle = *hex;
      
      break;
    }
  }
    
  // Make sure the hex has been found
  if( hex_handle == 0 && SimulationGeneralProperties::displayWarnings() )
  {
    #pragma omp critical( point_in_hex_warning_message )
    {
      std::cerr << "Warning: the hexahedron containing point {"
		<< point[0] << "," << point[1] << "," << point[2]
		<< "} could not be found (" << hexs_in_leaf.size()
		<< " hexs in leaf)!." << std::endl;
    }
  }
  
  // Make sure the leaf is valid
  testPostcondition( hexs_in_leaf.size() > 0 );
		      
  return hex_handle;
}

// Get all hex elements
template<typename ContributionMultiplierPolicy>
const moab::Range HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::getAllHexElements() const
{ 
  moab::Range all_hex_elements;
  
  moab::ErrorCode return_value = d_moab_interface->get_entities_by_dimension(
                                       d_hex_meshset, 3, all_hex_elements); 
                                       
  TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[return_value] );
                      
  return all_hex_elements;
}

// Export the estimator data
template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::exportData(
                                           EstimatorHDF5FileHandler& hdf5_file,
					                       const bool process_data ) const
{
  // Export data in FRENSIE formatting for data manipulation
  StandardEntityEstimator<moab::EntityHandle>::exportData( hdf5_file,
                                                           process_data );
        
  // Export data for visualization
  if( process_data )
  {
    moab::Range all_hex_elements;
    std::vector<moab::Tag> mean_tag( this->getNumberOfBins()*
                                     this->getNumberOfResponseFunctions()+
                                     this->getNumberOfResponseFunctions() ), 
                           relative_error_tag( mean_tag.size() );
    std::vector<moab::Tag> vov_tag( this->getNumberOfResponseFunctions() ), 
        fom_tag( vov_tag.size() );
    moab::ErrorCode return_value = d_moab_interface->get_entities_by_dimension(
                                       d_hex_meshset, 3, all_hex_elements);
                                       
    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                        Utility::MOABException,
                        moab::ErrorCodeStr[return_value] );
    
    // Process moments
    for ( moab::Range::const_iterator hex = all_hex_elements.begin(); 
	  hex != all_hex_elements.end(); 
	  ++hex )
    {
      const double hex_volume = this->getEntityNormConstant( *hex );
      
      const Estimator::TwoEstimatorMomentsArray& hex_bin_data = 
	  this->getEntityBinData( *hex );
      
	  std::string mean_tag_prefix = "mean: ";
      std::string relative_error_tag_prefix = "relative_error: ";	
      std::string vov_tag_prefix = "vov: ";
      std::string fom_tag_prefix = "fom: ";

      for( unsigned i = 0; i < hex_bin_data.size(); ++i )
      {
    	double mean, relative_error;
	
    	this->processMoments( hex_bin_data[i],
            			      hex_volume,
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
						       &(*hex),
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
						       &(*hex),
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
    
      const Estimator::FourEstimatorMomentsArray& total_hex_data = 
	  this->getEntityTotalData( *hex );
      
      for( unsigned i = 0; i != total_hex_data.size(); ++i )
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
						       &(*hex),
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
						    &(*hex),
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
						       &(*hex),
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
						       &(*hex),
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
                                                 &d_hex_meshset,
                                                 1,
                                                 &(output_tags[0]),
                                                 output_tags.size() );
       
    TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
			    Utility::MOABException,
			    moab::ErrorCodeStr[return_value] );                                               
  }   
}

// Print the estimator data
/*! \details Due to the large number of hexs that are likely to be printed,
 * printing of data to the screen will not be done.
 */
template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::print( 
						       std::ostream& os ) const
{ /* ... */ }

// Assign bin boundaries to an estimator dimension
template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::assignBinBoundaries(
	const Teuchos::RCP<EstimatorDimensionDiscretization>& bin_boundaries )
{
  if( bin_boundaries->getDimension() == COSINE_DIMENSION )
  {
    std::cerr << "Warning: " << bin_boundaries->getDimensionName()
    	      << " bins cannot be set for standard cell estimators. The bins "
     	      << "requested for hexahdedral mesh flux estimator " << this->getId()
    	      << " will be ignored."
    	      << std::endl;
  }
  else if( bin_boundaries->getDimension() == TIME_DIMENSION )
  {
    std::cerr << "Warning: " << bin_boundaries->getDimensionName()
    	      << " bins cannot be set for standard cell estimators. The bins "
     	      << "requested for hexahdedral mesh flux estimator " << this->getId()
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
// end MonteCarlo_HexMeshTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
