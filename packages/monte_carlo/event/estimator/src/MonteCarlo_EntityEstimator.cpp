//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EntityEstimator.cpp
//! \author Alex Robinson
//! \brief  The Entity estimator class template instantiations
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
#include "MonteCarlo_EntityEstimator.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace MonteCarlo{

EXPLICIT_TEMPLATE_CLASS_INST( EntityEstimator<Geometry::Model::InternalCellHandle> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZATION_INST( MonteCarlo::EntityEstimator<Geometry::Model::InternalCellHandle> );

EXPLICIT_TEMPLATE_CLASS_INST( EntityEstimator<size_t> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZATION_INST( MonteCarlo::EntityEstimator<size_t> );
  
EXPLICIT_TEMPLATE_CLASS_INST( EntityEstimator<moab::EntityHandle> );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZATION_INST( MonteCarlo::EntityEstimator<moab::EntityHandle> );
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_EntityEstimator.cpp
//---------------------------------------------------------------------------//
