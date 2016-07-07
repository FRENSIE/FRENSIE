//---------------------------------------------------------------------------//
//!
//! \file   DataGen_AdjointBremsstrahlungCrossSectionEvaluator.cpp
//! \author Luke Kersting
//! \brief  Adjoint bremsstrahlung cross section evaluator definition
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_AdjointBremsstrahlungCrossSectionEvaluator.hpp"
#include "MonteCarlo_StandardElectroatomicReaction.hpp"
#include "Utility_GaussKronrodIntegrator.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ContractException.hpp"

namespace DataGen{

// Constructor
AdjointBremsstrahlungCrossSectionEvaluator::AdjointBremsstrahlungCrossSectionEvaluator(
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    const Teuchos::ArrayRCP<const double>& electron_energy_grid,
    const Teuchos::ArrayRCP<const double>& bremsstrahlung_cross_section,
    const unsigned bremsstrahlung_threshold_energy_index,
    const BremsstrahlungDistribution& energy_loss_distribution )
  : d_grid_searcher( grid_searcher ),
    d_electron_energy_grid( electron_energy_grid ),
    d_bremsstrahlung_cross_section( bremsstrahlung_cross_section ),
    d_bremsstrahlung_threshold_energy_index( bremsstrahlung_threshold_energy_index ),
    d_energy_loss_distribution( energy_loss_distribution )
{
  // Make sure the grid searcher is valid
  testPrecondition( !d_grid_searcher.is_null() );
  // Make sure the electron energy grid is valid
  testPrecondition( electron_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						electron_energy_grid.begin(),
						electron_energy_grid.end() ) );
  // Make sure the cross section is valid
  testPrecondition( bremsstrahlung_cross_section.size() > 0 );
  testPrecondition( bremsstrahlung_cross_section.size() ==
		    electron_energy_grid.size() - bremsstrahlung_threshold_energy_index );
  // Make sure the threshold energy is valid
  testPrecondition( bremsstrahlung_threshold_energy_index < electron_energy_grid.size() );
  // Make sure the distribution is valid
  testPrecondition( d_energy_loss_distribution.size() > 0 );
}

// Evaluate the differential forward bremsstrahlung cross section (dc/dx)
double AdjointBremsstrahlungCrossSectionEvaluator::evaluateDifferentialCrossSection(
    const double incoming_energy,
    const double outgoing_energy ) const
{
  // Make sure the energies are valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( outgoing_energy <= incoming_energy );

  double outgoing_photon_energy = incoming_energy - outgoing_energy;

  // Evaluate the forward cross section at the incoming energy
  double forward_cs =
    MonteCarlo::StandardElectroatomicReaction<Utility::LinLin, false>::getCrossSection(
        incoming_energy,
        d_grid_searcher,
        d_electron_energy_grid,
        d_bremsstrahlung_cross_section,
        d_bremsstrahlung_threshold_energy_index );

  // Evaluate the energy loss distribution at a given incoming and outgoing energy
  double forward_pdf =
    MonteCarlo::evaluateTwoDDistributionCorrelatedPDF<BremsstrahlungDistribution, Utility::LinLog>(
                                     incoming_energy,
                                     outgoing_photon_energy,
                                     d_energy_loss_distribution );

  return forward_cs*forward_pdf;
}

// Return the adjoint cross section value at a given energy
double AdjointBremsstrahlungCrossSectionEvaluator::evaluateAdjointCrossSection(
    const double energy,
    const double precision ) const
{
  // Make sure the energies are valid
  testPrecondition( energy > 0.0 );

  Utility::long_float cross_section = Utility::long_float(0);

  // Create boost rapper function for the adjoint Bremsstahlung differential cross section
  boost::function<double (double x)> diff_adjoint_brem_wrapper =
    boost::bind<double>( &AdjointBremsstrahlungCrossSectionEvaluator::evaluateDifferentialCrossSection,
                         boost::cref( *this ),
                         _1,
                         energy );

  Utility::long_float cross_section_k, abs_error;

  Utility::GaussKronrodIntegrator<Utility::long_float>
    integrator( precision, 0.0, 1000, true );

  // Find the energy bin above the given energy
  BremsstrahlungDistribution::const_iterator lower_bin, upper_bin, end_bin;
  MonteCarlo::findLowerAndUpperBinBoundary<BremsstrahlungDistribution>(
    (energy + 1.0e-7),
	d_energy_loss_distribution,
    lower_bin,
    upper_bin );

  // Integrate from the given energy to the next highest energy bin (if necessary)
  if( lower_bin != upper_bin )
  {
    cross_section_k = Utility::long_float(0);
    abs_error = Utility::long_float(0);

    integrator.integrateAdaptively<15>(
        diff_adjoint_brem_wrapper,
        (Utility::long_float)(energy + 1.0e-7),
        (Utility::long_float)upper_bin->first,
        cross_section_k,
        abs_error );

    cross_section += cross_section_k;

    lower_bin = upper_bin;
    ++upper_bin;
  }
  else
  {
    ++upper_bin;
  }

  double max_energy = d_electron_energy_grid[d_electron_energy_grid.size()-1];
  // Find the upper boundary bin of the max adjoint electron energy on the forward bremsstrahlungn energy grid
  end_bin = Utility::Search::binaryUpperBound<Utility::FIRST>(
                        d_energy_loss_distribution.begin(),
                        d_energy_loss_distribution.end(),
                        max_energy );
std::cout << "energy = " << energy << std::endl;
  // Integrate through the energy bins above the given energy and below the max energy
  for ( upper_bin; upper_bin != end_bin; upper_bin++ )
  {
    cross_section_k = Utility::long_float(0);
    abs_error = Utility::long_float(0);
std::cout << "lower_bin->first = " << lower_bin->first << std::endl;
std::cout << "upper_bin->first = " << upper_bin->first << std::endl;
    integrator.integrateAdaptively<15>(
        diff_adjoint_brem_wrapper,
        (Utility::long_float)lower_bin->first,
        (Utility::long_float)upper_bin->first,
        cross_section_k,
        abs_error );

    lower_bin = upper_bin;

    cross_section += cross_section_k;
  }

  // Integrate from the last bin energy to the max energy (if necessary)
  if( upper_bin->first < max_energy )
  {
    cross_section_k = Utility::long_float(0);
    abs_error = Utility::long_float(0);
std::cout << "lower_bin->first = " << lower_bin->first << std::endl;
    // Integrate from the last bin to the max energy
    integrator.integrateAdaptively<15>(
        diff_adjoint_brem_wrapper,
        (Utility::long_float)lower_bin->first,
        (Utility::long_float)max_energy,
        cross_section_k,
        abs_error );
std::cout << "max_energy = " << max_energy << std::endl;
    cross_section += cross_section_k;
  }

  return (double) cross_section;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_AdjointBremsstrahlungCrossSectionEvaluator.cpp
//---------------------------------------------------------------------------//
