//---------------------------------------------------------------------------//
//!
//! \file   Utility_EvaporationDistribution.cpp
//! \author Alex Robinson
//! \brief  The evaporation distribution class template instantiations
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

// FRENSIE Includes
#include "Utility_EvaporationDistribution.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

// Explicit instantiation
EXPLICIT_TEMPLATE_CLASS_INST( UnitAwareEvaporationDistribution<void,void> );

EXPLICIT_TEMPLATE_FUNCTION_INST( void UnitAwareEvaporationDistribution<void,void>::save<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) const );
EXPLICIT_TEMPLATE_FUNCTION_INST( void UnitAwareEvaporationDistribution<void,void>::save<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) const );
EXPLICIT_TEMPLATE_FUNCTION_INST( void UnitAwareEvaporationDistribution<void,void>::save<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) const );
EXPLICIT_TEMPLATE_FUNCTION_INST( void UnitAwareEvaporationDistribution<void,void>::save<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) const );
  
EXPLICIT_TEMPLATE_FUNCTION_INST( void UnitAwareEvaporationDistribution<void,void>::load<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) );
EXPLICIT_TEMPLATE_FUNCTION_INST( void UnitAwareEvaporationDistribution<void,void>::load<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) );
EXPLICIT_TEMPLATE_FUNCTION_INST( void UnitAwareEvaporationDistribution<void,void>::load<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) );
EXPLICIT_TEMPLATE_FUNCTION_INST( void UnitAwareEvaporationDistribution<void,void>::load<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) );

} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_EvaporationDistribution.cpp
//---------------------------------------------------------------------------//
