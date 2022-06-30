//---------------------------------------------------------------------------//
//!
//! \file   sample_scattering_distribution.cpp
//! \author Alex Robinson
//! \brief  sample the scattering distribution
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <signal.h>

// Trilinos Includes
#include <Teuchos_ParameterList.hpp>
#include <Teuchos_XMLParameterListCoreHelpers.hpp>
#include <Teuchos_CommandLineProcessor.hpp>
#include <Teuchos_FancyOStream.hpp>
#include <Teuchos_VerboseObject.hpp>

// MonteCarlo Includes
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "MonteCarlo_ElasticNeutronNuclearScatteringDistribution.hpp"
#include "MonteCarlo_NeutronNuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearReactionACEFactory.hpp"
#include "MonteCarlo_SimulationNeutronProperties.hpp"
#include "Utility_DirectionHelpers.hpp"

// Transparent NeutronNuclearScatteringDistributionACEFactory
class TransNeutronNuclearScatteringDistributionACEFactory : public MonteCarlo::NeutronNuclearScatteringDistributionACEFactory
{
public:
  TransNeutronNuclearScatteringDistributionACEFactory(
                        const std::string& table_name,
                        const double atomic_weight_ratio,
                        const Data::XSSNeutronDataExtractor& raw_nuclide_data )
  : MonteCarlo::NeutronNuclearScatteringDistributionACEFactory( table_name,
							 atomic_weight_ratio,
							 raw_nuclide_data )
  { /* ... */ }

  ~TransNeutronNuclearScatteringDistributionACEFactory()
  { /* ... */ }


  using MonteCarlo::NeutronNuclearScatteringDistributionACEFactory::getReactionAngularDist;
};


int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor clp;

  std::string isotope, cross_section_directory;
  double incoming_energy;
  int number_of_samples;
  int mt_number;

  clp.setOption( "isotope",
		 &isotope,
		 "ACE file name",
		 true );
  clp.setOption( "cross_sec_dir",
		 &cross_section_directory,
		 "Cross section directory",
		 true );
  clp.setOption( "incoming_energy",
		 &incoming_energy,
		 "The incoming particle energy",
		 true );
  clp.setOption( "number_of_samples",
		 &number_of_samples,
		 "The number of samples to make from the distribution",
		 true );
  clp.setOption( "mt_number",
		 &mt_number,
		 "The reaction mt number",
		 true );

  clp.throwExceptions( false );

  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler;
  Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor;
  Teuchos::RCP<TransNeutronNuclearScatteringDistributionACEFactory>
    neutron_distribution_factory;
  Teuchos::RCP<MonteCarlo::NuclearReactionACEFactory> reaction_factory;

  const Teuchos::RCP<Teuchos::FancyOStream> out =
    Teuchos::VerboseObjectBase::getDefaultOStream();

  Teuchos::CommandLineProcessor::EParseCommandLineReturn parse_return =
    clp.parse(argc,argv);

  if ( parse_return != Teuchos::CommandLineProcessor::PARSE_SUCCESSFUL )
  {
    clp.printHelpMessage( argv[0], *out );

    return parse_return;
  }

  std::string cross_sections_xml_file = cross_section_directory;
  cross_sections_xml_file += "/cross_sections.xml";

  Teuchos::RCP<Teuchos::ParameterList> cross_sections_table_info =
    Teuchos::getParametersFromXmlFile( cross_sections_xml_file );

  Teuchos::ParameterList& table_info =
    cross_sections_table_info->get<Teuchos::ParameterList>( isotope );

  // Convert the mt number to a reaction type
  MonteCarlo::NuclearReactionType reaction =
    MonteCarlo::convertMTNumberToNuclearReactionType( mt_number );

  ace_file_handler.reset( new Data::ACEFileHandler(
			      table_info.get<std::string>( "file_path" ),
			      table_info.get<std::string>( "table_name" ),
			      table_info.get<int>( "start_line" ) ) );

  xss_data_extractor.reset( new Data::XSSNeutronDataExtractor(
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
  neutron_distribution_factory.reset(
			     new TransNeutronNuclearScatteringDistributionACEFactory(
			         table_info.get<std::string>( "table_name" ),
				 ace_file_handler->getTableAtomicWeightRatio(),
				 *xss_data_extractor ) );

  Teuchos::ArrayRCP<double> energy_grid;
  energy_grid.deepCopy( xss_data_extractor->extractEnergyGrid() );

  reaction_factory.reset( new MonteCarlo::NuclearReactionACEFactory(
				   table_info.get<std::string>( "table_name" ),
				   ace_file_handler->getTableAtomicWeightRatio(),
				   ace_file_handler->getTableTemperature(),
				   energy_grid,
				   *xss_data_extractor ) );

  Teuchos::RCP<MonteCarlo::NuclearScatteringDistribution<MonteCarlo::NeutronState,MonteCarlo::NeutronState> > scattering_dist;

  neutron_distribution_factory->createScatteringDistribution(
							     reaction,
							     scattering_dist );

  std::unordered_map<MonteCarlo::NuclearReactionType,Teuchos::RCP<MonteCarlo::NuclearReaction> >
    scattering_reactions;

  reaction_factory->createScatteringReactions( scattering_reactions );

  Teuchos::RCP<MonteCarlo::NuclearReaction> scattering_reaction =
    scattering_reactions.find( reaction )->second;

  // Turn off free gas treatment
  MonteCarlo::SimulationNeutronProperties::setFreeGasThreshold( 1e-11 );

  MonteCarlo::NeutronState neutron( 0ull );
  MonteCarlo::ParticleBank bank;
  neutron.setEnergy( incoming_energy );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  double A = ace_file_handler->getTableAtomicWeightRatio();
  double arg = 1 - scattering_reaction->getThresholdEnergy()/incoming_energy;
  double cm_angle;
  for( unsigned i = 0; i < number_of_samples; ++i )
  {
    scattering_reaction->react( neutron, bank );
    //scattering_dist->scatterNeutron(neutron,
    //			     ace_file_handler->getTableTemperature() );

    cm_angle =
      ((neutron.getEnergy()/incoming_energy)*(A+1)*(A+1) - A*A*arg -1)/
      (2*A*sqrt(arg));

    std::cout << cm_angle << std::endl;

    neutron.setEnergy( incoming_energy );
  }
}

//---------------------------------------------------------------------------//
// end sample_scattering_distribution.cpp
//---------------------------------------------------------------------------//
