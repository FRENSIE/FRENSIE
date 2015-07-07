//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectroionizationSubshellCrossSectionEvaluator.hpp
//! \author Luke Kersting
//! \brief  Adjoint electroionization subshell cross section evaluator definition
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_ELECTROIONIZATION_SUBSHELL_CROSS_SECTION_EVALUATOR_HPP
#define DATA_GEN_ADJOINT_ELECTROIONIZATION_SUBSHELL_CROSS_SECTION_EVALUATOR_HPP

// Boost Includes
#include <boost/scoped_ptr.hpp>
/*
// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/distribution.hpp>
#include <boost/bind.hpp>
*/
// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "MonteCarlo_ElectroionizationSubshellElectronScatteringDistribution.hpp"


namespace DataGen{

//! The adjoint electroionization subshell cross section class
class AdjointElectroionizationSubshellCrossSectionEvaluator
{
  
public:

  //! Typedef for the electroionization subshell distribution
  typedef Teuchos::Array<Utility::Pair<double,
		       Teuchos::RCP<const Utility::TabularOneDDistribution> > >
  ElectroionizationSubshellDistribution;

  //! Constructor
  AdjointElectroionizationSubshellCrossSectionEvaluator(
    const double& binding_energy,
    const Teuchos::RCP<MonteCarlo::ElectroatomicReaction>& 
                               electroionization_subshell_reaction,
    const Teuchos::RCP<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>&
                               knock_on_distribution );

  //! Destructor
  ~AdjointElectroionizationSubshellCrossSectionEvaluator()
  { /* ... */ }

  //! Evaluate the differential adjoint electroionization subshell cross section (dc/dx)
  double evaluateDifferentialCrossSection(
            const double incoming_energy, 
            const double outgoing_energy ) const;

  //! Return the cross section value at a given energy
  double evaluateCrossSection( const double energy, 
                               const double precision = 1e-6 ) const;

  //! Return the max outgoing adjoint energy for a given energy
  double getMaxOutgoingEnergyAtEnergy( const double energy );

private:

  // The forward reaction data
  Teuchos::RCP<MonteCarlo::ElectroatomicReaction> d_electroionization_subshell_reaction;

  // The knock on energy distribution
  Teuchos::RCP<const MonteCarlo::ElectroionizationSubshellElectronScatteringDistribution>
                                         d_knock_on_distribution;
  
  // The subshell binding energy
  double d_binding_energy;
};

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_ELECTROIONIZATION_SUBSHELL_CROSS_SECTION_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectroionizationSubshellCrossSectionEvaluator.hpp
//---------------------------------------------------------------------------//
