//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FullPhaseSpaceParticleResponseFunction.cpp
//! \author Alex Robinson
//! \brief  Full phase-space particle response function class definition
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
#include "MonteCarlo_FullPhaseSpaceParticleResponseFunction.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
FullPhaseSpaceParticleResponseFunction::FullPhaseSpaceParticleResponseFunction(
             const std::shared_ptr<const ParticleDistribution>& particle_dist )
  : d_particle_dist( particle_dist )
{
  // Make sure that the particle distribution pointer is valid
  testPrecondition( particle_dist.get() );
}

// Evaluate the response function at the desired phase space point
double FullPhaseSpaceParticleResponseFunction::evaluate( const ParticleState& particle ) const
{
  return d_particle_dist->evaluate( particle );
}

// Check if the response function is spatially uniform
bool FullPhaseSpaceParticleResponseFunction::isSpatiallyUniform() const
{
  return d_particle_dist->isSpatiallyUniform();
}

// Get a description of the response function
std::string FullPhaseSpaceParticleResponseFunction::description() const
{
  return std::string("f_\"") + d_particle_dist->getName() + "\"(particle)";
}

EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::FullPhaseSpaceParticleResponseFunction );
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( FullPhaseSpaceParticleResponseFunction, MonteCarlo );

//---------------------------------------------------------------------------//
// end MonteCarlo_FullPhaseSpaceParticleResponseFunction.cpp
//---------------------------------------------------------------------------//
