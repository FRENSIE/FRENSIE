//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SingleObserverPhaseSpaceDiscretizationImpl.cpp
//! \author Alex Robinson
//! \brief  The single observer phase space discretization impl. class
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <sstream>

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
#include "MonteCarlo_SingleObserverPhaseSpaceDiscretizationImpl.hpp"
#include "Utility_HDF5IArchive.hpp"
#include "Utility_HDF5OArchive.hpp"
#include "Utility_ContractException.hpp"

namespace MonteCarlo{

// Assign a discretization to a dimension
void SingleObserverPhaseSpaceDiscretizationImpl::assignDiscretizationToDimension(
        const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>&
        discretization,
        const bool range_dimension )
{
  // Make sure that the discretization pointer is valid
  testPrecondition( discretization.get() );
  // Make sure that the discretization is not for a range dimension
  testPrecondition( !range_dimension );

  d_dimension_discretization = discretization;
}

// Check if a dimension has a discretization
bool SingleObserverPhaseSpaceDiscretizationImpl::doesDimensionHaveDiscretization(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  return dimension == d_dimension_discretization->getDimension();
}

// Get the number of discretized dimensions
size_t SingleObserverPhaseSpaceDiscretizationImpl::getNumberOfDiscretizedDimensions() const
{
  return 1;
}

// Return the dimensions that have been discretized
void SingleObserverPhaseSpaceDiscretizationImpl::getDiscretizedDimensions(
          std::set<ObserverPhaseSpaceDimension>& discretized_dimensions ) const
{
  discretized_dimensions.insert( d_dimension_discretization->getDimension() );
}

// Return the dimensions that have been discretized
void SingleObserverPhaseSpaceDiscretizationImpl::getDiscretizedDimensions(
       std::vector<ObserverPhaseSpaceDimension>& discretized_dimensions ) const
{
  discretized_dimensions.resize( 1 );
  discretized_dimensions[0] = d_dimension_discretization->getDimension();
}

// Return the dimensions that have been discretized
void SingleObserverPhaseSpaceDiscretizationImpl::getDiscretizedDimensions( std::map<ObserverPhaseSpaceDimension,std::pair<std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>,bool> >& discretized_dimensions ) const
{
  discretized_dimensions[d_dimension_discretization->getDimension()].first =
    d_dimension_discretization;
  discretized_dimensions[d_dimension_discretization->getDimension()].second =
    false;
}

// Return the total number of bins in the discretization
size_t SingleObserverPhaseSpaceDiscretizationImpl::getNumberOfBins() const
{
  return d_dimension_discretization->getNumberOfBins();
}

// Return the number of bins for a phase space dimension
size_t SingleObserverPhaseSpaceDiscretizationImpl::getNumberOfBins(
                            const ObserverPhaseSpaceDimension dimension ) const
{
  if( dimension == d_dimension_discretization->getDimension() )
    return d_dimension_discretization->getNumberOfBins();
  else
    return 1;
}

//! Return the bin name
std::string SingleObserverPhaseSpaceDiscretizationImpl::getBinName(
                                                 const size_t bin_index ) const
{
  // Make sure that the bin index is valid
  testPrecondition( bin_index < this->getNumberOfBins() );

  std::ostringstream oss;

  d_dimension_discretization->printBoundariesOfBin( oss, bin_index );

  return oss.str();
}

// Print the discretization
void SingleObserverPhaseSpaceDiscretizationImpl::print( std::ostream& os ) const
{
  d_dimension_discretization->print( os );
}

// Print a dimension discretization
void SingleObserverPhaseSpaceDiscretizationImpl::print(
                            std::ostream& os,
                            const ObserverPhaseSpaceDimension dimension ) const
{
  if( dimension == d_dimension_discretization->getDimension() )
    d_dimension_discretization->print( os );
}

// Print a single bin of a dimension discretization
void SingleObserverPhaseSpaceDiscretizationImpl::print(
                                   std::ostream& os,
                                   const ObserverPhaseSpaceDimension dimension,
                                   const size_t index ) const
{
  if( dimension == d_dimension_discretization->getDimension() )
    d_dimension_discretization->printBoundariesOfBin( os, index );
}

// Check if the point is in the phase space discretization
bool SingleObserverPhaseSpaceDiscretizationImpl::isPointInDiscretization(
                              const DimensionValueMap& dimension_values ) const
{
  // Make sure that the dimension value map is valid
  testPrecondition( dimension_values.find( d_dimension_discretization->getDimension() ) != dimension_values.end() );

  return d_dimension_discretization->isValueInDiscretization( dimension_values.find( d_dimension_discretization->getDimension() )->second );
}

// Check if the point is in the phase space discretization
bool SingleObserverPhaseSpaceDiscretizationImpl::isPointInDiscretization(
             const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  return d_dimension_discretization->isValueInDiscretization( particle_state_wrapper );
}

// Check if the range intersects the phase space discretization
bool SingleObserverPhaseSpaceDiscretizationImpl::doesRangeIntersectDiscretization(
             const ObserverParticleStateWrapper& particle_state_wrapper ) const
{
  return d_dimension_discretization->isValueInDiscretization( particle_state_wrapper );
}

// Calculate the bin indices of a point
void SingleObserverPhaseSpaceDiscretizationImpl::calculateBinIndicesOfPoint(
                                     const DimensionValueMap& dimension_values,
                                     BinIndexArray& bin_indices ) const
{
  // Make sure that the dimension value map is valid
  testPrecondition( dimension_values.find( d_dimension_discretization->getDimension() ) != dimension_values.end() );
  
  d_dimension_discretization->calculateBinIndicesOfValue(
     dimension_values.find(d_dimension_discretization->getDimension())->second,
     bin_indices );
}
  
// Calculate the bin indices of a point
void SingleObserverPhaseSpaceDiscretizationImpl::calculateBinIndicesOfPoint(
                    const ObserverParticleStateWrapper& particle_state_wrapper,
                    BinIndexArray& bin_indices ) const
{
  d_dimension_discretization->calculateBinIndicesOfValue( particle_state_wrapper,
                                                          bin_indices );
}

// Calculate the bin indices and weights of a range
void SingleObserverPhaseSpaceDiscretizationImpl::calculateBinIndicesAndWeightsOfRange(
                    const ObserverParticleStateWrapper& particle_state_wrapper,
                    BinIndexWeightPairArray& bin_indices_and_weights ) const
{
  d_dimension_discretization->calculateBinIndicesOfValue( particle_state_wrapper,
                                                          bin_indices_and_weights );
}

// Set the dimension discretization
void SingleObserverPhaseSpaceDiscretizationImpl::setDimensionDiscretization(
        const std::shared_ptr<const ObserverPhaseSpaceDimensionDiscretization>&
        discretization )
{
  d_dimension_discretization = discretization;
}

// Get the dimension discretization
const ObserverPhaseSpaceDimensionDiscretization&
SingleObserverPhaseSpaceDiscretizationImpl::getDimensionDiscretization() const
{
  return *d_dimension_discretization;
}

} // end MonteCarlo namespace

BOOST_CLASS_EXPORT_IMPLEMENT( MonteCarlo::SingleObserverPhaseSpaceDiscretizationImpl );
EXPLICIT_MONTE_CARLO_CLASS_SERIALIZE_INST( MonteCarlo::SingleObserverPhaseSpaceDiscretizationImpl );

//---------------------------------------------------------------------------//
// end MonteCarlo_SingleObserverPhaseSpaceDiscretizationImpl.cpp
//---------------------------------------------------------------------------//
