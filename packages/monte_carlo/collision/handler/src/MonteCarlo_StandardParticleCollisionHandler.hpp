//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardParticleCollisionHandler.hpp
//! \author Alex Robinson
//! \brief  The standard particle collision handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PARTICLE_COLLISION_HANDLER_HPP
#define MONTE_CARLO_STANDARD_PARTICLE_COLLISION_HANDLER_HPP

// Std Lib Includes
#include <unordered_map>
#include <functional>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Geometry_Model.hpp"
#include "Utility_Vector.hpp"
#include "Utility_Map.hpp"

namespace MonteCarlo{

//! The standard particle collision handler class
template<typename Material>
class StandardParticleCollisionHandler
{
  // Typedef for this type
  typedef StandardParticleCollisionHandler<Material> ThisType;

public:

  //! Typedef for the material type
  typedef Material MaterialType;

  //! Typedef for the reaction enum type
  typedef typename Material::ReactionEnumType ReactionEnumType;

  //! Typedef for the particle type
  typedef typename Material::ParticleStateType ParticleStateType;

  //! Constructor
  StandardParticleCollisionHandler( const bool analogue_collisions = true );

  //! Destructor
  virtual ~StandardParticleCollisionHandler()
  { /* ... */ }

  //! Add a material to the collision handler
  void addMaterial( const std::shared_ptr<const MaterialType>& material,
                    const std::vector<Geometry::Model::InternalCellHandle>&
                    cells_containing_material );

  //! Check if a cell is void
  bool isCellVoid( const Geometry::Model::InternalCellHandle cell ) const;

  //! Get the material contained in a cell
  const std::shared_ptr<const MaterialType>&
  getMaterial( const Geometry::Model::InternalCellHandle cell ) const;

  //! Get the total macroscopic cross section of a material
  double getMacroscopicTotalCrossSection(
                                     const ParticleStateType& particle ) const;

  //! Get the total macroscopic cross section of a material
  double getMacroscopicTotalCrossSection(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const;

  //! Get the total macroscopic cross section of a material
  double getMacroscopicTotalCrossSectionQuick(
                                     const ParticleStateType& particle ) const;

  //! Get the total macroscopic cross section of a material
  double getMacroscopicTotalCrossSectionQuick(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const;

  //! Get the total forward macroscopic cross section of a material
  double getMacroscopicTotalForwardCrossSection(
                                     const ParticleStateType& particle ) const;

  //! Get the total forward macroscopic cross section of a material
  virtual double getMacroscopicTotalForwardCrossSection(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const;

  //! Get the total forward macroscopic cross section of a material
  double getMacroscopicTotalForwardCrossSectionQuick(
                                     const ParticleStateType& particle ) const;

  //! Get the total forward macroscopic cross section of a material
  virtual double getMacroscopicTotalForwardCrossSectionQuick(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy ) const;

  //! Get the macroscopic reaction cross section for a specific reaction
  double getMacroscopicReactionCrossSection(
                                       const ParticleStateType& particle,
                                       const ReactionEnumType reaction ) const;

  //! Get the macroscopic reaction cross section for a specific reaction
  double getMacroscopicReactionCrossSection(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy,
                                const ReactionEnumType reaction ) const;

  //! Get the macroscopic reaction cross section for a specific reaction
  double getMacroscopicReactionCrossSectionQuick(
                                       const ParticleStateType& particle,
                                       const ReactionEnumType reaction ) const;

  //! Get the macroscopic reaction cross section for a specific reaction
  double getMacroscopicReactionCrossSectionQuick(
                                const Geometry::Model::InternalCellHandle cell,
                                const double energy,
                                const ReactionEnumType reaction ) const;

  //! Collide with the material in a cell
  virtual void collideWithCellMaterial( ParticleType& particle,
                                        ParticleBank& bank ) const;

private:

  //! Collide with the material in a cell (analogue)
  void collideWithCellMaterialAnalogue( ParticleType& particle,
                                        ParticleBank& bank ) const;

  //! Collide with the material in a cell (survival bias)
  void collideWithCellMaterialSurvivalBias( ParticleType& particle,
                                            ParticleBank& bank ) const;

  // The collision method function pointer
  std::function<void(typename ParticleType&,ParticleBank&)>
  d_collision_method;

  // Typedef for cell id material map
  typedef std::unordered_map<Geometry::Model::InternalCellHandle,std::shared_ptr<const MaterialType> >
  CellIdMaterialMap;

  // The cell id neutron material map
  CellIdMaterialMap d_cell_id_material_map;
};
  
} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardParticleCollisionHandler_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_PARTICLE_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardParticleCollisionHandler.hpp
//---------------------------------------------------------------------------//
