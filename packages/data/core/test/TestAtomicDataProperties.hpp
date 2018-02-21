//---------------------------------------------------------------------------//
//!
//! \file   TestAtomicDataPropertiesProperties.hpp
//! \author Alex Robinson
//! \brief  The data properties class implementations for testing
//!
//---------------------------------------------------------------------------//

#ifndef TEST_ATOMIC_DATA_PROPERTIES_HPP
#define TEST_ATOMIC_DATA_PROPERTIES_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/filesystem.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Data_PhotoatomicDataProperties.hpp"
#include "Data_AdjointPhotoatomicDataProperties.hpp"
#include "Data_ElectroatomicDataProperties.hpp"
#include "Data_AdjointElectroatomicDataProperties.hpp"

namespace Data{

//! The atomic data properties test class
template<typename BaseProperties>
class TestAtomicDataProperties : public BaseProperties
{

public:
  
  //! Constructor
  TestAtomicDataProperties( const AtomType atom,
                            const typename BaseProperties::FileType file_type =
                            BaseProperties::ACE_FILE,
                            const unsigned version = 0 )
    : d_atom( atom ),
      d_file_type( file_type ),
      d_version( version )
  { /* ... */ }
   
  //! Destructor
  ~TestAtomicDataProperties()
  { /* ... */ }

  //! Get the atom that the file specifies data for
  AtomType atom() const override
  { return d_atom; }

  //! Get the photoatomic data file type
  typename BaseProperties::FileType fileType() const override
  { return d_file_type; }

  //! Get the photoatomic data file path (relative to the data directory)
  boost::filesystem::path filePath() const override
  { return boost::filesystem::current_path(); }

  //! Get the photoatomic data file start line
  size_t fileStartLine() const override
  { return 0; }

  //! Get the photoatomic data file version
  unsigned fileVersion() const override
  { return d_version; }

  //! Get the photoatomic table name
  std::string tableName() const override
  { return "test"; }

  //! Clone the properties
  TestAtomicDataProperties* clone() const override
  { return new TestAtomicDataProperties<BaseProperties>( d_atom, d_file_type ); }

private:

  // Save the properties to an archive
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { 
    ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP( BaseProperties );
    ar & BOOST_SERIALIZATION_NVP( d_atom );
    ar & BOOST_SERIALIZATION_NVP( d_file_type );
  }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The atom
  AtomType d_atom;

  // The file type
  typename BaseProperties::FileType d_file_type;

  // The file version
  unsigned d_version;
};

} // end Data namespace

#endif // end TEST_ATOMIC_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end TestAtomicDataPropertiesProperties.hpp
//---------------------------------------------------------------------------//
