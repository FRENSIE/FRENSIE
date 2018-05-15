//---------------------------------------------------------------------------//
//!
//! \file   Utility_CartesianSpatialCoordinateConversionPolicy.cpp
//! \author Alex Robinson
//! \brief  Cartesian spatial coordinate conversion policy template instant.
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
#include "Utility_CartesianSpatialCoordinateConversionPolicy.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

EXPLICIT_SYSTEM_CLASS_SERIALIZE_INST( Utility::CartesianSpatialCoordinateConversionPolicy );

//---------------------------------------------------------------------------//
// end Utility_CartesianSpatialCoordinateConversionPolicy.cpp
//---------------------------------------------------------------------------//
