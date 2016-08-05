//---------------------------------------------------------------------------//
//!
//! \file   Data_SabElasticMode.hpp
//! \author Alex Robinson
//! \brief  The S(a,b) elastic scattering mode enumeration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_SAB_ELASTIC_MODE_HPP
#define DATA_SAB_ELASTIC_MODE_HPP

namespace Data{

//! The S(a,b) elastic scattering mode enumeration
enum SabElasticMode
{
  INCOHERENT_ELASTIC_MODE = 0,
  COHERENT_ELASTIC_MODE = 4
};

//! Convert an unsigned int to a SabElasticMode
SabElasticMode convertUnsignedToSabElasticMode( const unsigned mode );

} // end Data namespace

#endif // end DATA_SAB_ELASTIC_MODE_HPP

//---------------------------------------------------------------------------//
// end Data_SabElasticMode.hpp
//---------------------------------------------------------------------------//
