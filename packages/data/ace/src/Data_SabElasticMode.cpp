//---------------------------------------------------------------------------//
//!
//! \file   Data_SabElasticMode.cpp
//! \author Alex Robinson
//! \brief  The S(a,b) elastic scattering mode enumeration helpers def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_SabElasticMode.hpp"

namespace Data{

// Convert an unsigned int to a SabElasticMode
SabElasticMode convertUnsignedToSabElasticMode( const unsigned mode )
{
  switch( mode )
  {
  case 4u: return COHERENT_ELASTIC_MODE;
  default: return INCOHERENT_ELASTIC_MODE;
  }
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_SabElasticMode.cpp
//---------------------------------------------------------------------------//
