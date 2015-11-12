//---------------------------------------------------------------------------//
//!
//! \file   tstDistributedSource.cpp
//! \author Alex Robinson
//! \brief  Distributed source unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_UnitTestRepository.hpp>
#include <Teuchos_GlobalMPISession.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_Ptr.hpp>
#include <Teuchos_RCP.hpp>

// Moab Includes
#include <moab/EntityHandle.hpp>
#include <DagMC.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_DistributedSource.hpp"
#include "Geometry_DagMCHelpers.hpp"
#include "Geometry_ModuleInterface.hpp"
#include "Utility_SphericalSpatialDistribution.hpp"
#include "Utility_SphericalDirectionalDistribution.hpp"
#include "Utility_PowerDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"

Teuchos::RCP<MonteCarlo::ParticleSource> source;

//---------------------------------------------------------------------------//
// Test Sat File Name
//---------------------------------------------------------------------------//
std::string test_geometry_file_name;

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )				\
  typedef moab::DagMC dagmc;						\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, dagmc ) 

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
// Initialize the source (uniform spherical source)
template<typename GeometryHandler>
void initializeSource( const bool set_importance_functions = false,
		       const bool set_rejection_cell = false )
{
  // Power distribution in r dimension
  Teuchos::RCP<Utility::OneDDistribution> 
    r_distribution( new Utility::PowerDistribution<2u>( 3.0, 0.0, 2.0 ) );
  
  // Uniform distribution in theta dimension
  Teuchos::RCP<Utility::OneDDistribution>
    theta_distribution( new Utility::UniformDistribution( 
					      0.0,
					      2*Utility::PhysicalConstants::pi,
					      1.0 ) );
  // Uniform distribution in mu dimension
  Teuchos::RCP<Utility::OneDDistribution>
    mu_distribution( new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

  // Create the spatial distribution
  Teuchos::RCP<Utility::SpatialDistribution>
    spatial_distribution( new Utility::SphericalSpatialDistribution( 
							    r_distribution,
							    theta_distribution,
							    mu_distribution,
							    0.0,
							    0.0,
							    0.0 ) );

  // Create the directional distribution
  Teuchos::RCP<Utility::DirectionalDistribution>
    directional_distribution( new Utility::SphericalDirectionalDistribution( 
							   theta_distribution,
							   mu_distribution ) );

  // Uniform distribution in energy dimension
  Teuchos::RCP<Utility::OneDDistribution>
    energy_distribution( new Utility::UniformDistribution( 1e-3, 1.0, 1.0 ) );

  // Delta distribution in time dimension
  Teuchos::RCP<Utility::OneDDistribution>
    time_distribution( new Utility::DeltaDistribution( 0.0 ) );

  // Create the distributed source
  source.reset( new MonteCarlo::DistributedSource( 
     0u,
     spatial_distribution,
     directional_distribution,
     energy_distribution,
     time_distribution,
     MonteCarlo::PHOTON,
     &Geometry::ModuleInterface<GeometryHandler>::getPointLocation) );

  // Set the importance functions if requested
  if( set_importance_functions )
  {
    // Uniform distribution in theta dimension
    Teuchos::Array<double> bin_boundaries( 4 );
    bin_boundaries[0] = 0.0;
    bin_boundaries[1] = Utility::PhysicalConstants::pi/2;
    bin_boundaries[2] = 3*Utility::PhysicalConstants::pi/2;
    bin_boundaries[3] = 2*Utility::PhysicalConstants::pi;

    Teuchos::Array<double> bin_values( 3 );
    bin_values[0] = 1.0;
    bin_values[1] = 2.0;
    bin_values[2] = 1.0;
    
    Teuchos::RCP<Utility::OneDDistribution>
      theta_importance_distribution( new Utility::HistogramDistribution(
								bin_boundaries,
								bin_values ) );

    // Create the spatial importance distribution 
    Teuchos::RCP<Utility::SpatialDistribution> spatial_importance_distribution(
       new Utility::SphericalSpatialDistribution( r_distribution,
						 theta_importance_distribution,
						 mu_distribution,
						 0.0,
						 0.0,
						 0.0 ) );

    // Create the directional importance distribution
    Teuchos::RCP<Utility::DirectionalDistribution>
      directional_importance_distribution( 
	   new Utility::SphericalDirectionalDistribution( 
						 theta_importance_distribution,
						 mu_distribution ) );

    // Create the energy importance distribution
    bin_boundaries[0] = 1e-3;
    bin_boundaries[1] = 1e-2;
    bin_boundaries[2] = 1e-1;
    bin_boundaries[3] = 1.0;
    
    bin_values[0] = 5.0;
    bin_values[1] = 2.0;
    bin_values[2] = 1.0;
    Teuchos::RCP<Utility::OneDDistribution>
      energy_importance_distribution( new Utility::HistogramDistribution(
								bin_boundaries,
								bin_values ) );
    
    Teuchos::RCP<MonteCarlo::DistributedSource> distributed_source = 
      Teuchos::rcp_dynamic_cast<MonteCarlo::DistributedSource>( source );
									     
    distributed_source->setSpatialImportanceDistribution( 
					     spatial_importance_distribution );
    distributed_source->setDirectionalImportanceDistribution( 
					 directional_importance_distribution );
    distributed_source->setEnergyImportanceDistribution( 
					      energy_importance_distribution );
  }

  // Set the rejection cell if requested
  if( set_rejection_cell )
  {
    Teuchos::RCP<MonteCarlo::DistributedSource> distributed_source = 
      Teuchos::rcp_dynamic_cast<MonteCarlo::DistributedSource>( source );

    // Cell (id=2) of the test geometry will be used as the rejection cell
    distributed_source->setRejectionCell( 2 );
  }
}

// Initialize DagMC
// Note: This function must be called before the initializeSource function
// when setting a rejection cell
void initializeDagMC()
{
  // Set up the valid property names
  std::vector<std::string> property_names( 1 );
  property_names[0] = "graveyard";

  Geometry::initializeDagMC( test_geometry_file_name,
			     property_names,
			     1e-3 );

  Geometry::ModuleInterface<moab::DagMC>::initialize();
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particle states can be sampled (no importance functions, no
// rejection cell )
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( DistributedSource,
				   sampleParticleState_no_importance_no_reject,
				   GeometryHandler )
{
  initializeSource<GeometryHandler>();
  
  MonteCarlo::ParticleBank bank;
  
  source->sampleParticleState( bank, 0 );
  
  MonteCarlo::ParticleState& particle = bank.top();
  
  TEST_EQUALITY_CONST( particle.getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY_CONST( particle.getHistoryNumber(), 0 );
  TEST_COMPARE( particle.getXPosition(), >=, -2.0 );
  TEST_COMPARE( particle.getXPosition(), <=, 2.0 );
  TEST_COMPARE( particle.getYPosition(), >=, -2.0 );
  TEST_COMPARE( particle.getYPosition(), <=, 2.0 );
  TEST_COMPARE( particle.getZPosition(), >=, -2.0 );
  TEST_COMPARE( particle.getZPosition(), <=, 2.0 );
  TEST_COMPARE( particle.getXDirection(), >=, -1.0 );
  TEST_COMPARE( particle.getXDirection(), <=, 1.0 );
  TEST_COMPARE( particle.getYDirection(), >=, -1.0 );
  TEST_COMPARE( particle.getYDirection(), <=, 1.0 );
  TEST_COMPARE( particle.getZDirection(), >=, -1.0 );
  TEST_COMPARE( particle.getZDirection(), <=, 1.0 );
  TEST_COMPARE( particle.getEnergy(), >=, 1e-3 );
  TEST_COMPARE( particle.getEnergy(), <=, 1.0 );
  TEST_EQUALITY_CONST( particle.getTime(), 0.0 );
  TEST_EQUALITY_CONST( particle.getWeight(), 1.0 );
}

UNIT_TEST_INSTANTIATION( DistributedSource, 
			 sampleParticleState_no_importance_no_reject );

//---------------------------------------------------------------------------//
// Check that particle states can be sampled (importance functions, no 
// rejection cells )
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( DistributedSource,
				   sampleParticleState_importance_no_reject,
				   GeometryHandler )
{
  initializeSource<GeometryHandler>( true );
  
  std::vector<double> fake_stream( 10 );
  fake_stream[0] = 0.0;
  fake_stream[1] = 0.0;
  fake_stream[2] = 0.0;
  fake_stream[3] = 0.0;
  fake_stream[4] = 0.0;
  fake_stream[5] = 0.0;
  fake_stream[6] = 0.0;
  fake_stream[7] = 0.0;
  fake_stream[8] = 0.0;
  fake_stream[9] = 0.0;

  Utility::RandomNumberGenerator::setFakeStream( fake_stream );

  MonteCarlo::ParticleBank bank;
  
  source->sampleParticleState( bank, 0 );

  MonteCarlo::ParticleState& particle = bank.top();
  
  TEST_EQUALITY_CONST( particle.getHistoryNumber(), 0 );
  TEST_EQUALITY_CONST( particle.getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY_CONST( particle.getXDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle.getYDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle.getZDirection(), -1.0 );
  TEST_EQUALITY_CONST( particle.getXPosition(), 0.0 );
  TEST_EQUALITY_CONST( particle.getYPosition(), 0.0 );
  TEST_EQUALITY_CONST( particle.getZPosition(), 0.0 );
  TEST_EQUALITY_CONST( particle.getEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( particle.getTime(), 0.0 );
  TEST_FLOATING_EQUALITY( particle.getWeight(), 0.3378378378375, 1e-9 );

  Utility::RandomNumberGenerator::unsetFakeStream();
}

UNIT_TEST_INSTANTIATION( DistributedSource, 
			 sampleParticleState_importance_no_reject );

//---------------------------------------------------------------------------//
// Check that particle states can be sampled (no importance functions,
// rejection cell )
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( DistributedSource,
				   sampleParticleState_no_importance_reject,
				   GeometryHandler )
{
  initializeSource<GeometryHandler>( false, true );
  
  MonteCarlo::ParticleBank bank;
  
  source->sampleParticleState( bank, 0 );

  MonteCarlo::ParticleState& particle = bank.top();
  
  TEST_EQUALITY_CONST( particle.getParticleType(), MonteCarlo::PHOTON );
  TEST_EQUALITY_CONST( particle.getHistoryNumber(), 0 );
  TEST_COMPARE( particle.getXPosition(), >=, -1.1547005383792 );
  TEST_COMPARE( particle.getXPosition(), <=, 1.1547005383792 );
  TEST_COMPARE( particle.getYPosition(), >=, -1.1547005383792 );
  TEST_COMPARE( particle.getYPosition(), <=, 1.1547005383792 );
  TEST_COMPARE( particle.getZPosition(), >=, -1.1547005383792 );
  TEST_COMPARE( particle.getZPosition(), <=, 1.1547005383792 );
  TEST_COMPARE( particle.getXDirection(), >=, -1.0 );
  TEST_COMPARE( particle.getXDirection(), <=, 1.0 );
  TEST_COMPARE( particle.getYDirection(), >=, -1.0 );
  TEST_COMPARE( particle.getYDirection(), <=, 1.0 );
  TEST_COMPARE( particle.getZDirection(), >=, -1.0 );
  TEST_COMPARE( particle.getZDirection(), <=, 1.0 );
  TEST_COMPARE( particle.getEnergy(), >=, 1e-3 );
  TEST_COMPARE( particle.getEnergy(), <=, 1.0 );
  TEST_EQUALITY_CONST( particle.getTime(), 0.0 );
  TEST_EQUALITY_CONST( particle.getWeight(), 1.0 );
}

UNIT_TEST_INSTANTIATION( DistributedSource, 
			 sampleParticleState_no_importance_reject );

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( DistributedSource,
				   getSamplingEfficiency,
				   GeometryHandler )
{
  initializeSource<GeometryHandler>( false, true );
  
  MonteCarlo::ParticleBank bank;
  
  // Conduct 10 samples
  for( unsigned i = 0; i < 10; ++i )
    source->sampleParticleState( bank, i );

  // Theoretical efficiency: (4/sqrt(3))^3/(4*pi*2^3/3) ~= 0.367552
  TEST_COMPARE( source->getSamplingEfficiency(), >, 0.0 );
  TEST_COMPARE( source->getSamplingEfficiency(), <=, 1.0 );
}

UNIT_TEST_INSTANTIATION( DistributedSource, getSamplingEfficiency );

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_sat_file",
		 &test_geometry_file_name,
		 "Test sat file name" );
  
  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  //Teuchos::UnitTestRepository::setUpCLP( Teuchos::outArg(clp) );

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);
  
  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }
  
  // Initialize DagMC with the test geometry
  initializeDagMC();

  Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  
  const bool success = Teuchos::UnitTestRepository::runUnitTests(*out);

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}

//---------------------------------------------------------------------------//
// end tstDistributedSource.cpp
//---------------------------------------------------------------------------//
