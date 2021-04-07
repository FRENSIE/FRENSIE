//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_StandardReactionBaseImpl_def.hpp
//! \author Alex Robinson
//! \brief  The standard generic atomic reaction class definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_STANDARD_REACTION_BASE_IMPL_DEF_HPP
#define MONTE_CARLO_STANDARD_REACTION_BASE_IMPL_DEF_HPP

// FRENSIE Includes
#include "Utility_StandardHashBasedGridSearcher.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_SearchAlgorithms.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

namespace Details{

/*! \brief The standard reaction base impl interp policy helper class
 */
template<typename InterpPolicy, bool processed_cross_section>
struct StandardReactionBaseImplInterpPolicyHelper
{
  //! Calculate the interpolated cross section (processed values)
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

  //! Return the energy of interest from the processed grid
  static inline double returnEnergyOfInterest( const double processed_energy )
  {
    return InterpPolicy::recoverProcessedIndepVar( processed_energy );
  }

  //! Return the cross section of interest from the processed grid
  static inline double returnCrossSectionOfInterest( const double processed_cs )
  {
    return InterpPolicy::recoverProcessedDepVar( processed_cs );
  }
};

/*! \brief Specialization of the standard reaction base impl interp policy
 * helper class for unprocessed grids
 */
template<typename InterpPolicy>
struct StandardReactionBaseImplInterpPolicyHelper<InterpPolicy,false>
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

/*! \brief The standard reaction base impl get cross section helper
 * \details This helper class should only be used by the
 * MonteCarlo::StandardReactionBaseImpl class.
 */
template<typename InterpPolicy>
struct StandardReactionBaseImplGetCrossSectionHelper
{
  //! Implementation of the getCrossSection method for the first bin
  template<bool processed_cross_section>
  static inline double getCrossSectionImplFirstBin( const double energy_0,
                                                    const double energy_1,
                                                    const double raw_energy,
                                                    const double cross_section_0,
                                                    const double cross_section_1 )
  {
    typedef StandardReactionBaseImplInterpPolicyHelper<InterpPolicy,processed_cross_section> InterpPolicyHelper;

    // Check for the special case of 0.0 in a grid with Log interpolation
    // Note: this should only occur at the first grid point, which is why we
    //       only check the first cross section value
    if( cross_section_0 != 0.0 )
    {
      if( energy_0 != 0.0 )
      {
        return InterpPolicyHelper::calculateInterpolatedCrossSection(
                                                             energy_0,
                                                             energy_1,
                                                             raw_energy,
                                                             cross_section_0,
                                                             cross_section_1 );
      }
      else // energy_0 == 0.0
      {
        typedef StandardReactionBaseImplInterpPolicyHelper<typename Utility::InterpPolicyCreationHelper<typename InterpPolicy::DepVarProcessingTag,Utility::LinIndepVarProcessingTag>::Policy,processed_cross_section> LocalInterpPolicyHelper;

        return LocalInterpPolicyHelper::calculateInterpolatedCrossSection(
                          energy_0,
                          InterpPolicyHelper::returnEnergyOfInterest(energy_1),
                          raw_energy,
                          cross_section_0,
                          cross_section_1 );
      }
    }
    else // cross_section_0 == 0.0
    {
      if( energy_0 != 0.0 )
      {
        typedef StandardReactionBaseImplInterpPolicyHelper<typename Utility::InterpPolicyCreationHelper<Utility::LinDepVarProcessingTag,typename InterpPolicy::IndepVarProcessingTag>::Policy,processed_cross_section> LocalInterpPolicyHelper;

        return LocalInterpPolicyHelper::calculateInterpolatedCrossSection(
           energy_0,
           energy_1,
           raw_energy,
           cross_section_0,
           InterpPolicyHelper::returnCrossSectionOfInterest(cross_section_1) );
      }
      else // energy == 0.0
      {
        typedef StandardReactionBaseImplInterpPolicyHelper<Utility::LinLin,processed_cross_section> LocalInterpPolicyHelper;

        return LocalInterpPolicyHelper::calculateInterpolatedCrossSection(
             energy_0,
             InterpPolicyHelper::returnEnergyOfInterest(energy_1),
             raw_energy,
             InterpPolicyHelper::returnCrossSectionOfInterest(cross_section_0),
             cross_section_1 );
      }
    }
  }

  //! Implementation of the getCrossSection method for the first cross section bin
  template<bool processed_cross_section>
  static inline double getCrossSectionImplFirstCSBin( const double energy_0,
                                                      const double energy_1,
                                                      const double raw_energy,
                                                      const double cross_section_0,
                                                      const double cross_section_1 )
  {
    typedef StandardReactionBaseImplInterpPolicyHelper<InterpPolicy,processed_cross_section> InterpPolicyHelper;

    // Check for the special case of 0.0 in a grid with Log interpolation
    // Note: this should only occur at the first grid point, which is why we
    //       only check the first cross section value
    if( cross_section_0 != 0.0 )
    {
      return InterpPolicyHelper::calculateInterpolatedCrossSection(
                                                             energy_0,
                                                             energy_1,
                                                             raw_energy,
                                                             cross_section_0,
                                                             cross_section_1 );
    }
    else // cross_section_0 == 0.0
    {
      typedef StandardReactionBaseImplInterpPolicyHelper<typename Utility::InterpPolicyCreationHelper<Utility::LinDepVarProcessingTag,typename InterpPolicy::IndepVarProcessingTag>::Policy,processed_cross_section> LocalInterpPolicyHelper;

      return LocalInterpPolicyHelper::calculateInterpolatedCrossSection(
           energy_0,
           energy_1,
           raw_energy,
           cross_section_0,
           InterpPolicyHelper::returnCrossSectionOfInterest(cross_section_1) );
    }
  }

  //! Implementation of the getCrossSection method
  template<bool processed_cross_section>
  static inline double getCrossSectionImpl( const double energy_0,
                                            const double energy_1,
                                            const double raw_energy,
                                            const double cross_section_0,
                                            const double cross_section_1 )
  {
    typedef StandardReactionBaseImplInterpPolicyHelper<InterpPolicy,processed_cross_section> InterpPolicyHelper;

    return InterpPolicyHelper::calculateInterpolatedCrossSection(
                                                             energy_0,
                                                             energy_1,
                                                             raw_energy,
                                                             cross_section_0,
                                                             cross_section_1 );
  }
};

/*! \brief The standard reaction base impl get cross section helper
 * specialization for Utility::LinLin
 * \details This helper class should only be used by the
 * MonteCarlo::StandardReactionBaseImpl class.
 */
template<>
struct StandardReactionBaseImplGetCrossSectionHelper<Utility::LinLin>
{
private:

  // This type
  typedef StandardReactionBaseImplGetCrossSectionHelper<Utility::LinLin> ThisType;

public:

  //! Implementation of the getCrossSection method for the first bin
  template<bool processed_cross_section>
  static inline double getCrossSectionImplFirstBin( const double energy_0,
                                                    const double energy_1,
                                                    const double raw_energy,
                                                    const double cross_section_0,
                                                    const double cross_section_1 )
  {
    return ThisType::getCrossSectionImpl<processed_cross_section>( energy_0,
                                                                   energy_1,
                                                                   raw_energy,
                                                                   cross_section_0,
                                                                   cross_section_1 );
  }

  //! Implementation of the getCrossSection method for the first cross section bin
  template<bool processed_cross_section>
  static inline double getCrossSectionImplFirstCSBin( const double energy_0,
                                                      const double energy_1,
                                                      const double raw_energy,
                                                      const double cross_section_0,
                                                      const double cross_section_1 )
  {
    return ThisType::getCrossSectionImpl<processed_cross_section>( energy_0,
                                                                   energy_1,
                                                                   raw_energy,
                                                                   cross_section_0,
                                                                   cross_section_1 );
  }

  //! Implementation of the getCrossSection method
  template<bool processed_cross_section>
  static inline double getCrossSectionImpl( const double energy_0,
                                            const double energy_1,
                                            const double raw_energy,
                                            const double cross_section_0,
                                            const double cross_section_1 )
  {
    return Utility::LinLin::interpolate( energy_0,
                                         energy_1,
                                         raw_energy,
                                         cross_section_0,
                                         cross_section_1 );
  }
};

} // end Details namespace

// Basic constructor
template<typename ReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
StandardReactionBaseImpl<ReactionBase,InterpPolicy,processed_cross_section>::StandardReactionBaseImpl(
       const std::shared_ptr<const std::vector<double> >& incoming_energy_grid,
       const std::shared_ptr<const std::vector<double> >& cross_section,
       const size_t threshold_energy_index )
  : d_incoming_energy_grid( incoming_energy_grid ),
    d_cross_section( cross_section ),
    d_threshold_energy_index( threshold_energy_index ),
    d_max_energy_index()
{
  // Make sure the incoming energy grid is valid
  testPrecondition( incoming_energy_grid->size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
                        incoming_energy_grid->begin(),
                        incoming_energy_grid->end() ) );
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid->size() );
  // Make sure the cross section is valid
  testPrecondition( cross_section->size() > 0 );
  testPrecondition( cross_section->size() + threshold_energy_index <=
                    incoming_energy_grid->size() );

  // Set the max energy index
  this->setMaxEnergyIndex();

  // Set the get cross section first bin method
  this->setGetCrossSectionFirstBinMethod();

  // Construct the grid searcher
  d_grid_searcher.reset( new Utility::StandardHashBasedGridSearcher<std::vector<double>,processed_cross_section>(
                                         incoming_energy_grid,
                                         incoming_energy_grid->front(),
                                         incoming_energy_grid->back(),
                                         incoming_energy_grid->size()/10+1 ) );
}

// Constructor
template<typename ReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
StandardReactionBaseImpl<ReactionBase,InterpPolicy,processed_cross_section>::StandardReactionBaseImpl(
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
  // Make sure the threshold energy is valid
  testPrecondition( threshold_energy_index < incoming_energy_grid->size() );
  // Make sure the cross section is valid
  testPrecondition( cross_section.get() );
  testPrecondition( cross_section->size() > 0 );
  testPrecondition( cross_section->size() + threshold_energy_index <=
                    incoming_energy_grid->size() );
  // Make sure the grid searcher is valid
  testPrecondition( grid_searcher.get() );

  // Set the max energy index
  this->setMaxEnergyIndex();

  // Set the get cross section first bin method
  this->setGetCrossSectionFirstBinMethod();
}

// Test if the energy falls within the energy grid
template<typename ReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
bool StandardReactionBaseImpl<ReactionBase,InterpPolicy,processed_cross_section>::isEnergyWithinEnergyGrid( const double energy ) const
{
  return d_grid_searcher->isValueWithinGridBounds( energy );
}

// Return the cross section at the given energy
template<typename ReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
double StandardReactionBaseImpl<ReactionBase,InterpPolicy,processed_cross_section>::getCrossSection( const double energy ) const
{
  // Make sure the energy is valid
  testPrecondition( this->isEnergyWithinEnergyGrid( energy ) );

  size_t energy_index = d_grid_searcher->findLowerBinIndex( energy );

  return StandardReactionBaseImpl<ReactionBase,InterpPolicy,processed_cross_section>::getCrossSection( energy, energy_index );
}

// Return the cross section at the given energy (efficient)
template<typename ReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
double StandardReactionBaseImpl<ReactionBase,InterpPolicy,processed_cross_section>::getCrossSection(
                                               const double energy,
                                               const size_t bin_index ) const
{
  return this->getCrossSectionImpl( *d_cross_section, energy, bin_index );
}

// Return the cross section at the given energy
/*! \details This method is exposed so that a different cross section can
 * be temporarily supplied to this class. The temporary cross section must have
 * the same properties as the stored cross section (same threshold index, max
 * index, and processed flag).
 */
template<typename ReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
double StandardReactionBaseImpl<ReactionBase,InterpPolicy,processed_cross_section>::getCrossSectionImpl(
                                      const std::vector<double>& cross_section,
                                      const double energy,
                                      const size_t bin_index ) const
{
  // Make sure the bin index is valid
  testPrecondition( bin_index < d_incoming_energy_grid->size() - 1 );
  testPrecondition( (Details::StandardReactionBaseImplInterpPolicyHelper<InterpPolicy,processed_cross_section>::returnEnergyOfInterest( (*d_incoming_energy_grid)[bin_index] ) <= energy) );
  testPrecondition( (Details::StandardReactionBaseImplInterpPolicyHelper<InterpPolicy,processed_cross_section>::returnEnergyOfInterest( (*d_incoming_energy_grid)[bin_index+1] ) >= energy) );

  if( bin_index > d_threshold_energy_index )
  {
    if( bin_index < d_max_energy_index )
    {
      size_t cs_index = bin_index - d_threshold_energy_index;

      return Details::StandardReactionBaseImplGetCrossSectionHelper<InterpPolicy>:: template getCrossSectionImpl<processed_cross_section>(
                                        (*d_incoming_energy_grid)[bin_index],
                                        (*d_incoming_energy_grid)[bin_index+1],
                                        energy,
                                        cross_section[cs_index],
                                        cross_section[cs_index+1] );
    }
    else
      return 0.0;
  }
  // Handle the special cases that can occur in the first bin (e.g. 0.0 values
  // in a grid with an interpolation type that does not support 0.0)
  else if( bin_index == d_threshold_energy_index )
  {
    return d_get_cross_section_first_bin_impl(
                                        (*d_incoming_energy_grid)[bin_index],
                                        (*d_incoming_energy_grid)[bin_index+1],
                                        energy,
                                        cross_section[0],
                                        cross_section[1] );
  }
  else
    return 0.0;
}

// Return the max energy
template<typename ReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
double StandardReactionBaseImpl<ReactionBase,InterpPolicy,processed_cross_section>::getMaxEnergy() const
{
  return Details::StandardReactionBaseImplInterpPolicyHelper<InterpPolicy,processed_cross_section>::returnEnergyOfInterest( (*d_incoming_energy_grid)[d_max_energy_index] );
}

// Return the threshold energy
template<typename ReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
double StandardReactionBaseImpl<ReactionBase,InterpPolicy,processed_cross_section>::getThresholdEnergy() const
{
  return Details::StandardReactionBaseImplInterpPolicyHelper<InterpPolicy,processed_cross_section>::returnEnergyOfInterest( (*d_incoming_energy_grid)[d_threshold_energy_index] );
}

// Return the head of the energy grid
template<typename ReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
const double* StandardReactionBaseImpl<ReactionBase,InterpPolicy,processed_cross_section>::getEnergyGridHead() const
{
  return d_incoming_energy_grid->data();
}

// Set the max energy index
template<typename ReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
void StandardReactionBaseImpl<ReactionBase,InterpPolicy,processed_cross_section>::setMaxEnergyIndex()
{
  d_max_energy_index = d_threshold_energy_index + d_cross_section->size() - 1;
}

// Set the max energy index
template<typename ReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
void StandardReactionBaseImpl<ReactionBase,InterpPolicy,processed_cross_section>::setMaxEnergyIndex( const size_t max_energy_index )
{
  d_max_energy_index = max_energy_index;
}

// Set the get cross section first bin implementation method
template<typename ReactionBase,
         typename InterpPolicy,
         bool processed_cross_section>
void StandardReactionBaseImpl<ReactionBase,InterpPolicy,processed_cross_section>::setGetCrossSectionFirstBinMethod()
{
  if( d_threshold_energy_index == 0 )
  {
    d_get_cross_section_first_bin_impl =
      &Details::StandardReactionBaseImplGetCrossSectionHelper<InterpPolicy>:: template getCrossSectionImplFirstBin<processed_cross_section>;
  }
  else
  {
    d_get_cross_section_first_bin_impl =
      &Details::StandardReactionBaseImplGetCrossSectionHelper<InterpPolicy>:: template getCrossSectionImplFirstCSBin<processed_cross_section>;
  }
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_STANDARD_REACTION_BASE_IMPL_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_StandardReactionBaseImpl_def.hpp
//---------------------------------------------------------------------------//
