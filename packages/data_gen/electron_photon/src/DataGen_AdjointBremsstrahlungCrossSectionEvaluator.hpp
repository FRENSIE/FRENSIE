//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointBremsstrahlungCrossSectionEvaluator.hpp
//! \author Luke Kersting
//! \brief  Adjoint bremsstrahlung cross section evaluator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_BREMSSTRAHLUNG_CROSS_SECTION_EVALUATOR_HPP
#define DATA_GEN_ADJOINT_BREMSSTRAHLUNG_CROSS_SECTION_EVALUATOR_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_StandardElectroatomicReaction.hpp"
#include "MonteCarlo_TwoDDistributionHelpers.hpp"
#include "Utility_OneDDistribution.hpp"
//#include "Utility_TabularOneDDistribution.hpp"


namespace DataGen{

//! The adjoint bremsstrahlung cross section class
class AdjointBremsstrahlungCrossSectionEvaluator
{

public:

  //! Typedef for the bremsstrahlung distribution
  typedef MonteCarlo::TwoDDistribution BremsstrahlungDistribution;

  //! Constructor
  AdjointBremsstrahlungCrossSectionEvaluator(
    const std::shared_ptr<MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> >&
        bremsstrahlung_reaction,
    const std::vector<double>& integration_points );

  //! Destructor
  ~AdjointBremsstrahlungCrossSectionEvaluator()
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

  // The forward bremsstrahlung reaction
  std::shared_ptr<MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin> >
    d_bremsstrahlung_reaction;

  // The energy used as integration points
  std::vector<double> d_integration_points;
};

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_BREMSSTRAHLUNG_CROSS_SECTION_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointBremsstrahlungCrossSectionEvaluator.hpp
//---------------------------------------------------------------------------//
