//---------------------------------------------------------------------------//
//!
//!
//! \file   tstCompoundSource.cpp
//! \author Alex Robinson
//! \brief  Compound source unit tests
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
#include <Teuchos_Array.hpp>

// Moab Includes
#include <moab/EntityHandle.hpp>
#include <DagMC.hpp>

// FACEMC Includes
#include "ParticleState.hpp"
#include "DistributedSource.hpp"
#include "CompoundSource.hpp"
#include "SphericalSpatialDistribution.hpp"
#include "CartesianSpatialDistribution.hpp"
#include "PowerDistribution.hpp"
#include "UniformDistribution.hpp"
#include "DeltaDistribution.hpp"
#include "HistogramDistribution.hpp"
#include "PhysicalConstants.hpp"
#include "RandomNumberGenerator.hpp"
#include "DagMCHelpers.hpp"
#include "GeometryModuleInterface.hpp"

Teuchos::RCP<FACEMC::ParticleSource> source;

//---------------------------------------------------------------------------//
// Test Sat File Name
//---------------------------------------------------------------------------//
std::string test_geometry_file_name;

//---------------------------------------------------------------------------//
// Instantiation Macros.
//---------------------------------------------------------------------------//
#define UNIT_TEST_INSTANTIATION( type, name )			\
  typedef moab::DagMC dagmc;					\
  TEUCHOS_UNIT_TEST_TEMPLATE_1_INSTANT( type, name, dagmc ) 

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
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

// Initialize the compound source (uniform spherical source and point source)
template<typename GeometryHandler>
void initializeSource()
{
  // Create the distributions required for each source
  Teuchos::RCP<FACEMC::OneDDistribution>
    r_distribution( new FACEMC::PowerDistribution<2u>( 3.0, 0.0, 2.0 ) );
  Teuchos::RCP<FACEMC::OneDDistribution>
    theta_distribution( new FACEMC::UniformDistribution( 
					       0.0,
					       2*FACEMC::PhysicalConstants::pi,
					       1.0 ) );
  Teuchos::RCP<FACEMC::OneDDistribution>
    mu_distribution( new FACEMC::UniformDistribution( -1.0, 1.0, 1.0 ) );

  Teuchos::RCP<FACEMC::SpatialDistribution>
    source_1_spatial_distribution( new FACEMC::SphericalSpatialDistribution(
							    r_distribution,
							    theta_distribution,
							    mu_distribution,
							    0.0,
							    0.0,
							    0.0 ) );
  Teuchos::RCP<FACEMC::DirectionalDistribution>
    directional_distribution( new FACEMC::DirectionalDistribution( 
							   theta_distribution,
							   mu_distribution ) );

  Teuchos::RCP<FACEMC::OneDDistribution>
    source_1_energy_distribution( new FACEMC::UniformDistribution( 1e-3, 
								   1.0, 
								   1.0 ) );
  Teuchos::RCP<FACEMC::OneDDistribution>
    time_distribution( new FACEMC::DeltaDistribution( 0.0 ) );

  Teuchos::RCP<FACEMC::OneDDistribution>
    x_distribution( new FACEMC::DeltaDistribution( 0.0 ) );
  Teuchos::RCP<FACEMC::OneDDistribution>
    y_distribution( new FACEMC::DeltaDistribution( 0.0 ) );
  Teuchos::RCP<FACEMC::OneDDistribution>
    z_distribution( new FACEMC::DeltaDistribution( 0.0 ) );

  Teuchos::RCP<FACEMC::SpatialDistribution>
    source_2_spatial_distribution( new FACEMC::CartesianSpatialDistribution(
							    x_distribution,
							    y_distribution,
							    z_distribution ) );
  Teuchos::RCP<FACEMC::OneDDistribution>
    source_2_energy_distribution( new FACEMC::DeltaDistribution( 14.1 ) );
  
  // Create the uniform spherical source
  Teuchos::RCP<FACEMC::DistributedSource> spherical_source( 
   new FACEMC::DistributedSource(
     source_1_spatial_distribution,
     directional_distribution,
     source_1_energy_distribution,
     time_distribution,
     FACEMC::PHOTON,
     &FACEMC::GeometryModuleInterface<GeometryHandler>::getParticleLocation) );
  
  spherical_source->setRejectionCell( 2 );

  // Create the point source
  Teuchos::RCP<FACEMC::ParticleSource> 
    point_source( new FACEMC::DistributedSource(
     source_2_spatial_distribution,
     directional_distribution,
     source_2_energy_distribution,
     time_distribution,
     FACEMC::NEUTRON,
     &FACEMC::GeometryModuleInterface<GeometryHandler>::getParticleLocation) );

  Teuchos::Array<Teuchos::RCP<FACEMC::ParticleSource> > sources( 2 );
  sources[0] = Teuchos::rcp_dynamic_cast<FACEMC::ParticleSource>( 
							    spherical_source );
  sources[1] = point_source;

  Teuchos::Array<double> source_weights( 2 );
  source_weights[0] = 0.5;
  source_weights[1] = 0.5;

  // Create the compound source
  source.reset( new FACEMC::CompoundSource( sources, source_weights ) );  
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particle states can be sampled
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CompoundSource,
				   sampleParticleState,
				   GeometryHandler )
{
  initializeSource<GeometryHandler>();

  FACEMC::ParticleBank bank;
  
  source->sampleParticleState( bank );

  TEST_ASSERT( bank.top()->getParticleType() == FACEMC::PHOTON ||
	       bank.top()->getParticleType() == FACEMC::NEUTRON );
  
  TEST_COMPARE( bank.top()->getXPosition(), >=, -2.0 );
  TEST_COMPARE( bank.top()->getXPosition(), <=, 2.0 );
  TEST_COMPARE( bank.top()->getYPosition(), >=, -2.0 );
  TEST_COMPARE( bank.top()->getYPosition(), <=, 2.0 );
  TEST_COMPARE( bank.top()->getZPosition(), >=, -2.0 );
  TEST_COMPARE( bank.top()->getZPosition(), <=, 2.0 );
  TEST_COMPARE( bank.top()->getXDirection(), >=, -1.0 );
  TEST_COMPARE( bank.top()->getXDirection(), <=, 1.0 );
  TEST_COMPARE( bank.top()->getYDirection(), >=, -1.0 );
  TEST_COMPARE( bank.top()->getYDirection(), <=, 1.0 );
  TEST_COMPARE( bank.top()->getZDirection(), >=, -1.0 );
  TEST_COMPARE( bank.top()->getZDirection(), <=, 1.0 );
  TEST_COMPARE( bank.top()->getEnergy(), >=, 1e-3 );
  TEST_ASSERT( bank.top()->getEnergy() <= 1.0 ||
	       bank.top()->getEnergy() == 14.1 );
  TEST_EQUALITY_CONST( bank.top()->getTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top()->getWeight(), 1.0 );
}

UNIT_TEST_INSTANTIATION( CompoundSource, sampleParticleState );

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CompoundSource,
				   getSamplingEfficiency,
				   GeometryHandler )
{
  initializeSource<GeometryHandler>();

  FACEMC::ParticleBank bank;
  
  // Conduct 10 samples
  for( unsigned i = 0; i < 10; ++i )
    source->sampleParticleState( bank );

  // Theoretical efficiency: eff_a*eff_b/(p_a*eff_b+p_b*eff_a)
  // eff_a = (4/sqrt(3))^3/(4*pi*2^3/3) ~= 0.367552
  TEST_COMPARE( source->getSamplingEfficiency(), >, 0.0 );
  TEST_COMPARE( source->getSamplingEfficiency(), <=, 1.0 );
}

UNIT_TEST_INSTANTIATION( CompoundSource, getSamplingEfficiency );

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
// end tstCompoundSource.cpp
//---------------------------------------------------------------------------//

