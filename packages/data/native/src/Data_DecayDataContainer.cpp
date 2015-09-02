//---------------------------------------------------------------------------//
//!
//! \file   Data_DecayDataContainer.cpp
//! \author Alex Robinson
//! \brief  The decay data container class definition (based on DecayFile.cpp
//!         written by CJ Solomon)
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "Data_DecayDataContainer.hpp"
#include "Utility_ContractException.hpp"

namespace Data{

// Constructor (from saved archive)
DecayDataContainer::DecayDataContainer(
		  const std::string& archive_name,
                  const Utility::ArchivableObject::ArchiveType archive_type )
{
  // Import the data in the archive - no way to use initialize list :(
  this->importData( archive_name, archive_type );
}

// Return the nuclide szaids
std::set<unsigned> DecayDataContainer::getNuclideIdentifiers() const
{
  std::set<unsigned> szaids;
  
  DecayNuclideMap::const_iterator it = d_decay_nuclides.begin();

  while( it != d_decay_nuclides.end() )
  {
    szaids.insert( it->first );

    ++it;
  }

  return szaids;
}

// Return the desired decay nuclide
const DecayNuclide& DecayDataContainer::getDecayNuclide( 
						   const unsigned szaid ) const
{
  // Make sure the szaid is valid
  testPrecondition( d_decay_nuclides.find( szaid ) != d_decay_nuclides.end() );

  return d_decay_nuclides.find( szaid )->second;
}

// Return the daughters of a nuclide
std::set<unsigned> DecayDataContainer::getNuclideDaughters( 
						   const unsigned szaid ) const
{
  // Make sure the szaid is valid
  testPrecondition( d_decay_nuclides.find( szaid ) != d_decay_nuclides.end() );

  std::set<unsigned> daughter_szaids;
  
  for( unsigned i = 0; 
       i < this->getDecayNuclide(szaid).getNumberOfDecayBranches();
       ++i )
  {
    unsigned daughter_szaid = this->getDecayNuclide(szaid).getDaughter(i);
    
    // Filter out 0 daughter values
    if( daughter_szaid > 0 ) 
      daughter_szaids.insert( daughter_szaid );
    
    // Find all daughters of the daughter
    if( d_decay_nuclides.find( szaid ) != d_decay_nuclides.end() )
    {
      std::set<unsigned> daughter_daughter_szaids = 
	this->getNuclideDaughters( daughter_szaid );
      
      daughter_szaids.insert( daughter_daughter_szaids.begin(),
			      daughter_daughter_szaids.end() );
    }
  }
  
  return daughter_szaids;
}

// Construct unit decay chain at the desired time
std::map<unsigned, double> DecayDataContainer::constructUnitDecayChain(
			     const unsigned szaid,
			     const double time,
		             std::vector<double> parent_decay_constants ) const
{
  const DecayNuclide nuclide = this->getDecayNuclide( szaid );

  // Assign the decay constants
  std::vector<double> decay_constants = parent_decay_constants;
  decay_constants.push_back( nuclide.getDecayConstant() );

  // Calculate the amount of the nuclide remaining after the desired time
  double remaining_fraction = 0.0, multiplier;

  for( unsigned i = 0; i < decay_constants.size(); ++i )
  {
    multiplier = 1.0;

    for( unsigned j = 0; j < decay_constants.size(); ++j )
    {
      if( j != i )
      {
	multiplier *= (decay_constants[j] > 0.0 ? decay_constants[j] : 1.0 )/
	  (decay_constants[j] - decay_constants[i]);
      }
    }

    remaining_fraction += 
      (decay_constants[i] > 0.0 ? decay_constants[i] : 1.0)*multiplier*
      exp(-decay_constants[i]*time);
  }

  // Check if the remaining fraction needs to be divided by the decay constant
  remaining_fraction /= (decay_constants.back() > 0.0 ? 
			 decay_constants.back() : 1.0 );
  

  // Create the unit decay chain
  std::map<unsigned,double> unit_decay_chain;
  unit_decay_chain[szaid] = (remaining_fraction > 0.0 ? 
			     remaining_fraction : 1.0);

  for( unsigned i = 0; i < nuclide.getNumberOfDecayBranches(); ++i )
  {
    unsigned daughter_szaid = nuclide.getDaughter( i );

    // Filter out spontaneous fission
    if( daughter_szaid == 0 )
      continue;

    std::map<unsigned,double> daughter_unit_decay_chain = 
      this->constructUnitDecayChain( daughter_szaid, time, decay_constants );

    std::map<unsigned,double>::iterator it = 
      daughter_unit_decay_chain.begin();

    while( it != daughter_unit_decay_chain.end() )
    {
      if( unit_decay_chain.find( it->first ) == unit_decay_chain.end() )
      {
	unit_decay_chain[it->first] =
	  it->second*nuclide.getBranchingRatio(i);
      }
      else
      {
	unit_decay_chain[it->first] += 
	  it->second*nuclide.getBranchingRatio(i);
      }
      
      ++it;
    }
  }

  return unit_decay_chain;  
}

// Add a decay nuclide
void DecayDataContainer::addDecayNuclide( const unsigned szaid,
					  const DecayNuclide& nuclide )
{
  d_decay_nuclides[szaid] = nuclide;
}

} // end Data namespace

//---------------------------------------------------------------------------//
// end Data_DecayDataContainer.cpp
//---------------------------------------------------------------------------//
