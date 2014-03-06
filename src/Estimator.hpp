//---------------------------------------------------------------------------//
//!
//! \file   Estimator.hpp
//! \author Alex Robinson
//! \brief  Estimator base class declaration.
//!
//---------------------------------------------------------------------------//

#ifndef ESTIMATOR_HPP
#define ESTIMATOR_HPP

// Trilinos Includes
#include <Teuchos_ScalarTraits.hpp>
#include <Teuchos_Array.hpp>
#include <Teuchos_RCP.hpp>

// FACEMC Includes
#include "PrintableObject.hpp"
#include "ResponseFunction.hpp"
#include "EstimatorContributionMultiplierPolicy.hpp"
#include "Tuple.hpp"

namespace FACEMC{

//! The base estimator class
class Estimator : public PrintableObject
{

protected:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

public:

  //! Set the number of particle histories that will be simulated
  static setNumberOfHistories( const counsigned long long num_histories );

  //! Default constructor
  Estimator();

  //! Constructor
  Estimator( const unsigned long long id,
	     const double norm_constant,
	     const double multiplier );

  //! Destructor
  virtual ~Estimator()
  { /* ... */ }
  
  //! Get the tally id
  virtual unsigned long long getId() const;

  //! Set the energy bin boundaries
  virtual void setEnergyBinBoundaries( 
			 const Teuchos::Array<double>& energy_bin_boundaries );

  //! Set the cosine bin boundaries
  virtual void setCosineBinBoundaries( 
			 const Teuchos::Array<double>& cosine_bin_boundaries );

  //! Set the time bin boundaries
  virtual void setTimeBinBoundaries( 
			   const Teuchos::Array<double>& time_bin_boundaries );

  //! Set the collision number bins
  virtual void setCollisionNumberBins( 
		       const Teuchos::Array<unsigned>& collision_number_bins );

  //! Set the response functions
  virtual void setResponseFunctions( 
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions );

  //! Commit the contribution from the current history to the estimator
  virtual void commitHistoryContribution() = 0;

protected:

  //! Print method implementation
  void printImplementation( std::ostream& os ) const;

  // Check if the particle state falls within the estimator phase space
  bool isParticleInEstimatorPhaseSpace( const BasicParticleState& particle,
					const double angle_cosine ) const;

  // Calculate the bin offset for the desired response function
  unsigned calculateBinIndex( const BasicParticleState& particle,
			      const double angle_cosine,
			      const unsigned response_function_index ) const;

  // Return the number of estimator bins
  unsigned getNumberOfBins() const;

  // Return the number of response functions
  unsigned getNumberOfResponseFunctions() const;

  // Evaluate the desired response function
  double evaluateResponseFunction( 
				const BasicParticleState& particle,
				const unsigned response_function_index ) const;
  
  // Commit history contribution to a bin of the estimator
  void commitHistoryContributionToBin( const unsigned bin_index,
				       const double contribution );

  // Commit history contribution to the estimator total for a response function
  void commitHistoryContributionToTotal( 
				        const unsigned response_function_index,
					const double contribution );
  
private:

  // Test if the bin index is valid
  bool isValidBinIndex( unsigned bin_index );

  // Calculate the mean for a bin
  double calculateMean( unsigned bin_index );

  // Calculate the estimator value for a bin
  double calculateEstimatorValue( unsigned bin_index );

  // Calculate the relative error for a bin
  double calculateRelativeError( unsigned bin_index );

  // Calculate the variance of the variance (VOV) for a bin
  double calculateVOV( unsigned bin_index );

  // The number of particle histories that will be run
  static unsigned long long num_histories;

  // The estimator id
  unsigned long long d_id;

  // The normalization constant
  double d_norm_constant;

  // The multiplier
  double d_multiplier;

  // The energy bins
  Teuchos::Array<double> d_energy_bin_boundaries;
  
  // The cosine bins
  Teuchos::Array<double> d_cosine_bin_boundaries;

  // The time bins
  Teuchos::Array<double> d_time_bin_boundaries;

  // The collision number bins
  Teuchos::Array<unsigned> d_collision_number_bins;

  // The response functions
  Teuchos::Array<Teuchos::RCP<ResponseFunction> > d_response_functions;

  // The estimator moments (1st,2nd,3rd,4th) for each bin
  Teuchos::Array<Quad<double,double,double,double> > d_estimator_moments;

  // The total estimator moments for each reaction rate
  Teuchos::Array<Quad<double,double,double,double> > d_estimator_total_moments;
};

} // end FACEMC namespace

#endif // end ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end Estimator.hpp
//---------------------------------------------------------------------------//
