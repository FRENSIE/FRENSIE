//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardReactionBaseImpl.hpp
//! \author Alex Robinson
//! \brief  The standard generic atomic reaction class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_REACTION_BASE_IMPL_HPP
#define MONTE_CARLO_STANDARD_REACTION_BASE_IMPL_HPP

// Std Lib Includes
#include <memory>
#include <functional>

// FRENSIE Includes
#include "Utility_Vector.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_HashBasedGridSearcher.hpp"

namespace MonteCarlo{

/*! The standard reaction base impl
 * \details This class inherits from the desired base class and implements
 * some standard features that are used by many reaction classes (
 * e.g. MonteCarlo::PhotoatomicReaction, MonteCarlo::NuclearReaction, etc.).
 * Use the InterpPolicy template parameter and the processed_cross_section
 * template parameter to customize the behavior of this class. Raw cross
 * section data from the EPDL library would use the Utility::LogLog policy with
 * processed_cross_section = false. Processed cross section data from an
 * ACE photon library would use the Utility::LogLog policy with
 * processed_cross_section = true. Cross section data from a ACE neutron
 * library or a native library would use Utility::LinLin with
 * processed_cross_section = false.
 */
template<typename ReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
class StandardReactionBaseImpl : public ReactionBase
{

public:

  //! Basic constructor
  StandardReactionBaseImpl(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index );

  //! Constructor
  StandardReactionBaseImpl(
     const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
     const std::shared_ptr<const std::vector<double> >& cross_section,
     const size_t threshold_energy_index,
     const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
     grid_searcher );

  //! Destructor
  virtual ~StandardReactionBaseImpl()
  { /* ... */ }

  //! Test if the energy falls within the energy grid
  bool isEnergyWithinEnergyGrid( const double energy ) const final override;

  //! Return the cross section at the given energy
  virtual double getCrossSection( const double energy ) const override;

  //! Return the cross section at the given energy (efficient)
  virtual double getCrossSection( const double energy,
                                  const size_t bin_index ) const override;

  //! Return the max energy
  double getMaxEnergy() const final override;

  //! Return the threshold energy
  double getThresholdEnergy() const final override;

protected:

  //! Return the head of the energy grid
  const double* getEnergyGridHead() const final override;

  //! Return the cross section at the given energy
  double getCrossSectionImpl( const std::vector<double>& cross_section,
                              const double energy,
                              const size_t bin_index ) const;

  // Set the max energy index manually
  void setMaxEnergyIndex( const size_t max_energy_index );

private:

  // Set the max energy index
  void setMaxEnergyIndex();

  // Set the get cross section first bin implementation method
  void setGetCrossSectionFirstBinMethod();

  // The processed incoming energy grid
  std::shared_ptr<const std::vector<double> > d_incoming_energy_grid;

  // The processed cross section values evaluated on the incoming e. grid
  std::shared_ptr<const std::vector<double> > d_cross_section;

  // The threshold energy index
  size_t d_threshold_energy_index;

  // The max energy index
  size_t d_max_energy_index;

  // The hash-based grid searcher
  std::shared_ptr<const Utility::HashBasedGridSearcher<double> >
  d_grid_searcher;

  // The get cross section first bin method
  std::function<double(const double,const double,const double,const double,const double)>
  d_get_cross_section_first_bin_impl;
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_StandardReactionBaseImpl_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_STANDARD_REACTION_BASE_IMPL_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardReactionBaseImpl.hpp
//---------------------------------------------------------------------------//

