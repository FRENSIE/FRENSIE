//---------------------------------------------------------------------------//
//!
//! \file   Geometry_CellBoundingBox_def.hpp
//! \author Alex Robinson
//! \brief  Cell bounding box class definition
//!
//---------------------------------------------------------------------------//

#ifndef GEOMETRY_CELL_BOUNDING_BOX_DEF_HPP
#define GEOMETRY_CELL_BOUNDING_BOX_DEF_HPP

// FRENSIE Includes
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_DesignByContract.hpp"

namespace Geometry{

// Constructor
template<typename Cell>
CellBoundingBox<Cell>::CellBoundingBox( const Teuchos::RCP<Cell> &cell,
					const scalarType x_min,
					const scalarType x_max,
					const scalarType y_min,
					const scalarType y_max,
					const scalarType z_min,
					const scalarType z_max,
					const scalarType convergence_ratio )
  : d_cell( cell ),
    d_x_min( x_min ),
    d_x_max( x_max ),
    d_y_min( y_min ),
    d_y_max( y_max ),
    d_z_min( z_min ),
    d_z_max( z_max ),
    d_convergence_ratio( convergence_ratio )
{
  // Make sure that the values are valid
  testPrecondition( !ST::isnaninf( x_min ) );
  testPrecondition( !ST::isnaninf( x_max ) );
  testPrecondition( !ST::isnaninf( y_min ) );
  testPrecondition( !ST::isnaninf( y_max ) );
  testPrecondition( !ST::isnaninf( z_min ) );
  testPrecondition( !ST::isnaninf( z_max ) );
  testPrecondition( !ST::isnaninf( convergence_ratio ) );
  // Make sure that max > min
  testPrecondition( x_max > x_min );
  testPrecondition( y_max > y_min );
  testPrecondition( z_max > z_min );
  // Make sure that the convergence ratio is valid
  testPrecondition( convergence_ratio > ST::zero() );
  testPrecondition( convergence_ratio < ST::one() );
}

// Calculate and set the cell volume
template<typename Cell>
void CellBoundingBox<Cell>::calculateCellVolume( int max_samples )
{
  scalarType cell_volume = ST::zero();
  scalarType cell_volume_estimate = ST::zero();

  int number_of_samples = 0;
  int number_of_scores = 0;

  bool cell_volume_converged = false;

  // The number of samples taken before checking for convergence
  int batch_size = (max_samples < 10000 ) ? max_samples : 10000;

  // The distance between max and min
  scalarType x_length = d_x_max - d_x_min;
  scalarType y_length = d_y_max - d_y_min;
  scalarType z_length = d_z_max - d_z_min;

  // The bounding box volume
  scalarType bounding_box_volume = x_length*y_length*z_length;

  // The sampled point
  scalarType x_sample, y_sample, z_sample;

  // Run batches until the volume converges or the max number of samples is hit
  while( number_of_samples < max_samples && !cell_volume_converged )
  {

    for( int i = 0; i < batch_size; ++i )
    {
      x_sample = d_x_min +
	x_length*Utility::RandomNumberGenerator::getRandomNumber<scalarType>();
      y_sample = d_y_min +
	y_length*Utility::RandomNumberGenerator::getRandomNumber<scalarType>();
      z_sample = d_z_min +
	z_length*Utility::RandomNumberGenerator::getRandomNumber<scalarType>();

      if( d_cell->isIn( x_sample, y_sample, z_sample ) )
	++number_of_scores;

      ++number_of_samples;
    }

    // Compute the average and variance of the samples
    cell_volume_estimate = number_of_scores*bounding_box_volume/
      number_of_samples;

    // Test if the relative error has converged
    cell_volume_converged =
      ST::magnitude( cell_volume_estimate/cell_volume - 1.0 ) <
      d_convergence_ratio;

    // Compute the cell volume estimate
    cell_volume = cell_volume_estimate;
  }

  // Make sure that a valid cell volume was calculated
  testPostcondition( cell_volume > ST::zero() );

  d_cell->setVolume( cell_volume );
}

// Calculate and set the cell surface areas
template<typename Cell>
void CellBoundingBox<Cell>::calculateCellSurfaceAreas( int max_samples )
{

}

// Calculate and set the cell volume and surface areas
template<typename Cell>
void CellBoundingBox<Cell>::calculateCellVolumeAndSurfaceAreas(
							      int max_samples )
{

}

} // end Geonetry namespace

#endif // end GEOMETRY_CELL_BOUNDING_BOX_DEF_HPP

//---------------------------------------------------------------------------//
// end Geometry_CellBoundingBox_def.hpp
//---------------------------------------------------------------------------//
