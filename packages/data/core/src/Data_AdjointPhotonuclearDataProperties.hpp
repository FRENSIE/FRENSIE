//---------------------------------------------------------------------------//
//!
//! \file   Data_AdjointPhotonuclearDataProperties.hpp
//! \author Alex Robinson
//! \brief  The adjoint nuclear data properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ADJOINT_PHOTONUCLEAR_DATA_PROPERTIES_HPP
#define DATA_ADJOINT_PHOTONUCLEAR_DATA_PROPERTIES_HPP

// Boost Includes
#include <boost/filesystem/path.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Data{

//! The adjoint nuclear data properties base class
class AdjointPhotonuclearDataProperties
{

public:

  enum FileType{
    Native_FILE
  };

  //! Default constructor
  AdjointPhotonuclearDataProperties();

  //! Destructor
  virtual ~AdjointPhotonuclearDataProperties()
  { /* ... */ }

  //! Get the adjoint nuclear data evaluation temperature (MeV)
  virtual double evaluationTemperatureInMeV() const = 0;

  //! Get the adjoint nuclear data evaluation temperature (Kelvin)
  virtual double evaluationTemperatureInKelvin() const;

  //! Get the adjoint nuclear data file type
  virtual FileType fileType() const = 0;

  //! Get the adjoint nuclear data file path (relative to the data directory)
  virtual boost::filesystem::path filePath() const = 0;

  //! Get the adjoint nuclear data file start line
  virtual size_t fileStartLine() const = 0;

  //! Get the adjoint nuclear data file table name
  virtual std::string tableName() const = 0;

  //! Clone the properties
  virtual AdjointPhotonuclearDataProperties* clone() const = 0;

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
 * Data::AdjointPhotonuclearDataProperties::FileType
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<Data::AdjointPhotonuclearDataProperties::FileType>
{
  //! Convert a Data::AdjointPhotonuclearDataProperties::FileType to a string
  static std::string toString( const Data::AdjointPhotonuclearDataProperties::FileType type );

  //! Place the Data::AdjointPhotonuclearDataProperties::FileType in a stream
  static void toStream( std::ostream& os, const Data::AdjointPhotonuclearDataProperties::FileType type );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing Datea::AdjointPhotonuclearDataProperties::FileType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const Data::AdjointPhotonuclearDataProperties::FileType type )
{
  Utility::toStream( os, type );

  return os;
}
  
} // end std namespace

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( AdjointPhotonuclearDataProperties, Data );
BOOST_SERIALIZATION_CLASS_VERSION( AdjointPhotonuclearDataProperties, Data, 0 );


#endif // end DATA_ADJOINT_PHOTONUCLEAR_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_AdjointPhotonuclearDataProperties.hpp
//---------------------------------------------------------------------------//
