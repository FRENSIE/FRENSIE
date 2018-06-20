//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleEnteringCellEventActor.cpp
//! \author Alex Robinson
//! \brief  Particle entering cell event actor base class declaration.
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
#include "MonteCarlo_ParticleEnteringCellEventActor.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_HDF5IArchive.hpp"

EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::ParticleEnteringCellEventActor );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleEnteringCellEventActor.cpp
//---------------------------------------------------------------------------//
