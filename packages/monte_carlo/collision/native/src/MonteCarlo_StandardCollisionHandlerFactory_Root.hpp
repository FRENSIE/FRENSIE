//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardCollisionHandlerFactory_Root.hpp
//! \author Alex Robinson, Eli Moll
//! \brief  Standard collision handler factory class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_COLLISION_HANDLER_FACTORY_ROOT_HPP
#define MONTE_CARLO_STANDARD_COLLISION_HANDLER_FACTORY_ROOT_HPP

// Std Lib Includes
#include <stdexcept>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterList.hpp>

// FRENSIE Includes
#include "MonteCarlo_CollisionHandler.hpp"
#include "MonteCarlo_StandardCollisionHandlerFactory.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"
#include "MonteCarlo_IncoherentModelType.hpp"
#include "MonteCarlo_BremsstrahlungAngularDistributionType.hpp"
#include "Geometry_Config.hpp"

#ifdef HAVE_FRENSIE_ROOT
#include "Geometry_Root.hpp"

namespace MonteCarlo{

/*! The specialization of the CollimatorHandlerFactory class for the Root 
 * geometry handler.
 * \ingroup estimator_module
 */ 
template<>
class StandardCollisionHandlerFactory<Geometry::Root> : public CollisionHandlerFactory
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

  //! Validate the material ids
  void validateMaterialIds( const MatIdSet& material_ids ) const;


  //! Create the cell id data maps
  void createCellIdDataMaps( CellIdMatIdMap& cell_id_mat_id_map,
                             CellIdDensityMap& cell_id_density_map ) const;
};

} // end MonteCarlo namespace

#endif // end HAVE_FRENSIE_ROOT

#endif // end MONTE_CARLO_STANDARD_COLLISION_HANDLER_FACTORY_ROOT_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCollisionHandlerFactory_Root.hpp
//---------------------------------------------------------------------------//
