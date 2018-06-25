//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleCrossingSurfaceEventObserver.cpp
//! \author Alex Robinson
//! \brief  Particle crossing surface event observer base class template
//!         instantiations
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
#include "MonteCarlo_ParticleCrossingSurfaceEventObserver.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_HDF5IArchive.hpp"

EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::ParticleCrossingSurfaceEventObserver );

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleCrossingSurfaceEventObserver.cpp
//---------------------------------------------------------------------------//
