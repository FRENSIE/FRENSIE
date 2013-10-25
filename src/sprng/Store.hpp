//---------------------------------------------------------------------------//
//!
//! \file    Store.hpp
//! \author  ?
//! \brief   Declaration of array storage functions.
//! \details Numbers are stored with the most significant bit first (left 
//!          most). This file originally appeared in the sprng4 library. It has
//!          been modified by Alex Robinson (aprobinson@wisc.edu) to better 
//!          support the needs of FACEMC.
//!
//---------------------------------------------------------------------------//

#ifndef STORE_HPP
#define STORE_HPP

// Std Lib Includes
#include <string>
#include <vector>

namespace sprng{

// Store an integer value in a character buffer
template<typename OrdinalType>
void store_value( const OrdinalType l, std::string &c );

// Store an array of integer values in a character buffer
template<typename OrdinalType>
void store_array( const std::vector<OrdinalType> &l, std::string &c );

// Load an integer value from a character buffer
template<typename OrdinalType>
void load_value( const std::string &c, OrdinalType &l );

// Load an array of integer values from a character buffer
template<typename OrdinalType>
void load_array( const std::string &c, int n, std::vector<OrdinalType> &l );

} // end namespace sprng

//---------------------------------------------------------------------------//
// Definition includes.
//---------------------------------------------------------------------------//

#include "Store_def.hpp"

//---------------------------------------------------------------------------//

#endif // end STORE_HPP

//---------------------------------------------------------------------------//
// end Store.hpp
//---------------------------------------------------------------------------//
