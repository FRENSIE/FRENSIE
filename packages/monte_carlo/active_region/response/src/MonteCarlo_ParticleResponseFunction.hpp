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

// Boost Includes
#include <boost/serialization/split_member.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/shared_ptr.hpp>

// FRENSIE Includes
#include "MonteCarlo_ParticleState.hpp"
#include "Utility_ExplicitSerializationTemplateInstantiationMacros.hpp"
#include "Utility_SerializationHelpers.hpp"

namespace MonteCarlo{

//! The particle response function base class
class ParticleResponseFunction : public std::enable_shared_from_this<ParticleResponseFunction>
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

  //! Get a description of the response function
  virtual std::string description() const = 0;

  //! Check if the description requires parentheses
  virtual bool doesDescriptionRequireParentheses() const;

  //! Return a shared ptr of the object
  std::shared_ptr<ParticleResponseFunction> getShared();

  //! Return a shared ptr of the object (const)
  std::shared_ptr<const ParticleResponseFunction> getShared() const;

protected:

  //! Constructor
  ParticleResponseFunction()
  { /* ... */ }

private:

  // Serialize the particle response function
  template<typename Archive>
  void serialize( Archive& ar, const unsigned version )
  { /* ... */ }

  // Declare the boost serialization access object as a friend
  friend class boost::serialization::access;
};

} // end MonteCarlo namespace

BOOST_SERIALIZATION_CLASS_VERSION( ParticleResponseFunction, MonteCarlo, 0 );
BOOST_SERIALIZATION_ASSUME_ABSTRACT_CLASS( ParticleResponseFunction, MonteCarlo );
EXTERN_EXPLICIT_CLASS_SERIALIZE_INST( MonteCarlo, ParticleResponseFunction );

//! Create a new response function from the addition of two response functions
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator+(
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs );

//! Create a new response function from the subtraction of two response functions
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator-(
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs );

//! Create a new response function from the multiplication of two response functions
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator*(
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs );

//! Create a new response function from the multiplication of a scalar and a response function
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator*(
      const double lhs,
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs );

//! Create a new response function from the multiplication of a response function and a scalar
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator*(
        const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
        const double rhs );

//! Create a new response function from the division of two response functions
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator/(
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs );

//! Create a new response function from the division of a scalar and a response function
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator/(
      const double lhs,
      const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& rhs );

//! Create a new response function from the division of a response function and a scalar
std::shared_ptr<const MonteCarlo::ParticleResponseFunction> operator/(
        const std::shared_ptr<const MonteCarlo::ParticleResponseFunction>& lhs,
        const double rhs );

#endif // end MONTE_CARLO_PARTICLE_RESPONSE_FUNCTION_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleResponseFunction.hpp
//---------------------------------------------------------------------------//
