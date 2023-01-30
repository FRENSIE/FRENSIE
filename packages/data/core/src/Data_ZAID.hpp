//---------------------------------------------------------------------------//
//!
//! \file   Data_ZAID.hpp
//! \author Alex Robinson
//! \brief  The ZAID class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ZAID_HPP
#define DATA_ZAID_HPP

// Std Lib Includes
#include <functional>

#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Data_AtomType.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_ToStringTraits.hpp"
#include "Utility_TypeTraits.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Data{

//! The ZAID class
class ZAID
{

public:

  //! Default constructor
  ZAID();

  //! String constructor
  ZAID( const std::string& zaid_string );

  //! C-string constructor
  ZAID( const char* zaid_string );

  //! Raw ZAID constructor
  ZAID( const unsigned raw_zaid );

  //! Component constructor
  ZAID( const unsigned atomic_number,
        const unsigned atomic_mass_number,
        const unsigned isomer_number );

  //! Elemental constructor
  ZAID( const AtomType atom_type );

  //! Copy constructor
  ZAID( const ZAID& that );

  //! Assignment operator
  ZAID& operator=( const ZAID& that );

  //! Destructor
  virtual ~ZAID()
  { /* ... */ }

  //! Equality operator
  bool operator==( const ZAID& that );

  //! Inequality operator
  bool operator!=( const ZAID& that );

  //! Less than operator
  bool operator<( const ZAID& that );

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

  //! Convert to a name (e.g. 1000 -> H, 1001 -> H1)
  std::string toName() const;

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

// Save the model to an archive
template<typename Archive>
void ZAID::save( Archive& ar, const unsigned version ) const
{
  unsigned raw_zaid = this->toRaw();
  
  ar & BOOST_SERIALIZATION_NVP( raw_zaid );
}

// Load the model from an archive
template<typename Archive>
void ZAID::load( Archive& ar, const unsigned version )
{
  unsigned raw_zaid;

  ar & BOOST_SERIALIZATION_NVP( raw_zaid );

  *this = ZAID( raw_zaid );
}

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

/*! Specialization of Utility::IsHashable for Data::ZAID
 * \ingroup type_traits
 */
template<>
struct IsHashable<Data::ZAID> : public std::true_type
{ /* ... */ };

} // end Utility namespace

namespace std{

//! Stream operator for printing Data::ZAID enums
inline std::ostream& operator<<( std::ostream& os, const Data::ZAID obj )
{
  Utility::toStream( os, obj );

  return os;
}

//! Specialization of std::hash for Data::ZAID
template<>
struct hash<Data::ZAID> : public hash<unsigned>
{ /* ... */ };

} // end std namespace

BOOST_SERIALIZATION_CLASS_VERSION( ZAID, Data, 0 );

EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Data, ZAID );

#endif // end DATA_ZAID_HPP

//---------------------------------------------------------------------------//
// end Data_ZAID.hpp
//---------------------------------------------------------------------------//
