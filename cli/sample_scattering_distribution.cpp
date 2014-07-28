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

// Facemc Includes
#include "Data_ACEFileHandler.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Facemc_ElasticNeutronScatteringDistribution.hpp"
#include "Facemc_NeutronScatteringDistributionFactory.hpp"
#include "Facemc_SimulationProperties.hpp"
#include "Utility_DirectionHelpers.hpp"

// Transparent NeutronScatteringDistributionFactory
class TransNeutronScatteringDistributionFactory : public Facemc::NeutronScatteringDistributionFactory
{
public:
  TransNeutronScatteringDistributionFactory(
                           const std::string& table_name,
                           const double atomic_weight_ratio,
                           const Teuchos::ArrayView<const double>& mtr_block,
                           const Teuchos::ArrayView<const double>& tyr_block,
                           const Teuchos::ArrayView<const double>& land_block,
                           const Teuchos::ArrayView<const double>& and_block,
                           const Teuchos::ArrayView<const double>& ldlw_block,
                           const Teuchos::ArrayView<const double>& dlw_block )
  : Facemc::NeutronScatteringDistributionFactory( table_name,
                                                  atomic_weight_ratio,
                                                  mtr_block,
                                                  tyr_block,
                                                  land_block,
                                                  and_block,
                                                  ldlw_block,
                                                  dlw_block )
  { /* ... */ }
  
  ~TransNeutronScatteringDistributionFactory()
  { /* ... */ }


  using Facemc::NeutronScatteringDistributionFactory::getReactionAngularDist;
};


int main( int argc, char** argv )
{
  Teuchos::CommandLineProcessor clp;

  std::string isotope, cross_section_directory;
  double incoming_energy;
  int number_of_samples;

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
  clp.throwExceptions( false );

  Teuchos::RCP<Data::ACEFileHandler> ace_file_handler;
  Teuchos::RCP<Data::XSSNeutronDataExtractor> xss_data_extractor;
  Teuchos::RCP<TransNeutronScatteringDistributionFactory> 
    neutron_distribution_factory;

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

  ace_file_handler.reset( new Data::ACEFileHandler( 
			      table_info.get<std::string>( "file_path" ),
			      table_info.get<std::string>( "table_name" ),
			      table_info.get<int>( "start_line" ) ) );
						    
  xss_data_extractor.reset( new Data::XSSNeutronDataExtractor( 
				      ace_file_handler->getTableNXSArray(),
				      ace_file_handler->getTableJXSArray(),
				      ace_file_handler->getTableXSSArray() ) );
  neutron_distribution_factory.reset(
			     new TransNeutronScatteringDistributionFactory(
			         table_info.get<std::string>( "table_name" ),
				 ace_file_handler->getTableAtomicWeightRatio(),
				 xss_data_extractor->extractMTRBlock(),
				 xss_data_extractor->extractTYRBlock(),
				 xss_data_extractor->extractLANDBlock(),
				 xss_data_extractor->extractANDBlock(),
				 xss_data_extractor->extractLDLWBlock(),
				 xss_data_extractor->extractDLWBlock() ) );

  Teuchos::RCP<Facemc::NeutronScatteringDistribution> scattering_dist;
  
  neutron_distribution_factory->createScatteringDistribution(
						Facemc::N__N_ELASTIC_REACTION,
						scattering_dist );

  // Turn off free gas treatmen
  Facemc::SimulationProperties::setFreeGasThreshold( 1e-11 );

  Facemc::NeutronState neutron( 0ull );
  neutron.setEnergy( incoming_energy );
  neutron.setDirection( 0.0, 0.0, 1.0 );
  double A = ace_file_handler->getTableAtomicWeightRatio();
  double cm_angle;
  for( unsigned i = 0; i < number_of_samples; ++i )
  {
    scattering_dist->scatterNeutron(neutron, 
				     ace_file_handler->getTableTemperature() );
    cm_angle = (neutron.getEnergy()/incoming_energy*(A+1)*(A+1) - A*A -1)/(2*A);
    
    std::cout << cm_angle << std::endl;

    neutron.setEnergy( incoming_energy );
  }
}

//---------------------------------------------------------------------------//
// end sample_scattering_distribution.cpp
//---------------------------------------------------------------------------//
