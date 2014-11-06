//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_PhotoatomFactory.hpp
//! \author Alex Robinson
//! \brief  The photoatom factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PHOTOATOM_FACTORY_HPP
#define MONTE_CARLO_PHOTOATOM_FACTORY_HPP

// Std Lib Includes
#include <string>

// Boost Includes
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_ArrayRCP.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_Photoatom.hpp"

namespace MonteCarlo{

//! The photoatom factory class
class PhotoatomFactory
{
  
public:

  //! Constructor
  PhotoatomFactory( const std::string& cross_sections_xml_directory,
		    const Teuchos::ParameterList& cross_section_table_info,
		    const boost::unordered_set<std::string>& nuclide_aliases );

  //! Destructor
  ~PhotoatomFactory()
  { /* ... */ }

  //! Create the map of photoatoms
  void createPhotoatomMap(
		    boost::unordered_map<std::string,Teuchos::RCP<Photoatom> >&
		    photoatom_map ) const;

private:

  // The photoatom map
  boost::unordered_map<std::string,Teuchos::RCP<Photoatom> > 
  d_photoatom_name_map;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PHOTOATOM_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_PhotoatomFactory.hpp
//---------------------------------------------------------------------------//
