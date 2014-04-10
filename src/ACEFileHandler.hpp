//---------------------------------------------------------------------------//
//!
//! \file   ACEFileHandler.hpp
//! \author Alex Robinson
//! \brief  A Compact ENDF file handler class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef ACE_FILE_HANDLER_HPP
#define ACE_FILE_HANDLER_HPP

// Std Lib Includes
#include <string>

// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_Tuple.hpp>

namespace FACEMC{

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
  Teuchos::ArrayView<const double> getTableXSSArray() const;

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
  Teuchos::Array<double> d_xss;
};

} // end FACEMC namespace

#endif // ACE_FILE_HANDLER_HPP

//---------------------------------------------------------------------------//
// end ACEFileHandler.hpp
//---------------------------------------------------------------------------//
