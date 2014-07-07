//---------------------------------------------------------------------------//
//!
//! \file   Transmutation_CellTransmutationData.hpp
//! \author Alex Bennett
//! \brief  Creates a class for the cell transmutation data. 
//!
//---------------------------------------------------------------------------//


#ifndef TRANSMUTATION_CELL_TRANSMUTATION_DATA_HPP
#define TRANSMUTATION_CELL_TRANSMUTATION_DATA_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_SerialDenseMatrix.hpp>

// FRENSIE Includes
#include "Geometry_ModuleTraits.hpp"
#include "Facemc_NuclearReactionType.hpp"

namespace Transmutation {

class CellTransmutationData {
public:
  
  //! Constructor
  CellTransmutationData( const Geometry::ModuleTraits::InternalCellHandle cell_id );

  //! Destructor
  ~CellTransmutationData();

  //! Get Cell ID
  int getCellID();

  //! Set Reaction Rates
  void setReactionRates(const Facemc::NuclearReactionType reaction, 
                        const Teuchos::Array<std::pair<int,double> >& reaction_rates);

  //! Set Fission Reaction Rates
  void setFissionReactionRates(const int fission_zaid,
                               const double fission_reaction_rate,
                               const Teuchos::Array<std::pair<int,double> >& fission_fragments);

  //! Populate matrix
  void populateMatrix(Teuchos::SerialDenseMatrix<int,double>& matrix);

private:

  // cell id
 int d_cell_id;

  // Map of reaction rates
  boost::unordered_map<Facemc::NuclearReactionType, Teuchos::Array<std::pair<int,double> > > d_reaction_rates;

  // Map of fission reaction rates
  boost::unordered_map<int,double> d_fission_reaction_rates;

  // Map of fission fragment reaction rates
  boost::unordered_map<int,Teuchos::Array<std::pair<int,double> > > d_fission_fragment_reaction_rates;

};

}
 
#endif // TRANSMUTATION_CELL_TRANSMUTATION_DATA_HPP

//---------------------------------------------------------------------------//
// end Transmutation_CellTransmutationData.hpp
//---------------------------------------------------------------------------//
