//---------------------------------------------------------------------------//
//!
//! \file   Data_NuclearDataProperties.hpp
//! \author Alex Robinson
//! \brief  The nuclear data properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_NUCLEAR_DATA_PROPERTIES_HPP
#define DATA_NUCLEAR_DATA_PROPERTIES_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/filesystem/path.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Data{

//! The nuclear data properties base class
class NuclearDataProperties
{

public:

  enum FileType{
    ACE_FILE
  };

  //! Default constructor
  NuclearDataProperties();

  //! Destructor
  virtual ~NuclearDataProperties()
  { /* ... */ }

  //! Get the nuclear data evaluation temperature (MeV)
  virtual double evaluationTemperatureInMeV() const = 0;

  //! Get the nuclear data evaluation temperature (Kelvin)
  virtual double evaluationTemperatureInKelvin() const;

  //! Get the nuclear data file type
  virtual FileType fileType() const = 0;

  //! Get the nuclear data file path (relative to the data directory)
  virtual boost::filesystem::path filePath() const = 0;

  //! Get the nuclear data file start line
  virtual size_t fileStartLine() const = 0;

  //! Get the nuclear data file table name
  virtual std::string tableName() const = 0;

  //! Clone the properties
  virtual NuclearDataProperties* clone() const = 0;

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
 * Data::NuclearDataProperties::FileType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<Data::NuclearDataProperties::FileType>
{
  //! Convert a Data::NuclearDataProperties::FileType to a string
  static std::string toString( const Data::NuclearDataProperties::FileType type );

  //! Place the Data::NuclearDataProperties::FileType in a stream
  static void toStream( std::ostream& os, const Data::NuclearDataProperties::FileType type );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing Datea::NuclearDataProperties::FileType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const Data::NuclearDataProperties::FileType type )
{
  Utility::toStream( os, type );

  return os;
}
  
} // end std namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( NuclearDataProperties, Data );
BOOST_SERIALIZATION_CLASS_VERSION( NuclearDataProperties, Data, 0 );

#endif // end DATA_NUCLEAR_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_NuclearDataProperties.hpp
//---------------------------------------------------------------------------//
