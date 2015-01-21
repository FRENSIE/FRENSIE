//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectroatomFactory.hpp
//! \author Luke Kersting
//! \brief  The electroatom factory class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_ELECTROATOM_FACTORY_HPP
#define MONTE_CARLO_ELECTROATOM_FACTORY_HPP

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
#include "MonteCarlo_Electroatom.hpp"
#include "MonteCarlo_AtomicRelaxationModelFactory.hpp"

namespace MonteCarlo{

//! The electroatom factory class
class ElectroatomFactory
{
  
public:

  //! Constructor
  ElectroatomFactory( const std::string& cross_sections_xml_directory,
                   const boost::unordered_set<std::string>& electroatom_aliases,
                   const double elastic_cutoff_angle,
                   const Teuchos::ParameterList& cross_section_table_info,
                   const Teuchos::RCP<AtomicRelaxationModelFactory>& 
                   atomic_relaxation_model_factory,
                   const bool use_detailed_bremsstrahlung_data,
                   const bool use_atomic_relaxation_data );

  //! Destructor
  ~ElectroatomFactory()
  { /* ... */ }

  //! Create the map of electroatoms
  void createElectroatomMap(
		    boost::unordered_map<std::string,Teuchos::RCP<Electroatom> >&
		    electroatom_map ) const;

private:

  // Create a electroatom from an ACE table
  void createElectroatomFromACETable(
			  const std::string& cross_sections_xml_directory,
			  const std::string& electroatom_alias,
              const double elastic_cutoff_angle,
			  const Teuchos::ParameterList& electroatom_table_info,
			  const Teuchos::RCP<AtomicRelaxationModelFactory>& 
			  atomic_relaxation_model_factory,
              const bool use_detailed_bremsstrahlung_data,
              const bool use_atomic_relaxation_data );

  // The electroatom map
  boost::unordered_map<std::string,Teuchos::RCP<Electroatom> > 
  d_electroatom_name_map;
  
  // The table map
  boost::unordered_map<std::string,Teuchos::RCP<Electroatom> >
  d_electroatomic_table_name_map;
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_ELECTROATOM_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ElectroatomFactory.hpp
//---------------------------------------------------------------------------//
