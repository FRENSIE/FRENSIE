//---------------------------------------------------------------------------//
//! 
//! \file   Transmutation_ModuleInterfaceDecl.hpp
//! \author Alex Bennett
//! \brief  Transmutation module interface class declaration
//!
//---------------------------------------------------------------------------//

#ifndef TRANSMUTATION_MODULE_INTERFACE_DECL_HPP
#define TRANSMUTATION_MODULE_INTERFACE_DECL_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// Boost Includes
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "Geometry_ModuleTraits.hpp"
#include "Facemc_NuclearReactionType.hpp"

/*! \defgroup transmutation_module Transmutation Module
 *
 * The handling of transmutation has been abstracted. This allows other
 * handling packages to use this software without changing other code modules.
 * The other code modules only interact with the transmutation module interface.
 */

namespace Transmutation{

//! The struct that provides the default transmutation handler compile time error
template<typename TransmutationHandler>
struct UndefinedTransmutationHandler
{
   //! This function should not compile if there is any attempt to instantiate
   static inline void notDefined() { return TransmutationHandler::this_transmutation_handler_is_missing_an_interface_specialization(); }
};

/*! \brief Default transmutation module interface class
 * \ingroup transmutation_module
 *
 * This struct specifiesthe interface to the transmutation module. This class
 * must be specialized for a particular transmutation handling package. Attempting
 * to use this class without a specialization will reseult in a compile time
 * error. The complile time error message is defined by the 
 * Transmutation::UndefinedTransmutationHandler struct.
 */

template<typename TransmutationHandler>
class ModuleInterface
{

public:
  //! Set the reaction rates
  static inline void setReactionRates(const int reaction, 
                                      Teuchos::Array<std::pair<int,double> >& reaction_rates, 
                                      const Geometry::ModuleTraits::InternalCellHandle cell_id)
  { (void)UndefinedTransmutationHandler<TransmutationHandler>::notDefined(); return 0; }

  //! Set the fission reaction rates
  static inline void setFissionReactionRates(const int zaid, 
                                             const double& reaction_rate, 
                                             Teuchos::Array<std::pair<int,double> >& fission_fragment_reaction_rates,
                                             const Geometry::ModuleTraits::InternalCellHandle cell_id)
  { (void)UndefinedTransmutationHandler<TransmutationHandler>::notDefined(); return 0; }

  //! Set the number densities
  static inline void setNumberDensities(const boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,Teuchos::Array<std::pair<int,double> > >& number_densities)
  { (void)UndefinedTransmutationHandler<TransmutationHandler>::notDefined(); return 0; }

  //! Solve the transmutation matrix
  static inline void burn(const double& time, 
                          boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,Teuchos::Array<std::pair<int,double> > >& final_number_density)
  { (void)UndefinedTransmutationHandler<TransmutationHandler>::notDefined(); return 0; }
};

//! Set the transmutation handler instance
template<typename TransmutationHandler>
void setTransmutationHandlerInstance ( const Teuchos::RCP<TransmutationHandler>& handler )
{
  Transmutation::ModuleInterface<TransmutationHandler>::setHandler(handler);
}

}; // end transmutation namespace

#endif // end TRANSMUTATION_MODULE_INTERFACE_DECL_HPP

//---------------------------------------------------------------------------//
// end Transmutation_ModuleInterfaceDecl.hpp
//---------------------------------------------------------------------------//

