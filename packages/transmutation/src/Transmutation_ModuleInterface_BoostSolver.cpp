//---------------------------------------------------------------------------//
//! 
//! \file   Transmutation_ModuleInterface_BoostSolver.cpp
//! \author Alex Bennett
//! \brief  Transmutation module interface class for the boost solver
//!
//---------------------------------------------------------------------------//

// Trilinos Includes
#include <Teuchos_Array.hpp>

// Boost Includes
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "Transmutation_ModuleInterface_BoostSolver.hpp"
#include "Transmutation_DecayMatrix.hpp"
#include "Transmutation_IsotopesArray.hpp"
#include "Transmutation_CellTransmutationData.hpp"
#include "Utility_BoostSolver.hpp"
#include "Utility_ContractException.hpp"

namespace Transmutation{

// Initialize the static member data
Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> > ModuleInterface<Utility::BoostSolver>::decay_matrix;
Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> > ModuleInterface<Utility::BoostSolver>::total_matrix( new Teuchos::SerialDenseMatrix<int,double> );
boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,CellTransmutationData> ModuleInterface<Utility::BoostSolver>::cell_data;

//! Set the reaction rates
void ModuleInterface<Utility::BoostSolver>::setReactionRates(const Facemc::NuclearReactionType reaction, 
                                                             Teuchos::Array<std::pair<int,double> >& reaction_rates, 
                                                             const Geometry::ModuleTraits::InternalCellHandle cell_id)
{
   // Make sure the cell instance has already been created
   testPrecondition( cell_data.find( cell_id ) != cell_data.end() );

   // Set the reaction rates in the cell instance
   cell_data.find(cell_id)->second.setReactionRates(reaction, reaction_rates);
} 

//! Set the fission reaction rates
void ModuleInterface<Utility::BoostSolver>::setFissionReactionRates(const int zaid, 
                                                        const double& reaction_rate, 
                                                        Teuchos::Array<std::pair<int,double> >& fission_fragment_reaction_rates,
                                                        const Geometry::ModuleTraits::InternalCellHandle cell_id)
{
   // Make sure the cell instance has already been created
   testPrecondition( cell_data.find( cell_id ) != cell_data.end() );

   // Set the fission reaction rates
   cell_data.find(cell_id)->second.setFissionReactionRates(zaid, reaction_rate, fission_fragment_reaction_rates);
}

//! Set the number densities
void ModuleInterface<Utility::BoostSolver>::setNumberDensities(const boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,Teuchos::Array<std::pair<int,double> > >& number_densities)
{
   // Make sure cell data map has not been created yet
   testPrecondition( cell_data.size() == 0 );

   // Loop through the number densities map
   for(boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,Teuchos::Array<std::pair<int,double> > >::const_iterator i = number_densities.begin();
       i != number_densities.end();
       ++i)
   {
      // Create the cell instance
      CellTransmutationData cell_instance(i->first, i->second);

      // Save the cell instance
      cell_data.insert( std::pair<Geometry::ModuleTraits::InternalCellHandle,CellTransmutationData>(i->first,cell_instance) );
   }
}      


//! Solve the transmutation matrix
void ModuleInterface<Utility::BoostSolver>::burn(const double& time, 
                                     boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,Teuchos::Array<std::pair<int,double> > >& final_number_densities)
{
   final_number_densities.clear();

   // Only have the decay matrix defined once
   if( decay_matrix.is_null() )
   {
      decay_matrix.reset( new Teuchos::SerialDenseMatrix<int,double> );
      
      //populate decay matrix
      Transmutation::DecayMatrix::getDecayMatrix( decay_matrix );
   }

   // Initialize the number densities arrays
   Teuchos::Array<double> number_densities;
   Teuchos::Array<std::pair<int,double> > unordered_number_densities;

   // Loop through the cells
   for(boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle, CellTransmutationData>::iterator i = cell_data.begin();
       i != cell_data.end();
       ++i)
   {
      // Set the total matrix equal to the decay matrix
      *total_matrix = *decay_matrix;    

      // clear the number density arrays
      number_densities.clear();
      unordered_number_densities.clear();
 
      // Populate the matrix
      i->second.populateMatrix(total_matrix);

      // Get the initial number densities
      i->second.getNumberDensities(number_densities);

      // Create the matrix solver instance
      Utility::BoostSolver solver_instance(total_matrix, number_densities);

      // Solve for the new number densities
      solver_instance.Solve(time);

      // Get the new number densities
      solver_instance.getNumberDensities( number_densities );

      // Convert number density array
      Transmutation::IsotopesArray::getUnorderedArray( unordered_number_densities, number_densities );

      // Add the new number densities into the final number density map
      final_number_densities[ i->first ] = unordered_number_densities;
   }

   cell_data.clear();
}

} // end transmutation namespace

//---------------------------------------------------------------------------//
// end Transmutation_ModuleInterface_BoostSolver.cpp
//---------------------------------------------------------------------------//
