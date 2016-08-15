//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointElectronCrossSectionEvaluator.hpp
//! \author Luke Kersting
//! \brief  Adjoint electron cross section evaluator definition
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_ELECTRON_CROSS_SECTION_EVALUATOR_HPP
#define DATA_GEN_ADJOINT_ELECTRON_CROSS_SECTION_EVALUATOR_HPP

namespace DataGen{

//! The adjoint electron cross section evaluator class
template<typename ElectroatomicReaction>
class AdjointElectronCrossSectionEvaluator
{

public:

  // Boost integrator state type
  typedef std::vector<long double> state_type;

  //! Typedef for the const electroatomic reaction
  typedef const ElectroatomicReaction
    ConstElectroatomicReaction;

  //! Constructor
  AdjointElectronCrossSectionEvaluator(
    const std::shared_ptr<ElectroatomicReaction>&
        electroatomic_reaction,
    const std::vector<double>& integration_points );

  //! Destructor
  ~AdjointElectronCrossSectionEvaluator()
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
        
  //! Return the cross section value at a given energy
  template <typename BoostIntegrator>
  double evaluateAdjointCrossSectionUsingBoost(
        const double adjoint_energy,
        const BoostIntegrator integrator ) const;

private:

  // Return the differential cross section at a given energy
  void getDifferentialCrossSection(
        const state_type& initial_value,
        state_type& differential_cross_section,
        const double outgoing_adjoint_energy,
        const double incoming_adjoint_energy ) const;

  // Observer, prints time and state when called (during integration)
  static void observer( const state_type& x, const double t );

  // The forward electroionization subshell reaction
  std::shared_ptr<ElectroatomicReaction>
    d_electroatomic_reaction;

  // The energies used as integration points
  std::vector<double> d_integration_points;
};

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_AdjointElectronCrossSectionEvaluator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_ADJOINT_ELECTRON_CROSS_SECTION_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointElectronCrossSectionEvaluator.hpp
//---------------------------------------------------------------------------//
