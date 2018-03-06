//---------------------------------------------------------------------------//
//!
//! \file   Utility_HybridElasticDistribution.cpp
//! \author Luke Kersting
//! \brief  The hybrid elastic distribution class template instantiations
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
#include "Utility_HybridElasticDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

// Explicit instantiation
EXPLICIT_DISTRIBUTION_INST( UnitAwareHybridElasticDistribution<LinLin,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareHybridElasticDistribution<LogLin,void,void> );

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_HybridElasticDistribution.cpp
//---------------------------------------------------------------------------//
