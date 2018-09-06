//---------------------------------------------------------------------------//
//!
//! \file   Data_PhotoatomicDataProperties.hpp
//! \author Alex Robinson
//! \brief  The photoatomic data properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_PHOTOATOMIC_DATA_PROPERTIES_HPP
#define DATA_PHOTOATOMIC_DATA_PROPERTIES_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/filesystem/path.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Data_AtomType.hpp"
#include "Utility_AtomicMassUnit.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

//! The photoatomic data properties base class
class PhotoatomicDataProperties
{

public:

  /*! The file types
   *
   * When adding a new file type the toString and serialize method must be
   * updated.
   */
  enum FileType{
    ACE_FILE = 0,
    ACE_EPR_FILE,
    Native_ENDL_FILE,
    Native_EPR_FILE
  };

  //! The atomic mass unit
  typedef Utility::Units::AtomicMass AtomicMassUnit;

  //! The atomic mass quantity
  typedef boost::units::quantity<AtomicMassUnit> AtomicWeight;

  //! Default constructor
  PhotoatomicDataProperties();

  //! Destructor
  virtual ~PhotoatomicDataProperties()
  { /* ... */ }

  //! Get the atom that the file specifies data for
  virtual AtomType atom() const = 0;

  //! Get the atomic number that the file specifies data for
  virtual unsigned atomicNumber() const
  { return this->atom(); }

  //! Get the atomic weight of the nuclide that the file specifies data for
  virtual AtomicWeight atomicWeight() const = 0;

  //! Get the photoatomic data file type
  virtual FileType fileType() const = 0;

  //! Get the photoatomic data file path (relative to the data directory)
  virtual boost::filesystem::path filePath() const = 0;

  //! Get the photoatomic data file start line
  virtual size_t fileStartLine() const = 0;

  //! Get the photoatomic data file version
  virtual unsigned fileVersion() const = 0;

  //! Get the photoatomic table name
  virtual std::string tableName() const = 0;

  //! Clone the properties
  virtual PhotoatomicDataProperties* clone() const = 0;

private:

  // Save the properties to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const
  { /* ... */ }

  // Load the properties from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version )
  { /* ... */ }

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end Data namespace

namespace Utility{

/*! \brief Specialization of Utility::ToStringTraits for
 * Data::PhotoatomicDataProperties::FileType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<Data::PhotoatomicDataProperties::FileType>
{
  //! Convert a Data::PhotoatomicDataProperties::FileType to a string
  static std::string toString( const Data::PhotoatomicDataProperties::FileType type );

  //! Place the Data::PhotoatomicDataProperties::FileType in a stream
  static void toStream( std::ostream& os, const Data::PhotoatomicDataProperties::FileType type );
};

} // end Utility namespace

namespace std{

//! Stream operator for printing Data::PhotoatomicDataProperties::FileType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const Data::PhotoatomicDataProperties::FileType type )
{
  Utility::toStream( os, type );

  return os;
}

} // end std namespace

namespace boost{

namespace serialization{

//! Serialize the file type enum
template<typename Archive>
void serialize( Archive& archive,
                Data::PhotoatomicDataProperties::FileType& file_type,
                const unsigned version )
{
  if( Archive::is_saving::value )
    archive & (int)file_type;
  else
  {
    int raw_file_type;

    archive & raw_file_type;

    switch( raw_file_type )
    {
      BOOST_SERIALIZATION_ENUM_CASE( Data::PhotoatomicDataProperties::ACE_FILE, int, file_type );
      BOOST_SERIALIZATION_ENUM_CASE( Data::PhotoatomicDataProperties::ACE_EPR_FILE, int, file_type );
      BOOST_SERIALIZATION_ENUM_CASE( Data::PhotoatomicDataProperties::Native_ENDL_FILE, int, file_type );
      BOOST_SERIALIZATION_ENUM_CASE( Data::PhotoatomicDataProperties::Native_EPR_FILE, int, file_type );
      default:
      {
        THROW_EXCEPTION( std::logic_error,
                         "Unable to deserialize file type "
                         << raw_file_type << "!" );
      }
    }
  }
}

} // end serialization namespace

} // end boost namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( PhotoatomicDataProperties, Data );
BOOST_SERIALIZATION_CLASS_VERSION( PhotoatomicDataProperties, Data, 0 );

#endif // end DATA_PHOTOATOMIC_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_PhotoatomicDataProperties.hpp
//---------------------------------------------------------------------------//
