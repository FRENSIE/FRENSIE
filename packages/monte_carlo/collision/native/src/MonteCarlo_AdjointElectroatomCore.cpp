//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AdjointElectroatomCore.cpp
//! \author Luke Kersting
//! \brief  The adjoint electroatom core class definition.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "MonteCarlo_AdjointElectroatomCore.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Initialize the static member data
const boost::unordered_set<AdjointElectroatomicReactionType>
AdjointElectroatomCore::scattering_reaction_types =
  AdjointElectroatomCore::setDefaultScatteringReactionTypes();

// Set the default scattering reaction types
boost::unordered_set<AdjointElectroatomicReactionType>
AdjointElectroatomCore::setDefaultScatteringReactionTypes()
{
  boost::unordered_set<AdjointElectroatomicReactionType> tmp_scattering_reaction_types;
  tmp_scattering_reaction_types.insert(
                  ANALOG_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  HYBRID_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  CUTOFF_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  SCREENED_RUTHERFORD_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  MOMENT_PRESERVING_ELASTIC_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  BREMSSTRAHLUNG_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  ATOMIC_EXCITATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  TOTAL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  K_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  L1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  L2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  L3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  M1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  M2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  M3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  M4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  M5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  N1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  N2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  N3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  N4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  N5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  N6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  N7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  O1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  O2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  O3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  O4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  O5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  O6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  O7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  O8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  O9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  P1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  P2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  P3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  P4_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  P5_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  P6_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  P7_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  P8_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  P9_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                 P10_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                 P11_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  Q1_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  Q2_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );
  tmp_scattering_reaction_types.insert(
                  Q3_SUBSHELL_ELECTROIONIZATION_ADJOINT_ELECTROATOMIC_REACTION );

  return tmp_scattering_reaction_types;
}

// Default constructor
AdjointElectroatomCore::AdjointElectroatomCore()
  : d_total_reaction(),
    d_total_absorption_reaction(),
    d_scattering_reactions(),
    d_absorption_reactions(),
    d_miscellaneous_reactions(),
    d_relaxation_model()
{ /* ... */ }

// Advanced constructor
/*! \details It is assumed that the scattering, absorption and miscellaneous
 * reactions have already been organized appropriately. The total and total
 * absorption cross sections should have been created from the scattering
 * and absorption reactions.
 */
AdjointElectroatomCore::AdjointElectroatomCore(
      const std::shared_ptr<const AdjointElectroatomicReaction>& total_reaction,
      const std::shared_ptr<const AdjointElectroatomicReaction>& total_absorption_reaction,
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
  testPrecondition( total_reaction.use_count() > 0 );
  // Make sure the absorption reaction is valid
  testPrecondition( total_absorption_reaction.use_count() > 0 );
  // Make sure the scattering reactions map is valid
  testPrecondition( scattering_reactions.size() > 0 );
  // Make sure the absorption reactions map is valid
  testPrecondition( absorption_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( !relaxation_model.is_null() );
}

//! Copy constructor
AdjointElectroatomCore::AdjointElectroatomCore( const AdjointElectroatomCore& instance )
  : d_total_reaction( instance.d_total_reaction ),
    d_total_absorption_reaction( instance.d_total_absorption_reaction ),
    d_scattering_reactions( instance.d_scattering_reactions ),
    d_absorption_reactions( instance.d_absorption_reactions ),
    d_miscellaneous_reactions( instance.d_miscellaneous_reactions ),
    d_relaxation_model( instance.d_relaxation_model )
{
  // Make sure the total reaction is valid
  testPrecondition( instance.d_total_reaction.use_count() > 0 );
  // Make sure the absorption reaction is valid
  testPrecondition( instance.d_total_absorption_reaction.use_count() > 0 );
  // Make sure the scattering and absorption reaction maps are valid
  testPrecondition( instance.d_scattering_reactions.size() +
                    instance.d_absorption_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( !instance.d_relaxation_model.is_null() );
}

//! Assignment Operator
AdjointElectroatomCore& AdjointElectroatomCore::operator=( const AdjointElectroatomCore& instance )
{
  // Make sure the total reaction is valid
  testPrecondition( instance.d_total_reaction.use_count() > 0 );
  // Make sure the absorption reaction is valid
  testPrecondition( instance.d_total_absorption_reaction.use_count() > 0 );
  // Make sure the scattering and absorption reaction maps are valid
  testPrecondition( instance.d_scattering_reactions.size() +
                    instance.d_absorption_reactions.size() > 0 );
  // Make sure the relaxation model is valid
  testPrecondition( !instance.d_relaxation_model.is_null() );

  // Avoid self-assignment
  if( this != &instance )
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
// end MonteCarlo_AdjointElectroatomCore.cpp
//---------------------------------------------------------------------------//

