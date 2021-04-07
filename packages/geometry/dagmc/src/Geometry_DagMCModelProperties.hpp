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
#include <vector>

// Boost Includes
#include <boost/filesystem.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "Geometry_ParticleType.hpp"
#include "Geometry_EstimatorType.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace Geometry{

//! The DagMC model properties
class DagMCModelProperties
{

public:

  //! Constructor
  DagMCModelProperties( const boost::filesystem::path& filename );

  //! Destructor
  ~DagMCModelProperties()
  { /* ... */ }

  //! Set the default file path
  static void setDefaultFilePath( const boost::filesystem::path& file_path );

  //! Get the default file path
  static std::string getDefaultFilePath();

  //! Get the model file name
  const std::string& getModelFileName() const;

  //! Get the model file path
  std::string getModelFilePath() const;

  //! Get the model file name with path
  std::string getModelFileNameWithPath() const;

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

  //! Get the cell track-length flux name
  const std::string& getCellTrackLengthFluxName() const;

  //! Set the cell collision flux name
  void setCellCollisionFluxName( const std::string& name );

  //! Get the cell collision flux name
  const std::string& getCellCollisionFluxName() const;

  //! Check if the cell estimator name is valid
  bool isCellEstimatorNameValid( const std::string& estimator_name ) const;

  //! Check if the surface estimator name is valid
  bool isSurfaceEstimatorNameValid( const std::string& estimator_name ) const;

  //! Check if the estimator name is valid
  bool isEstimatorNameValid( const std::string& estimator_name ) const;

  //! Get the estimator type
  EstimatorType getEstimatorType( const std::string& estimator_name ) const;

  //! Set the photon name
  void setPhotonName( const std::string& name );

  //! Get the photon name
  const std::string& getPhotonName() const;

  //! Set the neutron name
  void setNeutronName( const std::string& name );

  //! Get the neutron name
  const std::string& getNeutronName() const;

  //! Set the electron name
  void setElectronName( const std::string& name );

  //! Get the electron name
  const std::string& getElectronName() const;

  //! Set the adjoint photon name
  void setAdjointPhotonName( const std::string& name );

  //! Get the adjoint photon name
  const std::string& getAdjointPhotonName() const;

  //! Set the adjoint neutron name
  void setAdjointNeutronName( const std::string& name );

  //! Get the adjoint neutron name
  const std::string& getAdjointNeutronName() const;

  //! Set the adjoint electron name
  void setAdjointElectronName( const std::string& name );

  //! Get the adjoint electron name
  const std::string& getAdjointElectronName() const;

  //! Check if the particle name is valid
  bool isParticleNameValid( const std::string& particle_name ) const;

  //! Get the partile type
  ParticleType getParticleType( const std::string& particle_name ) const;

private:

  // Default constructor
  DagMCModelProperties();

  // Save the model to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the model from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // The default file path
  static boost::filesystem::path s_default_path;

  // The model file name
  std::string d_file_name;

  // The model file path
  boost::filesystem::path d_file_path;

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

  // The photon name
  std::string d_photon_name;

  // The neutron name
  std::string d_neutron_name;

  // The electron name
  std::string d_electron_name;

  // The adjoint photon name
  std::string d_adjoint_photon_name;

  // The adjoint neutron name
  std::string d_adjoint_neutron_name;

  // The adjoint electron name
  std::string d_adjoint_electron_name;
};

// Save the model to an archive
template<typename Archive>
void DagMCModelProperties::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_file_name );

  std::string raw_file_path = d_file_path.string();

  ar & BOOST_SERIALIZATION_NVP( raw_file_path );
  
  ar & BOOST_SERIALIZATION_NVP( d_fast_id_lookup );
  ar & BOOST_SERIALIZATION_NVP( d_termination_cell_property );
  ar & BOOST_SERIALIZATION_NVP( d_reflecting_surface_property );
  ar & BOOST_SERIALIZATION_NVP( d_material_property );
  ar & BOOST_SERIALIZATION_NVP( d_density_property );
  ar & BOOST_SERIALIZATION_NVP( d_estimator_property );
  ar & BOOST_SERIALIZATION_NVP( d_surface_current_name );
  ar & BOOST_SERIALIZATION_NVP( d_surface_flux_name );
  ar & BOOST_SERIALIZATION_NVP( d_cell_pulse_height_name );
  ar & BOOST_SERIALIZATION_NVP( d_cell_track_length_flux_name );
  ar & BOOST_SERIALIZATION_NVP( d_cell_collision_flux_name );
  ar & BOOST_SERIALIZATION_NVP( d_photon_name );
  ar & BOOST_SERIALIZATION_NVP( d_neutron_name );
  ar & BOOST_SERIALIZATION_NVP( d_electron_name );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photon_name );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_neutron_name );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_electron_name );
}

// Load the model from an archive
template<typename Archive>
void DagMCModelProperties::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_file_name );

  std::string raw_file_path;

  ar & BOOST_SERIALIZATION_NVP( raw_file_path );

  d_file_path = raw_file_path;
  d_file_path.make_preferred();

  // If the path doesn't exist - try to use the default path
  if( !boost::filesystem::exists( d_file_path ) ||
      !boost::filesystem::exists( d_file_path / d_file_name ) )
    d_file_path = s_default_path;
  
  ar & BOOST_SERIALIZATION_NVP( d_fast_id_lookup );
  ar & BOOST_SERIALIZATION_NVP( d_termination_cell_property );
  ar & BOOST_SERIALIZATION_NVP( d_reflecting_surface_property );
  ar & BOOST_SERIALIZATION_NVP( d_material_property );
  ar & BOOST_SERIALIZATION_NVP( d_density_property );
  ar & BOOST_SERIALIZATION_NVP( d_estimator_property );
  ar & BOOST_SERIALIZATION_NVP( d_surface_current_name );
  ar & BOOST_SERIALIZATION_NVP( d_surface_flux_name );
  ar & BOOST_SERIALIZATION_NVP( d_cell_pulse_height_name );
  ar & BOOST_SERIALIZATION_NVP( d_cell_track_length_flux_name );
  ar & BOOST_SERIALIZATION_NVP( d_cell_collision_flux_name );
  ar & BOOST_SERIALIZATION_NVP( d_photon_name );
  ar & BOOST_SERIALIZATION_NVP( d_neutron_name );
  ar & BOOST_SERIALIZATION_NVP( d_electron_name );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_photon_name );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_neutron_name );
  ar & BOOST_SERIALIZATION_NVP( d_adjoint_electron_name );
}

} // end Geometry namespace

BOOST_SERIALIZATION_CLASS_VERSION( DagMCModelProperties, Geometry, 0 );
BOOST_SERIALIZATION_CLASS_EXPORT_STANDARD_KEY( DagMCModelProperties, Geometry );
EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( Geometry, DagMCModelProperties );

#endif // end GEOMETRY_DAGMC_MODEL_PROPERTIES_HPP

//---------------------------------------------------------------------------//
// end Geometry_DagMCModelProperties.hpp
//---------------------------------------------------------------------------//

