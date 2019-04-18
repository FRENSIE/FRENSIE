//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_InocherentAdjointPhotonScatteringDistribution.cpp
//! \author Alex Robinson
//! \brief  The incoherent adjoint photon scattering distribution definition
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <limits>
#include <functional>

// FRENSIE Includes
#include "MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.hpp"
#include "MonteCarlo_AdjointPhotonKinematicsHelpers.hpp"
#include "MonteCarlo_AdjointPhotonProbeState.hpp"
#include "Utility_SortAlgorithms.hpp"
#include "Utility_RandomNumberGenerator.hpp"
#include "Utility_QuantityTraits.hpp"
#include "Utility_PhysicalConstants.hpp"
#include "Utility_ExceptionTestMacros.hpp"
#include "Utility_DesignByContract.hpp"

namespace MonteCarlo{

// Constructor
IncoherentAdjointPhotonScatteringDistribution::IncoherentAdjointPhotonScatteringDistribution(
                      const double max_energy,
                      const AdjointKleinNishinaSamplingType sampling_type )
  : d_max_energy( max_energy ),
    d_critical_line_energies( new std::vector<double>( 1, 0.0 ) ),
    d_integrated_cs_evaluator( std::bind<double>( &IncoherentAdjointPhotonScatteringDistribution::evaluateIntegratedCrossSectionImpl,
                                                  this,
                                                  std::placeholders::_1,
                                                  std::placeholders::_2,
                                                  std::placeholders::_3 ) ),
    d_klein_nishina_sampling_method()
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > 0.0 );

  switch( sampling_type )
  {
    case TWO_BRANCH_REJECTION_ADJOINT_KN_SAMPLING:
      d_klein_nishina_sampling_method = std::bind<void>( &IncoherentAdjointPhotonScatteringDistribution::sampleAndRecordTrialsAdjointKleinNishinaTwoBranch,
                                                         this,
                                                         std::placeholders::_1,
                                                         std::placeholders::_2,
                                                         std::placeholders::_3,
                                                         std::placeholders::_4 );
      break;
    case THREE_BRANCH_LIN_MIXED_ADJOINT_KN_SAMPLING:
      d_klein_nishina_sampling_method = std::bind<void>( &IncoherentAdjointPhotonScatteringDistribution::sampleAndRecordTrialsAdjointKleinNishinaThreeBranchLin,
                                                         this,
                                                         std::placeholders::_1,
                                                         std::placeholders::_2,
                                                         std::placeholders::_3,
                                                         std::placeholders::_4 );
      break;
    case THREE_BRANCH_INVERSE_MIXED_ADJOINT_KN_SAMPLING:
      d_klein_nishina_sampling_method = std::bind<void>( &IncoherentAdjointPhotonScatteringDistribution::sampleAndRecordTrialsAdjointKleinNishinaThreeBranchInverse,
                                                         this,
                                                         std::placeholders::_1,
                                                         std::placeholders::_2,
                                                         std::placeholders::_3,
                                                         std::placeholders::_4 );
      break;
    default:
    {
      THROW_EXCEPTION( std::runtime_error,
                       "The Klein-Nishina sampling type is not supported!" );
    }
  }
}

// Set the critical line energies
/*! \details The critical line energies must be sorted. It is acceptable for
 * some or all of them to be above the max energy.
 */
void IncoherentAdjointPhotonScatteringDistribution::setCriticalLineEnergies(
    const std::shared_ptr<const std::vector<double> >& critical_line_energies )
{
  // Make sure the critical line energies are valid
  testPrecondition( critical_line_energies.get() );
  testPrecondition( critical_line_energies->size() > 0 );
  testPrecondition( Utility::Sort::isSortedAscending(
					     critical_line_energies->begin(),
					     critical_line_energies->end() ) );

  d_critical_line_energies = critical_line_energies;
}

// Get the critical line energies
const std::vector<double>&
IncoherentAdjointPhotonScatteringDistribution::getCriticalLineEnergies() const
{
  return *d_critical_line_energies;
}

// Set the max energy
void IncoherentAdjointPhotonScatteringDistribution::setMaxEnergy(
						      const double max_energy )
{
  // Make sure the max energy is valid
  testPrecondition( max_energy > 0.0 );

  d_max_energy = max_energy;
}

// Return the max energy
double IncoherentAdjointPhotonScatteringDistribution::getMaxEnergy() const
{
  return d_max_energy;
}

// Evaluate the distribution
double IncoherentAdjointPhotonScatteringDistribution::evaluate(
				   const double incoming_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= d_max_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >=
		    calculateMinScatteringAngleCosine( incoming_energy,
						       d_max_energy ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return this->evaluate( incoming_energy,
			 d_max_energy,
			 scattering_angle_cosine );
}

// Evaluate the pdf
double IncoherentAdjointPhotonScatteringDistribution::evaluatePDF(
				  const double incoming_energy,
				  const double max_energy,
				  const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= max_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >=
		    calculateMinScatteringAngleCosine( incoming_energy,
						       max_energy ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  const double diff_cs =
    this->evaluate( incoming_energy, max_energy, scattering_angle_cosine);

  if( diff_cs > 0.0 )
  {
    return diff_cs/this->evaluateIntegratedCrossSection( incoming_energy, max_energy, 1e-3 );
  }
  else
    return 0.0;
}

// Evaluate the pdf
double IncoherentAdjointPhotonScatteringDistribution::evaluatePDF(
				  const double incoming_energy,
				  const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= d_max_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >=
		    MonteCarlo::calculateMinScatteringAngleCosine( incoming_energy,
                                                                   d_max_energy ) );
  testPrecondition( scattering_angle_cosine <= 1.0 );

  return this->evaluatePDF( incoming_energy,
			    d_max_energy,
			    scattering_angle_cosine );
}

// Set an external integrated cross section evaluator
/*! \details This is an advanced feature! This method can be used to set
 * an external evaluator (tabulated cross section evaluator) that is faster
 * than the default evaluator implementation (numerical integration).
 */
void IncoherentAdjointPhotonScatteringDistribution::setExternalIntegratedCrossSectionEvaluator(
                                    std::function<double(double,double,double)>
                                    integrated_cs_evaluator )
{
  d_integrated_cs_evaluator = integrated_cs_evaluator;
}

// Unset the integrated cross section evaluator
void IncoherentAdjointPhotonScatteringDistribution::unsetExternalIntegratedCrossSectionEvaluator()
{
  d_integrated_cs_evaluator = std::bind<double>( &IncoherentAdjointPhotonScatteringDistribution::evaluateIntegratedCrossSectionImpl,
                                                 this,
                                                 std::placeholders::_1,
                                                 std::placeholders::_2,
                                                 std::placeholders::_3 );
}

// Evaluate the integrated cross section (b)
double IncoherentAdjointPhotonScatteringDistribution::evaluateIntegratedCrossSection(
						 const double incoming_energy,
						 const double max_energy,
						 const double precision ) const
{
  return d_integrated_cs_evaluator( incoming_energy, max_energy, precision );
}

// Evaluate the integrated cross section (b)
double IncoherentAdjointPhotonScatteringDistribution::evaluateIntegratedCrossSection(
					         const double incoming_energy,
					         const double precision ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= d_max_energy );

  return this->evaluateIntegratedCrossSection( incoming_energy,
					       d_max_energy,
					       precision );
}

// Check if an energy is in the scattering window
bool IncoherentAdjointPhotonScatteringDistribution::isEnergyInScatteringWindow(
					    const double energy_of_interest,
					    const double initial_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( initial_energy > 0.0 );
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest >= 0.0 );

  if( energy_of_interest > d_max_energy )
    return false;
  else
  {
    if( this->isEnergyAboveScatteringWindow( energy_of_interest,
					     initial_energy ) )
      return false;
    else if( this->isEnergyBelowScatteringWindow( energy_of_interest,
						  initial_energy ) )
      return false;
    else
      return true;
  }
}

// Check if an energy is below the scattering window
/*! \details This is the lower boundary of the energy window when binding
 * effects are ignored.
 */
bool IncoherentAdjointPhotonScatteringDistribution::isEnergyBelowScatteringWindow(
					   const double energy_of_interest,
					   const double initial_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( initial_energy > 0.0 );
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest >= 0.0 );

  const double lower_energy_boundary = energy_of_interest/
      (1.0 + 2*energy_of_interest/
       Utility::PhysicalConstants::electron_rest_mass_energy);

  return initial_energy < lower_energy_boundary;
}

// Check if an energy is above the scattering window
/*! \details This is the upper boundary of the energy window when binding
 * effects are ignored.
 */
bool IncoherentAdjointPhotonScatteringDistribution::isEnergyAboveScatteringWindow(
					   const double energy_of_interest,
					   const double initial_energy ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( initial_energy > 0.0 );
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest >= 0.0 );

  return initial_energy > energy_of_interest;
}

// Evaluate the adjoint Klein-Nishina distribution
/*! \details The adjoint Klein-Nishina cross section (b) differential in the
 * scattering angle cosine is returned from this function.
 */
double IncoherentAdjointPhotonScatteringDistribution::evaluateAdjointKleinNishinaDist(
				   const double incoming_energy,
				   const double max_energy,
				   const double scattering_angle_cosine ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= max_energy );
  // Make sure the scattering angle cosine is valid
  testPrecondition( scattering_angle_cosine >=
		    calculateMinScatteringAngleCosine( incoming_energy,
						       max_energy ));

  double kn_cross_section;

  if( scattering_angle_cosine >=
      calculateMinScatteringAngleCosine( incoming_energy, max_energy ) )
  {
    const double mult = Utility::PhysicalConstants::pi*
      Utility::PhysicalConstants::classical_electron_radius*
      Utility::PhysicalConstants::classical_electron_radius*1e24;

    const double outgoing_energy = calculateAdjointComptonLineEnergy(
						     incoming_energy,
						     scattering_angle_cosine );


    kn_cross_section = mult*(outgoing_energy/incoming_energy +
			     incoming_energy/outgoing_energy - 1.0 +
			     scattering_angle_cosine*scattering_angle_cosine);
  }
  else
    kn_cross_section = 0.0;

  // Make sure the Klein-Nishina cross section is valid
  testPrecondition( kn_cross_section >= 0.0 );

  return kn_cross_section;
}

// Basic sampling implementation
void IncoherentAdjointPhotonScatteringDistribution::sampleAndRecordTrialsAdjointKleinNishina(
                                               const double incoming_energy,
                                               double& outgoing_energy,
					       double& scattering_angle_cosine,
                                               Counter& trials ) const
{
  d_klein_nishina_sampling_method( incoming_energy,
                                   outgoing_energy,
                                   scattering_angle_cosine,
                                   trials );
}

// Basic sampling implementation
void IncoherentAdjointPhotonScatteringDistribution::sampleAndRecordTrialsAdjointKleinNishinaTwoBranch(
					       const double incoming_energy,
                                               double& outgoing_energy,
					       double& scattering_angle_cosine,
                                               Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= d_max_energy );

  const double alpha = incoming_energy/
    Utility::PhysicalConstants::electron_rest_mass_energy;

  const double min_inverse_energy_gain_ratio =
    calculateMinInverseEnergyGainRatio( incoming_energy, d_max_energy );

  const double branch_value = (1.0 - min_inverse_energy_gain_ratio)/
    (1.0 + min_inverse_energy_gain_ratio);

  double inverse_energy_gain_ratio;

  while( true )
  {
    ++trials;
    
    const double random_number_1 =
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    const double random_number_2 =
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    const double random_number_3 =
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    inverse_energy_gain_ratio = min_inverse_energy_gain_ratio +
      random_number_2*(1.0 - min_inverse_energy_gain_ratio);

    scattering_angle_cosine = 1.0 - (1.0 - inverse_energy_gain_ratio)/alpha;

    // Evaluate branch 1 rejection function
    if( random_number_1 <= branch_value )
    {
      const double rejection_value =
        min_inverse_energy_gain_ratio/(1.0-min_inverse_energy_gain_ratio)*
        (1.0/inverse_energy_gain_ratio - 1.0);

      if( random_number_3 <= rejection_value )
        break;
    }
    // Evaluate branch 2 rejection function
    else
    {
      const double rejection_value =
        0.5*(scattering_angle_cosine*scattering_angle_cosine +
             inverse_energy_gain_ratio);

      if( random_number_3 <= rejection_value )
        break;
    }
  }

  // Calculate the scattering angle cosine
  scattering_angle_cosine = 1.0 - (1.0 - inverse_energy_gain_ratio)/alpha;

  // Calculate the outgoing energy
  outgoing_energy = incoming_energy/inverse_energy_gain_ratio;

  const double min_scattering_angle_cosine =
    calculateMinScatteringAngleCosine( incoming_energy, d_max_energy );
  
  // Check for roundoff error
  if( scattering_angle_cosine > 1.0 )
    scattering_angle_cosine = 1.0;
  else if( scattering_angle_cosine < min_scattering_angle_cosine )
    scattering_angle_cosine = min_scattering_angle_cosine;

  // Make sure the sampled value is valid
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf(
						 inverse_energy_gain_ratio ) );
  testPostcondition( inverse_energy_gain_ratio <= 1.0 );
  testPostcondition( inverse_energy_gain_ratio >=
		     min_inverse_energy_gain_ratio );
  // Make sure the sampled energy is valid
  testPostcondition( outgoing_energy >= incoming_energy );
  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= min_scattering_angle_cosine );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

// Basic sampling implementation
void IncoherentAdjointPhotonScatteringDistribution::sampleAndRecordTrialsAdjointKleinNishinaThreeBranchLin(
					       const double incoming_energy,
                                               double& outgoing_energy,
					       double& scattering_angle_cosine,
                                               Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= d_max_energy );

  const double alpha = incoming_energy/
    Utility::PhysicalConstants::electron_rest_mass_energy;
  const double alpha_sqr = alpha*alpha;

  const double min_inverse_energy_gain_ratio =
    calculateMinInverseEnergyGainRatio( incoming_energy, d_max_energy );

  const double term_1_arg = (1.0 - min_inverse_energy_gain_ratio);
  const double term_1 = term_1_arg*term_1_arg;
  
  const double term_2 = min_inverse_energy_gain_ratio*(1.0 - min_inverse_energy_gain_ratio*min_inverse_energy_gain_ratio);
  
  const double term_3_arg = min_inverse_energy_gain_ratio - 1.0 + alpha;
  const double term_3 = (2.0/3.0)*(min_inverse_energy_gain_ratio/alpha_sqr)*(alpha_sqr*alpha - term_3_arg*term_3_arg*term_3_arg);

  const double all_terms = term_1+term_2+term_3;

  // Make sure all of the branching values were positive
  testInvariant( term_1 >= 0.0 );
  testInvariant( term_2 >= 0.0 );
  testInvariant( term_3 >= 0.0 );
  testInvariant( all_terms > 0.0 );

  double inverse_energy_gain_ratio;

  double random_number_1, random_number_2;

  while( true )
  {
    ++trials;

    random_number_1 =
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    random_number_2 =
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    if( random_number_1 < term_1/all_terms )
    {
      inverse_energy_gain_ratio =
        1.0 - (1.0 - min_inverse_energy_gain_ratio)*std::sqrt(random_number_2);

      const double rejection_value = min_inverse_energy_gain_ratio/inverse_energy_gain_ratio;

      double random_number_3 =
        Utility::RandomNumberGenerator::getRandomNumber<double>();

      if( random_number_3 < rejection_value )
        break;
    }
    else if( random_number_1 < (term_1+term_2)/all_terms )
    {
      const double min_inverse_energy_gain_ratio_sqr =
        min_inverse_energy_gain_ratio*min_inverse_energy_gain_ratio;
      
      inverse_energy_gain_ratio =
        sqrt( random_number_2*(1.0 - min_inverse_energy_gain_ratio_sqr) + 
              min_inverse_energy_gain_ratio_sqr );

      break;
    }
    else
    {
      const double term_3_arg_cubed = term_3_arg*term_3_arg*term_3_arg;

      const double arg = random_number_2*
        (alpha_sqr*alpha - term_3_arg_cubed) + term_3_arg_cubed;

      inverse_energy_gain_ratio = 1.0 - alpha + std::cbrt( arg );

      break;
    }
  }

  // Calculate the scattering angle cosine
  scattering_angle_cosine = 1.0 - (1.0 - inverse_energy_gain_ratio)/alpha;

  // Calculate the outgoing energy
  outgoing_energy = incoming_energy/inverse_energy_gain_ratio;

  const double min_scattering_angle_cosine =
    calculateMinScatteringAngleCosine( incoming_energy, d_max_energy );
  
  // Check for roundoff error
  if( scattering_angle_cosine > 1.0 )
    scattering_angle_cosine = 1.0;
  else if( scattering_angle_cosine < min_scattering_angle_cosine )
    scattering_angle_cosine = min_scattering_angle_cosine;

  // Make sure the sampled value is valid
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf(
						 inverse_energy_gain_ratio ) );
  testPostcondition( inverse_energy_gain_ratio <= 1.0 );
  testPostcondition( inverse_energy_gain_ratio >=
		     min_inverse_energy_gain_ratio );
  // Make sure the sampled energy is valid
  testPostcondition( outgoing_energy >= incoming_energy );
  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= min_scattering_angle_cosine );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

// Basic sampling implementation
void IncoherentAdjointPhotonScatteringDistribution::sampleAndRecordTrialsAdjointKleinNishinaThreeBranchInverse(
					       const double incoming_energy,
                                               double& outgoing_energy,
					       double& scattering_angle_cosine,
                                               Counter& trials ) const
{
  // Make sure the incoming energy is valid
  testPrecondition( incoming_energy > 0.0 );
  testPrecondition( incoming_energy <= d_max_energy );

  const double alpha = incoming_energy/
    Utility::PhysicalConstants::electron_rest_mass_energy;
  const double alpha_sqr = alpha*alpha;

  const double min_inverse_energy_gain_ratio =
    calculateMinInverseEnergyGainRatio( incoming_energy, d_max_energy );

  const double term_1 = -3.0*log(min_inverse_energy_gain_ratio)*
    (1.0 - min_inverse_energy_gain_ratio)*alpha*alpha;

  const double term_2 = 3.0/2.0*alpha*alpha*
    (1.0 - min_inverse_energy_gain_ratio*min_inverse_energy_gain_ratio);

  const double term_3_arg = min_inverse_energy_gain_ratio - 1.0 + alpha;

  const double term_3 = alpha*alpha*alpha - term_3_arg*term_3_arg*term_3_arg;

  const double all_terms = term_1+term_2+term_3;

  // Make sure all of the branching values were positive
  testInvariant( term_1 >= 0.0 );
  testInvariant( term_2 >= 0.0 );
  testInvariant( term_3 >= 0.0 );
  testInvariant( all_terms > 0.0 );

  double inverse_energy_gain_ratio;

  double random_number_1, random_number_2;

  while( true )
  {
    ++trials;

    random_number_1 =
      Utility::RandomNumberGenerator::getRandomNumber<double>();
    random_number_2 =
      Utility::RandomNumberGenerator::getRandomNumber<double>();

    if( random_number_1 < term_1/all_terms )
    {
      inverse_energy_gain_ratio =
        pow( min_inverse_energy_gain_ratio, random_number_2 );

      const double rejection_value = (1.0 - inverse_energy_gain_ratio)/
        (1.0 - min_inverse_energy_gain_ratio);

      double random_number_3 =
        Utility::RandomNumberGenerator::getRandomNumber<double>();

      if( random_number_3 < rejection_value )
        break;
    }
    else if( random_number_1 < (term_1+term_2)/all_terms )
    {
      const double min_inverse_energy_gain_ratio_sqr =
        min_inverse_energy_gain_ratio*min_inverse_energy_gain_ratio;
      
      inverse_energy_gain_ratio =
        sqrt( random_number_2*(1.0 - min_inverse_energy_gain_ratio_sqr) + 
              min_inverse_energy_gain_ratio_sqr );

      break;
    }
    else
    {
      const double term_3_arg_cubed = term_3_arg*term_3_arg*term_3_arg;

      const double arg = random_number_2*
        (alpha_sqr*alpha - term_3_arg_cubed) + term_3_arg_cubed;

      inverse_energy_gain_ratio = 1.0 - alpha + std::cbrt( arg );

      break;
    }
  }

  // Calculate the scattering angle cosine
  scattering_angle_cosine = 1.0 - (1.0 - inverse_energy_gain_ratio)/alpha;

  // Calculate the outgoing energy
  outgoing_energy = incoming_energy/inverse_energy_gain_ratio;

  const double min_scattering_angle_cosine =
    calculateMinScatteringAngleCosine( incoming_energy, d_max_energy );

  // Check for roundoff error
  if( scattering_angle_cosine > 1.0 )
    scattering_angle_cosine = 1.0;
  else if( scattering_angle_cosine < min_scattering_angle_cosine )
    scattering_angle_cosine = min_scattering_angle_cosine;

  // Make sure the sampled value is valid
  testPostcondition( !Utility::QuantityTraits<double>::isnaninf(
						 inverse_energy_gain_ratio ) );
  testPostcondition( inverse_energy_gain_ratio <= 1.0 );
  testPostcondition( inverse_energy_gain_ratio >=
		     min_inverse_energy_gain_ratio );
  // Make sure the sampled energy is valid
  testPostcondition( outgoing_energy >= incoming_energy );
  // Make sure the scattering angle cosine is valid
  testPostcondition( scattering_angle_cosine >= min_scattering_angle_cosine );
  testPostcondition( scattering_angle_cosine <= 1.0 );
}

// Create a probe particle
/*! \details Energy binding effects will be ignored when creating probe
 * particles. This procedure will generate a probe particle (if physically
 * possible) even if the incoming particle is a probe (be careful about
 * create probe cascades).
 */
void IncoherentAdjointPhotonScatteringDistribution::createProbeParticle(
				      const double energy_of_interest,
				      const AdjointPhotonState& adjoint_photon,
				      ParticleBank& bank ) const
{
  // Make sure the energy of interest is valid
  testPrecondition( energy_of_interest > 0.0 );
  testPrecondition( energy_of_interest <= d_max_energy );
  // Make sure the adjoint photon energy is valid
  testPrecondition( adjoint_photon.getEnergy() <= d_max_energy );
  // Make sure the energy of interest is in the scattering window
  testPrecondition( this->isEnergyInScatteringWindow(
						energy_of_interest,
						adjoint_photon.getEnergy() ) );

  // Only generate the probe if the energy is in the scattering window
  if( this->isEnergyInScatteringWindow( energy_of_interest,
					adjoint_photon.getEnergy() ) )
  {
    double scattering_angle_cosine;

    if( energy_of_interest == d_max_energy )
    {
      scattering_angle_cosine =
        MonteCarlo::calculateMinScatteringAngleCosine( adjoint_photon.getEnergy(),
						       d_max_energy );
    }
    else
    {
      scattering_angle_cosine =
        MonteCarlo::calculateScatteringAngleCosineAdjoint( adjoint_photon.getEnergy(),
                                                           energy_of_interest );
    }

    const double pdf_conversion =
      Utility::PhysicalConstants::electron_rest_mass_energy/
      (energy_of_interest*energy_of_interest);

    const double weight_mult =
      this->evaluatePDF( adjoint_photon.getEnergy(), scattering_angle_cosine )*
      pdf_conversion;

    // Create the probe with the desired energy and modified weight
    std::shared_ptr<AdjointPhotonProbeState> probe(
			       new AdjointPhotonProbeState( adjoint_photon ) );

    probe->setEnergy( energy_of_interest );
    probe->rotateDirection( scattering_angle_cosine,
			    this->sampleAzimuthalAngle() );
    probe->multiplyWeight( weight_mult );
    probe->activate();

    // Add the probe to the bank
    bank.push( probe );
  }
}

// Create the probe particles
/*! \details Currently, probe cascades are not allowed (only non-probe states
 * can generate new probe states).
 */
void IncoherentAdjointPhotonScatteringDistribution::createProbeParticles(
				      const AdjointPhotonState& adjoint_photon,
				      ParticleBank& bank ) const
{
  // Avoid probe cascades
  if( !adjoint_photon.isProbe() )
  {
    // Find the critical line energies in the scattering window
    LineEnergyIterator line_energy, end_line_energy;

    this->getCriticalLineEnergiesInScatteringWindow(adjoint_photon.getEnergy(),
						    line_energy,
						    end_line_energy );

    while( line_energy != end_line_energy )
    {
      this->createProbeParticle( *line_energy, adjoint_photon, bank );

      ++line_energy;
    }
  }
}

// Return only the critical line energies that can be scattered into
void IncoherentAdjointPhotonScatteringDistribution::getCriticalLineEnergiesInScatteringWindow(
					 const double energy,
				         LineEnergyIterator& start_energy,
					 LineEnergyIterator& end_energy ) const
{
  // Make sure the energy is valid
  testPrecondition( energy > 0.0 );

  if( this->isEnergyAboveScatteringWindow( d_critical_line_energies->back(), energy ) )
  {
    start_energy = d_critical_line_energies->end();
    end_energy = start_energy;
  }
  else if( this->isEnergyBelowScatteringWindow( d_critical_line_energies->front(), energy ) )
  {
    start_energy = d_critical_line_energies->end();
    end_energy = start_energy;
  }
  else
  {
    start_energy = d_critical_line_energies->begin();

    while( start_energy != d_critical_line_energies->end() )
    {
      if( this->isEnergyInScatteringWindow( *start_energy, energy ) )
	break;

      ++start_energy;
    }

    end_energy = start_energy;

    if( start_energy != d_critical_line_energies->end() )
    {
      ++end_energy;

      while( end_energy != d_critical_line_energies->end() )
      {
	if( !this->isEnergyInScatteringWindow( *end_energy, energy ) )
	  break;

	++end_energy;
      }
    }
  }
}

} // end MonteCarlo namespace

//---------------------------------------------------------------------------//
// end MonteCarlo_IncoherentAdjointPhotonScatteringDistribution.cpp
//---------------------------------------------------------------------------//
