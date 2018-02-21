//---------------------------------------------------------------------------//
//!
//! \file   tstAtomProperties.cpp
//! \author Alex Robinson
//! \brief  Atom properties unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>

// FRENSIE Includes
#include "Data_AtomProperties.hpp"
#include "Utility_UnitTestHarnessWithMain.hpp"
#include "TestAtomicDataProperties.hpp"
#include "ArchiveTestHelpers.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

using Utility::Units::amu;

typedef std::tuple<
  std::tuple<boost::archive::xml_oarchive,boost::archive::xml_iarchive>,
  std::tuple<boost::archive::text_oarchive,boost::archive::text_iarchive>,
  std::tuple<boost::archive::binary_oarchive,boost::archive::binary_iarchive>,
  std::tuple<Utility::HDF5OArchive,Utility::HDF5IArchive>,
  std::tuple<boost::archive::polymorphic_oarchive*,boost::archive::polymorphic_iarchive*>
  > TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the properties do not correspond to a nuclide
FRENSIE_UNIT_TEST( AtomProperties, isNuclide )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  FRENSIE_CHECK( !atom_properties.isNuclide() );
}

//---------------------------------------------------------------------------//
// Check that the zaid can be returned
FRENSIE_UNIT_TEST( AtomProperties, zaid )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  FRENSIE_CHECK_EQUAL( atom_properties.zaid(), Data::ZAID(Data::H_ATOM) );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight can be returned
FRENSIE_UNIT_TEST( AtomProperties, atomicWeight )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  FRENSIE_CHECK_EQUAL( atom_properties.atomicWeight(), 1.0*amu );
}

//---------------------------------------------------------------------------//
// Check that the atomic weight ratio can be returned
FRENSIE_UNIT_TEST( AtomProperties, atomicWeightRatio )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0 );

  FRENSIE_CHECK_EQUAL( atom_properties.atomicWeightRatio(), 1.0 );
}

//---------------------------------------------------------------------------//
// Check that photoatomic data properties can be set
FRENSIE_UNIT_TEST( AtomProperties, setPhotoatomicDataProperties )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  FRENSIE_CHECK( !atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE ) );
  FRENSIE_CHECK( !atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_EPR_FILE ) );
  FRENSIE_CHECK( !atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::Native_EPR_FILE ) );
  
  {
    std::shared_ptr<const Data::PhotoatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_FILE,
                                 0 ) );
    
    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_FILE,
                                 1 ) );
  
    atom_properties.setPhotoatomicDataProperties( test_data );
  }

  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE ) );
  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE, 0 ) );
  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE, 1 ) );
  FRENSIE_CHECK( !atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE, 2 ) );
  
  FRENSIE_CHECK( !atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_EPR_FILE ) );
  FRENSIE_CHECK( !atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::Native_EPR_FILE ) );

  {
    std::shared_ptr<const Data::PhotoatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 0 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 1 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );
  }

  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE ) );
  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE, 0 ) );
  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE, 1 ) );
  FRENSIE_CHECK( !atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE, 2 ) );
  
  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_EPR_FILE ) );
  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_EPR_FILE, 0 ) );
  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_EPR_FILE, 1 ) );
  FRENSIE_CHECK( !atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_EPR_FILE, 2 ) );
  
  FRENSIE_CHECK( !atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::Native_EPR_FILE ) );

  {
    std::shared_ptr<const Data::PhotoatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                              Data::H_ATOM,
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              0 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                              Data::H_ATOM,
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              1 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );
  }

  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE ) );
  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE, 0 ) );
  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE, 1 ) );
  FRENSIE_CHECK( !atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_FILE, 2 ) );
  
  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_EPR_FILE ) );
  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_EPR_FILE, 0 ) );
  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_EPR_FILE, 1 ) );
  FRENSIE_CHECK( !atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::ACE_EPR_FILE, 2 ) );
  
  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::Native_EPR_FILE ) );
  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::Native_EPR_FILE, 0 ) );
  FRENSIE_CHECK( atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::Native_EPR_FILE, 1 ) );
  FRENSIE_CHECK( !atom_properties.photoatomicDataAvailable( Data::PhotoatomicDataProperties::Native_EPR_FILE, 2 ) );
}

//---------------------------------------------------------------------------//
// Check that the photoatomic data file types can be returned
FRENSIE_UNIT_TEST( AtomProperties, getPhotoatomicDataFileTypes )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  {
    std::shared_ptr<const Data::PhotoatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_FILE,
                                 0 ) );
    
    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 1 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );
  }

  std::set<Data::PhotoatomicDataProperties::FileType> file_types =
    atom_properties.getPhotoatomicDataFileTypes();

  FRENSIE_CHECK( file_types.count( Data::PhotoatomicDataProperties::ACE_FILE ) );
  FRENSIE_CHECK( file_types.count( Data::PhotoatomicDataProperties::ACE_EPR_FILE ) );
  FRENSIE_CHECK( !file_types.count( Data::PhotoatomicDataProperties::Native_EPR_FILE ) );
}

//---------------------------------------------------------------------------//
// end tstAtomProperties.cpp
//---------------------------------------------------------------------------//
