//---------------------------------------------------------------------------//
//!
//! \file   tstTetMeshTrackLengthFluxEstimator.cpp
//! \author Philip Britt
//! \brief  TetMeshTrackLengthFluxEstimator class unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_HexMeshTrackLengthFluxEstimator.hpp"
#include "MonteCarlo_EstimatorContributionMultiplierPolicy.hpp"
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_UnitTestHarnessExtensions.hpp"

int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();
  Teuchos::Array<double> x_grid_points, y_grid_points, z_grid_points;
  x_grid_points.push_back(0);
  x_grid_points.push_back(1);
  y_grid_points.push_back(0);
  y_grid_points.push_back(1);
  z_grid_points.push_back(0);
  z_grid_points.push_back(1);
  new MonteCarlo::HexMeshTrackLengthFluxEstimator<MonteCarlo::WeightMultiplier>(2, 2, x_grid_points, y_grid_points, z_grid_points);

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();
  
  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

