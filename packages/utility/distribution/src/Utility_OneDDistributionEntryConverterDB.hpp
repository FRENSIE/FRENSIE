//---------------------------------------------------------------------------//
//!
//! \file   Utility_OneDDistributionEntryConverterDB.hpp
//! \author Alex Robinson
//! \brief  1D distribution parameter entry converter database declaration
//!
//---------------------------------------------------------------------------//

#ifndef UTILITY_ONE_D_DISTRIBUTION_ENTRY_CONVERTER_DB_HPP
#define UTILITY_ONE_D_DISTRIBUTION_ENTRY_CONVERTER_DB_HPP

// Std Lib Includes
#include <memory>

// Boost Includes
#include <boost/unordered_map.hpp>

// Trilinos Includes
#include <Teuchos_RCP.hpp>
#include <Teuchos_ParameterEntry.hpp>

// FRENSIE Includes
#include "Utility_OneDDistributionEntryConverter.hpp"
#include "Utility_StandardOneDDistributionEntryConverter.hpp"
#include "Utility_DeltaDistribution.hpp"
#include "Utility_DiscreteDistribution.hpp"
#include "Utility_ExponentialDistribution.hpp"
#include "Utility_HistogramDistribution.hpp"
#include "Utility_NormalDistribution.hpp"
#include "Utility_PowerDistribution.hpp"
#include "Utility_TabularDistribution.hpp"
#include "Utility_EquiprobableBinDistribution.hpp"
#include "Utility_UniformDistribution.hpp"
#include "Utility_PolynomialDistribution.hpp"

namespace Utility{

//! The 1D distribution parameter entry converter database
class OneDDistributionEntryConverterDB
{
  
public:

  //! Add a converter to the database
  static void addConverter( 
     const std::shared_ptr<OneDDistributionEntryConverter>& converter_to_add );

  //! Get the appropriate converter for the given parameter entry
  static const OneDDistributionEntryConverter& getConverter(
		    const Teuchos::RCP<const Teuchos::ParameterEntry>& entry );

  //! Get the OneDDistribution from the given parameter entry
  static Teuchos::RCP<OneDDistribution> convertEntryToRCP(
		    const Teuchos::RCP<const Teuchos::ParameterEntry>& entry );

  //! Get the OneDDistribution from the given parameter entry
  static std::shared_ptr<OneDDistribution> convertEntryToSharedPtr(
		    const Teuchos::RCP<const Teuchos::ParameterEntry>& entry );
  
private:

  // Constructor
  OneDDistributionEntryConverterDB();

  // Initialize the class
  static bool initialize();

  // Typedef for the converter map
  typedef boost::unordered_map<std::string, std::shared_ptr<OneDDistributionEntryConverter> > ConverterMap;

  static ConverterMap master_map;

  // Records if the class has been initialized
  static const bool initialized;
};

} // end Utility namespace

//! Add a OneDDistribution converter to the database
#define UTILITY_ADD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER(T) \
  Utility::OneDDistributionEntryConverterDB::addConverter( \
           std::shared_ptr<Utility::OneDDistributionEntryConverter>( \
                   new Utility::StandardOneDDistributionEntryConverter< T > ) )

//! Set up the database
#define UTILITY_ONE_D_DISTRIBUTION_ENTRY_CONVERTER_DB_SETUP() \
  UTILITY_ADD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER(DeltaDistribution);	\
  UTILITY_ADD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER(DiscreteDistribution); \
  UTILITY_ADD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER(ExponentialDistribution); \
  UTILITY_ADD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER(HistogramDistribution); \
  UTILITY_ADD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER(NormalDistribution);	\
  UTILITY_ADD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER(PowerDistribution<1u>); \
  UTILITY_ADD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER(PowerDistribution<2u>); \
  UTILITY_ADD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER(TabularDistribution<LinLin>);\
  UTILITY_ADD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER(TabularDistribution<LogLin>);\
  UTILITY_ADD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER(TabularDistribution<LinLog>);\
  UTILITY_ADD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER(TabularDistribution<LogLog>);\
  UTILITY_ADD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER(EquiprobableBinDistribution); \
  UTILITY_ADD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER(UniformDistribution);	\
  UTILITY_ADD_ONE_D_DISTRIBUTION_ENTRY_CONVERTER(PolynomialDistribution)

#endif // end UTILITY_ONE_D_DISTRIBUTION_ENTRY_CONVERTER_DB_HPP

//---------------------------------------------------------------------------//
// end Utility_OneDDistributionEntryConverterDB.hpp
//---------------------------------------------------------------------------//
