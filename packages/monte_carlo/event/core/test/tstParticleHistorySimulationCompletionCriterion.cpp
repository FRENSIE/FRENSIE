//---------------------------------------------------------------------------//
//!
//! \file   tstParticleHistorySimulationCompletionCriterion.cpp
//! \author Alex Robinson
//! \brief  Particle history simulation completion criterion tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <sstream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleHistorySimulationCompletionCriterion.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that a history count criterion can be constructed
FRENSIE_UNIT_TEST( HistoryCountParticleHistorySimulationCompletionCriterion,
                   constructor )
{
  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion;

  FRENSIE_REQUIRE_NO_THROW( criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createHistoryCountCriterion( 10 ) );
}

//---------------------------------------------------------------------------//
// Check that a history count criterion can collect data
FRENSIE_UNIT_TEST( HistoryCountParticleHistorySimulationCompletionCriterion,
                   collect_data )
{
  // Set history wall to be > 2^32 so that the history wall is guaranteed to be checked against a 64 bit variable that represents the number of completed histories
  uint64_t history_wall = 5000000000;

  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createHistoryCountCriterion( history_wall );


  FRENSIE_CHECK( !criterion->isSimulationComplete() );
  FRENSIE_CHECK( criterion->hasUncommittedHistoryContribution() );

  // If the criterion hasn't been started all data accumulation will be ignored
  for( size_t i = 0; i <= history_wall; ++i )
    criterion->commitHistoryContribution();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
  
  criterion->start();

  for( size_t i = 0; i <= history_wall; ++i )
    criterion->commitHistoryContribution();

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->resetData();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  // If the criterion has been stopped all data accumulation will be ignored
  criterion->stop();

  for( size_t i = 0; i <= history_wall; ++i )
    criterion->commitHistoryContribution();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
}

//---------------------------------------------------------------------------//
// Check that a history count criterion can collect data with multiple threads
FRENSIE_UNIT_TEST( HistoryCountParticleHistorySimulationCompletionCriterion,
                   collect_data_thread_safe )
{
  unsigned threads =
    Utility::OpenMPProperties::getRequestedNumberOfThreads();
  
  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createHistoryCountCriterion( 2*threads - 1 );

  criterion->enableThreadSupport( threads );  

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
  FRENSIE_CHECK( criterion->hasUncommittedHistoryContribution() );

  // If the criterion hasn't been started all data accumulation will be ignored
  #pragma omp parallel num_threads( threads )
  {
    criterion->commitHistoryContribution();
    criterion->commitHistoryContribution();
  }

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
  
  criterion->start();

  #pragma omp parallel num_threads( threads )
  {
    criterion->commitHistoryContribution();
    criterion->commitHistoryContribution();
  }

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->resetData();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  // If the criterion has been stopped all data accumulation will be ignored
  criterion->stop();

  #pragma omp parallel num_threads( threads )
  {
    criterion->commitHistoryContribution();
    criterion->commitHistoryContribution();
  }

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
}

//---------------------------------------------------------------------------//
// Check that a distributed history count criterion can be reduced
FRENSIE_UNIT_TEST( HistoryCountParticleHistorySimulationCompletionCriterion,
                   reduceData )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createHistoryCountCriterion( 2*comm->size() - 1 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
  FRENSIE_CHECK( criterion->hasUncommittedHistoryContribution() );
  
  // If the criterion hasn't been started all data accumulation will be ignored
  criterion->commitHistoryContribution();
  criterion->commitHistoryContribution();

  criterion->reduceData( *comm, 0 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
  
  criterion->start();

  criterion->commitHistoryContribution();
  criterion->commitHistoryContribution();

  criterion->reduceData( *comm, 0 );
  
  if( comm->rank() == 0 )
  {
    FRENSIE_CHECK( criterion->isSimulationComplete() );
  }
  else
  {
    FRENSIE_CHECK( !criterion->isSimulationComplete() );
  }
  
  criterion->resetData();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  // If the criterion has been stopped all data accumulation will be ignored
  criterion->stop();

  criterion->commitHistoryContribution();
  criterion->commitHistoryContribution();

  criterion->reduceData( *comm, 0 );
  
  FRENSIE_CHECK( !criterion->isSimulationComplete() );
}

//---------------------------------------------------------------------------//
// Check that a summary of the history count criterion can be printed
FRENSIE_UNIT_TEST( HistoryCountParticleHistorySimulationCompletionCriterion,
                   printSummary )
{
  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createHistoryCountCriterion( 10 );

  std::ostringstream oss;

  FRENSIE_REQUIRE_NO_THROW( criterion->printSummary( oss ) );

  std::cout << oss.str() << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a summary of the history count criterion can be printed
FRENSIE_UNIT_TEST( HistoryCountParticleHistorySimulationCompletionCriterion,
                   logSummary )
{
  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createHistoryCountCriterion( 10 );

  FRENSIE_REQUIRE_NO_THROW( criterion->logSummary() );
}

//---------------------------------------------------------------------------//
// Check that a wall time criterion can be constructed
FRENSIE_UNIT_TEST( WallTimeParticleHistorySimulationCompletionCriterion,
                   constructor )
{
  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion;

  FRENSIE_REQUIRE_NO_THROW( criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createWallTimeCriterion( 300.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a wall time criterion can collect data
FRENSIE_UNIT_TEST( WallTimeParticleHistorySimulationCompletionCriterion,
                   collect_data )
{
  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createWallTimeCriterion( 0.01 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
  FRENSIE_CHECK( !criterion->hasUncommittedHistoryContribution() );

  std::shared_ptr<Utility::Timer> timer =
    Utility::GlobalMPISession::createTimer();

  timer->start();

  unsigned i = 0;
  
  // If the criterion hasn't been started all data accumulation will be ignored
  while( timer->elapsed().count() < 0.02 )
  {
    if( timer->elapsed().count()*1000 > i )
    {
      criterion->commitHistoryContribution();
      ++i;
    }
  }

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  timer->stop();

  timer = Utility::GlobalMPISession::createTimer();
  timer->start();
  criterion->start();

  i = 0;
  
  while( timer->elapsed().count() < 0.02 )
  {
    if( timer->elapsed().count()*1000 > i )
    {
      criterion->commitHistoryContribution();
      ++i;
    }
  }

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->resetData();

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->clearCache();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  // If the criterion has been stopped all data accumulation will be ignored
  criterion->stop();

  timer = Utility::GlobalMPISession::createTimer();
  timer->start();

  i = 0;
  
  while( timer->elapsed().count() < 0.02 )
  {
    if( timer->elapsed().count()*1000 > i )
    {
      criterion->commitHistoryContribution();
      ++i;
    }
  }

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
}

//---------------------------------------------------------------------------//
// Check that a wall time criterion can collect data with multiple threads
FRENSIE_UNIT_TEST( WallTimeParticleHistorySimulationCompletionCriterion,
                   collect_data_thread_safe )
{
  unsigned threads =
    Utility::OpenMPProperties::getRequestedNumberOfThreads();
  
  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createWallTimeCriterion( 0.01 );

  criterion->enableThreadSupport( threads );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
  FRENSIE_CHECK( !criterion->hasUncommittedHistoryContribution() );

  std::shared_ptr<Utility::Timer> timer =
    Utility::GlobalMPISession::createTimer();

  timer->start();

  unsigned i = 0;
  
  // If the criterion hasn't been started all data accumulation will be ignored
  while( timer->elapsed().count() < 0.02 )
  {
    if( timer->elapsed().count()*1000 > i )
    {
      #pragma omp parallel num_threads( threads )
      {
        criterion->commitHistoryContribution();
        criterion->commitHistoryContribution();
      }
      
      ++i;
    }
  }

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  timer->stop();

  timer = Utility::GlobalMPISession::createTimer();
  timer->start();
  criterion->start();

  i = 0;
  
  while( timer->elapsed().count() < 0.02 )
  {
    if( timer->elapsed().count()*1000 > i )
    {
      #pragma omp parallel num_threads( threads )
      {
        criterion->commitHistoryContribution();
        criterion->commitHistoryContribution();
      }

      ++i;
    }
  }

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->resetData();

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->clearCache();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  // If the criterion has been stopped all data accumulation will be ignored
  criterion->stop();

  timer = Utility::GlobalMPISession::createTimer();
  timer->start();

  i = 0;
  
  while( timer->elapsed().count() < 0.02 )
  {
    if( timer->elapsed().count()*1000 > i )
    {
      #pragma omp parallel num_threads( threads )
      {
        criterion->commitHistoryContribution();
        criterion->commitHistoryContribution();
      }

      ++i;
    }
  }

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
}

//---------------------------------------------------------------------------//
// Check that a distributed wall time criterion can be reduced
FRENSIE_UNIT_TEST( WallTimeParticleHistorySimulationCompletionCriterion,
                   reduceData )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createWallTimeCriterion( 0.01 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
  FRENSIE_CHECK( !criterion->hasUncommittedHistoryContribution() );

  std::shared_ptr<Utility::Timer> timer =
    Utility::GlobalMPISession::createTimer();

  timer->start();

  unsigned i = 0;
  
  // If the criterion hasn't been started all data accumulation will be ignored
  while( timer->elapsed().count() < 0.02 )
  {
    if( timer->elapsed().count()*1000 > i )
    {
      criterion->commitHistoryContribution();
      ++i;
    }
  }

  criterion->reduceData( *comm, 0 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  timer->stop();

  timer = Utility::GlobalMPISession::createTimer();
  timer->start();
  criterion->start();

  i = 0;
  
  while( timer->elapsed().count() < 0.02 )
  {
    if( timer->elapsed().count()*1000 > i )
    {
      criterion->commitHistoryContribution();
      ++i;
    }
  }

  criterion->reduceData( *comm, 0 );

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->resetData();

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->clearCache();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  // If the criterion has been stopped all data accumulation will be ignored
  criterion->stop();

  timer = Utility::GlobalMPISession::createTimer();
  timer->start();

  i = 0;
  
  while( timer->elapsed().count() < 0.02 )
  {
    if( timer->elapsed().count()*1000 > i )
    {
      criterion->commitHistoryContribution();
      ++i;
    }
  }

  criterion->reduceData( *comm, 0 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
}

//---------------------------------------------------------------------------//
// Check that a summary of a wall time criterion can be printed
FRENSIE_UNIT_TEST( WallTimeParticleHistorySimulationCompletionCriterion,
                   printSummary )
{
  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createWallTimeCriterion( 0.01 );

  std::ostringstream oss;

  FRENSIE_REQUIRE_NO_THROW( criterion->printSummary( oss ) );

  std::cout << oss.str() << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a summary of a wall time criterion can be logged
FRENSIE_UNIT_TEST( WallTimeParticleHistorySimulationCompletionCriterion,
                   logSummary )
{
  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createWallTimeCriterion( 0.01 );

  FRENSIE_REQUIRE_NO_THROW( criterion->logSummary() );
}

//---------------------------------------------------------------------------//
// Check that a mixed criterion can be constructed
FRENSIE_UNIT_TEST( MixedHistorySimulationCompletionCriterion,
                   constructor )
{
  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion;

  FRENSIE_REQUIRE_NO_THROW( criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createMixedCriterion( 10, 300.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a mixed criterion can collect data
FRENSIE_UNIT_TEST( MixedHistorySimulationCompletionCriterion,
                   collect_data )
{
  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createMixedCriterion( 10, 0.01 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
  FRENSIE_CHECK( criterion->hasUncommittedHistoryContribution() );

  // If the criterion hasn't been started all data accumulation will be ignored
  for( size_t i = 0; i <= 10; ++i )
    criterion->commitHistoryContribution();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  std::shared_ptr<Utility::Timer> timer =
    Utility::GlobalMPISession::createTimer();

  timer->start();
  
  while( timer->elapsed().count() < 0.02 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  timer->stop();
  
  criterion->start();

  for( size_t i = 0; i <= 10; ++i )
    criterion->commitHistoryContribution();

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->clearCache();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  timer = Utility::GlobalMPISession::createTimer();
  timer->start();
  criterion->start();

  while( timer->elapsed().count() < 0.02 );

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->clearCache();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  // If the criterion has been stopped all data accumulation will be ignored
  criterion->stop();

  for( size_t i = 0; i <= 10; ++i )
    criterion->commitHistoryContribution();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  timer = Utility::GlobalMPISession::createTimer();
  timer->start();
  
  while( timer->elapsed().count() < 0.02 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
}

//---------------------------------------------------------------------------//
// Check that a mixed time criterion can collect data with multiple threads
FRENSIE_UNIT_TEST( MixedParticleHistorySimulationCompletionCriterion,
                   collect_data_thread_safe )
{
  unsigned threads =
    Utility::OpenMPProperties::getRequestedNumberOfThreads();

  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createMixedCriterion( 2*threads - 1, 0.01 );

  criterion->enableThreadSupport( threads );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
  FRENSIE_CHECK( criterion->hasUncommittedHistoryContribution() );

  // If the criterion hasn't been started all data accumulation will be ignored
  #pragma omp parallel num_threads( threads )
  {
    criterion->commitHistoryContribution();
    criterion->commitHistoryContribution();
  }

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
  
  std::shared_ptr<Utility::Timer> timer =
    Utility::GlobalMPISession::createTimer();

  timer->start();
  
  while( timer->elapsed().count() < 0.02 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  timer->stop();
  
  criterion->start();

  #pragma omp parallel num_threads( threads )
  {
    criterion->commitHistoryContribution();
    criterion->commitHistoryContribution();
  }

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->clearCache();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  timer = Utility::GlobalMPISession::createTimer();
  timer->start();
  criterion->start();

  while( timer->elapsed().count() < 0.02 );

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->clearCache();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  // If the criterion has been stopped all data accumulation will be ignored
  criterion->stop();

  #pragma omp parallel num_threads( threads )
  {
    criterion->commitHistoryContribution();
    criterion->commitHistoryContribution();
  }

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  timer = Utility::GlobalMPISession::createTimer();
  timer->start();
  
  while( timer->elapsed().count() < 0.02 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
}

//---------------------------------------------------------------------------//
// Check that a mixed criterion can be reduced
FRENSIE_UNIT_TEST( MixedParticleHistorySimulationCompletionCriterion,
                   reduceData )
{
  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createMixedCriterion( 2*comm->size() - 1, 0.01 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
  FRENSIE_CHECK( criterion->hasUncommittedHistoryContribution() );

  // If the criterion hasn't been started all data accumulation will be ignored
  criterion->commitHistoryContribution();
  criterion->commitHistoryContribution();

  criterion->reduceData( *comm, 0 );
  
  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  std::shared_ptr<Utility::Timer> timer =
    Utility::GlobalMPISession::createTimer();

  timer->start();
  
  while( timer->elapsed().count() < 0.02 );

  criterion->reduceData( *comm, 0 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  timer->stop();
  
  criterion->start();

  criterion->commitHistoryContribution();
  criterion->commitHistoryContribution();

  criterion->reduceData( *comm, 0 );

  if( comm->rank() == 0 )
  {
    FRENSIE_CHECK( criterion->isSimulationComplete() );
  }
  else
  {
    FRENSIE_CHECK( !criterion->isSimulationComplete() );
  }

  criterion->clearCache();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  timer = Utility::GlobalMPISession::createTimer();
  timer->start();
  criterion->start();

  while( timer->elapsed().count() < 0.02 );

  criterion->reduceData( *comm, 0 );

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->clearCache();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  // If the criterion has been stopped all data accumulation will be ignored
  criterion->stop();

  criterion->commitHistoryContribution();
  criterion->commitHistoryContribution();

  criterion->reduceData( *comm, 0 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  timer = Utility::GlobalMPISession::createTimer();
  timer->start();
  
  while( timer->elapsed().count() < 0.02 );

  criterion->reduceData( *comm, 0 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
}

//---------------------------------------------------------------------------//
// Check that a summary of the mixed criterion can be printed
FRENSIE_UNIT_TEST( MixedParticleHistorySimulationCompletionCriterion,
                   printSummary )
{
  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createMixedCriterion( 10, 0.01 );

  std::ostringstream oss;

  FRENSIE_REQUIRE_NO_THROW( criterion->printSummary( oss ) );

  std::cout << oss.str() << std::endl;
}

//---------------------------------------------------------------------------//
// Check that a summary of the mixed criterion can be printed
FRENSIE_UNIT_TEST( MixedParticleHistorySimulationCompletionCriterion,
                   logSummary )
{
  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createMixedCriterion( 10, 0.01 );

  FRENSIE_REQUIRE_NO_THROW( criterion->logSummary() );
}

//---------------------------------------------------------------------------//
// Check that a custom mixed criterion can be created
FRENSIE_UNIT_TEST( MixedParticleHistorySimulationCompletionCriterion,
                   create_custom_or )
{
  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion_a = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createHistoryCountCriterion( 10 );

  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion_b = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createWallTimeCriterion( 0.01 );

  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion;

  FRENSIE_REQUIRE_NO_THROW( criterion = criterion_a || criterion_b );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
  FRENSIE_CHECK( criterion->hasUncommittedHistoryContribution() );

  criterion->start();

  for( size_t i = 0; i <= 10; ++i )
    criterion->commitHistoryContribution();

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->clearCache();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  std::shared_ptr<Utility::Timer> timer =
    Utility::GlobalMPISession::createTimer();
  
  timer->start();
  criterion->start();

  while( timer->elapsed().count() < 0.02 );

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->clearCache();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  criterion->stop();
}

//---------------------------------------------------------------------------//
// Check that a custom mixed criterion can be created
FRENSIE_UNIT_TEST( MixedParticleHistorySimulationCompletionCriterion,
                   create_custom_and )
{
  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion_a = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createHistoryCountCriterion( 10 );

  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion_b = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createWallTimeCriterion( 0.01 );

  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion;

  FRENSIE_REQUIRE_NO_THROW( criterion = criterion_a && criterion_b );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );
  FRENSIE_CHECK( criterion->hasUncommittedHistoryContribution() );

  std::shared_ptr<Utility::Timer> timer =
    Utility::GlobalMPISession::createTimer();
  
  timer->start();
  criterion->start();

  while( timer->elapsed().count() < 0.02 );

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  for( size_t i = 0; i <= 10; ++i )
    criterion->commitHistoryContribution();

  FRENSIE_CHECK( criterion->isSimulationComplete() );

  criterion->clearCache();

  FRENSIE_CHECK( !criterion->isSimulationComplete() );

  criterion->stop();
}

//---------------------------------------------------------------------------//
// Check that a criterion can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( ParticleHistorySimulationCompletionCriterion,
                                   archive,
                                   TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_observer_time_dimension_discretization" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
      criterion_a = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createHistoryCountCriterion( 10 );

    criterion_a->start();
    criterion_a->commitHistoryContribution();
    criterion_a->stop();

    std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
      criterion_b = MonteCarlo::ParticleHistorySimulationCompletionCriterion::createWallTimeCriterion( 0.01 );

    criterion_b->start();

    std::shared_ptr<Utility::Timer> timer =
      Utility::GlobalMPISession::createTimer();
  
    timer->start();
    criterion_b->start();

    while( timer->elapsed().count() < 0.02 );

    criterion_b->stop();

    std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
      criterion = criterion_a || criterion_b;

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( criterion_a ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( criterion_b ) );
    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( criterion ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  std::shared_ptr<MonteCarlo::ParticleHistorySimulationCompletionCriterion>
    criterion_a, criterion_b, criterion;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( criterion_a ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( criterion_b ) );
  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( criterion ) );

  iarchive.reset();

  FRENSIE_REQUIRE( !criterion_a->isSimulationComplete() );
  FRENSIE_REQUIRE( !criterion_b->isSimulationComplete() );
  FRENSIE_REQUIRE( !criterion->isSimulationComplete() );

  criterion->start();

  std::shared_ptr<Utility::Timer> timer =
    Utility::GlobalMPISession::createTimer();

  timer->start();
  
  while( timer->elapsed().count() < 0.02 );

  timer->stop();

  FRENSIE_CHECK( !criterion_a->isSimulationComplete() );
  FRENSIE_CHECK( criterion_b->isSimulationComplete() );
  FRENSIE_CHECK( criterion->isSimulationComplete() );

  // If the criterion hasn't been started all data accumulation will be ignored
  for( size_t i = 0; i <= 10; ++i )
  {
    criterion_a->commitHistoryContribution();
    criterion_b->commitHistoryContribution();
  }

  FRENSIE_CHECK( criterion_a->isSimulationComplete() );
  FRENSIE_CHECK( criterion_b->isSimulationComplete() );
  FRENSIE_CHECK( criterion->isSimulationComplete() );
}

//---------------------------------------------------------------------------//
// Custom setup
//---------------------------------------------------------------------------//
FRENSIE_CUSTOM_UNIT_TEST_SETUP_BEGIN();

int threads;

FRENSIE_CUSTOM_UNIT_TEST_COMMAND_LINE_OPTIONS()
{
  ADD_STANDARD_OPTION_AND_ASSIGN_VALUE( "threads",
                                        threads, 1,
                                        "Number of threads to use" );
}

FRENSIE_CUSTOM_UNIT_TEST_INIT()
{
  // Set up the global OpenMP session
  if( Utility::OpenMPProperties::isOpenMPUsed() )
    Utility::OpenMPProperties::setNumberOfThreads( threads );
}

FRENSIE_CUSTOM_UNIT_TEST_SETUP_END();

//---------------------------------------------------------------------------//
// end tstParticleHistorySimulationCompletionCriterion.cpp
//---------------------------------------------------------------------------//
