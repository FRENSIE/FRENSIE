//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardEvaluatedElectronDataGenerator.cpp
//! \author Luke Kersting
//! \brief  The standard electron-electron-relaxation data generator class def.
//!
//---------------------------------------------------------------------------//

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>

// FRENSIE Includes
#include "DataGen_StandardEvaluatedElectronDataGenerator.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_GridGenerator.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_ComparePolicy.hpp"

namespace DataGen{

// Initialize the static member data
/*! \details The u nion energy grid generator has a hard time generating grid 
    points near a value of zero. By inserting another point just above the 
    threshold, this problem is fixed.
 */
const double StandardEvaluatedElectronDataGenerator::s_threshold_energy_nudge_factor = 1.0001;

// Constructor
StandardEvaluatedElectronDataGenerator::StandardEvaluatedElectronDataGenerator( 
	   const unsigned atomic_number,
	   const Teuchos::RCP<Data::ENDLFileHandler>& eedl_file_handler,
	   const double min_electron_energy,
	   const double max_electron_energy,
       const double cutoff_angle,
	   const double grid_convergence_tol,
	   const double grid_absolute_diff_tol,
	   const double grid_distance_tol )
  : EvaluatedElectronDataGenerator( atomic_number ),
    d_eedl_file_handler( eedl_file_handler ),
    d_min_electron_energy( min_electron_energy ),
    d_max_electron_energy( max_electron_energy ),
    d_cutoff_angle( cutoff_angle ),
    d_grid_convergence_tol( grid_convergence_tol ),
    d_grid_absolute_diff_tol( grid_absolute_diff_tol ),
    d_grid_distance_tol( grid_distance_tol )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
  // Make sure the eedl data is valid
  testPrecondition( !d_eedl_file_handler.is_null() );
  // Make sure the electron energy limits are valid
  testPrecondition( min_electron_energy > 0.0 );
  testPrecondition( min_electron_energy < max_electron_energy );
  // Make sure the cutoff angle is valid
  testPrecondition( cutoff_angle >= 0.0 );
  testPrecondition( cutoff_angle < 2.0 );
}

// Populate the eedl data container
void StandardEvaluatedElectronDataGenerator::populateEvaluatedDataContainer(
			   Data::EvaluatedElectronVolatileDataContainer&
			   data_container ) const
{
  // Set the atomic number
  this->setAtomicNumber( data_container );

  // Set cutoff angle
  data_container.setCutoffAngle( d_cutoff_angle );

  // Set the electron data
  std::cout << "\nSetting the electron data: " << std::endl;
  this->setElectronData( data_container );
}

// Process EEDL file
/*! \details This function uses the Data::ENDLFileHandler to read the
 * EEDL data file. The data that is read is then processed into an appropriate
 * format and finally stored in the necessary HDF5 file. 
 */
void StandardEvaluatedElectronDataGenerator::setElectronData( 
    Data::EvaluatedElectronVolatileDataContainer& data_container ) const
{   
  // Information in first header of the EEDL file
  int atomic_number_in_table, 
      outgoing_particle_designator, 
      interpolation_flag;
  double atomic_weight;

  // Information in the second header of the EEDL file
  int reaction_type, electron_shell;

  // array of all the subshells read
  std::set<unsigned> atomic_subshells;

  // cross sections in the file
  Teuchos::RCP<const Utility::OneDDistribution>  
        bremsstrahlung_cross_section, atomic_excitation_cross_section,
        cutoff_elastic_cross_section, total_elastic_cross_section;

  Teuchos::Array<std::pair<unsigned,Teuchos::RCP<const Utility::OneDDistribution> > >
        electroionization_cross_section;

  // The elastic angular distribution energy grid and pdf
  std::vector<double> elastic_energy_grid;
  std::map<double,std::vector<double> > elastic_pdf;

  // Initialize union energy grid
  std::list<double> union_energy_grid;
  union_energy_grid.push_back( d_min_electron_energy );
  union_energy_grid.push_back( d_max_electron_energy );

  std::cout << " Reading ENDL Data file";
  std::cout.flush();

  // Process every table in the EEDL file
  while( d_eedl_file_handler->validFile() && !d_eedl_file_handler->endOfFile() )
  {
    // Read first table header and determine which element is being processed
    d_eedl_file_handler->readFirstTableHeader( atomic_number_in_table,
                                              outgoing_particle_designator,
                                              atomic_weight,
                                              interpolation_flag );
    
    // Check that the EEDL file is still valid (eof has not been reached)
    if( d_eedl_file_handler->endOfFile() )
    {
	  continue;
    }
      
    testPostcondition( atomic_number_in_table == 
                       data_container.getAtomicNumber() );

    // Read second table header and determine the reaction type
    d_eedl_file_handler->readSecondTableHeader( reaction_type,
                                                electron_shell );

    if ( electron_shell > 0 )
    {
      // set subshells
      atomic_subshells.insert( electron_shell );
      data_container.setSubshells( atomic_subshells );
    }

    // Read and process the data in the current table, then store in the HDF5
    // file
    switch( reaction_type )
    {
  
    case 7000:
      // Integrated elastic transport cross section data - ignored
      
      d_eedl_file_handler->skipTable();

      std::cout << ".";
      std::cout.flush();   
      break;

    case 8000:
    {
      // Interpolation should always be LogLog = 5 
      testPrecondition( interpolation_flag == 5 )

      // Extract in the integrated large angle scattering cross section data
      std::vector<double> raw_energy_grid, raw_cross_section;
      d_eedl_file_handler->processTwoColumnTable( raw_energy_grid, 
                                                  raw_cross_section );

      this->extractCrossSection<Utility::LogLog>( 
                raw_energy_grid,
                raw_cross_section,
                cutoff_elastic_cross_section );

      // merge raw energy grid with the union energy grid
      mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );


      std::cout << ".";
      std::cout.flush();     
      break;
    }
    case 8011:
      // Average energy to residual atom from elastic scattering - ignored
      
      d_eedl_file_handler->skipTable();

      std::cout << ".";
      std::cout.flush(); 
      break;

    case 8010:
      // Average energy of scattered electron from elastic scattering - ignored
      
      d_eedl_file_handler->skipTable();

      std::cout << ".";
      std::cout.flush();    
      break;


    case 8022:
    {
      // Read in the elastic angular distribution of the scattered electron data

      // Interpolation should always be LinLin = 0 
      testPrecondition( interpolation_flag == 0 )

      std::map<double,std::vector<double> > elastic_angle;

      d_eedl_file_handler->processThreeColumnTable( 
            elastic_energy_grid, 
            elastic_angle,
            elastic_pdf );

      data_container.setElasticAngularEnergyGrid( elastic_energy_grid );
      data_container.setAnalogElasticAngles( elastic_angle );
      data_container.setAnalogElasticPDF( elastic_pdf ); 

      std::cout << ".";
      std::cout.flush(); 
      break;
    }
    case 10000:
    {
      // Extract in the integrated total elastic cross section data

      // Interpolation should always be LogLog = 5 
      testPrecondition( interpolation_flag == 5 )

      std::vector<double> raw_energy_grid, raw_cross_section;
      d_eedl_file_handler->processTwoColumnTable( raw_energy_grid, 
                                                  raw_cross_section );

      this->extractCrossSection<Utility::LogLog>( 
                raw_energy_grid,
                raw_cross_section,
                total_elastic_cross_section );

      // merge raw energy grid with the union energy grid
      mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

      std::cout << ".";
      std::cout.flush(); 
      break;
    }
    case 81000:
    {
      // Extract the integrated ionization cross section

      // Interpolation should always be LinLin = 0 
      testPrecondition( interpolation_flag == 0 )

      std::vector<double> raw_energy_grid, raw_cross_section;
      d_eedl_file_handler->processTwoColumnTable( raw_energy_grid, 
                                                  raw_cross_section );

      Teuchos::RCP<const Utility::OneDDistribution> subshell_cross_section;

      this->extractCrossSection<Utility::LinLin>( 
                raw_energy_grid,
                raw_cross_section,
                subshell_cross_section );

      // merge raw energy grid with the union energy grid
      mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

      std::pair<unsigned,Teuchos::RCP<const Utility::OneDDistribution> >
        cross_section_pair( electron_shell, subshell_cross_section );

      electroionization_cross_section.push_back( cross_section_pair );


      std::cout << ".";
      std::cout.flush();     
      break;
    }
    case 81010:

      // Average energy of electron from ionization - ignored
      // ( Yo == 9 )
      // Average energy of secondary electron from ionization - ignored
      // ( Yo == 19 )

      d_eedl_file_handler->skipTable();

      std::cout << ".";
      std::cout.flush(); 
      break;

    case 81021:
    {
      // Interpolation should always be LinLin = 0 
      testPrecondition( interpolation_flag == 0 )
      // The outgoing particle designator should be electron as recoil (19)
      testPrecondition( outgoing_particle_designator == 19 );

      std::vector<double> electron_energy_grid;
      std::map<double,std::vector<double> > electroionization_recoil_energy,
                                            electroionization_recoil_pdf;

      // Read the recoil electron spectrum from ionization for a subshell
      // If electron_shell == 0 then no subshell data only total

      d_eedl_file_handler->processThreeColumnTable( 
            electron_energy_grid, 
            electroionization_recoil_energy,
            electroionization_recoil_pdf );  


      data_container.setElectroionizationEnergyGrid( 
                        electron_shell,
                        electron_energy_grid );

      data_container.setElectroionizationRecoilEnergy( 
                        electron_shell,
                        electroionization_recoil_energy );

      data_container.setElectroionizationRecoilPDF( 
                        electron_shell,
                        electroionization_recoil_pdf );

      std::cout << ".";
      std::cout.flush(); 
      break;
    }
    case 82000:
    {
      // Interpolation should always be LinLin = 0 
      testPrecondition( interpolation_flag == 0 )

      // Extract the integrated bremsstrahlung cross section
      std::vector<double> raw_energy_grid, raw_cross_section;
      d_eedl_file_handler->processTwoColumnTable( raw_energy_grid, 
                                                  raw_cross_section );

      this->extractCrossSection<Utility::LinLin>( 
                raw_energy_grid,
                raw_cross_section,
                bremsstrahlung_cross_section );

      // merge raw energy grid with the union energy grid
      mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

      std::cout << ".";
      std::cout.flush();     
      break;
    }
    case 82010:
      // Average energy of secondary photon from bremsstrahlung - ignored
      // ( Yo == 7 )
      // Average energy of secondary electron from bremsstrahlung - ignored
      // ( Yo == 9 )
      
      d_eedl_file_handler->skipTable();

      std::cout << ".";
      std::cout.flush(); 
      break;

    case 82021:
    {
      // Read the sprectrum of the secondary photon from bremsstrahlung

      // Interpolation should always be LinLin = 0 
      testPrecondition( interpolation_flag == 0 )
      // The outgoing particle designator should be photon (7)
      testPrecondition( outgoing_particle_designator == 7 );

      std::vector<double> electron_energy_grid;
      std::map<double,std::vector<double> > bremsstrahlung_photon_energy,
                                            bremsstrahlung_photon_pdf;

      d_eedl_file_handler->processThreeColumnTable( 
            electron_energy_grid, 
            bremsstrahlung_photon_energy,
            bremsstrahlung_photon_pdf );  

      data_container.setBremsstrahlungEnergyGrid( electron_energy_grid );

      data_container.setBremsstrahlungPhotonEnergy( 
                        bremsstrahlung_photon_energy );

      data_container.setBremsstrahlungPhotonPDF( 
                        bremsstrahlung_photon_pdf );

      std::cout << ".";
      std::cout.flush();    
      break;
    }
    case 83000:
    {
      // Extract the integrated excitation cross section

      // Interpolation should always be LinLin = 0 
      testPrecondition( interpolation_flag == 0 )

      std::vector<double> raw_energy_grid, raw_cross_section;
      d_eedl_file_handler->processTwoColumnTable( raw_energy_grid, 
                                                  raw_cross_section );

      this->extractCrossSection<Utility::LinLin>( 
                raw_energy_grid,
                raw_cross_section,
                atomic_excitation_cross_section );

      // merge raw energy grid with the union energy grid
      mergeElectronUnionEnergyGrid( raw_energy_grid, union_energy_grid );

      std::cout << ".";
      std::cout.flush(); 
      break;
    }
    case 83011:
    {
      // Read the average energy loss from excitation
      testPrecondition( interpolation_flag == 0 );

      std::vector<double> atomic_excitation_energy_grid, 
                          atomic_excitation_energy_loss; 

      d_eedl_file_handler->processTwoColumnTable( 
            atomic_excitation_energy_grid, 
            atomic_excitation_energy_loss );

      data_container.setAtomicExcitationEnergyGrid( 
            atomic_excitation_energy_grid );

      data_container.setAtomicExcitationEnergyLoss( 
            atomic_excitation_energy_loss );

      std::cout << ".";
      std::cout.flush();     
      break;
    }
    default:
      // Unknown reaction type found
      {
	bool known_reaction_type = false;
	std::cout << known_reaction_type <<
    " Fatal Error: An unknown reaction type was encountered while processing the EEDL file.";
    std::cout.flush();
      }
      break;
    }
  }
  // Close the EEDL file
  d_eedl_file_handler->closeENDLFile();

  std::cout << "done." << std::endl;


  // Set the screened Rutherford cross section data
  setScreenedRutherfordData( cutoff_elastic_cross_section, 
                             total_elastic_cross_section,
                             elastic_energy_grid, 
                             elastic_pdf,
                             data_container );


  // Create the union energy grid
  std::cout << " Creating union energy grid";
  std::cout.flush();


  Utility::GridGenerator<Utility::LinLin> 
    union_energy_grid_generator( d_grid_convergence_tol,
                                 d_grid_absolute_diff_tol,
                                 d_grid_distance_tol );
  
  // Calculate the union energy grid
  boost::function<double (double pz)> grid_function = 
    boost::bind( &Utility::OneDDistribution::evaluate,
                 boost::cref( *cutoff_elastic_cross_section ),
                 _1 );

  union_energy_grid_generator.generateInPlace( union_energy_grid,
                                               grid_function );

  std::cout << ".";
  std::cout.flush(); 
  
  grid_function = boost::bind( 
        &Utility::OneDDistribution::evaluate,
        boost::cref( *total_elastic_cross_section ),
        _1 );
  
  union_energy_grid_generator.generateInPlace( union_energy_grid,
                                               grid_function );
  std::cout << ".";
  std::cout.flush(); 

  grid_function = boost::bind( &Utility::OneDDistribution::evaluate,
			                   boost::cref( *bremsstrahlung_cross_section ),
			                   _1 );
  
  union_energy_grid_generator.generateInPlace( union_energy_grid,
                                               grid_function );
  std::cout << ".";
  std::cout.flush();

  grid_function = boost::bind( &Utility::OneDDistribution::evaluate,
			                   boost::cref( *atomic_excitation_cross_section ),
			                   _1 );

  union_energy_grid_generator.generateInPlace( union_energy_grid,
                                               grid_function );
  std::cout << ".";
  std::cout.flush(); 

  for( unsigned i = 0; i < electroionization_cross_section.size(); ++i )
  {
    grid_function = boost::bind( 
		   &Utility::OneDDistribution::evaluate,
		   boost::cref( *electroionization_cross_section[i].second ),
		   _1 );

  union_energy_grid_generator.generateInPlace( union_energy_grid,
                                               grid_function );
    std::cout << ".";
    std::cout.flush();
  }

  std::cout << "done." << std::endl;

  // Set the union energy grid
  std::vector<double> energy_grid;
  energy_grid.assign( union_energy_grid.begin(),
                      union_energy_grid.end() );
  
  data_container.setElectronEnergyGrid( energy_grid );


  // Create and set the cross sections
  std::vector<double> cross_section;
  unsigned threshold;

  {
  // Set Elastic cross section data
  std::vector<double> cutoff_cross_section, total_cross_section;

  std::cout << " Setting the cutoff elastic cross section...";
  std::cout.flush();
  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                             cutoff_elastic_cross_section,
                                             cutoff_cross_section,
                                             threshold );
  data_container.setCutoffElasticCrossSection( cutoff_cross_section );
  data_container.setCutoffElasticCrossSectionThresholdEnergyIndex( threshold ); 
  std::cout << "done." << std::endl;


  std::cout << " Setting the screened Rutherford elastic cross section...";
  std::cout.flush();
  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                             total_elastic_cross_section,
                                             total_cross_section,
                                             threshold );

  std::vector<double> raw_cross_section( total_cross_section.size() );
  for ( int i = 0; i < total_cross_section.size(); ++i )
  {
    raw_cross_section[i] = total_cross_section[i] - cutoff_cross_section[i];

    double relative_difference = raw_cross_section[i]/total_cross_section[i];
    
    // Check for roundoff error and reduce to zero if needed
    if ( relative_difference < 1.0e-6 )
    {
      raw_cross_section[i] = 0.0;
 
      // Update threshold index
      threshold = i+1;
    } 
  }

  std::vector<double>::iterator start = raw_cross_section.begin();
  std::advance( start, threshold );

  cross_section.assign( start, raw_cross_section.end() );

  data_container.setScreenedRutherfordElasticCrossSection( cross_section );
  data_container.setScreenedRutherfordElasticCrossSectionThresholdEnergyIndex( 
    threshold ); 
  std::cout << "done." << std::endl;
  }


  std::cout << " Setting the bremsstrahlung cross section...";
  std::cout.flush();
  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                             bremsstrahlung_cross_section,
                                             cross_section,
                                             threshold );

  data_container.setBremsstrahlungCrossSection( cross_section );
  data_container.setBremsstrahlungCrossSectionThresholdEnergyIndex( threshold ); 
  std::cout << "done." << std::endl;


  std::cout << " Setting the atomic excitation cross section...";
  std::cout.flush();
  this->createCrossSectionOnUnionEnergyGrid( union_energy_grid,
                                             atomic_excitation_cross_section,
                                             cross_section,
                                             threshold );

  data_container.setAtomicExcitationCrossSection( cross_section );
  data_container.setAtomicExcitationCrossSectionThresholdEnergyIndex( 
                    threshold ); 
  std::cout << "done." << std::endl;
  

  for( unsigned i = 0; i < electroionization_cross_section.size(); ++i )
  {
    std::cout << " Setting subshell " 
	      << electroionization_cross_section[i].first 
	      << " photoelectric cross section...";
    std::cout.flush();
    this->createCrossSectionOnUnionEnergyGrid( 
				   union_energy_grid,
				   electroionization_cross_section[i].second,
				   cross_section,
				   threshold );

    data_container.setElectroionizationCrossSection( 
				    electroionization_cross_section[i].first,
				    cross_section );
    data_container.setElectroionizationCrossSectionThresholdEnergyIndex(
				    electroionization_cross_section[i].first,
				    threshold );
    std::cout << "done." << std::endl;
  }
}

// Set the screened rutherford data
void StandardEvaluatedElectronDataGenerator::setScreenedRutherfordData( 
    const Teuchos::RCP<const Utility::OneDDistribution>& 
        cutoff_elastic_cross_section, 
    const Teuchos::RCP<const Utility::OneDDistribution>& 
        total_elastic_cross_section,
    const std::vector<double>& elastic_energy_grid,
    const std::map<double,std::vector<double> >& elastic_pdf,
    Data::EvaluatedElectronVolatileDataContainer& data_container ) const
{
  // Calculate Moliere's screening constant and the screened rutherford normalization constant
  std::vector<double> 
    moliere_screening_constant, screened_rutherford_normalization_constant;
  
  // iterate through all angular energy bins
  for ( int i = 0; i < elastic_energy_grid.size(); ++i )
  {
    // get the angular energy bin
    double energy = elastic_energy_grid[i];

    // get the ratio of the screened rutherford to cutoff cross section
    double cross_section_ratio = 
        ( total_elastic_cross_section->evaluate( energy ) -
        cutoff_elastic_cross_section->evaluate( energy ) )/
        cutoff_elastic_cross_section->evaluate( energy );

    
    if ( cross_section_ratio > 1.0e-6 )
    {
    // get the pdf value at the cutoff angle for the given energy
    double cutoff_pdf = elastic_pdf.find( energy )->second.front(); 

    // calculate Moliere's screening constant
    moliere_screening_constant.push_back( d_cutoff_angle/( 
        cross_section_ratio/( d_cutoff_angle*cutoff_pdf ) - 1.0 ) );

    // calculate the screened rutherford normalization constant
    screened_rutherford_normalization_constant.push_back( cutoff_pdf*( 
        ( d_cutoff_angle + moliere_screening_constant.back() )* 
        ( d_cutoff_angle + moliere_screening_constant.back() ) ) );
    }
  }
  // Set Moliere's screening constant
  data_container.setMoliereScreeningConstant( moliere_screening_constant );

  // Set the screened rutherford normalization constant
  data_container.setScreenedRutherfordNormalizationConstant( 
    screened_rutherford_normalization_constant );  
}


// Create the cross section on the union energy grid
void StandardEvaluatedElectronDataGenerator::createCrossSectionOnUnionEnergyGrid(
   const std::list<double>& union_energy_grid,
   const Teuchos::RCP<const Utility::OneDDistribution>& original_cross_section,
   std::vector<double>& cross_section,
   unsigned& threshold_index ) const
{
  std::vector<double> raw_cross_section( union_energy_grid.size() );
  
  std::list<double>::const_iterator energy_grid_pt = union_energy_grid.begin();
  
  unsigned index = 0u;
  
  while( energy_grid_pt != union_energy_grid.end() )
  {
    raw_cross_section[index] = 
      original_cross_section->evaluate( *energy_grid_pt );

    ++energy_grid_pt;
    ++index;
  }

  std::vector<double>::iterator start = 
    std::find_if( raw_cross_section.begin(),
		  raw_cross_section.end(),
		  notEqualZero );

  cross_section.assign( start, raw_cross_section.end() );

  threshold_index = std::distance( raw_cross_section.begin(), start );
}

// Merge a secondary energy grid with the electron union energy grid
void StandardEvaluatedElectronDataGenerator::mergeElectronUnionEnergyGrid( 
     const std::vector<double>& energy_grid,
     std::list<double>& union_energy_grid ) const
{
  // Assign the new grid to the union grid
  union_energy_grid.insert( union_energy_grid.begin(),
                            energy_grid.begin(), 
                            energy_grid.end() );

  // Sort the union energy grid
  union_energy_grid.sort();

  // Remove all energies less than the min
  while ( *union_energy_grid.begin() < d_min_electron_energy )
  {
      union_energy_grid.pop_front();
  }

  // Make sure the union energy grid values are unique
  union_energy_grid.unique();
}

} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_StandardEvaluatedElectronDataGenerator.cpp
//---------------------------------------------------------------------------//
