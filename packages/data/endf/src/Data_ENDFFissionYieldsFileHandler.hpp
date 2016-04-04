//---------------------------------------------------------------------------//
//!
//! \file   Data_ENDFFissionYieldsFileHandler.hpp
//! \author Alex Bennett
//! \brief  An ENDF file handler class declaration for fission yields.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ENDF_FISSION_YIELD_FILE_HANDLER_HPP
#define DATA_ENDF_FISSION_YIELD_FILE_HANDLER_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>

namespace Data{

/*! \defgroup ENDF Fission Yields Table
 *
 * The header of the ENDF Fission Yields table includes a description of what is
 * included in the file. The primary header end with a line number of 99999. No 
 * information is taken from this section. The file is then broken into 2 halfs.
 * The first half includes the independent(prompt) yields and the second half 
 * includes the cumulative(total) yields. The first part of the indepedent yields
 * includes a 2 line header for the independent yields. The information that was 
 * parsed from this section is the ZAID number and the number of energy group the
 * yields are given at. The next section includes a one line header block for the
 * yields given at a single energy. The information parsed from this block includes
 * the energy that the data is given at and the number of fission products listed 
 * in this section. The next section includes the data. The data is arranged in 
 * sets of 4 items. The first item is the ZAID of the fission product. The second
 * item is the metastable state for the fission product. The third item gives the
 * yield of the fission product. The forth item gives the standard deviation of
 * the yield. The data block and the header block for the data are repeated for 
 * all the energy levels. The concludes the independent yields section. The 
 * cumulative yields section is given in the same was as the independent yields
 * section. The task of reading in this data is handled by
 * FRENSIE::ENDFFissionYieldsFileHandler.
 */

//! The ENDF Fission Yields file handler class
class ENDFFissionYieldsFileHandler
{

public:

  //! Construction
  ENDFFissionYieldsFileHandler( const std::string& file_name, const int zaid_name );

  //! Destructor
  ~ENDFFissionYieldsFileHandler();

  //! Get the ZAID
  int getZaid() const;

  //! Get the energies for the independent yields
  Teuchos::ArrayView<const double> getEnergyIndependentYields() const;

  //! Get the ZAID of the fission products for the independent yields
  Teuchos::ArrayView<const Teuchos::Array<int> > getZaidFissionProductsIndependentYields() const;

  //! Get the meta state of the fission products for the independent yields
  Teuchos::ArrayView<const Teuchos::Array<int> > getMetaStateFissionProductsIndependentYields() const;

  //! Get the yields of the fission products for the independent yields
  Teuchos::ArrayView<const Teuchos::Array<double> > getYieldFissionProductsIndependentYields() const;

  //! Get the standard deviation for the yields of the fission products for the indepedent yields
  Teuchos::ArrayView<const Teuchos::Array<double> > getStdYieldFissionProductsIndependentYields() const;
 
  //! Get the energies for the cumulative yields
  Teuchos::ArrayView<const double> getEnergyCumulativeYields() const;

  //! Get the ZAID of the fission products for the cumulative yields
  Teuchos::ArrayView<const Teuchos::Array<int> > getZaidFissionProductsCumulativeYields() const;

  //! Get the meta state of the fission products for the cumulative yields
  Teuchos::ArrayView<const Teuchos::Array<int> > getMetaStateFissionProductsCumulativeYields() const;

  //! Get the yields of the fission products for the cumulative yields
  Teuchos::ArrayView<const Teuchos::Array<double> > getYieldFissionProductsCumulativeYields() const;

  //! Get the standard deviation for the yields of the fission products for the cumulative yields
  Teuchos::ArrayView<const Teuchos::Array<double> > getStdYieldFissionProductsCumulativeYields() const;

private:

  // Open the ENDF file
  void openENDFFile( const std::string& file_name );

  // Read the ENDF file
  void readENDFFile( const int zaid_name );

  // The ENDF file id used by fortran (always set to 1)
  int d_file_id;

  // The ZAID number of the file
  int d_zaid;

  // The number of energies of each of the data sets of the independent yields
  int d_number_energies_independent;

  // The energies of each of the data sets of the independent yields
  Teuchos::Array<double> d_energies_independent;

  // The number of data sets for each energy for the independent yields
  Teuchos::Array<int> d_number_data_sets_independent;

  // The ZAID of the fission products for the indpendent yields
  Teuchos::Array<Teuchos::Array<int> > d_yield_zaid_independent;

  // The meta state of the ZAID of the fission products for the independent yields
  Teuchos::Array<Teuchos::Array<int> > d_yield_meta_state_independent;

  // The yields of the fission products for the independent yields
  Teuchos::Array<Teuchos::Array<double> > d_yield_independent;

  // The standard deviation for the yields of the fission products for the independent yields
  Teuchos::Array<Teuchos::Array<double> > d_yield_std_independent;

  // The number of energies of each of the data sets of the cumulative yields
  int d_number_energies_cumulative;

  // The energies of each of the data sets of the cumulative yields
  Teuchos::Array<double> d_energies_cumulative;

  // The number of data sets for each energy for the cumulative yields
  Teuchos::Array<int> d_number_data_sets_cumulative;

  // The ZAID of the fission products for the cumulative yields
  Teuchos::Array<Teuchos::Array<int> > d_yield_zaid_cumulative;

  // The meta state of the ZAID of the fission products for the cumulative yields
  Teuchos::Array<Teuchos::Array<int> > d_yield_meta_state_cumulative;

  // The yields of the fission products for the cumulative yields
  Teuchos::Array<Teuchos::Array<double> > d_yield_cumulative;

  // The standard deviation for the yields of the fission products for the cumulative yields
  Teuchos::Array<Teuchos::Array<double> > d_yield_std_cumulative;


  // Remove all the zero yield entries
  void filterZeroYields( Teuchos::Array<int>& zaid,
                         Teuchos::Array<int>& meta_state,
                         Teuchos::Array<double>& yield,
                         Teuchos::Array<double>& yield_std );
};

} // end Data namespace

#endif // DATA_ENDF_FISSION_YIELDS_FILE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end Data_ENDFFissionYieldsFileHandler.hpp
//---------------------------------------------------------------------------//
