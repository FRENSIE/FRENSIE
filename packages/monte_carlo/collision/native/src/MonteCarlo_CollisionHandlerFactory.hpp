//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionHandlerFactory.hpp
//! \author Alex Robinson
//! \brief  Collision handler factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_COLLISION_HANDLER_FACTORY_HPP
#define MONTE_CARLO_COLLISION_HANDLER_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>
#include <ostream>
#include <unordered_map>
#include <unordered_set>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_CollisionHandler.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_IncoherentModelType.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"

namespace MonteCarlo{

//! The base collision handler factory
class CollisionHandlerFactory
{

public:

  //! Constructor
  CollisionHandlerFactory( std::ostream* os_warn );

  //! Destructor
  virtual ~CollisionHandlerFactory()
  { /* ... */ }

  //! Initialize the collision handler
  void initializeHandler( 
		     const Teuchos::ParameterList& material_reps,
		     const Teuchos::ParameterList& cross_sections_table_info,
		     const std::string& cross_sections_xml_directory );

protected:

  //! The cell id mat id map typedef
  typedef std::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                             ModuleTraits::InternalMaterialHandle>
  CellIdMatIdMap;

  //! The cell id density map typedef
  typedef std::unordered_map<Geometry::ModuleTraits::InternalCellHandle,double>
  CellIdDensityMap;

  //! The material id set typedef
  typedef std::unordered_set<ModuleTraits::InternalMaterialHandle>
  MatIdSet;

//! Validate the material ids
  virtual void validateMaterialIds( const MatIdSet& material_ids ) const = 0;

  //! Create the cell id data maps using the GeometryHandler
  virtual void createCellIdDataMaps( 
                             CellIdMatIdMap& cell_id_mat_id_map,
                             CellIdDensityMap& cell_id_density_map ) const = 0;

  //! Get the warning output stream
  std::ostream& getOsWarn() const;

private:
  
  //! The nuclide alias set
  typedef std::unordered_set<std::string> AliasSet;

  //! The material id fraction map typedef 
  typedef std::unordered_map<ModuleTraits::InternalMaterialHandle,
                             Teuchos::Array<double> >
  MatIdFractionMap;

  //! The material id component map typedef 
  typedef std::unordered_map<ModuleTraits::InternalMaterialHandle,
                             Teuchos::Array<std::string> >
  MatIdComponentMap;

  //! The material name cell ids map typedef
  typedef std::unordered_map<std::string,Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >
  MatNameCellIdsMap;

  //! Validate a material representation
  static void validateMaterialRep( const Teuchos::ParameterList& material_rep,
                                   MatIdSet& material_ids );

  //! Create the set of all nuclides/atoms needed to construct materials
  static void createAliasSet( 
		        const Teuchos::ParameterList& material_reps,
		        const Teuchos::ParameterList& cross_sections_alias_map,
		        AliasSet& nuclides );

  //! Create the material id data maps
  static void createMaterialIdDataMaps( 
                                const Teuchos::ParameterList& material_reps,
                                MatIdFractionMap& material_id_fraction_map,
                                MatIdComponentMap& material_id_component_map );

  //! Create the neutron materials
  void createNeutronMaterials( 
                       const Teuchos::ParameterList& cross_sections_table_info,
                       const std::string& cross_sections_xml_directory,
                       const MatIdFractionMap& material_id_fraction_map,
                       const MatIdComponentMap& material_id_component_map,
                       const AliasSet& nuclide_aliases,
                       const CellIdMatIdMap& cell_id_mat_id_map,
                       const CellIdDensityMap& cell_id_density_map,
                       const bool use_unresolved_resonance_data,
                       const bool use_photon_production_data );
   
  //! Create the photon materials
  void createPhotonMaterials(
   const Teuchos::ParameterList& cross_sections_table_info,
   const std::string& cross_sections_xml_directory,
   const MatIdFractionMap& material_id_fraction_map,
   const MatIdComponentMap& material_id_component_map,
   const AliasSet& nuclide_aliases,
   const CellIdMatIdMap& cell_id_mat_id_map,
   const CellIdDensityMap& cell_id_density_map,
   const Teuchos::RCP<AtomicRelaxationModelFactory>& 
   atomic_relaxation_model_factory,
   const unsigned hash_grid_bins,
   const IncoherentModelType incoherent_model,
   const double kahn_sampling_cutoff_energy,
   const bool use_detailed_pair_production_data,
   const bool use_atomic_relaxation_data,
   const bool use_photonuclear_data );

  //! Create the electron materials
  void createElectronMaterials(
   const Teuchos::ParameterList& cross_sections_table_info,
   const std::string& cross_sections_xml_directory,
   const MatIdFractionMap& material_id_fraction_map,
   const MatIdComponentMap& material_id_component_map,
   const AliasSet& nuclide_aliases,
   const CellIdMatIdMap& cell_id_mat_id_map,
   const CellIdDensityMap& cell_id_density_map,
   const Teuchos::RCP<AtomicRelaxationModelFactory>& 
   atomic_relaxation_model_factory,
   const BremsstrahlungAngularDistributionType photon_distribution_function,
   const bool use_atomic_relaxation_data );

  //! Create the material name data maps
  template<typename ScatteringCenterType, typename MaterialType>
  static void createMaterialNameDataMaps(
   const MatIdFractionMap& material_id_fraction_map,
   const MatIdComponentMap& material_id_component_map,
   const std::unordered_map<std::string,Teuchos::RCP<ScatteringCenterType> >&
   scattering_center_map,
   const CellIdMatIdMap& cell_id_mat_id_map,
   const CellIdDensityMap& cell_id_density_map,
   std::unordered_map<std::string,Teuchos::RCP<MaterialType> >& 
   material_name_pointer_map,
   MatNameCellIdsMap& material_name_cell_ids_map );  

  //! Register materials with the collision handler
  template<typename MaterialType>
  static void registerMaterials(
             const std::unordered_map<std::string,Teuchos::RCP<MaterialType> >&
             material_name_pointer_map,
             const MatNameCellIdsMap& material_name_cell_ids_map );

  // Copy constructor
  CollisionHandlerFactory( const CollisionHandlerFactory& copy );

  // Assignment operator
  CollisionHandlerFactory& operator=( CollisionHandlerFactory& copy );

  // The warning output stream
  std::ostream* d_os_warn;
};

//! The invalid material representation error
class InvalidMaterialRepresentation : public std::runtime_error
{
  
public:

  InvalidMaterialRepresentation( const std::string& what_arg )
    : std::runtime_error( what_arg )
  { /* ... */ }
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_CollisionHandlerFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_COLLISION_HANDLER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionHandlerFactory.hpp
//---------------------------------------------------------------------------//
