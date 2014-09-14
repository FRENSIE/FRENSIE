//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_CollisionHandlerFactory.hpp
//! \author Alex Robinson
//! \brief  Collision handler factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef FACEMC_COLLISION_HANDLER_FACTORY_HPP
#define FACEMC_COLLISION_HANDLER_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_CollisionHandler.hpp"

namespace MonteCarlo{

//! The collision handler factory
class CollisionHandlerFactory
{

public:

  //! Initialize the collision handler using DagMC
  static void initializeHandlerUsingDagMC( 
		     const Teuchos::ParameterList& material_reps,
		     const Teuchos::ParameterList& cross_sections_table_info,
		     const std::string& cross_sections_xml_directory );

private:
  
  // Constructor
  CollisionHandlerFactory();

  // Validate a material representation
  static void validateMaterialRep( 
	      const Teuchos::ParameterList& material_rep,
	      boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle>&
	      material_ids );
  
  // Validate the material ids using DagMC
  static void validateMaterialIdsUsingDagMC( 
				 const Teuchos::ParameterList& material_reps );

  // Create the set of all nuclides needed to construct materials
  static void createNuclideSet( const Teuchos::ParameterList& material_reps,
				boost::unordered_set<std::string>& nuclides );

  // Create the material id data maps
  static void createMaterialIdDataMaps( 
    const Teuchos::ParameterList& material_reps,
    boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                         Teuchos::Array<double> >& material_id_fraction_map,
    boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                      Teuchos::Array<std::string> >& material_id_nuclide_map );

  // Create the material name data maps
  static void createMaterialNameDataMapsUsingDagMC(
     const boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                            Teuchos::Array<double> >& material_id_fraction_map,
     const boost::unordered_map<ModuleTraits::InternalMaterialHandle,
                        Teuchos::Array<std::string> >& material_id_nuclide_map,
     const boost::unordered_map<std::string,Teuchos::RCP<Nuclide> >& 
     nuclide_map,
     boost::unordered_map<std::string,Teuchos::RCP<NeutronMaterial> >&
     material_name_pointer_map,
     boost::unordered_map<std::string,
                  Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle> >&
     material_name_cell_ids_map );  
};

//! The invalid material representation error
class InvalidMaterialRepresentation : public std::logic_error
{
  
public:

  InvalidMaterialRepresentation( const std::string& what_arg )
    : std::logic_error( what_arg )
  { /* ... */ }
};

} // end MonteCarlo namespace

#endif // end FACEMC_COLLISION_HANDLER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionHandlerFactory.hpp
//---------------------------------------------------------------------------//
