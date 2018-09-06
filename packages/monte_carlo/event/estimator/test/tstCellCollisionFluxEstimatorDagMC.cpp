//---------------------------------------------------------------------------//
//!
//! \file   tstCellCollisionFluxEstimatorDagMC.cpp
//! \author Alex Robinson
//! \brief  Cell collision flux estimator using DagMC unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_CellCollisionFluxEstimator.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_DagMCModel.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

std::shared_ptr<const Geometry::Model> model;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the cell volumes can be extracted if a DagMC model is used
FRENSIE_UNIT_TEST_TEMPLATE( CellCollisionFluxEstimator,
                            constructor,
                            MonteCarlo::WeightMultiplier,
                            MonteCarlo::WeightAndEnergyMultiplier )
{
  FETCH_TEMPLATE_PARAM( 0, ContributionMultiplierPolicy );

  std::shared_ptr<MonteCarlo::Estimator> estimator;

  std::vector<MonteCarlo::StandardCellEstimator::CellIdType>
    cell_ids( {1, 3, 5, 7, 9, 13, 19, 26, 27} );

  FRENSIE_REQUIRE_NO_THROW( estimator.reset( new MonteCarlo::CellCollisionFluxEstimator<ContributionMultiplierPolicy>(
                                                                  0u,
                                                                  1.0,
                                                                  cell_ids,
                                                                  *model ) ) );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 1 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 1 ),
                                   2.132266385813818943e+03,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 3 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 3 ),
                                   5.337709538131501859e+02,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 5 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 5 ),
                                   1.078484436147666202e+03,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 7 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 7 ),
                                   2.482463203839396044e+02,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 9 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 9 ),
                                   1.887323163037273162e+03,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 13 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 13 ),
                                   1.539742749775331276e+03,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 19 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 19 ),
                                   1.023254913345230079e+02,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 26 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 26 ),
                                   9.849797148475718132e+02,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 27 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 27 ),
                                   9.832239187547406800e+01,
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
  
  local_properties.setFacetTolerance( 1e-3 );
  local_properties.setTerminationCellPropertyName( "graveyard" );
  local_properties.setMaterialPropertyName( "mat" );
  local_properties.setDensityPropertyName( "rho" );
  local_properties.setEstimatorPropertyName( "tally" );
  
  std::shared_ptr<Geometry::DagMCModel> tmp_model =
    Geometry::DagMCModel::getInstance();

  tmp_model->initialize( local_properties );

  model = tmp_model;
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCellCollisionFluxEstimatorDagMC.cpp
//---------------------------------------------------------------------------//
