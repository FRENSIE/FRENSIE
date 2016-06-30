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

namespace MonteCarlo{

//! The S(alpha,beta) nuclear scattering distribution factory base class
template<typename IncomingParticleType, typename OutgoingParticleType>
class SAlphaBetaNuclearScatteringDistributionACEFactory : public NuclearScatteringDistributionACEFactory, 
 private NuclearScatteringDistributionACEFactoryHelper<IncomingParticleType,OutgoingParticleType>
{

public:

  //! The nuclear scattering distribution type to be created
  typedef NuclearScatteringDistribution<IncomingParticleType,
					OutgoingParticleType>
  DistributionType;

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
			    const Teuchos::ArrayView<const double> itxe_block,
			    const Teuchos::ArrayView<const double> itce_block,
			    const Teuchos::ArrayView<const double> itca_block  );

  //! Destructor
  virtual ~SAlphaBetaNuclearScatteringDistributionACEFactory()
  { /* ... */ }

  //! Check if there is an elastic S(alpha,beta) reaction
  bool isElasticSAlphaBeta( 
    const Teuchos::ArrayView<const double> itce_block );
  
  //! Check if the elastic S(alpha,beta) reaction is implicit
  bool isImplicitElasticSAlphaBeta(
    const Teuchos::ArrayView<const double> itca_block );
    
  //! Create S(alpha,beta) distributions
  void createSAlphaBetaScatteringDistributions(
    const unsigned reaction_type,
	  Teuchos::RCP<DistributionType>& distribution );

protected:

  //! Basic Constructor
  SAlphaBetaNuclearScatteringDistributionACEFactory( 
            const std::string& table_name,
					  const double atomic_weight_ratio );

  //! Initialize the factory
  void initialize( const Teuchos::ArrayView<const double> mtr_block,
		   const Teuchos::ArrayView<const double> tyr_block,
		   const Teuchos::ArrayView<const double> land_block,
		   const Teuchos::ArrayView<const double> and_block,
		   const Teuchos::ArrayView<const double> ldlw_block,
		   const Teuchos::ArrayView<const double> dlw_block,
		   const Teuchos::ArrayView<const double> itxe_block,
 	     const Teuchos::ArrayView<const double> itce_block,
	 	   const Teuchos::ArrayView<const double> itca_block  );

  //! Initialize the factory (no TYR block)
  void initialize( const Teuchos::ArrayView<const double> mtr_block,
		   const Teuchos::ArrayView<const double> land_block,
		   const Teuchos::ArrayView<const double> and_block,
		   const Teuchos::ArrayView<const double> ldlw_block,
		   const Teuchos::ArrayView<const double> dlw_block,
		   const Teuchos::ArrayView<const double> itxe_block,
			 const Teuchos::ArrayView<const double> itce_block,
			 const Teuchos::ArrayView<const double> itca_block  );
		   
};

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// Template Includes
//---------------------------------------------------------------------------//

#include "MonteCarlo_SAlphaBetaNuclearScatteringDistributionACEFactory_def.hpp"

//---------------------------------------------------------------------------//

#endif // end MONTE_CARLO_S_ALPHA_BETA_NUCLEAR_SCATTERING_DISTRIBUTION_ACE_FACTORY_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_SAlphaBetaNuclearScatteringDistributionACEFactory.hpp
//---------------------------------------------------------------------------//
