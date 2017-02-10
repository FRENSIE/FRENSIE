//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomNativeFactory.cpp
//! \author Luke Kersting
//! \brief  The electroatom native factory class definition.
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomNativeFactory.hpp"
#include "MonteCarlo_ElectroatomicReactionNativeFactory.hpp"
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_TwoDInterpolationPolicy.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Create a electroatom (using the provided atomic relaxation model)
/*! \details The provided atomic relaxation model will be used with this
 * atom. Special care must be taken to assure that the model corresponds to
 * the atom of interest. If the use of atomic relaxation data has been
 * requested, a electroionization reaction for each subshell will be created.
 * Otherwise a single total electroionization reaction will be created.
 */
void ElectroatomNativeFactory::createElectroatom(
       const Data::ElectronPhotonRelaxationDataContainer& raw_electroatom_data,
       const std::string& electroatom_name,
       const double atomic_weight,
       const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model,
       const SimulationElectronProperties& properties,
       Teuchos::RCP<Electroatom>& electroatom )
{
  // Make sure the atomic weight is valid
  testPrecondition( atomic_weight > 0.0 );
  // Make sure the atomic relaxation model is valid
  testPrecondition( !atomic_relaxation_model.is_null() );

  Teuchos::RCP<ElectroatomCore> core;

  // Check if LinLinLog interplation mode is on
  if ( properties.isLinLinLogInterpolationModeOn() )
  {
    // Set the secondary electron interpolation policy as LinLinLog
    ElectroatomNativeFactory::createElectroatomCore<Utility::LinLinLog>(
            raw_electroatom_data,
            atomic_relaxation_model,
            properties,
            core );
  }
  else
  {
    // Set the secondary electron interpolation policy as LinLinLin
    ElectroatomNativeFactory::createElectroatomCore<Utility::LinLinLin>(
            raw_electroatom_data,
            atomic_relaxation_model,
            properties,
            core );
  }

  // Create the electroatom
  electroatom.reset( new Electroatom( electroatom_name,
                                      raw_electroatom_data.getAtomicNumber(),
                                      atomic_weight,
                                      *core ) );
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomNativeFactory.cpp
//---------------------------------------------------------------------------//
