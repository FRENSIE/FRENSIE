//---------------------------------------------------------------------------//
//!
//! \file   Data_ACETableName.hpp
//! \author Alex Robinson
//! \brief  The ACE table name class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ACE_TABLE_NAME_HPP
#define DATA_ACE_TABLE_NAME_HPP

// FRENSIE Includes
#include "Data_ZAID.hpp"
#include "Data_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Data{

//! The ACE table name class
class ACETableName
{

public:

  //! Default constructor
  ACETableName();

  //! C-string constructor
  ACETableName( const char* raw_ace_table_name );

  //! String constructor
  ACETableName( const std::string& raw_ace_table_name );

  //! Component constructor
  ACETableName( const Data::ZAID& zaid,
                const size_t table_version,
                const char table_type_key );

  //! Copy constructor
  ACETableName( const ACETableName& that );

  //! Assignment operator
  ACETableName& operator=( const ACETableName& that );

  //! Destructor
  ~ACETableName()
  { /* ... */ }

  //! Equality operator
  bool operator==( const ACETableName& that ) const;

  //! Inequality operator
  bool operator!=( const ACETableName& that ) const;

  //! Return the zaid
  const Data::ZAID& zaid() const;

  //! Return the table version
  size_t version() const;

  //! Return the type key
  char typeKey() const;

  //! Return the raw table name
  const std::string& toRaw() const;

  //! Implicit conversion to std::string
  operator std::string() const;

private:

  // Save the model to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the model from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The raw table name
  std::string d_raw_table_name;

  // The table name zaid
  Data::ZAID d_table_name_zaid;

  // The table name version
  size_t d_table_name_version;

  // The table name type key
  char d_table_name_type_key;
};
  
} // end Data namespace

namespace Utility{

/*! Specialization of Utility::ToStringTraits for Data::ACETableName
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<Data::ACETableName>
{
  //! Convert a Data::ACETableName to a string
  static std::string toString( const Data::ACETableName obj );

  //! Place the Data::ACETableName in a stream
  static void toStream( std::ostream& os, const Data::ACETableName obj );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing Data::ACETableName enums
inline std::ostream& operator<<( std::ostream& os, const Data::ACETableName obj )
{
  Utility::toStream( os, obj );
  
  return os;
}

} // end std namespace

BOOST_SERIALIZATION_CLASS_VERSION( ACETableName, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ACETableName, Data );

EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ACETableName );

#endif // end DATA_ACE_TABLE_NAME_HPP

//---------------------------------------------------------------------------//
// end Data_ACETableName.hpp
//---------------------------------------------------------------------------//
