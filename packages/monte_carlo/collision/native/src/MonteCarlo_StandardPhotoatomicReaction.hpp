//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardPhotoatomicReaction.hpp
//! \author Alex Robinson
//! \brief  The standard photoatomic reaction base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PHOTOATOMIC_REACTION_HPP
#define MONTE_CARLO_STANDARD_PHOTOATOMIC_REACTION_HPP

// Trilinos Includes
#include <Teuchos_ArrayRCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_PhotonState.hpp"
#include "MonteCarlo_ParticleBank.hpp"
#include "Utility_HashBasedGridSearcher.hpp"

namespace MonteCarlo{

/*! The standard photoatomic reaction base class
 * \details Use the InterpPolicy template parameter and the
 * processed_cross_section template parameter to customize the behavior of
 * this class. Raw cross section data from the EPDL library would use
 * a LogLog policy with processed_cross_section = false. Processed cross
 * section data from an ACE library would use a LogLog policy with
 * processed_cross_section = true. When data is processed, the policy is used
 * to indicate how the data was processed.
 */
template<typename InterpPolicy, bool processed_cross_section>
class StandardPhotoatomicReaction : public PhotoatomicReaction
{

public:

  //! Basic constructor
  StandardPhotoatomicReaction(
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const unsigned threshold_energy_index );

  //! Constructor
  StandardPhotoatomicReaction( 
     const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
     const Teuchos::ArrayRCP<const double>& cross_section,
     const unsigned threshold_energy_index,
     const Teuchos::RCP<const Utility::HashBasedGridSearcher>& grid_searcher );

  //! Destructor
  virtual ~StandardPhotoatomicReaction()
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

  // The processed incoming energy grid
  Teuchos::ArrayRCP<const double> d_incoming_energy_grid;

  // The processed cross section values evaluated on the incoming e. grid 
  Teuchos::ArrayRCP<const double> d_cross_section;

  // The threshold energy
  unsigned d_threshold_energy_index;
  
  // The hash-based grid searcher
  Teuchos::RCP<const Utility::HashBasedGridSearcher> d_grid_searcher;
};

//! Partial template specialization for raw data
template<typename InterpPolicy>
class StandardPhotoatomicReaction<InterpPolicy,false> : public PhotoatomicReaction
{
public:

  //! Typedef for the hash-based grid searcher
  typedef Utility::HashBasedGridSearcher<Teuchos::ArrayRCP<const double>,false>
  HashBasedGridSearcher;

  //! Basic constructor
  StandardPhotoatomicReaction( 
		   const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
		   const Teuchos::ArrayRCP<const double>& cross_section,
		   const unsigned threshold_energy_index );

  //! Constructor
  StandardPhotoatomicReaction( 
	      const Teuchos::ArrayRCP<const double>& incoming_energy_grid,
	      const Teuchos::ArrayRCP<const double>& cross_section,
	      const unsigned threshold_energy_index,
	      const Teuchos::RCP<const HashBasedGridSearcher>& grid_searcher );

  //! Destructor
  virtual ~StandardPhotoatomicReaction()
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
  const unsigned d_threshold_energy_index;

  // The hash-based grid searcher
  Teuchos::RCP<const HashBasedGridSearcher> d_grid_searcher;
};


} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardPhotoatomicReaction_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_PHOTOATOMIC_REACTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardPhotoatomicReaction.hpp
//---------------------------------------------------------------------------//
