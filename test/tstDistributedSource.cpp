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

// FACEMC Includes
#include "ParticleState.hpp"
#include "DistributedSource.hpp"
#include "SphericalSpatialDistribution.hpp"
#include "PowerDistribution.hpp"
#include "UniformDistribution.hpp"
#include "DeltaDistribution.hpp"
#include "HistogramDistribution.hpp"
#include "PhysicalConstants.hpp"
#include "RandomNumberGenerator.hpp"
#include "DagMCHelpers.hpp"

Teuchos::RCP<FACEMC::ParticleSource> source;

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
  Teuchos::RCP<FACEMC::OneDDistribution> 
    r_distribution( new FACEMC::PowerDistribution<2u>( 3.0, 0.0, 2.0 ) );
  
  // Uniform distribution in theta dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    theta_distribution( new FACEMC::UniformDistribution( 
					       0.0,
					       2*FACEMC::PhysicalConstants::pi,
					       1.0 ) );
  // Uniform distribution in mu dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    mu_distribution( new FACEMC::UniformDistribution( -1.0, 1.0, 1.0 ) );

  // Create the spatial distribution
  Teuchos::RCP<FACEMC::SpatialDistribution>
    spatial_distribution( new FACEMC::SphericalSpatialDistribution( 
							    r_distribution,
							    theta_distribution,
							    mu_distribution,
							    0.0,
							    0.0,
							    0.0 ) );

  // Create the directional distribution
  Teuchos::RCP<FACEMC::DirectionalDistribution>
    directional_distribution( new FACEMC::DirectionalDistribution( 
							   theta_distribution,
							   mu_distribution ) );

  // Uniform distribution in energy dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    energy_distribution( new FACEMC::UniformDistribution( 1e-3, 1.0, 1.0 ) );

  // Delta distribution in time dimension
  Teuchos::RCP<FACEMC::OneDDistribution>
    time_distribution( new FACEMC::DeltaDistribution( 0.0 ) );

  // Create the distributed source
  source.reset( new FACEMC::DistributedSource<GeometryHandler>( 
						      spatial_distribution,
						      directional_distribution,
						      energy_distribution,
						      time_distribution,
						      FACEMC::PHOTON ) );

  // Set the importance functions if requested
  if( set_importance_functions )
  {
    // Uniform distribution in theta dimension
    Teuchos::Array<double> bin_boundaries( 4 );
    bin_boundaries[0] = 0.0;
    bin_boundaries[1] = FACEMC::PhysicalConstants::pi/2;
    bin_boundaries[2] = 3*FACEMC::PhysicalConstants::pi/2;
    bin_boundaries[3] = 2*FACEMC::PhysicalConstants::pi;

    Teuchos::Array<double> bin_values( 3 );
    bin_values[0] = 1.0;
    bin_values[1] = 2.0;
    bin_values[2] = 1.0;
    
    Teuchos::RCP<FACEMC::OneDDistribution>
      theta_importance_distribution( new FACEMC::HistogramDistribution(
								bin_boundaries,
								bin_values ) );

    // Create the spatial importance distribution 
    Teuchos::RCP<FACEMC::SpatialDistribution> spatial_importance_distribution( 
       new FACEMC::SphericalSpatialDistribution( r_distribution,
						 theta_importance_distribution,
						 mu_distribution,
						 0.0,
						 0.0,
						 0.0 ) );

    // Create the directional importance distribution
    Teuchos::RCP<FACEMC::DirectionalDistribution>
      directional_importance_distribution( 
	    new FACEMC::DirectionalDistribution( theta_importance_distribution,
						 mu_distribution ) );

    // Create the energy importance distribution
    bin_boundaries[0] = 1e-3;
    bin_boundaries[1] = 1e-2;
    bin_boundaries[2] = 1e-1;
    bin_boundaries[3] = 1.0;
    
    bin_values[0] = 5.0;
    bin_values[1] = 2.0;
    bin_values[2] = 1.0;
    Teuchos::RCP<FACEMC::OneDDistribution>
      energy_importance_distribution( new FACEMC::HistogramDistribution(
								bin_boundaries,
								bin_values ) );
    
    Teuchos::RCP<FACEMC::DistributedSource<GeometryHandler> >
      distributed_source = Teuchos::rcp_dynamic_cast<FACEMC::DistributedSource<GeometryHandler> >( source );
									     
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
    Teuchos::RCP<FACEMC::DistributedSource<GeometryHandler> >
      distributed_source = Teuchos::rcp_dynamic_cast<FACEMC::DistributedSource<GeometryHandler> >( source );

    // Cell (id=2) of the test geometry will be used as the rejection cell
    typename FACEMC::Traits::GeometryHandlerTraits<GeometryHandler>::CellHandle
      cell = FACEMC::Traits::GeometryHandlerTraits<GeometryHandler>::getCellHandle( 2 );
    distributed_source->setRejectionCell( cell );
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

  FACEMC::initializeDagMC( test_geometry_file_name,
			   property_names,
			   1e-3 );
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
  
  typedef FACEMC::Traits::GeometryHandlerTraits<GeometryHandler> GHT;

  FACEMC::ParticleState<typename GHT::CellHandle> particle_1( 1ull );

  source->sampleParticleState( particle_1 );
  
  TEST_EQUALITY_CONST( particle_1.getParticleType(), FACEMC::PHOTON );
  TEST_COMPARE( particle_1.getXPosition(), >=, -2.0 );
  TEST_COMPARE( particle_1.getXPosition(), <=, 2.0 );
  TEST_COMPARE( particle_1.getYPosition(), >=, -2.0 );
  TEST_COMPARE( particle_1.getYPosition(), <=, 2.0 );
  TEST_COMPARE( particle_1.getZPosition(), >=, -2.0 );
  TEST_COMPARE( particle_1.getZPosition(), <=, 2.0 );
  TEST_COMPARE( particle_1.getXDirection(), >=, -1.0 );
  TEST_COMPARE( particle_1.getXDirection(), <=, 1.0 );
  TEST_COMPARE( particle_1.getYDirection(), >=, -1.0 );
  TEST_COMPARE( particle_1.getYDirection(), <=, 1.0 );
  TEST_COMPARE( particle_1.getZDirection(), >=, -1.0 );
  TEST_COMPARE( particle_1.getZDirection(), <=, 1.0 );
  TEST_COMPARE( particle_1.getEnergy(), >=, 1e-3 );
  TEST_COMPARE( particle_1.getEnergy(), <=, 1.0 );
  TEST_EQUALITY_CONST( particle_1.getTime(), 0.0 );
  TEST_EQUALITY_CONST( particle_1.getWeight(), 1.0 );
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
  
  typedef FACEMC::Traits::GeometryHandlerTraits<GeometryHandler> GHT;

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

  FACEMC::RandomNumberGenerator::setFakeStream( fake_stream );

  FACEMC::ParticleState<typename GHT::CellHandle> particle_1( 1ull );

  source->sampleParticleState( particle_1 );
  
  TEST_EQUALITY_CONST( particle_1.getParticleType(), FACEMC::PHOTON );
  TEST_EQUALITY_CONST( particle_1.getXDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle_1.getYDirection(), 0.0 );
  TEST_EQUALITY_CONST( particle_1.getZDirection(), -1.0 );
  TEST_EQUALITY_CONST( particle_1.getXPosition(), 0.0 );
  TEST_EQUALITY_CONST( particle_1.getYPosition(), 0.0 );
  TEST_EQUALITY_CONST( particle_1.getZPosition(), 0.0 );
  TEST_EQUALITY_CONST( particle_1.getEnergy(), 1e-3 );
  TEST_EQUALITY_CONST( particle_1.getTime(), 0.0 );
  TEST_FLOATING_EQUALITY( particle_1.getWeight(), 0.3378378378375, 1e-9 );

  FACEMC::RandomNumberGenerator::unsetFakeStream();
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
  
  typedef FACEMC::Traits::GeometryHandlerTraits<GeometryHandler> GHT;

  FACEMC::ParticleState<typename GHT::CellHandle> particle_1( 1ull );

  source->sampleParticleState( particle_1 );
  
  TEST_EQUALITY_CONST( particle_1.getParticleType(), FACEMC::PHOTON );
  TEST_COMPARE( particle_1.getXPosition(), >=, -1.1547005383792 );
  TEST_COMPARE( particle_1.getXPosition(), <=, 1.1547005383792 );
  TEST_COMPARE( particle_1.getYPosition(), >=, -1.1547005383792 );
  TEST_COMPARE( particle_1.getYPosition(), <=, 1.1547005383792 );
  TEST_COMPARE( particle_1.getZPosition(), >=, -1.1547005383792 );
  TEST_COMPARE( particle_1.getZPosition(), <=, 1.1547005383792 );
  TEST_COMPARE( particle_1.getXDirection(), >=, -1.0 );
  TEST_COMPARE( particle_1.getXDirection(), <=, 1.0 );
  TEST_COMPARE( particle_1.getYDirection(), >=, -1.0 );
  TEST_COMPARE( particle_1.getYDirection(), <=, 1.0 );
  TEST_COMPARE( particle_1.getZDirection(), >=, -1.0 );
  TEST_COMPARE( particle_1.getZDirection(), <=, 1.0 );
  TEST_COMPARE( particle_1.getEnergy(), >=, 1e-3 );
  TEST_COMPARE( particle_1.getEnergy(), <=, 1.0 );
  TEST_EQUALITY_CONST( particle_1.getTime(), 0.0 );
  TEST_EQUALITY_CONST( particle_1.getWeight(), 1.0 );
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
  
  typedef FACEMC::Traits::GeometryHandlerTraits<GeometryHandler> GHT;

  FACEMC::ParticleState<typename GHT::CellHandle> particle_1( 1ull );
  
  // Conduct 10 samples
  for( unsigned i = 0; i < 10; ++i )
    source->sampleParticleState( particle_1 );

  TEST_COMPARE( source->getSamplingEfficiency(), >=, 0.0 );
  TEST_COMPARE( source->getSamplingEfficiency(), <=, 1.0 );

  std::cout << source->getSamplingEfficiency() << std::endl;
}

UNIT_TEST_INSTANTIATION( DistributedSource, getSamplingEfficiency );

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
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
