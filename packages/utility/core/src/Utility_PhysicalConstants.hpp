//---------------------------------------------------------------------------//
//!
//! \file   Utility_PhysicalConstants.hpp
//! \author Alex Robinson
//! \brief  Decl. of class that stores a variety of physical constants w/units
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_PHYSICAL_CONSTANTS_HPP
#define UTILITY_PHYSICAL_CONSTANTS_HPP

// Boost Includes
#include <boost/units/quantity.hpp>
#include <boost/units/systems/cgs.hpp>
#include <boost/units/systems/cgs/velocity.hpp>
#include <boost/units/systems/cgs/time.hpp>
#include <boost/units/systems/cgs/length.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/systems/si/temperature.hpp>

// FRENSIE Includes
#include "Utility_RawPhysicalConstants.hpp"
#include "Utility_ElectronVoltUnit.hpp"
#include "Utility_AtomicMassUnit.hpp"
#include "Utility_UnitTraits.hpp"

namespace Utility{

//! The physical constants class
class PhysicalConstants : public RawPhysicalConstants
{
private:

  // The MeV-s unit
  typedef UnitTraits<Units::MegaElectronVolt>::template GetMultipliedUnitType<boost::units::cgs::time>::type MeVSecond;

  // The MeV/K unit
  typedef UnitTraits<Units::MegaElectronVolt>::template GetMultipliedUnitType<UnitTraits<boost::units::si::temperature>::InverseUnit>::type MeVPerK;

public:

  //! The speed of light (cm/s)
  static const boost::units::quantity<boost::units::cgs::velocity> speed_of_light_q;

  //! Planck's constant (MeV-s)
  static const boost::units::quantity<MeVSecond> planck_constant_q;

  //! Plank's constant by pi (MeV-s)
  static const boost::units::quantity<MeVSecond> h_bar_q;

  //! Rest mass energy of electron (MeV)
  static const boost::units::quantity<Units::MegaElectronVolt> electron_rest_mass_energy_q;

  //! Rest mass energy of neutron (MeV)
  static const boost::units::quantity<Units::MegaElectronVolt> neutron_rest_mass_energy_q;

  //! The rest mass of neutron (amu)
  static const boost::units::quantity<Units::AtomicMass> neutron_rest_mass_amu_q;

  //! The classical electron radius (cm)
  static const boost::units::quantity<boost::units::cgs::length> classical_electron_radius_q;

  //! The boltzmann constant (MeV/K)
  static const boost::units::quantity<MeVPerK> boltzmann_constant_q;
};

} // end Utility namespace

#endif // end UTILITY_PHYSICAL_CONSTANTS_HPP

//---------------------------------------------------------------------------//
// end Utility_PhysicalConstants.hpp
//---------------------------------------------------------------------------//
