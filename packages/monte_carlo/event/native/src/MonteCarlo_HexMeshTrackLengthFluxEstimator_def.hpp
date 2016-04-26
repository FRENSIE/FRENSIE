//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_HexMeshTrackLengthFluxEstimator.cpp
//! \author Luke Kersting, Philip Britt
//! \brief  hex mesh flux estimator class declaration.
//!
//---------------------------------------------------------------------------//

// Moab Includes
#include <moab/Core.hpp>
//#include <moab/BoundBox.hpp>
#include <moab/ScdInterface.hpp>
#include <moab/ProgOptions.hpp>


// FRENSIE Includes
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
    d_output_mesh_name( output_mesh_file_name )
{
/*        int N=10; int dim = 3;

        Interface *mb = new Core();
        ScdInterface *scdiface;
        ErrorCode rval = mb->query_interface(scdiface);
        if(MB_SUCCESS != rval) return rval;

        int ilow = 0, ihigh = N

        ScdBox *box;
        rval = scdiface->construct_box(HomCoord(0, 0, 0)
                                       HomCoord(N, N, N)
                                       NULL,
                                       0,
                                       box);
        if(MB_SUCCESS != rval) return rval.

        Teuchos::Array<double> coords(3*pow(N+1,dim));
        Teuchos::Array<EntityHandle> connect;
  for (int k = 0; k < (dim>2?N:1); k++) {
    for (int j = 0; j < (dim>1?N:1); j++) {
      for (int i = 0; i < N-1; i++) {
          // 4a. Get the element corresponding to (i,j,k)
        EntityHandle ehandle = box->get_element(i, j, k);
        if (0 == ehandle) return MB_FAILURE;
          // 4b. Get the connectivity of the element
        rval = mb->get_connectivity(&ehandle, 1, connect); // get the connectivity, in canonical order
        if (MB_SUCCESS != rval) return rval;
          // 4c. Get the coordinates of the vertices comprising that element
        rval = mb->get_coords(connect.data(), connect.size(), coords.data()); // get the coordinates of those vertices
        if (MB_SUCCESS != rval) return rval;
      }
    }
  }*/
}
template<typename ContributionMultiplierPolicy>
HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::HexMeshTrackLengthFluxEstimator(
		     const Estimator::idType id,
		     const double multiplier,
		     const Teuchos::Array<double>& x_grid_points,
                     const Teuchos::Array<double>& y_grid_points,
                     const Teuchos::Array<double>& z_grid_points,
		     const std::string output_mesh_file_name
                     : d_moab_interface( new moab::Core ) )

{
//Test for 2 dimension grid points - input logical statement into precondition. Will tell coder what precondition failed when being used
        testPrecondition(x_grid_points.size()>=2);
        testPrecondition(y_grid_points.size()>=2);
        testPrecondition(z_grid_points.size()>=2);
        //check filename size > 0 (valid output name)
        testPrecondition(output_mesh_file_name.size()>0);

        Teuchos::Array<double> coordinates;
        
        //form coordinate array in MOAB readable format
        for(Teuchos::Array<double>::iterator i = x_grid_points.begin(); i!= x_grid_points.end(); i++) {
               for(Teuchos::Array<double>::iterator j = y_grid_points.begin(); j!= y_grid_points.end(); j++) {
                      for(Teuchos::Array<double>::iterator k = z_grid_points.begin(); k!= z_grid_points.end(); k++) {
        
                              coordinates.push_back(*i);
                              coordinates.push_back(*j);
                              coordinates.push_back(*k);
                        }
                }
        }
        
        moab::ScdInterface *scdiface;
        ErrorCode rval = d_moab_interface->query_interface(scdiface);
        if(moab::MB_SUCCESS!=rval) return rval;

        MOAB::ScdBox *box;

        rval = scdiface->construct_box(moab::homcoord(x_grid_points[0], y_grid_points[0], z_grid_points[0]),
                                       moab::homcoord(x_grid_points.back(), y_grid_points.back(), z_grid_points.back())
                                       coordinates, coordinates.size()
                                       box);
        if(moab::MB_SUCCESS!=rval) return rval;
        d_moab_interface -> release_interface(scdiface)  

        /*std::vector<Moab::EntityHandle> connect;
        vector<double::size_type x_dim=x_grid_points.size()
                                 y_dim=y_grid_points.size()
                                 z_dim=z_grid_points.size()
        for(unsigned k = 0; k < z_dim; ++k) {
                for(unsigned j = 0; k < y_dim; ++j) {
                        for(unsigned i = 0; i < x_dim; ++k) {
                                
                                Moab::EntityHandle ehandle = box->get_element(i,j,k);
                                if(ehandle == 0) return moab::MB_FAILURE;
                                rval = d_moab_interface->get_connectivity(&ehandle, 1, connect);
                                if(MOAB::MB_SUCCESS != rval) return rval;
                        }
                }
        }*/
        d_moab_interface->release_interface(scdiface);
        delete d_moab_interface;                        

}

template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::setParticleTypes( 
                const Teuchos::Array<ParticleType>& particle_types )
{
          Estimator::setParticleTypes( particle_types );
}

template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::setResponseFunction(
                Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions)
{

}

template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::updateFromGlobalParticleSubtrackEndingEvent(
                const particleState& particle,
                const double start_point[3],
                const double end_point[3])
{

}

template<typename ContributionMultiplierPolicy>
bool HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::isPointInMesh( 
						        const double point[3] )
{

}

template<typename ContributionMultiplierPolicy>
moab::EntityHandle HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::whichHexIsPointIn(
	                                                const double point[3] )
{

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
// end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HexMeshTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
