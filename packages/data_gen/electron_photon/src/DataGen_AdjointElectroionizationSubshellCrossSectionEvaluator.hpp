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
/*
  //! Constructor
  AdjointElectroionizationSubshellCrossSectionEvaluator(
    const double& binding_energy,
    const std::shared_ptr<ElectroionizationSubshellReaction>&
        electroionization_subshell_reaction,
    const std::shared_ptr<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>&
        knock_on_distribution );
*/
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
/*
  //! Evaluate the differential adjoint electroionization subshell cross section (dc/dx)
  double evaluateDifferentialCrossSection(
            const double incoming_energy,
            const double outgoing_energy ) const;

  //! Return the cross section value at a given energy
  double evaluateCrossSection( const double energy,
                               const double precision = 1e-6 ) const;

  //! Return the max outgoing adjoint energy for a given energy
  double getMaxOutgoingEnergyAtEnergy( const double energy );
*/
private:

  // The forward electroionization subshell reaction
  Teuchos::RCP<ElectroionizationSubshellReaction>
    d_electroionization_subshell_reaction;

  // The energies used as integration points
  std::vector<double> d_integration_points;

/*
  // The knock on energy distribution
  std::shared_ptr<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
                                         d_knock_on_distribution;

  // The subshell binding energy
  double d_binding_energy;*/
};

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_ELECTROIONIZATION_SUBSHELL_CROSS_SECTION_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectroionizationSubshellCrossSectionEvaluator.hpp
//---------------------------------------------------------------------------//
