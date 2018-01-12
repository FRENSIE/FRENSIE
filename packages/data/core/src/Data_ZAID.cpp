//---------------------------------------------------------------------------//
//!
//! \file   Data_ZAID.cpp
//! \author Alex Robinson
//! \brief  The ZAID class definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "Data_ZAID.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_FromStringTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Default constructor
ZAID::ZAID()
{ /* ... */ }

// String constructor
ZAID( const std::string& zaid_string )
  : ZAID( Utility::fromString<unsigned>( zaid_string ) )
{ /* ... */ }

// C-string constructor
ZAID( const char* zaid_string )
  : ZAID( Utility::fromString<unsigned>( zaid_string ) )
{ /* ... */ }

// Raw ZAID constructor
ZAID::ZAID( const unsigned raw_zaid )
  : d_atom_type( Data::convertAtomicNumberToAtomTypeEnum( raw_zaid/1000u ) ),
    d_atomic_mass_number( raw_zaid%1000u ),
    d_isomer_number( 0 )
{
  // Check if there is an isomer number
  if( d_atomic_mass_number > 800 )
  {
    d_atomic_mass_number %= 800;

    d_isomer_number = 2;
  }
  else if( d_atomic_mass_number > 400 )
  {
    d_atomic_mass_number %= 400;

    d_isomer_number = 1;
  }
}

// Component constructor
ZAID::ZAID( const unsigned atomic_number,
            const unsigned atomic_mass_number,
            const unsigned isomer_number )
  : d_atom_type( Data::convertAtomicNumberToAtomTypeEnum( atomic_number ) ),
    d_atomic_mass_number( atomic_mass_number ),
    d_isomer_number( isomer_number )
{
  TEST_FOR_EXCEPTION( atomic_number > 110,
                      std::runtime_error,
                      "The atomic number is too large!" );
  
  TEST_FOR_EXCEPTION( atomic_mass_number > 1000,
                      std::runtime_error,
                      "The atomic mass number is too large!" );
  
  if( atomic_mass_number < 200 )
  {
    TEST_FOR_EXCEPTION( isomer_number > 2,
                        std::runtime_error,
                        "Only the first two metastable states are currently "
                        "supported!" );
  }
  else
  {
    TEST_FOR_EXCEPTION( isomer_number > 1,
                        std::runtime_error,
                        "Only the first metastable state is currently "
                        "supported!" );
  }
}

// Copy constructor
ZAID::ZAID( const ZAID& that )
  : d_atom_type( that.d_atom_type ),
    d_atomic_mass_number( that.d_atomic_mass_number ),
    d_isomer_number( that.d_isomer_number )
{ /* ... */ }

// Assignment operator
ZAID& ZAID::operator=( const ZAID& that )
{
  if( this != &that )
  {
    d_atom_type = that.d_atom_type;
    d_atomic_mass_number = that.d_atomic_mass_number;
    d_isomer_number = that.d_isomer_number;
  }

  return *this;
}

// Equality operator
bool ZAID::operator==( const ZAID& that )
{
  return d_atom_type == that.d_atom_type &&
    d_atomic_mass_number == that.d_atomic_mass_number &&
    d_isomer_number == that.d_isomer_number;
}

// Inequality operator
bool ZAID::operator!=( const ZAID& that )
{
  return d_atom_type != that.d_atom_type ||
    d_atomic_mass_number != that.d_atomic_mass_number ||
    d_isomer_number != that.d_isomer_number;
}

// Less than operator
bool ZAID::operator<( const ZAID& that )
{
  return this->toRaw() < that.toRaw();
}

// Return the AtomType
AtomType ZAID::atom() const
{
  return d_atom_type;
}
  
// Return the atomic number
unsigned ZAID::atomicNumber() const
{
  return d_atom_type;
}

// Return the atomic mass number
unsigned ZAID::atomicMassNumber() const
{
  return d_atomic_mass_number;
}

// Return the isomer number
unsigned ZAID::isomerNumber() const
{
  return d_isomer_number;
}

// Return the raw zaid
unsigned ZAID::toRaw() const
{
  return d_atom_type*1000u + d_atomic_mass_number + 400*d_isomer_number;
}

// Implicit conversion to raw zaid
ZAID::operator unsigned() const
{
  return this->toRaw();
}
  
// Save the model to an archive
template<typename Archive>
void ZAID::save( Archive& ar, const unsigned version ) const
{
  const unsigned raw_zaid = this->toRaw();
  
  ar & boost::serialization::make_nvp( "zaid", raw_zaid );
}

// Load the model from an archive
template<typename Archive>
void ZAID::load( Archive& ar, const unsigned version )
{
  unsigned raw_zaid;

  ar & boost::serialization::make_nvp( "zaid", raw_zaid );

  *this = ZAID( raw_zaid );
}

EXPLICIT_DATA_CLASS_SAVE_LOAD_INST( ZAID );
  
} // end Data namespace

namespace Utility{

// Convert a Data::ZAID to a string
std::string ToStringTraits<Data::ZAID>::toString( const Data::ZAID obj )
{
  return Utility::toString<unsigned>( obj );
}

// Place the Data::ZAID in a stream
void ToStringTraits<Data::ZAID>::toStream( std::ostream& os,
                                           const Data::ZAID obj )
{
  return Utility::toStream<unsigned>( os, obj );
}

} // end Utility namespace

BOOST_SERIALIZATION_CLASS_EXPORT_IMPLEMENT( ZAID, Data );

//---------------------------------------------------------------------------//
// end Data_ZAID.cpp
//---------------------------------------------------------------------------//
