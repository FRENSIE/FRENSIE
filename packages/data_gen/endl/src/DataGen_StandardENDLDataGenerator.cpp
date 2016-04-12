//---------------------------------------------------------------------------//
//!
//! \file   DataGen_StandardENDLDataGenerator.cpp
//! \author Luke Kersting
//! \brief  The standard endl data generator class def.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_StandardENDLDataGenerator.hpp"
#include "Data_SubshellType.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_ContractException.hpp"
#include "Data_ENDLHelperWrappers.hpp"

namespace DataGen{

// Constructor
StandardENDLDataGenerator::StandardENDLDataGenerator( 
    const unsigned atomic_number,
    const std::string eadl_file_name,
    const std::string epdl_file_name,
    const std::string eedl_file_name )
  : ENDLDataGenerator( atomic_number ),
    d_eadl_file_name( eadl_file_name ),
    d_epdl_file_name( epdl_file_name ),
    d_eedl_file_name( eedl_file_name )
{
  // Make sure the atomic number is valid
  testPrecondition( atomic_number <= 100u );
}

// Populate the ENDL data container
void StandardENDLDataGenerator::populateENDLDataContainer(
			   Data::ENDLVolatileDataContainer&
			   data_container ) const
{
  // Set the atomic number
  this->setAtomicNumber( data_container );

  // Populate the relaxation data
  this->populateEADLDataContainer( data_container );

  // Populate the photon data
  this->populateEPDLDataContainer( data_container );

  // Populate the electron data
  this->populateEEDLDataContainer( data_container );
}

// Populate the EADL data container
void StandardENDLDataGenerator::populateEADLDataContainer(
			   Data::ENDLVolatileDataContainer&
			   data_container ) const
{
  // Set the relaxation data
  std::cout << std::endl << "Setting the relaxation data..." << std::endl;
  std::cout.flush();
  this->setRelaxationData( data_container );
  std::cout << "still needs to be implemented." << std::endl;
}

// Populate the EPDL data container
void StandardENDLDataGenerator::populateEPDLDataContainer(
			   Data::ENDLVolatileDataContainer&
			   data_container ) const
{
  // Set the photon data
  std::cout << std::endl << "Setting the photon data: " << std::endl;
  this->setPhotonData( data_container );
  std::cout << "still needs to be implemented." << std::endl;
}

// Populate the EEDL data container
void StandardENDLDataGenerator::populateEEDLDataContainer(
			   Data::ENDLVolatileDataContainer&
			   data_container ) const
{
  // Set the electron data
  std::cout << std::endl << "Setting the electron data: " << std::endl;
  this->setElectronData( data_container );
  std::cout << "done." << std::endl;
}


// Set the relaxation data
void StandardENDLDataGenerator::setRelaxationData( 
			   Data::ENDLVolatileDataContainer&
			   data_container ) const
{
  // Check if file exists
  if ( (bool)fileExistsUsingFortran( d_eadl_file_name.c_str(), 
                                     d_eadl_file_name.size() ) )
  {
    // Open eadl file
    Teuchos::RCP<Data::ENDLFileHandler> eadl_file_handler( 
      new Data::ENDLFileHandler( d_eadl_file_name ) );

    // Information in first header of the EADL file
    int atomic_number_in_table, 
        outgoing_particle_designator, 
        interpolation_flag;
    double atomic_weight;

    // Information in the second header of the EADL file
    int reaction_type, electron_shell;

    // subshells and subshell data
    std::vector<double> eadl_subshells, raw_subshell_data;
    std::vector<unsigned> endf_subshells;
    std::set<unsigned> endf_subshells_set;

    std::vector<double> indep_var, dep_var;


    std::cout << " Reading EADL Data file";
    std::cout.flush();

    // Process every table in the EADL file
    while( eadl_file_handler->validFile() && !eadl_file_handler->endOfFile() )
    {
      // Read first table header and determine which element is being processed
      eadl_file_handler->readFirstTableHeader( atomic_number_in_table,
                                               outgoing_particle_designator,
                                               atomic_weight,
                                               interpolation_flag );
      
      // Check that the EADL file is still valid (eof has not been reached)
      if( eadl_file_handler->endOfFile() )
      {
	    continue;
      }
        
      testPostcondition( atomic_number_in_table == 
                         data_container.getAtomicNumber() );

      // Read second table header and determine the reaction type
      eadl_file_handler->readSecondTableHeader( reaction_type,
                                                electron_shell );

      // Read and process the data in the current table, then store in the HDF5
      // file
      switch( reaction_type )
      {
    
      case 91912:
      {
        // Number of electrons in subshell

        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

  
        eadl_file_handler->processTwoColumnTable( 
            eadl_subshells,
            raw_subshell_data );

        // convert eadl subshell typ to endf subshell type
        endf_subshells.resize( eadl_subshells.size() );
        for ( int i = 0; i < eadl_subshells.size(); i++ )
        {
          unsigned shell = 
          Data::convertEADLDesignatorToENDFDesignator( eadl_subshells[i] );

          endf_subshells[i] = shell;
          endf_subshells_set.insert( shell );
        }

        // set subshell data
        data_container.setSubshells( endf_subshells_set );
/*
        // map subshell data
        std::map<unsigned,unsigned> subshell_data;
        mapEADLSubshellData( endf_subshells, raw_subshell_data, subshell_data );

        // set the subshell data
        data_container.setSubshellNumberOfElectrons( subshell_data );*/
        break;
      }
      case 91913:
      {
        // Binding energy of a subshell

        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

        eadl_file_handler->processTwoColumnTable( 
            eadl_subshells,
            raw_subshell_data );

        testPrecondition( eadl_subshells.size() == endf_subshells.size() );
/*
        // map subshell data
        std::map<unsigned,double> subshell_data;
        mapEADLSubshellData( endf_subshells, raw_subshell_data, subshell_data );

        // set the subshell data
        data_container.setSubshellKineticEnergy( subshell_data );*/

        break;
      }
      case 91914:
      {
        // Kinetic energy of a subshell

        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

        eadl_file_handler->processTwoColumnTable( 
            eadl_subshells,
            raw_subshell_data );

        testPrecondition( eadl_subshells.size() == endf_subshells.size() );
/*
        // map subshell data
        std::map<unsigned,double> subshell_data;
        mapEADLSubshellData( endf_subshells, raw_subshell_data, subshell_data );

        // set the subshell data
        data_container.setSubshellBindingEnergy( subshell_data );*/

        break;
      }
      case 91915:
      {
        // Average radius of a subshell

        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

        eadl_file_handler->processTwoColumnTable( 
            eadl_subshells,
            raw_subshell_data );

        testPrecondition( eadl_subshells.size() == endf_subshells.size() );
/*
        // map subshell data
        std::map<unsigned,double> subshell_data;
        mapEADLSubshellData( endf_subshells, raw_subshell_data, subshell_data );

        // set the subshell data
        data_container.setSubshellAverageRadius( subshell_data );*/

        break;
      }
      case 91921:
      {
        // Radiative level width of a subshell

        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

        eadl_file_handler->processTwoColumnTable( 
            eadl_subshells,
            raw_subshell_data );

        testPrecondition( eadl_subshells.size() == endf_subshells.size() );
/*
        // map subshell data
        std::map<unsigned,double> subshell_data;
        mapEADLSubshellData( endf_subshells, raw_subshell_data, subshell_data );

        // set the subshell data
        data_container.setSubshellRadiativeLevel( subshell_data );*/

        break;
      }
      case 91922:
      {
        // Non radiative level of a subshell

        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

        eadl_file_handler->processTwoColumnTable( 
            eadl_subshells,
            raw_subshell_data );

        testPrecondition( eadl_subshells.size() == endf_subshells.size() );
/*
        // map subshell data
        std::map<unsigned,double> subshell_data;
        mapEADLSubshellData( endf_subshells, raw_subshell_data, subshell_data );

        // set the subshell data
        data_container.setSubshellNonRadiativeLevel( subshell_data );*/

        break;
      }
      case 92931:
      {
std::cout << "91931" << std::endl;
        break;
      }
      case 92932:
      {
std::cout << "91932" << std::endl;
        break;
      }
     case 92933:
      {
        // The average number of particles per initial vacancy of a subshell

        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

        eadl_file_handler->processTwoColumnTable( 
            eadl_subshells,
            raw_subshell_data );

        testPrecondition( eadl_subshells.size() == endf_subshells.size() );
/*
        // map subshell data
        std::map<unsigned,unsigned> subshell_data;
        mapEADLSubshellData( endf_subshells, raw_subshell_data, subshell_data );

        // set the subshell data
        data_container.setAverageParticlesPerInitialVacancy( subshell_data );*/

        break;
      }
     case 92934:
      {
        // The average energy of particles per initial vacancy

        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

        eadl_file_handler->processTwoColumnTable( 
            eadl_subshells,
            raw_subshell_data );

        testPrecondition( eadl_subshells.size() == endf_subshells.size() );
/*
        // map subshell data
        std::map<unsigned,double> subshell_data;
        mapEADLSubshellData( endf_subshells, raw_subshell_data, subshell_data );

        // set the subshell data
        data_container.setAverageParitcleEnergyPerInitialVacancy(
            subshell_data );*/

        break;
      }
     case 92935:
      {
        // The local deposition per initial vacancy of a subshell

        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

        eadl_file_handler->processTwoColumnTable( 
            eadl_subshells,
            raw_subshell_data );

        testPrecondition( eadl_subshells.size() == endf_subshells.size() );
/*
        // map subshell data
        std::map<unsigned,double> subshell_data;
        mapEADLSubshellData( endf_subshells, raw_subshell_data, subshell_data );

        // set the subshell data
        data_container.setLocalDepositionPerInitialVacancy( subshell_data );*/

        break;
      }
      default:
        // Unknown reaction type found
      {
	  bool known_reaction_type = false;
	  std::cout << known_reaction_type <<
      " Fatal Error: An unknown reaction type was encountered while processing the EADL file.";
      std::cout.flush();
      }
        break;
      }
    }

    // Close the EADL file
    eadl_file_handler->closeENDLFile();

    // Set the subshells
    data_container.setSubshells( endf_subshells_set );
  }
  else
  {
    std::cout << "\033[1;31mWARNING:\033[0m EADL file " + d_eadl_file_name + 
    " does not exists. No EADL data will be generated!" << std::endl;
  }
}

// Set the photon data
void StandardENDLDataGenerator::setPhotonData( 
			   Data::ENDLVolatileDataContainer&
			   data_container ) const
{
  // Check if file exists
  if ( (bool)fileExistsUsingFortran( d_epdl_file_name.c_str(), 
                                     d_epdl_file_name.size() ) )
  {
    // Open epdl file
    Teuchos::RCP<Data::ENDLFileHandler> epdl_file_handler( 
      new Data::ENDLFileHandler( d_epdl_file_name ) );

    // Close the EPDL file
    epdl_file_handler->closeENDLFile();
  }
  else
  {
    std::cout << "\033[1;31mWARNING:\033[0m EPDL file " + d_epdl_file_name + 
    " does not exists. No EADL data will be generated!" << std::endl;
  }
}


// Process EEDL file
/*! \details This function uses the Data::ENDLFileHandler to read the
 * EEDL data file. The data that is read is then processed into an appropriate
 * format and finally stored in the necessary HDF5 file. 
 */
void StandardENDLDataGenerator::setElectronData( 
    Data::ENDLVolatileDataContainer& data_container ) const
{ 
  // Check if file exists
  if ( (bool)fileExistsUsingFortran( d_eedl_file_name.c_str(), 
                                     d_eedl_file_name.size() ) )
    {
    // Open eedl file
    Teuchos::RCP<Data::ENDLFileHandler> eedl_file_handler( 
      new Data::ENDLFileHandler( d_eedl_file_name ) );

    // Information in first header of the EEDL file
    int atomic_number_in_table, 
        outgoing_particle_designator, 
        interpolation_flag;
    double atomic_weight;

    // Information in the second header of the EEDL file
    int reaction_type, electron_shell;
    unsigned endf_subshell;

    // array of all the subshells read
    std::set<unsigned> endf_subshells;

    // The elastic angular distribution energy grid and pdf
    std::vector<double> elastic_angular_energy_grid;
    std::map<double,std::vector<double> > elastic_pdf;


    std::cout << " Reading EEDL Data file";
    std::cout.flush();

    // Process every table in the EEDL file
    while( eedl_file_handler->validFile() && !eedl_file_handler->endOfFile() )
    {
      // Read first table header and determine which element is being processed
      eedl_file_handler->readFirstTableHeader( atomic_number_in_table,
                                               outgoing_particle_designator,
                                               atomic_weight,
                                               interpolation_flag );
      
      // Check that the EEDL file is still valid (eof has not been reached)
      if( eedl_file_handler->endOfFile() )
      {
	    continue;
      }
        
      testPostcondition( atomic_number_in_table == 
                         data_container.getAtomicNumber() );

      // Read second table header and determine the reaction type
      eedl_file_handler->readSecondTableHeader( reaction_type,
                                                electron_shell );

      if ( electron_shell > 0 )
      {
        // Convert subshell number to endf number
        endf_subshell = 
          Data::convertEADLDesignatorToENDFDesignator( electron_shell );

        // insert subshell to set
        endf_subshells.insert( endf_subshell );
        
      }

      // Read and process the data in the current table, then store in the HDF5
      // file
      switch( reaction_type )
      {
    
      case 7000:
      {
        // Integrated elastic transport cross section data

        // Interpolation should always be LogLog = 5 
        testPrecondition( interpolation_flag == 5 )

        std::vector<double> energy_grid, cross_section;
        eedl_file_handler->processTwoColumnTable( energy_grid, 
                                                  cross_section );
        
        data_container.setElasticEnergyGrid( energy_grid );
        data_container.setElasticTransportCrossSection( cross_section );

        std::cout << ".";
        std::cout.flush();   
        break;
      }
      case 8000: 
      {
        // Integrated large angle scattering cross section data

        // Interpolation should always be LogLog = 5 
        testPrecondition( interpolation_flag == 5 )

        std::vector<double> energy_grid, cross_section;
        eedl_file_handler->processTwoColumnTable( energy_grid, 
                                                  cross_section );

        // Test that the cutoff energy grid is the same as the transport
        testPostcondition( energy_grid.size() == 
                           data_container.getElasticEnergyGrid().size() );

        data_container.setCutoffElasticCrossSection( cross_section );

        std::cout << ".";
        std::cout.flush();     
        break;
      }
      case 8011:
      {
        // Average energy to residual atom from elastic scattering
        
        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

        std::vector<double> residual_incident_energy, residual_energy;
        eedl_file_handler->processTwoColumnTable( residual_incident_energy, 
                                                  residual_energy );

        data_container.setCutoffElasticResidualIncidentEnergy( 
          residual_incident_energy );
        data_container.setCutoffElasticResidualEnergy( residual_energy );

        std::cout << ".";
        std::cout.flush(); 
        break;
      }
      case 8010:
      {
        // Average energy of scattered electron from elastic scattering
        
        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

        std::vector<double> scattered_incident_energy, scattered_energy;
        eedl_file_handler->processTwoColumnTable( scattered_incident_energy, 
                                                  scattered_energy );

        data_container.setCutoffElasticScatteredElectronIncidentEnergy( 
          scattered_incident_energy );
        data_container.setCutoffElasticScatteredElectronEnergy( 
          scattered_energy );

        std::cout << ".";
        std::cout.flush();    
        break;
      }
      case 8022:
      {
        // Elastic angular distribution of the scattered electron data

        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

        std::map<double,std::vector<double> > elastic_angle;

        eedl_file_handler->processThreeColumnTable( 
              elastic_angular_energy_grid, 
              elastic_angle,
              elastic_pdf );

        data_container.setCutoffElasticAngularEnergyGrid( 
          elastic_angular_energy_grid );
        data_container.setCutoffElasticAngles( elastic_angle );
        data_container.setCutoffElasticPDF( elastic_pdf ); 

        std::cout << ".";
        std::cout.flush(); 
        break;
      }
      case 10000:
      {
        // Integrated total elastic cross section data

        // Interpolation should always be LogLog = 5 
        testPrecondition( interpolation_flag == 5 )

        std::vector<double> energy_grid, cross_section;
        eedl_file_handler->processTwoColumnTable( energy_grid, 
                                                  cross_section );

        // Test that the energy grid is the same as the transport and cutoff
        testPostcondition( energy_grid.size() == 
                           data_container.getElasticEnergyGrid().size() );

        data_container.setTotalElasticCrossSection( cross_section );

        std::cout << ".";
        std::cout.flush(); 
        break;
      }
      case 81000:
      {
        // Extract the integrated ionization (electroionization) cross section

        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

        std::vector<double> energy_grid, cross_section;
        eedl_file_handler->processTwoColumnTable( energy_grid, 
                                                  cross_section );

        data_container.setElectroionizationCrossSectionEnergyGrid( 
          endf_subshell, 
          energy_grid );
        data_container.setElectroionizationCrossSection( 
          endf_subshell, 
          cross_section );

        std::cout << ".";
        std::cout.flush();     
        break;
      }
      case 81010:
      {
        // Average energy of primary and secondary electrons from ionization

        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

        std::vector<double> incident_energy, average_outgoing_energy;
        eedl_file_handler->processTwoColumnTable( incident_energy, 
                                                  average_outgoing_energy );

        // Average energy of electron from ionization
        if ( outgoing_particle_designator == 9 ) // 9 = electron
        {
          data_container.setElectroionizationAverageScatteredElectronIncidentEnergy(
              endf_subshell,
              incident_energy );
          data_container.setElectroionizationAverageScatteredElectronEnergy(
              endf_subshell,
              average_outgoing_energy );
        }
        // Average energy of secondary electron from ionization
        else
        {
          // The outgoing particle designator should be electron as recoil (19)
          testPrecondition( outgoing_particle_designator == 19 );

          data_container.setElectroionizationAverageRecoilElectronIncidentEnergy(
              endf_subshell,
              incident_energy );
          data_container.setElectroionizationAverageRecoilElectronEnergy(
              endf_subshell,
              average_outgoing_energy );
        }

        std::cout << ".";
        std::cout.flush(); 
        break;
      }
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

        eedl_file_handler->processThreeColumnTable( 
              electron_energy_grid, 
              electroionization_recoil_energy,
              electroionization_recoil_pdf );  


        data_container.setElectroionizationRecoilEnergyGrid( 
                          endf_subshell,
                          electron_energy_grid );

        data_container.setElectroionizationRecoilEnergy( 
                          endf_subshell,
                          electroionization_recoil_energy );

        data_container.setElectroionizationRecoilPDF( 
                          endf_subshell,
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
        std::vector<double> energy_grid, cross_section;
        eedl_file_handler->processTwoColumnTable( energy_grid, 
                                                  cross_section );

        data_container.setBremsstrahlungCrossSectionEnergyGrid( energy_grid );
        data_container.setBremsstrahlungCrossSection( cross_section );

        std::cout << ".";
        std::cout.flush();     
        break;
      }
      case 82010:
      {
        // Average energy of secondary particles from bremsstrahlung

        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

        std::vector<double> incident_energy, average_outgoing_energy;
        eedl_file_handler->processTwoColumnTable( incident_energy, 
                                                  average_outgoing_energy );

        // Average energy of secondary photon from bremsstrahlung
        if ( outgoing_particle_designator == 7 ) // 7 = photon
        {
          data_container.setBremsstrahlungAveragePhotonIncidentEnergy(
              incident_energy );
          data_container.setBremsstrahlungAveragePhotonEnergy(
              average_outgoing_energy );
        }
        // Average energy of secondary electron from bremsstrahlung
        else
        {
          // The outgoing particle designator should be electron (9)
          testPrecondition( outgoing_particle_designator == 9 );

          data_container.setBremsstrahlungAverageElectronIncidentEnergy(
              incident_energy );
          data_container.setBremsstrahlungAverageElectronEnergy(
              average_outgoing_energy );
        }

        std::cout << ".";
        std::cout.flush(); 
        break;
      }
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

        eedl_file_handler->processThreeColumnTable( 
              electron_energy_grid, 
              bremsstrahlung_photon_energy,
              bremsstrahlung_photon_pdf );  

        data_container.setBremsstrahlungPhotonEnergyGrid( electron_energy_grid );

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
        // Extract the integrated (atomic) excitation cross section

        // Interpolation should always be LinLin = 0 
        testPrecondition( interpolation_flag == 0 )

        std::vector<double> energy_grid, cross_section;
        eedl_file_handler->processTwoColumnTable( energy_grid, cross_section );

        data_container.setAtomicExcitationEnergyGrid( energy_grid );
        data_container.setAtomicExcitationCrossSection( cross_section );

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

        eedl_file_handler->processTwoColumnTable( 
              atomic_excitation_energy_grid, 
              atomic_excitation_energy_loss );

        testPostcondition( atomic_excitation_energy_grid.size() == 
                           data_container.getAtomicExcitationEnergyGrid().size() );

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
    eedl_file_handler->closeENDLFile();

    // Set the subshells
    data_container.setSubshells( endf_subshells );

  /*
    // Set the screened Rutherford cross section data
    setScreenedRutherfordData( cutoff_elastic_cross_section, 
                               total_elastic_cross_section,
                               elastic_angular_energy_grid, 
                               elastic_pdf,
                               data_container );
  */
  }
  else
  {
    std::cout << "\033[1;31mWARNING:\033[0m EEDL file " + d_eedl_file_name + 
    " does not exists. No EEDL data will be generated!" << std::endl;
  }
}

/*
// Set the screened rutherford data
void StandardENDLDataGenerator::setScreenedRutherfordData( 
    const Teuchos::RCP<const Utility::OneDDistribution>& 
        cutoff_elastic_cross_section, 
    const Teuchos::RCP<const Utility::OneDDistribution>& 
        total_elastic_cross_section,
    const std::vector<double>& elastic_angular_energy_grid,
    const std::map<double,std::vector<double> >& elastic_pdf,
    Data::ENDLVolatileDataContainer& data_container ) const
{
  // Calculate Moliere's screening constant and the screened rutherford normalization constant
  std::vector<double> moliere_screening_constant, 
                      screened_rutherford_normalization_constant;
  
  // iterate through all angular energy bins
  for ( int i = 0; i < elastic_angular_energy_grid.size(); ++i )
  {
    // get the angular energy bin
    double energy = elastic_angular_energy_grid[i];

    // get the screened rutherford cross section
    double sr_cross_section = 
        ( total_elastic_cross_section->evaluate( energy ) -
        cutoff_elastic_cross_section->evaluate( energy ) );

    if ( sr_cross_section == 0.0 )
    {
    /* in order to not calculate negative the screened Rutherford cross section
     * must be greater than ( cutoff_pdf*cutoff_angle ). It should also be small
     * enough to give a negligable contribution to the overall cross section.
     * This can be accomplished by setting eta slightly greater then the cutoff
     * angle.
     *//*
    // get the pdf value at the cutoff angle for the given energy
    double cutoff_pdf = elastic_pdf.find( energy )->second.front(); 

    // calculate Moliere's screening constant
    moliere_screening_constant.push_back( 1.01*d_cutoff_angle );

    // calculate the screened rutherford normalization constant
    screened_rutherford_normalization_constant.push_back( cutoff_pdf*
        ( 2.01*d_cutoff_angle )*( 2.01*d_cutoff_angle ) );
    }
    else
    {
    // get the pdf value at the cutoff angle for the given energy
    double cutoff_pdf = elastic_pdf.find( energy )->second.front(); 

    // calculate Moliere's screening constant
    moliere_screening_constant.push_back( d_cutoff_angle/( 
        sr_cross_section/( d_cutoff_angle*cutoff_pdf ) - 1.0 ) );

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
*/
} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_StandardENDLDataGenerator.cpp
//---------------------------------------------------------------------------//
