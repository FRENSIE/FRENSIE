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

typedef TestArchiveHelper::TestArchives TestArchives;

//---------------------------------------------------------------------------//
// Tests.
//---------------------------------------------------------------------------//
// Check that the constructor will throw an exception if the data is invalid
FRENSIE_UNIT_TEST( AtomProperties, constructor )
{
  FRENSIE_CHECK_NO_THROW( Data::AtomProperties( Data::H_ATOM, 1.0 ) );
  FRENSIE_CHECK_NO_THROW( Data::AtomProperties( Data::He_ATOM, 4.0*amu ) );

  FRENSIE_CHECK_THROW( Data::AtomProperties( Data::H_ATOM, 0.0 ),
                       Data::InvalidScatteringCenterPropertiesData );
  FRENSIE_CHECK_THROW( Data::AtomProperties( Data::He_ATOM, 0.0*amu ),
                       Data::InvalidScatteringCenterPropertiesData );
  
  FRENSIE_CHECK_THROW( Data::AtomProperties( Data::H_ATOM, -1.0 ),
                       Data::InvalidScatteringCenterPropertiesData );
  FRENSIE_CHECK_THROW( Data::AtomProperties( Data::He_ATOM, -1.0*amu ),
                       Data::InvalidScatteringCenterPropertiesData );
}

//---------------------------------------------------------------------------//
// Check that the atom type can be returned
FRENSIE_UNIT_TEST( AtomProperties, atom )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  FRENSIE_CHECK_EQUAL( atom_properties.atom(), Data::H_ATOM );
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

  {
    std::shared_ptr<const Data::PhotoatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                              Data::He_ATOM,
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              0 ) );

    FRENSIE_CHECK_THROW( atom_properties.setPhotoatomicDataProperties( test_data ),
                         Data::InvalidScatteringCenterPropertiesData );

  }
}

//---------------------------------------------------------------------------//
// Check that the photoatomic data file types can be returned
FRENSIE_UNIT_TEST( AtomProperties, getPhotoatomicDataFileTypes )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  FRENSIE_CHECK( atom_properties.getPhotoatomicDataFileTypes().empty() );

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
// Check that the data file versions associated with a file type can be
// returned
FRENSIE_UNIT_TEST( AtomProperties, getDataFileVersions_photoatomic )
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
                                 Data::PhotoatomicDataProperties::ACE_FILE,
                                 1 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 1 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 2 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                              Data::H_ATOM,
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              0 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                              Data::H_ATOM,
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              2 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );
  }

  std::set<unsigned> versions = atom_properties.getDataFileVersions(
                                   Data::PhotoatomicDataProperties::ACE_FILE );

  FRENSIE_CHECK_EQUAL( versions.size(), 2 );
  FRENSIE_CHECK( versions.count( 0 ) );
  FRENSIE_CHECK( versions.count( 1 ) );

  versions = atom_properties.getDataFileVersions(
                               Data::PhotoatomicDataProperties::ACE_EPR_FILE );

  FRENSIE_CHECK_EQUAL( versions.size(), 2 );
  FRENSIE_CHECK( versions.count( 1 ) );
  FRENSIE_CHECK( versions.count( 2 ) );

  versions = atom_properties.getDataFileVersions(
                            Data::PhotoatomicDataProperties::Native_EPR_FILE );

  FRENSIE_CHECK_EQUAL( versions.size(), 2 );
  FRENSIE_CHECK( versions.count( 0 ) );
  FRENSIE_CHECK( versions.count( 2 ) );
}

//---------------------------------------------------------------------------//
// Check that the recommended data file version associated with a file type
// can be returned
FRENSIE_UNIT_TEST( AtomProperties, getRecommendedDataFileVersion_photoatomic )
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
                                 Data::PhotoatomicDataProperties::ACE_FILE,
                                 1 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 1 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 2 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                              Data::H_ATOM,
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              0 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                              Data::H_ATOM,
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              2 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );
  }

  FRENSIE_CHECK_EQUAL( atom_properties.getRecommendedDataFileVersion( Data::PhotoatomicDataProperties::ACE_FILE ), 1 );
  FRENSIE_CHECK_EQUAL( atom_properties.getRecommendedDataFileVersion( Data::PhotoatomicDataProperties::ACE_EPR_FILE ), 2 );
  FRENSIE_CHECK_EQUAL( atom_properties.getRecommendedDataFileVersion( Data::PhotoatomicDataProperties::Native_EPR_FILE ), 2 );
}

//---------------------------------------------------------------------------//
// Check that the photoatomic data properties can be returned
FRENSIE_UNIT_TEST( AtomProperties, getPhotoatomicDataProperties )
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
                                 Data::PhotoatomicDataProperties::ACE_FILE,
                                 1 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 1 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 2 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                              Data::H_ATOM,
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              0 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                              Data::H_ATOM,
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              2 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );
  }

  const Data::PhotoatomicDataProperties* photoatomic_properties =
    &atom_properties.getPhotoatomicDataProperties(
                                Data::PhotoatomicDataProperties::ACE_FILE, 0 );

  FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                       Data::PhotoatomicDataProperties::ACE_FILE );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 0 );
  FRENSIE_CHECK( photoatomic_properties ==
                 atom_properties.getSharedPhotoatomicDataProperties(
                        Data::PhotoatomicDataProperties::ACE_FILE, 0 ).get() );

  photoatomic_properties =
    &atom_properties.getPhotoatomicDataProperties(
                                Data::PhotoatomicDataProperties::ACE_FILE, 1 );

  FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                       Data::PhotoatomicDataProperties::ACE_FILE );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 1 );
  FRENSIE_CHECK( photoatomic_properties ==
                 atom_properties.getSharedPhotoatomicDataProperties(
                        Data::PhotoatomicDataProperties::ACE_FILE, 1 ).get() );

  FRENSIE_CHECK_THROW( atom_properties.getPhotoatomicDataProperties(
                                Data::PhotoatomicDataProperties::ACE_FILE, 2 ),
                       Data::InvalidScatteringCenterPropertiesRequest );

  photoatomic_properties =
    &atom_properties.getPhotoatomicDataProperties(
                            Data::PhotoatomicDataProperties::ACE_EPR_FILE, 1 );

  FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                       Data::PhotoatomicDataProperties::ACE_EPR_FILE );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 1 );
  FRENSIE_CHECK( photoatomic_properties ==
                 atom_properties.getSharedPhotoatomicDataProperties(
                    Data::PhotoatomicDataProperties::ACE_EPR_FILE, 1 ).get() );

  photoatomic_properties =
    &atom_properties.getPhotoatomicDataProperties(
                            Data::PhotoatomicDataProperties::ACE_EPR_FILE, 2 );

  FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                       Data::PhotoatomicDataProperties::ACE_EPR_FILE );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 2 );
  FRENSIE_CHECK( photoatomic_properties ==
                 atom_properties.getSharedPhotoatomicDataProperties(
                    Data::PhotoatomicDataProperties::ACE_EPR_FILE, 2 ).get() );

  FRENSIE_CHECK_THROW( atom_properties.getPhotoatomicDataProperties(
                            Data::PhotoatomicDataProperties::ACE_EPR_FILE, 0 ),
                       Data::InvalidScatteringCenterPropertiesRequest );

  photoatomic_properties =
    &atom_properties.getPhotoatomicDataProperties(
                         Data::PhotoatomicDataProperties::Native_EPR_FILE, 0 );

  FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                       Data::PhotoatomicDataProperties::Native_EPR_FILE );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 0 );
  FRENSIE_CHECK( photoatomic_properties ==
                 atom_properties.getSharedPhotoatomicDataProperties(
                 Data::PhotoatomicDataProperties::Native_EPR_FILE, 0 ).get() );

  photoatomic_properties =
    &atom_properties.getPhotoatomicDataProperties(
                         Data::PhotoatomicDataProperties::Native_EPR_FILE, 2 );

  FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                       Data::PhotoatomicDataProperties::Native_EPR_FILE );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 2 );
  FRENSIE_CHECK( photoatomic_properties ==
                 atom_properties.getSharedPhotoatomicDataProperties(
                 Data::PhotoatomicDataProperties::Native_EPR_FILE, 2 ).get() );

  FRENSIE_CHECK_THROW( atom_properties.getPhotoatomicDataProperties(
                         Data::PhotoatomicDataProperties::Native_EPR_FILE, 1 ),
                       Data::InvalidScatteringCenterPropertiesRequest );
}

//---------------------------------------------------------------------------//
// Check that adjoint photoatomic data properties can be set
FRENSIE_UNIT_TEST( AtomProperties, setAdjointPhotoatomicDataProperties )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  FRENSIE_CHECK( !atom_properties.adjointPhotoatomicDataAvailable( Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE ) );
  
  {
    std::shared_ptr<const Data::AdjointPhotoatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointPhotoatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       0 ) );
    
    atom_properties.setAdjointPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::AdjointPhotoatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       1 ) );
  
    atom_properties.setAdjointPhotoatomicDataProperties( test_data );
  }

  FRENSIE_CHECK( atom_properties.adjointPhotoatomicDataAvailable( Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE ) );
  FRENSIE_CHECK( atom_properties.adjointPhotoatomicDataAvailable( Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 0 ) );
  FRENSIE_CHECK( atom_properties.adjointPhotoatomicDataAvailable( Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 1 ) );
  FRENSIE_CHECK( !atom_properties.adjointPhotoatomicDataAvailable( Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 2 ) );

  {
    std::shared_ptr<const Data::AdjointPhotoatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointPhotoatomicDataProperties>(
                       Data::He_ATOM,
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       0 ) );
    
    FRENSIE_CHECK_THROW( atom_properties.setAdjointPhotoatomicDataProperties( test_data ),
                         Data::InvalidScatteringCenterPropertiesData );
  }
}

//---------------------------------------------------------------------------//
// Check that the adjoint photoatomic data file types can be returned
FRENSIE_UNIT_TEST( AtomProperties, getAdjointPhotoatomicDataFileTypes )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  FRENSIE_CHECK( atom_properties.getAdjointPhotoatomicDataFileTypes().empty() );

  {
    std::shared_ptr<const Data::AdjointPhotoatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointPhotoatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       0 ) );
    
    atom_properties.setAdjointPhotoatomicDataProperties( test_data );
  }

  std::set<Data::AdjointPhotoatomicDataProperties::FileType> file_types =
    atom_properties.getAdjointPhotoatomicDataFileTypes();

  FRENSIE_CHECK( file_types.count( Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE ) );
}

//---------------------------------------------------------------------------//
// Check that the data file versions associated with a file type can be
// returned
FRENSIE_UNIT_TEST( AtomProperties, getDataFileVersions_adjoint_photoatomic )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  {
    std::shared_ptr<const Data::AdjointPhotoatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointPhotoatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       0 ) );
    
    atom_properties.setAdjointPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::AdjointPhotoatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       1 ) );

    atom_properties.setAdjointPhotoatomicDataProperties( test_data );
  }

  std::set<unsigned> versions = atom_properties.getDataFileVersions(
                     Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE );

  FRENSIE_CHECK_EQUAL( versions.size(), 2 );
  FRENSIE_CHECK( versions.count( 0 ) );
  FRENSIE_CHECK( versions.count( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that the recommended data file version associated with a file type
// can be returned
FRENSIE_UNIT_TEST( AtomProperties,
                   getRecommendedDataFileVersion_adjoint_photoatomic )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  {
    std::shared_ptr<const Data::AdjointPhotoatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointPhotoatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       0 ) );
    
    atom_properties.setAdjointPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::AdjointPhotoatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       1 ) );

    atom_properties.setAdjointPhotoatomicDataProperties( test_data );
  }

  FRENSIE_CHECK_EQUAL( atom_properties.getRecommendedDataFileVersion( Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE ), 1 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint photoatomic data properties can be returned
FRENSIE_UNIT_TEST( AtomProperties, getAdjointPhotoatomicDataProperties )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  {
    std::shared_ptr<const Data::AdjointPhotoatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointPhotoatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       0 ) );
    
    atom_properties.setAdjointPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::AdjointPhotoatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       1 ) );

    atom_properties.setAdjointPhotoatomicDataProperties( test_data );
  }

  const Data::AdjointPhotoatomicDataProperties* photoatomic_properties =
    &atom_properties.getAdjointPhotoatomicDataProperties(
                  Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 0 );

  FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 0 );
  FRENSIE_CHECK(
       photoatomic_properties ==
       atom_properties.getSharedAdjointPhotoatomicDataProperties(
          Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 0 ).get() );

  photoatomic_properties =
    &atom_properties.getAdjointPhotoatomicDataProperties(
                  Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 1 );

  FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE );
  FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 1 );
  FRENSIE_CHECK(
       photoatomic_properties ==
       atom_properties.getSharedAdjointPhotoatomicDataProperties(
          Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 1 ).get() );

  FRENSIE_CHECK_THROW(
             atom_properties.getAdjointPhotoatomicDataProperties(
                  Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 2 ),
             Data::InvalidScatteringCenterPropertiesRequest );
}

//---------------------------------------------------------------------------//
// Check that electroatomic data properties can be set
FRENSIE_UNIT_TEST( AtomProperties, setElectroatomicDataProperties )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  FRENSIE_CHECK( !atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE ) );
  FRENSIE_CHECK( !atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_EPR_FILE ) );
  FRENSIE_CHECK( !atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::Native_EPR_FILE ) );
  
  {
    std::shared_ptr<const Data::ElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::ElectroatomicDataProperties::ACE_FILE,
                                 0 ) );
    
    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::ElectroatomicDataProperties::ACE_FILE,
                                 1 ) );
  
    atom_properties.setElectroatomicDataProperties( test_data );
  }

  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE ) );
  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE, 0 ) );
  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE, 1 ) );
  FRENSIE_CHECK( !atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE, 2 ) );
  
  FRENSIE_CHECK( !atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_EPR_FILE ) );
  FRENSIE_CHECK( !atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::Native_EPR_FILE ) );

  {
    std::shared_ptr<const Data::ElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                               Data::H_ATOM,
                               Data::ElectroatomicDataProperties::ACE_EPR_FILE,
                               0 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                               Data::H_ATOM,
                               Data::ElectroatomicDataProperties::ACE_EPR_FILE,
                               1 ) );

    atom_properties.setElectroatomicDataProperties( test_data );
  }

  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE ) );
  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE, 0 ) );
  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE, 1 ) );
  FRENSIE_CHECK( !atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE, 2 ) );
  
  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_EPR_FILE ) );
  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_EPR_FILE, 0 ) );
  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_EPR_FILE, 1 ) );
  FRENSIE_CHECK( !atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_EPR_FILE, 2 ) );
  
  FRENSIE_CHECK( !atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::Native_EPR_FILE ) );

  {
    std::shared_ptr<const Data::ElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                            Data::H_ATOM,
                            Data::ElectroatomicDataProperties::Native_EPR_FILE,
                            0 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                            Data::H_ATOM,
                            Data::ElectroatomicDataProperties::Native_EPR_FILE,
                            1 ) );

    atom_properties.setElectroatomicDataProperties( test_data );
  }

  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE ) );
  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE, 0 ) );
  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE, 1 ) );
  FRENSIE_CHECK( !atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_FILE, 2 ) );
  
  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_EPR_FILE ) );
  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_EPR_FILE, 0 ) );
  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_EPR_FILE, 1 ) );
  FRENSIE_CHECK( !atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::ACE_EPR_FILE, 2 ) );
  
  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::Native_EPR_FILE ) );
  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::Native_EPR_FILE, 0 ) );
  FRENSIE_CHECK( atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::Native_EPR_FILE, 1 ) );
  FRENSIE_CHECK( !atom_properties.electroatomicDataAvailable( Data::ElectroatomicDataProperties::Native_EPR_FILE, 2 ) );

  {
    std::shared_ptr<const Data::ElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                                 Data::He_ATOM,
                                 Data::ElectroatomicDataProperties::ACE_FILE,
                                 0 ) );
    
    FRENSIE_CHECK_THROW( atom_properties.setElectroatomicDataProperties( test_data ),
                         Data::InvalidScatteringCenterPropertiesData );
  }
}

//---------------------------------------------------------------------------//
// Check that the electroatomic data file types can be returned
FRENSIE_UNIT_TEST( AtomProperties, getElectroatomicDataFileTypes )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  FRENSIE_CHECK( atom_properties.getElectroatomicDataFileTypes().empty() );

  {
    std::shared_ptr<const Data::ElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::ElectroatomicDataProperties::ACE_FILE,
                                 0 ) );
    
    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                               Data::H_ATOM,
                               Data::ElectroatomicDataProperties::ACE_EPR_FILE,
                               1 ) );

    atom_properties.setElectroatomicDataProperties( test_data );
  }

  std::set<Data::ElectroatomicDataProperties::FileType> file_types =
    atom_properties.getElectroatomicDataFileTypes();

  FRENSIE_CHECK( file_types.count( Data::ElectroatomicDataProperties::ACE_FILE ) );
  FRENSIE_CHECK( file_types.count( Data::ElectroatomicDataProperties::ACE_EPR_FILE ) );
  FRENSIE_CHECK( !file_types.count( Data::ElectroatomicDataProperties::Native_EPR_FILE ) );
}

//---------------------------------------------------------------------------//
// Check that the data file versions associated with a file type can be
// returned
FRENSIE_UNIT_TEST( AtomProperties, getDataFileVersions_electroatomic )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  {
    std::shared_ptr<const Data::ElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::ElectroatomicDataProperties::ACE_FILE,
                                 0 ) );
    
    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::ElectroatomicDataProperties::ACE_FILE,
                                 1 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                               Data::H_ATOM,
                               Data::ElectroatomicDataProperties::ACE_EPR_FILE,
                               1 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                               Data::H_ATOM,
                               Data::ElectroatomicDataProperties::ACE_EPR_FILE,
                               2 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                            Data::H_ATOM,
                            Data::ElectroatomicDataProperties::Native_EPR_FILE,
                            0 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                            Data::H_ATOM,
                            Data::ElectroatomicDataProperties::Native_EPR_FILE,
                            2 ) );

    atom_properties.setElectroatomicDataProperties( test_data );
  }

  std::set<unsigned> versions = atom_properties.getDataFileVersions(
                                 Data::ElectroatomicDataProperties::ACE_FILE );

  FRENSIE_CHECK_EQUAL( versions.size(), 2 );
  FRENSIE_CHECK( versions.count( 0 ) );
  FRENSIE_CHECK( versions.count( 1 ) );

  versions = atom_properties.getDataFileVersions(
                             Data::ElectroatomicDataProperties::ACE_EPR_FILE );

  FRENSIE_CHECK_EQUAL( versions.size(), 2 );
  FRENSIE_CHECK( versions.count( 1 ) );
  FRENSIE_CHECK( versions.count( 2 ) );

  versions = atom_properties.getDataFileVersions(
                          Data::ElectroatomicDataProperties::Native_EPR_FILE );

  FRENSIE_CHECK_EQUAL( versions.size(), 2 );
  FRENSIE_CHECK( versions.count( 0 ) );
  FRENSIE_CHECK( versions.count( 2 ) );
}

//---------------------------------------------------------------------------//
// Check that the recommended data file version associated with a file type
// can be returned
FRENSIE_UNIT_TEST( AtomProperties, getRecommendedDataFileVersion_electroatomic )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  {
    std::shared_ptr<const Data::ElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::ElectroatomicDataProperties::ACE_FILE,
                                 0 ) );
    
    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::ElectroatomicDataProperties::ACE_FILE,
                                 1 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                               Data::H_ATOM,
                               Data::ElectroatomicDataProperties::ACE_EPR_FILE,
                               1 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                               Data::H_ATOM,
                               Data::ElectroatomicDataProperties::ACE_EPR_FILE,
                               2 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                            Data::H_ATOM,
                            Data::ElectroatomicDataProperties::Native_EPR_FILE,
                            0 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                            Data::H_ATOM,
                            Data::ElectroatomicDataProperties::Native_EPR_FILE,
                            2 ) );

    atom_properties.setElectroatomicDataProperties( test_data );
  }

  FRENSIE_CHECK_EQUAL( atom_properties.getRecommendedDataFileVersion( Data::ElectroatomicDataProperties::ACE_FILE ), 1 );
  FRENSIE_CHECK_EQUAL( atom_properties.getRecommendedDataFileVersion( Data::ElectroatomicDataProperties::ACE_EPR_FILE ), 2 );
  FRENSIE_CHECK_EQUAL( atom_properties.getRecommendedDataFileVersion( Data::ElectroatomicDataProperties::Native_EPR_FILE ), 2 );
}

//---------------------------------------------------------------------------//
// Check that the electroatomic data properties can be returned
FRENSIE_UNIT_TEST( AtomProperties, getElectroatomicDataProperties )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  {
    std::shared_ptr<const Data::ElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::ElectroatomicDataProperties::ACE_FILE,
                                 0 ) );
    
    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::ElectroatomicDataProperties::ACE_FILE,
                                 1 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                               Data::H_ATOM,
                               Data::ElectroatomicDataProperties::ACE_EPR_FILE,
                               1 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                               Data::H_ATOM,
                               Data::ElectroatomicDataProperties::ACE_EPR_FILE,
                               2 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                            Data::H_ATOM,
                            Data::ElectroatomicDataProperties::Native_EPR_FILE,
                            0 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                            Data::H_ATOM,
                            Data::ElectroatomicDataProperties::Native_EPR_FILE,
                            2 ) );

    atom_properties.setElectroatomicDataProperties( test_data );
  }

  const Data::ElectroatomicDataProperties* electroatomic_properties =
    &atom_properties.getElectroatomicDataProperties(
                              Data::ElectroatomicDataProperties::ACE_FILE, 0 );

  FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                       Data::ElectroatomicDataProperties::ACE_FILE );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 0 );
  FRENSIE_CHECK( electroatomic_properties ==
                 atom_properties.getSharedElectroatomicDataProperties(
                      Data::ElectroatomicDataProperties::ACE_FILE, 0 ).get() );

  electroatomic_properties =
    &atom_properties.getElectroatomicDataProperties(
                              Data::ElectroatomicDataProperties::ACE_FILE, 1 );

  FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                       Data::ElectroatomicDataProperties::ACE_FILE );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 1 );
  FRENSIE_CHECK( electroatomic_properties ==
                 atom_properties.getSharedElectroatomicDataProperties(
                      Data::ElectroatomicDataProperties::ACE_FILE, 1 ).get() );

  FRENSIE_CHECK_THROW( atom_properties.getElectroatomicDataProperties(
                              Data::ElectroatomicDataProperties::ACE_FILE, 2 ),
                       Data::InvalidScatteringCenterPropertiesRequest );

  electroatomic_properties =
    &atom_properties.getElectroatomicDataProperties(
                          Data::ElectroatomicDataProperties::ACE_EPR_FILE, 1 );

  FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                       Data::ElectroatomicDataProperties::ACE_EPR_FILE );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 1 );
  FRENSIE_CHECK( electroatomic_properties ==
                 atom_properties.getSharedElectroatomicDataProperties(
                  Data::ElectroatomicDataProperties::ACE_EPR_FILE, 1 ).get() );

  electroatomic_properties =
    &atom_properties.getElectroatomicDataProperties(
                          Data::ElectroatomicDataProperties::ACE_EPR_FILE, 2 );

  FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                       Data::ElectroatomicDataProperties::ACE_EPR_FILE );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 2 );
  FRENSIE_CHECK( electroatomic_properties ==
                 atom_properties.getSharedElectroatomicDataProperties(
                  Data::ElectroatomicDataProperties::ACE_EPR_FILE, 2 ).get() );

  FRENSIE_CHECK_THROW( atom_properties.getElectroatomicDataProperties(
                          Data::ElectroatomicDataProperties::ACE_EPR_FILE, 0 ),
                       Data::InvalidScatteringCenterPropertiesRequest );

  electroatomic_properties =
    &atom_properties.getElectroatomicDataProperties(
                       Data::ElectroatomicDataProperties::Native_EPR_FILE, 0 );

  FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                       Data::ElectroatomicDataProperties::Native_EPR_FILE );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 0 );
  FRENSIE_CHECK(
               electroatomic_properties ==
               atom_properties.getSharedElectroatomicDataProperties(
               Data::ElectroatomicDataProperties::Native_EPR_FILE, 0 ).get() );

  electroatomic_properties =
    &atom_properties.getElectroatomicDataProperties(
                       Data::ElectroatomicDataProperties::Native_EPR_FILE, 2 );

  FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                       Data::ElectroatomicDataProperties::Native_EPR_FILE );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 2 );
  FRENSIE_CHECK(
               electroatomic_properties ==
               atom_properties.getSharedElectroatomicDataProperties(
               Data::ElectroatomicDataProperties::Native_EPR_FILE, 2 ).get() );

  FRENSIE_CHECK_THROW(
                    atom_properties.getElectroatomicDataProperties(
                       Data::ElectroatomicDataProperties::Native_EPR_FILE, 1 ),
                    Data::InvalidScatteringCenterPropertiesRequest );
}

//---------------------------------------------------------------------------//
// Check that adjoint electroatomic data properties can be set
FRENSIE_UNIT_TEST( AtomProperties, setAdjointElectroatomicDataProperties )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  FRENSIE_CHECK( !atom_properties.adjointElectroatomicDataAvailable( Data::AdjointElectroatomicDataProperties::Native_EPR_FILE ) );
  
  {
    std::shared_ptr<const Data::AdjointElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointElectroatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE,
                       0 ) );
    
    atom_properties.setAdjointElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::AdjointElectroatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE,
                       1 ) );
  
    atom_properties.setAdjointElectroatomicDataProperties( test_data );
  }

  FRENSIE_CHECK( atom_properties.adjointElectroatomicDataAvailable( Data::AdjointElectroatomicDataProperties::Native_EPR_FILE ) );
  FRENSIE_CHECK( atom_properties.adjointElectroatomicDataAvailable( Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 0 ) );
  FRENSIE_CHECK( atom_properties.adjointElectroatomicDataAvailable( Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 1 ) );
  FRENSIE_CHECK( !atom_properties.adjointElectroatomicDataAvailable( Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 2 ) );

  {
    std::shared_ptr<const Data::AdjointElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointElectroatomicDataProperties>(
                     Data::He_ATOM,
                     Data::AdjointElectroatomicDataProperties::Native_EPR_FILE,
                     0 ) );
    
    FRENSIE_CHECK_THROW( atom_properties.setAdjointElectroatomicDataProperties( test_data ),
                         Data::InvalidScatteringCenterPropertiesData );
  }
}

//---------------------------------------------------------------------------//
// Check that the adjoint electroatomic data file types can be returned
FRENSIE_UNIT_TEST( AtomProperties, getAdjointElectroatomicDataFileTypes )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  FRENSIE_CHECK( atom_properties.getAdjointElectroatomicDataFileTypes().empty() );

  {
    std::shared_ptr<const Data::AdjointElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointElectroatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE,
                       0 ) );
    
    atom_properties.setAdjointElectroatomicDataProperties( test_data );
  }

  std::set<Data::AdjointElectroatomicDataProperties::FileType> file_types =
    atom_properties.getAdjointElectroatomicDataFileTypes();

  FRENSIE_CHECK( file_types.count( Data::AdjointElectroatomicDataProperties::Native_EPR_FILE ) );
}

//---------------------------------------------------------------------------//
// Check that the data file versions associated with a file type can be
// returned
FRENSIE_UNIT_TEST( AtomProperties, getDataFileVersions_adjoint_electroatomic )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  {
    std::shared_ptr<const Data::AdjointElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointElectroatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE,
                       0 ) );
    
    atom_properties.setAdjointElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::AdjointElectroatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE,
                       1 ) );

    atom_properties.setAdjointElectroatomicDataProperties( test_data );
  }

  std::set<unsigned> versions = atom_properties.getDataFileVersions(
                     Data::AdjointElectroatomicDataProperties::Native_EPR_FILE );

  FRENSIE_CHECK_EQUAL( versions.size(), 2 );
  FRENSIE_CHECK( versions.count( 0 ) );
  FRENSIE_CHECK( versions.count( 1 ) );
}

//---------------------------------------------------------------------------//
// Check that the recommended data file version associated with a file type
// can be returned
FRENSIE_UNIT_TEST( AtomProperties,
                   getRecommendedDataFileVersion_adjoint_electroatomic )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  {
    std::shared_ptr<const Data::AdjointElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointElectroatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE,
                       0 ) );
    
    atom_properties.setAdjointElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::AdjointElectroatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE,
                       1 ) );

    atom_properties.setAdjointElectroatomicDataProperties( test_data );
  }

  FRENSIE_CHECK_EQUAL( atom_properties.getRecommendedDataFileVersion( Data::AdjointElectroatomicDataProperties::Native_EPR_FILE ), 1 );
}

//---------------------------------------------------------------------------//
// Check that the adjoint electroatomic data properties can be returned
FRENSIE_UNIT_TEST( AtomProperties, getAdjointElectroatomicDataProperties )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  {
    std::shared_ptr<const Data::AdjointElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointElectroatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE,
                       0 ) );
    
    atom_properties.setAdjointElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::AdjointElectroatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE,
                       1 ) );

    atom_properties.setAdjointElectroatomicDataProperties( test_data );
  }

  const Data::AdjointElectroatomicDataProperties* electroatomic_properties =
    &atom_properties.getAdjointElectroatomicDataProperties(
                  Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 0 );

  FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 0 );
  FRENSIE_CHECK(
      electroatomic_properties ==
      atom_properties.getSharedAdjointElectroatomicDataProperties(
        Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 0 ).get() );

  electroatomic_properties =
    &atom_properties.getAdjointElectroatomicDataProperties(
                  Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 1 );

  FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                       atom_properties.atom() );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE );
  FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 1 );
  FRENSIE_CHECK(
      electroatomic_properties ==
      atom_properties.getSharedAdjointElectroatomicDataProperties(
        Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 1 ).get() );

  FRENSIE_CHECK_THROW(
             atom_properties.getAdjointElectroatomicDataProperties(
                  Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 2 ),
             Data::InvalidScatteringCenterPropertiesRequest );
}

//---------------------------------------------------------------------------//
// Check that the atom properties can be placed in an output stream
FRENSIE_UNIT_TEST( AtomProperties, toStream )
{
  Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

  // Set the photoatomic data
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

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 1 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 2 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                              Data::H_ATOM,
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              0 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                              Data::H_ATOM,
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              2 ) );

    atom_properties.setPhotoatomicDataProperties( test_data );
  }

  // Set the adjoint photoatomic data
  {
    std::shared_ptr<const Data::AdjointPhotoatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointPhotoatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       0 ) );
    
    atom_properties.setAdjointPhotoatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::AdjointPhotoatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       1 ) );

    atom_properties.setAdjointPhotoatomicDataProperties( test_data );
  }

  // Set the electroatomic data
  {
    std::shared_ptr<const Data::ElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::ElectroatomicDataProperties::ACE_FILE,
                                 0 ) );
    
    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::ElectroatomicDataProperties::ACE_FILE,
                                 1 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                               Data::H_ATOM,
                               Data::ElectroatomicDataProperties::ACE_EPR_FILE,
                               1 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                               Data::H_ATOM,
                               Data::ElectroatomicDataProperties::ACE_EPR_FILE,
                               2 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                            Data::H_ATOM,
                            Data::ElectroatomicDataProperties::Native_EPR_FILE,
                            0 ) );

    atom_properties.setElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                            Data::H_ATOM,
                            Data::ElectroatomicDataProperties::Native_EPR_FILE,
                            2 ) );

    atom_properties.setElectroatomicDataProperties( test_data );
  }

  // Set the adjoint electroatomic data
  {
    std::shared_ptr<const Data::AdjointElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointElectroatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE,
                       0 ) );
    
    atom_properties.setAdjointElectroatomicDataProperties( test_data );

    test_data.reset(
           new Data::TestAtomicDataProperties<Data::AdjointElectroatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE,
                       1 ) );

    atom_properties.setAdjointElectroatomicDataProperties( test_data );
  }

  FRENSIE_CHECK_NO_THROW( atom_properties.toStream( std::cout ) );
  FRENSIE_CHECK_NO_THROW( std::cout << atom_properties );
}

//---------------------------------------------------------------------------//
// Check that the atom properties can be archived
FRENSIE_UNIT_TEST_TEMPLATE_EXPAND( AtomProperties, archive, TestArchives )
{
  FETCH_TEMPLATE_PARAM( 0, RawOArchive );
  FETCH_TEMPLATE_PARAM( 1, RawIArchive );

  typedef typename std::remove_pointer<RawOArchive>::type OArchive;
  typedef typename std::remove_pointer<RawIArchive>::type IArchive;

  std::string archive_base_name( "test_h_atom_properties" );
  std::ostringstream archive_ostream;

  {
    std::unique_ptr<OArchive> oarchive;

    createOArchive( archive_base_name, archive_ostream, oarchive );

    Data::AtomProperties atom_properties( Data::H_ATOM, 1.0*amu );

    // Set the photoatomic data
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
      
      test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 1 ) );

      atom_properties.setPhotoatomicDataProperties( test_data );
      
      test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::PhotoatomicDataProperties::ACE_EPR_FILE,
                                 2 ) );

      atom_properties.setPhotoatomicDataProperties( test_data );
      
      test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                              Data::H_ATOM,
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              0 ) );

      atom_properties.setPhotoatomicDataProperties( test_data );
      
      test_data.reset(
           new Data::TestAtomicDataProperties<Data::PhotoatomicDataProperties>(
                              Data::H_ATOM,
                              Data::PhotoatomicDataProperties::Native_EPR_FILE,
                              2 ) );

      atom_properties.setPhotoatomicDataProperties( test_data );
    }

    // Set the adjoint photoatomic data
    {
      std::shared_ptr<const Data::AdjointPhotoatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointPhotoatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       0 ) );
    
      atom_properties.setAdjointPhotoatomicDataProperties( test_data );
      
      test_data.reset(
           new Data::TestAtomicDataProperties<Data::AdjointPhotoatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE,
                       1 ) );

      atom_properties.setAdjointPhotoatomicDataProperties( test_data );
    }

    // Set the electroatomic data
    {
      std::shared_ptr<const Data::ElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::ElectroatomicDataProperties::ACE_FILE,
                                 0 ) );
    
      atom_properties.setElectroatomicDataProperties( test_data );

      test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                                 Data::H_ATOM,
                                 Data::ElectroatomicDataProperties::ACE_FILE,
                                 1 ) );

      atom_properties.setElectroatomicDataProperties( test_data );
      
      test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                               Data::H_ATOM,
                               Data::ElectroatomicDataProperties::ACE_EPR_FILE,
                               1 ) );

      atom_properties.setElectroatomicDataProperties( test_data );
      
      test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                               Data::H_ATOM,
                               Data::ElectroatomicDataProperties::ACE_EPR_FILE,
                               2 ) );

      atom_properties.setElectroatomicDataProperties( test_data );
      
      test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                            Data::H_ATOM,
                            Data::ElectroatomicDataProperties::Native_EPR_FILE,
                            0 ) );

      atom_properties.setElectroatomicDataProperties( test_data );
      
      test_data.reset(
           new Data::TestAtomicDataProperties<Data::ElectroatomicDataProperties>(
                            Data::H_ATOM,
                            Data::ElectroatomicDataProperties::Native_EPR_FILE,
                            2 ) );

      atom_properties.setElectroatomicDataProperties( test_data );
    }

    // Set the adjoint electroatomic data
    {
      std::shared_ptr<const Data::AdjointElectroatomicDataProperties> test_data(
           new Data::TestAtomicDataProperties<Data::AdjointElectroatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE,
                       0 ) );
    
      atom_properties.setAdjointElectroatomicDataProperties( test_data );
      
      test_data.reset(
           new Data::TestAtomicDataProperties<Data::AdjointElectroatomicDataProperties>(
                       Data::H_ATOM,
                       Data::AdjointElectroatomicDataProperties::Native_EPR_FILE,
                       1 ) );

      atom_properties.setAdjointElectroatomicDataProperties( test_data );
    }

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( atom_properties ) );

    std::unique_ptr<const Data::AtomProperties>
      atom_properties_ptr( new Data::AtomProperties( atom_properties ) );

    FRENSIE_REQUIRE_NO_THROW( (*oarchive) << BOOST_SERIALIZATION_NVP( atom_properties_ptr ) );
  }

  // Copy the archive ostream to an istream
  std::istringstream archive_istream( archive_ostream.str() );

  // Load the archived distributions
  std::unique_ptr<IArchive> iarchive;

  createIArchive( archive_istream, iarchive );

  Data::AtomProperties atom_properties( Data::He_ATOM, 4.0*amu );

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( atom_properties ) );

  FRENSIE_CHECK_EQUAL( atom_properties.atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( atom_properties.atomicWeight(), 1.0*amu );

  {
    const Data::PhotoatomicDataProperties* photoatomic_properties =
      &atom_properties.getPhotoatomicDataProperties(
                                Data::PhotoatomicDataProperties::ACE_FILE, 0 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::PhotoatomicDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 0 );
    
    photoatomic_properties =
      &atom_properties.getPhotoatomicDataProperties(
                                Data::PhotoatomicDataProperties::ACE_FILE, 1 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::PhotoatomicDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 1 );
    
    FRENSIE_CHECK_THROW( atom_properties.getPhotoatomicDataProperties(
                                Data::PhotoatomicDataProperties::ACE_FILE, 2 ),
                         Data::InvalidScatteringCenterPropertiesRequest );

    photoatomic_properties =
      &atom_properties.getPhotoatomicDataProperties(
                            Data::PhotoatomicDataProperties::ACE_EPR_FILE, 1 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::PhotoatomicDataProperties::ACE_EPR_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 1 );

    photoatomic_properties =
      &atom_properties.getPhotoatomicDataProperties(
                            Data::PhotoatomicDataProperties::ACE_EPR_FILE, 2 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::PhotoatomicDataProperties::ACE_EPR_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 2 );
    
    FRENSIE_CHECK_THROW( atom_properties.getPhotoatomicDataProperties(
                            Data::PhotoatomicDataProperties::ACE_EPR_FILE, 0 ),
                         Data::InvalidScatteringCenterPropertiesRequest );

    photoatomic_properties =
      &atom_properties.getPhotoatomicDataProperties(
                         Data::PhotoatomicDataProperties::Native_EPR_FILE, 0 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::PhotoatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 0 );

    photoatomic_properties =
      &atom_properties.getPhotoatomicDataProperties(
                         Data::PhotoatomicDataProperties::Native_EPR_FILE, 2 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::PhotoatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 2 );
    
    FRENSIE_CHECK_THROW( atom_properties.getPhotoatomicDataProperties(
                         Data::PhotoatomicDataProperties::Native_EPR_FILE, 1 ),
                         Data::InvalidScatteringCenterPropertiesRequest );
  }

  {
    const Data::AdjointPhotoatomicDataProperties* photoatomic_properties =
      &atom_properties.getAdjointPhotoatomicDataProperties(
                  Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 0 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 0 );

    photoatomic_properties =
      &atom_properties.getAdjointPhotoatomicDataProperties(
                  Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 1 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 1 );

    FRENSIE_CHECK_THROW(
             atom_properties.getAdjointPhotoatomicDataProperties(
                  Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 2 ),
             Data::InvalidScatteringCenterPropertiesRequest );
  }

  {
    const Data::ElectroatomicDataProperties* electroatomic_properties =
      &atom_properties.getElectroatomicDataProperties(
                              Data::ElectroatomicDataProperties::ACE_FILE, 0 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::ElectroatomicDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 0 );

    electroatomic_properties =
      &atom_properties.getElectroatomicDataProperties(
                              Data::ElectroatomicDataProperties::ACE_FILE, 1 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::ElectroatomicDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 1 );
    
    FRENSIE_CHECK_THROW( atom_properties.getElectroatomicDataProperties(
                              Data::ElectroatomicDataProperties::ACE_FILE, 2 ),
                         Data::InvalidScatteringCenterPropertiesRequest );

    electroatomic_properties =
      &atom_properties.getElectroatomicDataProperties(
                          Data::ElectroatomicDataProperties::ACE_EPR_FILE, 1 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::ElectroatomicDataProperties::ACE_EPR_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 1 );

    electroatomic_properties =
      &atom_properties.getElectroatomicDataProperties(
                          Data::ElectroatomicDataProperties::ACE_EPR_FILE, 2 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::ElectroatomicDataProperties::ACE_EPR_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 2 );

    FRENSIE_CHECK_THROW( atom_properties.getElectroatomicDataProperties(
                          Data::ElectroatomicDataProperties::ACE_EPR_FILE, 0 ),
                         Data::InvalidScatteringCenterPropertiesRequest );

    electroatomic_properties =
      &atom_properties.getElectroatomicDataProperties(
                       Data::ElectroatomicDataProperties::Native_EPR_FILE, 0 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::ElectroatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 0 );

    electroatomic_properties =
      &atom_properties.getElectroatomicDataProperties(
                       Data::ElectroatomicDataProperties::Native_EPR_FILE, 2 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::ElectroatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 2 );

    FRENSIE_CHECK_THROW(
                    atom_properties.getElectroatomicDataProperties(
                       Data::ElectroatomicDataProperties::Native_EPR_FILE, 1 ),
                    Data::InvalidScatteringCenterPropertiesRequest );
  }

  {
    const Data::AdjointElectroatomicDataProperties* electroatomic_properties =
      &atom_properties.getAdjointElectroatomicDataProperties(
                Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 0 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::AdjointElectroatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 0 );

    electroatomic_properties =
      &atom_properties.getAdjointElectroatomicDataProperties(
                Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 1 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties.atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::AdjointElectroatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 1 );

    FRENSIE_CHECK_THROW(
             atom_properties.getAdjointElectroatomicDataProperties(
                Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 2 ),
             Data::InvalidScatteringCenterPropertiesRequest );
  }

  std::unique_ptr<const Data::AtomProperties> atom_properties_ptr;

  FRENSIE_REQUIRE_NO_THROW( (*iarchive) >> BOOST_SERIALIZATION_NVP( atom_properties_ptr ) );

  FRENSIE_CHECK_EQUAL( atom_properties_ptr->atom(), Data::H_ATOM );
  FRENSIE_CHECK_EQUAL( atom_properties_ptr->atomicWeight(), 1.0*amu );

  {
    const Data::PhotoatomicDataProperties* photoatomic_properties =
      &atom_properties_ptr->getPhotoatomicDataProperties(
                                Data::PhotoatomicDataProperties::ACE_FILE, 0 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::PhotoatomicDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 0 );
    
    photoatomic_properties =
      &atom_properties_ptr->getPhotoatomicDataProperties(
                                Data::PhotoatomicDataProperties::ACE_FILE, 1 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::PhotoatomicDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 1 );
    
    FRENSIE_CHECK_THROW( atom_properties_ptr->getPhotoatomicDataProperties(
                                Data::PhotoatomicDataProperties::ACE_FILE, 2 ),
                         Data::InvalidScatteringCenterPropertiesRequest );

    photoatomic_properties =
      &atom_properties_ptr->getPhotoatomicDataProperties(
                            Data::PhotoatomicDataProperties::ACE_EPR_FILE, 1 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::PhotoatomicDataProperties::ACE_EPR_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 1 );

    photoatomic_properties =
      &atom_properties_ptr->getPhotoatomicDataProperties(
                            Data::PhotoatomicDataProperties::ACE_EPR_FILE, 2 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::PhotoatomicDataProperties::ACE_EPR_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 2 );
    
    FRENSIE_CHECK_THROW( atom_properties_ptr->getPhotoatomicDataProperties(
                            Data::PhotoatomicDataProperties::ACE_EPR_FILE, 0 ),
                         Data::InvalidScatteringCenterPropertiesRequest );

    photoatomic_properties =
      &atom_properties_ptr->getPhotoatomicDataProperties(
                         Data::PhotoatomicDataProperties::Native_EPR_FILE, 0 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::PhotoatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 0 );

    photoatomic_properties =
      &atom_properties_ptr->getPhotoatomicDataProperties(
                         Data::PhotoatomicDataProperties::Native_EPR_FILE, 2 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::PhotoatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 2 );
    
    FRENSIE_CHECK_THROW( atom_properties_ptr->getPhotoatomicDataProperties(
                         Data::PhotoatomicDataProperties::Native_EPR_FILE, 1 ),
                         Data::InvalidScatteringCenterPropertiesRequest );
  }

  {
    const Data::AdjointPhotoatomicDataProperties* photoatomic_properties =
      &atom_properties_ptr->getAdjointPhotoatomicDataProperties(
                  Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 0 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 0 );

    photoatomic_properties =
      &atom_properties_ptr->getAdjointPhotoatomicDataProperties(
                  Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 1 );

    FRENSIE_CHECK_EQUAL( photoatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileType(),
                         Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( photoatomic_properties->fileVersion(), 1 );

    FRENSIE_CHECK_THROW(
             atom_properties_ptr->getAdjointPhotoatomicDataProperties(
                  Data::AdjointPhotoatomicDataProperties::Native_EPR_FILE, 2 ),
             Data::InvalidScatteringCenterPropertiesRequest );
  }

  {
    const Data::ElectroatomicDataProperties* electroatomic_properties =
      &atom_properties_ptr->getElectroatomicDataProperties(
                              Data::ElectroatomicDataProperties::ACE_FILE, 0 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::ElectroatomicDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 0 );

    electroatomic_properties =
      &atom_properties_ptr->getElectroatomicDataProperties(
                              Data::ElectroatomicDataProperties::ACE_FILE, 1 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::ElectroatomicDataProperties::ACE_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 1 );
    
    FRENSIE_CHECK_THROW( atom_properties_ptr->getElectroatomicDataProperties(
                              Data::ElectroatomicDataProperties::ACE_FILE, 2 ),
                         Data::InvalidScatteringCenterPropertiesRequest );

    electroatomic_properties =
      &atom_properties_ptr->getElectroatomicDataProperties(
                          Data::ElectroatomicDataProperties::ACE_EPR_FILE, 1 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::ElectroatomicDataProperties::ACE_EPR_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 1 );

    electroatomic_properties =
      &atom_properties_ptr->getElectroatomicDataProperties(
                          Data::ElectroatomicDataProperties::ACE_EPR_FILE, 2 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::ElectroatomicDataProperties::ACE_EPR_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 2 );

    FRENSIE_CHECK_THROW( atom_properties_ptr->getElectroatomicDataProperties(
                          Data::ElectroatomicDataProperties::ACE_EPR_FILE, 0 ),
                         Data::InvalidScatteringCenterPropertiesRequest );

    electroatomic_properties =
      &atom_properties_ptr->getElectroatomicDataProperties(
                       Data::ElectroatomicDataProperties::Native_EPR_FILE, 0 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::ElectroatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 0 );

    electroatomic_properties =
      &atom_properties_ptr->getElectroatomicDataProperties(
                       Data::ElectroatomicDataProperties::Native_EPR_FILE, 2 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::ElectroatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 2 );

    FRENSIE_CHECK_THROW(
                    atom_properties_ptr->getElectroatomicDataProperties(
                       Data::ElectroatomicDataProperties::Native_EPR_FILE, 1 ),
                    Data::InvalidScatteringCenterPropertiesRequest );
  }

  {
    const Data::AdjointElectroatomicDataProperties* electroatomic_properties =
      &atom_properties_ptr->getAdjointElectroatomicDataProperties(
                Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 0 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::AdjointElectroatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 0 );

    electroatomic_properties =
      &atom_properties_ptr->getAdjointElectroatomicDataProperties(
                Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 1 );

    FRENSIE_CHECK_EQUAL( electroatomic_properties->atom(),
                         atom_properties_ptr->atom() );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileType(),
                         Data::AdjointElectroatomicDataProperties::Native_EPR_FILE );
    FRENSIE_CHECK_EQUAL( electroatomic_properties->fileVersion(), 1 );

    FRENSIE_CHECK_THROW(
             atom_properties_ptr->getAdjointElectroatomicDataProperties(
                Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, 2 ),
             Data::InvalidScatteringCenterPropertiesRequest );
  }
}

//---------------------------------------------------------------------------//
// end tstAtomProperties.cpp
//---------------------------------------------------------------------------//
