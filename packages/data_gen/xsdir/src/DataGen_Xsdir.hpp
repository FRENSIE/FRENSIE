//---------------------------------------------------------------------------//
//!
//! \file   DataGen_Xsdir.hpp
//! \author Alex Robinson
//! \brief  The xsdir class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_XSDIR_HPP
#define DATA_GEN_XSDIR_HPP

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_XsdirEntry.hpp"

namespace DataGen{

//! The xsdir
class Xsdir
{

public:

  //! Typedef for the id entries map
  typedef boost::unordered_map<unsigned,
			       Teuchos::Array<Teuchos::RCP<XsdirEntry> > >
  IdEntriesMap;

  //! Typedef for the id entry map
  typedef boost::unordered_map<unsigned,Teuchos::RCP<XsdirEntry> > IdEntryMap;

  //! Constructor
  Xsdir( const std::string& xsdir_file_name );

  //! Destructor
  ~Xsdir()
  { /* ... */ }

  //! Export the xsdir file to a parameter list
  void exportInfo( Teuchos::ParameterList& parameter_list ) const;

private:

  // Compare the versions of two entries
  static bool compareVersions( const Teuchos::RCP<XsdirEntry>& entry_a,
			       const Teuchos::RCP<XsdirEntry>& entry_b );

  // Compare the ids and version of two entries (id 1st, version 2nd)
  static bool compareIdsAndVersions( const Teuchos::RCP<XsdirEntry>& entry_a,
				     const Teuchos::RCP<XsdirEntry>& entry_b );

  // Export the continuous energy neutron entries
  void exportCENeutronEntries( Teuchos::ParameterList& parameter_list ) const;

  // Export the S(alpha,beta) entries
  void exportSAlphaBetaEntries( Teuchos::ParameterList& parameter_list ) const;

  // Export the photonuclear entries
  void exportPhotonuclearEntries(
				Teuchos::ParameterList& parameter_list ) const;

  //! Export the epr entries
  void exportEPREntries( Teuchos::ParameterList& parameter_list ) const;

  // The continuous energy neutron xsdir entries
  Teuchos::Array<Teuchos::RCP<XsdirEntry> > d_ce_neutron_xsdir_entries;

  // The S(alpha,beta) entries
  Teuchos::Array<Teuchos::RCP<XsdirEntry> > d_sab_xsdir_entries;

  // The photonuclear xsdir entries map - for quick lookup
  IdEntriesMap d_photonuclear_xsdir_entries_map;

  Teuchos::Array<Teuchos::RCP<XsdirEntry> > d_photonuclear_xsdir_entries;

  // The electron-photon-relaxation xsdir entries map - for quick lookup
  IdEntryMap d_epr_xsdir_entries_map;

  // The electron-photon-relaxation xsdir entries
  Teuchos::Array<Teuchos::RCP<XsdirEntry> > d_epr_xsdir_entries;
};

} // end DataGen namespace

#endif // end DATA_GEN_XSDIR_HPP

//---------------------------------------------------------------------------//
// end DataGen_Xsdir.hpp
//---------------------------------------------------------------------------//
