//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ParticleState_def.hpp
//! \author Alex Robinson
//! \brief  Particle state base class template definition
//!
//---------------------------------------------------------------------------//

#ifndef MONTE_CARLO_PARTICLE_STATE_DEF_HPP
#define MONTE_CARLO_PARTICLE_STATE_DEF_HPP

// Boost Includes
#include <boost/serialization/nvp.hpp>
#include <boost/archive/xml_oarchive.hpp>

namespace MonteCarlo{

// Print method implementation
template<typename DerivedType>
void ParticleState::printImplementation( std::ostream& os ) const
{
  os.precision( 18 );

  boost::archive::xml_oarchive ar(os);
  ar << boost::serialization::make_nvp(
  			typeid(*dynamic_cast<const DerivedType*>(this)).name(),
  			*dynamic_cast<const DerivedType*>(this) );
}

// Save the state to an archive (the ray object will not be archived)
template<typename Archive>
void ParticleState::save( Archive& ar, const unsigned version ) const
{
  ar & BOOST_SERIALIZATION_NVP( d_history_number );
  ar & BOOST_SERIALIZATION_NVP( d_particle_type );
  ar & BOOST_SERIALIZATION_NVP( d_source_id );
  ar & BOOST_SERIALIZATION_NVP( d_source_energy );
  ar & BOOST_SERIALIZATION_NVP( d_energy );
  ar & BOOST_SERIALIZATION_NVP( d_charge );
  ar & BOOST_SERIALIZATION_NVP( d_source_time );
  ar & BOOST_SERIALIZATION_NVP( d_time );
  ar & BOOST_SERIALIZATION_NVP( d_collision_number );
  ar & BOOST_SERIALIZATION_NVP( d_generation_number );
  ar & BOOST_SERIALIZATION_NVP( d_source_weight );
  ar & BOOST_SERIALIZATION_NVP( d_weight );
  ar & BOOST_SERIALIZATION_NVP( d_ray_safety_distance );
  ar & BOOST_SERIALIZATION_NVP( d_source_cell );
  ar & BOOST_SERIALIZATION_NVP( d_lost );
  ar & BOOST_SERIALIZATION_NVP( d_gone );
  ar & BOOST_SERIALIZATION_NVP( d_importance_pair );
  ar & boost::serialization::make_nvp( "d_x_position", d_navigator->getPosition()[0] );
  ar & boost::serialization::make_nvp( "d_y_position", d_navigator->getPosition()[1] );
  ar & boost::serialization::make_nvp( "d_z_position", d_navigator->getPosition()[2] );
  ar & boost::serialization::make_nvp( "d_x_direction", d_navigator->getDirection()[0] );
  ar & boost::serialization::make_nvp( "d_y_direction", d_navigator->getDirection()[1] );
  ar & boost::serialization::make_nvp( "d_z_direction", d_navigator->getDirection()[2] );

  // We will not use the cell when we set the internal ray because the
  // particle may not be embedded in the same geometry as it was when it
  // was archived.
}

// Load the data from an archive (the ray object is not archived)
template<typename Archive>
void ParticleState::load( Archive& ar, const unsigned version )
{
  ar & BOOST_SERIALIZATION_NVP( d_history_number );
  ar & BOOST_SERIALIZATION_NVP( d_particle_type );
  ar & BOOST_SERIALIZATION_NVP( d_source_id );
  ar & BOOST_SERIALIZATION_NVP( d_source_energy );
  ar & BOOST_SERIALIZATION_NVP( d_energy );
  ar & BOOST_SERIALIZATION_NVP( d_charge );
  ar & BOOST_SERIALIZATION_NVP( d_source_time );
  ar & BOOST_SERIALIZATION_NVP( d_time );
  ar & BOOST_SERIALIZATION_NVP( d_collision_number );
  ar & BOOST_SERIALIZATION_NVP( d_generation_number );
  ar & BOOST_SERIALIZATION_NVP( d_source_weight );
  ar & BOOST_SERIALIZATION_NVP( d_weight );
  ar & BOOST_SERIALIZATION_NVP( d_ray_safety_distance );
  ar & BOOST_SERIALIZATION_NVP( d_source_cell );
  ar & BOOST_SERIALIZATION_NVP( d_lost );
  ar & BOOST_SERIALIZATION_NVP( d_gone );
  ar & BOOST_SERIALIZATION_NVP( d_importance_pair );

  Geometry::Navigator::Length position[3];

  ar & boost::serialization::make_nvp( "d_x_position", position[0] );
  ar & boost::serialization::make_nvp( "d_y_position", position[1] );
  ar & boost::serialization::make_nvp( "d_z_position", position[2] );

  double direction[3];

  ar & boost::serialization::make_nvp( "d_x_direction", direction[0] );
  ar & boost::serialization::make_nvp( "d_y_direction", direction[1] );
  ar & boost::serialization::make_nvp( "d_z_direction", direction[2] );

  // We will not use the cell when we set the internal ray because the
  // particle may not be embedded in the same geometry as it was when it
  // was archived.
  d_navigator->setState( position, direction );
}

} // end MonteCarlo namespace

#endif // end MONTE_CARLO_PARTICLE_STATE_DEF_HPP

//---------------------------------------------------------------------------//
// end MonteCarlo_ParticleState_def.hpp
//---------------------------------------------------------------------------//
