//---------------------------------------------------------------------------//
//!
//! \file   Utility_BoostVersion.hpp
//! \author Alex Robinson
//! \brief  The boost version macro definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_BOOST_VERSION_HPP
#define UTILITY_BOOST_VERSION_HPP

// Boost Includes
#include <boost/version.hpp>

#define BOOST_MAJOR_VERSION BOOST_VERSION / 100000

#define BOOST_MINOR_VERSION BOOST_VERSION / 100 % 1000

#endif // end UTILITY_BOOST_VERSION_HPP

//---------------------------------------------------------------------------//
// end Utility_BoostVersion.hpp
//---------------------------------------------------------------------------//
