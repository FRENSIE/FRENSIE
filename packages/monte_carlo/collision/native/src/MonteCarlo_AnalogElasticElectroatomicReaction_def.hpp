//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_AnalogElasticElectroatomicReaction_def.hpp
//! \author Luke Kersting
//! \brief  The analog scattering elastic electroatomic reaction class def.
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ANALOG_ELASTIC_ELECTROATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_ANALOG_ELASTIC_ELECTROATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Basic Constructor
template<typename InterpPolicy, bool processed_cross_section>
AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::AnalogElasticElectroatomicReaction(
	  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	  const Teuchos::ArrayRCP<const double>& cutoff_cross_section,
	  const Teuchos::ArrayRCP<const double>& screened_rutherford_cross_section,
	  const unsigned cutoff_threshold_energy_index,
	  const unsigned screened_rutherford_threshold_energy_index,
      const Teuchos::RCP<const AnalogElasticElectronScatteringDistribution>&
            scattering_distribution )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
                                                    incoming_energy_grid,
                                                    cutoff_cross_section,
                                                    cutoff_threshold_energy_index ),
    d_cutoff_cross_section( cutoff_cross_section ),
    d_screened_rutherford_cross_section( screened_rutherford_cross_section ),
    d_cutoff_threshold_energy_index( cutoff_threshold_energy_index ),
    d_screened_rutherford_threshold_energy_index( screened_rutherford_threshold_energy_index ),
    d_scattering_distribution( scattering_distribution )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  // Make sure the cross sections are valid
  testPrecondition( cutoff_cross_section.size() > 0 );
  testPrecondition( cutoff_cross_section.size() ==
    incoming_energy_grid.size() - cutoff_threshold_energy_index );
  testPrecondition( screened_rutherford_cross_section.size() > 0 );
  testPrecondition( screened_rutherford_cross_section.size() ==
    incoming_energy_grid.size() - screened_rutherford_threshold_energy_index );
  // Make sure the threshold energies are valid
  testPrecondition( cutoff_threshold_energy_index <
                    incoming_energy_grid.size() );
  testPrecondition( screened_rutherford_threshold_energy_index <
                    incoming_energy_grid.size() );
  // Make sure scattering distribution is valid
  testPrecondition( !scattering_distribution.is_null() );
}

// Constructor
template<typename InterpPolicy, bool processed_cross_section>
AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::AnalogElasticElectroatomicReaction(
	  const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	  const Teuchos::ArrayRCP<const double>& cutoff_cross_section,
	  const Teuchos::ArrayRCP<const double>& screened_rutherford_cross_section,
	  const unsigned cutoff_threshold_energy_index,
	  const unsigned screened_rutherford_threshold_energy_index,
      const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher,
      const Teuchos::RCP<const AnalogElasticElectronScatteringDistribution>&
            scattering_distribution )
  : StandardElectroatomicReaction<InterpPolicy,processed_cross_section>(
        incoming_energy_grid,
        cutoff_cross_section,
        cutoff_threshold_energy_index,
        grid_searcher ),
    d_cutoff_cross_section( cutoff_cross_section ),
    d_screened_rutherford_cross_section( screened_rutherford_cross_section ),
    d_cutoff_threshold_energy_index( cutoff_threshold_energy_index ),
    d_screened_rutherford_threshold_energy_index( screened_rutherford_threshold_energy_index ),
    d_scattering_distribution( scattering_distribution )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
						incoming_energy_grid.begin(),
						incoming_energy_grid.end() ) );
  // Make sure the cross sections are valid
  testPrecondition( cutoff_cross_section.size() > 0 );
  testPrecondition( cutoff_cross_section.size() ==
    incoming_energy_grid.size() - cutoff_threshold_energy_index );
  testPrecondition( screened_rutherford_cross_section.size() > 0 );
  testPrecondition( screened_rutherford_cross_section.size() ==
    incoming_energy_grid.size() - screened_rutherford_threshold_energy_index );
  // Make sure the threshold energies are valid
  testPrecondition( cutoff_threshold_energy_index <
                    incoming_energy_grid.size() );
  testPrecondition( screened_rutherford_threshold_energy_index <
                    incoming_energy_grid.size() );
  // Make sure scattering distribution is valid
  testPrecondition( !scattering_distribution.is_null() );
  // Make sure the grid searcher is valid
  testPrecondition( !grid_searcher.is_null() );
}

// Return the number of photons emitted from the rxn at the given energy
/*! \details This does not include photons from atomic relaxation.
 */
template<typename InterpPolicy, bool processed_cross_section>
unsigned AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedPhotons( const double energy ) const
{
  return 0u;
}

// Return the number of electrons emitted from the rxn at the given energy
template<typename InterpPolicy, bool processed_cross_section>
unsigned AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getNumberOfEmittedElectrons( const double energy ) const
{
  return 0u;
}

// Return the reaction type
template<typename InterpPolicy, bool processed_cross_section>
ElectroatomicReactionType AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getReactionType() const
{
  return ANALOG_ELASTIC_ELECTROATOMIC_REACTION;
}

// Simulate the reaction
template<typename InterpPolicy, bool processed_cross_section>
void AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::react(
				     ElectronState& electron,
				     ParticleBank& bank,
				     Data::SubshellType& shell_of_interaction ) const
{
  d_scattering_distribution->scatterElectron( electron,
                                              bank,
                                              shell_of_interaction);

  electron.incrementCollisionNumber();

  // The shell of interaction is currently ignored
  shell_of_interaction =Data::UNKNOWN_SUBSHELL;
}


// Return the cross section at the given energy
template<typename InterpPolicy, bool processed_cross_section>
double AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
    const double energy ) const
{
  // Get the screened Rutherford cross section
  double screened_rutherford_cross_section =
    this->getScreenedRutherfordCrossSection( energy );

  // Get the cutoff cross section
  double cutoff_cross_section =
    this->getCutoffCrossSection( energy );

  return screened_rutherford_cross_section + cutoff_cross_section;
}

// Return the cross section at the given energy (efficient)
template<typename InterpPolicy, bool processed_cross_section>
double AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
    const double energy,
    const unsigned bin_index ) const
{
  // Get the screened Rutherford cross section
  double screened_rutherford_cross_section =
    this->getScreenedRutherfordCrossSection( energy, bin_index );

  // Get the cutoff cross section
  double cutoff_cross_section =
    this->getCutoffCrossSection( energy, bin_index );

  return screened_rutherford_cross_section + cutoff_cross_section;
}

// Return the cutoff cross section at the given energy
template<typename InterpPolicy, bool processed_cross_section>
double AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getCutoffCrossSection(
    const double energy ) const
{
  double cross_section;

  cross_section =
    StandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
        energy );

  return cross_section;
}

template<typename InterpPolicy, bool processed_cross_section>
double AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getCutoffCrossSection(
    const double energy,
    const unsigned bin_index ) const
{
  double cross_section;

  cross_section =
    StandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
        energy,
        bin_index );

  return cross_section;
}

template<typename InterpPolicy, bool processed_cross_section>
double AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getScreenedRutherfordCrossSection(
    const double energy ) const
{
  double cross_section;

  cross_section =
    StandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
        energy,
        d_screened_rutherford_cross_section,
        d_screened_rutherford_threshold_energy_index );

  return cross_section;
}

template<typename InterpPolicy, bool processed_cross_section>
double AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getScreenedRutherfordCrossSection(
    const double energy,
    const unsigned bin_index ) const
{
  double cross_section;

  cross_section =
    StandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getCrossSection(
        energy,
        bin_index,
        d_screened_rutherford_cross_section,
        d_screened_rutherford_threshold_energy_index );

  return cross_section;
}

// Return the threshold energy
template<typename InterpPolicy, bool processed_cross_section>
double AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getThresholdEnergy() const
{
  if ( d_cutoff_threshold_energy_index <= d_screened_rutherford_threshold_energy_index )
  {
    return this->getCutoffThresholdEnergy();
  }
  else
  {
    return this->getScreenedRutherfordThresholdEnergy();
  }
}

// Return the cutoff threshold energy
template<typename InterpPolicy, bool processed_cross_section>
double AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getCutoffThresholdEnergy() const
{
  return StandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getThresholdEnergy(
    d_cutoff_threshold_energy_index );
}

// Return the screened Rutherford threshold energy
template<typename InterpPolicy, bool processed_cross_section>
double AnalogElasticElectroatomicReaction<InterpPolicy,processed_cross_section>::getScreenedRutherfordThresholdEnergy() const
{
  return StandardElectroatomicReaction<InterpPolicy,processed_cross_section>::getThresholdEnergy(
    d_screened_rutherford_threshold_energy_index );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ANALOG_ELASTIC_ELECTROATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_AnalogElasticElectroatomicReaction_def.hpp
//---------------------------------------------------------------------------//
