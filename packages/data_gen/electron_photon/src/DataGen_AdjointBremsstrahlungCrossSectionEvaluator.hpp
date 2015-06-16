//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointBremsstrahlungCrossSectionEvaluator.hpp
//! \author Luke Kersting
//! \brief  Adjoint bremsstrahlung cross section evaluator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_BREMSSTRAHLUNG_CROSS_SECTION_EVALUATOR_HPP
#define DATA_GEN_ADJOINT_BREMSSTRAHLUNG_CROSS_SECTION_EVALUATOR_HPP

// Boost Includes
#include <boost/scoped_ptr.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"

namespace DataGen{

//! The adjoint bremsstrahlung cross section class
class AdjointBremsstrahlungCrossSectionEvaluator
{
  
public:

  //! Typedef for the bremsstrahlung distribution
  typedef Teuchos::Array<Utility::Pair<double,
		       Teuchos::RCP<const Utility::TabularOneDDistribution> > >
  BremsstrahlungDistribution;

  //! Constructor
  AdjointBremsstrahlungCrossSectionEvaluator(
    const Teuchos::RCP<const Utility::OneDDistribution>& forward_cross_sections,
    const BremsstrahlungDistribution& energy_loss_function );

  //! Destructor
  ~AdjointBremsstrahlungCrossSectionEvaluator()
  { /* ... */ }

  //! Evaluate the differential adjoint bremsstrahlung cross section (dc/dx)
  double evaluateDifferentialCrossSection(
	  const double incoming_energy, 
          const double outgoing_energy ) const;

  //! Return the cross section value at a given energy
  double evaluateCrossSection( const double energy, 
			       const double precision = 1e-6 ) const;

private:

  // The forward cross section table ( simga(E) )
  Teuchos::RCP<const Utility::OneDDistribution> d_forward_cross_sections;

  // The energy loss function
  BremsstrahlungDistribution d_energy_loss_function;
};

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_BREMSSTRAHLUNG_CROSS_SECTION_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointBremsstrahlungCrossSectionEvaluator.hpp
//---------------------------------------------------------------------------//
