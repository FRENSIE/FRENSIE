//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TetMeshTrackLengthFluxEstimator.cpp
//! \author Luke Kersting, Philip Britt
//! \brief  Tet mesh flux estimator class declaration.
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

        d_moab_interface->create_vertices(&coordinates[0],
                                          coordinates.size()/3,
                                          vertices );
        TEST_FOR_EXCEPTION( return_value != moab::MB_SUCCESS,
                            Utility::MOABException,
                            moab::ErrorCodeStr[return_value]) ;

                

}

template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::setParticleTypes( 
                const Teuchos::Array<ParticleType>& particle_types )
{

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

}

template<typename ContributionMultiplierPolicy>
void HexMeshTrackLengthFluxEstimator<ContributionMultiplierPolicy>::exportData(
                    const std::shared_ptr<Utility::HDF5FileHandler>& hdf5_file,
                    const bool process_data ) const

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
