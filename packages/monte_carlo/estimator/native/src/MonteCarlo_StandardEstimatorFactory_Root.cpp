//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardEstimatorFactory_Root.cpp
//! \author Alex Robinson
//! \brief  The standard estimator factory class specialization for Root
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_StandardEstimatorFactory_Root.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ExceptionCatchMacros.hpp"
#include "Utility_ContractException.hpp"

#ifdef HAVE_FRENSIE_ROOT

namespace MonteCarlo{

// Constructor
StandardEstimatorFactory<Geometry::Root>::StandardEstimatorFactory(
       const std::shared_ptr<EventHandler>& event_handler,
       const boost::unordered_map<unsigned,std::shared_ptr<ResponseFunction> >&
       response_function_id_map,
       std::ostream* os_warn )
  : EstimatorFactory( event_handler, response_function_id_map, os_warn ),
    d_cell_volume_map(),
    d_surface_area_map()
{ /* ... */ }

// Create and register cached estimators
/*! \details Root does not cache any estimator data so this method is empty.
 */ 
void StandardEstimatorFactory<Geometry::Root>::createAndRegisterCachedEstimators()
{ /* ... */ }

// Verify that the estimator type is consistent with cached data
/*! \details Root does not cache any estimator data so this method is empty 
 * (no cosistency check is required).
 */
void StandardEstimatorFactory<Geometry::Root>::verifyEstimatorTypeConsistency( 
                                      const unsigned estimator_id,
                                      const std::string& estimator_type ) const
{ /* ... */ }

// Verify the existence of cells
void StandardEstimatorFactory<Geometry::Root>::verifyExistenceOfCells(
        const boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle>&
        cells,
        const unsigned estimator_id ) const
{
  boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle>::const_iterator cell = cells.begin();

  while( cell != cells.end() )
  {
    TEST_FOR_EXCEPTION(
                     !Geometry::Root::doesCellExist( *cell ),
                     InvalidEstimatorRepresentation,
                     "Error: estimator " << estimator_id << " specified cell " 
                     << *cell << " in the xml file, which does not exists!" );

    ++cell;
  }
}

// Get the cached cells (add to set)
/*! \details Root does not cache any estimator data so this method is empty.
 */
void StandardEstimatorFactory<Geometry::Root>::getCachedCells( 
       boost::unordered_set<Geometry::ModuleTraits::InternalCellHandle>& cells,
       const unsigned estimator_id ) const
{ /* ... */ }

// Get the cell volumes
void StandardEstimatorFactory<Geometry::Root>::getCellVolumes( 
     Teuchos::Array<double>& cell_volumes,
     const Teuchos::Array<Geometry::ModuleTraits::InternalCellHandle>& cells )
{ 
  // Resize the cell volume array
  cell_volumes.resize( cells.size() );

  // Get the volume of every cell
  for( unsigned i = 0; i < cells.size(); ++i )
  {
    // Check if the cell volume has already been cached
    if( d_cell_volume_map.find( cells[i] ) != d_cell_volume_map.end() )
      cell_volumes[i] = d_cell_volume_map.find( cells[i] )->second;
  
    // Calculate and cache the cell volume if the cell is new
    else
    {
      cell_volumes[i] = Geometry::Root::getCellVolume( cells[i] );

      d_cell_volume_map[cells[i]] = cell_volumes[i];
    }
  }
}

// Verify the existence of surfaces
void StandardEstimatorFactory<Geometry::Root>::verifyExistenceOfSurfaces(
     const boost::unordered_set<Geometry::ModuleTraits::InternalSurfaceHandle>&
     surfaces,
     const unsigned estimator_id ) const
{ /* ... */ }

// Get the cached surfaces (add to set)
/*! \details Root does not cache any estimator data so this method is empty.
 */
void StandardEstimatorFactory<Geometry::Root>::getCachedSurfaces(
           boost::unordered_set<Geometry::ModuleTraits::InternalSurfaceHandle>&
           surfaces,
           const unsigned estimator_id ) const
{ /* ... */ }

// Get the surface areas
void StandardEstimatorFactory<Geometry::Root>::getSurfaceAreas( 
           Teuchos::Array<double>& surface_areas,
           const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
           surfaces )
{
  THROW_EXCEPTION( InvalidEstimatorRepresentation,
                   "Error: Surface estimators are not supported with Root!" );
}

// Create and register a surface estimator
/*! \details Surface estimators are not supported with Root. This estimator
 * will be ignored and a warning message will be displayed.
 */
void StandardEstimatorFactory<Geometry::Root>::createAndRegisterSurfaceEstimator(
      const std::string& surface_estimator_type,
      const unsigned id,
      const double multiplier,
      const Teuchos::Array<ParticleType> particle_types,
      const Teuchos::Array<std::shared_ptr<ResponseFunction> >& response_funcs,
      const Teuchos::Array<Geometry::ModuleTraits::InternalSurfaceHandle>&
      surfaces,
      const bool energy_multiplication,
      const Teuchos::ParameterList* bins )
{
  this->getWarningOutputStream() 
    << "Warning: Surface estimators are not supported when using Root. "
    << "Estimator " << id << " will be ignored." << std::endl;
}

// Update the estimator cache info
/*! \details Root does not cache any estimator data so this method is empty.
 */
void StandardEstimatorFactory<Geometry::Root>::updateEstimatorCacheInfo( 
                                                            const unsigned id )
{ /* ... */ }

} // end MonteCarlo namespace

#endif // end HAVE_FRENSIE_ROOT

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardEstimatorFactory_Root.cpp
//---------------------------------------------------------------------------//
