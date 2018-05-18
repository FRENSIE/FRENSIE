//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleResponseFunction.hpp
//! \author Alex Robinson
//! \brief  Particle response function base class declaration
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_RESPONSE_FUNCTION_HPP
#define MONTE_CARLO_PARTICLE_RESPONSE_FUNCTION_HPP

// Std Lib Includes
#include <string>
#include <memory>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"

namespace MonteCarlo{

//! The particle response function base class
class ParticleResponseFunction 
{

public:

  //! Destructor
  virtual ~ParticleResponseFunction()
  { /* ... */ }

  //! Evaluate the response function at the desired phase space point
  double operator()( const ParticleState& particle ) const;

  //! Evaluate the response function at the desired phase space point
  virtual double evaluate( const ParticleState& particle ) const = 0;

  //! Check if the response function is spatially uniform
  virtual bool isSpatiallyUniform() const = 0;

protected:

  //! Constructor
  ParticleResponseFunction()
  { /* ... */ }
};

// Evaluate the response function at the desired phase space point
inline double operator()( const ParticleState& particle ) const
{
  return this->evaluate( particle );
}

//! Create a new response function from the addition of two response functions
std::shared_ptr<const ParticleResponseFunction> operator+(
                  const std::shared_ptr<const ParticleResponseFunction>& lhs,
                  const std::shared_ptr<const ParticleResponseFunction>& rhs );

//! Create a new response function from the subtraction of two response functions
std::shared_ptr<const ParticleResponseFunction> operator-(
                  const std::shared_ptr<const ParticleResponseFunction>& lhs,
                  const std::shared_ptr<const ParticleResponseFunction>& rhs );

//! Create a new response function from the multiplication of two response functions
std::shared_ptr<const ParticleResponseFunction> operator*(
                  const std::shared_ptr<const ParticleResponseFunction>& lhs,
                  const std::shared_ptr<const ParticleResponseFunction>& rhs );

//! Create a new response function from the multiplication of a scalar and a response function
std::shared_ptr<const ParticleResponseFunction> operator*(
                  const double lhs,
                  const std::shared_ptr<const ParticleResponseFunction>& rhs );

//! Create a new response function from the multiplication of a response function and a scalar
std::shared_ptr<const ParticleResponseFunction> operator*(
                    const std::shared_ptr<const ParticleResponseFunction>& lhs,
                    const double rhs );

//! Create a new response function from the division of two response functions
std::shared_ptr<const ParticleResponseFunction> operator/(
                  const std::shared_ptr<const ParticleResponseFunction>& lhs,
                  const std::shared_ptr<const ParticleResponseFunction>& rhs );

//! Create a new response function from the division of a scalar and a response function
std::shared_ptr<const ParticleResponseFunction> operator/(
                  const double lhs,
                  const std::shared_ptr<const ParticleResponseFunction>& rhs );

//! Create a new response function from the division of a response function and a scalar
std::shared_ptr<const ParticleResponseFunction> operator/(
                  const std::shared_ptr<const ParticleResponseFunction>& lhs,
                  const double rhs );

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleResponseFunction.hpp
//---------------------------------------------------------------------------//
