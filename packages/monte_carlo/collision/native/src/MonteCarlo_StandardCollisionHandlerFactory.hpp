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
#include "Geometry_Root.hpp"

namespace MonteCarlo{

/*! The default initialization of the StandardCollisionHandlerFactory class.
 * \ingroup estimator_module
 */ 
template<typename GeometryHandler>
class StandardCollisionHandlerFactory : public CollisionHandlerFactory
{

public:

  //! Initialize the collision handler
  void initializeHandler( 
		     const Teuchos::ParameterList& material_reps,
		     const Teuchos::ParameterList& cross_sections_table_info,
		     const std::string& cross_sections_xml_directory );

};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_COLLISION_HANDLER_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardCollisionHandlerFactory.hpp
//---------------------------------------------------------------------------//
