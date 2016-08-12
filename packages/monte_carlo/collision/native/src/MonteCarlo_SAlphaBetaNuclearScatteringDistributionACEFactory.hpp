//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_SAlphaBetaNuclearScatteringDistributionACEFactory.hpp
//! \author Eli Moll
//! \brief  S(alpha,beta) nuclear scattering distribution factory base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_S_ALPHA_BETA_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP
#define MONTE_CARLO_S_ALPHA_BETA_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

// FRENSIE Includes
#include "MonteCarlo_NuclearScatteringDistributionACEFactory.hpp"
#include "MonteCarlo_NuclearScatteringDistributionACEFactoryHelper.hpp"
#include "MonteCarlo_NuclearReactionType.hpp"
#include "Data_XSSNeutronDataExtractor.hpp"
#include "Data_XSSSabDataExtractor.hpp"

namespace MonteCarlo{

//! The S(alpha,beta) nuclear scattering distribution factory base class
class SAlphaBetaNuclearScatteringDistributionACEFactory : public NuclearScatteringDistributionACEFactory<MonteCarlo::NeutronState,MonteCarlo::NeutronState>
{

public:

  //! The nuclear scattering distribution type to be created
  typedef NuclearScatteringDistribution<MonteCarlo::NeutronState,
					MonteCarlo::NeutronState>
  DistributionType;

  //! Basic Constructor
  SAlphaBetaNuclearScatteringDistributionACEFactory( 
            const std::string& table_name,
					  const double atomic_weight_ratio,
					  const Data::XSSNeutronDataExtractor& raw_nuclide_data,
					  const Data::XSSSabDataExtractor& sab_nuclide_data );

  //! Constructor
  SAlphaBetaNuclearScatteringDistributionACEFactory(
			    const std::string& table_name,
			    const double atomic_weight_ratio,
			    const Teuchos::ArrayView<const double> mtr_block,
			    const Teuchos::ArrayView<const double> tyr_block,
			    const Teuchos::ArrayView<const double> land_block,
			    const Teuchos::ArrayView<const double> and_block,
			    const Teuchos::ArrayView<const double> ldlw_block,
			    const Teuchos::ArrayView<const double> dlw_block,
			    const Teuchos::ArrayView<const double> itie_block,
			    const Teuchos::ArrayView<const double> itxe_block,
			    const Teuchos::ArrayView<const double> itce_block,
			    const Teuchos::ArrayView<const double> itca_block );

  //! Constructor (no TYR block)
  SAlphaBetaNuclearScatteringDistributionACEFactory(
			    const std::string& table_name,
			    const double atomic_weight_ratio,
			    const Teuchos::ArrayView<const double> mtr_block,
			    const Teuchos::ArrayView<const double> land_block,
			    const Teuchos::ArrayView<const double> and_block,
			    const Teuchos::ArrayView<const double> ldlw_block,
			    const Teuchos::ArrayView<const double> dlw_block,
			    const Teuchos::ArrayView<const double> itie_block,
			    const Teuchos::ArrayView<const double> itxe_block,
			    const Teuchos::ArrayView<const double> itce_block,
			    const Teuchos::ArrayView<const double> itca_block );

  //! Destructor
  virtual ~SAlphaBetaNuclearScatteringDistributionACEFactory()
  { /* ... */ }

  //! Populate the S(alpha,beta) data
  void initializeSAlphaBetaData( 
          const Teuchos::ArrayView<const double> itie_block,
          const Teuchos::ArrayView<const double> itxe_block,
			    const Teuchos::ArrayView<const double> itce_block,
			    const Teuchos::ArrayView<const double> itca_block );  
    
  //! Create S(alpha,beta) distributions
  void createSAlphaBetaScatteringDistributions(
    const unsigned reaction_type,
	  Teuchos::RCP<DistributionType>& distribution );

protected:

  //! Initialize the factory
  void initialize( 
       const Teuchos::ArrayView<const double> mtr_block,
		   const Teuchos::ArrayView<const double> tyr_block,
		   const Teuchos::ArrayView<const double> land_block,
		   const Teuchos::ArrayView<const double> and_block,
		   const Teuchos::ArrayView<const double> ldlw_block,
		   const Teuchos::ArrayView<const double> dlw_block,
		   const Teuchos::ArrayView<const double> itie_block,
		   const Teuchos::ArrayView<const double> itxe_block,
 	     const Teuchos::ArrayView<const double> itce_block,
	 	   const Teuchos::ArrayView<const double> itca_block  );

  //! Initialize the factory (no TYR block)
  void initialize( 
       const Teuchos::ArrayView<const double> mtr_block,
		   const Teuchos::ArrayView<const double> land_block,
		   const Teuchos::ArrayView<const double> and_block,
		   const Teuchos::ArrayView<const double> ldlw_block,
		   const Teuchos::ArrayView<const double> dlw_block,
		   const Teuchos::ArrayView<const double> itie_block,
		   const Teuchos::ArrayView<const double> itxe_block,
			 const Teuchos::ArrayView<const double> itce_block,
			 const Teuchos::ArrayView<const double> itca_block  );

  // The table name
  std::string d_table_name;

  // The atomic weight ratio
  const double d_atomic_weight_ratio;
			 
  // Set the inelastic S(alpha,beta) energies
	void setInelasticSAlphaBetaEnergies();
	
	// Set the inelastic S(alpha,beta) distribution locators
	void setInelasticSAlphaBetaDistributionLocators();
	
	// Set the inelastic S(alpha,beta) outgoing energies
	void setInelasticSAlphaBetaOutgoingEnergies();
			
	// Inelastic S(alpha,beta) energies
	Teuchos::ArrayView<const double> d_inelastic_energies;
	
	// Inelastic S(alpha,beta) angular locators
	Teuchos::ArrayView<const double> d_inelastic_distribution_locators;
	
	// Inelastic S(alpha,beta) outgoing energies
	Teuchos::ArrayView<const double> d_inelastic_outgoing_energies;
	
	// Inelastic S(alpha,beta) incoming block
	Teuchos::ArrayView<const double> d_itie_block;
	
	// Inelastic S(alpha,beta) outgoing distributions block
	Teuchos::ArrayView<const double> d_itxe_block;
	
	// Elastic S(alpha,beta) block
	Teuchos::ArrayView<const double> d_itce_block;
	
	// Elastic S(alpha,beta) angular block
	Teuchos::ArrayView<const double> d_itca_block;
		   
};

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_S_ALPHA_BETA_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SAlphaBetaNuclearScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
