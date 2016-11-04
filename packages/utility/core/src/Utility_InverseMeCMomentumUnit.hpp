//---------------------------------------------------------------------------//
//!
//! \file   Utility_InverseMeCMomentumUnit.hpp
//! \author Alex Robinson
//! \brief  The inverse me*c momentum unit
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_INVERSE_MEC_MOMENTUM_UNIT_HPP
#define UTILITY_INVERSE_MEC_MOMENTUM_UNIT_HPP

// FRENSIE Includes
#include "Utility_MeCMomentumUnit.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

namespace Units{

//! The inverse me*c momentum unit
typedef UnitTraits<MeCMomentum>::InverseUnit InverseMeCMomentum;

BOOST_UNITS_STATIC_CONSTANT( inverse_mec_momentum, InverseMeCMomentum );
BOOST_UNITS_STATIC_CONSTANT( inverse_mec, InverseMeCMomentum );

} // end Units namespace

} // end Utility namespace

#endif // end UTILITY_INVERSE_MEC_MOMENTUM_UNIT_HPP

//---------------------------------------------------------------------------//
// end Utility_InverseMeCMomentumUnit.hpp
//---------------------------------------------------------------------------//
