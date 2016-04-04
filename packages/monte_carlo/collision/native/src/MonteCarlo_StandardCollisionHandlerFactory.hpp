//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCollisionHandlerFactory.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Collision handler factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_COLLISION_HANDLER_FACTORY_HPP
#define MONTE_CARLO_STANDARD_COLLISION_HANDLER_FACTORY_HPP

// Std Lib Includes
#include <stdexcept>
#include <memory>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_CollisionHandler.hpp"
#include "MonteCarlo_CollisionHandlerFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_IncoherentModelType.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"

namespace MonteCarlo{

/*! The default implementation of the StandardCollisionHandlerFactory class.
 * \details This class specifies the functions that must be implemented in
 * specializations of this class. If a GeometryHandler class does not have
 * a specialization the code will not compile.
 * \ingroup collision_module
 */ 
template<typename GeometryHandler>
class StandardCollisionHandlerFactory : public CollisionHandlerFactory
{

public:

  // Constructor
  StandardCollisionHandlerFactory( std::ostream* os_warn = &std::cerr ) 
    : CollisionHandlerFactory( os_warn )
  { /* ... */ }

  // Destructor
  ~StandardCollisionHandlerFactory()
  { /* ... */ }

protected:

  //! The cell id mat id map typedef
  typedef CollisionHandlerFactory::CellIdMatIdMap CellIdMatIdMap;

  //! The cell id density map typedef
  typedef CollisionHandlerFactory::CellIdDensityMap CellIdDensityMap;

  //! The material id set typedef
  typedef CollisionHandlerFactory::MatIdSet MatIdSet;

  //! Validate the material ids using the GeometryHandler
  inline void validateMaterialIds( const MatIdSet& material_ids ) const
  { GeometryHandler::geometry_handler_is_missing_specialization(); }

  //! Create the cell id data maps using the GeometryHandler
  inline void createCellIdDataMaps( 
                                  CellIdMatIdMap& cell_id_mat_id_map,
                                  CellIdDensityMap& cell_id_density_map ) const
  { GeometryHandler::geometry_handler_is_missing_specialization(); }
};

//! Helper function for creating a collision handler instance
template<typename GeometryHandler>
inline std::shared_ptr<CollisionHandlerFactory> 
getCollisionHandlerFactoryInstance( std::ostream* os_warn = &std::cerr )
{
  return std::shared_ptr<CollisionHandlerFactory>( new StandardCollisionHandlerFactory<GeometryHandler>( os_warn ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_COLLISION_HANDLER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCollisionHandlerFactory.hpp
//---------------------------------------------------------------------------//
