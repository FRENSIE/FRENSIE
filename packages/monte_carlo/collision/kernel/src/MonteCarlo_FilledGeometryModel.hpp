//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_FilledGeometryModel.hpp
//! \author Alex Robinson
//! \brief  The filled geometry model class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_FILLED_GEOMETRY_MODEL_HPP
#define MONTE_CARLO_FILLED_GEOMETRY_MODEL_HPP

// Boost Includes
#include <boost/filesystem.hpp>
#include <boost/serialization/split_member.hpp>

// FRENSIE Includes
#include "MonteCarlo_FilledNeutronGeometryModel.hpp"
#include "MonteCarlo_FilledPhotonGeometryModel.hpp"
#include "MonteCarlo_FilledAdjointPhotonGeometryModel.hpp"
#include "MonteCarlo_FilledElectronGeometryModel.hpp"
#include "MonteCarlo_FilledAdjointElectronGeometryModel.hpp"
#include "MonteCarlo_FilledPositronGeometryModel.hpp"
#include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"
#include "MonteCarlo_MaterialDefinitionDatabase.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Geometry_Model.hpp"
#include "Utility_JustInTimeInitializer.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

/*! The filled geometry model class
 *
 * This class can be thought of as an extension to the Geometry::Model. All
 * of the material ids stored in the Geometry::Model object will have an
 * associated material object in this class. 
 */
class FilledGeometryModel : public FilledNeutronGeometryModel,
                            public FilledPhotonGeometryModel,
                            public FilledAdjointPhotonGeometryModel,
                            public FilledElectronGeometryModel,
                            public FilledAdjointElectronGeometryModel,
                            public FilledPositronGeometryModel
{

public:

  //! Constructor
  FilledGeometryModel(
               const boost::filesystem::path& database_path,
               const std::shared_ptr<const ScatteringCenterDefinitionDatabase>&
               scattering_center_definitions,
               const std::shared_ptr<const MaterialDefinitionDatabase>&
               material_definitions,
               const std::shared_ptr<const SimulationProperties>& properties,
               const std::shared_ptr<const Geometry::Model>& geometry_model,
               const bool verbose_construction = true );

  //! Destructor
  ~FilledGeometryModel()
  { /* ... */ }

  //! Set the default database path
  static void setDefaultDatabasePath(
                        const boost::filesystem::path& default_database_path );

  //! Check if a cell is void (as experienced by the given particle type)
  bool isCellVoid( const Geometry::Model::EntityId cell,
                   const MonteCarlo::ParticleType particle_type ) const;

  //! Check if a cell is void (as experienced by the given particle type)
  template<typename ParticleStateType>
  bool isCellVoid( const Geometry::Model::EntityId cell ) const;

  //! Check if a cell is a termination cell
  using FilledNeutronGeometryModel::isTerminationCell;

  //! Get the total macroscopic cross section of a material for the given particle type
  template<typename ParticleStateType>
  double getMacroscopicTotalCrossSection(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const;

  //! Get the total macroscopic cross section of a material for the given particle type
  template<typename ParticleStateType>
  double getMacroscopicTotalCrossSectionQuick(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const;

  //! Get the total macroscopic cross section of a material for neutrons
  using FilledNeutronGeometryModel::getMacroscopicTotalCrossSection;

  //! Get the total macroscopic cross section of a material for neutrons
  using FilledNeutronGeometryModel::getMacroscopicTotalCrossSectionQuick;

  //! Get the total macroscopic cross section of a material for photons
  using FilledPhotonGeometryModel::getMacroscopicTotalCrossSection;

  //! Get the total macroscopic cross section of a material for photons
  using FilledPhotonGeometryModel::getMacroscopicTotalCrossSectionQuick;

  //! Get the total macroscopic cross section of a material for adjoint photons
  using FilledAdjointPhotonGeometryModel::getMacroscopicTotalCrossSection;

  //! Get the total macroscopic cross section of a material for adjoint photons
  using FilledAdjointPhotonGeometryModel::getMacroscopicTotalCrossSectionQuick;

  //! Get the total macroscopic cross section of a material for electrons
  using FilledElectronGeometryModel::getMacroscopicTotalCrossSection;
  
  //! Get the total macroscopic cross section of a material for electrons
  using FilledElectronGeometryModel::getMacroscopicTotalCrossSectionQuick;

  //! Get the total macroscopic cross section of a material for adjoint electrons
  using FilledAdjointElectronGeometryModel::getMacroscopicTotalCrossSection;

  //! Get the total macroscopic cross section of a material for adjoint electrons
  using FilledAdjointElectronGeometryModel::getMacroscopicTotalCrossSectionQuick;

  //! Get the total macroscopic cross section of a material for positrons
  using FilledPositronGeometryModel::getMacroscopicTotalCrossSection;

  //! Get the total macroscopic cross section of a material for positrons
  using FilledPositronGeometryModel::getMacroscopicTotalCrossSectionQuick;

  //! Get the total forward macroscopic cross section of a material for the given particle type
  template<typename ParticleStateType>
  double getMacroscopicTotalForwardCrossSection(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const;

  //! Get the total macroscopic cross section of a material for the given particle type
  template<typename ParticleStateType>
  double getMacroscopicTotalForwardCrossSectionQuick(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const;

  //! Get the total forward macroscopic cs of a material for neutrons
  using FilledNeutronGeometryModel::getMacroscopicTotalForwardCrossSection;

  //! Get the total forward macroscopic cs of a material for neutrons
  using FilledNeutronGeometryModel::getMacroscopicTotalForwardCrossSectionQuick;

  //! Get the total forward macroscopic cs of a material for photons
  using FilledPhotonGeometryModel::getMacroscopicTotalForwardCrossSection;

  //! Get the total forward macroscopic cs of a material for photons
  using FilledPhotonGeometryModel::getMacroscopicTotalForwardCrossSectionQuick;

  //! Get the total forward macroscopic cs of a material for adjoint photons
  using FilledAdjointPhotonGeometryModel::getMacroscopicTotalForwardCrossSection;

  //! Get the total forward macroscopic cs of a material for adjoint photons
  using FilledAdjointPhotonGeometryModel::getMacroscopicTotalForwardCrossSectionQuick;

  //! Get the total forward macroscopic cs of a material for electrons
  using FilledElectronGeometryModel::getMacroscopicTotalForwardCrossSection;

  //! Get the total forward macroscopic cs of a material for electrons
  using FilledElectronGeometryModel::getMacroscopicTotalForwardCrossSectionQuick;

  //! Get the total forward macroscopic cs of a material for adjoint electrons
  using FilledAdjointElectronGeometryModel::getMacroscopicTotalForwardCrossSection;

  //! Get the total forward macroscopic cs of a material for adjoint electrons
  using FilledAdjointElectronGeometryModel::getMacroscopicTotalForwardCrossSectionQuick;

  //! Get the total forward macroscopic cs of a material for positrons
  using FilledPositronGeometryModel::getMacroscopicTotalForwardCrossSection;

  //! Get the total forward macroscopic cs of a material for positrons
  using FilledPositronGeometryModel::getMacroscopicTotalForwardCrossSectionQuick;

  //! Get the adjoint weight factor of a material for the given particle type
  template<typename ParticleStateType>
  double getAdjointWeightFactor(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const;

  //! Get the adjoint weight factor of a material for the given particle type
  template<typename ParticleStateType>
  double getAdjointWeightFactorQuick(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const;

  //! Get the adjoint weight factor for adjoint photons
  using FilledAdjointPhotonGeometryModel::getAdjointWeightFactor;

  //! Get the adjoint weight factor for adjoint photons
  using FilledAdjointPhotonGeometryModel::getAdjointWeightFactorQuick;

  //! Get the adjoint weight factor for adjoint electrons
  using FilledAdjointElectronGeometryModel::getAdjointWeightFactor;

  //! Get the adjoint weight factor for adjoint electrons
  using FilledAdjointElectronGeometryModel::getAdjointWeightFactorQuick;

  //! Get the critical line energies
  template<typename ParticleStateType>
  const std::vector<double>& getCriticalLineEnergies() const;

  //! Get the unfilled geometry model
  const Geometry::Model& getUnfilledModel() const;

  //! Convert to a const unfilled model reference
  operator const Geometry::Model&() const;

  //! Convert to a shared unfilled model
  operator std::shared_ptr<const Geometry::Model>() const;

  //! Check if the model is initialized
  bool isInitialized() const;

private:

  //! Default constructor
  FilledGeometryModel();

  // Pass the unfilled model to the bases
  void passUnfilledModelToBases();

  // Fill the geometry
  void fillGeometry( const bool verbose );

  // Initialize the geometry just-in-time
  void initializeJustInTime();

  // Save the object to an archive
  template<typename Archive>
  void save( Archive& ar, const unsigned version ) const;

  // Load the object from an archive
  template<typename Archive>
  void load( Archive& ar, const unsigned version );

  BOOST_SERIALIZATION_SPLIT_MEMBER();

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;

  // Declare the Utility::JustInTimeInitializer object as a friend
  friend class Utility::JustInTimeInitializer;

  // The default path to the cross section database
  static boost::filesystem::path s_default_database_path;

  // The path to the cross section database
  boost::filesystem::path d_database_path;

  // The scattering center definitions
  std::shared_ptr<const ScatteringCenterDefinitionDatabase>
  d_scattering_center_definitions;

  // The material definitions
  std::shared_ptr<const MaterialDefinitionDatabase> d_material_definitions;

  // The simulation properties
  std::shared_ptr<const SimulationProperties> d_properties;

  // The unfilled model
  std::shared_ptr<const Geometry::Model> d_unfilled_model;

  // Records if the model is filled
  bool d_filled;
};
  
} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( FilledGeometryModel, MonteCarlo, 0 );

EXTERN_EXPLICIT_CLASS_SAVE_LOAD_INST( MonteCarlo, FilledGeometryModel );

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_FilledGeometryModel_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_FILLED_GEOMETRY_MODEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_FilledGeometryModel.hpp
//---------------------------------------------------------------------------//
