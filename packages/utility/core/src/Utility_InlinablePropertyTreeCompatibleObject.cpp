//---------------------------------------------------------------------------//
//!
//! \file   Utility_InlinablePropertyTreeCompatibleObject.cpp
//! \author Alex Robinson
//! \brief  Inlinable property tree compatible object base class definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

// FRENSIE Includes
#include "Utility_InlinablePropertyTreeCompatibleObject.hpp"

namespace Utility{

// Check if data can be inlined
bool InlinablePropertyTreeCompatibleObject::canDataBeInlined() const
{
  return false;
}

// Method for converting the type to a property tree
Utility::PropertyTree InlinablePropertyTreeCompatibleObject::toPropertyTree() const
{
  return this->toPropertyTree( this->isDataInlinedByDefault() );
}

// Extract data from the stream
/*! \details If the type cannot be verified an exception will be thrown.
 */
void InlinablePropertyTreeCompatibleObject::fromStream( std::istream& is,
                                                        const std::string& )
{
  // Extract the stream data
  VariantList stream_data;
  
  Utility::Variant type_data =
    this->extractStreamData( is, stream_data, this->getTypeName(true, true) );

  // Verify the type
  this->verifyType( type_data );

  // Process the extracted data
  this->fromStreamImpl( stream_data );

  // Check for unused stream data
  this->checkForUnusedStreamData( stream_data );
}

// Extract the data from a stream
Utility::Variant InlinablePropertyTreeCompatibleObject::extractStreamData(
                                                 std::istream& is,
                                                 VariantList& stream_data,
                                                 const std::string& type_name )
{
  try{
    Utility::fromStream( is, stream_data );
  }
  EXCEPTION_CATCH_RETHROW( Utility::StringConversionException,
                           "Could not extract the data from the stream!" );

  if( !stream_data.empty() )
  {
    Utility::Variant type_data = stream_data.front();

    stream_data.pop_front();

    return type_data;
  }
  else
  {
    THROW_EXCEPTION( Utility::StringConversionException,
                     "The " << type_name << " could not be constructed "
                     "because the type could not be verified!" );
  }
}

//! Check for unused stream data
void InlinablePropertyTreeCompatibleObject::checkForUnusedStreamData(
                                            const VariantList& obj_data ) const
{
  // Check if there is any superfluous data
  if( !obj_data.empty() )
  {
    FRENSIE_LOG_TAGGED_WARNING( this->getTypeName( true, false ),
                                "Superfluous data was encountered during "
                                "initialization from stream ("
                                << obj_data << ")!" );
  }
}

// Add the data to an inlined property tree
Utility::PropertyTree InlinablePropertyTreeCompatibleObject::toInlinedPropertyTreeImpl() const
{
  Utility::PropertyTree ptree;

  ptree.put_value( *this );

  return ptree;
}

// Extract froman inlined property tree
/*! \details The data in the property tree node must be inlined (i.e. 
 * node.size() == 0).
 */
void InlinablePropertyTreeCompatibleObject::fromInlinedPropertyTreeImpl(
                                            const Utility::PropertyTree& node )
{
  std::istringstream iss( node.data().toString() );

  try{
    this->fromStream( iss );
  }
  EXCEPTION_CATCH_RETHROW_AS( std::runtime_error,
                              Utility::PropertyTreeConversionException,
                              "Could not create the "
                              << this->getTypeName(true, true) << "!" );
}

// Extract the type name from an inlined property tree
std::string InlinablePropertyTreeCompatibleObject::getInlinedPropertyTreeTypeName(
                                            const Utility::PropertyTree& node )
{
  std::istringstream iss( node.data().toString() );

  VariantList stream_data;

  return InlinablePropertyTreeCompatibleObject::extractStreamData( iss, stream_data ).toString();
}
  
} // end Utility namespace

//---------------------------------------------------------------------------//
// end Utility_InlinablePropertyTreeCompatibleObject.cpp
//---------------------------------------------------------------------------//
