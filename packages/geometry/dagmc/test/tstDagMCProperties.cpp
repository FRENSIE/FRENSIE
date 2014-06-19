//---------------------------------------------------------------------------//
//!
//! \file   tstDagMCProperties.cpp
//! \author Alex Robinson
//! \brief  DagMC property unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>

// FRENSIE Includes
#include "Geometry_DagMCHelpers.hpp"
#include "Geometry_DagMCProperties.hpp"

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the termination cell property name can be set
TEUCHOS_UNIT_TEST( DagMCProperties, setTerminationCellPropertyName )
{
  Geometry::DagMCProperties::setTerminationCellPropertyName( "term.cell" );

  TEST_EQUALITY_CONST( 
		   Geometry::DagMCProperties::getTerminationCellPropertyName(),
		   "term.cell" );
}

//---------------------------------------------------------------------------//
// Check that the material property name can be set
TEUCHOS_UNIT_TEST( DagMCProperties, setMaterialPropertyName )
{
  Geometry::DagMCProperties::setMaterialPropertyName( "mat" );

  TEST_EQUALITY_CONST( Geometry::DagMCProperties::getMaterialPropertyName(),
		       "mat" );
}

//---------------------------------------------------------------------------//
// Check that the density property name can be set
TEUCHOS_UNIT_TEST( DagMCProperties, setDensityPropertyName )
{
  Geometry::DagMCProperties::setDensityPropertyName( "dens" );

  TEST_EQUALITY_CONST( Geometry::DagMCProperties::getDensityPropertyName(),
		       "dens" );
}

//---------------------------------------------------------------------------//
// Check that the estimator property name can be set
TEUCHOS_UNIT_TEST( DagMCProperties, setEstimatorPropertyName )
{
  Geometry::DagMCProperties::setEstimatorPropertyName( "est" );

  TEST_EQUALITY_CONST( Geometry::DagMCProperties::getEstimatorPropertyName(),
		       "est" );
}

//---------------------------------------------------------------------------//
// Check that a cell estimator type can be tested 
TEUCHOS_UNIT_TEST( DagMCProperties, isCellEstimatorTypeValid )
{
  std::string e_type = "cell.pulse.height";

  TEST_ASSERT( Geometry::DagMCProperties::isCellEstimatorTypeValid( e_type ) );
  
  e_type = "cell.tl.flux";

  TEST_ASSERT( Geometry::DagMCProperties::isCellEstimatorTypeValid( e_type ) );

  e_type = "cell.c.flux";

  TEST_ASSERT( Geometry::DagMCProperties::isCellEstimatorTypeValid( e_type ) );

  e_type = "surface.flux";

  TEST_ASSERT( !Geometry::DagMCProperties::isCellEstimatorTypeValid( e_type ));

  e_type = "bad.type";

  TEST_ASSERT( !Geometry::DagMCProperties::isCellEstimatorTypeValid( e_type ));
}

//---------------------------------------------------------------------------//
// Check that a surface estimator type can be tested
TEUCHOS_UNIT_TEST( DagMCProperties, isSurfaceEstimatorTypeValid )
{
  std::string e_type = "surface.flux";

  TEST_ASSERT( Geometry::DagMCProperties::isSurfaceEstimatorTypeValid( e_type ) );

  e_type = "surface.current";

  TEST_ASSERT( Geometry::DagMCProperties::isSurfaceEstimatorTypeValid(e_type));

  e_type = "cell.tl.flux";

  TEST_ASSERT(!Geometry::DagMCProperties::isSurfaceEstimatorTypeValid(e_type));

  e_type = "bad.type";

  TEST_ASSERT(!Geometry::DagMCProperties::isSurfaceEstimatorTypeValid(e_type));
}

//---------------------------------------------------------------------------//
// Check that a particle type can be tested
TEUCHOS_UNIT_TEST( DagMCProperties, isParticleTypeValid )
{
  std::string p_type = "p";

  TEST_ASSERT( Geometry::DagMCProperties::isParticleTypeValid( p_type ) );

  p_type = "n";

  TEST_ASSERT( Geometry::DagMCProperties::isParticleTypeValid( p_type ) );

  p_type = "bad.type";

  TEST_ASSERT( !Geometry::DagMCProperties::isParticleTypeValid( p_type ) );
}

//---------------------------------------------------------------------------//
// Check that estimator property values can be extracted
TEUCHOS_UNIT_TEST( DagMCProperties, extractEstimatorPropertyValues )
{
  std::string prop_value = "0.cell.pulse.height.p";

  unsigned id;
  std::string e_type;
  std::string p_type;

  Geometry::DagMCProperties::extractEstimatorPropertyValues( prop_value,
							     id,
							     e_type,
							     p_type );

  TEST_EQUALITY_CONST( id, 0 );
  TEST_EQUALITY_CONST( e_type, "cell.pulse.height" );
  TEST_EQUALITY_CONST( p_type, "p" );

  prop_value = "1.cell.tl.flux.n";

  Geometry::DagMCProperties::extractEstimatorPropertyValues( prop_value,
							     id,
							     e_type,
							     p_type );

  TEST_EQUALITY_CONST( id, 1 );
  TEST_EQUALITY_CONST( e_type, "cell.tl.flux" );
  TEST_EQUALITY_CONST( p_type, "n" );

  prop_value = "2.cell.c.flux.p";

  Geometry::DagMCProperties::extractEstimatorPropertyValues( prop_value,
							     id,
							     e_type,
							     p_type );

  TEST_EQUALITY_CONST( id, 2 );
  TEST_EQUALITY_CONST( e_type, "cell.c.flux" );
  TEST_EQUALITY_CONST( p_type, "p" );

  prop_value = "3.surface.flux.n";

  Geometry::DagMCProperties::extractEstimatorPropertyValues( prop_value,
							     id,
							     e_type,
							     p_type );

  TEST_EQUALITY_CONST( id, 3 );
  TEST_EQUALITY_CONST( e_type, "surface.flux" );
  TEST_EQUALITY_CONST( p_type, "n" );

  prop_value = "4.surface.current.p";

  Geometry::DagMCProperties::extractEstimatorPropertyValues( prop_value,
							     id,
							     e_type,
							     p_type );

  TEST_EQUALITY_CONST( id, 4 );
  TEST_EQUALITY_CONST( e_type, "surface.current" );
  TEST_EQUALITY_CONST( p_type, "p" );
}

//---------------------------------------------------------------------------//
// end tstDagMCProperties.cpp
//---------------------------------------------------------------------------//
