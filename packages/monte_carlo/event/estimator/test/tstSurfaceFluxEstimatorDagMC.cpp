//---------------------------------------------------------------------------//
//!
//! \file   tstSurfaceFluxEstimatorDagMC.cpp
//! \author Alex Robinson
//! \brief  Surface flux estimator using DagMC unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "MonteCarlo_SurfaceFluxEstimator.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_DagMCModel.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const Geometry::Model> model;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the surface areas can be extracted if a DagMC model is used
FRENSIE_UNIT_TEST_TEMPLATE( SurfaceFluxEstimator,
                            constructor,
                            MonteCarlo::WeightMultiplier,
                            MonteCarlo::WeightAndEnergyMultiplier,
                            MonteCarlo::WeightAndChargeMultiplier )
{
  FETCH_TEMPLATE_PARAM( 0, ContributionMultiplierPolicy );

  std::shared_ptr<MonteCarlo::Estimator> estimator;

  std::vector<MonteCarlo::StandardSurfaceEstimator::SurfaceIdType>
    surface_ids( {46, 53, 55, 57, 58, 83, 86, 89, 92, 425, 434} );

  FRENSIE_REQUIRE_NO_THROW( estimator.reset( new MonteCarlo::SurfaceFluxEstimator<ContributionMultiplierPolicy>(
							     0u,
							     10.0,
							     surface_ids,
                                                             *model ) ) );
  FRENSIE_REQUIRE( estimator->isEntityAssigned( 46 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 46 ),
                                   2.848516339523823717e+02,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 53 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 53 ),
                                   9.773235727898624248e+01,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 55 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 55 ),
                                   1.666730003051475251e+01,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 57 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 57 ),
                                   2.594277176251208061e+02,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 58 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 58 ),
                                   3.715085987553494107e+01,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 83 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 83 ),
                                   6.714270351030512529e+01,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 86 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 86 ),
                                   3.165650076907713384e-01,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 89 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 89 ),
                                   3.165650076907712274e-01,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 92 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 92 ),
                                   3.165650076907711163e-01,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 425 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 425 ),
                                   8.970071513450820433,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 434 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 434 ),
                                   4.002587201643236448,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_dagmc_geom_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_cad_file",
                                        test_dagmc_geom_file_name, "",
                                        "Test CAD file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Geometry::DagMCModelProperties local_properties( test_dagmc_geom_file_name );

  local_properties.setTerminationCellPropertyName( "graveyard" );
  local_properties.setMaterialPropertyName( "mat" );
  local_properties.setDensityPropertyName( "rho" );
  local_properties.setEstimatorPropertyName( "tally" );

  model.reset( new Geometry::DagMCModel( local_properties ) );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstSurfaceFluxEstimatorDagMC.cpp
//---------------------------------------------------------------------------//

