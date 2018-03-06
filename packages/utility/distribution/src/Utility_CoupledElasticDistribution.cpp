//---------------------------------------------------------------------------//
//!
//! \file   Utility_CoupledElasticDistribution.cpp
//! \author Luke Kersting
//! \brief  The coupled elastic distribution class template instantiations
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
#include "Utility_CoupledElasticDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

// Explicit instantiation
EXPLICIT_DISTRIBUTION_INST( UnitAwareCoupledElasticDistribution<LinLin,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareCoupledElasticDistribution<LogLin,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareCoupledElasticDistribution<LinLogCos,void,void> );
EXPLICIT_DISTRIBUTION_INST( UnitAwareCoupledElasticDistribution<LogLogCos,void,void> );

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_CoupledElasticDistribution.cpp
//---------------------------------------------------------------------------//
