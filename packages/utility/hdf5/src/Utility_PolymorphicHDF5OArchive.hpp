//---------------------------------------------------------------------------//
//!
//! \file   Utility_PolymorphicHDF5OArchive.hpp
//! \author Alex Robinson
//! \brief  Polymorphic HDF5 output archive class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_POLYMORPHIC_HDF5_OARCHIVE_HPP
#define UTILITY_POLYMORPHIC_HDF5_OARCHIVE_HPP

// Boost Includes
#include <boost/config.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>

// FRENSIE Includes
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

/*! The polymorphic HDF5 output archive
 * \ingroup hdf5
 */
typedef boost::archive::detail::polymorphic_oarchive_route<Utility::HDF5OArchive> PolymorphicHDF5OArchive;

TYPE_NAME_TRAITS_QUICK_DECL( PolymorphicHDF5OArchive );
  
} // end Utility namespace

// The archive must be registered before we can use the export method
BOOST_SERIALIZATION_REGISTER_ARCHIVE(Utility::PolymorphicHDF5OArchive)

// Allow use of our custom HDF5 array optimization methods
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(Utility::PolymorphicHDF5OArchive)

#endif // end UTILITY_POLYMORPHIC_HDF5_OARCHIVE_HPP

//---------------------------------------------------------------------------//
// end Utility_PolymorphicHDF5OArchive.hpp
//---------------------------------------------------------------------------//
