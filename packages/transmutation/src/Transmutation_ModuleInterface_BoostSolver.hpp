//---------------------------------------------------------------------------//
//! 
//! \file   Transmutation_ModuleInterface_BoostSolver.hpp
//! \author Alex Bennett
//! \brief  Transmutation module interface class for the boost solver
//!
//---------------------------------------------------------------------------//

#ifndef TRANSMUTATION_MODULE_INTERFACE_BOOST_SOLVER_HPP
#define TRANSMUTATION_MODULE_INTERFACE_BOOST_SOVLER_HPP

// Trilinos Includes
#include <Teuchos_Array.hpp>

// Boost Includes
#include <boost/unordered_map.hpp>

// FRENSIE Includes
#include "Transmutation_ModuleInterfaceDecl.hpp"
#include "Transmutation_CellTransmutationData.hpp"
#include "Geometry_ModuleTraits.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "Utility_BoostSolver.hpp"

namespace Transmutation{

/*! This specialization of the module interface class for the transmutation
 * package.
 */
template<>
class ModuleInterface<Utility::BoostSolver>
{

public:
  //! Set the reaction rates
  static void setReactionRates(const MonteCarlo::NuclearReactionType reaction, 
                               Teuchos::Array<std::pair<int,double> >& reaction_rates, 
                               const Geometry::ModuleTraits::InternalCellHandle cell_id);
  
  //! Set the fission reaction rates
  static void setFissionReactionRates(const int zaid, 
                                      const double& reaction_rate, 
                                      Teuchos::Array<std::pair<int,double> >& fission_fragment_reaction_rates,
                                      const Geometry::ModuleTraits::InternalCellHandle cell_id);
  
  //! Set the number densities
  static void setNumberDensities(const boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,Teuchos::Array<std::pair<int,double> > >& number_densities);
  
  //! Solve the transmutation matrix
  static void burn(const double& time, 
                   boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,Teuchos::Array<std::pair<int,double> > >& final_number_density);

private:
  // Map to store cell transmutation data instances
  static boost::unordered_map<Geometry::ModuleTraits::InternalCellHandle,CellTransmutationData> cell_data;

  // Decay Matrix
  static Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> > decay_matrix;

  // Totatl Matrix
  static Teuchos::RCP<Teuchos::SerialDenseMatrix<int,double> > total_matrix;
};

} // end Transmutation namespace

#endif // end TRANSMUTATION_MODULE_INTERFACE_BOOST_SOLVER_HPP

//---------------------------------------------------------------------------//
// end Transmutation_ModuleInterface_BoostSolver.hpp
//---------------------------------------------------------------------------//

