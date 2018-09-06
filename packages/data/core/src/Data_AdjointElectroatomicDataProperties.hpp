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
#include "Data_AtomType.hpp"
#include "Utility_AtomicMassUnit.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"
#include "Utility_ExceptionTestMacros.hpp"

namespace Data{

//! The electroatomic data properties base class
class AdjointElectroatomicDataProperties
{

public:

  /*! The file types
   *
   * When adding a new file type the toString and serialize methods must be
   * updated.
   */
  enum FileType{
    Native_EPR_FILE = 0
  };

  //! The atomic mass unit
  typedef Utility::Units::AtomicMass AtomicMassUnit;

  //! The atomic mass quantity
  typedef boost::units::quantity<AtomicMassUnit> AtomicWeight;

  //! Default constructor
  AdjointElectroatomicDataProperties();

  //! Destructor
  virtual ~AdjointElectroatomicDataProperties()
  { /* ... */ }

  //! Get the atom that the file specifies data for
  virtual AtomType atom() const = 0;

  //! Get the atomic number that the file specifies data for
  virtual unsigned atomicNumber() const
  { return this->atom(); }

  //! Get the atomic weight of the nuclide that the file specifies data for
  virtual AtomicWeight atomicWeight() const = 0;

  //! Get the electroatomic data file type
  virtual FileType fileType() const = 0;

  //! Get the electroatomic data file path (relative to the data directory)
  virtual boost::filesystem::path filePath() const = 0;

  //! Get the electroatomic data file start line
  virtual size_t fileStartLine() const = 0;

  //! Get the nuclear data file version
  virtual unsigned fileVersion() const = 0;

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

//! Stream operator for printing Data::AdjointElectroatomicDataProperties::FileType enums
inline std::ostream& operator<<( std::ostream& os,
                                 const Data::AdjointElectroatomicDataProperties::FileType type )
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
                Data::AdjointElectroatomicDataProperties::FileType& file_type,
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
      BOOST_SERIALIZATION_ENUM_CASE( Data::AdjointElectroatomicDataProperties::Native_EPR_FILE, int, file_type );
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

BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( AdjointElectroatomicDataProperties, Data );
BOOST_SERIALIZATION_CLASS_VERSION( AdjointElectroatomicDataProperties, Data, 0 );

#endif // end DATA_ADJOINT_ELECTROATOMIC_DATA_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Data_AdjointElectroatomicDataProperties.hpp
//---------------------------------------------------------------------------//
