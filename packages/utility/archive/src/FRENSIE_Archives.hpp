//---------------------------------------------------------------------------//
//!
//! \file   FRENSIE_Archives.hpp
//! \author Alex Robinson
//! \brief  All archives that can be used by FRENSIE. This file must be
//!         included before all other FRENSIE includes in a .cpp file that
//!         has a serialize, save or load method defined
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ARCHIVES_HPP
#define UTILITY_ARCHIVES_HPP

// FRENSIE Includes
#include "FRENSIE_config.hpp"

#ifdef HAVE_FRENSIE_HDF5
#include "Utility_HDF5OArchive.hpp"
#include "Utility_HDF5IArchive.hpp"
#endif // end HAVE_FRENSIE_HDF5

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

#ifdef HAVE_FRENSIE_MPI
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/packed_iarchive.hpp>
#include <boost/mpi/skeleton_and_content.hpp>
#include <boost/mpi/detail/mpi_datatype_oarchive.hpp>
#endif // end HAVE_FRENSIE_MPI

#endif // end UTILITY_ARCHIVES_HPP

//---------------------------------------------------------------------------//
// end FRENSIE_Archives.hpp
//---------------------------------------------------------------------------//
