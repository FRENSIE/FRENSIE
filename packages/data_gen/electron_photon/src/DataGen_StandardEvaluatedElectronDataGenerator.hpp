//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardEvaluatedElectronDataGenerator.hpp
//! \author Alex Robinson
//! \brief  The standard eedl data generator class decl.
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_STANDARD_EVALUATED_ELECTRON_DATA_GENERATOR_HPP
#define DATA_GEN_STANDARD_EVALUATED_ELECTRON_DATA_GENERATOR_HPP

// Std Lib Includes
#include <utility>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_Array.hpp>

// FRENSIE Includes
#include "DataGen_EvaluatedElectronDataGenerator.hpp"
#include "Data_ENDLFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_OneDDistribution.hpp"

namespace DataGen{

//! The standard evaluated electron data generator class
class StandardEvaluatedElectronDataGenerator : public EvaluatedElectronDataGenerator
{

public:

  //! Constructor
  StandardEvaluatedElectronDataGenerator( 
        const unsigned atomic_number,
        const Teuchos::RCP<Data::ENDLFileHandler>& eedl_file_handler,
        const Teuchos::RCP<const Data::XSSEPRDataExtractor>& ace_epr_data,
        const double min_electron_energy = 1.0e-5,
        const double max_electron_energy = 1.0e5,
        const double cutoff_angle = 1.0e-6,
        const double grid_convergence_tol = 0.001,
        const double grid_absolute_diff_tol = 1e-13,
        const double grid_distance_tol = 1e-13 );

  //! Destructor
  ~StandardEvaluatedElectronDataGenerator()
  { /* ... */ }

  //! Populate the eedl data container
  void populateEvaluatedDataContainer(
			   Data::EvaluatedElectronVolatileDataContainer&
			   data_container ) const;

protected:

  // Set the atomic data
  void setRelaxationData( Data::EvaluatedElectronVolatileDataContainer&
			  data_container ) const;

  // Set the electron data
  void setElectronData( 
        Data::EvaluatedElectronVolatileDataContainer& data_container ) const;

private:

  // Set the screened rutherford data
  void setScreenedRutherfordData( 
    const Teuchos::RCP<const Utility::OneDDistribution>& 
        cutoff_elastic_cross_section, 
    const Teuchos::RCP<const Utility::OneDDistribution>& 
        total_elastic_cross_section,
    const std::vector<double>& elastic_energy_grid,
    const std::map<double,std::vector<double> >& elastic_pdf,
    Data::EvaluatedElectronVolatileDataContainer& data_container ) const;

  // Set the transition data
  void setTransitionData( const unsigned subshell,
			  const unsigned transitions,
			  const unsigned subshell_data_start_index,
			  Data::EvaluatedElectronVolatileDataContainer&
			  data_container ) const;
 
  // Test if a value is greater than or equal to one
  static bool greaterThanOrEqualToOne( const double value );

  // Test if a value is greater than one
  static bool greaterThanOne( const double value );

  // The if a value is not equal to zero
  static bool notEqualZero( const double value );

  // Extract electron cross sections
  template<typename InterpPolicy>
  void extractCrossSection(
        std::vector<double>& raw_energy_grid,
        std::vector<double>& raw_cross_section,
        Teuchos::RCP<const Utility::OneDDistribution>& cross_section ) const;

  // Create the cross section on the union energy grid
  void createCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const Teuchos::RCP<const Utility::OneDDistribution>& original_cross_section,
   std::vector<double>& cross_section,
   unsigned& threshold_index ) const;

  // Merge the electron union energy grid
  void mergeElectronUnionEnergyGrid( 
    const std::vector<double>& energy_grid,
    std::list<double>& union_energy_grid ) const;

  // The EEDL data
  Teuchos::RCP<Data::ENDLFileHandler> d_eedl_file_handler;

  // The ACE data
  Teuchos::RCP<const Data::XSSEPRDataExtractor> d_ace_epr_data;

  // The min electron energy
  double d_min_electron_energy;

  // The max electron energy
  double d_max_electron_energy;

  // The cutoff angle below which screened rutherford is used
  double d_cutoff_angle;

  // The grid convergence tolerance
  double d_grid_convergence_tol;

  // The grid absolute difference tolerance
  double d_grid_absolute_diff_tol;

  // The grid distance tolerance
  double d_grid_distance_tol;

  // The atomic subshells
  Teuchos::Array<unsigned> d_subshells;
};

// Test if a value is greater than or equal to one
inline bool 
StandardEvaluatedElectronDataGenerator::greaterThanOrEqualToOne( 
							   const double value )
{
  return value >= 1.0;
}

// Test if a value is greater than one
inline bool 
StandardEvaluatedElectronDataGenerator::greaterThanOne( 
							   const double value )
{
  return value > 1.0;
}

// The if a value is not equal to zero
inline bool StandardEvaluatedElectronDataGenerator::notEqualZero( 
							   const double value )
{
  return value != 0.0;
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "DataGen_StandardEvaluatedElectronDataGenerator_def.hpp"

//---------------------------------------------------------------------------//

#endif // end DATA_GEN_STANDARD_EVALUATED_ELECTRON_DATA_GENERATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_StandardEvaluatedElectronDataGenerator.hpp
//---------------------------------------------------------------------------//
