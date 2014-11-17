//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardPhotoatom.hpp
//! \author Alex Robinson
//! \brief  The standard photoatom class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_PHOTOATOM_HPP
#define MONTE_CARLO_STANDARD_PHOTOATOM_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_Photoatom.hpp"
#include "MonteCarlo_PhotoatomicReaction.hpp"
#include "MonteCarlo_AtomicRelaxationModel.hpp"
#include "MonteCarlo_PhotoatomicReactionType.hpp"

namespace MonteCarlo{

/*! The standard photoatom class
 * \details Use the InterpPolicy template parameter and the 
 * process_cross_section template parameter to customize the behavior of
 * this class. Raw cross section data from the EPDL library would use
 * a LogLog policy with processed_cross_section = false. Processed cross
 * section data from an ACE library would use a LogLog policy with
 * processed_cross_section = true. When data is processed, the policy is
 * used to indicate how the data was processed.
 */
template<typename InterpPolicy, bool processed_cross_section = true>
class StandardPhotoatom : public Photoatom
{
  
public:
  
  //! Constructor 
  StandardPhotoatom(
	  const std::string& name,
	  const unsigned atomic_number,
	  const Teuchos::ArrayRCP<double>& energy_grid,
	  const Photoatom::ReactionMap& standard_scattering_reactions,
	  const Photoatom::ReactionMap& standard_absorption_reactions,
	  const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model );

  //! Destructor
  ~StandardPhotoatom()
  { /* ... */ }

  //! Return the total cross section at the desired energy
  double getTotalCrossSection( const double energy ) const;

  //! Return the total absorption cross section at the desired energy
  double getAbsorptionCrossSection( const double energy ) const;

private:

  // Calculate the total absorption cross section
  void calculateTotalAbsorptionCrossSection();

  // Calculate the total cross section
  void calculateTotalCrossSection();

  // Return the cross section at the desired energy
  double getCrossSection( const double energy,
			  const Teuchos::Array<double>& cross_section,
			  const unsigned threshold_index ) const;

  // The processed incoming energy grid
  Teuchos::ArrayRCP<const double> d_energy_grid;

  // The processed microscopic total cross section
  Teuchos::Array<double> d_total_cross_section;

  // The processed microscopic absorption cross section
  Teuchos::Array<double> d_absorption_cross_section;

  // The total cross section threshold index
  unsigned d_total_threshold_energy_index;

  // The absorption cross section threshold index
  unsigned d_absorption_threshold_energy_index;
};

//! Partial template specialization for raw data
template<typename InterpPolicy>
class StandardPhotoatom<InterpPolicy,false> : public Photoatom
{
  //! Constructor 
  StandardPhotoatom(
	  const std::string& name,
	  const unsigned atomic_number,
	  const Teuchos::ArrayRCP<double>& energy_grid,
	  const Photoatom::ReactionMap& standard_scattering_reactions,
	  const Photoatom::ReactionMap& standard_absorption_reactions,
	  const Teuchos::RCP<AtomicRelaxationModel>& atomic_relaxation_model );

  //! Destructor
  ~StandardPhotoatom()
  { /* ... */ }

  //! Return the total cross section at the desired energy
  double getTotalCrossSection( const double energy ) const;

  //! Return the total absorption cross section at the desired energy
  double getAbsorptionCrossSection( const double energy ) const;

private:

  // Calculate the total absorption cross section
  void calculateTotalAbsorptionCrossSection();

  // Calculate the total cross section
  void calculateTotalCrossSection();

  // Return the cross section at the desired energy
  double getCrossSection( const double energy,
			  const Teuchos::Array<double>& cross_section ) const;

  // The raw incoming energy grid
  Teuchos::ArrayRCP<const double> d_energy_grid;

  // The raw microscopic total cross section
  Teuchos::Array<double> d_total_cross_section;

  // The raw microscopic absorption cross section
  Teuchos::Array<double> d_absorption_cross_section;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes.
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardPhotoatom_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_PHOTOATOM_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardPhotoatom.hpp
//---------------------------------------------------------------------------//
