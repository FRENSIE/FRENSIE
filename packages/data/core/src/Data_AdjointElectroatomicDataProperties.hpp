//---------------------------------------------------------------------------//
//!
//! \file   Data_AdjointElectroatomicDataProperties.hpp
//! \author Alex Robinson
//! \brief  The adjoint electroatomic data properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ADJOINT_ELECTROATOMIC_DATA_PROPERTIES_HPP
#define DATA_ADJOINT_ELECTROATOMIC_DATA_PROPERTIES_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/filesystem/path.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Data{

//! The electroatomic data properties base class
class AdjointElectroatomicDataProperties
{

public:

  enum FileType{
    Native_EPR_FILE
  };

  //! Default constructor
  AdjointElectroatomicDataProperties();

  //! Destructor
  virtual ~AdjointElectroatomicDataProperties()
  { /* ... */ }

  //! Get the electroatomic data file type
  virtual FileType fileType() const = 0;

  //! Get the electroatomic data file path (relative to the data directory)
  virtual boost::filesystem::path filePath() const = 0;

  //! Get the electroatomic data file start line
  virtual size_t fileStartLine() const = 0;

  //! Get the electroatomic table name
  virtual std::string tableName() const = 0;

  //! Clone the properties
  virtual AdjointElectroatomicDataProperties* clone() const = 0;

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
 * Data::AdjointElectroatomicDataProperties::FileType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<Data::AdjointElectroatomicDataProperties::FileType>
{
  //! Convert a Data::AdjointElectroatomicDataProperties::FileType to a string
  static std::string toString( const Data::AdjointElectroatomicDataProperties::FileType type );

  //! Place the Data::AdjointElectroatomicDataProperties::FileType in a stream
  static void toStream( std::ostream& os, const Data::AdjointElectroatomicDataProperties::FileType type );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing Datea::AdjointElectroatomicDataProperties::FileType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const Data::AdjointElectroatomicDataProperties::FileType type )
{
  Utility::toStream( os, type );

  return os;
}
  
} // end std namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( AdjointElectroatomicDataProperties, Data );
BOOST_SERIALIZATION_CLASS_VERSION( AdjointElectroatomicDataProperties, Data, 0 );

#endif // end DATA_ADJOINT_ELECTROATOMIC_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_AdjointElectroatomicDataProperties.hpp
//---------------------------------------------------------------------------//
