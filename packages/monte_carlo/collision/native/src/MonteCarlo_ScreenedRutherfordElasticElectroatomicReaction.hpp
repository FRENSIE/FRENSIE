//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ScreenedRutherfordElasticElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The screened rutherford scattering elastic electroatomic reaction class decl.
//! 
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_StandardElectroatomicReaction.hpp"
#include "MonteCarlo_ScreenedRutherfordElasticElectronScatteringDistribution.hpp"

namespace MonteCarlo{

//! \todo Write Unit Test once ENDL Data is available
//! The screened rutherford elastic electroatomic reaction class
template<typename InterpPolicy, bool processed_cross_section = false>
class ScreenedRutherfordElasticElectroatomicReaction : public StandardElectroatomicReaction<InterpPolicy,processed_cross_section>
{

public:

  //! Basic Constructor
  ScreenedRutherfordElasticElectroatomicReaction( 
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
            scattering_distribution,
    const double upper_cutoff_angle = 1.0e-6 );

  //! Constructor
  ScreenedRutherfordElasticElectroatomicReaction( 
    const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
    const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<Utility::HashBasedGridSearcher>& grid_searcher,
    const Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution>&
            scattering_distribution,
    const double upper_cutoff_angle = 1.0e-6 );


  //! Destructor
  ~ScreenedRutherfordElasticElectroatomicReaction()
  { /* ... */ }

  //! Return the number of electrons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedElectrons( const double energy ) const;

  //! Return the number of photons emitted from the rxn at the given energy
  unsigned getNumberOfEmittedPhotons( const double energy ) const;

  //! Return the reaction type
  ElectroatomicReactionType getReactionType() const;

  //! Simulate the reaction
  void react( ElectronState& electron, 
              ParticleBank& bank,
              Data::SubshellType& shell_of_interaction ) const;

private:


  // The screened rutherford_elastic scattering distribution
  Teuchos::RCP<const ScreenedRutherfordElasticElectronScatteringDistribution> 
    d_scattering_distribution;

  // The incoming energy grid
  Teuchos::ArrayRCP<const double> d_incoming_energy_grid;

  // The cross section values evaluated on the incoming energy grid
  Teuchos::ArrayRCP<const double> d_cross_section;

  // The threshold energy
  const unsigned d_threshold_energy_index;

  // The upper cutoff angle above which screened rutherford is used
  double d_upper_cutoff_angle;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_ScreenedRutherfordElasticElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_SCREENED_RUTHERFORD_ELASTIC_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ScreenedRutherfordElasticElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
