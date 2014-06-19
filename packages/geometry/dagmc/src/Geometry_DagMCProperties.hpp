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

  //! Set the termination cell property name
  static void setTerminationCellPropertyName( const std::string& name );

  //! Get the termination cell property name
  static const std::string& getTerminationCellPropertyName();

  //! Set the material property name
  static void setMaterialPropertyName( const std::string& name );

  //! Get the material property name
  static const std::string& getMaterialPropertyName();

  //! Set the density property name
  static void setDensityPropertyName( const std::string& name );

  //! Get the density property name
  static const std::string& getDensityPropertyName();

  //! Set the estimator property name
  static void setEstimatorPropertyName( const std::string& name );

  //! Get the estimator property name
  static const std::string& getEstimatorPropertyName();

  //! Extract estimator property values
  static void extractEstimatorPropertyValues( const std::string& prop_value,
					      unsigned& estimator_id,
					      std::string& estimator_type,
					      std::string& particle_type );

  //! Check if the cell estimator type is valid
  static bool isCellEstimatorTypeValid( const std::string& estimator_type );

  //! Check if the surface estimator type is valid
  static bool isSurfaceEstimatorTypeValid( const std::string& estimator_type );

  //! Check if the particle type is valid
  static bool isParticleTypeValid( const std::string& particle_type );

  //! Get all of the properties
  static void getProperties( std::vector<std::string>& properties );

private:

  //! The termination cell property name
  static std::string termination_cell_property;

  //! The material property name
  static std::string material_property;

  //! The density property name
  static std::string density_property;

  //! The estimator property name
  static std::string estimator_property;
};

} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCProperties.hpp
//---------------------------------------------------------------------------//
