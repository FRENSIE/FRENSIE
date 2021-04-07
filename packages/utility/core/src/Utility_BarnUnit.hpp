//---------------------------------------------------------------------------//
//!
//! \file   Utility_BarnUnit.hpp
//! \author Alex Robinson
//! \brief  The barn unit declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_BARN_UNIT_HPP
#define UTILITY_BARN_UNIT_HPP

// Boost Includes
#include <boost/units/systems/cgs/area.hpp>
#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/io.hpp>

namespace Utility{

namespace Units{

typedef boost::units::make_scaled_unit<boost::units::cgs::area, boost::units::scale<10,boost::units::static_rational<-24> > >::type Barn;

BOOST_UNITS_STATIC_CONSTANT( barn, Barn );
BOOST_UNITS_STATIC_CONSTANT( barns, Barn );

} // end Units namespace

} // end Utility namespace

namespace boost{

namespace units{

inline std::string name_string( const Utility::Units::Barn& )
{
  return "Barn";
}

inline std::string symbol_string( const Utility::Units::Barn& )
{
  return "b";
}

} // end units namespace

} // end boost namespace

#endif // end UTILITY_BARN_UNIT_HPP

//---------------------------------------------------------------------------//
// end Utility_BarnUnit.hpp
//---------------------------------------------------------------------------//
