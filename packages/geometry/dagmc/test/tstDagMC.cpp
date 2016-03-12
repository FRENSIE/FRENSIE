//---------------------------------------------------------------------------//
//!
//! \file   tstDagMC.cpp
//! \author Alex Robinson
//! \brief  DagMC wrapper class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>
#include <map>
#include <set>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "Geometry_DagMC.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string test_dagmc_geom_file_name;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that DagMC can be initialized
TEUCHOS_UNIT_TEST( DagMC, initialize )
{
  
}

//---------------------------------------------------------------------------//
// Check if cells exist
TEUCHOS_UNIT_TEST( DagMC, doesCellExist )
{

}

//---------------------------------------------------------------------------//
// Check if surfaces exist
TEUCHOS_UNIT_TEST( DagMC, doesSurfaceExist )
{

}

//---------------------------------------------------------------------------//
// Check that the problem cells can be returned
TEUCHOS_UNIT_TEST( DagMC, getCells )
{

}

//---------------------------------------------------------------------------//
// Check that the problem surfaces can be returned
TEUCHOS_UNIT_TEST( DagMC, getSurfaces )
{

}

//---------------------------------------------------------------------------//
// Check that the cell volume can be returned
TEUCHOS_UNIT_TEST( DagMC, getCellVolume )
{

}

//---------------------------------------------------------------------------//
// Check that the surface area can be returned
TEUCHOS_UNIT_TEST( DagMC, getSurfaceArea )
{

}

//---------------------------------------------------------------------------//
// Check is cells are termination cells
TEUCHOS_UNIT_TEST( DagMC, isTerminationCell )
{

}

//---------------------------------------------------------------------------//
// Check if the cell is a void cell
TEUCHOS_UNIT_TEST( DagMC, isVoidCell )
{

}

//---------------------------------------------------------------------------//
// Check that the cell material ids can be returned
TEUCHOS_UNIT_TEST( DagMC, getCellMaterialIds )
{

}

//---------------------------------------------------------------------------//
// Check that the cell densities can be returned
TEUCHOS_UNIT_TEST( DagMC, getCellDensities )
{

}

//---------------------------------------------------------------------------//
// Check that the point location w.r.t. a given cell can be returned
TEUCHOS_UNIT_TEST( DagMC, getPointLocation )
{

}

//---------------------------------------------------------------------------//
// Check that the boundary cell can be found
TEUCHOS_UNIT_TEST( DagMC, getBoundaryCell )
{

}

//---------------------------------------------------------------------------//
// Check that the surface normal can be found
TEUCHOS_UNIT_TEST( DagMC, getSurfaceNormal )
{
  
}

//---------------------------------------------------------------------------//
// Check that the cell containing the external ray can be found
TEUCHOS_UNIT_TEST( DagMC, findCellContainingExternalRay )
{

}

//---------------------------------------------------------------------------//
// Check that the cell containing the external ray can be found and cached
TEUCHOS_UNIT_TEST( DagMC, findAndCacheCellContainingExternalRay )
{

}

//---------------------------------------------------------------------------//
// Check that an external ray can be fired
TEUCHOS_UNIT_TEST( DagMC, fireExternalRay_unknown_cell )
{

}

//---------------------------------------------------------------------------//
// Check that an external ray can be fired
TEUCHOS_UNIT_TEST( DagMC, fireExternalRay_known_cell )
{

}

//---------------------------------------------------------------------------//
// Check that an external ray track can be done
TEUCHOS_UNIT_TEST( DagMC, external_ray_trace )
{

}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
TEUCHOS_UNIT_TEST( DagMC, setInternalRay_unknown_cell )
{

}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
TEUCHOS_UNIT_TEST( DagMC, setInternalRay_known_cell )
{
  
}

//---------------------------------------------------------------------------//
// Check that the internal ray direction can be changed
TEUCHOS_UNIT_TEST( DagMC, changeInternalRayDirection )
{

}

//---------------------------------------------------------------------------//
// Check that the cell containing the internal ray can be found
TEUCHOS_UNIT_TEST( DagMC, findCellContainingInternalRay )
{

}

//---------------------------------------------------------------------------//
// Check that the internal ray can be fired
TEUCHOS_UNIT_TEST( DagMC, fireInternalRay )
{

}

//---------------------------------------------------------------------------//
// Check that an internal ray trace can be done
TEUCHOS_UNIT_TEST( DagMC, internal_ray_trace )
{

}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_cad_file",
                 &test_dagmc_geom_file_name,
		 "Test cad file name" );
  
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Set up the global OpenMP session
  if( Utility::GlobalOpenMPSession::isOpenMPUsed() )
    Utility::GlobalOpenMPSession::setNumberOfThreads( threads );

  // Initialize the global MPI session
  Teuchos::GlobalMPISession mpiSession( &argc, &argv );

  out->setProcRankAndSize( mpiSession.getRank(), mpiSession.getNProc() );
  out->setOutputToRootOnly( 0 );
  
  mpiSession.barrier();
  
  // Run the unit tests
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstDagMC.cpp
//---------------------------------------------------------------------------//
