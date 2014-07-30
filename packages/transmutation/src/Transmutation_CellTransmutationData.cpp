//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_CellTransmutationData.cpp
//! \author Alex Bennett
//! \brief  Creates a class for the cell transmutation data.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

// FRENSIE Includes
#include "Transmutation_CellTransmutationData.hpp"
#include "Transmutation_DecayMatrix.hpp"
#include "Transmutation_IsotopesArray.hpp"
#include "Transmutation_ReactionRateMatrix.hpp"
#include "Facemc_NuclearReactionType.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"

namespace Transmutation {

// Constructor
CellTransmutationData::CellTransmutationData( const Geometry::ModuleTraits::InternalCellHandle cell_id,
                                              const Teuchos::Array<std::pair<int,double> >& initial_number_densities)
   : d_cell_id(cell_id)
{
   // Convert the array isotopes in an isotope map
   IsotopesArray::getNumberDensityMapFromUnorderedArray( d_number_densities, initial_number_densities);
}

// Destructor
CellTransmutationData::~CellTransmutationData()
{}

// Get Cell ID
Geometry::ModuleTraits::InternalCellHandle CellTransmutationData::getCellID()
{
   return d_cell_id;
}

// Get Number Densities
void CellTransmutationData::getNumberDensities(Teuchos::Array<double>& number_densities)
{
   // Convert the isotope map into the isotope array
   IsotopesArray::getOrderedIsotopesArray( d_number_densities, number_densities);
}

// Set Reaction Rates
void CellTransmutationData::setReactionRates(const Facemc::NuclearReactionType reaction,
                                             const Teuchos::Array<std::pair<int,double> >& reaction_rates)
{
   // Make sure the reaction rate has not already been added 
   testPrecondition(d_reaction_rates.find(reaction) == d_reaction_rates.end() )

   // Make sure reaction rate zaids are in the isotope map
   testPrecondition( CellTransmutationData::areReactionRateZaidsInIsotopeMap( reaction_rates ) );

   // Store the reaction rates
   d_reaction_rates[reaction] = reaction_rates; 
}

// Set Fission Reaction Rates
void CellTransmutationData::setFissionReactionRates(const int fission_zaid,
                                                    const double fission_reaction_rates,
                                                    const Teuchos::Array<std::pair<int,double> >& fission_fragments)
{
   // Make sure the fission zaid has not already been stored
   testPrecondition(d_fission_reaction_rates.find(fission_zaid) == d_fission_reaction_rates.end() );
   testPrecondition(d_fission_fragment_reaction_rates.find(fission_zaid) == d_fission_fragment_reaction_rates.end() );

   // Make sure the fission zaid is in the isotope map
   testPrecondition( CellTransmutationData::isFissionReactionRateZaidInIsotopeMap(fission_zaid) );

   // Store the fission reaction rate
   d_fission_reaction_rates[fission_zaid] = fission_reaction_rates;

   // Store the fission fragment reaction rate
   d_fission_fragment_reaction_rates[fission_zaid] = fission_fragments;
}

// Populate the matrix
void CellTransmutationData::populateMatrix(Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> >& matrix)
{
   // Loop through and add all the reaction rates
   for(boost::unordered_map<Facemc::NuclearReactionType, Teuchos::Array<std::pair<int,double> > >::iterator i = d_reaction_rates.begin();
       i != d_reaction_rates.end(); 
       ++i)
   {
      ReactionRateMatrix::addReactionRates(matrix, i->second, i->first);
   }

   // Loop through and add the fission fragment reaction rates
   for(boost::unordered_map<int,Teuchos::Array<std::pair<int,double> > >::iterator i = d_fission_fragment_reaction_rates.begin();
       i != d_fission_fragment_reaction_rates.end();
       ++i)
   {
      ReactionRateMatrix::addFissionFragments(matrix,
                                              i->first,
                                              d_fission_reaction_rates.find( i->first )->second,
                                              i->second);
   }
}

// Check reaction rates zaids are in isotope map
bool CellTransmutationData::areReactionRateZaidsInIsotopeMap(const Teuchos::Array<std::pair<int,double> >& reaction_rates)
{
   for(Teuchos::Array<std::pair<int,double> >::const_iterator i = reaction_rates.begin();
       i != reaction_rates.end();
       ++i)
   {
      if( d_number_densities.find( i->first ) == d_number_densities.end() )
      {
         return false;
      }
   }
   return true;
}

// Check if fission reaction rate zaid is in isotope map
bool CellTransmutationData::isFissionReactionRateZaidInIsotopeMap(const int fission_zaid)
{
   if( d_number_densities.find( fission_zaid ) == d_number_densities.end() )
   {
      return false;
   }
   return true;
}
} // End namespace transmutation

//---------------------------------------------------------------------------//
// end Transmutation_CellTransmutationData.cpp
//---------------------------------------------------------------------------//
