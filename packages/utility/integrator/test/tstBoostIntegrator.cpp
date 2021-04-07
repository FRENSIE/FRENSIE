//---------------------------------------------------------------------------//
//!
//! \file   tstBoostIntegrator.cpp
//! \author Luke Kersting
//! \brief  Gauss-Kronrod quadrature integrator unit tests.
//!
//---------------------------------------------------------------------------//

// Std Lib Includes
#include <iostream>
#include <limits>

// Boost Includes
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/tools/precision.hpp>
#include <boost/numeric/odeint.hpp>

// FRENSIE Includes
#include "Utility_UnitTestHarnessWithMain.hpp"

//---------------------------------------------------------------------------//
// Testing Types
//---------------------------------------------------------------------------//

typedef boost::multiprecision::cpp_dec_float_50 long_float;

typedef std::vector<double> state_type;

struct X2Functor
{
  void operator()( const state_type& x, state_type& y, const double t ) const
  {
    if( t >= 0.0 && t <= 1.0 )
      y[0] = t*t;
    else
      y[0] = 0.0;
  }

  static double getIntegratedValue()
  {
    return 1.0/3.0;
  }

  static double getLowerIntegratedValue()
  {
    return 1.0/24.0;
  }

  static double getUpperIntegratedValue()
  {
    return 7.0/24.0;
  }
};

struct X3Functor
{
  void operator()( const state_type& x, state_type& y, const double t ) const
  {
    if( t >= 0.0 && t <= 1.0 )
      y[0] = t*t*t;
    else
      y[0] = 0.0;
  }

  static double getIntegratedValue()
  {
    return 0.25;
  }

  static double getLowerIntegratedValue()
  {
    return 1.0/64.0;
  }

  static double getUpperIntegratedValue()
  {
    return 15.0/64.0;
  }
};

namespace Utility{

TYPE_NAME_TRAITS_QUICK_DECL( boost::multiprecision::cpp_dec_float_50 );
TYPE_NAME_TRAITS_QUICK_DECL( X2Functor );
TYPE_NAME_TRAITS_QUICK_DECL( X3Functor );
  
} // end Utility namespace

typedef std::tuple<X2Functor,X3Functor> TestFunctors;

typedef std::vector< double > state_type;

//---------------------------------------------------------------------------//
// Testing Functions
//---------------------------------------------------------------------------//

// Observer, prints time and state when called (during integration)
void my_observer( const state_type& x, const double t )
{    std::cout  << t << "   " << x[0] << std::endl;   }

//---------------------------------------------------------------------------//
// Tests
//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1]
FRENSIE_UNIT_TEST_TEMPLATE( BoostIntegrator,
                            integrate,
                            TestFunctors )
{
  FETCH_TEMPLATE_PARAM( 0, Functor );
  
  state_type x0(1);
  x0[0] = 0.0;
  double t0 = 0.0;
  double t1 = 1.0;
  double dt = 0.01;

  Functor functor_instance;

  int steps = boost::numeric::odeint::integrate(
    functor_instance, x0, t0, t1, dt );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 1e-10 );
  std::cout << "steps = " << steps << std::endl;
}

//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1]
FRENSIE_UNIT_TEST_TEMPLATE( BoostIntegrator,
                            integrate_const,
                            TestFunctors )
{
  FETCH_TEMPLATE_PARAM( 0, Functor );
  
  state_type x0(1);
  x0[0] = 0.0;
  double t0 = 0.0;
  double t1 = 1.0;
  double dt = 0.01;

  Functor functor_instance;

  int steps = boost::numeric::odeint::integrate_const(
    boost::numeric::odeint::runge_kutta4<state_type>(), functor_instance, x0, t0, t1, dt );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 1e-10 );
  std::cout << "steps = " << steps << std::endl;

  x0[0] = 0.0;
  dt = 0.00001;
  steps = boost::numeric::odeint::integrate_const(
    boost::numeric::odeint::euler<state_type>(), functor_instance, x0, t0, t1, dt );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 0.5 );
  std::cout << "steps = " << steps << std::endl;

  x0[0] = 0.0;
  dt = 0.01;
  steps = boost::numeric::odeint::integrate_const(
    boost::numeric::odeint::runge_kutta_cash_karp54<state_type>(), functor_instance, x0, t0, t1, dt );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 1e-10 );
  std::cout << "steps = " << steps << std::endl;

  x0[0] = 0.0;
  steps = boost::numeric::odeint::integrate_const(
    boost::numeric::odeint::runge_kutta_dopri5<state_type>(), functor_instance, x0, t0, t1, dt );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 1e-10 );
  std::cout << "steps = " << steps << std::endl;

  x0[0] = 0.0;
  steps = boost::numeric::odeint::integrate_const(
    boost::numeric::odeint::runge_kutta_fehlberg78<state_type>(), functor_instance, x0, t0, t1, dt );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 1e-10 );
  std::cout << "steps = " << steps << std::endl;

  x0[0] = 0.0;
  dt = 0.00001;
  steps = boost::numeric::odeint::integrate_const(
    boost::numeric::odeint::modified_midpoint<state_type>(), functor_instance, x0, t0, t1, dt );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 0.01 );
  std::cout << "steps = " << steps << std::endl;
}

//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1]
FRENSIE_UNIT_TEST_TEMPLATE( BoostIntegrator,
                            integrate_n_steps,
                            TestFunctors )
{
  FETCH_TEMPLATE_PARAM( 0, Functor );
  
  state_type x0(1);
  x0[0] = 0.0;
  double t0 = 0.0;
  double t1 = 1.0;
  double dt = 0.1;
  int n = 10;

  Functor functor_instance;

  int end_time = boost::numeric::odeint::integrate_n_steps(
    boost::numeric::odeint::runge_kutta4<state_type>(), functor_instance, x0, t0, dt, n );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 1e-10 );
  std::cout << "end time = " << end_time << std::endl;
  
  x0[0] = 0.0;
  end_time = boost::numeric::odeint::integrate_n_steps(
    boost::numeric::odeint::euler<state_type>(), functor_instance, x0, t0, dt, n );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 0.5 );
  std::cout << "end time = " << end_time << std::endl;
  
  x0[0] = 0.0;
  end_time = boost::numeric::odeint::integrate_n_steps(
    boost::numeric::odeint::runge_kutta_cash_karp54<state_type>(), functor_instance, x0, t0, dt, n );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 1e-10 );
  std::cout << "end time = " << end_time << std::endl;
  
  x0[0] = 0.0;
  end_time = boost::numeric::odeint::integrate_n_steps(
    boost::numeric::odeint::runge_kutta_dopri5<state_type>(), functor_instance, x0, t0, dt, n );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 1e-10 );
  std::cout << "end time = " << end_time << std::endl;
  
  x0[0] = 0.0;
  end_time = boost::numeric::odeint::integrate_n_steps(
    boost::numeric::odeint::runge_kutta_fehlberg78<state_type>(), functor_instance, x0, t0, dt, n );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 1e-10 );
  std::cout << "end time = " << end_time << std::endl;
  
  x0[0] = 0.0;
  end_time = boost::numeric::odeint::integrate_n_steps(
    boost::numeric::odeint::modified_midpoint<state_type>(), functor_instance, x0, t0, dt, n );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 0.01 );
  std::cout << "end time = " << end_time << std::endl;
/*
  x0[0] = 0.0;
  boost::numeric::odeint::integrate_n_steps(
    boost::numeric::odeint::rosenbrock4<state_type>(), functor_instance, x0, t0, dt, n );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 1e-10 );*/
}

//---------------------------------------------------------------------------//
// Check that functions can be integrated over [0,1]
FRENSIE_UNIT_TEST_TEMPLATE( BoostIntegrator,
                            integrate_adaptive,
                            TestFunctors )
{
  FETCH_TEMPLATE_PARAM( 0, Functor );
  
  state_type x0(1);
  x0[0] = 0.0;
  double t0 = 0.0;
  double t1 = 1.0;
  double dt = 0.1;

  Functor functor_instance;

  int steps =  boost::numeric::odeint::integrate_adaptive(
    boost::numeric::odeint::runge_kutta4<state_type>(), functor_instance, x0, t0, t1, dt );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 1e-10 );
  std::cout << "steps = " << steps << std::endl;
  
  x0[0] = 0.0;
  steps = boost::numeric::odeint::integrate_adaptive(
    boost::numeric::odeint::euler<state_type>(), functor_instance, x0, t0, t1, dt );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 0.5 );
  std::cout << "steps = " << steps << std::endl;
  
  x0[0] = 0.0;
  auto stepper = make_controlled( 1.0e-16 , 1.0e-16 , boost::numeric::odeint::runge_kutta_cash_karp54< state_type >() );
  steps = boost::numeric::odeint::integrate_adaptive(
    stepper, functor_instance, x0, t0, t1, dt );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 1e-10 );
  std::cout << "steps = " << steps << std::endl;
  
  x0[0] = 0.0;
  boost::numeric::odeint::controlled_runge_kutta< boost::numeric::odeint::runge_kutta_dopri5< state_type > > rkd5;
  steps = boost::numeric::odeint::integrate_adaptive(
    rkd5, functor_instance, x0, t0, t1, dt );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 1e-10 );
  std::cout << "steps = " << steps << std::endl;
  
  x0[0] = 0.0;
  boost::numeric::odeint::controlled_runge_kutta< boost::numeric::odeint::runge_kutta_fehlberg78< state_type > > rkf78;
  steps = boost::numeric::odeint::integrate_adaptive(
    rkf78, functor_instance, x0, t0, t1, dt );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 1e-10 );
  std::cout << "steps = " << steps << std::endl;
  
  x0[0] = 0.0;
  steps = boost::numeric::odeint::integrate_adaptive(
    boost::numeric::odeint::modified_midpoint<state_type>(), functor_instance, x0, t0, t1, dt );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 0.01 );
  std::cout << "steps = " << steps << std::endl;

  boost::numeric::odeint::bulirsch_stoer< state_type > bs;
  x0[0] = 0.0;
  steps = boost::numeric::odeint::integrate_adaptive(
    bs, functor_instance, x0, t0, t1/2, dt );
    
  steps = boost::numeric::odeint::integrate_adaptive(
    bs, functor_instance, x0, t1/2, t1, dt );

  FRENSIE_CHECK_FLOATING_EQUALITY( Functor::getIntegratedValue(), x0[0], 1e-10 );
  std::cout << "steps = " << steps << std::endl;
}

//---------------------------------------------------------------------------//
// end tstGaussKronrodIntegrator.cpp
//---------------------------------------------------------------------------//
