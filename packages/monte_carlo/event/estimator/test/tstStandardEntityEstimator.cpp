//---------------------------------------------------------------------------//
//!
//! \file   tstEstimator.cpp
//! \author Alex Robinson
//! \brief  Standard entity estimator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_StandardEntityEstimator.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "Utility_OpenMPProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestStandardEntityEstimator : public MonteCarlo::StandardEntityEstimator
{
public:
  TestStandardEntityEstimator( const unsigned long long id,
			       const double multiplier,
			       const std::vector<uint64_t>& entity_ids,
			       const std::vector<double>& entity_norm_constants )
    : MonteCarlo::StandardEntityEstimator( id,
                                           multiplier,
                                           entity_ids,
                                           entity_norm_constants )
  { /* ... */ }

  ~TestStandardEntityEstimator()
  { /* ... */ }

  void printSummary( std::ostream& os ) const final override
  { this->printImplementation( os, "Surface" ); }

  // Allow public access to the standard entity estimator protected mem. funcs.
  using MonteCarlo::StandardEntityEstimator::addPartialHistoryPointContribution;
  using MonteCarlo::StandardEntityEstimator::addPartialHistoryRangeContribution;
  using MonteCarlo::StandardEntityEstimator::assignDiscretization;
};

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//
// Set the standard entity estimator bins (and response functions)
void setEstimatorBins( TestStandardEntityEstimator& estimator,
                       const bool ranged_time_bins )
{
  // Set the energy bins
  std::vector<double> energy_bin_boundaries( 3 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 0.1;
  energy_bin_boundaries[2] = 1.0;

  estimator.setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>(energy_bin_boundaries);

  // Set the cosine bins
  std::vector<double> cosine_bin_boundaries( 3 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = 0.0;
  cosine_bin_boundaries[2] = 1.0;

  estimator.setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>(cosine_bin_boundaries);

  // Set the time bins
  if( ranged_time_bins )
  {
    std::vector<double> time_bin_boundaries( 3 );
    time_bin_boundaries[0] = 1e-6;
    time_bin_boundaries[1] = 1e-5;
    time_bin_boundaries[2] = 1.9e-5;

    std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
      time_discretization( new MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>( time_bin_boundaries ) );

    estimator.assignDiscretization( time_discretization, ranged_time_bins );
  }
  else
  {
    std::vector<double> time_bin_boundaries( 3 );
    time_bin_boundaries[0] = 1e-6;
    time_bin_boundaries[1] = 1e-5;
    time_bin_boundaries[2] = 1e-4;

    std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
      time_discretization( new MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>( time_bin_boundaries ) );

    estimator.assignDiscretization( time_discretization, ranged_time_bins );
  }

  // Set the collision number bins
  std::vector<unsigned> collision_number_bins( 2 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;

  estimator.setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

  // Set the response functions
  std::vector<std::shared_ptr<const MonteCarlo::ParticleResponse> >
    response_functions( 2 );
  response_functions[0] = MonteCarlo::ParticleResponse::getDefault();
  response_functions[1] = response_functions[0];
  
  estimator.setResponseFunctions( response_functions );
}

// Initialize the standard entity estimator (int)
void initializeStandardEntityEstimator( std::shared_ptr<TestStandardEntityEstimator>& estimator,
                                        const bool ranged_time_bins = false )
{
  // Set the entity ids
  std::vector<uint64_t> entity_ids( 2 );
  entity_ids[0] = 0;
  entity_ids[1] = 1;

  // Set the entity normalization constants
  std::vector<double> entity_norm_constants( 2 );
  entity_norm_constants[0] = 1.0;
  entity_norm_constants[1] = 2.0;

  // Set the estimator multiplier
  double estimator_multiplier = 10.0;

  estimator.reset( new TestStandardEntityEstimator( 0ull,
                                                    estimator_multiplier,
                                                    entity_ids,
                                                    entity_norm_constants ) );

  std::vector<MonteCarlo::ParticleType> particle_types( 1 );
  particle_types[0] = MonteCarlo::PHOTON;
  
  estimator->setParticleTypes( particle_types );

  setEstimatorBins( *estimator, ranged_time_bins );
}

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the number of bins can be returned
FRENSIE_UNIT_TEST( StandardEntityEstimator, getNumberOfBins )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 16 );
}

//---------------------------------------------------------------------------//
// Check that the number of response functions can be returned
FRENSIE_UNIT_TEST( StandardEntityEstimator, getNumberOfResponseFunctions )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator );

  FRENSIE_CHECK_EQUAL( estimator->getNumberOfResponseFunctions(), 2 );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
FRENSIE_UNIT_TEST( StandardEntityEstimator,
                   addPartialHistoryPointContribution )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator );

  FRENSIE_CHECK( !estimator->hasUncommittedHistoryContribution() );

  // bin 0 (E=0, Mu=0, T=0, Col=0)
  MonteCarlo::PhotonState particle( 0ull );
  MonteCarlo::ObserverParticleStateWrapper particle_wrapper( particle );
  
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( -0.5 );
  particle.setTime( 5e-6 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  FRENSIE_CHECK( estimator->hasUncommittedHistoryContribution() );

  // bin 1 (E=1, Mu=0, T=0, Col=0)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 2 (E=0, Mu=1, T=0, Col=0)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( 0.5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 3 (E=1, Mu=1, T=0, Col=0)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 4 (E=0, Mu=0, T=1, Col=0)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( -0.5 );
  particle.setTime( 5e-5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 5 (E=1, Mu=0, T=1, Col=0)
  particle.setEnergy( 0.11 );
  
  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 6 (E=0, Mu=1, T=1, Col=0)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( 0.5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 7 (E=1, Mu=1, T=1, Col=0)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 8 (E=0, Mu=0, T=0, Col=1)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( -0.5 );
  particle.setTime( 5e-6 );
  particle.incrementCollisionNumber();

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 9 (E=1, Mu=0, T=0, Col=1)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 10 (E=0, Mu=1, T=0, Col=1)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( 0.5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 11 (E=1, Mu=1, T=0, Col=1)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 12 (E=0, Mu=0, T=1, Col=1)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( -0.5 );
  particle.setTime( 5e-5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 13 (E=1, Mu=0, T=1, Col=1)
  particle.setEnergy( 0.11 );
  
  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 14 (E=0, Mu=1, T=1, Col=1)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( 0.5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 15 (E=1, Mu=1, T=1, Col=1)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // Commit the contributions
  estimator->commitHistoryContribution();

  FRENSIE_CHECK( !estimator->hasUncommittedHistoryContribution() );

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( 1.0 );
  MonteCarlo::ParticleHistoryObserver::setElapsedTime( 1.0 );

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    estimator->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    estimator->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 32, 2.0 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 32, 4.0 ) );
  
  // Check the entity bin data moments
  Utility::ArrayView<const double> entity_bin_first_moments =
    estimator->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    estimator->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 32, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 32, 1.0 ) );

  entity_bin_first_moments = estimator->getEntityBinDataFirstMoments( 1 );
  entity_bin_second_moments = estimator->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 32, 1.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 32, 1.0 ) );

  // Check the entity total data moments
  FRENSIE_REQUIRE( estimator->isTotalDataAvailable() );
  
  Utility::ArrayView<const double> entity_total_first_moments =
    estimator->getEntityTotalDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_total_second_moments =
    estimator->getEntityTotalDataSecondMoments( 0 );

  Utility::ArrayView<const double> entity_total_third_moments =
    estimator->getEntityTotalDataThirdMoments( 0 );

  Utility::ArrayView<const double> entity_total_fourth_moments =
    estimator->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 2, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 2, 256.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 2, 4096.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 2, 65536.0 ) );

  entity_total_first_moments = estimator->getEntityTotalDataFirstMoments( 1 );
  entity_total_second_moments = estimator->getEntityTotalDataSecondMoments( 1 );
  entity_total_third_moments = estimator->getEntityTotalDataThirdMoments( 1 );
  entity_total_fourth_moments = estimator->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 2, 16.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 2, 256.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 2, 4096.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 2, 65536.0 ) );

  // Check the entity processed total data
  std::vector<double> entity_total_mean, entity_total_re, entity_total_vov,
    entity_total_fom;

  estimator->getEntityTotalProcessedData( 0,
                                          entity_total_mean,
                                          entity_total_re,
                                          entity_total_vov,
                                          entity_total_fom );

  FRENSIE_CHECK_EQUAL( entity_total_mean, std::vector<double>( 2, 160.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_re, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_vov, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fom, std::vector<double>( 2, 0.0 ) );

  estimator->getEntityTotalProcessedData( 1,
                                          entity_total_mean,
                                          entity_total_re,
                                          entity_total_vov,
                                          entity_total_fom );

  FRENSIE_CHECK_EQUAL( entity_total_mean, std::vector<double>( 2, 80.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_re, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_vov, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fom, std::vector<double>( 2, 0.0 ) );

  // Check the total data moments
  Utility::ArrayView<const double> total_first_moments =
    estimator->getTotalDataFirstMoments();

  Utility::ArrayView<const double> total_second_moments =
    estimator->getTotalDataSecondMoments();

  Utility::ArrayView<const double> total_third_moments =
    estimator->getTotalDataThirdMoments();

  Utility::ArrayView<const double> total_fourth_moments =
    estimator->getTotalDataFourthMoments();

  FRENSIE_CHECK_EQUAL( total_first_moments,
                       std::vector<double>( 2, 32.0 ) );
  FRENSIE_CHECK_EQUAL( total_second_moments,
                       std::vector<double>( 2, 1024.0 ) );
  FRENSIE_CHECK_EQUAL( total_third_moments,
                       std::vector<double>( 2, 32768.0 ) );
  FRENSIE_CHECK_EQUAL( total_fourth_moments,
                       std::vector<double>( 2, 1048576.0 ) );

  // Check the processed total data
  std::vector<double> total_mean, total_re, total_vov, total_fom;

  estimator->getTotalProcessedData( total_mean, total_re, total_vov, total_fom );

  FRENSIE_CHECK_EQUAL( total_mean, std::vector<double>( 2, 320.0/3 ) );
  FRENSIE_CHECK_EQUAL( total_re, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_vov, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_fom, std::vector<double>( 2, 0.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
// in a thread safe way
FRENSIE_UNIT_TEST( StandardEntityEstimator,
                   addPartialHistoryPointContribution_thread_safe )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator );
  
  // Enable thread support
  estimator->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );

  unsigned threads =
    Utility::OpenMPProperties::getRequestedNumberOfThreads();

  for( unsigned i = 0; i < threads; ++i )
  {
    FRENSIE_CHECK( !estimator->hasUncommittedHistoryContribution( i ) );
  }

  #pragma omp parallel num_threads( threads )
  {
    // bin 0 (E=0, Mu=0, T=0, Col=0)
    MonteCarlo::PhotonState particle( 0ull );
    MonteCarlo::ObserverParticleStateWrapper particle_wrapper( particle );
  
    particle.setEnergy( 1e-2 );
    particle_wrapper.setAngleCosine( -0.5 );
    particle.setTime( 5e-6 );

    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

    #pragma omp critical
    {
      FRENSIE_CHECK( estimator->hasUncommittedHistoryContribution() );
    }
  }

  #pragma omp parallel num_threads( threads )
  {
    // bin 1 (E=1, Mu=0, T=0, Col=0)
    MonteCarlo::PhotonState particle( 0ull );
    MonteCarlo::ObserverParticleStateWrapper particle_wrapper( particle );
  
    particle.setEnergy( 0.11 );
    particle_wrapper.setAngleCosine( -0.5 );
    particle.setTime( 5e-6 );
        
    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );
    
    // bin 2 (E=0, Mu=1, T=0, Col=0)
    particle.setEnergy( 1e-2 );
    particle_wrapper.setAngleCosine( 0.5 );
    
    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );
    
    // bin 3 (E=1, Mu=1, T=0, Col=0)
    particle.setEnergy( 0.11 );
    
    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );
    
    // bin 4 (E=0, Mu=0, T=1, Col=0)
    particle.setEnergy( 1e-2 );
    particle_wrapper.setAngleCosine( -0.5 );
    particle.setTime( 5e-5 );
    
    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );
    
    // bin 5 (E=1, Mu=0, T=1, Col=0)
    particle.setEnergy( 0.11 );
    
    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );
    
    // bin 6 (E=0, Mu=1, T=1, Col=0)
    particle.setEnergy( 1e-2 );
    particle_wrapper.setAngleCosine( 0.5 );
    
    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );
    
    // bin 7 (E=1, Mu=1, T=1, Col=0)
    particle.setEnergy( 0.11 );
    
    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

    // bin 8 (E=0, Mu=0, T=0, Col=1)
    particle.setEnergy( 1e-2 );
    particle_wrapper.setAngleCosine( -0.5 );
    particle.setTime( 5e-6 );
    particle.incrementCollisionNumber();
    
    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );
    
    // bin 9 (E=1, Mu=0, T=0, Col=1)
    particle.setEnergy( 0.11 );
    
    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );
    
    // bin 10 (E=0, Mu=1, T=0, Col=1)
    particle.setEnergy( 1e-2 );
    particle_wrapper.setAngleCosine( 0.5 );
    
    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );
    
    // bin 11 (E=1, Mu=1, T=0, Col=1)
    particle.setEnergy( 0.11 );
    
    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

    // bin 12 (E=0, Mu=0, T=1, Col=1)
    particle.setEnergy( 1e-2 );
    particle_wrapper.setAngleCosine( -0.5 );
    particle.setTime( 5e-5 );
    
    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );
    
    // bin 13 (E=1, Mu=0, T=1, Col=1)
    particle.setEnergy( 0.11 );
    
    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );
    
    // bin 14 (E=0, Mu=1, T=1, Col=1)
    particle.setEnergy( 1e-2 );
    particle_wrapper.setAngleCosine( 0.5 );
    
    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );
    
    // bin 15 (E=1, Mu=1, T=1, Col=1)
    particle.setEnergy( 0.11 );
    
    estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );
    
    // Commit the contributions
    estimator->commitHistoryContribution();
  }

  for( unsigned i = 0; i < threads; ++i )
  {
    FRENSIE_CHECK( !estimator->hasUncommittedHistoryContribution( i ) );
  }

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( threads );
  MonteCarlo::ParticleHistoryObserver::setElapsedTime( 1.0 );

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    estimator->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    estimator->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 32, 2.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 32, 4.0*threads ) );
  
  // Check the entity bin data moments
  Utility::ArrayView<const double> entity_bin_first_moments =
    estimator->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    estimator->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 32, threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 32, threads ) );

  entity_bin_first_moments = estimator->getEntityBinDataFirstMoments( 1 );
  entity_bin_second_moments = estimator->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 32, threads ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 32, threads ) );

  // Check the entity total data moments
  FRENSIE_REQUIRE( estimator->isTotalDataAvailable() );
  
  Utility::ArrayView<const double> entity_total_first_moments =
    estimator->getEntityTotalDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_total_second_moments =
    estimator->getEntityTotalDataSecondMoments( 0 );

  Utility::ArrayView<const double> entity_total_third_moments =
    estimator->getEntityTotalDataThirdMoments( 0 );

  Utility::ArrayView<const double> entity_total_fourth_moments =
    estimator->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 2, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 2, 256.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 2, 4096.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 2, 65536.0*threads ) );

  entity_total_first_moments = estimator->getEntityTotalDataFirstMoments( 1 );
  entity_total_second_moments = estimator->getEntityTotalDataSecondMoments( 1 );
  entity_total_third_moments = estimator->getEntityTotalDataThirdMoments( 1 );
  entity_total_fourth_moments = estimator->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 2, 16.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 2, 256.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 2, 4096.0*threads ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 2, 65536.0*threads ) );

  // Check the entity processed total data
  std::vector<double> entity_total_mean, entity_total_re, entity_total_vov,
    entity_total_fom;

  estimator->getEntityTotalProcessedData( 0,
                                          entity_total_mean,
                                          entity_total_re,
                                          entity_total_vov,
                                          entity_total_fom );

  FRENSIE_CHECK_EQUAL( entity_total_mean, std::vector<double>( 2, 160.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_re, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_vov, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fom, std::vector<double>( 2, 0.0 ) );

  estimator->getEntityTotalProcessedData( 1,
                                          entity_total_mean,
                                          entity_total_re,
                                          entity_total_vov,
                                          entity_total_fom );

  FRENSIE_CHECK_EQUAL( entity_total_mean, std::vector<double>( 2, 80.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_re, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_vov, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fom, std::vector<double>( 2, 0.0 ) );

  // Check the total data moments
  Utility::ArrayView<const double> total_first_moments =
    estimator->getTotalDataFirstMoments();

  Utility::ArrayView<const double> total_second_moments =
    estimator->getTotalDataSecondMoments();

  Utility::ArrayView<const double> total_third_moments =
    estimator->getTotalDataThirdMoments();

  Utility::ArrayView<const double> total_fourth_moments =
    estimator->getTotalDataFourthMoments();

  FRENSIE_CHECK_EQUAL( total_first_moments,
                       std::vector<double>( 2, 32.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_second_moments,
                       std::vector<double>( 2, 1024.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_third_moments,
                       std::vector<double>( 2, 32768.0*threads ) );
  FRENSIE_CHECK_EQUAL( total_fourth_moments,
                       std::vector<double>( 2, 1048576.0*threads ) );

  // Check the processed total data
  std::vector<double> total_mean, total_re, total_vov, total_fom;

  estimator->getTotalProcessedData( total_mean, total_re, total_vov, total_fom );

  FRENSIE_CHECK_EQUAL( total_mean, std::vector<double>( 2, 320.0/3 ) );
  FRENSIE_CHECK_EQUAL( total_re, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_vov, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_fom, std::vector<double>( 2, 0.0 ) );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
FRENSIE_UNIT_TEST( StandardEntityEstimator,
                   addPartialHistoryRangeContribution )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator, true );

  FRENSIE_CHECK( !estimator->hasUncommittedHistoryContribution() );

  // bin 0, bin 4 (E=0, Mu=0, T=0 and T=1, Col=0)
  MonteCarlo::PhotonState particle( 0ull );
  MonteCarlo::ObserverParticleStateWrapper particle_wrapper( particle );
  
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( -0.5 );
  particle.setTime( 0.0 );
  particle_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 134906606.10000002 );

  estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );

  FRENSIE_CHECK( estimator->hasUncommittedHistoryContribution() );

  // bin 1, bin 5 (E=1, Mu=0, T=0 and T=1, Col=0)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );

  // bin 2, bin 6 (E=0, Mu=1, T=0 and T=1, Col=0)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( 0.5 );

  estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );

  // bin 3, bin 7 (E=1, Mu=1, T=0 and T=1, Col=0)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );

  // bin 8, bin 12 (E=0, Mu=0, T=0 and T=1, Col=1)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( -0.5 );
  particle.incrementCollisionNumber();

  estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );

  // bin 9, bin 13 (E=1, Mu=0, T=0 and T=1, Col=1)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );

  // bin 10, bin 14 (E=0, Mu=1, T=0 and T=1, Col=1)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( 0.5 );

  estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );

  // bin 11, bin 15 (E=1, Mu=1, T=0 and T=1, Col=1)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );

  // Commit the contributions
  estimator->commitHistoryContribution();

  FRENSIE_CHECK( !estimator->hasUncommittedHistoryContribution() );

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( 1.0 );
  MonteCarlo::ParticleHistoryObserver::setElapsedTime( 1.0 );

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    estimator->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    estimator->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_first_moments,
                                   std::vector<double>( 32, 4e-3 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_second_moments,
                                   std::vector<double>( 32, 1.6e-5 ),
                                   1e-15 );
  
  // Check the entity bin data moments
  Utility::ArrayView<const double> entity_bin_first_moments =
    estimator->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    estimator->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 32, 2e-3 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 32, 4e-6 ),
                                   1e-15 );

  entity_bin_first_moments = estimator->getEntityBinDataFirstMoments( 1 );
  entity_bin_second_moments = estimator->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 32, 2e-3 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 32, 4e-6 ),
                                   1e-15 );

  // Check the entity total data moments
  FRENSIE_REQUIRE( estimator->isTotalDataAvailable() );
  
  Utility::ArrayView<const double> entity_total_first_moments =
    estimator->getEntityTotalDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_total_second_moments =
    estimator->getEntityTotalDataSecondMoments( 0 );

  Utility::ArrayView<const double> entity_total_third_moments =
    estimator->getEntityTotalDataThirdMoments( 0 );

  Utility::ArrayView<const double> entity_total_fourth_moments =
    estimator->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 2, 0.032 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 2, 0.001024 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 2, 3.2768e-05 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 2, 1.048576e-06 ),
                                   1e-14 );

  entity_total_first_moments = estimator->getEntityTotalDataFirstMoments( 1 );
  entity_total_second_moments = estimator->getEntityTotalDataSecondMoments( 1 );
  entity_total_third_moments = estimator->getEntityTotalDataThirdMoments( 1 );
  entity_total_fourth_moments = estimator->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 2, 0.032 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 2, 0.001024 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 2, 3.2768e-05 ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 2, 1.048576e-06 ),
                                   1e-14 );

  // Check the entity processed total data
  std::vector<double> entity_total_mean, entity_total_re, entity_total_vov,
    entity_total_fom;

  estimator->getEntityTotalProcessedData( 0,
                                          entity_total_mean,
                                          entity_total_re,
                                          entity_total_vov,
                                          entity_total_fom );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_mean,
                                   std::vector<double>( 2, 0.32 ),
                                   1e-15 );
  FRENSIE_CHECK_SMALL( entity_total_re, 1e-15 );
  FRENSIE_CHECK_SMALL( entity_total_vov, 1e-15 );
  FRENSIE_CHECK_SMALL( entity_total_fom, 1e-15 );

  estimator->getEntityTotalProcessedData( 1,
                                          entity_total_mean,
                                          entity_total_re,
                                          entity_total_vov,
                                          entity_total_fom );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_mean,
                                   std::vector<double>( 2, 0.16 ),
                                   1e-15 );
  FRENSIE_CHECK_SMALL( entity_total_re, 1e-15 );
  FRENSIE_CHECK_SMALL( entity_total_vov, 1e-15 );
  FRENSIE_CHECK_SMALL( entity_total_fom, 1e-15 );

  // Check the total data moments
  Utility::ArrayView<const double> total_first_moments =
    estimator->getTotalDataFirstMoments();

  Utility::ArrayView<const double> total_second_moments =
    estimator->getTotalDataSecondMoments();

  Utility::ArrayView<const double> total_third_moments =
    estimator->getTotalDataThirdMoments();

  Utility::ArrayView<const double> total_fourth_moments =
    estimator->getTotalDataFourthMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_first_moments,
                                   std::vector<double>( 2, 0.064 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_second_moments,
                                   std::vector<double>( 2, 0.004096 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_third_moments,
                                   std::vector<double>( 2, 0.000262144 ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_fourth_moments,
                                   std::vector<double>( 2, 1.6777216e-05 ),
                                   1e-15 );

  // Check the processed total data
  std::vector<double> total_mean, total_re, total_vov, total_fom;

  estimator->getTotalProcessedData( total_mean, total_re, total_vov, total_fom );

  FRENSIE_CHECK_FLOATING_EQUALITY( total_mean,
                                   std::vector<double>( 2, 0.64/3 ),
                                   1e-15 );
  FRENSIE_CHECK_SMALL( total_re, 1e-15 );
  FRENSIE_CHECK_SMALL( total_vov, 1e-15 );
  FRENSIE_CHECK_SMALL( total_fom, 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
FRENSIE_UNIT_TEST( StandardEntityEstimator,
                   addPartialHistoryRangeContribution_thread_safe )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator, true );

  // Enable thread support
  estimator->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );

  unsigned threads =
    Utility::OpenMPProperties::getRequestedNumberOfThreads();

  for( unsigned i = 0; i < threads; ++i )
  {
    FRENSIE_CHECK( !estimator->hasUncommittedHistoryContribution( i ) );
  }

  #pragma omp parallel num_threads( threads )
  {
    // bin 0, bin 4 (E=0, Mu=0, T=0 and T=1, Col=0)
    MonteCarlo::PhotonState particle( 0ull );
    MonteCarlo::ObserverParticleStateWrapper particle_wrapper( particle );
  
    particle.setEnergy( 1e-2 );
    particle_wrapper.setAngleCosine( -0.5 );
    particle.setTime( 0.0 );
    particle_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 134906606.10000002 );
    
    estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );

    #pragma omp critical
    {
      FRENSIE_CHECK( estimator->hasUncommittedHistoryContribution() );
    }
  }

  #pragma omp parallel num_threads( threads )
  {
    // bin 1, bin 5 (E=1, Mu=0, T=0 and T=1, Col=0)
    MonteCarlo::PhotonState particle( 0ull );
    MonteCarlo::ObserverParticleStateWrapper particle_wrapper( particle );
  
    particle.setEnergy( 0.11 );
    particle_wrapper.setAngleCosine( -0.5 );
    particle.setTime( 0.0 );
    particle_wrapper.calculateStateTimesUsingParticleTimeAsStartTime( 134906606.10000002 );

    estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );

    // bin 2, bin 6 (E=0, Mu=1, T=0 and T=1, Col=0)
    particle.setEnergy( 1e-2 );
    particle_wrapper.setAngleCosine( 0.5 );
    
    estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );
    
    // bin 3, bin 7 (E=1, Mu=1, T=0 and T=1, Col=0)
    particle.setEnergy( 0.11 );
    
    estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );
    
    // bin 8, bin 12 (E=0, Mu=0, T=0 and T=1, Col=1)
    particle.setEnergy( 1e-2 );
    particle_wrapper.setAngleCosine( -0.5 );
    particle.incrementCollisionNumber();
    
    estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );

    // bin 9, bin 13 (E=1, Mu=0, T=0 and T=1, Col=1)
    particle.setEnergy( 0.11 );
    
    estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );
    
    // bin 10, bin 14 (E=0, Mu=1, T=0 and T=1, Col=1)
    particle.setEnergy( 1e-2 );
    particle_wrapper.setAngleCosine( 0.5 );
    
    estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );
    
    // bin 11, bin 15 (E=1, Mu=1, T=0 and T=1, Col=1)
    particle.setEnergy( 0.11 );
    
    estimator->addPartialHistoryRangeContribution( 0, particle_wrapper, 1.0 );
    estimator->addPartialHistoryRangeContribution( 1, particle_wrapper, 1.0 );
    
    // Commit the contributions
    estimator->commitHistoryContribution();
  }

  for( unsigned i = 0; i < threads; ++i )
  {
    FRENSIE_CHECK( !estimator->hasUncommittedHistoryContribution() );
  }
  
  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( threads );
  MonteCarlo::ParticleHistoryObserver::setElapsedTime( 1.0 );

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    estimator->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    estimator->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_first_moments,
                                   std::vector<double>( 32, 4e-3*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_bin_second_moments,
                                   std::vector<double>( 32, 1.6e-5*threads ),
                                   1e-15 );
  
  // Check the entity bin data moments
  Utility::ArrayView<const double> entity_bin_first_moments =
    estimator->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    estimator->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 32, 2e-3*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 32, 4e-6*threads ),
                                   1e-15 );

  entity_bin_first_moments = estimator->getEntityBinDataFirstMoments( 1 );
  entity_bin_second_moments = estimator->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_first_moments,
                                   std::vector<double>( 32, 2e-3*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_bin_second_moments,
                                   std::vector<double>( 32, 4e-6*threads ),
                                   1e-15 );

  // Check the entity total data moments
  FRENSIE_REQUIRE( estimator->isTotalDataAvailable() );
  
  Utility::ArrayView<const double> entity_total_first_moments =
    estimator->getEntityTotalDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_total_second_moments =
    estimator->getEntityTotalDataSecondMoments( 0 );

  Utility::ArrayView<const double> entity_total_third_moments =
    estimator->getEntityTotalDataThirdMoments( 0 );

  Utility::ArrayView<const double> entity_total_fourth_moments =
    estimator->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 2, 0.032*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 2, 0.001024*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 2, 3.2768e-05*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 2, 1.048576e-06*threads ),
                                   1e-14 );

  entity_total_first_moments = estimator->getEntityTotalDataFirstMoments( 1 );
  entity_total_second_moments = estimator->getEntityTotalDataSecondMoments( 1 );
  entity_total_third_moments = estimator->getEntityTotalDataThirdMoments( 1 );
  entity_total_fourth_moments = estimator->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_first_moments,
                                   std::vector<double>( 2, 0.032*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_second_moments,
                                   std::vector<double>( 2, 0.001024*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_third_moments,
                                   std::vector<double>( 2, 3.2768e-05*threads ),
                                   1e-14 );
  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fourth_moments,
                                   std::vector<double>( 2, 1.048576e-06*threads ),
                                   1e-14 );

  // Check the entity processed total data
  std::vector<double> entity_total_mean, entity_total_re, entity_total_vov,
    entity_total_fom;

  estimator->getEntityTotalProcessedData( 0,
                                          entity_total_mean,
                                          entity_total_re,
                                          entity_total_vov,
                                          entity_total_fom );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_mean,
                                   std::vector<double>( 2, 0.32 ),
                                   1e-15 );
  FRENSIE_CHECK_SMALL( entity_total_re, 1e-6 );
  FRENSIE_CHECK_SMALL( entity_total_vov, 1e-15 );

  if( entity_total_re.front() > 0.0 )
  {
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fom,
                                     std::vector<double>( 2, 1.0/(entity_total_re.front()*entity_total_re.front()) ),
                                     1e-15 );
  }
  else
  {
    FRENSIE_CHECK_SMALL( entity_total_fom, 1e-15 );
  }

  estimator->getEntityTotalProcessedData( 1,
                                          entity_total_mean,
                                          entity_total_re,
                                          entity_total_vov,
                                          entity_total_fom );

  FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_mean,
                                   std::vector<double>( 2, 0.16 ),
                                   1e-15 );
  FRENSIE_CHECK_SMALL( entity_total_re, 1e-6 );
  FRENSIE_CHECK_SMALL( entity_total_vov, 1e-15 );

  if( entity_total_re.front() > 0.0 )
  {
    FRENSIE_CHECK_FLOATING_EQUALITY( entity_total_fom,
                                     std::vector<double>( 2, 1.0/(entity_total_re.front()*entity_total_re.front()) ),
                                     1e-15 );
  }
  else
  {
    FRENSIE_CHECK_SMALL( entity_total_fom, 1e-15 );
  }

  // Check the total data moments
  Utility::ArrayView<const double> total_first_moments =
    estimator->getTotalDataFirstMoments();

  Utility::ArrayView<const double> total_second_moments =
    estimator->getTotalDataSecondMoments();

  Utility::ArrayView<const double> total_third_moments =
    estimator->getTotalDataThirdMoments();

  Utility::ArrayView<const double> total_fourth_moments =
    estimator->getTotalDataFourthMoments();

  FRENSIE_CHECK_FLOATING_EQUALITY( total_first_moments,
                                   std::vector<double>( 2, 0.064*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_second_moments,
                                   std::vector<double>( 2, 0.004096*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_third_moments,
                                   std::vector<double>( 2, 0.000262144*threads ),
                                   1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( total_fourth_moments,
                                   std::vector<double>( 2, 1.6777216e-05*threads ),
                                   1e-15 );

  // Check the processed total data
  std::vector<double> total_mean, total_re, total_vov, total_fom;

  estimator->getTotalProcessedData( total_mean, total_re, total_vov, total_fom );

  FRENSIE_CHECK_FLOATING_EQUALITY( total_mean,
                                   std::vector<double>( 2, 0.64/3 ),
                                   1e-15 );
  FRENSIE_CHECK_SMALL( total_re, 1e-6 );
  FRENSIE_CHECK_SMALL( total_vov, 1e-15 );

  if( total_re.front() > 0.0 )
  {
    FRENSIE_CHECK_FLOATING_EQUALITY( total_fom,
                                     std::vector<double>( 2, 1.0/(total_re.front()*total_re.front()) ),
                                     1e-15 );
  }
  else
  {
    FRENSIE_CHECK_SMALL( total_fom, 1e-15 );
  }
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
FRENSIE_UNIT_TEST( StandardEntityEstimator, resetData )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator );

  FRENSIE_CHECK( !estimator->hasUncommittedHistoryContribution() );

  // bin 0 (E=0, Mu=0, T=0, Col=0)
  MonteCarlo::PhotonState particle( 0ull );
  MonteCarlo::ObserverParticleStateWrapper particle_wrapper( particle );
  
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( -0.5 );
  particle.setTime( 5e-6 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  FRENSIE_CHECK( estimator->hasUncommittedHistoryContribution() );

  // bin 1 (E=1, Mu=0, T=0, Col=0)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 2 (E=0, Mu=1, T=0, Col=0)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( 0.5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 3 (E=1, Mu=1, T=0, Col=0)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 4 (E=0, Mu=0, T=1, Col=0)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( -0.5 );
  particle.setTime( 5e-5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 5 (E=1, Mu=0, T=1, Col=0)
  particle.setEnergy( 0.11 );
  
  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 6 (E=0, Mu=1, T=1, Col=0)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( 0.5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 7 (E=1, Mu=1, T=1, Col=0)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 8 (E=0, Mu=0, T=0, Col=1)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( -0.5 );
  particle.setTime( 5e-6 );
  particle.incrementCollisionNumber();

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 9 (E=1, Mu=0, T=0, Col=1)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 10 (E=0, Mu=1, T=0, Col=1)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( 0.5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 11 (E=1, Mu=1, T=0, Col=1)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 12 (E=0, Mu=0, T=1, Col=1)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( -0.5 );
  particle.setTime( 5e-5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 13 (E=1, Mu=0, T=1, Col=1)
  particle.setEnergy( 0.11 );
  
  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 14 (E=0, Mu=1, T=1, Col=1)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( 0.5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 15 (E=1, Mu=1, T=1, Col=1)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // Commit the contributions
  estimator->commitHistoryContribution();

  FRENSIE_CHECK( !estimator->hasUncommittedHistoryContribution() );

  // Reset the estimator data
  estimator->resetData();

  // Make sure all partial contributions have been deleted
  FRENSIE_CHECK( !estimator->hasUncommittedHistoryContribution() );

  // Check the total bin data moments
  Utility::ArrayView<const double> total_bin_first_moments =
    estimator->getTotalBinDataFirstMoments();

  Utility::ArrayView<const double> total_bin_second_moments =
    estimator->getTotalBinDataSecondMoments();

  FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                       std::vector<double>( 32, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                       std::vector<double>( 32, 0.0 ) );
  
  // Check the entity bin data moments
  Utility::ArrayView<const double> entity_bin_first_moments =
    estimator->getEntityBinDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_bin_second_moments =
    estimator->getEntityBinDataSecondMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 32, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 32, 0.0 ) );

  entity_bin_first_moments = estimator->getEntityBinDataFirstMoments( 1 );
  entity_bin_second_moments = estimator->getEntityBinDataSecondMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                       std::vector<double>( 32, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                       std::vector<double>( 32, 0.0 ) );

  // Check the entity total data moments
  FRENSIE_REQUIRE( estimator->isTotalDataAvailable() );
  
  Utility::ArrayView<const double> entity_total_first_moments =
    estimator->getEntityTotalDataFirstMoments( 0 );

  Utility::ArrayView<const double> entity_total_second_moments =
    estimator->getEntityTotalDataSecondMoments( 0 );

  Utility::ArrayView<const double> entity_total_third_moments =
    estimator->getEntityTotalDataThirdMoments( 0 );

  Utility::ArrayView<const double> entity_total_fourth_moments =
    estimator->getEntityTotalDataFourthMoments( 0 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 2, 0.0 ) );

  entity_total_first_moments = estimator->getEntityTotalDataFirstMoments( 1 );
  entity_total_second_moments = estimator->getEntityTotalDataSecondMoments( 1 );
  entity_total_third_moments = estimator->getEntityTotalDataThirdMoments( 1 );
  entity_total_fourth_moments = estimator->getEntityTotalDataFourthMoments( 1 );

  FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                       std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                       std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                       std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                       std::vector<double>( 2, 0.0 ) );

  // Check the total data moments
  Utility::ArrayView<const double> total_first_moments =
    estimator->getTotalDataFirstMoments();

  Utility::ArrayView<const double> total_second_moments =
    estimator->getTotalDataSecondMoments();

  Utility::ArrayView<const double> total_third_moments =
    estimator->getTotalDataThirdMoments();

  Utility::ArrayView<const double> total_fourth_moments =
    estimator->getTotalDataFourthMoments();

  FRENSIE_CHECK_EQUAL( total_first_moments,
                       std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_second_moments,
                       std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_third_moments,
                       std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_fourth_moments,
                       std::vector<double>( 2, 0.0 ) );
}

//---------------------------------------------------------------------------//
// Check that the estimator data can be reduced
FRENSIE_UNIT_TEST( StandardEntityEstimator, reduceData )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator );

  // bin 0 (E=0, Mu=0, T=0, Col=0)
  MonteCarlo::PhotonState particle( 0ull );
  MonteCarlo::ObserverParticleStateWrapper particle_wrapper( particle );
  
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( -0.5 );
  particle.setTime( 5e-6 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 1 (E=1, Mu=0, T=0, Col=0)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 2 (E=0, Mu=1, T=0, Col=0)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( 0.5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 3 (E=1, Mu=1, T=0, Col=0)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 4 (E=0, Mu=0, T=1, Col=0)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( -0.5 );
  particle.setTime( 5e-5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 5 (E=1, Mu=0, T=1, Col=0)
  particle.setEnergy( 0.11 );
  
  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 6 (E=0, Mu=1, T=1, Col=0)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( 0.5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 7 (E=1, Mu=1, T=1, Col=0)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 8 (E=0, Mu=0, T=0, Col=1)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( -0.5 );
  particle.setTime( 5e-6 );
  particle.incrementCollisionNumber();

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 9 (E=1, Mu=0, T=0, Col=1)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 10 (E=0, Mu=1, T=0, Col=1)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( 0.5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 11 (E=1, Mu=1, T=0, Col=1)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 12 (E=0, Mu=0, T=1, Col=1)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( -0.5 );
  particle.setTime( 5e-5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 13 (E=1, Mu=0, T=1, Col=1)
  particle.setEnergy( 0.11 );
  
  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 14 (E=0, Mu=1, T=1, Col=1)
  particle.setEnergy( 1e-2 );
  particle_wrapper.setAngleCosine( 0.5 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // bin 15 (E=1, Mu=1, T=1, Col=1)
  particle.setEnergy( 0.11 );

  estimator->addPartialHistoryPointContribution( 0, particle_wrapper, 1.0 );
  estimator->addPartialHistoryPointContribution( 1, particle_wrapper, 1.0 );

  // Commit the contributions
  estimator->commitHistoryContribution();

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  comm->barrier();

  estimator->reduceData( *comm, 0 );

  unsigned procs = comm->size();

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( procs );
  MonteCarlo::ParticleHistoryObserver::setElapsedTime( 1.0 );

  if( comm->rank() == 0 )
  {
    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator->getTotalBinDataSecondMoments();
    
    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( 32, 2.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                         std::vector<double>( 32, 4.0*procs ) );
  
    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator->getEntityBinDataFirstMoments( 0 );
    
    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator->getEntityBinDataSecondMoments( 0 );
    
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, procs ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, procs ) );

    entity_bin_first_moments = estimator->getEntityBinDataFirstMoments( 1 );
    entity_bin_second_moments = estimator->getEntityBinDataSecondMoments( 1 );
    
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, procs ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, procs ) );
    
    // Check the entity total data moments
    FRENSIE_REQUIRE( estimator->isTotalDataAvailable() );
    
    Utility::ArrayView<const double> entity_total_first_moments =
      estimator->getEntityTotalDataFirstMoments( 0 );
    
    Utility::ArrayView<const double> entity_total_second_moments =
      estimator->getEntityTotalDataSecondMoments( 0 );
    
    Utility::ArrayView<const double> entity_total_third_moments =
      estimator->getEntityTotalDataThirdMoments( 0 );
    
    Utility::ArrayView<const double> entity_total_fourth_moments =
      estimator->getEntityTotalDataFourthMoments( 0 );
    
    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 2, 16.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 256.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 4096.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 65536.0*procs ) );
    
    entity_total_first_moments = estimator->getEntityTotalDataFirstMoments( 1 );
    entity_total_second_moments = estimator->getEntityTotalDataSecondMoments( 1 );
    entity_total_third_moments = estimator->getEntityTotalDataThirdMoments( 1 );
    entity_total_fourth_moments = estimator->getEntityTotalDataFourthMoments( 1 );
    
    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 2, 16.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 256.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 4096.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 65536.0*procs ) );
    
    // Check the entity processed total data
    std::vector<double> entity_total_mean, entity_total_re, entity_total_vov,
      entity_total_fom;
    
    estimator->getEntityTotalProcessedData( 0,
                                            entity_total_mean,
                                            entity_total_re,
                                            entity_total_vov,
                                            entity_total_fom );
    
    FRENSIE_CHECK_EQUAL( entity_total_mean, std::vector<double>( 2, 160.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_re, std::vector<double>( 2, 0.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_vov, std::vector<double>( 2, 0.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fom, std::vector<double>( 2, 0.0 ) );
    
    estimator->getEntityTotalProcessedData( 1,
                                            entity_total_mean,
                                            entity_total_re,
                                            entity_total_vov,
                                            entity_total_fom );
    
    FRENSIE_CHECK_EQUAL( entity_total_mean, std::vector<double>( 2, 80.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_re, std::vector<double>( 2, 0.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_vov, std::vector<double>( 2, 0.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fom, std::vector<double>( 2, 0.0 ) );
    
    // Check the total data moments
    Utility::ArrayView<const double> total_first_moments =
      estimator->getTotalDataFirstMoments();
    
    Utility::ArrayView<const double> total_second_moments =
      estimator->getTotalDataSecondMoments();
    
    Utility::ArrayView<const double> total_third_moments =
      estimator->getTotalDataThirdMoments();
    
    Utility::ArrayView<const double> total_fourth_moments =
      estimator->getTotalDataFourthMoments();
    
    FRENSIE_CHECK_EQUAL( total_first_moments,
                         std::vector<double>( 2, 32.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_second_moments,
                         std::vector<double>( 2, 1024.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_third_moments,
                         std::vector<double>( 2, 32768.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_fourth_moments,
                         std::vector<double>( 2, 1048576.0*procs ) );
    
    // Check the processed total data
    std::vector<double> total_mean, total_re, total_vov, total_fom;
    
    estimator->getTotalProcessedData( total_mean, total_re, total_vov, total_fom );
    
    FRENSIE_CHECK_EQUAL( total_mean, std::vector<double>( 2, 320.0/3 ) );
    FRENSIE_CHECK_EQUAL( total_re, std::vector<double>( 2, 0.0 ) );
    FRENSIE_CHECK_EQUAL( total_vov, std::vector<double>( 2, 0.0 ) );
    FRENSIE_CHECK_EQUAL( total_fom, std::vector<double>( 2, 0.0 ) );
  }
  // Make sure that estimators on other processes were reset
  else
  {
    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator->getTotalBinDataSecondMoments();

    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( 32, 0.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                         std::vector<double>( 32, 0.0 ) );
    
    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator->getEntityBinDataFirstMoments( 0 );
    
    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator->getEntityBinDataSecondMoments( 0 );
    
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, 0.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, 0.0 ) );
    
    entity_bin_first_moments = estimator->getEntityBinDataFirstMoments( 1 );
    entity_bin_second_moments = estimator->getEntityBinDataSecondMoments( 1 );
    
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, 0.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, 0.0 ) );
    
    // Check the entity total data moments
    FRENSIE_REQUIRE( estimator->isTotalDataAvailable() );
    
    Utility::ArrayView<const double> entity_total_first_moments =
      estimator->getEntityTotalDataFirstMoments( 0 );
    
    Utility::ArrayView<const double> entity_total_second_moments =
      estimator->getEntityTotalDataSecondMoments( 0 );
    
    Utility::ArrayView<const double> entity_total_third_moments =
      estimator->getEntityTotalDataThirdMoments( 0 );
    
    Utility::ArrayView<const double> entity_total_fourth_moments =
      estimator->getEntityTotalDataFourthMoments( 0 );
    
    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 2, 0.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 0.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 0.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 0.0 ) );
    
    entity_total_first_moments = estimator->getEntityTotalDataFirstMoments( 1 );
    entity_total_second_moments = estimator->getEntityTotalDataSecondMoments( 1 );
    entity_total_third_moments = estimator->getEntityTotalDataThirdMoments( 1 );
    entity_total_fourth_moments = estimator->getEntityTotalDataFourthMoments( 1 );
    
    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 2, 0.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 0.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 0.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 0.0 ) );
    
    // Check the total data moments
    Utility::ArrayView<const double> total_first_moments =
      estimator->getTotalDataFirstMoments();
    
    Utility::ArrayView<const double> total_second_moments =
      estimator->getTotalDataSecondMoments();
    
    Utility::ArrayView<const double> total_third_moments =
      estimator->getTotalDataThirdMoments();
    
    Utility::ArrayView<const double> total_fourth_moments =
      estimator->getTotalDataFourthMoments();
    
    FRENSIE_CHECK_EQUAL( total_first_moments,
                         std::vector<double>( 2, 0.0 ) );
    FRENSIE_CHECK_EQUAL( total_second_moments,
                         std::vector<double>( 2, 0.0 ) );
    FRENSIE_CHECK_EQUAL( total_third_moments,
                       std::vector<double>( 2, 0.0 ) );
    FRENSIE_CHECK_EQUAL( total_fourth_moments,
                         std::vector<double>( 2, 0.0 ) );
  }
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
// end tstStandardEntityEstimator.cpp
//---------------------------------------------------------------------------//


