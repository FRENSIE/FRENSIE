//---------------------------------------------------------------------------//
//!
//! \file   Facemc_CollisionHandler.hpp
//! \author Alex Robinson
//! \brief  Collision handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_COLLISION_HANDLER_HPP
#define FACEMC_COLLISION_HANDLER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "Facemc_NeutronMaterial.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace Facemc{

//! The collision handler class
class CollisionHandler
{

public:

  //! Add a material to the collision handler
  static void addMaterial( 
	      const Teuchos::RCP<NeutronMaterial>& material,
	      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
	      cells_containing_material );

  //! Check if a cell is void
  static bool isCellVoid(
		       const Geometry::ModuleTraits::InternalCellHandle cell );

  //! Get the material contained in a cell
  static const Teuchos::RCP<NeutronMaterial>& 
  getCellMaterial( const Geometry::ModuleTraits::InternalCellHandle cell );

  //! Get the total macroscopic cross section of a material
  static double getMacroscopicTotalCrossSection(
					       const ParticleState& particle );

  //! Get the macroscopic cross section for a specific reaction
  static double getMacroscopicReactionCrossSection(
					  const ParticleState& particle,
					  const NuclearReactionType reaction );

  //! Collide with the material in a cell
  static void collideWithCellMaterial( ParticleState& particle,
				       ParticleBank& bank,
				       const bool analogue );	       

private:

  // Typedef for cell id material map
  typedef boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
			       Teuchos::RCP<NeutronMaterial> >
  CellIdMaterialMap;

  static CellIdMaterialMap master_neutron_map;
};

} // end Facemc namespace

#endif // end FACEMC_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end Facemc_CollisionHandler.hpp
//---------------------------------------------------------------------------//
