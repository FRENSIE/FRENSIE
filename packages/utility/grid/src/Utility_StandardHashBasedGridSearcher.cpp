//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardHashBasedGridSearcher.cpp
//! \author Alex Robinson
//! \brief  The standard hash-based grid searcher
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
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"

namespace Utility{

  EXPLICIT_TEMPLATE_CLASS_INST( StandardHashBasedGridSearcher<std::vector<double>,true> );

  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,true>::save<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) const );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,true>::save<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) const );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,true>::save<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) const );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,true>::save<boost::archive::polymorphic_oarchive>( boost::archive::polymorphic_oarchive& ar, const unsigned version ) const );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,true>::save<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) const );

  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,true>::load<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,true>::load<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,true>::load<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,true>::load<boost::archive::polymorphic_iarchive>( boost::archive::polymorphic_iarchive& ar, const unsigned version ) );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,true>::load<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) );

  EXPLICIT_TEMPLATE_CLASS_INST( StandardHashBasedGridSearcher<std::vector<double>,false> );

  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,false>::save<boost::archive::text_oarchive>( boost::archive::text_oarchive& ar, const unsigned version ) const );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,false>::save<boost::archive::xml_oarchive>( boost::archive::xml_oarchive& ar, const unsigned version ) const );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,false>::save<boost::archive::binary_oarchive>( boost::archive::binary_oarchive& ar, const unsigned version ) const );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,false>::save<boost::archive::polymorphic_oarchive>( boost::archive::polymorphic_oarchive& ar, const unsigned version ) const );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,false>::save<Utility::HDF5OArchive>( Utility::HDF5OArchive& ar, const unsigned version ) const );

  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,false>::load<boost::archive::text_iarchive>( boost::archive::text_iarchive& ar, const unsigned version ) );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,false>::load<boost::archive::xml_iarchive>( boost::archive::xml_iarchive& ar, const unsigned version ) );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,false>::load<boost::archive::binary_iarchive>( boost::archive::binary_iarchive& ar, const unsigned version ) );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,false>::load<boost::archive::polymorphic_iarchive>( boost::archive::polymorphic_iarchive& ar, const unsigned version ) );
  EXPLICIT_TEMPLATE_FUNCTION_INST( void StandardHashBasedGridSearcher<std::vector<double>,false>::load<Utility::HDF5IArchive>( Utility::HDF5IArchive& ar, const unsigned version ) );
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_StandardHashBasedGridSearcher.cpp
//---------------------------------------------------------------------------//
