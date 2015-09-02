//---------------------------------------------------------------------------//
//!
//! \file   DataGen_XsdirEntry.hpp
//! \author Alex Robinson
//! \brief  The xsdir entry base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_XSDIR_ENTRY_HPP
#define DATA_GEN_XSDIR_ENTRY_HPP

// Std Lib Includes
#include <string>
#include <vector>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>

namespace DataGen{

//! The xsdir entry
class XsdirEntry
{

public:
  
  //! The table types
  enum TableType{CONTINUOUS_ENERGY_NEUTRON_TABLE,
		 S_ALPHA_BETA_TABLE,
		 ELECTRON_PHOTON_RELAXATION_TABLE,
		 PHOTONUCLEAR_TABLE,
		 UNSUPPORTED_TABLE};

  //! Extract the xsdir entry tokens from the xsdir line
  template<typename STLCompliantContainer>
  static unsigned extractTableTokensFromXsdirLine(
                                      const std::string& xsdir_line,
				      STLCompliantContainer& entry_tokens );
  
  //! Check if the line is a table entry
  template<typename STLCompliantContainer>
  static bool isLineTableEntry( const STLCompliantContainer& entry_tokens );

  //! Check if the table type is supported
  template<typename STLCompliantContainer>
  static bool isTableTypeSupported(
				const STLCompliantContainer& entry_tokens );

  //! Extract the table type from the entry tokens
  template<typename STLCompliantContainer>
  static TableType extractTableTypeFromEntryTokens(
				const STLCompliantContainer& entry_tokens );

  //! Extract zaid from table name
  static unsigned extractZaidFromTableName( const std::string& table_name );

  //! Extract atomic number from zaid
  static unsigned extractAtomicNumberFromZaid( const unsigned zaid );

  //! Extract atomic mass number from zaid
  static unsigned extractAtomicMassNumberFromZaid( const unsigned zaid );

  //! Constructor
  template<typename STLCompliantContainer>
  XsdirEntry( const STLCompliantContainer& entry_tokens );

  //! Destructor
  virtual ~XsdirEntry()
  { /* ... */ }

  //! Return the table name
  const std::string& getTableName() const;

  //! Return the table alias
  virtual const std::string& getTableAlias() const = 0;

  //! Return the table type
  TableType getTableType() const;

  //! Return the table version
  unsigned getTableVersion() const;

  //! Return the table file path
  const std::string& getTableFilePath() const;

  //! Return the table file start line
  unsigned getTableFileStartLine() const;

  //! Return the table length
  unsigned getTableLength() const;

  //! Return the table atomic weight ratio
  double getTableAtomicWeightRatio() const;

  //! Return the table temperature (MeV)
  double getTableTemperatureMeV() const;

  //! Return the table temperature (Kelvin)
  double getTableTemperatureKelvin() const;

  //! Add information to parameter list
  virtual void addInfoToParameterList( 
			    Teuchos::ParameterList& parameter_list ) const = 0;

protected:

  //! Extract the table version from the entry tokens
  template<typename STLCompliantContainer>
  static unsigned extractTableVersionFromEntryTokens( 
			        const STLCompliantContainer& entry_tokens );

  //! Extract the file path from the entry tokens
  template<typename STLCompliantContainer>
  static std::string extractFilePathFromEntryTokens(
			        const STLCompliantContainer& entry_tokens );

  //! Extract the file start line from the entry tokens
  template<typename STLCompliantContainer>
  static unsigned extractFileStartLineFromEntryTokens(
				const STLCompliantContainer& entry_tokens );

  //! Extract the table length from the entry tokens
  template<typename STLCompliantContainer>
  static unsigned extractTableLengthFromEntryTokens(
				const STLCompliantContainer& entry_tokens );

  //! Extract the table atomic weight ratio from the entry tokens
  template<typename STLCompliantContainer>
  static double extractTableAtomicWeightRatioFromEntryTokens(
				const STLCompliantContainer& entry_tokens );

  //! Extract the table temperature (MeV) from the entry tokens
  template<typename STLCompliantContainer>
  static double extractTableTemperatureFromEntryTokens(
				const STLCompliantContainer& entry_tokens );
					   

private:

  // The table name
  std::string d_table_name;

  // The table type
  TableType d_table_type;

  // The table version
  unsigned d_table_version;

  // The table file path
  std::string d_table_file_path;

  // The table file start line
  unsigned d_table_file_start_line;

  // The table length
  unsigned d_table_length;

  // The table atomic weight ratio
  double d_table_atomic_weight_ratio;

  // The table table temperature (MeV)
  double d_table_temperature;
};

} // end DataGen

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_XsdirEntry_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_XSDIR_ENTRY_HPP

//---------------------------------------------------------------------------//
// end DataGen_XsdirEntry.hpp
//---------------------------------------------------------------------------//
