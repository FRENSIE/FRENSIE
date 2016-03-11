//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardElectroatomicReaction.hpp
//! \author Luke Kersting
//! \brief  The standard Electroatomic reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_ELECTROATOMIC_REACTION_HPP
#define MONTE_CARLO_STANDARD_ELECTROATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_HashBasedGridSearcher.hpp"

namespace MonteCarlo{

/*! The standard Electroatomic reaction base class
 * \details Use the InterpPolicy template parameter and the
 * processed_cross_section template parameter to customize the behavior of
 * this class. Raw cross section data from a EPR library would use a LinLin 
 * policy with processed_cross_section = false. When data is processed, 
 * the policy is used to indicate how the data was processed.
 */
template<typename InterpPolicy, bool processed_cross_section>
class StandardElectroatomicReaction : public ElectroatomicReaction
{

public:

  //! Basic Constructor
  StandardElectroatomicReaction( 
	const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	const Teuchos::ArrayRCP<const double>& cross_section,
	const unsigned threshold_energy_index );

  //! Constructor
  StandardElectroatomicReaction( 
	const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	const Teuchos::ArrayRCP<const double>& cross_section,
	const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher );

  //! Destructor
  virtual ~StandardElectroatomicReaction()
  { /* ... */ }


  //! Test if the energy falls within the energy grid
  bool isEnergyWithinEnergyGrid( const double energy ) const;

  //! Return the cross section at the given energy
  double getCrossSection( const double energy ) const;

  //! Return the cross section at the given energy (efficient)
  double getCrossSection( const double energy,
                          const unsigned bin_index ) const;

  //! Return the threshold energy
  double getThresholdEnergy() const;


protected:

  //! Return the head of the energy grid
  const double* getEnergyGridHead() const;

private:

  // The incoming energy grid
  Teuchos::ArrayRCP<const double> d_incoming_energy_grid;

  // The cross section values evaluated on the incoming energy grid
  Teuchos::ArrayRCP<const double> d_cross_section;

  // The threshold energy
  unsigned d_threshold_energy_index;

  // The hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> d_grid_searcher;
};

//! Partial template specialization for raw data
template<typename InterpPolicy>
class StandardElectroatomicReaction<InterpPolicy,true> : public ElectroatomicReaction
{
  public:

  //! Basic Constructor
  StandardElectroatomicReaction( 
	const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	const Teuchos::ArrayRCP<const double>& cross_section,
	const unsigned threshold_energy_index );

  //! Constructor
  StandardElectroatomicReaction( 
	const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	const Teuchos::ArrayRCP<const double>& cross_section,
    const unsigned threshold_energy_index,
    const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher );


  //! Destructor
  virtual ~StandardElectroatomicReaction()
  { /* ... */ }

//! Test if the energy falls within the energy grid
  bool isEnergyWithinEnergyGrid( const double energy ) const;

  //! Return the cross section at the given energy
  double getCrossSection( const double energy ) const;

  //! Return the cross section at the given energy (efficient)
  double getCrossSection( const double energy,
			  const unsigned bin_index ) const;

  //! Return the threshold energy
  double getThresholdEnergy() const;

protected:

  //! Return the head of the energy grid
  const double* getEnergyGridHead() const;

private:

  // The incoming energy grid (logarithms)
  Teuchos::ArrayRCP<const double> d_incoming_energy_grid;

  // The cross section values evaluated on the incoming energy grid
  Teuchos::ArrayRCP<const double> d_cross_section;

  // The threshold energy
  const unsigned d_threshold_energy_index;

  // The hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> d_grid_searcher;
};



} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardElectroatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_ELECTROATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardElectroatomicReaction.hpp
//---------------------------------------------------------------------------//
