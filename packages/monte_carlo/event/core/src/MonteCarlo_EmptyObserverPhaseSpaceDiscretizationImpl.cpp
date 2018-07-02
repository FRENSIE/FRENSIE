//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_EmptyObserverPhaseSpaceDiscretizationImpl.cpp
//! \author Alex Robinson
//! \brief  The empty observer phase space dimension discretization impl. class
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/polymorphic_oarchive.hpp>
#include <boost/archive/polymorphic_iarchive.hpp>

// FRENSIE Includes
#include "MonteCarlo_EmptyObserverPhaseSpaceDiscretizationImpl.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Assign a discretization to a dimension
void EmptyObserverPhaseSpaceDiscretizationImpl::assignDiscretizationToDimension(
   const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>&,
   const bool )
{
  // Make sure that this is never called
  testPrecondition( false );
}

// Check if a dimension has a discretization
bool EmptyObserverPhaseSpaceDiscretizationImpl::doesDimensionHaveDiscretization(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  return false;
}

// Get the number of discretized dimensions
size_t EmptyObserverPhaseSpaceDiscretizationImpl::getNumberOfDiscretizedDimensions() const
{
  return 0;
}

// Return the dimensions that have been discretized
void EmptyObserverPhaseSpaceDiscretizationImpl::getDiscretizedDimensions( std::set<ObserverPhaseSpaceDimension>& ) const
{ /* ... */ }

// Return the dimensions that have been discretized
void EmptyObserverPhaseSpaceDiscretizationImpl::getDiscretizedDimensions( std::vector<ObserverPhaseSpaceDimension>& ) const
{ /* ... */ }

// Return the dimensions that have been discretized
void EmptyObserverPhaseSpaceDiscretizationImpl::getDiscretizedDimensions( std::map<ObserverPhaseSpaceDimension,std::pair<std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>,bool> >& ) const
{ /* ... */ }

// Return the total number of bins in the discretization
size_t EmptyObserverPhaseSpaceDiscretizationImpl::getNumberOfBins() const
{
  return 1;
}

// Return the number of bins for a phase space dimension
size_t EmptyObserverPhaseSpaceDiscretizationImpl::getNumberOfBins(
                                      const ObserverPhaseSpaceDimension ) const
{
  return 1;
}

// Return the bin name
std::string EmptyObserverPhaseSpaceDiscretizationImpl::getBinName(
                                                 const size_t bin_index ) const
{
  // Make sure that the bin index is valid
  testPrecondition( bin_index >= 0 );

  return "";
}

// Print the discretization
void EmptyObserverPhaseSpaceDiscretizationImpl::print( std::ostream& ) const
{ /* ... */ }

// Print a dimension discretization
void EmptyObserverPhaseSpaceDiscretizationImpl::print(
                                      std::ostream&,
                                      const ObserverPhaseSpaceDimension ) const
{ /* ... */ }

// Print a single bin of a dimension discretization
void EmptyObserverPhaseSpaceDiscretizationImpl::print(
                                             std::ostream&,
                                             const ObserverPhaseSpaceDimension,
                                             const size_t ) const
{ /* ... */ }

// Check if the point is in the phase space discretization
bool EmptyObserverPhaseSpaceDiscretizationImpl::isPointInDiscretization(
                                               const DimensionValueMap& ) const
{
  return true;
}
  
// Check if the point is in the phase space discretization
bool EmptyObserverPhaseSpaceDiscretizationImpl::isPointInDiscretization(
                                    const ObserverParticleStateWrapper& ) const
{
  return true;
}

// Check if the range intersects the phase space discretization
bool EmptyObserverPhaseSpaceDiscretizationImpl::doesRangeIntersectDiscretization(
                                    const ObserverParticleStateWrapper& ) const
{
  return true;
}

// Calculate the bin indices of a point
void EmptyObserverPhaseSpaceDiscretizationImpl::calculateBinIndicesOfPoint(
                                             const DimensionValueMap&,
                                             BinIndexArray& bin_indices ) const
{
  bin_indices.resize( 1 );
  bin_indices[0] = 0;
}
  
// Calculate the bin indices of a point
void EmptyObserverPhaseSpaceDiscretizationImpl::calculateBinIndicesOfPoint(
                                           const ObserverParticleStateWrapper&,
                                           BinIndexArray& bin_indices ) const
{
  bin_indices.resize( 1 );
  bin_indices[0] = 0;
}

// Calculate the bin indices and weights of a range
void EmptyObserverPhaseSpaceDiscretizationImpl::calculateBinIndicesAndWeightsOfRange(
                       const ObserverParticleStateWrapper&,
                       BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  bin_indices_and_weights.resize( 1 );
  bin_indices_and_weights[0].first = 0;
  bin_indices_and_weights[0].second = 1.0;
}
  
} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::EmptyObserverPhaseSpaceDiscretizationImpl );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::EmptyObserverPhaseSpaceDiscretizationImpl );

//---------------------------------------------------------------------------//
// end MonteCarlo_EmptyObserverPhaseSpaceDiscretizationImpl.cpp
//---------------------------------------------------------------------------//
