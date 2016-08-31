//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionHandler.hpp
//! \author Alex Robinson
//! \brief  Collision handler class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COLLISION_HANDLER_HPP
#define MONTE_CARLO_COLLISION_HANDLER_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "MonteCarlo_NeutronMaterial.hpp"
#include "MonteCarlo_PhotonMaterial.hpp"
#include "MonteCarlo_ElectronMaterial.hpp"
#include "MonteCarlo_NeutronState.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Geometry_ModuleTraits.hpp"

namespace MonteCarlo{

//! The collision handler class
class CollisionHandler
{

private:

  // Typedef for cell id neutron material map
  typedef boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
			       Teuchos::RCP<NeutronMaterial> >
  CellIdNeutronMaterialMap;

  // Typedef for cell id photon material map
  typedef boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
			       Teuchos::RCP<PhotonMaterial> >
  CellIdPhotonMaterialMap;

  // Typedef for cell id electron material map
  typedef boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
			       Teuchos::RCP<ElectronMaterial> >
  CellIdElectronMaterialMap;

public:

  //! Add a material to the collision handler
  static void addMaterial(
	      const Teuchos::RCP<NeutronMaterial>& material,
	      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
	      cells_containing_material );

  //! Add a material to the collision handler
  static void addMaterial(
	      const Teuchos::RCP<PhotonMaterial>& material,
	      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
	      cells_containing_material );

  //! Add a material to the collision handler
  static void addMaterial(
	      const Teuchos::RCP<NeutronMaterial>& neutron_material,
	      const Teuchos::RCP<PhotonMaterial>& photon_material,
	      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
	      cells_containing_material );

  //! Add a material to the collision handler
  static void addMaterial(
	      const Teuchos::RCP<ElectronMaterial>& material,
	      const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>&
	      cells_containing_material );

  //! Check if a cell is void
  static bool isCellVoid(const Geometry::ModuleTraits::InternalCellHandle cell,
			 const ParticleType particle_type );

  //! Get the neutron material contained in a cell
  static const Teuchos::RCP<NeutronMaterial>&
  getCellNeutronMaterial(
		       const Geometry::ModuleTraits::InternalCellHandle cell );

  //! Get the photon material contained in a cell
  static const Teuchos::RCP<PhotonMaterial>&
  getCellPhotonMaterial(
		       const Geometry::ModuleTraits::InternalCellHandle cell );

  //! Get the electron material contained in a cell
  static const Teuchos::RCP<ElectronMaterial>&
  getCellElectronMaterial(
		       const Geometry::ModuleTraits::InternalCellHandle cell );

  //! Get the total macroscopic cross section of a material
  static double getMacroscopicTotalCrossSection( const NeutronState& particle);

  //! Get the total macroscopic cross section of a material
  static double getMacroscopicTotalCrossSection( const PhotonState& particle );

  //! Get the total macroscopic cross section of a material
  static double getMacroscopicTotalCrossSection( const ElectronState& particle );

  //! Get the macroscopic cross section for a specific reaction
  static double getMacroscopicReactionCrossSection(
					  const NeutronState& particle,
					  const NuclearReactionType reaction );

  //! Get the macroscopic cross section for a specific reaction
  static double getMacroscopicReactionCrossSection(
				      const PhotonState& particle,
				      const PhotoatomicReactionType reaction );

  //! Get the macroscopic cross section for a specific reaction
  static double getMacroscopicReactionCrossSection(
				     const PhotonState& particle,
				     const PhotonuclearReactionType reaction );

  //! Get the macroscopic cross section for a specific reaction
  static double getMacroscopicReactionCrossSection(
				      const ElectronState& particle,
				      const ElectroatomicReactionType reaction );

  //! Collide with the material in a cell
  static void collideWithCellMaterial( PhotonState& particle,
				       ParticleBank& bank,
				       const bool analogue );

  //! Collide with the material in a cell
  static void collideWithCellMaterial( NeutronState& particle,
				       ParticleBank& bank,
				       const bool analogue );

  //! Collide with the material in a cell
  static void collideWithCellMaterial( ElectronState& particle,
				       ParticleBank& bank,
				       const bool analogue );

private:

  // The cell id neutron material map
  static CellIdNeutronMaterialMap master_neutron_map;

  static CellIdPhotonMaterialMap master_photon_map;

  static CellIdElectronMaterialMap master_electron_map;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_COLLISION_HANDLER_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionHandler.hpp
//---------------------------------------------------------------------------//
