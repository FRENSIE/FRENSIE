//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointIncoherentCrossSectionEvaluator.hpp
//! \author Alex Robinson
//! \brief  Adjoint incoherent cross section declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ADJOINT_INCOHERENT_CROSS_SECTION_EVALUATOR_HPP
#define DATA_GEN_ADJOINT_INCOHERENT_CROSS_SECTION_EVALUATOR_HPP

// Boost Includes
#include <boost/scoped_ptr.hpp>

// FRENSIE Includes
#include "Utility_OneDDistribution.hpp"
#include "Utility_AdjointKleinNishinaDistribution.hpp"
#include "Utility_GaussKronrodQuadratureKernel.hpp"

namespace DataGen{

//! The adjoint incoherent cross section class
class AdjointIncoherentCrossSectionEvaluator
{
  
public:

  //! Return the energy of the max cross section value
  static double getEnergyOfMaxCrossSection( const double max_energy );

  /*! Check if the energy corresponds to the max cross section value at any
   * max energy
   */
  static double doesEnergyCorrespondToAMaxCrossSectionValue( 
							 const double energy );

  //! Return the max energy that results in a max cross section value at energy
  static double getMaxEnergyResultingInMaxCrossSectionValueAtEnergy( 
						         const double energy );

  //! Default constructor
  AdjointIncoherentCrossSectionEvaluator();

  //! Constructor
  AdjointIncoherentCrossSectionEvaluator(
    const Teuchos::RCP<const Utility::OneDDistribution>& scattering_function );

  //! Destructor
  ~AdjointIncoherentCrossSectionEvaluator()
  { /* ... */ }

  //! Return the cross section value at a given energy and max energy
  double evaluateCrossSection( const double energy, 
			       const double max_energy ) const;

private:

  // Evaluate the differential adjoint incoherent cross section (dc/dx)
  double evaluateDifferentialAdjointIncoherentCrossSection(
	  const double inverse_energy_gain_ratio, 
	  const Utility::AdjointKleinNishinaDistribution& distribution ) const;

  // The scattering function
  Teuchos::RCP<const Utility::OneDDistribution> d_scattering_function;

  // The quadrature kernel
  boost::scoped_ptr<Utility::GaussKronrodQuadratureKernel> d_quadrature_kernel;
};

} // end DataGen namespace

#endif // end DATA_GEN_ADJOINT_INCOHERENT_CROSS_SECTION_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_AdjointIncoherentCrossSectionEvaluator.hpp
//---------------------------------------------------------------------------//
