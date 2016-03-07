//---------------------------------------------------------------------------//
//!
//! \file   tstCompoundSource.cpp
//! \author Alex Robinson
//! \brief  Compound source unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// Boost Includes
#include <boost/bind.hpp>

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

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_DistributedSource.hpp"
#include "MonteCarlo_CompoundSource.hpp"
#include "Geometry_DagMCHelpers.hpp"
#include "Geometry_ModuleInterface.hpp"
#include "Utility_SphericalSpatialDistribution.hpp"
#include "Utility_CartesianSpatialDistribution.hpp"
#include "Utility_SphericalDirectionalDistribution.hpp"
#include "Utility_PowerDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_RandomNumberGenerator.hpp"

std::shared_ptr<MonteCarlo::ParticleSource> source;

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
  
  Geometry::initializeDagMC( test_geometry_file_name,
			     property_names,
			     1e-3 );

  Geometry::ModuleInterface<moab::DagMC>::initialize();
}

// Initialize the compound source (uniform spherical source and point source)
template<typename GeometryHandler>
void initializeSource()
{
  // Create the distributions required for each source
  std::shared_ptr<Utility::OneDDistribution>
    r_distribution( new Utility::PowerDistribution<2u>( 3.0, 0.0, 2.0 ) );
  std::shared_ptr<Utility::OneDDistribution>
    theta_distribution( new Utility::UniformDistribution( 
					      0.0,
					      2*Utility::PhysicalConstants::pi,
					      1.0 ) );
  std::shared_ptr<Utility::OneDDistribution>
    mu_distribution( new Utility::UniformDistribution( -1.0, 1.0, 1.0 ) );

  std::shared_ptr<Utility::SpatialDistribution>
    source_1_spatial_distribution( new Utility::SphericalSpatialDistribution(
							    r_distribution,
							    theta_distribution,
							    mu_distribution,
							    0.0,
							    0.0,
							    0.0 ) );
  std::shared_ptr<Utility::DirectionalDistribution>
    directional_distribution( new Utility::SphericalDirectionalDistribution( 
							   theta_distribution,
							   mu_distribution ) );

  std::shared_ptr<Utility::OneDDistribution>
    source_1_energy_distribution( new Utility::UniformDistribution( 1e-3, 
								   1.0, 
								   1.0 ) );
  std::shared_ptr<Utility::OneDDistribution>
    time_distribution( new Utility::DeltaDistribution( 0.0 ) );

  std::shared_ptr<Utility::OneDDistribution>
    x_distribution( new Utility::DeltaDistribution( 0.0 ) );
  std::shared_ptr<Utility::OneDDistribution>
    y_distribution( new Utility::DeltaDistribution( 0.0 ) );
  std::shared_ptr<Utility::OneDDistribution>
    z_distribution( new Utility::DeltaDistribution( 0.0 ) );

  std::shared_ptr<Utility::SpatialDistribution>
    source_2_spatial_distribution( new Utility::CartesianSpatialDistribution(
							    x_distribution,
							    y_distribution,
							    z_distribution ) );
  std::shared_ptr<Utility::OneDDistribution>
    source_2_energy_distribution( new Utility::DeltaDistribution( 14.1 ) );
  
  // Create the uniform spherical source
  std::shared_ptr<MonteCarlo::DistributedSource> spherical_source( 
     new MonteCarlo::DistributedSource(
	      0u,
	      source_1_spatial_distribution,
	      directional_distribution,
	      source_1_energy_distribution,
	      time_distribution,
              MonteCarlo::PHOTON,
              &Geometry::ModuleInterface<GeometryHandler>::getPointLocation) );
  
  spherical_source->setRejectionCell( 2 );

  // Create the point source
  std::shared_ptr<MonteCarlo::ParticleSource> point_source( 
     new MonteCarlo::DistributedSource(
	      1u,
              source_2_spatial_distribution,
	      directional_distribution,
	      source_2_energy_distribution,
	      time_distribution,
              MonteCarlo::NEUTRON,
              &Geometry::ModuleInterface<GeometryHandler>::getPointLocation) );

  Teuchos::Array<std::shared_ptr<MonteCarlo::ParticleSource> > sources( 2 );
  sources[0] = std::dynamic_pointer_cast<MonteCarlo::ParticleSource>( 
							    spherical_source );
  sources[1] = point_source;

  Teuchos::Array<double> source_weights( 2 );
  source_weights[0] = 0.5;
  source_weights[1] = 0.5;

  // Create the compound source
  source.reset( new MonteCarlo::CompoundSource( sources, source_weights ) );  
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

  MonteCarlo::ParticleBank bank;
  
  source->sampleParticleState( bank, 0 );

  TEST_ASSERT( bank.top().getParticleType() == MonteCarlo::PHOTON ||
	       bank.top().getParticleType() == MonteCarlo::NEUTRON );
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0 );
  TEST_COMPARE( bank.top().getXPosition(), >=, -2.0 );
  TEST_COMPARE( bank.top().getXPosition(), <=, 2.0 );
  TEST_COMPARE( bank.top().getYPosition(), >=, -2.0 );
  TEST_COMPARE( bank.top().getYPosition(), <=, 2.0 );
  TEST_COMPARE( bank.top().getZPosition(), >=, -2.0 );
  TEST_COMPARE( bank.top().getZPosition(), <=, 2.0 );
  TEST_COMPARE( bank.top().getXDirection(), >=, -1.0 );
  TEST_COMPARE( bank.top().getXDirection(), <=, 1.0 );
  TEST_COMPARE( bank.top().getYDirection(), >=, -1.0 );
  TEST_COMPARE( bank.top().getYDirection(), <=, 1.0 );
  TEST_COMPARE( bank.top().getZDirection(), >=, -1.0 );
  TEST_COMPARE( bank.top().getZDirection(), <=, 1.0 );
  TEST_COMPARE( bank.top().getEnergy(), >=, 1e-3 );
  TEST_ASSERT( bank.top().getEnergy() <= 1.0 ||
	       bank.top().getEnergy() == 14.1 );
  TEST_EQUALITY_CONST( bank.top().getTime(), 0.0 );
  TEST_EQUALITY_CONST( bank.top().getWeight(), 1.0 );
}

UNIT_TEST_INSTANTIATION( CompoundSource, sampleParticleState );

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST_TEMPLATE_1_DECL( CompoundSource,
				   getSamplingEfficiency,
				   GeometryHandler )
{
  initializeSource<GeometryHandler>();

  MonteCarlo::ParticleBank bank;
  
  // Conduct 10 samples
  for( unsigned i = 0; i < 10; ++i )
    source->sampleParticleState( bank, i );

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
// end tstCompoundSource.cpp
//---------------------------------------------------------------------------//

