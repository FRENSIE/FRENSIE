//---------------------------------------------------------------------------//
//!
//! \file   TestParticleState.hpp
//! \author Alex Robinson
//! \brief  Dummy particle state child for testing
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/serialization/base_object.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"

//! The test particle state class
class TestParticleState : public MonteCarlo::ParticleState
{
public:

  TestParticleState()
  { /* ... */ }

  TestParticleState( const unsigned long long history_number )
  : MonteCarlo::ParticleState( history_number, MonteCarlo::PHOTON, 1 )
  { /* ... */ }

  TestParticleState( const MonteCarlo::ParticleState& existing_base_state,
                     const bool increment_generation_number = false,
                     const bool reset_collision_number = false )
    : MonteCarlo::ParticleState( existing_base_state,
                                 MonteCarlo::PHOTON,
                                 1,
                                 increment_generation_number,
                                 reset_collision_number,
                                 existing_base_state.getRaySafetyDistance() )
  { /* ... */ }

  ~TestParticleState()
  { /* ... */ }

  double getSpeed() const override
  { return 1.0; }

  MonteCarlo::ParticleState::timeType calculateTraversalTime(
                                         const double distance ) const override
  { return distance/this->getSpeed(); }

  MonteCarlo::ParticleState* clone() const override
  { return NULL; }

  void toStream( std::ostream& os ) const override
  { printImplementation<TestParticleState>( os ); }

private:
  TestParticleState( const TestParticleState& state );

  // Save the state to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  {
    ar & boost::serialization::make_nvp("ParticleState",boost::serialization::base_object<MonteCarlo::ParticleState>(*this));
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

//---------------------------------------------------------------------------//
// end TestParticleState.hpp
//---------------------------------------------------------------------------//

