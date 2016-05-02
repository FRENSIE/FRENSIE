//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HexMeshTrackLengthFluxEstimator.cpp
//! \author Luke Kersting, Philip Britt
//! \brief  hex mesh flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

// Moab Includes
#include <moab/Core.hpp>
#include <moab/BoundBox.hpp>
#include <moab/ProgOptions.hpp>


// FRENSIE Includes
#include "MonteCarlo_HexMeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_Tuple.hpp"
#include "Utility_HexahedronHelpers.hpp"
#include "Utility_MOABException.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DirectionHelpers.hpp"

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
    //d_moab_box_tree_tool(new moab::OrientedBoxTreeTool(d_moab_interface.get())),
    //d_box_root_set(),
    d_output_mesh_name( output_mesh_file_name )

{

}
template<typename ContributionMultiplierPolicy>
HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::HexMeshTrackLengthFluxEstimator(
		     const Estimator::idType id,
		     const double multiplier,
		     const Teuchos::Array<double>& x_grid_points,
                     const Teuchos::Array<double>& y_grid_points,
                     const Teuchos::Array<double>& z_grid_points,
		     const std::string output_mesh_file_name)
                     : StandardEntityEstimator<moab::EntityHandle>( id, multiplier ),
                       d_moab_interface( new moab::Core ),
                       d_hex_meshset(),
                       d_kd_tree( new moab::AdaptiveKDTree( d_moab_interface.get() ) ),
                       d_kd_tree_root(),
                       d_output_mesh_name(output_mesh_file_name)

{
//Test for 2 dimension grid points - input logical statement into precondition. Will tell coder what precondition failed when being used
        testPrecondition(x_grid_points.size()>=2);
        testPrecondition(y_grid_points.size()>=2);
        testPrecondition(z_grid_points.size()>=2);
        //check filename size > 0 (valid output name)
        testPrecondition(output_mesh_file_name.size()>0);
        
        Teuchos::Array<double> coordinates;

        //form coordinate array in MOAB readable format
        for(Teuchos::Array<double>::const_iterator k = z_grid_points.begin(); k!= z_grid_points.end(); k++) {
               for(Teuchos::Array<double>::const_iterator j = y_grid_points.begin(); j!= y_grid_points.end(); j++) {
                      for(Teuchos::Array<double>::const_iterator i = x_grid_points.begin(); i!= x_grid_points.end(); i++) {
        
                              coordinates.push_back(*i);
                              coordinates.push_back(*j);
                              coordinates.push_back(*k);
                        }
                }
        }
        
        unsigned tag_creation_flag=moab::MB_TAG_DENSE|moab::MB_TAG_CREAT|
                moab::MB_TAG_EXCL|moab::MB_TAG_BYTES;

        moab::Range vertices;
        
        moab::ErrorCode err = d_moab_interface->create_vertices(&coordinates[0],
                                                              coordinates.size()/3,
                                                              vertices);

        TEST_FOR_EXCEPTION( err!=moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[err]);
        moab::Range hexahedrons;
        moab::EntityHandle connections[8];
                          
        Teuchos::Array<double>::size_type i, x_dim=x_grid_points.size()-1;
        Teuchos::Array<double>::size_type j, y_dim=y_grid_points.size()-1;
        Teuchos::Array<double>::size_type k, z_dim=z_grid_points.size()-1;

        boost::unordered_map<moab::EntityHandle,double> entity_volumes;
        for( k=0; k != z_dim; ++k) {
                for( j=0; j != y_dim; ++j) {
                        for( i=0; i != x_dim; ++i) {
                                unsigned index = i + j*(x_dim+1)+k*(x_dim+1)*(y_dim+1);
                                
                                connections[0] = vertices[index];
                                connections[1] = vertices[index+1];
                                connections[2] = vertices[index+(x_dim+1)+1];
                                connections[3] = vertices[index+(x_dim+1)];
                                connections[4] = vertices[index+(x_dim+1)*(y_dim+1)];
                                connections[5] = vertices[index+(x_dim+1)*(y_dim+1)+1];
                                connections[6] = vertices[index+(x_dim+1)*(y_dim+1)+(x_dim+1)+1];
                                connections[7] = vertices[index+(x_dim+1)*(y_dim+1)+(x_dim+1)];

                                moab::EntityHandle hex;
                                err = d_moab_interface->create_element(moab::MBHEX,
                                                                       connections,
                                                                       8,
                                                                       hex );

                                TEST_FOR_EXCEPTION( err != moab::MB_SUCCESS,
                                                    Utility::MOABException,
                                                    moab::ErrorCodeStr[err]);
                             

                                hexahedrons.insert(hex);

                                double dx = x_grid_points[i+1]-x_grid_points[i];
                                double dy = y_grid_points[i+1]-y_grid_points[i];
                                double dz = z_grid_points[i+1]-z_grid_points[i];

                                double hexahedron_volume=dx*dy*dz;

                                entity_volumes[hex] = hexahedron_volume;




                        }
                }
        }

        // Create empty MOAB meshset
        err = d_moab_interface->create_meshset(
					moab::MESHSET_SET, d_hex_meshset);
  
        TEST_FOR_EXCEPTION( err != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[err] );
        //add elements to mesh set
        err = d_moab_interface->add_entities(d_hex_meshset, hexahedrons);
        TEST_FOR_EXCEPTION( err!=moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[err]);       

        // Assign the entity volumes
        this->assignEntities( entity_volumes );

        //get hex faces
        int current_dimension = d_moab_interface->dimension_from_handle(hexahedrons[0]);
        moab::Range surface_quads;
        std::cout<<current_dimension<<std::endl;
        err = d_moab_interface->get_adjacencies(hexahedrons,
                                                current_dimension-1,
                                                true,
                                                surface_quads,
                                                moab::Interface::UNION);


        TEST_FOR_EXCEPTION( err != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[err]);
        
        //split quads into triangles

        moab::Range surface_tris;

        for(moab::Range::iterator quad_it=surface_quads.begin();
            quad_it != surface_quads.end();
            ++quad_it)

        {

                const moab::EntityHandle* connectivity;
                int conn_size;

                err = d_moab_interface->get_connectivity(*quad_it,
                                                         connectivity,
                                                         conn_size);

                TEST_FOR_EXCEPTION( err != moab::MB_SUCCESS,
                                    Utility::MOABException,
                                    moab::ErrorCodeStr[err]);
                //get vertices of quad elements
                moab::CartVect quad_vertices[4];
                err = d_moab_interface->get_coords( connectivity,
                                                    conn_size,
                                                    (double*) &quad_vertices[0]);

                TEST_FOR_EXCEPTION( err != moab::MB_SUCCESS,
                                    Utility::MOABException,
                                    moab::ErrorCodeStr[err]);

                moab::EntityHandle new_tri_a[3] = {connectivity[0],
                                             connectivity[1],
                                             connectivity[2]};

                moab::EntityHandle new_tri_b[3] = {connectivity[0],
                                             connectivity[2],
                                             connectivity[3]};

                bool valid_orientation = 
                        (quad_vertices[2] - quad_vertices[0]).length_squared()
                        < (quad_vertices[3] - quad_vertices[1]).length_squared();

                if(!valid_orientation) {

                        new_tri_a[2]=connectivity[3];
                        new_tri_b[0]=connectivity[1];

                }

                moab::EntityHandle new_tri_handle;

                err = d_moab_interface->create_element(moab::MBTRI,
                                                       new_tri_a,
                                                       3,
                                                       new_tri_handle);

                TEST_FOR_EXCEPTION( err != moab::MB_SUCCESS,
                                    Utility::MOABException,
                                    moab::ErrorCodeStr[err]);

                surface_tris.insert(new_tri_handle);

                err = d_moab_interface->create_element(moab::MBTRI,
                                                       new_tri_b,
                                                       3,
                                                       new_tri_handle);

                TEST_FOR_EXCEPTION( err != moab::MB_SUCCESS,
                                    Utility::MOABException,
                                    moab::ErrorCodeStr[err]);

                surface_tris.insert(new_tri_handle);

        }

        hexahedrons.merge(surface_tris);
        d_kd_tree->build_tree(hexahedrons, &d_kd_tree_root);
        
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
        moab::ErrorCode err;



        if( this->isParticleTypeAssigned( particle.getParticleType() ) )
        {        
                //use function in moab to determine whether or not the ray in between the two points intersects one of the faces of the mesh

        double track_length = sqrt(
                (end_point[0]-start_point[0])*(end_point[0]-start_point[0]) +
                (end_point[1]-start_point[1])*(end_point[1]-start_point[1]) +
                (end_point[2]-start_point[2])*(end_point[2]-start_point[2]) );



                std::vector<double> ray_hex_intersections;
                std::vector<moab::EntityHandle> hex_surface_triangles;

                err = d_kd_tree->ray_intersect_triangles( d_kd_tree_root,
                                                                          s_tol,
                                                                          particle.getDirection(),
                                                                          start_point,
                                                                          hex_surface_triangles,
                                                                          ray_hex_intersections,
                                                                          0,
                                                                          track_length);

                TEST_FOR_EXCEPTION( err != moab::MB_SUCCESS,
                                    Utility::MOABException,
			            moab::ErrorCodeStr[err] );
                hex_surface_triangles.clear();
        
                if(ray_hex_intersections.size() > 0)
                {
                        std::sort(ray_hex_intersections.begin(),
                                  ray_hex_intersections.end());

                        Teuchos::Array<moab::CartVect> array_of_hit_points;

                        {
                        //check if first point is inside mesh
                                if(this->isPointInMesh(start_point))
                                {
                                        moab::CartVect start_point_cv( start_point[0],
                                                                       start_point[1],
                                                                       start_point[2] );
                                                                       array_of_hit_points.push_back(start_point_cv);
                                        
                                }
  

                        }

                        for(unsigned i = 0; i < ray_hex_intersections.size(); ++i)
                        {

                                moab::CartVect hit_point;
                                
                                hit_point[0] = particle.getXDirection() * ray_hex_intersections[i] + start_point[0];
                                hit_point[1] = particle.getYDirection() * ray_hex_intersections[i] + start_point[1];
                                hit_point[2] = particle.getZDirection() * ray_hex_intersections[i] + start_point[2];

                                array_of_hit_points.push_back(hit_point);
                        }
                        //test if last point is inside mesh or outside
                        if(track_length > ray_hex_intersections.back() )
                        {

                                moab::CartVect end_point_cv(end_point[0], end_point[1], end_point[2]);
                                array_of_hit_points.push_back(end_point_cv);
                                ray_hex_intersections.push_back(track_length);
                        }
                        
                        //cycle through hit points and figure out which hex to bin the track length in
                        for( unsigned int i = 0; i < ray_hex_intersections.size(); ++i)
                        {
                        	moab::CartVect hex_centroid = ( (array_of_hit_points[i+1] + 
					 array_of_hit_points[i])/2.0 );


                                

                                moab::EntityHandle hex = whichHexIsPointIn( hex_centroid.array() );
                                


                                // leave loop if it isn't inside a hex. Shouldn't ever happen at this point
                                if( hex == 0 )continue;
                                //compute track length for that individual hex cell
                                double partial_track_length;
                                if( i != 0)
	                        { 
	                                partial_track_length = ray_hex_intersections[i] - 
	                                                       ray_hex_intersections[i-1];
	                        }
                                //might not be right - check later. Got from tetmesh.
                                else partial_track_length = ray_hex_intersections[i];

                                //Special case - first point is on mesh surface
	                        if( partial_track_length > 0.0 )
	                        {                     	
                                        EstimatorParticleStateWrapper particle_state_wrapper( particle );
            
	                                // Add partial history contribution
	                                addPartialHistoryContribution( hex,
					                               particle_state_wrapper,
					                               partial_track_length );
	                        }
                                
                       }
                }

                else
                {
                        // case 1: track is entirely in one hex
                        if(this->isPointInMesh(start_point));
                        {
                                moab::EntityHandle hex = whichHexIsPointIn( start_point );

                                        
      	
	                                // Add partial history contribution if hex was found (tolerance
	                                // issues may prevent this)
	                        if( hex != 0 )
                                {
                                        EstimatorParticleStateWrapper particle_state_wrapper( particle );
          
	                                addPartialHistoryContribution( hex, 
                                                                       particle_state_wrapper, 
                                                                      track_length );
                                }
                        // case 2: track entirely misses mesh - do nothing
                        }
                }
                        
        }

}

template<typename ContributionMultiplierPolicy>
bool HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::isPointInMesh( 
						        const double point[3] )
{

        std::vector<double> coordinates;

        moab::ErrorCode err = d_moab_interface->get_vertex_coordinates(coordinates);

        std::vector<double>::size_type coord_size=coordinates.size();

        double x_low=coordinates[1];
        double x_high=coordinates[coord_size/3];
        double y_low=coordinates[1+(coord_size/3)];
        double y_high=coordinates[2*coord_size/3];
        double z_low=coordinates[(2*coord_size/3)+1];
        double z_high=coordinates[coord_size];

        std::cout<< x_low << ", " << y_low << ", " << z_low << std::endl;
        std::cout<< x_high << ", " << y_high << ", " << z_high << std::endl;
        

        if(point[0] > x_low && point[1] > y_low && point[2] > z_low)
        {
                if(point[0] < x_high && point[1] < y_high && point[2] < z_high)
                {
                        return true;
                }
        }

        return false;

}

template<typename ContributionMultiplierPolicy>
moab::EntityHandle HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::whichHexIsPointIn(
	                                                const double point[3] )
{
        moab::EntityHandle leaf;
        moab::ErrorCode err = d_kd_tree->point_search(point, leaf);
        TEST_FOR_EXCEPTION( err != moab::MB_SUCCESS,
                      Utility::MOABException,
                      moab::ErrorCodeStr[err] );
        TEST_FOR_EXCEPTION(leaf == 0,
		      Utility::MOABException,
		      moab::ErrorCodeStr[err] );
        moab::Range hexes_in_leaf;

        err = d_moab_interface->get_entities_by_dimension( leaf,
							      3,
							      hexes_in_leaf,
							      false );
        TEST_FOR_EXCEPTION( err != moab::MB_SUCCESS,
		      Utility::MOABException,
		      moab::ErrorCodeStr[err] );
        moab::EntityHandle hex_answer=0;

       for( moab::Range::const_iterator hex = hexes_in_leaf.begin(); hex != hexes_in_leaf.end();  ++hex )
       {
                moab::BoundBox hex_box;

                err = hex_box.update(*d_moab_interface, *hex);
                TEST_FOR_EXCEPTION( err != moab::MB_SUCCESS,
		                    Utility::MOABException,
		                    moab::ErrorCodeStr[err] );
                if(hex_box.contains_point(point, s_tol))
                {
                        hex_answer = *hex;
                        break;
                }
            
       }
       if( hex_answer == 0 && SimulationGeneralProperties::displayWarnings() )
       {
               #pragma omp critical( point_in_tet_warning_message )
               {
                        std::cerr << "Warning: the tetrahedron containing point {"
		        << point[0] << "," << point[1] << "," << point[2]
		        << "} could not be found (" << hexes_in_leaf.size()
		        << " tets in leaf)!." << std::endl;
               }
       }
        //test if size of leaf is valid
       testPostcondition( hexes_in_leaf.size() > 0 );
       return hex_answer;    
    
        
}

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

template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::exportData(
                    const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                    const bool process_data ) const
{
          // Export data in FRENSIE formatting for data manipulation
  StandardEntityEstimator<moab::EntityHandle>::exportData( hdf5_file,
                                                           process_data );

  // Set the estimator as a mesh estimator
  EstimatorHDF5FileHandler estimator_hdf5_file( hdf5_file );
  
  estimator_hdf5_file.setMeshEstimator( this->getId() );
        
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

template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::printSummary( 
						       std::ostream& os ) const
{

}

template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::assignBinBoundaries(
	const Teuchos::RCP<EstimatorDimensionDiscretization>& bin_boundaries )
{

}

}// end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HexMeshTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
