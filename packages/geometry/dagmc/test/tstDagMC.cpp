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
#include <Teuchos_Tuple.hpp>

// FRENSIE Includes
#include "Geometry_DagMC.hpp"
#include "Utility_Tuple.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//
std::string test_dagmc_geom_file_name;

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check the default property names
TEUCHOS_UNIT_TEST( DagMC, default_property_names )
{
  std::string default_property = 
    Geometry::DagMC::getTerminationCellPropertyName();

  TEST_EQUALITY_CONST( default_property, "termination.cell" );

  default_property = 
    Geometry::DagMC::getReflectingSurfacePropertyName();

  TEST_EQUALITY_CONST( default_property, "reflecting.surface" );

  default_property = 
    Geometry::DagMC::getMaterialPropertyName();

  TEST_EQUALITY_CONST( default_property, "material" );

  default_property = 
    Geometry::DagMC::getDensityPropertyName();

  TEST_EQUALITY_CONST( default_property, "density" );

  default_property = 
    Geometry::DagMC::getEstimatorPropertyName();

  TEST_EQUALITY_CONST( default_property, "estimator" );

  std::string default_estimator_name = 
    Geometry::DagMC::getSurfaceCurrentName();

  TEST_EQUALITY_CONST( default_estimator_name, "surface.current" );

  default_estimator_name = 
    Geometry::DagMC::getSurfaceFluxName();

  TEST_EQUALITY_CONST( default_estimator_name, "surface.flux" );

  default_estimator_name = 
    Geometry::DagMC::getCellPulseHeightName();

  TEST_EQUALITY_CONST( default_estimator_name, "cell.pulse.height" );

  default_estimator_name = 
    Geometry::DagMC::getCellTrackLengthFluxName();

  TEST_EQUALITY_CONST( default_estimator_name, "cell.tl.flux" );

  default_estimator_name = 
    Geometry::DagMC::getCellCollisionFluxName();

  TEST_EQUALITY_CONST( default_estimator_name, "cell.c.flux" );
}

//---------------------------------------------------------------------------//
// Check that the termination cell property name can be set
TEUCHOS_UNIT_TEST( DagMC, setTerminationCellPropertyName )
{
  std::string default_property = 
    Geometry::DagMC::getTerminationCellPropertyName();

  Geometry::DagMC::setTerminationCellPropertyName( "graveyard" );

  std::string new_property = 
    Geometry::DagMC::getTerminationCellPropertyName();

  TEST_EQUALITY_CONST( new_property, "graveyard" );

  Geometry::DagMC::setTerminationCellPropertyName( default_property );
}

//---------------------------------------------------------------------------//
// Check that the reflecting surface property name can be set
TEUCHOS_UNIT_TEST( DagMC, setReflectingSurfacePropertyName )
{
  std::string default_property = 
    Geometry::DagMC::getReflectingSurfacePropertyName();

  Geometry::DagMC::setReflectingSurfacePropertyName( "spec.reflect" );

  std::string new_property = 
    Geometry::DagMC::getReflectingSurfacePropertyName();

  TEST_EQUALITY_CONST( new_property, "spec.reflect" );

  Geometry::DagMC::setReflectingSurfacePropertyName( default_property );
}

//---------------------------------------------------------------------------//
// Check that the material property name can be set
TEUCHOS_UNIT_TEST( DagMC, setMaterialPropertyName )
{
  std::string default_property = 
    Geometry::DagMC::getMaterialPropertyName();

  Geometry::DagMC::setMaterialPropertyName( "mat" );

  std::string new_property = 
    Geometry::DagMC::getMaterialPropertyName();

  TEST_EQUALITY_CONST( new_property, "mat" );

  Geometry::DagMC::setMaterialPropertyName( default_property );
}

//---------------------------------------------------------------------------//
// Check that the density property name can be set
TEUCHOS_UNIT_TEST( DagMC, setDensityPropertyName )
{
  std::string default_property = 
    Geometry::DagMC::getDensityPropertyName();

  Geometry::DagMC::setDensityPropertyName( "rho" );

  std::string new_property = 
    Geometry::DagMC::getDensityPropertyName();

  TEST_EQUALITY_CONST( new_property, "rho" );

  Geometry::DagMC::setDensityPropertyName( default_property );
}

//---------------------------------------------------------------------------//
// Check that the estimator property name can be set
TEUCHOS_UNIT_TEST( DagMC, setEstimatorPropertyName )
{
  std::string default_property = 
    Geometry::DagMC::getEstimatorPropertyName();

  Geometry::DagMC::setEstimatorPropertyName( "tally" );

  std::string new_property = 
    Geometry::DagMC::getEstimatorPropertyName();

  TEST_EQUALITY_CONST( new_property, "tally" );

  Geometry::DagMC::setEstimatorPropertyName( default_property );
}

//---------------------------------------------------------------------------//
// Check that the surface current name can be set
TEUCHOS_UNIT_TEST( DagMC, setSurfaceCurrentName )
{
  std::string default_estimator_name = 
    Geometry::DagMC::getSurfaceCurrentName();

  Geometry::DagMC::setSurfaceCurrentName( "surf.cur" );

  std::string estimator_name = 
    Geometry::DagMC::getSurfaceCurrentName();

  TEST_EQUALITY_CONST( estimator_name, "surf.cur" );

  Geometry::DagMC::setSurfaceCurrentName( default_estimator_name );
}

//---------------------------------------------------------------------------//
// Check that the surface flux name can be set
TEUCHOS_UNIT_TEST( DagMC, setSurfaceFluxName )
{
  std::string default_estimator_name = 
    Geometry::DagMC::getSurfaceFluxName();

  Geometry::DagMC::setSurfaceFluxName( "surf.flux" );

  std::string estimator_name = 
    Geometry::DagMC::getSurfaceFluxName();

  TEST_EQUALITY_CONST( estimator_name, "surf.flux" );

  Geometry::DagMC::setSurfaceFluxName( default_estimator_name );
}

//---------------------------------------------------------------------------//
// Check that the cell pulse height name can be set
TEUCHOS_UNIT_TEST( DagMC, setCellPulseHeightName )
{
  std::string default_estimator_name = 
    Geometry::DagMC::getCellPulseHeightName();

  Geometry::DagMC::setCellPulseHeightName( "cell.ph" );

  std::string estimator_name = 
    Geometry::DagMC::getCellPulseHeightName();

  TEST_EQUALITY_CONST( estimator_name, "cell.ph" );

  Geometry::DagMC::setCellPulseHeightName( default_estimator_name );
}

//---------------------------------------------------------------------------//
// Check that the cell track-length flux name can be set
TEUCHOS_UNIT_TEST( DagMC, setCellTrackLengthFluxName )
{
  std::string default_estimator_name = 
    Geometry::DagMC::getCellTrackLengthFluxName();

  Geometry::DagMC::setCellTrackLengthFluxName( "cell.tl" );

  std::string estimator_name = 
    Geometry::DagMC::getCellTrackLengthFluxName();

  TEST_EQUALITY_CONST( estimator_name, "cell.tl" );

  Geometry::DagMC::setCellTrackLengthFluxName( default_estimator_name );
}

//---------------------------------------------------------------------------//
// Check that the cell collision flux name can be set
TEUCHOS_UNIT_TEST( DagMC, setCellCollisionFluxName )
{
  std::string default_estimator_name = 
    Geometry::DagMC::getCellCollisionFluxName();

  Geometry::DagMC::setCellCollisionFluxName( "cell.c" );

  std::string estimator_name = 
    Geometry::DagMC::getCellCollisionFluxName();

  TEST_EQUALITY_CONST( estimator_name, "cell.c" );

  Geometry::DagMC::setCellCollisionFluxName( default_estimator_name );
}

//---------------------------------------------------------------------------//
// Check that the estimator type is valid
TEUCHOS_UNIT_TEST( DagMC, isEstimatorTypeValid )
{
  TEST_ASSERT( Geometry::DagMC::isEstimatorTypeValid( "surface.current" ) );
  TEST_ASSERT( Geometry::DagMC::isEstimatorTypeValid( "surface.flux" ) );
  TEST_ASSERT( Geometry::DagMC::isEstimatorTypeValid( "cell.pulse.height" ) );
  TEST_ASSERT( Geometry::DagMC::isEstimatorTypeValid( "cell.tl.flux" ) );
  TEST_ASSERT( Geometry::DagMC::isEstimatorTypeValid( "cell.c.flux" ) );
  TEST_ASSERT( !Geometry::DagMC::isEstimatorTypeValid( "what?" ) );
}

//---------------------------------------------------------------------------//
// Check that the cell estimator type is valid
TEUCHOS_UNIT_TEST( DagMC, isCellEstimatorTypeValid )
{
  TEST_ASSERT( !Geometry::DagMC::isCellEstimatorTypeValid( "surface.current" ) );
  TEST_ASSERT( !Geometry::DagMC::isCellEstimatorTypeValid( "surface.flux" ) );
  TEST_ASSERT( Geometry::DagMC::isCellEstimatorTypeValid( "cell.pulse.height" ) );
  TEST_ASSERT( Geometry::DagMC::isCellEstimatorTypeValid( "cell.tl.flux" ) );
  TEST_ASSERT( Geometry::DagMC::isCellEstimatorTypeValid( "cell.c.flux" ) );
  TEST_ASSERT( !Geometry::DagMC::isCellEstimatorTypeValid( "what?" ) );
}

//---------------------------------------------------------------------------//
// Check that the surface estimator type is valid
TEUCHOS_UNIT_TEST( DagMC, isSurfaceEstimatorValid )
{
  TEST_ASSERT( Geometry::DagMC::isSurfaceEstimatorTypeValid( "surface.current" ) );
  TEST_ASSERT( Geometry::DagMC::isSurfaceEstimatorTypeValid( "surface.flux" ) );
  TEST_ASSERT( !Geometry::DagMC::isSurfaceEstimatorTypeValid( "cell.pulse.height" ) );
  TEST_ASSERT( !Geometry::DagMC::isSurfaceEstimatorTypeValid( "cell.tl.flux" ) );
  TEST_ASSERT( !Geometry::DagMC::isSurfaceEstimatorTypeValid( "cell.c.flux" ) );
  TEST_ASSERT( !Geometry::DagMC::isSurfaceEstimatorTypeValid( "what?" ) );
}

//---------------------------------------------------------------------------//
// Check that the particle type is valid
TEUCHOS_UNIT_TEST( DagMC, isParticleTypeValid )
{
  TEST_ASSERT( Geometry::DagMC::isParticleTypeValid( "n" ) );
  TEST_ASSERT( Geometry::DagMC::isParticleTypeValid( "p" ) );
  TEST_ASSERT( Geometry::DagMC::isParticleTypeValid( "e" ) );
  TEST_ASSERT( !Geometry::DagMC::isParticleTypeValid( "z" ) );
}

//---------------------------------------------------------------------------//
// Check that DagMC can be initialized
TEUCHOS_UNIT_TEST( DagMC, initialize )
{
  Geometry::DagMC::setTerminationCellPropertyName( "graveyard" );
  Geometry::DagMC::setMaterialPropertyName( "mat" );
  Geometry::DagMC::setDensityPropertyName( "rho" );
  Geometry::DagMC::setEstimatorPropertyName( "tally" );

  TEST_ASSERT( !Geometry::DagMC::isInitialized() );
  
  TEST_NOTHROW( Geometry::DagMC::initialize( test_dagmc_geom_file_name,
                                             1e-3,
                                             false ) );

  TEST_ASSERT( Geometry::DagMC::isInitialized() );
}

//---------------------------------------------------------------------------//
// Check that the material ids can be returned
TEUCHOS_UNIT_TEST( DagMC, getMaterialIds )
{
  std::set<unsigned> material_ids;

  TEST_NOTHROW( Geometry::DagMC::getMaterialIds( material_ids ) );

  TEST_EQUALITY_CONST( material_ids.size(), 8 );
  TEST_ASSERT( material_ids.count( 1 ) );
  TEST_ASSERT( material_ids.count( 2 ) );
  TEST_ASSERT( material_ids.count( 3 ) );
  TEST_ASSERT( material_ids.count( 4 ) );
  TEST_ASSERT( material_ids.count( 7 ) );
  TEST_ASSERT( material_ids.count( 8 ) );
  TEST_ASSERT( material_ids.count( 9 ) );
  TEST_ASSERT( material_ids.count( 10 ) );
}

//---------------------------------------------------------------------------//
// Check that the cell estimator data can be returned
TEUCHOS_UNIT_TEST( DagMC, getCellEstimatorData )
{
  std::map<unsigned,Utility::Trip<std::string,std::string,std::vector<Geometry::ModuleTraits::InternalCellHandle> > > cell_estimator_id_data_map;

  TEST_NOTHROW( Geometry::DagMC::getCellEstimatorData( 
                                                cell_estimator_id_data_map ) );

  TEST_EQUALITY_CONST( cell_estimator_id_data_map.size(), 5 );
  TEST_ASSERT( cell_estimator_id_data_map.count( 0 ) );
  TEST_ASSERT( cell_estimator_id_data_map.count( 1 ) );
  TEST_ASSERT( cell_estimator_id_data_map.count( 2 ) );
  TEST_ASSERT( cell_estimator_id_data_map.count( 3 ) );
  TEST_ASSERT( cell_estimator_id_data_map.count( 4 ) );

  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 0 )->second.first,
                       "cell.tl.flux" );
  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 0 )->second.second,
                       "n" );
  TEST_EQUALITY_CONST( 
                     cell_estimator_id_data_map.find( 0 )->second.third.size(),
                     55 );
  
  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 1 )->second.first,
                       "cell.tl.flux" );
  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 1 )->second.second,
                       "p" );
  TEST_EQUALITY_CONST( 
                     cell_estimator_id_data_map.find( 1 )->second.third.size(),
                     55 );

  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 2 )->second.first,
                       "cell.c.flux" );
  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 2 )->second.second,
                       "n" );
  TEST_EQUALITY_CONST( 
                     cell_estimator_id_data_map.find( 2 )->second.third.size(),
                     36 );

  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 3 )->second.first,
                       "cell.c.flux" );
  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 3 )->second.second,
                       "p" );
  TEST_EQUALITY_CONST( 
                     cell_estimator_id_data_map.find( 3 )->second.third.size(),
                     36 );
  
  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 4 )->second.first,
                       "cell.pulse.height" );
  TEST_EQUALITY_CONST( cell_estimator_id_data_map.find( 4 )->second.second,
                       "p" );
  TEST_EQUALITY_CONST( 
                     cell_estimator_id_data_map.find( 4 )->second.third.size(),
                     2 );
}

//---------------------------------------------------------------------------//
// Check that the surface estimator data can be returned
TEUCHOS_UNIT_TEST( DagMC, getSurfaceEstimatorData )
{
  std::map<unsigned,Utility::Trip<std::string,std::string,std::vector<Geometry::ModuleTraits::InternalSurfaceHandle> > > surface_estimator_id_data_map;

  TEST_NOTHROW( Geometry::DagMC::getSurfaceEstimatorData( 
                                             surface_estimator_id_data_map ) );

  TEST_EQUALITY_CONST( surface_estimator_id_data_map.size(), 4 );
  TEST_ASSERT( surface_estimator_id_data_map.count( 5 ) );
  TEST_ASSERT( surface_estimator_id_data_map.count( 6 ) );
  TEST_ASSERT( surface_estimator_id_data_map.count( 7 ) );
  TEST_ASSERT( surface_estimator_id_data_map.count( 8 ) );

  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 5 )->second.first,
                       "surface.flux" );
  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 5 )->second.second,
                       "n" );
  TEST_EQUALITY_CONST( 
                  surface_estimator_id_data_map.find( 5 )->second.third.size(),
                  7 );

  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 6 )->second.first,
                       "surface.flux" );
  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 6 )->second.second,
                       "p" );
  TEST_EQUALITY_CONST( 
                  surface_estimator_id_data_map.find( 6 )->second.third.size(),
                  7 );

  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 7 )->second.first,
                       "surface.current" );
  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 7 )->second.second,
                       "n" );
  TEST_EQUALITY_CONST( 
                  surface_estimator_id_data_map.find( 7 )->second.third.size(),
                  7 );

  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 8 )->second.first,
                       "surface.current" );
  TEST_EQUALITY_CONST( surface_estimator_id_data_map.find( 8 )->second.second,
                       "p" );
  TEST_EQUALITY_CONST( 
                  surface_estimator_id_data_map.find( 8 )->second.third.size(),
                  7 );
}

//---------------------------------------------------------------------------//
// Check if cells exist
TEUCHOS_UNIT_TEST( DagMC, doesCellExist )
{
  TEST_ASSERT( !Geometry::DagMC::doesCellExist( 0 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 1 ) );
  TEST_ASSERT( !Geometry::DagMC::doesCellExist( 2 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 3 ) );
  TEST_ASSERT( !Geometry::DagMC::doesCellExist( 4 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 5 ) );
  TEST_ASSERT( !Geometry::DagMC::doesCellExist( 6 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 7 ) );
  TEST_ASSERT( !Geometry::DagMC::doesCellExist( 8 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 9 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 13 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 19 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 26 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 27 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 28 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 29 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 30 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 31 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 32 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 33 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 34 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 35 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 36 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 37 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 41 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 48 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 49 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 50 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 51 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 52 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 53 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 54 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 55 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 56 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 57 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 58 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 59 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 63 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 70 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 71 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 72 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 73 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 74 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 75 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 76 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 77 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 78 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 79 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 80 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 81 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 82 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 83 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 88 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 136 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 152 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 154 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 166 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 168 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 184 ) );
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 188 ) );
  
  // Implicit compliment cell
  TEST_ASSERT( Geometry::DagMC::doesCellExist( 189 ) ); 
}

//---------------------------------------------------------------------------//
// Check if surfaces exist
TEUCHOS_UNIT_TEST( DagMC, doesSurfaceExist )
{
  TEST_ASSERT( !Geometry::DagMC::doesSurfaceExist( 0 ) );
  TEST_ASSERT( Geometry::DagMC::doesSurfaceExist( 1 ) );
  TEST_ASSERT( !Geometry::DagMC::doesSurfaceExist( 2 ) );
  TEST_ASSERT( !Geometry::DagMC::doesSurfaceExist( 3 ) );
  TEST_ASSERT( !Geometry::DagMC::doesSurfaceExist( 4 ) );
  TEST_ASSERT( !Geometry::DagMC::doesSurfaceExist( 5 ) );
  TEST_ASSERT( !Geometry::DagMC::doesSurfaceExist( 6 ) );
  TEST_ASSERT( Geometry::DagMC::doesSurfaceExist( 7 ) );
  TEST_ASSERT( Geometry::DagMC::doesSurfaceExist( 8 ) );
  TEST_ASSERT( Geometry::DagMC::doesSurfaceExist( 9 ) );

  // There are more surfaces than this but too many to feasibly check
}

//---------------------------------------------------------------------------//
// Check that the problem cells can be returned
TEUCHOS_UNIT_TEST( DagMC, getCells )
{
  std::set<Geometry::ModuleTraits::InternalCellHandle> cells;

  Geometry::DagMC::getCells( cells );

  // 55 + implicit compliment cell
  TEST_EQUALITY_CONST( cells.size(), 56 );
  
  TEST_ASSERT( cells.count( 1 ) );
  TEST_ASSERT( cells.count( 3 ) );
  TEST_ASSERT( cells.count( 5 ) );
  TEST_ASSERT( cells.count( 7 ) );
  TEST_ASSERT( cells.count( 9 ) );
  TEST_ASSERT( cells.count( 13 ) );
  TEST_ASSERT( cells.count( 19 ) );
  TEST_ASSERT( cells.count( 26 ) );
  TEST_ASSERT( cells.count( 27 ) );
  TEST_ASSERT( cells.count( 28 ) );
  TEST_ASSERT( cells.count( 29 ) );
  TEST_ASSERT( cells.count( 30 ) );
  TEST_ASSERT( cells.count( 31 ) );
  TEST_ASSERT( cells.count( 32 ) );
  TEST_ASSERT( cells.count( 33 ) );
  TEST_ASSERT( cells.count( 34 ) );
  TEST_ASSERT( cells.count( 35 ) );
  TEST_ASSERT( cells.count( 36 ) );
  TEST_ASSERT( cells.count( 37 ) );
  TEST_ASSERT( cells.count( 41 ) );
  TEST_ASSERT( cells.count( 48 ) );
  TEST_ASSERT( cells.count( 49 ) );
  TEST_ASSERT( cells.count( 50 ) );
  TEST_ASSERT( cells.count( 51 ) );
  TEST_ASSERT( cells.count( 52 ) );
  TEST_ASSERT( cells.count( 53 ) );
  TEST_ASSERT( cells.count( 54 ) );
  TEST_ASSERT( cells.count( 55 ) );
  TEST_ASSERT( cells.count( 56 ) );
  TEST_ASSERT( cells.count( 57 ) );
  TEST_ASSERT( cells.count( 58 ) );
  TEST_ASSERT( cells.count( 59 ) );
  TEST_ASSERT( cells.count( 63 ) );
  TEST_ASSERT( cells.count( 70 ) );
  TEST_ASSERT( cells.count( 71 ) );
  TEST_ASSERT( cells.count( 72 ) );
  TEST_ASSERT( cells.count( 73 ) );
  TEST_ASSERT( cells.count( 74 ) );
  TEST_ASSERT( cells.count( 75 ) );
  TEST_ASSERT( cells.count( 76 ) );
  TEST_ASSERT( cells.count( 77 ) );
  TEST_ASSERT( cells.count( 78 ) );
  TEST_ASSERT( cells.count( 79 ) );
  TEST_ASSERT( cells.count( 80 ) );
  TEST_ASSERT( cells.count( 81 ) );
  TEST_ASSERT( cells.count( 82 ) );
  TEST_ASSERT( cells.count( 83 ) );
  TEST_ASSERT( cells.count( 88 ) );
  TEST_ASSERT( cells.count( 136 ) );
  TEST_ASSERT( cells.count( 152 ) );
  TEST_ASSERT( cells.count( 154 ) );
  TEST_ASSERT( cells.count( 166 ) );
  TEST_ASSERT( cells.count( 168 ) );
  TEST_ASSERT( cells.count( 184 ) );
  TEST_ASSERT( cells.count( 188 ) );
  TEST_ASSERT( cells.count( 189 ) );
}

//---------------------------------------------------------------------------//
// Check that the problem surfaces can be returned
TEUCHOS_UNIT_TEST( DagMC, getSurfaces )
{
  std::set<Geometry::ModuleTraits::InternalSurfaceHandle> surfaces;

  Geometry::DagMC::getSurfaces( surfaces );

  TEST_EQUALITY_CONST( surfaces.size(), 293 );
}

//---------------------------------------------------------------------------//
// Check that the cell volume can be returned
TEUCHOS_UNIT_TEST( DagMC, getCellVolume )
{
  // Get the volume of cell 53
  double cell_volume = Geometry::DagMC::getCellVolume( 53 );

  TEST_FLOATING_EQUALITY( cell_volume, 98.322384, 1e-6 );
}

//---------------------------------------------------------------------------//
// Check that the surface area can be returned
TEUCHOS_UNIT_TEST( DagMC, getSurfaceArea )
{
  // Get the surface area of surface 242
  double surface_area = Geometry::DagMC::getSurfaceArea( 242 );

  TEST_FLOATING_EQUALITY( surface_area, 38.7096, 1e-6 );
}

//---------------------------------------------------------------------------//
// Check is cells are termination cells
TEUCHOS_UNIT_TEST( DagMC, isTerminationCell )
{
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 1 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 3 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 5 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 7 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 9 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 13 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 19 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 26 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 27 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 28 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 29 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 30 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 31 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 32 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 33 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 34 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 35 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 36 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 37 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 41 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 48 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 49 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 50 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 51 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 52 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 53 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 54 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 55 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 56 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 57 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 58 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 59 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 63 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 70 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 71 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 72 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 73 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 74 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 75 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 76 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 77 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 78 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 79 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 80 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 81 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 82 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 83 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 88 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 136 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 152 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 154 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 166 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 168 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 184 ) );
  TEST_ASSERT( Geometry::DagMC::isTerminationCell( 188 ) );
  TEST_ASSERT( !Geometry::DagMC::isTerminationCell( 189 ) );
}

//---------------------------------------------------------------------------//
// Check if the cell is a void cell
TEUCHOS_UNIT_TEST( DagMC, isVoidCell )
{
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 1 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 3 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 5 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 7 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 9 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 13 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 19 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 26 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 27 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 28 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 29 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 30 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 31 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 32 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 33 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 34 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 35 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 36 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 37 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 41 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 48 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 49 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 50 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 51 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 52 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 53 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 54 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 55 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 56 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 57 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 58 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 59 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 63 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 70 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 71 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 72 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 73 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 74 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 75 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 76 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 77 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 78 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 79 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 80 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 81 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 82 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 83 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 88 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 136 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 152 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 154 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 166 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 168 ) );
  TEST_ASSERT( !Geometry::DagMC::isVoidCell( 184 ) );
  TEST_ASSERT( Geometry::DagMC::isVoidCell( 188 ) );
  TEST_ASSERT( Geometry::DagMC::isVoidCell( 189 ) );
}

//---------------------------------------------------------------------------//
// Check if a surface is a reflecting surface
TEUCHOS_UNIT_TEST( DagMC, isReflectingSurface )
{
  TEST_ASSERT( Geometry::DagMC::isReflectingSurface( 408 ) );
  TEST_ASSERT( !Geometry::DagMC::isReflectingSurface( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that the cell material ids can be returned
TEUCHOS_UNIT_TEST( DagMC, getCellMaterialIds )
{
  std::map<Geometry::ModuleTraits::InternalCellHandle,unsigned>
    cell_id_mat_id_map;

  TEST_NOTHROW( Geometry::DagMC::getCellMaterialIds( cell_id_mat_id_map ) );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.size(), 54 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 9 )->second, 1 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 88 )->second, 1 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 136 )->second, 2 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 19 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 41 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 63 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 82 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 152 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 166 )->second, 3 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 184 )->second, 3 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 3 )->second, 4 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 7 )->second, 4 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 13 )->second, 7 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 83 )->second, 7 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 154 )->second, 7 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 168 )->second, 7 );

  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 1 )->second, 8 );
  
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 26 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 27 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 28 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 29 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 30 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 31 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 32 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 33 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 34 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 35 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 36 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 37 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 48 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 49 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 50 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 51 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 52 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 53 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 54 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 55 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 56 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 57 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 58 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 59 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 70 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 71 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 72 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 73 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 74 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 75 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 76 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 77 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 78 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 79 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 80 )->second, 9 );
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 81 )->second, 9 );
  
  TEST_EQUALITY_CONST( cell_id_mat_id_map.find( 5 )->second, 10 );
}

//---------------------------------------------------------------------------//
// Check that the cell densities can be returned
TEUCHOS_UNIT_TEST( DagMC, getCellDensities )
{
  std::map<Geometry::ModuleTraits::InternalCellHandle,double>
    cell_id_density_map;

  TEST_NOTHROW( Geometry::DagMC::getCellDensities( cell_id_density_map ) );

  TEST_EQUALITY_CONST( cell_id_density_map.size(), 54 );

  TEST_EQUALITY_CONST( cell_id_density_map.size(), 54 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 9 )->second, -8.027 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 88 )->second, -8.027 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 136 )->second, -7.75 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 19 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 41 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 63 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 82 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 152 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 166 )->second, -0.001633 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 184 )->second, -0.001633 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 3 )->second, -0.99823 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 7 )->second, -0.99823 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 13 )->second, -5.65 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 83 )->second, -5.65 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 154 )->second, -5.65 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 168 )->second, -5.65 );

  TEST_EQUALITY_CONST( cell_id_density_map.find( 1 )->second, -1.8583 );
  
  TEST_EQUALITY_CONST( cell_id_density_map.find( 26 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 27 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 28 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 29 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 30 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 31 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 32 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 33 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 34 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 35 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 36 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 37 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 48 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 49 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 50 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 51 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 52 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 53 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 54 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 55 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 56 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 57 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 58 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 59 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 70 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 71 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 72 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 73 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 74 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 75 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 76 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 77 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 78 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 79 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 80 )->second, -7.83 );
  TEST_EQUALITY_CONST( cell_id_density_map.find( 81 )->second, -7.83 );
  
  TEST_EQUALITY_CONST( cell_id_density_map.find( 5 )->second, -13.31 );
}

//---------------------------------------------------------------------------//
// Check that the surface normal can be found
TEUCHOS_UNIT_TEST( DagMC, getSurfaceNormal )
{
  // Initialize the ray (on cell 53)
  Geometry::Ray ray( -40.0, -40.0, 60.959999084, 0.0, 0.0, 1.0 );

  // Get the surface normal
  Teuchos::Tuple<double,3> normal;
  
  Geometry::DagMC::getSurfaceNormal( 242, 
                                     ray.getPosition(), 
                                     normal.getRawPtr() );

  Teuchos::Tuple<double,3> ref_normal = Teuchos::tuple( 0.0, 0.0, 1.0 );
  
  TEST_COMPARE_ARRAYS( normal, ref_normal );
}

//---------------------------------------------------------------------------//
// Check that the point location w.r.t. a given cell can be returned
TEUCHOS_UNIT_TEST( DagMC, getPointLocation )
{
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> ray( new Geometry::Ray( 
                                         -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );
  
  Geometry::PointLocation location = 
    Geometry::DagMC::getPointLocation( *ray, 53 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  ray.reset( new Geometry::Ray( -42.647, -40.0, 59.0, -1.0, 0.0, 0.0 ) );

  location = Geometry::DagMC::getPointLocation( *ray, 53 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_INSIDE_CELL );

  ray.reset( new Geometry::Ray( -42.648, -40.0, 59.0, -1.0, 0.0, 0.0 ) );

  location = Geometry::DagMC::getPointLocation( *ray, 53 );

  TEST_EQUALITY_CONST( location, Geometry::POINT_OUTSIDE_CELL );
}

//---------------------------------------------------------------------------//
// Check that the boundary cell can be found
TEUCHOS_UNIT_TEST( DagMC, getBoundaryCell )
{
  TEST_EQUALITY_CONST( Geometry::DagMC::getBoundaryCell( 53, 242 ), 54 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getBoundaryCell( 54, 248 ), 55 );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the external ray can be found
TEUCHOS_UNIT_TEST( DagMC, findCellContainingExternalRay )
{
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> ray( 
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );
  
  // Find the cell that contains the point
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::DagMC::findCellContainingExternalRay( *ray );
  
  TEST_EQUALITY_CONST( cell, 53 );

  // Initailize a new ray
  ray.reset( new Geometry::Ray( -40.0, -40.0, 61.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = Geometry::DagMC::findCellContainingExternalRay( *ray );
  
  TEST_EQUALITY_CONST( cell, 54 );

  // Initialize the new ray
  ray.reset( new Geometry::Ray( -40.0, -40.0, 64.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = Geometry::DagMC::findCellContainingExternalRay( *ray );
  
  TEST_EQUALITY_CONST( cell, 55 );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the external ray can be found and cached
TEUCHOS_UNIT_TEST( DagMC, findAndCacheCellContainingExternalRay )
{
  // Initialize the ray
  std::shared_ptr<Geometry::Ray> ray( 
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );
  
  // Find the cell that contains the point
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::DagMC::findAndCacheCellContainingExternalRay( *ray );
  
  TEST_EQUALITY_CONST( cell, 53 );

  // Initailize a new ray
  ray.reset( new Geometry::Ray( -39.0, -39.0, 59.0, 1.0, 0.0, 0.0 ) );

  // Find the cell that contains the point
  cell = Geometry::DagMC::findAndCacheCellContainingExternalRay( *ray );
  
  TEST_EQUALITY_CONST( cell, 53 );

  // Initailize a new ray
  ray.reset( new Geometry::Ray( -40.0, -40.0, 61.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = Geometry::DagMC::findAndCacheCellContainingExternalRay( *ray );
  
  TEST_EQUALITY_CONST( cell, 54 );

  // Initialize the new ray
  ray.reset( new Geometry::Ray( -40.0, -40.0, 64.0, 0.0, 0.0, 1.0 ) );

  // Find the cell that contains the point
  cell = Geometry::DagMC::findAndCacheCellContainingExternalRay( *ray );
  
  TEST_EQUALITY_CONST( cell, 55 );

  // Check the found cell cache
  std::set<Geometry::ModuleTraits::InternalCellHandle> found_cell_cache;

  Geometry::DagMC::getFoundCellCache( found_cell_cache );

  TEST_EQUALITY_CONST( found_cell_cache.size(), 3 );
  TEST_ASSERT( found_cell_cache.count( 53 ) );
  TEST_ASSERT( found_cell_cache.count( 54 ) );
  TEST_ASSERT( found_cell_cache.count( 55 ) );

  Geometry::DagMC::clearFoundCellCache();
}

//---------------------------------------------------------------------------//
// Check that an external ray can be fired
TEUCHOS_UNIT_TEST( DagMC, fireExternalRay_unknown_cell )
{
  // Initialize the ray
  Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );

  // Fire an external ray through the geometry
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
  double distance_to_surface_hit = 
    Geometry::DagMC::fireExternalRay( ray, surface_hit );
 
  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.959999084, 1e-9 );
  TEST_EQUALITY_CONST( surface_hit, 242 );
}

//---------------------------------------------------------------------------//
// Check that an external ray can be fired
TEUCHOS_UNIT_TEST( DagMC, fireExternalRay_known_cell )
{
  // Initialize the ray
  Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );

  // Fire an external ray through the geometry
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
  double distance_to_surface_hit = 
    Geometry::DagMC::fireExternalRay( ray, 53, surface_hit );
 
  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.959999084, 1e-9 );
  TEST_EQUALITY_CONST( surface_hit, 242 );
}

//---------------------------------------------------------------------------//
// Check that an external ray track can be done
TEUCHOS_UNIT_TEST( DagMC, external_ray_trace )
{
  // Initialize the ray
  Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::DagMC::findCellContainingExternalRay( ray );

  TEST_EQUALITY_CONST( cell, 53 );

  // Fire the ray
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
  double distance_to_surface_hit = 
    Geometry::DagMC::fireExternalRay( ray, cell, surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.959999084, 1e-9 );
  TEST_EQUALITY_CONST( surface_hit, 242 );

  // Advance the ray to the boundary surface
  ray.advanceHead( distance_to_surface_hit );

  // Find the cell on the other side of the boundary surface
  cell = Geometry::DagMC::getBoundaryCell( cell, surface_hit );

  TEST_EQUALITY_CONST( cell, 54 );

  // Fire the ray
  distance_to_surface_hit = 
    Geometry::DagMC::fireExternalRay( ray, cell, surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 2.54, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 248 );

  // Advance the ray to the boundary surface
  ray.advanceHead( distance_to_surface_hit );

  // Find the cell on the other side of the boundary surface
  cell = Geometry::DagMC::getBoundaryCell( cell, surface_hit );

  TEST_EQUALITY_CONST( cell, 55 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
TEUCHOS_UNIT_TEST( DagMC, setInternalRay_unknown_cell )
{
  TEST_ASSERT( !Geometry::DagMC::isInternalRaySet() );

  // Set the internal ray but do not cache its starting cell
  std::shared_ptr<Geometry::Ray> ray( 
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  Geometry::DagMC::setInternalRay( ray->getPosition(),
                                   ray->getDirection(),
                                   false );

  TEST_ASSERT( Geometry::DagMC::isInternalRaySet() );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[0], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[1], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[2], 59.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[2], 1.0 );

  ray.reset( new Geometry::Ray( -40.0, -40.0, 61.0, 0.0, 0.0, 1.0 ) );

  Geometry::DagMC::setInternalRay( *ray, false );

  TEST_ASSERT( Geometry::DagMC::isInternalRaySet() );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[0], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[1], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[2], 61.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[2], 1.0 );

  std::set<Geometry::ModuleTraits::InternalCellHandle> cached_cells;
  
  Geometry::DagMC::getFoundCellCache( cached_cells );

  TEST_EQUALITY_CONST( cached_cells.size(), 0 );

  // Set the internal ray and cache its starting cell
  ray.reset( new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  Geometry::DagMC::setInternalRay( ray->getPosition(),
                                   ray->getDirection(),
                                   true );

  TEST_ASSERT( Geometry::DagMC::isInternalRaySet() );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[0], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[1], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[2], 59.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[2], 1.0 );

  ray.reset( new Geometry::Ray( -40.0, -40.0, 61.0, 0.0, 0.0, 1.0 ) );

  Geometry::DagMC::setInternalRay( *ray, true );

  TEST_ASSERT( Geometry::DagMC::isInternalRaySet() );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[0], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[1], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[2], 61.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[2], 1.0 );

  Geometry::DagMC::getFoundCellCache( cached_cells );

  TEST_EQUALITY_CONST( cached_cells.size(), 2 );
  TEST_ASSERT( cached_cells.count( 53 ) );
  TEST_ASSERT( cached_cells.count( 54 ) );

  Geometry::DagMC::clearFoundCellCache();
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be set
TEUCHOS_UNIT_TEST( DagMC, setInternalRay_known_cell )
{
  // Set the internal ray but do not cache its starting cell
  std::shared_ptr<Geometry::Ray> ray( 
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  Geometry::DagMC::setInternalRay( ray->getPosition(),
                                   ray->getDirection(),
                                   53,
                                   false );

  TEST_ASSERT( Geometry::DagMC::isInternalRaySet() );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[0], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[1], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[2], 59.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[2], 1.0 );

  ray.reset( new Geometry::Ray( -40.0, -40.0, 61.0, 0.0, 0.0, 1.0 ) );

  Geometry::DagMC::setInternalRay( *ray, 54, false );

  TEST_ASSERT( Geometry::DagMC::isInternalRaySet() );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[0], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[1], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[2], 61.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[2], 1.0 );

  std::set<Geometry::ModuleTraits::InternalCellHandle> cached_cells;
  
  Geometry::DagMC::getFoundCellCache( cached_cells );

  TEST_EQUALITY_CONST( cached_cells.size(), 0 );

  // Set the internal ray and cache its starting cell
  ray.reset( new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  Geometry::DagMC::setInternalRay( ray->getPosition(),
                                   ray->getDirection(),
                                   53,
                                   true );

  TEST_ASSERT( Geometry::DagMC::isInternalRaySet() );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[0], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[1], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[2], 59.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[2], 1.0 );

  ray.reset( new Geometry::Ray( -40.0, -40.0, 61.0, 0.0, 0.0, 1.0 ) );

  Geometry::DagMC::setInternalRay( *ray, 54, true );

  TEST_ASSERT( Geometry::DagMC::isInternalRaySet() );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[0], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[1], -40.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayPosition()[2], 61.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[0], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[2], 1.0 );

  Geometry::DagMC::getFoundCellCache( cached_cells );

  TEST_EQUALITY_CONST( cached_cells.size(), 2 );
  TEST_ASSERT( cached_cells.count( 53 ) );
  TEST_ASSERT( cached_cells.count( 54 ) );

  Geometry::DagMC::clearFoundCellCache();
}

//---------------------------------------------------------------------------//
// Check that the internal ray direction can be changed
TEUCHOS_UNIT_TEST( DagMC, changeInternalRayDirection )
{
  std::shared_ptr<Geometry::Ray> ray( 
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  Geometry::DagMC::setInternalRay( ray->getPosition(),
                                   ray->getDirection(),
                                   53,
                                   false );

  ray.reset( new Geometry::Ray( -40.0, -40.0, 59.0, 1.0, 0.0, 0.0 ) );
  
  Geometry::DagMC::changeInternalRayDirection( ray->getDirection() );

  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[0], 1.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[1], 0.0 );
  TEST_EQUALITY_CONST( Geometry::DagMC::getInternalRayDirection()[2], 0.0 );
}

//---------------------------------------------------------------------------//
// Check that the cell containing the internal ray can be found
TEUCHOS_UNIT_TEST( DagMC, findCellContainingInternalRay )
{
  std::shared_ptr<Geometry::Ray> ray( 
                      new Geometry::Ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 ) );

  Geometry::DagMC::setInternalRay( ray->getPosition(),
                                   ray->getDirection(),
                                   false );
  
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::DagMC::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 53 );

  Geometry::DagMC::setInternalRay( ray->getPosition(),
                                   ray->getDirection(),
                                   53,
                                   false );

  cell = Geometry::DagMC::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 53 );
}

//---------------------------------------------------------------------------//
// Check that the internal ray can be fired
TEUCHOS_UNIT_TEST( DagMC, fireInternalRay )
{
  // Initialize the ray
  Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );

  Geometry::DagMC::setInternalRay( ray, 53, false );

  // Fire an external ray through the geometry
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
  double distance_to_surface_hit = 
    Geometry::DagMC::fireInternalRay( surface_hit );
 
  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.959999084, 1e-9 );
  TEST_EQUALITY_CONST( surface_hit, 242 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be advanced by a substep
TEUCHOS_UNIT_TEST( DagMC, advanceInternalRayBySubstep )
{
  // Initialize the ray
  {
    Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );
    
    Geometry::DagMC::setInternalRay( ray, 53, false );
  }

  Geometry::DagMC::advanceInternalRayBySubstep( 0.959999084 );

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::DagMC::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 53 );
  
  // Fire the ray
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
  double distance_to_surface_hit = 
    Geometry::DagMC::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.0, 1e-9 );
  TEST_EQUALITY_CONST( surface_hit, 242 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be advanced
TEUCHOS_UNIT_TEST( DagMC, advanceInternalRayToCellBoundary_basic )
{
  // Initialize the ray
  {
    Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );
    
    Geometry::DagMC::setInternalRay( ray, 53, false );
  }

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::DagMC::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 53 );

  // Advance the ray to the boundary surface
  Geometry::DagMC::advanceInternalRayToCellBoundary();

  cell = Geometry::DagMC::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 54 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray can be advanced
TEUCHOS_UNIT_TEST( DagMC, advanceInternalRayToCellBoundary_advanced )
{
  // Initialize the ray
  {
    Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );
    
    Geometry::DagMC::setInternalRay( ray, 53, false );
  }

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::DagMC::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 53 );

  // Advance the ray to the boundary surface
  double surface_normal[3];
  
  bool reflection = 
    Geometry::DagMC::advanceInternalRayToCellBoundary( surface_normal );

  TEST_ASSERT( !reflection );
  TEST_EQUALITY_CONST( surface_normal[0], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[1], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[2], 1.0 );

  cell = Geometry::DagMC::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 54 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray trace can be done
TEUCHOS_UNIT_TEST( DagMC, internal_ray_trace )
{
  // Initialize the ray
  {
    Geometry::Ray ray( -40.0, -40.0, 59.0, 0.0, 0.0, 1.0 );
    
    Geometry::DagMC::setInternalRay( ray, false );
  }

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::DagMC::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 53 );

  // Fire the ray
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
  double distance_to_surface_hit = 
    Geometry::DagMC::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.959999084, 1e-9 );
  TEST_EQUALITY_CONST( surface_hit, 242 );

  // Advance the ray to the boundary surface
  Geometry::DagMC::advanceInternalRayToCellBoundary();

  cell = Geometry::DagMC::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 54 );

  // Fire the ray
  distance_to_surface_hit = Geometry::DagMC::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 2.54, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 248 );

  // Advance the ray to the boundary surface
  Geometry::DagMC::advanceInternalRayToCellBoundary();

  cell = Geometry::DagMC::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 55 );

  // Fire the ray
  distance_to_surface_hit = Geometry::DagMC::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 2.54, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 254 );

  // Advance the ray a substep
  Geometry::DagMC::advanceInternalRayBySubstep( 0.5*distance_to_surface_hit );

  // Change the ray direction
  Geometry::DagMC::changeInternalRayDirection( 0.0, 0.0, -1.0 );

  // Fire the ray
  distance_to_surface_hit = Geometry::DagMC::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.27, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 248 );
}

//---------------------------------------------------------------------------//
// Check that an internal ray trace can be done
TEUCHOS_UNIT_TEST( DagMC, internal_ray_trace_with_reflection )
{
  // Initialize the ray
  {
    Geometry::Ray ray( -40.0, -40.0, 108.0, 0.0, 0.0, 1.0 );
    
    Geometry::DagMC::setInternalRay( ray, false );
  }

  // Find the cell that contains the ray
  Geometry::ModuleTraits::InternalCellHandle cell = 
    Geometry::DagMC::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 82 );

  // Fire the ray
  Geometry::ModuleTraits::InternalSurfaceHandle surface_hit;
  
  double distance_to_surface_hit = 
    Geometry::DagMC::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 1.474, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 394 );

  // Advance the ray to the boundary surface
  bool reflection = Geometry::DagMC::advanceInternalRayToCellBoundary();

  TEST_ASSERT( !reflection );

  cell = Geometry::DagMC::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 83 );

  distance_to_surface_hit = Geometry::DagMC::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 17.526, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 408 );

  // Advance the ray to the boundary surface (reflecting)
  double surface_normal[3];
  
  reflection = 
    Geometry::DagMC::advanceInternalRayToCellBoundary( surface_normal );

  TEST_ASSERT( reflection );
  TEST_EQUALITY_CONST( surface_normal[0], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[1], 0.0 );
  TEST_EQUALITY_CONST( surface_normal[2], 1.0 );

  cell = Geometry::DagMC::findCellContainingInternalRay();

  TEST_EQUALITY_CONST( cell, 83 );

  distance_to_surface_hit = Geometry::DagMC::fireInternalRay( surface_hit );

  TEST_FLOATING_EQUALITY( distance_to_surface_hit, 17.526, 1e-6 );
  TEST_EQUALITY_CONST( surface_hit, 394 );
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
