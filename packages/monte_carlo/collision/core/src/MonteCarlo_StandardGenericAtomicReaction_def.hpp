//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardGenericAtomicReaction_def.hpp
//! \author Alex Robinson
//! \brief  The standard generic atomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_GENERIC_ATOMIC_REACTION_DEF_HPP
#define MONTE_CARLO_GENERIC_ATOMIC_REACTION_DEF_HPP

// FRENSIE Includes
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

/*! \brief The standard generic atomic reaction helper class for processed
 * cross sections
 * \details This helper class should only be used by the
 * MonteCarlo::StandardGenericAtomicReaction class.
 */
template<typename InterpPolicy, bool processed_cross_section>
struct StandardGenericAtomicReactionHelper
{
  //! Calculate the interpolated cross section
  static inline double calculateInterpolatedCrossSection(
                                                 const double energy_0,
                                                 const double energy_1,
                                                 const double raw_energy,
                                                 const double cross_section_0,
                                                 const double cross_section_1 )
  {
    const double processed_slope =
      (cross_section_1 - cross_section_0)/(energy_1 - energy_0);

    return InterpPolicy::interpolate(
                                   energy_0,
                                   InterpPolicy::processIndepVar( raw_energy ),
                                   cross_section_0,
                                   processed_slope );
  }

  //! Return the energy of interest
  static inline double returnEnergyOfInterest( const double processed_energy )
  {
    return InterpPolicy::recoverProcessedIndepVar( processed_energy );
  }

  //! Return the cross section of interest
  static inline double returnCrossSectionOfInterest( const double processed_cs )
  {
    return InterpPolicy::recoverProcessedDepVar( processed_cs );
  }
};

/*! \brief The standard generic atomic reaction helper class for raw cross
 * sections
 * \details This helper class should only be used by the
 * MonteCarlo::StandardGenericAtomicReaction class.
 */
template<typename InterpPolicy>
struct StandardGenericAtomicReactionHelper<InterpPolicy,false>
{
  //! Calculate the interpolated cross section
  static inline double calculateInterpolatedCrossSection(
                                                 const double energy_0,
                                                 const double energy_1,
                                                 const double raw_energy,
                                                 const double cross_section_0,
                                                 const double cross_section_1 )
  {
    return InterpPolicy::interpolate( energy_0,
                                      energy_1,
                                      raw_energy,
                                      cross_section_0,
                                      cross_section_1 );
  }

  //! Return the energy of interest
  static inline double returnEnergyOfInterest( const double processed_energy )
  {
    return processed_energy;
  }

  //! Return the cross section of interest
  static inline double returnCrossSectionOfInterest( const double processed_cs )
  {
    return processed_cs;
  }
};

// Basic constructor
template<typename AtomicReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
StandardGenericAtomicReaction<AtomicReactionBase,InterpPolicy,processed_cross_section>::StandardGenericAtomicReaction(
           const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
           const std::shared_ptr<const std::vector<double> >& cross_section,
           const size_t threshold_energy_index )
  : d_incoming_energy_grid( incoming_energy_grid ),
    d_cross_section( cross_section ),
    d_threshold_energy_index( threshold_energy_index )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid->size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
                        incoming_energy_grid->begin(),
                        incoming_energy_grid->end() ) );
  // Make sure the cross section is valid
  testPrecondition( cross_section->size() > 0 );
  testPrecondition( cross_section->size() ==
            incoming_energy_grid->size() - threshold_energy_index );
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid->size() );

  // Construct the grid searcher
  d_grid_searcher.reset( new Utility::StandardHashBasedGridSearcher<std::vector<double>,processed_cross_section>(
                                         incoming_energy_grid,
                                         incoming_energy_grid->front(),
                                         incoming_energy_grid->back(),
                                         incoming_energy_grid->size()/10+1 ) );
}

// Constructor
template<typename AtomicReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
StandardGenericAtomicReaction<AtomicReactionBase,InterpPolicy,processed_cross_section>::StandardGenericAtomicReaction(
      const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
      const std::shared_ptr<const std::vector<double> >& cross_section,
      const size_t threshold_energy_index,
      const std::shared_ptr<const Utility::HashBasedGridSearcher<double> >&
      grid_searcher )
  : d_incoming_energy_grid( incoming_energy_grid ),
    d_cross_section( cross_section ),
    d_threshold_energy_index( threshold_energy_index ),
    d_grid_searcher( grid_searcher )
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid.get() );
  testPrecondition( incoming_energy_grid->size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
                        incoming_energy_grid->begin(),
                        incoming_energy_grid->end() ) );
  // Make sure the cross section is valid
  testPrecondition( cross_section.get() );
  testPrecondition( cross_section->size() > 0 );
  testPrecondition( cross_section->size() ==
            incoming_energy_grid->size() - threshold_energy_index );
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid->size() );
  // Make sure the grid searcher is valid
  testPrecondition( grid_searcher.get() );
}

// Test if the energy falls within the energy grid
template<typename AtomicReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
bool StandardGenericAtomicReaction<AtomicReactionBase,InterpPolicy,processed_cross_section>::isEnergyWithinEnergyGrid( const double energy ) const
{
  return d_grid_searcher->isValueWithinGridBounds( energy );
}

// Return the cross section at the given energy
template<typename AtomicReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
double StandardGenericAtomicReaction<AtomicReactionBase,InterpPolicy,processed_cross_section>::getCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( this->isEnergyWithinEnergyGrid( energy ) );

  size_t energy_index = d_grid_searcher->findLowerBinIndex( energy );
  
  return this->getCrossSection( energy, energy_index );
}

// Return the cross section at the given energy (efficient)
template<typename AtomicReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
double StandardGenericAtomicReaction<AtomicReactionBase,InterpPolicy,processed_cross_section>::getCrossSection(
                                               const double energy,
                                               const size_t bin_index ) const
{
  // Make sure the bin index is valid
  testPrecondition( (StandardGenericAtomicReactionHelper<InterpPolicy,processed_cross_section>::returnEnergyOfInterest( (*d_incoming_energy_grid)[bin_index] ) <=
                     energy) );
  testPrecondition( (StandardGenericAtomicReactionHelper<InterpPolicy,processed_cross_section>::returnEnergyOfInterest( (*d_incoming_energy_grid)[bin_index+1] ) >=
                     energy) );

  if( bin_index >= d_threshold_energy_index )
  {
    size_t cs_index = bin_index - d_threshold_energy_index;

    if( (*d_cross_section)[cs_index] == 0.0 )
    {
      typedef StandardGenericAtomicReactionHelper<typename Utility::InterpPolicyCreationHelper<Utility::LinDepVarProcessingTag,typename InterpPolicy::IndepVarProcessingTag>::Policy,processed_cross_section> Helper;
      
      return Helper::calculateInterpolatedCrossSection(
        (*d_incoming_energy_grid)[bin_index],
        (*d_incoming_energy_grid)[bin_index+1],
        energy,
        (*d_cross_section)[cs_index],
        Helper::returnCrossSectionOfInterest((*d_cross_section)[cs_index+1]) );
    }
    else
    {
      typedef StandardGenericAtomicReactionHelper<InterpPolicy,processed_cross_section> Helper;
      
      return Helper::calculateInterpolatedCrossSection(
                                        (*d_incoming_energy_grid)[bin_index],
                                        (*d_incoming_energy_grid)[bin_index+1],
                                        energy,
                                        (*d_cross_section)[cs_index],
                                        (*d_cross_section)[cs_index+1] );
    }
  }
  else
    return 0.0;
}

// Return the max energy
template<typename AtomicReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
double StandardGenericAtomicReaction<AtomicReactionBase,InterpPolicy,processed_cross_section>::getMaxEnergy() const
{
  return StandardGenericAtomicReactionHelper<InterpPolicy,processed_cross_section>::returnEnergyOfInterest( d_incoming_energy_grid->back() );
}

// Return the threshold energy
template<typename AtomicReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
double StandardGenericAtomicReaction<AtomicReactionBase,InterpPolicy,processed_cross_section>::getThresholdEnergy() const
{
  return StandardGenericAtomicReactionHelper<InterpPolicy,processed_cross_section>::returnEnergyOfInterest( (*d_incoming_energy_grid)[d_threshold_energy_index] );
}

// Return the head of the energy grid
template<typename AtomicReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
const double* StandardGenericAtomicReaction<AtomicReactionBase,InterpPolicy,processed_cross_section>::getEnergyGridHead() const
{
  return d_incoming_energy_grid->data();
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_GENERIC_ATOMIC_REACTION_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardGenericAtomicReaction_def.hpp
//---------------------------------------------------------------------------//
