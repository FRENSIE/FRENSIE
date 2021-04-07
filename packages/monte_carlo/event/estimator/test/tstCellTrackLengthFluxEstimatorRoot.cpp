//---------------------------------------------------------------------------//
//!
//! \file   tstCellTrackLengthFluxEstimatorRoot.cpp
//! \author Alex Robinson
//! \brief  Cell track length flux estimator using Root unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_CellTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Geometry_RootModel.hpp"
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
FRENSIE_UNIT_TEST_TEMPLATE( CellTrackLengthFluxEstimator,
                            constructor,
                            MonteCarlo::WeightMultiplier,
                            MonteCarlo::WeightAndEnergyMultiplier,
                            MonteCarlo::WeightAndChargeMultiplier )
{
  FETCH_TEMPLATE_PARAM( 0, ContributionMultiplierPolicy );

  std::shared_ptr<MonteCarlo::Estimator> estimator;

  std::vector<MonteCarlo::StandardCellEstimator::CellIdType>
    cell_ids( {1, 2} );

  FRENSIE_REQUIRE_NO_THROW( estimator.reset( new MonteCarlo::CellTrackLengthFluxEstimator<ContributionMultiplierPolicy>(
                                                                  0u,
                                                                  1.0,
                                                                  cell_ids,
                                                                  *model ) ) );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 1 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 1 ),
                                   934.5501530502127,
                                   1e-15 );

  FRENSIE_REQUIRE( estimator->isEntityAssigned( 2 ) );
  FRENSIE_CHECK_FLOATING_EQUALITY( estimator->getEntityNormConstant( 2 ),
                                   65.44984694978736,
                                   1e-15 );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

std::string test_root_geom_file_name;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "test_root_file",
                                        test_root_geom_file_name, "",
                                        "Test ROOT file name" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  Geometry::RootModelProperties local_properties( test_root_geom_file_name );

  std::shared_ptr<Geometry::RootModel> tmp_model =
    Geometry::RootModel::getInstance();

  tmp_model->initialize( local_properties );

  model = tmp_model;
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstCellTrackLengthFluxEstimatorRoot.cpp
//---------------------------------------------------------------------------//
