//---------------------------------------------------------------------------//
//!
//! \file   Data_SabInelasticMode.hpp
//! \author Alex Robinson
//! \brief  S(a,b) inelastic mode enumeration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_SAB_INELASTIC_MODE_HPP
#define Data_SAB_INELASTIC_MODE_HPP

namespace Data{

//! The S(a,b) inelastic mode enumeration
enum SabInelasticMode
{
  EQUIPROBABLE_COSINE_INELASTIC_MODE = 3
};

//! Convert an unsigned int to a SabInelasticMode
SabInelasticMode convertUnsignedToSabInelasticMode( const unsigned mode );

} // end Data namespace

#endif // end DATA_SAB_INELASTIC_MODE_HPP

//---------------------------------------------------------------------------//
// end Data_SabInelasticMode.hpp
//---------------------------------------------------------------------------//
