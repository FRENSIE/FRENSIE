//---------------------------------------------------------------------------//
//!
//! \file   Utility_StandardSerializableObject_def.hpp
//! \author Alex Robinson
//! \brief  Standard serializable object base class template definitions
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_STANDARD_SERIALIZABLE_OBJECT_DEF_HPP
#define UTILITY_STANDARD_SERIALIZABLE_OBJECT_DEF_HPP

// Std Lib Includes
#include <sstream>

// Boost Includes
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

namespace Utility{

// Pack the data in the container into a string
template<typename DerivedType>
std::string StandardSerializableObject<DerivedType,false>::packDataInString() const
{
  std::ostringstream oss;

  boost::archive::binary_oarchive ar(oss);

  ar << *dynamic_cast<const DerivedType*>(this);

  return oss.str();
}

// Unpack the data from a string and store in the container
template<typename DerivedType>
void StandardSerializableObject<DerivedType,false>::unpackDataFromString(
					     const std::string& packed_string )
{
  std::istringstream iss( packed_string );

  boost::archive::binary_iarchive ar(iss);

  ar >> *dynamic_cast<DerivedType*>(this);
}

} // end Utility namespace

#endif // end UTILITY_STANDARD_SERIALIZABLE_OBJECT_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_StandardSerializableObject_def.hpp
//---------------------------------------------------------------------------//
