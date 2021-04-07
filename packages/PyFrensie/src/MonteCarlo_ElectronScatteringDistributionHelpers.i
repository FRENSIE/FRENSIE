//---------------------------------------------------------------------------//
//!
//! \file   MonteCarlo_ElectronScatteringDistributionHelpers.i
//! \author Luke Kersting
//! \brief  The distribution helper macros
//!
//---------------------------------------------------------------------------//

// Include std::string support
%include <std_string.i>

//---------------------------------------------------------------------------//
// Helper macro for setting up a basic electron distribution class python interface
//---------------------------------------------------------------------------//
%define %electron_distribution_interface_setup( DISTRIBUTION )

%feature("docstring") DISTRIBUTION
"The DISTRIBUTION proxy class. This class can be evaluated, sampled
from, exported to an XML file (using the PyTrilinos.Teuchos.ParameterList and
the PyTrilinos.Teuchos.XMLParameterListWriter), and imported from an XML file
(using the PyTrilinos.Teuchos.ParameterList and the
PyTrilinos.Teuchos.XMLParameterListReader). Before sampling, make sure to
initialize the Frensie Pseudo-Random Number Generator
(PyFrensie.Utility.initFrensiePrng())"

%feature("autodoc",
"evaluate(DISTRIBUTION self, const double incoming_energy, const double secondary_indep_var_val ) -> double" )
MonteCarlo::DISTRIBUTION::evaluate;

%feature("autodoc",
"evaluatePDF(DISTRIBUTION self, const double incoming_energy, const double secondary_indep_var_val ) -> double" )
MonteCarlo::DISTRIBUTION::evaluatePDF;

%feature("autodoc",
"sample(DISTRIBUTION self, const double incoming_energy) -> double, double")
MonteCarlo::DISTRIBUTION::sample;

%feature("autodoc",
"sampleAndRecordTrials(DISTRIBUTION self, const double incoming_energy, unsigned int & trials ) -> double, double, unsigned int

Sample from the DISTRIBUTION and record the number of trials
(iterations) that were required to generate the sample. The first element of
the returned tuple is the sampled outgoing energy. The second element of the
returned tuple is the sampled scattering angle cosine. The third element of the
returned tuple is the trials counter. The trials counter can be reused as such:

  import PyFrensie.MonteCarlo.Collision
  import PyFrensie.Utility

  PyFrensie.Utility.initFrensiePrng()

  u = PyFrensie.MonteCarlo.DISTRIBUTION( ... )
  trials_counter = 0
  incoming_energy = 1.0

  outgoing_energy, scattering_angle_cosine,trials_counter =
    u.sampleAndRecordTrials( incoming_energy, trials_counter )
  outgoing_energy, scattering_angle_cosine,trials_counter =
    u.sampleAndRecordTrials( incoming_energy, trials_counter )

  print trials_counter
  2")
MonteCarlo::DISTRIBUTION::sampleAndRecordTrials;

%enddef

//---------------------------------------------------------------------------//
// end Utility_ElectronScatteringDistributionHelpers.i
//---------------------------------------------------------------------------//
