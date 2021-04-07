//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardFilledParticleGeometryModel.hpp
//! \author Alex Robinson
//! \brief  The standard filled particle geometry model class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_FILLED_PARTICLE_GEOMETRY_MODEL_HPP
#define MONTE_CARLO_STANDARD_FILLED_PARTICLE_GEOMETRY_MODEL_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/filesystem.hpp>

// FRENSIE Includes
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_ScatteringCenterDefinitionDatabase.hpp"
#include "MonteCarlo_MaterialDefinitionDatabase.hpp"
#include "MonteCarlo_SimulationProperties.hpp"
#include "Geometry_Model.hpp"
#include "Utility_Map.hpp"
#include "Utility_Set.hpp"
#include "Utility_Vector.hpp"

namespace MonteCarlo{

//! The standard filled particle geometry model class
template<typename Material>
class StandardFilledParticleGeometryModel
{
  // Typedef for this type
  typedef StandardFilledParticleGeometryModel<Material> ThisType;

public:

  //! Typedef for the material type
  typedef Material MaterialType;

  //! Typedef for the scattering center name map
  typedef typename Material::ScatteringCenterNameMap ScatteringCenterNameMap;

  //! Typedef for the reaction enum type
  typedef typename Material::ReactionEnumType ReactionEnumType;

  //! Typedef for the particle type
  typedef typename Material::ParticleStateType ParticleStateType;

  //! Check if the entire model is void
  bool isVoid() const;

  //! Check if a cell is void
  bool isCellVoid( const Geometry::Model::EntityId cell ) const;

  //! Check if a cell is a termination cell
  bool isTerminationCell( const Geometry::Model::EntityId cell ) const;

  //! Get the material contained in a cell
  const std::shared_ptr<const MaterialType>&
  getMaterial( const Geometry::Model::EntityId cell ) const;

  //! Destructor
  virtual ~StandardFilledParticleGeometryModel()
  { /* ... */ }

  //! Get the total macroscopic cross section of a material
  double getMacroscopicTotalCrossSection(
                                     const ParticleStateType& particle ) const;

  //! Get the total macroscopic cross section of a material
  double getMacroscopicTotalCrossSection(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const;

  //! Get the total macroscopic cross section of a material
  double getMacroscopicTotalCrossSectionQuick(
                                     const ParticleStateType& particle ) const;

  //! Get the total macroscopic cross section of a material
  double getMacroscopicTotalCrossSectionQuick(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const;

  //! Get the total forward macroscopic cross section of a material
  double getMacroscopicTotalForwardCrossSection(
                                     const ParticleStateType& particle ) const;

  //! Get the total forward macroscopic cross section of a material
  virtual double getMacroscopicTotalForwardCrossSection(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const;

  //! Get the total forward macroscopic cross section of a material
  double getMacroscopicTotalForwardCrossSectionQuick(
                                     const ParticleStateType& particle ) const;

  //! Get the total forward macroscopic cross section of a material
  virtual double getMacroscopicTotalForwardCrossSectionQuick(
                                const Geometry::Model::EntityId cell,
                                const double energy ) const;

  //! Get the macroscopic reaction cross section for a specific reaction
  double getMacroscopicReactionCrossSection(
                                       const ParticleStateType& particle,
                                       const ReactionEnumType reaction ) const;

  //! Get the macroscopic reaction cross section for a specific reaction
  double getMacroscopicReactionCrossSection(
                                const Geometry::Model::EntityId cell,
                                const double energy,
                                const ReactionEnumType reaction ) const;

  //! Get the macroscopic reaction cross section for a specific reaction
  double getMacroscopicReactionCrossSectionQuick(
                                       const ParticleStateType& particle,
                                       const ReactionEnumType reaction ) const;

  //! Get the macroscopic reaction cross section for a specific reaction
  double getMacroscopicReactionCrossSectionQuick(
                                const Geometry::Model::EntityId cell,
                                const double energy,
                                const ReactionEnumType reaction ) const;

  //! Get the unfilled model
  const Geometry::Model& getUnfilledModel() const;
  
protected:

  //! Default constructor
  StandardFilledParticleGeometryModel();

  //! Constructor
  StandardFilledParticleGeometryModel(
                const std::shared_ptr<const Geometry::Model>& unfilled_model );

  //! Set the unfilled model
  void setUnfilledModel( const std::shared_ptr<const Geometry::Model>& unfilled_model );

  //! Load the materials and fill the model
  void loadMaterialsAndFillModel(
       const boost::filesystem::path& database_path,
       const MaterialDefinitionDatabase::ScatteringCenterNameSet&
       unique_scattering_center_names,
       const ScatteringCenterDefinitionDatabase& scattering_center_definitions,
       const std::shared_ptr<AtomicRelaxationModelFactory>&
       atomic_relaxation_model_factory,
       const SimulationProperties& properties,
       const bool verbose_material_construction,
       const MaterialDefinitionDatabase& material_definitions,
       const Geometry::Model::CellIdMatIdMap& cell_id_mat_id_map,
       const Geometry::Model::CellIdDensityMap& cell_id_density_map );

  //! Load the scattering centers
  virtual void loadScatteringCenters(
       const boost::filesystem::path& database_path,
       const MaterialDefinitionDatabase::ScatteringCenterNameSet&
       unique_scattering_center_names,
       const ScatteringCenterDefinitionDatabase& scattering_center_definitions,
       const std::shared_ptr<AtomicRelaxationModelFactory>&
       atomic_relaxation_model_factory,
       const SimulationProperties& properties,
       const bool verbose,                  
       ScatteringCenterNameMap& scattering_center_name_map ) const = 0;
  
  //! Process the loaded scattering centers
  virtual void processLoadedScatteringCenters(
                   const ScatteringCenterNameMap& scattering_centers );

private:

  // Add a material to the collision kernel
  void addMaterial( const std::shared_ptr<const MaterialType>& material,
                    const std::vector<Geometry::Model::EntityId>&
                    cells_containing_material );

  // The unfilled model
  std::shared_ptr<const Geometry::Model> d_unfilled_model;

  // The scattering center name map
  ScatteringCenterNameMap d_scattering_center_name_map;

  // The material name map
  typedef std::unordered_map<std::string,std::shared_ptr<const MaterialType> >
  MaterialNameMap;
  
  MaterialNameMap d_material_name_map;

  // The cell id material map
  typedef std::unordered_map<Geometry::Model::EntityId,std::shared_ptr<const MaterialType> >
  CellIdMaterialMap;

  CellIdMaterialMap d_cell_id_material_map;  
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardFilledParticleGeometryModel_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_FILLED_PARTICLE_GEOMETRY_MODEL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardFilledParticleGeometryModel.hpp
//---------------------------------------------------------------------------//
