//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCollisionHandlerFactory.cpp
//! \author Alex Robinson, Eli Moll
//! \brief  Standard collision handler factory class definition.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/unordered_set.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardCollisionHandlerFactory_Root.hpp"
#include "MonteCarlo_NuclideFactory.hpp"
#include "MonteCarlo_PhotoatomFactory.hpp"
#include "MonteCarlo_ElectroatomFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_SimulationGeneralProperties.hpp"
#include "Utility_ArrayString.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

#ifdef HAVE_FRENSIE_ROOT

// Validate the material ids
/*! \details If ROOT has not been enabled this function will be empty. 
 */
void StandardCollisionHandlerFactory<Geometry::Root>::validateMaterialIds(
			    const Teuchos::ParameterList& material_reps ) const
{
  // Construct the set of material ids
  boost::unordered_set<ModuleTraits::InternalMaterialHandle> material_ids;

  Teuchos::ParameterList::ConstIterator it = material_reps.begin();

  while( it != material_reps.end() )
  {
    const Teuchos::ParameterList& material_rep = 
      Teuchos::any_cast<Teuchos::ParameterList>( it->second.getAny() );

    material_ids.insert( material_rep.get<unsigned int>( "Id" ) );
    
    ++it;
  }

  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                       ModuleTraits::InternalMaterialHandle>
    cell_id_mat_id_map;

  try{
    Geometry::Root::getCellMaterialIds( cell_id_mat_id_map );
  }
  EXCEPTION_CATCH_RETHROW_AS( Geometry::InvalidRootGeometry,
                              InvalidMaterialRepresentation,
                              "Error: could not extract the material ids "
                              "from ROOT!" );                              
  
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                       ModuleTraits::InternalMaterialHandle>::const_iterator 
    cell_it = cell_id_mat_id_map.begin();
  
  while( cell_it != cell_id_mat_id_map.end() )
  {
    TEST_FOR_EXCEPTION( material_ids.find( cell_it->second ) ==
                        material_ids.end(),
                        InvalidMaterialRepresentation,
                        "Error: ROOT has requested material number "
                        << cell_it->second << " which is lacking "
                        "a definition!" );

    ++cell_it;
  }
}

// Create the cell id data maps
/*! If ROOT has not been enabled this function will be empty
 */
void StandardCollisionHandlerFactory<Geometry::Root>::createCellIdDataMaps(
          boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
	  std::vector<std::string> >& cell_id_mat_id_map,
          boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
	  std::vector<std::string> >& cell_id_density_map ) const
{
  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                       ModuleTraits::InternalMaterialHandle>
    raw_cell_id_mat_id_map;
  
  try{
    Geometry::Root::getCellMaterialIds( raw_cell_id_mat_id_map );
  }
  EXCEPTION_CATCH_RETHROW_AS( Geometry::InvalidRootGeometry,
                              InvalidMaterialRepresentation,
                              "Error: could not extract the material ids "
                              "from ROOT!" );  

  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,double>
    raw_cell_id_density_map;

  try{
    Geometry::Root::getCellDensities( raw_cell_id_density_map );
  }
  EXCEPTION_CATCH_RETHROW_AS( Geometry::InvalidRootGeometry,
                              InvalidMaterialRepresentation,
                              "Error: could not extract the cell densities "
                              "from ROOT!" );  
    
  // Make sure that the maps have the same size
  TEST_FOR_EXCEPTION( raw_cell_id_mat_id_map.size() != 
                      raw_cell_id_density_map.size(),
		      InvalidMaterialRepresentation,
		      "Error: ROOT must specify densities with material "
		      "ids!" );

  // Convert the raw cell id mat id map
  {
    boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                         ModuleTraits::InternalMaterialHandle>::const_iterator
      cell_it = raw_cell_id_mat_id_map.begin();

    while( cell_it != raw_cell_id_mat_id_map.end() )
    {
      std::vector<std::string> converted_mat_id;
      converted_mat_id.push_back( std::to_string( cell_it->second ) );
      
      cell_id_mat_id_map[cell_it->first] = converted_mat_id;
      
      ++cell_it;
    }
  }

  // Convert the raw cell id density map
  {
    boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,double>::const_iterator
      cell_it = raw_cell_id_density_map.begin();

    while( cell_it != raw_cell_id_density_map.end() )
    {
      std::vector<std::string> converted_density;
      converted_density.push_back( std::to_string( cell_it->second ) );

      cell_id_density_map[cell_it->first] = converted_density;

      ++cell_it;
    }         
  }
}

#endif // end HAVE_FRENSIE_ROOT

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_CollisionHandlerFactory.cpp
//---------------------------------------------------------------------------//
