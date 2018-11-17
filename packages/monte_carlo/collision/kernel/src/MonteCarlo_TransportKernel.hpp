//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_TransportKernel.hpp
//! \author Alex Robinson
//! \brief  Transport kernel class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_TRANSPORT_KERNEL_HPP
#define MONTE_CARLO_TRANSPORT_KERNEL_HPP

// FRENSIE Includes
#include "MonteCarlo_CollisionKernel.hpp"
#include "MonteCarlo_FilledGeometryModel.hpp"

namespace MonteCarlo{

/*! The transport kernel class
 */
class TransportKernel
{

public:

  //! Constructor
  TransportKernel( const std::shared_ptr<const FilledGeometryModel>& model );

  //! Destructor
  ~TransportKernel()
  { /* ... */ }

  //! Sample the optical path length traveled by a particle before a collision
  static double sampleOpticalPathLengthToNextCollisionSite();

  //! Sample a simple distance to the next collision site
  template<typename ParticleStateType>
  double sampleSimpleDistanceToNextCollisionSite(
                   const ParticleStateType& particle,
                   double* cell_macroscopic_total_cross_section = NULL ) const;

  //! Sample the the distance to the next collision
  template<typename ParticleStateType>
  double sampleDistanceToNextCollisionSite(
                                     const ParticleStateType& particle ) const;

  //! Check if the transport kernel is defined on the model of interest
  bool isDefinedOnModel( const FilledGeometryModel& model ) const;

private:

  // The geometry model
  std::shared_ptr<const FilledGeometryModel> d_model;
};

// Sample a simple distance to the next collision site
/*! \details This method assumes that the current cell material extends to
 * infinity in the direction of particle travel. This method should only be
 * used when particle tracks are simulated using the "alternative" algorithm 
 * (each time a new cell is entered the distance to collision is re-sampled).
 * To avoid multiple macroscopic total cross section lookups, a double memory
 * address can be passed to store the cross section used by this method.
 */
template<typename ParticleStateType>
double TransportKernel::sampleSimpleDistanceToNextCollisionSite(
                           const ParticleStateType& particle,
                           double* cell_macroscopic_total_cross_section ) const
{
  // Make sure that the particle is embedded in the model that the
  // transport kernel is defined in.
  testPrecondition( particle.isEmbeddedInModel( *d_model ) );

  // Get the macroscopic total cross section (default to void cell) 
  double macroscopic_total_cross_section = 0.0;

  // The sampled distance to collision (default to void cell distance
  // to collision)
  double distance_to_collision = std::numeric_limits<double>::infinity();

  if( !d_model->isCellVoid<ParticleStateType>( particle.getCell() ) )
  {
    macroscopic_total_cross_section =
      d_model->getMacroscopicTotalForwardCrossSectionQuick<ParticleStateType>(
                                    particle.getCell(), particle.getEnergy() );

    distance_to_collision = this->sampleOpticalPathLengthToNextCollisionSite()/
      macroscopic_total_cross_section;
  }

  if( cell_macroscopic_total_cross_section != NULL )
    *cell_macroscopic_total_cross_section = macroscopic_total_cross_section;

  return distance_to_collision;
}

// Sample the the distance to the next collision
/* \details This method will sample an optical path and then convert it to
 * distance by tracking a particle clone through the geometry and converting
 * distances to surface crossings to optical paths using the cell macroscopic
 * total cross section.
 */
template<typename ParticleStateType>
double TransportKernel::sampleDistanceToNextCollisionSite(
                                      const ParticleStateType& particle ) const
{
  // Make sure that the particle is embedded in the model that the
  // transport kernel is defined in.
  testPrecondition( particle.isEmbeddedInModel( *d_model ) );
  // Make sure that the particle is still in the geometry
  testPrecondition( !d_model->isTerminationCell( particle.getCell() ) );

  // Sample an optical path
  double remaining_optical_path_length =
    this->sampleOpticalPathLengthToNextCollisionSite();

  // Convert the optical path to a distance
  double distance_to_collision_site = 0.0;
  
  std::shared_ptr<Geometry::Navigator>
    navigator( particle.navigator().clone() );

  while( true )
  {    
    double distance_to_cell_boundary = navigator->fireRay().value();

    double cell_total_macro_cross_section = 0.0;

    if( !d_model->isCellVoid<ParticleStateType>(navigator->getCurrentCell()) )
    {
      cell_total_macro_cross_section =
        d_model->getMacroscopicTotalForwardCrossSectionQuick<ParticleStateType>( navigator->getCurrentCell(), particle.getEnergy() );
    }
    // The particle is inside of an empty infinite medium
    else if( distance_to_cell_boundary == Utility::QuantityTraits<double>::inf() )
      return distance_to_cell_boundary;

    double optical_path_to_cell_boundary =
      distance_to_cell_boundary*cell_total_macro_cross_section;
    
    // The collision site is beyond the current cell
    if( optical_path_to_cell_boundary < remaining_optical_path_length )
    {
      distance_to_collision_site += distance_to_cell_boundary;
      remaining_optical_path_length -= optical_path_to_cell_boundary;

      navigator->advanceToCellBoundary();

      // If the geometry is exited before the entire optical path has
      // been converted the distance traveled is infinite from the kernels
      // perspective.
      if( d_model->isTerminationCell( navigator->getCurrentCell() ) )
      {
        distance_to_collision_site = std::numeric_limits<double>::infinity();
        break;
      }
    }

    // The collision site is in the current cell
    else
    {
      distance_to_collision_site +=
        remaining_optical_path_length/cell_total_macro_cross_section;

      break;
    }
  }

  return distance_to_collision_site;
}
  
} // end MonteCarlo namespace

#endif // end MONTE_CARLO_TRANSPORT_KERNEL_HPP
