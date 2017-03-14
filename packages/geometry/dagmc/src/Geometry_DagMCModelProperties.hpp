//---------------------------------------------------------------------------//
//!
//! \file   Geometry_DagMCModelProperties.hpp
//! \author Alex Robinson
//! \brief  DagMC model properties class declaration
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_DAGMC_MODEL_PROPERTIES_HPP
#define GEOMETRY_DAGMC_MODEL_PROPERTIES_HPP

// Std Lib Includes
#include <string>

namespace Geometry{

//! The DagMC model properties
class DagMCModelProperties
{

public:

  //! Constructor
  DagMCModelProperties( const std::string& filename );

  //! Destructor
  ~DagMCModelProperties()
  { /* ... */ }

  //! Get the model file name
  const std::string& getModelFileName() const;

  //! Set the face tolerance for the model
  void setFacetTolerance( const double facet_tol );
  
  //! Get the facet tolerance for the model
  double getFacetTolerance() const;

  //! Check if fast id lookup is used with the model
  bool isFastIdLookupUsed() const;

  //! Use fast id lookup with the model
  void useFastIdLookup();

  //! Use standard id lookup with the model
  void useStandardIdLookup();

  //! Set the termination cell property name
  void setTerminationCellPropertyName( const std::string& name );

  //! Get the termination cell property name
  const std::string& getTerminationCellPropertyName() const;

  //! Set the reflecting surface property name
  void setReflectingSurfacePropertyName( const std::string& name );

  //! Get the reflecting surface property name
  const std::string& getReflectingSurfacePropertyName() const;

  //! Set the material property name
  void setMaterialPropertyName( const std::string& name );

  //! Get the material property name
  const std::string& getMaterialPropertyName() const;

  //! Set the density property name
  void setDensityPropertyName( const std::string& name );

  //! Get the density property name
  const std::string& getDensityPropertyName() const;

  //! Set the estimator property name
  void setEstimatorPropertyName( const std::string& name );

  //! Get the estimator property name
  const std::string& getEstimatorPropertyName() const;

  //! Get all of the properties
  void getPropertyNames( std::vector<std::string>& properties ) const;

  //! Set the surface current name
  void setSurfaceCurrentName( const std::string& name );

  //! Get the surface current name
  const std::string& getSurfaceCurrentName() const;

  //! Set the surface flux name
  void setSurfaceFluxName( const std::string& name );

  //! Get the surface flux name
  const std::string& getSurfaceFluxName() const;

  //! Set the cell pulse height name
  void setCellPulseHeightName( const std::string& name );

  //! Get the cell pulse height name
  const std::string& getCellPulseHeightName() const;

  //! Set the cell track-length flux name
  void setCellTrackLengthFluxName( const std::string& name );

  //! Get the cell pulse height name
  const std::string& getCellTrackLengthFluxName() const;

  //! Set the cell collision flux name
  void setCellCollisionFluxName( const std::string& name );

  //! Get the cell collision flux name
  const std::string& getCellCollisionFluxName() const;

  //! Check if the cell estimator type is valid
  bool isCellEstimatorTypeValid( const std::string& estimator_type ) const;

  //! Check if the surface estimator type is valid
  bool isSurfaceEstimatorTypeValid( const std::string& estimator_type ) const;

  //! Check if the estimator type is valid
  bool isEstimatorTypeValid( const std::string& estimator_type ) const;

  //! Check if the particle type is valid
  bool isParticleTypeValid( const std::string& particle_type ) const;

private:

  // The model file name
  std::string d_file_name;

  // The facet tolerance
  double d_facet_tolerance;

  // The fast id lookup flag
  bool d_fast_id_lookup;

  // The termination cell property name
  std::string d_termination_cell_property;

  // The reflecting surface property name
  std::string d_reflecting_surface_property;

  // The material property name
  std::string d_material_property;

  // The density property name
  std::string d_density_property;

  // The estimator property name
  std::string d_estimator_property;

  // The surface current name
  std::string d_surface_current_name;

  // The surface flux name
  std::string d_surface_flux_name;

  // The cell pulse height name
  std::string d_cell_pulse_height_name;

  // The cell track-length flux name
  std::string d_cell_track_length_flux_name;

  // The cell collision flux name
  std::string d_cell_collision_flux_name;
};
  
  
} // end Geometry namespace

#endif // end GEOMETRY_DAGMC_MODEL_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCModelProperties.hpp
//---------------------------------------------------------------------------//

