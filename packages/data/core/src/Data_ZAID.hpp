//---------------------------------------------------------------------------//
//!
//! \file   Data_ZAID.hpp
//! \author Alex Robinson
//! \brief  The ZAID class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ZAID_HPP
#define DATA_ZAID_HPP

// FRENSIE Includes
#include "Data_AtomType.hpp"
#include "Data_ExplicitTemplateInstantiationMacros.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Data{

//! The ZAID class
class ZAID
{

public:

  //! Default constructor
  ZAID();

  //! Raw ZAID constructor
  explicit ZAID( const unsigned raw_zaid );

  //! Component constructor
  ZAID( const unsigned atomic_number,
        const unsigned atomic_mass_number,
        const unsigned isomer_number );

  //! Copy constructor
  ZAID( const ZAID& that );

  //! Assignment operator
  ZAID& operator=( const ZAID& that );

  //! Destructor
  ~ZAID()
  { /* ... */ }

  //! Equality operator
  bool operator==( const ZAID& that );

  //! Inequality operator
  bool operator!=( const ZAID& that );

  //! Return the AtomType
  AtomType atom() const;
  
  //! Return the atomic number
  unsigned atomicNumber() const;

  //! Return the atomic mass number
  unsigned atomicMassNumber() const;

  //! Return the isomer number
  unsigned isomerNumber() const;

  //! Return the raw zaid
  unsigned toRaw() const;

  //! Implicit conversion to raw zaid
  operator unsigned() const;

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

  // The atom type
  AtomType d_atom_type;

  // The atomic mass number
  unsigned d_atomic_mass_number;

  // The isomer number
  unsigned d_isomer_number;
};
  
} // end Data namespace

namespace Utility{

/*! Specialization of Utility::ToStringTraits for Data::ZAID
 * \ingroup to_string_traits
 */
template<>
struct ToStringTraits<Data::ZAID>
{
  //! Convert a Data::ZAID to a string
  static std::string toString( const Data::ZAID obj );

  //! Place the Data::ZAID in a stream
  static void toStream( std::ostream& os, const Data::ZAID obj );
};
  
} // end Utility namespace

namespace std{

//! Stream operator for printing Data::ZAID enums
inline std::ostream& operator<<( std::ostream& os, const Data::ZAID obj )
{
  Utility::toStream( os, obj );
  
  return os;
}

} // end std namespace

BOOST_SERIALIZATION_CLASS_VERSION( ZAID, Data, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( ZAID, Data );

EXTERN_EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ZAID );

#endif // end DATA_ZAID_HPP

//---------------------------------------------------------------------------//
// end Data_ZAID.hpp
//---------------------------------------------------------------------------//
