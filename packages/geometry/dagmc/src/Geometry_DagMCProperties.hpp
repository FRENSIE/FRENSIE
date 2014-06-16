//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCProperties.hpp
//! \author Alex Robinson
//! \brief  DagMC property keywords class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_PROPERTIES_HPP
#define GEOMETRY_DAGMC_PROPERTIES_HPP

// Std Lib Includes
#include <string>
#include <vector>

namespace Geometry{

//! The DagMC property class
class DagMCProperties
{

public:

  //! The termination cell property name
  static const std::string termination_cell_property;

  //! The material property name
  static const std::string material_property;

  //! The density property name
  static const std::string density_property;

  //! The estimator property name
  static const std::string estimator_property;

  //! The cell track length flux property name
  static const std::string cell_track_length_flux_property;

  //! The cell collision flux property name
  static const std::string cell_collision_flux_property;
  
  //! The cell pulse height property name
  static const std::string cell_pulse_height_property;

  //! The surface flux property name
  static const std::string surface_flux_property;

  //! The surface current property name
  static const std::string surface_current_property;

  //! Get all of the properties
  static void getProperties( std::vector<std::string>& properties );
};

} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCProperties.hpp
//---------------------------------------------------------------------------//
