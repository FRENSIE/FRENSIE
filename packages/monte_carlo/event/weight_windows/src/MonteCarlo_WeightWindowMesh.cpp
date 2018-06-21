//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_WeightWindowMesh.cpp
//! \author Alex Robinson
//! \brief  Weight window mesh class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "MonteCarlo_WeightWindowMesh.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Default constructor
WeightWindowMesh::WeightWindowMesh()
  : d_id( std::numeric_limits<size_t>::max() )
{ /* ... */ }

// Constructor
WeightWindowMesh::WeightWindowMesh( const size_t id,
                                    const ParticleType particle_type )
  : d_id( id ),
    d_particle_type( particle_type )
{ /* ... */ }

// Update the particle state and bank
void WeightWindowMesh::updateFromGlobalParticleCollidingEvent(
                  const SimulateParticleCollision& simulate_particle_collision,
                  ParticleState& particle,
                  ParticleBank& bank ) const
{
  // Make sure that the particle type is valid
  testPrecondition( particle.getParticleType() == d_particle_type );

  // Determine if the particle needs to be killed, split or left alone
  std::shared_ptr<ParticleState> split_particle;
  
  // Killed
  // particle.setAsGone();

  // Split
  // particle.setWeight( x );
  // split_particle.reset( particle.clone() );
  
  if( split_particle )
  {
    ParticleBank local_bank;

    // Simulate the collision of the split particle
    simulate_particle_collision( *split_particle, local_bank );

    // Add the split particle to the bank
    bank.push( split_particle );

    // Add the local bank to the bank (doing this last ensures that the
    // collided particle will be simulated before its progeny, assuming that
    // no bank sorting occurs)
    bank.splice( local_bank );
  }
}
  
} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::WeightWindowMesh );
EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( MonteCarlo::WeightWindowMesh );

//---------------------------------------------------------------------------//
// end MonteCarlo_WeightWindowMesh.cpp
//---------------------------------------------------------------------------//
