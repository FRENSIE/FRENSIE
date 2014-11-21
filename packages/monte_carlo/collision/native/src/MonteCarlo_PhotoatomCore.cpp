//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomCore.cpp
//! \author Alex Robinson
//! \brief  The photoatom core class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_PhotoatomCore.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

//! Constructor
PhotoatomCore::PhotoatomCore( 
      const Teuchos::RCP<const PhotoatomicReaction>& total_reaction,
      const Teuchos::RCP<const PhotoatomicReaction>& total_absorption_reaction,
      const ConstReactionMap& scattering_reactions,
      const ConstReactionMap& absorption_reactions,
      const ConstReactionMap& miscellaneous_reactions,
      const Teuchos::RCP<const AtomicRelaxationModel> relaxation_model )
  : d_total_reaction( total_reaction ),
    d_total_absorption_reaction( total_absorption_reaction ),
    d_scattering_reactions( d_scattering_reactions ),
    d_absorption_reactions( absorption_reactions ),
    d_miscellaneous_reactions( miscellaneous_reactions ),
    d_relaxation_model( relaxation_model )
{
  // Make sure the total reaction is valid
  testPrecondition( !total_reaction.is_null() );
  // Make sure the absorption reaction is valid
  testPrecondition( !total_absorption_reaction.is_null() );
  // Make sure the scattering reactions map is valid
  testPrecondition( scattering_reactions.size() > 0 );  
  // Make sure the absorption reactions map is valid
  testPrecondition( absorption_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( !relaxation_model.is_null() );
}

//! Copy constructor
PhotoatomCore::PhotoatomCore( const PhotoatomCore& instance )
  : d_total_reaction( instance.d_total_reaction ),
    d_total_absorption_reaction( instance.total_absorption_reaction ),
    d_scattering_reactions( instance.d_scattering_reactions ),
    d_absorption_reactions( instance.d_absorption_reactions ),
    d_miscellaneous_reactions( instance.d_miscellaneous_reactions ),
    d_relaxation_model( instance.d_relaxation_model )
{
  // Make sure the total reaction is valid
  testPrecondition( !instance.d_total_reaction.is_null() );
  // Make sure the absorption reaction is valid
  testPrecondition( !instance.d_total_absorption_reaction.is_null() );
  // Make sure the scattering reactions map is valid
  testPrecondition( !instance.d_scattering_reactions.size() > 0 );  
  // Make sure the absorption reactions map is valid
  testPrecondition( !instance.d_absorption_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( !instance.d_relaxation_model.is_null() );
}

//! Assignment Operator
PhotoatomCore& PhotoatomCore::operator=( const PhotoatomCore& instance )
{
  // Make sure the total reaction is valid
  testPrecondition( !instance.d_total_reaction.is_null() );
  // Make sure the absorption reaction is valid
  testPrecondition( !instance.d_total_absorption_reaction.is_null() );
  // Make sure the scattering reactions map is valid
  testPrecondition( !instance.d_scattering_reactions.size() > 0 );  
  // Make sure the absorption reactions map is valid
  testPrecondition( !instance.d_absorption_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( !instance.d_relaxation_model.is_null() );

  // Avoid self-assignment
  if( this != &that )
  {
    d_total_reaction = instance.d_total_reaction;
    d_total_absorption_reaction = instance.d_total_absorption_reaction;
    d_scattering_reactions = instance.d_scattering_reactions;
    d_absorption_reactions = instance.d_absorption_reactions;
    d_relaxation_model = instance.d_relaxation_model;
  }
  
  return *this;
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomCore.cpp
//---------------------------------------------------------------------------//
