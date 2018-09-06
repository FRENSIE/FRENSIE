//---------------------------------------------------------------------------//
//!
//! \file   Utility_OStreamableObject_def.hpp
//! \author Alex Robinson
//! \brief  Output streamable object base class definition
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_OSTREAMABLE_OBJECT_DEF_HPP
#define UTILITY_OSTREAMABLE_OBJECT_DEF_HPP

// Std Lib Includes
#include <tuple>

namespace Utility{

namespace Details{

//! Helper class for placing data in an output stream
template<size_t I, typename TupleType, typename Enabled = void>
struct DataOStreamHelper
{
  static inline void placeElementInOStream( std::ostream& os,
                                            const TupleType& data )
  {
    Utility::toStream( os, std::get<I>( data ) );
    os << Utility::next_container_element_char << " ";

    DataOStreamHelper<I+1,TupleType>::placeElementInOStream( os, data );
  }
};

//! Specialization of DataOStreamHelper for parameter packs of I = TupleSize-1
template<size_t I, typename TupleType>
struct DataOStreamHelper<I,TupleType,typename std::enable_if<I==std::tuple_size<TupleType>::value-1>::type>
{
  static inline void placeElementInOStream( std::ostream& os,
                                            const TupleType& data )
  { Utility::toStream( os, std::get<I>( data ) ); }
};

//! Specialization of DataOStreamHelper for parameter packs of I = TupleSize
template<size_t I, typename TupleType>
struct DataOStreamHelper<I,TupleType,typename std::enable_if<I==std::tuple_size<TupleType>::value>::type>
{
  static inline void placeElementInOStream( std::ostream&, const TupleType& )
  { /* ... */ }
};
  
} // end Details namespace

// Add data to the stream
template<typename... Types>
void OStreamableObject::toStreamImpl( std::ostream& os,
                                      const Types&... data ) const
{
  os << Utility::container_start_char;
  
  Details::DataOStreamHelper<0,decltype(std::tie(data...))>::placeElementInOStream( os, std::tie(data...) );

  os << Utility::container_end_char;
}
  
} // end Utility namespace

#endif // end UTILITY_OSTREAMABLE_OBJECT_DEF_HPP

//---------------------------------------------------------------------------//
// end Utility_OStreamableObject_def.hpp
//---------------------------------------------------------------------------//
