//---------------------------------------------------------------------------//
//!
//! \file   Utility_PolymorphicHDF5IArchive.hpp
//! \author Alex Robinson
//! \brief  Polymorphic HDF5 input archive class declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_POLYMORPHIC_HDF5_IARCHIVE_HPP
#define UTILITY_POLYMORPHIC_HDF5_IARCHIVE_HPP

// Boost Includes
#include <boost/config.hpp>
#include <boost/archive/detail/polymorphic_iarchive_route.hpp>

// FRENSIE Includes
#include "Utility_HDF5IArchive.hpp"

namespace Utility{

/*! The polymorphic HDF5 input archive
 * \ingroup hdf5
 */
typedef public boost::archive::detail::polymorphic_iarchive_route<Utility::NakedHDF5IArchive> PolymorphicHDF5IArchive;

} // end Utility namespace

// The archive must be registered before we can use the export method
BOOST_SERIALIZATION_REGISTER_ARCHIVE(Utility::PolymorphicHDF5IArchive)

// Allow use of our custom HDF5 array optimization methods
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(Utility::PolymorphicHDF5IArchive)

#endif // end UTILITY_POLYMORPHIC_HDF5_IARCHIVE_HPP

//---------------------------------------------------------------------------//
// end Utility_PolymorphicHDF5IArchive.hpp
//---------------------------------------------------------------------------//