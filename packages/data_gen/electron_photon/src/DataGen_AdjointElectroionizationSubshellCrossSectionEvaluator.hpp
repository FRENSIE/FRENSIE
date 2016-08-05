//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectroionizationSubshellCrossSectionEvaluator.hpp
//! \author Luke Kersting
//! \brief  Adjoint electroionization subshell cross section evaluator definition
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_ELECTROIONIZATION_SUBSHELL_CROSS_SECTION_EVALUATOR_HPP
#define DATA_GEN_ADJOINT_ELECTROIONIZATION_SUBSHELL_CROSS_SECTION_EVALUATOR_HPP

// FRENSIE Includes
#include "MonteCarlo_ElectroionizationSubshellElectroatomicReaction.hpp"


namespace DataGen{

//! The adjoint electroionization subshell cross section class
class AdjointElectroionizationSubshellCrossSectionEvaluator
{

public:

  //! Typedef for the electroionization subshell distribution
  typedef MonteCarlo::TwoDDistribution ElectroionizationSubshellDistribution;

  //! Typedef for the electroionization subshell reaction
  typedef MonteCarlo::ElectroionizationSubshellElectroatomicReaction<Utility::LinLin>
    ElectroionizationSubshellReaction;

  //! Typedef for the const electroionization subshell reaction
  typedef const ElectroionizationSubshellReaction
    ConstElectroionizationSubshellReaction;

  //! Constructor
  AdjointElectroionizationSubshellCrossSectionEvaluator(
    const std::shared_ptr<ElectroionizationSubshellReaction>&
        electroionization_subshell_reaction,
    const std::vector<double>& integration_points );

  //! Destructor
  ~AdjointElectroionizationSubshellCrossSectionEvaluator()
  { /* ... */ }

  //! Evaluate the adjoint PDF value
  double evaluateAdjointPDF(
        const double incoming_adjoint_energy,
        const double outgoing_adjoint_energy,
        const double precision = 1e-6 ) const;

  //! Evaluate the adjoint PDF value
  double evaluateAdjointPDF(
        const double adjoint_cross_section,
        const double incoming_adjoint_energy,
        const double outgoing_adjoint_energy,
        const double precision ) const;

  //! Return the cross section value at a given energy
  double evaluateAdjointCrossSection(
        const double adjoint_energy,
        const double precision = 1e-6 ) const;

private:

  // The forward electroionization subshell reaction
  std::shared_ptr<ElectroionizationSubshellReaction>
    d_electroionization_subshell_reaction;

  // The energies used as integration points
  std::vector<double> d_integration_points;
};

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_ELECTROIONIZATION_SUBSHELL_CROSS_SECTION_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectroionizationSubshellCrossSectionEvaluator.hpp
//---------------------------------------------------------------------------//
