//---------------------------------------------------------------------------//
//!
//! \file   Utility_SphericalSpatialCoordinateConversionPolicy.hpp
//! \author Alex Robinson
//! \brief  Spherical spatial coordinate conversion policy declaration
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
#include "Utility_SphericalSpatialCoordinateConversionPolicy.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

EXPLICIT_SYSTEM_CLASS_SERIALIZE_INST( Utility::SphericalSpatialCoordinateConversionPolicy );

//---------------------------------------------------------------------------//
// end Utility_SphericalSpatialCoordinateConversionPolicy.hpp
//---------------------------------------------------------------------------//
