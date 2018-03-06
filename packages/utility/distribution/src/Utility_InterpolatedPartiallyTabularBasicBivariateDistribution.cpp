//---------------------------------------------------------------------------//
//!
//! \file   Utility_InterpolatedPartiallyTabularBasicBivariateDistribution.cpp
//! \author Alex Robinson
//! \brief  The interpolated partially tabular basic bivariate dist. class
//!         template instantiation
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
#include "Utility_InterpolatedPartiallyTabularBasicBivariateDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

EXPLICIT_INTERPOLATED_TABULAR_BASIC_BIVARIATE_DIST( Utility::InterpolatedPartiallyTabularBasicBivariateDistribution, void, void, void );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_InterpolatedPartiallyTabularBasicBivariateDistribution.cpp
//---------------------------------------------------------------------------//
