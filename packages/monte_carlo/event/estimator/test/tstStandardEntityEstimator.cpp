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
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef TestArchiveHelper::TestArchives TestArchives;

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

  //! Check if the estimator is a cell estimator
  bool isCellEstimator() const final override
  { return false; }

  //! Check if the estimator is a surface estimator
  bool isSurfaceEstimator() const final override
  { return false; }

  //! Check if the estimator is a mesh estimator
  bool isMeshEstimator() const final override
  { return false; }

  void printSummary( std::ostream& os ) const final override
  { this->printImplementation( os, "Surface" ); }

  // Allow public access to the standard entity estimator protected mem. funcs.
  using MonteCarlo::StandardEntityEstimator::addPartialHistoryPointContribution;
  using MonteCarlo::StandardEntityEstimator::addPartialHistoryRangeContribution;
  using MonteCarlo::StandardEntityEstimator::assignDiscretization;

private:

  // Default constructor
  TestStandardEntityEstimator()
  { /* ... */ }

  // Serialize the entity estimator
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( StandardEntityEstimator ); }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

BOOST_CLASS_VERSION( TestStandardEntityEstimator, 0 );
BOOST_CLASS_EXPORT_KEY2( TestStandardEntityEstimator, "TestStandardEntityEstimator" );
BOOST_CLASS_EXPORT_IMPLEMENT( TestStandardEntityEstimator );

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
// Check that the sample moment histogram bins can be set
FRENSIE_UNIT_TEST( StandardEntityEstimator, setSampleMomentHistogramBins )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator );

  // Check the entity total histograms (default)
  Utility::SampleMomentHistogram<double> histogram;

  std::vector<double> expected_histogram_bins =
    Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );

  estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  // Check the total histograms (default)
  estimator->getTotalSampleMomentHistogram( 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  estimator->getTotalSampleMomentHistogram( 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  std::shared_ptr<const std::vector<double> > custom_histogram_bins =
    std::make_shared<std::vector<double> >( Utility::fromString<std::vector<double> >( "{0.0, 1.0, 2.0, 3.0, 4.0, 5.0}" ) );

  estimator->setSampleMomentHistogramBins( custom_histogram_bins );

  // Check the entity total histograms
  estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       *custom_histogram_bins );

  estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       *custom_histogram_bins );

  estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       *custom_histogram_bins );

  estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       *custom_histogram_bins );

  // Check the total histograms (default)
  estimator->getTotalSampleMomentHistogram( 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       *custom_histogram_bins );

  estimator->getTotalSampleMomentHistogram( 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       *custom_histogram_bins );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
FRENSIE_UNIT_TEST( StandardEntityEstimator,
                   addPartialHistoryPointContribution_no_bin_histograms )
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
  std::map<std::string,std::vector<double> > processed_data;

  estimator->getEntityTotalProcessedData( 0,
                                          entity_total_mean,
                                          entity_total_re,
                                          entity_total_vov,
                                          entity_total_fom );
  estimator->getEntityTotalProcessedData( 0, processed_data );

  FRENSIE_CHECK_EQUAL( entity_total_mean, std::vector<double>( 2, 160.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 2, 160.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_re, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_vov, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fom, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 2, 0.0 ) );

  estimator->getEntityTotalProcessedData( 1,
                                          entity_total_mean,
                                          entity_total_re,
                                          entity_total_vov,
                                          entity_total_fom );
  estimator->getEntityTotalProcessedData( 1, processed_data );

  FRENSIE_CHECK_EQUAL( entity_total_mean, std::vector<double>( 2, 80.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 2, 80.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_re, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_vov, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fom, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 2, 0.0 ) );

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
  estimator->getTotalProcessedData( processed_data );

  FRENSIE_CHECK_EQUAL( total_mean, std::vector<double>( 2, 320.0/3 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 2, 320.0/3 ) );
  FRENSIE_CHECK_EQUAL( total_re, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_vov, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_fom, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 2, 0.0 ) );

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;

  size_t num_estimator_bins = estimator->getNumberOfBins()*
    estimator->getNumberOfResponseFunctions();
  
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinSampleMomentHistogram( 0, j, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }

  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinSampleMomentHistogram( 1, j, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }

  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }

  // Check the entity total histograms
  std::vector<double> expected_histogram_bins =
    Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
  std::vector<double> expected_histogram_values =
    Utility::fromString<std::vector<double> >( "{0.0r314, 1.0, 0.0r288}" );
  
  estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  // Check the entity total histograms
  expected_histogram_values =
    Utility::fromString<std::vector<double> >( "{0.0r317, 1.0, 0.0r285}" );
  
  estimator->getTotalSampleMomentHistogram( 0, histogram );
  
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getTotalSampleMomentHistogram( 1, histogram );
  
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
FRENSIE_UNIT_TEST( StandardEntityEstimator,
                   addPartialHistoryPointContribution_with_bin_histograms )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator );

  estimator->enableSampleMomentHistogramsOnEntityBins();
  
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
  std::map<std::string,std::vector<double> > processed_data;

  estimator->getEntityTotalProcessedData( 0,
                                          entity_total_mean,
                                          entity_total_re,
                                          entity_total_vov,
                                          entity_total_fom );
  estimator->getEntityTotalProcessedData( 0, processed_data );

  FRENSIE_CHECK_EQUAL( entity_total_mean, std::vector<double>( 2, 160.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 2, 160.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_re, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_vov, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fom, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 2, 0.0 ) );

  estimator->getEntityTotalProcessedData( 1,
                                          entity_total_mean,
                                          entity_total_re,
                                          entity_total_vov,
                                          entity_total_fom );
  estimator->getEntityTotalProcessedData( 1, processed_data );

  FRENSIE_CHECK_EQUAL( entity_total_mean, std::vector<double>( 2, 80.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 2, 80.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_re, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_vov, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( entity_total_fom, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 2, 0.0 ) );

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
  estimator->getTotalProcessedData( processed_data );

  FRENSIE_CHECK_EQUAL( total_mean, std::vector<double>( 2, 320.0/3 ) );
  FRENSIE_CHECK_EQUAL( processed_data["mean"], std::vector<double>( 2, 320.0/3 ) );
  FRENSIE_CHECK_EQUAL( total_re, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["re"], std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_vov, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["vov"], std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( total_fom, std::vector<double>( 2, 0.0 ) );
  FRENSIE_CHECK_EQUAL( processed_data["fom"], std::vector<double>( 2, 0.0 ) );

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;

  std::vector<double> expected_histogram_bins =
    Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
  std::vector<double> expected_histogram_values =
    Utility::fromString<std::vector<double> >( "{0.0r302, 1.0, 0.0r300}" );

  size_t num_estimator_bins = estimator->getNumberOfBins()*
    estimator->getNumberOfResponseFunctions();
  
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinSampleMomentHistogram( 0, j, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  }

  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinSampleMomentHistogram( 1, j, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  }

  // Check the total bin histograms
  expected_histogram_values =
    Utility::fromString<std::vector<double> >( "{0.0r305, 1.0, 0.0r297}" );
  
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  }

  // Check the entity total histograms
  expected_histogram_values =
    Utility::fromString<std::vector<double> >( "{0.0r314, 1.0, 0.0r288}" );
  
  estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  // Check the entity total histograms
  expected_histogram_values =
    Utility::fromString<std::vector<double> >( "{0.0r317, 1.0, 0.0r285}" );
  
  estimator->getTotalSampleMomentHistogram( 0, histogram );
  
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getTotalSampleMomentHistogram( 1, histogram );
  
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 1 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
// in a thread safe way
FRENSIE_UNIT_TEST( StandardEntityEstimator,
                   addPartialHistoryPointContribution_thread_safe_no_bin_histograms )
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

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;

  size_t num_estimator_bins = estimator->getNumberOfBins()*
    estimator->getNumberOfResponseFunctions();
  
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinSampleMomentHistogram( 0, j, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }

  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinSampleMomentHistogram( 1, j, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }

  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }

  // Check the entity total histograms
  std::vector<double> expected_histogram_bins =
    Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
  std::vector<double> expected_histogram_values;

  {
    std::string expected_histogram_values_string = "{0.0r314, ";
    expected_histogram_values_string += Utility::toString( threads );
    expected_histogram_values_string += ", 0.0r288}";
    
    expected_histogram_values = 
      Utility::fromString<std::vector<double> >( expected_histogram_values_string );
  }
  
  estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), threads );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), threads );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), threads );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), threads );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  // Check the entity total histograms
  {
    std::string expected_histogram_values_string = "{0.0r317, ";
    expected_histogram_values_string += Utility::toString( threads );
    expected_histogram_values_string += ", 0.0r285}";
    
    expected_histogram_values =
      Utility::fromString<std::vector<double> >( expected_histogram_values_string );
  }
  
  estimator->getTotalSampleMomentHistogram( 0, histogram );
  
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), threads );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getTotalSampleMomentHistogram( 1, histogram );
  
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), threads );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
// in a thread safe way
FRENSIE_UNIT_TEST( StandardEntityEstimator,
                   addPartialHistoryPointContribution_thread_safe_with_bin_histograms )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator );
  
  // Enable thread support
  estimator->enableThreadSupport( Utility::OpenMPProperties::getRequestedNumberOfThreads() );

  estimator->enableSampleMomentHistogramsOnEntityBins();
  
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

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;

  std::vector<double> expected_histogram_bins =
    Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
  std::vector<double> expected_histogram_values;

  {
    std::string expected_histogram_values_string = "{0.0r302, ";
    expected_histogram_values_string += Utility::toString( threads );
    expected_histogram_values_string += ", 0.0r300}";
    
    expected_histogram_values = 
      Utility::fromString<std::vector<double> >( expected_histogram_values_string );
  }

  size_t num_estimator_bins = estimator->getNumberOfBins()*
    estimator->getNumberOfResponseFunctions();
  
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinSampleMomentHistogram( 0, j, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), threads );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  }

  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinSampleMomentHistogram( 1, j, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), threads );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  }

  // Check the total bin histograms
  {
    std::string expected_histogram_value_string = "{0.0r305, ";
    expected_histogram_value_string += Utility::toString( threads );
    expected_histogram_value_string += ", 0.0r297}";
    
    expected_histogram_values =
      Utility::fromString<std::vector<double> >( expected_histogram_value_string );
  }
  
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), threads );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  }

  // Check the entity total histograms
  {
    std::string expected_histogram_values_string = "{0.0r314, ";
    expected_histogram_values_string += Utility::toString( threads );
    expected_histogram_values_string += ", 0.0r288}";
    
    expected_histogram_values = 
      Utility::fromString<std::vector<double> >( expected_histogram_values_string );
  }
  
  estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), threads );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), threads );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), threads );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), threads );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  // Check the entity total histograms
  {
    std::string expected_histogram_values_string = "{0.0r317, ";
    expected_histogram_values_string += Utility::toString( threads );
    expected_histogram_values_string += ", 0.0r285}";
    
    expected_histogram_values =
      Utility::fromString<std::vector<double> >( expected_histogram_values_string );
  }
  
  estimator->getTotalSampleMomentHistogram( 0, histogram );
  
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), threads );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );

  estimator->getTotalSampleMomentHistogram( 1, histogram );
  
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), threads );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );
  FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                       expected_histogram_values );
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
// Check that a snapshot of the estimator state can be made
FRENSIE_UNIT_TEST( StandardEntityEstimator, takeSnapshot_no_bin_snapshots )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator );

  for( size_t i = 0; i < 2; ++i )
  {
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

    // Take a snapshot
    estimator->takeSnapshot( 5, 2.0 );
  }

  // Check the entity bin moment snapshots
  std::vector<uint64_t> history_values;
  std::vector<double> sampling_times;

  std::vector<double> first_moments, second_moments, third_moments,
    fourth_moments;

  estimator->getEntityBinMomentSnapshotHistoryValues( 0, history_values );

  estimator->getEntityBinMomentSnapshotSamplingTimes( 0, sampling_times );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

  estimator->getEntityBinMomentSnapshotHistoryValues( 1, history_values );

  estimator->getEntityBinMomentSnapshotSamplingTimes( 1, sampling_times );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

  size_t num_estimator_bins = estimator->getNumberOfBins()*
    estimator->getNumberOfResponseFunctions();
    
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinFirstMomentSnapshots( 1, j, first_moments );
    estimator->getEntityBinSecondMomentSnapshots( 1, j, second_moments );
    estimator->getEntityBinThirdMomentSnapshots( 1, j, third_moments );
    estimator->getEntityBinFourthMomentSnapshots( 1, j, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
  }

  // Check the total bin moment snapshots
  estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
  estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
  
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {  
    estimator->getTotalBinFirstMomentSnapshots( j, first_moments );
    estimator->getTotalBinSecondMomentSnapshots( j, second_moments );
    estimator->getTotalBinThirdMomentSnapshots( j, third_moments );
    estimator->getTotalBinFourthMomentSnapshots( j, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
  }

  // Check the entity total moment snapshots
  estimator->getEntityTotalMomentSnapshotHistoryValues( 0, history_values );

  FRENSIE_CHECK_EQUAL( history_values, std::vector<uint64_t>( {5, 10} ) );

  estimator->getEntityTotalMomentSnapshotSamplingTimes( 0, sampling_times );

  FRENSIE_CHECK_EQUAL( sampling_times, std::vector<double>( {2.0, 4.0} ) );

  estimator->getEntityTotalFirstMomentSnapshots( 0, 0, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 0, 0, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 0, 0, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 0, 0, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {16.0, 32.0} )  );
  FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {256, 512} ) );
  FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( {4096, 8192} ) );
  FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( {65536, 131072} ) );

  estimator->getEntityTotalFirstMomentSnapshots( 0, 1, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 0, 1, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 0, 1, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 0, 1, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {16.0, 32.0} )  );
  FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {256, 512} ) );
  FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( {4096, 8192} ) );
  FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( {65536, 131072} ) );

  estimator->getEntityTotalMomentSnapshotHistoryValues( 1, history_values );

  FRENSIE_CHECK_EQUAL( history_values, std::vector<uint64_t>( {5, 10} ) );

  estimator->getEntityTotalMomentSnapshotSamplingTimes( 1, sampling_times );

  FRENSIE_CHECK_EQUAL( sampling_times, std::vector<double>( {2.0, 4.0} ) );

  estimator->getEntityTotalFirstMomentSnapshots( 1, 0, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 1, 0, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 1, 0, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 1, 0, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {16.0, 32.0} )  );
  FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {256, 512} ) );
  FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( {4096, 8192} ) );
  FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( {65536, 131072} ) );

  estimator->getEntityTotalFirstMomentSnapshots( 1, 1, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 1, 1, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 1, 1, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 1, 1, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {16.0, 32.0} )  );
  FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {256, 512} ) );
  FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( {4096, 8192} ) );
  FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( {65536, 131072} ) );

  // Check the entity total processed snapshots
  std::vector<double> mean_snapshots, re_snapshots, vov_snapshots,
    fom_snapshots;

  std::map<std::string,std::vector<double> > processed_snapshots;

  estimator->getEntityTotalProcessedSnapshots( 0, 0, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
  estimator->getEntityTotalProcessedSnapshots( 0, 0, processed_snapshots );

  FRENSIE_CHECK_FLOATING_EQUALITY( mean_snapshots, std::vector<double>( {32.0, 32.0} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["mean"], std::vector<double>( {32.0, 32.0} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.225} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.225} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {0.5, 0.5625} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {0.5, 0.5625} ), 1e-15 );

  estimator->getEntityTotalProcessedSnapshots( 0, 1, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
  estimator->getEntityTotalProcessedSnapshots( 0, 1, processed_snapshots );

  FRENSIE_CHECK_FLOATING_EQUALITY( mean_snapshots, std::vector<double>( {32.0, 32.0} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["mean"], std::vector<double>( {32.0, 32.0} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.225} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.225} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {0.5, 0.5625} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {0.5, 0.5625} ), 1e-15 );

  estimator->getEntityTotalProcessedSnapshots( 1, 0, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
  estimator->getEntityTotalProcessedSnapshots( 1, 0, processed_snapshots );

  FRENSIE_CHECK_FLOATING_EQUALITY( mean_snapshots, std::vector<double>( {16.0, 16.0} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["mean"], std::vector<double>( {16.0, 16.0} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.225} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.225} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {0.5, 0.5625} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {0.5, 0.5625} ), 1e-15 );

  estimator->getEntityTotalProcessedSnapshots( 1, 1, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
  estimator->getEntityTotalProcessedSnapshots( 1, 1, processed_snapshots );

  FRENSIE_CHECK_FLOATING_EQUALITY( mean_snapshots, std::vector<double>( {16.0, 16.0} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["mean"], std::vector<double>( {16.0, 16.0} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.225} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.225} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {0.5, 0.5625} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {0.5, 0.5625} ), 1e-15 );
  
  // Check the total moment snapshots
  estimator->getTotalMomentSnapshotHistoryValues( history_values );

  FRENSIE_CHECK_EQUAL( history_values, std::vector<uint64_t>( {5, 10} ) );

  estimator->getTotalMomentSnapshotSamplingTimes( sampling_times );

  FRENSIE_CHECK_EQUAL( sampling_times, std::vector<double>( {2.0, 4.0} ) );

  estimator->getTotalFirstMomentSnapshots( 0, first_moments );
  estimator->getTotalSecondMomentSnapshots( 0, second_moments );
  estimator->getTotalThirdMomentSnapshots( 0, third_moments );
  estimator->getTotalFourthMomentSnapshots( 0, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {32.0, 64.0} )  );
  FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1024.0, 2048.0} ) );
  FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( {32768.0, 65536.0} ) );
  FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( {1048576.0, 2097152.0} ) );

  estimator->getTotalFirstMomentSnapshots( 1, first_moments );
  estimator->getTotalSecondMomentSnapshots( 1, second_moments );
  estimator->getTotalThirdMomentSnapshots( 1, third_moments );
  estimator->getTotalFourthMomentSnapshots( 1, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {32.0, 64.0} )  );
  FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1024.0, 2048.0} ) );
  FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( {32768.0, 65536.0} ) );
  FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( {1048576.0, 2097152.0} ) );

  // Check the total processed snapshots
  estimator->getTotalProcessedSnapshots( 0, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
  estimator->getTotalProcessedSnapshots( 0, processed_snapshots );

  FRENSIE_CHECK_FLOATING_EQUALITY( mean_snapshots, std::vector<double>( {64.0/3, 64.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["mean"], std::vector<double>( {64.0/3, 64.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.225} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.225} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {0.5, 0.5625} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {0.5, 0.5625} ), 1e-15 );

  estimator->getTotalProcessedSnapshots( 1, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
  estimator->getTotalProcessedSnapshots( 1, processed_snapshots );

  FRENSIE_CHECK_FLOATING_EQUALITY( mean_snapshots, std::vector<double>( {64.0/3, 64.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["mean"], std::vector<double>( {64.0/3, 64.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.225} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.225} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {0.5, 0.5625} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {0.5, 0.5625} ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a snapshot of the estimator state can be made
FRENSIE_UNIT_TEST( StandardEntityEstimator, takeSnapshot_with_bin_snapshots )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator );

  estimator->enableSnapshotsOnEntityBins();

  for( size_t i = 0; i < 2; ++i )
  {
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

    // Take a snapshot
    estimator->takeSnapshot( 5, 2.0 );
  }

  // Check the entity bin moment snapshots
  std::vector<uint64_t> history_values;
  std::vector<double> sampling_times;

  std::vector<double> first_moments, second_moments, third_moments,
    fourth_moments;

  estimator->getEntityBinMomentSnapshotHistoryValues( 0, history_values );

  estimator->getEntityBinMomentSnapshotSamplingTimes( 0, sampling_times );

  FRENSIE_CHECK_EQUAL( history_values, std::vector<uint64_t>({5, 10}) );
  FRENSIE_CHECK_EQUAL( sampling_times, std::vector<double>({2.0, 4.0}) );

  estimator->getEntityBinMomentSnapshotHistoryValues( 1, history_values );

  estimator->getEntityBinMomentSnapshotSamplingTimes( 1, sampling_times );

  FRENSIE_CHECK_EQUAL( history_values, std::vector<uint64_t>({5, 10}) );
  FRENSIE_CHECK_EQUAL( sampling_times, std::vector<double>({2.0, 4.0}) );

  size_t num_estimator_bins = estimator->getNumberOfBins()*
    estimator->getNumberOfResponseFunctions();
    
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinFirstMomentSnapshots( 0, j, first_moments );
    estimator->getEntityBinSecondMomentSnapshots( 0, j, second_moments );
    estimator->getEntityBinThirdMomentSnapshots( 0, j, third_moments );
    estimator->getEntityBinFourthMomentSnapshots( 0, j, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>({1.0, 2.0}) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>({1.0, 2.0}) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>({1.0, 2.0}) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>({1.0, 2.0}) );
    
    estimator->getEntityBinFirstMomentSnapshots( 1, j, first_moments );
    estimator->getEntityBinSecondMomentSnapshots( 1, j, second_moments );
    estimator->getEntityBinThirdMomentSnapshots( 1, j, third_moments );
    estimator->getEntityBinFourthMomentSnapshots( 1, j, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>({1.0, 2.0}) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>({1.0, 2.0}) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>({1.0, 2.0}) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>({1.0, 2.0}) );
  }

  // Check the total bin moment snapshots
  estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
  estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );

  FRENSIE_CHECK_EQUAL( history_values, std::vector<uint64_t>({5, 10}) );
  FRENSIE_CHECK_EQUAL( sampling_times, std::vector<double>({2.0, 4.0}) );
  
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {  
    estimator->getTotalBinFirstMomentSnapshots( j, first_moments );
    estimator->getTotalBinSecondMomentSnapshots( j, second_moments );
    estimator->getTotalBinThirdMomentSnapshots( j, third_moments );
    estimator->getTotalBinFourthMomentSnapshots( j, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>({2.0, 4.0}) );
    FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>({4.0, 8.0}) );
    FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>({8.0, 16.0}) );
    FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>({16.0, 32.0}) );
  }

  // Check the entity total moment snapshots
  estimator->getEntityTotalMomentSnapshotHistoryValues( 0, history_values );

  FRENSIE_CHECK_EQUAL( history_values, std::vector<uint64_t>( {5, 10} ) );

  estimator->getEntityTotalMomentSnapshotSamplingTimes( 0, sampling_times );

  FRENSIE_CHECK_EQUAL( sampling_times, std::vector<double>( {2.0, 4.0} ) );

  estimator->getEntityTotalFirstMomentSnapshots( 0, 0, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 0, 0, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 0, 0, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 0, 0, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {16.0, 32.0} )  );
  FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {256, 512} ) );
  FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( {4096, 8192} ) );
  FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( {65536, 131072} ) );

  estimator->getEntityTotalFirstMomentSnapshots( 0, 1, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 0, 1, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 0, 1, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 0, 1, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {16.0, 32.0} )  );
  FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {256, 512} ) );
  FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( {4096, 8192} ) );
  FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( {65536, 131072} ) );

  estimator->getEntityTotalMomentSnapshotHistoryValues( 1, history_values );

  FRENSIE_CHECK_EQUAL( history_values, std::vector<uint64_t>( {5, 10} ) );

  estimator->getEntityTotalMomentSnapshotSamplingTimes( 1, sampling_times );

  FRENSIE_CHECK_EQUAL( sampling_times, std::vector<double>( {2.0, 4.0} ) );

  estimator->getEntityTotalFirstMomentSnapshots( 1, 0, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 1, 0, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 1, 0, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 1, 0, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {16.0, 32.0} )  );
  FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {256, 512} ) );
  FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( {4096, 8192} ) );
  FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( {65536, 131072} ) );

  estimator->getEntityTotalFirstMomentSnapshots( 1, 1, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 1, 1, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 1, 1, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 1, 1, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {16.0, 32.0} )  );
  FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {256, 512} ) );
  FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( {4096, 8192} ) );
  FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( {65536, 131072} ) );

  // Check the entity total processed snapshots
  std::vector<double> mean_snapshots, re_snapshots, vov_snapshots,
    fom_snapshots;

  std::map<std::string,std::vector<double> > processed_snapshots;

  estimator->getEntityTotalProcessedSnapshots( 0, 0, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
  estimator->getEntityTotalProcessedSnapshots( 0, 0, processed_snapshots );

  FRENSIE_CHECK_FLOATING_EQUALITY( mean_snapshots, std::vector<double>( {32.0, 32.0} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["mean"], std::vector<double>( {32.0, 32.0} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.225} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.225} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {0.5, 0.5625} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {0.5, 0.5625} ), 1e-15 );

  estimator->getEntityTotalProcessedSnapshots( 0, 1, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
  estimator->getEntityTotalProcessedSnapshots( 0, 1, processed_snapshots );

  FRENSIE_CHECK_FLOATING_EQUALITY( mean_snapshots, std::vector<double>( {32.0, 32.0} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["mean"], std::vector<double>( {32.0, 32.0} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.225} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.225} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {0.5, 0.5625} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {0.5, 0.5625} ), 1e-15 );

  estimator->getEntityTotalProcessedSnapshots( 1, 0, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
  estimator->getEntityTotalProcessedSnapshots( 1, 0, processed_snapshots );

  FRENSIE_CHECK_FLOATING_EQUALITY( mean_snapshots, std::vector<double>( {16.0, 16.0} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["mean"], std::vector<double>( {16.0, 16.0} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.225} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.225} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {0.5, 0.5625} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {0.5, 0.5625} ), 1e-15 );

  estimator->getEntityTotalProcessedSnapshots( 1, 1, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
  estimator->getEntityTotalProcessedSnapshots( 1, 1, processed_snapshots );

  FRENSIE_CHECK_FLOATING_EQUALITY( mean_snapshots, std::vector<double>( {16.0, 16.0} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["mean"], std::vector<double>( {16.0, 16.0} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.225} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.225} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {0.5, 0.5625} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {0.5, 0.5625} ), 1e-15 );
  
  // Check the total moment snapshots
  estimator->getTotalMomentSnapshotHistoryValues( history_values );

  FRENSIE_CHECK_EQUAL( history_values, std::vector<uint64_t>( {5, 10} ) );

  estimator->getTotalMomentSnapshotSamplingTimes( sampling_times );

  FRENSIE_CHECK_EQUAL( sampling_times, std::vector<double>( {2.0, 4.0} ) );

  estimator->getTotalFirstMomentSnapshots( 0, first_moments );
  estimator->getTotalSecondMomentSnapshots( 0, second_moments );
  estimator->getTotalThirdMomentSnapshots( 0, third_moments );
  estimator->getTotalFourthMomentSnapshots( 0, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {32.0, 64.0} )  );
  FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1024.0, 2048.0} ) );
  FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( {32768.0, 65536.0} ) );
  FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( {1048576.0, 2097152.0} ) );

  estimator->getTotalFirstMomentSnapshots( 1, first_moments );
  estimator->getTotalSecondMomentSnapshots( 1, second_moments );
  estimator->getTotalThirdMomentSnapshots( 1, third_moments );
  estimator->getTotalFourthMomentSnapshots( 1, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments, std::vector<double>( {32.0, 64.0} )  );
  FRENSIE_CHECK_EQUAL( second_moments, std::vector<double>( {1024.0, 2048.0} ) );
  FRENSIE_CHECK_EQUAL( third_moments, std::vector<double>( {32768.0, 65536.0} ) );
  FRENSIE_CHECK_EQUAL( fourth_moments, std::vector<double>( {1048576.0, 2097152.0} ) );

  // Check the total processed snapshots
  estimator->getTotalProcessedSnapshots( 0, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
  estimator->getTotalProcessedSnapshots( 0, processed_snapshots );

  FRENSIE_CHECK_FLOATING_EQUALITY( mean_snapshots, std::vector<double>( {64.0/3, 64.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["mean"], std::vector<double>( {64.0/3, 64.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.225} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.225} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {0.5, 0.5625} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {0.5, 0.5625} ), 1e-15 );

  estimator->getTotalProcessedSnapshots( 1, mean_snapshots, re_snapshots, vov_snapshots, fom_snapshots );
  estimator->getTotalProcessedSnapshots( 1, processed_snapshots );

  FRENSIE_CHECK_FLOATING_EQUALITY( mean_snapshots, std::vector<double>( {64.0/3, 64.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["mean"], std::vector<double>( {64.0/3, 64.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( re_snapshots, std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["re"], std::vector<double>( {1.0, 2.0/3} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( vov_snapshots, std::vector<double>( {0.45, 0.225} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["vov"], std::vector<double>( {0.45, 0.225} ), 1e-15 );
  
  FRENSIE_CHECK_FLOATING_EQUALITY( fom_snapshots, std::vector<double>( {0.5, 0.5625} ), 1e-15 );
  FRENSIE_CHECK_FLOATING_EQUALITY( processed_snapshots["fom"], std::vector<double>( {0.5, 0.5625} ), 1e-15 );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
FRENSIE_UNIT_TEST( StandardEntityEstimator, resetData_no_additional_bin_stats )
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
  estimator->takeSnapshot( 5, 1.0 );

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

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;

  size_t num_estimator_bins = estimator->getNumberOfBins()*
    estimator->getNumberOfResponseFunctions();
  
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinSampleMomentHistogram( 0, j, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }

  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinSampleMomentHistogram( 1, j, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }

  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }

  // Check the entity total histograms
  std::vector<double> expected_histogram_bins =
    Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
  
  estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  // Check the entity total histograms
  estimator->getTotalSampleMomentHistogram( 0, histogram );
  
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  estimator->getTotalSampleMomentHistogram( 1, histogram );
  
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  // Check the entity bin moment snapshots
  std::vector<uint64_t> history_values;
  std::vector<double> sampling_times;

  std::vector<double> first_moments, second_moments, third_moments,
    fourth_moments;

  estimator->getEntityBinMomentSnapshotHistoryValues( 0, history_values );

  estimator->getEntityBinMomentSnapshotSamplingTimes( 0, sampling_times );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

  estimator->getEntityBinMomentSnapshotHistoryValues( 1, history_values );

  estimator->getEntityBinMomentSnapshotSamplingTimes( 1, sampling_times );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

  num_estimator_bins = estimator->getNumberOfBins()*
    estimator->getNumberOfResponseFunctions();
    
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinFirstMomentSnapshots( 1, j, first_moments );
    estimator->getEntityBinSecondMomentSnapshots( 1, j, second_moments );
    estimator->getEntityBinThirdMomentSnapshots( 1, j, third_moments );
    estimator->getEntityBinFourthMomentSnapshots( 1, j, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
  }

  // Check the total bin moment snapshots
  estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
  estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
  
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {  
    estimator->getTotalBinFirstMomentSnapshots( j, first_moments );
    estimator->getTotalBinSecondMomentSnapshots( j, second_moments );
    estimator->getTotalBinThirdMomentSnapshots( j, third_moments );
    estimator->getTotalBinFourthMomentSnapshots( j, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
  }

  // Check the entity total moment snapshots
  estimator->getEntityTotalMomentSnapshotHistoryValues( 0, history_values );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );

  estimator->getEntityTotalMomentSnapshotSamplingTimes( 0, sampling_times );

  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

  estimator->getEntityTotalFirstMomentSnapshots( 0, 0, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 0, 0, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 0, 0, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 0, 0, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );

  estimator->getEntityTotalFirstMomentSnapshots( 0, 1, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 0, 1, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 0, 1, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 0, 1, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );

  estimator->getEntityTotalMomentSnapshotHistoryValues( 1, history_values );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );

  estimator->getEntityTotalMomentSnapshotSamplingTimes( 1, sampling_times );

  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

  estimator->getEntityTotalFirstMomentSnapshots( 1, 0, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 1, 0, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 1, 0, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 1, 0, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );

  estimator->getEntityTotalFirstMomentSnapshots( 1, 1, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 1, 1, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 1, 1, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 1, 1, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );

  // Check the total moment snapshots
  estimator->getTotalMomentSnapshotHistoryValues( history_values );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );

  estimator->getTotalMomentSnapshotSamplingTimes( sampling_times );

  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

  estimator->getTotalFirstMomentSnapshots( 0, first_moments );
  estimator->getTotalSecondMomentSnapshots( 0, second_moments );
  estimator->getTotalThirdMomentSnapshots( 0, third_moments );
  estimator->getTotalFourthMomentSnapshots( 0, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );

  estimator->getTotalFirstMomentSnapshots( 1, first_moments );
  estimator->getTotalSecondMomentSnapshots( 1, second_moments );
  estimator->getTotalThirdMomentSnapshots( 1, third_moments );
  estimator->getTotalFourthMomentSnapshots( 1, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that a partial history contribution can be added to the estimator
FRENSIE_UNIT_TEST( StandardEntityEstimator, resetData_with_additional_bin_stats )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator );

  estimator->enableSnapshotsOnEntityBins();
  estimator->enableSampleMomentHistogramsOnEntityBins();

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
  estimator->takeSnapshot( 5, 1.0 );

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

  // Check the entity bin histograms
  Utility::SampleMomentHistogram<double> histogram;

  size_t num_estimator_bins = estimator->getNumberOfBins()*
    estimator->getNumberOfResponseFunctions();
  
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinSampleMomentHistogram( 0, j, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }

  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinSampleMomentHistogram( 1, j, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }

  // Check the total bin histograms
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getTotalBinSampleMomentHistogram( j, histogram );

    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  }

  // Check the entity total histograms
  std::vector<double> expected_histogram_bins =
    Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
  
  estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );

  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  // Check the entity total histograms
  estimator->getTotalSampleMomentHistogram( 0, histogram );
  
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  estimator->getTotalSampleMomentHistogram( 1, histogram );
  
  FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
  FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                       expected_histogram_bins );

  // Check the entity bin moment snapshots
  std::vector<uint64_t> history_values;
  std::vector<double> sampling_times;

  std::vector<double> first_moments, second_moments, third_moments,
    fourth_moments;

  estimator->getEntityBinMomentSnapshotHistoryValues( 0, history_values );

  estimator->getEntityBinMomentSnapshotSamplingTimes( 0, sampling_times );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

  estimator->getEntityBinMomentSnapshotHistoryValues( 1, history_values );

  estimator->getEntityBinMomentSnapshotSamplingTimes( 1, sampling_times );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

  num_estimator_bins = estimator->getNumberOfBins()*
    estimator->getNumberOfResponseFunctions();
    
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {
    estimator->getEntityBinFirstMomentSnapshots( 1, j, first_moments );
    estimator->getEntityBinSecondMomentSnapshots( 1, j, second_moments );
    estimator->getEntityBinThirdMomentSnapshots( 1, j, third_moments );
    estimator->getEntityBinFourthMomentSnapshots( 1, j, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
  }

  // Check the total bin moment snapshots
  estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
  estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
  
  for( size_t j = 0; j < num_estimator_bins; ++j )
  {  
    estimator->getTotalBinFirstMomentSnapshots( j, first_moments );
    estimator->getTotalBinSecondMomentSnapshots( j, second_moments );
    estimator->getTotalBinThirdMomentSnapshots( j, third_moments );
    estimator->getTotalBinFourthMomentSnapshots( j, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
  }

  // Check the entity total moment snapshots
  estimator->getEntityTotalMomentSnapshotHistoryValues( 0, history_values );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );

  estimator->getEntityTotalMomentSnapshotSamplingTimes( 0, sampling_times );

  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

  estimator->getEntityTotalFirstMomentSnapshots( 0, 0, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 0, 0, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 0, 0, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 0, 0, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );

  estimator->getEntityTotalFirstMomentSnapshots( 0, 1, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 0, 1, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 0, 1, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 0, 1, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );

  estimator->getEntityTotalMomentSnapshotHistoryValues( 1, history_values );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );

  estimator->getEntityTotalMomentSnapshotSamplingTimes( 1, sampling_times );

  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

  estimator->getEntityTotalFirstMomentSnapshots( 1, 0, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 1, 0, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 1, 0, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 1, 0, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );

  estimator->getEntityTotalFirstMomentSnapshots( 1, 1, first_moments );
  estimator->getEntityTotalSecondMomentSnapshots( 1, 1, second_moments );
  estimator->getEntityTotalThirdMomentSnapshots( 1, 1, third_moments );
  estimator->getEntityTotalFourthMomentSnapshots( 1, 1, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );

  // Check the total moment snapshots
  estimator->getTotalMomentSnapshotHistoryValues( history_values );

  FRENSIE_CHECK_EQUAL( history_values.size(), 0 );

  estimator->getTotalMomentSnapshotSamplingTimes( sampling_times );

  FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

  estimator->getTotalFirstMomentSnapshots( 0, first_moments );
  estimator->getTotalSecondMomentSnapshots( 0, second_moments );
  estimator->getTotalThirdMomentSnapshots( 0, third_moments );
  estimator->getTotalFourthMomentSnapshots( 0, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );

  estimator->getTotalFirstMomentSnapshots( 1, first_moments );
  estimator->getTotalSecondMomentSnapshots( 1, second_moments );
  estimator->getTotalThirdMomentSnapshots( 1, third_moments );
  estimator->getTotalFourthMomentSnapshots( 1, fourth_moments );

  FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
  FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the estimator data can be reduced
FRENSIE_UNIT_TEST( StandardEntityEstimator, reduceData_no_additional_bin_stats )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator );

  for( size_t i = 0; i < 2; ++i )
  {
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

    estimator->takeSnapshot( 5, 1.0 );
  }

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  comm->barrier();

  estimator->reduceData( *comm, 0 );

  unsigned procs = comm->size();

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( procs*10 );
  MonteCarlo::ParticleHistoryObserver::setElapsedTime( 2.0 );

  if( comm->rank() == 0 )
  {
    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator->getTotalBinDataSecondMoments();

    Utility::ArrayView<const double> total_bin_third_moments =
      estimator->getTotalBinDataThirdMoments();

    Utility::ArrayView<const double> total_bin_fourth_moments =
      estimator->getTotalBinDataFourthMoments();
    
    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( 32, 4.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                         std::vector<double>( 32, 8.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_bin_third_moments,
                         std::vector<double>( 32, 16.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_bin_fourth_moments,
                         std::vector<double>( 32, 32.0*procs ) );
  
    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator->getEntityBinDataFirstMoments( 0 );
    
    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator->getEntityBinDataSecondMoments( 0 );

    Utility::ArrayView<const double> entity_bin_third_moments =
      estimator->getEntityBinDataThirdMoments( 0 );

    Utility::ArrayView<const double> entity_bin_fourth_moments =
      estimator->getEntityBinDataFourthMoments( 0 );
    
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, 2.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, 2.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                         std::vector<double>( 32, 2.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                         std::vector<double>( 32, 2.0*procs ) );

    entity_bin_first_moments = estimator->getEntityBinDataFirstMoments( 1 );
    entity_bin_second_moments = estimator->getEntityBinDataSecondMoments( 1 );
    entity_bin_third_moments = estimator->getEntityBinDataThirdMoments( 1 );
    entity_bin_fourth_moments = estimator->getEntityBinDataFourthMoments( 1 );
    
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, 2.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, 2.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                         std::vector<double>( 32, 2.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                         std::vector<double>( 32, 2.0*procs ) );
    
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
                         std::vector<double>( 2, 32.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 512.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 8192.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 131072.0*procs ) );
    
    entity_total_first_moments = estimator->getEntityTotalDataFirstMoments( 1 );
    entity_total_second_moments = estimator->getEntityTotalDataSecondMoments( 1 );
    entity_total_third_moments = estimator->getEntityTotalDataThirdMoments( 1 );
    entity_total_fourth_moments = estimator->getEntityTotalDataFourthMoments( 1 );
    
    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 2, 32.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 512.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 8192.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 131072.0*procs ) );
    
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
                         std::vector<double>( 2, 64.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_second_moments,
                         std::vector<double>( 2, 2048.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_third_moments,
                         std::vector<double>( 2, 65536.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_fourth_moments,
                         std::vector<double>( 2, 2097152.0*procs ) );
    
    // Check the entity bin histograms
    Utility::SampleMomentHistogram<double> histogram;

    size_t num_estimator_bins = estimator->getNumberOfBins()*
      estimator->getNumberOfResponseFunctions();
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getEntityBinSampleMomentHistogram( 0, j, histogram );
      
      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }

    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getEntityBinSampleMomentHistogram( 1, j, histogram );
      
      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }

    // Check the total bin histograms
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getTotalBinSampleMomentHistogram( j, histogram );
      
      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }

    // Check the entity total histograms
    std::vector<double> expected_histogram_bins =
      Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
    std::vector<double> expected_histogram_values;

    {
      std::string expected_histogram_values_string = "{0.0r314, ";
      expected_histogram_values_string += Utility::toString( 2*procs );
      expected_histogram_values_string += ", 0.0r288}";
    
      expected_histogram_values = 
        Utility::fromString<std::vector<double> >( expected_histogram_values_string );
    }
  
    estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2*procs );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
    
    estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2*procs );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
    
    estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2*procs );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
    
    estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2*procs );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );

    // Check the entity total histograms
    {
      std::string expected_histogram_values_string = "{0.0r317, ";
      expected_histogram_values_string += Utility::toString( 2*procs );
      expected_histogram_values_string += ", 0.0r285}";
      
      expected_histogram_values =
        Utility::fromString<std::vector<double> >( expected_histogram_values_string );
    }
  
    estimator->getTotalSampleMomentHistogram( 0, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2*procs );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
    
    estimator->getTotalSampleMomentHistogram( 1, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2*procs );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );

    // Check the entity bin moment snapshots
    std::vector<uint64_t> history_values;
    std::vector<double> sampling_times;

    std::vector<double> first_moments, second_moments, third_moments,
      fourth_moments;

    estimator->getEntityBinMomentSnapshotHistoryValues( 0, history_values );

    estimator->getEntityBinMomentSnapshotSamplingTimes( 0, sampling_times );

    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

    estimator->getEntityBinMomentSnapshotHistoryValues( 1, history_values );

    estimator->getEntityBinMomentSnapshotSamplingTimes( 1, sampling_times );

    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );

    num_estimator_bins = estimator->getNumberOfBins()*
    estimator->getNumberOfResponseFunctions();
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getEntityBinFirstMomentSnapshots( 0, j, first_moments );
      estimator->getEntityBinSecondMomentSnapshots( 0, j, second_moments );
      estimator->getEntityBinThirdMomentSnapshots( 0, j, third_moments );
      estimator->getEntityBinFourthMomentSnapshots( 0, j, fourth_moments );
      
      FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
      
      estimator->getEntityBinFirstMomentSnapshots( 1, j, first_moments );
      estimator->getEntityBinSecondMomentSnapshots( 1, j, second_moments );
      estimator->getEntityBinThirdMomentSnapshots( 1, j, third_moments );
      estimator->getEntityBinFourthMomentSnapshots( 1, j, fourth_moments );
      
      FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    }

    // Check the total bin moment snapshots
    estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
    estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );
    
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {  
      estimator->getTotalBinFirstMomentSnapshots( j, first_moments );
      estimator->getTotalBinSecondMomentSnapshots( j, second_moments );
      estimator->getTotalBinThirdMomentSnapshots( j, third_moments );
      estimator->getTotalBinFourthMomentSnapshots( j, fourth_moments );
      
      FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    }

    // Check the entity total moment snapshots
    std::vector<uint64_t> expected_history_values( 2*procs );
    std::vector<double> expected_sampling_times( 2*procs );
    std::vector<double> expected_first_moments( 2*procs );
    std::vector<double> expected_second_moments( 2*procs );
    std::vector<double> expected_third_moments( 2*procs );
    std::vector<double> expected_fourth_moments( 2*procs );

    for( size_t i = 0; i < 2*procs; ++i )
    {
      expected_history_values[i] = (i+1)*5;
      expected_sampling_times[i] = (i+1)*1.0;
      expected_first_moments[i] = (i+1)*16.0;
      expected_second_moments[i] = (i+1)*256.0;
      expected_third_moments[i] = (i+1)*4096.0;
      expected_fourth_moments[i] = (i+1)*65536.0;
    }
    
    estimator->getEntityTotalMomentSnapshotHistoryValues( 0, history_values );

    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 0, sampling_times );
    
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
    
    estimator->getEntityTotalFirstMomentSnapshots( 0, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 0, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
    
    estimator->getEntityTotalFirstMomentSnapshots( 0, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 1, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
    
    estimator->getEntityTotalMomentSnapshotHistoryValues( 1, history_values );
    
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 1, sampling_times );
    
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
    
    estimator->getEntityTotalFirstMomentSnapshots( 1, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 0, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
    
    estimator->getEntityTotalFirstMomentSnapshots( 1, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 1, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );

    // Check the total moment snapshots
    for( size_t i = 0; i < 2*procs; ++i )
    {
      expected_first_moments[i] = (i+1)*32.0;
      expected_second_moments[i] = (i+1)*1024.0;
      expected_third_moments[i] = (i+1)*32768.0;
      expected_fourth_moments[i] = (i+1)*1048576.0;
    }
    
    estimator->getTotalMomentSnapshotHistoryValues( history_values );
    
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    
    estimator->getTotalMomentSnapshotSamplingTimes( sampling_times );
    
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );

    estimator->getTotalFirstMomentSnapshots( 0, first_moments );
    estimator->getTotalSecondMomentSnapshots( 0, second_moments );
    estimator->getTotalThirdMomentSnapshots( 0, third_moments );
    estimator->getTotalFourthMomentSnapshots( 0, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
    
    estimator->getTotalFirstMomentSnapshots( 1, first_moments );
    estimator->getTotalSecondMomentSnapshots( 1, second_moments );
    estimator->getTotalThirdMomentSnapshots( 1, third_moments );
    estimator->getTotalFourthMomentSnapshots( 1, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments ); 
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

    // Check the entity bin histograms
    Utility::SampleMomentHistogram<double> histogram;

    size_t num_estimator_bins = estimator->getNumberOfBins()*
      estimator->getNumberOfResponseFunctions();
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getEntityBinSampleMomentHistogram( 0, j, histogram );
      
      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getEntityBinSampleMomentHistogram( 1, j, histogram );
      
      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }
    
    // Check the total bin histograms
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getTotalBinSampleMomentHistogram( j, histogram );
      
      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }
    
    // Check the entity total histograms
    std::vector<double> expected_histogram_bins =
      Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
    
    estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    
    estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    
    estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    
    estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    
    // Check the entity total histograms
    estimator->getTotalSampleMomentHistogram( 0, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    
    estimator->getTotalSampleMomentHistogram( 1, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    
    // Check the entity bin moment snapshots
    std::vector<uint64_t> history_values;
    std::vector<double> sampling_times;
    
    std::vector<double> first_moments, second_moments, third_moments,
      fourth_moments;
    
    estimator->getEntityBinMomentSnapshotHistoryValues( 0, history_values );
    
    estimator->getEntityBinMomentSnapshotSamplingTimes( 0, sampling_times );
    
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    estimator->getEntityBinMomentSnapshotHistoryValues( 1, history_values );
    
    estimator->getEntityBinMomentSnapshotSamplingTimes( 1, sampling_times );
    
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    num_estimator_bins = estimator->getNumberOfBins()*
      estimator->getNumberOfResponseFunctions();
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getEntityBinFirstMomentSnapshots( 1, j, first_moments );
      estimator->getEntityBinSecondMomentSnapshots( 1, j, second_moments );
      estimator->getEntityBinThirdMomentSnapshots( 1, j, third_moments );
      estimator->getEntityBinFourthMomentSnapshots( 1, j, fourth_moments );
      
      FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    }
    
    // Check the total bin moment snapshots
    estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
    estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );
    
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {  
      estimator->getTotalBinFirstMomentSnapshots( j, first_moments );
      estimator->getTotalBinSecondMomentSnapshots( j, second_moments );
      estimator->getTotalBinThirdMomentSnapshots( j, third_moments );
      estimator->getTotalBinFourthMomentSnapshots( j, fourth_moments );
      
      FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    }

    // Check the entity total moment snapshots
    estimator->getEntityTotalMomentSnapshotHistoryValues( 0, history_values );
    
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 0, sampling_times );
    
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    estimator->getEntityTotalFirstMomentSnapshots( 0, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 0, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    
    estimator->getEntityTotalFirstMomentSnapshots( 0, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 1, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    
    estimator->getEntityTotalMomentSnapshotHistoryValues( 1, history_values );
    
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 1, sampling_times );
    
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    estimator->getEntityTotalFirstMomentSnapshots( 1, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 0, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    
    estimator->getEntityTotalFirstMomentSnapshots( 1, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 1, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    
    // Check the total moment snapshots
    estimator->getTotalMomentSnapshotHistoryValues( history_values );
    
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    
    estimator->getTotalMomentSnapshotSamplingTimes( sampling_times );
    
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    estimator->getTotalFirstMomentSnapshots( 0, first_moments );
    estimator->getTotalSecondMomentSnapshots( 0, second_moments );
    estimator->getTotalThirdMomentSnapshots( 0, third_moments );
    estimator->getTotalFourthMomentSnapshots( 0, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    
    estimator->getTotalFirstMomentSnapshots( 1, first_moments );
    estimator->getTotalSecondMomentSnapshots( 1, second_moments );
    estimator->getTotalThirdMomentSnapshots( 1, third_moments );
    estimator->getTotalFourthMomentSnapshots( 1, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that the estimator data can be reduced
FRENSIE_UNIT_TEST( StandardEntityEstimator, reduceData_with_additional_bin_stats )
{
  std::shared_ptr<TestStandardEntityEstimator> estimator;
  initializeStandardEntityEstimator( estimator );

  estimator->enableSnapshotsOnEntityBins();
  estimator->enableSampleMomentHistogramsOnEntityBins();

  for( size_t i = 0; i < 2; ++i )
  {
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

    estimator->takeSnapshot( 5, 1.0 );
  }

  std::shared_ptr<const Utility::Communicator> comm =
    Utility::Communicator::getDefault();

  comm->barrier();

  estimator->reduceData( *comm, 0 );

  unsigned procs = comm->size();

  MonteCarlo::ParticleHistoryObserver::setNumberOfHistories( procs*10 );
  MonteCarlo::ParticleHistoryObserver::setElapsedTime( 2.0 );

  if( comm->rank() == 0 )
  {
    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator->getTotalBinDataSecondMoments();

    Utility::ArrayView<const double> total_bin_third_moments =
      estimator->getTotalBinDataThirdMoments();

    Utility::ArrayView<const double> total_bin_fourth_moments =
      estimator->getTotalBinDataFourthMoments();
    
    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( 32, 4.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                         std::vector<double>( 32, 8.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_bin_third_moments,
                         std::vector<double>( 32, 16.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_bin_fourth_moments,
                         std::vector<double>( 32, 32.0*procs ) );
  
    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator->getEntityBinDataFirstMoments( 0 );
    
    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator->getEntityBinDataSecondMoments( 0 );

    Utility::ArrayView<const double> entity_bin_third_moments =
      estimator->getEntityBinDataThirdMoments( 0 );

    Utility::ArrayView<const double> entity_bin_fourth_moments =
      estimator->getEntityBinDataFourthMoments( 0 );
    
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, 2.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, 2.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                         std::vector<double>( 32, 2.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                         std::vector<double>( 32, 2.0*procs ) );

    entity_bin_first_moments = estimator->getEntityBinDataFirstMoments( 1 );
    entity_bin_second_moments = estimator->getEntityBinDataSecondMoments( 1 );
    entity_bin_third_moments = estimator->getEntityBinDataThirdMoments( 1 );
    entity_bin_fourth_moments = estimator->getEntityBinDataFourthMoments( 1 );
    
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, 2.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, 2.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                         std::vector<double>( 32, 2.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                         std::vector<double>( 32, 2.0*procs ) );
    
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
                         std::vector<double>( 2, 32.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 512.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 8192.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 131072.0*procs ) );
    
    entity_total_first_moments = estimator->getEntityTotalDataFirstMoments( 1 );
    entity_total_second_moments = estimator->getEntityTotalDataSecondMoments( 1 );
    entity_total_third_moments = estimator->getEntityTotalDataThirdMoments( 1 );
    entity_total_fourth_moments = estimator->getEntityTotalDataFourthMoments( 1 );
    
    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 2, 32.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 512.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 8192.0*procs ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 131072.0*procs ) );
    
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
                         std::vector<double>( 2, 64.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_second_moments,
                         std::vector<double>( 2, 2048.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_third_moments,
                         std::vector<double>( 2, 65536.0*procs ) );
    FRENSIE_CHECK_EQUAL( total_fourth_moments,
                         std::vector<double>( 2, 2097152.0*procs ) );
    
    // Check the entity bin histograms
    Utility::SampleMomentHistogram<double> histogram;

    std::vector<double> expected_histogram_bins =
      Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
    std::vector<double> expected_histogram_values;

    {
      std::string expected_histogram_values_string = "{0.0r302, ";
      expected_histogram_values_string += Utility::toString( 2*procs );
      expected_histogram_values_string += ", 0.0r300}";
      
      expected_histogram_values = 
        Utility::fromString<std::vector<double> >( expected_histogram_values_string );
    }

    size_t num_estimator_bins = estimator->getNumberOfBins()*
      estimator->getNumberOfResponseFunctions();
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getEntityBinSampleMomentHistogram( 0, j, histogram );

      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2*procs );
      FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                           expected_histogram_bins );
      FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                           expected_histogram_values );
    }

    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getEntityBinSampleMomentHistogram( 1, j, histogram );
      
      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2*procs );
      FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                           expected_histogram_bins );
      FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                           expected_histogram_values );
    }

    // Check the total bin histograms
    {
      std::string expected_histogram_value_string = "{0.0r305, ";
      expected_histogram_value_string += Utility::toString( 2*procs );
      expected_histogram_value_string += ", 0.0r297}";
      
      expected_histogram_values =
        Utility::fromString<std::vector<double> >( expected_histogram_value_string );
  }
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getTotalBinSampleMomentHistogram( j, histogram );

      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2*procs );
      FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                           expected_histogram_bins );
      FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                           expected_histogram_values );
    }

    // Check the entity total histograms
    {
      std::string expected_histogram_values_string = "{0.0r314, ";
      expected_histogram_values_string += Utility::toString( 2*procs );
      expected_histogram_values_string += ", 0.0r288}";
    
      expected_histogram_values = 
        Utility::fromString<std::vector<double> >( expected_histogram_values_string );
    }
  
    estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2*procs );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
    
    estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2*procs );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
    
    estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2*procs );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
    
    estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2*procs );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );

    // Check the entity total histograms
    {
      std::string expected_histogram_values_string = "{0.0r317, ";
      expected_histogram_values_string += Utility::toString( 2*procs );
      expected_histogram_values_string += ", 0.0r285}";
      
      expected_histogram_values =
        Utility::fromString<std::vector<double> >( expected_histogram_values_string );
    }
  
    estimator->getTotalSampleMomentHistogram( 0, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2*procs );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
    
    estimator->getTotalSampleMomentHistogram( 1, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2*procs );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );

    // Check the entity bin moment snapshots
    std::vector<uint64_t> expected_history_values( 2*procs );
    std::vector<double> expected_sampling_times( 2*procs );
    std::vector<double> expected_first_moments( 2*procs );
    std::vector<double> expected_second_moments( 2*procs );
    std::vector<double> expected_third_moments( 2*procs );
    std::vector<double> expected_fourth_moments( 2*procs );

    for( size_t i = 0; i < 2*procs; ++i )
    {
      expected_history_values[i] = (i+1)*5;
      expected_sampling_times[i] = (i+1)*1.0;
      expected_first_moments[i] = (i+1)*1.0;
      expected_second_moments[i] = (i+1)*1.0;
      expected_third_moments[i] = (i+1)*1.0;
      expected_fourth_moments[i] = (i+1)*1.0;
    }

    std::vector<uint64_t> history_values;
    std::vector<double> sampling_times;

    std::vector<double> first_moments, second_moments, third_moments,
      fourth_moments;

    estimator->getEntityBinMomentSnapshotHistoryValues( 0, history_values );

    estimator->getEntityBinMomentSnapshotSamplingTimes( 0, sampling_times );

    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );

    estimator->getEntityBinMomentSnapshotHistoryValues( 1, history_values );

    estimator->getEntityBinMomentSnapshotSamplingTimes( 1, sampling_times );

    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );

    num_estimator_bins = estimator->getNumberOfBins()*
      estimator->getNumberOfResponseFunctions();
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getEntityBinFirstMomentSnapshots( 0, j, first_moments );
      estimator->getEntityBinSecondMomentSnapshots( 0, j, second_moments );
      estimator->getEntityBinThirdMomentSnapshots( 0, j, third_moments );
      estimator->getEntityBinFourthMomentSnapshots( 0, j, fourth_moments );
      
      FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
      FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
      FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
      FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
      
      estimator->getEntityBinFirstMomentSnapshots( 1, j, first_moments );
      estimator->getEntityBinSecondMomentSnapshots( 1, j, second_moments );
      estimator->getEntityBinThirdMomentSnapshots( 1, j, third_moments );
      estimator->getEntityBinFourthMomentSnapshots( 1, j, fourth_moments );
      
      FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
      FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
      FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
      FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
    }

    // Check the total bin moment snapshots
    estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
    estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );
    
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );

    for( size_t i = 0; i < 2*procs; ++i )
    {
      expected_first_moments[i] = (i+1)*2.0;
      expected_second_moments[i] = (i+1)*4.0;
      expected_third_moments[i] = (i+1)*8.0;
      expected_fourth_moments[i] = (i+1)*16.0;
    }
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {  
      estimator->getTotalBinFirstMomentSnapshots( j, first_moments );
      estimator->getTotalBinSecondMomentSnapshots( j, second_moments );
      estimator->getTotalBinThirdMomentSnapshots( j, third_moments );
      estimator->getTotalBinFourthMomentSnapshots( j, fourth_moments );
      
      FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
      FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
      FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
      FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
    }

    // Check the entity total moment snapshots
    for( size_t i = 0; i < 2*procs; ++i )
    {
      expected_first_moments[i] = (i+1)*16.0;
      expected_second_moments[i] = (i+1)*256.0;
      expected_third_moments[i] = (i+1)*4096.0;
      expected_fourth_moments[i] = (i+1)*65536.0;
    }
    
    estimator->getEntityTotalMomentSnapshotHistoryValues( 0, history_values );

    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 0, sampling_times );
    
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
    
    estimator->getEntityTotalFirstMomentSnapshots( 0, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 0, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
    
    estimator->getEntityTotalFirstMomentSnapshots( 0, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 1, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
    
    estimator->getEntityTotalMomentSnapshotHistoryValues( 1, history_values );
    
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 1, sampling_times );
    
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
    
    estimator->getEntityTotalFirstMomentSnapshots( 1, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 0, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
    
    estimator->getEntityTotalFirstMomentSnapshots( 1, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 1, fourth_moments );

    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );

    // Check the total moment snapshots
    for( size_t i = 0; i < 2*procs; ++i )
    {
      expected_first_moments[i] = (i+1)*32.0;
      expected_second_moments[i] = (i+1)*1024.0;
      expected_third_moments[i] = (i+1)*32768.0;
      expected_fourth_moments[i] = (i+1)*1048576.0;
    }
    
    estimator->getTotalMomentSnapshotHistoryValues( history_values );
    
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    
    estimator->getTotalMomentSnapshotSamplingTimes( sampling_times );
    
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );

    estimator->getTotalFirstMomentSnapshots( 0, first_moments );
    estimator->getTotalSecondMomentSnapshots( 0, second_moments );
    estimator->getTotalThirdMomentSnapshots( 0, third_moments );
    estimator->getTotalFourthMomentSnapshots( 0, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
    
    estimator->getTotalFirstMomentSnapshots( 1, first_moments );
    estimator->getTotalSecondMomentSnapshots( 1, second_moments );
    estimator->getTotalThirdMomentSnapshots( 1, third_moments );
    estimator->getTotalFourthMomentSnapshots( 1, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments ); 
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

    // Check the entity bin histograms
    Utility::SampleMomentHistogram<double> histogram;

    size_t num_estimator_bins = estimator->getNumberOfBins()*
      estimator->getNumberOfResponseFunctions();
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getEntityBinSampleMomentHistogram( 0, j, histogram );
      
      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getEntityBinSampleMomentHistogram( 1, j, histogram );
      
      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }
    
    // Check the total bin histograms
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getTotalBinSampleMomentHistogram( j, histogram );
      
      FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    }
    
    // Check the entity total histograms
    std::vector<double> expected_histogram_bins =
      Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
    
    estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    
    estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    
    estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    
    estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    
    // Check the entity total histograms
    estimator->getTotalSampleMomentHistogram( 0, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    
    estimator->getTotalSampleMomentHistogram( 1, histogram );
    
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    
    // Check the entity bin moment snapshots
    std::vector<uint64_t> history_values;
    std::vector<double> sampling_times;
    
    std::vector<double> first_moments, second_moments, third_moments,
      fourth_moments;
    
    estimator->getEntityBinMomentSnapshotHistoryValues( 0, history_values );
    
    estimator->getEntityBinMomentSnapshotSamplingTimes( 0, sampling_times );
    
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    estimator->getEntityBinMomentSnapshotHistoryValues( 1, history_values );
    
    estimator->getEntityBinMomentSnapshotSamplingTimes( 1, sampling_times );
    
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    num_estimator_bins = estimator->getNumberOfBins()*
      estimator->getNumberOfResponseFunctions();
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {
      estimator->getEntityBinFirstMomentSnapshots( 1, j, first_moments );
      estimator->getEntityBinSecondMomentSnapshots( 1, j, second_moments );
      estimator->getEntityBinThirdMomentSnapshots( 1, j, third_moments );
      estimator->getEntityBinFourthMomentSnapshots( 1, j, fourth_moments );
      
      FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    }
    
    // Check the total bin moment snapshots
    estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
    estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );
    
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    for( size_t j = 0; j < num_estimator_bins; ++j )
    {  
      estimator->getTotalBinFirstMomentSnapshots( j, first_moments );
      estimator->getTotalBinSecondMomentSnapshots( j, second_moments );
      estimator->getTotalBinThirdMomentSnapshots( j, third_moments );
      estimator->getTotalBinFourthMomentSnapshots( j, fourth_moments );
      
      FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
      FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    }

    // Check the entity total moment snapshots
    estimator->getEntityTotalMomentSnapshotHistoryValues( 0, history_values );
    
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 0, sampling_times );
    
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    estimator->getEntityTotalFirstMomentSnapshots( 0, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 0, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    
    estimator->getEntityTotalFirstMomentSnapshots( 0, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 1, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    
    estimator->getEntityTotalMomentSnapshotHistoryValues( 1, history_values );
    
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 1, sampling_times );
    
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    estimator->getEntityTotalFirstMomentSnapshots( 1, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 0, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    
    estimator->getEntityTotalFirstMomentSnapshots( 1, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 1, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    
    // Check the total moment snapshots
    estimator->getTotalMomentSnapshotHistoryValues( history_values );
    
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    
    estimator->getTotalMomentSnapshotSamplingTimes( sampling_times );
    
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
    
    estimator->getTotalFirstMomentSnapshots( 0, first_moments );
    estimator->getTotalSecondMomentSnapshots( 0, second_moments );
    estimator->getTotalThirdMomentSnapshots( 0, third_moments );
    estimator->getTotalFourthMomentSnapshots( 0, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    
    estimator->getTotalFirstMomentSnapshots( 1, first_moments );
    estimator->getTotalSecondMomentSnapshots( 1, second_moments );
    estimator->getTotalThirdMomentSnapshots( 1, third_moments );
    estimator->getTotalFourthMomentSnapshots( 1, fourth_moments );
    
    FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
    FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
  }
}

//---------------------------------------------------------------------------//
// Check that an estimator can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardEntityEstimator,
                                   archive_no_bin_stats,
                                   TestArchives )
{
  if( Utility::GlobalMPISession::rank() == 0 )
  {
    FETCH_TEMPLATE_PARAM( 0, RawOArchive );
    FETCH_TEMPLATE_PARAM( 1, RawIArchive );

    typedef typename std::remove_pointer<RawOArchive>::type OArchive;
    typedef typename std::remove_pointer<RawIArchive>::type IArchive;

    std::string archive_base_name( "test_standard_entity_estimator" );
    std::ostringstream archive_ostream;

    {
      std::unique_ptr<OArchive> oarchive;

      createOArchive( archive_base_name, archive_ostream, oarchive );

      std::shared_ptr<TestStandardEntityEstimator> estimator;
      std::shared_ptr<MonteCarlo::Estimator> estimator_base;

      initializeStandardEntityEstimator( estimator );
      estimator_base = estimator;

      for( size_t i = 0; i < 2; ++i )
        {
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
      
          estimator->takeSnapshot( 5, 1.0 );
        }

      FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( estimator ) );
      FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( estimator_base ) );
    }

    // Copy the archive ostream to an istream
    std::istringstream archive_istream( archive_ostream.str() );

    // Load the archived distributions
    std::unique_ptr<IArchive> iarchive;

    createIArchive( archive_istream, iarchive );

    std::shared_ptr<TestStandardEntityEstimator> estimator;
    std::shared_ptr<MonteCarlo::Estimator> estimator_base;

    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator ) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_base ) );

    iarchive.reset();

    FRENSIE_CHECK( estimator.get() == estimator_base.get() );
    FRENSIE_CHECK_EQUAL( estimator->getId(), 0 );
    FRENSIE_CHECK_EQUAL( estimator->getMultiplier(), 10.0 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 16 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfResponseFunctions(), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getParticleTypes().size(), 1 );
    FRENSIE_CHECK( estimator->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator->getParticleTypes().end() );

    std::set<MonteCarlo::Estimator::EntityId> entity_ids;
    estimator->getEntityIds( entity_ids );

    FRENSIE_CHECK_EQUAL( entity_ids.size(), 2 );
    FRENSIE_CHECK( entity_ids.find( 0 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 1 ) != entity_ids.end() );

    FRENSIE_CHECK_EQUAL( estimator->getEntityNormConstant( 0 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator->getEntityNormConstant( 1 ), 2.0 );
    FRENSIE_CHECK_EQUAL( estimator->getTotalNormConstant(), 3.0 );

    FRENSIE_CHECK( !estimator->areSnapshotsOnEntityBinsEnabled() );
    FRENSIE_CHECK( !estimator->areSampleMomentHistogramsOnEntityBinsEnabled() );

    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator->getTotalBinDataFirstMoments();
  
    Utility::ArrayView<const double> total_bin_second_moments =
      estimator->getTotalBinDataSecondMoments();
  
    Utility::ArrayView<const double> total_bin_third_moments =
      estimator->getTotalBinDataThirdMoments();
  
    Utility::ArrayView<const double> total_bin_fourth_moments =
      estimator->getTotalBinDataFourthMoments();
  
    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( 32, 4.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                         std::vector<double>( 32, 8.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_third_moments,
                         std::vector<double>( 32, 16.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_fourth_moments,
                         std::vector<double>( 32, 32.0 ) );
  
    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator->getEntityBinDataFirstMoments( 0 );
  
    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator->getEntityBinDataSecondMoments( 0 );
  
    Utility::ArrayView<const double> entity_bin_third_moments =
      estimator->getEntityBinDataThirdMoments( 0 );
  
    Utility::ArrayView<const double> entity_bin_fourth_moments =
      estimator->getEntityBinDataFourthMoments( 0 );
  
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                         std::vector<double>( 32, 2.0 ) );
  
    entity_bin_first_moments = estimator->getEntityBinDataFirstMoments( 1 );
    entity_bin_second_moments = estimator->getEntityBinDataSecondMoments( 1 );
    entity_bin_third_moments = estimator->getEntityBinDataThirdMoments( 1 );
    entity_bin_fourth_moments = estimator->getEntityBinDataFourthMoments( 1 );
  
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                         std::vector<double>( 32, 2.0 ) );
  
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
                         std::vector<double>( 2, 32.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 512.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 8192.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 131072.0 ) );
  
    entity_total_first_moments = estimator->getEntityTotalDataFirstMoments( 1 );
    entity_total_second_moments = estimator->getEntityTotalDataSecondMoments( 1 );
    entity_total_third_moments = estimator->getEntityTotalDataThirdMoments( 1 );
    entity_total_fourth_moments = estimator->getEntityTotalDataFourthMoments( 1 );
  
    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 2, 32.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 512.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 8192.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 131072.0 ) );
  
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
                         std::vector<double>( 2, 64.0 ) );
    FRENSIE_CHECK_EQUAL( total_second_moments,
                         std::vector<double>( 2, 2048.0 ) );
    FRENSIE_CHECK_EQUAL( total_third_moments,
                         std::vector<double>( 2, 65536.0 ) );
    FRENSIE_CHECK_EQUAL( total_fourth_moments,
                         std::vector<double>( 2, 2097152.0 ) );
  
    // Check the entity bin histograms
    Utility::SampleMomentHistogram<double> histogram;
  
    size_t num_estimator_bins = estimator->getNumberOfBins()*
      estimator->getNumberOfResponseFunctions();
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getEntityBinSampleMomentHistogram( 0, j, histogram );
    
        FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
      }
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getEntityBinSampleMomentHistogram( 1, j, histogram );
    
        FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
      }
  
    // Check the total bin histograms
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getTotalBinSampleMomentHistogram( j, histogram );
    
        FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
      }
  
    // Check the entity total histograms
    std::vector<double> expected_histogram_bins =
      Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
    std::vector<double> expected_histogram_values;
  
    {
      std::string expected_histogram_values_string = "{0.0r314, ";
      expected_histogram_values_string += Utility::toString( 2 );
      expected_histogram_values_string += ", 0.0r288}";
    
      expected_histogram_values = 
        Utility::fromString<std::vector<double> >( expected_histogram_values_string );
    }
  
    estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    // Check the entity total histograms
    {
      std::string expected_histogram_values_string = "{0.0r317, ";
      expected_histogram_values_string += Utility::toString( 2 );
      expected_histogram_values_string += ", 0.0r285}";
    
      expected_histogram_values =
        Utility::fromString<std::vector<double> >( expected_histogram_values_string );
    }
  
    estimator->getTotalSampleMomentHistogram( 0, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getTotalSampleMomentHistogram( 1, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    // Check the entity bin moment snapshots
    std::vector<uint64_t> history_values;
    std::vector<double> sampling_times;
  
    std::vector<double> first_moments, second_moments, third_moments,
      fourth_moments;
  
    estimator->getEntityBinMomentSnapshotHistoryValues( 0, history_values );
  
    estimator->getEntityBinMomentSnapshotSamplingTimes( 0, sampling_times );
  
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
  
    estimator->getEntityBinMomentSnapshotHistoryValues( 1, history_values );
  
    estimator->getEntityBinMomentSnapshotSamplingTimes( 1, sampling_times );
  
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
  
    num_estimator_bins = estimator->getNumberOfBins()*
      estimator->getNumberOfResponseFunctions();
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getEntityBinFirstMomentSnapshots( 0, j, first_moments );
        estimator->getEntityBinSecondMomentSnapshots( 0, j, second_moments );
        estimator->getEntityBinThirdMomentSnapshots( 0, j, third_moments );
        estimator->getEntityBinFourthMomentSnapshots( 0, j, fourth_moments );
    
        FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    
        estimator->getEntityBinFirstMomentSnapshots( 1, j, first_moments );
        estimator->getEntityBinSecondMomentSnapshots( 1, j, second_moments );
        estimator->getEntityBinThirdMomentSnapshots( 1, j, third_moments );
        estimator->getEntityBinFourthMomentSnapshots( 1, j, fourth_moments );
    
        FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
      }
  
    // Check the total bin moment snapshots
    estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
    estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );
  
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {  
        estimator->getTotalBinFirstMomentSnapshots( j, first_moments );
        estimator->getTotalBinSecondMomentSnapshots( j, second_moments );
        estimator->getTotalBinThirdMomentSnapshots( j, third_moments );
        estimator->getTotalBinFourthMomentSnapshots( j, fourth_moments );
    
        FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
      }
  
    // Check the entity total moment snapshots
    std::vector<uint64_t> expected_history_values( {5, 10} );
    std::vector<double> expected_sampling_times( {1.0, 2.0}  );
    std::vector<double> expected_first_moments( {16.0, 32.0} );
    std::vector<double> expected_second_moments( {256.0, 512.0} );
    std::vector<double> expected_third_moments( {4096.0, 8192.0} );
    std::vector<double> expected_fourth_moments( {65536.0, 131072.0} );
  
    estimator->getEntityTotalMomentSnapshotHistoryValues( 0, history_values );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
  
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 0, sampling_times );
  
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    estimator->getEntityTotalFirstMomentSnapshots( 0, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 0, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getEntityTotalFirstMomentSnapshots( 0, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 1, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getEntityTotalMomentSnapshotHistoryValues( 1, history_values );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
  
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 1, sampling_times );
  
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    estimator->getEntityTotalFirstMomentSnapshots( 1, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 0, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getEntityTotalFirstMomentSnapshots( 1, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 1, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    // Check the total moment snapshots
    expected_first_moments = std::vector<double>( {32.0, 64.0} );
    expected_second_moments = std::vector<double>( {1024.0, 2048.0} );
    expected_third_moments = std::vector<double>( {32768.0, 65536} );
    expected_fourth_moments = std::vector<double>( {1048576.0, 2097152} );
  
    estimator->getTotalMomentSnapshotHistoryValues( history_values );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
  
    estimator->getTotalMomentSnapshotSamplingTimes( sampling_times );
  
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    estimator->getTotalFirstMomentSnapshots( 0, first_moments );
    estimator->getTotalSecondMomentSnapshots( 0, second_moments );
    estimator->getTotalThirdMomentSnapshots( 0, third_moments );
    estimator->getTotalFourthMomentSnapshots( 0, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getTotalFirstMomentSnapshots( 1, first_moments );
    estimator->getTotalSecondMomentSnapshots( 1, second_moments );
    estimator->getTotalThirdMomentSnapshots( 1, third_moments );
    estimator->getTotalFourthMomentSnapshots( 1, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  }
}

//---------------------------------------------------------------------------//
// Check that an estimator can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardEntityEstimator,
                                   archive_with_bin_histograms,
                                   TestArchives )
{
  if( Utility::GlobalMPISession::rank() == 0 )
  {
    FETCH_TEMPLATE_PARAM( 0, RawOArchive );
    FETCH_TEMPLATE_PARAM( 1, RawIArchive );

    typedef typename std::remove_pointer<RawOArchive>::type OArchive;
    typedef typename std::remove_pointer<RawIArchive>::type IArchive;

    std::string archive_base_name( "test_standard_entity_estimator" );
    std::ostringstream archive_ostream;

    {
      std::unique_ptr<OArchive> oarchive;

      createOArchive( archive_base_name, archive_ostream, oarchive );

      std::shared_ptr<TestStandardEntityEstimator> estimator;
      std::shared_ptr<MonteCarlo::Estimator> estimator_base;

      initializeStandardEntityEstimator( estimator );
      estimator_base = estimator;

      estimator->enableSampleMomentHistogramsOnEntityBins();

      for( size_t i = 0; i < 2; ++i )
        {
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
      
          estimator->takeSnapshot( 5, 1.0 );
        }

      FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( estimator ) );
      FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( estimator_base ) );
    }

    // Copy the archive ostream to an istream
    std::istringstream archive_istream( archive_ostream.str() );

    // Load the archived distributions
    std::unique_ptr<IArchive> iarchive;

    createIArchive( archive_istream, iarchive );

    std::shared_ptr<TestStandardEntityEstimator> estimator;
    std::shared_ptr<MonteCarlo::Estimator> estimator_base;

    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator ) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_base ) );

    iarchive.reset();

    FRENSIE_CHECK( estimator.get() == estimator_base.get() );
    FRENSIE_CHECK_EQUAL( estimator->getId(), 0 );
    FRENSIE_CHECK_EQUAL( estimator->getMultiplier(), 10.0 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 16 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfResponseFunctions(), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getParticleTypes().size(), 1 );
    FRENSIE_CHECK( estimator->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator->getParticleTypes().end() );

    std::set<MonteCarlo::Estimator::EntityId> entity_ids;
    estimator->getEntityIds( entity_ids );

    FRENSIE_CHECK_EQUAL( entity_ids.size(), 2 );
    FRENSIE_CHECK( entity_ids.find( 0 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 1 ) != entity_ids.end() );

    FRENSIE_CHECK_EQUAL( estimator->getEntityNormConstant( 0 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator->getEntityNormConstant( 1 ), 2.0 );
    FRENSIE_CHECK_EQUAL( estimator->getTotalNormConstant(), 3.0 );

    FRENSIE_CHECK( !estimator->areSnapshotsOnEntityBinsEnabled() );
    FRENSIE_CHECK( estimator->areSampleMomentHistogramsOnEntityBinsEnabled() );

    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator->getTotalBinDataSecondMoments();
  
    Utility::ArrayView<const double> total_bin_third_moments =
      estimator->getTotalBinDataThirdMoments();
  
    Utility::ArrayView<const double> total_bin_fourth_moments =
      estimator->getTotalBinDataFourthMoments();
  
    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( 32, 4.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                         std::vector<double>( 32, 8.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_third_moments,
                         std::vector<double>( 32, 16.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_fourth_moments,
                         std::vector<double>( 32, 32.0 ) );
  
    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator->getEntityBinDataFirstMoments( 0 );
  
    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator->getEntityBinDataSecondMoments( 0 );
  
    Utility::ArrayView<const double> entity_bin_third_moments =
      estimator->getEntityBinDataThirdMoments( 0 );
  
    Utility::ArrayView<const double> entity_bin_fourth_moments =
      estimator->getEntityBinDataFourthMoments( 0 );
  
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                         std::vector<double>( 32, 2.0 ) );
  
    entity_bin_first_moments = estimator->getEntityBinDataFirstMoments( 1 );
    entity_bin_second_moments = estimator->getEntityBinDataSecondMoments( 1 );
    entity_bin_third_moments = estimator->getEntityBinDataThirdMoments( 1 );
    entity_bin_fourth_moments = estimator->getEntityBinDataFourthMoments( 1 );
  
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                         std::vector<double>( 32, 2.0 ) );
  
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
                         std::vector<double>( 2, 32.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 512.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 8192.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 131072.0 ) );
  
    entity_total_first_moments = estimator->getEntityTotalDataFirstMoments( 1 );
    entity_total_second_moments = estimator->getEntityTotalDataSecondMoments( 1 );
    entity_total_third_moments = estimator->getEntityTotalDataThirdMoments( 1 );
    entity_total_fourth_moments = estimator->getEntityTotalDataFourthMoments( 1 );
  
    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 2, 32.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 512.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 8192.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 131072.0 ) );
  
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
                         std::vector<double>( 2, 64.0 ) );
    FRENSIE_CHECK_EQUAL( total_second_moments,
                         std::vector<double>( 2, 2048.0 ) );
    FRENSIE_CHECK_EQUAL( total_third_moments,
                         std::vector<double>( 2, 65536.0 ) );
    FRENSIE_CHECK_EQUAL( total_fourth_moments,
                         std::vector<double>( 2, 2097152.0 ) );
  
    // Check the entity bin histograms
    Utility::SampleMomentHistogram<double> histogram;
  
    std::vector<double> expected_histogram_bins =
      Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
    std::vector<double> expected_histogram_values;
  
    {
      std::string expected_histogram_values_string = "{0.0r302, ";
      expected_histogram_values_string += Utility::toString( 2 );
      expected_histogram_values_string += ", 0.0r300}";
    
      expected_histogram_values = 
        Utility::fromString<std::vector<double> >( expected_histogram_values_string );
    }
  
    size_t num_estimator_bins = estimator->getNumberOfBins()*
      estimator->getNumberOfResponseFunctions();
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getEntityBinSampleMomentHistogram( 0, j, histogram );
    
        FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
        FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                             expected_histogram_bins );
        FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                             expected_histogram_values );
      }
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getEntityBinSampleMomentHistogram( 1, j, histogram );
    
        FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
        FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                             expected_histogram_bins );
        FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                             expected_histogram_values );
      }
  
    // Check the total bin histograms
    {
      std::string expected_histogram_value_string = "{0.0r305, ";
      expected_histogram_value_string += Utility::toString( 2 );
      expected_histogram_value_string += ", 0.0r297}";
    
      expected_histogram_values =
        Utility::fromString<std::vector<double> >( expected_histogram_value_string );
    }
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getTotalBinSampleMomentHistogram( j, histogram );
    
        FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
        FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                             expected_histogram_bins );
        FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                             expected_histogram_values );
      }
  
    // Check the entity total histograms
    {
      std::string expected_histogram_values_string = "{0.0r314, ";
      expected_histogram_values_string += Utility::toString( 2 );
      expected_histogram_values_string += ", 0.0r288}";
    
      expected_histogram_values = 
        Utility::fromString<std::vector<double> >( expected_histogram_values_string );
    }
  
    estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    // Check the entity total histograms
    {
      std::string expected_histogram_values_string = "{0.0r317, ";
      expected_histogram_values_string += Utility::toString( 2 );
      expected_histogram_values_string += ", 0.0r285}";
    
      expected_histogram_values =
        Utility::fromString<std::vector<double> >( expected_histogram_values_string );
    }
  
    estimator->getTotalSampleMomentHistogram( 0, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getTotalSampleMomentHistogram( 1, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    // Check the entity bin moment snapshots
    std::vector<uint64_t> history_values;
    std::vector<double> sampling_times;
  
    std::vector<double> first_moments, second_moments, third_moments,
      fourth_moments;
  
    estimator->getEntityBinMomentSnapshotHistoryValues( 0, history_values );
  
    estimator->getEntityBinMomentSnapshotSamplingTimes( 0, sampling_times );
  
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
  
    estimator->getEntityBinMomentSnapshotHistoryValues( 1, history_values );
  
    estimator->getEntityBinMomentSnapshotSamplingTimes( 1, sampling_times );
  
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
  
    num_estimator_bins = estimator->getNumberOfBins()*
      estimator->getNumberOfResponseFunctions();
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getEntityBinFirstMomentSnapshots( 0, j, first_moments );
        estimator->getEntityBinSecondMomentSnapshots( 0, j, second_moments );
        estimator->getEntityBinThirdMomentSnapshots( 0, j, third_moments );
        estimator->getEntityBinFourthMomentSnapshots( 0, j, fourth_moments );
    
        FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
    
        estimator->getEntityBinFirstMomentSnapshots( 1, j, first_moments );
        estimator->getEntityBinSecondMomentSnapshots( 1, j, second_moments );
        estimator->getEntityBinThirdMomentSnapshots( 1, j, third_moments );
        estimator->getEntityBinFourthMomentSnapshots( 1, j, fourth_moments );
    
        FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
      }
  
    // Check the total bin moment snapshots
    estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
    estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );
  
    FRENSIE_CHECK_EQUAL( history_values.size(), 0 );
    FRENSIE_CHECK_EQUAL( sampling_times.size(), 0 );
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {  
        estimator->getTotalBinFirstMomentSnapshots( j, first_moments );
        estimator->getTotalBinSecondMomentSnapshots( j, second_moments );
        estimator->getTotalBinThirdMomentSnapshots( j, third_moments );
        estimator->getTotalBinFourthMomentSnapshots( j, fourth_moments );
    
        FRENSIE_CHECK_EQUAL( first_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( second_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( third_moments.size(), 0 );
        FRENSIE_CHECK_EQUAL( fourth_moments.size(), 0 );
      }
  
    // Check the entity total moment snapshots
    std::vector<uint64_t> expected_history_values( {5, 10} );
    std::vector<double> expected_sampling_times( {1.0, 2.0}  );
    std::vector<double> expected_first_moments( 2 );
    std::vector<double> expected_second_moments( 2 );
    std::vector<double> expected_third_moments( 2 );
    std::vector<double> expected_fourth_moments( 2 );
  
    for( size_t i = 0; i < 2; ++i )
      {
        expected_first_moments[i] = (i+1)*16.0;
        expected_second_moments[i] = (i+1)*256.0;
        expected_third_moments[i] = (i+1)*4096.0;
        expected_fourth_moments[i] = (i+1)*65536.0;
      }
  
    estimator->getEntityTotalMomentSnapshotHistoryValues( 0, history_values );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
  
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 0, sampling_times );
  
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    estimator->getEntityTotalFirstMomentSnapshots( 0, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 0, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getEntityTotalFirstMomentSnapshots( 0, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 1, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getEntityTotalMomentSnapshotHistoryValues( 1, history_values );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
  
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 1, sampling_times );
  
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    estimator->getEntityTotalFirstMomentSnapshots( 1, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 0, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getEntityTotalFirstMomentSnapshots( 1, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 1, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    // Check the total moment snapshots
    for( size_t i = 0; i < 2; ++i )
      {
        expected_first_moments[i] = (i+1)*32.0;
        expected_second_moments[i] = (i+1)*1024.0;
        expected_third_moments[i] = (i+1)*32768.0;
        expected_fourth_moments[i] = (i+1)*1048576.0;
      }
  
    estimator->getTotalMomentSnapshotHistoryValues( history_values );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
  
    estimator->getTotalMomentSnapshotSamplingTimes( sampling_times );
  
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    estimator->getTotalFirstMomentSnapshots( 0, first_moments );
    estimator->getTotalSecondMomentSnapshots( 0, second_moments );
    estimator->getTotalThirdMomentSnapshots( 0, third_moments );
    estimator->getTotalFourthMomentSnapshots( 0, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getTotalFirstMomentSnapshots( 1, first_moments );
    estimator->getTotalSecondMomentSnapshots( 1, second_moments );
    estimator->getTotalThirdMomentSnapshots( 1, third_moments );
    estimator->getTotalFourthMomentSnapshots( 1, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  }
}

//---------------------------------------------------------------------------//
// Check that an estimator can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardEntityEstimator,
                                   archive_with_bin_snapshots,
                                   TestArchives )
{
  if( Utility::GlobalMPISession::rank() == 0 )
  {
    FETCH_TEMPLATE_PARAM( 0, RawOArchive );
    FETCH_TEMPLATE_PARAM( 1, RawIArchive );

    typedef typename std::remove_pointer<RawOArchive>::type OArchive;
    typedef typename std::remove_pointer<RawIArchive>::type IArchive;

    std::string archive_base_name( "test_standard_entity_estimator" );
    std::ostringstream archive_ostream;

    {
      std::unique_ptr<OArchive> oarchive;

      createOArchive( archive_base_name, archive_ostream, oarchive );

      std::shared_ptr<TestStandardEntityEstimator> estimator;
      std::shared_ptr<MonteCarlo::Estimator> estimator_base;

      initializeStandardEntityEstimator( estimator );
      estimator_base = estimator;

      estimator->enableSnapshotsOnEntityBins();

      for( size_t i = 0; i < 2; ++i )
        {
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
      
          estimator->takeSnapshot( 5, 1.0 );
        }

      FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( estimator ) );
      FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( estimator_base ) );
    }

    // Copy the archive ostream to an istream
    std::istringstream archive_istream( archive_ostream.str() );

    // Load the archived distributions
    std::unique_ptr<IArchive> iarchive;

    createIArchive( archive_istream, iarchive );

    std::shared_ptr<TestStandardEntityEstimator> estimator;
    std::shared_ptr<MonteCarlo::Estimator> estimator_base;

    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator ) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_base ) );

    iarchive.reset();

    FRENSIE_CHECK( estimator.get() == estimator_base.get() );
    FRENSIE_CHECK_EQUAL( estimator->getId(), 0 );
    FRENSIE_CHECK_EQUAL( estimator->getMultiplier(), 10.0 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 16 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfResponseFunctions(), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getParticleTypes().size(), 1 );
    FRENSIE_CHECK( estimator->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator->getParticleTypes().end() );

    std::set<MonteCarlo::Estimator::EntityId> entity_ids;
    estimator->getEntityIds( entity_ids );

    FRENSIE_CHECK_EQUAL( entity_ids.size(), 2 );
    FRENSIE_CHECK( entity_ids.find( 0 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 1 ) != entity_ids.end() );

    FRENSIE_CHECK_EQUAL( estimator->getEntityNormConstant( 0 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator->getEntityNormConstant( 1 ), 2.0 );
    FRENSIE_CHECK_EQUAL( estimator->getTotalNormConstant(), 3.0 );

    FRENSIE_CHECK( estimator->areSnapshotsOnEntityBinsEnabled() );
    FRENSIE_CHECK( !estimator->areSampleMomentHistogramsOnEntityBinsEnabled() );

    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator->getTotalBinDataSecondMoments();
  
    Utility::ArrayView<const double> total_bin_third_moments =
      estimator->getTotalBinDataThirdMoments();
  
    Utility::ArrayView<const double> total_bin_fourth_moments =
      estimator->getTotalBinDataFourthMoments();
  
    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( 32, 4.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                         std::vector<double>( 32, 8.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_third_moments,
                         std::vector<double>( 32, 16.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_fourth_moments,
                         std::vector<double>( 32, 32.0 ) );
  
    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator->getEntityBinDataFirstMoments( 0 );
  
    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator->getEntityBinDataSecondMoments( 0 );
  
    Utility::ArrayView<const double> entity_bin_third_moments =
      estimator->getEntityBinDataThirdMoments( 0 );
  
    Utility::ArrayView<const double> entity_bin_fourth_moments =
      estimator->getEntityBinDataFourthMoments( 0 );
  
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                         std::vector<double>( 32, 2.0 ) );
  
    entity_bin_first_moments = estimator->getEntityBinDataFirstMoments( 1 );
    entity_bin_second_moments = estimator->getEntityBinDataSecondMoments( 1 );
    entity_bin_third_moments = estimator->getEntityBinDataThirdMoments( 1 );
    entity_bin_fourth_moments = estimator->getEntityBinDataFourthMoments( 1 );
  
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                         std::vector<double>( 32, 2.0 ) );
  
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
                         std::vector<double>( 2, 32.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 512.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 8192.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 131072.0 ) );
  
    entity_total_first_moments = estimator->getEntityTotalDataFirstMoments( 1 );
    entity_total_second_moments = estimator->getEntityTotalDataSecondMoments( 1 );
    entity_total_third_moments = estimator->getEntityTotalDataThirdMoments( 1 );
    entity_total_fourth_moments = estimator->getEntityTotalDataFourthMoments( 1 );
  
    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 2, 32.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 512.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 8192.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 131072.0 ) );
  
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
                         std::vector<double>( 2, 64.0 ) );
    FRENSIE_CHECK_EQUAL( total_second_moments,
                         std::vector<double>( 2, 2048.0 ) );
    FRENSIE_CHECK_EQUAL( total_third_moments,
                         std::vector<double>( 2, 65536.0 ) );
    FRENSIE_CHECK_EQUAL( total_fourth_moments,
                         std::vector<double>( 2, 2097152.0 ) );

    // Check the entity bin histograms
    Utility::SampleMomentHistogram<double> histogram;
  
    size_t num_estimator_bins = estimator->getNumberOfBins()*
      estimator->getNumberOfResponseFunctions();
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getEntityBinSampleMomentHistogram( 0, j, histogram );
    
        FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
      }
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getEntityBinSampleMomentHistogram( 1, j, histogram );
    
        FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
      }
  
    // Check the total bin histograms
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getTotalBinSampleMomentHistogram( j, histogram );
    
        FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 0 );
      }
  
    // Check the entity total histograms
    std::vector<double> expected_histogram_bins =
      Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
    std::vector<double> expected_histogram_values;
  
    {
      std::string expected_histogram_values_string = "{0.0r314, ";
      expected_histogram_values_string += Utility::toString( 2 );
      expected_histogram_values_string += ", 0.0r288}";
    
      expected_histogram_values = 
        Utility::fromString<std::vector<double> >( expected_histogram_values_string );
    }
  
    estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    // Check the entity total histograms
    {
      std::string expected_histogram_values_string = "{0.0r317, ";
      expected_histogram_values_string += Utility::toString( 2 );
      expected_histogram_values_string += ", 0.0r285}";
    
      expected_histogram_values =
        Utility::fromString<std::vector<double> >( expected_histogram_values_string );
    }
  
    estimator->getTotalSampleMomentHistogram( 0, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getTotalSampleMomentHistogram( 1, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    // Check the entity bin moment snapshots
    std::vector<uint64_t> expected_history_values( 2 );
    std::vector<double> expected_sampling_times( 2 );
    std::vector<double> expected_first_moments( 2 );
    std::vector<double> expected_second_moments( 2 );
    std::vector<double> expected_third_moments( 2 );
    std::vector<double> expected_fourth_moments( 2 );
  
    for( size_t i = 0; i < 2; ++i )
      {
        expected_history_values[i] = (i+1)*5;
        expected_sampling_times[i] = (i+1)*1.0;
        expected_first_moments[i] = (i+1)*1.0;
        expected_second_moments[i] = (i+1)*1.0;
        expected_third_moments[i] = (i+1)*1.0;
        expected_fourth_moments[i] = (i+1)*1.0;
      }
  
    std::vector<uint64_t> history_values;
    std::vector<double> sampling_times;
  
    std::vector<double> first_moments, second_moments, third_moments,
      fourth_moments;
  
    estimator->getEntityBinMomentSnapshotHistoryValues( 0, history_values );
  
    estimator->getEntityBinMomentSnapshotSamplingTimes( 0, sampling_times );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    estimator->getEntityBinMomentSnapshotHistoryValues( 1, history_values );
  
    estimator->getEntityBinMomentSnapshotSamplingTimes( 1, sampling_times );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    num_estimator_bins = estimator->getNumberOfBins()*
      estimator->getNumberOfResponseFunctions();
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getEntityBinFirstMomentSnapshots( 0, j, first_moments );
        estimator->getEntityBinSecondMomentSnapshots( 0, j, second_moments );
        estimator->getEntityBinThirdMomentSnapshots( 0, j, third_moments );
        estimator->getEntityBinFourthMomentSnapshots( 0, j, fourth_moments );
    
        FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
        FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
        FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
        FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
    
        estimator->getEntityBinFirstMomentSnapshots( 1, j, first_moments );
        estimator->getEntityBinSecondMomentSnapshots( 1, j, second_moments );
        estimator->getEntityBinThirdMomentSnapshots( 1, j, third_moments );
        estimator->getEntityBinFourthMomentSnapshots( 1, j, fourth_moments );
    
        FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
        FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
        FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
        FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
      }
  
    // Check the total bin moment snapshots
    estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
    estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    for( size_t i = 0; i < 2; ++i )
      {
        expected_first_moments[i] = (i+1)*2.0;
        expected_second_moments[i] = (i+1)*4.0;
        expected_third_moments[i] = (i+1)*8.0;
        expected_fourth_moments[i] = (i+1)*16.0;
      }
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {  
        estimator->getTotalBinFirstMomentSnapshots( j, first_moments );
        estimator->getTotalBinSecondMomentSnapshots( j, second_moments );
        estimator->getTotalBinThirdMomentSnapshots( j, third_moments );
        estimator->getTotalBinFourthMomentSnapshots( j, fourth_moments );
    
        FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
        FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
        FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
        FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
      }
  
    // Check the entity total moment snapshots
    for( size_t i = 0; i < 2; ++i )
      {
        expected_first_moments[i] = (i+1)*16.0;
        expected_second_moments[i] = (i+1)*256.0;
        expected_third_moments[i] = (i+1)*4096.0;
        expected_fourth_moments[i] = (i+1)*65536.0;
      }
  
    estimator->getEntityTotalMomentSnapshotHistoryValues( 0, history_values );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
  
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 0, sampling_times );
  
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    estimator->getEntityTotalFirstMomentSnapshots( 0, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 0, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getEntityTotalFirstMomentSnapshots( 0, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 1, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getEntityTotalMomentSnapshotHistoryValues( 1, history_values );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
  
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 1, sampling_times );
  
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    estimator->getEntityTotalFirstMomentSnapshots( 1, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 0, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getEntityTotalFirstMomentSnapshots( 1, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 1, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    // Check the total moment snapshots
    for( size_t i = 0; i < 2; ++i )
      {
        expected_first_moments[i] = (i+1)*32.0;
        expected_second_moments[i] = (i+1)*1024.0;
        expected_third_moments[i] = (i+1)*32768.0;
        expected_fourth_moments[i] = (i+1)*1048576.0;
      }
  
    estimator->getTotalMomentSnapshotHistoryValues( history_values );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
  
    estimator->getTotalMomentSnapshotSamplingTimes( sampling_times );
  
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    estimator->getTotalFirstMomentSnapshots( 0, first_moments );
    estimator->getTotalSecondMomentSnapshots( 0, second_moments );
    estimator->getTotalThirdMomentSnapshots( 0, third_moments );
    estimator->getTotalFourthMomentSnapshots( 0, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getTotalFirstMomentSnapshots( 1, first_moments );
    estimator->getTotalSecondMomentSnapshots( 1, second_moments );
    estimator->getTotalThirdMomentSnapshots( 1, third_moments );
    estimator->getTotalFourthMomentSnapshots( 1, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  }
}

//---------------------------------------------------------------------------//
// Check that an estimator can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( StandardEntityEstimator,
                                   archive_with_bin_stats,
                                   TestArchives )
{
  if( Utility::GlobalMPISession::rank() == 0 )
  {
    FETCH_TEMPLATE_PARAM( 0, RawOArchive );
    FETCH_TEMPLATE_PARAM( 1, RawIArchive );

    typedef typename std::remove_pointer<RawOArchive>::type OArchive;
    typedef typename std::remove_pointer<RawIArchive>::type IArchive;

    std::string archive_base_name( "test_standard_entity_estimator" );
    std::ostringstream archive_ostream;

    {
      std::unique_ptr<OArchive> oarchive;

      createOArchive( archive_base_name, archive_ostream, oarchive );

      std::shared_ptr<TestStandardEntityEstimator> estimator;
      std::shared_ptr<MonteCarlo::Estimator> estimator_base;

      initializeStandardEntityEstimator( estimator );
      estimator_base = estimator;

      estimator->enableSnapshotsOnEntityBins();
      estimator->enableSampleMomentHistogramsOnEntityBins();

      for( size_t i = 0; i < 2; ++i )
        {
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
      
          estimator->takeSnapshot( 5, 1.0 );
        }

      FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( estimator ) );
      FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( estimator_base ) );
    }

    // Copy the archive ostream to an istream
    std::istringstream archive_istream( archive_ostream.str() );

    // Load the archived distributions
    std::unique_ptr<IArchive> iarchive;

    createIArchive( archive_istream, iarchive );

    std::shared_ptr<TestStandardEntityEstimator> estimator;
    std::shared_ptr<MonteCarlo::Estimator> estimator_base;

    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator ) );
    FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( estimator_base ) );

    iarchive.reset();

    FRENSIE_CHECK( estimator.get() == estimator_base.get() );
    FRENSIE_CHECK_EQUAL( estimator->getId(), 0 );
    FRENSIE_CHECK_EQUAL( estimator->getMultiplier(), 10.0 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins(), 16 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getNumberOfResponseFunctions(), 2 );
    FRENSIE_CHECK_EQUAL( estimator->getParticleTypes().size(), 1 );
    FRENSIE_CHECK( estimator->getParticleTypes().find( MonteCarlo::PHOTON ) != estimator->getParticleTypes().end() );

    std::set<MonteCarlo::Estimator::EntityId> entity_ids;
    estimator->getEntityIds( entity_ids );

    FRENSIE_CHECK_EQUAL( entity_ids.size(), 2 );
    FRENSIE_CHECK( entity_ids.find( 0 ) != entity_ids.end() );
    FRENSIE_CHECK( entity_ids.find( 1 ) != entity_ids.end() );

    FRENSIE_CHECK_EQUAL( estimator->getEntityNormConstant( 0 ), 1.0 );
    FRENSIE_CHECK_EQUAL( estimator->getEntityNormConstant( 1 ), 2.0 );
    FRENSIE_CHECK_EQUAL( estimator->getTotalNormConstant(), 3.0 );

    FRENSIE_CHECK( estimator->areSnapshotsOnEntityBinsEnabled() );
    FRENSIE_CHECK( estimator->areSampleMomentHistogramsOnEntityBinsEnabled() );

    // Check the total bin data moments
    Utility::ArrayView<const double> total_bin_first_moments =
      estimator->getTotalBinDataFirstMoments();

    Utility::ArrayView<const double> total_bin_second_moments =
      estimator->getTotalBinDataSecondMoments();
  
    Utility::ArrayView<const double> total_bin_third_moments =
      estimator->getTotalBinDataThirdMoments();
  
    Utility::ArrayView<const double> total_bin_fourth_moments =
      estimator->getTotalBinDataFourthMoments();
  
    FRENSIE_CHECK_EQUAL( total_bin_first_moments,
                         std::vector<double>( 32, 4.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_second_moments,
                         std::vector<double>( 32, 8.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_third_moments,
                         std::vector<double>( 32, 16.0 ) );
    FRENSIE_CHECK_EQUAL( total_bin_fourth_moments,
                         std::vector<double>( 32, 32.0 ) );
  
    // Check the entity bin data moments
    Utility::ArrayView<const double> entity_bin_first_moments =
      estimator->getEntityBinDataFirstMoments( 0 );
  
    Utility::ArrayView<const double> entity_bin_second_moments =
      estimator->getEntityBinDataSecondMoments( 0 );
  
    Utility::ArrayView<const double> entity_bin_third_moments =
      estimator->getEntityBinDataThirdMoments( 0 );
  
    Utility::ArrayView<const double> entity_bin_fourth_moments =
      estimator->getEntityBinDataFourthMoments( 0 );
  
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                         std::vector<double>( 32, 2.0 ) );
  
    entity_bin_first_moments = estimator->getEntityBinDataFirstMoments( 1 );
    entity_bin_second_moments = estimator->getEntityBinDataSecondMoments( 1 );
    entity_bin_third_moments = estimator->getEntityBinDataThirdMoments( 1 );
    entity_bin_fourth_moments = estimator->getEntityBinDataFourthMoments( 1 );
  
    FRENSIE_CHECK_EQUAL( entity_bin_first_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_second_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_third_moments,
                         std::vector<double>( 32, 2.0 ) );
    FRENSIE_CHECK_EQUAL( entity_bin_fourth_moments,
                         std::vector<double>( 32, 2.0 ) );
  
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
                         std::vector<double>( 2, 32.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 512.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 8192.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 131072.0 ) );
  
    entity_total_first_moments = estimator->getEntityTotalDataFirstMoments( 1 );
    entity_total_second_moments = estimator->getEntityTotalDataSecondMoments( 1 );
    entity_total_third_moments = estimator->getEntityTotalDataThirdMoments( 1 );
    entity_total_fourth_moments = estimator->getEntityTotalDataFourthMoments( 1 );
  
    FRENSIE_CHECK_EQUAL( entity_total_first_moments,
                         std::vector<double>( 2, 32.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_second_moments,
                         std::vector<double>( 2, 512.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_third_moments,
                         std::vector<double>( 2, 8192.0 ) );
    FRENSIE_CHECK_EQUAL( entity_total_fourth_moments,
                         std::vector<double>( 2, 131072.0 ) );
  
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
                         std::vector<double>( 2, 64.0 ) );
    FRENSIE_CHECK_EQUAL( total_second_moments,
                         std::vector<double>( 2, 2048.0 ) );
    FRENSIE_CHECK_EQUAL( total_third_moments,
                         std::vector<double>( 2, 65536.0 ) );
    FRENSIE_CHECK_EQUAL( total_fourth_moments,
                         std::vector<double>( 2, 2097152.0 ) );
  
    // Check the entity bin histograms
    Utility::SampleMomentHistogram<double> histogram;
  
    std::vector<double> expected_histogram_bins =
      Utility::fromString<std::vector<double> >( "{-1.7976931348623157e+308, 0.0, 1e-30, 599l, 1e30, 1.7976931348623157e+308}" );
    std::vector<double> expected_histogram_values;
  
    {
      std::string expected_histogram_values_string = "{0.0r302, ";
      expected_histogram_values_string += Utility::toString( 2 );
      expected_histogram_values_string += ", 0.0r300}";
    
      expected_histogram_values = 
        Utility::fromString<std::vector<double> >( expected_histogram_values_string );
    }
  
    size_t num_estimator_bins = estimator->getNumberOfBins()*
      estimator->getNumberOfResponseFunctions();
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getEntityBinSampleMomentHistogram( 0, j, histogram );
    
        FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
        FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                             expected_histogram_bins );
        FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                             expected_histogram_values );
      }
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getEntityBinSampleMomentHistogram( 1, j, histogram );
    
        FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
        FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                             expected_histogram_bins );
        FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                             expected_histogram_values );
      }
  
    // Check the total bin histograms
    {
      std::string expected_histogram_value_string = "{0.0r305, ";
      expected_histogram_value_string += Utility::toString( 2 );
      expected_histogram_value_string += ", 0.0r297}";
    
      expected_histogram_values =
        Utility::fromString<std::vector<double> >( expected_histogram_value_string );
    }
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getTotalBinSampleMomentHistogram( j, histogram );
    
        FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
        FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                             expected_histogram_bins );
        FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                             expected_histogram_values );
      }
  
    // Check the entity total histograms
    {
      std::string expected_histogram_values_string = "{0.0r314, ";
      expected_histogram_values_string += Utility::toString( 2 );
      expected_histogram_values_string += ", 0.0r288}";
    
      expected_histogram_values = 
        Utility::fromString<std::vector<double> >( expected_histogram_values_string );
    }
  
    estimator->getEntityTotalSampleMomentHistogram( 0, 0, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getEntityTotalSampleMomentHistogram( 0, 1, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getEntityTotalSampleMomentHistogram( 1, 0, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getEntityTotalSampleMomentHistogram( 1, 1, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    // Check the entity total histograms
    {
      std::string expected_histogram_values_string = "{0.0r317, ";
      expected_histogram_values_string += Utility::toString( 2 );
      expected_histogram_values_string += ", 0.0r285}";
    
      expected_histogram_values =
        Utility::fromString<std::vector<double> >( expected_histogram_values_string );
    }
  
    estimator->getTotalSampleMomentHistogram( 0, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    estimator->getTotalSampleMomentHistogram( 1, histogram );
  
    FRENSIE_CHECK_EQUAL( histogram.getNumberOfScores(), 2 );
    FRENSIE_CHECK_EQUAL( histogram.getBinBoundaries(),
                         expected_histogram_bins );
    FRENSIE_CHECK_EQUAL( histogram.getHistogramValues(),
                         expected_histogram_values );
  
    // Check the entity bin moment snapshots
    std::vector<uint64_t> expected_history_values( 2 );
    std::vector<double> expected_sampling_times( 2 );
    std::vector<double> expected_first_moments( 2 );
    std::vector<double> expected_second_moments( 2 );
    std::vector<double> expected_third_moments( 2 );
    std::vector<double> expected_fourth_moments( 2 );
  
    for( size_t i = 0; i < 2; ++i )
      {
        expected_history_values[i] = (i+1)*5;
        expected_sampling_times[i] = (i+1)*1.0;
        expected_first_moments[i] = (i+1)*1.0;
        expected_second_moments[i] = (i+1)*1.0;
        expected_third_moments[i] = (i+1)*1.0;
        expected_fourth_moments[i] = (i+1)*1.0;
      }
  
    std::vector<uint64_t> history_values;
    std::vector<double> sampling_times;
  
    std::vector<double> first_moments, second_moments, third_moments,
      fourth_moments;
  
    estimator->getEntityBinMomentSnapshotHistoryValues( 0, history_values );
  
    estimator->getEntityBinMomentSnapshotSamplingTimes( 0, sampling_times );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    estimator->getEntityBinMomentSnapshotHistoryValues( 1, history_values );
  
    estimator->getEntityBinMomentSnapshotSamplingTimes( 1, sampling_times );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    num_estimator_bins = estimator->getNumberOfBins()*
      estimator->getNumberOfResponseFunctions();
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {
        estimator->getEntityBinFirstMomentSnapshots( 0, j, first_moments );
        estimator->getEntityBinSecondMomentSnapshots( 0, j, second_moments );
        estimator->getEntityBinThirdMomentSnapshots( 0, j, third_moments );
        estimator->getEntityBinFourthMomentSnapshots( 0, j, fourth_moments );
    
        FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
        FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
        FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
        FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
    
        estimator->getEntityBinFirstMomentSnapshots( 1, j, first_moments );
        estimator->getEntityBinSecondMomentSnapshots( 1, j, second_moments );
        estimator->getEntityBinThirdMomentSnapshots( 1, j, third_moments );
        estimator->getEntityBinFourthMomentSnapshots( 1, j, fourth_moments );
    
        FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
        FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
        FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
        FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
      }
  
    // Check the total bin moment snapshots
    estimator->getTotalBinMomentSnapshotHistoryValues( history_values );
    estimator->getTotalBinMomentSnapshotSamplingTimes( sampling_times );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    for( size_t i = 0; i < 2; ++i )
      {
        expected_first_moments[i] = (i+1)*2.0;
        expected_second_moments[i] = (i+1)*4.0;
        expected_third_moments[i] = (i+1)*8.0;
        expected_fourth_moments[i] = (i+1)*16.0;
      }
  
    for( size_t j = 0; j < num_estimator_bins; ++j )
      {  
        estimator->getTotalBinFirstMomentSnapshots( j, first_moments );
        estimator->getTotalBinSecondMomentSnapshots( j, second_moments );
        estimator->getTotalBinThirdMomentSnapshots( j, third_moments );
        estimator->getTotalBinFourthMomentSnapshots( j, fourth_moments );
    
        FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
        FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
        FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
        FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
      }
  
    // Check the entity total moment snapshots
    for( size_t i = 0; i < 2; ++i )
      {
        expected_first_moments[i] = (i+1)*16.0;
        expected_second_moments[i] = (i+1)*256.0;
        expected_third_moments[i] = (i+1)*4096.0;
        expected_fourth_moments[i] = (i+1)*65536.0;
      }
  
    estimator->getEntityTotalMomentSnapshotHistoryValues( 0, history_values );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
  
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 0, sampling_times );
  
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    estimator->getEntityTotalFirstMomentSnapshots( 0, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 0, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getEntityTotalFirstMomentSnapshots( 0, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 0, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 0, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 0, 1, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getEntityTotalMomentSnapshotHistoryValues( 1, history_values );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
  
    estimator->getEntityTotalMomentSnapshotSamplingTimes( 1, sampling_times );
  
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    estimator->getEntityTotalFirstMomentSnapshots( 1, 0, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 0, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 0, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 0, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getEntityTotalFirstMomentSnapshots( 1, 1, first_moments );
    estimator->getEntityTotalSecondMomentSnapshots( 1, 1, second_moments );
    estimator->getEntityTotalThirdMomentSnapshots( 1, 1, third_moments );
    estimator->getEntityTotalFourthMomentSnapshots( 1, 1, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    // Check the total moment snapshots
    for( size_t i = 0; i < 2; ++i )
      {
        expected_first_moments[i] = (i+1)*32.0;
        expected_second_moments[i] = (i+1)*1024.0;
        expected_third_moments[i] = (i+1)*32768.0;
        expected_fourth_moments[i] = (i+1)*1048576.0;
      }
  
    estimator->getTotalMomentSnapshotHistoryValues( history_values );
  
    FRENSIE_CHECK_EQUAL( history_values, expected_history_values );
  
    estimator->getTotalMomentSnapshotSamplingTimes( sampling_times );
  
    FRENSIE_CHECK_EQUAL( sampling_times, expected_sampling_times );
  
    estimator->getTotalFirstMomentSnapshots( 0, first_moments );
    estimator->getTotalSecondMomentSnapshots( 0, second_moments );
    estimator->getTotalThirdMomentSnapshots( 0, third_moments );
    estimator->getTotalFourthMomentSnapshots( 0, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
  
    estimator->getTotalFirstMomentSnapshots( 1, first_moments );
    estimator->getTotalSecondMomentSnapshots( 1, second_moments );
    estimator->getTotalThirdMomentSnapshots( 1, third_moments );
    estimator->getTotalFourthMomentSnapshots( 1, fourth_moments );
  
    FRENSIE_CHECK_EQUAL( first_moments, expected_first_moments );
    FRENSIE_CHECK_EQUAL( second_moments, expected_second_moments );
    FRENSIE_CHECK_EQUAL( third_moments, expected_third_moments );
    FRENSIE_CHECK_EQUAL( fourth_moments, expected_fourth_moments );
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


