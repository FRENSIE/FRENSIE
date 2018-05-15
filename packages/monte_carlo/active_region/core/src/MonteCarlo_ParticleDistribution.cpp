//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleDistribution.hpp
//! \author Alex Robinson
//! \brief  Particle distribution class declaration
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>

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
#include "MonteCarlo_ParticleDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Constructor
ParticleDistribution::ParticleDistribution( const size_t id,
                                            const std::string& name )
  : d_id( id ),
    d_name( name )
{
  // Make sure that the id is valid
  testPrecondition( id != std::numeric_limits<size_t>::max() );
  // Make sure that the name is valid
  testPrecondition( name.size() > 0 );
}

// Return the id
ModuleTraits::InternalROIHandle ParticleDistribution::getId() const
{
  return d_id;
}

// Return the name of the region of interest
const std::string& ParticleDistribution::getName() const
{
  return d_name;
}

EXPLICIT_MONTE_CARLO_CLASS_SAVE_LOAD_INST( ParticleDistribution );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleDistribution.cpp
//---------------------------------------------------------------------------//
