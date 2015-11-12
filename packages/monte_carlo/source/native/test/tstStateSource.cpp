//---------------------------------------------------------------------------//
//! 
//! \file   tstStateSource.cpp
//! \author Alex Robinson
//! \brief  State source unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// Boost Includes
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/nvp.hpp>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_VerboseObject.hpp>

// FRENSIE Includes
#include "MonteCarlo_StateSource.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Utility_RandomNumberGenerator.hpp"

//---------------------------------------------------------------------------//
// Testing variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ParticleSource> source;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that particle states can be "sampled"
TEUCHOS_UNIT_TEST( StateSource, sampleParticleState )
{
  MonteCarlo::ParticleBank bank;
  source->sampleParticleState( bank, 0 );

  TEST_EQUALITY_CONST( bank.size(), 2 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  
  bank.pop();
    
  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 0ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::PHOTON );
  
  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 1 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 1ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::NEUTRON );
  
  bank.pop();

  // Sample from the source again
  source->sampleParticleState( bank, 2 );

  TEST_EQUALITY_CONST( bank.size(), 1 );

  TEST_EQUALITY_CONST( bank.top().getHistoryNumber(), 2ull );
  TEST_EQUALITY_CONST( bank.top().getParticleType(), MonteCarlo::ELECTRON );
  
  bank.pop();

  // Attempting to get another particle state should cause an exception
  TEST_THROW( source->sampleParticleState( bank, 3 ), std::runtime_error );
}

//---------------------------------------------------------------------------//
// Check that the sampling efficiency can be returned
TEUCHOS_UNIT_TEST( StateSource, getSamplingEfficiency )
{
  TEST_EQUALITY_CONST( source->getSamplingEfficiency(), 1.0 );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_dists_xml_file;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  const Teuchos::RCP<Teuchos::FancyOStream> out = 
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return = 
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  // Initialize the source
  {
    MonteCarlo::ParticleBank bank;
    
    boost::shared_ptr<MonteCarlo::ParticleState> particle( 
					 new MonteCarlo::PhotonState( 1ull ) );

    bank.push( *particle );

    particle.reset( new MonteCarlo::NeutronState( 10ull ) );

    bank.push( *particle );

    particle.reset( new MonteCarlo::PhotonState( 1ull ) );

    bank.push( *particle );

    particle.reset( new MonteCarlo::ElectronState( 11ull ) );

    bank.push( *particle );

    std::string bank_archive_name( "test_state_source_bank_archive.xml" );
    std::string bank_name_in_archive( "state_bank" );
 
    {
      std::ofstream ofs( bank_archive_name.c_str() );

      boost::archive::xml_oarchive ar(ofs);
      ar << boost::serialization::make_nvp( bank_name_in_archive.c_str(), bank );
    }

    source.reset( new MonteCarlo::StateSource( 
				    bank_archive_name,
				    bank_name_in_archive,
				    Utility::ArchivableObject::XML_ARCHIVE ) );
  }
  
  // Initialize the random number generator
  Utility::RandomNumberGenerator::createStreams();
  
  // Run the unit tests
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
// end tstStateSource.cpp
//---------------------------------------------------------------------------//
