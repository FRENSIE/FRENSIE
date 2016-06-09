//---------------------------------------------------------------------------//
//!
//! \file   tstElectroatomCore.cpp
//! \author Luke Kersting
//! \brief  ElectroatomCore unit tests
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <algorithm>

// Trilinos Includes
#include <Teuchos_UnitTestHarness.hpp>
#include <Teuchos_VerboseObject.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomCore.hpp"
#include "MonteCarlo_BremsstrahlungElectroatomicReaction.hpp"
#include "MonteCarlo_AtomicExcitationElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAbsorptionElectroatomicReaction.hpp"
#include "MonteCarlo_VoidAtomicRelaxationModel.hpp"
#include "MonteCarlo_ElectronState.hpp"
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSEPRDataExtractor.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_InterpolationPolicy.hpp"
#include "Utility_PhysicalConstants.hpp"

//---------------------------------------------------------------------------//
// Testing Variables
//---------------------------------------------------------------------------//

Teuchos::RCP<MonteCarlo::ElectroatomCore> ace_electroatom_core;

//---------------------------------------------------------------------------//
// Testing Functions.
//---------------------------------------------------------------------------//
bool notEqualZero( const double value )
{
  return value != 0.0;
}

//---------------------------------------------------------------------------//
// Check that the total reaction can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getTotalReaction )
{
  const MonteCarlo::ElectroatomicReaction& total_reaction =
    ace_electroatom_core->getTotalReaction();

  double cross_section =
    total_reaction.getCrossSection( 2.000000000000E-03 );

  TEST_FLOATING_EQUALITY( cross_section,
                          9.258661418255E+03 + 1.965170000000E+08,
                          1e-12 );

  cross_section =
    total_reaction.getCrossSection( 4.000000000000E-04 );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.914234996439E+03 + 6.226820000000E+08,
                          1e-12 );

  cross_section =
    total_reaction.getCrossSection( 9.000000000000E-05 );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.249970966838E+03 + 1.160420000000E+09,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reaction can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getTotalAbsorptionReaction )
{
  const MonteCarlo::ElectroatomicReaction& absorption_reaction =
    ace_electroatom_core->getTotalAbsorptionReaction();

  double cross_section = absorption_reaction.getCrossSection( 1.000000000E-02 );

  TEST_FLOATING_EQUALITY( cross_section, 0.000000000000, 1e-12 );

  cross_section = absorption_reaction.getCrossSection( 2.000000000000E-03 );

  TEST_FLOATING_EQUALITY( cross_section, 0.000000000000, 1e-12 );

  cross_section = absorption_reaction.getCrossSection( 4.000000000000E-04 );

  TEST_FLOATING_EQUALITY( cross_section, 0.000000000000, 1e-12 );

  cross_section = absorption_reaction.getCrossSection( 9.000000000000E-05 );

  TEST_FLOATING_EQUALITY( cross_section, 0.000000000000, 1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the scattering reactions can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getScatteringReactions )
{
  const MonteCarlo::ElectroatomCore::ConstReactionMap& scattering_reactions =
    ace_electroatom_core->getScatteringReactions();

  TEST_EQUALITY_CONST( scattering_reactions.size(), 2 );

  const MonteCarlo::ElectroatomicReaction& ae_reaction =
    *(scattering_reactions.find(MonteCarlo::ATOMIC_EXCITATION_ELECTROATOMIC_REACTION)->second);

  const MonteCarlo::ElectroatomicReaction& b_reaction =
    *(scattering_reactions.find(MonteCarlo::BREMSSTRAHLUNG_ELECTROATOMIC_REACTION)->second);

  double cross_section =
    ae_reaction.getCrossSection( 2.000000000000E-03 ) +
     b_reaction.getCrossSection( 2.000000000000E-03 );

  TEST_FLOATING_EQUALITY( cross_section,
                          9.258661418255E+03 + 1.965170000000E+08,
                          1e-12 );

  cross_section = ae_reaction.getCrossSection( 4.000000000000E-04 ) +
                   b_reaction.getCrossSection( 4.000000000000E-04 );

  TEST_FLOATING_EQUALITY( cross_section,
                          8.914234996439E+03 + 6.226820000000E+08,
                          1e-12 );

  cross_section = ae_reaction.getCrossSection( 9.000000000000E-05 ) +
                   b_reaction.getCrossSection( 9.000000000000E-05 );

  TEST_FLOATING_EQUALITY( cross_section,
                          7.249970966838E+03 + 1.160420000000E+09,
                          1e-12 );
}

//---------------------------------------------------------------------------//
// Check that the absorption reactions can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getAbsorptionReactions )
{
  const MonteCarlo::ElectroatomCore::ConstReactionMap& absorption_reactions =
    ace_electroatom_core->getAbsorptionReactions();

  TEST_EQUALITY_CONST( absorption_reactions.size(), 0 );

}

//---------------------------------------------------------------------------//
// Check that miscellaneous reactions can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getMiscReactions )
{
  const MonteCarlo::ElectroatomCore::ConstReactionMap& misc_reactions =
    ace_electroatom_core->getMiscReactions();

  TEST_EQUALITY_CONST( misc_reactions.size(), 0 );
}

//---------------------------------------------------------------------------//
// Check that the atomic relaxation model can be returned
TEUCHOS_UNIT_TEST( ElectroatomCore, getAtomicRelaxationModel )
{
  Data::SubshellType vacancy = Data::K_SUBSHELL;

  MonteCarlo::ElectronState electron( 0u );
  electron.setEnergy( 1.0 );
  electron.setDirection( 0.0, 0.0, 1.0 );
  electron.setPosition( 0.0, 0.0, 0.0 );

  MonteCarlo::ParticleBank bank;

  const MonteCarlo::AtomicRelaxationModel& relaxation_model =
    ace_electroatom_core->getAtomicRelaxationModel();

  relaxation_model.relaxAtom( vacancy, electron, bank );

  TEST_EQUALITY_CONST( bank.size(), 0u );
}

//---------------------------------------------------------------------------//
// Custom main function
//---------------------------------------------------------------------------//
int main( int argc, char** argv )
{
  std::string test_ace_file_name, test_ace_table_name;

  Teuchos::CommandLineProcessor& clp = Teuchos::UnitTestRepository::getCLP();

  clp.setOption( "test_ace_file",
		 &test_ace_file_name,
		 "Test ACE file name" );
  clp.setOption( "test_ace_table",
		 &test_ace_table_name,
		 "Test ACE table name" );

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL ) {
    *out << "\nEnd Result: TEST FAILED" << std::endl;
    return parse_return;
  }

  {
    // Create a file handler and data extractor
    Teuchos::RCP<Data::ACEFileHandler> ace_file_handler(
				 new Data::ACEFileHandler( test_ace_file_name,
							   test_ace_table_name,
							   1u ) );
    Teuchos::RCP<Data::XSSEPRDataExtractor> xss_data_extractor(
                            new Data::XSSEPRDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );

    // Create the atomic excitation, bremsstrahlung cross sections
    Teuchos::ArrayRCP<double> energy_grid;
    energy_grid.deepCopy( xss_data_extractor->extractElectronEnergyGrid() );

    Teuchos::ArrayView<const double> raw_ae_cross_section =
      xss_data_extractor->extractExcitationCrossSection();

    Teuchos::ArrayView<const double>::iterator start =
      std::find_if( raw_ae_cross_section.begin(),
		    raw_ae_cross_section.end(),
		    notEqualZero );

    Teuchos::ArrayRCP<double> ae_cross_section;
    ae_cross_section.assign( start, raw_ae_cross_section.end() );

    unsigned ae_threshold_index =
      energy_grid.size() - ae_cross_section.size();

    // Extract the atomic excitation information data block (EXCIT)
    Teuchos::ArrayView<const double> excit_block(
				      xss_data_extractor->extractEXCITBlock() );

    // Extract the number of tabulated energies
    int size = excit_block.size()/2;

    // Extract the energy grid for atomic excitation energy loss
    Teuchos::Array<double> ae_energy_grid(excit_block(0,size));

    // Extract the energy loss for atomic excitation
    Teuchos::Array<double> energy_loss(excit_block(size,size));

    // Create the energy loss distributions
    MonteCarlo::AtomicExcitationElectronScatteringDistribution::AtomicDistribution
     ae_energy_loss_function;

    ae_energy_loss_function.reset(
      new Utility::TabularDistribution<Utility::LinLin>( ae_energy_grid,
                                                         energy_loss ) );

    Teuchos::RCP<const MonteCarlo::AtomicExcitationElectronScatteringDistribution>
                      ae_energy_loss_distribution;

    ae_energy_loss_distribution.reset(
    new MonteCarlo::AtomicExcitationElectronScatteringDistribution(
                      ae_energy_loss_function ) );

    Teuchos::RCP<MonteCarlo::ElectroatomicReaction> ae_reaction(
	    new MonteCarlo::AtomicExcitationElectroatomicReaction<Utility::LinLin>(
			    energy_grid,
			    ae_cross_section,
			    ae_threshold_index,
                ae_energy_loss_distribution ) );

    // Bremsstrahlung
    Teuchos::ArrayView<const double> raw_b_cross_section =
      xss_data_extractor->extractBremsstrahlungCrossSection();

    start = std::find_if( raw_b_cross_section.begin(),
		    raw_b_cross_section.end(),
		    notEqualZero );

    Teuchos::ArrayRCP<double> b_cross_section;
    b_cross_section.assign( start, raw_b_cross_section.end() );

    unsigned b_threshold_index =
      energy_grid.size() - b_cross_section.size();

    //! \todo Find real bremsstrahlung photon angular distribution
    // Create the tabular angular distribution
    Teuchos::Array<double> b_energy_bins( 3 ); // (MeV)
    b_energy_bins[0] = 1e-7;
    b_energy_bins[1] = 1.0;
    b_energy_bins[2] = 1e5;

    Teuchos::Array<double> b_angular_distribution_values( 3 );
    b_angular_distribution_values[0] =  0.0;
    b_angular_distribution_values[1] =  0.5;
    b_angular_distribution_values[2] =  1.0;

    Teuchos::RCP<const Utility::OneDDistribution> b_angular_distribution(
	  		    new Utility::TabularDistribution<Utility::LinLin>(
						b_energy_bins,
						b_angular_distribution_values ) );

    // Extract the elastic scattering information data block (BREMI)
    Teuchos::ArrayView<const double> bremi_block(
	  			      xss_data_extractor->extractBREMIBlock() );

    // Extract the number of tabulated distributions
    int N = bremi_block.size()/3;

    // Extract the electron energy grid for bremsstrahlung energy distributions
    Teuchos::Array<double> b_energy_grid(bremi_block(0,N));

    // Extract the table lengths for bremsstrahlung energy distributions
    Teuchos::Array<double> table_length(bremi_block(N,N));

    // Extract the offsets for bremsstrahlung energy distributions
    Teuchos::Array<double> offset(bremi_block(2*N,N));

    // Extract the bremsstrahlung photon energy distributions block (BREME)
    Teuchos::ArrayView<const double> breme_block =
      xss_data_extractor->extractBREMEBlock();

    // Create the bremsstrahlung scattering distributions
    MonteCarlo::BremsstrahlungElectronScatteringDistribution::BremsstrahlungDistribution
      b_scattering_function( N );

    for( unsigned n = 0; n < N; ++n )
    {
      b_scattering_function[n].first = b_energy_grid[n];

      b_scattering_function[n].second.reset(
	    new Utility::HistogramDistribution(
		   breme_block( offset[n], table_length[n] ),
		   breme_block( offset[n] + 1 + table_length[n], table_length[n]-1 ),
           true ) );
    }

	Teuchos::RCP<const MonteCarlo::BremsstrahlungElectronScatteringDistribution>
        b_scattering_distribution;

    b_scattering_distribution.reset(
        new MonteCarlo::BremsstrahlungElectronScatteringDistribution(
            b_scattering_function,
            xss_data_extractor->extractAtomicNumber() ) );


    // Create the bremsstrahlung scattering reaction
    Teuchos::RCP<MonteCarlo::ElectroatomicReaction> b_reaction(
	    new MonteCarlo::BremsstrahlungElectroatomicReaction<Utility::LinLin>(
            energy_grid,
            b_cross_section,
            b_threshold_index,
            b_scattering_distribution ) );

    // Create the reaction maps
    MonteCarlo::ElectroatomCore::ReactionMap scattering_reactions,
      absorption_reactions;

    scattering_reactions[ae_reaction->getReactionType()] = ae_reaction;

    scattering_reactions[b_reaction->getReactionType()] = b_reaction;

    // Create a void atomic relaxation model
    Teuchos::RCP<MonteCarlo::AtomicRelaxationModel> relaxation_model(
				   new MonteCarlo::VoidAtomicRelaxationModel );

    // Create a test electroatom core
    ace_electroatom_core.reset(
			  new MonteCarlo::ElectroatomCore( energy_grid,
							 scattering_reactions,
							 absorption_reactions,
							 relaxation_model,
							 false,
							 Utility::LinLin() ) );

    // Run the unit tests
    Teuchos::GlobalMPISession mpiSession( &argc, &argv );
  }

  const bool success = Teuchos::UnitTestRepository::runUnitTests( *out );

  if (success)
    *out << "\nEnd Result: TEST PASSED" << std::endl;
  else
    *out << "\nEnd Result: TEST FAILED" << std::endl;

  clp.printFinalTimerSummary(out.ptr());

  return (success ? 0 : 1);
}


//---------------------------------------------------------------------------//
// end tstElectroatomCore.cpp
//---------------------------------------------------------------------------//
