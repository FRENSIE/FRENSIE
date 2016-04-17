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
    d_output_mesh_name( output_mesh_file_name )
{
        int N=10; int dim = 3;

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
  }
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_HexMeshTrackLengthFluxEstimator.hpp
//---------------------------------------------------------------------------//
