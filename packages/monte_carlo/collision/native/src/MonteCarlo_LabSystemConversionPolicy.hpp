//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_LabSystemConversionPolicy
//! \author Alex Robinson
//! \brief  Policies for converting scattering angle and energy to lab system
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_LAB_SYSTEM_CONVERSION_POLICY_HPP
#define MONTE_CARLO_LAB_SYSTEM_CONVERSION_POLICY_HPP

// Std Lib Includes
#include <math.h>

namespace MonteCarlo {

//! Policy for converting from the CM system to the Lab system 
struct CMSystemConversionPolicy
{
  //! Convert the outgoing CM energy to the outgoing Lab energy
  inline static double convertToLabEnergy( 
		                      const double incident_energy,
				      const double outgoing_sys_energy,
		                      const double sys_scattering_angle_cosine,
				      const double atomic_weight_ratio )
  {
    double a_plus_1 = atomic_weight_ratio + 1.0;
  
    return outgoing_sys_energy + (incident_energy + 
				 2.0*sys_scattering_angle_cosine*a_plus_1*
				 sqrt(incident_energy*outgoing_sys_energy))/
				 (a_plus_1*a_plus_1);
  }

  //! Convert the CM scattering angle cosine to the outgoing lab angle cosine
  inline static double convertToLabAngleCosine( 
			              const double incident_energy,
				      const double outgoing_sys_energy,
				      const double outgoing_lab_energy,
			              const double sys_scattering_angle_cosine,
				      const double atomic_weight_ratio )
  {
    return sys_scattering_angle_cosine * 
      sqrt(outgoing_sys_energy/outgoing_lab_energy) +
      sqrt(incident_energy/outgoing_lab_energy)/(atomic_weight_ratio + 1.0);

  }
};

//! Policy for converting from the Lab system to the Lab system (dummy)
struct LabSystemConversionPolicy
{
  //! Return the Lab energy (dummy function)
  inline static double convertToLabEnergy(
				      const double incident_energy,
				      const double outgoing_sys_energy,
		                      const double sys_scattering_angle_cosine,
				      const double atomic_weight_ratio )
  {
    return outgoing_sys_energy;
  }

  //! Return the Lab scattering angle cosine
  inline static double convertToLabAngleCosine(
				      const double incident_energy,
				      const double outgoing_sys_energy,
				      const double outgoing_lab_energy,
			              const double sys_scattering_angle_cosine,
				      const double atomic_weight_ratio )
  {
    return sys_scattering_angle_cosine;
  }
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_LAB_SYSTEM_CONVERSION_POLICY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_LabSystemConversionPolicy.hpp
//---------------------------------------------------------------------------//
