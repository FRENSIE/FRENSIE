//---------------------------------------------------------------------------//
//!
//! \file   DataGen.ElectronPhoton.i
//! \author Luke Kersting
//! \brief  The DataGen.ElectronPhoton sub-module swig interface file
//!
//---------------------------------------------------------------------------//

%define %data_gen_electron_photon_docstring
"
PyFrensie.DataGen.ElectronPhoton is the python interface to the FRENSIE
data_gen/electron_photon subpackage.

The purpose of ElectronPhoton is to provide tools for generating Electron-Photon
data.
"
%enddef

%module(package   = "PyFrensie.DataGen",
        autodoc   = "1",
        docstring = %data_gen_electron_photon_docstring) ElectronPhoton

%{
// PyFrensie Includes
#define NO_IMPORT_ARRAY
#include "numpy_include.h"
%}

// Add support for the electron photon relaxation data generator
%include "DataGen_ElectronPhotonRelaxationDataGenerator.i"

// Add support for the adjoint electron photon relaxation data generator
%include "DataGen_AdjointElectronPhotonRelaxationDataGenerator.i"

// Add support for the moment preserving electron data generator
//%include "DataGen_MomentPreservingElectronDataGenerator.i"

//---------------------------------------------------------------------------//
// end DataGen.ElectronPhoton.i
//---------------------------------------------------------------------------//
