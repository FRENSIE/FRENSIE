//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ElasticElectronMomentsEvaluator.hpp
//! \author Luke Kersting
//! \brief  Elastic electron cross section moments evaluator declaration
//!
//---------------------------------------------------------------------------//

#ifndef DATA_GEN_ELASTIC_ELECTRON_MOMENTS_EVALUATOR_HPP
#define DATA_GEN_ELASTIC_ELECTRON_MOMENTS_EVALUATOR_HPP

// Boost Includes
#include <boost/scoped_ptr.hpp>
/*
// Std Lib Includes
#include <limits>

// Boost Includes
#include <boost/distribution.hpp>
#include <boost/bind.hpp>
*/
// Trilinos Includes
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FRENSIE Includes
#include "MonteCarlo_ElectroatomicReaction.hpp"
#include "Utility_OneDDistribution.hpp"
#include "Utility_TabularOneDDistribution.hpp"
#include "MonteCarlo_HardElasticElectronScatteringDistribution.hpp"


namespace DataGen{

//! The elastic electron cross section moments class
class ElasticElectronMomentsEvaluator
{
  
public:

  //! Typedef for the elastic distribution
  typedef Teuchos::Array<Utility::Pair<double,
		       Teuchos::RCP<const Utility::TabularOneDDistribution> > >
  ElasticDistribution;

  //! Constructor
  ElasticElectronMomentsEvaluator(
    const Teuchos::RCP<MonteCarlo::ElectroatomicReaction>& 
                               elatic_reaction,
    const Teuchos::RCP<const MonteCarlo::HardElasticElectronScatteringDistribution>&
                               elastic_distribution );

  //! Destructor
  ~ElasticElectronMomentsEvaluator()
  { /* ... */ }

  //! Evaluate the differential hard elastic cross section (dc/dx)
  double evaluateDifferentialCrossSection(
                                    const double scattering_angle_cosine,
                                    const double incoming_energy ) const;

  //! Evaluate the Legnendre Polynomial expansion of the differential hard elastic cross section (dc/dx)
  double evaluateLegendreExpandedDifferentialCrossSection(
                                    const double scattering_angle_cosine,
                                    const double incoming_energy, 
                                    const int polynomial_order = 0) const;

  //! Return the cross section moment at a given energy and polynomial order
  double evaluateCrossSectionMoment( const double energy, 
                                     const int polynomial_order,
                                     const double precision ) const;

private:

  // The forward reaction data
  Teuchos::RCP<MonteCarlo::ElectroatomicReaction> d_elastic_reaction;

  // The knock on energy distribution
  Teuchos::RCP<const MonteCarlo::HardElasticElectronScatteringDistribution>
                                         d_elastic_distribution;
};

} // end DataGen namespace

#endif // end DATA_GEN_ELASTIC_ELECTRON_MOMENTS_EVALUATOR_HPP

//---------------------------------------------------------------------------//
// end DataGen_ElasticElectronMomentsEvaluator.hpp
//---------------------------------------------------------------------------//
