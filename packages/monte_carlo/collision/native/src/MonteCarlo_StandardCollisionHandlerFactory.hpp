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
  StandardCollisionHandlerFactory()
  { /* ... */ }

  // Destructor
  ~StandardCollisionHandlerFactory()
  { /* ... */ }

protected:

  //! Validate the material ids using the GeometryHandler
  inline void validateMaterialIds(
				  const Teuchos::ParameterList& material_reps )
  { GeometryHandler::geometry_handler_is_missing_specialization(); }

  //! Create the cell id data maps using the GeometryHandler
  inline void createCellIdDataMaps(
	  boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                               std::vector<std::string> >& cell_id_mat_id_map,
          boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,
                              std::vector<std::string> >& cell_id_density_map )
  { GeometryHandler::geometry_handler_is_missing_specialization(); }
};

//! Helper function for creating a collision handler instance
template<typename GeometryHandler>
inline Teuchos::RCP<CollisionHandlerFactory> 
getCollisionHandlerFactoryInstance()
{
  return Teuchos::rcp( new StandardCollisionHandlerFactory<GeometryHandler>() );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_COLLISION_HANDLER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCollisionHandlerFactory.hpp
//---------------------------------------------------------------------------//
