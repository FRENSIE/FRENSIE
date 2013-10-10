//---------------------------------------------------------------------------//
//!
//! \file   UndefinedTraits.hpp
//! \author Alex Robinson
//! \brief  A class that causes a compile time error in default trait/policy
//!         structs.
//!
//---------------------------------------------------------------------------//

#ifndef UNDEFINED_TRAITS_HPP
#define UNDEFINED_TRAITS_HPP

namespace FACEMC{

namespace Traits{

/*! \brief A struct designed to give a compile time error
 * \ingroup hdf5_type_traits
 * \ingroup compare_policy
 * \ingroup tuple_traits
 */
template<typename T>
struct UndefinedTraits
{
  //! This function should not compile if there is any attempt to instantiate!
  static inline T notDefined() { return T::this_type_is_missing_a_specialization(); }
};

} // end Traits namespace

} // end FACEMC namespace

#endif // end UNDEFINED_TRAITS_HPP

//---------------------------------------------------------------------------//
// end UndefinedTraits.hpp
//---------------------------------------------------------------------------//
