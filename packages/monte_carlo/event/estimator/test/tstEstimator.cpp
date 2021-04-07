//---------------------------------------------------------------------------//
//!
//! \file   tstEstimator.cpp
//! \author Alex Robinson
//! \brief  Estimator unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_Estimator.hpp"
#include "MonteCarlo_DefaultTypedObserverPhaseSpaceDimensionDiscretization.hpp"
#include "MonteCarlo_SinglePhaseSpaceDimensionParticleResponseFunction.hpp"
#include "MonteCarlo_ObserverDirectionDimensionDiscretization.hpp"
#include "MonteCarlo_StandardParticleResponse.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_PQLATypeObserverDirectionDimensionDiscretization.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Structs.
//---------------------------------------------------------------------------//
class TestEstimator : public MonteCarlo::Estimator
{
public:
  TestEstimator( const uint32_t id, const double multiplier );

  ~TestEstimator();

  //! Check if the estimator is a cell estimator
  bool isCellEstimator() const final override
  { return false; }

  //! Check if the estimator is a surface estimator
  bool isSurfaceEstimator() const final override
  { return false; }

  //! Check if the estimator is a mesh estimator
  bool isMeshEstimator() const final override
  { return false; }

  //! Get the entities assigned to the estimator
  void getEntityIds( std::set<uint64_t>& ) const final override;

  //! Check if an entity is assigned to this estimator
  bool isEntityAssigned( const uint64_t ) const final override
  { return false; }

  //! Return the normalization constant for an entity
  double getEntityNormConstant( const uint64_t ) const final override
  { return 1.0; }

  //! Return the total normalization constant
  double getTotalNormConstant() const final override
  { return 1.0; }

  //! Enable snapshots on entity bins
  void enableSnapshotsOnEntityBins() final override
  { /* ... */ }

  //! Check if snapshots have been enabled on entity bins
  bool areSnapshotsOnEntityBinsEnabled() const final override
  { return false; }

  //! Enable sample moment histograms on entity bins
  void enableSampleMomentHistogramsOnEntityBins() final override
  { /* ... */ }

  //! Check if sample moment histograms are enabled on on entity bins
  bool areSampleMomentHistogramsOnEntityBinsEnabled() const final override
  { return false; }

  //! Get the total estimator bin data first moments
  Utility::ArrayView<const double> getTotalBinDataFirstMoments() const final override
  { return Utility::ArrayView<const double>(); }

  //! Get the total estimator bin data second moments
  Utility::ArrayView<const double> getTotalBinDataSecondMoments() const final override
  { return Utility::ArrayView<const double>(); }

  //! Get the total estimator bin data third moments
  Utility::ArrayView<const double> getTotalBinDataThirdMoments() const final override
  { return Utility::ArrayView<const double>(); }

  //! Get the total estimator bin data fourth moments
  Utility::ArrayView<const double> getTotalBinDataFourthMoments() const final override
  { return Utility::ArrayView<const double>(); }

  //! Get the bin data first moments for an entity
  Utility::ArrayView<const double> getEntityBinDataFirstMoments( const uint64_t entity_id ) const final override
  { return Utility::ArrayView<const double>(); }

  //! Get the bin data second moments for an entity
  Utility::ArrayView<const double> getEntityBinDataSecondMoments( const uint64_t entity_id ) const final override
  { return Utility::ArrayView<const double>(); }

  //! Get the bin data third moments for an entity
  Utility::ArrayView<const double> getEntityBinDataThirdMoments( const uint64_t entity_id ) const final override
  { return Utility::ArrayView<const double>(); }

  //! Get the bin data fourth moments for an entity
  Utility::ArrayView<const double> getEntityBinDataFourthMoments( const uint64_t entity_id ) const final override
  { return Utility::ArrayView<const double>(); }

  void printSummary( std::ostream& os ) const final override
  {
    this->printEstimatorResponseFunctionNames( os );
    this->printObserverDiscretization( os );
  }

  void commitHistoryContribution() final override
  { /* ... */ }

  void takeSnapshot( const uint64_t num_histories, const double time ) final override
  { /* ... */ }

  void resetData() final override
  { /* ... */ }

  void reduceData( const Utility::Communicator& comm,
                   const int root_process ) final override
  { /* ... */ }

  // Allow public access to the estimator protected member functions
  using MonteCarlo::Estimator::DimensionValueMap;
  using MonteCarlo::Estimator::setHasUncommittedHistoryContribution;
  using MonteCarlo::Estimator::unsetHasUncommittedHistoryContribution;
  using MonteCarlo::Estimator::assignDiscretization;
  using MonteCarlo::Estimator::getMultiplier;
  using MonteCarlo::Estimator::getResponseFunctionName;
  using MonteCarlo::Estimator::getBinName;
  using MonteCarlo::Estimator::calculateResponseFunctionIndex;
};

TestEstimator::TestEstimator( const uint32_t id, const double multiplier )
  : MonteCarlo::Estimator( id, multiplier )
{ /* ... */ }

TestEstimator::~TestEstimator()
{ /* ... */ }

void TestEstimator::getEntityIds( std::set<uint64_t>& ) const
{ /* ... */ }

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the estimator id can be returned
FRENSIE_UNIT_TEST( Estimator, getId )
{
  TestEstimator estimator( 0, 1.0 );

  FRENSIE_CHECK_EQUAL( estimator.getId(), 0ull );
}

//---------------------------------------------------------------------------//
// Check that the multiplier can be returned
FRENSIE_UNIT_TEST( Estimator, getMultiplier )
{
  TestEstimator estimator( 0, 1.0 );

  FRENSIE_CHECK_EQUAL( estimator.getMultiplier(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that dimension discretizations can be set
FRENSIE_UNIT_TEST( Estimator, setDiscretization_raw_data )
{
  {
    TestEstimator estimator( 0, 1.0 );

    FRENSIE_CHECK( !estimator.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_ENERGY_DIMENSION ) );

    std::vector<double> energy_bin_boundaries( 7 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 1e-1;
    energy_bin_boundaries[2] = 1e-1;
    energy_bin_boundaries[3] = 1.0;
    energy_bin_boundaries[4] = 10.0;
    energy_bin_boundaries[5] = 10.0;
    energy_bin_boundaries[6] = 20.0;

    estimator.setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>( energy_bin_boundaries);

    FRENSIE_CHECK( estimator.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_ENERGY_DIMENSION ) );
    FRENSIE_CHECK_EQUAL( estimator.getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ),
                         6u );

    std::vector<double> energy_bin_boundaries_copy;

    estimator.getDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>( energy_bin_boundaries_copy );

    FRENSIE_CHECK_EQUAL( energy_bin_boundaries, energy_bin_boundaries_copy );
  }

  {
    TestEstimator estimator( 0, 1.0 );

    FRENSIE_CHECK( !estimator.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );

    std::vector<double> cosine_bin_boundaries( 4 );
    cosine_bin_boundaries[0] = -1.0;
    cosine_bin_boundaries[1] = -1.0/3.0;
    cosine_bin_boundaries[2] = 1.0/3.0;
    cosine_bin_boundaries[3] = 1.0;
    
    estimator.setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>( cosine_bin_boundaries );

    FRENSIE_CHECK( estimator.doesDimensionHaveDiscretization( MonteCarlo::OBSERVER_COSINE_DIMENSION ) );
    FRENSIE_CHECK_EQUAL( estimator.getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ),
                         3u );

    std::vector<double> cosine_bin_boundaries_copy;

    estimator.getDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>( cosine_bin_boundaries_copy );

    FRENSIE_CHECK_EQUAL( cosine_bin_boundaries, cosine_bin_boundaries_copy );
  }

  {
    TestEstimator estimator( 0, 1.0 );

    std::vector<double> time_bin_boundaries( 4 );
    time_bin_boundaries[0] = 0.0;
    time_bin_boundaries[1] = 1e3;
    time_bin_boundaries[2] = 1e5;
    time_bin_boundaries[3] = 1e7;
    
    estimator.setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>( time_bin_boundaries );

    FRENSIE_CHECK_EQUAL( estimator.getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ),
                         3u );

    std::vector<double> time_bin_boundaries_copy;

    estimator.getDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>( time_bin_boundaries_copy );

    FRENSIE_CHECK_EQUAL( time_bin_boundaries, time_bin_boundaries_copy );
  }

  {
    TestEstimator estimator( 0, 1.0 );

    std::vector<unsigned> collision_number_bins( 4 );
    collision_number_bins[0] = 0u;
    collision_number_bins[1] = 1u;
    collision_number_bins[2] = 2u;
    collision_number_bins[3] = std::numeric_limits<unsigned>::max();
    
    estimator.setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

    FRENSIE_CHECK_EQUAL( estimator.getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 4u );

    std::vector<unsigned> collision_number_bins_copy;

    estimator.getDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
                                                  collision_number_bins_copy );

    FRENSIE_CHECK_EQUAL( collision_number_bins, collision_number_bins_copy );
  }

  {
    TestEstimator estimator( 0, 1.0 );

    std::vector<std::set<MonteCarlo::ParticleState::sourceIdType> > source_id_bins( 3 );
    source_id_bins[0].insert( 0 );
    source_id_bins[0].insert( 1 );
    source_id_bins[1].insert( 1 );
    source_id_bins[2].insert( 0 );
    source_id_bins[2].insert( 2 );

    estimator.setDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION>( source_id_bins );

    FRENSIE_CHECK_EQUAL( estimator.getNumberOfBins( MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION ), 3 );

    std::vector<std::set<MonteCarlo::ParticleState::sourceIdType> > source_id_bins_copy;

    estimator.getDiscretization<MonteCarlo::OBSERVER_SOURCE_ID_DIMENSION>( source_id_bins_copy );

    FRENSIE_CHECK_EQUAL( source_id_bins, source_id_bins_copy );
  }
}

//---------------------------------------------------------------------------//
// Check that dimension discretizations can be set
FRENSIE_UNIT_TEST( Estimator, setDiscretization )
{
  {
    TestEstimator estimator( 0, 1.0 );

    std::vector<double> energy_bin_boundaries( 7 );
    energy_bin_boundaries[0] = 0.0;
    energy_bin_boundaries[1] = 1e-1;
    energy_bin_boundaries[2] = 1e-1;
    energy_bin_boundaries[3] = 1.0;
    energy_bin_boundaries[4] = 10.0;
    energy_bin_boundaries[5] = 10.0;
    energy_bin_boundaries[6] = 20.0;

    std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
      dimension_discretization( new MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>( energy_bin_boundaries ) );

    estimator.setDiscretization( dimension_discretization );

    FRENSIE_CHECK_EQUAL( estimator.getNumberOfBins( MonteCarlo::OBSERVER_ENERGY_DIMENSION ),
                         6u );
  }

  {
    TestEstimator estimator( 0, 1.0 );

    std::vector<double> cosine_bin_boundaries( 4 );
    cosine_bin_boundaries[0] = -1.0;
    cosine_bin_boundaries[1] = -1.0/3.0;
    cosine_bin_boundaries[2] = 1.0/3.0;
    cosine_bin_boundaries[3] = 1.0;

    std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
      dimension_discretization( new MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>( cosine_bin_boundaries ) );

    estimator.setDiscretization( dimension_discretization );
    
    FRENSIE_CHECK_EQUAL( estimator.getNumberOfBins( MonteCarlo::OBSERVER_COSINE_DIMENSION ),
                         3u );
  }

  {
    TestEstimator estimator( 0, 1.0 );

    std::vector<double> time_bin_boundaries( 4 );
    time_bin_boundaries[0] = 0.0;
    time_bin_boundaries[1] = 1e3;
    time_bin_boundaries[2] = 1e5;
    time_bin_boundaries[3] = 1e7;

    std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
      dimension_discretization( new MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>( time_bin_boundaries ) );

    estimator.setDiscretization( dimension_discretization );
    
    FRENSIE_CHECK_EQUAL( estimator.getNumberOfBins( MonteCarlo::OBSERVER_TIME_DIMENSION ),
                         3u );
  }

  {
    TestEstimator estimator( 0, 1.0 );

    std::vector<unsigned> collision_number_bins( 4 );
    collision_number_bins[0] = 0u;
    collision_number_bins[1] = 1u;
    collision_number_bins[2] = 2u;
    collision_number_bins[3] = std::numeric_limits<unsigned>::max();

    std::shared_ptr<const MonteCarlo::ObserverPhaseSpaceDimensionDiscretization>
      dimension_discretization( new MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>( collision_number_bins ) );

    estimator.setDiscretization( dimension_discretization );
    
    FRENSIE_CHECK_EQUAL( estimator.getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 4u );

    // These bins should be ignored
    collision_number_bins.resize( 2 );
    collision_number_bins[0] = 0u;
    collision_number_bins[1] = 1u;

    dimension_discretization.reset( new MonteCarlo::DefaultTypedObserverPhaseSpaceDimensionDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>( collision_number_bins ) );

    estimator.setDiscretization( dimension_discretization );
    
    FRENSIE_CHECK_EQUAL( estimator.getNumberOfBins( MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION ), 4u );
  }

  // Test PQLA direction discretization implementation
  {
    TestEstimator estimator( 0, 1.0 );

    estimator.setDirectionDiscretization( MonteCarlo::ObserverDirectionDimensionDiscretization::ObserverDirectionDiscretizationType::PQLA,
                                          2,
                                          true );

    FRENSIE_CHECK_EQUAL( estimator.getNumberOfBins( MonteCarlo::OBSERVER_DIRECTION_DIMENSION ),
                         8*4 );
  }
}

//---------------------------------------------------------------------------//
// Check that the dimensions that have been discretized can be returned
FRENSIE_UNIT_TEST( Estimator, getDiscretizedDimensions )
{
  TestEstimator estimator( 0, 1.0 );

  std::vector<MonteCarlo::ObserverPhaseSpaceDimension> discretized_dimensions;

  estimator.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_CHECK_EQUAL( discretized_dimensions.size(), 0 );
  
  std::vector<double> energy_bin_boundaries( 7 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1e-1;
  energy_bin_boundaries[3] = 1.0;
  energy_bin_boundaries[4] = 10.0;
  energy_bin_boundaries[5] = 10.0;
  energy_bin_boundaries[6] = 20.0;

  estimator.setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>( energy_bin_boundaries);

  estimator.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 1 );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[0], MonteCarlo::OBSERVER_ENERGY_DIMENSION );

  std::vector<double> time_bin_boundaries( 4 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1e3;
  time_bin_boundaries[2] = 1e5;
  time_bin_boundaries[3] = 1e7;

  estimator.setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>( time_bin_boundaries);

  estimator.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 2 );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[0], MonteCarlo::OBSERVER_ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[1], MonteCarlo::OBSERVER_TIME_DIMENSION );

  std::vector<unsigned> collision_number_bins( 4 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;
  collision_number_bins[2] = 2u;
  collision_number_bins[3] = std::numeric_limits<unsigned>::max();

  estimator.setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

  estimator.getDiscretizedDimensions( discretized_dimensions );

  FRENSIE_REQUIRE_EQUAL( discretized_dimensions.size(), 3 );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[0], MonteCarlo::OBSERVER_ENERGY_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[1], MonteCarlo::OBSERVER_TIME_DIMENSION );
  FRENSIE_CHECK_EQUAL( discretized_dimensions[2], MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION );
}

//---------------------------------------------------------------------------//
// Check that the total number of bins can be returned
FRENSIE_UNIT_TEST( Estimator, getNumberOfBins )
{
  TestEstimator estimator( 0, 1.0 );

  std::vector<double> energy_bin_boundaries( 7 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1e-1;
  energy_bin_boundaries[3] = 1.0;
  energy_bin_boundaries[4] = 10.0;
  energy_bin_boundaries[5] = 10.0;
  energy_bin_boundaries[6] = 20.0;

  estimator.setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>( energy_bin_boundaries);

  std::vector<double> time_bin_boundaries( 4 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1e3;
  time_bin_boundaries[2] = 1e5;
  time_bin_boundaries[3] = 1e7;

  estimator.setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>( time_bin_boundaries);

  std::vector<unsigned> collision_number_bins( 4 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;
  collision_number_bins[2] = 2u;
  collision_number_bins[3] = std::numeric_limits<unsigned>::max();

  estimator.setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

  FRENSIE_CHECK_EQUAL( estimator.getNumberOfBins(), 72u );

  // These bins should be ignored
  collision_number_bins.resize( 2 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;

  estimator.setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

  FRENSIE_CHECK_EQUAL( estimator.getNumberOfBins(), 72u );
}

//---------------------------------------------------------------------------//
// Check that the response functions can be set
FRENSIE_UNIT_TEST( Estimator, setResponseFunctions )
{
  TestEstimator estimator( 0, 1.0 );

  std::vector<std::shared_ptr<const MonteCarlo::ParticleResponse> >
    response_functions( 2 );

  {
    std::shared_ptr<const Utility::UnivariateDistribution> energy_distribution(
			   new Utility::UniformDistribution( 0.0, 10., 1.0 ) );

    std::shared_ptr<const MonteCarlo::ParticleResponseFunction> response_function(
       new MonteCarlo::EnergyParticleResponseFunction( energy_distribution ) );

    response_functions[0].reset( new MonteCarlo::StandardParticleResponse(
                                                         response_function ) );

    response_functions[1] = MonteCarlo::ParticleResponse::getDefault();
  }

  estimator.setResponseFunctions( response_functions );

  FRENSIE_CHECK_EQUAL( estimator.getNumberOfResponseFunctions(), 2u );
  FRENSIE_CHECK_EQUAL( estimator.getResponseFunctionName( 0u ),
		       "f_custom(Energy Dimension)" );
  FRENSIE_CHECK_EQUAL( estimator.getResponseFunctionName( 1u ),
		       "f(particle) = 1" );
}

//---------------------------------------------------------------------------//
// Check that the response functions can be set
FRENSIE_UNIT_TEST( Estimator, addResponseFunction )
{
  TestEstimator estimator( 0, 1.0 );

  std::shared_ptr<const MonteCarlo::ParticleResponse> particle_response;

  {
    std::shared_ptr<const Utility::UnivariateDistribution> energy_distribution(
                           new Utility::UniformDistribution( 0.0, 10., 1.0 ) );

    std::shared_ptr<const MonteCarlo::ParticleResponseFunction> response_function(
       new MonteCarlo::EnergyParticleResponseFunction( energy_distribution ) );

    particle_response.reset( new MonteCarlo::StandardParticleResponse(
                                                         response_function ) );
  }

  estimator.addResponseFunction( particle_response );

  FRENSIE_CHECK_EQUAL( estimator.getNumberOfResponseFunctions(), 2u );
  FRENSIE_CHECK_EQUAL( estimator.getResponseFunctionName( 0u ),
		       "f(particle) = 1" );
  FRENSIE_CHECK_EQUAL( estimator.getResponseFunctionName( 1u ),
		       "f_custom(Energy Dimension)" );
}

//---------------------------------------------------------------------------//
// Check that the particle types that can contribute to the estimator can
// be set
FRENSIE_UNIT_TEST( Estimator, setParticleTypes )
{
  TestEstimator estimator( 0, 1.0 );

  std::vector<MonteCarlo::ParticleType> particle_types( 2 );
  particle_types[0] = MonteCarlo::PHOTON;
  particle_types[1] = MonteCarlo::NEUTRON;

  estimator.setParticleTypes( particle_types );

  FRENSIE_CHECK( estimator.isParticleTypeAssigned( MonteCarlo::PHOTON ) );
  FRENSIE_CHECK( estimator.isParticleTypeAssigned( MonteCarlo::NEUTRON ) );
  FRENSIE_CHECK( !estimator.isParticleTypeAssigned( MonteCarlo::ADJOINT_PHOTON ) );
  FRENSIE_CHECK( !estimator.isParticleTypeAssigned( MonteCarlo::ADJOINT_NEUTRON ) );
}

//---------------------------------------------------------------------------//
// Check if the estimator can calculate the response function index
FRENSIE_UNIT_TEST( Estimator, calculateResponseFunctionIndex )
{
  TestEstimator estimator( 0, 1.0 );

  // Set the bins
  std::vector<double> energy_bin_boundaries( 7 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1e-1;
  energy_bin_boundaries[3] = 1.0;
  energy_bin_boundaries[4] = 10.0;
  energy_bin_boundaries[5] = 10.0;
  energy_bin_boundaries[6] = 20.0;

  estimator.setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>( energy_bin_boundaries);

  std::vector<double> cosine_bin_boundaries( 4 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = -1.0/3.0;
  cosine_bin_boundaries[2] = 1.0/3.0;
  cosine_bin_boundaries[3] = 1.0;

  estimator.setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>( cosine_bin_boundaries);

  std::vector<double> time_bin_boundaries( 4 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1e3;
  time_bin_boundaries[2] = 1e5;
  time_bin_boundaries[3] = 1e7;

  estimator.setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>( time_bin_boundaries);

  std::vector<unsigned> collision_number_bins( 4 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;
  collision_number_bins[2] = 2u;
  collision_number_bins[3] = std::numeric_limits<unsigned>::max();

  estimator.setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

  // Set the response functions
  std::vector<std::shared_ptr<const MonteCarlo::ParticleResponse> >
    response_functions( 2 );

  std::shared_ptr<const Utility::UnivariateDistribution> energy_distribution(
			   new Utility::UniformDistribution( 0.0, 10., 1.0 ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction> response_function(
       new MonteCarlo::EnergyParticleResponseFunction( energy_distribution ) );

  response_functions[0].reset( new MonteCarlo::StandardParticleResponse(
                                                         response_function ) );

  response_functions[1] = MonteCarlo::ParticleResponse::getDefault();

  estimator.setResponseFunctions( response_functions );

  // Calculate the response function index
  unsigned bin_index = 0u;

  unsigned response_function_index =
    estimator.calculateResponseFunctionIndex( bin_index );

  FRENSIE_CHECK_EQUAL( response_function_index, 0u );

  bin_index = 215;

  response_function_index =
    estimator.calculateResponseFunctionIndex( bin_index );

  FRENSIE_CHECK_EQUAL( response_function_index, 0u );

  bin_index = 216;

  response_function_index =
    estimator.calculateResponseFunctionIndex( bin_index );

  FRENSIE_CHECK_EQUAL( response_function_index, 1u );

  bin_index = 431;

  response_function_index =
    estimator.calculateResponseFunctionIndex( bin_index );

  FRENSIE_CHECK_EQUAL( response_function_index, 1u );
}

//---------------------------------------------------------------------------//
// Check if the estimator has an uncommitted history contribution
FRENSIE_UNIT_TEST( Estimator, hasUncommittedHisotryContribution_serial )
{
  TestEstimator estimator( 0, 1.0 );

  FRENSIE_CHECK( !estimator.hasUncommittedHistoryContribution() );

  estimator.setHasUncommittedHistoryContribution( 0u );

  FRENSIE_CHECK( estimator.hasUncommittedHistoryContribution() );

  estimator.unsetHasUncommittedHistoryContribution( 0u );

  FRENSIE_CHECK( !estimator.hasUncommittedHistoryContribution() );
}

//---------------------------------------------------------------------------//
// Check if the estimator has an uncommitted history contribution on a
// given thread
FRENSIE_UNIT_TEST( Estimator, hasUncommittedHistoryContribution_parallel_safe )
{
  TestEstimator estimator( 0, 1.0 );

  estimator.enableThreadSupport(
		 Utility::OpenMPProperties::getRequestedNumberOfThreads() );

  #pragma omp parallel num_threads( Utility::OpenMPProperties::getRequestedNumberOfThreads() )
  {
    unsigned thread_id = Utility::OpenMPProperties::getThreadId();

    #pragma omp critical(thread_check)
    {
      // Explicit thread id
      FRENSIE_CHECK( !estimator.hasUncommittedHistoryContribution( thread_id ) );
      // Implicit thread id
      FRENSIE_CHECK( !estimator.hasUncommittedHistoryContribution() );

      estimator.setHasUncommittedHistoryContribution( thread_id );

      FRENSIE_CHECK( estimator.hasUncommittedHistoryContribution() );

      estimator.unsetHasUncommittedHistoryContribution( thread_id );

      FRENSIE_CHECK( !estimator.hasUncommittedHistoryContribution() );
    }
  }
}

//---------------------------------------------------------------------------//
// Check that the bin name can be created
FRENSIE_UNIT_TEST( Estimator, getBinName )
{
  TestEstimator estimator( 0, 1.0 );

  std::vector<double> energy_bin_boundaries( 7 );
  energy_bin_boundaries[0] = 0.0;
  energy_bin_boundaries[1] = 1e-1;
  energy_bin_boundaries[2] = 1e-1;
  energy_bin_boundaries[3] = 1.0;
  energy_bin_boundaries[4] = 10.0;
  energy_bin_boundaries[5] = 10.0;
  energy_bin_boundaries[6] = 20.0;

  estimator.setDiscretization<MonteCarlo::OBSERVER_ENERGY_DIMENSION>( energy_bin_boundaries);

  std::vector<double> time_bin_boundaries( 4 );
  time_bin_boundaries[0] = 0.0;
  time_bin_boundaries[1] = 1.0;
  time_bin_boundaries[2] = 2.0;
  time_bin_boundaries[3] = 3.0;

  estimator.setDiscretization<MonteCarlo::OBSERVER_TIME_DIMENSION>( time_bin_boundaries);

  std::vector<unsigned> collision_number_bins( 4 );
  collision_number_bins[0] = 0u;
  collision_number_bins[1] = 1u;
  collision_number_bins[2] = 2u;
  collision_number_bins[3] = 10u;

  estimator.setDiscretization<MonteCarlo::OBSERVER_COLLISION_NUMBER_DIMENSION>(
						       collision_number_bins );

  std::vector<double> cosine_bin_boundaries( 4 );
  cosine_bin_boundaries[0] = -1.0;
  cosine_bin_boundaries[1] = -0.5;
  cosine_bin_boundaries[2] = 0.5;
  cosine_bin_boundaries[3] = 1.0;

  estimator.setDiscretization<MonteCarlo::OBSERVER_COSINE_DIMENSION>( cosine_bin_boundaries);

  std::vector<std::shared_ptr<const MonteCarlo::ParticleResponse> >
    response_functions( 2 );

  std::shared_ptr<const Utility::UnivariateDistribution> energy_distribution(
			   new Utility::UniformDistribution( 0.0, 10., 1.0 ) );

  std::shared_ptr<const MonteCarlo::ParticleResponseFunction> response_function(
       new MonteCarlo::EnergyParticleResponseFunction( energy_distribution ) );

  response_functions[0].reset( new MonteCarlo::StandardParticleResponse(
                                                         response_function ) );

  response_functions[1] = MonteCarlo::ParticleResponse::getDefault();

  estimator.setResponseFunctions( response_functions );

  std::string bin_name = estimator.getBinName( 0u );

  std::string true_bin_name = "Energy Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 0.1 ) + "], ";
  true_bin_name += "Time Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 1.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 0 ) + "," + Utility::toString( 0 ) + "], ";
  true_bin_name += "Cosine Bin: [";
  true_bin_name += Utility::toString( -1.0 ) + "," + Utility::toString( -0.5 ) + "], ";
  true_bin_name += response_functions[0]->getName();

  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  bin_name = estimator.getBinName( 5u );
  
  true_bin_name = "Energy Bin: (";
  true_bin_name += Utility::toString( 10.0 ) + "," + Utility::toString( 20.0 ) + "], ";
  true_bin_name += "Time Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 1.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 0 ) + "," + Utility::toString( 0 ) + "], ";
  true_bin_name += "Cosine Bin: [";
  true_bin_name += Utility::toString( -1.0 ) + "," + Utility::toString( -0.5 ) + "], ";
  true_bin_name += response_functions[0]->getName();

  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  bin_name = estimator.getBinName( 12u );

  true_bin_name = "Energy Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 0.1 ) + "], ";
  true_bin_name += "Time Bin: (";
  true_bin_name += Utility::toString( 2.0 ) + "," + Utility::toString( 3.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 0 ) + "," + Utility::toString( 0 ) + "], ";
  true_bin_name += "Cosine Bin: [";
  true_bin_name += Utility::toString( -1.0 ) + "," + Utility::toString( -0.5 ) + "], ";
  true_bin_name += response_functions[0]->getName();

  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  bin_name = estimator.getBinName( 17u );

  true_bin_name = "Energy Bin: (";
  true_bin_name += Utility::toString( 10.0 ) + "," + Utility::toString( 20.0 ) + "], ";
  true_bin_name += "Time Bin: (";
  true_bin_name += Utility::toString( 2.0 ) + "," + Utility::toString( 3.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 0 ) + "," + Utility::toString( 0 ) + "], ";
  true_bin_name += "Cosine Bin: [";
  true_bin_name += Utility::toString( -1.0 ) + "," + Utility::toString( -0.5 ) + "], ";
  true_bin_name += response_functions[0]->getName();

  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  bin_name = estimator.getBinName( 54u );

  true_bin_name = "Energy Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 0.1 ) + "], ";
  true_bin_name += "Time Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 1.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 3 ) + "," + Utility::toString( 10 ) + "], ";
  true_bin_name += "Cosine Bin: [";
  true_bin_name += Utility::toString( -1.0 ) + "," + Utility::toString( -0.5 ) + "], ";
  true_bin_name += response_functions[0]->getName();
  
  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  bin_name = estimator.getBinName( 71u );

  true_bin_name = "Energy Bin: (";
  true_bin_name += Utility::toString( 10.0 ) + "," + Utility::toString( 20.0 ) + "], ";
  true_bin_name += "Time Bin: (";
  true_bin_name += Utility::toString( 2.0 ) + "," + Utility::toString( 3.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 3 ) + "," + Utility::toString( 10 ) + "], ";
  true_bin_name += "Cosine Bin: [";
  true_bin_name += Utility::toString( -1.0 ) + "," + Utility::toString( -0.5 ) + "], ";
  true_bin_name += response_functions[0]->getName();
  
  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  bin_name = estimator.getBinName( 144u );

  true_bin_name = "Energy Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 0.1 ) + "], ";
  true_bin_name += "Time Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 1.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 0 ) + "," + Utility::toString( 0 ) + "], ";
  true_bin_name += "Cosine Bin: (";
  true_bin_name += Utility::toString( 0.5 ) + "," + Utility::toString( 1.0 ) + "], ";
  true_bin_name += response_functions[0]->getName();
  
  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  bin_name = estimator.getBinName( 215u );

  true_bin_name = "Energy Bin: (";
  true_bin_name += Utility::toString( 10.0 ) + "," + Utility::toString( 20.0 ) + "], ";
  true_bin_name += "Time Bin: (";
  true_bin_name += Utility::toString( 2.0 ) + "," + Utility::toString( 3.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 3 ) + "," + Utility::toString( 10 ) + "], ";
  true_bin_name += "Cosine Bin: (";
  true_bin_name += Utility::toString( 0.5 ) + "," + Utility::toString( 1.0 ) + "], ";
  true_bin_name += response_functions[0]->getName();
  
  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  bin_name = estimator.getBinName( 216u );

  true_bin_name = "Energy Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 0.1 ) + "], ";
  true_bin_name += "Time Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 1.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 0 ) + "," + Utility::toString( 0 ) + "], ";
  true_bin_name += "Cosine Bin: [";
  true_bin_name += Utility::toString( -1.0 ) + "," + Utility::toString( -0.5 ) + "], ";
  true_bin_name += response_functions[1]->getName();
  
  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  bin_name = estimator.getBinName( 221u );

  true_bin_name = "Energy Bin: (";
  true_bin_name += Utility::toString( 10.0 ) + "," + Utility::toString( 20.0 ) + "], ";
  true_bin_name += "Time Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 1.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 0 ) + "," + Utility::toString( 0 ) + "], ";
  true_bin_name += "Cosine Bin: [";
  true_bin_name += Utility::toString( -1.0 ) + "," + Utility::toString( -0.5 ) + "], ";
  true_bin_name += response_functions[1]->getName();
  
  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  bin_name = estimator.getBinName( 228u );

  true_bin_name = "Energy Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 0.1 ) + "], ";
  true_bin_name += "Time Bin: (";
  true_bin_name += Utility::toString( 2.0 ) + "," + Utility::toString( 3.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 0 ) + "," + Utility::toString( 0 ) + "], ";
  true_bin_name += "Cosine Bin: [";
  true_bin_name += Utility::toString( -1.0 ) + "," + Utility::toString( -0.5 ) + "], ";
  true_bin_name += response_functions[1]->getName();
  
  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  bin_name = estimator.getBinName( 233u );

  true_bin_name = "Energy Bin: (";
  true_bin_name += Utility::toString( 10.0 ) + "," + Utility::toString( 20.0 ) + "], ";
  true_bin_name += "Time Bin: (";
  true_bin_name += Utility::toString( 2.0 ) + "," + Utility::toString( 3.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 0 ) + "," + Utility::toString( 0 ) + "], ";
  true_bin_name += "Cosine Bin: [";
  true_bin_name += Utility::toString( -1.0 ) + "," + Utility::toString( -0.5 ) + "], ";
  true_bin_name += response_functions[1]->getName();

  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  bin_name = estimator.getBinName( 270u );

  true_bin_name = "Energy Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 0.1 ) + "], ";
  true_bin_name += "Time Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 1.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 3 ) + "," + Utility::toString( 10 ) + "], ";
  true_bin_name += "Cosine Bin: [";
  true_bin_name += Utility::toString( -1.0 ) + "," + Utility::toString( -0.5 ) + "], ";
  true_bin_name += response_functions[1]->getName();
  
  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  bin_name = estimator.getBinName( 287u );

  true_bin_name = "Energy Bin: (";
  true_bin_name += Utility::toString( 10.0 ) + "," + Utility::toString( 20.0 ) + "], ";
  true_bin_name += "Time Bin: (";
  true_bin_name += Utility::toString( 2.0 ) + "," + Utility::toString( 3.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 3 ) + "," + Utility::toString( 10 ) + "], ";
  true_bin_name += "Cosine Bin: [";
  true_bin_name += Utility::toString( -1.0 ) + "," + Utility::toString( -0.5 ) + "], ";
  true_bin_name += response_functions[1]->getName();
  
  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  true_bin_name = "Energy Bin: (";
  true_bin_name += Utility::toString( 10.0 ) + "," + Utility::toString( 20.0 ) + "], ";
  true_bin_name += "Time Bin: (";
  true_bin_name += Utility::toString( 2.0 ) + "," + Utility::toString( 3.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 3 ) + "," + Utility::toString( 10 ) + "], ";
  true_bin_name += "Cosine Bin: [";
  true_bin_name += Utility::toString( -1.0 ) + "," + Utility::toString( -0.5 ) + "], ";
  true_bin_name += response_functions[1]->getName();
  
  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  bin_name = estimator.getBinName( 360u );

  true_bin_name = "Energy Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 0.1 ) + "], ";
  true_bin_name += "Time Bin: [";
  true_bin_name += Utility::toString( 0.0 ) + "," + Utility::toString( 1.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 0 ) + "," + Utility::toString( 0 ) + "], ";
  true_bin_name += "Cosine Bin: (";
  true_bin_name += Utility::toString( 0.5 ) + "," + Utility::toString( 1.0 ) + "], ";
  true_bin_name += response_functions[1]->getName();
  
  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );

  bin_name = estimator.getBinName( 431u );

  true_bin_name = "Energy Bin: (";
  true_bin_name += Utility::toString( 10.0 ) + "," + Utility::toString( 20.0 ) + "], ";
  true_bin_name += "Time Bin: (";
  true_bin_name += Utility::toString( 2.0 ) + "," + Utility::toString( 3.0 ) + "], ";
  true_bin_name += "Collision Number Bin: [";
  true_bin_name += Utility::toString( 3 ) + "," + Utility::toString( 10 ) + "], ";
  true_bin_name += "Cosine Bin: (";
  true_bin_name += Utility::toString( 0.5 ) + "," + Utility::toString( 1.0 ) + "], ";
  true_bin_name += response_functions[1]->getName();
  
  FRENSIE_CHECK_EQUAL( bin_name, true_bin_name );
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
// end tstEstimator.cpp
//---------------------------------------------------------------------------//
