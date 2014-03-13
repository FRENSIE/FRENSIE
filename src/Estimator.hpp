//---------------------------------------------------------------------------//
//!
//! \file    Estimator.hpp
//! \author  Alex Robinson
//! \brief   Estimator base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef ESTIMATOR_HPP
#define ESTIMATOR_HPP

// Trilinos Includes
#include "Teuchos_Array.hpp"
#include "Teuchos_ScalarTraits.hpp"

// FACEMC Includes
#include "PrintableObject.hpp"
#include "ParticleType.hpp"
#include "Tuple.hpp"
#include "ResponseFunction.hpp"

namespace FACEMC{

//! The estimator base class
class Estimator : public PrintableObject
{

protected:

  // Typedef for Teuchos::ScalarTraits
  typedef Teuchos::ScalarTraits<double> ST;

  // Typedef for tuple of estimator moments (1st,2nd,3rd,4th)
  typedef Quad<double,double,double,double> EstimatorMoments;

  // Typedef for the array of estimator moments 
  typedef Teuchos::Array<EstimatorMoments> EstimatorMomentsArray;

public:

  //! Set the number of particle histories that will be simulated
  static void setNumberOfHistories( const unsigned long long num_histories );
  
  //! Set the start time for the figure of merit calculation
  static void setStartTime( const double start_time );
  
  //! Set the end time for the figure of merit calculation
  static void setEndTime( const double end_time );

  //! Constructor
  Estimator( const unsigned long long id,
	     const double multiplier );

  //! Destructor
  virtual ~Estimator()
  { /* ... */ }

  //! Return the estimator id
  unsigned long long getId() const;

  //! Return the estimator constant multiplier
  double getMultiplier() const;

  //! Set the energy bin boundaries
  virtual void setEnergyBinBoundaries( 
			 const Teuchos::Array<double>& energy_bin_boundaries );

  //! Return the number of energy bins
  unsigned getNumberOfEnergyBins() const;

  //! Set the cosine bin boundaries
  virtual void setCosineBinBoundaries( 
			 const Teuchos::Array<double>& cosine_bin_boundaries );

  //! Return the number of cosine bins
  unsigned getNumberOfCosineBins() const;

  //! Set the time bin boundaries
  virtual void setTimeBinBoundaries( 
			   const Teuchos::Array<double>& time_bin_boundaries );

  //! Return the number of time bins
  unsigned getNumberOfTimeBins() const;

  //! Set the collision number bins
  virtual void setCollisionNumberBins( 
		       const Teuchos::Array<unsigned>& collision_number_bins );

  //! Return the number of collision bins
  unsigned getNumberOfCollisionNumberBins() const;

  //! Return the total number of bins
  unsigned getNumberOfBins() const;
  
  //! Set the response functions
  virtual void setResponseFunctions( 
   const Teuchos::Array<Teuchos::RCP<ResponseFunction> >& response_functions );

  //! Return the number of response functions
  unsigned getNumberOfResponseFunctions() const;

  //! Set the particle types that can contribute to the estimator
  virtual void setParticleTypes( 
			  const Teuchos::Array<ParticleType>& particle_types );

  //! Check if the particle type is assigned to the estimator
  bool isParticleTypeAssigned( const ParticleType particle_type ) const;

  //! Commit the contribution from the current history to the estimator
  virtual void commitHistoryContribution() = 0;

protected:

  //! Return the energy boundaries of a bin
  Pair<double,double> getBoundariesOfEnergyBin( 
					     const unsigned energy_bin ) const;

  //! Return the cosine boundaries of a bin
  Pair<double,double> getBoundariesOfCosineBin( 
					     const unsigned cosine_bin ) const;

  //! Return the time boundaries of a bin
  Pair<double,double> getBoundariesOfTimeBin( const unsigned time_bin ) const;

  //! Return the collision number boundaries of a bin
  Pair<unsigned,unsigned> getBoundariesOfCollisionNumberBin( 
				   const unsigned collision_number_bin ) const;

  //! Return the response function name
  const std::string& getResponseFunctionName( 
				const unsigned response_function_index ) const;

  //! Print the estimator response function names
  void printEstimatorResponseFunctionNames( std::ostream& os ) const;

  //! Print the estimator bins
  void printEstimatorBins( std::ostream& os ) const;

  //! Print the estimator data stored in an array
  void printEstimatorBinData( 
			    std::ostream& os,
			    const EstimatorMomentsArray& estimator_moment_data,
			    const double norm_constant );

  //! Print the total estimator data stored in an array
  void printEstimatorTotalData( 
		     std::ostream& os,
		     const EstimatorMomentsArray& total_estimator_moments_data,
		     const double norm_constant );

  //! Evaluate the desired response function
  double evaluateResponseFunction( 
				const BasicParticleState& particle,
				const unsigned response_function_index ) const;

  //! Check if the energy lies within the estimator energy space
  bool isEnergyInEstimatorEnergySpace( const double energy ) const;

  //! Check if the angle cosine lies within the estimator angle cosine space
  bool isAngleCosineInEstimatorCosineSpace( const double angle_cosine ) const;

  //! Check if the time lies within the estimator time space
  bool isTimeInEstimatorTimeSpace( const double time ) const;

  //! Check if the collision number lies within the estimator col. num. space
  bool isCollisionNumberInEstimatorCollisionNumberSpace( 
				       const unsigned collision_number ) const;
  
  //! Check if a phase space point lies within the estimator phase space
  bool isPointInEstimatorPhaseSpace( const double energy,
				     const double angle_cosine,
				     const double time,
				     const unsigned collision_number ) const;

  //! Calculate the energy bin index for the desired energy
  unsigned calculateEnergyBinIndex( const double energy ) const;
  
  //! Calculate the cosine bin index for the desired angle cosine
  unsigned calculateCosineBinIndex( const double angle_cosine ) const;

  //! Calculate the time bin index for the desired time
  unsigned calculateTimeBinIndex( const double time ) const;

  //! Calculate the collision number bin for the desired collision number
  unsigned calculateCollisionNumberBinIndex( 
					 const double collision_number ) const;

  //! Calculate the bin index for the desired response function
  unsigned calculateBinIndex( const double energy,
			      const double angle_cosine,
			      const double time,
			      const unsigned collision_number,
			      const unsigned response_function_index ) const;

  //! Calculate the mean of a set of contributions
  double calculateMean( const double first_moment_contributions ) const;

  //! Calculate the relative error of a set of contributions
  double calculateRelativeError( 
			      const double first_moment_contributions,
			      const double second_moment_contributions ) const;

  //! Calculate the variance of the variance (VOV) of a set of contributions
  double calculateVOV( const double first_moment_contributions,
		       const double second_moment_contributions,
		       const double third_moment_contributions,
		       const double fourth_moment_contributions ) const;

  //! Calculate the figure of merit (FOM) of an estimator bin
  double calculateFOM( const double relative_error ) const;

private:

  // The number of particle histories that will be run
  static unsigned long long num_histories;

  // The start time used for the figure of merit calculation
  static double start_time;

  // The end time used for the figure of merit calculation
  static double end_time;

  // The estimator id
  unsigned long long d_id;

  // The constant multiplier for the estimator
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

  // The particle types that this estimator will take contributions from
  std::set<ParticleType> d_particle_types;
};

} // end FACEMC namespace

#endif // end ESTIMATOR_HPP

//---------------------------------------------------------------------------//
// end Estimator.hpp
//---------------------------------------------------------------------------//
