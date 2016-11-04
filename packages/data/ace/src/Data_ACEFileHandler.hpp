//---------------------------------------------------------------------------//
//!
//! \file   Data_ACEFileHandler.hpp
//! \author Alex Robinson
//! \brief  A Compact ENDF file handler class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_ACE_FILE_HANDLER_HPP
#define DATA_ACE_FILE_HANDLER_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_Tuple.hpp>

namespace Data{

/*! \defgroup ace_table A Compact ENDF (ACE) Table
 *
 * The first line of every ACE table contains the table name, the atomic
 * weight ratio, the temperature (in MEV) that the table was evaluated at,
 * and the date the table was evaluated on. The second line contains a 70
 * character comment and a 10 character material identifier. The third through
 * sixth lines contain the zaids and atomic weight ratios of the isotopes
 * corresponding to the particular element or molecule represented in the
 * table. If the table corresponds to an isotope, no data is given in these
 * lines. The seventh and eighth lines contain the NXS array. The nineth
 * through twelfth lines contain the JXS array. All remaining lines in the
 * table contain the XSS array. The contents of each of these arrays depends
 * on the type of table (i.e. continuous energy neutron, continuous energy
 * photon, etc.). The task of reading in this data is handled by the
 * Data::ACEFileHandler.
 */

//! The ACE (A Compact ENDF) file handler class
class ACEFileHandler
{

public:

  //! Constructor
  ACEFileHandler( const std::string& file_name,
		  const std::string& table_name,
		  const unsigned table_start_line,
		  const bool is_ascii = true );

  //! Destructor
  ~ACEFileHandler();

  //! Get the library name
  const std::string& getLibraryName() const;

  //! Get the table name
  const std::string& getTableName() const;

  //! Get the table atomic weight ratio
  double getTableAtomicWeightRatio() const;

  //! Get the table temperature
  double getTableTemperature() const;

  //! Get the table processing date
  const std::string& getTableProcessingDate() const;

  //! Get the table comment
  const std::string& getTableComment() const;

  //! Get the table mat id
  const std::string& getTableMatId() const;

  //! Get the table zaids
  Teuchos::ArrayView<const int> getTableZAIDs() const;

  //! Get the table atomic weight ratios
  Teuchos::ArrayView<const double> getTableAtomicWeightRatios() const;

  //! Get the table NXS array
  Teuchos::ArrayView<const int> getTableNXSArray() const;

  //! Get the table JXS array
  Teuchos::ArrayView<const int> getTableJXSArray() const;

  //! Get the table XSS array
  Teuchos::ArrayRCP<const double> getTableXSSArray() const;

private:

  // Open the ACE file
  void openACEFile( const std::string& file_name,
		    const bool is_ascii );

  // Read the ACE table
  void readACETable( const std::string& table_name,
		     const unsigned table_start_line );

  // Remove white space from string
  void removeWhiteSpaceFromString( std::string& string ) const;

  // The ace file id used by the ace_helpers fortran module (always set to 1)
  int d_ace_file_id;

  // The name of the ace library that is currently open
  std::string d_ace_library_name;

  // The name of the ace table read from the ace library
  std::string d_ace_table_name;

  // The ace table processing date
  std::string d_ace_table_processing_date;

  // The ace table comment
  std::string d_ace_table_comment;

  // The ace table material id
  std::string d_ace_table_material_id;

  // The ace table atomic weight ratio
  double d_atomic_weight_ratio;

  // The ace table temperature (MeV)
  double d_temperature;

  // The ace table zaids
  Teuchos::Tuple<int,16> d_zaids;

  // The ace table atomic weight ratios
  Teuchos::Tuple<double,16> d_atomic_weight_ratios;

  // The ace table NXS array
  Teuchos::Tuple<int,16> d_nxs;

  // The ace table JXS array
  Teuchos::Tuple<int,32> d_jxs;

  // The ace table XSS array
  Teuchos::ArrayRCP<double> d_xss;
};

} // end Data namespace

#endif // DATA_ACE_FILE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end Data_ACEFileHandler.hpp
//---------------------------------------------------------------------------//
