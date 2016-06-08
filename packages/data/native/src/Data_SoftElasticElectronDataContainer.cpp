//---------------------------------------------------------------------------//
//!
//! \file   Data_SoftElasticElectronDataContainer.cpp
//! \author Luke Kersting
//! \brief  The native soft elastic electron data container class def.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <algorithm>
#include <fstream>
#include <sstream>
#include <typeinfo>

// Boost Includes
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

// FRENSIE Includes
#include "Data_SoftElasticElectronDataContainer.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Constructor (from saved archive)
SoftElasticElectronDataContainer::SoftElasticElectronDataContainer( 
		    const std::string& archive_name,
		    const Utility::ArchivableObject::ArchiveType archive_type )
{
  // Import the data in the archive - no way to use initializer list :(
  this->importData( archive_name, archive_type );
}

// Return the atomic number
unsigned SoftElasticElectronDataContainer::getAtomicNumber() const
{
  return d_atomic_number;
}

// Return the elastic cutoff angle cosine
double SoftElasticElectronDataContainer::getCutoffAngleCosine() const
{
  return d_cutoff_angle_cosine;
}

// Return the elastic angular energy grid
const std::vector<double>& 
SoftElasticElectronDataContainer::getElasticAngularEnergyGrid() const
{
  return d_angular_energy_grid;
}

// Return the number of discrete angles for an angular energy bin
unsigned SoftElasticElectronDataContainer::getNumberOfDiscreteAngles( 
                            const unsigned angular_energy_bin ) const
{
  // Make sure the angular energy bin is valid
  testPrecondition( angular_energy_bin >= 0 );
  testPrecondition( angular_energy_bin < d_angular_energy_grid.size() );

  return d_number_of_discrete_angles.find( angular_energy_bin )->second;
}

// Return the soft elastic discrete angles for an angular energy bin
const std::vector<double>& 
SoftElasticElectronDataContainer::getSoftElasticDiscreteAngles(
					        const unsigned angular_energy_bin ) const
{
  // Make sure the angular energy bin is valid
  testPrecondition( angular_energy_bin >= 0 );
  testPrecondition( angular_energy_bin < d_angular_energy_grid.size() );

  return d_soft_elastic_discrete_angles.find( angular_energy_bin )->second;
}

// Return the soft elastic weights for an angular energy bin
const std::vector<double>& 
SoftElasticElectronDataContainer::getSoftElasticWeights(
					        const unsigned angular_energy_bin ) const
{
  // Make sure the angular energy bin is valid
  testPrecondition( angular_energy_bin >= 0 );
  testPrecondition( angular_energy_bin < d_angular_energy_grid.size() );

  return d_soft_elastic_weights.find( angular_energy_bin )->second;
}
/*
// Return the electron energy grid
const std::vector<double>& 
SoftElasticElectronDataContainer::getElectronEnergyGrid() const
{
  return d_electron_energy_grid;
}

// Return the Moment Preserving (MP) soft elastic electron cross section
const std::vector<double>& 
SoftElasticElectronDataContainer::getMomentPreservingSoftElasticCrossSection() const
{
  return d_moment_preserving_soft_elastic_cross_section;
}

// Return the MP soft elastic cross section threshold energy bin index
unsigned
SoftElasticElectronDataContainer::getMomentPreservingSoftElasticCrossSectionThresholdEnergyIndex() const
{
  return d_moment_preserving_soft_elastic_cross_section_threshold_index;
}
*/
// Set the atomic number
void SoftElasticElectronDataContainer::setAtomicNumber( 
						 const unsigned atomic_number )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number > 0 );
  testPrecondition( atomic_number <= 100 );

  d_atomic_number = atomic_number;
}

// Set the elastic cutoff angle cosine
void SoftElasticElectronDataContainer::setCutoffAngleCosine( 
                         const double cutoff_angle_cosine )
{
  // Make sure the elastic cutoff angle cosine is valid
  testPrecondition( cutoff_angle_cosine > -1.0 );
  testPrecondition( cutoff_angle_cosine <= 1.0 );

  d_cutoff_angle_cosine = cutoff_angle_cosine;
}

// Set the elastic angular energy grid
void SoftElasticElectronDataContainer::setElasticAngularEnergyGrid( 
				       const std::vector<double>& angular_energy_grid )
{
  // Make sure the angular energy grid is valid
  testPrecondition( angular_energy_grid.size() > 0 );
  testPrecondition( 
        Utility::Sort::isSortedAscending( angular_energy_grid.begin(),
			                              angular_energy_grid.end() ) );

  testPrecondition( std::find_if( angular_energy_grid.begin(),
                                  angular_energy_grid.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    angular_energy_grid.end() );

  d_angular_energy_grid = angular_energy_grid;
}

// Set the number of discrete angles for an angular energy bin
void SoftElasticElectronDataContainer::setNumberOfDiscreteAngles( 
             const unsigned angular_energy_bin,
             const unsigned number_of_discrete_angles )
{
  // Make sure the angular_energy_bin is valid
  testPrecondition( angular_energy_bin >= 0 );
  testPrecondition( angular_energy_bin < d_angular_energy_grid.size() );
  // Make sure the number of discrete angles is valid
  testPrecondition( number_of_discrete_angles > 0 );
  
  d_number_of_discrete_angles[angular_energy_bin] = number_of_discrete_angles;
}

// Set the soft elastic discrete angles for an angular energy bin
void SoftElasticElectronDataContainer::setSoftElasticDiscreteAngles(
		     const unsigned angular_energy_bin,
		     const std::vector<double>& soft_elastic_discrete_angles )
{/*
std::cout << "angular_energy_bin =\t" << angular_energy_bin << std::endl;
std::cout << "angular_energy =\t" << d_angular_energy_grid[angular_energy_bin] << std::endl;
std::cout << "# of angles =\t" << soft_elastic_discrete_angles.size() << std::endl;
std::cout << "angle 1 =\t" << soft_elastic_discrete_angles[0] << std::endl;
std::cout << "angle 2 =\t" << soft_elastic_discrete_angles[1] << std::endl;
*/
  // Make sure the angular_energy_bin is valid
  testPrecondition( angular_energy_bin >= 0 );
  testPrecondition( angular_energy_bin < d_angular_energy_grid.size() );
  // Make sure the soft elastic discrete angles are valid
  testPrecondition( soft_elastic_discrete_angles.size() ==
               d_number_of_discrete_angles.find( angular_energy_bin )->second );
  testPrecondition( std::find_if( soft_elastic_discrete_angles.begin(),
                                  soft_elastic_discrete_angles.end(),
                                  isValueLessThanMinusOne ) ==
                    soft_elastic_discrete_angles.end() );
  testPrecondition( std::find_if( soft_elastic_discrete_angles.begin(),
                                  soft_elastic_discrete_angles.end(),
                                  isValueGreaterThanOne ) ==
                    soft_elastic_discrete_angles.end() );

  d_soft_elastic_discrete_angles[angular_energy_bin] = 
        soft_elastic_discrete_angles;
}

// Set the soft elastic weights for an angular energy bin
void SoftElasticElectronDataContainer::setSoftElasticWeights( 
			 const unsigned angular_energy_bin,
			 const std::vector<double>& soft_elastic_weights )
{/*
std::cout << "angular_energy_bin =\t" << angular_energy_bin << std::endl;
std::cout << "angular_energy =\t" << d_angular_energy_grid[angular_energy_bin] << std::endl;
std::cout << "# of weights =\t" << soft_elastic_weights.size() << std::endl;
std::cout << std::setprecision(20) << "weight 1 =\t" << soft_elastic_weights[0] << std::endl;
std::cout << std::setprecision(20) << "weight 2 =\t" << soft_elastic_weights[1] << std::endl;*/

  // Make sure the angular_energy_bin is valid
  testPrecondition( angular_energy_bin >= 0 );
  testPrecondition( angular_energy_bin < d_angular_energy_grid.size() );
  // Make sure the weight is valid
  testPrecondition( soft_elastic_weights.size() ==
               d_number_of_discrete_angles.find( angular_energy_bin )->second );
//  testPrecondition( std::find_if( soft_elastic_weights.begin(),
//                                  soft_elastic_weights.end(),
//                                  isValueLessThanOrEqualToZero ) ==
//                    soft_elastic_weights.end() );
  testPrecondition( std::find_if( soft_elastic_weights.begin(),
                                  soft_elastic_weights.end(),
                                  isValueGreaterThanOne ) ==
                    soft_elastic_weights.end() );
  
  d_soft_elastic_weights[angular_energy_bin] = soft_elastic_weights;
}
/*
// Set the electron energy grid
void SoftElasticElectronDataContainer::setElectronEnergyGrid( 
				       const std::vector<double>& energy_grid )
{
  // Make sure the energy grid is valid
  testPrecondition( energy_grid.size() > 1 );
  testPrecondition( Utility::Sort::isSortedAscending( energy_grid.begin(),
						                              energy_grid.end() ) );
  testPrecondition( energy_grid.front() > 0.0 );

  d_electron_energy_grid = energy_grid;
}

// Set the soft elastic electron cross section using Moment Preserving (MP) theory
void SoftElasticElectronDataContainer::setMomentPreservingSoftElasticCrossSection(
			 const std::vector<double>& soft_elastic_cross_section )
{
  // Make sure the soft elastic cross section is valid
  testPrecondition( soft_elastic_cross_section.size() <= 
                    d_electron_energy_grid.size() );
  testPrecondition( std::find_if( soft_elastic_cross_section.begin(),
                                  soft_elastic_cross_section.end(),
                                  isValueLessThanOrEqualToZero ) ==
                    soft_elastic_cross_section.end() );
  
  d_moment_preserving_soft_elastic_cross_section = soft_elastic_cross_section;
}

// Set the MP soft elastic cross section threshold energy bin index
void SoftElasticElectronDataContainer::setMomentPreservingSoftElasticCrossSectionThresholdEnergyIndex(
						        const unsigned index )
{
  // Make sure the threshold index is valid
  testPrecondition( 
        d_moment_preserving_soft_elastic_cross_section.size() + index ==
        d_electron_energy_grid.size() );
  
 d_moment_preserving_soft_elastic_cross_section_threshold_index= index;
}
*/
// Test if a value is less than or equal to zero
bool SoftElasticElectronDataContainer::isValueLessThanOrEqualToZero( 
							   const double value )
{
  return value <= 0.0;
}

// Test if a value is less than zero
bool SoftElasticElectronDataContainer::isValueLessThanZero( 
							   const double value )
{
  return value < 0.0;
}

// Test if a value is greater than one
bool SoftElasticElectronDataContainer::isValueGreaterThanOne( 
							   const double value )
{
  return value > 1.0;
}

// Test if a value is less than the angle cosine cutoff
bool SoftElasticElectronDataContainer::isValueLessThanMinusOne( 
							   const double value )
{
  return value < -1.0;
}


} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_SoftElasticElectronDataContainer.cpp
//---------------------------------------------------------------------------//
