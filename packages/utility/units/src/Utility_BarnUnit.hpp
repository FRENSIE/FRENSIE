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
#include <boost/units/system/cgs/area.hpp>
#include <boost/units/system/si/energy.hpp>
#include <boost/units/physical_dimensions/energy.hpp>
#include <boost/units/base_unit.hpp>
#include <boost/units/conversion.hpp>
#include <boost/units/make_scaled_unit.hpp>
#include <boost/units/io.hpp>

namespace Utility{

typedef boost::units::make_scaled_unit<boost::units::cgs::area, boost::units::scale<10,boost::units::static_rational<24> > > >::type Barn;

BOOST_UNITS_STATIC_CONSTANT( b, Barn );

} // end Utility namespace

namespace boost{

namespace units{

std::string name_string( const Utility::Barn& )
{
  return "Barn";
}

std::string symbol_string( const cgs::force& )
{
  return "b";
}

} // end units namespace

} // end boost namespace

#endif // end UTILITY_BARN_UNIT_HPP

//---------------------------------------------------------------------------//
// end Utility_BarnUnit.hpp
//---------------------------------------------------------------------------//
