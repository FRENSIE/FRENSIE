//---------------------------------------------------------------------------//
//!
//! \file   DataGen_ComptonProfileGenerator.cpp
//! \author Alex Robinson
//! \brief  The Compton profile generator definition. All default Compton
//!         profile generators return the Compton profiles reported in
//!         F. Biggs et al., HARTREE-FOCK COMPTON PROFILES FOR THE ELEMENTS.
//!
//---------------------------------------------------------------------------//

// FRENSIE Includes
#include "DataGen_ComptonProfileGenerator.hpp"

namespace DataGen{

//! The default Compton profile generator
struct DefaultComptonProfileGenerator : public ComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfiles(
           std::vector<std::vector<double> >& subshell_half_profiles,
           std::vector<double>& union_half_momentum_grid ) const final override
  {
    this->generateHalfProfilesOnly( subshell_half_profiles );

    union_half_momentum_grid =
      std::vector<double>( {0.00, 0.05, 0.10, 0.15, 0.20, 0.30, 0.40, 0.50,
            0.60, 0.70, 0.80, 1.00, 1.20, 1.40, 1.60, 1.80, 2.00, 2.40, 3.00,
            4.00, 5.00, 6.00, 7.00, 8.00, 10.00, 15.00, 20.00, 30.00, 40.00,
            60.00, 100.00} );
  }

  //! Generate the half profiles only
  virtual void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                         subshell_half_profiles ) const = 0;
};

//! The default Compton profile generator implementation
template<unsigned atomic_number>
struct DefaultComptonProfileGeneratorImpl;

//! The default Compton profile generator implementation for A=1
template<>
struct DefaultComptonProfileGeneratorImpl<1u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 1 );

    subshell_half_profiles[0] = 
      std::vector<double>( {8.4900E-01, 8.4200E-01, 8.2400E-01, 7.9400E-01, 
            7.5500E-01, 6.5500E-01, 5.4400E-01, 4.3500E-01, 3.3700E-01, 
            2.5700E-01, 1.9200E-01, 1.0600E-01, 5.8400E-02, 3.2700E-02, 
            1.8800E-02, 1.1100E-02, 6.7900E-03, 2.7500E-03, 8.4900E-04, 
            1.7300E-04, 4.8300E-05, 1.6800E-05, 6.7900E-06, 3.0900E-06, 
            8.2000E-07, 7.4000E-08, 1.3000E-08, 1.2000E-09, 2.3000E-10, 
            4.3000E-11, 2.6000E-11} );
  }
};

//! The default Compton profile generator implementation for A=2
template<>
struct DefaultComptonProfileGeneratorImpl<2u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 1 );

    subshell_half_profiles[0] = 
      std::vector<double>( {5.3500E-01, 5.3400E-01, 5.2800E-01, 5.2000E-01, 
            5.0900E-01, 4.7800E-01, 4.3900E-01, 3.9600E-01, 3.5000E-01, 
            3.0600E-01, 2.6400E-01, 1.9100E-01, 1.3600E-01, 9.5500E-02, 
            6.7200E-02, 4.7600E-02, 3.4000E-02, 1.7900E-02, 7.4000E-03, 
            2.0600E-03, 6.9800E-04, 2.7400E-04, 1.2000E-04, 5.7800E-05, 
            1.6000E-05, 1.6000E-06, 2.9000E-07, 2.6000E-08, 4.7000E-09, 
            4.3000E-10, 3.9000E-11} );
  }
};

//! The default Compton profile generator implementation for A=3
template<>
struct DefaultComptonProfileGeneratorImpl<3u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 2 );

    subshell_half_profiles[0] = 
      std::vector<double>( {3.2900E-01, 3.2800E-01, 3.2700E-01, 3.2500E-01, 
            3.2200E-01, 3.1500E-01, 3.0500E-01, 2.9300E-01, 2.7900E-01, 
            2.6300E-01, 2.4700E-01, 2.1300E-01, 1.8000E-01, 1.4900E-01, 
            1.2200E-01, 9.9000E-02, 7.9800E-02, 5.1300E-02, 2.6600E-02, 
            9.4300E-03, 3.7100E-03, 1.6100E-03, 7.6400E-04, 3.8900E-04, 
            1.2000E-04, 1.2000E-05, 2.4000E-06, 2.2000E-07, 3.9000E-08, 
            3.5000E-09, 1.8000E-10} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.9400E+00, 1.8700E+00, 1.6900E+00, 1.4300E+00, 
            1.1400E+00, 6.1200E-01, 2.7400E-01, 1.0800E-01, 4.1100E-02, 
            1.9400E-02, 1.4100E-02, 1.3400E-02, 1.2000E-02, 9.5800E-03, 
            7.2400E-03, 5.3600E-03, 3.9500E-03, 2.1800E-03, 9.6200E-04, 
            2.9500E-04, 1.0800E-04, 4.4800E-05, 2.0600E-05, 1.0300E-05, 
            3.1000E-06, 3.1000E-07, 5.9000E-08, 5.4000E-09, 9.6000E-10, 
            8.6000E-11, 4.4000E-12} );
  }
};

//! The default Compton profile generator implementation for A=4
template<>
struct DefaultComptonProfileGeneratorImpl<4u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 2 );

    subshell_half_profiles[0] = 
      std::vector<double>( {2.3700E-01, 2.3700E-01, 2.3600E-01, 2.3600E-01, 
            2.3500E-01, 2.3200E-01, 2.2800E-01, 2.2300E-01, 2.1800E-01, 
            2.1100E-01, 2.0400E-01, 1.8800E-01, 1.7100E-01, 1.5300E-01, 
            1.3600E-01, 1.1900E-01, 1.0400E-01, 7.7100E-02, 4.8100E-02, 
            2.1500E-02, 9.8600E-03, 4.7700E-03, 2.4400E-03, 1.3100E-03, 
            4.4000E-04, 5.0000E-05, 9.9000E-06, 9.4000E-07, 1.7000E-07, 
            1.5000E-08, 7.4000E-10} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.3400E+00, 1.3200E+00, 1.2500E+00, 1.1500E+00, 
            1.0200E+00, 7.4300E-01, 4.8600E-01, 2.9300E-01, 1.6500E-01, 
            8.9200E-02, 4.7500E-02, 1.6400E-02, 1.0800E-02, 1.0400E-02, 
            1.0200E-02, 9.3900E-03, 8.2300E-03, 5.8000E-03, 3.1500E-03, 
            1.1500E-03, 4.6100E-04, 2.0400E-04, 9.8700E-05, 5.1100E-05, 
            1.6000E-05, 1.8000E-06, 3.4000E-07, 3.2000E-08, 5.8000E-09, 
            5.2000E-10, 2.5000E-11} );
  }
};

//! The default Compton profile generator implementation for A=5
template<>
struct DefaultComptonProfileGeneratorImpl<5u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 3 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.8600E-01, 1.8600E-01, 1.8600E-01, 1.8500E-01, 
            1.8500E-01, 1.8400E-01, 1.8200E-01, 1.7900E-01, 1.7600E-01, 
            1.7300E-01, 1.6900E-01, 1.6100E-01, 1.5100E-01, 1.4100E-01, 
            1.3000E-01, 1.1900E-01, 1.0900E-01, 8.8400E-02, 6.2800E-02, 
            3.3800E-02, 1.7900E-02, 9.6100E-03, 5.3200E-03, 3.0400E-03, 
            1.1000E-03, 1.4000E-04, 2.9000E-05, 2.9000E-06, 5.3000E-07, 
            4.8000E-08, 2.3000E-09} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.0000E+00, 9.9200E-01, 9.6300E-01, 9.1700E-01, 
            8.5700E-01, 7.1100E-01, 5.5200E-01, 4.0500E-01, 2.8400E-01, 
            1.9100E-01, 1.2400E-01, 5.0000E-02, 2.0900E-02, 1.1500E-02, 
            9.2400E-03, 8.9700E-03, 8.9300E-03, 8.0800E-03, 5.7300E-03, 
            2.6800E-03, 1.2200E-03, 5.8600E-04, 2.9800E-04, 1.6100E-04, 
            5.4000E-05, 6.3000E-06, 1.3000E-06, 1.2000E-07, 2.2000E-08, 
            2.0000E-09, 9.4000E-11} );

    subshell_half_profiles[2] = 
      std::vector<double>( {6.1500E-01, 6.1500E-01, 6.1400E-01, 6.1200E-01, 
            6.0600E-01, 5.8100E-01, 5.3300E-01, 4.6700E-01, 3.9300E-01, 
            3.2100E-01, 2.5600E-01, 1.5700E-01, 9.4300E-02, 5.6800E-02, 
            3.4600E-02, 2.1500E-02, 1.3500E-02, 5.7100E-03, 1.7800E-03, 
            3.4500E-04, 8.8800E-05, 2.8200E-05, 1.0400E-05, 4.2900E-06, 
            9.3000E-07, 5.0000E-08, 5.7000E-09, 2.5000E-10, 2.5000E-11, 
            1.0000E-12, 1.7000E-14} );
  }
};

//! The default Compton profile generator implementation for A=6
template<>
struct DefaultComptonProfileGeneratorImpl<6u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 3 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5300E-01, 
            1.5300E-01, 1.5200E-01, 1.5100E-01, 1.4900E-01, 1.4800E-01, 
            1.4600E-01, 1.4400E-01, 1.3900E-01, 1.3300E-01, 1.2600E-01, 
            1.2000E-01, 1.1200E-01, 1.0500E-01, 9.0500E-02, 7.0100E-02, 
            4.3300E-02, 2.5800E-02, 1.5300E-02, 9.1300E-03, 5.5500E-03, 
            2.2000E-03, 3.1000E-04, 6.8000E-05, 7.0000E-06, 1.3000E-06, 
            1.2000E-07, 5.8000E-09} );

    subshell_half_profiles[1] = 
      std::vector<double>( {8.0400E-01, 7.9800E-01, 7.8300E-01, 7.5900E-01, 
            7.2600E-01, 6.4100E-01, 5.4100E-01, 4.3900E-01, 3.4300E-01, 
            2.6000E-01, 1.9200E-01, 9.8200E-02, 4.7700E-02, 2.3400E-02, 
            1.3000E-02, 9.0900E-03, 7.9500E-03, 7.7500E-03, 6.9500E-03, 
            4.2500E-03, 2.2700E-03, 1.2000E-03, 6.4900E-04, 3.6500E-04, 
            1.3000E-04, 1.6000E-05, 3.4000E-06, 3.3000E-07, 6.2000E-08, 
            5.6000E-09, 2.7000E-10} );

    subshell_half_profiles[2] = 
      std::vector<double>( {4.8800E-01, 4.8800E-01, 4.8800E-01, 4.8700E-01, 
            4.8500E-01, 4.7500E-01, 4.5300E-01, 4.2000E-01, 3.7900E-01, 
            3.3300E-01, 2.8700E-01, 2.0400E-01, 1.4000E-01, 9.5000E-02, 
            6.4400E-02, 4.3800E-02, 3.0100E-02, 1.4600E-02, 5.3000E-03, 
            1.2000E-03, 3.3400E-04, 1.1000E-04, 4.1600E-05, 1.7500E-05, 
            3.9000E-06, 2.2000E-07, 2.6000E-08, 1.2000E-09, 1.2000E-10, 
            4.8000E-12, 8.0000E-14} );
  }
};

//! The default Compton profile generator implementation for A=7
template<>
struct DefaultComptonProfileGeneratorImpl<7u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 3 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.3000E-01, 1.3000E-01, 1.3000E-01, 1.3000E-01, 
            1.3000E-01, 1.2900E-01, 1.2900E-01, 1.2800E-01, 1.2700E-01, 
            1.2600E-01, 1.2400E-01, 1.2100E-01, 1.1700E-01, 1.1300E-01, 
            1.0900E-01, 1.0400E-01, 9.8700E-02, 8.8100E-02, 7.2400E-02, 
            4.9500E-02, 3.2500E-02, 2.0900E-02, 1.3300E-02, 8.5800E-03, 
            3.7000E-03, 5.9000E-04, 1.4000E-04, 1.5000E-05, 2.8000E-06, 
            2.6000E-07, 1.3000E-08} );

    subshell_half_profiles[1] = 
      std::vector<double>( {6.7200E-01, 6.6900E-01, 6.6000E-01, 6.4600E-01, 
            6.2500E-01, 5.7200E-01, 5.0700E-01, 4.3500E-01, 3.6400E-01, 
            2.9600E-01, 2.3600E-01, 1.4200E-01, 8.0700E-02, 4.4300E-02, 
            2.4400E-02, 1.4200E-02, 9.5300E-03, 6.9400E-03, 6.7600E-03, 
            5.2900E-03, 3.3300E-03, 1.9500E-03, 1.1400E-03, 6.7400E-04, 
            2.6000E-04, 3.5000E-05, 7.5000E-06, 7.6000E-07, 1.4000E-07, 
            1.3000E-08, 6.2000E-10} );

    subshell_half_profiles[2] = 
      std::vector<double>( {4.0700E-01, 4.0700E-01, 4.0700E-01, 4.0700E-01, 
            4.0600E-01, 4.0100E-01, 3.9000E-01, 3.7200E-01, 3.4800E-01, 
            3.1900E-01, 2.8700E-01, 2.2400E-01, 1.6800E-01, 1.2400E-01, 
            9.0800E-02, 6.6200E-02, 4.8400E-02, 2.6100E-02, 1.0900E-02, 
            2.8700E-03, 8.8200E-04, 3.0900E-04, 1.2100E-04, 5.2300E-05, 
            1.2000E-05, 7.3000E-07, 8.9000E-08, 4.1000E-09, 4.2000E-10, 
            1.7000E-11, 3.0000E-13} );
  }
};

//! The default Compton profile generator implementation for A=8
template<>
struct DefaultComptonProfileGeneratorImpl<8u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 3 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1300E-01, 
            1.1300E-01, 1.1300E-01, 1.1200E-01, 1.1200E-01, 1.1100E-01, 
            1.1000E-01, 1.0900E-01, 1.0700E-01, 1.0500E-01, 1.0200E-01, 
            9.8600E-02, 9.5200E-02, 9.1500E-02, 8.3800E-02, 7.1800E-02, 
            5.2900E-02, 3.7300E-02, 2.5700E-02, 1.7400E-02, 1.1800E-02, 
            5.5000E-03, 1.0000E-03, 2.4000E-04, 2.8000E-05, 5.4000E-06, 
            5.1000E-07, 2.5000E-08} );

    subshell_half_profiles[1] = 
      std::vector<double>( {5.7900E-01, 5.7700E-01, 5.7100E-01, 5.6100E-01, 
            5.4800E-01, 5.1300E-01, 4.6800E-01, 4.1700E-01, 3.6300E-01, 
            3.1100E-01, 2.6100E-01, 1.7500E-01, 1.1100E-01, 6.8400E-02, 
            4.0900E-02, 2.4500E-02, 1.5100E-02, 7.6500E-03, 6.0500E-03, 
            5.6100E-03, 4.1400E-03, 2.7100E-03, 1.7100E-03, 1.0700E-03, 
            4.4000E-04, 6.5000E-05, 1.5000E-05, 1.5000E-06, 2.9000E-07, 
            2.7000E-08, 1.3000E-09} );

    subshell_half_profiles[2] = 
      std::vector<double>( {3.5000E-01, 3.5000E-01, 3.5000E-01, 3.4900E-01, 
            3.4900E-01, 3.4600E-01, 3.4000E-01, 3.3000E-01, 3.1500E-01, 
            2.9700E-01, 2.7500E-01, 2.2800E-01, 1.8300E-01, 1.4300E-01, 
            1.1100E-01, 8.5200E-02, 6.5300E-02, 3.8500E-02, 1.7900E-02, 
            5.4200E-03, 1.8400E-03, 6.9000E-04, 2.8400E-04, 1.2600E-04, 
            3.0000E-05, 1.9000E-06, 2.4000E-07, 1.1000E-08, 1.2000E-09, 
            5.0000E-11, 8.5000E-13} );
  }
};

//! The default Compton profile generator implementation for A=9
template<>
struct DefaultComptonProfileGeneratorImpl<9u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 3 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.0000E-01, 1.0000E-01, 1.0000E-01, 1.0000E-01, 
            1.0000E-01, 9.9900E-02, 9.9600E-02, 9.9200E-02, 9.8700E-02, 
            9.8200E-02, 9.7500E-02, 9.6000E-02, 9.4200E-02, 9.2200E-02, 
            8.9900E-02, 8.7400E-02, 8.4700E-02, 7.8900E-02, 6.9700E-02, 
            5.4200E-02, 4.0500E-02, 2.9500E-02, 2.1100E-02, 1.5000E-02, 
            7.5000E-03, 1.5000E-03, 4.0000E-04, 4.8000E-05, 9.6000E-06, 
            9.2000E-07, 4.5000E-08} );

    subshell_half_profiles[1] = 
      std::vector<double>( {5.0800E-01, 5.0700E-01, 5.0300E-01, 4.9600E-01, 
            4.8700E-01, 4.6200E-01, 4.3000E-01, 3.9300E-01, 3.5300E-01, 
            3.1200E-01, 2.7100E-01, 1.9700E-01, 1.3600E-01, 9.1100E-02, 
            5.9200E-02, 3.7800E-02, 2.4100E-02, 1.0700E-02, 5.7900E-03, 
            5.3900E-03, 4.5800E-03, 3.3500E-03, 2.2800E-03, 1.5200E-03, 
            6.7000E-04, 1.1000E-04, 2.6000E-05, 2.8000E-06, 5.4000E-07, 
            5.0000E-08, 2.4000E-09} );

    subshell_half_profiles[2] = 
      std::vector<double>( {3.0700E-01, 3.0700E-01, 3.0700E-01, 3.0700E-01, 
            3.0600E-01, 3.0500E-01, 3.0100E-01, 2.9500E-01, 2.8600E-01, 
            2.7400E-01, 2.5900E-01, 2.2400E-01, 1.8800E-01, 1.5400E-01, 
            1.2500E-01, 9.9800E-02, 7.9500E-02, 5.0300E-02, 2.5500E-02, 
            8.7200E-03, 3.2400E-03, 1.3000E-03, 5.6300E-04, 2.6000E-04, 
            6.6000E-05, 4.4000E-06, 5.7000E-07, 2.8000E-08, 3.0000E-09, 
            1.3000E-10, 2.1000E-12} );
  }
};

//! The default Compton profile generator implementation for A=10
template<>
struct DefaultComptonProfileGeneratorImpl<10u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 3 );

    subshell_half_profiles[0] = 
      std::vector<double>( {9.0000E-02, 9.0000E-02, 8.9900E-02, 8.9900E-02, 
            8.9800E-02, 8.9700E-02, 8.9500E-02, 8.9200E-02, 8.8800E-02, 
            8.8400E-02, 8.8000E-02, 8.6900E-02, 8.5500E-02, 8.4000E-02, 
            8.2300E-02, 8.0500E-02, 7.8400E-02, 7.4000E-02, 6.6800E-02, 
            5.4300E-02, 4.2400E-02, 3.2300E-02, 2.4100E-02, 1.7800E-02, 
            9.6000E-03, 2.2000E-03, 6.0000E-04, 7.6000E-05, 1.6000E-05, 
            1.5000E-06, 7.6000E-08} );

    subshell_half_profiles[1] = 
      std::vector<double>( {4.5300E-01, 4.5200E-01, 4.4900E-01, 4.4400E-01, 
            4.3800E-01, 4.2000E-01, 3.9700E-01, 3.6900E-01, 3.3800E-01, 
            3.0500E-01, 2.7200E-01, 2.0900E-01, 1.5500E-01, 1.1000E-01, 
            7.6700E-02, 5.2200E-02, 3.5100E-02, 1.5900E-02, 6.5600E-03, 
            4.9300E-03, 4.6600E-03, 3.7700E-03, 2.7800E-03, 1.9600E-03, 
            9.4000E-04, 1.7000E-04, 4.2000E-05, 4.7000E-06, 9.3000E-07, 
            8.7000E-08, 4.2000E-09} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.7400E-01, 2.7400E-01, 2.7400E-01, 2.7300E-01, 
            2.7300E-01, 2.7200E-01, 2.7000E-01, 2.6600E-01, 2.6000E-01, 
            2.5200E-01, 2.4100E-01, 2.1600E-01, 1.8800E-01, 1.5900E-01, 
            1.3300E-01, 1.1000E-01, 9.0600E-02, 6.0700E-02, 3.3200E-02, 
            1.2600E-02, 5.0500E-03, 2.1600E-03, 9.8400E-04, 4.7300E-04, 
            1.3000E-04, 9.0000E-06, 1.2000E-06, 6.0000E-08, 6.7000E-09, 
            2.8000E-10, 4.8000E-12} );
  }
};

//! The default Compton profile generator implementation for A=11
template<>
struct DefaultComptonProfileGeneratorImpl<11u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 4 );

    subshell_half_profiles[0] = 
      std::vector<double>( {8.1500E-02, 8.1500E-02, 8.1500E-02, 8.1500E-02, 
            8.1400E-02, 8.1300E-02, 8.1100E-02, 8.0900E-02, 8.0700E-02, 
            8.0400E-02, 8.0000E-02, 7.9200E-02, 7.8200E-02, 7.7100E-02, 
            7.5800E-02, 7.4300E-02, 7.2800E-02, 6.9400E-02, 6.3700E-02, 
            5.3400E-02, 4.3300E-02, 3.4200E-02, 2.6500E-02, 2.0300E-02, 
            1.2000E-02, 3.0000E-03, 8.7000E-04, 1.2000E-04, 2.4000E-05, 
            2.4000E-06, 1.2000E-07} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.9000E-01, 3.9000E-01, 3.8800E-01, 3.8500E-01, 
            3.8100E-01, 3.6900E-01, 3.5400E-01, 3.3500E-01, 3.1400E-01, 
            2.9100E-01, 2.6700E-01, 2.1800E-01, 1.7200E-01, 1.3200E-01, 
            9.8000E-02, 7.1300E-02, 5.1000E-02, 2.5200E-02, 9.4300E-03, 
            4.8400E-03, 4.7200E-03, 4.2000E-03, 3.3500E-03, 2.5100E-03, 
            1.3000E-03, 2.6000E-04, 6.7000E-05, 7.9000E-06, 1.6000E-06, 
            1.5000E-07, 7.4000E-09} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.2500E-01, 2.2500E-01, 2.2500E-01, 2.2500E-01, 
            2.2400E-01, 2.2400E-01, 2.2300E-01, 2.2200E-01, 2.2000E-01, 
            2.1600E-01, 2.1200E-01, 1.9900E-01, 1.8200E-01, 1.6400E-01, 
            1.4400E-01, 1.2500E-01, 1.0800E-01, 7.7400E-02, 4.6000E-02, 
            1.9200E-02, 8.3200E-03, 3.7700E-03, 1.8000E-03, 8.9600E-04, 
            2.5000E-04, 1.9000E-05, 2.6000E-06, 1.4000E-07, 1.5000E-08, 
            6.5000E-10, 1.1000E-11} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.0700E+00, 1.9900E+00, 1.7700E+00, 1.4600E+00, 
            1.1300E+00, 5.5600E-01, 2.2300E-01, 7.9600E-02, 3.1900E-02, 
            2.0500E-02, 1.9100E-02, 1.8000E-02, 1.4200E-02, 1.0000E-02, 
            6.7200E-03, 4.4000E-03, 2.8600E-03, 1.1900E-03, 3.3900E-04, 
            1.1500E-04, 1.0900E-04, 9.8900E-05, 7.9400E-05, 5.9600E-05, 
            3.1000E-05, 6.1000E-06, 1.5000E-06, 1.8000E-07, 3.6000E-08, 
            3.4000E-09, 1.7000E-10} );
  }
};

//! The default Compton profile generator implementation for A=12
template<>
struct DefaultComptonProfileGeneratorImpl<12u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 4 );

    subshell_half_profiles[0] = 
      std::vector<double>( {7.4500E-02, 7.4500E-02, 7.4500E-02, 7.4500E-02, 
            7.4400E-02, 7.4300E-02, 7.4200E-02, 7.4000E-02, 7.3800E-02, 
            7.3600E-02, 7.3300E-02, 7.2700E-02, 7.2000E-02, 7.1100E-02, 
            7.0100E-02, 6.9000E-02, 6.7800E-02, 6.5100E-02, 6.0500E-02, 
            5.2100E-02, 4.3500E-02, 3.5400E-02, 2.8300E-02, 2.2300E-02, 
            1.4000E-02, 3.8000E-03, 1.2000E-03, 1.7000E-04, 3.6000E-05, 
            3.7000E-06, 1.9000E-07} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.4200E-01, 3.4200E-01, 3.4000E-01, 3.3800E-01, 
            3.3600E-01, 3.2800E-01, 3.1700E-01, 3.0500E-01, 2.9000E-01, 
            2.7300E-01, 2.5500E-01, 2.1800E-01, 1.8100E-01, 1.4600E-01, 
            1.1500E-01, 8.8300E-02, 6.6700E-02, 3.6400E-02, 1.4300E-02, 
            5.1700E-03, 4.5900E-03, 4.4100E-03, 3.7900E-03, 3.0200E-03, 
            1.7000E-03, 3.9000E-04, 1.0000E-04, 1.3000E-05, 2.6000E-06, 
            2.5000E-07, 1.2000E-08} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.9200E-01, 1.9200E-01, 1.9200E-01, 1.9200E-01, 
            1.9200E-01, 1.9200E-01, 1.9100E-01, 1.9100E-01, 1.9000E-01, 
            1.8800E-01, 1.8600E-01, 1.7900E-01, 1.6900E-01, 1.5800E-01, 
            1.4400E-01, 1.3000E-01, 1.1600E-01, 8.9400E-02, 5.7800E-02, 
            2.6700E-02, 1.2400E-02, 5.9300E-03, 2.9500E-03, 1.5200E-03, 
            4.5000E-04, 3.7000E-05, 5.2000E-06, 2.8000E-07, 3.2000E-08, 
            1.4000E-09, 2.4000E-11} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.5900E+00, 1.5500E+00, 1.4400E+00, 1.2800E+00, 
            1.0900E+00, 6.9600E-01, 3.8700E-01, 1.9300E-01, 9.1100E-02, 
            4.4900E-02, 2.7200E-02, 2.1200E-02, 2.0700E-02, 1.8100E-02, 
            1.4400E-02, 1.0700E-02, 7.6300E-03, 3.6400E-03, 1.1200E-03, 
            2.3700E-04, 1.7400E-04, 1.7000E-04, 1.4800E-04, 1.1800E-04, 
            6.7000E-05, 1.5000E-05, 3.9000E-06, 4.7000E-07, 9.6000E-08, 
            9.3000E-09, 4.5000E-10} );
  }
};

//! The default Compton profile generator implementation for A=13
template<>
struct DefaultComptonProfileGeneratorImpl<13u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 5 );

    subshell_half_profiles[0] = 
      std::vector<double>( {6.8600E-02, 6.8600E-02, 6.8600E-02, 6.8500E-02, 
            6.8500E-02, 6.8400E-02, 6.8300E-02, 6.8200E-02, 6.8100E-02, 
            6.7900E-02, 6.7700E-02, 6.7200E-02, 6.6600E-02, 6.5900E-02, 
            6.5100E-02, 6.4200E-02, 6.3300E-02, 6.1100E-02, 5.7500E-02, 
            5.0500E-02, 4.3200E-02, 3.6100E-02, 2.9600E-02, 2.3900E-02, 
            1.5000E-02, 4.7000E-03, 1.6000E-03, 2.4000E-04, 5.2000E-05, 
            5.5000E-06, 2.8000E-07} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.0500E-01, 3.0400E-01, 3.0400E-01, 3.0200E-01, 
            3.0000E-01, 2.9500E-01, 2.8700E-01, 2.7800E-01, 2.6700E-01, 
            2.5500E-01, 2.4100E-01, 2.1300E-01, 1.8300E-01, 1.5300E-01, 
            1.2600E-01, 1.0100E-01, 8.0100E-02, 4.7900E-02, 2.0700E-02, 
            6.2500E-03, 4.4500E-03, 4.3900E-03, 4.0400E-03, 3.4200E-03, 
            2.1000E-03, 5.3000E-04, 1.5000E-04, 1.9000E-05, 4.0000E-06, 
            3.9000E-07, 1.9000E-08} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.6800E-01, 1.6800E-01, 1.6800E-01, 1.6800E-01, 
            1.6800E-01, 1.6700E-01, 1.6700E-01, 1.6700E-01, 1.6600E-01, 
            1.6600E-01, 1.6400E-01, 1.6100E-01, 1.5500E-01, 1.4800E-01, 
            1.3900E-01, 1.2900E-01, 1.1800E-01, 9.6400E-02, 6.7300E-02, 
            3.4300E-02, 1.7100E-02, 8.6300E-03, 4.4700E-03, 2.3900E-03, 
            7.5000E-04, 6.6000E-05, 9.7000E-06, 5.3000E-07, 6.1000E-08, 
            2.7000E-09, 4.8000E-11} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.2400E+00, 1.2200E+00, 1.1700E+00, 1.0800E+00, 
            9.7500E-01, 7.2900E-01, 4.9400E-01, 3.0800E-01, 1.8000E-01, 
            1.0100E-01, 5.7500E-02, 2.7100E-02, 2.3300E-02, 2.3100E-02, 
            2.1200E-02, 1.7900E-02, 1.4300E-02, 8.0600E-03, 2.9300E-03, 
            5.4100E-04, 2.5200E-04, 2.4100E-04, 2.2700E-04, 1.9400E-04, 
            1.2000E-04, 3.0000E-05, 8.2000E-06, 1.0000E-06, 2.1000E-07, 
            2.1000E-08, 1.0000E-09} );

    subshell_half_profiles[4] = 
      std::vector<double>( {9.1900E-01, 9.1800E-01, 9.1600E-01, 9.0400E-01, 
            8.7900E-01, 7.7600E-01, 6.1900E-01, 4.5200E-01, 3.0700E-01, 
            1.9900E-01, 1.2400E-01, 4.5200E-02, 1.6200E-02, 6.6600E-03, 
            4.0200E-03, 3.5000E-03, 3.4600E-03, 3.2800E-03, 2.4900E-03, 
            1.2700E-03, 6.1800E-04, 3.0700E-04, 1.5700E-04, 8.3300E-05, 
            2.6000E-05, 2.2000E-06, 3.2000E-07, 1.7000E-08, 2.0000E-09, 
            8.6000E-11, 1.6000E-12} );
  }
};

//! The default Compton profile generator implementation for A=14
template<>
struct DefaultComptonProfileGeneratorImpl<14u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 5 );

    subshell_half_profiles[0] = 
      std::vector<double>( {6.3500E-02, 6.3500E-02, 6.3500E-02, 6.3500E-02, 
            6.3500E-02, 6.3400E-02, 6.3300E-02, 6.3200E-02, 6.3100E-02, 
            6.3000E-02, 6.2800E-02, 6.2400E-02, 6.1900E-02, 6.1400E-02, 
            6.0800E-02, 6.0100E-02, 5.9300E-02, 5.7600E-02, 5.4500E-02, 
            4.8800E-02, 4.2500E-02, 3.6300E-02, 3.0400E-02, 2.5200E-02, 
            1.7000E-02, 5.6000E-03, 2.0000E-03, 3.2000E-04, 7.3000E-05, 
            7.8000E-06, 4.0000E-07} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.7500E-01, 2.7500E-01, 2.7400E-01, 2.7300E-01, 
            2.7200E-01, 2.6800E-01, 2.6200E-01, 2.5500E-01, 2.4700E-01, 
            2.3700E-01, 2.2700E-01, 2.0500E-01, 1.8100E-01, 1.5600E-01, 
            1.3200E-01, 1.1000E-01, 9.0600E-02, 5.8400E-02, 2.7900E-02, 
            8.2200E-03, 4.5000E-03, 4.2500E-03, 4.1200E-03, 3.6900E-03, 
            2.5000E-03, 7.0000E-04, 2.1000E-04, 2.8000E-05, 5.9000E-06, 
            5.9000E-07, 2.9000E-08} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.4900E-01, 1.4900E-01, 1.4900E-01, 1.4900E-01, 
            1.4900E-01, 1.4900E-01, 1.4900E-01, 1.4900E-01, 1.4800E-01, 
            1.4800E-01, 1.4700E-01, 1.4500E-01, 1.4200E-01, 1.3700E-01, 
            1.3100E-01, 1.2400E-01, 1.1600E-01, 9.9200E-02, 7.4000E-02, 
            4.1400E-02, 2.2100E-02, 1.1800E-02, 6.3600E-03, 3.5200E-03, 
            1.2000E-03, 1.1000E-04, 1.7000E-05, 9.4000E-07, 1.1000E-07, 
            4.9000E-09, 8.9000E-11} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.0400E+00, 1.0300E+00, 9.9200E-01, 9.4000E-01, 
            8.7200E-01, 7.0700E-01, 5.3100E-01, 3.7400E-01, 2.4800E-01, 
            1.5800E-01, 9.7900E-02, 4.0700E-02, 2.5600E-02, 2.3700E-02, 
            2.3500E-02, 2.2100E-02, 1.9400E-02, 1.2900E-02, 5.6600E-03, 
            1.1600E-03, 3.6100E-04, 2.8700E-04, 2.8300E-04, 2.5800E-04, 
            1.8000E-04, 4.9000E-05, 1.4000E-05, 1.9000E-06, 3.9000E-07, 
            3.9000E-08, 1.9000E-09} );

    subshell_half_profiles[4] = 
      std::vector<double>( {7.4400E-01, 7.4400E-01, 7.4300E-01, 7.3900E-01, 
            7.2800E-01, 6.8100E-01, 5.9700E-01, 4.9000E-01, 3.8000E-01, 
            2.8100E-01, 2.0100E-01, 9.4600E-02, 4.1900E-02, 1.8300E-02, 
            8.7200E-03, 5.2400E-03, 4.2100E-03, 4.0100E-03, 3.6000E-03, 
            2.1700E-03, 1.1500E-03, 5.9900E-04, 3.1900E-04, 1.7400E-04, 
            5.6000E-05, 5.2000E-06, 7.7000E-07, 4.3000E-08, 5.0000E-09, 
            2.2000E-10, 4.1000E-12} );
  }
};

//! The default Compton profile generator implementation for A=15
template<>
struct DefaultComptonProfileGeneratorImpl<15u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 5 );

    subshell_half_profiles[0] = 
      std::vector<double>( {5.9200E-02, 5.9200E-02, 5.9100E-02, 5.9100E-02, 
            5.9100E-02, 5.9100E-02, 5.9000E-02, 5.8900E-02, 5.8800E-02, 
            5.8700E-02, 5.8600E-02, 5.8300E-02, 5.7900E-02, 5.7400E-02, 
            5.6900E-02, 5.6400E-02, 5.5700E-02, 5.4300E-02, 5.1800E-02, 
            4.7000E-02, 4.1600E-02, 3.6200E-02, 3.0900E-02, 2.6100E-02, 
            1.8000E-02, 6.6000E-03, 2.4000E-03, 4.2000E-04, 9.8000E-05, 
            1.1000E-05, 5.7000E-07} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.5100E-01, 2.5000E-01, 2.5000E-01, 2.4900E-01, 
            2.4800E-01, 2.4500E-01, 2.4100E-01, 2.3500E-01, 2.2900E-01, 
            2.2200E-01, 2.1400E-01, 1.9600E-01, 1.7600E-01, 1.5600E-01, 
            1.3600E-01, 1.1600E-01, 9.8200E-02, 6.7400E-02, 3.5300E-02, 
            1.1100E-02, 4.9200E-03, 4.0900E-03, 4.0600E-03, 3.8200E-03, 
            2.8000E-03, 8.9000E-04, 2.8000E-04, 3.9000E-05, 8.4000E-06, 
            8.5000E-07, 4.3000E-08} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.3400E-01, 1.3400E-01, 1.3400E-01, 1.3400E-01, 
            1.3400E-01, 1.3400E-01, 1.3400E-01, 1.3400E-01, 1.3400E-01, 
            1.3400E-01, 1.3300E-01, 1.3200E-01, 1.3000E-01, 1.2700E-01, 
            1.2300E-01, 1.1800E-01, 1.1200E-01, 9.9100E-02, 7.8100E-02, 
            4.7500E-02, 2.7200E-02, 1.5200E-02, 8.5600E-03, 4.8900E-03, 
            1.7000E-03, 1.7000E-04, 2.7000E-05, 1.6000E-06, 1.9000E-07, 
            8.5000E-09, 1.5000E-10} );

    subshell_half_profiles[3] = 
      std::vector<double>( {8.9700E-01, 8.9000E-01, 8.6800E-01, 8.3300E-01, 
            7.8600E-01, 6.6900E-01, 5.3600E-01, 4.0700E-01, 2.9500E-01, 
            2.0500E-01, 1.3800E-01, 6.1100E-02, 3.2000E-02, 2.4300E-02, 
            2.3300E-02, 2.3200E-02, 2.2000E-02, 1.7000E-02, 8.9300E-03, 
            2.2100E-03, 5.7900E-04, 3.3000E-04, 3.1700E-04, 3.0600E-04, 
            2.3000E-04, 7.2000E-05, 2.2000E-05, 3.0000E-06, 6.5000E-07, 
            6.5000E-08, 3.3000E-09} );

    subshell_half_profiles[4] = 
      std::vector<double>( {6.3100E-01, 6.3100E-01, 6.3100E-01, 6.2900E-01, 
            6.2400E-01, 5.9900E-01, 5.5100E-01, 4.8300E-01, 4.0400E-01, 
            3.2500E-01, 2.5300E-01, 1.4200E-01, 7.4100E-02, 3.7100E-02, 
            1.8500E-02, 9.8000E-03, 6.0900E-03, 4.3300E-03, 4.2000E-03, 
            3.0400E-03, 1.7800E-03, 9.8200E-04, 5.4400E-04, 3.0600E-04, 
            1.0000E-04, 1.0000E-05, 1.6000E-06, 9.1000E-08, 1.1000E-08, 
            4.8000E-10, 8.7000E-12} );
  }
};

//! The default Compton profile generator implementation for A=16
template<>
struct DefaultComptonProfileGeneratorImpl<16u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 5 );

    subshell_half_profiles[0] = 
      std::vector<double>( {5.5300E-02, 5.5300E-02, 5.5300E-02, 5.5300E-02, 
            5.5300E-02, 5.5300E-02, 5.5200E-02, 5.5200E-02, 5.5100E-02, 
            5.5000E-02, 5.4900E-02, 5.4600E-02, 5.4300E-02, 5.3900E-02, 
            5.3500E-02, 5.3000E-02, 5.2500E-02, 5.1300E-02, 4.9300E-02, 
            4.5200E-02, 4.0600E-02, 3.5800E-02, 3.1100E-02, 2.6700E-02, 
            1.9000E-02, 7.5000E-03, 2.9000E-03, 5.3000E-04, 1.3000E-04, 
            1.5000E-05, 7.8000E-07} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.3000E-01, 2.3000E-01, 2.3000E-01, 2.2900E-01, 
            2.2800E-01, 2.2600E-01, 2.2300E-01, 2.1800E-01, 2.1300E-01, 
            2.0800E-01, 2.0100E-01, 1.8700E-01, 1.7100E-01, 1.5400E-01, 
            1.3700E-01, 1.2000E-01, 1.0300E-01, 7.4600E-02, 4.2300E-02, 
            1.4600E-02, 5.8200E-03, 4.0400E-03, 3.9200E-03, 3.8300E-03, 
            3.1000E-03, 1.1000E-03, 3.6000E-04, 5.3000E-05, 1.2000E-05, 
            1.2000E-06, 6.1000E-08} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.2200E-01, 1.2200E-01, 1.2200E-01, 1.2200E-01, 
            1.2200E-01, 1.2200E-01, 1.2200E-01, 1.2200E-01, 1.2200E-01, 
            1.2200E-01, 1.2200E-01, 1.2100E-01, 1.1900E-01, 1.1700E-01, 
            1.1500E-01, 1.1100E-01, 1.0700E-01, 9.7100E-02, 8.0000E-02, 
            5.2400E-02, 3.1900E-02, 1.8800E-02, 1.1000E-02, 6.5000E-03, 
            2.4000E-03, 2.6000E-04, 4.2000E-05, 2.6000E-06, 3.1000E-07, 
            1.4000E-08, 2.6000E-10} );

    subshell_half_profiles[3] = 
      std::vector<double>( {7.9400E-01, 7.8800E-01, 7.7300E-01, 7.4800E-01, 
            7.1500E-01, 6.2800E-01, 5.2600E-01, 4.2100E-01, 3.2400E-01, 
            2.4000E-01, 1.7300E-01, 8.4700E-02, 4.2900E-02, 2.7200E-02, 
            2.3100E-02, 2.2700E-02, 2.2500E-02, 1.9600E-02, 1.2200E-02, 
            3.7100E-03, 9.8300E-04, 4.0700E-04, 3.3900E-04, 3.3600E-04, 
            2.8000E-04, 9.9000E-05, 3.2000E-05, 4.6000E-06, 1.0000E-06, 
            1.0000E-07, 5.2000E-09} );

    subshell_half_profiles[4] = 
      std::vector<double>( {5.5100E-01, 5.5100E-01, 5.5000E-01, 5.4900E-01, 
            5.4700E-01, 5.3300E-01, 5.0400E-01, 4.5900E-01, 4.0400E-01, 
            3.4300E-01, 2.8300E-01, 1.7900E-01, 1.0600E-01, 5.9600E-02, 
            3.2600E-02, 1.7900E-02, 1.0300E-02, 5.0800E-03, 4.3600E-03, 
            3.7200E-03, 2.4300E-03, 1.4400E-03, 8.2900E-04, 4.8200E-04, 
            1.7000E-04, 1.8000E-05, 2.9000E-06, 1.7000E-07, 2.0000E-08, 
            9.3000E-10, 1.7000E-11} );
  }
};

//! The default Compton profile generator implementation for A=17
template<>
struct DefaultComptonProfileGeneratorImpl<17u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 5 );

    subshell_half_profiles[0] = 
      std::vector<double>( {5.2000E-02, 5.2000E-02, 5.2000E-02, 5.2000E-02, 
            5.2000E-02, 5.1900E-02, 5.1900E-02, 5.1800E-02, 5.1800E-02, 
            5.1700E-02, 5.1600E-02, 5.1400E-02, 5.1100E-02, 5.0800E-02, 
            5.0500E-02, 5.0100E-02, 4.9700E-02, 4.8700E-02, 4.6900E-02, 
            4.3500E-02, 3.9500E-02, 3.5300E-02, 3.1100E-02, 2.7100E-02, 
            2.0000E-02, 8.4000E-03, 3.4000E-03, 6.6000E-04, 1.7000E-04, 
            1.9000E-05, 1.0000E-06} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.1300E-01, 2.1300E-01, 2.1300E-01, 2.1200E-01, 
            2.1200E-01, 2.1000E-01, 2.0700E-01, 2.0400E-01, 2.0000E-01, 
            1.9500E-01, 1.9000E-01, 1.7800E-01, 1.6500E-01, 1.5000E-01, 
            1.3600E-01, 1.2100E-01, 1.0700E-01, 8.0200E-02, 4.8700E-02, 
            1.8500E-02, 7.2000E-03, 4.2000E-03, 3.7700E-03, 3.7400E-03, 
            3.2000E-03, 1.3000E-03, 4.5000E-04, 7.0000E-05, 1.6000E-05, 
            1.7000E-06, 8.5000E-08} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.1200E-01, 1.1200E-01, 1.1200E-01, 1.1200E-01, 
            1.1200E-01, 1.1200E-01, 1.1200E-01, 1.1200E-01, 1.1200E-01, 
            1.1200E-01, 1.1200E-01, 1.1100E-01, 1.1000E-01, 1.0900E-01, 
            1.0700E-01, 1.0500E-01, 1.0100E-01, 9.4000E-02, 8.0300E-02, 
            5.6000E-02, 3.6100E-02, 2.2400E-02, 1.3600E-02, 8.3100E-03, 
            3.2000E-03, 3.8000E-04, 6.4000E-05, 4.0000E-06, 4.9000E-07, 
            2.3000E-08, 4.2000E-10} );

    subshell_half_profiles[3] = 
      std::vector<double>( {7.1300E-01, 7.0900E-01, 6.9800E-01, 6.8000E-01, 
            6.5500E-01, 5.8900E-01, 5.0900E-01, 4.2300E-01, 3.4000E-01, 
            2.6500E-01, 2.0100E-01, 1.0800E-01, 5.6900E-02, 3.3100E-02, 
            2.4300E-02, 2.2100E-02, 2.1900E-02, 2.0800E-02, 1.5000E-02, 
            5.5600E-03, 1.6300E-03, 5.6000E-04, 3.6600E-04, 3.5200E-04, 
            3.2000E-04, 1.3000E-04, 4.4000E-05, 6.6000E-06, 1.5000E-06, 
            1.5000E-07, 7.8000E-09} );

    subshell_half_profiles[4] = 
      std::vector<double>( {4.9000E-01, 4.9000E-01, 4.8900E-01, 4.8900E-01, 
            4.8700E-01, 4.7900E-01, 4.6000E-01, 4.3100E-01, 3.9200E-01, 
            3.4600E-01, 2.9800E-01, 2.0600E-01, 1.3400E-01, 8.2600E-02, 
            4.9300E-02, 2.8800E-02, 1.6900E-02, 6.9500E-03, 4.4000E-03, 
            4.1200E-03, 3.0200E-03, 1.9300E-03, 1.1700E-03, 7.0200E-04, 
            2.6000E-04, 3.0000E-05, 4.9000E-06, 3.0000E-07, 3.6000E-08, 
            1.6000E-09, 3.0000E-11} );
  }
};

//! The default Compton profile generator implementation for A=18
template<>
struct DefaultComptonProfileGeneratorImpl<18u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 5 );

    subshell_half_profiles[0] = 
      std::vector<double>( {4.9000E-02, 4.9000E-02, 4.9000E-02, 4.9000E-02, 
            4.9000E-02, 4.9000E-02, 4.8900E-02, 4.8900E-02, 4.8800E-02, 
            4.8800E-02, 4.8700E-02, 4.8500E-02, 4.8300E-02, 4.8000E-02, 
            4.7800E-02, 4.7400E-02, 4.7100E-02, 4.6200E-02, 4.4700E-02, 
            4.1800E-02, 3.8300E-02, 3.4700E-02, 3.0900E-02, 2.7200E-02, 
            2.1000E-02, 9.2000E-03, 3.9000E-03, 8.1000E-04, 2.1000E-04, 
            2.5000E-05, 1.4000E-06} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.9800E-01, 1.9800E-01, 1.9800E-01, 1.9800E-01, 
            1.9700E-01, 1.9600E-01, 1.9300E-01, 1.9100E-01, 1.8700E-01, 
            1.8400E-01, 1.7900E-01, 1.7000E-01, 1.5900E-01, 1.4600E-01, 
            1.3400E-01, 1.2100E-01, 1.0800E-01, 8.4300E-02, 5.4200E-02, 
            2.2600E-02, 9.0200E-03, 4.6200E-03, 3.6800E-03, 3.6100E-03, 
            3.3000E-03, 1.5000E-03, 5.6000E-04, 9.1000E-05, 2.1000E-05, 
            2.2000E-06, 1.2000E-07} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 
            1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 
            1.0400E-01, 1.0300E-01, 1.0300E-01, 1.0200E-01, 1.0100E-01, 
            1.0000E-01, 9.8300E-02, 9.6100E-02, 9.0400E-02, 7.9400E-02, 
            5.8600E-02, 3.9800E-02, 2.5800E-02, 1.6300E-02, 1.0300E-02, 
            4.1000E-03, 5.3000E-04, 9.3000E-05, 6.0000E-06, 7.5000E-07, 
            3.5000E-08, 6.5000E-10} );

    subshell_half_profiles[3] = 
      std::vector<double>( {6.4900E-01, 6.4600E-01, 6.3700E-01, 6.2300E-01, 
            6.0400E-01, 5.5200E-01, 4.8900E-01, 4.1900E-01, 3.4800E-01, 
            2.8100E-01, 2.2200E-01, 1.3000E-01, 7.2300E-02, 4.1500E-02, 
            2.7500E-02, 2.2400E-02, 2.1100E-02, 2.0800E-02, 1.7000E-02, 
            7.5800E-03, 2.5300E-03, 8.3100E-04, 4.2000E-04, 3.6200E-04, 
            3.5000E-04, 1.6000E-04, 5.8000E-05, 9.2000E-06, 2.1000E-06, 
            2.2000E-07, 1.1000E-08} );

    subshell_half_profiles[4] = 
      std::vector<double>( {4.4200E-01, 4.4200E-01, 4.4100E-01, 4.4100E-01, 
            4.4000E-01, 4.3500E-01, 4.2300E-01, 4.0200E-01, 3.7400E-01, 
            3.4000E-01, 3.0200E-01, 2.2400E-01, 1.5600E-01, 1.0400E-01, 
            6.6500E-02, 4.1600E-02, 2.5700E-02, 1.0200E-02, 4.6500E-03, 
            4.2000E-03, 3.4500E-03, 2.3800E-03, 1.5200E-03, 9.4900E-04, 
            3.7000E-04, 4.5000E-05, 7.7000E-06, 4.8000E-07, 6.0000E-08, 
            2.8000E-09, 5.1000E-11} );
  }
};

//! The default Compton profile generator implementation for A=19
template<>
struct DefaultComptonProfileGeneratorImpl<19u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 6 );

    subshell_half_profiles[0] = 
      std::vector<double>( {4.6400E-02, 4.6400E-02, 4.6400E-02, 4.6400E-02, 
            4.6400E-02, 4.6300E-02, 4.6300E-02, 4.6300E-02, 4.6200E-02, 
            4.6200E-02, 4.6100E-02, 4.6000E-02, 4.5800E-02, 4.5500E-02, 
            4.5300E-02, 4.5000E-02, 4.4700E-02, 4.4000E-02, 4.2700E-02, 
            4.0200E-02, 3.7200E-02, 3.3900E-02, 3.0600E-02, 2.7200E-02, 
            2.1000E-02, 1.0000E-02, 4.5000E-03, 9.7000E-04, 2.6000E-04, 
            3.2000E-05, 1.8000E-06} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.8500E-01, 1.8500E-01, 1.8500E-01, 1.8500E-01, 
            1.8400E-01, 1.8300E-01, 1.8100E-01, 1.7900E-01, 1.7600E-01, 
            1.7300E-01, 1.7000E-01, 1.6200E-01, 1.5200E-01, 1.4200E-01, 
            1.3100E-01, 1.2000E-01, 1.0900E-01, 8.7200E-02, 5.8800E-02, 
            2.6700E-02, 1.1200E-02, 5.3500E-03, 3.7200E-03, 3.4800E-03, 
            3.3000E-03, 1.7000E-03, 6.7000E-04, 1.2000E-04, 2.7000E-05, 
            2.9000E-06, 1.5000E-07} );

    subshell_half_profiles[2] = 
      std::vector<double>( {9.6500E-02, 9.6500E-02, 9.6500E-02, 9.6500E-02, 
            9.6500E-02, 9.6500E-02, 9.6500E-02, 9.6500E-02, 9.6400E-02, 
            9.6400E-02, 9.6300E-02, 9.6000E-02, 9.5600E-02, 9.4900E-02, 
            9.3900E-02, 9.2600E-02, 9.0900E-02, 8.6600E-02, 7.7800E-02, 
            6.0000E-02, 4.2800E-02, 2.8900E-02, 1.9000E-02, 1.2300E-02, 
            5.2000E-03, 7.1000E-04, 1.3000E-04, 8.8000E-06, 1.1000E-06, 
            5.3000E-08, 9.9000E-10} );

    subshell_half_profiles[3] = 
      std::vector<double>( {5.7000E-01, 5.6800E-01, 5.6200E-01, 5.5200E-01, 
            5.3900E-01, 5.0300E-01, 4.5700E-01, 4.0500E-01, 3.4900E-01, 
            2.9500E-01, 2.4300E-01, 1.5600E-01, 9.4600E-02, 5.6300E-02, 
            3.5500E-02, 2.5700E-02, 2.2100E-02, 2.1200E-02, 1.9200E-02, 
            1.0200E-02, 3.9000E-03, 1.3300E-03, 5.6200E-04, 4.0100E-04, 
            3.8000E-04, 2.0000E-04, 7.8000E-05, 1.3000E-05, 3.0000E-06, 
            3.2000E-07, 1.7000E-08} );

    subshell_half_profiles[4] = 
      std::vector<double>( {3.7600E-01, 3.7600E-01, 3.7600E-01, 3.7600E-01, 
            3.7500E-01, 3.7300E-01, 3.6700E-01, 3.5700E-01, 3.4200E-01, 
            3.2200E-01, 2.9800E-01, 2.4200E-01, 1.8500E-01, 1.3400E-01, 
            9.3300E-02, 6.2800E-02, 4.1300E-02, 1.7400E-02, 6.2500E-03, 
            4.5900E-03, 4.1700E-03, 3.1200E-03, 2.1200E-03, 1.3700E-03, 
            5.7000E-04, 7.3000E-05, 1.3000E-05, 8.5000E-07, 1.1000E-07, 
            5.0000E-09, 9.0000E-11} );

    subshell_half_profiles[5] = 
      std::vector<double>( {2.4600E+00, 2.3200E+00, 1.9600E+00, 1.4900E+00, 
            1.0200E+00, 3.7100E-01, 1.1100E-01, 4.9100E-02, 4.2700E-02, 
            4.1900E-02, 3.7300E-02, 2.3300E-02, 1.2300E-02, 6.0400E-03, 
            2.9500E-03, 1.5700E-03, 1.0300E-03, 8.2300E-04, 7.7800E-04, 
            4.3500E-04, 1.6700E-04, 5.5900E-05, 2.2300E-05, 1.5100E-05, 
            1.4000E-05, 7.6000E-06, 2.9000E-06, 4.9000E-07, 1.1000E-07, 
            1.2000E-08, 6.3000E-10} );
  }
};

//! The default Compton profile generator implementation for A=20
template<>
struct DefaultComptonProfileGeneratorImpl<20u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 6 );

    subshell_half_profiles[0] = 
      std::vector<double>( {4.4000E-02, 4.4000E-02, 4.4000E-02, 4.4000E-02, 
            4.4000E-02, 4.4000E-02, 4.3900E-02, 4.3900E-02, 4.3900E-02, 
            4.3800E-02, 4.3800E-02, 4.3600E-02, 4.3500E-02, 4.3300E-02, 
            4.3100E-02, 4.2800E-02, 4.2600E-02, 4.2000E-02, 4.0900E-02, 
            3.8700E-02, 3.6000E-02, 3.3200E-02, 3.0200E-02, 2.7100E-02, 
            2.1000E-02, 1.1000E-02, 5.0000E-03, 1.2000E-03, 3.2000E-04, 
            4.0000E-05, 2.3000E-06} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.7400E-01, 1.7400E-01, 1.7400E-01, 1.7400E-01, 
            1.7300E-01, 1.7200E-01, 1.7100E-01, 1.6900E-01, 1.6700E-01, 
            1.6400E-01, 1.6100E-01, 1.5400E-01, 1.4600E-01, 1.3800E-01, 
            1.2800E-01, 1.1800E-01, 1.0900E-01, 8.9100E-02, 6.2600E-02, 
            3.0700E-02, 1.3700E-02, 6.3700E-03, 3.9300E-03, 3.3900E-03, 
            3.3000E-03, 1.9000E-03, 7.9000E-04, 1.4000E-04, 3.4000E-05, 
            3.8000E-06, 2.0000E-07} );

    subshell_half_profiles[2] = 
      std::vector<double>( {9.0200E-02, 9.0200E-02, 9.0200E-02, 9.0200E-02, 
            9.0200E-02, 9.0200E-02, 9.0200E-02, 9.0200E-02, 9.0100E-02, 
            9.0100E-02, 9.0000E-02, 8.9900E-02, 8.9500E-02, 8.9000E-02, 
            8.8300E-02, 8.7300E-02, 8.6100E-02, 8.2700E-02, 7.5800E-02, 
            6.0700E-02, 4.5100E-02, 3.1700E-02, 2.1600E-02, 1.4400E-02, 
            6.4000E-03, 9.4000E-04, 1.8000E-04, 1.3000E-05, 1.6000E-06, 
            7.8000E-08, 1.5000E-09} );

    subshell_half_profiles[3] = 
      std::vector<double>( {5.0800E-01, 5.0700E-01, 5.0300E-01, 4.9600E-01, 
            4.8600E-01, 4.6000E-01, 4.2600E-01, 3.8600E-01, 3.4200E-01, 
            2.9800E-01, 2.5400E-01, 1.7600E-01, 1.1500E-01, 7.2400E-02, 
            4.6000E-02, 3.1400E-02, 2.4500E-02, 2.1200E-02, 2.0400E-02, 
            1.2800E-02, 5.5900E-03, 2.0600E-03, 8.0600E-04, 4.6600E-04, 
            4.1000E-04, 2.5000E-04, 1.0000E-04, 1.8000E-05, 4.2000E-06, 
            4.6000E-07, 2.4000E-08} );

    subshell_half_profiles[4] = 
      std::vector<double>( {3.3000E-01, 3.3000E-01, 3.3000E-01, 3.3000E-01, 
            3.3000E-01, 3.2900E-01, 3.2600E-01, 3.2000E-01, 3.1100E-01, 
            2.9900E-01, 2.8300E-01, 2.4400E-01, 1.9900E-01, 1.5500E-01, 
            1.1600E-01, 8.3500E-02, 5.8400E-02, 2.7100E-02, 9.0500E-03, 
            4.8300E-03, 4.6500E-03, 3.7900E-03, 2.7300E-03, 1.8500E-03, 
            8.1000E-04, 1.1000E-04, 2.1000E-05, 1.4000E-06, 1.8000E-07, 
            8.4000E-09, 1.7000E-10} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.9500E+00, 1.8700E+00, 1.6800E+00, 1.4000E+00, 
            1.0900E+00, 5.4700E-01, 2.2800E-01, 9.3500E-02, 5.3200E-02, 
            4.6600E-02, 4.6300E-02, 3.9200E-02, 2.6400E-02, 1.5400E-02, 
            8.3100E-03, 4.3900E-03, 2.4600E-03, 1.3400E-03, 1.2600E-03, 
            8.4800E-04, 3.7600E-04, 1.3700E-04, 5.1200E-05, 2.7600E-05, 
            2.3000E-05, 1.4000E-05, 5.8000E-06, 1.0000E-06, 2.4000E-07, 
            2.6000E-08, 1.4000E-09} );
  }
};

//! The default Compton profile generator implementation for A=21
template<>
struct DefaultComptonProfileGeneratorImpl<21u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 7 );

    subshell_half_profiles[0] = 
      std::vector<double>( {4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1800E-02, 
            4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1700E-02, 
            4.1700E-02, 4.1600E-02, 4.1500E-02, 4.1400E-02, 4.1200E-02, 
            4.1100E-02, 4.0800E-02, 4.0600E-02, 4.0100E-02, 3.9100E-02, 
            3.7200E-02, 3.4900E-02, 3.2400E-02, 2.9700E-02, 2.6900E-02, 
            2.2000E-02, 1.1000E-02, 5.5000E-03, 1.3000E-03, 3.8000E-04, 
            5.0000E-05, 2.9000E-06} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.6400E-01, 1.6400E-01, 1.6400E-01, 1.6400E-01, 
            1.6300E-01, 1.6200E-01, 1.6100E-01, 1.6000E-01, 1.5800E-01, 
            1.5500E-01, 1.5300E-01, 1.4700E-01, 1.4000E-01, 1.3300E-01, 
            1.2500E-01, 1.1600E-01, 1.0800E-01, 9.0100E-02, 6.5700E-02, 
            3.4400E-02, 1.6300E-02, 7.6500E-03, 4.3300E-03, 3.3800E-03, 
            3.2000E-03, 2.1000E-03, 9.2000E-04, 1.8000E-04, 4.3000E-05, 
            4.9000E-06, 2.6000E-07} );

    subshell_half_profiles[2] = 
      std::vector<double>( {8.4700E-02, 8.4700E-02, 8.4700E-02, 8.4700E-02, 
            8.4700E-02, 8.4700E-02, 8.4700E-02, 8.4700E-02, 8.4600E-02, 
            8.4600E-02, 8.4600E-02, 8.4400E-02, 8.4200E-02, 8.3800E-02, 
            8.3300E-02, 8.2500E-02, 8.1600E-02, 7.9000E-02, 7.3400E-02, 
            6.0700E-02, 4.6700E-02, 3.4100E-02, 2.3900E-02, 1.6500E-02, 
            7.6000E-03, 1.2000E-03, 2.4000E-04, 1.7000E-05, 2.3000E-06, 
            1.1000E-07, 2.1000E-09} );

    subshell_half_profiles[3] = 
      std::vector<double>( {4.7100E-01, 4.7000E-01, 4.6700E-01, 4.6100E-01, 
            4.5300E-01, 4.3200E-01, 4.0400E-01, 3.7100E-01, 3.3400E-01, 
            2.9600E-01, 2.5800E-01, 1.8700E-01, 1.2800E-01, 8.4400E-02, 
            5.4900E-02, 3.6900E-02, 2.7100E-02, 2.0800E-02, 2.0200E-02, 
            1.4500E-02, 7.1900E-03, 2.9200E-03, 1.1400E-03, 5.6200E-04, 
            4.1000E-04, 2.8000E-04, 1.2000E-04, 2.3000E-05, 5.5000E-06, 
            6.2000E-07, 3.3000E-08} );

    subshell_half_profiles[4] = 
      std::vector<double>( {3.0400E-01, 3.0400E-01, 3.0400E-01, 3.0400E-01, 
            3.0400E-01, 3.0300E-01, 3.0100E-01, 2.9700E-01, 2.9000E-01, 
            2.8100E-01, 2.7000E-01, 2.4000E-01, 2.0300E-01, 1.6500E-01, 
            1.2900E-01, 9.7100E-02, 7.1200E-02, 3.5900E-02, 1.2400E-02, 
            4.9000E-03, 4.6900E-03, 4.1300E-03, 3.1600E-03, 2.2500E-03, 
            1.0000E-03, 1.6000E-04, 3.0000E-05, 2.1000E-06, 2.7000E-07, 
            1.3000E-08, 2.4000E-10} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.1000E-01, 3.1000E-01, 3.1000E-01, 3.1000E-01, 
            3.1000E-01, 3.0900E-01, 3.0700E-01, 3.0300E-01, 2.9400E-01, 
            2.8200E-01, 2.6600E-01, 2.2900E-01, 1.9000E-01, 1.5400E-01, 
            1.2300E-01, 9.7400E-02, 7.6800E-02, 4.7600E-02, 2.3500E-02, 
            7.6600E-03, 2.7000E-03, 1.0300E-03, 4.2400E-04, 1.8700E-04, 
            4.3000E-05, 2.3000E-06, 2.3000E-07, 6.6000E-09, 4.6000E-10, 
            9.8000E-12, 1.5000E-13} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.8400E+00, 1.7800E+00, 1.6100E+00, 1.3700E+00, 
            1.0900E+00, 5.8900E-01, 2.6600E-01, 1.1200E-01, 5.6900E-02, 
            4.3500E-02, 4.2200E-02, 3.8900E-02, 2.8900E-02, 1.8500E-02, 
            1.0800E-02, 6.0300E-03, 3.3800E-03, 1.4700E-03, 1.2000E-03, 
            9.4300E-04, 4.7900E-04, 1.9400E-04, 7.3600E-05, 3.4000E-05, 
            2.3000E-05, 1.6000E-05, 7.0000E-06, 1.3000E-06, 3.1000E-07, 
            3.5000E-08, 1.8000E-09} );
  }
};

//! The default Compton profile generator implementation for A=22
template<>
struct DefaultComptonProfileGeneratorImpl<22u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 7 );

    subshell_half_profiles[0] = 
      std::vector<double>( {3.9900E-02, 3.9900E-02, 3.9900E-02, 3.9900E-02, 
            3.9900E-02, 3.9900E-02, 3.9800E-02, 3.9800E-02, 3.9800E-02, 
            3.9800E-02, 3.9700E-02, 3.9600E-02, 3.9500E-02, 3.9400E-02, 
            3.9200E-02, 3.9000E-02, 3.8800E-02, 3.8400E-02, 3.7500E-02, 
            3.5900E-02, 3.3800E-02, 3.1600E-02, 2.9100E-02, 2.6700E-02, 
            2.2000E-02, 1.2000E-02, 6.0000E-03, 1.5000E-03, 4.5000E-04, 
            6.1000E-05, 3.6000E-06} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.5500E-01, 1.5500E-01, 1.5500E-01, 1.5500E-01, 
            1.5400E-01, 1.5400E-01, 1.5300E-01, 1.5100E-01, 1.5000E-01, 
            1.4800E-01, 1.4600E-01, 1.4100E-01, 1.3500E-01, 1.2800E-01, 
            1.2100E-01, 1.1400E-01, 1.0600E-01, 9.0500E-02, 6.8000E-02, 
            3.7800E-02, 1.8900E-02, 9.1400E-03, 4.9200E-03, 3.4700E-03, 
            3.1000E-03, 2.2000E-03, 1.0000E-03, 2.1000E-04, 5.3000E-05, 
            6.2000E-06, 3.3000E-07} );

    subshell_half_profiles[2] = 
      std::vector<double>( {7.9800E-02, 7.9800E-02, 7.9800E-02, 7.9800E-02, 
            7.9800E-02, 7.9800E-02, 7.9800E-02, 7.9800E-02, 7.9800E-02, 
            7.9800E-02, 7.9700E-02, 7.9600E-02, 7.9400E-02, 7.9200E-02, 
            7.8700E-02, 7.8200E-02, 7.7400E-02, 7.5400E-02, 7.0900E-02, 
            6.0300E-02, 4.7900E-02, 3.6000E-02, 2.6100E-02, 1.8500E-02, 
            9.0000E-03, 1.5000E-03, 3.1000E-04, 2.4000E-05, 3.2000E-06, 
            1.6000E-07, 3.0000E-09} );

    subshell_half_profiles[3] = 
      std::vector<double>( {4.4100E-01, 4.4000E-01, 4.3700E-01, 4.3200E-01, 
            4.2600E-01, 4.0800E-01, 3.8500E-01, 3.5700E-01, 3.2600E-01, 
            2.9300E-01, 2.5900E-01, 1.9400E-01, 1.3900E-01, 9.5000E-02, 
            6.3700E-02, 4.3100E-02, 3.0600E-02, 2.0900E-02, 1.9500E-02, 
            1.5700E-02, 8.7200E-03, 3.8900E-03, 1.5900E-03, 7.1700E-04, 
            4.1000E-04, 3.1000E-04, 1.5000E-04, 2.9000E-05, 7.1000E-06, 
            8.0000E-07, 4.3000E-08} );

    subshell_half_profiles[4] = 
      std::vector<double>( {2.8200E-01, 2.8200E-01, 2.8200E-01, 2.8200E-01, 
            2.8200E-01, 2.8200E-01, 2.8000E-01, 2.7700E-01, 2.7300E-01, 
            2.6600E-01, 2.5700E-01, 2.3300E-01, 2.0300E-01, 1.7000E-01, 
            1.3800E-01, 1.0800E-01, 8.2200E-02, 4.4700E-02, 1.6500E-02, 
            5.2200E-03, 4.6000E-03, 4.3000E-03, 3.5000E-03, 2.6100E-03, 
            1.3000E-03, 2.1000E-04, 4.1000E-05, 3.0000E-06, 3.9000E-07, 
            1.9000E-08, 3.5000E-10} );

    subshell_half_profiles[5] = 
      std::vector<double>( {2.7500E-01, 2.7500E-01, 2.7500E-01, 2.7500E-01, 
            2.7500E-01, 2.7500E-01, 2.7400E-01, 2.7100E-01, 2.6600E-01, 
            2.5900E-01, 2.4900E-01, 2.2300E-01, 1.9200E-01, 1.6200E-01, 
            1.3400E-01, 1.1000E-01, 8.9400E-02, 5.8600E-02, 3.0900E-02, 
            1.1000E-02, 4.1400E-03, 1.6600E-03, 7.0500E-04, 3.1800E-04, 
            7.6000E-05, 4.2000E-06, 4.3000E-07, 1.3000E-08, 9.0000E-10, 
            1.9000E-11, 6.5000E-14} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.7600E+00, 1.7100E+00, 1.5600E+00, 1.3400E+00, 
            1.0900E+00, 6.1900E-01, 2.9700E-01, 1.3000E-01, 6.2300E-02, 
            4.1900E-02, 3.8400E-02, 3.7000E-02, 2.9700E-02, 2.0500E-02, 
            1.2800E-02, 7.5700E-03, 4.3700E-03, 1.7000E-03, 1.1200E-03, 
            9.7400E-04, 5.6100E-04, 2.5200E-04, 1.0100E-04, 4.3400E-05, 
            2.2000E-05, 1.7000E-05, 8.0000E-06, 1.6000E-06, 3.9000E-07, 
            4.4000E-08, 2.4000E-09} );
  }
};

//! The default Compton profile generator implementation for A=23
template<>
struct DefaultComptonProfileGeneratorImpl<23u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 7 );

    subshell_half_profiles[0] = 
      std::vector<double>( {3.8100E-02, 3.8100E-02, 3.8100E-02, 3.8100E-02, 
            3.8100E-02, 3.8100E-02, 3.8100E-02, 3.8100E-02, 3.8000E-02, 
            3.8000E-02, 3.8000E-02, 3.7900E-02, 3.7800E-02, 3.7600E-02, 
            3.7500E-02, 3.7400E-02, 3.7200E-02, 3.6800E-02, 3.6100E-02, 
            3.4600E-02, 3.2800E-02, 3.0800E-02, 2.8600E-02, 2.6300E-02, 
            2.2000E-02, 1.2000E-02, 6.5000E-03, 1.8000E-03, 5.3000E-04, 
            7.3000E-05, 4.5000E-06} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.4700E-01, 1.4700E-01, 1.4700E-01, 1.4700E-01, 
            1.4600E-01, 1.4600E-01, 1.4500E-01, 1.4400E-01, 1.4200E-01, 
            1.4100E-01, 1.3900E-01, 1.3500E-01, 1.3000E-01, 1.2400E-01, 
            1.1800E-01, 1.1100E-01, 1.0400E-01, 9.0400E-02, 6.9700E-02, 
            4.0800E-02, 2.1500E-02, 1.0800E-02, 5.7000E-03, 3.6900E-03, 
            3.0000E-03, 2.3000E-03, 1.2000E-03, 2.5000E-04, 6.5000E-05, 
            7.7000E-06, 4.2000E-07} );

    subshell_half_profiles[2] = 
      std::vector<double>( {7.5500E-02, 7.5500E-02, 7.5500E-02, 7.5500E-02, 
            7.5500E-02, 7.5500E-02, 7.5500E-02, 7.5500E-02, 7.5500E-02, 
            7.5500E-02, 7.5400E-02, 7.5400E-02, 7.5200E-02, 7.5000E-02, 
            7.4700E-02, 7.4200E-02, 7.3700E-02, 7.2000E-02, 6.8400E-02, 
            5.9500E-02, 4.8500E-02, 3.7600E-02, 2.8000E-02, 2.0400E-02, 
            1.0000E-02, 1.9000E-03, 4.0000E-04, 3.2000E-05, 4.3000E-06, 
            2.2000E-07, 4.3000E-09} );

    subshell_half_profiles[3] = 
      std::vector<double>( {4.1500E-01, 4.1400E-01, 4.1200E-01, 4.0800E-01, 
            4.0300E-01, 3.8800E-01, 3.6800E-01, 3.4400E-01, 3.1700E-01, 
            2.8800E-01, 2.5800E-01, 1.9900E-01, 1.4700E-01, 1.0400E-01, 
            7.2100E-02, 4.9500E-02, 3.4900E-02, 2.1600E-02, 1.8700E-02, 
            1.6400E-02, 1.0100E-02, 4.9400E-03, 2.1500E-03, 9.4600E-04, 
            4.2000E-04, 3.3000E-04, 1.7000E-04, 3.5000E-05, 8.9000E-06, 
            1.0000E-06, 5.6000E-08} );

    subshell_half_profiles[4] = 
      std::vector<double>( {2.6400E-01, 2.6400E-01, 2.6400E-01, 2.6400E-01, 
            2.6400E-01, 2.6400E-01, 2.6300E-01, 2.6100E-01, 2.5700E-01, 
            2.5200E-01, 2.4500E-01, 2.2600E-01, 2.0100E-01, 1.7300E-01, 
            1.4400E-01, 1.1600E-01, 9.1500E-02, 5.3200E-02, 2.1200E-02, 
            5.8700E-03, 4.4600E-03, 4.3400E-03, 3.7500E-03, 2.9200E-03, 
            1.5000E-03, 2.7000E-04, 5.5000E-05, 4.1000E-06, 5.5000E-07, 
            2.7000E-08, 5.4000E-10} );

    subshell_half_profiles[5] = 
      std::vector<double>( {2.5000E-01, 2.5000E-01, 2.5000E-01, 2.5000E-01, 
            2.5000E-01, 2.5000E-01, 2.4900E-01, 2.4800E-01, 2.4500E-01, 
            2.4000E-01, 2.3300E-01, 2.1400E-01, 1.9000E-01, 1.6500E-01, 
            1.4000E-01, 1.1800E-01, 9.8400E-02, 6.7400E-02, 3.7700E-02, 
            1.4500E-02, 5.7900E-03, 2.4300E-03, 1.0700E-03, 4.9600E-04, 
            1.2000E-04, 7.1000E-06, 7.5000E-07, 2.3000E-08, 1.6000E-09, 
            3.5000E-11, 1.2000E-13} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.6900E+00, 1.6500E+00, 1.5100E+00, 1.3200E+00, 
            1.0900E+00, 6.4300E-01, 3.2400E-01, 1.4700E-01, 6.9100E-02, 
            4.2000E-02, 3.5600E-02, 3.4600E-02, 2.9600E-02, 2.1700E-02, 
            1.4400E-02, 8.9700E-03, 5.3800E-03, 2.0300E-03, 1.0500E-03, 
            9.6100E-04, 6.2200E-04, 3.0800E-04, 1.3300E-04, 5.6500E-05, 
            2.2000E-05, 1.8000E-05, 8.9000E-06, 1.9000E-06, 4.7000E-07, 
            5.4000E-08, 2.9000E-09} );
  }
};

//! The default Compton profile generator implementation for A=24
template<>
struct DefaultComptonProfileGeneratorImpl<24u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 7 );

    subshell_half_profiles[0] = 
      std::vector<double>( {3.6500E-02, 3.6500E-02, 3.6500E-02, 3.6500E-02, 
            3.6500E-02, 3.6500E-02, 3.6400E-02, 3.6400E-02, 3.6400E-02, 
            3.6400E-02, 3.6300E-02, 3.6300E-02, 3.6200E-02, 3.6100E-02, 
            3.6000E-02, 3.5800E-02, 3.5700E-02, 3.5300E-02, 3.4700E-02, 
            3.3400E-02, 3.1800E-02, 3.0000E-02, 2.8000E-02, 2.6000E-02, 
            2.2000E-02, 1.3000E-02, 7.0000E-03, 2.0000E-03, 6.2000E-04, 
            8.8000E-05, 5.4000E-06} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.4000E-01, 1.4000E-01, 1.4000E-01, 1.4000E-01, 
            1.3900E-01, 1.3900E-01, 1.3800E-01, 1.3700E-01, 1.3600E-01, 
            1.3400E-01, 1.3300E-01, 1.2900E-01, 1.2500E-01, 1.2000E-01, 
            1.1400E-01, 1.0900E-01, 1.0300E-01, 8.9900E-02, 7.0900E-02, 
            4.3400E-02, 2.4100E-02, 1.2600E-02, 6.6300E-03, 4.0500E-03, 
            2.9000E-03, 2.4000E-03, 1.3000E-03, 3.0000E-04, 7.8000E-05, 
            9.4000E-06, 5.3000E-07} );

    subshell_half_profiles[2] = 
      std::vector<double>( {7.1600E-02, 7.1600E-02, 7.1600E-02, 7.1600E-02, 
            7.1600E-02, 7.1600E-02, 7.1600E-02, 7.1600E-02, 7.1600E-02, 
            7.1600E-02, 7.1600E-02, 7.1500E-02, 7.1400E-02, 7.1200E-02, 
            7.1000E-02, 7.0600E-02, 7.0200E-02, 6.8900E-02, 6.5900E-02, 
            5.8400E-02, 4.8800E-02, 3.8800E-02, 2.9700E-02, 2.2100E-02, 
            1.2000E-02, 2.3000E-03, 5.1000E-04, 4.2000E-05, 5.8000E-06, 
            3.0000E-07, 5.9000E-09} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.9800E-01, 3.9800E-01, 3.9500E-01, 3.9200E-01, 
            3.8700E-01, 3.7400E-01, 3.5600E-01, 3.3400E-01, 3.1000E-01, 
            2.8400E-01, 2.5600E-01, 2.0200E-01, 1.5200E-01, 1.1100E-01, 
            7.8200E-02, 5.4600E-02, 3.8500E-02, 2.2500E-02, 1.7700E-02, 
            1.6400E-02, 1.1100E-02, 5.9100E-03, 2.7400E-03, 1.2300E-03, 
            4.3000E-04, 3.5000E-04, 1.9000E-04, 4.2000E-05, 1.1000E-05, 
            1.3000E-06, 7.0000E-08} );

    subshell_half_profiles[4] = 
      std::vector<double>( {2.5300E-01, 2.5300E-01, 2.5300E-01, 2.5200E-01, 
            2.5200E-01, 2.5200E-01, 2.5100E-01, 2.4900E-01, 2.4600E-01, 
            2.4200E-01, 2.3600E-01, 2.2000E-01, 1.9800E-01, 1.7300E-01, 
            1.4700E-01, 1.2100E-01, 9.7400E-02, 5.9400E-02, 2.5500E-02, 
            6.7300E-03, 4.2700E-03, 4.2000E-03, 3.8100E-03, 3.1200E-03, 
            1.8000E-03, 3.3000E-04, 7.1000E-05, 5.5000E-06, 7.4000E-07, 
            3.7000E-08, 7.4000E-10} );

    subshell_half_profiles[5] = 
      std::vector<double>( {2.6100E-01, 2.6100E-01, 2.6100E-01, 2.6100E-01, 
            2.6100E-01, 2.6100E-01, 2.6000E-01, 2.5700E-01, 2.5100E-01, 
            2.4400E-01, 2.3400E-01, 2.0900E-01, 1.8300E-01, 1.5600E-01, 
            1.3300E-01, 1.1100E-01, 9.3300E-02, 6.5000E-02, 3.7600E-02, 
            1.5300E-02, 6.4600E-03, 2.8300E-03, 1.2900E-03, 6.1400E-04, 
            1.6000E-04, 9.6000E-06, 1.0000E-06, 3.2000E-08, 2.4000E-09, 
            5.3000E-11, 3.1000E-13} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.8500E+00, 1.7900E+00, 1.6200E+00, 1.3800E+00, 
            1.1100E+00, 6.1100E-01, 2.8200E-01, 1.1700E-01, 5.1200E-02, 
            3.1300E-02, 2.7500E-02, 2.6700E-02, 2.2200E-02, 1.6100E-02, 
            1.0800E-02, 6.8400E-03, 4.2100E-03, 1.6300E-03, 7.4000E-04, 
            6.7300E-04, 4.8200E-04, 2.6100E-04, 1.2100E-04, 5.3300E-05, 
            1.7000E-05, 1.3000E-05, 7.1000E-06, 1.6000E-06, 4.1000E-07, 
            4.8000E-08, 2.6000E-09} );
  }
};

//! The default Compton profile generator implementation for A=25
template<>
struct DefaultComptonProfileGeneratorImpl<25u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 7 );

    subshell_half_profiles[0] = 
      std::vector<double>( {3.5000E-02, 3.5000E-02, 3.5000E-02, 3.5000E-02, 
            3.5000E-02, 3.5000E-02, 3.5000E-02, 3.4900E-02, 3.4900E-02, 
            3.4900E-02, 3.4900E-02, 3.4800E-02, 3.4700E-02, 3.4600E-02, 
            3.4500E-02, 3.4400E-02, 3.4300E-02, 3.4000E-02, 3.3400E-02, 
            3.2200E-02, 3.0800E-02, 2.9200E-02, 2.7400E-02, 2.5500E-02, 
            2.2000E-02, 1.3000E-02, 7.4000E-03, 2.2000E-03, 7.1000E-04, 
            1.0000E-04, 6.6000E-06} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 
            1.3300E-01, 1.3200E-01, 1.3200E-01, 1.3100E-01, 1.3000E-01, 
            1.2900E-01, 1.2700E-01, 1.2400E-01, 1.2000E-01, 1.1600E-01, 
            1.1100E-01, 1.0600E-01, 1.0000E-01, 8.9100E-02, 7.1700E-02, 
            4.5700E-02, 2.6500E-02, 1.4400E-02, 7.7100E-03, 4.5300E-03, 
            2.9000E-03, 2.5000E-03, 1.4000E-03, 3.4000E-04, 9.3000E-05, 
            1.1000E-05, 6.5000E-07} );

    subshell_half_profiles[2] = 
      std::vector<double>( {6.8100E-02, 6.8100E-02, 6.8100E-02, 6.8100E-02, 
            6.8100E-02, 6.8100E-02, 6.8100E-02, 6.8100E-02, 6.8100E-02, 
            6.8100E-02, 6.8100E-02, 6.8100E-02, 6.8000E-02, 6.7800E-02, 
            6.7600E-02, 6.7400E-02, 6.7000E-02, 6.6000E-02, 6.3500E-02, 
            5.7200E-02, 4.8800E-02, 3.9700E-02, 3.1100E-02, 2.3600E-02, 
            1.3000E-02, 2.7000E-03, 6.3000E-04, 5.4000E-05, 7.6000E-06, 
            4.0000E-07, 8.0000E-09} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.7300E-01, 3.7200E-01, 3.7000E-01, 3.6700E-01, 
            3.6400E-01, 3.5200E-01, 3.3800E-01, 3.2000E-01, 2.9900E-01, 
            2.7600E-01, 2.5300E-01, 2.0500E-01, 1.5900E-01, 1.1900E-01, 
            8.7000E-02, 6.2300E-02, 4.4500E-02, 2.5000E-02, 1.7500E-02, 
            1.6600E-02, 1.2300E-02, 7.0700E-03, 3.5200E-03, 1.6400E-03, 
            4.9000E-04, 3.6000E-04, 2.1000E-04, 5.0000E-05, 1.3000E-05, 
            1.6000E-06, 8.9000E-08} );

    subshell_half_profiles[4] = 
      std::vector<double>( {2.3500E-01, 2.3500E-01, 2.3500E-01, 2.3500E-01, 
            2.3500E-01, 2.3500E-01, 2.3400E-01, 2.3300E-01, 2.3100E-01, 
            2.2800E-01, 2.2300E-01, 2.1100E-01, 1.9400E-01, 1.7300E-01, 
            1.5000E-01, 1.2700E-01, 1.0500E-01, 6.8000E-02, 3.1500E-02, 
            8.3700E-03, 4.3800E-03, 4.1700E-03, 3.9500E-03, 3.3800E-03, 
            2.0000E-03, 4.2000E-04, 9.3000E-05, 7.5000E-06, 1.0000E-06, 
            5.2000E-08, 1.0000E-09} );

    subshell_half_profiles[5] = 
      std::vector<double>( {2.1500E-01, 2.1500E-01, 2.1500E-01, 2.1500E-01, 
            2.1500E-01, 2.1500E-01, 2.1400E-01, 2.1400E-01, 2.1200E-01, 
            2.1000E-01, 2.0600E-01, 1.9500E-01, 1.8000E-01, 1.6200E-01, 
            1.4400E-01, 1.2600E-01, 1.0900E-01, 8.0100E-02, 4.9300E-02, 
            2.1600E-02, 9.5900E-03, 4.3800E-03, 2.0700E-03, 1.0100E-03, 
            2.7000E-04, 1.7000E-05, 1.9000E-06, 6.2000E-08, 4.6000E-09, 
            1.0000E-10, 8.2000E-13} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.5900E+00, 1.5500E+00, 1.4400E+00, 1.2700E+00, 
            1.0800E+00, 6.7700E-01, 3.6800E-01, 1.8000E-01, 8.5600E-02, 
            4.5800E-02, 3.2600E-02, 2.9600E-02, 2.7700E-02, 2.2500E-02, 
            1.6500E-02, 1.1200E-02, 7.3100E-03, 2.9200E-03, 1.0500E-03, 
            8.6300E-04, 6.8300E-04, 4.0500E-04, 2.0300E-04, 9.3000E-05, 
            2.5000E-05, 1.8000E-05, 1.0000E-05, 2.4000E-06, 6.5000E-07, 
            7.7000E-08, 4.3000E-09} );
  }
};

//! The default Compton profile generator implementation for A=26
template<>
struct DefaultComptonProfileGeneratorImpl<26u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 7 );

    subshell_half_profiles[0] = 
      std::vector<double>( {3.3600E-02, 3.3600E-02, 3.3600E-02, 3.3600E-02, 
            3.3600E-02, 3.3600E-02, 3.3600E-02, 3.3600E-02, 3.3500E-02, 
            3.3500E-02, 3.3500E-02, 3.3400E-02, 3.3400E-02, 3.3300E-02, 
            3.3200E-02, 3.3100E-02, 3.3000E-02, 3.2700E-02, 3.2200E-02, 
            3.1200E-02, 2.9900E-02, 2.8400E-02, 2.6800E-02, 2.5100E-02, 
            2.2000E-02, 1.4000E-02, 7.8000E-03, 2.4000E-03, 8.1000E-04, 
            1.2000E-04, 7.9000E-06} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.2700E-01, 1.2700E-01, 1.2700E-01, 1.2700E-01, 
            1.2700E-01, 1.2700E-01, 1.2600E-01, 1.2500E-01, 1.2400E-01, 
            1.2300E-01, 1.2200E-01, 1.1900E-01, 1.1600E-01, 1.1200E-01, 
            1.0800E-01, 1.0300E-01, 9.8300E-02, 8.8000E-02, 7.2100E-02, 
            4.7600E-02, 2.8700E-02, 1.6200E-02, 8.8800E-03, 5.1300E-03, 
            2.9000E-03, 2.5000E-03, 1.5000E-03, 3.9000E-04, 1.1000E-04, 
            1.4000E-05, 7.9000E-07} );

    subshell_half_profiles[2] = 
      std::vector<double>( {6.5000E-02, 6.5000E-02, 6.5000E-02, 6.5000E-02, 
            6.5000E-02, 6.5000E-02, 6.5000E-02, 6.5000E-02, 6.5000E-02, 
            6.5000E-02, 6.5000E-02, 6.4900E-02, 6.4900E-02, 6.4800E-02, 
            6.4600E-02, 6.4400E-02, 6.4100E-02, 6.3200E-02, 6.1200E-02, 
            5.5900E-02, 4.8500E-02, 4.0300E-02, 3.2200E-02, 2.5000E-02, 
            1.4000E-02, 3.2000E-03, 7.7000E-04, 6.9000E-05, 9.9000E-06, 
            5.3000E-07, 1.1000E-08} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.5500E-01, 3.5400E-01, 3.5300E-01, 3.5000E-01, 
            3.4700E-01, 3.3700E-01, 3.2400E-01, 3.0900E-01, 2.9000E-01, 
            2.7000E-01, 2.4900E-01, 2.0500E-01, 1.6300E-01, 1.2500E-01, 
            9.3500E-02, 6.8400E-02, 4.9600E-02, 2.7500E-02, 1.7300E-02, 
            1.6300E-02, 1.3000E-02, 8.0600E-03, 4.2900E-03, 2.0900E-03, 
            5.7000E-04, 3.7000E-04, 2.3000E-04, 5.9000E-05, 1.6000E-05, 
            2.0000E-06, 1.1000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {2.2300E-01, 2.2300E-01, 2.2300E-01, 2.2300E-01, 
            2.2300E-01, 2.2300E-01, 2.2200E-01, 2.2100E-01, 2.2000E-01, 
            2.1700E-01, 2.1400E-01, 2.0300E-01, 1.8900E-01, 1.7100E-01, 
            1.5100E-01, 1.3100E-01, 1.1000E-01, 7.4300E-02, 3.6700E-02, 
            1.0200E-02, 4.5400E-03, 4.0300E-03, 3.9400E-03, 3.5100E-03, 
            2.3000E-03, 5.1000E-04, 1.2000E-04, 9.9000E-06, 1.4000E-06, 
            7.1000E-08, 1.4000E-09} );

    subshell_half_profiles[5] = 
      std::vector<double>( {2.0100E-01, 2.0100E-01, 2.0100E-01, 2.0100E-01, 
            2.0100E-01, 2.0100E-01, 2.0100E-01, 2.0000E-01, 1.9900E-01, 
            1.9700E-01, 1.9500E-01, 1.8600E-01, 1.7400E-01, 1.5900E-01, 
            1.4300E-01, 1.2700E-01, 1.1200E-01, 8.4500E-02, 5.4100E-02, 
            2.5000E-02, 1.1700E-02, 5.5300E-03, 2.7000E-03, 1.3600E-03, 
            3.8000E-04, 2.5000E-05, 2.9000E-06, 9.6000E-08, 7.2000E-09, 
            1.6000E-10, 1.3000E-12} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.5500E+00, 1.5100E+00, 1.4100E+00, 1.2500E+00, 
            1.0700E+00, 6.9000E-01, 3.8700E-01, 1.9600E-01, 9.4600E-02, 
            4.9200E-02, 3.2400E-02, 2.7300E-02, 2.6400E-02, 2.2400E-02, 
            1.7100E-02, 1.2100E-02, 8.1500E-03, 3.4300E-03, 1.1300E-03, 
            8.0000E-04, 6.8600E-04, 4.4200E-04, 2.3700E-04, 1.1500E-04, 
            2.9000E-05, 1.7000E-05, 1.1000E-05, 2.7000E-06, 7.5000E-07, 
            9.1000E-08, 5.1000E-09} );
  }
};

//! The default Compton profile generator implementation for A=27
template<>
struct DefaultComptonProfileGeneratorImpl<27u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 7 );

    subshell_half_profiles[0] = 
      std::vector<double>( {3.2300E-02, 3.2300E-02, 3.2300E-02, 3.2300E-02, 
            3.2300E-02, 3.2300E-02, 3.2300E-02, 3.2300E-02, 3.2300E-02, 
            3.2300E-02, 3.2200E-02, 3.2200E-02, 3.2100E-02, 3.2100E-02, 
            3.2000E-02, 3.1900E-02, 3.1800E-02, 3.1500E-02, 3.1100E-02, 
            3.0100E-02, 2.9000E-02, 2.7700E-02, 2.6200E-02, 2.4700E-02, 
            2.1000E-02, 1.4000E-02, 8.2000E-03, 2.7000E-03, 9.1000E-04, 
            1.4000E-04, 9.4000E-06} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.2200E-01, 1.2200E-01, 1.2200E-01, 1.2200E-01, 
            1.2200E-01, 1.2100E-01, 1.2100E-01, 1.2000E-01, 1.1900E-01, 
            1.1800E-01, 1.1700E-01, 1.1500E-01, 1.1200E-01, 1.0800E-01, 
            1.0500E-01, 1.0100E-01, 9.6100E-02, 8.6800E-02, 7.2200E-02, 
            4.9200E-02, 3.0800E-02, 1.8000E-02, 1.0100E-02, 5.8500E-03, 
            2.9000E-03, 2.5000E-03, 1.6000E-03, 4.5000E-04, 1.3000E-04, 
            1.7000E-05, 9.6000E-07} );

    subshell_half_profiles[2] = 
      std::vector<double>( {6.2100E-02, 6.2100E-02, 6.2100E-02, 6.2100E-02, 
            6.2100E-02, 6.2100E-02, 6.2100E-02, 6.2100E-02, 6.2100E-02, 
            6.2100E-02, 6.2100E-02, 6.2100E-02, 6.2000E-02, 6.1900E-02, 
            6.1800E-02, 6.1600E-02, 6.1400E-02, 6.0700E-02, 5.9000E-02, 
            5.4500E-02, 4.8100E-02, 4.0600E-02, 3.3100E-02, 2.6200E-02, 
            1.6000E-02, 3.7000E-03, 9.4000E-04, 8.7000E-05, 1.3000E-05, 
            6.9000E-07, 1.4000E-08} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.3900E-01, 3.3900E-01, 3.3700E-01, 3.3500E-01, 
            3.3200E-01, 3.2400E-01, 3.1200E-01, 2.9800E-01, 2.8200E-01, 
            2.6400E-01, 2.4500E-01, 2.0500E-01, 1.6600E-01, 1.3000E-01, 
            9.9200E-02, 7.4100E-02, 5.4600E-02, 3.0300E-02, 1.7500E-02, 
            1.5800E-02, 1.3400E-02, 8.9500E-03, 5.0700E-03, 2.6000E-03, 
            6.9000E-04, 3.7000E-04, 2.5000E-04, 6.8000E-05, 1.9000E-05, 
            2.4000E-06, 1.3000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {2.1200E-01, 2.1200E-01, 2.1200E-01, 2.1200E-01, 
            2.1200E-01, 2.1200E-01, 2.1200E-01, 2.1100E-01, 2.0900E-01, 
            2.0700E-01, 2.0500E-01, 1.9600E-01, 1.8400E-01, 1.6900E-01, 
            1.5100E-01, 1.3300E-01, 1.1400E-01, 7.9700E-02, 4.1700E-02, 
            1.2300E-02, 4.8900E-03, 3.9100E-03, 3.8700E-03, 3.5800E-03, 
            2.5000E-03, 6.1000E-04, 1.5000E-04, 1.3000E-05, 1.8000E-06, 
            9.4000E-08, 1.9000E-09} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.9000E-01, 1.9000E-01, 1.9000E-01, 1.9000E-01, 
            1.9000E-01, 1.8900E-01, 1.8900E-01, 1.8900E-01, 1.8800E-01, 
            1.8700E-01, 1.8500E-01, 1.7800E-01, 1.6800E-01, 1.5500E-01, 
            1.4100E-01, 1.2700E-01, 1.1300E-01, 8.7900E-02, 5.8200E-02, 
            2.8300E-02, 1.3800E-02, 6.7800E-03, 3.4100E-03, 1.7600E-03, 
            5.1000E-04, 3.6000E-05, 4.2000E-06, 1.4000E-07, 1.1000E-08, 
            2.5000E-10, 1.7000E-12} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.5100E+00, 1.4800E+00, 1.3800E+00, 1.2400E+00, 
            1.0600E+00, 7.0000E-01, 4.0400E-01, 2.1100E-01, 1.0400E-01, 
            5.3300E-02, 3.3000E-02, 2.5400E-02, 2.4900E-02, 2.2000E-02, 
            1.7400E-02, 1.2800E-02, 8.9000E-03, 3.9600E-03, 1.2500E-03, 
            7.4000E-04, 6.7500E-04, 4.6900E-04, 2.6900E-04, 1.3800E-04, 
            3.5000E-05, 1.6000E-05, 1.1000E-05, 3.1000E-06, 8.5000E-07, 
            1.1000E-07, 6.0000E-09} );
  }
};

//! The default Compton profile generator implementation for A=28
template<>
struct DefaultComptonProfileGeneratorImpl<28u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 7 );

    subshell_half_profiles[0] = 
      std::vector<double>( {3.1100E-02, 3.1100E-02, 3.1100E-02, 3.1100E-02, 
            3.1100E-02, 3.1100E-02, 3.1100E-02, 3.1100E-02, 3.1100E-02, 
            3.1100E-02, 3.1100E-02, 3.1000E-02, 3.1000E-02, 3.0900E-02, 
            3.0800E-02, 3.0700E-02, 3.0600E-02, 3.0400E-02, 3.0000E-02, 
            2.9200E-02, 2.8200E-02, 2.7000E-02, 2.5600E-02, 2.4200E-02, 
            2.1000E-02, 1.4000E-02, 8.5000E-03, 2.9000E-03, 1.0000E-03, 
            1.6000E-04, 1.1000E-05} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.1700E-01, 1.1700E-01, 1.1700E-01, 1.1700E-01, 
            1.1700E-01, 1.1600E-01, 1.1600E-01, 1.1500E-01, 1.1500E-01, 
            1.1400E-01, 1.1300E-01, 1.1100E-01, 1.0800E-01, 1.0500E-01, 
            1.0200E-01, 9.7900E-02, 9.3900E-02, 8.5500E-02, 7.2100E-02, 
            5.0500E-02, 3.2600E-02, 1.9700E-02, 1.1400E-02, 6.6500E-03, 
            3.1000E-03, 2.5000E-03, 1.7000E-03, 5.0000E-04, 1.5000E-04, 
            2.0000E-05, 1.2000E-06} );

    subshell_half_profiles[2] = 
      std::vector<double>( {5.9500E-02, 5.9500E-02, 5.9500E-02, 5.9500E-02, 
            5.9500E-02, 5.9500E-02, 5.9500E-02, 5.9500E-02, 5.9500E-02, 
            5.9500E-02, 5.9500E-02, 5.9500E-02, 5.9400E-02, 5.9300E-02, 
            5.9200E-02, 5.9100E-02, 5.8900E-02, 5.8300E-02, 5.6900E-02, 
            5.3100E-02, 4.7500E-02, 4.0800E-02, 3.3800E-02, 2.7300E-02, 
            1.7000E-02, 4.3000E-03, 1.1000E-03, 1.1000E-04, 1.6000E-05, 
            8.9000E-07, 1.8000E-08} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.2500E-01, 3.2400E-01, 3.2300E-01, 3.2100E-01, 
            3.1800E-01, 3.1100E-01, 3.0100E-01, 2.8800E-01, 2.7400E-01, 
            2.5800E-01, 2.4100E-01, 2.0400E-01, 1.6800E-01, 1.3400E-01, 
            1.0400E-01, 7.9300E-02, 5.9500E-02, 3.3400E-02, 1.8000E-02, 
            1.5200E-02, 1.3700E-02, 9.7200E-03, 5.8400E-03, 3.1600E-03, 
            8.5000E-04, 3.6000E-04, 2.7000E-04, 7.7000E-05, 2.2000E-05, 
            2.8000E-06, 1.6000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {2.0200E-01, 2.0200E-01, 2.0200E-01, 2.0200E-01, 
            2.0200E-01, 2.0200E-01, 2.0200E-01, 2.0100E-01, 2.0000E-01, 
            1.9900E-01, 1.9600E-01, 1.8900E-01, 1.7900E-01, 1.6600E-01, 
            1.5100E-01, 1.3400E-01, 1.1700E-01, 8.4400E-02, 4.6600E-02, 
            1.4700E-02, 5.4400E-03, 3.8400E-03, 3.7600E-03, 3.6000E-03, 
            2.6000E-03, 7.1000E-04, 1.8000E-04, 1.6000E-05, 2.3000E-06, 
            1.2000E-07, 2.5000E-09} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.7900E-01, 1.7900E-01, 1.7900E-01, 1.7900E-01, 
            1.7900E-01, 1.7900E-01, 1.7900E-01, 1.7900E-01, 1.7800E-01, 
            1.7700E-01, 1.7600E-01, 1.7000E-01, 1.6200E-01, 1.5100E-01, 
            1.3900E-01, 1.2700E-01, 1.1400E-01, 9.0400E-02, 6.1700E-02, 
            3.1400E-02, 1.5900E-02, 8.0900E-03, 4.1900E-03, 2.2200E-03, 
            6.7000E-04, 4.9000E-05, 5.9000E-06, 2.1000E-07, 1.6000E-08, 
            3.6000E-10, 2.4000E-12} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.4700E+00, 1.4400E+00, 1.3500E+00, 1.2200E+00, 
            1.0500E+00, 7.0900E-01, 4.2000E-01, 2.2500E-01, 1.1300E-01, 
            5.8000E-02, 3.4200E-02, 2.3800E-02, 2.3400E-02, 2.1300E-02, 
            1.7500E-02, 1.3300E-02, 9.5400E-03, 4.4800E-03, 1.4200E-03, 
            6.8800E-04, 6.5200E-04, 4.8700E-04, 2.9800E-04, 1.6200E-04, 
            4.2000E-05, 1.6000E-05, 1.2000E-05, 3.4000E-06, 9.6000E-07, 
            1.2000E-07, 7.1000E-09} );
  }
};

//! The default Compton profile generator implementation for A=29
template<>
struct DefaultComptonProfileGeneratorImpl<29u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 7 );

    subshell_half_profiles[0] = 
      std::vector<double>( {3.0100E-02, 3.0100E-02, 3.0000E-02, 3.0000E-02, 
            3.0000E-02, 3.0000E-02, 3.0000E-02, 3.0000E-02, 3.0000E-02, 
            3.0000E-02, 3.0000E-02, 2.9900E-02, 2.9900E-02, 2.9800E-02, 
            2.9800E-02, 2.9700E-02, 2.9600E-02, 2.9400E-02, 2.9000E-02, 
            2.8300E-02, 2.7300E-02, 2.6300E-02, 2.5100E-02, 2.3800E-02, 
            2.1000E-02, 1.4000E-02, 8.9000E-03, 3.2000E-03, 1.1000E-03, 
            1.9000E-04, 1.3000E-05} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.1200E-01, 1.1200E-01, 1.1200E-01, 1.1200E-01, 
            1.1200E-01, 1.1200E-01, 1.1100E-01, 1.1100E-01, 1.1000E-01, 
            1.1000E-01, 1.0900E-01, 1.0700E-01, 1.0400E-01, 1.0200E-01, 
            9.8600E-02, 9.5300E-02, 9.1700E-02, 8.4100E-02, 7.1800E-02, 
            5.1600E-02, 3.4300E-02, 2.1400E-02, 1.2800E-02, 7.5300E-03, 
            3.3000E-03, 2.4000E-03, 1.8000E-03, 5.6000E-04, 1.7000E-04, 
            2.3000E-05, 1.4000E-06} );

    subshell_half_profiles[2] = 
      std::vector<double>( {5.7100E-02, 5.7100E-02, 5.7100E-02, 5.7100E-02, 
            5.7100E-02, 5.7100E-02, 5.7100E-02, 5.7100E-02, 5.7100E-02, 
            5.7100E-02, 5.7100E-02, 5.7100E-02, 5.7000E-02, 5.7000E-02, 
            5.6900E-02, 5.6800E-02, 5.6600E-02, 5.6100E-02, 5.5000E-02, 
            5.1700E-02, 4.6700E-02, 4.0700E-02, 3.4300E-02, 2.8200E-02, 
            1.8000E-02, 4.8000E-03, 1.3000E-03, 1.3000E-04, 2.0000E-05, 
            1.1000E-06, 2.4000E-08} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.1500E-01, 3.1500E-01, 3.1400E-01, 3.1200E-01, 
            3.0900E-01, 3.0200E-01, 2.9300E-01, 2.8200E-01, 2.6800E-01, 
            2.5300E-01, 2.3700E-01, 2.0300E-01, 1.6900E-01, 1.3700E-01, 
            1.0800E-01, 8.3100E-02, 6.3100E-02, 3.6000E-02, 1.8500E-02, 
            1.4500E-02, 1.3600E-02, 1.0200E-02, 6.5000E-03, 3.6900E-03, 
            1.0000E-03, 3.5000E-04, 2.8000E-04, 8.6000E-05, 2.5000E-05, 
            3.3000E-06, 1.9000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.9600E-01, 1.9600E-01, 1.9600E-01, 1.9600E-01, 
            1.9600E-01, 1.9600E-01, 1.9500E-01, 1.9500E-01, 1.9400E-01, 
            1.9300E-01, 1.9000E-01, 1.8400E-01, 1.7500E-01, 1.6300E-01, 
            1.4900E-01, 1.3400E-01, 1.1800E-01, 8.7200E-02, 5.0200E-02, 
            1.6900E-02, 6.0700E-03, 3.7800E-03, 3.5900E-03, 3.5200E-03, 
            2.7000E-03, 8.1000E-04, 2.1000E-04, 2.0000E-05, 3.0000E-06, 
            1.6000E-07, 3.3000E-09} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.8500E-01, 1.8500E-01, 1.8500E-01, 1.8500E-01, 
            1.8500E-01, 1.8500E-01, 1.8500E-01, 1.8400E-01, 1.8300E-01, 
            1.8100E-01, 1.7900E-01, 1.7100E-01, 1.6100E-01, 1.4800E-01, 
            1.3500E-01, 1.2200E-01, 1.1000E-01, 8.6900E-02, 5.9900E-02, 
            3.1400E-02, 1.6400E-02, 8.6200E-03, 4.5900E-03, 2.4900E-03, 
            7.8000E-04, 6.1000E-05, 7.5000E-06, 2.8000E-07, 2.2000E-08, 
            5.1000E-10, 3.5000E-12} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.6400E+00, 1.6000E+00, 1.4800E+00, 1.3100E+00, 
            1.1000E+00, 6.8600E-01, 3.7000E-01, 1.7900E-01, 8.1900E-02, 
            3.9200E-02, 2.3400E-02, 1.8000E-02, 1.7700E-02, 1.5600E-02, 
            1.2500E-02, 9.3600E-03, 6.7500E-03, 3.2500E-03, 1.0600E-03, 
            4.6100E-04, 4.4300E-04, 3.5100E-04, 2.2900E-04, 1.3100E-04, 
            3.6000E-05, 1.1000E-05, 8.4000E-06, 2.6000E-06, 7.7000E-07, 
            1.0000E-07, 5.9000E-09} );
  }
};

//! The default Compton profile generator implementation for A=30
template<>
struct DefaultComptonProfileGeneratorImpl<30u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 7 );

    subshell_half_profiles[0] = 
      std::vector<double>( {2.9000E-02, 2.9000E-02, 2.9000E-02, 2.9000E-02, 
            2.9000E-02, 2.9000E-02, 2.9000E-02, 2.9000E-02, 2.9000E-02, 
            2.9000E-02, 2.9000E-02, 2.8900E-02, 2.8900E-02, 2.8800E-02, 
            2.8800E-02, 2.8700E-02, 2.8600E-02, 2.8400E-02, 2.8100E-02, 
            2.7400E-02, 2.6600E-02, 2.5600E-02, 2.4500E-02, 2.3300E-02, 
            2.1000E-02, 1.4000E-02, 9.2000E-03, 3.4000E-03, 1.3000E-03, 
            2.2000E-04, 1.5000E-05} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 
            1.0800E-01, 1.0800E-01, 1.0700E-01, 1.0700E-01, 1.0600E-01, 
            1.0600E-01, 1.0500E-01, 1.0300E-01, 1.0100E-01, 9.8500E-02, 
            9.5800E-02, 9.2800E-02, 8.9600E-02, 8.2600E-02, 7.1300E-02, 
            5.2400E-02, 3.5800E-02, 2.3000E-02, 1.4100E-02, 8.4700E-03, 
            3.5000E-03, 2.4000E-03, 1.9000E-03, 6.2000E-04, 1.9000E-04, 
            2.7000E-05, 1.6000E-06} );

    subshell_half_profiles[2] = 
      std::vector<double>( {5.4900E-02, 5.4900E-02, 5.4900E-02, 5.4900E-02, 
            5.4900E-02, 5.4900E-02, 5.4900E-02, 5.4900E-02, 5.4900E-02, 
            5.4900E-02, 5.4900E-02, 5.4900E-02, 5.4800E-02, 5.4800E-02, 
            5.4700E-02, 5.4600E-02, 5.4500E-02, 5.4100E-02, 5.3100E-02, 
            5.0300E-02, 4.6000E-02, 4.0600E-02, 3.4700E-02, 2.8900E-02, 
            1.9000E-02, 5.4000E-03, 1.5000E-03, 1.6000E-04, 2.5000E-05, 
            1.4000E-06, 3.0000E-08} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.9900E-01, 2.9900E-01, 2.9800E-01, 2.9700E-01, 
            2.9400E-01, 2.8900E-01, 2.8100E-01, 2.7100E-01, 2.5900E-01, 
            2.4600E-01, 2.3200E-01, 2.0100E-01, 1.7000E-01, 1.4000E-01, 
            1.1300E-01, 8.8500E-02, 6.8500E-02, 4.0000E-02, 2.0000E-02, 
            1.4200E-02, 1.3600E-02, 1.0900E-02, 7.2700E-03, 4.3400E-03, 
            1.3000E-03, 3.5000E-04, 2.9000E-04, 9.7000E-05, 3.0000E-05, 
            4.0000E-06, 2.3000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.8600E-01, 1.8600E-01, 1.8600E-01, 1.8600E-01, 
            1.8600E-01, 1.8500E-01, 1.8500E-01, 1.8500E-01, 1.8400E-01, 
            1.8300E-01, 1.8100E-01, 1.7600E-01, 1.6900E-01, 1.5900E-01, 
            1.4700E-01, 1.3400E-01, 1.2000E-01, 9.1500E-02, 5.5300E-02, 
            1.9900E-02, 7.1400E-03, 3.9400E-03, 3.5300E-03, 3.5000E-03, 
            2.9000E-03, 9.3000E-04, 2.6000E-04, 2.5000E-05, 3.8000E-06, 
            2.1000E-07, 4.3000E-09} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.6200E-01, 1.6200E-01, 1.6200E-01, 1.6200E-01, 
            1.6200E-01, 1.6200E-01, 1.6200E-01, 1.6200E-01, 1.6200E-01, 
            1.6100E-01, 1.6000E-01, 1.5700E-01, 1.5100E-01, 1.4300E-01, 
            1.3400E-01, 1.2400E-01, 1.1400E-01, 9.3300E-02, 6.7100E-02, 
            3.7000E-02, 2.0100E-02, 1.0900E-02, 5.9400E-03, 3.3000E-03, 
            1.1000E-03, 8.9000E-05, 1.1000E-05, 4.3000E-07, 3.4000E-08, 
            8.1000E-10, 6.2000E-12} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.4100E+00, 1.3800E+00, 1.3000E+00, 1.1800E+00, 
            1.0400E+00, 7.2100E-01, 4.4600E-01, 2.5100E-01, 1.3200E-01, 
            6.8700E-02, 3.8300E-02, 2.1600E-02, 2.0600E-02, 1.9800E-02, 
            1.7200E-02, 1.3800E-02, 1.0500E-02, 5.4500E-03, 1.8300E-03, 
            6.2400E-04, 5.8800E-04, 4.9700E-04, 3.4300E-04, 2.0700E-04, 
            6.1000E-05, 1.4000E-05, 1.2000E-05, 3.9000E-06, 1.2000E-06, 
            1.6000E-07, 9.4000E-09} );
  }
};

//! The default Compton profile generator implementation for A=31
template<>
struct DefaultComptonProfileGeneratorImpl<31u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 8 );

    subshell_half_profiles[0] = 
      std::vector<double>( {2.8100E-02, 2.8100E-02, 2.8100E-02, 2.8100E-02, 
            2.8100E-02, 2.8100E-02, 2.8100E-02, 2.8000E-02, 2.8000E-02, 
            2.8000E-02, 2.8000E-02, 2.8000E-02, 2.7900E-02, 2.7900E-02, 
            2.7800E-02, 2.7800E-02, 2.7700E-02, 2.7500E-02, 2.7200E-02, 
            2.6600E-02, 2.5900E-02, 2.5000E-02, 2.3900E-02, 2.2800E-02, 
            2.0000E-02, 1.4000E-02, 9.4000E-03, 3.6000E-03, 1.4000E-03, 
            2.4000E-04, 1.8000E-05} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 
            1.0400E-01, 1.0400E-01, 1.0300E-01, 1.0300E-01, 1.0300E-01, 
            1.0200E-01, 1.0100E-01, 9.9700E-02, 9.7800E-02, 9.5600E-02, 
            9.3100E-02, 9.0400E-02, 8.7500E-02, 8.1100E-02, 7.0700E-02, 
            5.3000E-02, 3.7100E-02, 2.4500E-02, 1.5400E-02, 9.4500E-03, 
            3.9000E-03, 2.3000E-03, 1.9000E-03, 6.8000E-04, 2.2000E-04, 
            3.1000E-05, 1.9000E-06} );

    subshell_half_profiles[2] = 
      std::vector<double>( {5.2800E-02, 5.2800E-02, 5.2800E-02, 5.2800E-02, 
            5.2800E-02, 5.2800E-02, 5.2800E-02, 5.2800E-02, 5.2800E-02, 
            5.2800E-02, 5.2800E-02, 5.2800E-02, 5.2800E-02, 5.2700E-02, 
            5.2700E-02, 5.2600E-02, 5.2500E-02, 5.2100E-02, 5.1300E-02, 
            4.8900E-02, 4.5100E-02, 4.0300E-02, 3.4900E-02, 2.9500E-02, 
            2.0000E-02, 6.0000E-03, 1.8000E-03, 1.9000E-04, 3.1000E-05, 
            1.8000E-06, 3.9000E-08} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.8500E-01, 2.8400E-01, 2.8400E-01, 2.8200E-01, 
            2.8100E-01, 2.7500E-01, 2.6900E-01, 2.6000E-01, 2.5000E-01, 
            2.3800E-01, 2.2600E-01, 1.9900E-01, 1.7000E-01, 1.4300E-01, 
            1.1700E-01, 9.3400E-02, 7.3600E-02, 4.4300E-02, 2.1900E-02, 
            1.3900E-02, 1.3600E-02, 1.1400E-02, 8.0200E-03, 5.0100E-03, 
            1.6000E-03, 3.5000E-04, 3.0000E-04, 1.1000E-04, 3.4000E-05, 
            4.7000E-06, 2.8000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.7600E-01, 1.7600E-01, 1.7600E-01, 1.7600E-01, 
            1.7600E-01, 1.7600E-01, 1.7500E-01, 1.7500E-01, 1.7500E-01, 
            1.7400E-01, 1.7300E-01, 1.6900E-01, 1.6300E-01, 1.5500E-01, 
            1.4500E-01, 1.3300E-01, 1.2100E-01, 9.5200E-02, 6.0200E-02, 
            2.3300E-02, 8.5000E-03, 4.2400E-03, 3.5100E-03, 3.4800E-03, 
            3.0000E-03, 1.1000E-03, 3.1000E-04, 3.2000E-05, 4.8000E-06, 
            2.7000E-07, 5.6000E-09} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.4600E-01, 1.4600E-01, 1.4600E-01, 1.4600E-01, 
            1.4600E-01, 1.4600E-01, 1.4600E-01, 1.4600E-01, 1.4500E-01, 
            1.4500E-01, 1.4500E-01, 1.4300E-01, 1.4000E-01, 1.3500E-01, 
            1.2900E-01, 1.2200E-01, 1.1400E-01, 9.7100E-02, 7.2900E-02, 
            4.2400E-02, 2.3800E-02, 1.3300E-02, 7.4700E-03, 4.2400E-03, 
            1.4000E-03, 1.2000E-04, 1.6000E-05, 6.4000E-07, 5.2000E-08, 
            1.3000E-09, 1.0000E-11} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.1800E+00, 1.1600E+00, 1.1100E+00, 1.0400E+00, 
            9.4400E-01, 7.2300E-01, 5.0600E-01, 3.2700E-01, 1.9800E-01, 
            1.1600E-01, 6.7300E-02, 3.0200E-02, 2.4400E-02, 2.4100E-02, 
            2.2700E-02, 1.9600E-02, 1.5800E-02, 8.9900E-03, 3.2200E-03, 
            8.9100E-04, 7.8400E-04, 7.0100E-04, 5.1200E-04, 3.2500E-04, 
            1.0000E-04, 1.9000E-05, 1.7000E-05, 6.0000E-06, 1.9000E-06, 
            2.6000E-07, 1.5000E-08} );

    subshell_half_profiles[7] = 
      std::vector<double>( {9.1500E-01, 9.1400E-01, 9.1200E-01, 9.0100E-01, 
            8.7600E-01, 7.7300E-01, 6.1800E-01, 4.5200E-01, 3.0900E-01, 
            2.0100E-01, 1.2600E-01, 4.6400E-02, 1.6800E-02, 7.1200E-03, 
            4.4700E-03, 3.9800E-03, 3.9500E-03, 3.6700E-03, 2.5500E-03, 
            9.8100E-04, 3.2600E-04, 1.3100E-04, 9.2100E-05, 8.9200E-05, 
            8.0000E-05, 2.9000E-05, 8.3000E-06, 8.5000E-07, 1.3000E-07, 
            7.1000E-09, 1.5000E-10} );
  }
};

//! The default Compton profile generator implementation for A=32
template<>
struct DefaultComptonProfileGeneratorImpl<32u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 8 );

    subshell_half_profiles[0] = 
      std::vector<double>( {2.7200E-02, 2.7200E-02, 2.7200E-02, 2.7200E-02, 
            2.7200E-02, 2.7200E-02, 2.7200E-02, 2.7200E-02, 2.7100E-02, 
            2.7100E-02, 2.7100E-02, 2.7100E-02, 2.7100E-02, 2.7000E-02, 
            2.7000E-02, 2.6900E-02, 2.6800E-02, 2.6700E-02, 2.6400E-02, 
            2.5900E-02, 2.5200E-02, 2.4300E-02, 2.3400E-02, 2.2400E-02, 
            2.0000E-02, 1.5000E-02, 9.7000E-03, 3.9000E-03, 1.5000E-03, 
            2.8000E-04, 2.0000E-05} );

    subshell_half_profiles[1] = 
      std::vector<double>( {1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0000E-01, 
            1.0000E-01, 1.0000E-01, 9.9900E-02, 9.9500E-02, 9.9100E-02, 
            9.8500E-02, 9.7900E-02, 9.6500E-02, 9.4800E-02, 9.2800E-02, 
            9.0500E-02, 8.8100E-02, 8.5400E-02, 7.9600E-02, 7.0000E-02, 
            5.3500E-02, 3.8300E-02, 2.5900E-02, 1.6700E-02, 1.0500E-02, 
            4.3000E-03, 2.3000E-03, 1.9000E-03, 7.4000E-04, 2.5000E-04, 
            3.6000E-05, 2.2000E-06} );

    subshell_half_profiles[2] = 
      std::vector<double>( {5.0900E-02, 5.0900E-02, 5.0900E-02, 5.0900E-02, 
            5.0900E-02, 5.0900E-02, 5.0900E-02, 5.0900E-02, 5.0900E-02, 
            5.0900E-02, 5.0900E-02, 5.0900E-02, 5.0900E-02, 5.0800E-02, 
            5.0800E-02, 5.0700E-02, 5.0600E-02, 5.0300E-02, 4.9600E-02, 
            4.7500E-02, 4.4200E-02, 3.9900E-02, 3.5000E-02, 2.9900E-02, 
            2.1000E-02, 6.6000E-03, 2.0000E-03, 2.3000E-04, 3.8000E-05, 
            2.2000E-06, 4.8000E-08} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.7100E-01, 2.7100E-01, 2.7000E-01, 2.6900E-01, 
            2.6700E-01, 2.6300E-01, 2.5700E-01, 2.5000E-01, 2.4100E-01, 
            2.3100E-01, 2.2000E-01, 1.9500E-01, 1.7000E-01, 1.4400E-01, 
            1.2000E-01, 9.7800E-02, 7.8400E-02, 4.8600E-02, 2.4100E-02, 
            1.3800E-02, 1.3500E-02, 1.1800E-02, 8.7300E-03, 5.7000E-03, 
            1.9000E-03, 3.5000E-04, 3.1000E-04, 1.2000E-04, 3.9000E-05, 
            5.6000E-06, 3.4000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.6700E-01, 1.6700E-01, 1.6700E-01, 1.6700E-01, 
            1.6700E-01, 1.6700E-01, 1.6600E-01, 1.6600E-01, 1.6600E-01, 
            1.6500E-01, 1.6400E-01, 1.6100E-01, 1.5600E-01, 1.5000E-01, 
            1.4200E-01, 1.3200E-01, 1.2100E-01, 9.8000E-02, 6.4800E-02, 
            2.7000E-02, 1.0100E-02, 4.7000E-03, 3.5300E-03, 3.4400E-03, 
            3.1000E-03, 1.2000E-03, 3.6000E-04, 3.9000E-05, 6.1000E-06, 
            3.4000E-07, 7.2000E-09} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 
            1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 
            1.3300E-01, 1.3200E-01, 1.3100E-01, 1.3000E-01, 1.2700E-01, 
            1.2300E-01, 1.1800E-01, 1.1200E-01, 9.8400E-02, 7.7100E-02, 
            4.7200E-02, 2.7600E-02, 1.5900E-02, 9.1300E-03, 5.2900E-03, 
            1.8000E-03, 1.7000E-04, 2.3000E-05, 9.3000E-07, 7.7000E-08, 
            1.9000E-09, 1.5000E-11} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.0300E+00, 1.0200E+00, 9.8500E-01, 9.3400E-01, 
            8.6600E-01, 7.0200E-01, 5.2700E-01, 3.7100E-01, 2.4600E-01, 
            1.5600E-01, 9.7100E-02, 4.1500E-02, 2.7700E-02, 2.6200E-02, 
            2.5800E-02, 2.3800E-02, 2.0400E-02, 1.2800E-02, 5.0100E-03, 
            1.2100E-03, 9.3800E-04, 8.8000E-04, 6.8000E-04, 4.5300E-04, 
            1.5000E-04, 2.3000E-05, 2.1000E-05, 8.1000E-06, 2.6000E-06, 
            3.7000E-07, 2.2000E-08} );

    subshell_half_profiles[7] = 
      std::vector<double>( {7.6900E-01, 7.6900E-01, 7.6800E-01, 7.6300E-01, 
            7.5100E-01, 6.9800E-01, 6.0500E-01, 4.8900E-01, 3.7100E-01, 
            2.6900E-01, 1.8700E-01, 8.3700E-02, 3.5100E-02, 1.5000E-02, 
            7.7500E-03, 5.6100E-03, 5.2000E-03, 5.0900E-03, 3.9500E-03, 
            1.7000E-03, 5.9500E-04, 2.2600E-04, 1.3700E-04, 1.2600E-04, 
            1.2000E-04, 4.8000E-05, 1.4000E-05, 1.5000E-06, 2.3000E-07, 
            1.3000E-08, 2.8000E-10} );
  }
};

//! The default Compton profile generator implementation for A=33
template<>
struct DefaultComptonProfileGeneratorImpl<33u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 8 );

    subshell_half_profiles[0] = 
      std::vector<double>( {2.6300E-02, 2.6300E-02, 2.6300E-02, 2.6300E-02, 
            2.6300E-02, 2.6300E-02, 2.6300E-02, 2.6300E-02, 2.6300E-02, 
            2.6300E-02, 2.6300E-02, 2.6300E-02, 2.6200E-02, 2.6200E-02, 
            2.6100E-02, 2.6100E-02, 2.6000E-02, 2.5900E-02, 2.5700E-02, 
            2.5100E-02, 2.4500E-02, 2.3700E-02, 2.2900E-02, 2.2000E-02, 
            2.0000E-02, 1.5000E-02, 9.9000E-03, 4.1000E-03, 1.6000E-03, 
            3.1000E-04, 2.3000E-05} );

    subshell_half_profiles[1] = 
      std::vector<double>( {9.7100E-02, 9.7100E-02, 9.7100E-02, 9.7000E-02, 
            9.7000E-02, 9.6800E-02, 9.6500E-02, 9.6200E-02, 9.5800E-02, 
            9.5300E-02, 9.4800E-02, 9.3500E-02, 9.1900E-02, 9.0100E-02, 
            8.8100E-02, 8.5800E-02, 8.3400E-02, 7.8100E-02, 6.9300E-02, 
            5.3800E-02, 3.9300E-02, 2.7200E-02, 1.7900E-02, 1.1500E-02, 
            4.7000E-03, 2.2000E-03, 2.0000E-03, 8.0000E-04, 2.7000E-04, 
            4.1000E-05, 2.6000E-06} );

    subshell_half_profiles[2] = 
      std::vector<double>( {4.9100E-02, 4.9100E-02, 4.9100E-02, 4.9100E-02, 
            4.9100E-02, 4.9100E-02, 4.9100E-02, 4.9100E-02, 4.9100E-02, 
            4.9100E-02, 4.9100E-02, 4.9100E-02, 4.9100E-02, 4.9100E-02, 
            4.9000E-02, 4.9000E-02, 4.8900E-02, 4.8700E-02, 4.8100E-02, 
            4.6300E-02, 4.3300E-02, 3.9500E-02, 3.5000E-02, 3.0200E-02, 
            2.1000E-02, 7.2000E-03, 2.3000E-03, 2.7000E-04, 4.6000E-05, 
            2.7000E-06, 6.0000E-08} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.5800E-01, 2.5800E-01, 2.5800E-01, 2.5700E-01, 
            2.5500E-01, 2.5200E-01, 2.4600E-01, 2.4000E-01, 2.3200E-01, 
            2.2300E-01, 2.1300E-01, 1.9200E-01, 1.6900E-01, 1.4500E-01, 
            1.2200E-01, 1.0100E-01, 8.2600E-02, 5.2800E-02, 2.6600E-02, 
            1.3900E-02, 1.3300E-02, 1.2100E-02, 9.3700E-03, 6.3900E-03, 
            2.3000E-03, 3.5000E-04, 3.2000E-04, 1.3000E-04, 4.5000E-05, 
            6.5000E-06, 4.0000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.5800E-01, 1.5800E-01, 1.5800E-01, 1.5800E-01, 
            1.5800E-01, 1.5800E-01, 1.5800E-01, 1.5800E-01, 1.5800E-01, 
            1.5700E-01, 1.5600E-01, 1.5400E-01, 1.5000E-01, 1.4500E-01, 
            1.3800E-01, 1.3000E-01, 1.2100E-01, 9.9900E-02, 6.8900E-02, 
            3.0700E-02, 1.2000E-02, 5.3200E-03, 3.6200E-03, 3.4100E-03, 
            3.2000E-03, 1.4000E-03, 4.3000E-04, 4.8000E-05, 7.6000E-06, 
            4.3000E-07, 9.3000E-09} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 
            1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 
            1.2200E-01, 1.2200E-01, 1.2200E-01, 1.2100E-01, 1.1900E-01, 
            1.1600E-01, 1.1300E-01, 1.0900E-01, 9.7900E-02, 7.9700E-02, 
            5.1400E-02, 3.1200E-02, 1.8500E-02, 1.0900E-02, 6.4600E-03, 
            2.3000E-03, 2.3000E-04, 3.2000E-05, 1.3000E-06, 1.1000E-07, 
            2.8000E-09, 2.1000E-11} );

    subshell_half_profiles[6] = 
      std::vector<double>( {9.2200E-01, 9.1400E-01, 8.9000E-01, 8.5200E-01, 
            8.0100E-01, 6.7300E-01, 5.3100E-01, 3.9600E-01, 2.8000E-01, 
            1.9000E-01, 1.2500E-01, 5.5200E-02, 3.2100E-02, 2.7500E-02, 
            2.7300E-02, 2.6400E-02, 2.3900E-02, 1.6500E-02, 7.1900E-03, 
            1.6500E-03, 1.0700E-03, 1.0300E-03, 8.4500E-04, 5.9000E-04, 
            2.2000E-04, 2.7000E-05, 2.5000E-05, 1.0000E-05, 3.5000E-06, 
            5.0000E-07, 3.1000E-08} );

    subshell_half_profiles[7] = 
      std::vector<double>( {6.7400E-01, 6.7400E-01, 6.7300E-01, 6.7000E-01, 
            6.6400E-01, 6.3200E-01, 5.7300E-01, 4.9100E-01, 3.9900E-01, 
            3.1000E-01, 2.3200E-01, 1.2000E-01, 5.6900E-02, 2.6300E-02, 
            1.2900E-02, 7.8900E-03, 6.3600E-03, 6.0700E-03, 5.2400E-03, 
            2.5500E-03, 9.5400E-04, 3.5400E-04, 1.8800E-04, 1.6000E-04, 
            1.5000E-04, 6.8000E-05, 2.1000E-05, 2.4000E-06, 3.7000E-07, 
            2.1000E-08, 4.6000E-10} );
  }
};

//! The default Compton profile generator implementation for A=34
template<>
struct DefaultComptonProfileGeneratorImpl<34u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 8 );

    subshell_half_profiles[0] = 
      std::vector<double>( {2.5500E-02, 2.5500E-02, 2.5500E-02, 2.5500E-02, 
            2.5500E-02, 2.5500E-02, 2.5500E-02, 2.5500E-02, 2.5500E-02, 
            2.5500E-02, 2.5500E-02, 2.5500E-02, 2.5400E-02, 2.5400E-02, 
            2.5400E-02, 2.5300E-02, 2.5300E-02, 2.5100E-02, 2.4900E-02, 
            2.4400E-02, 2.3900E-02, 2.3200E-02, 2.2400E-02, 2.1500E-02, 
            2.0000E-02, 1.5000E-02, 1.0000E-02, 4.3000E-03, 1.8000E-03, 
            3.4000E-04, 2.7000E-05} );

    subshell_half_profiles[1] = 
      std::vector<double>( {9.3900E-02, 9.3900E-02, 9.3900E-02, 9.3900E-02, 
            9.3800E-02, 9.3600E-02, 9.3400E-02, 9.3100E-02, 9.2700E-02, 
            9.2300E-02, 9.1800E-02, 9.0600E-02, 8.9200E-02, 8.7600E-02, 
            8.5700E-02, 8.3700E-02, 8.1500E-02, 7.6600E-02, 6.8400E-02, 
            5.4000E-02, 4.0100E-02, 2.8300E-02, 1.9100E-02, 1.2500E-02, 
            5.2000E-03, 2.2000E-03, 2.0000E-03, 8.6000E-04, 3.0000E-04, 
            4.7000E-05, 3.0000E-06} );

    subshell_half_profiles[2] = 
      std::vector<double>( {4.7500E-02, 4.7500E-02, 4.7500E-02, 4.7500E-02, 
            4.7500E-02, 4.7500E-02, 4.7500E-02, 4.7500E-02, 4.7500E-02, 
            4.7500E-02, 4.7500E-02, 4.7500E-02, 4.7500E-02, 4.7400E-02, 
            4.7400E-02, 4.7300E-02, 4.7300E-02, 4.7100E-02, 4.6600E-02, 
            4.5000E-02, 4.2400E-02, 3.9000E-02, 3.4900E-02, 3.0500E-02, 
            2.2000E-02, 7.9000E-03, 2.6000E-03, 3.2000E-04, 5.5000E-05, 
            3.3000E-06, 7.5000E-08} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.4700E-01, 2.4700E-01, 2.4600E-01, 2.4500E-01, 
            2.4400E-01, 2.4100E-01, 2.3600E-01, 2.3000E-01, 2.2300E-01, 
            2.1600E-01, 2.0700E-01, 1.8800E-01, 1.6700E-01, 1.4500E-01, 
            1.2400E-01, 1.0400E-01, 8.6400E-02, 5.6800E-02, 2.9300E-02, 
            1.4200E-02, 1.3000E-02, 1.2300E-02, 9.9400E-03, 7.0600E-03, 
            2.8000E-03, 3.6000E-04, 3.3000E-04, 1.5000E-04, 5.1000E-05, 
            7.6000E-06, 4.8000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.5100E-01, 1.5100E-01, 1.5100E-01, 1.5100E-01, 
            1.5100E-01, 1.5100E-01, 1.5100E-01, 1.5000E-01, 1.5000E-01, 
            1.5000E-01, 1.4900E-01, 1.4700E-01, 1.4400E-01, 1.4000E-01, 
            1.3400E-01, 1.2700E-01, 1.1900E-01, 1.0100E-01, 7.2300E-02, 
            3.4400E-02, 1.4200E-02, 6.1300E-03, 3.7900E-03, 3.3800E-03, 
            3.3000E-03, 1.5000E-03, 5.0000E-04, 5.8000E-05, 9.4000E-06, 
            5.5000E-07, 1.2000E-08} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.1400E-01, 1.1400E-01, 1.1400E-01, 1.1400E-01, 
            1.1400E-01, 1.1400E-01, 1.1400E-01, 1.1400E-01, 1.1400E-01, 
            1.1400E-01, 1.1400E-01, 1.1400E-01, 1.1300E-01, 1.1200E-01, 
            1.1000E-01, 1.0800E-01, 1.0400E-01, 9.6300E-02, 8.0900E-02, 
            5.4900E-02, 3.4700E-02, 2.1200E-02, 1.2800E-02, 7.7300E-03, 
            2.9000E-03, 3.0000E-04, 4.2000E-05, 1.8000E-06, 1.6000E-07, 
            4.0000E-09, 2.9000E-11} );

    subshell_half_profiles[6] = 
      std::vector<double>( {8.3900E-01, 8.3300E-01, 8.1400E-01, 7.8500E-01, 
            7.4500E-01, 6.4300E-01, 5.2600E-01, 4.0900E-01, 3.0400E-01, 
            2.1700E-01, 1.5000E-01, 7.0200E-02, 3.8100E-02, 2.9100E-02, 
            2.8000E-02, 2.7700E-02, 2.6200E-02, 1.9800E-02, 9.6400E-03, 
            2.2400E-03, 1.1900E-03, 1.1600E-03, 1.0000E-03, 7.3400E-04, 
            2.9000E-04, 3.2000E-05, 2.8000E-05, 1.3000E-05, 4.4000E-06, 
            6.5000E-07, 4.1000E-08} );

    subshell_half_profiles[7] = 
      std::vector<double>( {6.0400E-01, 6.0400E-01, 6.0300E-01, 6.0200E-01, 
            5.9800E-01, 5.7800E-01, 5.3800E-01, 4.7900E-01, 4.0800E-01, 
            3.3300E-01, 2.6300E-01, 1.5100E-01, 7.9700E-02, 4.0000E-02, 
            2.0200E-02, 1.1300E-02, 7.9100E-03, 6.7300E-03, 6.2800E-03, 
            3.4900E-03, 1.4100E-03, 5.2800E-04, 2.5200E-04, 1.9200E-04, 
            1.8000E-04, 9.0000E-05, 3.0000E-05, 3.5000E-06, 5.6000E-07, 
            3.2000E-08, 7.0000E-10} );
  }
};

//! The default Compton profile generator implementation for A=35
template<>
struct DefaultComptonProfileGeneratorImpl<35u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 8 );

    subshell_half_profiles[0] = 
      std::vector<double>( {2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 
            2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 
            2.4800E-02, 2.4800E-02, 2.4700E-02, 2.4700E-02, 2.4700E-02, 
            2.4600E-02, 2.4600E-02, 2.4500E-02, 2.4400E-02, 2.4200E-02, 
            2.3800E-02, 2.3300E-02, 2.2600E-02, 2.1900E-02, 2.1100E-02, 
            1.9000E-02, 1.5000E-02, 1.0000E-02, 4.5000E-03, 1.9000E-03, 
            3.8000E-04, 3.0000E-05} );

    subshell_half_profiles[1] = 
      std::vector<double>( {9.0900E-02, 9.0900E-02, 9.0900E-02, 9.0900E-02, 
            9.0800E-02, 9.0700E-02, 9.0400E-02, 9.0200E-02, 8.9800E-02, 
            8.9400E-02, 8.9000E-02, 8.7900E-02, 8.6600E-02, 8.5100E-02, 
            8.3400E-02, 8.1600E-02, 7.9600E-02, 7.5100E-02, 6.7500E-02, 
            5.4000E-02, 4.0900E-02, 2.9400E-02, 2.0300E-02, 1.3500E-02, 
            5.8000E-03, 2.1000E-03, 2.0000E-03, 9.2000E-04, 3.4000E-04, 
            5.3000E-05, 3.5000E-06} );

    subshell_half_profiles[2] = 
      std::vector<double>( {4.5900E-02, 4.5900E-02, 4.5900E-02, 4.5900E-02, 
            4.5900E-02, 4.5900E-02, 4.5900E-02, 4.5900E-02, 4.5900E-02, 
            4.5900E-02, 4.5900E-02, 4.5900E-02, 4.5900E-02, 4.5900E-02, 
            4.5900E-02, 4.5800E-02, 4.5800E-02, 4.5600E-02, 4.5100E-02, 
            4.3800E-02, 4.1500E-02, 3.8400E-02, 3.4700E-02, 3.0600E-02, 
            2.3000E-02, 8.5000E-03, 2.9000E-03, 3.7000E-04, 6.5000E-05, 
            4.0000E-06, 9.2000E-08} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.3600E-01, 2.3600E-01, 2.3600E-01, 2.3500E-01, 
            2.3400E-01, 2.3100E-01, 2.2700E-01, 2.2200E-01, 2.1600E-01, 
            2.0900E-01, 2.0100E-01, 1.8400E-01, 1.6500E-01, 1.4500E-01, 
            1.2500E-01, 1.0700E-01, 8.9500E-02, 6.0500E-02, 3.2100E-02, 
            1.4700E-02, 1.2800E-02, 1.2400E-02, 1.0400E-02, 7.6900E-03, 
            3.2000E-03, 3.9000E-04, 3.3000E-04, 1.6000E-04, 5.8000E-05, 
            8.8000E-06, 5.6000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.4400E-01, 1.4400E-01, 1.4400E-01, 1.4400E-01, 
            1.4400E-01, 1.4400E-01, 1.4400E-01, 1.4300E-01, 1.4300E-01, 
            1.4300E-01, 1.4200E-01, 1.4100E-01, 1.3800E-01, 1.3500E-01, 
            1.3000E-01, 1.2400E-01, 1.1700E-01, 1.0100E-01, 7.5100E-02, 
            3.8000E-02, 1.6500E-02, 7.1200E-03, 4.0500E-03, 3.3900E-03, 
            3.3000E-03, 1.7000E-03, 5.7000E-04, 7.0000E-05, 1.2000E-05, 
            6.8000E-07, 1.5000E-08} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0700E-01, 
            1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0700E-01, 
            1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0600E-01, 1.0500E-01, 
            1.0400E-01, 1.0200E-01, 1.0000E-01, 9.3800E-02, 8.1200E-02, 
            5.7700E-02, 3.7800E-02, 2.3800E-02, 1.4700E-02, 9.0900E-03, 
            3.5000E-03, 3.8000E-04, 5.6000E-05, 2.5000E-06, 2.2000E-07, 
            5.6000E-09, 3.8000E-11} );

    subshell_half_profiles[6] = 
      std::vector<double>( {7.7200E-01, 7.6700E-01, 7.5200E-01, 7.2900E-01, 
            6.9700E-01, 6.1400E-01, 5.1600E-01, 4.1500E-01, 3.2000E-01, 
            2.3800E-01, 1.7200E-01, 8.5500E-02, 4.5400E-02, 3.1400E-02, 
            2.8400E-02, 2.8200E-02, 2.7600E-02, 2.2600E-02, 1.2200E-02, 
            3.0300E-03, 1.3400E-03, 1.2600E-03, 1.1400E-03, 8.7800E-04, 
            3.8000E-04, 3.9000E-05, 3.1000E-05, 1.5000E-05, 5.5000E-06, 
            8.3000E-07, 6.3000E-08} );

    subshell_half_profiles[7] = 
      std::vector<double>( {5.4900E-01, 5.4900E-01, 5.4900E-01, 5.4800E-01, 
            5.4500E-01, 5.3200E-01, 5.0400E-01, 4.6100E-01, 4.0600E-01, 
            3.4500E-01, 2.8300E-01, 1.7700E-01, 1.0200E-01, 5.5100E-02, 
            2.9200E-02, 1.6100E-02, 1.0200E-02, 7.2800E-03, 7.0300E-03, 
            4.4400E-03, 1.9500E-03, 7.5600E-04, 3.3500E-04, 2.2700E-04, 
            2.1000E-04, 1.1000E-04, 3.9000E-05, 4.8000E-06, 7.8000E-07, 
            4.6000E-08, 1.0000E-09} );
  }
};

//! The default Compton profile generator implementation for A=36
template<>
struct DefaultComptonProfileGeneratorImpl<36u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 12 );

    subshell_half_profiles[0] = 
      std::vector<double>( {2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3400E-02, 
            2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3400E-02, 
            2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3300E-02, 2.3300E-02, 
            2.3300E-02, 2.3200E-02, 2.3200E-02, 2.3100E-02, 2.2900E-02, 
            2.2600E-02, 2.2100E-02, 2.1500E-02, 2.0900E-02, 2.0200E-02, 
            1.9000E-02, 1.4000E-02, 1.0000E-02, 4.9000E-03, 2.2000E-03, 
            4.9000E-04, 4.9000E-05} );

    subshell_half_profiles[1] = 
      std::vector<double>( {8.6200E-02, 8.6200E-02, 8.6200E-02, 8.6100E-02, 
            8.6100E-02, 8.5900E-02, 8.5800E-02, 8.5500E-02, 8.5200E-02, 
            8.4900E-02, 8.4500E-02, 8.3600E-02, 8.2500E-02, 8.1200E-02, 
            7.9800E-02, 7.8200E-02, 7.6400E-02, 7.2500E-02, 6.5900E-02, 
            5.3800E-02, 4.1800E-02, 3.1000E-02, 2.2000E-02, 1.5200E-02, 
            6.8000E-03, 2.0000E-03, 1.9000E-03, 1.0000E-03, 4.1000E-04, 
            7.5000E-05, 6.1000E-06} );

    subshell_half_profiles[2] = 
      std::vector<double>( {4.3300E-02, 4.3300E-02, 4.3300E-02, 4.3300E-02, 
            4.3300E-02, 4.3300E-02, 4.3300E-02, 4.3300E-02, 4.3300E-02, 
            4.3300E-02, 4.3300E-02, 4.3300E-02, 4.3300E-02, 4.3300E-02, 
            4.3300E-02, 4.3200E-02, 4.3200E-02, 4.3100E-02, 4.2700E-02, 
            4.1600E-02, 3.9800E-02, 3.7300E-02, 3.4100E-02, 3.0500E-02, 
            2.3000E-02, 9.5000E-03, 3.5000E-03, 5.2000E-04, 1.0000E-04, 
            7.8000E-06, 2.8000E-07} );

    subshell_half_profiles[3] = 
      std::vector<double>( {4.4300E-02, 4.4300E-02, 4.4300E-02, 4.4300E-02, 
            4.4300E-02, 4.4300E-02, 4.4300E-02, 4.4300E-02, 4.4300E-02, 
            4.4300E-02, 4.4300E-02, 4.4300E-02, 4.4300E-02, 4.4200E-02, 
            4.4200E-02, 4.4200E-02, 4.4100E-02, 4.4000E-02, 4.3600E-02, 
            4.2400E-02, 4.0500E-02, 3.7700E-02, 3.4400E-02, 3.0600E-02, 
            2.3000E-02, 9.1000E-03, 3.2000E-03, 4.5000E-04, 8.2000E-05, 
            5.6000E-06, 1.5000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {2.2200E-01, 2.2200E-01, 2.2200E-01, 2.2100E-01, 
            2.2000E-01, 2.1800E-01, 2.1400E-01, 2.1000E-01, 2.0500E-01, 
            1.9900E-01, 1.9200E-01, 1.7800E-01, 1.6100E-01, 1.4400E-01, 
            1.2600E-01, 1.0900E-01, 9.3400E-02, 6.5500E-02, 3.6300E-02, 
            1.5600E-02, 1.2300E-02, 1.2100E-02, 1.0800E-02, 8.5000E-03, 
            4.0000E-03, 4.5000E-04, 3.2000E-04, 1.9000E-04, 7.3000E-05, 
            1.3000E-05, 1.0000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.3400E-01, 1.3400E-01, 1.3400E-01, 1.3400E-01, 
            1.3400E-01, 1.3400E-01, 1.3400E-01, 1.3400E-01, 1.3400E-01, 
            1.3400E-01, 1.3400E-01, 1.3200E-01, 1.3100E-01, 1.2800E-01, 
            1.2400E-01, 1.2000E-01, 1.1400E-01, 1.0100E-01, 7.8100E-02, 
            4.2900E-02, 2.0100E-02, 8.9200E-03, 4.6200E-03, 3.3900E-03, 
            3.2000E-03, 1.9000E-03, 7.2000E-04, 1.0000E-04, 1.9000E-05, 
            1.4000E-06, 4.8000E-08} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.3700E-01, 1.3700E-01, 1.3700E-01, 1.3700E-01, 
            1.3700E-01, 1.3700E-01, 1.3700E-01, 1.3700E-01, 1.3700E-01, 
            1.3600E-01, 1.3600E-01, 1.3500E-01, 1.3300E-01, 1.3000E-01, 
            1.2600E-01, 1.2100E-01, 1.1500E-01, 1.0100E-01, 7.7400E-02, 
            4.1500E-02, 1.9000E-02, 8.3700E-03, 4.4500E-03, 3.4200E-03, 
            3.3000E-03, 1.8000E-03, 6.7000E-04, 8.8000E-05, 1.5000E-05, 
            9.9000E-07, 2.6000E-08} );

    subshell_half_profiles[7] = 
      std::vector<double>( {1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 
            1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 
            1.0100E-01, 1.0100E-01, 1.0000E-01, 1.0000E-01, 9.9600E-02, 
            9.8800E-02, 9.7500E-02, 9.5800E-02, 9.0900E-02, 8.0500E-02, 
            5.9700E-02, 4.0600E-02, 2.6400E-02, 1.6800E-02, 1.0600E-02, 
            4.2000E-03, 5.0000E-04, 7.7000E-05, 3.7000E-06, 3.5000E-07, 
            1.1000E-08, 1.3000E-10} );

    subshell_half_profiles[8] = 
      std::vector<double>( {1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 
            1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 
            1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0000E-01, 
            9.9400E-02, 9.8100E-02, 9.6300E-02, 9.1300E-02, 8.0700E-02, 
            5.9500E-02, 4.0300E-02, 2.6100E-02, 1.6500E-02, 1.0400E-02, 
            4.1000E-03, 4.8000E-04, 7.3000E-05, 3.4000E-06, 3.1000E-07, 
            8.6000E-09, 9.3000E-11} );

    subshell_half_profiles[9] = 
      std::vector<double>( {7.0500E-01, 7.0100E-01, 6.8900E-01, 6.7100E-01, 
            6.4600E-01, 5.8100E-01, 5.0100E-01, 4.1600E-01, 3.3300E-01, 
            2.5900E-01, 1.9500E-01, 1.0400E-01, 5.6100E-02, 3.5300E-02, 
            2.8800E-02, 2.7700E-02, 2.7600E-02, 2.4700E-02, 1.5400E-02, 
            4.3800E-03, 1.5600E-03, 1.3100E-03, 1.2500E-03, 1.0400E-03, 
            5.1000E-04, 5.0000E-05, 3.3000E-05, 1.9000E-05, 7.6000E-06, 
            1.3000E-06, 1.0000E-07} );

    subshell_half_profiles[10] = 
      std::vector<double>( {4.9600E-01, 4.9600E-01, 4.9600E-01, 4.9500E-01, 
            4.9400E-01, 4.8500E-01, 4.6700E-01, 4.3600E-01, 3.9600E-01, 
            3.4800E-01, 2.9800E-01, 2.0200E-01, 1.2600E-01, 7.4500E-02, 
            4.2300E-02, 2.3900E-02, 1.4300E-02, 7.9700E-03, 7.3100E-03, 
            5.4500E-03, 2.7300E-03, 1.1400E-03, 4.8300E-04, 2.7400E-04, 
            2.2000E-04, 1.4000E-04, 5.5000E-05, 7.6000E-06, 1.4000E-06, 
            1.0000E-07, 3.5000E-09} );

    subshell_half_profiles[11] = 
      std::vector<double>( {5.0800E-01, 5.0800E-01, 5.0800E-01, 5.0700E-01, 
            5.0500E-01, 4.9600E-01, 4.7500E-01, 4.4200E-01, 3.9800E-01, 
            3.4800E-01, 2.9500E-01, 1.9600E-01, 1.2100E-01, 6.9800E-02, 
            3.9000E-02, 2.1900E-02, 1.3200E-02, 7.8200E-03, 7.3400E-03, 
            5.2700E-03, 2.5400E-03, 1.0400E-03, 4.4200E-04, 2.6400E-04, 
            2.3000E-04, 1.4000E-04, 5.1000E-05, 6.6000E-06, 1.1000E-06, 
            7.3000E-08, 1.9000E-09} );
  }
};

//! The default Compton profile generator implementation for A=37
template<>
struct DefaultComptonProfileGeneratorImpl<37u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 13 );

    subshell_half_profiles[0] = 
      std::vector<double>( {2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 
            2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 
            2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2600E-02, 
            2.2600E-02, 2.2600E-02, 2.2500E-02, 2.2500E-02, 2.2300E-02, 
            2.2000E-02, 2.1500E-02, 2.1000E-02, 2.0400E-02, 1.9800E-02, 
            1.8000E-02, 1.4000E-02, 1.1000E-02, 5.1000E-03, 2.3000E-03, 
            5.4000E-04, 5.6000E-05} );

    subshell_half_profiles[1] = 
      std::vector<double>( {8.3500E-02, 8.3500E-02, 8.3500E-02, 8.3400E-02, 
            8.3400E-02, 8.3300E-02, 8.3100E-02, 8.2900E-02, 8.2600E-02, 
            8.2300E-02, 8.2000E-02, 8.1100E-02, 8.0100E-02, 7.9000E-02, 
            7.7600E-02, 7.6200E-02, 7.4500E-02, 7.1000E-02, 6.4900E-02, 
            5.3600E-02, 4.2200E-02, 3.1800E-02, 2.3100E-02, 1.6100E-02, 
            7.4000E-03, 2.0000E-03, 1.9000E-03, 1.1000E-03, 4.5000E-04, 
            8.4000E-05, 7.1000E-06} );

    subshell_half_profiles[2] = 
      std::vector<double>( {4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 
            4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 
            4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 
            4.1900E-02, 4.1900E-02, 4.1800E-02, 4.1700E-02, 4.1400E-02, 
            4.0500E-02, 3.8900E-02, 3.6600E-02, 3.3700E-02, 3.0500E-02, 
            2.4000E-02, 1.0000E-02, 3.9000E-03, 6.0000E-04, 1.2000E-04, 
            9.4000E-06, 3.4000E-07} );

    subshell_half_profiles[3] = 
      std::vector<double>( {4.2900E-02, 4.2900E-02, 4.2900E-02, 4.2900E-02, 
            4.2900E-02, 4.2900E-02, 4.2900E-02, 4.2900E-02, 4.2900E-02, 
            4.2900E-02, 4.2900E-02, 4.2900E-02, 4.2900E-02, 4.2900E-02, 
            4.2900E-02, 4.2800E-02, 4.2800E-02, 4.2700E-02, 4.2300E-02, 
            4.1300E-02, 3.9600E-02, 3.7100E-02, 3.4100E-02, 3.0600E-02, 
            2.3000E-02, 9.7000E-03, 3.6000E-03, 5.2000E-04, 9.7000E-05, 
            6.7000E-06, 1.8000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {2.1300E-01, 2.1300E-01, 2.1300E-01, 2.1200E-01, 
            2.1100E-01, 2.0900E-01, 2.0600E-01, 2.0200E-01, 1.9800E-01, 
            1.9200E-01, 1.8700E-01, 1.7300E-01, 1.5800E-01, 1.4300E-01, 
            1.2700E-01, 1.1100E-01, 9.5500E-02, 6.8600E-02, 3.9200E-02, 
            1.6700E-02, 1.2100E-02, 1.1900E-02, 1.1000E-02, 8.9900E-03, 
            4.5000E-03, 5.1000E-04, 3.2000E-04, 2.0000E-04, 8.1000E-05, 
            1.5000E-05, 1.2000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.2900E-01, 1.2900E-01, 1.2900E-01, 1.2900E-01, 
            1.2900E-01, 1.2900E-01, 1.2900E-01, 1.2800E-01, 1.2800E-01, 
            1.2800E-01, 1.2800E-01, 1.2700E-01, 1.2600E-01, 1.2300E-01, 
            1.2000E-01, 1.1600E-01, 1.1200E-01, 1.0000E-01, 7.9600E-02, 
            4.6000E-02, 2.2700E-02, 1.0400E-02, 5.2000E-03, 3.5200E-03, 
            3.2000E-03, 2.0000E-03, 8.1000E-04, 1.2000E-04, 2.3000E-05, 
            1.7000E-06, 6.0000E-08} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.3100E-01, 1.3100E-01, 1.3100E-01, 1.3100E-01, 
            1.3100E-01, 1.3100E-01, 1.3100E-01, 1.3100E-01, 1.3100E-01, 
            1.3000E-01, 1.3000E-01, 1.2900E-01, 1.2800E-01, 1.2500E-01, 
            1.2200E-01, 1.1800E-01, 1.1300E-01, 1.0100E-01, 7.9000E-02, 
            4.4700E-02, 2.1500E-02, 9.7100E-03, 4.9600E-03, 3.5200E-03, 
            3.3000E-03, 2.0000E-03, 7.6000E-04, 1.0000E-04, 1.9000E-05, 
            1.2000E-06, 3.2000E-08} );

    subshell_half_profiles[7] = 
      std::vector<double>( {9.5000E-02, 9.5000E-02, 9.5000E-02, 9.5000E-02, 
            9.5000E-02, 9.5000E-02, 9.5000E-02, 9.5000E-02, 9.5000E-02, 
            9.5000E-02, 9.5000E-02, 9.4900E-02, 9.4700E-02, 9.4400E-02, 
            9.3800E-02, 9.2900E-02, 9.1600E-02, 8.7900E-02, 7.9500E-02, 
            6.1100E-02, 4.3100E-02, 2.8800E-02, 1.8800E-02, 1.2100E-02, 
            5.0000E-03, 6.2000E-04, 9.8000E-05, 4.9000E-06, 4.7000E-07, 
            1.4000E-08, 1.8000E-10} );

    subshell_half_profiles[8] = 
      std::vector<double>( {9.5700E-02, 9.5700E-02, 9.5700E-02, 9.5700E-02, 
            9.5700E-02, 9.5700E-02, 9.5700E-02, 9.5700E-02, 9.5700E-02, 
            9.5700E-02, 9.5600E-02, 9.5600E-02, 9.5400E-02, 9.5000E-02, 
            9.4400E-02, 9.3400E-02, 9.2100E-02, 8.8300E-02, 7.9700E-02, 
            6.1000E-02, 4.2900E-02, 2.8600E-02, 1.8500E-02, 1.1900E-02, 
            4.9000E-03, 6.0000E-04, 9.3000E-05, 4.5000E-06, 4.2000E-07, 
            1.2000E-08, 1.3000E-10} );

    subshell_half_profiles[9] = 
      std::vector<double>( {6.3100E-01, 6.2900E-01, 6.2000E-01, 6.0700E-01, 
            5.8900E-01, 5.3900E-01, 4.7800E-01, 4.1000E-01, 3.4100E-01, 
            2.7600E-01, 2.1700E-01, 1.2600E-01, 7.1100E-02, 4.3200E-02, 
            3.2000E-02, 2.9000E-02, 2.8700E-02, 2.7200E-02, 1.8800E-02, 
            6.0200E-03, 1.9600E-03, 1.4400E-03, 1.4100E-03, 1.2300E-03, 
            6.5000E-04, 6.6000E-05, 3.6000E-05, 2.3000E-05, 9.4000E-06, 
            1.7000E-06, 1.4000E-07} );

    subshell_half_profiles[10] = 
      std::vector<double>( {4.3300E-01, 4.3300E-01, 4.3300E-01, 4.3300E-01, 
            4.3200E-01, 4.2800E-01, 4.1800E-01, 4.0000E-01, 3.7500E-01, 
            3.4300E-01, 3.0700E-01, 2.2800E-01, 1.5700E-01, 1.0100E-01, 
            6.1300E-02, 3.6400E-02, 2.1800E-02, 1.0300E-02, 8.2600E-03, 
            6.8600E-03, 3.7800E-03, 1.6800E-03, 7.1400E-04, 3.6900E-04, 
            2.7000E-04, 1.8000E-04, 7.5000E-05, 1.1000E-05, 2.1000E-06, 
            1.5000E-07, 5.4000E-09} );

    subshell_half_profiles[11] = 
      std::vector<double>( {4.4300E-01, 4.4300E-01, 4.4300E-01, 4.4200E-01, 
            4.4100E-01, 4.3700E-01, 4.2500E-01, 4.0600E-01, 3.7900E-01, 
            3.4500E-01, 3.0600E-01, 2.2500E-01, 1.5200E-01, 9.5800E-02, 
            5.7500E-02, 3.3700E-02, 2.0100E-02, 9.9300E-03, 8.3800E-03, 
            6.7300E-03, 3.5700E-03, 1.5400E-03, 6.5000E-04, 3.5100E-04, 
            2.7000E-04, 1.8000E-04, 6.9000E-05, 9.5000E-06, 1.7000E-06, 
            1.1000E-07, 2.8000E-09} );

    subshell_half_profiles[12] = 
      std::vector<double>( {2.5600E+00, 2.4000E+00, 2.0000E+00, 1.4800E+00, 
            9.7700E-01, 3.2400E-01, 9.7200E-02, 5.5600E-02, 5.3700E-02, 
            5.0000E-02, 4.1400E-02, 2.2400E-02, 1.0400E-02, 4.6100E-03, 
            2.3000E-03, 1.5400E-03, 1.3700E-03, 1.3400E-03, 9.8800E-04, 
            3.2300E-04, 9.6700E-05, 6.5600E-05, 6.4300E-05, 5.6300E-05, 
            3.0000E-05, 3.0000E-06, 1.6000E-06, 1.0000E-06, 4.3000E-07, 
            7.6000E-08, 6.2000E-09} );
  }
};

//! The default Compton profile generator implementation for A=38
template<>
struct DefaultComptonProfileGeneratorImpl<38u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 13 );

    subshell_half_profiles[0] = 
      std::vector<double>( {2.2100E-02, 2.2100E-02, 2.2100E-02, 2.2100E-02, 
            2.2100E-02, 2.2100E-02, 2.2100E-02, 2.2100E-02, 2.2100E-02, 
            2.2100E-02, 2.2100E-02, 2.2100E-02, 2.2000E-02, 2.2000E-02, 
            2.2000E-02, 2.1900E-02, 2.1900E-02, 2.1800E-02, 2.1700E-02, 
            2.1400E-02, 2.1000E-02, 2.0500E-02, 2.0000E-02, 1.9400E-02, 
            1.8000E-02, 1.4000E-02, 1.1000E-02, 5.3000E-03, 2.5000E-03, 
            5.9000E-04, 6.3000E-05} );

    subshell_half_profiles[1] = 
      std::vector<double>( {8.0900E-02, 8.0900E-02, 8.0900E-02, 8.0900E-02, 
            8.0800E-02, 8.0700E-02, 8.0600E-02, 8.0400E-02, 8.0100E-02, 
            7.9900E-02, 7.9500E-02, 7.8800E-02, 7.7900E-02, 7.6800E-02, 
            7.5600E-02, 7.4200E-02, 7.2800E-02, 6.9500E-02, 6.3800E-02, 
            5.3300E-02, 4.2600E-02, 3.2600E-02, 2.4000E-02, 1.7100E-02, 
            8.1000E-03, 2.1000E-03, 1.9000E-03, 1.1000E-03, 4.9000E-04, 
            9.4000E-05, 8.1000E-06} );

    subshell_half_profiles[2] = 
      std::vector<double>( {4.0600E-02, 4.0600E-02, 4.0600E-02, 4.0600E-02, 
            4.0600E-02, 4.0600E-02, 4.0600E-02, 4.0600E-02, 4.0600E-02, 
            4.0600E-02, 4.0600E-02, 4.0600E-02, 4.0600E-02, 4.0600E-02, 
            4.0600E-02, 4.0600E-02, 4.0500E-02, 4.0400E-02, 4.0200E-02, 
            3.9400E-02, 3.7900E-02, 3.5900E-02, 3.3300E-02, 3.0300E-02, 
            2.4000E-02, 1.1000E-02, 4.2000E-03, 6.8000E-04, 1.4000E-04, 
            1.1000E-05, 4.2000E-07} );

    subshell_half_profiles[3] = 
      std::vector<double>( {4.1600E-02, 4.1600E-02, 4.1600E-02, 4.1600E-02, 
            4.1600E-02, 4.1600E-02, 4.1600E-02, 4.1600E-02, 4.1600E-02, 
            4.1600E-02, 4.1600E-02, 4.1600E-02, 4.1600E-02, 4.1600E-02, 
            4.1600E-02, 4.1500E-02, 4.1500E-02, 4.1400E-02, 4.1100E-02, 
            4.0200E-02, 3.8700E-02, 3.6500E-02, 3.3700E-02, 3.0500E-02, 
            2.4000E-02, 1.0000E-02, 3.9000E-03, 5.9000E-04, 1.1000E-04, 
            8.0000E-06, 2.2000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {2.0400E-01, 2.0400E-01, 2.0400E-01, 2.0400E-01, 
            2.0300E-01, 2.0100E-01, 1.9800E-01, 1.9500E-01, 1.9100E-01, 
            1.8600E-01, 1.8100E-01, 1.6900E-01, 1.5500E-01, 1.4100E-01, 
            1.2600E-01, 1.1100E-01, 9.7200E-02, 7.1400E-02, 4.2100E-02, 
            1.7900E-02, 1.2100E-02, 1.1700E-02, 1.1100E-02, 9.4100E-03, 
            5.1000E-03, 5.9000E-04, 3.1000E-04, 2.1000E-04, 9.0000E-05, 
            1.7000E-05, 1.4000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 
            1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 
            1.2300E-01, 1.2300E-01, 1.2200E-01, 1.2100E-01, 1.1900E-01, 
            1.1600E-01, 1.1300E-01, 1.0900E-01, 9.9100E-02, 8.0600E-02, 
            4.8900E-02, 2.5300E-02, 1.2000E-02, 5.9200E-03, 3.7300E-03, 
            3.1000E-03, 2.2000E-03, 9.1000E-04, 1.4000E-04, 2.7000E-05, 
            2.1000E-06, 7.5000E-08} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.2500E-01, 1.2500E-01, 1.2500E-01, 1.2500E-01, 
            1.2500E-01, 1.2500E-01, 1.2500E-01, 1.2500E-01, 1.2500E-01, 
            1.2500E-01, 1.2500E-01, 1.2400E-01, 1.2300E-01, 1.2100E-01, 
            1.1800E-01, 1.1500E-01, 1.1000E-01, 9.9600E-02, 8.0200E-02, 
            4.7600E-02, 2.4100E-02, 1.1200E-02, 5.5900E-03, 3.6800E-03, 
            3.2000E-03, 2.1000E-03, 8.5000E-04, 1.2000E-04, 2.2000E-05, 
            1.5000E-06, 4.0000E-08} );

    subshell_half_profiles[7] = 
      std::vector<double>( {9.0100E-02, 9.0100E-02, 9.0100E-02, 9.0100E-02, 
            9.0100E-02, 9.0100E-02, 9.0100E-02, 9.0100E-02, 9.0100E-02, 
            9.0100E-02, 9.0100E-02, 9.0000E-02, 8.9900E-02, 8.9600E-02, 
            8.9200E-02, 8.8600E-02, 8.7600E-02, 8.4800E-02, 7.8000E-02, 
            6.2100E-02, 4.5200E-02, 3.1200E-02, 2.0800E-02, 1.3600E-02, 
            5.8000E-03, 7.6000E-04, 1.2000E-04, 6.4000E-06, 6.3000E-07, 
            1.9000E-08, 2.5000E-10} );

    subshell_half_profiles[8] = 
      std::vector<double>( {9.0700E-02, 9.0700E-02, 9.0700E-02, 9.0700E-02, 
            9.0700E-02, 9.0700E-02, 9.0700E-02, 9.0700E-02, 9.0700E-02, 
            9.0700E-02, 9.0700E-02, 9.0600E-02, 9.0500E-02, 9.0200E-02, 
            8.9800E-02, 8.9100E-02, 8.8200E-02, 8.5200E-02, 7.8300E-02, 
            6.2000E-02, 4.5000E-02, 3.0900E-02, 2.0500E-02, 1.3400E-02, 
            5.7000E-03, 7.3000E-04, 1.2000E-04, 5.9000E-06, 5.5000E-07, 
            1.6000E-08, 1.7000E-10} );

    subshell_half_profiles[9] = 
      std::vector<double>( {5.7300E-01, 5.7100E-01, 5.6400E-01, 5.5400E-01, 
            5.4000E-01, 5.0200E-01, 4.5400E-01, 3.9900E-01, 3.4100E-01, 
            2.8500E-01, 2.3200E-01, 1.4500E-01, 8.6200E-02, 5.2500E-02, 
            3.6500E-02, 3.0700E-02, 2.9500E-02, 2.8900E-02, 2.2000E-02, 
            8.0100E-03, 2.5200E-03, 1.5900E-03, 1.5500E-03, 1.4100E-03, 
            8.1000E-04, 8.8000E-05, 4.0000E-05, 2.7000E-05, 1.2000E-05, 
            2.1000E-06, 1.8000E-07} );

    subshell_half_profiles[10] = 
      std::vector<double>( {3.8900E-01, 3.8900E-01, 3.8900E-01, 3.8900E-01, 
            3.8800E-01, 3.8600E-01, 3.7900E-01, 3.6800E-01, 3.5200E-01, 
            3.3000E-01, 3.0300E-01, 2.4100E-01, 1.7800E-01, 1.2300E-01, 
            8.0300E-02, 5.0500E-02, 3.1200E-02, 1.3600E-02, 9.0200E-03, 
            8.0800E-03, 4.9000E-03, 2.3300E-03, 1.0100E-03, 4.9400E-04, 
            3.0000E-04, 2.3000E-04, 9.7000E-05, 1.5000E-05, 2.9000E-06, 
            2.2000E-07, 7.8000E-09} );

    subshell_half_profiles[11] = 
      std::vector<double>( {3.9700E-01, 3.9700E-01, 3.9700E-01, 3.9700E-01, 
            3.9600E-01, 3.9300E-01, 3.8700E-01, 3.7400E-01, 3.5600E-01, 
            3.3300E-01, 3.0400E-01, 2.3900E-01, 1.7400E-01, 1.1800E-01, 
            7.6100E-02, 4.7200E-02, 2.9000E-02, 1.2900E-02, 9.1500E-03, 
            8.0100E-03, 4.6700E-03, 2.1500E-03, 9.2200E-04, 4.6100E-04, 
            3.1000E-04, 2.2000E-04, 9.0000E-05, 1.3000E-05, 2.3000E-06, 
            1.6000E-07, 4.1000E-09} );

    subshell_half_profiles[12] = 
      std::vector<double>( {2.0600E+00, 1.9700E+00, 1.7400E+00, 1.4100E+00, 
            1.0600E+00, 4.8600E-01, 1.8700E-01, 8.2100E-02, 6.0400E-02, 
            5.9100E-02, 5.6800E-02, 4.1000E-02, 2.3300E-02, 1.1700E-02, 
            5.6500E-03, 3.1200E-03, 2.2900E-03, 2.1100E-03, 1.7500E-03, 
            6.6600E-04, 1.9500E-04, 1.0900E-04, 1.0500E-04, 9.6400E-05, 
            5.6000E-05, 6.0000E-06, 2.7000E-06, 1.8000E-06, 7.8000E-07, 
            1.4000E-07, 1.2000E-08} );
  }
};

//! The default Compton profile generator implementation for A=39
template<>
struct DefaultComptonProfileGeneratorImpl<39u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 14 );

    subshell_half_profiles[0] = 
      std::vector<double>( {2.1500E-02, 2.1500E-02, 2.1500E-02, 2.1500E-02, 
            2.1500E-02, 2.1500E-02, 2.1500E-02, 2.1500E-02, 2.1500E-02, 
            2.1500E-02, 2.1500E-02, 2.1400E-02, 2.1400E-02, 2.1400E-02, 
            2.1400E-02, 2.1300E-02, 2.1300E-02, 2.1200E-02, 2.1100E-02, 
            2.0800E-02, 2.0400E-02, 2.0000E-02, 1.9500E-02, 1.9000E-02, 
            1.8000E-02, 1.4000E-02, 1.1000E-02, 5.4000E-03, 2.6000E-03, 
            6.5000E-04, 7.0000E-05} );

    subshell_half_profiles[1] = 
      std::vector<double>( {7.8500E-02, 7.8500E-02, 7.8500E-02, 7.8500E-02, 
            7.8400E-02, 7.8300E-02, 7.8200E-02, 7.8000E-02, 7.7800E-02, 
            7.7500E-02, 7.7300E-02, 7.6600E-02, 7.5700E-02, 7.4700E-02, 
            7.3600E-02, 7.2400E-02, 7.1000E-02, 6.8000E-02, 6.2800E-02, 
            5.3000E-02, 4.2800E-02, 3.3200E-02, 2.4900E-02, 1.8000E-02, 
            8.8000E-03, 2.1000E-03, 1.8000E-03, 1.2000E-03, 5.3000E-04, 
            1.1000E-04, 9.2000E-06} );

    subshell_half_profiles[2] = 
      std::vector<double>( {3.9400E-02, 3.9400E-02, 3.9400E-02, 3.9400E-02, 
            3.9400E-02, 3.9400E-02, 3.9400E-02, 3.9400E-02, 3.9400E-02, 
            3.9400E-02, 3.9400E-02, 3.9400E-02, 3.9400E-02, 3.9400E-02, 
            3.9300E-02, 3.9300E-02, 3.9300E-02, 3.9200E-02, 3.9000E-02, 
            3.8300E-02, 3.7000E-02, 3.5200E-02, 3.2900E-02, 3.0100E-02, 
            2.4000E-02, 1.1000E-02, 4.6000E-03, 7.7000E-04, 1.6000E-04, 
            1.3000E-05, 5.1000E-07} );

    subshell_half_profiles[3] = 
      std::vector<double>( {4.0400E-02, 4.0400E-02, 4.0400E-02, 4.0400E-02, 
            4.0400E-02, 4.0400E-02, 4.0400E-02, 4.0400E-02, 4.0400E-02, 
            4.0400E-02, 4.0400E-02, 4.0400E-02, 4.0400E-02, 4.0400E-02, 
            4.0400E-02, 4.0300E-02, 4.0300E-02, 4.0200E-02, 4.0000E-02, 
            3.9200E-02, 3.7800E-02, 3.5800E-02, 3.3300E-02, 3.0400E-02, 
            2.4000E-02, 1.1000E-02, 4.3000E-03, 6.7000E-04, 1.3000E-04, 
            9.5000E-06, 2.7000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.9600E-01, 1.9600E-01, 1.9600E-01, 1.9600E-01, 
            1.9500E-01, 1.9300E-01, 1.9100E-01, 1.8800E-01, 1.8400E-01, 
            1.8000E-01, 1.7500E-01, 1.6500E-01, 1.5200E-01, 1.3900E-01, 
            1.2600E-01, 1.1200E-01, 9.8400E-02, 7.3800E-02, 4.4800E-02, 
            1.9200E-02, 1.2200E-02, 1.1500E-02, 1.1200E-02, 9.7400E-03, 
            5.6000E-03, 6.9000E-04, 3.1000E-04, 2.2000E-04, 9.9000E-05, 
            1.9000E-05, 1.6000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.1800E-01, 1.1800E-01, 1.1800E-01, 1.1800E-01, 
            1.1800E-01, 1.1800E-01, 1.1800E-01, 1.1800E-01, 1.1800E-01, 
            1.1800E-01, 1.1800E-01, 1.1700E-01, 1.1600E-01, 1.1500E-01, 
            1.1300E-01, 1.1000E-01, 1.0600E-01, 9.7600E-02, 8.1100E-02, 
            5.1400E-02, 2.7900E-02, 1.3700E-02, 6.7800E-03, 4.0300E-03, 
            3.1000E-03, 2.3000E-03, 1.0000E-03, 1.6000E-04, 3.3000E-05, 
            2.6000E-06, 9.3000E-08} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.2000E-01, 1.2000E-01, 1.2000E-01, 1.2000E-01, 
            1.2000E-01, 1.2000E-01, 1.2000E-01, 1.2000E-01, 1.2000E-01, 
            1.2000E-01, 1.2000E-01, 1.1900E-01, 1.1800E-01, 1.1700E-01, 
            1.1400E-01, 1.1100E-01, 1.0800E-01, 9.8400E-02, 8.0900E-02, 
            5.0200E-02, 2.6600E-02, 1.2800E-02, 6.3400E-03, 3.9200E-03, 
            3.2000E-03, 2.2000E-03, 9.5000E-04, 1.4000E-04, 2.7000E-05, 
            1.8000E-06, 4.9000E-08} );

    subshell_half_profiles[7] = 
      std::vector<double>( {8.5600E-02, 8.5600E-02, 8.5600E-02, 8.5600E-02, 
            8.5600E-02, 8.5600E-02, 8.5600E-02, 8.5600E-02, 8.5600E-02, 
            8.5600E-02, 8.5600E-02, 8.5600E-02, 8.5500E-02, 8.5300E-02, 
            8.5000E-02, 8.4500E-02, 8.3900E-02, 8.1700E-02, 7.6200E-02, 
            6.2500E-02, 4.7000E-02, 3.3300E-02, 2.2700E-02, 1.5200E-02, 
            6.7000E-03, 9.2000E-04, 1.6000E-04, 8.3000E-06, 8.2000E-07, 
            2.6000E-08, 3.3000E-10} );

    subshell_half_profiles[8] = 
      std::vector<double>( {8.6300E-02, 8.6300E-02, 8.6300E-02, 8.6300E-02, 
            8.6300E-02, 8.6300E-02, 8.6300E-02, 8.6300E-02, 8.6300E-02, 
            8.6200E-02, 8.6200E-02, 8.6200E-02, 8.6100E-02, 8.5900E-02, 
            8.5600E-02, 8.5100E-02, 8.4400E-02, 8.2200E-02, 7.6600E-02, 
            6.2600E-02, 4.6800E-02, 3.3000E-02, 2.2400E-02, 1.5000E-02, 
            6.5000E-03, 8.9000E-04, 1.5000E-04, 7.6000E-06, 7.3000E-07, 
            2.1000E-08, 2.2000E-10} );

    subshell_half_profiles[9] = 
      std::vector<double>( {5.3300E-01, 5.3100E-01, 5.2600E-01, 5.1800E-01, 
            5.0600E-01, 4.7500E-01, 4.3400E-01, 3.8800E-01, 3.3800E-01, 
            2.8800E-01, 2.4000E-01, 1.5700E-01, 9.7900E-02, 6.0800E-02, 
            4.1000E-02, 3.2400E-02, 2.9800E-02, 2.9300E-02, 2.4200E-02, 
            1.0000E-02, 3.1900E-03, 1.7200E-03, 1.6400E-03, 1.5400E-03, 
            9.6000E-04, 1.1000E-04, 4.2000E-05, 3.1000E-05, 1.4000E-05, 
            2.6000E-06, 2.2000E-07} );

    subshell_half_profiles[10] = 
      std::vector<double>( {3.6100E-01, 3.6100E-01, 3.6100E-01, 3.6100E-01, 
            3.6100E-01, 3.5900E-01, 3.5400E-01, 3.4600E-01, 3.3300E-01, 
            3.1600E-01, 2.9500E-01, 2.4400E-01, 1.8800E-01, 1.3700E-01, 
            9.4300E-02, 6.2300E-02, 4.0100E-02, 1.7300E-02, 9.5100E-03, 
            8.7700E-03, 5.8500E-03, 2.9800E-03, 1.3500E-03, 6.3600E-04, 
            3.3000E-04, 2.6000E-04, 1.2000E-04, 1.9000E-05, 3.7000E-06, 
            2.9000E-07, 1.1000E-08} );

    subshell_half_profiles[11] = 
      std::vector<double>( {3.6600E-01, 3.6600E-01, 3.6600E-01, 3.6600E-01, 
            3.6600E-01, 3.6400E-01, 3.5900E-01, 3.5100E-01, 3.3700E-01, 
            3.1900E-01, 2.9700E-01, 2.4300E-01, 1.8600E-01, 1.3400E-01, 
            9.1000E-02, 5.9400E-02, 3.7800E-02, 1.6400E-02, 9.6600E-03, 
            8.8600E-03, 5.6800E-03, 2.8000E-03, 1.2400E-03, 5.9100E-04, 
            3.4000E-04, 2.6000E-04, 1.1000E-04, 1.7000E-05, 3.1000E-06, 
            2.1000E-07, 5.6000E-09} );

    subshell_half_profiles[12] = 
      std::vector<double>( {4.5400E-01, 4.5400E-01, 4.5400E-01, 4.5400E-01, 
            4.5400E-01, 4.5000E-01, 4.3900E-01, 4.1700E-01, 3.8400E-01, 
            3.4400E-01, 3.0100E-01, 2.1800E-01, 1.5100E-01, 1.0100E-01, 
            6.6600E-02, 4.3200E-02, 2.7700E-02, 1.1200E-02, 3.2600E-03, 
            1.6000E-03, 1.5400E-03, 1.2800E-03, 9.4500E-04, 6.5800E-04, 
            3.0000E-04, 4.2000E-05, 7.1000E-06, 3.8000E-07, 3.7000E-08, 
            1.2000E-09, 1.5000E-11} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.9000E+00, 1.8300E+00, 1.6400E+00, 1.3700E+00, 
            1.0700E+00, 5.4400E-01, 2.3100E-01, 9.9800E-02, 6.2000E-02, 
            5.6600E-02, 5.6200E-02, 4.6000E-02, 2.9500E-02, 1.6300E-02, 
            8.3600E-03, 4.4400E-03, 2.8400E-03, 2.2600E-03, 2.0500E-03, 
            9.1000E-04, 2.7600E-04, 1.2900E-04, 1.1900E-04, 1.1300E-04, 
            7.1000E-05, 8.3000E-06, 3.1000E-06, 2.2000E-06, 9.8000E-07, 
            1.9000E-07, 1.6000E-08} );
  }
};

//! The default Compton profile generator implementation for A=40
template<>
struct DefaultComptonProfileGeneratorImpl<40u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 14 );

    subshell_half_profiles[0] = 
      std::vector<double>( {2.0900E-02, 2.0900E-02, 2.0900E-02, 2.0900E-02, 
            2.0900E-02, 2.0900E-02, 2.0900E-02, 2.0900E-02, 2.0900E-02, 
            2.0900E-02, 2.0900E-02, 2.0900E-02, 2.0800E-02, 2.0800E-02, 
            2.0800E-02, 2.0800E-02, 2.0700E-02, 2.0700E-02, 2.0500E-02, 
            2.0300E-02, 1.9900E-02, 1.9500E-02, 1.9100E-02, 1.8600E-02, 
            1.7000E-02, 1.4000E-02, 1.1000E-02, 5.6000E-03, 2.8000E-03, 
            7.0000E-04, 7.8000E-05} );

    subshell_half_profiles[1] = 
      std::vector<double>( {7.6200E-02, 7.6200E-02, 7.6200E-02, 7.6200E-02, 
            7.6100E-02, 7.6100E-02, 7.5900E-02, 7.5800E-02, 7.5600E-02, 
            7.5300E-02, 7.5100E-02, 7.4400E-02, 7.3700E-02, 7.2800E-02, 
            7.1700E-02, 7.0600E-02, 6.9300E-02, 6.6600E-02, 6.1700E-02, 
            5.2600E-02, 4.3000E-02, 3.3800E-02, 2.5700E-02, 1.8900E-02, 
            9.5000E-03, 2.2000E-03, 1.8000E-03, 1.2000E-03, 5.6000E-04, 
            1.2000E-04, 1.0000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {3.8200E-02, 3.8200E-02, 3.8200E-02, 3.8200E-02, 
            3.8200E-02, 3.8200E-02, 3.8200E-02, 3.8200E-02, 3.8200E-02, 
            3.8200E-02, 3.8200E-02, 3.8200E-02, 3.8200E-02, 3.8200E-02, 
            3.8200E-02, 3.8200E-02, 3.8100E-02, 3.8100E-02, 3.7900E-02, 
            3.7200E-02, 3.6100E-02, 3.4500E-02, 3.2400E-02, 2.9900E-02, 
            2.4000E-02, 1.2000E-02, 5.0000E-03, 8.7000E-04, 1.9000E-04, 
            1.6000E-05, 6.1000E-07} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.9200E-02, 3.9200E-02, 3.9200E-02, 3.9200E-02, 
            3.9200E-02, 3.9200E-02, 3.9200E-02, 3.9200E-02, 3.9200E-02, 
            3.9200E-02, 3.9200E-02, 3.9200E-02, 3.9200E-02, 3.9200E-02, 
            3.9200E-02, 3.9200E-02, 3.9200E-02, 3.9100E-02, 3.8900E-02, 
            3.8200E-02, 3.7000E-02, 3.5200E-02, 3.2900E-02, 3.0200E-02, 
            2.4000E-02, 1.1000E-02, 4.6000E-03, 7.6000E-04, 1.5000E-04, 
            1.1000E-05, 3.2000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.8900E-01, 1.8900E-01, 1.8900E-01, 1.8800E-01, 
            1.8800E-01, 1.8600E-01, 1.8400E-01, 1.8100E-01, 1.7800E-01, 
            1.7400E-01, 1.7000E-01, 1.6000E-01, 1.4900E-01, 1.3700E-01, 
            1.2500E-01, 1.1200E-01, 9.9300E-02, 7.5800E-02, 4.7400E-02, 
            2.0700E-02, 1.2400E-02, 1.1300E-02, 1.1100E-02, 9.9800E-03, 
            6.1000E-03, 8.1000E-04, 3.1000E-04, 2.3000E-04, 1.1000E-04, 
            2.2000E-05, 1.9000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.1400E-01, 1.1400E-01, 1.1400E-01, 1.1400E-01, 
            1.1400E-01, 1.1400E-01, 1.1400E-01, 1.1300E-01, 1.1300E-01, 
            1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1200E-01, 1.1100E-01, 
            1.0900E-01, 1.0600E-01, 1.0400E-01, 9.6000E-02, 8.1300E-02, 
            5.3600E-02, 3.0400E-02, 1.5500E-02, 7.7500E-03, 4.4200E-03, 
            3.0000E-03, 2.4000E-03, 1.1000E-03, 1.9000E-04, 3.9000E-05, 
            3.1000E-06, 1.2000E-07} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 
            1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 
            1.1600E-01, 1.1500E-01, 1.1500E-01, 1.1400E-01, 1.1300E-01, 
            1.1100E-01, 1.0800E-01, 1.0500E-01, 9.6900E-02, 8.1200E-02, 
            5.2400E-02, 2.9000E-02, 1.4500E-02, 7.2100E-03, 4.2300E-03, 
            3.1000E-03, 2.4000E-03, 1.1000E-03, 1.7000E-04, 3.1000E-05, 
            2.2000E-06, 6.0000E-08} );

    subshell_half_profiles[7] = 
      std::vector<double>( {8.1600E-02, 8.1600E-02, 8.1600E-02, 8.1600E-02, 
            8.1600E-02, 8.1600E-02, 8.1600E-02, 8.1600E-02, 8.1600E-02, 
            8.1600E-02, 8.1600E-02, 8.1600E-02, 8.1500E-02, 8.1400E-02, 
            8.1200E-02, 8.0800E-02, 8.0300E-02, 7.8600E-02, 7.4300E-02, 
            6.2600E-02, 4.8400E-02, 3.5200E-02, 2.4600E-02, 1.6800E-02, 
            7.6000E-03, 1.1000E-03, 1.9000E-04, 1.1000E-05, 1.1000E-06, 
            3.4000E-08, 4.4000E-10} );

    subshell_half_profiles[8] = 
      std::vector<double>( {8.2300E-02, 8.2300E-02, 8.2300E-02, 8.2300E-02, 
            8.2300E-02, 8.2300E-02, 8.2300E-02, 8.2300E-02, 8.2300E-02, 
            8.2300E-02, 8.2300E-02, 8.2200E-02, 8.2200E-02, 8.2000E-02, 
            8.1800E-02, 8.1500E-02, 8.0900E-02, 7.9200E-02, 7.4700E-02, 
            6.2700E-02, 4.8200E-02, 3.4900E-02, 2.4300E-02, 1.6500E-02, 
            7.4000E-03, 1.1000E-03, 1.8000E-04, 9.7000E-06, 9.4000E-07, 
            2.8000E-08, 2.9000E-10} );

    subshell_half_profiles[9] = 
      std::vector<double>( {5.0100E-01, 5.0000E-01, 4.9600E-01, 4.8800E-01, 
            4.7900E-01, 4.5200E-01, 4.1700E-01, 3.7700E-01, 3.3300E-01, 
            2.8800E-01, 2.4500E-01, 1.6700E-01, 1.0800E-01, 6.8600E-02, 
            4.5800E-02, 3.4500E-02, 3.0200E-02, 2.9100E-02, 2.5800E-02, 
            1.2100E-02, 4.0100E-03, 1.9000E-03, 1.6900E-03, 1.6400E-03, 
            1.1000E-03, 1.4000E-04, 4.5000E-05, 3.4000E-05, 1.6000E-05, 
            3.1000E-06, 2.7000E-07} );

    subshell_half_profiles[10] = 
      std::vector<double>( {3.3900E-01, 3.3900E-01, 3.3900E-01, 3.3900E-01, 
            3.3800E-01, 3.3700E-01, 3.3300E-01, 3.2700E-01, 3.1700E-01, 
            3.0400E-01, 2.8700E-01, 2.4400E-01, 1.9500E-01, 1.4700E-01, 
            1.0600E-01, 7.3100E-02, 4.8800E-02, 2.1500E-02, 1.0200E-02, 
            9.1700E-03, 6.6900E-03, 3.6700E-03, 1.7300E-03, 8.1400E-04, 
            3.6000E-04, 2.9000E-04, 1.4000E-04, 2.3000E-05, 4.7000E-06, 
            3.8000E-07, 1.4000E-08} );

    subshell_half_profiles[11] = 
      std::vector<double>( {3.4200E-01, 3.4200E-01, 3.4200E-01, 3.4200E-01, 
            3.4200E-01, 3.4100E-01, 3.3700E-01, 3.3100E-01, 3.2100E-01, 
            3.0600E-01, 2.8900E-01, 2.4400E-01, 1.9400E-01, 1.4500E-01, 
            1.0300E-01, 7.0500E-02, 4.6600E-02, 2.0400E-02, 1.0300E-02, 
            9.3800E-03, 6.5900E-03, 3.4900E-03, 1.6000E-03, 7.5300E-04, 
            3.7000E-04, 2.9000E-04, 1.3000E-04, 2.1000E-05, 3.9000E-06, 
            2.7000E-07, 7.3000E-09} );

    subshell_half_profiles[12] = 
      std::vector<double>( {3.9300E-01, 3.9300E-01, 3.9300E-01, 3.9300E-01, 
            3.9300E-01, 3.9200E-01, 3.8700E-01, 3.7500E-01, 3.5700E-01, 
            3.3200E-01, 3.0300E-01, 2.3800E-01, 1.7800E-01, 1.2800E-01, 
            8.9400E-02, 6.1300E-02, 4.1400E-02, 1.8300E-02, 5.4800E-03, 
            1.9700E-03, 1.8800E-03, 1.6600E-03, 1.2800E-03, 9.2000E-04, 
            4.4000E-04, 6.5000E-05, 1.1000E-05, 6.2000E-07, 6.1000E-08, 
            2.0000E-09, 2.6000E-11} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.8000E+00, 1.7400E+00, 1.5800E+00, 1.3400E+00, 
            1.0700E+00, 5.7900E-01, 2.6400E-01, 1.1500E-01, 6.4500E-02, 
            5.3700E-02, 5.3100E-02, 4.7100E-02, 3.3100E-02, 1.9800E-02, 
            1.0800E-02, 5.8100E-03, 3.4500E-03, 2.2900E-03, 2.1700E-03, 
            1.1200E-03, 3.6300E-04, 1.4900E-04, 1.2400E-04, 1.2200E-04, 
            8.3000E-05, 1.1000E-05, 3.3000E-06, 2.5000E-06, 1.2000E-06, 
            2.3000E-07, 2.0000E-08} );
  }
};

//! The default Compton profile generator implementation for A=41
template<>
struct DefaultComptonProfileGeneratorImpl<41u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 14 );

    subshell_half_profiles[0] = 
      std::vector<double>( {2.0300E-02, 2.0300E-02, 2.0300E-02, 2.0300E-02, 
            2.0300E-02, 2.0300E-02, 2.0300E-02, 2.0300E-02, 2.0300E-02, 
            2.0300E-02, 2.0300E-02, 2.0300E-02, 2.0300E-02, 2.0300E-02, 
            2.0300E-02, 2.0200E-02, 2.0200E-02, 2.0100E-02, 2.0000E-02, 
            1.9800E-02, 1.9500E-02, 1.9100E-02, 1.8700E-02, 1.8200E-02, 
            1.7000E-02, 1.4000E-02, 1.1000E-02, 5.8000E-03, 2.9000E-03, 
            7.6000E-04, 8.7000E-05} );

    subshell_half_profiles[1] = 
      std::vector<double>( {7.4100E-02, 7.4000E-02, 7.4000E-02, 7.4000E-02, 
            7.4000E-02, 7.3900E-02, 7.3800E-02, 7.3600E-02, 7.3500E-02, 
            7.3200E-02, 7.3000E-02, 7.2400E-02, 7.1700E-02, 7.0900E-02, 
            6.9900E-02, 6.8900E-02, 6.7700E-02, 6.5100E-02, 6.0700E-02, 
            5.2100E-02, 4.3100E-02, 3.4300E-02, 2.6400E-02, 1.9700E-02, 
            1.0000E-02, 2.3000E-03, 1.7000E-03, 1.3000E-03, 6.0000E-04, 
            1.3000E-04, 1.2000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {3.7100E-02, 3.7100E-02, 3.7100E-02, 3.7100E-02, 
            3.7100E-02, 3.7100E-02, 3.7100E-02, 3.7100E-02, 3.7100E-02, 
            3.7100E-02, 3.7100E-02, 3.7100E-02, 3.7100E-02, 3.7100E-02, 
            3.7100E-02, 3.7000E-02, 3.7000E-02, 3.7000E-02, 3.6800E-02, 
            3.6300E-02, 3.5300E-02, 3.3800E-02, 3.1900E-02, 2.9600E-02, 
            2.4000E-02, 1.2000E-02, 5.3000E-03, 9.8000E-04, 2.1000E-04, 
            1.9000E-05, 7.4000E-07} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.8100E-02, 3.8100E-02, 3.8100E-02, 3.8100E-02, 
            3.8100E-02, 3.8100E-02, 3.8100E-02, 3.8100E-02, 3.8100E-02, 
            3.8100E-02, 3.8100E-02, 3.8100E-02, 3.8100E-02, 3.8100E-02, 
            3.8100E-02, 3.8100E-02, 3.8100E-02, 3.8000E-02, 3.7800E-02, 
            3.7200E-02, 3.6100E-02, 3.4500E-02, 3.2500E-02, 3.0000E-02, 
            2.4000E-02, 1.2000E-02, 5.0000E-03, 8.5000E-04, 1.7000E-04, 
            1.3000E-05, 3.8000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.8200E-01, 1.8200E-01, 1.8200E-01, 1.8200E-01, 
            1.8100E-01, 1.8000E-01, 1.7800E-01, 1.7500E-01, 1.7200E-01, 
            1.6900E-01, 1.6500E-01, 1.5600E-01, 1.4600E-01, 1.3500E-01, 
            1.2400E-01, 1.1200E-01, 9.9900E-02, 7.7600E-02, 4.9700E-02, 
            2.2200E-02, 1.2700E-02, 1.1100E-02, 1.1000E-02, 1.0100E-02, 
            6.6000E-03, 9.5000E-04, 3.1000E-04, 2.4000E-04, 1.2000E-04, 
            2.4000E-05, 2.1000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.0900E-01, 1.0900E-01, 1.0900E-01, 1.0900E-01, 
            1.0900E-01, 1.0900E-01, 1.0900E-01, 1.0900E-01, 1.0900E-01, 
            1.0900E-01, 1.0900E-01, 1.0900E-01, 1.0800E-01, 1.0700E-01, 
            1.0500E-01, 1.0300E-01, 1.0100E-01, 9.4200E-02, 8.1100E-02, 
            5.5400E-02, 3.2700E-02, 1.7400E-02, 8.8400E-03, 4.9000E-03, 
            3.0000E-03, 2.5000E-03, 1.2000E-03, 2.2000E-04, 4.6000E-05, 
            3.8000E-06, 1.4000E-07} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.1200E-01, 1.1200E-01, 1.1200E-01, 1.1200E-01, 
            1.1200E-01, 1.1200E-01, 1.1200E-01, 1.1200E-01, 1.1100E-01, 
            1.1100E-01, 1.1100E-01, 1.1100E-01, 1.1000E-01, 1.0900E-01, 
            1.0700E-01, 1.0500E-01, 1.0200E-01, 9.5200E-02, 8.1200E-02, 
            5.4400E-02, 3.1300E-02, 1.6200E-02, 8.1800E-03, 4.6400E-03, 
            3.1000E-03, 2.5000E-03, 1.2000E-03, 1.9000E-04, 3.7000E-05, 
            2.7000E-06, 7.3000E-08} );

    subshell_half_profiles[7] = 
      std::vector<double>( {7.7900E-02, 7.7900E-02, 7.7900E-02, 7.7900E-02, 
            7.7900E-02, 7.7900E-02, 7.7900E-02, 7.7900E-02, 7.7900E-02, 
            7.7900E-02, 7.7900E-02, 7.7900E-02, 7.7900E-02, 7.7800E-02, 
            7.7600E-02, 7.7400E-02, 7.7000E-02, 7.5700E-02, 7.2200E-02, 
            6.2300E-02, 4.9500E-02, 3.6900E-02, 2.6400E-02, 1.8400E-02, 
            8.6000E-03, 1.3000E-03, 2.4000E-04, 1.3000E-05, 1.4000E-06, 
            4.5000E-08, 5.7000E-10} );

    subshell_half_profiles[8] = 
      std::vector<double>( {7.8700E-02, 7.8700E-02, 7.8700E-02, 7.8700E-02, 
            7.8700E-02, 7.8700E-02, 7.8700E-02, 7.8700E-02, 7.8700E-02, 
            7.8700E-02, 7.8700E-02, 7.8700E-02, 7.8600E-02, 7.8500E-02, 
            7.8400E-02, 7.8100E-02, 7.7700E-02, 7.6300E-02, 7.2700E-02, 
            6.2400E-02, 4.9300E-02, 3.6600E-02, 2.6000E-02, 1.8100E-02, 
            8.4000E-03, 1.3000E-03, 2.2000E-04, 1.2000E-05, 1.2000E-06, 
            3.6000E-08, 3.8000E-10} );

    subshell_half_profiles[9] = 
      std::vector<double>( {4.8000E-01, 4.7900E-01, 4.7500E-01, 4.6900E-01, 
            4.6000E-01, 4.3600E-01, 4.0500E-01, 3.6800E-01, 3.2800E-01, 
            2.8700E-01, 2.4700E-01, 1.7300E-01, 1.1500E-01, 7.4600E-02, 
            4.9700E-02, 3.6400E-02, 3.0500E-02, 2.8400E-02, 2.6300E-02, 
            1.3800E-02, 4.9000E-03, 2.1000E-03, 1.7100E-03, 1.6900E-03, 
            1.2000E-03, 1.8000E-04, 4.7000E-05, 3.6000E-05, 1.8000E-05, 
            3.6000E-06, 3.2000E-07} );

    subshell_half_profiles[10] = 
      std::vector<double>( {3.2400E-01, 3.2400E-01, 3.2400E-01, 3.2400E-01, 
            3.2400E-01, 3.2300E-01, 3.2000E-01, 3.1500E-01, 3.0600E-01, 
            2.9400E-01, 2.7900E-01, 2.4100E-01, 1.9800E-01, 1.5300E-01, 
            1.1400E-01, 8.0800E-02, 5.5700E-02, 2.5500E-02, 1.0800E-02, 
            9.1500E-03, 7.2400E-03, 4.2600E-03, 2.1200E-03, 1.0100E-03, 
            3.8000E-04, 3.0000E-04, 1.6000E-04, 2.8000E-05, 5.8000E-06, 
            4.7000E-07, 1.8000E-08} );

    subshell_half_profiles[11] = 
      std::vector<double>( {3.2600E-01, 3.2600E-01, 3.2600E-01, 3.2600E-01, 
            3.2500E-01, 3.2400E-01, 3.2200E-01, 3.1600E-01, 3.0800E-01, 
            2.9600E-01, 2.8100E-01, 2.4300E-01, 1.9800E-01, 1.5300E-01, 
            1.1200E-01, 7.9100E-02, 5.4000E-02, 2.4400E-02, 1.0900E-02, 
            9.5200E-03, 7.2600E-03, 4.1200E-03, 1.9900E-03, 9.3600E-04, 
            3.9000E-04, 3.1000E-04, 1.5000E-04, 2.5000E-05, 4.8000E-06, 
            3.4000E-07, 9.4000E-09} );

    subshell_half_profiles[12] = 
      std::vector<double>( {3.8500E-01, 3.8500E-01, 3.8500E-01, 3.8500E-01, 
            3.8400E-01, 3.8300E-01, 3.7700E-01, 3.6600E-01, 3.4800E-01, 
            3.2300E-01, 2.9500E-01, 2.3500E-01, 1.7900E-01, 1.3200E-01, 
            9.5000E-02, 6.7400E-02, 4.7100E-02, 2.2300E-02, 7.1100E-03, 
            2.0500E-03, 1.8200E-03, 1.6900E-03, 1.3700E-03, 1.0200E-03, 
            5.0000E-04, 7.9000E-05, 1.4000E-05, 8.0000E-07, 8.1000E-08, 
            2.6000E-09, 3.5000E-11} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.8800E+00, 1.8100E+00, 1.6300E+00, 1.3700E+00, 
            1.0800E+00, 5.6700E-01, 2.4800E-01, 1.0300E-01, 5.5500E-02, 
            4.5700E-02, 4.5200E-02, 4.0200E-02, 2.8600E-02, 1.7600E-02, 
            9.9300E-03, 5.4700E-03, 3.2100E-03, 1.8900E-03, 1.7900E-03, 
            1.0500E-03, 3.7300E-04, 1.4100E-04, 1.0500E-04, 1.0400E-04, 
            7.6000E-05, 1.1000E-05, 2.9000E-06, 2.2000E-06, 1.1000E-06, 
            2.2000E-07, 1.9000E-08} );
  }
};

//! The default Compton profile generator implementation for A=42
template<>
struct DefaultComptonProfileGeneratorImpl<42u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 15 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 
            1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 
            1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9700E-02, 
            1.9700E-02, 1.9700E-02, 1.9700E-02, 1.9600E-02, 1.9500E-02, 
            1.9300E-02, 1.9000E-02, 1.8600E-02, 1.8200E-02, 1.7800E-02, 
            1.7000E-02, 1.4000E-02, 1.1000E-02, 5.9000E-03, 3.0000E-03, 
            8.2000E-04, 9.7000E-05} );

    subshell_half_profiles[1] = 
      std::vector<double>( {7.2000E-02, 7.2000E-02, 7.2000E-02, 7.2000E-02, 
            7.1900E-02, 7.1900E-02, 7.1700E-02, 7.1600E-02, 7.1400E-02, 
            7.1200E-02, 7.1000E-02, 7.0500E-02, 6.9800E-02, 6.9100E-02, 
            6.8200E-02, 6.7200E-02, 6.6200E-02, 6.3800E-02, 5.9600E-02, 
            5.1600E-02, 4.3100E-02, 3.4700E-02, 2.7100E-02, 2.0500E-02, 
            1.1000E-02, 2.4000E-03, 1.7000E-03, 1.3000E-03, 6.4000E-04, 
            1.4000E-04, 1.3000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {3.6000E-02, 3.6000E-02, 3.6000E-02, 3.6000E-02, 
            3.6000E-02, 3.6000E-02, 3.6000E-02, 3.6000E-02, 3.6000E-02, 
            3.6000E-02, 3.6000E-02, 3.6000E-02, 3.6000E-02, 3.6000E-02, 
            3.6000E-02, 3.6000E-02, 3.6000E-02, 3.5900E-02, 3.5800E-02, 
            3.5300E-02, 3.4400E-02, 3.3100E-02, 3.1400E-02, 2.9300E-02, 
            2.4000E-02, 1.3000E-02, 5.7000E-03, 1.1000E-03, 2.5000E-04, 
            2.2000E-05, 8.8000E-07} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.7100E-02, 3.7100E-02, 3.7100E-02, 3.7100E-02, 
            3.7100E-02, 3.7100E-02, 3.7100E-02, 3.7100E-02, 3.7100E-02, 
            3.7100E-02, 3.7100E-02, 3.7100E-02, 3.7100E-02, 3.7100E-02, 
            3.7100E-02, 3.7100E-02, 3.7000E-02, 3.7000E-02, 3.6800E-02, 
            3.6300E-02, 3.5300E-02, 3.3900E-02, 3.2000E-02, 2.9700E-02, 
            2.4000E-02, 1.2000E-02, 5.3000E-03, 9.5000E-04, 2.0000E-04, 
            1.5000E-05, 4.5000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.7600E-01, 1.7600E-01, 1.7600E-01, 1.7500E-01, 
            1.7500E-01, 1.7400E-01, 1.7200E-01, 1.7000E-01, 1.6700E-01, 
            1.6400E-01, 1.6000E-01, 1.5200E-01, 1.4300E-01, 1.3300E-01, 
            1.2200E-01, 1.1100E-01, 1.0000E-01, 7.9000E-02, 5.1900E-02, 
            2.3800E-02, 1.3100E-02, 1.0900E-02, 1.0800E-02, 1.0200E-02, 
            7.0000E-03, 1.1000E-03, 3.2000E-04, 2.5000E-04, 1.3000E-04, 
            2.7000E-05, 2.5000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.0500E-01, 1.0500E-01, 1.0500E-01, 1.0500E-01, 
            1.0500E-01, 1.0500E-01, 1.0500E-01, 1.0500E-01, 1.0500E-01, 
            1.0500E-01, 1.0500E-01, 1.0500E-01, 1.0400E-01, 1.0300E-01, 
            1.0200E-01, 1.0000E-01, 9.8100E-02, 9.2400E-02, 8.0700E-02, 
            5.6900E-02, 3.4900E-02, 1.9200E-02, 1.0000E-02, 5.4800E-03, 
            3.0000E-03, 2.5000E-03, 1.3000E-03, 2.5000E-04, 5.3000E-05, 
            4.5000E-06, 1.7000E-07} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 
            1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 
            1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0600E-01, 1.0500E-01, 
            1.0400E-01, 1.0200E-01, 9.9700E-02, 9.3500E-02, 8.1000E-02, 
            5.6000E-02, 3.3600E-02, 1.8000E-02, 9.2600E-03, 5.1300E-03, 
            3.1000E-03, 2.5000E-03, 1.3000E-03, 2.2000E-04, 4.3000E-05, 
            3.2000E-06, 8.9000E-08} );

    subshell_half_profiles[7] = 
      std::vector<double>( {7.4700E-02, 7.4700E-02, 7.4700E-02, 7.4700E-02, 
            7.4700E-02, 7.4700E-02, 7.4700E-02, 7.4700E-02, 7.4700E-02, 
            7.4700E-02, 7.4700E-02, 7.4700E-02, 7.4600E-02, 7.4600E-02, 
            7.4400E-02, 7.4300E-02, 7.4000E-02, 7.3000E-02, 7.0100E-02, 
            6.1700E-02, 5.0200E-02, 3.8400E-02, 2.8000E-02, 1.9900E-02, 
            9.6000E-03, 1.5000E-03, 2.9000E-04, 1.7000E-05, 1.8000E-06, 
            5.8000E-08, 7.4000E-10} );

    subshell_half_profiles[8] = 
      std::vector<double>( {7.5400E-02, 7.5400E-02, 7.5400E-02, 7.5400E-02, 
            7.5400E-02, 7.5400E-02, 7.5400E-02, 7.5400E-02, 7.5400E-02, 
            7.5400E-02, 7.5400E-02, 7.5400E-02, 7.5300E-02, 7.5300E-02, 
            7.5200E-02, 7.4900E-02, 7.4600E-02, 7.3600E-02, 7.0600E-02, 
            6.1900E-02, 5.0100E-02, 3.8100E-02, 2.7700E-02, 1.9600E-02, 
            9.4000E-03, 1.5000E-03, 2.7000E-04, 1.5000E-05, 1.5000E-06, 
            4.6000E-08, 4.9000E-10} );

    subshell_half_profiles[9] = 
      std::vector<double>( {4.5600E-01, 4.5500E-01, 4.5200E-01, 4.4600E-01, 
            4.3900E-01, 4.1800E-01, 3.9000E-01, 3.5800E-01, 3.2200E-01, 
            2.8500E-01, 2.4800E-01, 1.7900E-01, 1.2300E-01, 8.1700E-02, 
            5.4800E-02, 3.9300E-02, 3.1600E-02, 2.7900E-02, 2.6800E-02, 
            1.5600E-02, 5.9700E-03, 2.4100E-03, 1.7600E-03, 1.7300E-03, 
            1.3000E-03, 2.2000E-04, 5.0000E-05, 3.9000E-05, 2.0000E-05, 
            4.2000E-06, 3.8000E-07} );

    subshell_half_profiles[10] = 
      std::vector<double>( {3.0600E-01, 3.0600E-01, 3.0600E-01, 3.0600E-01, 
            3.0600E-01, 3.0500E-01, 3.0300E-01, 2.9800E-01, 2.9200E-01, 
            2.8300E-01, 2.7000E-01, 2.3900E-01, 2.0000E-01, 1.6000E-01, 
            1.2300E-01, 9.0200E-02, 6.4300E-02, 3.0800E-02, 1.2200E-02, 
            9.2600E-03, 7.8700E-03, 4.9800E-03, 2.6100E-03, 1.2700E-03, 
            4.3000E-04, 3.3000E-04, 1.8000E-04, 3.4000E-05, 7.1000E-06, 
            6.0000E-07, 2.3000E-08} );

    subshell_half_profiles[11] = 
      std::vector<double>( {3.0900E-01, 3.0900E-01, 3.0900E-01, 3.0900E-01, 
            3.0900E-01, 3.0800E-01, 3.0600E-01, 3.0200E-01, 2.9500E-01, 
            2.8500E-01, 2.7300E-01, 2.4000E-01, 2.0000E-01, 1.5900E-01, 
            1.2100E-01, 8.7800E-02, 6.1800E-02, 2.9200E-02, 1.2000E-02, 
            9.5900E-03, 7.8900E-03, 4.8000E-03, 2.4400E-03, 1.1700E-03, 
            4.3000E-04, 3.4000E-04, 1.7000E-04, 3.0000E-05, 5.9000E-06, 
            4.3000E-07, 1.2000E-08} );

    subshell_half_profiles[12] = 
      std::vector<double>( {3.4700E-01, 3.4700E-01, 3.4700E-01, 3.4700E-01, 
            3.4700E-01, 3.4600E-01, 3.4300E-01, 3.3600E-01, 3.2500E-01, 
            3.0800E-01, 2.8700E-01, 2.4000E-01, 1.9100E-01, 1.4700E-01, 
            1.1100E-01, 8.1500E-02, 5.9200E-02, 3.0000E-02, 1.0300E-02, 
            2.5600E-03, 2.0000E-03, 1.9300E-03, 1.6300E-03, 1.2500E-03, 
            6.5000E-04, 1.1000E-04, 2.0000E-05, 1.2000E-06, 1.2000E-07, 
            4.0000E-09, 5.2000E-11} );

    subshell_half_profiles[13] = 
      std::vector<double>( {3.5700E-01, 3.5700E-01, 3.5700E-01, 3.5700E-01, 
            3.5700E-01, 3.5600E-01, 3.5200E-01, 3.4400E-01, 3.3000E-01, 
            3.1100E-01, 2.8800E-01, 2.3700E-01, 1.8700E-01, 1.4300E-01, 
            1.0600E-01, 7.8000E-02, 5.6300E-02, 2.8300E-02, 9.6300E-03, 
            2.4500E-03, 1.9700E-03, 1.8900E-03, 1.5900E-03, 1.2100E-03, 
            6.2000E-04, 1.0000E-04, 1.9000E-05, 1.0000E-06, 1.0000E-07, 
            3.1000E-09, 3.4000E-11} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.8200E+00, 1.7600E+00, 1.6000E+00, 1.3600E+00, 
            1.0900E+00, 5.9000E-01, 2.6900E-01, 1.1400E-01, 5.7600E-02, 
            4.3500E-02, 4.2000E-02, 3.9000E-02, 2.9500E-02, 1.9200E-02, 
            1.1400E-02, 6.5100E-03, 3.7900E-03, 1.9300E-03, 1.7400E-03, 
            1.1500E-03, 4.5100E-04, 1.6400E-04, 1.0700E-04, 1.0400E-04, 
            8.2000E-05, 1.3000E-05, 3.0000E-06, 2.3000E-06, 1.2000E-06, 
            2.5000E-07, 2.3000E-08} );
  }
};

//! The default Compton profile generator implementation for A=43
template<>
struct DefaultComptonProfileGeneratorImpl<43u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 15 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.9300E-02, 1.9300E-02, 1.9300E-02, 1.9300E-02, 
            1.9300E-02, 1.9300E-02, 1.9300E-02, 1.9300E-02, 1.9300E-02, 
            1.9300E-02, 1.9300E-02, 1.9300E-02, 1.9300E-02, 1.9200E-02, 
            1.9200E-02, 1.9200E-02, 1.9200E-02, 1.9100E-02, 1.9000E-02, 
            1.8800E-02, 1.8500E-02, 1.8200E-02, 1.7900E-02, 1.7400E-02, 
            1.6000E-02, 1.4000E-02, 1.1000E-02, 6.0000E-03, 3.2000E-03, 
            8.8000E-04, 1.1000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {7.0000E-02, 7.0000E-02, 7.0000E-02, 7.0000E-02, 
            7.0000E-02, 6.9900E-02, 6.9800E-02, 6.9700E-02, 6.9500E-02, 
            6.9300E-02, 6.9100E-02, 6.8600E-02, 6.8000E-02, 6.7300E-02, 
            6.6500E-02, 6.5600E-02, 6.4700E-02, 6.2400E-02, 5.8600E-02, 
            5.1100E-02, 4.3000E-02, 3.5000E-02, 2.7600E-02, 2.1200E-02, 
            1.2000E-02, 2.5000E-03, 1.7000E-03, 1.3000E-03, 6.8000E-04, 
            1.6000E-04, 1.5000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {3.5000E-02, 3.5000E-02, 3.5000E-02, 3.5000E-02, 
            3.5000E-02, 3.5000E-02, 3.5000E-02, 3.5000E-02, 3.5000E-02, 
            3.5000E-02, 3.5000E-02, 3.5000E-02, 3.5000E-02, 3.5000E-02, 
            3.5000E-02, 3.5000E-02, 3.5000E-02, 3.4900E-02, 3.4800E-02, 
            3.4400E-02, 3.3600E-02, 3.2500E-02, 3.0900E-02, 2.9000E-02, 
            2.4000E-02, 1.3000E-02, 6.1000E-03, 1.2000E-03, 2.8000E-04, 
            2.6000E-05, 1.0000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.6100E-02, 3.6100E-02, 3.6100E-02, 3.6100E-02, 
            3.6100E-02, 3.6100E-02, 3.6100E-02, 3.6100E-02, 3.6100E-02, 
            3.6100E-02, 3.6100E-02, 3.6100E-02, 3.6100E-02, 3.6100E-02, 
            3.6100E-02, 3.6100E-02, 3.6100E-02, 3.6000E-02, 3.5900E-02, 
            3.5400E-02, 3.4500E-02, 3.3300E-02, 3.1500E-02, 2.9400E-02, 
            2.5000E-02, 1.3000E-02, 5.7000E-03, 1.1000E-03, 2.2000E-04, 
            1.8000E-05, 5.3000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.7000E-01, 1.7000E-01, 1.7000E-01, 1.6900E-01, 
            1.6900E-01, 1.6800E-01, 1.6600E-01, 1.6400E-01, 1.6200E-01, 
            1.5900E-01, 1.5600E-01, 1.4900E-01, 1.4000E-01, 1.3100E-01, 
            1.2100E-01, 1.1100E-01, 1.0000E-01, 8.0200E-02, 5.4000E-02, 
            2.5500E-02, 1.3700E-02, 1.0800E-02, 1.0600E-02, 1.0200E-02, 
            7.4000E-03, 1.3000E-03, 3.3000E-04, 2.6000E-04, 1.4000E-04, 
            3.0000E-05, 2.8000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {1.0200E-01, 1.0200E-01, 1.0200E-01, 1.0200E-01, 
            1.0200E-01, 1.0200E-01, 1.0200E-01, 1.0200E-01, 1.0200E-01, 
            1.0200E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 9.9900E-02, 
            9.8800E-02, 9.7300E-02, 9.5400E-02, 9.0400E-02, 8.0000E-02, 
            5.8200E-02, 3.7000E-02, 2.1100E-02, 1.1300E-02, 6.1600E-03, 
            3.1000E-03, 2.6000E-03, 1.4000E-03, 2.8000E-04, 6.2000E-05, 
            5.4000E-06, 2.1000E-07} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 
            1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 
            1.0400E-01, 1.0400E-01, 1.0300E-01, 1.0300E-01, 1.0200E-01, 
            1.0100E-01, 9.9200E-02, 9.7100E-02, 9.1700E-02, 8.0500E-02, 
            5.7400E-02, 3.5600E-02, 1.9800E-02, 1.0400E-02, 5.7100E-03, 
            3.1000E-03, 2.6000E-03, 1.4000E-03, 2.5000E-04, 5.0000E-05, 
            3.8000E-06, 1.1000E-07} );

    subshell_half_profiles[7] = 
      std::vector<double>( {7.1700E-02, 7.1700E-02, 7.1700E-02, 7.1700E-02, 
            7.1700E-02, 7.1700E-02, 7.1700E-02, 7.1700E-02, 7.1700E-02, 
            7.1700E-02, 7.1700E-02, 7.1700E-02, 7.1700E-02, 7.1600E-02, 
            7.1500E-02, 7.1400E-02, 7.1100E-02, 7.0400E-02, 6.8100E-02, 
            6.0900E-02, 5.0700E-02, 3.9600E-02, 2.9500E-02, 2.1400E-02, 
            1.1000E-02, 1.8000E-03, 3.4000E-04, 2.1000E-05, 2.2000E-06, 
            7.4000E-08, 9.6000E-10} );

    subshell_half_profiles[8] = 
      std::vector<double>( {7.2400E-02, 7.2400E-02, 7.2400E-02, 7.2400E-02, 
            7.2400E-02, 7.2400E-02, 7.2400E-02, 7.2400E-02, 7.2400E-02, 
            7.2400E-02, 7.2400E-02, 7.2400E-02, 7.2400E-02, 7.2300E-02, 
            7.2200E-02, 7.2100E-02, 7.1800E-02, 7.1000E-02, 6.8600E-02, 
            6.1200E-02, 5.0600E-02, 3.9300E-02, 2.9200E-02, 2.1000E-02, 
            1.0000E-02, 1.7000E-03, 3.2000E-04, 1.9000E-05, 1.9000E-06, 
            5.9000E-08, 6.3000E-10} );

    subshell_half_profiles[9] = 
      std::vector<double>( {4.3000E-01, 4.2900E-01, 4.2600E-01, 4.2200E-01, 
            4.1500E-01, 3.9700E-01, 3.7400E-01, 3.4600E-01, 3.1500E-01, 
            2.8200E-01, 2.4900E-01, 1.8500E-01, 1.3100E-01, 8.9600E-02, 
            6.1100E-02, 4.3300E-02, 3.3700E-02, 2.7900E-02, 2.7100E-02, 
            1.7500E-02, 7.2600E-03, 2.8400E-03, 1.8500E-03, 1.7800E-03, 
            1.5000E-03, 2.7000E-04, 5.5000E-05, 4.2000E-05, 2.2000E-05, 
            4.9000E-06, 4.5000E-07} );

    subshell_half_profiles[10] = 
      std::vector<double>( {2.8700E-01, 2.8700E-01, 2.8700E-01, 2.8700E-01, 
            2.8700E-01, 2.8600E-01, 2.8500E-01, 2.8200E-01, 2.7700E-01, 
            2.6900E-01, 2.6000E-01, 2.3400E-01, 2.0200E-01, 1.6600E-01, 
            1.3100E-01, 9.9900E-02, 7.3500E-02, 3.7100E-02, 1.4300E-02, 
            9.3900E-03, 8.4700E-03, 5.7400E-03, 3.1900E-03, 1.6000E-03, 
            5.0000E-04, 3.5000E-04, 2.0000E-04, 4.1000E-05, 8.8000E-06, 
            7.6000E-07, 2.9000E-08} );

    subshell_half_profiles[11] = 
      std::vector<double>( {2.9100E-01, 2.9100E-01, 2.9100E-01, 2.9100E-01, 
            2.9100E-01, 2.9000E-01, 2.8900E-01, 2.8500E-01, 2.8000E-01, 
            2.7300E-01, 2.6300E-01, 2.3600E-01, 2.0200E-01, 1.6500E-01, 
            1.2900E-01, 9.7100E-02, 7.0700E-02, 3.5100E-02, 1.3700E-02, 
            9.7200E-03, 8.5200E-03, 5.5600E-03, 2.9800E-03, 1.4600E-03, 
            4.8000E-04, 3.6000E-04, 2.0000E-04, 3.6000E-05, 7.2000E-06, 
            5.4000E-07, 1.5000E-08} );

    subshell_half_profiles[12] = 
      std::vector<double>( {2.9900E-01, 2.9900E-01, 2.9900E-01, 2.9900E-01, 
            2.9900E-01, 2.9800E-01, 2.9700E-01, 2.9500E-01, 2.9000E-01, 
            2.8200E-01, 2.7100E-01, 2.4100E-01, 2.0400E-01, 1.6700E-01, 
            1.3200E-01, 1.0200E-01, 7.7300E-02, 4.2200E-02, 1.5700E-02, 
            3.6100E-03, 2.3500E-03, 2.3000E-03, 2.0400E-03, 1.6300E-03, 
            8.8000E-04, 1.6000E-04, 3.0000E-05, 1.8000E-06, 1.9000E-07, 
            6.3000E-09, 8.3000E-11} );

    subshell_half_profiles[13] = 
      std::vector<double>( {3.0500E-01, 3.0500E-01, 3.0500E-01, 3.0500E-01, 
            3.0500E-01, 3.0400E-01, 3.0300E-01, 3.0000E-01, 2.9500E-01, 
            2.8600E-01, 2.7300E-01, 2.4100E-01, 2.0300E-01, 1.6400E-01, 
            1.2900E-01, 9.9200E-02, 7.4700E-02, 4.0400E-02, 1.4900E-02, 
            3.4600E-03, 2.3400E-03, 2.2900E-03, 2.0100E-03, 1.5900E-03, 
            8.6000E-04, 1.5000E-04, 2.8000E-05, 1.6000E-06, 1.6000E-07, 
            5.0000E-09, 5.5000E-11} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.6200E+00, 1.5800E+00, 1.4600E+00, 1.2800E+00, 
            1.0600E+00, 6.4300E-01, 3.3400E-01, 1.5800E-01, 7.8400E-02, 
            5.0500E-02, 4.4100E-02, 4.2900E-02, 3.6300E-02, 2.6000E-02, 
            1.6700E-02, 1.0000E-02, 5.9000E-03, 2.5800E-03, 2.0500E-03, 
            1.5300E-03, 6.5900E-04, 2.3900E-04, 1.3500E-04, 1.2600E-04, 
            1.1000E-04, 2.0000E-05, 3.9000E-06, 3.0000E-06, 1.6000E-06, 
            3.4000E-07, 3.2000E-08} );
  }
};

//! The default Compton profile generator implementation for A=44
template<>
struct DefaultComptonProfileGeneratorImpl<44u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 15 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.8800E-02, 1.8800E-02, 1.8800E-02, 1.8800E-02, 
            1.8800E-02, 1.8800E-02, 1.8800E-02, 1.8800E-02, 1.8800E-02, 
            1.8800E-02, 1.8800E-02, 1.8800E-02, 1.8800E-02, 1.8800E-02, 
            1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8600E-02, 
            1.8400E-02, 1.8100E-02, 1.7800E-02, 1.7500E-02, 1.7100E-02, 
            1.6000E-02, 1.4000E-02, 1.1000E-02, 6.2000E-03, 3.3000E-03, 
            9.4000E-04, 1.2000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {6.8200E-02, 6.8200E-02, 6.8200E-02, 6.8100E-02, 
            6.8100E-02, 6.8100E-02, 6.8000E-02, 6.7800E-02, 6.7700E-02, 
            6.7500E-02, 6.7300E-02, 6.6900E-02, 6.6300E-02, 6.5700E-02, 
            6.4900E-02, 6.4100E-02, 6.3200E-02, 6.1100E-02, 5.7500E-02, 
            5.0600E-02, 4.2900E-02, 3.5300E-02, 2.8200E-02, 2.1900E-02, 
            1.2000E-02, 2.7000E-03, 1.6000E-03, 1.3000E-03, 7.2000E-04, 
            1.7000E-04, 1.7000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {3.4100E-02, 3.4100E-02, 3.4100E-02, 3.4100E-02, 
            3.4100E-02, 3.4100E-02, 3.4100E-02, 3.4100E-02, 3.4100E-02, 
            3.4100E-02, 3.4100E-02, 3.4100E-02, 3.4100E-02, 3.4100E-02, 
            3.4000E-02, 3.4000E-02, 3.4000E-02, 3.4000E-02, 3.3900E-02, 
            3.3500E-02, 3.2800E-02, 3.1800E-02, 3.0400E-02, 2.8600E-02, 
            2.4000E-02, 1.4000E-02, 6.5000E-03, 1.3000E-03, 3.2000E-04, 
            3.0000E-05, 1.2000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.5200E-02, 3.5200E-02, 3.5200E-02, 3.5200E-02, 
            3.5200E-02, 3.5200E-02, 3.5200E-02, 3.5200E-02, 3.5200E-02, 
            3.5200E-02, 3.5200E-02, 3.5200E-02, 3.5200E-02, 3.5200E-02, 
            3.5200E-02, 3.5200E-02, 3.5100E-02, 3.5100E-02, 3.5000E-02, 
            3.4600E-02, 3.3800E-02, 3.2600E-02, 3.1100E-02, 2.9100E-02, 
            2.5000E-02, 1.3000E-02, 6.0000E-03, 1.2000E-03, 2.5000E-04, 
            2.1000E-05, 6.2000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.6400E-01, 1.6400E-01, 1.6400E-01, 1.6400E-01, 
            1.6300E-01, 1.6200E-01, 1.6100E-01, 1.5900E-01, 1.5700E-01, 
            1.5400E-01, 1.5200E-01, 1.4500E-01, 1.3700E-01, 1.2900E-01, 
            1.1900E-01, 1.1000E-01, 1.0000E-01, 8.1100E-02, 5.5800E-02, 
            2.7100E-02, 1.4300E-02, 1.0800E-02, 1.0400E-02, 1.0200E-02, 
            7.7000E-03, 1.5000E-03, 3.4000E-04, 2.6000E-04, 1.5000E-04, 
            3.3000E-05, 3.2000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {9.8200E-02, 9.8200E-02, 9.8200E-02, 9.8200E-02, 
            9.8200E-02, 9.8200E-02, 9.8200E-02, 9.8100E-02, 9.8100E-02, 
            9.8100E-02, 9.8000E-02, 9.7800E-02, 9.7300E-02, 9.6700E-02, 
            9.5700E-02, 9.4500E-02, 9.2900E-02, 8.8500E-02, 7.9200E-02, 
            5.9200E-02, 3.8900E-02, 2.2900E-02, 1.2600E-02, 6.9100E-03, 
            3.2000E-03, 2.6000E-03, 1.5000E-03, 3.2000E-04, 7.2000E-05, 
            6.4000E-06, 2.5000E-07} );

    subshell_half_profiles[6] = 
      std::vector<double>( {1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 
            1.0100E-01, 1.0100E-01, 1.0000E-01, 1.0000E-01, 1.0000E-01, 
            1.0000E-01, 1.0000E-01, 1.0000E-01, 9.9600E-02, 9.8800E-02, 
            9.7800E-02, 9.6400E-02, 9.4600E-02, 8.9800E-02, 7.9800E-02, 
            5.8500E-02, 3.7500E-02, 2.1600E-02, 1.1600E-02, 6.3600E-03, 
            3.2000E-03, 2.7000E-03, 1.5000E-03, 2.8000E-04, 5.8000E-05, 
            4.5000E-06, 1.3000E-07} );

    subshell_half_profiles[7] = 
      std::vector<double>( {6.9000E-02, 6.9000E-02, 6.9000E-02, 6.9000E-02, 
            6.9000E-02, 6.9000E-02, 6.9000E-02, 6.9000E-02, 6.9000E-02, 
            6.9000E-02, 6.9000E-02, 6.9000E-02, 6.9000E-02, 6.8900E-02, 
            6.8900E-02, 6.8700E-02, 6.8600E-02, 6.7900E-02, 6.6100E-02, 
            6.0000E-02, 5.0900E-02, 4.0600E-02, 3.0900E-02, 2.2700E-02, 
            1.2000E-02, 2.1000E-03, 4.1000E-04, 2.6000E-05, 2.8000E-06, 
            9.4000E-08, 1.2000E-09} );

    subshell_half_profiles[8] = 
      std::vector<double>( {6.9700E-02, 6.9700E-02, 6.9700E-02, 6.9700E-02, 
            6.9700E-02, 6.9700E-02, 6.9700E-02, 6.9700E-02, 6.9700E-02, 
            6.9700E-02, 6.9700E-02, 6.9600E-02, 6.9600E-02, 6.9600E-02, 
            6.9500E-02, 6.9400E-02, 6.9200E-02, 6.8500E-02, 6.6600E-02, 
            6.0300E-02, 5.0900E-02, 4.0400E-02, 3.0600E-02, 2.2400E-02, 
            1.1000E-02, 2.0000E-03, 3.9000E-04, 2.3000E-05, 2.4000E-06, 
            7.5000E-08, 8.1000E-10} );

    subshell_half_profiles[9] = 
      std::vector<double>( {4.1600E-01, 4.1500E-01, 4.1200E-01, 4.0800E-01, 
            4.0200E-01, 3.8600E-01, 3.6500E-01, 3.3900E-01, 3.1000E-01, 
            2.7900E-01, 2.4800E-01, 1.8800E-01, 1.3500E-01, 9.4400E-02, 
            6.5000E-02, 4.6000E-02, 3.5000E-02, 2.7400E-02, 2.6600E-02, 
            1.8700E-02, 8.3900E-03, 3.2900E-03, 1.9200E-03, 1.7700E-03, 
            1.5000E-03, 3.2000E-04, 6.0000E-05, 4.4000E-05, 2.4000E-05, 
            5.5000E-06, 5.2000E-07} );

    subshell_half_profiles[10] = 
      std::vector<double>( {2.7600E-01, 2.7600E-01, 2.7600E-01, 2.7600E-01, 
            2.7600E-01, 2.7500E-01, 2.7400E-01, 2.7100E-01, 2.6700E-01, 
            2.6100E-01, 2.5200E-01, 2.3000E-01, 2.0100E-01, 1.6800E-01, 
            1.3600E-01, 1.0600E-01, 7.9600E-02, 4.2000E-02, 1.6200E-02, 
            9.2300E-03, 8.6800E-03, 6.2900E-03, 3.6900E-03, 1.9300E-03, 
            5.7000E-04, 3.6000E-04, 2.2000E-04, 4.7000E-05, 1.1000E-05, 
            9.3000E-07, 3.6000E-08} );

    subshell_half_profiles[11] = 
      std::vector<double>( {2.8100E-01, 2.8100E-01, 2.8100E-01, 2.8100E-01, 
            2.8100E-01, 2.8100E-01, 2.7900E-01, 2.7600E-01, 2.7200E-01, 
            2.6500E-01, 2.5600E-01, 2.3200E-01, 2.0100E-01, 1.6700E-01, 
            1.3300E-01, 1.0200E-01, 7.6100E-02, 3.9300E-02, 1.5200E-02, 
            9.4900E-03, 8.7200E-03, 6.0700E-03, 3.4300E-03, 1.7400E-03, 
            5.4000E-04, 3.7000E-04, 2.1000E-04, 4.2000E-05, 8.5000E-06, 
            6.5000E-07, 1.9000E-08} );

    subshell_half_profiles[12] = 
      std::vector<double>( {2.9600E-01, 2.9600E-01, 2.9600E-01, 2.9600E-01, 
            2.9600E-01, 2.9600E-01, 2.9400E-01, 2.9200E-01, 2.8600E-01, 
            2.7700E-01, 2.6600E-01, 2.3600E-01, 2.0000E-01, 1.6500E-01, 
            1.3200E-01, 1.0400E-01, 7.9800E-02, 4.5500E-02, 1.8100E-02, 
            4.1500E-03, 2.2700E-03, 2.2100E-03, 2.0300E-03, 1.6800E-03, 
            9.6000E-04, 1.8000E-04, 3.6000E-05, 2.2000E-06, 2.4000E-07, 
            8.0000E-09, 1.1000E-10} );

    subshell_half_profiles[13] = 
      std::vector<double>( {3.0300E-01, 3.0300E-01, 3.0300E-01, 3.0300E-01, 
            3.0300E-01, 3.0200E-01, 3.0100E-01, 2.9800E-01, 2.9100E-01, 
            2.8100E-01, 2.6900E-01, 2.3600E-01, 1.9900E-01, 1.6200E-01, 
            1.2900E-01, 1.0100E-01, 7.7000E-02, 4.3400E-02, 1.7100E-02, 
            3.9300E-03, 2.2400E-03, 2.1900E-03, 2.0000E-03, 1.6400E-03, 
            9.2000E-04, 1.7000E-04, 3.3000E-05, 2.0000E-06, 2.0000E-07, 
            6.3000E-09, 6.9000E-11} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.7400E+00, 1.6900E+00, 1.5400E+00, 1.3300E+00, 
            1.0900E+00, 6.2400E-01, 3.0400E-01, 1.3500E-01, 6.3900E-02, 
            4.1100E-02, 3.6500E-02, 3.5500E-02, 2.9600E-02, 2.1200E-02, 
            1.3800E-02, 8.4100E-03, 5.0400E-03, 2.1500E-03, 1.5700E-03, 
            1.2700E-03, 6.0000E-04, 2.2500E-04, 1.1400E-04, 9.9500E-05, 
            8.9000E-05, 1.9000E-05, 3.4000E-06, 2.4000E-06, 1.4000E-06, 
            3.1000E-07, 2.9000E-08} );
  }
};

//! The default Compton profile generator implementation for A=45
template<>
struct DefaultComptonProfileGeneratorImpl<45u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 15 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.8400E-02, 1.8400E-02, 1.8400E-02, 1.8400E-02, 
            1.8400E-02, 1.8400E-02, 1.8400E-02, 1.8400E-02, 1.8300E-02, 
            1.8300E-02, 1.8300E-02, 1.8300E-02, 1.8300E-02, 1.8300E-02, 
            1.8300E-02, 1.8300E-02, 1.8300E-02, 1.8200E-02, 1.8100E-02, 
            1.7900E-02, 1.7700E-02, 1.7400E-02, 1.7100E-02, 1.6700E-02, 
            1.6000E-02, 1.3000E-02, 1.1000E-02, 6.3000E-03, 3.4000E-03, 
            1.0000E-03, 1.3000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {6.6400E-02, 6.6400E-02, 6.6400E-02, 6.6400E-02, 
            6.6300E-02, 6.6300E-02, 6.6200E-02, 6.6100E-02, 6.6000E-02, 
            6.5800E-02, 6.5600E-02, 6.5200E-02, 6.4700E-02, 6.4100E-02, 
            6.3400E-02, 6.2600E-02, 6.1800E-02, 5.9900E-02, 5.6500E-02, 
            5.0000E-02, 4.2800E-02, 3.5500E-02, 2.8600E-02, 2.2500E-02, 
            1.3000E-02, 2.9000E-03, 1.6000E-03, 1.4000E-03, 7.5000E-04, 
            1.8000E-04, 1.9000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {3.3200E-02, 3.3200E-02, 3.3200E-02, 3.3200E-02, 
            3.3200E-02, 3.3200E-02, 3.3200E-02, 3.3200E-02, 3.3200E-02, 
            3.3200E-02, 3.3200E-02, 3.3100E-02, 3.3100E-02, 3.3100E-02, 
            3.3100E-02, 3.3100E-02, 3.3100E-02, 3.3100E-02, 3.3000E-02, 
            3.2700E-02, 3.2100E-02, 3.1100E-02, 2.9900E-02, 2.8300E-02, 
            2.4000E-02, 1.4000E-02, 6.8000E-03, 1.5000E-03, 3.6000E-04, 
            3.5000E-05, 1.5000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.4300E-02, 3.4300E-02, 3.4300E-02, 3.4300E-02, 
            3.4300E-02, 3.4300E-02, 3.4300E-02, 3.4300E-02, 3.4300E-02, 
            3.4300E-02, 3.4300E-02, 3.4300E-02, 3.4300E-02, 3.4300E-02, 
            3.4300E-02, 3.4300E-02, 3.4300E-02, 3.4200E-02, 3.4100E-02, 
            3.3700E-02, 3.3100E-02, 3.2000E-02, 3.0600E-02, 2.8800E-02, 
            2.5000E-02, 1.4000E-02, 6.4000E-03, 1.3000E-03, 2.9000E-04, 
            2.4000E-05, 7.3000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.5900E-01, 1.5900E-01, 1.5900E-01, 1.5900E-01, 
            1.5800E-01, 1.5700E-01, 1.5600E-01, 1.5400E-01, 1.5200E-01, 
            1.5000E-01, 1.4700E-01, 1.4100E-01, 1.3400E-01, 1.2600E-01, 
            1.1800E-01, 1.0900E-01, 9.9800E-02, 8.1800E-02, 5.7400E-02, 
            2.8800E-02, 1.5100E-02, 1.0800E-02, 1.0200E-02, 1.0100E-02, 
            8.0000E-03, 1.7000E-03, 3.6000E-04, 2.7000E-04, 1.5000E-04, 
            3.7000E-05, 3.6000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {9.4900E-02, 9.4900E-02, 9.4900E-02, 9.4900E-02, 
            9.4900E-02, 9.4900E-02, 9.4900E-02, 9.4900E-02, 9.4900E-02, 
            9.4900E-02, 9.4800E-02, 9.4600E-02, 9.4200E-02, 9.3700E-02, 
            9.2900E-02, 9.1800E-02, 9.0400E-02, 8.6500E-02, 7.8300E-02, 
            5.9900E-02, 4.0500E-02, 2.4700E-02, 1.4000E-02, 7.7500E-03, 
            3.3000E-03, 2.7000E-03, 1.6000E-03, 3.6000E-04, 8.3000E-05, 
            7.5000E-06, 3.0000E-07} );

    subshell_half_profiles[6] = 
      std::vector<double>( {9.7300E-02, 9.7300E-02, 9.7300E-02, 9.7300E-02, 
            9.7300E-02, 9.7300E-02, 9.7300E-02, 9.7300E-02, 9.7200E-02, 
            9.7200E-02, 9.7100E-02, 9.6900E-02, 9.6500E-02, 9.5900E-02, 
            9.5000E-02, 9.3800E-02, 9.2200E-02, 8.8000E-02, 7.9000E-02, 
            5.9300E-02, 3.9200E-02, 2.3300E-02, 1.2900E-02, 7.1000E-03, 
            3.3000E-03, 2.7000E-03, 1.6000E-03, 3.1000E-04, 6.7000E-05, 
            5.2000E-06, 1.5000E-07} );

    subshell_half_profiles[7] = 
      std::vector<double>( {6.6500E-02, 6.6500E-02, 6.6500E-02, 6.6500E-02, 
            6.6500E-02, 6.6500E-02, 6.6500E-02, 6.6500E-02, 6.6500E-02, 
            6.6500E-02, 6.6500E-02, 6.6500E-02, 6.6400E-02, 6.6400E-02, 
            6.6400E-02, 6.6300E-02, 6.6100E-02, 6.5600E-02, 6.4100E-02, 
            5.9000E-02, 5.0900E-02, 4.1400E-02, 3.2100E-02, 2.4000E-02, 
            1.3000E-02, 2.4000E-03, 4.8000E-04, 3.1000E-05, 3.4000E-06, 
            1.2000E-07, 1.6000E-09} );

    subshell_half_profiles[8] = 
      std::vector<double>( {6.7100E-02, 6.7100E-02, 6.7100E-02, 6.7100E-02, 
            6.7100E-02, 6.7100E-02, 6.7100E-02, 6.7100E-02, 6.7100E-02, 
            6.7100E-02, 6.7100E-02, 6.7100E-02, 6.7100E-02, 6.7100E-02, 
            6.7000E-02, 6.6900E-02, 6.6800E-02, 6.6200E-02, 6.4600E-02, 
            5.9300E-02, 5.0900E-02, 4.1200E-02, 3.1800E-02, 2.3700E-02, 
            1.2000E-02, 2.3000E-03, 4.5000E-04, 2.8000E-05, 3.0000E-06, 
            9.5000E-08, 1.0000E-09} );

    subshell_half_profiles[9] = 
      std::vector<double>( {3.9900E-01, 3.9800E-01, 3.9600E-01, 3.9200E-01, 
            3.8700E-01, 3.7200E-01, 3.5300E-01, 3.3000E-01, 3.0400E-01, 
            2.7600E-01, 2.4700E-01, 1.9100E-01, 1.4000E-01, 1.0000E-01, 
            7.0000E-02, 4.9700E-02, 3.7200E-02, 2.7400E-02, 2.6200E-02, 
            1.9900E-02, 9.6500E-03, 3.8800E-03, 2.0500E-03, 1.7800E-03, 
            1.6000E-03, 3.8000E-04, 6.8000E-05, 4.5000E-05, 2.6000E-05, 
            6.3000E-06, 6.1000E-07} );

    subshell_half_profiles[10] = 
      std::vector<double>( {2.6300E-01, 2.6300E-01, 2.6300E-01, 2.6300E-01, 
            2.6300E-01, 2.6300E-01, 2.6200E-01, 2.5900E-01, 2.5600E-01, 
            2.5100E-01, 2.4400E-01, 2.2500E-01, 2.0000E-01, 1.7000E-01, 
            1.4000E-01, 1.1200E-01, 8.6200E-02, 4.7600E-02, 1.8700E-02, 
            9.2400E-03, 8.8700E-03, 6.8400E-03, 4.2500E-03, 2.3200E-03, 
            6.7000E-04, 3.8000E-04, 2.4000E-04, 5.5000E-05, 1.3000E-05, 
            1.1000E-06, 4.5000E-08} );

    subshell_half_profiles[11] = 
      std::vector<double>( {2.7000E-01, 2.7000E-01, 2.7000E-01, 2.7000E-01, 
            2.6900E-01, 2.6900E-01, 2.6800E-01, 2.6500E-01, 2.6200E-01, 
            2.5600E-01, 2.4800E-01, 2.2800E-01, 2.0000E-01, 1.6900E-01, 
            1.3800E-01, 1.0800E-01, 8.2400E-02, 4.4400E-02, 1.7300E-02, 
            9.4300E-03, 8.9500E-03, 6.6200E-03, 3.9500E-03, 2.0900E-03, 
            6.1000E-04, 3.9000E-04, 2.4000E-04, 4.8000E-05, 1.0000E-05, 
            7.8000E-07, 2.3000E-08} );

    subshell_half_profiles[12] = 
      std::vector<double>( {2.7700E-01, 2.7700E-01, 2.7700E-01, 2.7700E-01, 
            2.7700E-01, 2.7700E-01, 2.7600E-01, 2.7400E-01, 2.7000E-01, 
            2.6400E-01, 2.5500E-01, 2.3100E-01, 2.0100E-01, 1.6900E-01, 
            1.3900E-01, 1.1200E-01, 8.8200E-02, 5.2700E-02, 2.2500E-02, 
            5.2900E-03, 2.4400E-03, 2.2800E-03, 2.1700E-03, 1.8600E-03, 
            1.1000E-03, 2.2000E-04, 4.6000E-05, 2.9000E-06, 3.2000E-07, 
            1.1000E-08, 1.4000E-10} );

    subshell_half_profiles[13] = 
      std::vector<double>( {2.8300E-01, 2.8300E-01, 2.8300E-01, 2.8300E-01, 
            2.8300E-01, 2.8300E-01, 2.8200E-01, 2.7900E-01, 2.7500E-01, 
            2.6800E-01, 2.5800E-01, 2.3200E-01, 2.0000E-01, 1.6700E-01, 
            1.3700E-01, 1.0900E-01, 8.5600E-02, 5.0600E-02, 2.1300E-02, 
            5.0000E-03, 2.4000E-03, 2.2700E-03, 2.1500E-03, 1.8300E-03, 
            1.1000E-03, 2.1000E-04, 4.3000E-05, 2.6000E-06, 2.7000E-07, 
            8.6000E-09, 9.4000E-11} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.7000E+00, 1.6500E+00, 1.5200E+00, 1.3200E+00, 
            1.0900E+00, 6.3800E-01, 3.1900E-01, 1.4500E-01, 6.7700E-02, 
            4.0900E-02, 3.4500E-02, 3.3500E-02, 2.9000E-02, 2.1600E-02, 
            1.4600E-02, 9.2300E-03, 5.6600E-03, 2.3300E-03, 1.4900E-03, 
            1.2800E-03, 6.6700E-04, 2.6100E-04, 1.2200E-04, 9.7000E-05, 
            9.0000E-05, 2.1000E-05, 3.7000E-06, 2.5000E-06, 1.4000E-06, 
            3.4000E-07, 3.3000E-08} );
  }
};

//! The default Compton profile generator implementation for A=46
template<>
struct DefaultComptonProfileGeneratorImpl<46u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 14 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.7900E-02, 1.7900E-02, 1.7900E-02, 1.7900E-02, 
            1.7900E-02, 1.7900E-02, 1.7900E-02, 1.7900E-02, 1.7900E-02, 
            1.7900E-02, 1.7900E-02, 1.7900E-02, 1.7900E-02, 1.7900E-02, 
            1.7900E-02, 1.7800E-02, 1.7800E-02, 1.7800E-02, 1.7700E-02, 
            1.7500E-02, 1.7300E-02, 1.7000E-02, 1.6700E-02, 1.6400E-02, 
            1.6000E-02, 1.3000E-02, 1.1000E-02, 6.4000E-03, 3.5000E-03, 
            1.1000E-03, 1.4000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {6.4700E-02, 6.4700E-02, 6.4700E-02, 6.4700E-02, 
            6.4600E-02, 6.4600E-02, 6.4500E-02, 6.4400E-02, 6.4300E-02, 
            6.4200E-02, 6.4000E-02, 6.3600E-02, 6.3100E-02, 6.2600E-02, 
            6.1900E-02, 6.1200E-02, 6.0400E-02, 5.8700E-02, 5.5500E-02, 
            4.9400E-02, 4.2600E-02, 3.5700E-02, 2.9100E-02, 2.3100E-02, 
            1.4000E-02, 3.1000E-03, 1.6000E-03, 1.4000E-03, 7.9000E-04, 
            2.0000E-04, 2.1000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {3.2300E-02, 3.2300E-02, 3.2300E-02, 3.2300E-02, 
            3.2300E-02, 3.2300E-02, 3.2300E-02, 3.2300E-02, 3.2300E-02, 
            3.2300E-02, 3.2300E-02, 3.2300E-02, 3.2300E-02, 3.2300E-02, 
            3.2300E-02, 3.2300E-02, 3.2300E-02, 3.2200E-02, 3.2100E-02, 
            3.1800E-02, 3.1300E-02, 3.0500E-02, 2.9300E-02, 2.7900E-02, 
            2.4000E-02, 1.4000E-02, 7.2000E-03, 1.6000E-03, 4.0000E-04, 
            4.0000E-05, 1.7000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.3500E-02, 3.3500E-02, 3.3500E-02, 3.3500E-02, 
            3.3500E-02, 3.3500E-02, 3.3500E-02, 3.3500E-02, 3.3500E-02, 
            3.3500E-02, 3.3500E-02, 3.3500E-02, 3.3500E-02, 3.3400E-02, 
            3.3400E-02, 3.3400E-02, 3.3400E-02, 3.3400E-02, 3.3300E-02, 
            3.3000E-02, 3.2300E-02, 3.1400E-02, 3.0100E-02, 2.8500E-02, 
            2.4000E-02, 1.4000E-02, 6.7000E-03, 1.4000E-03, 3.2000E-04, 
            2.7000E-05, 8.5000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.5400E-01, 1.5400E-01, 1.5400E-01, 1.5400E-01, 
            1.5300E-01, 1.5300E-01, 1.5100E-01, 1.5000E-01, 1.4800E-01, 
            1.4600E-01, 1.4400E-01, 1.3800E-01, 1.3100E-01, 1.2400E-01, 
            1.1600E-01, 1.0800E-01, 9.9300E-02, 8.2300E-02, 5.8900E-02, 
            3.0400E-02, 1.5900E-02, 1.0900E-02, 1.0000E-02, 9.9600E-03, 
            8.3000E-03, 2.0000E-03, 3.9000E-04, 2.7000E-04, 1.6000E-04, 
            4.1000E-05, 4.1000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {9.1900E-02, 9.1900E-02, 9.1900E-02, 9.1900E-02, 
            9.1900E-02, 9.1900E-02, 9.1900E-02, 9.1900E-02, 9.1900E-02, 
            9.1800E-02, 9.1800E-02, 9.1600E-02, 9.1300E-02, 9.0800E-02, 
            9.0100E-02, 8.9200E-02, 8.7900E-02, 8.4600E-02, 7.7200E-02, 
            6.0400E-02, 4.2000E-02, 2.6400E-02, 1.5400E-02, 8.6600E-03, 
            3.5000E-03, 2.7000E-03, 1.7000E-03, 4.0000E-04, 9.5000E-05, 
            8.9000E-06, 3.6000E-07} );

    subshell_half_profiles[6] = 
      std::vector<double>( {9.4300E-02, 9.4300E-02, 9.4300E-02, 9.4300E-02, 
            9.4300E-02, 9.4300E-02, 9.4300E-02, 9.4300E-02, 9.4200E-02, 
            9.4200E-02, 9.4100E-02, 9.3900E-02, 9.3600E-02, 9.3100E-02, 
            9.2300E-02, 9.1200E-02, 8.9800E-02, 8.6100E-02, 7.8000E-02, 
            5.9900E-02, 4.0800E-02, 2.5000E-02, 1.4200E-02, 7.9000E-03, 
            3.4000E-03, 2.7000E-03, 1.6000E-03, 3.5000E-04, 7.6000E-05, 
            6.1000E-06, 1.8000E-07} );

    subshell_half_profiles[7] = 
      std::vector<double>( {6.4200E-02, 6.4200E-02, 6.4200E-02, 6.4200E-02, 
            6.4200E-02, 6.4200E-02, 6.4200E-02, 6.4200E-02, 6.4200E-02, 
            6.4200E-02, 6.4200E-02, 6.4100E-02, 6.4100E-02, 6.4100E-02, 
            6.4100E-02, 6.4000E-02, 6.3900E-02, 6.3500E-02, 6.2300E-02, 
            5.7900E-02, 5.0700E-02, 4.2000E-02, 3.3100E-02, 2.5200E-02, 
            1.4000E-02, 2.7000E-03, 5.6000E-04, 3.8000E-05, 4.2000E-06, 
            1.5000E-07, 2.0000E-09} );

    subshell_half_profiles[8] = 
      std::vector<double>( {6.4700E-02, 6.4700E-02, 6.4700E-02, 6.4700E-02, 
            6.4700E-02, 6.4700E-02, 6.4700E-02, 6.4700E-02, 6.4700E-02, 
            6.4700E-02, 6.4700E-02, 6.4700E-02, 6.4700E-02, 6.4700E-02, 
            6.4600E-02, 6.4600E-02, 6.4400E-02, 6.4000E-02, 6.2700E-02, 
            5.8200E-02, 5.0800E-02, 4.1900E-02, 3.2900E-02, 2.5000E-02, 
            1.3000E-02, 2.6000E-03, 5.3000E-04, 3.4000E-05, 3.7000E-06, 
            1.2000E-07, 1.3000E-09} );

    subshell_half_profiles[9] = 
      std::vector<double>( {3.8600E-01, 3.8500E-01, 3.8300E-01, 3.8000E-01, 
            3.7500E-01, 3.6200E-01, 3.4400E-01, 3.2300E-01, 2.9900E-01, 
            2.7200E-01, 2.4600E-01, 1.9200E-01, 1.4400E-01, 1.0400E-01, 
            7.3900E-02, 5.2700E-02, 3.9200E-02, 2.7500E-02, 2.5500E-02, 
            2.0700E-02, 1.0800E-02, 4.5100E-03, 2.2300E-03, 1.7900E-03, 
            1.7000E-03, 4.4000E-04, 7.7000E-05, 4.7000E-05, 2.8000E-05, 
            7.0000E-06, 6.9000E-07} );

    subshell_half_profiles[10] = 
      std::vector<double>( {2.5400E-01, 2.5400E-01, 2.5400E-01, 2.5400E-01, 
            2.5400E-01, 2.5300E-01, 2.5200E-01, 2.5100E-01, 2.4800E-01, 
            2.4300E-01, 2.3700E-01, 2.2000E-01, 1.9800E-01, 1.7100E-01, 
            1.4300E-01, 1.1600E-01, 9.1100E-02, 5.2400E-02, 2.1200E-02, 
            9.2400E-03, 8.8600E-03, 7.2400E-03, 4.7500E-03, 2.7100E-03, 
            7.9000E-04, 3.8000E-04, 2.6000E-04, 6.3000E-05, 1.5000E-05, 
            1.4000E-06, 5.5000E-08} );

    subshell_half_profiles[11] = 
      std::vector<double>( {2.6100E-01, 2.6100E-01, 2.6100E-01, 2.6100E-01, 
            2.6100E-01, 2.6100E-01, 2.6000E-01, 2.5800E-01, 2.5400E-01, 
            2.4900E-01, 2.4200E-01, 2.2400E-01, 1.9900E-01, 1.7000E-01, 
            1.4000E-01, 1.1200E-01, 8.6900E-02, 4.8600E-02, 1.9300E-02, 
            9.3000E-03, 8.9500E-03, 7.0100E-03, 4.4100E-03, 2.4300E-03, 
            7.0000E-04, 3.9000E-04, 2.5000E-04, 5.5000E-05, 1.2000E-05, 
            9.3000E-07, 2.7000E-08} );

    subshell_half_profiles[12] = 
      std::vector<double>( {2.7800E-01, 2.7800E-01, 2.7800E-01, 2.7800E-01, 
            2.7800E-01, 2.7700E-01, 2.7600E-01, 2.7400E-01, 2.6900E-01, 
            2.6100E-01, 2.5100E-01, 2.2500E-01, 1.9600E-01, 1.6500E-01, 
            1.3700E-01, 1.1100E-01, 8.8800E-02, 5.4800E-02, 2.4700E-02, 
            6.1100E-03, 2.4800E-03, 2.1600E-03, 2.1100E-03, 1.8700E-03, 
            1.2000E-03, 2.5000E-04, 5.3000E-05, 3.5000E-06, 3.9000E-07, 
            1.4000E-08, 1.8000E-10} );

    subshell_half_profiles[13] = 
      std::vector<double>( {2.8500E-01, 2.8500E-01, 2.8500E-01, 2.8500E-01, 
            2.8500E-01, 2.8400E-01, 2.8300E-01, 2.8000E-01, 2.7400E-01, 
            2.6500E-01, 2.5400E-01, 2.2600E-01, 1.9500E-01, 1.6300E-01, 
            1.3400E-01, 1.0800E-01, 8.6100E-02, 5.2600E-02, 2.3400E-02, 
            5.7200E-03, 2.3900E-03, 2.1200E-03, 2.0600E-03, 1.8100E-03, 
            1.1000E-03, 2.3000E-04, 4.9000E-05, 3.1000E-06, 3.3000E-07, 
            1.1000E-08, 1.2000E-10} );
  }
};

//! The default Compton profile generator implementation for A=47
template<>
struct DefaultComptonProfileGeneratorImpl<47u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 15 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.7500E-02, 1.7500E-02, 1.7500E-02, 1.7500E-02, 
            1.7500E-02, 1.7500E-02, 1.7500E-02, 1.7500E-02, 1.7500E-02, 
            1.7500E-02, 1.7500E-02, 1.7500E-02, 1.7500E-02, 1.7400E-02, 
            1.7400E-02, 1.7400E-02, 1.7400E-02, 1.7400E-02, 1.7300E-02, 
            1.7100E-02, 1.6900E-02, 1.6700E-02, 1.6400E-02, 1.6100E-02, 
            1.5000E-02, 1.3000E-02, 1.1000E-02, 6.5000E-03, 3.7000E-03, 
            1.1000E-03, 1.5000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {6.3100E-02, 6.3100E-02, 6.3100E-02, 6.3100E-02, 
            6.3000E-02, 6.3000E-02, 6.2900E-02, 6.2800E-02, 6.2700E-02, 
            6.2600E-02, 6.2400E-02, 6.2100E-02, 6.1600E-02, 6.1100E-02, 
            6.0500E-02, 5.9800E-02, 5.9100E-02, 5.7500E-02, 5.4500E-02, 
            4.8800E-02, 4.2400E-02, 3.5800E-02, 2.9400E-02, 2.3600E-02, 
            1.4000E-02, 3.3000E-03, 1.6000E-03, 1.4000E-03, 8.2000E-04, 
            2.2000E-04, 2.3000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {3.1500E-02, 3.1500E-02, 3.1500E-02, 3.1500E-02, 
            3.1500E-02, 3.1500E-02, 3.1500E-02, 3.1500E-02, 3.1500E-02, 
            3.1500E-02, 3.1500E-02, 3.1500E-02, 3.1400E-02, 3.1400E-02, 
            3.1400E-02, 3.1400E-02, 3.1400E-02, 3.1400E-02, 3.1300E-02, 
            3.1100E-02, 3.0600E-02, 2.9800E-02, 2.8800E-02, 2.7500E-02, 
            2.4000E-02, 1.5000E-02, 7.6000E-03, 1.8000E-03, 4.5000E-04, 
            4.6000E-05, 2.0000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.2700E-02, 3.2700E-02, 3.2700E-02, 3.2700E-02, 
            3.2700E-02, 3.2700E-02, 3.2700E-02, 3.2700E-02, 3.2700E-02, 
            3.2700E-02, 3.2700E-02, 3.2600E-02, 3.2600E-02, 3.2600E-02, 
            3.2600E-02, 3.2600E-02, 3.2600E-02, 3.2600E-02, 3.2500E-02, 
            3.2200E-02, 3.1700E-02, 3.0800E-02, 2.9600E-02, 2.8100E-02, 
            2.4000E-02, 1.4000E-02, 7.1000E-03, 1.5000E-03, 3.6000E-04, 
            3.1000E-05, 9.9000E-07} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.4900E-01, 1.4900E-01, 1.4900E-01, 1.4900E-01, 
            1.4900E-01, 1.4800E-01, 1.4700E-01, 1.4600E-01, 1.4400E-01, 
            1.4200E-01, 1.4000E-01, 1.3500E-01, 1.2900E-01, 1.2200E-01, 
            1.1400E-01, 1.0700E-01, 9.8700E-02, 8.2700E-02, 6.0200E-02, 
            3.1900E-02, 1.6800E-02, 1.1100E-02, 9.8600E-03, 9.8000E-03, 
            8.5000E-03, 2.2000E-03, 4.3000E-04, 2.7000E-04, 1.7000E-04, 
            4.5000E-05, 4.6000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {8.9100E-02, 8.9100E-02, 8.9100E-02, 8.9100E-02, 
            8.9100E-02, 8.9000E-02, 8.9000E-02, 8.9000E-02, 8.9000E-02, 
            8.9000E-02, 8.8900E-02, 8.8800E-02, 8.8500E-02, 8.8100E-02, 
            8.7500E-02, 8.6700E-02, 8.5600E-02, 8.2700E-02, 7.6100E-02, 
            6.0700E-02, 4.3400E-02, 2.8000E-02, 1.6800E-02, 9.6300E-03, 
            3.7000E-03, 2.7000E-03, 1.8000E-03, 4.4000E-04, 1.1000E-04, 
            1.0000E-05, 4.3000E-07} );

    subshell_half_profiles[6] = 
      std::vector<double>( {9.1500E-02, 9.1500E-02, 9.1500E-02, 9.1500E-02, 
            9.1500E-02, 9.1500E-02, 9.1400E-02, 9.1400E-02, 9.1400E-02, 
            9.1400E-02, 9.1300E-02, 9.1200E-02, 9.0900E-02, 9.0400E-02, 
            8.9700E-02, 8.8800E-02, 8.7600E-02, 8.4300E-02, 7.7000E-02, 
            6.0400E-02, 4.2200E-02, 2.6600E-02, 1.5500E-02, 8.7600E-03, 
            3.6000E-03, 2.8000E-03, 1.7000E-03, 3.9000E-04, 8.7000E-05, 
            7.1000E-06, 2.1000E-07} );

    subshell_half_profiles[7] = 
      std::vector<double>( {6.2000E-02, 6.2000E-02, 6.2000E-02, 6.2000E-02, 
            6.2000E-02, 6.2000E-02, 6.2000E-02, 6.2000E-02, 6.2000E-02, 
            6.2000E-02, 6.2000E-02, 6.2000E-02, 6.2000E-02, 6.2000E-02, 
            6.1900E-02, 6.1900E-02, 6.1800E-02, 6.1500E-02, 6.0400E-02, 
            5.6700E-02, 5.0400E-02, 4.2400E-02, 3.4000E-02, 2.6300E-02, 
            1.5000E-02, 3.0000E-03, 6.6000E-04, 4.5000E-05, 5.2000E-06, 
            1.8000E-07, 2.5000E-09} );

    subshell_half_profiles[8] = 
      std::vector<double>( {6.2500E-02, 6.2500E-02, 6.2500E-02, 6.2500E-02, 
            6.2500E-02, 6.2500E-02, 6.2500E-02, 6.2500E-02, 6.2500E-02, 
            6.2500E-02, 6.2500E-02, 6.2500E-02, 6.2500E-02, 6.2500E-02, 
            6.2500E-02, 6.2400E-02, 6.2300E-02, 6.2000E-02, 6.0900E-02, 
            5.7100E-02, 5.0500E-02, 4.2300E-02, 3.3800E-02, 2.6100E-02, 
            1.4000E-02, 2.9000E-03, 6.2000E-04, 4.1000E-05, 4.5000E-06, 
            1.5000E-07, 1.6000E-09} );

    subshell_half_profiles[9] = 
      std::vector<double>( {3.6900E-01, 3.6800E-01, 3.6600E-01, 3.6300E-01, 
            3.5900E-01, 3.4700E-01, 3.3200E-01, 3.1300E-01, 2.9100E-01, 
            2.6800E-01, 2.4300E-01, 1.9400E-01, 1.4800E-01, 1.1000E-01, 
            7.9300E-02, 5.7100E-02, 4.2300E-02, 2.8200E-02, 2.5100E-02, 
            2.1500E-02, 1.2100E-02, 5.3000E-03, 2.5000E-03, 1.8300E-03, 
            1.7000E-03, 5.2000E-04, 8.9000E-05, 4.8000E-05, 3.1000E-05, 
            7.9000E-06, 8.0000E-07} );

    subshell_half_profiles[10] = 
      std::vector<double>( {2.4200E-01, 2.4200E-01, 2.4200E-01, 2.4200E-01, 
            2.4200E-01, 2.4100E-01, 2.4100E-01, 2.3900E-01, 2.3700E-01, 
            2.3300E-01, 2.2800E-01, 2.1400E-01, 1.9500E-01, 1.7200E-01, 
            1.4600E-01, 1.2100E-01, 9.7200E-02, 5.8300E-02, 2.4500E-02, 
            9.5400E-03, 8.9200E-03, 7.6800E-03, 5.3100E-03, 3.1700E-03, 
            9.5000E-04, 3.9000E-04, 2.8000E-04, 7.2000E-05, 1.7000E-05, 
            1.6000E-06, 6.8000E-08} );

    subshell_half_profiles[11] = 
      std::vector<double>( {2.4900E-01, 2.4900E-01, 2.4900E-01, 2.4900E-01, 
            2.4900E-01, 2.4900E-01, 2.4800E-01, 2.4600E-01, 2.4300E-01, 
            2.3900E-01, 2.3400E-01, 2.1800E-01, 1.9700E-01, 1.7100E-01, 
            1.4400E-01, 1.1800E-01, 9.3200E-02, 5.4400E-02, 2.2300E-02, 
            9.5000E-03, 9.0700E-03, 7.5000E-03, 4.9700E-03, 2.8500E-03, 
            8.3000E-04, 4.1000E-04, 2.8000E-04, 6.3000E-05, 1.4000E-05, 
            1.1000E-06, 3.4000E-08} );

    subshell_half_profiles[12] = 
      std::vector<double>( {2.4700E-01, 2.4700E-01, 2.4700E-01, 2.4700E-01, 
            2.4700E-01, 2.4700E-01, 2.4600E-01, 2.4500E-01, 2.4300E-01, 
            2.3900E-01, 2.3400E-01, 2.1800E-01, 1.9700E-01, 1.7200E-01, 
            1.4700E-01, 1.2300E-01, 1.0100E-01, 6.5700E-02, 3.1500E-02, 
            8.2800E-03, 3.0100E-03, 2.3700E-03, 2.3400E-03, 2.1400E-03, 
            1.4000E-03, 3.2000E-04, 7.1000E-05, 4.9000E-06, 5.4000E-07, 
            1.9000E-08, 2.6000E-10} );

    subshell_half_profiles[13] = 
      std::vector<double>( {2.5100E-01, 2.5100E-01, 2.5100E-01, 2.5100E-01, 
            2.5100E-01, 2.5100E-01, 2.5100E-01, 2.5000E-01, 2.4700E-01, 
            2.4300E-01, 2.3700E-01, 2.2000E-01, 1.9700E-01, 1.7200E-01, 
            1.4600E-01, 1.2100E-01, 9.9300E-02, 6.3700E-02, 3.0100E-02, 
            7.8000E-03, 2.9000E-03, 2.3400E-03, 2.3100E-03, 2.1000E-03, 
            1.4000E-03, 3.0000E-04, 6.5000E-05, 4.3000E-06, 4.7000E-07, 
            1.5000E-08, 1.7000E-10} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.6400E+00, 1.6000E+00, 1.4800E+00, 1.3000E+00, 
            1.0800E+00, 6.6000E-01, 3.4600E-01, 1.6400E-01, 7.6300E-02, 
            4.2000E-02, 3.1600E-02, 2.9600E-02, 2.7200E-02, 2.1800E-02, 
            1.5700E-02, 1.0600E-02, 6.8200E-03, 2.8100E-03, 1.3700E-03, 
            1.2400E-03, 7.7100E-04, 3.4000E-04, 1.4600E-04, 9.4700E-05, 
            8.8000E-05, 2.7000E-05, 4.6000E-06, 2.4000E-06, 1.5000E-06, 
            4.0000E-07, 4.0000E-08} );
  }
};

//! The default Compton profile generator implementation for A=48
template<>
struct DefaultComptonProfileGeneratorImpl<48u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 15 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.7100E-02, 1.7100E-02, 1.7100E-02, 1.7100E-02, 
            1.7100E-02, 1.7100E-02, 1.7100E-02, 1.7100E-02, 1.7100E-02, 
            1.7100E-02, 1.7100E-02, 1.7100E-02, 1.7000E-02, 1.7000E-02, 
            1.7000E-02, 1.7000E-02, 1.7000E-02, 1.7000E-02, 1.6900E-02, 
            1.6700E-02, 1.6500E-02, 1.6300E-02, 1.6100E-02, 1.5800E-02, 
            1.5000E-02, 1.3000E-02, 1.1000E-02, 6.6000E-03, 3.8000E-03, 
            1.2000E-03, 1.7000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {6.1500E-02, 6.1500E-02, 6.1500E-02, 6.1500E-02, 
            6.1500E-02, 6.1400E-02, 6.1400E-02, 6.1300E-02, 6.1200E-02, 
            6.1100E-02, 6.0900E-02, 6.0600E-02, 6.0200E-02, 5.9700E-02, 
            5.9100E-02, 5.8500E-02, 5.7800E-02, 5.6300E-02, 5.3600E-02, 
            4.8200E-02, 4.2100E-02, 3.5800E-02, 2.9700E-02, 2.4100E-02, 
            1.5000E-02, 3.6000E-03, 1.6000E-03, 1.4000E-03, 8.5000E-04, 
            2.3000E-04, 2.6000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {3.0700E-02, 3.0700E-02, 3.0700E-02, 3.0700E-02, 
            3.0700E-02, 3.0700E-02, 3.0700E-02, 3.0700E-02, 3.0700E-02, 
            3.0700E-02, 3.0700E-02, 3.0700E-02, 3.0700E-02, 3.0700E-02, 
            3.0600E-02, 3.0600E-02, 3.0600E-02, 3.0600E-02, 3.0500E-02, 
            3.0300E-02, 2.9900E-02, 2.9200E-02, 2.8300E-02, 2.7100E-02, 
            2.4000E-02, 1.5000E-02, 7.9000E-03, 1.9000E-03, 5.0000E-04, 
            5.3000E-05, 2.4000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.1900E-02, 3.1900E-02, 3.1900E-02, 3.1900E-02, 
            3.1900E-02, 3.1900E-02, 3.1900E-02, 3.1900E-02, 3.1900E-02, 
            3.1900E-02, 3.1900E-02, 3.1900E-02, 3.1900E-02, 3.1900E-02, 
            3.1900E-02, 3.1900E-02, 3.1900E-02, 3.1800E-02, 3.1700E-02, 
            3.1500E-02, 3.1000E-02, 3.0200E-02, 2.9100E-02, 2.7700E-02, 
            2.4000E-02, 1.5000E-02, 7.4000E-03, 1.7000E-03, 4.0000E-04, 
            3.5000E-05, 1.1000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.4500E-01, 1.4500E-01, 1.4500E-01, 1.4500E-01, 
            1.4400E-01, 1.4400E-01, 1.4300E-01, 1.4200E-01, 1.4000E-01, 
            1.3800E-01, 1.3600E-01, 1.3100E-01, 1.2600E-01, 1.2000E-01, 
            1.1300E-01, 1.0600E-01, 9.8000E-02, 8.2900E-02, 6.1300E-02, 
            3.3400E-02, 1.7800E-02, 1.1300E-02, 9.7300E-03, 9.6200E-03, 
            8.6000E-03, 2.5000E-03, 4.8000E-04, 2.7000E-04, 1.8000E-04, 
            4.9000E-05, 5.1000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {8.6400E-02, 8.6400E-02, 8.6400E-02, 8.6400E-02, 
            8.6400E-02, 8.6400E-02, 8.6400E-02, 8.6300E-02, 8.6300E-02, 
            8.6300E-02, 8.6300E-02, 8.6100E-02, 8.5900E-02, 8.5600E-02, 
            8.5000E-02, 8.4300E-02, 8.3400E-02, 8.0800E-02, 7.4900E-02, 
            6.0800E-02, 4.4500E-02, 2.9600E-02, 1.8200E-02, 1.0700E-02, 
            4.0000E-03, 2.6000E-03, 1.9000E-03, 4.9000E-04, 1.2000E-04, 
            1.2000E-05, 5.1000E-07} );

    subshell_half_profiles[6] = 
      std::vector<double>( {8.8800E-02, 8.8800E-02, 8.8800E-02, 8.8800E-02, 
            8.8800E-02, 8.8800E-02, 8.8800E-02, 8.8800E-02, 8.8700E-02, 
            8.8700E-02, 8.8700E-02, 8.8500E-02, 8.8300E-02, 8.7900E-02, 
            8.7300E-02, 8.6400E-02, 8.5400E-02, 8.2500E-02, 7.6000E-02, 
            6.0700E-02, 4.3400E-02, 2.8100E-02, 1.6800E-02, 9.6700E-03, 
            3.8000E-03, 2.8000E-03, 1.8000E-03, 4.3000E-04, 9.8000E-05, 
            8.2000E-06, 2.5000E-07} );

    subshell_half_profiles[7] = 
      std::vector<double>( {6.0000E-02, 6.0000E-02, 6.0000E-02, 6.0000E-02, 
            6.0000E-02, 6.0000E-02, 6.0000E-02, 6.0000E-02, 6.0000E-02, 
            6.0000E-02, 6.0000E-02, 6.0000E-02, 5.9900E-02, 5.9900E-02, 
            5.9900E-02, 5.9900E-02, 5.9800E-02, 5.9500E-02, 5.8700E-02, 
            5.5500E-02, 5.0000E-02, 4.2600E-02, 3.4800E-02, 2.7400E-02, 
            1.6000E-02, 3.4000E-03, 7.6000E-04, 5.4000E-05, 6.3000E-06, 
            2.3000E-07, 3.1000E-09} );

    subshell_half_profiles[8] = 
      std::vector<double>( {6.0500E-02, 6.0500E-02, 6.0500E-02, 6.0500E-02, 
            6.0500E-02, 6.0500E-02, 6.0500E-02, 6.0500E-02, 6.0500E-02, 
            6.0500E-02, 6.0500E-02, 6.0500E-02, 6.0500E-02, 6.0500E-02, 
            6.0500E-02, 6.0400E-02, 6.0400E-02, 6.0100E-02, 5.9200E-02, 
            5.5900E-02, 5.0100E-02, 4.2600E-02, 3.4600E-02, 2.7100E-02, 
            1.5000E-02, 3.3000E-03, 7.1000E-04, 4.9000E-05, 5.5000E-06, 
            1.8000E-07, 2.0000E-09} );

    subshell_half_profiles[9] = 
      std::vector<double>( {3.5200E-01, 3.5100E-01, 3.5000E-01, 3.4700E-01, 
            3.4300E-01, 3.3300E-01, 3.2000E-01, 3.0300E-01, 2.8400E-01, 
            2.6300E-01, 2.4000E-01, 1.9500E-01, 1.5200E-01, 1.1500E-01, 
            8.4600E-02, 6.1700E-02, 4.5700E-02, 2.9400E-02, 2.4800E-02, 
            2.2300E-02, 1.3500E-02, 6.1900E-03, 2.8400E-03, 1.9000E-03, 
            1.8000E-03, 6.0000E-04, 1.1000E-04, 4.9000E-05, 3.3000E-05, 
            8.9000E-06, 9.3000E-07} );

    subshell_half_profiles[10] = 
      std::vector<double>( {2.3000E-01, 2.3000E-01, 2.3000E-01, 2.3000E-01, 
            2.3000E-01, 2.3000E-01, 2.2900E-01, 2.2800E-01, 2.2600E-01, 
            2.2400E-01, 2.2000E-01, 2.0800E-01, 1.9100E-01, 1.7100E-01, 
            1.4800E-01, 1.2500E-01, 1.0300E-01, 6.4100E-02, 2.8200E-02, 
            1.0000E-02, 8.9400E-03, 8.0500E-03, 5.8700E-03, 3.6500E-03, 
            1.1000E-03, 4.0000E-04, 3.1000E-04, 8.3000E-05, 2.0000E-05, 
            2.0000E-06, 8.4000E-08} );

    subshell_half_profiles[11] = 
      std::vector<double>( {2.3700E-01, 2.3700E-01, 2.3700E-01, 2.3700E-01, 
            2.3700E-01, 2.3700E-01, 2.3600E-01, 2.3500E-01, 2.3300E-01, 
            2.3000E-01, 2.2500E-01, 2.1200E-01, 1.9400E-01, 1.7100E-01, 
            1.4700E-01, 1.2200E-01, 9.8900E-02, 6.0100E-02, 2.5600E-02, 
            9.8600E-03, 9.1500E-03, 7.9400E-03, 5.5300E-03, 3.3100E-03, 
            9.9000E-04, 4.2000E-04, 3.0000E-04, 7.2000E-05, 1.6000E-05, 
            1.4000E-06, 4.1000E-08} );

    subshell_half_profiles[12] = 
      std::vector<double>( {2.2400E-01, 2.2400E-01, 2.2400E-01, 2.2400E-01, 
            2.2400E-01, 2.2400E-01, 2.2400E-01, 2.2300E-01, 2.2200E-01, 
            2.2000E-01, 2.1700E-01, 2.0700E-01, 1.9300E-01, 1.7400E-01, 
            1.5300E-01, 1.3200E-01, 1.1100E-01, 7.5600E-02, 3.8500E-02, 
            1.0900E-02, 3.6900E-03, 2.5600E-03, 2.5200E-03, 2.3800E-03, 
            1.7000E-03, 4.0000E-04, 9.1000E-05, 6.5000E-06, 7.4000E-07, 
            2.7000E-08, 3.6000E-10} );

    subshell_half_profiles[13] = 
      std::vector<double>( {2.2800E-01, 2.2800E-01, 2.2800E-01, 2.2800E-01, 
            2.2800E-01, 2.2800E-01, 2.2800E-01, 2.2700E-01, 2.2600E-01, 
            2.2400E-01, 2.2000E-01, 2.1000E-01, 1.9400E-01, 1.7400E-01, 
            1.5300E-01, 1.3100E-01, 1.1000E-01, 7.3800E-02, 3.7100E-02, 
            1.0300E-02, 3.5400E-03, 2.5400E-03, 2.5100E-03, 2.3500E-03, 
            1.6000E-03, 3.8000E-04, 8.5000E-05, 5.8000E-06, 6.4000E-07, 
            2.1000E-08, 2.3000E-10} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.4500E+00, 1.4200E+00, 1.3300E+00, 1.2000E+00, 
            1.0400E+00, 6.9400E-01, 4.0900E-01, 2.1900E-01, 1.1200E-01, 
            6.0500E-02, 3.9800E-02, 3.2500E-02, 3.1700E-02, 2.7500E-02, 
            2.1300E-02, 1.5200E-02, 1.0200E-02, 4.3200E-03, 1.7900E-03, 
            1.5600E-03, 1.0600E-03, 4.9800E-04, 2.1300E-04, 1.2400E-04, 
            1.1000E-04, 3.9000E-05, 6.7000E-06, 3.0000E-06, 2.0000E-06, 
            5.5000E-07, 5.7000E-08} );
  }
};

//! The default Compton profile generator implementation for A=49
template<>
struct DefaultComptonProfileGeneratorImpl<49u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 16 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 
            1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 
            1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6600E-02, 
            1.6600E-02, 1.6600E-02, 1.6600E-02, 1.6600E-02, 1.6500E-02, 
            1.6400E-02, 1.6200E-02, 1.6000E-02, 1.5700E-02, 1.5500E-02, 
            1.5000E-02, 1.3000E-02, 1.1000E-02, 6.7000E-03, 3.9000E-03, 
            1.3000E-03, 1.8000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {6.0000E-02, 6.0000E-02, 6.0000E-02, 6.0000E-02, 
            6.0000E-02, 6.0000E-02, 5.9900E-02, 5.9800E-02, 5.9700E-02, 
            5.9600E-02, 5.9500E-02, 5.9200E-02, 5.8800E-02, 5.8300E-02, 
            5.7800E-02, 5.7200E-02, 5.6600E-02, 5.5200E-02, 5.2600E-02, 
            4.7600E-02, 4.1800E-02, 3.5800E-02, 3.0000E-02, 2.4500E-02, 
            1.5000E-02, 3.9000E-03, 1.6000E-03, 1.4000E-03, 8.8000E-04, 
            2.5000E-04, 2.8000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.9900E-02, 2.9900E-02, 2.9900E-02, 2.9900E-02, 
            2.9900E-02, 2.9900E-02, 2.9900E-02, 2.9900E-02, 2.9900E-02, 
            2.9900E-02, 2.9900E-02, 2.9900E-02, 2.9900E-02, 2.9900E-02, 
            2.9900E-02, 2.9900E-02, 2.9900E-02, 2.9900E-02, 2.9800E-02, 
            2.9600E-02, 2.9200E-02, 2.8600E-02, 2.7800E-02, 2.6600E-02, 
            2.4000E-02, 1.5000E-02, 8.2000E-03, 2.1000E-03, 5.6000E-04, 
            6.0000E-05, 2.7000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.1100E-02, 3.1100E-02, 3.1100E-02, 3.1100E-02, 
            3.1100E-02, 3.1100E-02, 3.1100E-02, 3.1100E-02, 3.1100E-02, 
            3.1100E-02, 3.1100E-02, 3.1100E-02, 3.1100E-02, 3.1100E-02, 
            3.1100E-02, 3.1100E-02, 3.1100E-02, 3.1100E-02, 3.1000E-02, 
            3.0800E-02, 3.0300E-02, 2.9600E-02, 2.8600E-02, 2.7400E-02, 
            2.4000E-02, 1.5000E-02, 7.7000E-03, 1.8000E-03, 4.4000E-04, 
            4.0000E-05, 1.3000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.4100E-01, 1.4100E-01, 1.4100E-01, 1.4100E-01, 
            1.4000E-01, 1.4000E-01, 1.3900E-01, 1.3800E-01, 1.3600E-01, 
            1.3500E-01, 1.3300E-01, 1.2800E-01, 1.2300E-01, 1.1700E-01, 
            1.1100E-01, 1.0400E-01, 9.7300E-02, 8.2900E-02, 6.2300E-02, 
            3.4900E-02, 1.8700E-02, 1.1700E-02, 9.6500E-03, 9.4400E-03, 
            8.7000E-03, 2.8000E-03, 5.4000E-04, 2.7000E-04, 1.9000E-04, 
            5.3000E-05, 5.7000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {8.3800E-02, 8.3800E-02, 8.3800E-02, 8.3800E-02, 
            8.3800E-02, 8.3800E-02, 8.3800E-02, 8.3800E-02, 8.3800E-02, 
            8.3800E-02, 8.3700E-02, 8.3600E-02, 8.3400E-02, 8.3100E-02, 
            8.2700E-02, 8.2000E-02, 8.1200E-02, 7.8900E-02, 7.3700E-02, 
            6.0800E-02, 4.5500E-02, 3.1000E-02, 1.9600E-02, 1.1700E-02, 
            4.4000E-03, 2.6000E-03, 1.9000E-03, 5.4000E-04, 1.4000E-04, 
            1.4000E-05, 6.0000E-07} );

    subshell_half_profiles[6] = 
      std::vector<double>( {8.6300E-02, 8.6300E-02, 8.6300E-02, 8.6300E-02, 
            8.6300E-02, 8.6300E-02, 8.6200E-02, 8.6200E-02, 8.6200E-02, 
            8.6200E-02, 8.6200E-02, 8.6000E-02, 8.5800E-02, 8.5400E-02, 
            8.4900E-02, 8.4200E-02, 8.3300E-02, 8.0700E-02, 7.4800E-02, 
            6.0800E-02, 4.4400E-02, 2.9500E-02, 1.8100E-02, 1.0600E-02, 
            4.1000E-03, 2.7000E-03, 1.9000E-03, 4.7000E-04, 1.1000E-04, 
            9.5000E-06, 2.9000E-07} );

    subshell_half_profiles[7] = 
      std::vector<double>( {5.8100E-02, 5.8100E-02, 5.8100E-02, 5.8100E-02, 
            5.8100E-02, 5.8100E-02, 5.8100E-02, 5.8100E-02, 5.8100E-02, 
            5.8100E-02, 5.8100E-02, 5.8100E-02, 5.8100E-02, 5.8000E-02, 
            5.8000E-02, 5.8000E-02, 5.7900E-02, 5.7700E-02, 5.7000E-02, 
            5.4300E-02, 4.9400E-02, 4.2800E-02, 3.5400E-02, 2.8300E-02, 
            1.7000E-02, 3.8000E-03, 8.7000E-04, 6.4000E-05, 7.6000E-06, 
            2.8000E-07, 3.8000E-09} );

    subshell_half_profiles[8] = 
      std::vector<double>( {5.8600E-02, 5.8600E-02, 5.8600E-02, 5.8600E-02, 
            5.8600E-02, 5.8600E-02, 5.8600E-02, 5.8600E-02, 5.8600E-02, 
            5.8600E-02, 5.8600E-02, 5.8600E-02, 5.8600E-02, 5.8600E-02, 
            5.8600E-02, 5.8600E-02, 5.8500E-02, 5.8300E-02, 5.7500E-02, 
            5.4700E-02, 4.9600E-02, 4.2800E-02, 3.5300E-02, 2.8000E-02, 
            1.6000E-02, 3.6000E-03, 8.2000E-04, 5.9000E-05, 6.6000E-06, 
            2.2000E-07, 2.4000E-09} );

    subshell_half_profiles[9] = 
      std::vector<double>( {3.3600E-01, 3.3600E-01, 3.3500E-01, 3.3200E-01, 
            3.2900E-01, 3.2000E-01, 3.0800E-01, 2.9300E-01, 2.7600E-01, 
            2.5700E-01, 2.3700E-01, 1.9500E-01, 1.5500E-01, 1.1900E-01, 
            8.9500E-02, 6.6300E-02, 4.9400E-02, 3.0900E-02, 2.4600E-02, 
            2.2800E-02, 1.4700E-02, 7.1500E-03, 3.2700E-03, 2.0100E-03, 
            1.8000E-03, 6.9000E-04, 1.2000E-04, 5.0000E-05, 3.5000E-05, 
            9.9000E-06, 1.1000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {2.1900E-01, 2.1900E-01, 2.1900E-01, 2.1900E-01, 
            2.1900E-01, 2.1900E-01, 2.1900E-01, 2.1800E-01, 2.1600E-01, 
            2.1400E-01, 2.1100E-01, 2.0100E-01, 1.8700E-01, 1.7000E-01, 
            1.5000E-01, 1.2900E-01, 1.0700E-01, 6.9900E-02, 3.2300E-02, 
            1.0800E-02, 8.9400E-03, 8.3600E-03, 6.4000E-03, 4.1700E-03, 
            1.4000E-03, 4.0000E-04, 3.3000E-04, 9.4000E-05, 2.4000E-05, 
            2.4000E-06, 1.0000E-07} );

    subshell_half_profiles[11] = 
      std::vector<double>( {2.2600E-01, 2.2600E-01, 2.2600E-01, 2.2600E-01, 
            2.2600E-01, 2.2600E-01, 2.2600E-01, 2.2500E-01, 2.2300E-01, 
            2.2000E-01, 2.1600E-01, 2.0600E-01, 1.9000E-01, 1.7100E-01, 
            1.4900E-01, 1.2600E-01, 1.0400E-01, 6.5800E-02, 2.9300E-02, 
            1.0400E-02, 9.1800E-03, 8.3100E-03, 6.0800E-03, 3.8000E-03, 
            1.2000E-03, 4.3000E-04, 3.2000E-04, 8.3000E-05, 1.9000E-05, 
            1.6000E-06, 5.0000E-08} );

    subshell_half_profiles[12] = 
      std::vector<double>( {2.0600E-01, 2.0600E-01, 2.0600E-01, 2.0600E-01, 
            2.0600E-01, 2.0600E-01, 2.0600E-01, 2.0600E-01, 2.0500E-01, 
            2.0400E-01, 2.0200E-01, 1.9600E-01, 1.8600E-01, 1.7200E-01, 
            1.5500E-01, 1.3700E-01, 1.1900E-01, 8.4300E-02, 4.5700E-02, 
            1.3900E-02, 4.5500E-03, 2.7800E-03, 2.6700E-03, 2.5800E-03, 
            1.9000E-03, 5.0000E-04, 1.2000E-04, 8.5000E-06, 9.9000E-07, 
            3.6000E-08, 4.9000E-10} );

    subshell_half_profiles[13] = 
      std::vector<double>( {2.0800E-01, 2.0800E-01, 2.0800E-01, 2.0800E-01, 
            2.0800E-01, 2.0800E-01, 2.0800E-01, 2.0800E-01, 2.0700E-01, 
            2.0600E-01, 2.0400E-01, 1.9800E-01, 1.8700E-01, 1.7300E-01, 
            1.5600E-01, 1.3700E-01, 1.1800E-01, 8.3100E-02, 4.4500E-02, 
            1.3300E-02, 4.3800E-03, 2.7700E-03, 2.6800E-03, 2.5700E-03, 
            1.9000E-03, 4.7000E-04, 1.1000E-04, 7.7000E-06, 8.6000E-07, 
            2.9000E-08, 3.2000E-10} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.2400E+00, 1.2200E+00, 1.1600E+00, 1.0700E+00, 
            9.6100E-01, 7.0600E-01, 4.6700E-01, 2.8300E-01, 1.6200E-01, 
            9.1900E-02, 5.6800E-02, 3.7400E-02, 3.6500E-02, 3.4100E-02, 
            2.8400E-02, 2.1500E-02, 1.5200E-02, 6.7600E-03, 2.4600E-03, 
            1.9700E-03, 1.4500E-03, 7.3400E-04, 3.1900E-04, 1.7100E-04, 
            1.4000E-04, 5.6000E-05, 1.0000E-05, 3.9000E-06, 2.7000E-06, 
            7.7000E-07, 8.2000E-08} );

    subshell_half_profiles[15] = 
      std::vector<double>( {9.6200E-01, 9.6100E-01, 9.5800E-01, 9.4400E-01, 
            9.1400E-01, 7.9200E-01, 6.1400E-01, 4.3000E-01, 2.7900E-01, 
            1.7000E-01, 9.9900E-02, 3.2600E-02, 1.2600E-02, 8.2400E-03, 
            7.7900E-03, 7.7000E-03, 7.1900E-03, 5.2600E-03, 2.4800E-03, 
            5.9400E-04, 3.5900E-04, 3.4700E-04, 2.7900E-04, 1.8700E-04, 
            6.2000E-05, 1.6000E-05, 1.3000E-05, 3.9000E-06, 9.8000E-07, 
            9.8000E-08, 4.2000E-09} );
  }
};

//! The default Compton profile generator implementation for A=50
template<>
struct DefaultComptonProfileGeneratorImpl<50u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 16 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.6300E-02, 1.6300E-02, 1.6300E-02, 1.6300E-02, 
            1.6300E-02, 1.6300E-02, 1.6300E-02, 1.6300E-02, 1.6300E-02, 
            1.6300E-02, 1.6300E-02, 1.6300E-02, 1.6300E-02, 1.6300E-02, 
            1.6300E-02, 1.6200E-02, 1.6200E-02, 1.6200E-02, 1.6100E-02, 
            1.6000E-02, 1.5800E-02, 1.5600E-02, 1.5400E-02, 1.5200E-02, 
            1.5000E-02, 1.3000E-02, 1.1000E-02, 6.8000E-03, 4.0000E-03, 
            1.3000E-03, 2.0000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {5.8600E-02, 5.8600E-02, 5.8600E-02, 5.8600E-02, 
            5.8600E-02, 5.8500E-02, 5.8500E-02, 5.8400E-02, 5.8300E-02, 
            5.8200E-02, 5.8100E-02, 5.7800E-02, 5.7400E-02, 5.7000E-02, 
            5.6500E-02, 5.6000E-02, 5.5400E-02, 5.4100E-02, 5.1700E-02, 
            4.6900E-02, 4.1500E-02, 3.5800E-02, 3.0200E-02, 2.4900E-02, 
            1.6000E-02, 4.2000E-03, 1.6000E-03, 1.4000E-03, 9.1000E-04, 
            2.7000E-04, 3.1000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.9200E-02, 2.9200E-02, 2.9200E-02, 2.9200E-02, 
            2.9200E-02, 2.9200E-02, 2.9200E-02, 2.9200E-02, 2.9200E-02, 
            2.9200E-02, 2.9200E-02, 2.9200E-02, 2.9200E-02, 2.9200E-02, 
            2.9200E-02, 2.9200E-02, 2.9200E-02, 2.9100E-02, 2.9100E-02, 
            2.8900E-02, 2.8600E-02, 2.8000E-02, 2.7200E-02, 2.6200E-02, 
            2.4000E-02, 1.5000E-02, 8.6000E-03, 2.3000E-03, 6.2000E-04, 
            6.8000E-05, 3.2000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 
            3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 
            3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 
            3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0300E-02, 
            3.0100E-02, 2.9700E-02, 2.9100E-02, 2.8200E-02, 2.7000E-02, 
            2.4000E-02, 1.5000E-02, 8.0000E-03, 1.9000E-03, 4.8000E-04, 
            4.5000E-05, 1.5000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.3700E-01, 1.3700E-01, 1.3700E-01, 1.3700E-01, 
            1.3600E-01, 1.3600E-01, 1.3500E-01, 1.3400E-01, 1.3300E-01, 
            1.3100E-01, 1.2900E-01, 1.2500E-01, 1.2100E-01, 1.1500E-01, 
            1.0900E-01, 1.0300E-01, 9.6400E-02, 8.2900E-02, 6.3100E-02, 
            3.6300E-02, 1.9800E-02, 1.2100E-02, 9.6200E-03, 9.2600E-03, 
            8.7000E-03, 3.1000E-03, 6.1000E-04, 2.7000E-04, 2.0000E-04, 
            5.7000E-05, 6.4000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {8.1400E-02, 8.1400E-02, 8.1400E-02, 8.1400E-02, 
            8.1400E-02, 8.1400E-02, 8.1400E-02, 8.1400E-02, 8.1400E-02, 
            8.1300E-02, 8.1300E-02, 8.1200E-02, 8.1100E-02, 8.0800E-02, 
            8.0400E-02, 7.9800E-02, 7.9100E-02, 7.7100E-02, 7.2400E-02, 
            6.0700E-02, 4.6300E-02, 3.2300E-02, 2.0900E-02, 1.2800E-02, 
            4.8000E-03, 2.6000E-03, 2.0000E-03, 5.9000E-04, 1.6000E-04, 
            1.6000E-05, 7.1000E-07} );

    subshell_half_profiles[6] = 
      std::vector<double>( {8.3900E-02, 8.3900E-02, 8.3900E-02, 8.3900E-02, 
            8.3900E-02, 8.3900E-02, 8.3900E-02, 8.3800E-02, 8.3800E-02, 
            8.3800E-02, 8.3800E-02, 8.3700E-02, 8.3500E-02, 8.3200E-02, 
            8.2700E-02, 8.2100E-02, 8.1200E-02, 7.8900E-02, 7.3700E-02, 
            6.0800E-02, 4.5400E-02, 3.0800E-02, 1.9400E-02, 1.1600E-02, 
            4.4000E-03, 2.7000E-03, 2.0000E-03, 5.2000E-04, 1.2000E-04, 
            1.1000E-05, 3.4000E-07} );

    subshell_half_profiles[7] = 
      std::vector<double>( {5.6300E-02, 5.6300E-02, 5.6300E-02, 5.6300E-02, 
            5.6300E-02, 5.6300E-02, 5.6300E-02, 5.6300E-02, 5.6300E-02, 
            5.6300E-02, 5.6300E-02, 5.6300E-02, 5.6300E-02, 5.6300E-02, 
            5.6300E-02, 5.6200E-02, 5.6200E-02, 5.6000E-02, 5.5400E-02, 
            5.3100E-02, 4.8800E-02, 4.2800E-02, 3.5900E-02, 2.9100E-02, 
            1.8000E-02, 4.2000E-03, 9.9000E-04, 7.6000E-05, 9.1000E-06, 
            3.4000E-07, 4.7000E-09} );

    subshell_half_profiles[8] = 
      std::vector<double>( {5.6900E-02, 5.6900E-02, 5.6900E-02, 5.6900E-02, 
            5.6900E-02, 5.6900E-02, 5.6900E-02, 5.6900E-02, 5.6900E-02, 
            5.6900E-02, 5.6900E-02, 5.6900E-02, 5.6800E-02, 5.6800E-02, 
            5.6800E-02, 5.6800E-02, 5.6700E-02, 5.6600E-02, 5.6000E-02, 
            5.3600E-02, 4.9100E-02, 4.2900E-02, 3.5800E-02, 2.8900E-02, 
            1.7000E-02, 4.0000E-03, 9.3000E-04, 6.9000E-05, 7.9000E-06, 
            2.7000E-07, 3.0000E-09} );

    subshell_half_profiles[9] = 
      std::vector<double>( {3.2200E-01, 3.2200E-01, 3.2000E-01, 3.1800E-01, 
            3.1600E-01, 3.0800E-01, 2.9700E-01, 2.8300E-01, 2.6800E-01, 
            2.5100E-01, 2.3300E-01, 1.9500E-01, 1.5700E-01, 1.2300E-01, 
            9.4100E-02, 7.0700E-02, 5.3100E-02, 3.2700E-02, 2.4500E-02, 
            2.3100E-02, 1.5900E-02, 8.1800E-03, 3.7800E-03, 2.1600E-03, 
            1.8000E-03, 7.8000E-04, 1.5000E-04, 5.1000E-05, 3.8000E-05, 
            1.1000E-05, 1.2000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {2.0900E-01, 2.0900E-01, 2.0900E-01, 2.0900E-01, 
            2.0900E-01, 2.0900E-01, 2.0800E-01, 2.0800E-01, 2.0700E-01, 
            2.0500E-01, 2.0200E-01, 1.9400E-01, 1.8300E-01, 1.6800E-01, 
            1.5000E-01, 1.3100E-01, 1.1100E-01, 7.5300E-02, 3.6600E-02, 
            1.1800E-02, 8.9500E-03, 8.6000E-03, 6.9100E-03, 4.7000E-03, 
            1.6000E-03, 4.1000E-04, 3.5000E-04, 1.1000E-04, 2.8000E-05, 
            2.9000E-06, 1.2000E-07} );

    subshell_half_profiles[11] = 
      std::vector<double>( {2.1600E-01, 2.1600E-01, 2.1600E-01, 2.1600E-01, 
            2.1600E-01, 2.1600E-01, 2.1600E-01, 2.1500E-01, 2.1300E-01, 
            2.1100E-01, 2.0800E-01, 1.9900E-01, 1.8600E-01, 1.6900E-01, 
            1.5000E-01, 1.2900E-01, 1.0800E-01, 7.1200E-02, 3.3300E-02, 
            1.1200E-02, 9.1900E-03, 8.6200E-03, 6.6100E-03, 4.3000E-03, 
            1.4000E-03, 4.4000E-04, 3.5000E-04, 9.4000E-05, 2.2000E-05, 
            1.9000E-06, 6.0000E-08} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.9200E-01, 1.9200E-01, 1.9200E-01, 1.9200E-01, 
            1.9200E-01, 1.9200E-01, 1.9200E-01, 1.9100E-01, 1.9100E-01, 
            1.9000E-01, 1.8900E-01, 1.8500E-01, 1.7800E-01, 1.6700E-01, 
            1.5400E-01, 1.3900E-01, 1.2300E-01, 9.1300E-02, 5.2500E-02, 
            1.7200E-02, 5.6300E-03, 3.0400E-03, 2.7900E-03, 2.7400E-03, 
            2.1000E-03, 5.9000E-04, 1.4000E-04, 1.1000E-05, 1.3000E-06, 
            4.8000E-08, 6.6000E-10} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.9300E-01, 1.9300E-01, 1.9300E-01, 1.9300E-01, 
            1.9300E-01, 1.9300E-01, 1.9300E-01, 1.9300E-01, 1.9200E-01, 
            1.9200E-01, 1.9100E-01, 1.8700E-01, 1.7900E-01, 1.6900E-01, 
            1.5500E-01, 1.4000E-01, 1.2300E-01, 9.0800E-02, 5.1500E-02, 
            1.6600E-02, 5.4200E-03, 3.0200E-03, 2.8100E-03, 2.7500E-03, 
            2.1000E-03, 5.7000E-04, 1.4000E-04, 9.9000E-06, 1.1000E-06, 
            3.8000E-08, 4.2000E-10} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.1000E+00, 1.0900E+00, 1.0500E+00, 9.8100E-01, 
            8.9700E-01, 6.9700E-01, 4.9500E-01, 3.2600E-01, 2.0200E-01, 
            1.2200E-01, 7.5400E-02, 4.2400E-02, 3.8900E-02, 3.8000E-02, 
            3.3800E-02, 2.7200E-02, 2.0200E-02, 9.6500E-03, 3.2800E-03, 
            2.3000E-03, 1.8300E-03, 9.9100E-04, 4.4400E-04, 2.2300E-04, 
            1.6000E-04, 7.4000E-05, 1.4000E-05, 4.6000E-06, 3.4000E-06, 
            1.0000E-06, 1.1000E-07} );

    subshell_half_profiles[15] = 
      std::vector<double>( {8.3600E-01, 8.3600E-01, 8.3400E-01, 8.2700E-01, 
            8.1000E-01, 7.3600E-01, 6.1400E-01, 4.7200E-01, 3.3700E-01, 
            2.2800E-01, 1.4800E-01, 5.6700E-02, 2.2200E-02, 1.1700E-02, 
            9.6300E-03, 9.5000E-03, 9.2900E-03, 7.4800E-03, 3.9000E-03, 
            9.5300E-04, 4.8100E-04, 4.6500E-04, 3.9500E-04, 2.7800E-04, 
            9.8000E-05, 2.2000E-05, 1.9000E-05, 5.8000E-06, 1.5000E-06, 
            1.5000E-07, 6.7000E-09} );
  }
};

//! The default Compton profile generator implementation for A=51
template<>
struct DefaultComptonProfileGeneratorImpl<51u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 17 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.5900E-02, 1.5900E-02, 1.5900E-02, 1.5900E-02, 
            1.5900E-02, 1.5900E-02, 1.5900E-02, 1.5900E-02, 1.5900E-02, 
            1.5900E-02, 1.5900E-02, 1.5900E-02, 1.5900E-02, 1.5900E-02, 
            1.5900E-02, 1.5900E-02, 1.5900E-02, 1.5800E-02, 1.5800E-02, 
            1.5700E-02, 1.5500E-02, 1.5300E-02, 1.5100E-02, 1.4900E-02, 
            1.4000E-02, 1.3000E-02, 1.1000E-02, 6.8000E-03, 4.1000E-03, 
            1.4000E-03, 2.1000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {5.7200E-02, 5.7200E-02, 5.7200E-02, 5.7200E-02, 
            5.7200E-02, 5.7200E-02, 5.7100E-02, 5.7100E-02, 5.7000E-02, 
            5.6900E-02, 5.6800E-02, 5.6500E-02, 5.6200E-02, 5.5800E-02, 
            5.5300E-02, 5.4800E-02, 5.4300E-02, 5.3000E-02, 5.0800E-02, 
            4.6300E-02, 4.1200E-02, 3.5800E-02, 3.0400E-02, 2.5200E-02, 
            1.6000E-02, 4.5000E-03, 1.6000E-03, 1.3000E-03, 9.3000E-04, 
            2.9000E-04, 3.4000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.8500E-02, 2.8500E-02, 2.8500E-02, 2.8500E-02, 
            2.8500E-02, 2.8500E-02, 2.8500E-02, 2.8500E-02, 2.8500E-02, 
            2.8500E-02, 2.8500E-02, 2.8500E-02, 2.8500E-02, 2.8500E-02, 
            2.8500E-02, 2.8500E-02, 2.8500E-02, 2.8400E-02, 2.8400E-02, 
            2.8200E-02, 2.7900E-02, 2.7400E-02, 2.6700E-02, 2.5800E-02, 
            2.3000E-02, 1.6000E-02, 8.9000E-03, 2.4000E-03, 6.8000E-04, 
            7.7000E-05, 3.7000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.9800E-02, 2.9800E-02, 2.9800E-02, 2.9800E-02, 
            2.9800E-02, 2.9800E-02, 2.9800E-02, 2.9800E-02, 2.9800E-02, 
            2.9800E-02, 2.9800E-02, 2.9800E-02, 2.9800E-02, 2.9800E-02, 
            2.9800E-02, 2.9800E-02, 2.9700E-02, 2.9700E-02, 2.9700E-02, 
            2.9500E-02, 2.9100E-02, 2.8500E-02, 2.7700E-02, 2.6600E-02, 
            2.4000E-02, 1.5000E-02, 8.3000E-03, 2.1000E-03, 5.3000E-04, 
            5.1000E-05, 1.7000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 
            1.3300E-01, 1.3200E-01, 1.3100E-01, 1.3000E-01, 1.2900E-01, 
            1.2800E-01, 1.2600E-01, 1.2200E-01, 1.1800E-01, 1.1300E-01, 
            1.0700E-01, 1.0200E-01, 9.5500E-02, 8.2700E-02, 6.3800E-02, 
            3.7600E-02, 2.0800E-02, 1.2500E-02, 9.6400E-03, 9.0900E-03, 
            8.7000E-03, 3.3000E-03, 7.0000E-04, 2.7000E-04, 2.0000E-04, 
            6.2000E-05, 7.1000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {7.9100E-02, 7.9100E-02, 7.9100E-02, 7.9100E-02, 
            7.9100E-02, 7.9100E-02, 7.9100E-02, 7.9100E-02, 7.9100E-02, 
            7.9100E-02, 7.9000E-02, 7.9000E-02, 7.8800E-02, 7.8600E-02, 
            7.8200E-02, 7.7700E-02, 7.7100E-02, 7.5300E-02, 7.1100E-02, 
            6.0500E-02, 4.7000E-02, 3.3500E-02, 2.2200E-02, 1.3900E-02, 
            5.3000E-03, 2.5000E-03, 2.1000E-03, 6.4000E-04, 1.7000E-04, 
            1.8000E-05, 8.3000E-07} );

    subshell_half_profiles[6] = 
      std::vector<double>( {8.1600E-02, 8.1600E-02, 8.1600E-02, 8.1600E-02, 
            8.1600E-02, 8.1600E-02, 8.1600E-02, 8.1600E-02, 8.1600E-02, 
            8.1500E-02, 8.1500E-02, 8.1400E-02, 8.1200E-02, 8.1000E-02, 
            8.0600E-02, 8.0000E-02, 7.9300E-02, 7.7200E-02, 7.2500E-02, 
            6.0700E-02, 4.6100E-02, 3.2100E-02, 2.0700E-02, 1.2600E-02, 
            4.8000E-03, 2.7000E-03, 2.0000E-03, 5.7000E-04, 1.4000E-04, 
            1.2000E-05, 4.0000E-07} );

    subshell_half_profiles[7] = 
      std::vector<double>( {5.4600E-02, 5.4600E-02, 5.4600E-02, 5.4600E-02, 
            5.4600E-02, 5.4600E-02, 5.4600E-02, 5.4600E-02, 5.4600E-02, 
            5.4600E-02, 5.4600E-02, 5.4600E-02, 5.4600E-02, 5.4600E-02, 
            5.4600E-02, 5.4600E-02, 5.4500E-02, 5.4400E-02, 5.3900E-02, 
            5.2000E-02, 4.8200E-02, 4.2700E-02, 3.6300E-02, 2.9800E-02, 
            1.9000E-02, 4.6000E-03, 1.1000E-03, 8.9000E-05, 1.1000E-05, 
            4.2000E-07, 5.7000E-09} );

    subshell_half_profiles[8] = 
      std::vector<double>( {5.5200E-02, 5.5200E-02, 5.5200E-02, 5.5200E-02, 
            5.5200E-02, 5.5200E-02, 5.5200E-02, 5.5200E-02, 5.5200E-02, 
            5.5200E-02, 5.5200E-02, 5.5200E-02, 5.5200E-02, 5.5200E-02, 
            5.5200E-02, 5.5100E-02, 5.5100E-02, 5.4900E-02, 5.4400E-02, 
            5.2400E-02, 4.8400E-02, 4.2800E-02, 3.6300E-02, 2.9600E-02, 
            1.8000E-02, 4.4000E-03, 1.1000E-03, 8.1000E-05, 9.4000E-06, 
            3.3000E-07, 3.6000E-09} );

    subshell_half_profiles[9] = 
      std::vector<double>( {3.0900E-01, 3.0800E-01, 3.0700E-01, 3.0500E-01, 
            3.0300E-01, 2.9600E-01, 2.8600E-01, 2.7400E-01, 2.6100E-01, 
            2.4500E-01, 2.2900E-01, 1.9400E-01, 1.5900E-01, 1.2700E-01, 
            9.8200E-02, 7.4900E-02, 5.6800E-02, 3.4800E-02, 2.4500E-02, 
            2.3200E-02, 1.7000E-02, 9.2500E-03, 4.3700E-03, 2.3700E-03, 
            1.8000E-03, 8.7000E-04, 1.7000E-04, 5.2000E-05, 4.0000E-05, 
            1.2000E-05, 1.4000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {2.0000E-01, 2.0000E-01, 2.0000E-01, 2.0000E-01, 
            2.0000E-01, 2.0000E-01, 1.9900E-01, 1.9900E-01, 1.9800E-01, 
            1.9600E-01, 1.9400E-01, 1.8800E-01, 1.7800E-01, 1.6500E-01, 
            1.5000E-01, 1.3200E-01, 1.1500E-01, 8.0100E-02, 4.0900E-02, 
            1.3100E-02, 8.9700E-03, 8.7500E-03, 7.3500E-03, 5.2200E-03, 
            1.9000E-03, 4.2000E-04, 3.7000E-04, 1.2000E-04, 3.2000E-05, 
            3.4000E-06, 1.5000E-07} );

    subshell_half_profiles[11] = 
      std::vector<double>( {2.0700E-01, 2.0700E-01, 2.0700E-01, 2.0700E-01, 
            2.0700E-01, 2.0700E-01, 2.0600E-01, 2.0600E-01, 2.0400E-01, 
            2.0300E-01, 2.0000E-01, 1.9300E-01, 1.8200E-01, 1.6700E-01, 
            1.5000E-01, 1.3100E-01, 1.1200E-01, 7.6200E-02, 3.7400E-02, 
            1.2200E-02, 9.2100E-03, 8.8500E-03, 7.1000E-03, 4.8200E-03, 
            1.7000E-03, 4.4000E-04, 3.7000E-04, 1.1000E-04, 2.6000E-05, 
            2.3000E-06, 7.3000E-08} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.7900E-01, 1.7900E-01, 1.7900E-01, 1.7900E-01, 
            1.7900E-01, 1.7900E-01, 1.7900E-01, 1.7900E-01, 1.7900E-01, 
            1.7800E-01, 1.7800E-01, 1.7500E-01, 1.7000E-01, 1.6200E-01, 
            1.5200E-01, 1.4000E-01, 1.2600E-01, 9.7100E-02, 5.9000E-02, 
            2.1000E-02, 6.9600E-03, 3.3900E-03, 2.9000E-03, 2.8700E-03, 
            2.3000E-03, 7.0000E-04, 1.8000E-04, 1.4000E-05, 1.7000E-06, 
            6.3000E-08, 8.7000E-10} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.8100E-01, 1.8100E-01, 1.8100E-01, 1.8100E-01, 
            1.8100E-01, 1.8000E-01, 1.8000E-01, 1.8000E-01, 1.8000E-01, 
            1.8000E-01, 1.7900E-01, 1.7600E-01, 1.7100E-01, 1.6300E-01, 
            1.5300E-01, 1.4000E-01, 1.2600E-01, 9.6600E-02, 5.8000E-02, 
            2.0200E-02, 6.6700E-03, 3.3400E-03, 2.9200E-03, 2.8900E-03, 
            2.3000E-03, 6.8000E-04, 1.7000E-04, 1.3000E-05, 1.4000E-06, 
            5.0000E-08, 5.6000E-10} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.0000E+00, 9.9000E-01, 9.5800E-01, 9.0700E-01, 
            8.4100E-01, 6.7900E-01, 5.0800E-01, 3.5500E-01, 2.3400E-01, 
            1.4900E-01, 9.4700E-02, 4.8500E-02, 4.0400E-02, 4.0100E-02, 
            3.7500E-02, 3.1900E-02, 2.5000E-02, 1.2900E-02, 4.3300E-03, 
            2.5600E-03, 2.1800E-03, 1.2700E-03, 5.9200E-04, 2.8500E-04, 
            1.9000E-04, 9.4000E-05, 1.9000E-05, 5.3000E-06, 4.1000E-06, 
            1.2000E-06, 1.4000E-07} );

    subshell_half_profiles[15] = 
      std::vector<double>( {7.3700E-01, 7.3700E-01, 7.3600E-01, 7.3200E-01, 
            7.2300E-01, 6.7800E-01, 5.9600E-01, 4.8900E-01, 3.7700E-01, 
            2.7500E-01, 1.9200E-01, 8.4900E-02, 3.5600E-02, 1.7100E-02, 
            1.1900E-02, 1.1000E-02, 1.1000E-02, 9.6100E-03, 5.5800E-03, 
            1.4500E-03, 6.1700E-04, 5.7900E-04, 5.1700E-04, 3.8200E-04, 
            1.5000E-04, 2.8000E-05, 2.4000E-05, 8.1000E-06, 2.2000E-06, 
            2.3000E-07, 1.0000E-08} );

    subshell_half_profiles[16] = 
      std::vector<double>( {7.6400E-01, 7.6400E-01, 7.6300E-01, 7.5800E-01, 
            7.4700E-01, 6.9600E-01, 6.0400E-01, 4.8700E-01, 3.6700E-01, 
            2.6200E-01, 1.7800E-01, 7.4600E-02, 3.0300E-02, 1.5300E-02, 
            1.1600E-02, 1.1300E-02, 1.1100E-02, 9.2600E-03, 4.9700E-03, 
            1.2200E-03, 6.0000E-04, 5.7900E-04, 4.9200E-04, 3.4600E-04, 
            1.2000E-04, 2.8000E-05, 2.4000E-05, 6.9000E-06, 1.7000E-06, 
            1.5000E-07, 4.7000E-09} );
  }
};

//! The default Compton profile generator implementation for A=52
template<>
struct DefaultComptonProfileGeneratorImpl<52u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 17 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.5600E-02, 1.5600E-02, 1.5600E-02, 1.5600E-02, 
            1.5600E-02, 1.5600E-02, 1.5600E-02, 1.5600E-02, 1.5600E-02, 
            1.5600E-02, 1.5600E-02, 1.5600E-02, 1.5600E-02, 1.5600E-02, 
            1.5600E-02, 1.5500E-02, 1.5500E-02, 1.5500E-02, 1.5400E-02, 
            1.5300E-02, 1.5200E-02, 1.5000E-02, 1.4800E-02, 1.4600E-02, 
            1.4000E-02, 1.2000E-02, 1.0000E-02, 6.9000E-03, 4.2000E-03, 
            1.5000E-03, 2.3000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {5.5900E-02, 5.5900E-02, 5.5900E-02, 5.5900E-02, 
            5.5900E-02, 5.5900E-02, 5.5800E-02, 5.5800E-02, 5.5700E-02, 
            5.5600E-02, 5.5500E-02, 5.5200E-02, 5.4900E-02, 5.4600E-02, 
            5.4100E-02, 5.3700E-02, 5.3100E-02, 5.2000E-02, 4.9900E-02, 
            4.5700E-02, 4.0800E-02, 3.5700E-02, 3.0500E-02, 2.5500E-02, 
            1.7000E-02, 4.8000E-03, 1.7000E-03, 1.3000E-03, 9.6000E-04, 
            3.1000E-04, 3.8000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 
            2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 
            2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 
            2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7700E-02, 
            2.7600E-02, 2.7300E-02, 2.6900E-02, 2.6200E-02, 2.5400E-02, 
            2.3000E-02, 1.6000E-02, 9.2000E-03, 2.6000E-03, 7.4000E-04, 
            8.7000E-05, 4.2000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.9100E-02, 2.9100E-02, 2.9100E-02, 2.9100E-02, 
            2.9100E-02, 2.9100E-02, 2.9100E-02, 2.9100E-02, 2.9100E-02, 
            2.9100E-02, 2.9100E-02, 2.9100E-02, 2.9100E-02, 2.9100E-02, 
            2.9100E-02, 2.9100E-02, 2.9100E-02, 2.9100E-02, 2.9000E-02, 
            2.8900E-02, 2.8500E-02, 2.8000E-02, 2.7200E-02, 2.6300E-02, 
            2.4000E-02, 1.5000E-02, 8.6000E-03, 2.2000E-03, 5.8000E-04, 
            5.7000E-05, 2.0000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.3000E-01, 1.3000E-01, 1.2900E-01, 1.2900E-01, 
            1.2900E-01, 1.2900E-01, 1.2800E-01, 1.2700E-01, 1.2600E-01, 
            1.2500E-01, 1.2300E-01, 1.2000E-01, 1.1600E-01, 1.1100E-01, 
            1.0600E-01, 1.0000E-01, 9.4500E-02, 8.2400E-02, 6.4400E-02, 
            3.8800E-02, 2.1900E-02, 1.3100E-02, 9.7100E-03, 8.9500E-03, 
            8.7000E-03, 3.6000E-03, 7.9000E-04, 2.6000E-04, 2.1000E-04, 
            6.7000E-05, 7.8000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {7.6900E-02, 7.6900E-02, 7.6900E-02, 7.6900E-02, 
            7.6900E-02, 7.6900E-02, 7.6900E-02, 7.6900E-02, 7.6900E-02, 
            7.6900E-02, 7.6900E-02, 7.6800E-02, 7.6700E-02, 7.6500E-02, 
            7.6100E-02, 7.5700E-02, 7.5200E-02, 7.3600E-02, 6.9800E-02, 
            6.0100E-02, 4.7500E-02, 3.4600E-02, 2.3400E-02, 1.5000E-02, 
            5.8000E-03, 2.5000E-03, 2.1000E-03, 6.9000E-04, 1.9000E-04, 
            2.1000E-05, 9.7000E-07} );

    subshell_half_profiles[6] = 
      std::vector<double>( {7.9400E-02, 7.9400E-02, 7.9400E-02, 7.9400E-02, 
            7.9400E-02, 7.9400E-02, 7.9400E-02, 7.9400E-02, 7.9400E-02, 
            7.9400E-02, 7.9400E-02, 7.9300E-02, 7.9100E-02, 7.8900E-02, 
            7.8500E-02, 7.8000E-02, 7.7400E-02, 7.5500E-02, 7.1300E-02, 
            6.0400E-02, 4.6800E-02, 3.3200E-02, 2.1900E-02, 1.3600E-02, 
            5.2000E-03, 2.7000E-03, 2.1000E-03, 6.1000E-04, 1.6000E-04, 
            1.4000E-05, 4.6000E-07} );

    subshell_half_profiles[7] = 
      std::vector<double>( {5.3000E-02, 5.3000E-02, 5.3000E-02, 5.3000E-02, 
            5.3000E-02, 5.3000E-02, 5.3000E-02, 5.3000E-02, 5.3000E-02, 
            5.3000E-02, 5.3000E-02, 5.3000E-02, 5.3000E-02, 5.3000E-02, 
            5.3000E-02, 5.3000E-02, 5.3000E-02, 5.2800E-02, 5.2400E-02, 
            5.0800E-02, 4.7400E-02, 4.2500E-02, 3.6600E-02, 3.0400E-02, 
            1.9000E-02, 5.0000E-03, 1.3000E-03, 1.0000E-04, 1.3000E-05, 
            5.0000E-07, 7.0000E-09} );

    subshell_half_profiles[8] = 
      std::vector<double>( {5.3600E-02, 5.3600E-02, 5.3600E-02, 5.3600E-02, 
            5.3600E-02, 5.3600E-02, 5.3600E-02, 5.3600E-02, 5.3600E-02, 
            5.3600E-02, 5.3600E-02, 5.3600E-02, 5.3600E-02, 5.3600E-02, 
            5.3600E-02, 5.3600E-02, 5.3500E-02, 5.3400E-02, 5.3000E-02, 
            5.1200E-02, 4.7800E-02, 4.2700E-02, 3.6600E-02, 3.0200E-02, 
            1.9000E-02, 4.9000E-03, 1.2000E-03, 9.4000E-05, 1.1000E-05, 
            4.0000E-07, 4.4000E-09} );

    subshell_half_profiles[9] = 
      std::vector<double>( {2.9600E-01, 2.9600E-01, 2.9500E-01, 2.9300E-01, 
            2.9100E-01, 2.8500E-01, 2.7600E-01, 2.6600E-01, 2.5300E-01, 
            2.3900E-01, 2.2400E-01, 1.9200E-01, 1.6000E-01, 1.2900E-01, 
            1.0200E-01, 7.8800E-02, 6.0500E-02, 3.7000E-02, 2.4700E-02, 
            2.3200E-02, 1.8000E-02, 1.0300E-02, 5.0300E-03, 2.6300E-03, 
            1.8000E-03, 9.7000E-04, 2.1000E-04, 5.2000E-05, 4.2000E-05, 
            1.4000E-05, 1.6000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.9100E-01, 1.9100E-01, 1.9100E-01, 1.9100E-01, 
            1.9100E-01, 1.9100E-01, 1.9100E-01, 1.9100E-01, 1.9000E-01, 
            1.8900E-01, 1.8700E-01, 1.8100E-01, 1.7300E-01, 1.6200E-01, 
            1.4900E-01, 1.3300E-01, 1.1700E-01, 8.4300E-02, 4.5200E-02, 
            1.4600E-02, 9.0400E-03, 8.8300E-03, 7.7200E-03, 5.7200E-03, 
            2.3000E-03, 4.3000E-04, 3.8000E-04, 1.3000E-04, 3.7000E-05, 
            4.0000E-06, 1.8000E-07} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.9800E-01, 1.9800E-01, 1.9800E-01, 1.9800E-01, 
            1.9800E-01, 1.9800E-01, 1.9800E-01, 1.9700E-01, 1.9600E-01, 
            1.9500E-01, 1.9300E-01, 1.8600E-01, 1.7700E-01, 1.6400E-01, 
            1.4900E-01, 1.3200E-01, 1.1500E-01, 8.0700E-02, 4.1500E-02, 
            1.3400E-02, 9.2400E-03, 9.0100E-03, 7.5400E-03, 5.3300E-03, 
            2.0000E-03, 4.5000E-04, 3.9000E-04, 1.2000E-04, 3.0000E-05, 
            2.7000E-06, 8.7000E-08} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.6800E-01, 1.6800E-01, 1.6800E-01, 1.6800E-01, 
            1.6800E-01, 1.6800E-01, 1.6800E-01, 1.6800E-01, 1.6800E-01, 
            1.6800E-01, 1.6700E-01, 1.6600E-01, 1.6200E-01, 1.5600E-01, 
            1.4800E-01, 1.3800E-01, 1.2700E-01, 1.0100E-01, 6.4900E-02, 
            2.4900E-02, 8.5400E-03, 3.8200E-03, 3.0100E-03, 2.9700E-03, 
            2.5000E-03, 8.2000E-04, 2.1000E-04, 1.7000E-05, 2.1000E-06, 
            8.2000E-08, 1.1000E-09} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.7000E-01, 1.7000E-01, 1.7000E-01, 1.7000E-01, 
            1.7000E-01, 1.7000E-01, 1.7000E-01, 1.7000E-01, 1.7000E-01, 
            1.7000E-01, 1.6900E-01, 1.6700E-01, 1.6300E-01, 1.5800E-01, 
            1.4900E-01, 1.3900E-01, 1.2700E-01, 1.0100E-01, 6.3900E-02, 
            2.4000E-02, 8.1600E-03, 3.7400E-03, 3.0200E-03, 2.9900E-03, 
            2.5000E-03, 7.9000E-04, 2.0000E-04, 1.6000E-05, 1.8000E-06, 
            6.4000E-08, 7.2000E-10} );

    subshell_half_profiles[14] = 
      std::vector<double>( {9.2000E-01, 9.1100E-01, 8.8600E-01, 8.4500E-01, 
            7.9200E-01, 6.5900E-01, 5.1200E-01, 3.7400E-01, 2.5900E-01, 
            1.7300E-01, 1.1400E-01, 5.6000E-02, 4.2000E-02, 4.0900E-02, 
            3.9700E-02, 3.5500E-02, 2.9200E-02, 1.6400E-02, 5.6500E-03, 
            2.7700E-03, 2.5000E-03, 1.5600E-03, 7.6300E-04, 3.6100E-04, 
            2.1000E-04, 1.1000E-04, 2.4000E-05, 5.8000E-06, 4.7000E-06, 
            1.5000E-06, 1.8000E-07} );

    subshell_half_profiles[15] = 
      std::vector<double>( {6.6500E-01, 6.6500E-01, 6.6400E-01, 6.6200E-01, 
            6.5600E-01, 6.2600E-01, 5.6900E-01, 4.8900E-01, 3.9700E-01, 
            3.0700E-01, 2.2700E-01, 1.1300E-01, 5.1300E-02, 2.4300E-02, 
            1.4700E-02, 1.2300E-02, 1.2100E-02, 1.1300E-02, 7.3200E-03, 
            2.0800E-03, 7.7100E-04, 6.7800E-04, 6.3000E-04, 4.8900E-04, 
            2.0000E-04, 3.3000E-05, 3.0000E-05, 1.1000E-05, 2.9000E-06, 
            3.1000E-07, 1.4000E-08} );

    subshell_half_profiles[16] = 
      std::vector<double>( {6.9300E-01, 6.9300E-01, 6.9300E-01, 6.9000E-01, 
            6.8200E-01, 6.4700E-01, 5.8100E-01, 4.9000E-01, 3.9000E-01, 
            2.9400E-01, 2.1200E-01, 9.9800E-02, 4.3700E-02, 2.1000E-02, 
            1.3800E-02, 1.2400E-02, 1.2300E-02, 1.1100E-02, 6.6000E-03, 
            1.7300E-03, 7.2600E-04, 6.8000E-04, 6.0500E-04, 4.4600E-04, 
            1.7000E-04, 3.4000E-05, 2.9000E-05, 9.1000E-06, 2.3000E-06, 
            2.1000E-07, 6.6000E-09} );
  }
};

//! The default Compton profile generator implementation for A=53
template<>
struct DefaultComptonProfileGeneratorImpl<53u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 17 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.5300E-02, 1.5300E-02, 1.5300E-02, 1.5300E-02, 
            1.5300E-02, 1.5300E-02, 1.5300E-02, 1.5300E-02, 1.5300E-02, 
            1.5300E-02, 1.5300E-02, 1.5200E-02, 1.5200E-02, 1.5200E-02, 
            1.5200E-02, 1.5200E-02, 1.5200E-02, 1.5200E-02, 1.5100E-02, 
            1.5000E-02, 1.4900E-02, 1.4700E-02, 1.4500E-02, 1.4300E-02, 
            1.4000E-02, 1.2000E-02, 1.0000E-02, 6.9000E-03, 4.3000E-03, 
            1.5000E-03, 2.5000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {5.4700E-02, 5.4700E-02, 5.4700E-02, 5.4700E-02, 
            5.4700E-02, 5.4600E-02, 5.4600E-02, 5.4500E-02, 5.4400E-02, 
            5.4400E-02, 5.4300E-02, 5.4000E-02, 5.3700E-02, 5.3400E-02, 
            5.3000E-02, 5.2600E-02, 5.2100E-02, 5.1000E-02, 4.9000E-02, 
            4.5000E-02, 4.0500E-02, 3.5600E-02, 3.0600E-02, 2.5800E-02, 
            1.7000E-02, 5.1000E-03, 1.7000E-03, 1.3000E-03, 9.8000E-04, 
            3.3000E-04, 4.1000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.7200E-02, 2.7200E-02, 2.7200E-02, 2.7200E-02, 
            2.7200E-02, 2.7200E-02, 2.7200E-02, 2.7200E-02, 2.7200E-02, 
            2.7200E-02, 2.7200E-02, 2.7200E-02, 2.7200E-02, 2.7200E-02, 
            2.7200E-02, 2.7200E-02, 2.7100E-02, 2.7100E-02, 2.7100E-02, 
            2.7000E-02, 2.6700E-02, 2.6300E-02, 2.5700E-02, 2.5000E-02, 
            2.3000E-02, 1.6000E-02, 9.5000E-03, 2.8000E-03, 8.1000E-04, 
            9.8000E-05, 4.9000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.8500E-02, 2.8500E-02, 2.8500E-02, 2.8500E-02, 
            2.8500E-02, 2.8500E-02, 2.8500E-02, 2.8500E-02, 2.8500E-02, 
            2.8500E-02, 2.8500E-02, 2.8500E-02, 2.8500E-02, 2.8500E-02, 
            2.8500E-02, 2.8500E-02, 2.8500E-02, 2.8500E-02, 2.8400E-02, 
            2.8300E-02, 2.8000E-02, 2.7500E-02, 2.6800E-02, 2.5900E-02, 
            2.3000E-02, 1.6000E-02, 8.9000E-03, 2.4000E-03, 6.4000E-04, 
            6.4000E-05, 2.3000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.2600E-01, 1.2600E-01, 1.2600E-01, 1.2600E-01, 
            1.2600E-01, 1.2500E-01, 1.2500E-01, 1.2400E-01, 1.2300E-01, 
            1.2200E-01, 1.2000E-01, 1.1700E-01, 1.1300E-01, 1.0900E-01, 
            1.0400E-01, 9.8900E-02, 9.3400E-02, 8.2100E-02, 6.4900E-02, 
            4.0000E-02, 2.2900E-02, 1.3700E-02, 9.8300E-03, 8.8300E-03, 
            8.6000E-03, 3.9000E-03, 8.9000E-04, 2.6000E-04, 2.1000E-04, 
            7.2000E-05, 8.7000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {7.4800E-02, 7.4800E-02, 7.4800E-02, 7.4800E-02, 
            7.4800E-02, 7.4800E-02, 7.4800E-02, 7.4800E-02, 7.4800E-02, 
            7.4800E-02, 7.4800E-02, 7.4700E-02, 7.4600E-02, 7.4400E-02, 
            7.4200E-02, 7.3800E-02, 7.3300E-02, 7.1900E-02, 6.8500E-02, 
            5.9700E-02, 4.8000E-02, 3.5600E-02, 2.4600E-02, 1.6100E-02, 
            6.3000E-03, 2.5000E-03, 2.1000E-03, 7.5000E-04, 2.1000E-04, 
            2.4000E-05, 1.1000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {7.7400E-02, 7.7400E-02, 7.7400E-02, 7.7400E-02, 
            7.7400E-02, 7.7400E-02, 7.7400E-02, 7.7400E-02, 7.7400E-02, 
            7.7300E-02, 7.7300E-02, 7.7200E-02, 7.7100E-02, 7.6900E-02, 
            7.6600E-02, 7.6100E-02, 7.5600E-02, 7.3900E-02, 7.0100E-02, 
            6.0100E-02, 4.7300E-02, 3.4300E-02, 2.3100E-02, 1.4600E-02, 
            5.7000E-03, 2.6000E-03, 2.2000E-03, 6.6000E-04, 1.7000E-04, 
            1.6000E-05, 5.4000E-07} );

    subshell_half_profiles[7] = 
      std::vector<double>( {5.1500E-02, 5.1500E-02, 5.1500E-02, 5.1500E-02, 
            5.1500E-02, 5.1500E-02, 5.1500E-02, 5.1500E-02, 5.1500E-02, 
            5.1500E-02, 5.1500E-02, 5.1500E-02, 5.1500E-02, 5.1500E-02, 
            5.1500E-02, 5.1500E-02, 5.1500E-02, 5.1400E-02, 5.1100E-02, 
            4.9600E-02, 4.6700E-02, 4.2300E-02, 3.6800E-02, 3.0900E-02, 
            2.0000E-02, 5.5000E-03, 1.4000E-03, 1.2000E-04, 1.5000E-05, 
            6.1000E-07, 8.5000E-09} );

    subshell_half_profiles[8] = 
      std::vector<double>( {5.2100E-02, 5.2100E-02, 5.2100E-02, 5.2100E-02, 
            5.2100E-02, 5.2100E-02, 5.2100E-02, 5.2100E-02, 5.2100E-02, 
            5.2100E-02, 5.2100E-02, 5.2100E-02, 5.2100E-02, 5.2100E-02, 
            5.2100E-02, 5.2100E-02, 5.2100E-02, 5.2000E-02, 5.1600E-02, 
            5.0100E-02, 4.7000E-02, 4.2400E-02, 3.6800E-02, 3.0800E-02, 
            2.0000E-02, 5.3000E-03, 1.3000E-03, 1.1000E-04, 1.3000E-05, 
            4.8000E-07, 5.3000E-09} );

    subshell_half_profiles[9] = 
      std::vector<double>( {2.8500E-01, 2.8400E-01, 2.8400E-01, 2.8200E-01, 
            2.8000E-01, 2.7500E-01, 2.6700E-01, 2.5700E-01, 2.4600E-01, 
            2.3300E-01, 2.2000E-01, 1.9000E-01, 1.6000E-01, 1.3100E-01, 
            1.0500E-01, 8.2400E-02, 6.4000E-02, 3.9400E-02, 2.5100E-02, 
            2.3100E-02, 1.8800E-02, 1.1400E-02, 5.7600E-03, 2.9500E-03, 
            1.8000E-03, 1.1000E-03, 2.4000E-04, 5.3000E-05, 4.4000E-05, 
            1.5000E-05, 1.8000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.8400E-01, 1.8400E-01, 1.8400E-01, 1.8400E-01, 
            1.8400E-01, 1.8300E-01, 1.8300E-01, 1.8300E-01, 1.8200E-01, 
            1.8100E-01, 1.8000E-01, 1.7500E-01, 1.6800E-01, 1.5900E-01, 
            1.4700E-01, 1.3300E-01, 1.1800E-01, 8.7900E-02, 4.9300E-02, 
            1.6300E-02, 9.1900E-03, 8.8500E-03, 8.0300E-03, 6.1900E-03, 
            2.6000E-03, 4.4000E-04, 4.0000E-04, 1.5000E-04, 4.3000E-05, 
            4.7000E-06, 2.2000E-07} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.9000E-01, 1.9000E-01, 1.9000E-01, 1.9000E-01, 
            1.9000E-01, 1.9000E-01, 1.9000E-01, 1.8900E-01, 1.8800E-01, 
            1.8700E-01, 1.8600E-01, 1.8000E-01, 1.7200E-01, 1.6100E-01, 
            1.4800E-01, 1.3300E-01, 1.1700E-01, 8.4600E-02, 4.5600E-02, 
            1.4900E-02, 9.3200E-03, 9.1000E-03, 7.9300E-03, 5.8300E-03, 
            2.3000E-03, 4.6000E-04, 4.1000E-04, 1.3000E-04, 3.4000E-05, 
            3.2000E-06, 1.0000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.5900E-01, 1.5900E-01, 1.5900E-01, 1.5900E-01, 
            1.5900E-01, 1.5900E-01, 1.5900E-01, 1.5900E-01, 1.5900E-01, 
            1.5900E-01, 1.5900E-01, 1.5700E-01, 1.5500E-01, 1.5000E-01, 
            1.4400E-01, 1.3600E-01, 1.2600E-01, 1.0400E-01, 6.9900E-02, 
            2.8900E-02, 1.0300E-02, 4.3800E-03, 3.1300E-03, 3.0400E-03, 
            2.7000E-03, 9.5000E-04, 2.5000E-04, 2.1000E-05, 2.7000E-06, 
            1.0000E-07, 1.5000E-09} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.6100E-01, 1.6100E-01, 1.6100E-01, 1.6100E-01, 
            1.6100E-01, 1.6100E-01, 1.6100E-01, 1.6100E-01, 1.6100E-01, 
            1.6100E-01, 1.6000E-01, 1.5900E-01, 1.5600E-01, 1.5200E-01, 
            1.4500E-01, 1.3700E-01, 1.2700E-01, 1.0400E-01, 6.9000E-02, 
            2.7900E-02, 9.8700E-03, 4.2500E-03, 3.1400E-03, 3.0700E-03, 
            2.7000E-03, 9.1000E-04, 2.4000E-04, 1.9000E-05, 2.3000E-06, 
            8.2000E-08, 9.3000E-10} );

    subshell_half_profiles[14] = 
      std::vector<double>( {8.5300E-01, 8.4600E-01, 8.2600E-01, 7.9200E-01, 
            7.4800E-01, 6.3700E-01, 5.1000E-01, 3.8700E-01, 2.7900E-01, 
            1.9400E-01, 1.3100E-01, 6.4500E-02, 4.4100E-02, 4.1300E-02, 
            4.0900E-02, 3.8100E-02, 3.2700E-02, 1.9900E-02, 7.2500E-03, 
            2.9800E-03, 2.7700E-03, 1.8600E-03, 9.5800E-04, 4.5400E-04, 
            2.2000E-04, 1.4000E-04, 3.1000E-05, 6.3000E-06, 5.3000E-06, 
            1.8000E-06, 2.1000E-07} );

    subshell_half_profiles[15] = 
      std::vector<double>( {6.0800E-01, 6.0800E-01, 6.0800E-01, 6.0600E-01, 
            6.0200E-01, 5.8200E-01, 5.4100E-01, 4.7900E-01, 4.0500E-01, 
            3.2700E-01, 2.5400E-01, 1.3800E-01, 6.8300E-02, 3.3300E-02, 
            1.8700E-02, 1.3900E-02, 1.3000E-02, 1.2600E-02, 9.0200E-03, 
            2.8600E-03, 9.5800E-04, 7.6400E-04, 7.3400E-04, 5.9700E-04, 
            2.6000E-04, 3.9000E-05, 3.5000E-05, 1.3000E-05, 3.8000E-06, 
            4.2000E-07, 1.9000E-08} );

    subshell_half_profiles[16] = 
      std::vector<double>( {6.3700E-01, 6.3700E-01, 6.3700E-01, 6.3500E-01, 
            6.3000E-01, 6.0500E-01, 5.5600E-01, 4.8500E-01, 4.0100E-01, 
            3.1700E-01, 2.3900E-01, 1.2400E-01, 5.8400E-02, 2.8100E-02, 
            1.6700E-02, 1.3500E-02, 1.3100E-02, 1.2400E-02, 8.2300E-03, 
            2.3700E-03, 8.7200E-04, 7.6700E-04, 7.1100E-04, 5.4800E-04, 
            2.2000E-04, 3.9000E-05, 3.5000E-05, 1.1000E-05, 2.9000E-06, 
            2.7000E-07, 8.9000E-09} );
  }
};

//! The default Compton profile generator implementation for A=54
template<>
struct DefaultComptonProfileGeneratorImpl<54u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 17 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.4900E-02, 1.4900E-02, 1.4900E-02, 1.4900E-02, 
            1.4900E-02, 1.4900E-02, 1.4900E-02, 1.4900E-02, 1.4900E-02, 
            1.4900E-02, 1.4900E-02, 1.4900E-02, 1.4900E-02, 1.4900E-02, 
            1.4900E-02, 1.4900E-02, 1.4900E-02, 1.4900E-02, 1.4800E-02, 
            1.4700E-02, 1.4600E-02, 1.4400E-02, 1.4200E-02, 1.4000E-02, 
            1.4000E-02, 1.2000E-02, 1.0000E-02, 7.0000E-03, 4.4000E-03, 
            1.6000E-03, 2.7000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {5.3500E-02, 5.3500E-02, 5.3500E-02, 5.3500E-02, 
            5.3400E-02, 5.3400E-02, 5.3400E-02, 5.3300E-02, 5.3200E-02, 
            5.3200E-02, 5.3100E-02, 5.2800E-02, 5.2600E-02, 5.2300E-02, 
            5.1900E-02, 5.1500E-02, 5.1000E-02, 5.0000E-02, 4.8100E-02, 
            4.4400E-02, 4.0100E-02, 3.5400E-02, 3.0600E-02, 2.6000E-02, 
            1.8000E-02, 5.4000E-03, 1.8000E-03, 1.3000E-03, 9.9000E-04, 
            3.4000E-04, 4.5000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.6500E-02, 2.6500E-02, 2.6500E-02, 2.6500E-02, 
            2.6500E-02, 2.6500E-02, 2.6500E-02, 2.6500E-02, 2.6500E-02, 
            2.6500E-02, 2.6500E-02, 2.6500E-02, 2.6500E-02, 2.6500E-02, 
            2.6500E-02, 2.6500E-02, 2.6500E-02, 2.6500E-02, 2.6500E-02, 
            2.6400E-02, 2.6100E-02, 2.5800E-02, 2.5300E-02, 2.4500E-02, 
            2.3000E-02, 1.6000E-02, 9.7000E-03, 3.0000E-03, 8.9000E-04, 
            1.1000E-04, 5.6000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.7900E-02, 2.7900E-02, 2.7900E-02, 2.7900E-02, 
            2.7900E-02, 2.7900E-02, 2.7900E-02, 2.7900E-02, 2.7900E-02, 
            2.7900E-02, 2.7900E-02, 2.7900E-02, 2.7900E-02, 2.7900E-02, 
            2.7900E-02, 2.7900E-02, 2.7900E-02, 2.7900E-02, 2.7800E-02, 
            2.7700E-02, 2.7400E-02, 2.7000E-02, 2.6300E-02, 2.5500E-02, 
            2.3000E-02, 1.6000E-02, 9.2000E-03, 2.5000E-03, 6.9000E-04, 
            7.2000E-05, 2.6000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 
            1.2300E-01, 1.2200E-01, 1.2100E-01, 1.2100E-01, 1.2000E-01, 
            1.1900E-01, 1.1700E-01, 1.1400E-01, 1.1100E-01, 1.0700E-01, 
            1.0200E-01, 9.7500E-02, 9.2400E-02, 8.1600E-02, 6.5300E-02, 
            4.1100E-02, 2.4000E-02, 1.4300E-02, 1.0000E-02, 8.7400E-03, 
            8.5000E-03, 4.2000E-03, 1.0000E-03, 2.6000E-04, 2.2000E-04, 
            7.7000E-05, 9.5000E-06} );

    subshell_half_profiles[5] = 
      std::vector<double>( {7.2900E-02, 7.2900E-02, 7.2900E-02, 7.2900E-02, 
            7.2900E-02, 7.2900E-02, 7.2900E-02, 7.2900E-02, 7.2900E-02, 
            7.2800E-02, 7.2800E-02, 7.2800E-02, 7.2700E-02, 7.2500E-02, 
            7.2300E-02, 7.1900E-02, 7.1500E-02, 7.0200E-02, 6.7200E-02, 
            5.9200E-02, 4.8300E-02, 3.6500E-02, 2.5800E-02, 1.7200E-02, 
            6.9000E-03, 2.4000E-03, 2.2000E-03, 8.0000E-04, 2.4000E-04, 
            2.7000E-05, 1.3000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {7.5400E-02, 7.5400E-02, 7.5400E-02, 7.5400E-02, 
            7.5400E-02, 7.5400E-02, 7.5400E-02, 7.5400E-02, 7.5400E-02, 
            7.5400E-02, 7.5400E-02, 7.5300E-02, 7.5200E-02, 7.5000E-02, 
            7.4700E-02, 7.4300E-02, 7.3800E-02, 7.2300E-02, 6.8900E-02, 
            5.9800E-02, 4.7800E-02, 3.5200E-02, 2.4200E-02, 1.5700E-02, 
            6.2000E-03, 2.6000E-03, 2.2000E-03, 7.1000E-04, 1.9000E-04, 
            1.8000E-05, 6.2000E-07} );

    subshell_half_profiles[7] = 
      std::vector<double>( {5.0100E-02, 5.0100E-02, 5.0100E-02, 5.0100E-02, 
            5.0100E-02, 5.0100E-02, 5.0100E-02, 5.0100E-02, 5.0100E-02, 
            5.0100E-02, 5.0100E-02, 5.0100E-02, 5.0100E-02, 5.0100E-02, 
            5.0100E-02, 5.0100E-02, 5.0100E-02, 5.0000E-02, 4.9700E-02, 
            4.8500E-02, 4.5900E-02, 4.1900E-02, 3.6900E-02, 3.1400E-02, 
            2.1000E-02, 6.0000E-03, 1.6000E-03, 1.4000E-04, 1.8000E-05, 
            7.3000E-07, 1.0000E-08} );

    subshell_half_profiles[8] = 
      std::vector<double>( {5.0700E-02, 5.0700E-02, 5.0700E-02, 5.0700E-02, 
            5.0700E-02, 5.0700E-02, 5.0700E-02, 5.0700E-02, 5.0700E-02, 
            5.0700E-02, 5.0700E-02, 5.0700E-02, 5.0700E-02, 5.0700E-02, 
            5.0700E-02, 5.0700E-02, 5.0700E-02, 5.0600E-02, 5.0300E-02, 
            4.9000E-02, 4.6300E-02, 4.2100E-02, 3.6900E-02, 3.1300E-02, 
            2.1000E-02, 5.7000E-03, 1.5000E-03, 1.3000E-04, 1.5000E-05, 
            5.7000E-07, 6.4000E-09} );

    subshell_half_profiles[9] = 
      std::vector<double>( {2.7400E-01, 2.7400E-01, 2.7300E-01, 2.7200E-01, 
            2.7000E-01, 2.6500E-01, 2.5800E-01, 2.4900E-01, 2.3900E-01, 
            2.2800E-01, 2.1500E-01, 1.8800E-01, 1.6000E-01, 1.3300E-01, 
            1.0800E-01, 8.5700E-02, 6.7300E-02, 4.1800E-02, 2.5600E-02, 
            2.2800E-02, 1.9500E-02, 1.2500E-02, 6.5500E-03, 3.3300E-03, 
            1.9000E-03, 1.2000E-03, 2.8000E-04, 5.3000E-05, 4.6000E-05, 
            1.6000E-05, 2.0000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.7600E-01, 1.7600E-01, 1.7600E-01, 1.7600E-01, 
            1.7600E-01, 1.7600E-01, 1.7600E-01, 1.7600E-01, 1.7500E-01, 
            1.7500E-01, 1.7300E-01, 1.7000E-01, 1.6400E-01, 1.5500E-01, 
            1.4500E-01, 1.3300E-01, 1.1900E-01, 9.0900E-02, 5.3200E-02, 
            1.8300E-02, 9.4400E-03, 8.8200E-03, 8.2600E-03, 6.6200E-03, 
            3.0000E-03, 4.6000E-04, 4.1000E-04, 1.6000E-04, 4.8000E-05, 
            5.5000E-06, 2.6000E-07} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.8200E-01, 1.8200E-01, 1.8200E-01, 1.8200E-01, 
            1.8200E-01, 1.8200E-01, 1.8200E-01, 1.8200E-01, 1.8100E-01, 
            1.8000E-01, 1.7900E-01, 1.7400E-01, 1.6800E-01, 1.5800E-01, 
            1.4600E-01, 1.3300E-01, 1.1800E-01, 8.8000E-02, 4.9600E-02, 
            1.6600E-02, 9.4700E-03, 9.1500E-03, 8.2500E-03, 6.3100E-03, 
            2.6000E-03, 4.7000E-04, 4.3000E-04, 1.5000E-04, 3.9000E-05, 
            3.7000E-06, 1.2000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.5100E-01, 1.5100E-01, 1.5100E-01, 1.5100E-01, 
            1.5100E-01, 1.5100E-01, 1.5100E-01, 1.5100E-01, 1.5100E-01, 
            1.5100E-01, 1.5100E-01, 1.5000E-01, 1.4800E-01, 1.4500E-01, 
            1.4000E-01, 1.3300E-01, 1.2500E-01, 1.0600E-01, 7.4200E-02, 
            3.2900E-02, 1.2400E-02, 5.0700E-03, 3.3000E-03, 3.1000E-03, 
            2.9000E-03, 1.1000E-03, 3.0000E-04, 2.6000E-05, 3.3000E-06, 
            1.3000E-07, 1.9000E-09} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5300E-01, 
            1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5300E-01, 
            1.5300E-01, 1.5200E-01, 1.5100E-01, 1.4900E-01, 1.4600E-01, 
            1.4100E-01, 1.3400E-01, 1.2600E-01, 1.0600E-01, 7.3300E-02, 
            3.1900E-02, 1.1800E-02, 4.8800E-03, 3.2800E-03, 3.1200E-03, 
            2.9000E-03, 1.0000E-03, 2.8000E-04, 2.4000E-05, 2.9000E-06, 
            1.0000E-07, 1.2000E-09} );

    subshell_half_profiles[14] = 
      std::vector<double>( {7.9700E-01, 7.9100E-01, 7.7400E-01, 7.4700E-01, 
            7.1000E-01, 6.1500E-01, 5.0500E-01, 3.9400E-01, 2.9400E-01, 
            2.1100E-01, 1.4800E-01, 7.3800E-02, 4.7000E-02, 4.1500E-02, 
            4.1200E-02, 3.9600E-02, 3.5400E-02, 2.3300E-02, 9.1100E-03, 
            3.1900E-03, 3.0000E-03, 2.1600E-03, 1.1700E-03, 5.6500E-04, 
            2.4000E-04, 1.6000E-04, 3.9000E-05, 6.8000E-06, 5.9000E-06, 
            2.1000E-06, 2.6000E-07} );

    subshell_half_profiles[15] = 
      std::vector<double>( {5.6200E-01, 5.6200E-01, 5.6100E-01, 5.6000E-01, 
            5.5800E-01, 5.4300E-01, 5.1300E-01, 4.6600E-01, 4.0600E-01, 
            3.3900E-01, 2.7300E-01, 1.6000E-01, 8.5500E-02, 4.3600E-02, 
            2.3700E-02, 1.6000E-02, 1.3800E-02, 1.3500E-02, 1.0600E-02, 
            3.7600E-03, 1.2000E-03, 8.4300E-04, 8.2400E-04, 7.0100E-04, 
            3.3000E-04, 4.5000E-05, 4.0000E-05, 1.6000E-05, 4.8000E-06, 
            5.4000E-07, 2.5000E-08} );

    subshell_half_profiles[16] = 
      std::vector<double>( {5.9200E-01, 5.9200E-01, 5.9100E-01, 5.9000E-01, 
            5.8600E-01, 5.6800E-01, 5.3100E-01, 4.7500E-01, 4.0500E-01, 
            3.3100E-01, 2.6000E-01, 1.4500E-01, 7.3700E-02, 3.6600E-02, 
            2.0400E-02, 1.4800E-02, 1.3600E-02, 1.3300E-02, 9.7200E-03, 
            3.1200E-03, 1.0400E-03, 8.3600E-04, 8.0000E-04, 6.4500E-04, 
            2.8000E-04, 4.4000E-05, 4.0000E-05, 1.4000E-05, 3.6000E-06, 
            3.5000E-07, 1.2000E-08} );
  }
};

//! The default Compton profile generator implementation for A=55
template<>
struct DefaultComptonProfileGeneratorImpl<55u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 18 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.4600E-02, 1.4600E-02, 1.4600E-02, 1.4600E-02, 
            1.4600E-02, 1.4600E-02, 1.4600E-02, 1.4600E-02, 1.4600E-02, 
            1.4600E-02, 1.4600E-02, 1.4600E-02, 1.4600E-02, 1.4600E-02, 
            1.4600E-02, 1.4600E-02, 1.4600E-02, 1.4500E-02, 1.4500E-02, 
            1.4400E-02, 1.4300E-02, 1.4100E-02, 1.4000E-02, 1.3800E-02, 
            1.3000E-02, 1.2000E-02, 1.0000E-02, 7.0000E-03, 4.5000E-03, 
            1.7000E-03, 2.9000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {5.2300E-02, 5.2300E-02, 5.2300E-02, 5.2300E-02, 
            5.2300E-02, 5.2200E-02, 5.2200E-02, 5.2200E-02, 5.2100E-02, 
            5.2000E-02, 5.1900E-02, 5.1700E-02, 5.1500E-02, 5.1200E-02, 
            5.0800E-02, 5.0400E-02, 5.0000E-02, 4.9000E-02, 4.7300E-02, 
            4.3800E-02, 3.9700E-02, 3.5200E-02, 3.0700E-02, 2.6200E-02, 
            1.8000E-02, 5.8000E-03, 1.9000E-03, 1.3000E-03, 1.0000E-03, 
            3.6000E-04, 4.9000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.5900E-02, 2.5900E-02, 2.5900E-02, 2.5900E-02, 
            2.5900E-02, 2.5900E-02, 2.5900E-02, 2.5900E-02, 2.5900E-02, 
            2.5900E-02, 2.5900E-02, 2.5900E-02, 2.5900E-02, 2.5900E-02, 
            2.5900E-02, 2.5900E-02, 2.5900E-02, 2.5900E-02, 2.5900E-02, 
            2.5800E-02, 2.5600E-02, 2.5300E-02, 2.4800E-02, 2.4100E-02, 
            2.2000E-02, 1.6000E-02, 1.0000E-02, 3.1000E-03, 9.7000E-04, 
            1.2000E-04, 6.4000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.7300E-02, 2.7300E-02, 2.7300E-02, 2.7300E-02, 
            2.7300E-02, 2.7300E-02, 2.7300E-02, 2.7300E-02, 2.7300E-02, 
            2.7300E-02, 2.7300E-02, 2.7300E-02, 2.7300E-02, 2.7300E-02, 
            2.7300E-02, 2.7300E-02, 2.7300E-02, 2.7300E-02, 2.7300E-02, 
            2.7100E-02, 2.6900E-02, 2.6500E-02, 2.5900E-02, 2.5100E-02, 
            2.3000E-02, 1.6000E-02, 9.4000E-03, 2.7000E-03, 7.5000E-04, 
            7.9000E-05, 2.9000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.2000E-01, 1.2000E-01, 1.2000E-01, 1.2000E-01, 
            1.1900E-01, 1.1900E-01, 1.1800E-01, 1.1800E-01, 1.1700E-01, 
            1.1600E-01, 1.1500E-01, 1.1200E-01, 1.0900E-01, 1.0500E-01, 
            1.0100E-01, 9.6100E-02, 9.1300E-02, 8.1100E-02, 6.5500E-02, 
            4.2100E-02, 2.5000E-02, 1.4900E-02, 1.0200E-02, 8.6800E-03, 
            8.4000E-03, 4.4000E-03, 1.1000E-03, 2.5000E-04, 2.2000E-04, 
            8.2000E-05, 1.0000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {7.1000E-02, 7.1000E-02, 7.1000E-02, 7.1000E-02, 
            7.1000E-02, 7.1000E-02, 7.1000E-02, 7.1000E-02, 7.1000E-02, 
            7.1000E-02, 7.0900E-02, 7.0900E-02, 7.0800E-02, 7.0700E-02, 
            7.0500E-02, 7.0200E-02, 6.9800E-02, 6.8700E-02, 6.6000E-02, 
            5.8600E-02, 4.8500E-02, 3.7300E-02, 2.6800E-02, 1.8200E-02, 
            7.6000E-03, 2.4000E-03, 2.2000E-03, 8.6000E-04, 2.6000E-04, 
            3.1000E-05, 1.5000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {7.3500E-02, 7.3500E-02, 7.3500E-02, 7.3500E-02, 
            7.3500E-02, 7.3500E-02, 7.3500E-02, 7.3500E-02, 7.3500E-02, 
            7.3500E-02, 7.3500E-02, 7.3400E-02, 7.3300E-02, 7.3200E-02, 
            7.2900E-02, 7.2600E-02, 7.2100E-02, 7.0800E-02, 6.7700E-02, 
            5.9300E-02, 4.8100E-02, 3.6100E-02, 2.5200E-02, 1.6700E-02, 
            6.7000E-03, 2.6000E-03, 2.2000E-03, 7.7000E-04, 2.1000E-04, 
            2.1000E-05, 7.1000E-07} );

    subshell_half_profiles[7] = 
      std::vector<double>( {4.8800E-02, 4.8800E-02, 4.8800E-02, 4.8800E-02, 
            4.8800E-02, 4.8800E-02, 4.8800E-02, 4.8800E-02, 4.8800E-02, 
            4.8800E-02, 4.8800E-02, 4.8800E-02, 4.8800E-02, 4.8800E-02, 
            4.8800E-02, 4.8800E-02, 4.8800E-02, 4.8700E-02, 4.8500E-02, 
            4.7400E-02, 4.5200E-02, 4.1600E-02, 3.6900E-02, 3.1700E-02, 
            2.2000E-02, 6.4000E-03, 1.8000E-03, 1.6000E-04, 2.1000E-05, 
            8.6000E-07, 1.2000E-08} );

    subshell_half_profiles[8] = 
      std::vector<double>( {4.9400E-02, 4.9400E-02, 4.9400E-02, 4.9400E-02, 
            4.9400E-02, 4.9400E-02, 4.9400E-02, 4.9400E-02, 4.9400E-02, 
            4.9400E-02, 4.9400E-02, 4.9400E-02, 4.9400E-02, 4.9400E-02, 
            4.9400E-02, 4.9400E-02, 4.9300E-02, 4.9300E-02, 4.9000E-02, 
            4.7900E-02, 4.5500E-02, 4.1800E-02, 3.7000E-02, 3.1600E-02, 
            2.1000E-02, 6.2000E-03, 1.7000E-03, 1.4000E-04, 1.8000E-05, 
            6.8000E-07, 7.7000E-09} );

    subshell_half_profiles[9] = 
      std::vector<double>( {2.6400E-01, 2.6400E-01, 2.6300E-01, 2.6200E-01, 
            2.6000E-01, 2.5600E-01, 2.4900E-01, 2.4200E-01, 2.3200E-01, 
            2.2200E-01, 2.1100E-01, 1.8600E-01, 1.6000E-01, 1.3400E-01, 
            1.1000E-01, 8.8700E-02, 7.0500E-02, 4.4300E-02, 2.6400E-02, 
            2.2500E-02, 2.0100E-02, 1.3500E-02, 7.3800E-03, 3.7800E-03, 
            1.9000E-03, 1.3000E-03, 3.3000E-04, 5.4000E-05, 4.8000E-05, 
            1.8000E-05, 2.3000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.7000E-01, 1.7000E-01, 1.7000E-01, 1.7000E-01, 
            1.7000E-01, 1.7000E-01, 1.6900E-01, 1.6900E-01, 1.6900E-01, 
            1.6800E-01, 1.6700E-01, 1.6400E-01, 1.5900E-01, 1.5200E-01, 
            1.4300E-01, 1.3200E-01, 1.2000E-01, 9.3400E-02, 5.6900E-02, 
            2.0400E-02, 9.8200E-03, 8.7700E-03, 8.4200E-03, 7.0100E-03, 
            3.4000E-03, 4.8000E-04, 4.2000E-04, 1.8000E-04, 5.5000E-05, 
            6.4000E-06, 3.1000E-07} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.7600E-01, 1.7600E-01, 1.7600E-01, 1.7600E-01, 
            1.7600E-01, 1.7500E-01, 1.7500E-01, 1.7500E-01, 1.7500E-01, 
            1.7400E-01, 1.7300E-01, 1.6900E-01, 1.6300E-01, 1.5500E-01, 
            1.4500E-01, 1.3200E-01, 1.1900E-01, 9.0800E-02, 5.3300E-02, 
            1.8400E-02, 9.7100E-03, 9.1400E-03, 8.5000E-03, 6.7400E-03, 
            3.0000E-03, 4.9000E-04, 4.4000E-04, 1.6000E-04, 4.4000E-05, 
            4.3000E-06, 1.5000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.4400E-01, 1.4400E-01, 1.4400E-01, 1.4400E-01, 
            1.4400E-01, 1.4400E-01, 1.4400E-01, 1.4400E-01, 1.4400E-01, 
            1.4400E-01, 1.4300E-01, 1.4300E-01, 1.4100E-01, 1.3900E-01, 
            1.3500E-01, 1.3000E-01, 1.2300E-01, 1.0700E-01, 7.7800E-02, 
            3.6800E-02, 1.4600E-02, 5.9100E-03, 3.5100E-03, 3.1500E-03, 
            3.0000E-03, 1.2000E-03, 3.5000E-04, 3.2000E-05, 4.1000E-06, 
            1.7000E-07, 2.4000E-09} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.4500E-01, 1.4500E-01, 1.4500E-01, 1.4500E-01, 
            1.4500E-01, 1.4500E-01, 1.4500E-01, 1.4500E-01, 1.4500E-01, 
            1.4500E-01, 1.4500E-01, 1.4400E-01, 1.4300E-01, 1.4000E-01, 
            1.3600E-01, 1.3100E-01, 1.2400E-01, 1.0700E-01, 7.7000E-02, 
            3.5800E-02, 1.3900E-02, 5.6600E-03, 3.4800E-03, 3.1800E-03, 
            3.0000E-03, 1.2000E-03, 3.3000E-04, 2.9000E-05, 3.5000E-06, 
            1.3000E-07, 1.5000E-09} );

    subshell_half_profiles[14] = 
      std::vector<double>( {7.2000E-01, 7.1500E-01, 7.0200E-01, 6.8200E-01, 
            6.5400E-01, 5.8000E-01, 4.9200E-01, 3.9900E-01, 3.1100E-01, 
            2.3400E-01, 1.7100E-01, 8.9600E-02, 5.4100E-02, 4.3900E-02, 
            4.2800E-02, 4.2200E-02, 3.9300E-02, 2.8000E-02, 1.1900E-02, 
            3.6600E-03, 3.3600E-03, 2.5900E-03, 1.4900E-03, 7.3400E-04, 
            2.8000E-04, 1.9000E-04, 5.0000E-05, 7.6000E-06, 6.8000E-06, 
            2.5000E-06, 3.2000E-07} );

    subshell_half_profiles[15] = 
      std::vector<double>( {4.9800E-01, 4.9800E-01, 4.9800E-01, 4.9700E-01, 
            4.9600E-01, 4.8800E-01, 4.7000E-01, 4.3900E-01, 3.9800E-01, 
            3.4800E-01, 2.9500E-01, 1.9200E-01, 1.1300E-01, 6.1500E-02, 
            3.3700E-02, 2.0900E-02, 1.6200E-02, 1.5100E-02, 1.2900E-02, 
            5.2200E-03, 1.6300E-03, 9.9900E-04, 9.7600E-04, 8.6700E-04, 
            4.5000E-04, 5.6000E-05, 4.8000E-05, 2.1000E-05, 6.3000E-06, 
            7.4000E-07, 3.5000E-08} );

    subshell_half_profiles[16] = 
      std::vector<double>( {5.2200E-01, 5.2200E-01, 5.2200E-01, 5.2100E-01, 
            5.1900E-01, 5.0900E-01, 4.8700E-01, 4.5100E-01, 4.0200E-01, 
            3.4600E-01, 2.8700E-01, 1.7900E-01, 1.0100E-01, 5.3100E-02, 
            2.9000E-02, 1.8900E-02, 1.5800E-02, 1.5300E-02, 1.2300E-02, 
            4.4300E-03, 1.4000E-03, 9.9500E-04, 9.7100E-04, 8.1900E-04, 
            3.8000E-04, 5.4000E-05, 4.9000E-05, 1.8000E-05, 4.9000E-06, 
            4.8000E-07, 1.6000E-08} );

    subshell_half_profiles[17] = 
      std::vector<double>( {2.7400E+00, 2.5500E+00, 2.0500E+00, 1.4400E+00, 
            8.9100E-01, 2.5400E-01, 8.6700E-02, 7.1000E-02, 6.8100E-02, 
            5.6100E-02, 4.0700E-02, 1.7200E-02, 6.6600E-03, 3.2200E-03, 
            2.4800E-03, 2.4300E-03, 2.3700E-03, 1.8100E-03, 7.9300E-04, 
            2.0600E-04, 1.8100E-04, 1.4300E-04, 8.2900E-05, 4.0800E-05, 
            1.5000E-05, 1.0000E-05, 2.7000E-06, 4.1000E-07, 3.6000E-07, 
            1.3000E-07, 1.7000E-08} );
  }
};

//! The default Compton profile generator implementation for A=56
template<>
struct DefaultComptonProfileGeneratorImpl<56u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 18 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.4300E-02, 1.4300E-02, 1.4300E-02, 1.4300E-02, 
            1.4300E-02, 1.4300E-02, 1.4300E-02, 1.4300E-02, 1.4300E-02, 
            1.4300E-02, 1.4300E-02, 1.4300E-02, 1.4300E-02, 1.4300E-02, 
            1.4300E-02, 1.4300E-02, 1.4300E-02, 1.4200E-02, 1.4200E-02, 
            1.4100E-02, 1.4000E-02, 1.3900E-02, 1.3700E-02, 1.3500E-02, 
            1.3000E-02, 1.2000E-02, 1.0000E-02, 7.0000E-03, 4.5000E-03, 
            1.8000E-03, 3.1000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {5.1200E-02, 5.1200E-02, 5.1200E-02, 5.1200E-02, 
            5.1200E-02, 5.1100E-02, 5.1100E-02, 5.1000E-02, 5.1000E-02, 
            5.0900E-02, 5.0800E-02, 5.0600E-02, 5.0400E-02, 5.0100E-02, 
            4.9800E-02, 4.9400E-02, 4.9000E-02, 4.8100E-02, 4.6500E-02, 
            4.3200E-02, 3.9300E-02, 3.5000E-02, 3.0700E-02, 2.6400E-02, 
            1.9000E-02, 6.1000E-03, 2.0000E-03, 1.2000E-03, 1.0000E-03, 
            3.8000E-04, 5.3000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 
            2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 
            2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 
            2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5300E-02, 
            2.5200E-02, 2.5100E-02, 2.4800E-02, 2.4300E-02, 2.3700E-02, 
            2.2000E-02, 1.6000E-02, 1.0000E-02, 3.3000E-03, 1.0000E-03, 
            1.4000E-04, 7.3000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.6800E-02, 2.6800E-02, 2.6800E-02, 2.6800E-02, 
            2.6800E-02, 2.6800E-02, 2.6800E-02, 2.6800E-02, 2.6800E-02, 
            2.6800E-02, 2.6800E-02, 2.6800E-02, 2.6800E-02, 2.6800E-02, 
            2.6800E-02, 2.6800E-02, 2.6800E-02, 2.6800E-02, 2.6700E-02, 
            2.6600E-02, 2.6400E-02, 2.6000E-02, 2.5500E-02, 2.4800E-02, 
            2.3000E-02, 1.6000E-02, 9.7000E-03, 2.9000E-03, 8.1000E-04, 
            8.8000E-05, 3.3000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.1700E-01, 1.1700E-01, 1.1700E-01, 1.1700E-01, 
            1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1500E-01, 1.1400E-01, 
            1.1300E-01, 1.1200E-01, 1.0900E-01, 1.0600E-01, 1.0300E-01, 
            9.8900E-02, 9.4700E-02, 9.0200E-02, 8.0600E-02, 6.5700E-02, 
            4.3000E-02, 2.6000E-02, 1.5600E-02, 1.0500E-02, 8.6600E-03, 
            8.3000E-03, 4.7000E-03, 1.3000E-03, 2.5000E-04, 2.3000E-04, 
            8.7000E-05, 1.1000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {6.9200E-02, 6.9200E-02, 6.9200E-02, 6.9200E-02, 
            6.9200E-02, 6.9200E-02, 6.9200E-02, 6.9200E-02, 6.9200E-02, 
            6.9200E-02, 6.9200E-02, 6.9100E-02, 6.9000E-02, 6.8900E-02, 
            6.8700E-02, 6.8500E-02, 6.8100E-02, 6.7100E-02, 6.4700E-02, 
            5.8000E-02, 4.8600E-02, 3.8000E-02, 2.7800E-02, 1.9200E-02, 
            8.3000E-03, 2.4000E-03, 2.2000E-03, 9.1000E-04, 2.9000E-04, 
            3.5000E-05, 1.7000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {7.1800E-02, 7.1800E-02, 7.1800E-02, 7.1800E-02, 
            7.1800E-02, 7.1800E-02, 7.1800E-02, 7.1800E-02, 7.1800E-02, 
            7.1700E-02, 7.1700E-02, 7.1700E-02, 7.1600E-02, 7.1400E-02, 
            7.1200E-02, 7.0900E-02, 7.0500E-02, 6.9300E-02, 6.6500E-02, 
            5.8800E-02, 4.8300E-02, 3.6800E-02, 2.6200E-02, 1.7600E-02, 
            7.3000E-03, 2.5000E-03, 2.3000E-03, 8.2000E-04, 2.3000E-04, 
            2.3000E-05, 8.1000E-07} );

    subshell_half_profiles[7] = 
      std::vector<double>( {4.7500E-02, 4.7500E-02, 4.7500E-02, 4.7500E-02, 
            4.7500E-02, 4.7500E-02, 4.7500E-02, 4.7500E-02, 4.7500E-02, 
            4.7500E-02, 4.7500E-02, 4.7500E-02, 4.7500E-02, 4.7500E-02, 
            4.7500E-02, 4.7500E-02, 4.7500E-02, 4.7400E-02, 4.7200E-02, 
            4.6300E-02, 4.4400E-02, 4.1100E-02, 3.6900E-02, 3.2000E-02, 
            2.2000E-02, 6.9000E-03, 1.9000E-03, 1.8000E-04, 2.4000E-05, 
            1.0000E-06, 1.5000E-08} );

    subshell_half_profiles[8] = 
      std::vector<double>( {4.8100E-02, 4.8100E-02, 4.8100E-02, 4.8100E-02, 
            4.8100E-02, 4.8100E-02, 4.8100E-02, 4.8100E-02, 4.8100E-02, 
            4.8100E-02, 4.8100E-02, 4.8100E-02, 4.8100E-02, 4.8100E-02, 
            4.8100E-02, 4.8100E-02, 4.8100E-02, 4.8000E-02, 4.7800E-02, 
            4.6900E-02, 4.4800E-02, 4.1400E-02, 3.7000E-02, 3.1900E-02, 
            2.2000E-02, 6.7000E-03, 1.8000E-03, 1.6000E-04, 2.1000E-05, 
            8.0000E-07, 9.2000E-09} );

    subshell_half_profiles[9] = 
      std::vector<double>( {2.5500E-01, 2.5400E-01, 2.5400E-01, 2.5300E-01, 
            2.5100E-01, 2.4700E-01, 2.4100E-01, 2.3400E-01, 2.2600E-01, 
            2.1700E-01, 2.0600E-01, 1.8300E-01, 1.5900E-01, 1.3500E-01, 
            1.1200E-01, 9.1300E-02, 7.3400E-02, 4.6800E-02, 2.7300E-02, 
            2.2200E-02, 2.0400E-02, 1.4500E-02, 8.2500E-03, 4.2900E-03, 
            1.9000E-03, 1.3000E-03, 3.8000E-04, 5.5000E-05, 4.9000E-05, 
            1.9000E-05, 2.5000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.6300E-01, 1.6300E-01, 1.6300E-01, 1.6300E-01, 
            1.6300E-01, 1.6300E-01, 1.6300E-01, 1.6300E-01, 1.6300E-01, 
            1.6200E-01, 1.6100E-01, 1.5900E-01, 1.5400E-01, 1.4800E-01, 
            1.4000E-01, 1.3000E-01, 1.2000E-01, 9.5300E-02, 6.0300E-02, 
            2.2700E-02, 1.0300E-02, 8.7200E-03, 8.5200E-03, 7.3400E-03, 
            3.8000E-03, 5.1000E-04, 4.3000E-04, 2.0000E-04, 6.2000E-05, 
            7.4000E-06, 3.6000E-07} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.6900E-01, 1.6900E-01, 1.6900E-01, 1.6900E-01, 
            1.6900E-01, 1.6900E-01, 1.6900E-01, 1.6900E-01, 1.6800E-01, 
            1.6800E-01, 1.6700E-01, 1.6400E-01, 1.5900E-01, 1.5100E-01, 
            1.4200E-01, 1.3100E-01, 1.1900E-01, 9.3100E-02, 5.6700E-02, 
            2.0400E-02, 1.0100E-02, 9.1000E-03, 8.6800E-03, 7.1400E-03, 
            3.3000E-03, 5.1000E-04, 4.6000E-04, 1.8000E-04, 5.0000E-05, 
            5.0000E-06, 1.7000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.3700E-01, 1.3700E-01, 1.3700E-01, 1.3700E-01, 
            1.3700E-01, 1.3700E-01, 1.3700E-01, 1.3700E-01, 1.3700E-01, 
            1.3700E-01, 1.3700E-01, 1.3600E-01, 1.3500E-01, 1.3400E-01, 
            1.3100E-01, 1.2600E-01, 1.2100E-01, 1.0700E-01, 8.0700E-02, 
            4.0600E-02, 1.6900E-02, 6.9000E-03, 3.8000E-03, 3.2100E-03, 
            3.1000E-03, 1.3000E-03, 4.0000E-04, 3.8000E-05, 5.0000E-06, 
            2.1000E-07, 3.0000E-09} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3900E-01, 
            1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3900E-01, 
            1.3900E-01, 1.3900E-01, 1.3800E-01, 1.3700E-01, 1.3500E-01, 
            1.3200E-01, 1.2800E-01, 1.2200E-01, 1.0700E-01, 8.0000E-02, 
            3.9600E-02, 1.6200E-02, 6.5900E-03, 3.7300E-03, 3.2300E-03, 
            3.1000E-03, 1.3000E-03, 3.8000E-04, 3.4000E-05, 4.3000E-06, 
            1.6000E-07, 1.9000E-09} );

    subshell_half_profiles[14] = 
      std::vector<double>( {6.5700E-01, 6.5300E-01, 6.4300E-01, 6.2700E-01, 
            6.0500E-01, 5.4700E-01, 4.7500E-01, 3.9700E-01, 3.2000E-01, 
            2.5000E-01, 1.9000E-01, 1.0500E-01, 6.2400E-02, 4.6900E-02, 
            4.3900E-02, 4.3700E-02, 4.2100E-02, 3.2500E-02, 1.5200E-02, 
            4.2400E-03, 3.6600E-03, 3.0200E-03, 1.8400E-03, 9.3900E-04, 
            3.2000E-04, 2.2000E-04, 6.3000E-05, 8.5000E-06, 7.7000E-06, 
            3.0000E-06, 3.9000E-07} );

    subshell_half_profiles[15] = 
      std::vector<double>( {4.5200E-01, 4.5200E-01, 4.5200E-01, 4.5200E-01, 
            4.5100E-01, 4.4600E-01, 4.3300E-01, 4.1300E-01, 3.8300E-01, 
            3.4500E-01, 3.0200E-01, 2.1300E-01, 1.3600E-01, 7.9700E-02, 
            4.5300E-02, 2.7200E-02, 1.9300E-02, 1.6300E-02, 1.4900E-02, 
            6.8500E-03, 2.1900E-03, 1.1600E-03, 1.1000E-03, 1.0200E-03, 
            5.7000E-04, 6.9000E-05, 5.5000E-05, 2.6000E-05, 8.1000E-06, 
            9.7000E-07, 4.8000E-08} );

    subshell_half_profiles[16] = 
      std::vector<double>( {4.7300E-01, 4.7300E-01, 4.7300E-01, 4.7200E-01, 
            4.7100E-01, 4.6400E-01, 4.5000E-01, 4.2500E-01, 3.9000E-01, 
            3.4700E-01, 2.9900E-01, 2.0300E-01, 1.2400E-01, 7.0300E-02, 
            3.9200E-02, 2.4100E-02, 1.8300E-02, 1.6600E-02, 1.4500E-02, 
            5.9200E-03, 1.8500E-03, 1.1400E-03, 1.1200E-03, 9.8400E-04, 
            4.9000E-04, 6.5000E-05, 5.7000E-05, 2.3000E-05, 6.4000E-06, 
            6.3000E-07, 2.2000E-08} );

    subshell_half_profiles[17] = 
      std::vector<double>( {2.2300E+00, 2.1200E+00, 1.8200E+00, 1.4200E+00, 
            1.0100E+00, 4.0100E-01, 1.4400E-01, 8.2400E-02, 7.7400E-02, 
            7.4500E-02, 6.4000E-02, 3.5600E-02, 1.5900E-02, 7.0200E-03, 
            4.2000E-03, 3.6900E-03, 3.6700E-03, 3.1200E-03, 1.5400E-03, 
            3.6700E-04, 2.8800E-04, 2.4400E-04, 1.5100E-04, 7.7000E-05, 
            2.6000E-05, 1.7000E-05, 5.0000E-06, 6.6000E-07, 6.0000E-07, 
            2.3000E-07, 3.1000E-08} );
  }
};

//! The default Compton profile generator implementation for A=57
template<>
struct DefaultComptonProfileGeneratorImpl<57u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 19 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 
            1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 
            1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 
            1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 1.3900E-02, 
            1.3800E-02, 1.3700E-02, 1.3600E-02, 1.3400E-02, 1.3300E-02, 
            1.3000E-02, 1.2000E-02, 1.0000E-02, 7.1000E-03, 4.4000E-03, 
            1.8000E-03, 3.3000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {5.0100E-02, 5.0100E-02, 5.0100E-02, 5.0100E-02, 
            5.0100E-02, 5.0000E-02, 5.0000E-02, 5.0000E-02, 4.9900E-02, 
            4.9800E-02, 4.9800E-02, 4.9600E-02, 4.9300E-02, 4.9100E-02, 
            4.8800E-02, 4.8400E-02, 4.8100E-02, 4.7200E-02, 4.5700E-02, 
            4.2500E-02, 3.8900E-02, 3.4800E-02, 3.0700E-02, 2.6500E-02, 
            1.9000E-02, 6.4000E-03, 2.1000E-03, 1.2000E-03, 1.0000E-03, 
            4.0000E-04, 5.8000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 
            2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 
            2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 
            2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 
            2.4700E-02, 2.4500E-02, 2.4300E-02, 2.3900E-02, 2.3300E-02, 
            2.2000E-02, 1.6000E-02, 1.0000E-02, 3.5000E-03, 1.1000E-03, 
            1.5000E-04, 8.2000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.6300E-02, 2.6300E-02, 2.6300E-02, 2.6300E-02, 
            2.6300E-02, 2.6300E-02, 2.6300E-02, 2.6300E-02, 2.6300E-02, 
            2.6300E-02, 2.6300E-02, 2.6300E-02, 2.6300E-02, 2.6300E-02, 
            2.6300E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 
            2.6100E-02, 2.5900E-02, 2.5600E-02, 2.5100E-02, 2.4400E-02, 
            2.3000E-02, 1.6000E-02, 9.9000E-03, 3.0000E-03, 8.8000E-04, 
            9.7000E-05, 3.7000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.1400E-01, 1.1400E-01, 1.1400E-01, 1.1400E-01, 
            1.1400E-01, 1.1300E-01, 1.1300E-01, 1.1200E-01, 1.1100E-01, 
            1.1100E-01, 1.0900E-01, 1.0700E-01, 1.0400E-01, 1.0100E-01, 
            9.7200E-02, 9.3300E-02, 8.9000E-02, 8.0000E-02, 6.5800E-02, 
            4.3800E-02, 2.7000E-02, 1.6300E-02, 1.0800E-02, 8.6800E-03, 
            8.1000E-03, 4.9000E-03, 1.4000E-03, 2.5000E-04, 2.3000E-04, 
            9.2000E-05, 1.3000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {6.7500E-02, 6.7500E-02, 6.7500E-02, 6.7500E-02, 
            6.7500E-02, 6.7500E-02, 6.7500E-02, 6.7500E-02, 6.7500E-02, 
            6.7400E-02, 6.7400E-02, 6.7400E-02, 6.7300E-02, 6.7200E-02, 
            6.7100E-02, 6.6800E-02, 6.6500E-02, 6.5600E-02, 6.3400E-02, 
            5.7300E-02, 4.8600E-02, 3.8500E-02, 2.8700E-02, 2.0200E-02, 
            8.9000E-03, 2.3000E-03, 2.2000E-03, 9.7000E-04, 3.1000E-04, 
            3.9000E-05, 2.0000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {7.0100E-02, 7.0100E-02, 7.0100E-02, 7.0100E-02, 
            7.0100E-02, 7.0100E-02, 7.0100E-02, 7.0100E-02, 7.0100E-02, 
            7.0100E-02, 7.0000E-02, 7.0000E-02, 6.9900E-02, 6.9800E-02, 
            6.9600E-02, 6.9300E-02, 6.8900E-02, 6.7900E-02, 6.5300E-02, 
            5.8300E-02, 4.8500E-02, 3.7500E-02, 2.7200E-02, 1.8600E-02, 
            7.8000E-03, 2.5000E-03, 2.3000E-03, 8.7000E-04, 2.5000E-04, 
            2.6000E-05, 9.2000E-07} );

    subshell_half_profiles[7] = 
      std::vector<double>( {4.6300E-02, 4.6300E-02, 4.6300E-02, 4.6300E-02, 
            4.6300E-02, 4.6300E-02, 4.6300E-02, 4.6300E-02, 4.6300E-02, 
            4.6300E-02, 4.6300E-02, 4.6300E-02, 4.6300E-02, 4.6300E-02, 
            4.6300E-02, 4.6300E-02, 4.6300E-02, 4.6300E-02, 4.6100E-02, 
            4.5300E-02, 4.3600E-02, 4.0700E-02, 3.6800E-02, 3.2200E-02, 
            2.3000E-02, 7.4000E-03, 2.1000E-03, 2.1000E-04, 2.8000E-05, 
            1.2000E-06, 1.8000E-08} );

    subshell_half_profiles[8] = 
      std::vector<double>( {4.6900E-02, 4.6900E-02, 4.6900E-02, 4.6900E-02, 
            4.6900E-02, 4.6900E-02, 4.6900E-02, 4.6900E-02, 4.6900E-02, 
            4.6900E-02, 4.6900E-02, 4.6900E-02, 4.6900E-02, 4.6900E-02, 
            4.6900E-02, 4.6900E-02, 4.6900E-02, 4.6800E-02, 4.6700E-02, 
            4.5800E-02, 4.4000E-02, 4.1000E-02, 3.6900E-02, 3.2200E-02, 
            2.3000E-02, 7.1000E-03, 2.0000E-03, 1.9000E-04, 2.4000E-05, 
            9.4000E-07, 1.1000E-08} );

    subshell_half_profiles[9] = 
      std::vector<double>( {2.4600E-01, 2.4600E-01, 2.4500E-01, 2.4400E-01, 
            2.4300E-01, 2.3900E-01, 2.3400E-01, 2.2700E-01, 2.2000E-01, 
            2.1100E-01, 2.0200E-01, 1.8100E-01, 1.5800E-01, 1.3500E-01, 
            1.1400E-01, 9.3600E-02, 7.6100E-02, 4.9300E-02, 2.8300E-02, 
            2.1900E-02, 2.0700E-02, 1.5300E-02, 9.1300E-03, 4.8500E-03, 
            2.0000E-03, 1.4000E-03, 4.3000E-04, 5.6000E-05, 5.1000E-05, 
            2.1000E-05, 2.8000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.5800E-01, 1.5800E-01, 1.5800E-01, 1.5800E-01, 
            1.5800E-01, 1.5800E-01, 1.5700E-01, 1.5700E-01, 1.5700E-01, 
            1.5600E-01, 1.5600E-01, 1.5400E-01, 1.5000E-01, 1.4400E-01, 
            1.3700E-01, 1.2900E-01, 1.1900E-01, 9.6900E-02, 6.3400E-02, 
            2.5100E-02, 1.1000E-02, 8.6800E-03, 8.5600E-03, 7.6200E-03, 
            4.2000E-03, 5.5000E-04, 4.4000E-04, 2.1000E-04, 6.9000E-05, 
            8.5000E-06, 4.3000E-07} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.6300E-01, 1.6300E-01, 1.6300E-01, 1.6300E-01, 
            1.6300E-01, 1.6300E-01, 1.6300E-01, 1.6300E-01, 1.6300E-01, 
            1.6200E-01, 1.6100E-01, 1.5800E-01, 1.5400E-01, 1.4800E-01, 
            1.4000E-01, 1.3000E-01, 1.1900E-01, 9.5000E-02, 6.0000E-02, 
            2.2500E-02, 1.0500E-02, 9.0600E-03, 8.8000E-03, 7.4900E-03, 
            3.7000E-03, 5.3000E-04, 4.7000E-04, 1.9000E-04, 5.6000E-05, 
            5.7000E-06, 2.0000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.3100E-01, 1.3100E-01, 1.3100E-01, 1.3100E-01, 
            1.3100E-01, 1.3100E-01, 1.3100E-01, 1.3100E-01, 1.3100E-01, 
            1.3100E-01, 1.3100E-01, 1.3100E-01, 1.3000E-01, 1.2800E-01, 
            1.2600E-01, 1.2300E-01, 1.1800E-01, 1.0600E-01, 8.2900E-02, 
            4.4300E-02, 1.9500E-02, 8.0600E-03, 4.1700E-03, 3.2800E-03, 
            3.2000E-03, 1.5000E-03, 4.6000E-04, 4.5000E-05, 6.1000E-06, 
            2.5000E-07, 3.7000E-09} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 
            1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 
            1.3300E-01, 1.3300E-01, 1.3200E-01, 1.3100E-01, 1.3000E-01, 
            1.2700E-01, 1.2400E-01, 1.1900E-01, 1.0700E-01, 8.2400E-02, 
            4.3200E-02, 1.8600E-02, 7.6700E-03, 4.0600E-03, 3.3000E-03, 
            3.2000E-03, 1.4000E-03, 4.4000E-04, 4.1000E-05, 5.2000E-06, 
            2.0000E-07, 2.3000E-09} );

    subshell_half_profiles[14] = 
      std::vector<double>( {6.1600E-01, 6.1300E-01, 6.0400E-01, 5.9100E-01, 
            5.7200E-01, 5.2200E-01, 4.6000E-01, 3.9200E-01, 3.2300E-01, 
            2.5800E-01, 2.0100E-01, 1.1600E-01, 6.9400E-02, 4.9600E-02, 
            4.4200E-02, 4.3700E-02, 4.3000E-02, 3.5500E-02, 1.8300E-02, 
            4.8900E-03, 3.8500E-03, 3.3600E-03, 2.1700E-03, 1.1500E-03, 
            3.7000E-04, 2.5000E-04, 7.7000E-05, 9.3000E-06, 8.4000E-06, 
            3.4000E-06, 4.6000E-07} );

    subshell_half_profiles[15] = 
      std::vector<double>( {4.2400E-01, 4.2400E-01, 4.2400E-01, 4.2400E-01, 
            4.2300E-01, 4.1900E-01, 4.1000E-01, 3.9300E-01, 3.6900E-01, 
            3.3800E-01, 3.0200E-01, 2.2300E-01, 1.5000E-01, 9.3300E-02, 
            5.5300E-02, 3.3300E-02, 2.2300E-02, 1.6700E-02, 1.5900E-02, 
            8.2900E-03, 2.7700E-03, 1.3000E-03, 1.1800E-03, 1.1200E-03, 
            6.7000E-04, 8.2000E-05, 6.0000E-05, 3.0000E-05, 9.7000E-06, 
            1.2000E-06, 6.0000E-08} );

    subshell_half_profiles[16] = 
      std::vector<double>( {4.4000E-01, 4.4000E-01, 4.4000E-01, 4.4000E-01, 
            4.3900E-01, 4.3400E-01, 4.2300E-01, 4.0400E-01, 3.7700E-01, 
            3.4200E-01, 3.0200E-01, 2.1700E-01, 1.4100E-01, 8.4600E-02, 
            4.9000E-02, 2.9600E-02, 2.0800E-02, 1.7200E-02, 1.5900E-02, 
            7.3700E-03, 2.3500E-03, 1.2700E-03, 1.2200E-03, 1.1100E-03, 
            6.0000E-04, 7.6000E-05, 6.4000E-05, 2.7000E-05, 7.8000E-06, 
            7.9000E-07, 2.8000E-08} );

    subshell_half_profiles[17] = 
      std::vector<double>( {5.0900E-01, 5.0900E-01, 5.0900E-01, 5.0900E-01, 
            5.0900E-01, 5.0400E-01, 4.8800E-01, 4.5700E-01, 4.1200E-01, 
            3.5800E-01, 3.0100E-01, 1.9800E-01, 1.2100E-01, 6.9500E-02, 
            3.8600E-02, 2.1000E-02, 1.1800E-02, 5.4000E-03, 4.5500E-03, 
            3.5200E-03, 1.7500E-03, 7.1200E-04, 3.1300E-04, 2.0500E-04, 
            1.9000E-04, 9.6000E-05, 3.0000E-05, 2.9000E-06, 3.9000E-07, 
            1.6000E-08, 2.4000E-10} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.0700E+00, 1.9800E+00, 1.7300E+00, 1.3900E+00, 
            1.0300E+00, 4.5700E-01, 1.7500E-01, 8.8000E-02, 7.4800E-02, 
            7.4000E-02, 6.7900E-02, 4.3400E-02, 2.1700E-02, 9.9300E-03, 
            5.3000E-03, 4.0700E-03, 3.9400E-03, 3.6200E-03, 2.0200E-03, 
            4.7800E-04, 3.2400E-04, 2.9100E-04, 1.9200E-04, 1.0200E-04, 
            3.2000E-05, 2.1000E-05, 6.6000E-06, 7.8000E-07, 7.0000E-07, 
            2.9000E-07, 3.9000E-08} );
  }
};

//! The default Compton profile generator implementation for A=58
template<>
struct DefaultComptonProfileGeneratorImpl<58u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 20 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3700E-02, 
            1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3700E-02, 
            1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3700E-02, 
            1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3600E-02, 
            1.3600E-02, 1.3500E-02, 1.3300E-02, 1.3200E-02, 1.3000E-02, 
            1.3000E-02, 1.1000E-02, 1.0000E-02, 7.1000E-03, 4.7000E-03, 
            1.9000E-03, 3.5000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {4.9000E-02, 4.9000E-02, 4.9000E-02, 4.9000E-02, 
            4.9000E-02, 4.9000E-02, 4.9000E-02, 4.8900E-02, 4.8900E-02, 
            4.8800E-02, 4.8700E-02, 4.8600E-02, 4.8300E-02, 4.8100E-02, 
            4.7800E-02, 4.7500E-02, 4.7100E-02, 4.6300E-02, 4.4900E-02, 
            4.1900E-02, 3.8400E-02, 3.4600E-02, 3.0600E-02, 2.6600E-02, 
            1.9000E-02, 6.8000E-03, 2.2000E-03, 1.2000E-03, 1.0000E-03, 
            4.2000E-04, 6.2000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 
            2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 
            2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 
            2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4200E-02, 
            2.4200E-02, 2.4000E-02, 2.3800E-02, 2.3400E-02, 2.2900E-02, 
            2.2000E-02, 1.6000E-02, 1.1000E-02, 3.7000E-03, 1.2000E-03, 
            1.7000E-04, 9.4000E-06} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.5700E-02, 2.5700E-02, 2.5700E-02, 2.5700E-02, 
            2.5700E-02, 2.5700E-02, 2.5700E-02, 2.5700E-02, 2.5700E-02, 
            2.5700E-02, 2.5700E-02, 2.5700E-02, 2.5700E-02, 2.5700E-02, 
            2.5700E-02, 2.5700E-02, 2.5700E-02, 2.5700E-02, 2.5700E-02, 
            2.5600E-02, 2.5400E-02, 2.5100E-02, 2.4700E-02, 2.4000E-02, 
            2.2000E-02, 1.6000E-02, 1.0000E-02, 3.2000E-03, 9.5000E-04, 
            1.1000E-04, 4.2000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.1100E-01, 1.1100E-01, 1.1100E-01, 1.1100E-01, 
            1.1100E-01, 1.1100E-01, 1.1000E-01, 1.1000E-01, 1.0900E-01, 
            1.0800E-01, 1.0700E-01, 1.0500E-01, 1.0200E-01, 9.9000E-02, 
            9.5600E-02, 9.1900E-02, 8.7900E-02, 7.9300E-02, 6.5900E-02, 
            4.4600E-02, 2.7900E-02, 1.7100E-02, 1.1200E-02, 8.7400E-03, 
            8.0000E-03, 5.2000E-03, 1.6000E-03, 2.5000E-04, 2.3000E-04, 
            9.7000E-05, 1.4000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {6.5800E-02, 6.5800E-02, 6.5800E-02, 6.5800E-02, 
            6.5800E-02, 6.5800E-02, 6.5800E-02, 6.5800E-02, 6.5800E-02, 
            6.5800E-02, 6.5800E-02, 6.5800E-02, 6.5700E-02, 6.5600E-02, 
            6.5500E-02, 6.5300E-02, 6.5000E-02, 6.4200E-02, 6.2200E-02, 
            5.6600E-02, 4.8500E-02, 3.9000E-02, 2.9600E-02, 2.1200E-02, 
            9.7000E-03, 2.4000E-03, 2.2000E-03, 1.0000E-03, 3.4000E-04, 
            4.4000E-05, 2.3000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {6.8400E-02, 6.8400E-02, 6.8400E-02, 6.8400E-02, 
            6.8400E-02, 6.8400E-02, 6.8400E-02, 6.8400E-02, 6.8400E-02, 
            6.8400E-02, 6.8400E-02, 6.8400E-02, 6.8300E-02, 6.8200E-02, 
            6.8000E-02, 6.7800E-02, 6.7400E-02, 6.6500E-02, 6.4100E-02, 
            5.7700E-02, 4.8500E-02, 3.8100E-02, 2.8100E-02, 1.9500E-02, 
            8.5000E-03, 2.5000E-03, 2.3000E-03, 9.3000E-04, 2.7000E-04, 
            2.9000E-05, 1.0000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 
            4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 
            4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 
            4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5100E-02, 4.5000E-02, 
            4.4300E-02, 4.2800E-02, 4.0200E-02, 3.6600E-02, 3.2300E-02, 
            2.3000E-02, 7.9000E-03, 2.3000E-03, 2.4000E-04, 3.3000E-05, 
            1.4000E-06, 2.1000E-08} );

    subshell_half_profiles[8] = 
      std::vector<double>( {4.5800E-02, 4.5800E-02, 4.5800E-02, 4.5800E-02, 
            4.5800E-02, 4.5800E-02, 4.5800E-02, 4.5800E-02, 4.5800E-02, 
            4.5800E-02, 4.5800E-02, 4.5800E-02, 4.5800E-02, 4.5800E-02, 
            4.5800E-02, 4.5800E-02, 4.5700E-02, 4.5700E-02, 4.5500E-02, 
            4.4800E-02, 4.3200E-02, 4.0500E-02, 3.6700E-02, 3.2300E-02, 
            2.3000E-02, 7.6000E-03, 2.2000E-03, 2.1000E-04, 2.8000E-05, 
            1.1000E-06, 1.3000E-08} );

    subshell_half_profiles[9] = 
      std::vector<double>( {2.3900E-01, 2.3900E-01, 2.3800E-01, 2.3800E-01, 
            2.3600E-01, 2.3300E-01, 2.2800E-01, 2.2200E-01, 2.1500E-01, 
            2.0700E-01, 1.9800E-01, 1.7900E-01, 1.5700E-01, 1.3600E-01, 
            1.1500E-01, 9.5400E-02, 7.8200E-02, 5.1300E-02, 2.9300E-02, 
            2.1500E-02, 2.0600E-02, 1.5900E-02, 9.9000E-03, 5.4000E-03, 
            2.1000E-03, 1.5000E-03, 4.9000E-04, 5.7000E-05, 5.1000E-05, 
            2.2000E-05, 3.1000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5300E-01, 
            1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5300E-01, 
            1.5200E-01, 1.5200E-01, 1.5000E-01, 1.4600E-01, 1.4200E-01, 
            1.3500E-01, 1.2700E-01, 1.1800E-01, 9.7800E-02, 6.5800E-02, 
            2.7100E-02, 1.1600E-02, 8.6000E-03, 8.4600E-03, 7.7600E-03, 
            4.5000E-03, 5.9000E-04, 4.3000E-04, 2.3000E-04, 7.6000E-05, 
            9.7000E-06, 5.0000E-07} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.5900E-01, 1.5900E-01, 1.5900E-01, 1.5900E-01, 
            1.5900E-01, 1.5900E-01, 1.5900E-01, 1.5900E-01, 1.5800E-01, 
            1.5800E-01, 1.5700E-01, 1.5500E-01, 1.5100E-01, 1.4500E-01, 
            1.3800E-01, 1.2900E-01, 1.1900E-01, 9.6200E-02, 6.2400E-02, 
            2.4400E-02, 1.0900E-02, 8.9200E-03, 8.7700E-03, 7.6900E-03, 
            4.1000E-03, 5.6000E-04, 4.7000E-04, 2.1000E-04, 6.2000E-05, 
            6.4000E-06, 2.3000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.2700E-01, 1.2700E-01, 1.2700E-01, 1.2700E-01, 
            1.2700E-01, 1.2700E-01, 1.2700E-01, 1.2700E-01, 1.2700E-01, 
            1.2700E-01, 1.2700E-01, 1.2700E-01, 1.2600E-01, 1.2500E-01, 
            1.2300E-01, 1.2000E-01, 1.1600E-01, 1.0500E-01, 8.3900E-02, 
            4.6800E-02, 2.1500E-02, 9.0900E-03, 4.5100E-03, 3.3200E-03, 
            3.2000E-03, 1.6000E-03, 5.2000E-04, 5.2000E-05, 7.2000E-06, 
            3.1000E-07, 4.5000E-09} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.2900E-01, 1.2900E-01, 1.2900E-01, 1.2900E-01, 
            1.2900E-01, 1.2900E-01, 1.2900E-01, 1.2900E-01, 1.2900E-01, 
            1.2900E-01, 1.2900E-01, 1.2800E-01, 1.2800E-01, 1.2600E-01, 
            1.2400E-01, 1.2100E-01, 1.1700E-01, 1.0600E-01, 8.3500E-02, 
            4.5800E-02, 2.0600E-02, 8.6500E-03, 4.3700E-03, 3.3200E-03, 
            3.2000E-03, 1.6000E-03, 4.9000E-04, 4.7000E-05, 6.1000E-06, 
            2.4000E-07, 2.8000E-09} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 
            1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 
            1.4200E-01, 1.4200E-01, 1.4000E-01, 1.3800E-01, 1.3400E-01, 
            1.2800E-01, 1.2100E-01, 1.1400E-01, 9.7800E-02, 7.4300E-02, 
            4.3800E-02, 2.4700E-02, 1.3800E-02, 7.7000E-03, 4.3400E-03, 
            1.4000E-03, 1.2000E-04, 1.4000E-05, 4.7000E-07, 3.1000E-08, 
            5.1000E-10, 3.5000E-12} );

    subshell_half_profiles[15] = 
      std::vector<double>( {6.0200E-01, 5.9900E-01, 5.9100E-01, 5.7900E-01, 
            5.6100E-01, 5.1500E-01, 4.5600E-01, 3.9100E-01, 3.2500E-01, 
            2.6200E-01, 2.0600E-01, 1.2100E-01, 7.2200E-02, 5.0100E-02, 
            4.3300E-02, 4.2400E-02, 4.2100E-02, 3.6000E-02, 1.9600E-02, 
            5.2200E-03, 3.7500E-03, 3.4100E-03, 2.3300E-03, 1.2900E-03, 
            3.9000E-04, 2.6000E-04, 8.7000E-05, 9.4000E-06, 8.5000E-06, 
            3.7000E-06, 5.1000E-07} );

    subshell_half_profiles[16] = 
      std::vector<double>( {4.1400E-01, 4.1400E-01, 4.1400E-01, 4.1300E-01, 
            4.1300E-01, 4.0900E-01, 4.0100E-01, 3.8600E-01, 3.6400E-01, 
            3.3600E-01, 3.0200E-01, 2.2700E-01, 1.5600E-01, 9.9300E-02, 
            6.0000E-02, 3.6200E-02, 2.3700E-02, 1.6400E-02, 1.5700E-02, 
            8.9000E-03, 3.1300E-03, 1.3600E-03, 1.1500E-03, 1.1200E-03, 
            7.2000E-04, 9.0000E-05, 6.0000E-05, 3.2000E-05, 1.1000E-05, 
            1.4000E-06, 6.9000E-08} );

    subshell_half_profiles[17] = 
      std::vector<double>( {4.3100E-01, 4.3100E-01, 4.3100E-01, 4.3100E-01, 
            4.3000E-01, 4.2600E-01, 4.1600E-01, 3.9800E-01, 3.7300E-01, 
            3.4000E-01, 3.0200E-01, 2.2100E-01, 1.4600E-01, 8.9700E-02, 
            5.2600E-02, 3.1600E-02, 2.1500E-02, 1.6600E-02, 1.5700E-02, 
            7.9000E-03, 2.6000E-03, 1.2800E-03, 1.1900E-03, 1.1200E-03, 
            6.4000E-04, 8.0000E-05, 6.3000E-05, 2.9000E-05, 8.5000E-06, 
            8.9000E-07, 3.1000E-08} );

    subshell_half_profiles[18] = 
      std::vector<double>( {4.9800E-01, 4.9800E-01, 4.9800E-01, 4.9800E-01, 
            4.9800E-01, 4.9300E-01, 4.7900E-01, 4.5000E-01, 4.0800E-01, 
            3.5800E-01, 3.0400E-01, 2.0300E-01, 1.2700E-01, 7.4700E-02, 
            4.2400E-02, 2.3600E-02, 1.3300E-02, 5.6400E-03, 4.3700E-03, 
            3.5800E-03, 1.9000E-03, 8.0700E-04, 3.5000E-04, 2.1200E-04, 
            1.9000E-04, 1.0000E-04, 3.3000E-05, 3.4000E-06, 4.6000E-07, 
            2.0000E-08, 2.9000E-10} );

    subshell_half_profiles[19] = 
      std::vector<double>( {2.0500E+00, 1.9600E+00, 1.7200E+00, 1.3900E+00, 
            1.0400E+00, 4.6900E-01, 1.8100E-01, 8.8000E-02, 7.2100E-02, 
            7.1500E-02, 6.6600E-02, 4.4100E-02, 2.2800E-02, 1.0600E-02, 
            5.4700E-03, 3.9500E-03, 3.7300E-03, 3.5200E-03, 2.1000E-03, 
            5.0900E-04, 3.0800E-04, 2.8700E-04, 2.0000E-04, 1.1100E-04, 
            3.3000E-05, 2.1000E-05, 7.1000E-06, 7.7000E-07, 6.9000E-07, 
            3.0000E-07, 4.2000E-08} );
  }
};

//! The default Compton profile generator implementation for A=59
template<>
struct DefaultComptonProfileGeneratorImpl<59u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 19 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.3500E-02, 1.3500E-02, 1.3500E-02, 1.3500E-02, 
            1.3500E-02, 1.3500E-02, 1.3500E-02, 1.3500E-02, 1.3500E-02, 
            1.3500E-02, 1.3500E-02, 1.3500E-02, 1.3400E-02, 1.3400E-02, 
            1.3400E-02, 1.3400E-02, 1.3400E-02, 1.3400E-02, 1.3400E-02, 
            1.3300E-02, 1.3200E-02, 1.3100E-02, 1.2900E-02, 1.2800E-02, 
            1.2000E-02, 1.1000E-02, 9.9000E-03, 7.1000E-03, 4.7000E-03, 
            2.0000E-03, 3.7000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {4.8000E-02, 4.8000E-02, 4.8000E-02, 4.8000E-02, 
            4.8000E-02, 4.8000E-02, 4.7900E-02, 4.7900E-02, 4.7900E-02, 
            4.7800E-02, 4.7700E-02, 4.7600E-02, 4.7400E-02, 4.7100E-02, 
            4.6900E-02, 4.6600E-02, 4.6200E-02, 4.5500E-02, 4.4100E-02, 
            4.1300E-02, 3.8000E-02, 3.4400E-02, 3.0500E-02, 2.6700E-02, 
            1.9000E-02, 7.1000E-03, 2.4000E-03, 1.2000E-03, 1.0000E-03, 
            4.4000E-04, 6.7000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.3800E-02, 2.3800E-02, 2.3800E-02, 2.3800E-02, 
            2.3800E-02, 2.3800E-02, 2.3800E-02, 2.3800E-02, 2.3800E-02, 
            2.3800E-02, 2.3800E-02, 2.3800E-02, 2.3800E-02, 2.3800E-02, 
            2.3800E-02, 2.3800E-02, 2.3800E-02, 2.3700E-02, 2.3700E-02, 
            2.3700E-02, 2.3500E-02, 2.3300E-02, 2.3000E-02, 2.2500E-02, 
            2.1000E-02, 1.6000E-02, 1.1000E-02, 3.9000E-03, 1.3000E-03, 
            1.9000E-04, 1.1000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.5200E-02, 2.5200E-02, 2.5200E-02, 2.5200E-02, 
            2.5200E-02, 2.5200E-02, 2.5200E-02, 2.5200E-02, 2.5200E-02, 
            2.5200E-02, 2.5200E-02, 2.5200E-02, 2.5200E-02, 2.5200E-02, 
            2.5200E-02, 2.5200E-02, 2.5200E-02, 2.5200E-02, 2.5200E-02, 
            2.5100E-02, 2.4900E-02, 2.4700E-02, 2.4200E-02, 2.3700E-02, 
            2.2000E-02, 1.6000E-02, 1.0000E-02, 3.3000E-03, 1.0000E-03, 
            1.2000E-04, 4.7000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.0900E-01, 1.0900E-01, 1.0900E-01, 1.0800E-01, 
            1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0700E-01, 1.0600E-01, 
            1.0600E-01, 1.0500E-01, 1.0300E-01, 1.0000E-01, 9.7200E-02, 
            9.4000E-02, 9.0500E-02, 8.6700E-02, 7.8600E-02, 6.5800E-02, 
            4.5300E-02, 2.8800E-02, 1.7800E-02, 1.1600E-02, 8.8400E-03, 
            7.8000E-03, 5.4000E-03, 1.7000E-03, 2.5000E-04, 2.3000E-04, 
            1.0000E-04, 1.5000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {6.4300E-02, 6.4300E-02, 6.4300E-02, 6.4300E-02, 
            6.4300E-02, 6.4300E-02, 6.4300E-02, 6.4300E-02, 6.4300E-02, 
            6.4200E-02, 6.4200E-02, 6.4200E-02, 6.4200E-02, 6.4100E-02, 
            6.3900E-02, 6.3800E-02, 6.3500E-02, 6.2800E-02, 6.1000E-02, 
            5.5900E-02, 4.8400E-02, 3.9400E-02, 3.0300E-02, 2.2100E-02, 
            1.0000E-02, 2.4000E-03, 2.2000E-03, 1.1000E-03, 3.7000E-04, 
            4.9000E-05, 2.6000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {6.6900E-02, 6.6900E-02, 6.6900E-02, 6.6900E-02, 
            6.6900E-02, 6.6900E-02, 6.6900E-02, 6.6900E-02, 6.6900E-02, 
            6.6900E-02, 6.6900E-02, 6.6800E-02, 6.6800E-02, 6.6700E-02, 
            6.6500E-02, 6.6300E-02, 6.6000E-02, 6.5100E-02, 6.3000E-02, 
            5.7100E-02, 4.8500E-02, 3.8600E-02, 2.8900E-02, 2.0400E-02, 
            9.1000E-03, 2.5000E-03, 2.3000E-03, 9.8000E-04, 3.0000E-04, 
            3.2000E-05, 1.2000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {4.4100E-02, 4.4100E-02, 4.4100E-02, 4.4100E-02, 
            4.4100E-02, 4.4100E-02, 4.4100E-02, 4.4100E-02, 4.4100E-02, 
            4.4100E-02, 4.4100E-02, 4.4100E-02, 4.4100E-02, 4.4100E-02, 
            4.4100E-02, 4.4100E-02, 4.4100E-02, 4.4100E-02, 4.3900E-02, 
            4.3400E-02, 4.2000E-02, 3.9600E-02, 3.6400E-02, 3.2400E-02, 
            2.4000E-02, 8.4000E-03, 2.6000E-03, 2.7000E-04, 3.8000E-05, 
            1.7000E-06, 2.5000E-08} );

    subshell_half_profiles[8] = 
      std::vector<double>( {4.4700E-02, 4.4700E-02, 4.4700E-02, 4.4700E-02, 
            4.4700E-02, 4.4700E-02, 4.4700E-02, 4.4700E-02, 4.4700E-02, 
            4.4700E-02, 4.4700E-02, 4.4700E-02, 4.4700E-02, 4.4700E-02, 
            4.4700E-02, 4.4700E-02, 4.4600E-02, 4.4600E-02, 4.4500E-02, 
            4.3900E-02, 4.2400E-02, 4.0000E-02, 3.6600E-02, 3.2400E-02, 
            2.4000E-02, 8.1000E-03, 2.4000E-03, 2.4000E-04, 3.2000E-05, 
            1.3000E-06, 1.5000E-08} );

    subshell_half_profiles[9] = 
      std::vector<double>( {2.3400E-01, 2.3400E-01, 2.3300E-01, 2.3300E-01, 
            2.3200E-01, 2.2800E-01, 2.2400E-01, 2.1800E-01, 2.1100E-01, 
            2.0400E-01, 1.9500E-01, 1.7700E-01, 1.5700E-01, 1.3600E-01, 
            1.1600E-01, 9.6800E-02, 7.9900E-02, 5.2900E-02, 3.0000E-02, 
            2.1000E-02, 2.0400E-02, 1.6300E-02, 1.0600E-02, 5.9200E-03, 
            2.2000E-03, 1.5000E-03, 5.4000E-04, 5.9000E-05, 5.2000E-05, 
            2.3000E-05, 3.4000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.5000E-01, 1.5000E-01, 1.5000E-01, 1.5000E-01, 
            1.5000E-01, 1.5000E-01, 1.5000E-01, 1.5000E-01, 1.4900E-01, 
            1.4900E-01, 1.4800E-01, 1.4700E-01, 1.4400E-01, 1.3900E-01, 
            1.3300E-01, 1.2600E-01, 1.1800E-01, 9.8200E-02, 6.7500E-02, 
            2.8900E-02, 1.2200E-02, 8.4800E-03, 8.2800E-03, 7.7700E-03, 
            4.8000E-03, 6.4000E-04, 4.3000E-04, 2.4000E-04, 8.3000E-05, 
            1.1000E-05, 5.7000E-07} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.5600E-01, 1.5600E-01, 1.5600E-01, 1.5600E-01, 
            1.5600E-01, 1.5600E-01, 1.5600E-01, 1.5500E-01, 1.5500E-01, 
            1.5500E-01, 1.5400E-01, 1.5200E-01, 1.4800E-01, 1.4300E-01, 
            1.3600E-01, 1.2800E-01, 1.1900E-01, 9.6900E-02, 6.4200E-02, 
            2.5900E-02, 1.1300E-02, 8.7400E-03, 8.6200E-03, 7.7700E-03, 
            4.4000E-03, 5.9000E-04, 4.7000E-04, 2.2000E-04, 6.7000E-05, 
            7.2000E-06, 2.6000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.2500E-01, 1.2500E-01, 1.2500E-01, 1.2500E-01, 
            1.2500E-01, 1.2500E-01, 1.2500E-01, 1.2500E-01, 1.2500E-01, 
            1.2500E-01, 1.2500E-01, 1.2400E-01, 1.2400E-01, 1.2300E-01, 
            1.2100E-01, 1.1800E-01, 1.1500E-01, 1.0400E-01, 8.4200E-02, 
            4.8400E-02, 2.3000E-02, 9.9700E-03, 4.8200E-03, 3.3400E-03, 
            3.1000E-03, 1.7000E-03, 5.6000E-04, 5.9000E-05, 8.3000E-06, 
            3.6000E-07, 5.4000E-09} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.2600E-01, 1.2600E-01, 1.2600E-01, 1.2600E-01, 
            1.2600E-01, 1.2600E-01, 1.2600E-01, 1.2600E-01, 1.2600E-01, 
            1.2600E-01, 1.2600E-01, 1.2600E-01, 1.2500E-01, 1.2400E-01, 
            1.2200E-01, 1.1900E-01, 1.1500E-01, 1.0500E-01, 8.4000E-02, 
            4.7500E-02, 2.2200E-02, 9.5100E-03, 4.6500E-03, 3.3100E-03, 
            3.1000E-03, 1.6000E-03, 5.3000E-04, 5.3000E-05, 7.1000E-06, 
            2.8000E-07, 3.3000E-09} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.4900E-01, 1.4900E-01, 1.4900E-01, 1.4900E-01, 
            1.4900E-01, 1.4900E-01, 1.4800E-01, 1.4800E-01, 1.4800E-01, 
            1.4800E-01, 1.4700E-01, 1.4500E-01, 1.4000E-01, 1.3500E-01, 
            1.2800E-01, 1.2000E-01, 1.1200E-01, 9.4600E-02, 7.1200E-02, 
            4.2100E-02, 2.4100E-02, 1.3700E-02, 7.7800E-03, 4.4500E-03, 
            1.5000E-03, 1.3000E-04, 1.6000E-05, 5.4000E-07, 3.7000E-08, 
            6.0000E-10, 3.8000E-12} );

    subshell_half_profiles[15] = 
      std::vector<double>( {6.0900E-01, 6.0700E-01, 5.9900E-01, 5.8600E-01, 
            5.6800E-01, 5.2000E-01, 4.6100E-01, 3.9500E-01, 3.2700E-01, 
            2.6400E-01, 2.0700E-01, 1.2100E-01, 7.0900E-02, 4.8300E-02, 
            4.1100E-02, 4.0100E-02, 3.9900E-02, 3.4500E-02, 1.9400E-02, 
            5.1700E-03, 3.4500E-03, 3.2200E-03, 2.3100E-03, 1.3300E-03, 
            4.0000E-04, 2.5000E-04, 9.1000E-05, 9.2000E-06, 8.0000E-06, 
            3.6000E-06, 5.3000E-07} );

    subshell_half_profiles[16] = 
      std::vector<double>( {4.1700E-01, 4.1700E-01, 4.1600E-01, 4.1600E-01, 
            4.1600E-01, 4.1200E-01, 4.0300E-01, 3.8800E-01, 3.6600E-01, 
            3.3700E-01, 3.0300E-01, 2.2800E-01, 1.5600E-01, 9.9000E-02, 
            5.9600E-02, 3.5700E-02, 2.3000E-02, 1.5300E-02, 1.4700E-02, 
            8.7400E-03, 3.2100E-03, 1.3300E-03, 1.0600E-03, 1.0400E-03, 
            7.2000E-04, 9.3000E-05, 5.5000E-05, 3.2000E-05, 1.1000E-05, 
            1.4000E-06, 7.5000E-08} );

    subshell_half_profiles[17] = 
      std::vector<double>( {4.4200E-01, 4.4200E-01, 4.4200E-01, 4.4100E-01, 
            4.4000E-01, 4.3600E-01, 4.2500E-01, 4.0500E-01, 3.7800E-01, 
            3.4300E-01, 3.0300E-01, 2.1800E-01, 1.4300E-01, 8.6500E-02, 
            5.0200E-02, 2.9700E-02, 1.9900E-02, 1.5100E-02, 1.4300E-02, 
            7.5000E-03, 2.5500E-03, 1.1800E-03, 1.0500E-03, 1.0100E-03, 
            6.2000E-04, 7.7000E-05, 5.7000E-05, 2.7000E-05, 8.4000E-06, 
            9.0000E-07, 3.2000E-08} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.1500E+00, 2.0500E+00, 1.7800E+00, 1.4200E+00, 
            1.0300E+00, 4.4100E-01, 1.6200E-01, 7.9900E-02, 6.8600E-02, 
            6.7700E-02, 6.1600E-02, 3.8700E-02, 1.9200E-02, 8.7300E-03, 
            4.5000E-03, 3.2800E-03, 3.1100E-03, 2.9300E-03, 1.7800E-03, 
            4.4200E-04, 2.4900E-04, 2.3700E-04, 1.7300E-04, 1.0000E-04, 
            3.0000E-05, 1.8000E-05, 6.6000E-06, 6.6000E-07, 5.7000E-07, 
            2.6000E-07, 3.8000E-08} );
  }
};

//! The default Compton profile generator implementation for A=60
template<>
struct DefaultComptonProfileGeneratorImpl<60u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 19 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.3200E-02, 1.3200E-02, 1.3200E-02, 1.3200E-02, 
            1.3200E-02, 1.3200E-02, 1.3200E-02, 1.3200E-02, 1.3200E-02, 
            1.3200E-02, 1.3200E-02, 1.3200E-02, 1.3200E-02, 1.3200E-02, 
            1.3200E-02, 1.3200E-02, 1.3200E-02, 1.3100E-02, 1.3100E-02, 
            1.3000E-02, 1.2900E-02, 1.2800E-02, 1.2700E-02, 1.2600E-02, 
            1.2000E-02, 1.1000E-02, 9.8000E-03, 7.1000E-03, 4.8000E-03, 
            2.0000E-03, 3.9000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {4.7000E-02, 4.7000E-02, 4.7000E-02, 4.7000E-02, 
            4.7000E-02, 4.7000E-02, 4.7000E-02, 4.6900E-02, 4.6900E-02, 
            4.6800E-02, 4.6800E-02, 4.6600E-02, 4.6400E-02, 4.6200E-02, 
            4.6000E-02, 4.5700E-02, 4.5400E-02, 4.4600E-02, 4.3400E-02, 
            4.0700E-02, 3.7600E-02, 3.4100E-02, 3.0400E-02, 2.6800E-02, 
            2.0000E-02, 7.5000E-03, 2.5000E-03, 1.2000E-03, 1.0000E-03, 
            4.6000E-04, 7.2000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 
            2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 
            2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 
            2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3200E-02, 2.3200E-02, 
            2.3200E-02, 2.3000E-02, 2.2800E-02, 2.2500E-02, 2.2100E-02, 
            2.1000E-02, 1.6000E-02, 1.1000E-02, 4.1000E-03, 1.4000E-03, 
            2.0000E-04, 1.2000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 
            2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 
            2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 
            2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4700E-02, 
            2.4700E-02, 2.4500E-02, 2.4200E-02, 2.3900E-02, 2.3300E-02, 
            2.2000E-02, 1.6000E-02, 1.1000E-02, 3.5000E-03, 1.1000E-03, 
            1.3000E-04, 5.2000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.0600E-01, 1.0600E-01, 1.0600E-01, 1.0600E-01, 
            1.0600E-01, 1.0600E-01, 1.0500E-01, 1.0500E-01, 1.0400E-01, 
            1.0300E-01, 1.0200E-01, 1.0100E-01, 9.8200E-02, 9.5400E-02, 
            9.2400E-02, 8.9100E-02, 8.5600E-02, 7.7900E-02, 6.5700E-02, 
            4.5900E-02, 2.9700E-02, 1.8600E-02, 1.2100E-02, 8.9700E-03, 
            7.7000E-03, 5.5000E-03, 1.9000E-03, 2.6000E-04, 2.3000E-04, 
            1.1000E-04, 1.6000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {6.2800E-02, 6.2800E-02, 6.2800E-02, 6.2800E-02, 
            6.2800E-02, 6.2800E-02, 6.2800E-02, 6.2800E-02, 6.2800E-02, 
            6.2800E-02, 6.2700E-02, 6.2700E-02, 6.2700E-02, 6.2600E-02, 
            6.2500E-02, 6.2300E-02, 6.2100E-02, 6.1400E-02, 5.9800E-02, 
            5.5200E-02, 4.8200E-02, 3.9800E-02, 3.1000E-02, 2.2900E-02, 
            1.1000E-02, 2.4000E-03, 2.2000E-03, 1.1000E-03, 4.0000E-04, 
            5.5000E-05, 3.0000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {6.5400E-02, 6.5400E-02, 6.5400E-02, 6.5400E-02, 
            6.5400E-02, 6.5400E-02, 6.5400E-02, 6.5400E-02, 6.5400E-02, 
            6.5400E-02, 6.5400E-02, 6.5300E-02, 6.5300E-02, 6.5200E-02, 
            6.5100E-02, 6.4900E-02, 6.4600E-02, 6.3800E-02, 6.1900E-02, 
            5.6400E-02, 4.8400E-02, 3.9000E-02, 2.9600E-02, 2.1300E-02, 
            9.8000E-03, 2.5000E-03, 2.3000E-03, 1.0000E-03, 3.2000E-04, 
            3.6000E-05, 1.3000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {4.3100E-02, 4.3100E-02, 4.3100E-02, 4.3100E-02, 
            4.3100E-02, 4.3100E-02, 4.3100E-02, 4.3100E-02, 4.3100E-02, 
            4.3100E-02, 4.3100E-02, 4.3100E-02, 4.3100E-02, 4.3100E-02, 
            4.3100E-02, 4.3100E-02, 4.3100E-02, 4.3100E-02, 4.2900E-02, 
            4.2400E-02, 4.1200E-02, 3.9100E-02, 3.6100E-02, 3.2400E-02, 
            2.4000E-02, 8.9000E-03, 2.8000E-03, 3.0000E-04, 4.3000E-05, 
            2.0000E-06, 3.0000E-08} );

    subshell_half_profiles[8] = 
      std::vector<double>( {4.3600E-02, 4.3600E-02, 4.3600E-02, 4.3600E-02, 
            4.3600E-02, 4.3600E-02, 4.3600E-02, 4.3600E-02, 4.3600E-02, 
            4.3600E-02, 4.3600E-02, 4.3600E-02, 4.3600E-02, 4.3600E-02, 
            4.3600E-02, 4.3600E-02, 4.3600E-02, 4.3600E-02, 4.3500E-02, 
            4.2900E-02, 4.1700E-02, 3.9400E-02, 3.6300E-02, 3.2500E-02, 
            2.4000E-02, 8.6000E-03, 2.6000E-03, 2.7000E-04, 3.7000E-05, 
            1.5000E-06, 1.8000E-08} );

    subshell_half_profiles[9] = 
      std::vector<double>( {2.2800E-01, 2.2800E-01, 2.2800E-01, 2.2700E-01, 
            2.2600E-01, 2.2300E-01, 2.1900E-01, 2.1300E-01, 2.0700E-01, 
            2.0000E-01, 1.9200E-01, 1.7500E-01, 1.5600E-01, 1.3600E-01, 
            1.1600E-01, 9.8200E-02, 8.1600E-02, 5.4800E-02, 3.1100E-02, 
            2.0700E-02, 2.0200E-02, 1.6800E-02, 1.1200E-02, 6.5100E-03, 
            2.3000E-03, 1.6000E-03, 6.0000E-04, 6.1000E-05, 5.2000E-05, 
            2.5000E-05, 3.7000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.4600E-01, 1.4600E-01, 1.4600E-01, 1.4600E-01, 
            1.4600E-01, 1.4600E-01, 1.4600E-01, 1.4600E-01, 1.4600E-01, 
            1.4500E-01, 1.4500E-01, 1.4300E-01, 1.4000E-01, 1.3600E-01, 
            1.3100E-01, 1.2500E-01, 1.1700E-01, 9.8700E-02, 6.9300E-02, 
            3.0900E-02, 1.3100E-02, 8.5000E-03, 8.1400E-03, 7.8000E-03, 
            5.1000E-03, 7.1000E-04, 4.2000E-04, 2.5000E-04, 9.0000E-05, 
            1.2000E-05, 6.5000E-07} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.5200E-01, 1.5200E-01, 1.5200E-01, 1.5200E-01, 
            1.5200E-01, 1.5200E-01, 1.5200E-01, 1.5200E-01, 1.5100E-01, 
            1.5100E-01, 1.5000E-01, 1.4800E-01, 1.4500E-01, 1.4100E-01, 
            1.3400E-01, 1.2700E-01, 1.1800E-01, 9.7700E-02, 6.6200E-02, 
            2.7700E-02, 1.1900E-02, 8.6700E-03, 8.5200E-03, 7.8600E-03, 
            4.7000E-03, 6.3000E-04, 4.7000E-04, 2.3000E-04, 7.3000E-05, 
            8.1000E-06, 3.0000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.2100E-01, 1.2100E-01, 1.2100E-01, 1.2100E-01, 
            1.2100E-01, 1.2100E-01, 1.2100E-01, 1.2100E-01, 1.2100E-01, 
            1.2100E-01, 1.2100E-01, 1.2100E-01, 1.2000E-01, 1.1900E-01, 
            1.1800E-01, 1.1600E-01, 1.1200E-01, 1.0300E-01, 8.4700E-02, 
            5.0500E-02, 2.4900E-02, 1.1100E-02, 5.2900E-03, 3.4400E-03, 
            3.1000E-03, 1.8000E-03, 6.2000E-04, 6.8000E-05, 9.7000E-06, 
            4.3000E-07, 6.4000E-09} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 
            1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 
            1.2300E-01, 1.2300E-01, 1.2200E-01, 1.2200E-01, 1.2100E-01, 
            1.1900E-01, 1.1700E-01, 1.1300E-01, 1.0400E-01, 8.4700E-02, 
            4.9700E-02, 2.4100E-02, 1.0600E-02, 5.0700E-03, 3.3900E-03, 
            3.1000E-03, 1.7000E-03, 5.8000E-04, 6.1000E-05, 8.3000E-06, 
            3.3000E-07, 3.9000E-09} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.4100E-01, 1.4100E-01, 1.4100E-01, 1.4100E-01, 
            1.4100E-01, 1.4100E-01, 1.4100E-01, 1.4100E-01, 1.4100E-01, 
            1.4000E-01, 1.4000E-01, 1.3800E-01, 1.3500E-01, 1.3000E-01, 
            1.2400E-01, 1.1800E-01, 1.1000E-01, 9.5100E-02, 7.3300E-02, 
            4.4800E-02, 2.6400E-02, 1.5300E-02, 8.8900E-03, 5.1800E-03, 
            1.8000E-03, 1.6000E-04, 2.1000E-05, 7.1000E-07, 4.9000E-08, 
            8.2000E-10, 4.8000E-12} );

    subshell_half_profiles[15] = 
      std::vector<double>( {5.9700E-01, 5.9500E-01, 5.8700E-01, 5.7500E-01, 
            5.5800E-01, 5.1300E-01, 4.5700E-01, 3.9300E-01, 3.2900E-01, 
            2.6700E-01, 2.1100E-01, 1.2500E-01, 7.3800E-02, 4.9100E-02, 
            4.0500E-02, 3.9000E-02, 3.8900E-02, 3.4600E-02, 2.0500E-02, 
            5.5800E-03, 3.3700E-03, 3.2200E-03, 2.4200E-03, 1.4600E-03, 
            4.4000E-04, 2.5000E-04, 1.0000E-04, 9.5000E-06, 8.0000E-06, 
            3.8000E-06, 5.7000E-07} );

    subshell_half_profiles[16] = 
      std::vector<double>( {4.0700E-01, 4.0700E-01, 4.0700E-01, 4.0700E-01, 
            4.0600E-01, 4.0300E-01, 3.9500E-01, 3.8200E-01, 3.6100E-01, 
            3.3400E-01, 3.0300E-01, 2.3100E-01, 1.6100E-01, 1.0400E-01, 
            6.4100E-02, 3.8700E-02, 2.4500E-02, 1.5200E-02, 1.4300E-02, 
            9.1900E-03, 3.5700E-03, 1.4300E-03, 1.0400E-03, 1.0300E-03, 
            7.5000E-04, 1.0000E-04, 5.5000E-05, 3.3000E-05, 1.2000E-05, 
            1.6000E-06, 8.6000E-08} );

    subshell_half_profiles[17] = 
      std::vector<double>( {4.3400E-01, 4.3400E-01, 4.3400E-01, 4.3400E-01, 
            4.3300E-01, 4.2800E-01, 4.1800E-01, 4.0000E-01, 3.7400E-01, 
            3.4200E-01, 3.0300E-01, 2.2200E-01, 1.4800E-01, 9.1000E-02, 
            5.3500E-02, 3.1700E-02, 2.0600E-02, 1.4600E-02, 1.4000E-02, 
            7.8800E-03, 2.7900E-03, 1.2100E-03, 1.0200E-03, 9.9600E-04, 
            6.5000E-04, 8.3000E-05, 5.6000E-05, 2.9000E-05, 9.1000E-06, 
            9.9000E-07, 3.7000E-08} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.1300E+00, 2.0300E+00, 1.7700E+00, 1.4200E+00, 
            1.0400E+00, 4.5200E-01, 1.6700E-01, 7.9900E-02, 6.6400E-02, 
            6.5700E-02, 6.0600E-02, 3.9400E-02, 2.0100E-02, 9.2900E-03, 
            4.6700E-03, 3.2100E-03, 2.9500E-03, 2.8400E-03, 1.8200E-03, 
            4.7400E-04, 2.3900E-04, 2.2900E-04, 1.7600E-04, 1.0700E-04, 
            3.2000E-05, 1.8000E-05, 7.1000E-06, 6.7000E-07, 5.6000E-07, 
            2.7000E-07, 4.0000E-08} );
  }
};

//! The default Compton profile generator implementation for A=61
template<>
struct DefaultComptonProfileGeneratorImpl<61u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 19 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.2900E-02, 1.2900E-02, 1.2900E-02, 1.2900E-02, 
            1.2900E-02, 1.2900E-02, 1.2900E-02, 1.2900E-02, 1.2900E-02, 
            1.2900E-02, 1.2900E-02, 1.2900E-02, 1.2900E-02, 1.2900E-02, 
            1.2900E-02, 1.2900E-02, 1.2900E-02, 1.2900E-02, 1.2800E-02, 
            1.2800E-02, 1.2700E-02, 1.2600E-02, 1.2500E-02, 1.2300E-02, 
            1.2000E-02, 1.1000E-02, 9.7000E-03, 7.1000E-03, 4.9000E-03, 
            2.1000E-03, 4.2000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {4.6100E-02, 4.6100E-02, 4.6100E-02, 4.6100E-02, 
            4.6100E-02, 4.6000E-02, 4.6000E-02, 4.6000E-02, 4.5900E-02, 
            4.5900E-02, 4.5800E-02, 4.5700E-02, 4.5500E-02, 4.5300E-02, 
            4.5100E-02, 4.4800E-02, 4.4500E-02, 4.3800E-02, 4.2600E-02, 
            4.0100E-02, 3.7100E-02, 3.3800E-02, 3.0300E-02, 2.6800E-02, 
            2.0000E-02, 7.8000E-03, 2.7000E-03, 1.1000E-03, 1.0000E-03, 
            4.8000E-04, 7.8000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.2800E-02, 2.2800E-02, 2.2800E-02, 2.2800E-02, 
            2.2800E-02, 2.2800E-02, 2.2800E-02, 2.2800E-02, 2.2800E-02, 
            2.2800E-02, 2.2800E-02, 2.2800E-02, 2.2800E-02, 2.2800E-02, 
            2.2800E-02, 2.2800E-02, 2.2800E-02, 2.2800E-02, 2.2700E-02, 
            2.2700E-02, 2.2600E-02, 2.2400E-02, 2.2100E-02, 2.1700E-02, 
            2.1000E-02, 1.6000E-02, 1.1000E-02, 4.3000E-03, 1.5000E-03, 
            2.2000E-04, 1.3000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 
            2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 
            2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 
            2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 
            2.4200E-02, 2.4100E-02, 2.3800E-02, 2.3500E-02, 2.3000E-02, 
            2.2000E-02, 1.6000E-02, 1.1000E-02, 3.7000E-03, 1.2000E-03, 
            1.4000E-04, 5.8000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 
            1.0400E-01, 1.0300E-01, 1.0300E-01, 1.0200E-01, 1.0200E-01, 
            1.0100E-01, 1.0000E-01, 9.8500E-02, 9.6300E-02, 9.3700E-02, 
            9.0900E-02, 8.7800E-02, 8.4400E-02, 7.7200E-02, 6.5500E-02, 
            4.6500E-02, 3.0600E-02, 1.9300E-02, 1.2500E-02, 9.1400E-03, 
            7.6000E-03, 5.7000E-03, 2.1000E-03, 2.6000E-04, 2.3000E-04, 
            1.1000E-04, 1.8000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {6.1300E-02, 6.1300E-02, 6.1300E-02, 6.1300E-02, 
            6.1300E-02, 6.1300E-02, 6.1300E-02, 6.1300E-02, 6.1300E-02, 
            6.1300E-02, 6.1300E-02, 6.1300E-02, 6.1200E-02, 6.1200E-02, 
            6.1100E-02, 6.0900E-02, 6.0700E-02, 6.0100E-02, 5.8700E-02, 
            5.4400E-02, 4.8000E-02, 4.0000E-02, 3.1600E-02, 2.3800E-02, 
            1.2000E-02, 2.5000E-03, 2.1000E-03, 1.2000E-03, 4.3000E-04, 
            6.1000E-05, 3.4000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {6.4000E-02, 6.4000E-02, 6.4000E-02, 6.4000E-02, 
            6.4000E-02, 6.4000E-02, 6.4000E-02, 6.4000E-02, 6.4000E-02, 
            6.4000E-02, 6.4000E-02, 6.3900E-02, 6.3900E-02, 6.3800E-02, 
            6.3700E-02, 6.3500E-02, 6.3200E-02, 6.2500E-02, 6.0800E-02, 
            5.5800E-02, 4.8300E-02, 3.9400E-02, 3.0300E-02, 2.2100E-02, 
            1.0000E-02, 2.5000E-03, 2.3000E-03, 1.1000E-03, 3.5000E-04, 
            4.0000E-05, 1.5000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {4.2100E-02, 4.2100E-02, 4.2100E-02, 4.2100E-02, 
            4.2100E-02, 4.2100E-02, 4.2100E-02, 4.2100E-02, 4.2100E-02, 
            4.2100E-02, 4.2100E-02, 4.2100E-02, 4.2100E-02, 4.2100E-02, 
            4.2100E-02, 4.2100E-02, 4.2100E-02, 4.2100E-02, 4.2000E-02, 
            4.1500E-02, 4.0500E-02, 3.8600E-02, 3.5800E-02, 3.2400E-02, 
            2.5000E-02, 9.3000E-03, 3.0000E-03, 3.4000E-04, 4.9000E-05, 
            2.3000E-06, 3.5000E-08} );

    subshell_half_profiles[8] = 
      std::vector<double>( {4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 
            4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 
            4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 
            4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2500E-02, 
            4.2000E-02, 4.0900E-02, 3.8900E-02, 3.6100E-02, 3.2500E-02, 
            2.4000E-02, 9.1000E-03, 2.9000E-03, 3.0000E-04, 4.2000E-05, 
            1.8000E-06, 2.1000E-08} );

    subshell_half_profiles[9] = 
      std::vector<double>( {2.2300E-01, 2.2300E-01, 2.2200E-01, 2.2100E-01, 
            2.2000E-01, 2.1800E-01, 2.1400E-01, 2.0900E-01, 2.0300E-01, 
            1.9600E-01, 1.8900E-01, 1.7200E-01, 1.5400E-01, 1.3600E-01, 
            1.1700E-01, 9.9500E-02, 8.3300E-02, 5.6700E-02, 3.2200E-02, 
            2.0400E-02, 1.9900E-02, 1.7100E-02, 1.1900E-02, 7.1000E-03, 
            2.4000E-03, 1.6000E-03, 6.6000E-04, 6.4000E-05, 5.2000E-05, 
            2.6000E-05, 4.0000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 
            1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 
            1.4200E-01, 1.4100E-01, 1.4000E-01, 1.3700E-01, 1.3400E-01, 
            1.2900E-01, 1.2300E-01, 1.1600E-01, 9.8900E-02, 7.1000E-02, 
            3.2900E-02, 1.4000E-02, 8.5700E-03, 7.9900E-03, 7.7800E-03, 
            5.4000E-03, 7.9000E-04, 4.2000E-04, 2.6000E-04, 9.8000E-05, 
            1.4000E-05, 7.5000E-07} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.4800E-01, 1.4800E-01, 1.4800E-01, 1.4800E-01, 
            1.4800E-01, 1.4800E-01, 1.4800E-01, 1.4800E-01, 1.4800E-01, 
            1.4700E-01, 1.4700E-01, 1.4500E-01, 1.4200E-01, 1.3800E-01, 
            1.3200E-01, 1.2500E-01, 1.1700E-01, 9.8200E-02, 6.8000E-02, 
            2.9600E-02, 1.2600E-02, 8.6300E-03, 8.3900E-03, 7.9100E-03, 
            5.0000E-03, 6.8000E-04, 4.7000E-04, 2.5000E-04, 8.0000E-05, 
            9.0000E-06, 3.4000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.1800E-01, 1.1800E-01, 1.1800E-01, 1.1800E-01, 
            1.1800E-01, 1.1800E-01, 1.1800E-01, 1.1800E-01, 1.1800E-01, 
            1.1800E-01, 1.1800E-01, 1.1800E-01, 1.1700E-01, 1.1700E-01, 
            1.1500E-01, 1.1300E-01, 1.1000E-01, 1.0200E-01, 8.5100E-02, 
            5.2400E-02, 2.6800E-02, 1.2300E-02, 5.8200E-03, 3.5800E-03, 
            3.0000E-03, 1.9000E-03, 6.8000E-04, 7.8000E-05, 1.1000E-05, 
            5.1000E-07, 7.7000E-09} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.1900E-01, 1.1900E-01, 1.1900E-01, 1.1900E-01, 
            1.1900E-01, 1.1900E-01, 1.1900E-01, 1.1900E-01, 1.1900E-01, 
            1.1900E-01, 1.1900E-01, 1.1900E-01, 1.1900E-01, 1.1800E-01, 
            1.1600E-01, 1.1400E-01, 1.1100E-01, 1.0300E-01, 8.5100E-02, 
            5.1600E-02, 2.6000E-02, 1.1700E-02, 5.5600E-03, 3.5000E-03, 
            3.0000E-03, 1.8000E-03, 6.4000E-04, 6.9000E-05, 9.6000E-06, 
            3.9000E-07, 4.7000E-09} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.3400E-01, 1.3400E-01, 1.3400E-01, 1.3400E-01, 
            1.3400E-01, 1.3400E-01, 1.3400E-01, 1.3400E-01, 1.3400E-01, 
            1.3400E-01, 1.3400E-01, 1.3200E-01, 1.3000E-01, 1.2600E-01, 
            1.2100E-01, 1.1500E-01, 1.0900E-01, 9.5000E-02, 7.4700E-02, 
            4.7000E-02, 2.8400E-02, 1.6900E-02, 9.9800E-03, 5.9200E-03, 
            2.1000E-03, 2.0000E-04, 2.6000E-05, 9.2000E-07, 6.4000E-08, 
            1.1000E-09, 6.1000E-12} );

    subshell_half_profiles[15] = 
      std::vector<double>( {5.8600E-01, 5.8400E-01, 5.7600E-01, 5.6500E-01, 
            5.4900E-01, 5.0600E-01, 4.5300E-01, 3.9200E-01, 3.3000E-01, 
            2.7000E-01, 2.1600E-01, 1.3000E-01, 7.6700E-02, 5.0200E-02, 
            4.0200E-02, 3.7900E-02, 3.7800E-02, 3.4600E-02, 2.1500E-02, 
            6.0500E-03, 3.3000E-03, 3.1800E-03, 2.5100E-03, 1.5800E-03, 
            4.8000E-04, 2.5000E-04, 1.1000E-04, 1.0000E-05, 7.9000E-06, 
            4.0000E-06, 6.2000E-07} );

    subshell_half_profiles[16] = 
      std::vector<double>( {3.9900E-01, 3.9900E-01, 3.9900E-01, 3.9900E-01, 
            3.9800E-01, 3.9500E-01, 3.8800E-01, 3.7500E-01, 3.5700E-01, 
            3.3200E-01, 3.0200E-01, 2.3300E-01, 1.6600E-01, 1.1000E-01, 
            6.8400E-02, 4.1700E-02, 2.6200E-02, 1.5200E-02, 1.4000E-02, 
            9.5600E-03, 3.9400E-03, 1.5400E-03, 1.0300E-03, 1.0100E-03, 
            7.8000E-04, 1.2000E-04, 5.4000E-05, 3.5000E-05, 1.3000E-05, 
            1.8000E-06, 9.8000E-08} );

    subshell_half_profiles[17] = 
      std::vector<double>( {4.2700E-01, 4.2700E-01, 4.2700E-01, 4.2700E-01, 
            4.2600E-01, 4.2200E-01, 4.1200E-01, 3.9600E-01, 3.7100E-01, 
            3.4000E-01, 3.0400E-01, 2.2500E-01, 1.5200E-01, 9.5300E-02, 
            5.6700E-02, 3.3700E-02, 2.1500E-02, 1.4300E-02, 1.3700E-02, 
            8.2000E-03, 3.0500E-03, 1.2600E-03, 9.9000E-04, 9.7500E-04, 
            6.8000E-04, 8.9000E-05, 5.5000E-05, 3.0000E-05, 9.7000E-06, 
            1.1000E-06, 4.1000E-08} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.1100E+00, 2.0100E+00, 1.7600E+00, 1.4100E+00, 
            1.0500E+00, 4.6200E-01, 1.7300E-01, 8.0200E-02, 6.4400E-02, 
            6.3700E-02, 5.9600E-02, 3.9900E-02, 2.1000E-02, 9.8600E-03, 
            4.8800E-03, 3.1800E-03, 2.8200E-03, 2.7300E-03, 1.8600E-03, 
            5.0800E-04, 2.3100E-04, 2.2100E-04, 1.7800E-04, 1.1300E-04, 
            3.4000E-05, 1.7000E-05, 7.5000E-06, 6.9000E-07, 5.4000E-07, 
            2.8000E-07, 4.2000E-08} );
  }
};

//! The default Compton profile generator implementation for A=62
template<>
struct DefaultComptonProfileGeneratorImpl<62u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 19 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.2700E-02, 1.2700E-02, 1.2700E-02, 1.2700E-02, 
            1.2700E-02, 1.2700E-02, 1.2700E-02, 1.2700E-02, 1.2700E-02, 
            1.2700E-02, 1.2700E-02, 1.2700E-02, 1.2700E-02, 1.2700E-02, 
            1.2700E-02, 1.2700E-02, 1.2600E-02, 1.2600E-02, 1.2600E-02, 
            1.2500E-02, 1.2500E-02, 1.2400E-02, 1.2200E-02, 1.2100E-02, 
            1.2000E-02, 1.1000E-02, 9.7000E-03, 7.1000E-03, 4.9000E-03, 
            2.1000E-03, 4.4000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 
            4.5200E-02, 4.5100E-02, 4.5100E-02, 4.5100E-02, 4.5000E-02, 
            4.5000E-02, 4.4900E-02, 4.4800E-02, 4.4600E-02, 4.4400E-02, 
            4.4200E-02, 4.4000E-02, 4.3700E-02, 4.3000E-02, 4.1900E-02, 
            3.9500E-02, 3.6700E-02, 3.3600E-02, 3.0200E-02, 2.6800E-02, 
            2.0000E-02, 8.1000E-03, 2.8000E-03, 1.1000E-03, 1.0000E-03, 
            5.0000E-04, 8.4000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.2300E-02, 2.2300E-02, 2.2300E-02, 2.2300E-02, 
            2.2300E-02, 2.2300E-02, 2.2300E-02, 2.2300E-02, 2.2300E-02, 
            2.2300E-02, 2.2300E-02, 2.2300E-02, 2.2300E-02, 2.2300E-02, 
            2.2300E-02, 2.2300E-02, 2.2300E-02, 2.2300E-02, 2.2300E-02, 
            2.2200E-02, 2.2100E-02, 2.2000E-02, 2.1700E-02, 2.1400E-02, 
            2.0000E-02, 1.6000E-02, 1.1000E-02, 4.5000E-03, 1.6000E-03, 
            2.5000E-04, 1.5000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.3900E-02, 2.3900E-02, 2.3900E-02, 2.3900E-02, 
            2.3900E-02, 2.3900E-02, 2.3900E-02, 2.3900E-02, 2.3900E-02, 
            2.3900E-02, 2.3900E-02, 2.3900E-02, 2.3900E-02, 2.3900E-02, 
            2.3900E-02, 2.3900E-02, 2.3900E-02, 2.3900E-02, 2.3800E-02, 
            2.3800E-02, 2.3600E-02, 2.3400E-02, 2.3100E-02, 2.2600E-02, 
            2.1000E-02, 1.6000E-02, 1.1000E-02, 3.8000E-03, 1.2000E-03, 
            1.6000E-04, 6.5000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 
            1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0000E-01, 9.9600E-02, 
            9.9000E-02, 9.8300E-02, 9.6500E-02, 9.4400E-02, 9.2000E-02, 
            8.9400E-02, 8.6400E-02, 8.3300E-02, 7.6400E-02, 6.5300E-02, 
            4.7000E-02, 3.1300E-02, 2.0000E-02, 1.3000E-02, 9.3500E-03, 
            7.5000E-03, 5.8000E-03, 2.3000E-03, 2.7000E-04, 2.3000E-04, 
            1.2000E-04, 1.9000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {5.9900E-02, 5.9900E-02, 5.9900E-02, 5.9900E-02, 
            5.9900E-02, 5.9900E-02, 5.9900E-02, 5.9900E-02, 5.9900E-02, 
            5.9900E-02, 5.9900E-02, 5.9900E-02, 5.9900E-02, 5.9800E-02, 
            5.9700E-02, 5.9600E-02, 5.9400E-02, 5.8900E-02, 5.7500E-02, 
            5.3700E-02, 4.7700E-02, 4.0200E-02, 3.2200E-02, 2.4500E-02, 
            1.3000E-02, 2.5000E-03, 2.1000E-03, 1.2000E-03, 4.6000E-04, 
            6.7000E-05, 3.8000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {6.2600E-02, 6.2600E-02, 6.2600E-02, 6.2600E-02, 
            6.2600E-02, 6.2600E-02, 6.2600E-02, 6.2600E-02, 6.2600E-02, 
            6.2600E-02, 6.2600E-02, 6.2600E-02, 6.2500E-02, 6.2500E-02, 
            6.2300E-02, 6.2200E-02, 6.2000E-02, 6.1300E-02, 5.9700E-02, 
            5.5100E-02, 4.8100E-02, 3.9700E-02, 3.0900E-02, 2.2900E-02, 
            1.1000E-02, 2.5000E-03, 2.3000E-03, 1.1000E-03, 3.8000E-04, 
            4.4000E-05, 1.7000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {4.1200E-02, 4.1200E-02, 4.1200E-02, 4.1200E-02, 
            4.1200E-02, 4.1200E-02, 4.1200E-02, 4.1200E-02, 4.1200E-02, 
            4.1200E-02, 4.1200E-02, 4.1200E-02, 4.1200E-02, 4.1200E-02, 
            4.1200E-02, 4.1200E-02, 4.1200E-02, 4.1200E-02, 4.1100E-02, 
            4.0700E-02, 3.9700E-02, 3.8000E-02, 3.5500E-02, 3.2300E-02, 
            2.5000E-02, 9.8000E-03, 3.3000E-03, 3.8000E-04, 5.6000E-05, 
            2.6000E-06, 4.1000E-08} );

    subshell_half_profiles[8] = 
      std::vector<double>( {4.1700E-02, 4.1700E-02, 4.1700E-02, 4.1700E-02, 
            4.1700E-02, 4.1700E-02, 4.1700E-02, 4.1700E-02, 4.1700E-02, 
            4.1700E-02, 4.1700E-02, 4.1700E-02, 4.1700E-02, 4.1700E-02, 
            4.1700E-02, 4.1700E-02, 4.1700E-02, 4.1700E-02, 4.1600E-02, 
            4.1200E-02, 4.0200E-02, 3.8400E-02, 3.5800E-02, 3.2400E-02, 
            2.5000E-02, 9.5000E-03, 3.1000E-03, 3.4000E-04, 4.8000E-05, 
            2.0000E-06, 2.5000E-08} );

    subshell_half_profiles[9] = 
      std::vector<double>( {2.1700E-01, 2.1700E-01, 2.1700E-01, 2.1600E-01, 
            2.1500E-01, 2.1300E-01, 2.0900E-01, 2.0400E-01, 1.9900E-01, 
            1.9300E-01, 1.8600E-01, 1.7000E-01, 1.5300E-01, 1.3500E-01, 
            1.1800E-01, 1.0100E-01, 8.4800E-02, 5.8400E-02, 3.3300E-02, 
            2.0200E-02, 1.9600E-02, 1.7300E-02, 1.2500E-02, 7.7000E-03, 
            2.6000E-03, 1.6000E-03, 7.2000E-04, 6.9000E-05, 5.2000E-05, 
            2.7000E-05, 4.4000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3900E-01, 
            1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3900E-01, 
            1.3800E-01, 1.3800E-01, 1.3700E-01, 1.3400E-01, 1.3100E-01, 
            1.2700E-01, 1.2100E-01, 1.1500E-01, 9.9000E-02, 7.2500E-02, 
            3.4800E-02, 1.5000E-02, 8.7100E-03, 7.8500E-03, 7.7300E-03, 
            5.6000E-03, 8.8000E-04, 4.2000E-04, 2.8000E-04, 1.1000E-04, 
            1.5000E-05, 8.6000E-07} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.4500E-01, 1.4500E-01, 1.4500E-01, 1.4500E-01, 
            1.4500E-01, 1.4500E-01, 1.4500E-01, 1.4500E-01, 1.4400E-01, 
            1.4400E-01, 1.4400E-01, 1.4200E-01, 1.3900E-01, 1.3600E-01, 
            1.3000E-01, 1.2400E-01, 1.1600E-01, 9.8600E-02, 6.9600E-02, 
            3.1300E-02, 1.3400E-02, 8.6400E-03, 8.2500E-03, 7.9200E-03, 
            5.2000E-03, 7.3000E-04, 4.6000E-04, 2.6000E-04, 8.7000E-05, 
            1.0000E-05, 3.8000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.1500E-01, 1.1500E-01, 1.1500E-01, 1.1500E-01, 
            1.1500E-01, 1.1500E-01, 1.1500E-01, 1.1500E-01, 1.1500E-01, 
            1.1500E-01, 1.1500E-01, 1.1500E-01, 1.1400E-01, 1.1400E-01, 
            1.1200E-01, 1.1100E-01, 1.0800E-01, 1.0100E-01, 8.5200E-02, 
            5.4100E-02, 2.8700E-02, 1.3500E-02, 6.4200E-03, 3.7700E-03, 
            3.0000E-03, 2.0000E-03, 7.4000E-04, 8.8000E-05, 1.3000E-05, 
            6.0000E-07, 9.2000E-09} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 
            1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 
            1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1500E-01, 
            1.1400E-01, 1.1200E-01, 1.0900E-01, 1.0200E-01, 8.5300E-02, 
            5.3300E-02, 2.7800E-02, 1.2900E-02, 6.1000E-03, 3.6500E-03, 
            3.0000E-03, 1.9000E-03, 7.0000E-04, 7.8000E-05, 1.1000E-05, 
            4.5000E-07, 5.5000E-09} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.2900E-01, 1.2900E-01, 1.2900E-01, 1.2900E-01, 
            1.2900E-01, 1.2900E-01, 1.2900E-01, 1.2900E-01, 1.2900E-01, 
            1.2900E-01, 1.2800E-01, 1.2700E-01, 1.2500E-01, 1.2200E-01, 
            1.1800E-01, 1.1300E-01, 1.0700E-01, 9.4600E-02, 7.5600E-02, 
            4.8900E-02, 3.0200E-02, 1.8400E-02, 1.1100E-02, 6.6600E-03, 
            2.5000E-03, 2.4000E-04, 3.2000E-05, 1.2000E-06, 8.2000E-08, 
            1.4000E-09, 7.8000E-12} );

    subshell_half_profiles[15] = 
      std::vector<double>( {5.7500E-01, 5.7300E-01, 5.6600E-01, 5.5500E-01, 
            5.4000E-01, 5.0000E-01, 4.4900E-01, 3.9100E-01, 3.3100E-01, 
            2.7300E-01, 2.1900E-01, 1.3400E-01, 7.9700E-02, 5.1400E-02, 
            4.0000E-02, 3.7000E-02, 3.6800E-02, 3.4300E-02, 2.2400E-02, 
            6.5500E-03, 3.2500E-03, 3.1300E-03, 2.5700E-03, 1.6900E-03, 
            5.3000E-04, 2.5000E-04, 1.2000E-04, 1.1000E-05, 7.8000E-06, 
            4.2000E-06, 6.7000E-07} );

    subshell_half_profiles[16] = 
      std::vector<double>( {3.9100E-01, 3.9100E-01, 3.9100E-01, 3.9100E-01, 
            3.9000E-01, 3.8700E-01, 3.8100E-01, 3.6900E-01, 3.5200E-01, 
            3.2900E-01, 3.0100E-01, 2.3600E-01, 1.7000E-01, 1.1400E-01, 
            7.2600E-02, 4.4800E-02, 2.8100E-02, 1.5300E-02, 1.3600E-02, 
            9.8700E-03, 4.3100E-03, 1.6700E-03, 1.0300E-03, 9.8500E-04, 
            8.1000E-04, 1.3000E-04, 5.3000E-05, 3.6000E-05, 1.4000E-05, 
            2.0000E-06, 1.1000E-07} );

    subshell_half_profiles[17] = 
      std::vector<double>( {4.2000E-01, 4.2000E-01, 4.2000E-01, 4.2000E-01, 
            4.1900E-01, 4.1600E-01, 4.0700E-01, 3.9100E-01, 3.6800E-01, 
            3.3800E-01, 3.0400E-01, 2.2800E-01, 1.5600E-01, 9.9300E-02, 
            5.9900E-02, 3.5700E-02, 2.2500E-02, 1.4000E-02, 1.3300E-02, 
            8.4600E-03, 3.3000E-03, 1.3200E-03, 9.6500E-04, 9.5000E-04, 
            7.0000E-04, 9.7000E-05, 5.4000E-05, 3.1000E-05, 1.0000E-05, 
            1.2000E-06, 4.6000E-08} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.0900E+00, 2.0000E+00, 1.7500E+00, 1.4100E+00, 
            1.0500E+00, 4.7200E-01, 1.7800E-01, 8.0800E-02, 6.2600E-02, 
            6.1800E-02, 5.8500E-02, 4.0300E-02, 2.1800E-02, 1.0400E-02, 
            5.1200E-03, 3.1800E-03, 2.7100E-03, 2.6300E-03, 1.8800E-03, 
            5.4500E-04, 2.2600E-04, 2.1300E-04, 1.7900E-04, 1.1900E-04, 
            3.7000E-05, 1.7000E-05, 8.0000E-06, 7.2000E-07, 5.2000E-07, 
            2.8000E-07, 4.5000E-08} );
  }
};

//! The default Compton profile generator implementation for A=63
template<>
struct DefaultComptonProfileGeneratorImpl<63u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 20 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.2400E-02, 1.2400E-02, 1.2400E-02, 1.2400E-02, 
            1.2400E-02, 1.2400E-02, 1.2400E-02, 1.2400E-02, 1.2400E-02, 
            1.2400E-02, 1.2400E-02, 1.2400E-02, 1.2400E-02, 1.2400E-02, 
            1.2400E-02, 1.2400E-02, 1.2400E-02, 1.2400E-02, 1.2400E-02, 
            1.2300E-02, 1.2200E-02, 1.2100E-02, 1.2000E-02, 1.1900E-02, 
            1.1900E-02, 1.1000E-02, 9.6000E-03, 7.1000E-03, 5.0000E-03, 
            2.2000E-03, 4.6000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {4.4300E-02, 4.4300E-02, 4.4300E-02, 4.4300E-02, 
            4.4300E-02, 4.4200E-02, 4.4200E-02, 4.4200E-02, 4.4100E-02, 
            4.4100E-02, 4.4100E-02, 4.3900E-02, 4.3800E-02, 4.3600E-02, 
            4.3400E-02, 4.3100E-02, 4.2900E-02, 4.2300E-02, 4.1200E-02, 
            3.9000E-02, 3.6300E-02, 3.3300E-02, 3.0100E-02, 2.6800E-02, 
            2.0000E-02, 8.5000E-03, 3.0000E-03, 1.1000E-03, 1.0000E-03, 
            5.2000E-04, 9.0000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.1900E-02, 2.1900E-02, 2.1900E-02, 2.1900E-02, 
            2.1900E-02, 2.1900E-02, 2.1900E-02, 2.1900E-02, 2.1900E-02, 
            2.1900E-02, 2.1900E-02, 2.1900E-02, 2.1900E-02, 2.1900E-02, 
            2.1900E-02, 2.1800E-02, 2.1800E-02, 2.1800E-02, 2.1800E-02, 
            2.1800E-02, 2.1700E-02, 2.1500E-02, 2.1300E-02, 2.1000E-02, 
            2.0000E-02, 1.6000E-02, 1.1000E-02, 4.6100E-03, 1.7000E-03, 
            2.7000E-04, 1.7000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3400E-02, 
            2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3400E-02, 
            2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3400E-02, 
            2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3400E-02, 
            2.3300E-02, 2.3200E-02, 2.3000E-02, 2.2700E-02, 2.2300E-02, 
            2.1000E-02, 1.6000E-02, 1.1000E-02, 4.0000E-03, 1.3000E-03, 
            1.7000E-04, 7.2000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {9.9200E-02, 9.9200E-02, 9.9200E-02, 9.9100E-02, 
            9.9000E-02, 9.8800E-02, 9.8500E-02, 9.8000E-02, 9.7500E-02, 
            9.6900E-02, 9.6200E-02, 9.4600E-02, 9.2700E-02, 9.0400E-02, 
            8.7900E-02, 8.5100E-02, 8.2100E-02, 7.5600E-02, 6.5100E-02, 
            4.7400E-02, 3.2100E-02, 2.0800E-02, 1.3500E-02, 9.5900E-03, 
            7.4000E-03, 6.0000E-03, 2.4000E-03, 2.8000E-04, 2.2000E-04, 
            1.2000E-04, 2.1000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {5.8600E-02, 5.8600E-02, 5.8600E-02, 5.8600E-02, 
            5.8600E-02, 5.8600E-02, 5.8600E-02, 5.8600E-02, 5.8600E-02, 
            5.8600E-02, 5.8600E-02, 5.8600E-02, 5.8500E-02, 5.8500E-02, 
            5.8400E-02, 5.8300E-02, 5.8100E-02, 5.7600E-02, 5.6400E-02, 
            5.2900E-02, 4.7300E-02, 4.0300E-02, 3.2600E-02, 2.5200E-02, 
            1.3000E-02, 2.6000E-03, 2.1000E-03, 1.3000E-03, 5.0000E-04, 
            7.4000E-05, 4.3000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {6.1300E-02, 6.1300E-02, 6.1300E-02, 6.1300E-02, 
            6.1300E-02, 6.1300E-02, 6.1300E-02, 6.1300E-02, 6.1300E-02, 
            6.1300E-02, 6.1300E-02, 6.1300E-02, 6.1200E-02, 6.1200E-02, 
            6.1100E-02, 6.0900E-02, 6.0700E-02, 6.0100E-02, 5.8700E-02, 
            5.4400E-02, 4.7900E-02, 3.9900E-02, 3.1500E-02, 2.3600E-02, 
            1.2000E-02, 2.6000E-03, 2.3000E-03, 1.2000E-03, 4.0000E-04, 
            4.9000E-05, 1.9000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {4.0300E-02, 4.0300E-02, 4.0300E-02, 4.0300E-02, 
            4.0300E-02, 4.0300E-02, 4.0300E-02, 4.0300E-02, 4.0300E-02, 
            4.0300E-02, 4.0300E-02, 4.0300E-02, 4.0300E-02, 4.0300E-02, 
            4.0300E-02, 4.0300E-02, 4.0300E-02, 4.0200E-02, 4.0200E-02, 
            3.9800E-02, 3.9000E-02, 3.7400E-02, 3.5100E-02, 3.2200E-02, 
            2.5000E-02, 1.0000E-02, 3.5000E-03, 4.2000E-04, 6.4000E-05, 
            3.1000E-06, 4.9000E-08} );

    subshell_half_profiles[8] = 
      std::vector<double>( {4.0800E-02, 4.0800E-02, 4.0800E-02, 4.0800E-02, 
            4.0800E-02, 4.0800E-02, 4.0800E-02, 4.0800E-02, 4.0800E-02, 
            4.0800E-02, 4.0800E-02, 4.0800E-02, 4.0800E-02, 4.0800E-02, 
            4.0800E-02, 4.0800E-02, 4.0800E-02, 4.0800E-02, 4.0700E-02, 
            4.0300E-02, 3.9400E-02, 3.7800E-02, 3.5400E-02, 3.2400E-02, 
            2.5000E-02, 1.0000E-02, 3.3000E-03, 3.8000E-04, 5.5000E-05, 
            2.4000E-06, 2.9000E-08} );

    subshell_half_profiles[9] = 
      std::vector<double>( {2.1200E-01, 2.1200E-01, 2.1200E-01, 2.1100E-01, 
            2.1000E-01, 2.0800E-01, 2.0500E-01, 2.0000E-01, 1.9500E-01, 
            1.8900E-01, 1.8300E-01, 1.6800E-01, 1.5200E-01, 1.3500E-01, 
            1.1800E-01, 1.0100E-01, 8.6100E-02, 6.0100E-02, 3.4600E-02, 
            2.0100E-02, 1.9200E-02, 1.7400E-02, 1.3000E-02, 8.2900E-03, 
            2.9000E-03, 1.6000E-03, 7.8000E-04, 7.4000E-05, 5.1000E-05, 
            2.9000E-05, 4.8000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.3500E-01, 1.3500E-01, 1.3500E-01, 1.3500E-01, 
            1.3500E-01, 1.3500E-01, 1.3500E-01, 1.3500E-01, 1.3500E-01, 
            1.3500E-01, 1.3500E-01, 1.3300E-01, 1.3100E-01, 1.2900E-01, 
            1.2500E-01, 1.2000E-01, 1.1400E-01, 9.8900E-02, 7.3800E-02, 
            3.6800E-02, 1.6100E-02, 8.9300E-03, 7.7200E-03, 7.6400E-03, 
            5.9000E-03, 9.8000E-04, 4.1000E-04, 2.9000E-04, 1.1000E-04, 
            1.7000E-05, 9.8000E-07} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 
            1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4100E-01, 1.4100E-01, 
            1.4100E-01, 1.4000E-01, 1.3900E-01, 1.3700E-01, 1.3300E-01, 
            1.2800E-01, 1.2300E-01, 1.1500E-01, 9.8800E-02, 7.1100E-02, 
            3.3100E-02, 1.4200E-02, 8.7000E-03, 8.1100E-03, 7.9000E-03, 
            5.5000E-03, 8.0000E-04, 4.6000E-04, 2.7000E-04, 9.4000E-05, 
            1.1000E-05, 4.3000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.1200E-01, 1.1200E-01, 1.1200E-01, 1.1200E-01, 
            1.1200E-01, 1.1200E-01, 1.1200E-01, 1.1200E-01, 1.1200E-01, 
            1.1200E-01, 1.1200E-01, 1.1200E-01, 1.1200E-01, 1.1100E-01, 
            1.1000E-01, 1.0800E-01, 1.0600E-01, 9.9600E-02, 8.5200E-02, 
            5.5700E-02, 3.0500E-02, 1.4800E-02, 7.0800E-03, 4.0000E-03, 
            2.9000E-03, 2.1000E-03, 8.1000E-04, 9.9000E-05, 1.5000E-05, 
            7.0000E-07, 1.1000E-08} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.1400E-01, 1.1400E-01, 1.1400E-01, 1.1400E-01, 
            1.1400E-01, 1.1400E-01, 1.1400E-01, 1.1400E-01, 1.1400E-01, 
            1.1400E-01, 1.1400E-01, 1.1300E-01, 1.1300E-01, 1.1200E-01, 
            1.1100E-01, 1.1000E-01, 1.0700E-01, 1.0000E-01, 8.5400E-02, 
            5.4900E-02, 2.9600E-02, 1.4100E-02, 6.7000E-03, 3.8500E-03, 
            3.0000E-03, 2.0000E-03, 7.6000E-04, 8.8000E-05, 1.3000E-05, 
            5.3000E-07, 6.5000E-09} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.2400E-01, 1.2400E-01, 1.2400E-01, 1.2400E-01, 
            1.2400E-01, 1.2400E-01, 1.2400E-01, 1.2400E-01, 1.2400E-01, 
            1.2400E-01, 1.2400E-01, 1.2300E-01, 1.2100E-01, 1.1800E-01, 
            1.1500E-01, 1.1000E-01, 1.0500E-01, 9.3900E-02, 7.6200E-02, 
            5.0500E-02, 3.1900E-02, 1.9800E-02, 1.2100E-02, 7.4200E-03, 
            2.8000E-03, 2.9000E-04, 3.9000E-05, 1.5000E-06, 1.1000E-07, 
            1.8000E-09, 9.9000E-12} );

    subshell_half_profiles[15] = 
      std::vector<double>( {1.3000E-01, 1.3000E-01, 1.3000E-01, 1.3000E-01, 
            1.3000E-01, 1.3000E-01, 1.3000E-01, 1.3000E-01, 1.3000E-01, 
            1.3000E-01, 1.3000E-01, 1.2800E-01, 1.2500E-01, 1.2200E-01, 
            1.1700E-01, 1.1200E-01, 1.0600E-01, 9.3000E-02, 7.4400E-02, 
            4.8400E-02, 3.0300E-02, 1.8600E-02, 1.1400E-02, 6.9300E-03, 
            2.6000E-03, 2.6000E-04, 3.5000E-05, 1.3000E-06, 8.9000E-08, 
            1.4000E-09, 6.6000E-12} );

    subshell_half_profiles[16] = 
      std::vector<double>( {5.6400E-01, 5.6200E-01, 5.5600E-01, 5.4600E-01, 
            5.3100E-01, 4.9300E-01, 4.4400E-01, 3.8900E-01, 3.3100E-01, 
            2.7500E-01, 2.2300E-01, 1.3800E-01, 8.2900E-02, 5.2900E-02, 
            4.0000E-02, 3.6200E-02, 3.5800E-02, 3.4000E-02, 2.3200E-02, 
            7.1200E-03, 3.2400E-03, 3.0800E-03, 2.6300E-03, 1.8000E-03, 
            5.9000E-04, 2.5000E-04, 1.3000E-04, 1.2000E-05, 7.8000E-06, 
            4.4000E-06, 7.3000E-07} );

    subshell_half_profiles[17] = 
      std::vector<double>( {3.8400E-01, 3.8400E-01, 3.8400E-01, 3.8300E-01, 
            3.8300E-01, 3.8100E-01, 3.7500E-01, 3.6400E-01, 3.4800E-01, 
            3.2600E-01, 2.9900E-01, 2.3700E-01, 1.7400E-01, 1.1900E-01, 
            7.6700E-02, 4.7800E-02, 3.0000E-02, 1.5500E-02, 1.3100E-02, 
            1.0100E-02, 4.6500E-03, 1.8200E-03, 1.0400E-03, 9.5500E-04, 
            8.2000E-04, 1.5000E-04, 5.2000E-05, 3.7000E-05, 1.5000E-05, 
            2.2000E-06, 1.3000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {4.1300E-01, 4.1300E-01, 4.1300E-01, 4.1300E-01, 
            4.1200E-01, 4.0900E-01, 4.0000E-01, 3.8600E-01, 3.6400E-01, 
            3.3600E-01, 3.0300E-01, 2.3000E-01, 1.6000E-01, 1.0400E-01, 
            6.3500E-02, 3.8100E-02, 2.3800E-02, 1.3900E-02, 1.2900E-02, 
            8.7500E-03, 3.5800E-03, 1.4100E-03, 9.5200E-04, 9.3000E-04, 
            7.2000E-04, 1.1000E-04, 5.3000E-05, 3.2000E-05, 1.1000E-05, 
            1.3000E-06, 5.1000E-08} );

    subshell_half_profiles[19] = 
      std::vector<double>( {2.0700E+00, 1.9800E+00, 1.7400E+00, 1.4100E+00, 
            1.0600E+00, 4.8200E-01, 1.8400E-01, 8.1700E-02, 6.1000E-02, 
            5.9900E-02, 5.7300E-02, 4.0600E-02, 2.2600E-02, 1.1000E-02, 
            5.4100E-03, 3.2200E-03, 2.6200E-03, 2.5200E-03, 1.8900E-03, 
            5.8400E-04, 2.2300E-04, 2.0400E-04, 1.7800E-04, 1.2300E-04, 
            4.0000E-05, 1.7000E-05, 8.4000E-06, 7.6000E-07, 5.1000E-07, 
            2.9000E-07, 4.8000E-08} );
  }
};

//! The default Compton profile generator implementation for A=64
template<>
struct DefaultComptonProfileGeneratorImpl<64u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 21 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.2200E-02, 1.2200E-02, 1.2200E-02, 1.2200E-02, 
            1.2200E-02, 1.2200E-02, 1.2200E-02, 1.2200E-02, 1.2200E-02, 
            1.2200E-02, 1.2200E-02, 1.2200E-02, 1.2200E-02, 1.2200E-02, 
            1.2200E-02, 1.2200E-02, 1.2200E-02, 1.2200E-02, 1.2100E-02, 
            1.2100E-02, 1.2000E-02, 1.1900E-02, 1.1800E-02, 1.1700E-02, 
            1.1000E-02, 1.1000E-02, 9.5000E-03, 7.1000E-03, 5.0000E-03, 
            2.3000E-03, 4.9000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {4.3400E-02, 4.3400E-02, 4.3400E-02, 4.3400E-02, 
            4.3400E-02, 4.3400E-02, 4.3400E-02, 4.3300E-02, 4.3300E-02, 
            4.3300E-02, 4.3200E-02, 4.3100E-02, 4.2900E-02, 4.2800E-02, 
            4.2600E-02, 4.2300E-02, 4.2100E-02, 4.1500E-02, 4.0500E-02, 
            3.8400E-02, 3.5800E-02, 3.3000E-02, 2.9900E-02, 2.6800E-02, 
            2.1000E-02, 8.8000E-03, 3.2000E-03, 1.1000E-03, 1.0000E-03, 
            5.4000E-04, 9.6000E-05} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.1400E-02, 2.1400E-02, 2.1400E-02, 2.1400E-02, 
            2.1400E-02, 2.1400E-02, 2.1400E-02, 2.1400E-02, 2.1400E-02, 
            2.1400E-02, 2.1400E-02, 2.1400E-02, 2.1400E-02, 2.1400E-02, 
            2.1400E-02, 2.1400E-02, 2.1400E-02, 2.1400E-02, 2.1400E-02, 
            2.1400E-02, 2.1300E-02, 2.1100E-02, 2.0900E-02, 2.0600E-02, 
            2.0000E-02, 1.6000E-02, 1.2000E-02, 4.8000E-03, 1.8000E-03, 
            2.9000E-04, 1.9000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 
            2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 
            2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 
            2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 
            2.2900E-02, 2.2800E-02, 2.2600E-02, 2.2400E-02, 2.2000E-02, 
            2.1000E-02, 1.6000E-02, 1.1000E-02, 4.2000E-03, 1.4000E-03, 
            1.8000E-04, 8.0000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {9.7100E-02, 9.7100E-02, 9.7100E-02, 9.7000E-02, 
            9.6900E-02, 9.6700E-02, 9.6400E-02, 9.6000E-02, 9.5500E-02, 
            9.5000E-02, 9.4300E-02, 9.2800E-02, 9.0900E-02, 8.8800E-02, 
            8.6400E-02, 8.3800E-02, 8.1000E-02, 7.4800E-02, 6.4800E-02, 
            4.7800E-02, 3.2800E-02, 2.1500E-02, 1.4100E-02, 9.8600E-03, 
            7.3000E-03, 6.1000E-03, 2.6000E-03, 3.0000E-04, 2.2000E-04, 
            1.3000E-04, 2.2000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {5.7300E-02, 5.7300E-02, 5.7300E-02, 5.7300E-02, 
            5.7300E-02, 5.7300E-02, 5.7300E-02, 5.7300E-02, 5.7300E-02, 
            5.7300E-02, 5.7300E-02, 5.7300E-02, 5.7300E-02, 5.7200E-02, 
            5.7100E-02, 5.7000E-02, 5.6900E-02, 5.6500E-02, 5.5400E-02, 
            5.2100E-02, 4.7000E-02, 4.0400E-02, 3.3100E-02, 2.5900E-02, 
            1.4000E-02, 2.8000E-03, 2.0000E-03, 1.3000E-03, 5.3000E-04, 
            8.2000E-05, 4.9000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {6.0100E-02, 6.0100E-02, 6.0100E-02, 6.0100E-02, 
            6.0100E-02, 6.0100E-02, 6.0100E-02, 6.0100E-02, 6.0100E-02, 
            6.0100E-02, 6.0100E-02, 6.0000E-02, 6.0000E-02, 5.9900E-02, 
            5.9800E-02, 5.9700E-02, 5.9500E-02, 5.9000E-02, 5.7700E-02, 
            5.3700E-02, 4.7700E-02, 4.0100E-02, 3.2000E-02, 2.4300E-02, 
            1.2000E-02, 2.6000E-03, 2.3000E-03, 1.2000E-03, 4.3000E-04, 
            5.3000E-05, 2.2000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {3.9400E-02, 3.9400E-02, 3.9400E-02, 3.9400E-02, 
            3.9400E-02, 3.9400E-02, 3.9400E-02, 3.9400E-02, 3.9400E-02, 
            3.9400E-02, 3.9400E-02, 3.9400E-02, 3.9400E-02, 3.9400E-02, 
            3.9400E-02, 3.9400E-02, 3.9400E-02, 3.9400E-02, 3.9300E-02, 
            3.9000E-02, 3.8300E-02, 3.6900E-02, 3.4800E-02, 3.2000E-02, 
            2.5000E-02, 1.1000E-02, 3.8000E-03, 4.7000E-04, 7.2000E-05, 
            3.5000E-06, 5.7000E-08} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.9900E-02, 3.9900E-02, 3.9900E-02, 3.9900E-02, 
            3.9900E-02, 3.9900E-02, 3.9900E-02, 3.9900E-02, 3.9900E-02, 
            3.9900E-02, 3.9900E-02, 3.9900E-02, 3.9900E-02, 3.9900E-02, 
            3.9900E-02, 3.9900E-02, 3.9900E-02, 3.9900E-02, 3.9900E-02, 
            3.9500E-02, 3.8700E-02, 3.7300E-02, 3.5100E-02, 3.2200E-02, 
            2.5000E-02, 1.0000E-02, 3.6000E-03, 4.2000E-04, 6.2000E-05, 
            2.7000E-06, 3.4000E-08} );

    subshell_half_profiles[9] = 
      std::vector<double>( {2.0700E-01, 2.0700E-01, 2.0600E-01, 2.0600E-01, 
            2.0500E-01, 2.0300E-01, 2.0000E-01, 1.9600E-01, 1.9100E-01, 
            1.8500E-01, 1.7900E-01, 1.6600E-01, 1.5000E-01, 1.3400E-01, 
            1.1800E-01, 1.0200E-01, 8.7500E-02, 6.1900E-02, 3.6000E-02, 
            2.0200E-02, 1.8900E-02, 1.7600E-02, 1.3600E-02, 8.9100E-03, 
            3.1000E-03, 1.6000E-03, 8.5000E-04, 8.1000E-05, 5.1000E-05, 
            3.0000E-05, 5.2000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.3200E-01, 1.3200E-01, 1.3200E-01, 1.3200E-01, 
            1.3200E-01, 1.3200E-01, 1.3200E-01, 1.3200E-01, 1.3200E-01, 
            1.3100E-01, 1.3100E-01, 1.3000E-01, 1.2800E-01, 1.2600E-01, 
            1.2200E-01, 1.1800E-01, 1.1200E-01, 9.8700E-02, 7.5100E-02, 
            3.8800E-02, 1.7400E-02, 9.2800E-03, 7.6500E-03, 7.5800E-03, 
            6.1000E-03, 1.1000E-03, 4.1000E-04, 3.0000E-04, 1.2000E-04, 
            1.9000E-05, 1.1000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.3800E-01, 1.3800E-01, 1.3800E-01, 1.3800E-01, 
            1.3800E-01, 1.3800E-01, 1.3800E-01, 1.3800E-01, 1.3800E-01, 
            1.3700E-01, 1.3700E-01, 1.3600E-01, 1.3400E-01, 1.3000E-01, 
            1.2600E-01, 1.2100E-01, 1.1400E-01, 9.8900E-02, 7.2600E-02, 
            3.5100E-02, 1.5200E-02, 8.8800E-03, 8.0100E-03, 7.8900E-03, 
            5.7000E-03, 8.9000E-04, 4.6000E-04, 2.9000E-04, 1.0000E-04, 
            1.2000E-05, 4.9000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.0900E-01, 1.0900E-01, 1.0900E-01, 1.0900E-01, 
            1.0900E-01, 1.0900E-01, 1.0900E-01, 1.0900E-01, 1.0900E-01, 
            1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 
            1.0700E-01, 1.0500E-01, 1.0400E-01, 9.8000E-02, 8.5100E-02, 
            5.7400E-02, 3.2600E-02, 1.6400E-02, 7.9100E-03, 4.3300E-03, 
            2.9000E-03, 2.2000E-03, 8.8000E-04, 1.1000E-04, 1.7000E-05, 
            8.3000E-07, 1.3000E-08} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 
            1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 
            1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 1.0900E-01, 
            1.0800E-01, 1.0700E-01, 1.0500E-01, 9.9000E-02, 8.5400E-02, 
            5.6700E-02, 3.1600E-02, 1.5600E-02, 7.4500E-03, 4.1300E-03, 
            2.9000E-03, 2.1000E-03, 8.3000E-04, 1.0000E-04, 1.5000E-05, 
            6.2000E-07, 7.7000E-09} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1300E-01, 
            1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1300E-01, 
            1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1200E-01, 1.1000E-01, 
            1.0800E-01, 1.0500E-01, 1.0200E-01, 9.3400E-02, 7.8500E-02, 
            5.4400E-02, 3.5600E-02, 2.2600E-02, 1.4100E-02, 8.8000E-03, 
            3.4000E-03, 3.7000E-04, 5.1000E-05, 2.0000E-06, 1.4000E-07, 
            2.5000E-09, 1.4000E-11} );

    subshell_half_profiles[15] = 
      std::vector<double>( {1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 
            1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 
            1.1600E-01, 1.1600E-01, 1.1500E-01, 1.1400E-01, 1.1300E-01, 
            1.1000E-01, 1.0700E-01, 1.0300E-01, 9.3700E-02, 7.8000E-02, 
            5.3300E-02, 3.4500E-02, 2.1800E-02, 1.3500E-02, 8.3900E-03, 
            3.2000E-03, 3.4000E-04, 4.7000E-05, 1.8000E-06, 1.2000E-07, 
            2.0000E-09, 9.1000E-12} );

    subshell_half_profiles[16] = 
      std::vector<double>( {5.3800E-01, 5.3600E-01, 5.3100E-01, 5.2200E-01, 
            5.0900E-01, 4.7500E-01, 4.3200E-01, 3.8200E-01, 3.3000E-01, 
            2.7800E-01, 2.2900E-01, 1.4600E-01, 9.0000E-02, 5.7500E-02, 
            4.2100E-02, 3.6700E-02, 3.5700E-02, 3.4700E-02, 2.5200E-02, 
            8.2800E-03, 3.4500E-03, 3.1600E-03, 2.8100E-03, 2.0000E-03, 
            6.9000E-04, 2.6000E-04, 1.4000E-04, 1.3000E-05, 8.0000E-06, 
            4.8000E-06, 8.2000E-07} );

    subshell_half_profiles[17] = 
      std::vector<double>( {3.6600E-01, 3.6600E-01, 3.6600E-01, 3.6600E-01, 
            3.6600E-01, 3.6400E-01, 3.5900E-01, 3.5000E-01, 3.3600E-01, 
            3.1800E-01, 2.9500E-01, 2.4000E-01, 1.8100E-01, 1.2800E-01, 
            8.5500E-02, 5.4900E-02, 3.4900E-02, 1.7100E-02, 1.3300E-02, 
            1.0900E-02, 5.3800E-03, 2.1500E-03, 1.1300E-03, 9.8500E-04, 
            8.8000E-04, 1.7000E-04, 5.5000E-05, 4.0000E-05, 1.7000E-05, 
            2.6000E-06, 1.5000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {3.9100E-01, 3.9100E-01, 3.9100E-01, 3.9100E-01, 
            3.9000E-01, 3.8800E-01, 3.8100E-01, 3.7000E-01, 3.5200E-01, 
            3.2900E-01, 3.0100E-01, 2.3600E-01, 1.7000E-01, 1.1500E-01, 
            7.3000E-02, 4.5000E-02, 2.8200E-02, 1.5200E-02, 1.3400E-02, 
            9.7700E-03, 4.2600E-03, 1.6600E-03, 1.0200E-03, 9.8000E-04, 
            8.0000E-04, 1.3000E-04, 5.6000E-05, 3.6000E-05, 1.3000E-05, 
            1.6000E-06, 6.2000E-08} );

    subshell_half_profiles[19] = 
      std::vector<double>( {4.6800E-01, 4.6800E-01, 4.6800E-01, 4.6700E-01, 
            4.6700E-01, 4.6300E-01, 4.5200E-01, 4.2800E-01, 3.9300E-01, 
            3.5100E-01, 3.0500E-01, 2.1600E-01, 1.4400E-01, 9.2400E-02, 
            5.7400E-02, 3.4800E-02, 2.0800E-02, 7.7700E-03, 3.3700E-03, 
            3.0500E-03, 2.2100E-03, 1.2200E-03, 5.8600E-04, 2.8600E-04, 
            1.5000E-04, 1.1000E-04, 4.7000E-05, 6.1000E-06, 9.3000E-07, 
            4.4000E-08, 6.9000E-10} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.9300E+00, 1.8500E+00, 1.6600E+00, 1.3700E+00, 
            1.0600E+00, 5.3000E-01, 2.2100E-01, 9.6300E-02, 6.3300E-02, 
            5.9500E-02, 5.8700E-02, 4.6100E-02, 2.8100E-02, 1.4800E-02, 
            7.4400E-03, 4.1600E-03, 3.0400E-03, 2.8000E-03, 2.2700E-03, 
            7.7000E-04, 2.6900E-04, 2.3100E-04, 2.1000E-04, 1.5200E-04, 
            5.2000E-05, 1.9000E-05, 1.0000E-05, 9.7000E-07, 5.8000E-07, 
            3.5000E-07, 5.9000E-08} );
  }
};

//! The default Compton profile generator implementation for A=65
template<>
struct DefaultComptonProfileGeneratorImpl<65u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 20 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.2000E-02, 1.2000E-02, 1.2000E-02, 1.2000E-02, 
            1.2000E-02, 1.2000E-02, 1.2000E-02, 1.2000E-02, 1.2000E-02, 
            1.2000E-02, 1.2000E-02, 1.2000E-02, 1.2000E-02, 1.2000E-02, 
            1.2000E-02, 1.1900E-02, 1.1900E-02, 1.1900E-02, 1.1900E-02, 
            1.1800E-02, 1.1800E-02, 1.1700E-02, 1.1600E-02, 1.1500E-02, 
            1.1000E-02, 1.0000E-02, 9.4000E-03, 7.1000E-03, 5.1000E-03, 
            2.3000E-03, 5.1000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 
            4.2600E-02, 4.2600E-02, 4.2500E-02, 4.2500E-02, 4.2500E-02, 
            4.2400E-02, 4.2400E-02, 4.2300E-02, 4.2100E-02, 4.2000E-02, 
            4.1800E-02, 4.1600E-02, 4.1300E-02, 4.0800E-02, 3.9800E-02, 
            3.7800E-02, 3.5400E-02, 3.2700E-02, 2.9700E-02, 2.6700E-02, 
            2.1000E-02, 9.1000E-03, 3.4000E-03, 1.1000E-03, 1.0000E-03, 
            5.5000E-04, 1.0000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.1000E-02, 2.1000E-02, 2.1000E-02, 2.1000E-02, 
            2.1000E-02, 2.1000E-02, 2.1000E-02, 2.1000E-02, 2.1000E-02, 
            2.1000E-02, 2.1000E-02, 2.1000E-02, 2.1000E-02, 2.1000E-02, 
            2.1000E-02, 2.1000E-02, 2.1000E-02, 2.1000E-02, 2.1000E-02, 
            2.0900E-02, 2.0900E-02, 2.0700E-02, 2.0500E-02, 2.0300E-02, 
            1.9000E-02, 1.6000E-02, 1.2000E-02, 5.0000E-03, 1.9000E-03, 
            3.2000E-04, 2.1000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.2600E-02, 2.2600E-02, 2.2600E-02, 2.2600E-02, 
            2.2600E-02, 2.2600E-02, 2.2600E-02, 2.2600E-02, 2.2600E-02, 
            2.2600E-02, 2.2600E-02, 2.2600E-02, 2.2600E-02, 2.2600E-02, 
            2.2600E-02, 2.2600E-02, 2.2600E-02, 2.2600E-02, 2.2600E-02, 
            2.2500E-02, 2.2400E-02, 2.2300E-02, 2.2000E-02, 2.1700E-02, 
            2.1000E-02, 1.6000E-02, 1.1000E-02, 4.3000E-03, 1.5000E-03, 
            2.0000E-04, 8.9000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {9.5000E-02, 9.5000E-02, 9.5000E-02, 9.5000E-02, 
            9.4900E-02, 9.4700E-02, 9.4400E-02, 9.4000E-02, 9.3600E-02, 
            9.3000E-02, 9.2400E-02, 9.1000E-02, 8.9300E-02, 8.7300E-02, 
            8.5000E-02, 8.2500E-02, 7.9900E-02, 7.4000E-02, 6.4400E-02, 
            4.8100E-02, 3.3500E-02, 2.2200E-02, 1.4600E-02, 1.0200E-02, 
            7.2000E-03, 6.1000E-03, 2.8000E-03, 3.2000E-04, 2.2000E-04, 
            1.3000E-04, 2.4000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {5.6100E-02, 5.6100E-02, 5.6100E-02, 5.6100E-02, 
            5.6100E-02, 5.6100E-02, 5.6100E-02, 5.6100E-02, 5.6100E-02, 
            5.6100E-02, 5.6100E-02, 5.6100E-02, 5.6000E-02, 5.6000E-02, 
            5.5900E-02, 5.5800E-02, 5.5700E-02, 5.5300E-02, 5.4300E-02, 
            5.1300E-02, 4.6600E-02, 4.0400E-02, 3.3400E-02, 2.6500E-02, 
            1.5000E-02, 2.9000E-03, 2.0000E-03, 1.4000E-03, 5.7000E-04, 
            9.0000E-05, 5.5000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {5.8900E-02, 5.8900E-02, 5.8900E-02, 5.8900E-02, 
            5.8900E-02, 5.8900E-02, 5.8900E-02, 5.8900E-02, 5.8900E-02, 
            5.8900E-02, 5.8900E-02, 5.8900E-02, 5.8800E-02, 5.8800E-02, 
            5.8700E-02, 5.8600E-02, 5.8400E-02, 5.7900E-02, 5.6700E-02, 
            5.3000E-02, 4.7400E-02, 4.0200E-02, 3.2400E-02, 2.4900E-02, 
            1.3000E-02, 2.7000E-03, 2.2000E-03, 1.3000E-03, 4.6000E-04, 
            5.9000E-05, 2.4000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {3.8600E-02, 3.8600E-02, 3.8600E-02, 3.8600E-02, 
            3.8600E-02, 3.8600E-02, 3.8600E-02, 3.8600E-02, 3.8600E-02, 
            3.8600E-02, 3.8600E-02, 3.8600E-02, 3.8600E-02, 3.8600E-02, 
            3.8600E-02, 3.8600E-02, 3.8600E-02, 3.8500E-02, 3.8500E-02, 
            3.8200E-02, 3.7600E-02, 3.6300E-02, 3.4400E-02, 3.1900E-02, 
            2.6000E-02, 1.1000E-02, 4.1000E-03, 5.2000E-04, 8.1000E-05, 
            4.1000E-06, 6.6000E-08} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.9100E-02, 3.9100E-02, 3.9100E-02, 3.9100E-02, 
            3.9100E-02, 3.9100E-02, 3.9100E-02, 3.9100E-02, 3.9100E-02, 
            3.9100E-02, 3.9100E-02, 3.9100E-02, 3.9100E-02, 3.9100E-02, 
            3.9100E-02, 3.9100E-02, 3.9100E-02, 3.9100E-02, 3.9100E-02, 
            3.8800E-02, 3.8100E-02, 3.6700E-02, 3.4700E-02, 3.2100E-02, 
            2.6000E-02, 1.1000E-02, 3.8000E-03, 4.6000E-04, 7.0000E-05, 
            3.1000E-06, 4.0000E-08} );

    subshell_half_profiles[9] = 
      std::vector<double>( {2.0300E-01, 2.0300E-01, 2.0300E-01, 2.0200E-01, 
            2.0100E-01, 1.9900E-01, 1.9600E-01, 1.9200E-01, 1.8800E-01, 
            1.8300E-01, 1.7700E-01, 1.6400E-01, 1.4900E-01, 1.3400E-01, 
            1.1800E-01, 1.0300E-01, 8.8500E-02, 6.3200E-02, 3.7000E-02, 
            2.0200E-02, 1.8500E-02, 1.7500E-02, 1.3900E-02, 9.4300E-03, 
            3.4000E-03, 1.6000E-03, 9.0000E-04, 8.9000E-05, 5.0000E-05, 
            3.1000E-05, 5.6000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.2900E-01, 1.2900E-01, 1.2900E-01, 1.2900E-01, 
            1.2900E-01, 1.2900E-01, 1.2900E-01, 1.2900E-01, 1.2900E-01, 
            1.2900E-01, 1.2800E-01, 1.2800E-01, 1.2600E-01, 1.2400E-01, 
            1.2000E-01, 1.1600E-01, 1.1100E-01, 9.8400E-02, 7.5900E-02, 
            4.0400E-02, 1.8500E-02, 9.5900E-03, 7.5300E-03, 7.4100E-03, 
            6.2000E-03, 1.2000E-03, 4.1000E-04, 3.1000E-04, 1.3000E-04, 
            2.1000E-05, 1.3000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.3600E-01, 1.3600E-01, 1.3600E-01, 1.3600E-01, 
            1.3600E-01, 1.3600E-01, 1.3600E-01, 1.3500E-01, 1.3500E-01, 
            1.3500E-01, 1.3500E-01, 1.3400E-01, 1.3200E-01, 1.2900E-01, 
            1.2500E-01, 1.2000E-01, 1.1300E-01, 9.8800E-02, 7.3500E-02, 
            3.6500E-02, 1.6000E-02, 9.0000E-03, 7.8500E-03, 7.7700E-03, 
            5.9000E-03, 9.7000E-04, 4.5000E-04, 3.0000E-04, 1.1000E-04, 
            1.4000E-05, 5.5000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0700E-01, 
            1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0700E-01, 
            1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0600E-01, 1.0600E-01, 
            1.0500E-01, 1.0400E-01, 1.0200E-01, 9.6800E-02, 8.4700E-02, 
            5.8300E-02, 3.3900E-02, 1.7500E-02, 8.5600E-03, 4.6000E-03, 
            2.9000E-03, 2.2000E-03, 9.4000E-04, 1.2000E-04, 2.0000E-05, 
            9.5000E-07, 1.5000E-08} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 
            1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 
            1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0700E-01, 
            1.0700E-01, 1.0500E-01, 1.0300E-01, 9.7800E-02, 8.5000E-02, 
            5.7600E-02, 3.2900E-02, 1.6600E-02, 8.0500E-03, 4.3700E-03, 
            2.9000E-03, 2.1000E-03, 8.8000E-04, 1.1000E-04, 1.6000E-05, 
            7.2000E-07, 9.0000E-09} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 
            1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 
            1.1600E-01, 1.1600E-01, 1.1500E-01, 1.1400E-01, 1.1200E-01, 
            1.0900E-01, 1.0600E-01, 1.0100E-01, 9.2000E-02, 7.6600E-02, 
            5.2900E-02, 3.4800E-02, 2.2300E-02, 1.4100E-02, 8.9200E-03, 
            3.6000E-03, 4.0000E-04, 5.7000E-05, 2.2000E-06, 1.7000E-07, 
            3.0000E-09, 1.6000E-11} );

    subshell_half_profiles[15] = 
      std::vector<double>( {1.2100E-01, 1.2100E-01, 1.2100E-01, 1.2100E-01, 
            1.2100E-01, 1.2100E-01, 1.2100E-01, 1.2100E-01, 1.2100E-01, 
            1.2100E-01, 1.2000E-01, 1.1900E-01, 1.1800E-01, 1.1500E-01, 
            1.1100E-01, 1.0700E-01, 1.0200E-01, 9.1800E-02, 7.5400E-02, 
            5.1300E-02, 3.3400E-02, 2.1300E-02, 1.3400E-02, 8.4200E-03, 
            3.3000E-03, 3.7000E-04, 5.2000E-05, 2.0000E-06, 1.4000E-07, 
            2.3000E-09, 1.0000E-11} );

    subshell_half_profiles[16] = 
      std::vector<double>( {5.4400E-01, 5.4200E-01, 5.3700E-01, 5.2800E-01, 
            5.1500E-01, 4.8000E-01, 4.3600E-01, 3.8500E-01, 3.3200E-01, 
            2.7900E-01, 2.2900E-01, 1.4600E-01, 8.9300E-02, 5.6400E-02, 
            4.0700E-02, 3.5100E-02, 3.4000E-02, 3.3100E-02, 2.4500E-02, 
            8.3500E-03, 3.3100E-03, 2.9400E-03, 2.6800E-03, 1.9900E-03, 
            7.2000E-04, 2.5000E-04, 1.4000E-04, 1.4000E-05, 7.5000E-06, 
            4.7000E-06, 8.4000E-07} );

    subshell_half_profiles[17] = 
      std::vector<double>( {3.7000E-01, 3.7000E-01, 3.7000E-01, 3.7000E-01, 
            3.7000E-01, 3.6800E-01, 3.6300E-01, 3.5400E-01, 3.3900E-01, 
            3.2000E-01, 2.9600E-01, 2.4000E-01, 1.8100E-01, 1.2700E-01, 
            8.4500E-02, 5.4000E-02, 3.4200E-02, 1.6300E-02, 1.2300E-02, 
            1.0300E-02, 5.3100E-03, 2.1700E-03, 1.0900E-03, 9.0200E-04, 
            8.3000E-04, 1.8000E-04, 5.1000E-05, 3.9000E-05, 1.7000E-05, 
            2.6000E-06, 1.6000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {4.0000E-01, 4.0000E-01, 4.0000E-01, 4.0000E-01, 
            3.9900E-01, 3.9600E-01, 3.8900E-01, 3.7600E-01, 3.5700E-01, 
            3.3200E-01, 3.0200E-01, 2.3400E-01, 1.6800E-01, 1.1200E-01, 
            7.0400E-02, 4.3000E-02, 2.6700E-02, 1.4000E-02, 1.2200E-02, 
            9.1500E-03, 4.1400E-03, 1.6200E-03, 9.4700E-04, 8.8300E-04, 
            7.5000E-04, 1.3000E-04, 5.1000E-05, 3.4000E-05, 1.3000E-05, 
            1.6000E-06, 6.4000E-08} );

    subshell_half_profiles[19] = 
      std::vector<double>( {2.0300E+00, 1.9400E+00, 1.7200E+00, 1.4100E+00, 
            1.0700E+00, 5.0200E-01, 1.9700E-01, 8.4300E-02, 5.8400E-02, 
            5.6400E-02, 5.4800E-02, 4.1000E-02, 2.4000E-02, 1.2300E-02, 
            6.0500E-03, 3.3900E-03, 2.5100E-03, 2.3200E-03, 1.8900E-03, 
            6.6400E-04, 2.2700E-04, 1.8700E-04, 1.7400E-04, 1.3100E-04, 
            4.8000E-05, 1.6000E-05, 9.2000E-06, 8.9000E-07, 4.7000E-07, 
            3.0000E-07, 5.3000E-08} );
  }
};

//! The default Compton profile generator implementation for A=66
template<>
struct DefaultComptonProfileGeneratorImpl<66u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 20 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 
            1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 
            1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 
            1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 
            1.1600E-02, 1.1600E-02, 1.1500E-02, 1.1400E-02, 1.1300E-02, 
            1.1000E-02, 1.0000E-02, 9.3000E-03, 7.1000E-03, 5.1000E-03, 
            2.4000E-03, 5.4000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1800E-02, 
            4.1800E-02, 4.1700E-02, 4.1700E-02, 4.1700E-02, 4.1700E-02, 
            4.1600E-02, 4.1600E-02, 4.1500E-02, 4.1300E-02, 4.1200E-02, 
            4.1000E-02, 4.0800E-02, 4.0600E-02, 4.0100E-02, 3.9200E-02, 
            3.7300E-02, 3.5000E-02, 3.2400E-02, 2.9600E-02, 2.6700E-02, 
            2.1000E-02, 9.4000E-03, 3.6000E-03, 1.1000E-03, 1.0000E-03, 
            5.7000E-04, 1.1000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.0600E-02, 2.0600E-02, 2.0600E-02, 2.0600E-02, 
            2.0600E-02, 2.0600E-02, 2.0600E-02, 2.0600E-02, 2.0600E-02, 
            2.0600E-02, 2.0600E-02, 2.0600E-02, 2.0600E-02, 2.0600E-02, 
            2.0600E-02, 2.0600E-02, 2.0600E-02, 2.0600E-02, 2.0600E-02, 
            2.0500E-02, 2.0500E-02, 2.0300E-02, 2.0200E-02, 1.9900E-02, 
            1.9000E-02, 1.6000E-02, 1.2000E-02, 5.2000E-03, 2.0000E-03, 
            3.5000E-04, 2.4000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.2200E-02, 2.2200E-02, 2.2200E-02, 2.2200E-02, 
            2.2200E-02, 2.2200E-02, 2.2200E-02, 2.2200E-02, 2.2200E-02, 
            2.2200E-02, 2.2200E-02, 2.2200E-02, 2.2200E-02, 2.2200E-02, 
            2.2200E-02, 2.2200E-02, 2.2200E-02, 2.2200E-02, 2.2200E-02, 
            2.2200E-02, 2.2100E-02, 2.1900E-02, 2.1700E-02, 2.1300E-02, 
            2.0000E-02, 1.6000E-02, 1.1000E-02, 4.5000E-03, 1.6000E-03, 
            2.2000E-04, 9.8000E-06} );

    subshell_half_profiles[4] = 
      std::vector<double>( {9.3100E-02, 9.3100E-02, 9.3000E-02, 9.3000E-02, 
            9.2900E-02, 9.2700E-02, 9.2500E-02, 9.2100E-02, 9.1700E-02, 
            9.1200E-02, 9.0600E-02, 8.9300E-02, 8.7600E-02, 8.5700E-02, 
            8.3600E-02, 8.1300E-02, 7.8800E-02, 7.3200E-02, 6.4100E-02, 
            4.8300E-02, 3.4100E-02, 2.2900E-02, 1.5100E-02, 1.0500E-02, 
            7.2000E-03, 6.2000E-03, 3.0000E-03, 3.4000E-04, 2.2000E-04, 
            1.4000E-04, 2.6000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {5.4900E-02, 5.4900E-02, 5.4900E-02, 5.4900E-02, 
            5.4900E-02, 5.4900E-02, 5.4900E-02, 5.4900E-02, 5.4900E-02, 
            5.4900E-02, 5.4900E-02, 5.4900E-02, 5.4800E-02, 5.4800E-02, 
            5.4700E-02, 5.4600E-02, 5.4500E-02, 5.4200E-02, 5.3300E-02, 
            5.0600E-02, 4.6100E-02, 4.0300E-02, 3.3700E-02, 2.7000E-02, 
            1.5000E-02, 3.1000E-03, 2.0000E-03, 1.4000E-03, 6.0000E-04, 
            9.9000E-05, 6.2000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {5.7700E-02, 5.7700E-02, 5.7700E-02, 5.7700E-02, 
            5.7700E-02, 5.7700E-02, 5.7700E-02, 5.7700E-02, 5.7700E-02, 
            5.7700E-02, 5.7700E-02, 5.7700E-02, 5.7700E-02, 5.7600E-02, 
            5.7500E-02, 5.7400E-02, 5.7300E-02, 5.6800E-02, 5.5700E-02, 
            5.2300E-02, 4.7000E-02, 4.0300E-02, 3.2800E-02, 2.5500E-02, 
            1.4000E-02, 2.8000E-03, 2.2000E-03, 1.3000E-03, 4.9000E-04, 
            6.4000E-05, 2.7000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {3.7800E-02, 3.7800E-02, 3.7800E-02, 3.7800E-02, 
            3.7800E-02, 3.7800E-02, 3.7800E-02, 3.7800E-02, 3.7800E-02, 
            3.7800E-02, 3.7800E-02, 3.7800E-02, 3.7800E-02, 3.7800E-02, 
            3.7800E-02, 3.7800E-02, 3.7800E-02, 3.7700E-02, 3.7700E-02, 
            3.7500E-02, 3.6900E-02, 3.5700E-02, 3.4000E-02, 3.1700E-02, 
            2.6000E-02, 1.2000E-02, 4.3000E-03, 5.7000E-04, 9.2000E-05, 
            4.7000E-06, 7.7000E-08} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.8400E-02, 3.8400E-02, 3.8400E-02, 3.8400E-02, 
            3.8400E-02, 3.8400E-02, 3.8400E-02, 3.8400E-02, 3.8400E-02, 
            3.8400E-02, 3.8400E-02, 3.8400E-02, 3.8400E-02, 3.8400E-02, 
            3.8400E-02, 3.8400E-02, 3.8300E-02, 3.8300E-02, 3.8300E-02, 
            3.8000E-02, 3.7400E-02, 3.6200E-02, 3.4300E-02, 3.1900E-02, 
            2.6000E-02, 1.1000E-02, 4.1000E-03, 5.1000E-04, 7.8000E-05, 
            3.6000E-06, 4.6000E-08} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.9900E-01, 1.9800E-01, 1.9800E-01, 1.9800E-01, 
            1.9700E-01, 1.9500E-01, 1.9200E-01, 1.8900E-01, 1.8400E-01, 
            1.8000E-01, 1.7400E-01, 1.6200E-01, 1.4800E-01, 1.3300E-01, 
            1.1800E-01, 1.0400E-01, 8.9400E-02, 6.4700E-02, 3.8300E-02, 
            2.0300E-02, 1.8100E-02, 1.7400E-02, 1.4300E-02, 9.9600E-03, 
            3.7000E-03, 1.6000E-03, 9.6000E-04, 9.9000E-05, 5.0000E-05, 
            3.2000E-05, 6.0000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.2600E-01, 1.2600E-01, 1.2600E-01, 1.2600E-01, 
            1.2600E-01, 1.2600E-01, 1.2600E-01, 1.2600E-01, 1.2600E-01, 
            1.2600E-01, 1.2600E-01, 1.2500E-01, 1.2300E-01, 1.2100E-01, 
            1.1800E-01, 1.1400E-01, 1.1000E-01, 9.8000E-02, 7.6700E-02, 
            4.2100E-02, 1.9700E-02, 1.0000E-02, 7.4900E-03, 7.2800E-03, 
            6.3000E-03, 1.4000E-03, 4.1000E-04, 3.2000E-04, 1.4000E-04, 
            2.3000E-05, 1.4000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 
            1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 
            1.3200E-01, 1.3200E-01, 1.3100E-01, 1.2900E-01, 1.2600E-01, 
            1.2300E-01, 1.1800E-01, 1.1200E-01, 9.8600E-02, 7.4500E-02, 
            3.8100E-02, 1.7000E-02, 9.2300E-03, 7.7400E-03, 7.6700E-03, 
            6.1000E-03, 1.1000E-03, 4.5000E-04, 3.1000E-04, 1.2000E-04, 
            1.5000E-05, 6.2000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 
            1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 
            1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0300E-01, 
            1.0300E-01, 1.0200E-01, 1.0000E-01, 9.5400E-02, 8.4300E-02, 
            5.9400E-02, 3.5500E-02, 1.8800E-02, 9.3700E-03, 4.9600E-03, 
            2.9000E-03, 2.3000E-03, 1.0000E-03, 1.4000E-04, 2.2000E-05, 
            1.1000E-06, 1.8000E-08} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.0600E-01, 1.0600E-01, 1.0600E-01, 1.0600E-01, 
            1.0600E-01, 1.0600E-01, 1.0600E-01, 1.0600E-01, 1.0600E-01, 
            1.0600E-01, 1.0600E-01, 1.0600E-01, 1.0600E-01, 1.0500E-01, 
            1.0400E-01, 1.0300E-01, 1.0200E-01, 9.6500E-02, 8.4700E-02, 
            5.8600E-02, 3.4400E-02, 1.7900E-02, 8.7900E-03, 4.6900E-03, 
            2.9000E-03, 2.2000E-03, 9.4000E-04, 1.2000E-04, 1.9000E-05, 
            8.3000E-07, 1.1000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1300E-01, 
            1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1300E-01, 
            1.1300E-01, 1.1300E-01, 1.1200E-01, 1.1100E-01, 1.0900E-01, 
            1.0700E-01, 1.0300E-01, 9.9600E-02, 9.0900E-02, 7.6500E-02, 
            5.3800E-02, 3.6000E-02, 2.3500E-02, 1.5100E-02, 9.6600E-03, 
            3.9000E-03, 4.6000E-04, 6.7000E-05, 2.7000E-06, 2.0000E-07, 
            3.8000E-09, 2.0000E-11} );

    subshell_half_profiles[15] = 
      std::vector<double>( {1.1700E-01, 1.1700E-01, 1.1700E-01, 1.1700E-01, 
            1.1700E-01, 1.1700E-01, 1.1700E-01, 1.1700E-01, 1.1700E-01, 
            1.1700E-01, 1.1700E-01, 1.1600E-01, 1.1400E-01, 1.1200E-01, 
            1.0900E-01, 1.0500E-01, 1.0100E-01, 9.0900E-02, 7.5600E-02, 
            5.2400E-02, 3.4800E-02, 2.2500E-02, 1.4400E-02, 9.1600E-03, 
            3.7000E-03, 4.3000E-04, 6.1000E-05, 2.4000E-06, 1.7000E-07, 
            3.0000E-09, 1.3000E-11} );

    subshell_half_profiles[16] = 
      std::vector<double>( {5.3500E-01, 5.3300E-01, 5.2800E-01, 5.1900E-01, 
            5.0700E-01, 4.7400E-01, 4.3200E-01, 3.8300E-01, 3.3200E-01, 
            2.8100E-01, 2.3200E-01, 1.5000E-01, 9.2500E-02, 5.8300E-02, 
            4.1200E-02, 3.4700E-02, 3.3200E-02, 3.2600E-02, 2.5000E-02, 
            8.9900E-03, 3.4000E-03, 2.8600E-03, 2.6900E-03, 2.0600E-03, 
            7.9000E-04, 2.4000E-04, 1.5000E-04, 1.5000E-05, 7.4000E-06, 
            4.9000E-06, 9.0000E-07} );

    subshell_half_profiles[17] = 
      std::vector<double>( {3.6400E-01, 3.6400E-01, 3.6400E-01, 3.6400E-01, 
            3.6400E-01, 3.6200E-01, 3.5700E-01, 3.4900E-01, 3.3500E-01, 
            3.1700E-01, 2.9500E-01, 2.4100E-01, 1.8300E-01, 1.3100E-01, 
            8.8200E-02, 5.7100E-02, 3.6400E-02, 1.6900E-02, 1.1900E-02, 
            1.0300E-02, 5.6100E-03, 2.3600E-03, 1.1300E-03, 8.8200E-04, 
            8.2000E-04, 2.0000E-04, 5.1000E-05, 3.9000E-05, 1.8000E-05, 
            2.9000E-06, 1.8000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {3.9400E-01, 3.9400E-01, 3.9400E-01, 3.9400E-01, 
            3.9300E-01, 3.9000E-01, 3.8400E-01, 3.7200E-01, 3.5400E-01, 
            3.3000E-01, 3.0100E-01, 2.3600E-01, 1.7100E-01, 1.1500E-01, 
            7.3700E-02, 4.5500E-02, 2.8300E-02, 1.4200E-02, 1.1900E-02, 
            9.2800E-03, 4.4100E-03, 1.7400E-03, 9.5600E-04, 8.5900E-04, 
            7.5000E-04, 1.4000E-04, 5.1000E-05, 3.5000E-05, 1.3000E-05, 
            1.7000E-06, 7.1000E-08} );

    subshell_half_profiles[19] = 
      std::vector<double>( {2.0100E+00, 1.9300E+00, 1.7100E+00, 1.4000E+00, 
            1.0700E+00, 5.1100E-01, 2.0300E-01, 8.5900E-02, 5.7400E-02, 
            5.4700E-02, 5.3600E-02, 4.1000E-02, 2.4600E-02, 1.2800E-02, 
            6.4000E-03, 3.5100E-03, 2.4800E-03, 2.2200E-03, 1.8800E-03, 
            7.0300E-04, 2.3200E-04, 1.7900E-04, 1.7000E-04, 1.3300E-04, 
            5.1000E-05, 1.5000E-05, 9.5000E-06, 9.6000E-07, 4.6000E-07, 
            3.0000E-07, 5.6000E-08} );
  }
};

//! The default Compton profile generator implementation for A=67
template<>
struct DefaultComptonProfileGeneratorImpl<67u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 20 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 
            1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 
            1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 
            1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 
            1.1400E-02, 1.1400E-02, 1.1300E-02, 1.1200E-02, 1.1100E-02, 
            1.1000E-02, 1.0000E-02, 9.2000E-03, 7.1000E-03, 5.1000E-03, 
            2.5000E-03, 5.7000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {4.1000E-02, 4.1000E-02, 4.1000E-02, 4.1000E-02, 
            4.1000E-02, 4.1000E-02, 4.0900E-02, 4.0900E-02, 4.0900E-02, 
            4.0800E-02, 4.0800E-02, 4.0700E-02, 4.0600E-02, 4.0400E-02, 
            4.0300E-02, 4.0100E-02, 3.9900E-02, 3.9400E-02, 3.8500E-02, 
            3.6700E-02, 3.4500E-02, 3.2000E-02, 2.9400E-02, 2.6600E-02, 
            2.1000E-02, 9.7000E-03, 3.8000E-03, 1.1000E-03, 1.0000E-03, 
            5.9000E-04, 1.2000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {2.0200E-02, 2.0200E-02, 2.0200E-02, 2.0200E-02, 
            2.0200E-02, 2.0200E-02, 2.0200E-02, 2.0200E-02, 2.0200E-02, 
            2.0200E-02, 2.0200E-02, 2.0200E-02, 2.0200E-02, 2.0200E-02, 
            2.0200E-02, 2.0200E-02, 2.0200E-02, 2.0200E-02, 2.0200E-02, 
            2.0100E-02, 2.0100E-02, 2.0000E-02, 1.9800E-02, 1.9600E-02, 
            1.9000E-02, 1.6000E-02, 1.2000E-02, 5.4000E-03, 2.2000E-03, 
            3.8000E-04, 2.6000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.1900E-02, 2.1900E-02, 2.1900E-02, 2.1900E-02, 
            2.1900E-02, 2.1900E-02, 2.1900E-02, 2.1900E-02, 2.1900E-02, 
            2.1900E-02, 2.1900E-02, 2.1900E-02, 2.1900E-02, 2.1900E-02, 
            2.1900E-02, 2.1900E-02, 2.1900E-02, 2.1800E-02, 2.1800E-02, 
            2.1800E-02, 2.1700E-02, 2.1600E-02, 2.1300E-02, 2.1000E-02, 
            2.0000E-02, 1.6000E-02, 1.2000E-02, 4.6000E-03, 1.7000E-03, 
            2.3000E-04, 1.1000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {9.1200E-02, 9.1200E-02, 9.1100E-02, 9.1100E-02, 
            9.1000E-02, 9.0800E-02, 9.0600E-02, 9.0300E-02, 8.9900E-02, 
            8.9400E-02, 8.8900E-02, 8.7600E-02, 8.6000E-02, 8.4300E-02, 
            8.2300E-02, 8.0000E-02, 7.7700E-02, 7.2400E-02, 6.3700E-02, 
            4.8500E-02, 3.4700E-02, 2.3500E-02, 1.5700E-02, 1.0800E-02, 
            7.2000E-03, 6.2000E-03, 3.2000E-03, 3.7000E-04, 2.1000E-04, 
            1.4000E-04, 2.7000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {5.3700E-02, 5.3700E-02, 5.3700E-02, 5.3700E-02, 
            5.3700E-02, 5.3700E-02, 5.3700E-02, 5.3700E-02, 5.3700E-02, 
            5.3700E-02, 5.3700E-02, 5.3700E-02, 5.3700E-02, 5.3700E-02, 
            5.3600E-02, 5.3500E-02, 5.3400E-02, 5.3100E-02, 5.2300E-02, 
            4.9800E-02, 4.5700E-02, 4.0300E-02, 3.4000E-02, 2.7500E-02, 
            1.6000E-02, 3.3000E-03, 1.9000E-03, 1.4000E-03, 6.4000E-04, 
            1.1000E-04, 7.0000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {5.6600E-02, 5.6600E-02, 5.6600E-02, 5.6600E-02, 
            5.6600E-02, 5.6600E-02, 5.6600E-02, 5.6600E-02, 5.6600E-02, 
            5.6600E-02, 5.6600E-02, 5.6600E-02, 5.6600E-02, 5.6500E-02, 
            5.6500E-02, 5.6400E-02, 5.6200E-02, 5.5800E-02, 5.4800E-02, 
            5.1700E-02, 4.6700E-02, 4.0300E-02, 3.3200E-02, 2.6100E-02, 
            1.4000E-02, 2.9000E-03, 2.2000E-03, 1.4000E-03, 5.2000E-04, 
            7.0000E-05, 3.0000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {3.7000E-02, 3.7000E-02, 3.7000E-02, 3.7000E-02, 
            3.7000E-02, 3.7000E-02, 3.7000E-02, 3.7000E-02, 3.7000E-02, 
            3.7000E-02, 3.7000E-02, 3.7000E-02, 3.7000E-02, 3.7000E-02, 
            3.7000E-02, 3.7000E-02, 3.7000E-02, 3.7000E-02, 3.6900E-02, 
            3.6700E-02, 3.6200E-02, 3.5200E-02, 3.3600E-02, 3.1400E-02, 
            2.6000E-02, 1.2000E-02, 4.6000E-03, 6.3000E-04, 1.0000E-04, 
            5.3000E-06, 9.0000E-08} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.7600E-02, 3.7600E-02, 3.7600E-02, 3.7600E-02, 
            3.7600E-02, 3.7600E-02, 3.7600E-02, 3.7600E-02, 3.7600E-02, 
            3.7600E-02, 3.7600E-02, 3.7600E-02, 3.7600E-02, 3.7600E-02, 
            3.7600E-02, 3.7600E-02, 3.7600E-02, 3.7600E-02, 3.7500E-02, 
            3.7300E-02, 3.6700E-02, 3.5700E-02, 3.4000E-02, 3.1700E-02, 
            2.6000E-02, 1.2000E-02, 4.4000E-03, 5.6000E-04, 8.7000E-05, 
            4.1000E-06, 5.3000E-08} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.9400E-01, 1.9400E-01, 1.9400E-01, 1.9400E-01, 
            1.9300E-01, 1.9100E-01, 1.8800E-01, 1.8500E-01, 1.8100E-01, 
            1.7600E-01, 1.7100E-01, 1.6000E-01, 1.4700E-01, 1.3300E-01, 
            1.1800E-01, 1.0400E-01, 9.0300E-02, 6.6000E-02, 3.9500E-02, 
            2.0500E-02, 1.7800E-02, 1.7300E-02, 1.4600E-02, 1.0500E-02, 
            4.0000E-03, 1.6000E-03, 1.0000E-03, 1.1000E-04, 4.9000E-05, 
            3.4000E-05, 6.5000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 
            1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 
            1.2300E-01, 1.2300E-01, 1.2200E-01, 1.2100E-01, 1.1900E-01, 
            1.1600E-01, 1.1300E-01, 1.0800E-01, 9.7400E-02, 7.7300E-02, 
            4.3800E-02, 2.1000E-02, 1.0500E-02, 7.5000E-03, 7.1500E-03, 
            6.4000E-03, 1.5000E-03, 4.2000E-04, 3.2000E-04, 1.5000E-04, 
            2.5000E-05, 1.6000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.3000E-01, 1.3000E-01, 1.3000E-01, 1.3000E-01, 
            1.3000E-01, 1.3000E-01, 1.3000E-01, 1.3000E-01, 1.3000E-01, 
            1.3000E-01, 1.2900E-01, 1.2800E-01, 1.2700E-01, 1.2400E-01, 
            1.2100E-01, 1.1700E-01, 1.1100E-01, 9.8300E-02, 7.5400E-02, 
            3.9700E-02, 1.8000E-02, 9.5200E-03, 7.6600E-03, 7.5600E-03, 
            6.2000E-03, 1.2000E-03, 4.5000E-04, 3.2000E-04, 1.2000E-04, 
            1.7000E-05, 6.9000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {1.0200E-01, 1.0200E-01, 1.0200E-01, 1.0200E-01, 
            1.0200E-01, 1.0200E-01, 1.0200E-01, 1.0200E-01, 1.0200E-01, 
            1.0200E-01, 1.0200E-01, 1.0200E-01, 1.0200E-01, 1.0100E-01, 
            1.0100E-01, 9.9600E-02, 9.8200E-02, 9.4000E-02, 8.3800E-02, 
            6.0300E-02, 3.7000E-02, 2.0100E-02, 1.0200E-02, 5.3800E-03, 
            2.9000E-03, 2.3000E-03, 1.1000E-03, 1.5000E-04, 2.5000E-05, 
            1.3000E-06, 2.1000E-08} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 
            1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 
            1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0300E-01, 1.0300E-01, 
            1.0200E-01, 1.0100E-01, 9.9700E-02, 9.5200E-02, 8.4300E-02, 
            5.9600E-02, 3.5900E-02, 1.9100E-02, 9.5600E-03, 5.0500E-03, 
            2.9000E-03, 2.3000E-03, 1.0000E-03, 1.4000E-04, 2.1000E-05, 
            9.6000E-07, 1.2000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 
            1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 
            1.1000E-01, 1.1000E-01, 1.0900E-01, 1.0800E-01, 1.0600E-01, 
            1.0400E-01, 1.0100E-01, 9.7900E-02, 8.9800E-02, 7.6200E-02, 
            5.4500E-02, 3.7100E-02, 2.4600E-02, 1.6000E-02, 1.0400E-02, 
            4.3000E-03, 5.3000E-04, 7.9000E-05, 3.3000E-06, 2.5000E-07, 
            4.7000E-09, 2.5000E-11} );

    subshell_half_profiles[15] = 
      std::vector<double>( {1.1400E-01, 1.1400E-01, 1.1400E-01, 1.1400E-01, 
            1.1400E-01, 1.1400E-01, 1.1400E-01, 1.1400E-01, 1.1300E-01, 
            1.1300E-01, 1.1300E-01, 1.1200E-01, 1.1100E-01, 1.0900E-01, 
            1.0600E-01, 1.0300E-01, 9.8900E-02, 9.0000E-02, 7.5600E-02, 
            5.3300E-02, 3.6000E-02, 2.3700E-02, 1.5300E-02, 9.8900E-03, 
            4.1000E-03, 4.9000E-04, 7.3000E-05, 2.9000E-06, 2.1000E-07, 
            3.7000E-09, 1.7000E-11} );

    subshell_half_profiles[16] = 
      std::vector<double>( {5.2600E-01, 5.2400E-01, 5.1900E-01, 5.1100E-01, 
            4.9900E-01, 4.6800E-01, 4.2800E-01, 3.8100E-01, 3.3200E-01, 
            2.8200E-01, 2.3500E-01, 1.5400E-01, 9.5700E-02, 6.0300E-02, 
            4.2000E-02, 3.4500E-02, 3.2400E-02, 3.1900E-02, 2.5400E-02, 
            9.6500E-03, 3.5200E-03, 2.7900E-03, 2.6700E-03, 2.1300E-03, 
            8.6000E-04, 2.4000E-04, 1.6000E-04, 1.7000E-05, 7.3000E-06, 
            5.0000E-06, 9.6000E-07} );

    subshell_half_profiles[17] = 
      std::vector<double>( {3.5800E-01, 3.5800E-01, 3.5800E-01, 3.5800E-01, 
            3.5800E-01, 3.5600E-01, 3.5200E-01, 3.4400E-01, 3.3100E-01, 
            3.1400E-01, 2.9300E-01, 2.4200E-01, 1.8600E-01, 1.3400E-01, 
            9.1800E-02, 6.0200E-02, 3.8700E-02, 1.7600E-02, 1.1500E-02, 
            1.0300E-02, 5.8900E-03, 2.5600E-03, 1.1900E-03, 8.6800E-04, 
            8.2000E-04, 2.2000E-04, 5.2000E-05, 4.0000E-05, 1.9000E-05, 
            3.1000E-06, 2.0000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {3.8800E-01, 3.8800E-01, 3.8800E-01, 3.8800E-01, 
            3.8800E-01, 3.8500E-01, 3.7900E-01, 3.6700E-01, 3.5000E-01, 
            3.2800E-01, 3.0000E-01, 2.3700E-01, 1.7400E-01, 1.1900E-01, 
            7.6900E-02, 4.8000E-02, 2.9900E-02, 1.4500E-02, 1.1500E-02, 
            9.3700E-03, 4.6600E-03, 1.8800E-03, 9.7400E-04, 8.3800E-04, 
            7.6000E-04, 1.5000E-04, 5.0000E-05, 3.6000E-05, 1.4000E-05, 
            1.9000E-06, 7.9000E-08} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.9900E+00, 1.9100E+00, 1.7000E+00, 1.4000E+00, 
            1.0700E+00, 5.2000E-01, 2.0900E-01, 8.7700E-02, 5.6600E-02, 
            5.3200E-02, 5.2400E-02, 4.1000E-02, 2.5200E-02, 1.3400E-02, 
            6.7600E-03, 3.6500E-03, 2.4800E-03, 2.1200E-03, 1.8600E-03, 
            7.4100E-04, 2.4100E-04, 1.7100E-04, 1.6600E-04, 1.3400E-04, 
            5.5000E-05, 1.5000E-05, 9.8000E-06, 1.1000E-06, 4.4000E-07, 
            3.0000E-07, 5.9000E-08} );
  }
};

//! The default Compton profile generator implementation for A=68
template<>
struct DefaultComptonProfileGeneratorImpl<68u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 20 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 
            1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 
            1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 
            1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 
            1.1200E-02, 1.1200E-02, 1.1100E-02, 1.1000E-02, 1.0900E-02, 
            1.0900E-02, 1.0000E-02, 9.1000E-03, 7.0000E-03, 5.1000E-03, 
            2.5000E-03, 6.0000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {4.0200E-02, 4.0200E-02, 4.0200E-02, 4.0200E-02, 
            4.0200E-02, 4.0200E-02, 4.0200E-02, 4.0200E-02, 4.0100E-02, 
            4.0100E-02, 4.0000E-02, 4.0000E-02, 3.9800E-02, 3.9700E-02, 
            3.9500E-02, 3.9400E-02, 3.9200E-02, 3.8700E-02, 3.7900E-02, 
            3.6200E-02, 3.4100E-02, 3.1700E-02, 2.9200E-02, 2.6500E-02, 
            2.1000E-02, 1.0000E-02, 4.0000E-03, 1.1000E-03, 9.8000E-04, 
            6.0000E-04, 1.2000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 
            1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 
            1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 
            1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 
            1.9700E-02, 1.9700E-02, 1.9600E-02, 1.9400E-02, 1.9200E-02, 
            1.9000E-02, 1.6000E-02, 1.2000E-02, 5.5000E-03, 2.3000E-03, 
            4.1000E-04, 2.9000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.1500E-02, 2.1500E-02, 2.1500E-02, 2.1500E-02, 
            2.1500E-02, 2.1500E-02, 2.1500E-02, 2.1500E-02, 2.1500E-02, 
            2.1500E-02, 2.1500E-02, 2.1500E-02, 2.1500E-02, 2.1500E-02, 
            2.1500E-02, 2.1500E-02, 2.1500E-02, 2.1500E-02, 2.1500E-02, 
            2.1400E-02, 2.1400E-02, 2.1200E-02, 2.1000E-02, 2.0700E-02, 
            2.0000E-02, 1.6000E-02, 1.2000E-02, 4.8000E-03, 1.7000E-03, 
            2.5000E-04, 1.2000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {8.9300E-02, 8.9300E-02, 8.9300E-02, 8.9300E-02, 
            8.9200E-02, 8.9000E-02, 8.8800E-02, 8.8500E-02, 8.8100E-02, 
            8.7700E-02, 8.7200E-02, 8.6000E-02, 8.4500E-02, 8.2800E-02, 
            8.0900E-02, 7.8800E-02, 7.6600E-02, 7.1600E-02, 6.3300E-02, 
            4.8700E-02, 3.5200E-02, 2.4200E-02, 1.6300E-02, 1.1200E-02, 
            7.2000E-03, 6.2000E-03, 3.3000E-03, 4.1000E-04, 2.1000E-04, 
            1.4000E-04, 2.9000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {5.2600E-02, 5.2600E-02, 5.2600E-02, 5.2600E-02, 
            5.2600E-02, 5.2600E-02, 5.2600E-02, 5.2600E-02, 5.2600E-02, 
            5.2600E-02, 5.2600E-02, 5.2600E-02, 5.2600E-02, 5.2600E-02, 
            5.2500E-02, 5.2400E-02, 5.2300E-02, 5.2000E-02, 5.1300E-02, 
            4.9000E-02, 4.5200E-02, 4.0100E-02, 3.4200E-02, 2.8000E-02, 
            1.7000E-02, 3.5000E-03, 1.9000E-03, 1.5000E-03, 6.7000E-04, 
            1.2000E-04, 7.8000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {5.5600E-02, 5.5600E-02, 5.5600E-02, 5.5600E-02, 
            5.5600E-02, 5.5600E-02, 5.5600E-02, 5.5600E-02, 5.5600E-02, 
            5.5600E-02, 5.5600E-02, 5.5500E-02, 5.5500E-02, 5.5500E-02, 
            5.5400E-02, 5.5300E-02, 5.5200E-02, 5.4800E-02, 5.3900E-02, 
            5.1000E-02, 4.6300E-02, 4.0300E-02, 3.3400E-02, 2.6600E-02, 
            1.5000E-02, 3.0000E-03, 2.2000E-03, 1.4000E-03, 5.6000E-04, 
            7.6000E-05, 3.3000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {3.6200E-02, 3.6200E-02, 3.6200E-02, 3.6200E-02, 
            3.6200E-02, 3.6200E-02, 3.6200E-02, 3.6200E-02, 3.6200E-02, 
            3.6200E-02, 3.6200E-02, 3.6200E-02, 3.6200E-02, 3.6200E-02, 
            3.6200E-02, 3.6200E-02, 3.6200E-02, 3.6200E-02, 3.6200E-02, 
            3.6000E-02, 3.5500E-02, 3.4600E-02, 3.3200E-02, 3.1200E-02, 
            2.6000E-02, 1.2000E-02, 4.9000E-03, 6.9000E-04, 1.1000E-04, 
            6.1000E-06, 1.0000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.6900E-02, 3.6900E-02, 3.6900E-02, 3.6900E-02, 
            3.6900E-02, 3.6900E-02, 3.6900E-02, 3.6900E-02, 3.6900E-02, 
            3.6900E-02, 3.6900E-02, 3.6900E-02, 3.6900E-02, 3.6900E-02, 
            3.6900E-02, 3.6900E-02, 3.6900E-02, 3.6900E-02, 3.6800E-02, 
            3.6600E-02, 3.6100E-02, 3.5100E-02, 3.3600E-02, 3.1500E-02, 
            2.6000E-02, 1.2000E-02, 4.6000E-03, 6.2000E-04, 9.7000E-05, 
            4.6000E-06, 6.1000E-08} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.9000E-01, 1.9000E-01, 1.9000E-01, 1.9000E-01, 
            1.8900E-01, 1.8700E-01, 1.8500E-01, 1.8100E-01, 1.7800E-01, 
            1.7300E-01, 1.6900E-01, 1.5800E-01, 1.4500E-01, 1.3200E-01, 
            1.1800E-01, 1.0400E-01, 9.1100E-02, 6.7300E-02, 4.0800E-02, 
            2.0700E-02, 1.7500E-02, 1.7100E-02, 1.4800E-02, 1.0900E-02, 
            4.4000E-03, 1.6000E-03, 1.1000E-03, 1.2000E-04, 4.9000E-05, 
            3.5000E-05, 7.0000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.2100E-01, 1.2100E-01, 1.2100E-01, 1.2100E-01, 
            1.2100E-01, 1.2100E-01, 1.2100E-01, 1.2100E-01, 1.2100E-01, 
            1.2000E-01, 1.2000E-01, 1.2000E-01, 1.1800E-01, 1.1700E-01, 
            1.1400E-01, 1.1100E-01, 1.0700E-01, 9.6800E-02, 7.7900E-02, 
            4.5300E-02, 2.2300E-02, 1.1100E-02, 7.5400E-03, 7.0200E-03, 
            6.5000E-03, 1.7000E-03, 4.3000E-04, 3.3000E-04, 1.6000E-04, 
            2.8000E-05, 1.8000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.2800E-01, 1.2800E-01, 1.2800E-01, 1.2800E-01, 
            1.2800E-01, 1.2800E-01, 1.2800E-01, 1.2700E-01, 1.2700E-01, 
            1.2700E-01, 1.2700E-01, 1.2600E-01, 1.2400E-01, 1.2200E-01, 
            1.1900E-01, 1.1500E-01, 1.1000E-01, 9.8000E-02, 7.6100E-02, 
            4.1200E-02, 1.9100E-02, 9.8700E-03, 7.6000E-03, 7.4500E-03, 
            6.3000E-03, 1.3000E-03, 4.5000E-04, 3.3000E-04, 1.3000E-04, 
            1.8000E-05, 7.7000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {9.9600E-02, 9.9600E-02, 9.9600E-02, 9.9600E-02, 
            9.9600E-02, 9.9600E-02, 9.9600E-02, 9.9600E-02, 9.9600E-02, 
            9.9600E-02, 9.9600E-02, 9.9500E-02, 9.9300E-02, 9.9000E-02, 
            9.8500E-02, 9.7600E-02, 9.6400E-02, 9.2600E-02, 8.3300E-02, 
            6.1100E-02, 3.8400E-02, 2.1400E-02, 1.1100E-02, 5.8300E-03, 
            2.9000E-03, 2.3000E-03, 1.1000E-03, 1.7000E-04, 2.8000E-05, 
            1.5000E-06, 2.4000E-08} );

    subshell_half_profiles[13] = 
      std::vector<double>( {1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 
            1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 
            1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 
            1.0000E-01, 9.9300E-02, 9.8000E-02, 9.3800E-02, 8.3800E-02, 
            6.0400E-02, 3.7300E-02, 2.0300E-02, 1.0400E-02, 5.4600E-03, 
            2.9000E-03, 2.3000E-03, 1.1000E-03, 1.5000E-04, 2.4000E-05, 
            1.1000E-06, 1.4000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0700E-01, 
            1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0700E-01, 
            1.0700E-01, 1.0700E-01, 1.0600E-01, 1.0600E-01, 1.0400E-01, 
            1.0200E-01, 9.9300E-02, 9.6100E-02, 8.8600E-02, 7.5900E-02, 
            5.5100E-02, 3.8100E-02, 2.5600E-02, 1.6900E-02, 1.1100E-02, 
            4.7000E-03, 6.0000E-04, 9.2000E-05, 4.0000E-06, 3.0000E-07, 
            5.8000E-09, 3.2000E-11} );

    subshell_half_profiles[15] = 
      std::vector<double>( {1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 
            1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 
            1.1000E-01, 1.1000E-01, 1.0900E-01, 1.0800E-01, 1.0600E-01, 
            1.0400E-01, 1.0100E-01, 9.7200E-02, 8.8900E-02, 7.5400E-02, 
            5.4100E-02, 3.7000E-02, 2.4700E-02, 1.6300E-02, 1.0600E-02, 
            4.5000E-03, 5.6000E-04, 8.5000E-05, 3.5000E-06, 2.6000E-07, 
            4.6000E-09, 2.1000E-11} );

    subshell_half_profiles[16] = 
      std::vector<double>( {5.1700E-01, 5.1600E-01, 5.1100E-01, 5.0300E-01, 
            4.9200E-01, 4.6200E-01, 4.2400E-01, 3.7900E-01, 3.3100E-01, 
            2.8300E-01, 2.3700E-01, 1.5700E-01, 9.8900E-02, 6.2400E-02, 
            4.2900E-02, 3.4400E-02, 3.1800E-02, 3.1300E-02, 2.5700E-02, 
            1.0300E-02, 3.6700E-03, 2.7300E-03, 2.6500E-03, 2.1800E-03, 
            9.4000E-04, 2.3000E-04, 1.7000E-04, 1.9000E-05, 7.2000E-06, 
            5.1000E-06, 1.0000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {3.5300E-01, 3.5300E-01, 3.5300E-01, 3.5300E-01, 
            3.5200E-01, 3.5100E-01, 3.4700E-01, 3.3900E-01, 3.2700E-01, 
            3.1100E-01, 2.9100E-01, 2.4200E-01, 1.8800E-01, 1.3800E-01, 
            9.5400E-02, 6.3300E-02, 4.1100E-02, 1.8400E-02, 1.1300E-02, 
            1.0200E-02, 6.1500E-03, 2.7700E-03, 1.2600E-03, 8.6000E-04, 
            8.0000E-04, 2.4000E-04, 5.3000E-05, 4.0000E-05, 1.9000E-05, 
            3.4000E-06, 2.2000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {3.8300E-01, 3.8300E-01, 3.8300E-01, 3.8300E-01, 
            3.8200E-01, 3.8000E-01, 3.7400E-01, 3.6300E-01, 3.4700E-01, 
            3.2500E-01, 2.9900E-01, 2.3900E-01, 1.7600E-01, 1.2200E-01, 
            8.0000E-02, 5.0500E-02, 3.1600E-02, 1.4900E-02, 1.1200E-02, 
            9.4200E-03, 4.9100E-03, 2.0200E-03, 1.0000E-03, 8.1900E-04, 
            7.6000E-04, 1.7000E-04, 5.0000E-05, 3.7000E-05, 1.5000E-05, 
            2.0000E-06, 8.7000E-08} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.9700E+00, 1.9000E+00, 1.6900E+00, 1.4000E+00, 
            1.0800E+00, 5.2800E-01, 2.1500E-01, 8.9700E-02, 5.5900E-02, 
            5.1700E-02, 5.1100E-02, 4.0900E-02, 2.5700E-02, 1.4000E-02, 
            7.1400E-03, 3.8200E-03, 2.4900E-03, 2.0400E-03, 1.8300E-03, 
            7.7800E-04, 2.5100E-04, 1.6500E-04, 1.6100E-04, 1.3500E-04, 
            5.9000E-05, 1.4000E-05, 1.0000E-05, 1.2000E-06, 4.3000E-07, 
            3.1000E-07, 6.2000E-08} );
  }
};

//! The default Compton profile generator implementation for A=69
template<>
struct DefaultComptonProfileGeneratorImpl<69u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 20 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 
            1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 
            1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 
            1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 
            1.1000E-02, 1.1000E-02, 1.0900E-02, 1.0800E-02, 1.0700E-02, 
            1.0700E-02, 9.8000E-03, 9.0000E-03, 7.0000E-03, 5.2000E-03, 
            2.6000E-03, 6.2000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.9500E-02, 3.9500E-02, 3.9500E-02, 3.9500E-02, 
            3.9500E-02, 3.9500E-02, 3.9400E-02, 3.9400E-02, 3.9400E-02, 
            3.9400E-02, 3.9300E-02, 3.9200E-02, 3.9100E-02, 3.9000E-02, 
            3.8800E-02, 3.8700E-02, 3.8500E-02, 3.8000E-02, 3.7300E-02, 
            3.5600E-02, 3.3700E-02, 3.1400E-02, 2.9000E-02, 2.6400E-02, 
            2.1000E-02, 1.0000E-02, 4.2000E-03, 1.1000E-03, 9.7000E-04, 
            6.2000E-04, 1.3000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.9400E-02, 1.9400E-02, 1.9400E-02, 1.9400E-02, 
            1.9400E-02, 1.9400E-02, 1.9400E-02, 1.9400E-02, 1.9400E-02, 
            1.9400E-02, 1.9400E-02, 1.9400E-02, 1.9400E-02, 1.9400E-02, 
            1.9400E-02, 1.9400E-02, 1.9400E-02, 1.9400E-02, 1.9400E-02, 
            1.9400E-02, 1.9300E-02, 1.9200E-02, 1.9100E-02, 1.8900E-02, 
            1.8000E-02, 1.6000E-02, 1.2000E-02, 5.7000E-03, 2.4000E-03, 
            4.4000E-04, 3.2000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.1100E-02, 2.1100E-02, 2.1100E-02, 2.1100E-02, 
            2.1100E-02, 2.1100E-02, 2.1100E-02, 2.1100E-02, 2.1100E-02, 
            2.1100E-02, 2.1100E-02, 2.1100E-02, 2.1100E-02, 2.1100E-02, 
            2.1100E-02, 2.1100E-02, 2.1100E-02, 2.1100E-02, 2.1100E-02, 
            2.1100E-02, 2.1000E-02, 2.0900E-02, 2.0700E-02, 2.0400E-02, 
            2.0000E-02, 1.6000E-02, 1.2000E-02, 5.0000E-03, 1.8000E-03, 
            2.7000E-04, 1.3000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {8.7600E-02, 8.7600E-02, 8.7500E-02, 8.7500E-02, 
            8.7400E-02, 8.7300E-02, 8.7100E-02, 8.6800E-02, 8.6400E-02, 
            8.6000E-02, 8.5500E-02, 8.4400E-02, 8.3000E-02, 8.1400E-02, 
            7.9600E-02, 7.7600E-02, 7.5500E-02, 7.0700E-02, 6.2800E-02, 
            4.8800E-02, 3.5700E-02, 2.4800E-02, 1.6800E-02, 1.1600E-02, 
            7.2000E-03, 6.2000E-03, 3.5000E-03, 4.4000E-04, 2.1000E-04, 
            1.5000E-04, 3.1000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {5.1600E-02, 5.1600E-02, 5.1600E-02, 5.1600E-02, 
            5.1600E-02, 5.1600E-02, 5.1600E-02, 5.1600E-02, 5.1600E-02, 
            5.1600E-02, 5.1500E-02, 5.1500E-02, 5.1500E-02, 5.1500E-02, 
            5.1400E-02, 5.1400E-02, 5.1300E-02, 5.1000E-02, 5.0300E-02, 
            4.8200E-02, 4.4700E-02, 4.0000E-02, 3.4300E-02, 2.8400E-02, 
            1.7000E-02, 3.7000E-03, 1.9000E-03, 1.5000E-03, 7.1000E-04, 
            1.3000E-04, 8.7000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {5.4500E-02, 5.4500E-02, 5.4500E-02, 5.4500E-02, 
            5.4500E-02, 5.4500E-02, 5.4500E-02, 5.4500E-02, 5.4500E-02, 
            5.4500E-02, 5.4500E-02, 5.4500E-02, 5.4500E-02, 5.4400E-02, 
            5.4400E-02, 5.4300E-02, 5.4200E-02, 5.3800E-02, 5.3000E-02, 
            5.0300E-02, 4.6000E-02, 4.0200E-02, 3.3700E-02, 2.7000E-02, 
            1.6000E-02, 3.2000E-03, 2.1000E-03, 1.5000E-03, 5.9000E-04, 
            8.3000E-05, 3.7000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 
            3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 
            3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 
            3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 
            3.5300E-02, 3.4900E-02, 3.4100E-02, 3.2800E-02, 3.0900E-02, 
            2.6000E-02, 1.3000E-02, 5.2000E-03, 7.5000E-04, 1.3000E-04, 
            6.9000E-06, 1.2000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.6200E-02, 3.6200E-02, 3.6200E-02, 3.6200E-02, 
            3.6200E-02, 3.6200E-02, 3.6200E-02, 3.6200E-02, 3.6200E-02, 
            3.6200E-02, 3.6200E-02, 3.6200E-02, 3.6200E-02, 3.6200E-02, 
            3.6200E-02, 3.6200E-02, 3.6200E-02, 3.6200E-02, 3.6100E-02, 
            3.6000E-02, 3.5500E-02, 3.4600E-02, 3.3200E-02, 3.1200E-02, 
            2.6000E-02, 1.3000E-02, 4.9000E-03, 6.7000E-04, 1.1000E-04, 
            5.2000E-06, 7.1000E-08} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.8600E-01, 1.8600E-01, 1.8600E-01, 1.8600E-01, 
            1.8500E-01, 1.8300E-01, 1.8100E-01, 1.7800E-01, 1.7500E-01, 
            1.7100E-01, 1.6600E-01, 1.5500E-01, 1.4400E-01, 1.3100E-01, 
            1.1800E-01, 1.0500E-01, 9.1700E-02, 6.8500E-02, 4.2000E-02, 
            2.1100E-02, 1.7200E-02, 1.6900E-02, 1.4900E-02, 1.1300E-02, 
            4.8000E-03, 1.6000E-03, 1.1000E-03, 1.4000E-04, 4.8000E-05, 
            3.6000E-05, 7.5000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.1800E-01, 1.1800E-01, 1.1800E-01, 1.1800E-01, 
            1.1800E-01, 1.1800E-01, 1.1800E-01, 1.1800E-01, 1.1800E-01, 
            1.1800E-01, 1.1800E-01, 1.1700E-01, 1.1600E-01, 1.1400E-01, 
            1.1200E-01, 1.0900E-01, 1.0600E-01, 9.6100E-02, 7.8300E-02, 
            4.6800E-02, 2.3600E-02, 1.1800E-02, 7.6400E-03, 6.9000E-03, 
            6.5000E-03, 1.8000E-03, 4.4000E-04, 3.4000E-04, 1.7000E-04, 
            3.1000E-05, 2.0000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.2500E-01, 1.2500E-01, 1.2500E-01, 1.2500E-01, 
            1.2500E-01, 1.2500E-01, 1.2500E-01, 1.2500E-01, 1.2500E-01, 
            1.2500E-01, 1.2500E-01, 1.2400E-01, 1.2200E-01, 1.2000E-01, 
            1.1700E-01, 1.1400E-01, 1.0900E-01, 9.7600E-02, 7.6700E-02, 
            4.2600E-02, 2.0200E-02, 1.0300E-02, 7.5700E-03, 7.3200E-03, 
            6.4000E-03, 1.4000E-03, 4.5000E-04, 3.4000E-04, 1.4000E-04, 
            2.0000E-05, 8.6000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {9.7500E-02, 9.7500E-02, 9.7500E-02, 9.7500E-02, 
            9.7500E-02, 9.7500E-02, 9.7500E-02, 9.7500E-02, 9.7500E-02, 
            9.7500E-02, 9.7500E-02, 9.7400E-02, 9.7300E-02, 9.7000E-02, 
            9.6500E-02, 9.5700E-02, 9.4600E-02, 9.1200E-02, 8.2600E-02, 
            6.1700E-02, 3.9700E-02, 2.2700E-02, 1.2000E-02, 6.3200E-03, 
            2.9000E-03, 2.4000E-03, 1.2000E-03, 1.9000E-04, 3.2000E-05, 
            1.7000E-06, 2.8000E-08} );

    subshell_half_profiles[13] = 
      std::vector<double>( {9.9400E-02, 9.9400E-02, 9.9400E-02, 9.9400E-02, 
            9.9400E-02, 9.9400E-02, 9.9400E-02, 9.9400E-02, 9.9400E-02, 
            9.9400E-02, 9.9400E-02, 9.9300E-02, 9.9200E-02, 9.8900E-02, 
            9.8300E-02, 9.7500E-02, 9.6300E-02, 9.2500E-02, 8.3200E-02, 
            6.1100E-02, 3.8600E-02, 2.1600E-02, 1.1200E-02, 5.8900E-03, 
            2.9000E-03, 2.3000E-03, 1.1000E-03, 1.7000E-04, 2.7000E-05, 
            1.3000E-06, 1.7000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 
            1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 
            1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0300E-01, 1.0200E-01, 
            9.9800E-02, 9.7400E-02, 9.4400E-02, 8.7500E-02, 7.5500E-02, 
            5.5600E-02, 3.9000E-02, 2.6600E-02, 1.7800E-02, 1.1800E-02, 
            5.2000E-03, 6.8000E-04, 1.1000E-04, 4.7000E-06, 3.7000E-07, 
            7.1000E-09, 4.0000E-11} );

    subshell_half_profiles[15] = 
      std::vector<double>( {1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0700E-01, 
            1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0700E-01, 
            1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0600E-01, 1.0400E-01, 
            1.0200E-01, 9.8800E-02, 9.5500E-02, 8.7900E-02, 7.5200E-02, 
            5.4700E-02, 3.8000E-02, 2.5700E-02, 1.7100E-02, 1.1300E-02, 
            4.9000E-03, 6.4000E-04, 9.9000E-05, 4.2000E-06, 3.2000E-07, 
            5.6000E-09, 2.6000E-11} );

    subshell_half_profiles[16] = 
      std::vector<double>( {5.0900E-01, 5.0700E-01, 5.0300E-01, 4.9500E-01, 
            4.8500E-01, 4.5600E-01, 4.1900E-01, 3.7700E-01, 3.3100E-01, 
            2.8400E-01, 2.3900E-01, 1.6000E-01, 1.0200E-01, 6.4600E-02, 
            4.3900E-02, 3.4400E-02, 3.1200E-02, 3.0600E-02, 2.5900E-02, 
            1.1000E-02, 3.8700E-03, 2.6700E-03, 2.6100E-03, 2.2300E-03, 
            1.0000E-03, 2.3000E-04, 1.7000E-04, 2.1000E-05, 7.1000E-06, 
            5.2000E-06, 1.1000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {3.4700E-01, 3.4700E-01, 3.4700E-01, 3.4700E-01, 
            3.4700E-01, 3.4500E-01, 3.4100E-01, 3.3400E-01, 3.2300E-01, 
            3.0800E-01, 2.8900E-01, 2.4300E-01, 1.9000E-01, 1.4100E-01, 
            9.8800E-02, 6.6400E-02, 4.3500E-02, 1.9400E-02, 1.1000E-02, 
            1.0100E-02, 6.3900E-03, 2.9800E-03, 1.3500E-03, 8.6100E-04, 
            7.9000E-04, 2.6000E-04, 5.5000E-05, 4.0000E-05, 2.0000E-05, 
            3.7000E-06, 2.4000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {3.7800E-01, 3.7800E-01, 3.7800E-01, 3.7700E-01, 
            3.7700E-01, 3.7500E-01, 3.6900E-01, 3.5900E-01, 3.4400E-01, 
            3.2300E-01, 2.9800E-01, 2.4000E-01, 1.7900E-01, 1.2500E-01, 
            8.3100E-02, 5.3000E-02, 3.3400E-02, 1.5300E-02, 1.0900E-02, 
            9.4300E-03, 5.1400E-03, 2.1700E-03, 1.0400E-03, 8.0300E-04, 
            7.5000E-04, 1.8000E-04, 5.0000E-05, 3.8000E-05, 1.6000E-05, 
            2.2000E-06, 9.6000E-08} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.9500E+00, 1.8800E+00, 1.6800E+00, 1.3900E+00, 
            1.0800E+00, 5.3700E-01, 2.2200E-01, 9.1900E-02, 5.5400E-02, 
            5.0300E-02, 4.9900E-02, 4.0800E-02, 2.6200E-02, 1.4600E-02, 
            7.5300E-03, 4.0100E-03, 2.5300E-03, 1.9600E-03, 1.8000E-03, 
            8.1300E-04, 2.6400E-04, 1.6000E-04, 1.5600E-04, 1.3500E-04, 
            6.3000E-05, 1.4000E-05, 1.0000E-05, 1.3000E-06, 4.2000E-07, 
            3.1000E-07, 6.5000E-08} );
  }
};

//! The default Compton profile generator implementation for A=70
template<>
struct DefaultComptonProfileGeneratorImpl<70u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 20 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.0900E-02, 1.0900E-02, 1.0900E-02, 1.0900E-02, 
            1.0900E-02, 1.0900E-02, 1.0900E-02, 1.0900E-02, 1.0900E-02, 
            1.0900E-02, 1.0900E-02, 1.0900E-02, 1.0900E-02, 1.0900E-02, 
            1.0900E-02, 1.0900E-02, 1.0900E-02, 1.0900E-02, 1.0900E-02, 
            1.0800E-02, 1.0800E-02, 1.0700E-02, 1.0600E-02, 1.0500E-02, 
            1.0000E-02, 9.7000E-03, 8.9000E-03, 7.0000E-03, 5.2000E-03, 
            2.6000E-03, 6.5000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.8800E-02, 3.8800E-02, 3.8800E-02, 3.8800E-02, 
            3.8700E-02, 3.8700E-02, 3.8700E-02, 3.8700E-02, 3.8700E-02, 
            3.8600E-02, 3.8600E-02, 3.8500E-02, 3.8400E-02, 3.8300E-02, 
            3.8100E-02, 3.8000E-02, 3.7800E-02, 3.7400E-02, 3.6700E-02, 
            3.5100E-02, 3.3200E-02, 3.1100E-02, 2.8700E-02, 2.6300E-02, 
            2.1000E-02, 1.1000E-02, 4.4000E-03, 1.1000E-03, 9.5000E-04, 
            6.3000E-04, 1.4000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.9000E-02, 1.9000E-02, 1.9000E-02, 1.9000E-02, 
            1.9000E-02, 1.9000E-02, 1.9000E-02, 1.9000E-02, 1.9000E-02, 
            1.9000E-02, 1.9000E-02, 1.9000E-02, 1.9000E-02, 1.9000E-02, 
            1.9000E-02, 1.9000E-02, 1.9000E-02, 1.9000E-02, 1.9000E-02, 
            1.9000E-02, 1.8900E-02, 1.8900E-02, 1.8700E-02, 1.8600E-02, 
            1.8000E-02, 1.6000E-02, 1.2000E-02, 5.8000E-03, 2.5000E-03, 
            4.8000E-04, 3.6000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.0800E-02, 2.0800E-02, 2.0800E-02, 2.0800E-02, 
            2.0800E-02, 2.0800E-02, 2.0800E-02, 2.0800E-02, 2.0800E-02, 
            2.0800E-02, 2.0800E-02, 2.0800E-02, 2.0800E-02, 2.0800E-02, 
            2.0800E-02, 2.0800E-02, 2.0800E-02, 2.0800E-02, 2.0800E-02, 
            2.0700E-02, 2.0700E-02, 2.0600E-02, 2.0400E-02, 2.0100E-02, 
            1.9000E-02, 1.6000E-02, 1.2000E-02, 5.1000E-03, 1.9000E-03, 
            2.9000E-04, 1.4000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {8.5900E-02, 8.5900E-02, 8.5800E-02, 8.5800E-02, 
            8.5700E-02, 8.5600E-02, 8.5400E-02, 8.5100E-02, 8.4800E-02, 
            8.4400E-02, 8.3900E-02, 8.2800E-02, 8.1500E-02, 8.0000E-02, 
            7.8300E-02, 7.6500E-02, 7.4400E-02, 6.9900E-02, 6.2400E-02, 
            4.8900E-02, 3.6100E-02, 2.5400E-02, 1.7400E-02, 1.2000E-02, 
            7.2000E-03, 6.2000E-03, 3.7000E-03, 4.9000E-04, 2.0000E-04, 
            1.5000E-04, 3.3000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {5.0500E-02, 5.0500E-02, 5.0500E-02, 5.0500E-02, 
            5.0500E-02, 5.0500E-02, 5.0500E-02, 5.0500E-02, 5.0500E-02, 
            5.0500E-02, 5.0500E-02, 5.0500E-02, 5.0500E-02, 5.0500E-02, 
            5.0400E-02, 5.0400E-02, 5.0300E-02, 5.0000E-02, 4.9400E-02, 
            4.7500E-02, 4.4200E-02, 3.9800E-02, 3.4500E-02, 2.8700E-02, 
            1.8000E-02, 3.9000E-03, 1.9000E-03, 1.5000E-03, 7.4000E-04, 
            1.4000E-04, 9.7000E-06} );

    subshell_half_profiles[6] = 
      std::vector<double>( {5.3500E-02, 5.3500E-02, 5.3500E-02, 5.3500E-02, 
            5.3500E-02, 5.3500E-02, 5.3500E-02, 5.3500E-02, 5.3500E-02, 
            5.3500E-02, 5.3500E-02, 5.3500E-02, 5.3500E-02, 5.3500E-02, 
            5.3400E-02, 5.3300E-02, 5.3200E-02, 5.2900E-02, 5.2100E-02, 
            4.9600E-02, 4.5600E-02, 4.0200E-02, 3.3900E-02, 2.7500E-02, 
            1.6000E-02, 3.3000E-03, 2.1000E-03, 1.5000E-03, 6.2000E-04, 
            9.0000E-05, 4.1000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {3.4800E-02, 3.4800E-02, 3.4800E-02, 3.4800E-02, 
            3.4800E-02, 3.4800E-02, 3.4800E-02, 3.4800E-02, 3.4800E-02, 
            3.4800E-02, 3.4800E-02, 3.4800E-02, 3.4800E-02, 3.4800E-02, 
            3.4800E-02, 3.4800E-02, 3.4800E-02, 3.4800E-02, 3.4800E-02, 
            3.4700E-02, 3.4300E-02, 3.3500E-02, 3.2300E-02, 3.0600E-02, 
            2.6000E-02, 1.3000E-02, 5.5000E-03, 8.2000E-04, 1.4000E-04, 
            7.8000E-06, 1.4000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 
            3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 
            3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 
            3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 
            3.5300E-02, 3.4900E-02, 3.4100E-02, 3.2800E-02, 3.1000E-02, 
            2.6000E-02, 1.3000E-02, 5.2000E-03, 7.3000E-04, 1.2000E-04, 
            5.9000E-06, 8.1000E-08} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.8300E-01, 1.8300E-01, 1.8200E-01, 1.8200E-01, 
            1.8100E-01, 1.8000E-01, 1.7800E-01, 1.7500E-01, 1.7200E-01, 
            1.6800E-01, 1.6300E-01, 1.5300E-01, 1.4200E-01, 1.3000E-01, 
            1.1700E-01, 1.0500E-01, 9.2300E-02, 6.9600E-02, 4.3200E-02, 
            2.1500E-02, 1.6900E-02, 1.6700E-02, 1.5100E-02, 1.1700E-02, 
            5.1000E-03, 1.5000E-03, 1.2000E-03, 1.5000E-04, 4.8000E-05, 
            3.6000E-05, 8.0000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 
            1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 1.1600E-01, 
            1.1500E-01, 1.1500E-01, 1.1500E-01, 1.1400E-01, 1.1200E-01, 
            1.1000E-01, 1.0800E-01, 1.0400E-01, 9.5400E-02, 7.8500E-02, 
            4.8100E-02, 2.4900E-02, 1.2400E-02, 7.7800E-03, 6.8000E-03, 
            6.5000E-03, 2.0000E-03, 4.6000E-04, 3.4000E-04, 1.8000E-04, 
            3.3000E-05, 2.3000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 
            1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 1.2300E-01, 
            1.2200E-01, 1.2200E-01, 1.2100E-01, 1.2000E-01, 1.1800E-01, 
            1.1600E-01, 1.1200E-01, 1.0800E-01, 9.7100E-02, 7.7200E-02, 
            4.4000E-02, 2.1300E-02, 1.0700E-02, 7.5800E-03, 7.2000E-03, 
            6.5000E-03, 1.5000E-03, 4.5000E-04, 3.5000E-04, 1.5000E-04, 
            2.2000E-05, 9.6000E-07} );

    subshell_half_profiles[12] = 
      std::vector<double>( {9.5400E-02, 9.5400E-02, 9.5400E-02, 9.5400E-02, 
            9.5400E-02, 9.5400E-02, 9.5400E-02, 9.5400E-02, 9.5400E-02, 
            9.5400E-02, 9.5400E-02, 9.5400E-02, 9.5300E-02, 9.5000E-02, 
            9.4600E-02, 9.3900E-02, 9.2900E-02, 8.9800E-02, 8.1900E-02, 
            6.2300E-02, 4.1000E-02, 2.3900E-02, 1.2900E-02, 6.8500E-03, 
            3.0000E-03, 2.4000E-03, 1.3000E-03, 2.1000E-04, 3.6000E-05, 
            1.9000E-06, 3.3000E-08} );

    subshell_half_profiles[13] = 
      std::vector<double>( {9.7400E-02, 9.7400E-02, 9.7400E-02, 9.7400E-02, 
            9.7400E-02, 9.7400E-02, 9.7400E-02, 9.7400E-02, 9.7400E-02, 
            9.7400E-02, 9.7400E-02, 9.7300E-02, 9.7200E-02, 9.6900E-02, 
            9.6400E-02, 9.5700E-02, 9.4600E-02, 9.1100E-02, 8.2600E-02, 
            6.1700E-02, 3.9800E-02, 2.2800E-02, 1.2000E-02, 6.3700E-03, 
            2.9000E-03, 2.4000E-03, 1.2000E-03, 1.8000E-04, 3.0000E-05, 
            1.4000E-06, 1.9000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {1.0200E-01, 1.0200E-01, 1.0200E-01, 1.0200E-01, 
            1.0200E-01, 1.0200E-01, 1.0200E-01, 1.0200E-01, 1.0200E-01, 
            1.0200E-01, 1.0200E-01, 1.0200E-01, 1.0100E-01, 9.9600E-02, 
            9.7800E-02, 9.5500E-02, 9.2800E-02, 8.6300E-02, 7.5000E-02, 
            5.5900E-02, 3.9700E-02, 2.7400E-02, 1.8600E-02, 1.2500E-02, 
            5.6000E-03, 7.7000E-04, 1.2000E-04, 5.6000E-06, 4.4000E-07, 
            8.7000E-09, 4.9000E-11} );

    subshell_half_profiles[15] = 
      std::vector<double>( {1.0500E-01, 1.0500E-01, 1.0500E-01, 1.0500E-01, 
            1.0500E-01, 1.0500E-01, 1.0500E-01, 1.0500E-01, 1.0500E-01, 
            1.0500E-01, 1.0400E-01, 1.0400E-01, 1.0300E-01, 1.0200E-01, 
            9.9500E-02, 9.6900E-02, 9.3900E-02, 8.6800E-02, 7.4800E-02, 
            5.5200E-02, 3.8900E-02, 2.6700E-02, 1.8000E-02, 1.2000E-02, 
            5.3000E-03, 7.2000E-04, 1.1000E-04, 5.0000E-06, 3.8000E-07, 
            6.9000E-09, 3.2000E-11} );

    subshell_half_profiles[16] = 
      std::vector<double>( {5.0100E-01, 4.9900E-01, 4.9500E-01, 4.8800E-01, 
            4.7800E-01, 4.5100E-01, 4.1500E-01, 3.7400E-01, 3.3000E-01, 
            2.8500E-01, 2.4100E-01, 1.6300E-01, 1.0500E-01, 6.6900E-02, 
            4.5000E-02, 3.4600E-02, 3.0800E-02, 2.9900E-02, 2.6000E-02, 
            1.1600E-02, 4.0900E-03, 2.6300E-03, 2.5700E-03, 2.2500E-03, 
            1.1000E-03, 2.3000E-04, 1.8000E-04, 2.4000E-05, 7.0000E-06, 
            5.3000E-06, 1.2000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {3.4200E-01, 3.4200E-01, 3.4200E-01, 3.4200E-01, 
            3.4100E-01, 3.4000E-01, 3.3600E-01, 3.3000E-01, 3.2000E-01, 
            3.0500E-01, 2.8700E-01, 2.4300E-01, 1.9200E-01, 1.4400E-01, 
            1.0200E-01, 6.9500E-02, 4.5900E-02, 2.0500E-02, 1.0900E-02, 
            9.9900E-03, 6.6000E-03, 3.2000E-03, 1.4400E-03, 8.7100E-04, 
            7.7000E-04, 2.8000E-04, 5.8000E-05, 4.0000E-05, 2.1000E-05, 
            4.0000E-06, 2.7000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {3.7300E-01, 3.7300E-01, 3.7300E-01, 3.7200E-01, 
            3.7200E-01, 3.7000E-01, 3.6400E-01, 3.5500E-01, 3.4000E-01, 
            3.2100E-01, 2.9700E-01, 2.4000E-01, 1.8100E-01, 1.2800E-01, 
            8.6100E-02, 5.5500E-02, 3.5200E-02, 1.5800E-02, 1.0600E-02, 
            9.4100E-03, 5.3500E-03, 2.3200E-03, 1.0800E-03, 7.9200E-04, 
            7.4000E-04, 2.0000E-04, 5.0000E-05, 3.8000E-05, 1.7000E-05, 
            2.4000E-06, 1.1000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.9400E+00, 1.8700E+00, 1.6700E+00, 1.3900E+00, 
            1.0800E+00, 5.4500E-01, 2.2800E-01, 9.4300E-02, 5.5100E-02, 
            4.8900E-02, 4.8600E-02, 4.0600E-02, 2.6600E-02, 1.5100E-02, 
            7.9300E-03, 4.2100E-03, 2.5800E-03, 1.8800E-03, 1.7600E-03, 
            8.4600E-04, 2.7800E-04, 1.5600E-04, 1.5000E-04, 1.3400E-04, 
            6.6000E-05, 1.3000E-05, 1.0000E-05, 1.4000E-06, 4.1000E-07, 
            3.1000E-07, 6.8000E-08} );
  }
};

//! The default Compton profile generator implementation for A=71
template<>
struct DefaultComptonProfileGeneratorImpl<71u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 21 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.0700E-02, 1.0700E-02, 1.0700E-02, 1.0700E-02, 
            1.0700E-02, 1.0700E-02, 1.0700E-02, 1.0700E-02, 1.0700E-02, 
            1.0700E-02, 1.0700E-02, 1.0700E-02, 1.0700E-02, 1.0700E-02, 
            1.0700E-02, 1.0700E-02, 1.0700E-02, 1.0700E-02, 1.0700E-02, 
            1.0600E-02, 1.0600E-02, 1.0500E-02, 1.0400E-02, 1.0400E-02, 
            1.0000E-02, 9.5000E-03, 8.8000E-03, 7.0000E-03, 5.2000E-03, 
            2.7000E-03, 6.8000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.8100E-02, 3.8100E-02, 3.8100E-02, 3.8100E-02, 
            3.8000E-02, 3.8000E-02, 3.8000E-02, 3.8000E-02, 3.8000E-02, 
            3.7900E-02, 3.7900E-02, 3.7800E-02, 3.7700E-02, 3.7600E-02, 
            3.7500E-02, 3.7300E-02, 3.7200E-02, 3.6800E-02, 3.6100E-02, 
            3.4600E-02, 3.2800E-02, 3.0800E-02, 2.8500E-02, 2.6100E-02, 
            2.1000E-02, 1.1000E-02, 4.6000E-03, 1.1000E-03, 9.4000E-04, 
            6.4000E-04, 1.5000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8700E-02, 
            1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8700E-02, 
            1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8700E-02, 
            1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8700E-02, 
            1.8600E-02, 1.8600E-02, 1.8500E-02, 1.8400E-02, 1.8200E-02, 
            1.8000E-02, 1.5000E-02, 1.2000E-02, 6.0000E-03, 2.6000E-03, 
            5.1000E-04, 3.9000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.0500E-02, 2.0500E-02, 2.0500E-02, 2.0500E-02, 
            2.0500E-02, 2.0500E-02, 2.0500E-02, 2.0500E-02, 2.0500E-02, 
            2.0500E-02, 2.0500E-02, 2.0500E-02, 2.0500E-02, 2.0500E-02, 
            2.0500E-02, 2.0500E-02, 2.0500E-02, 2.0500E-02, 2.0400E-02, 
            2.0400E-02, 2.0400E-02, 2.0200E-02, 2.0100E-02, 1.9800E-02, 
            1.9000E-02, 1.6000E-02, 1.2000E-02, 5.3000E-03, 2.0000E-03, 
            3.1000E-04, 1.6000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {8.4200E-02, 8.4200E-02, 8.4200E-02, 8.4100E-02, 
            8.4100E-02, 8.4000E-02, 8.3800E-02, 8.3500E-02, 8.3200E-02, 
            8.2800E-02, 8.2400E-02, 8.1400E-02, 8.0100E-02, 7.8700E-02, 
            7.7100E-02, 7.5300E-02, 7.3400E-02, 6.9100E-02, 6.1900E-02, 
            4.9000E-02, 3.6600E-02, 2.6000E-02, 1.7900E-02, 1.2400E-02, 
            7.3000E-03, 6.2000E-03, 3.8000E-03, 5.3000E-04, 2.0000E-04, 
            1.5000E-04, 3.5000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {4.9500E-02, 4.9500E-02, 4.9500E-02, 4.9500E-02, 
            4.9500E-02, 4.9500E-02, 4.9500E-02, 4.9500E-02, 4.9500E-02, 
            4.9500E-02, 4.9500E-02, 4.9500E-02, 4.9500E-02, 4.9500E-02, 
            4.9400E-02, 4.9400E-02, 4.9300E-02, 4.9100E-02, 4.8500E-02, 
            4.6700E-02, 4.3700E-02, 3.9600E-02, 3.4500E-02, 2.9000E-02, 
            1.9000E-02, 4.2000E-03, 1.9000E-03, 1.5000E-03, 7.8000E-04, 
            1.5000E-04, 1.1000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {5.2600E-02, 5.2600E-02, 5.2600E-02, 5.2600E-02, 
            5.2600E-02, 5.2600E-02, 5.2600E-02, 5.2600E-02, 5.2600E-02, 
            5.2600E-02, 5.2600E-02, 5.2600E-02, 5.2500E-02, 5.2500E-02, 
            5.2500E-02, 5.2400E-02, 5.2300E-02, 5.2000E-02, 5.1300E-02, 
            4.9000E-02, 4.5200E-02, 4.0000E-02, 3.4100E-02, 2.7800E-02, 
            1.7000E-02, 3.5000E-03, 2.1000E-03, 1.5000E-03, 6.5000E-04, 
            9.7000E-05, 4.5000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {3.4200E-02, 3.4200E-02, 3.4200E-02, 3.4200E-02, 
            3.4200E-02, 3.4200E-02, 3.4200E-02, 3.4200E-02, 3.4200E-02, 
            3.4200E-02, 3.4200E-02, 3.4200E-02, 3.4200E-02, 3.4200E-02, 
            3.4200E-02, 3.4200E-02, 3.4200E-02, 3.4200E-02, 3.4200E-02, 
            3.4000E-02, 3.3700E-02, 3.3000E-02, 3.1900E-02, 3.0300E-02, 
            2.6000E-02, 1.4000E-02, 5.7000E-03, 8.9000E-04, 1.6000E-04, 
            8.9000E-06, 1.6000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.4900E-02, 3.4900E-02, 3.4900E-02, 3.4900E-02, 
            3.4900E-02, 3.4900E-02, 3.4900E-02, 3.4900E-02, 3.4900E-02, 
            3.4900E-02, 3.4900E-02, 3.4900E-02, 3.4900E-02, 3.4900E-02, 
            3.4900E-02, 3.4900E-02, 3.4900E-02, 3.4900E-02, 3.4800E-02, 
            3.4700E-02, 3.4300E-02, 3.3600E-02, 3.2400E-02, 3.0700E-02, 
            2.6000E-02, 1.3000E-02, 5.4000E-03, 8.0000E-04, 1.3000E-04, 
            6.7000E-06, 9.3000E-08} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.7900E-01, 1.7900E-01, 1.7800E-01, 1.7800E-01, 
            1.7700E-01, 1.7600E-01, 1.7400E-01, 1.7100E-01, 1.6800E-01, 
            1.6500E-01, 1.6000E-01, 1.5100E-01, 1.4100E-01, 1.2900E-01, 
            1.1700E-01, 1.0500E-01, 9.2800E-02, 7.0700E-02, 4.4500E-02, 
            2.2000E-02, 1.6700E-02, 1.6500E-02, 1.5200E-02, 1.2100E-02, 
            5.6000E-03, 1.5000E-03, 1.2000E-03, 1.7000E-04, 4.8000E-05, 
            3.7000E-05, 8.5000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1300E-01, 
            1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1300E-01, 
            1.1300E-01, 1.1300E-01, 1.1200E-01, 1.1100E-01, 1.1000E-01, 
            1.0800E-01, 1.0600E-01, 1.0300E-01, 9.4500E-02, 7.8800E-02, 
            4.9500E-02, 2.6300E-02, 1.3300E-02, 8.0100E-03, 6.7500E-03, 
            6.5000E-03, 2.2000E-03, 4.9000E-04, 3.4000E-04, 1.9000E-04, 
            3.6000E-05, 2.5000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.2000E-01, 1.2000E-01, 1.2000E-01, 1.2000E-01, 
            1.2000E-01, 1.2000E-01, 1.2000E-01, 1.2000E-01, 1.2000E-01, 
            1.2000E-01, 1.2000E-01, 1.1900E-01, 1.1800E-01, 1.1600E-01, 
            1.1400E-01, 1.1000E-01, 1.0600E-01, 9.6500E-02, 7.7700E-02, 
            4.5400E-02, 2.2500E-02, 1.1300E-02, 7.6500E-03, 7.1200E-03, 
            6.5000E-03, 1.7000E-03, 4.6000E-04, 3.5000E-04, 1.6000E-04, 
            2.4000E-05, 1.1000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {9.3100E-02, 9.3100E-02, 9.3100E-02, 9.3100E-02, 
            9.3100E-02, 9.3100E-02, 9.3100E-02, 9.3100E-02, 9.3100E-02, 
            9.3100E-02, 9.3100E-02, 9.3000E-02, 9.2900E-02, 9.2700E-02, 
            9.2400E-02, 9.1800E-02, 9.0900E-02, 8.8200E-02, 8.1100E-02, 
            6.2900E-02, 4.2300E-02, 2.5300E-02, 1.3900E-02, 7.4800E-03, 
            3.1000E-03, 2.4000E-03, 1.3000E-03, 2.3000E-04, 4.0000E-05, 
            2.2000E-06, 3.8000E-08} );

    subshell_half_profiles[13] = 
      std::vector<double>( {9.5100E-02, 9.5100E-02, 9.5100E-02, 9.5100E-02, 
            9.5100E-02, 9.5100E-02, 9.5100E-02, 9.5100E-02, 9.5100E-02, 
            9.5000E-02, 9.5000E-02, 9.5000E-02, 9.4900E-02, 9.4600E-02, 
            9.4200E-02, 9.3600E-02, 9.2600E-02, 8.9600E-02, 8.1900E-02, 
            6.2400E-02, 4.1200E-02, 2.4100E-02, 1.3000E-02, 6.9300E-03, 
            3.0000E-03, 2.4000E-03, 1.3000E-03, 2.0000E-04, 3.4000E-05, 
            1.6000E-06, 2.2000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {9.5300E-02, 9.5300E-02, 9.5300E-02, 9.5300E-02, 
            9.5300E-02, 9.5300E-02, 9.5300E-02, 9.5300E-02, 9.5300E-02, 
            9.5200E-02, 9.5200E-02, 9.5000E-02, 9.4700E-02, 9.4000E-02, 
            9.3000E-02, 9.1500E-02, 8.9600E-02, 8.4600E-02, 7.5200E-02, 
            5.7800E-02, 4.2000E-02, 2.9500E-02, 2.0300E-02, 1.3800E-02, 
            6.3000E-03, 9.0000E-04, 1.5000E-04, 6.9000E-06, 5.6000E-07, 
            1.1000E-08, 6.4000E-11} );

    subshell_half_profiles[15] = 
      std::vector<double>( {9.6700E-02, 9.6700E-02, 9.6700E-02, 9.6700E-02, 
            9.6700E-02, 9.6700E-02, 9.6700E-02, 9.6700E-02, 9.6700E-02, 
            9.6700E-02, 9.6700E-02, 9.6500E-02, 9.6100E-02, 9.5400E-02, 
            9.4200E-02, 9.2700E-02, 9.0600E-02, 8.5400E-02, 7.5500E-02, 
            5.7500E-02, 4.1500E-02, 2.9000E-02, 1.9800E-02, 1.3400E-02, 
            6.1000E-03, 8.5000E-04, 1.4000E-04, 6.2000E-06, 4.8000E-07, 
            8.9000E-09, 4.2000E-11} );

    subshell_half_profiles[16] = 
      std::vector<double>( {4.8000E-01, 4.7800E-01, 4.7400E-01, 4.6800E-01, 
            4.5900E-01, 4.3500E-01, 4.0300E-01, 3.6600E-01, 3.2600E-01, 
            2.8400E-01, 2.4300E-01, 1.6900E-01, 1.1200E-01, 7.2400E-02, 
            4.8700E-02, 3.6500E-02, 3.1500E-02, 3.0000E-02, 2.7000E-02, 
            1.3000E-02, 4.6100E-03, 2.7200E-03, 2.6300E-03, 2.3800E-03, 
            1.2000E-03, 2.3000E-04, 1.9000E-04, 2.8000E-05, 7.3000E-06, 
            5.7000E-06, 1.3000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {3.2700E-01, 3.2700E-01, 3.2700E-01, 3.2700E-01, 
            3.2700E-01, 3.2600E-01, 3.2300E-01, 3.1700E-01, 3.0900E-01, 
            2.9700E-01, 2.8100E-01, 2.4200E-01, 1.9600E-01, 1.5000E-01, 
            1.1000E-01, 7.6700E-02, 5.1900E-02, 2.3500E-02, 1.1500E-02, 
            1.0400E-02, 7.2300E-03, 3.6600E-03, 1.6600E-03, 9.4700E-04, 
            8.0000E-04, 3.2000E-04, 6.5000E-05, 4.2000E-05, 2.3000E-05, 
            4.5000E-06, 3.2000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {3.5400E-01, 3.5400E-01, 3.5400E-01, 3.5400E-01, 
            3.5400E-01, 3.5200E-01, 3.4800E-01, 3.4000E-01, 3.2800E-01, 
            3.1200E-01, 2.9200E-01, 2.4200E-01, 1.8800E-01, 1.3700E-01, 
            9.5200E-02, 6.3200E-02, 4.0900E-02, 1.8300E-02, 1.1100E-02, 
            1.0100E-02, 6.0500E-03, 2.7200E-03, 1.2400E-03, 8.4700E-04, 
            7.9000E-04, 2.3000E-04, 5.5000E-05, 4.1000E-05, 1.9000E-05, 
            2.8000E-06, 1.3000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {4.8900E-01, 4.8900E-01, 4.8900E-01, 4.8900E-01, 
            4.8800E-01, 4.8200E-01, 4.6500E-01, 4.3300E-01, 3.8900E-01, 
            3.4000E-01, 2.9100E-01, 2.0300E-01, 1.3600E-01, 8.9500E-02, 
            5.7800E-02, 3.6900E-02, 2.3300E-02, 9.2100E-03, 2.8200E-03, 
            1.7700E-03, 1.6100E-03, 1.1300E-03, 6.6400E-04, 3.5600E-04, 
            1.2000E-04, 7.9000E-05, 4.6000E-05, 7.9000E-06, 1.4000E-06, 
            7.7000E-08, 1.3000E-09} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.7700E+00, 1.7200E+00, 1.5600E+00, 1.3300E+00, 
            1.0700E+00, 5.9400E-01, 2.7600E-01, 1.2100E-01, 6.4700E-02, 
            5.1300E-02, 5.0200E-02, 4.5600E-02, 3.3000E-02, 2.0200E-02, 
            1.1300E-02, 6.0900E-03, 3.5600E-03, 2.2300E-03, 2.1200E-03, 
            1.1100E-03, 3.7500E-04, 1.9000E-04, 1.7800E-04, 1.6400E-04, 
            8.6000E-05, 1.6000E-05, 1.3000E-05, 1.9000E-06, 4.9000E-07, 
            3.8000E-07, 8.7000E-08} );
  }
};

//! The default Compton profile generator implementation for A=72
template<>
struct DefaultComptonProfileGeneratorImpl<72u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 21 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.0500E-02, 1.0500E-02, 1.0500E-02, 1.0500E-02, 
            1.0500E-02, 1.0500E-02, 1.0500E-02, 1.0500E-02, 1.0500E-02, 
            1.0500E-02, 1.0500E-02, 1.0500E-02, 1.0500E-02, 1.0500E-02, 
            1.0500E-02, 1.0500E-02, 1.0500E-02, 1.0500E-02, 1.0500E-02, 
            1.0400E-02, 1.0400E-02, 1.0300E-02, 1.0300E-02, 1.0200E-02, 
            1.0000E-02, 9.4000E-03, 8.7000E-03, 6.9000E-03, 5.2000E-03, 
            2.7000E-03, 7.1000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.7400E-02, 3.7400E-02, 3.7400E-02, 3.7400E-02, 
            3.7400E-02, 3.7400E-02, 3.7300E-02, 3.7300E-02, 3.7300E-02, 
            3.7300E-02, 3.7200E-02, 3.7200E-02, 3.7100E-02, 3.7000E-02, 
            3.6800E-02, 3.6700E-02, 3.6500E-02, 3.6200E-02, 3.5500E-02, 
            3.4100E-02, 3.2400E-02, 3.0400E-02, 2.8300E-02, 2.6000E-02, 
            2.1000E-02, 1.1000E-02, 4.8000E-03, 1.1000E-03, 9.2000E-04, 
            6.5000E-04, 1.5000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.8300E-02, 1.8300E-02, 1.8300E-02, 1.8300E-02, 
            1.8300E-02, 1.8300E-02, 1.8300E-02, 1.8300E-02, 1.8300E-02, 
            1.8300E-02, 1.8300E-02, 1.8300E-02, 1.8300E-02, 1.8300E-02, 
            1.8300E-02, 1.8300E-02, 1.8300E-02, 1.8300E-02, 1.8300E-02, 
            1.8300E-02, 1.8300E-02, 1.8200E-02, 1.8100E-02, 1.7900E-02, 
            1.7000E-02, 1.5000E-02, 1.2000E-02, 6.2000E-03, 2.7000E-03, 
            5.5000E-04, 4.3000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {2.0100E-02, 2.0100E-02, 2.0100E-02, 2.0100E-02, 
            2.0100E-02, 2.0100E-02, 2.0100E-02, 2.0100E-02, 2.0100E-02, 
            2.0100E-02, 2.0100E-02, 2.0100E-02, 2.0100E-02, 2.0100E-02, 
            2.0100E-02, 2.0100E-02, 2.0100E-02, 2.0100E-02, 2.0100E-02, 
            2.0100E-02, 2.0000E-02, 1.9900E-02, 1.9800E-02, 1.9600E-02, 
            1.9000E-02, 1.6000E-02, 1.2000E-02, 5.4000E-03, 2.1000E-03, 
            3.3000E-04, 1.7000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {8.2600E-02, 8.2600E-02, 8.2600E-02, 8.2600E-02, 
            8.2500E-02, 8.2400E-02, 8.2200E-02, 8.1900E-02, 8.1600E-02, 
            8.1300E-02, 8.0900E-02, 7.9900E-02, 7.8800E-02, 7.7400E-02, 
            7.5900E-02, 7.4200E-02, 7.2400E-02, 6.8300E-02, 6.1400E-02, 
            4.9000E-02, 3.6900E-02, 2.6500E-02, 1.8500E-02, 1.2900E-02, 
            7.4000E-03, 6.1000E-03, 4.0000E-03, 5.9000E-04, 2.0000E-04, 
            1.6000E-04, 3.7000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {4.8600E-02, 4.8600E-02, 4.8600E-02, 4.8600E-02, 
            4.8600E-02, 4.8600E-02, 4.8600E-02, 4.8600E-02, 4.8600E-02, 
            4.8600E-02, 4.8600E-02, 4.8600E-02, 4.8500E-02, 4.8500E-02, 
            4.8500E-02, 4.8400E-02, 4.8400E-02, 4.8200E-02, 4.7600E-02, 
            4.6000E-02, 4.3200E-02, 3.9300E-02, 3.4600E-02, 2.9300E-02, 
            1.9000E-02, 4.5000E-03, 1.9000E-03, 1.5000E-03, 8.1000E-04, 
            1.6000E-04, 1.2000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {5.1700E-02, 5.1700E-02, 5.1700E-02, 5.1700E-02, 
            5.1700E-02, 5.1700E-02, 5.1700E-02, 5.1700E-02, 5.1700E-02, 
            5.1700E-02, 5.1700E-02, 5.1600E-02, 5.1600E-02, 5.1600E-02, 
            5.1500E-02, 5.1500E-02, 5.1400E-02, 5.1100E-02, 5.0400E-02, 
            4.8300E-02, 4.4700E-02, 3.9900E-02, 3.4200E-02, 2.8200E-02, 
            1.7000E-02, 3.7000E-03, 2.1000E-03, 1.6000E-03, 6.9000E-04, 
            1.1000E-04, 5.0000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {3.3600E-02, 3.3600E-02, 3.3600E-02, 3.3600E-02, 
            3.3600E-02, 3.3600E-02, 3.3600E-02, 3.3600E-02, 3.3600E-02, 
            3.3600E-02, 3.3600E-02, 3.3600E-02, 3.3600E-02, 3.3600E-02, 
            3.3600E-02, 3.3600E-02, 3.3600E-02, 3.3600E-02, 3.3500E-02, 
            3.3400E-02, 3.3100E-02, 3.2500E-02, 3.1500E-02, 3.0000E-02, 
            2.6000E-02, 1.4000E-02, 6.0000E-03, 9.7000E-04, 1.7000E-04, 
            1.0000E-05, 1.8000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.4300E-02, 3.4300E-02, 3.4300E-02, 3.4300E-02, 
            3.4300E-02, 3.4300E-02, 3.4300E-02, 3.4300E-02, 3.4300E-02, 
            3.4300E-02, 3.4300E-02, 3.4300E-02, 3.4300E-02, 3.4300E-02, 
            3.4300E-02, 3.4300E-02, 3.4300E-02, 3.4200E-02, 3.4200E-02, 
            3.4100E-02, 3.3800E-02, 3.3100E-02, 3.2000E-02, 3.0400E-02, 
            2.6000E-02, 1.4000E-02, 5.7000E-03, 8.6000E-04, 1.5000E-04, 
            7.5000E-06, 1.1000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.7500E-01, 1.7500E-01, 1.7400E-01, 1.7400E-01, 
            1.7400E-01, 1.7200E-01, 1.7000E-01, 1.6800E-01, 1.6500E-01, 
            1.6100E-01, 1.5800E-01, 1.4900E-01, 1.3900E-01, 1.2800E-01, 
            1.1600E-01, 1.0500E-01, 9.3200E-02, 7.1700E-02, 4.5800E-02, 
            2.2600E-02, 1.6600E-02, 1.6200E-02, 1.5200E-02, 1.2500E-02, 
            6.0000E-03, 1.5000E-03, 1.2000E-03, 1.9000E-04, 4.9000E-05, 
            3.8000E-05, 9.1000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 
            1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 
            1.1000E-01, 1.1000E-01, 1.1000E-01, 1.0900E-01, 1.0800E-01, 
            1.0600E-01, 1.0400E-01, 1.0100E-01, 9.3500E-02, 7.8800E-02, 
            5.0800E-02, 2.7700E-02, 1.4100E-02, 8.3100E-03, 6.7200E-03, 
            6.5000E-03, 2.4000E-03, 5.2000E-04, 3.5000E-04, 2.0000E-04, 
            4.0000E-05, 2.8000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.1800E-01, 1.1800E-01, 1.1800E-01, 1.1800E-01, 
            1.1800E-01, 1.1800E-01, 1.1800E-01, 1.1800E-01, 1.1700E-01, 
            1.1700E-01, 1.1700E-01, 1.1700E-01, 1.1500E-01, 1.1400E-01, 
            1.1200E-01, 1.0900E-01, 1.0500E-01, 9.5800E-02, 7.8100E-02, 
            4.6800E-02, 2.3700E-02, 1.1900E-02, 7.7700E-03, 7.0400E-03, 
            6.6000E-03, 1.8000E-03, 4.7000E-04, 3.6000E-04, 1.7000E-04, 
            2.6000E-05, 1.2000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {9.0800E-02, 9.0800E-02, 9.0800E-02, 9.0800E-02, 
            9.0800E-02, 9.0800E-02, 9.0800E-02, 9.0800E-02, 9.0800E-02, 
            9.0800E-02, 9.0700E-02, 9.0700E-02, 9.0600E-02, 9.0500E-02, 
            9.0200E-02, 8.9700E-02, 8.8900E-02, 8.6500E-02, 8.0200E-02, 
            6.3400E-02, 4.3600E-02, 2.6700E-02, 1.5000E-02, 8.1700E-03, 
            3.2000E-03, 2.5000E-03, 1.4000E-03, 2.5000E-04, 4.5000E-05, 
            2.5000E-06, 4.4000E-08} );

    subshell_half_profiles[13] = 
      std::vector<double>( {9.2700E-02, 9.2700E-02, 9.2700E-02, 9.2700E-02, 
            9.2700E-02, 9.2700E-02, 9.2700E-02, 9.2700E-02, 9.2700E-02, 
            9.2700E-02, 9.2700E-02, 9.2700E-02, 9.2600E-02, 9.2400E-02, 
            9.2000E-02, 9.1500E-02, 9.0700E-02, 8.8000E-02, 8.1100E-02, 
            6.3000E-02, 4.2500E-02, 2.5500E-02, 1.4100E-02, 7.5500E-03, 
            3.1000E-03, 2.4000E-03, 1.3000E-03, 2.2000E-04, 3.8000E-05, 
            1.9000E-06, 2.6000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {8.9800E-02, 8.9800E-02, 8.9800E-02, 8.9800E-02, 
            8.9800E-02, 8.9800E-02, 8.9800E-02, 8.9800E-02, 8.9800E-02, 
            8.9800E-02, 8.9800E-02, 8.9700E-02, 8.9500E-02, 8.9100E-02, 
            8.8500E-02, 8.7500E-02, 8.6200E-02, 8.2400E-02, 7.4700E-02, 
            5.9100E-02, 4.4000E-02, 3.1500E-02, 2.2000E-02, 1.5200E-02, 
            7.1000E-03, 1.1000E-03, 1.8000E-04, 8.5000E-06, 7.0000E-07, 
            1.4000E-08, 8.2000E-11} );

    subshell_half_profiles[15] = 
      std::vector<double>( {9.0700E-02, 9.0700E-02, 9.0700E-02, 9.0700E-02, 
            9.0700E-02, 9.0700E-02, 9.0700E-02, 9.0700E-02, 9.0700E-02, 
            9.0700E-02, 9.0700E-02, 9.0600E-02, 9.0400E-02, 9.0100E-02, 
            8.9400E-02, 8.8400E-02, 8.7000E-02, 8.3200E-02, 7.5200E-02, 
            5.9100E-02, 4.3700E-02, 3.1100E-02, 2.1600E-02, 1.4800E-02, 
            6.8000E-03, 1.0000E-03, 1.7000E-04, 7.7000E-06, 6.0000E-07, 
            1.1000E-08, 5.4000E-11} );

    subshell_half_profiles[16] = 
      std::vector<double>( {4.6100E-01, 4.5900E-01, 4.5600E-01, 4.5000E-01, 
            4.4200E-01, 4.2000E-01, 3.9200E-01, 3.5800E-01, 3.2100E-01, 
            2.8300E-01, 2.4500E-01, 1.7400E-01, 1.1800E-01, 7.7600E-02, 
            5.2400E-02, 3.8500E-02, 3.2300E-02, 2.9900E-02, 2.7800E-02, 
            1.4400E-02, 5.2200E-03, 2.8400E-03, 2.6800E-03, 2.4900E-03, 
            1.4000E-03, 2.4000E-04, 2.0000E-04, 3.2000E-05, 7.7000E-06, 
            6.0000E-06, 1.4000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {3.1400E-01, 3.1400E-01, 3.1400E-01, 3.1400E-01, 
            3.1400E-01, 3.1300E-01, 3.1100E-01, 3.0600E-01, 2.9900E-01, 
            2.8800E-01, 2.7500E-01, 2.4000E-01, 1.9800E-01, 1.5600E-01, 
            1.1600E-01, 8.3400E-02, 5.7800E-02, 2.6800E-02, 1.2100E-02, 
            1.0600E-02, 7.8400E-03, 4.1600E-03, 1.9200E-03, 1.0400E-03, 
            8.2000E-04, 3.6000E-04, 7.3000E-05, 4.4000E-05, 2.5000E-05, 
            5.2000E-06, 3.7000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {3.3800E-01, 3.3800E-01, 3.3800E-01, 3.3800E-01, 
            3.3800E-01, 3.3600E-01, 3.3300E-01, 3.2700E-01, 3.1700E-01, 
            3.0300E-01, 2.8600E-01, 2.4200E-01, 1.9300E-01, 1.4500E-01, 
            1.0300E-01, 7.0400E-02, 4.6700E-02, 2.1000E-02, 1.1600E-02, 
            1.0600E-02, 6.7500E-03, 3.1500E-03, 1.4200E-03, 9.0900E-04, 
            8.3000E-04, 2.7000E-04, 6.0000E-05, 4.5000E-05, 2.1000E-05, 
            3.2000E-06, 1.5000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {4.2300E-01, 4.2300E-01, 4.2300E-01, 4.2300E-01, 
            4.2300E-01, 4.2000E-01, 4.1200E-01, 3.9600E-01, 3.7100E-01, 
            3.3900E-01, 3.0200E-01, 2.2900E-01, 1.6500E-01, 1.1500E-01, 
            7.7900E-02, 5.1900E-02, 3.4000E-02, 1.4200E-02, 4.2400E-03, 
            2.2400E-03, 2.1000E-03, 1.5400E-03, 9.3700E-04, 5.1500E-04, 
            1.6000E-04, 1.0000E-04, 6.3000E-05, 1.1000E-05, 2.1000E-06, 
            1.1000E-07, 2.0000E-09} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.6800E+00, 1.6300E+00, 1.5000E+00, 1.3000E+00, 
            1.0700E+00, 6.2100E-01, 3.0800E-01, 1.4100E-01, 7.2700E-02, 
            5.2600E-02, 4.9600E-02, 4.7200E-02, 3.6600E-02, 2.4000E-02, 
            1.4100E-02, 7.8500E-03, 4.5300E-03, 2.4700E-03, 2.3100E-03, 
            1.3400E-03, 4.7000E-04, 2.1700E-04, 1.9500E-04, 1.8500E-04, 
            1.0000E-04, 1.7000E-05, 1.5000E-05, 2.4000E-06, 5.5000E-07, 
            4.3000E-07, 1.0000E-07} );
  }
};

//! The default Compton profile generator implementation for A=73
template<>
struct DefaultComptonProfileGeneratorImpl<73u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 21 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.0300E-02, 1.0300E-02, 1.0300E-02, 1.0300E-02, 
            1.0300E-02, 1.0300E-02, 1.0300E-02, 1.0300E-02, 1.0300E-02, 
            1.0300E-02, 1.0300E-02, 1.0300E-02, 1.0300E-02, 1.0300E-02, 
            1.0300E-02, 1.0300E-02, 1.0300E-02, 1.0300E-02, 1.0300E-02, 
            1.0300E-02, 1.0200E-02, 1.0200E-02, 1.0100E-02, 1.0000E-02, 
            9.8000E-03, 9.3000E-03, 8.6000E-03, 6.9000E-03, 5.2000E-03, 
            2.8000E-03, 7.4000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.6700E-02, 3.6700E-02, 3.6700E-02, 3.6700E-02, 
            3.6700E-02, 3.6700E-02, 3.6700E-02, 3.6700E-02, 3.6600E-02, 
            3.6600E-02, 3.6600E-02, 3.6500E-02, 3.6400E-02, 3.6300E-02, 
            3.6200E-02, 3.6100E-02, 3.5900E-02, 3.5600E-02, 3.4900E-02, 
            3.3600E-02, 3.2000E-02, 3.0100E-02, 2.8000E-02, 2.5900E-02, 
            2.1000E-02, 1.1000E-02, 5.0000E-03, 1.1000E-03, 9.0000E-04, 
            6.6000E-04, 1.6000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.8000E-02, 1.8000E-02, 1.8000E-02, 1.8000E-02, 
            1.8000E-02, 1.8000E-02, 1.8000E-02, 1.8000E-02, 1.8000E-02, 
            1.8000E-02, 1.8000E-02, 1.8000E-02, 1.8000E-02, 1.8000E-02, 
            1.8000E-02, 1.8000E-02, 1.8000E-02, 1.8000E-02, 1.8000E-02, 
            1.8000E-02, 1.7900E-02, 1.7900E-02, 1.7800E-02, 1.7600E-02, 
            1.7000E-02, 1.5000E-02, 1.2000E-02, 6.3000E-03, 2.9000E-03, 
            5.9000E-04, 4.8000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 
            1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 
            1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 
            1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 1.9800E-02, 
            1.9800E-02, 1.9700E-02, 1.9600E-02, 1.9500E-02, 1.9300E-02, 
            1.9000E-02, 1.6000E-02, 1.2000E-02, 5.5000E-03, 2.2000E-03, 
            3.6000E-04, 1.9000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {8.1100E-02, 8.1100E-02, 8.1000E-02, 8.1000E-02, 
            8.1000E-02, 8.0800E-02, 8.0600E-02, 8.0400E-02, 8.0100E-02, 
            7.9800E-02, 7.9400E-02, 7.8500E-02, 7.7400E-02, 7.6100E-02, 
            7.4700E-02, 7.3100E-02, 7.1300E-02, 6.7500E-02, 6.0900E-02, 
            4.9000E-02, 3.7300E-02, 2.7100E-02, 1.9000E-02, 1.3300E-02, 
            7.5000E-03, 6.1000E-03, 4.1000E-03, 6.5000E-04, 2.0000E-04, 
            1.6000E-04, 4.0000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {4.7600E-02, 4.7600E-02, 4.7600E-02, 4.7600E-02, 
            4.7600E-02, 4.7600E-02, 4.7600E-02, 4.7600E-02, 4.7600E-02, 
            4.7600E-02, 4.7600E-02, 4.7600E-02, 4.7600E-02, 4.7600E-02, 
            4.7600E-02, 4.7500E-02, 4.7500E-02, 4.7300E-02, 4.6800E-02, 
            4.5300E-02, 4.2700E-02, 3.9100E-02, 3.4500E-02, 2.9500E-02, 
            2.0000E-02, 4.8000E-03, 1.9000E-03, 1.6000E-03, 8.5000E-04, 
            1.8000E-04, 1.3000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {5.0800E-02, 5.0800E-02, 5.0800E-02, 5.0800E-02, 
            5.0800E-02, 5.0800E-02, 5.0800E-02, 5.0800E-02, 5.0800E-02, 
            5.0800E-02, 5.0800E-02, 5.0700E-02, 5.0700E-02, 5.0700E-02, 
            5.0700E-02, 5.0600E-02, 5.0500E-02, 5.0300E-02, 4.9600E-02, 
            4.7600E-02, 4.4300E-02, 3.9800E-02, 3.4300E-02, 2.8500E-02, 
            1.8000E-02, 3.9000E-03, 2.0000E-03, 1.6000E-03, 7.2000E-04, 
            1.1000E-04, 5.5000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {3.3000E-02, 3.3000E-02, 3.3000E-02, 3.3000E-02, 
            3.3000E-02, 3.3000E-02, 3.3000E-02, 3.3000E-02, 3.3000E-02, 
            3.3000E-02, 3.3000E-02, 3.3000E-02, 3.3000E-02, 3.3000E-02, 
            3.3000E-02, 3.3000E-02, 3.3000E-02, 3.2900E-02, 3.2900E-02, 
            3.2800E-02, 3.2600E-02, 3.2000E-02, 3.1100E-02, 2.9700E-02, 
            2.6000E-02, 1.4000E-02, 6.3000E-03, 1.0000E-03, 1.9000E-04, 
            1.1000E-05, 2.1000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.3700E-02, 3.3700E-02, 3.3700E-02, 3.3700E-02, 
            3.3700E-02, 3.3700E-02, 3.3700E-02, 3.3700E-02, 3.3700E-02, 
            3.3700E-02, 3.3700E-02, 3.3700E-02, 3.3700E-02, 3.3700E-02, 
            3.3700E-02, 3.3700E-02, 3.3700E-02, 3.3600E-02, 3.3600E-02, 
            3.3500E-02, 3.3200E-02, 3.2600E-02, 3.1600E-02, 3.0100E-02, 
            2.6000E-02, 1.4000E-02, 6.0000E-03, 9.3000E-04, 1.6000E-04, 
            8.4000E-06, 1.2000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.7100E-01, 1.7100E-01, 1.7100E-01, 1.7000E-01, 
            1.7000E-01, 1.6800E-01, 1.6700E-01, 1.6400E-01, 1.6200E-01, 
            1.5800E-01, 1.5500E-01, 1.4700E-01, 1.3700E-01, 1.2700E-01, 
            1.1600E-01, 1.0500E-01, 9.3500E-02, 7.2700E-02, 4.7100E-02, 
            2.3200E-02, 1.6500E-02, 1.6000E-02, 1.5200E-02, 1.2800E-02, 
            6.4000E-03, 1.5000E-03, 1.3000E-03, 2.2000E-04, 4.9000E-05, 
            3.9000E-05, 9.7000E-06} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 
            1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 
            1.0800E-01, 1.0800E-01, 1.0700E-01, 1.0700E-01, 1.0500E-01, 
            1.0400E-01, 1.0200E-01, 9.9300E-02, 9.2500E-02, 7.8800E-02, 
            5.2000E-02, 2.9200E-02, 1.5100E-02, 8.6700E-03, 6.7300E-03, 
            6.4000E-03, 2.5000E-03, 5.6000E-04, 3.5000E-04, 2.1000E-04, 
            4.3000E-05, 3.2000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.1500E-01, 1.1500E-01, 1.1500E-01, 1.1500E-01, 
            1.1500E-01, 1.1500E-01, 1.1500E-01, 1.1500E-01, 1.1500E-01, 
            1.1500E-01, 1.1500E-01, 1.1400E-01, 1.1300E-01, 1.1200E-01, 
            1.1000E-01, 1.0700E-01, 1.0400E-01, 9.5100E-02, 7.8400E-02, 
            4.8200E-02, 2.5000E-02, 1.2600E-02, 7.9400E-03, 6.9800E-03, 
            6.6000E-03, 2.0000E-03, 4.9000E-04, 3.7000E-04, 1.8000E-04, 
            2.8000E-05, 1.3000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {8.8500E-02, 8.8500E-02, 8.8500E-02, 8.8500E-02, 
            8.8500E-02, 8.8500E-02, 8.8500E-02, 8.8500E-02, 8.8500E-02, 
            8.8500E-02, 8.8500E-02, 8.8500E-02, 8.8400E-02, 8.8200E-02, 
            8.8000E-02, 8.7600E-02, 8.6900E-02, 8.4900E-02, 7.9200E-02, 
            6.3700E-02, 4.4900E-02, 2.8100E-02, 1.6200E-02, 8.9100E-03, 
            3.4000E-03, 2.5000E-03, 1.5000E-03, 2.7000E-04, 5.0000E-05, 
            2.9000E-06, 5.2000E-08} );

    subshell_half_profiles[13] = 
      std::vector<double>( {9.0500E-02, 9.0500E-02, 9.0500E-02, 9.0500E-02, 
            9.0500E-02, 9.0500E-02, 9.0500E-02, 9.0500E-02, 9.0500E-02, 
            9.0500E-02, 9.0500E-02, 9.0400E-02, 9.0400E-02, 9.0200E-02, 
            8.9900E-02, 8.9400E-02, 8.8700E-02, 8.6400E-02, 8.0200E-02, 
            6.3500E-02, 4.3800E-02, 2.6900E-02, 1.5100E-02, 8.2200E-03, 
            3.2000E-03, 2.5000E-03, 1.4000E-03, 2.4000E-04, 4.2000E-05, 
            2.1000E-06, 3.0000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {8.5300E-02, 8.5300E-02, 8.5300E-02, 8.5300E-02, 
            8.5300E-02, 8.5300E-02, 8.5300E-02, 8.5300E-02, 8.5300E-02, 
            8.5300E-02, 8.5200E-02, 8.5200E-02, 8.5100E-02, 8.4800E-02, 
            8.4400E-02, 8.3700E-02, 8.2800E-02, 8.0000E-02, 7.3700E-02, 
            5.9900E-02, 4.5600E-02, 3.3300E-02, 2.3600E-02, 1.6500E-02, 
            7.9000E-03, 1.2000E-03, 2.1000E-04, 1.0000E-05, 8.6000E-07, 
            1.8000E-08, 1.0000E-10} );

    subshell_half_profiles[15] = 
      std::vector<double>( {8.5800E-02, 8.5800E-02, 8.5800E-02, 8.5800E-02, 
            8.5800E-02, 8.5800E-02, 8.5800E-02, 8.5800E-02, 8.5800E-02, 
            8.5800E-02, 8.5800E-02, 8.5800E-02, 8.5700E-02, 8.5500E-02, 
            8.5100E-02, 8.4400E-02, 8.3500E-02, 8.0700E-02, 7.4300E-02, 
            6.0100E-02, 4.5500E-02, 3.3000E-02, 2.3300E-02, 1.6200E-02, 
            7.6000E-03, 1.2000E-03, 2.0000E-04, 9.3000E-06, 7.5000E-07, 
            1.4000E-08, 6.9000E-11} );

    subshell_half_profiles[16] = 
      std::vector<double>( {4.4300E-01, 4.4200E-01, 4.3900E-01, 4.3400E-01, 
            4.2700E-01, 4.0700E-01, 3.8100E-01, 3.5000E-01, 3.1600E-01, 
            2.8100E-01, 2.4500E-01, 1.7800E-01, 1.2300E-01, 8.2700E-02, 
            5.6100E-02, 4.0800E-02, 3.3300E-02, 2.9800E-02, 2.8400E-02, 
            1.5800E-02, 5.9100E-03, 2.9900E-03, 2.7300E-03, 2.5900E-03, 
            1.5000E-03, 2.5000E-04, 2.1000E-04, 3.8000E-05, 8.1000E-06, 
            6.3000E-06, 1.6000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {3.0200E-01, 3.0200E-01, 3.0200E-01, 3.0200E-01, 
            3.0200E-01, 3.0100E-01, 2.9900E-01, 2.9500E-01, 2.8900E-01, 
            2.8000E-01, 2.6800E-01, 2.3700E-01, 2.0000E-01, 1.6000E-01, 
            1.2200E-01, 8.9600E-02, 6.3500E-02, 3.0400E-02, 1.3000E-02, 
            1.0800E-02, 8.4100E-03, 4.6800E-03, 2.2000E-03, 1.1500E-03, 
            8.4000E-04, 4.0000E-04, 8.3000E-05, 4.6000E-05, 2.8000E-05, 
            5.8000E-06, 4.3000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {3.2400E-01, 3.2400E-01, 3.2400E-01, 3.2400E-01, 
            3.2400E-01, 3.2300E-01, 3.2000E-01, 3.1500E-01, 3.0600E-01, 
            2.9500E-01, 2.8000E-01, 2.4100E-01, 1.9600E-01, 1.5100E-01, 
            1.1000E-01, 7.7300E-02, 5.2500E-02, 2.3900E-02, 1.2100E-02, 
            1.1100E-02, 7.4500E-03, 3.6300E-03, 1.6300E-03, 9.8100E-04, 
            8.7000E-04, 3.0000E-04, 6.6000E-05, 4.8000E-05, 2.3000E-05, 
            3.6000E-06, 1.7000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {3.8200E-01, 3.8200E-01, 3.8200E-01, 3.8200E-01, 
            3.8200E-01, 3.8100E-01, 3.7600E-01, 3.6700E-01, 3.5000E-01, 
            3.2800E-01, 3.0100E-01, 2.4100E-01, 1.8200E-01, 1.3300E-01, 
            9.4100E-02, 6.5100E-02, 4.4100E-02, 1.9500E-02, 5.8700E-03, 
            2.6000E-03, 2.4900E-03, 1.9100E-03, 1.2100E-03, 6.8000E-04, 
            2.1000E-04, 1.2000E-04, 7.8000E-05, 1.5000E-05, 2.7000E-06, 
            1.6000E-07, 2.8000E-09} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.6100E+00, 1.5600E+00, 1.4400E+00, 1.2700E+00, 
            1.0600E+00, 6.4000E-01, 3.3300E-01, 1.5900E-01, 8.0600E-02, 
            5.4200E-02, 4.8700E-02, 4.7200E-02, 3.8800E-02, 2.6900E-02, 
            1.6600E-02, 9.6100E-03, 5.5600E-03, 2.7100E-03, 2.4200E-03, 
            1.5400E-03, 5.7000E-04, 2.4500E-04, 2.0800E-04, 2.0100E-04, 
            1.2000E-04, 1.9000E-05, 1.6000E-05, 2.9000E-06, 6.1000E-07, 
            4.8000E-07, 1.2000E-07} );
  }
};

//! The default Compton profile generator implementation for A=74
template<>
struct DefaultComptonProfileGeneratorImpl<74u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 21 );

    subshell_half_profiles[0] = 
      std::vector<double>( {1.0100E-02, 1.0100E-02, 1.0100E-02, 1.0100E-02, 
            1.0100E-02, 1.0100E-02, 1.0100E-02, 1.0100E-02, 1.0100E-02, 
            1.0100E-02, 1.0100E-02, 1.0100E-02, 1.0100E-02, 1.0100E-02, 
            1.0100E-02, 1.0100E-02, 1.0100E-02, 1.0100E-02, 1.0100E-02, 
            1.0100E-02, 1.0000E-02, 9.9800E-03, 9.9200E-03, 9.8500E-03, 
            9.7000E-03, 9.1000E-03, 8.5000E-03, 6.8000E-03, 5.2000E-03, 
            2.8000E-03, 7.7000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.6100E-02, 3.6100E-02, 3.6100E-02, 3.6100E-02, 
            3.6100E-02, 3.6000E-02, 3.6000E-02, 3.6000E-02, 3.6000E-02, 
            3.6000E-02, 3.5900E-02, 3.5900E-02, 3.5800E-02, 3.5700E-02, 
            3.5600E-02, 3.5400E-02, 3.5300E-02, 3.5000E-02, 3.4400E-02, 
            3.3100E-02, 3.1600E-02, 2.9800E-02, 2.7800E-02, 2.5700E-02, 
            2.1000E-02, 1.2000E-02, 5.3000E-03, 1.2000E-03, 8.9000E-04, 
            6.7000E-04, 1.7000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.7700E-02, 1.7700E-02, 1.7700E-02, 1.7700E-02, 
            1.7700E-02, 1.7700E-02, 1.7700E-02, 1.7700E-02, 1.7700E-02, 
            1.7700E-02, 1.7700E-02, 1.7700E-02, 1.7700E-02, 1.7700E-02, 
            1.7700E-02, 1.7600E-02, 1.7600E-02, 1.7600E-02, 1.7600E-02, 
            1.7600E-02, 1.7600E-02, 1.7500E-02, 1.7400E-02, 1.7300E-02, 
            1.7000E-02, 1.5000E-02, 1.2000E-02, 6.4000E-03, 3.0000E-03, 
            6.3000E-04, 5.3000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.9500E-02, 1.9500E-02, 1.9500E-02, 1.9500E-02, 
            1.9500E-02, 1.9500E-02, 1.9500E-02, 1.9500E-02, 1.9500E-02, 
            1.9500E-02, 1.9500E-02, 1.9500E-02, 1.9500E-02, 1.9500E-02, 
            1.9500E-02, 1.9500E-02, 1.9500E-02, 1.9500E-02, 1.9500E-02, 
            1.9500E-02, 1.9400E-02, 1.9400E-02, 1.9200E-02, 1.9000E-02, 
            1.8000E-02, 1.6000E-02, 1.2000E-02, 5.7000E-03, 2.3000E-03, 
            3.8000E-04, 2.0000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {7.9600E-02, 7.9600E-02, 7.9500E-02, 7.9500E-02, 
            7.9500E-02, 7.9300E-02, 7.9200E-02, 7.8900E-02, 7.8700E-02, 
            7.8400E-02, 7.8000E-02, 7.7100E-02, 7.6100E-02, 7.4900E-02, 
            7.3500E-02, 7.2000E-02, 7.0300E-02, 6.6700E-02, 6.0400E-02, 
            4.8900E-02, 3.7600E-02, 2.7600E-02, 1.9500E-02, 1.3700E-02, 
            7.7000E-03, 6.0000E-03, 4.2000E-03, 7.1000E-04, 2.0000E-04, 
            1.6000E-04, 4.2000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {4.6700E-02, 4.6700E-02, 4.6700E-02, 4.6700E-02, 
            4.6700E-02, 4.6700E-02, 4.6700E-02, 4.6700E-02, 4.6700E-02, 
            4.6700E-02, 4.6700E-02, 4.6700E-02, 4.6700E-02, 4.6700E-02, 
            4.6700E-02, 4.6600E-02, 4.6600E-02, 4.6400E-02, 4.6000E-02, 
            4.4600E-02, 4.2200E-02, 3.8800E-02, 3.4500E-02, 2.9700E-02, 
            2.0000E-02, 5.1000E-03, 1.9000E-03, 1.6000E-03, 8.8000E-04, 
            1.9000E-04, 1.5000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {4.9900E-02, 4.9900E-02, 4.9900E-02, 4.9900E-02, 
            4.9900E-02, 4.9900E-02, 4.9900E-02, 4.9900E-02, 4.9900E-02, 
            4.9900E-02, 4.9900E-02, 4.9900E-02, 4.9900E-02, 4.9800E-02, 
            4.9800E-02, 4.9700E-02, 4.9700E-02, 4.9400E-02, 4.8900E-02, 
            4.7000E-02, 4.3900E-02, 3.9600E-02, 3.4400E-02, 2.8800E-02, 
            1.8000E-02, 4.1000E-03, 2.0000E-03, 1.6000E-03, 7.5000E-04, 
            1.2000E-04, 6.0000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {3.2400E-02, 3.2400E-02, 3.2400E-02, 3.2400E-02, 
            3.2400E-02, 3.2400E-02, 3.2400E-02, 3.2400E-02, 3.2400E-02, 
            3.2400E-02, 3.2400E-02, 3.2400E-02, 3.2400E-02, 3.2400E-02, 
            3.2400E-02, 3.2400E-02, 3.2400E-02, 3.2400E-02, 3.2300E-02, 
            3.2300E-02, 3.2000E-02, 3.1500E-02, 3.0700E-02, 2.9400E-02, 
            2.6000E-02, 1.5000E-02, 6.6000E-03, 1.1000E-03, 2.1000E-04, 
            1.3000E-05, 2.4000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.3100E-02, 3.3100E-02, 3.3100E-02, 3.3100E-02, 
            3.3100E-02, 3.3100E-02, 3.3100E-02, 3.3100E-02, 3.3100E-02, 
            3.3100E-02, 3.3100E-02, 3.3100E-02, 3.3100E-02, 3.3100E-02, 
            3.3100E-02, 3.3100E-02, 3.3100E-02, 3.3100E-02, 3.3000E-02, 
            3.2900E-02, 3.2700E-02, 3.2100E-02, 3.1200E-02, 2.9800E-02, 
            2.6000E-02, 1.4000E-02, 6.2000E-03, 1.0000E-03, 1.8000E-04, 
            9.4000E-06, 1.4000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.6700E-01, 1.6700E-01, 1.6700E-01, 1.6600E-01, 
            1.6600E-01, 1.6500E-01, 1.6300E-01, 1.6100E-01, 1.5800E-01, 
            1.5500E-01, 1.5200E-01, 1.4400E-01, 1.3500E-01, 1.2500E-01, 
            1.1500E-01, 1.0400E-01, 9.3700E-02, 7.3500E-02, 4.8300E-02, 
            2.3900E-02, 1.6500E-02, 1.5800E-02, 1.5200E-02, 1.3000E-02, 
            6.8000E-03, 1.5000E-03, 1.3000E-03, 2.4000E-04, 5.1000E-05, 
            4.0000E-05, 1.0000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.0500E-01, 1.0500E-01, 1.0500E-01, 1.0500E-01, 
            1.0500E-01, 1.0500E-01, 1.0500E-01, 1.0500E-01, 1.0500E-01, 
            1.0500E-01, 1.0500E-01, 1.0500E-01, 1.0400E-01, 1.0300E-01, 
            1.0200E-01, 1.0000E-01, 9.7700E-02, 9.1400E-02, 7.8700E-02, 
            5.3100E-02, 3.0600E-02, 1.6000E-02, 9.0900E-03, 6.7800E-03, 
            6.4000E-03, 2.7000E-03, 6.0000E-04, 3.5000E-04, 2.1000E-04, 
            4.7000E-05, 3.6000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1300E-01, 
            1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1300E-01, 
            1.1200E-01, 1.1200E-01, 1.1200E-01, 1.1100E-01, 1.1000E-01, 
            1.0800E-01, 1.0500E-01, 1.0200E-01, 9.4300E-02, 7.8600E-02, 
            4.9400E-02, 2.6300E-02, 1.3300E-02, 8.1500E-03, 6.9400E-03, 
            6.7000E-03, 2.1000E-03, 5.1000E-04, 3.8000E-04, 1.9000E-04, 
            3.0000E-05, 1.5000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {8.6300E-02, 8.6300E-02, 8.6300E-02, 8.6300E-02, 
            8.6300E-02, 8.6300E-02, 8.6300E-02, 8.6300E-02, 8.6300E-02, 
            8.6300E-02, 8.6300E-02, 8.6300E-02, 8.6200E-02, 8.6100E-02, 
            8.5900E-02, 8.5500E-02, 8.5000E-02, 8.3200E-02, 7.8200E-02, 
            6.3900E-02, 4.6000E-02, 2.9500E-02, 1.7300E-02, 9.6900E-03, 
            3.6000E-03, 2.5000E-03, 1.5000E-03, 3.0000E-04, 5.6000E-05, 
            3.3000E-06, 6.0000E-08} );

    subshell_half_profiles[13] = 
      std::vector<double>( {8.8300E-02, 8.8300E-02, 8.8300E-02, 8.8300E-02, 
            8.8300E-02, 8.8300E-02, 8.8300E-02, 8.8300E-02, 8.8300E-02, 
            8.8300E-02, 8.8300E-02, 8.8300E-02, 8.8200E-02, 8.8100E-02, 
            8.7800E-02, 8.7400E-02, 8.6800E-02, 8.4800E-02, 7.9200E-02, 
            6.3800E-02, 4.5000E-02, 2.8200E-02, 1.6200E-02, 8.9300E-03, 
            3.4000E-03, 2.5000E-03, 1.5000E-03, 2.7000E-04, 4.7000E-05, 
            2.4000E-06, 3.4000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {8.1300E-02, 8.1300E-02, 8.1300E-02, 8.1300E-02, 
            8.1300E-02, 8.1300E-02, 8.1300E-02, 8.1300E-02, 8.1300E-02, 
            8.1300E-02, 8.1300E-02, 8.1300E-02, 8.1200E-02, 8.1100E-02, 
            8.0800E-02, 8.0300E-02, 7.9600E-02, 7.7500E-02, 7.2400E-02, 
            6.0300E-02, 4.6900E-02, 3.4900E-02, 2.5200E-02, 1.7800E-02, 
            8.7000E-03, 1.4000E-03, 2.5000E-04, 1.2000E-05, 1.1000E-06, 
            2.2000E-08, 1.3000E-10} );

    subshell_half_profiles[15] = 
      std::vector<double>( {8.1700E-02, 8.1700E-02, 8.1700E-02, 8.1700E-02, 
            8.1700E-02, 8.1700E-02, 8.1700E-02, 8.1700E-02, 8.1700E-02, 
            8.1700E-02, 8.1700E-02, 8.1700E-02, 8.1600E-02, 8.1500E-02, 
            8.1200E-02, 8.0800E-02, 8.0100E-02, 7.8100E-02, 7.3000E-02, 
            6.0600E-02, 4.7000E-02, 3.4700E-02, 2.4900E-02, 1.7500E-02, 
            8.4000E-03, 1.3000E-03, 2.3000E-04, 1.1000E-05, 9.2000E-07, 
            1.8000E-08, 8.7000E-11} );

    subshell_half_profiles[16] = 
      std::vector<double>( {4.2700E-01, 4.2600E-01, 4.2300E-01, 4.1800E-01, 
            4.1200E-01, 3.9400E-01, 3.7100E-01, 3.4200E-01, 3.1100E-01, 
            2.7800E-01, 2.4500E-01, 1.8200E-01, 1.2800E-01, 8.7500E-02, 
            5.9900E-02, 4.3200E-02, 3.4500E-02, 2.9700E-02, 2.8700E-02, 
            1.7100E-02, 6.6800E-03, 3.1700E-03, 2.7600E-03, 2.6800E-03, 
            1.6000E-03, 2.6000E-04, 2.2000E-04, 4.3000E-05, 8.6000E-06, 
            6.6000E-06, 1.7000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {2.9100E-01, 2.9100E-01, 2.9100E-01, 2.9100E-01, 
            2.9100E-01, 2.9000E-01, 2.8900E-01, 2.8500E-01, 2.8000E-01, 
            2.7200E-01, 2.6200E-01, 2.3400E-01, 2.0000E-01, 1.6300E-01, 
            1.2700E-01, 9.5400E-02, 6.9100E-02, 3.4100E-02, 1.4000E-02, 
            1.0900E-02, 8.9400E-03, 5.2200E-03, 2.5300E-03, 1.2800E-03, 
            8.5000E-04, 4.4000E-04, 9.5000E-05, 4.7000E-05, 3.0000E-05, 
            6.5000E-06, 4.9000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {3.1100E-01, 3.1100E-01, 3.1100E-01, 3.1100E-01, 
            3.1100E-01, 3.1000E-01, 3.0800E-01, 3.0300E-01, 2.9600E-01, 
            2.8600E-01, 2.7300E-01, 2.3900E-01, 1.9800E-01, 1.5600E-01, 
            1.1700E-01, 8.3700E-02, 5.8100E-02, 2.7100E-02, 1.2800E-02, 
            1.1400E-02, 8.1100E-03, 4.1300E-03, 1.8700E-03, 1.0600E-03, 
            9.0000E-04, 3.5000E-04, 7.3000E-05, 5.1000E-05, 2.5000E-05, 
            4.1000E-06, 2.0000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {3.5200E-01, 3.5200E-01, 3.5200E-01, 3.5200E-01, 
            3.5200E-01, 3.5100E-01, 3.4900E-01, 3.4200E-01, 3.3100E-01, 
            3.1500E-01, 2.9500E-01, 2.4500E-01, 1.9400E-01, 1.4700E-01, 
            1.0800E-01, 7.6900E-02, 5.3700E-02, 2.5000E-02, 7.7700E-03, 
            2.9300E-03, 2.8000E-03, 2.2500E-03, 1.4700E-03, 8.5400E-04, 
            2.7000E-04, 1.4000E-04, 9.3000E-05, 1.9000E-05, 3.5000E-06, 
            2.0000E-07, 3.7000E-09} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.5500E+00, 1.5100E+00, 1.4000E+00, 1.2400E+00, 
            1.0400E+00, 6.5400E-01, 3.5400E-01, 1.7400E-01, 8.8500E-02, 
            5.6200E-02, 4.7800E-02, 4.6500E-02, 4.0000E-02, 2.9100E-02, 
            1.8800E-02, 1.1300E-02, 6.6600E-03, 2.9900E-03, 2.4800E-03, 
            1.7200E-03, 6.7700E-04, 2.7500E-04, 2.1700E-04, 2.1300E-04, 
            1.4000E-04, 2.1000E-05, 1.7000E-05, 3.4000E-06, 6.7000E-07, 
            5.1000E-07, 1.3000E-07} );
  }
};

//! The default Compton profile generator implementation for A=75
template<>
struct DefaultComptonProfileGeneratorImpl<75u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 22 );

    subshell_half_profiles[0] = 
      std::vector<double>( {9.9700E-03, 9.9700E-03, 9.9700E-03, 9.9700E-03, 
            9.9700E-03, 9.9700E-03, 9.9700E-03, 9.9700E-03, 9.9700E-03, 
            9.9700E-03, 9.9700E-03, 9.9700E-03, 9.9600E-03, 9.9600E-03, 
            9.9600E-03, 9.9600E-03, 9.9500E-03, 9.9400E-03, 9.9300E-03, 
            9.9000E-03, 9.8600E-03, 9.8100E-03, 9.7500E-03, 9.6800E-03, 
            9.5000E-03, 9.0000E-03, 8.3000E-03, 6.8000E-03, 5.3000E-03, 
            2.9000E-03, 8.0000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.5400E-02, 3.5400E-02, 3.5400E-02, 3.5400E-02, 
            3.5400E-02, 3.5400E-02, 3.5400E-02, 3.5400E-02, 3.5400E-02, 
            3.5300E-02, 3.5300E-02, 3.5300E-02, 3.5200E-02, 3.5100E-02, 
            3.5000E-02, 3.4800E-02, 3.4700E-02, 3.4400E-02, 3.3800E-02, 
            3.2600E-02, 3.1100E-02, 2.9400E-02, 2.7600E-02, 2.5500E-02, 
            2.1000E-02, 1.2000E-02, 5.5000E-03, 1.2000E-03, 8.7000E-04, 
            6.8000E-04, 1.8000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.7300E-02, 1.7300E-02, 1.7300E-02, 1.7300E-02, 
            1.7300E-02, 1.7300E-02, 1.7300E-02, 1.7300E-02, 1.7300E-02, 
            1.7300E-02, 1.7300E-02, 1.7300E-02, 1.7300E-02, 1.7300E-02, 
            1.7300E-02, 1.7300E-02, 1.7300E-02, 1.7300E-02, 1.7300E-02, 
            1.7300E-02, 1.7300E-02, 1.7200E-02, 1.7100E-02, 1.7000E-02, 
            1.7000E-02, 1.5000E-02, 1.2000E-02, 6.6000E-03, 3.1000E-03, 
            6.8000E-04, 5.8000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.9200E-02, 1.9200E-02, 1.9200E-02, 1.9200E-02, 
            1.9200E-02, 1.9200E-02, 1.9200E-02, 1.9200E-02, 1.9200E-02, 
            1.9200E-02, 1.9200E-02, 1.9200E-02, 1.9200E-02, 1.9200E-02, 
            1.9200E-02, 1.9200E-02, 1.9200E-02, 1.9200E-02, 1.9200E-02, 
            1.9200E-02, 1.9100E-02, 1.9100E-02, 1.8900E-02, 1.8800E-02, 
            1.8000E-02, 1.6000E-02, 1.2000E-02, 5.8000E-03, 2.4000E-03, 
            4.1000E-04, 2.2000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {7.8100E-02, 7.8100E-02, 7.8100E-02, 7.8000E-02, 
            7.8000E-02, 7.7900E-02, 7.7700E-02, 7.7500E-02, 7.7300E-02, 
            7.7000E-02, 7.6600E-02, 7.5800E-02, 7.4800E-02, 7.3700E-02, 
            7.2400E-02, 7.0900E-02, 6.9400E-02, 6.5800E-02, 5.9900E-02, 
            4.8900E-02, 3.7900E-02, 2.8000E-02, 2.0100E-02, 1.4200E-02, 
            7.9000E-03, 5.9000E-03, 4.3000E-03, 7.8000E-04, 2.0000E-04, 
            1.6000E-04, 4.4000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {4.5800E-02, 4.5800E-02, 4.5800E-02, 4.5800E-02, 
            4.5800E-02, 4.5800E-02, 4.5800E-02, 4.5800E-02, 4.5800E-02, 
            4.5800E-02, 4.5800E-02, 4.5800E-02, 4.5800E-02, 4.5800E-02, 
            4.5800E-02, 4.5700E-02, 4.5700E-02, 4.5500E-02, 4.5100E-02, 
            4.3900E-02, 4.1700E-02, 3.8500E-02, 3.4400E-02, 2.9900E-02, 
            2.1000E-02, 5.4000E-03, 1.9000E-03, 1.6000E-03, 9.1000E-04, 
            2.0000E-04, 1.6000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {4.9100E-02, 4.9100E-02, 4.9100E-02, 4.9100E-02, 
            4.9100E-02, 4.9100E-02, 4.9100E-02, 4.9100E-02, 4.9100E-02, 
            4.9100E-02, 4.9100E-02, 4.9000E-02, 4.9000E-02, 4.9000E-02, 
            4.9000E-02, 4.8900E-02, 4.8800E-02, 4.8600E-02, 4.8100E-02, 
            4.6400E-02, 4.3500E-02, 3.9400E-02, 3.4400E-02, 2.9000E-02, 
            1.9000E-02, 4.3000E-03, 2.0000E-03, 1.6000E-03, 7.9000E-04, 
            1.3000E-04, 6.6000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {3.1800E-02, 3.1800E-02, 3.1800E-02, 3.1800E-02, 
            3.1800E-02, 3.1800E-02, 3.1800E-02, 3.1800E-02, 3.1800E-02, 
            3.1800E-02, 3.1800E-02, 3.1800E-02, 3.1800E-02, 3.1800E-02, 
            3.1800E-02, 3.1800E-02, 3.1800E-02, 3.1800E-02, 3.1800E-02, 
            3.1700E-02, 3.1500E-02, 3.1000E-02, 3.0200E-02, 2.9100E-02, 
            2.6000E-02, 1.5000E-02, 6.9000E-03, 1.2000E-03, 2.3000E-04, 
            1.4000E-05, 2.7000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.2500E-02, 3.2500E-02, 3.2500E-02, 3.2500E-02, 
            3.2500E-02, 3.2500E-02, 3.2500E-02, 3.2500E-02, 3.2500E-02, 
            3.2500E-02, 3.2500E-02, 3.2500E-02, 3.2500E-02, 3.2500E-02, 
            3.2500E-02, 3.2500E-02, 3.2500E-02, 3.2500E-02, 3.2500E-02, 
            3.2400E-02, 3.2200E-02, 3.1600E-02, 3.0800E-02, 2.9500E-02, 
            2.6000E-02, 1.5000E-02, 6.5000E-03, 1.1000E-03, 1.9000E-04, 
            1.1000E-05, 1.6000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.6300E-01, 1.6300E-01, 1.6300E-01, 1.6300E-01, 
            1.6200E-01, 1.6100E-01, 1.6000E-01, 1.5800E-01, 1.5500E-01, 
            1.5200E-01, 1.4900E-01, 1.4200E-01, 1.3300E-01, 1.2400E-01, 
            1.1400E-01, 1.0400E-01, 9.3900E-02, 7.4300E-02, 4.9500E-02, 
            2.4700E-02, 1.6500E-02, 1.5500E-02, 1.5100E-02, 1.3200E-02, 
            7.3000E-03, 1.5000E-03, 1.3000E-03, 2.7000E-04, 5.3000E-05, 
            4.0000E-05, 1.1000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.0300E-01, 1.0300E-01, 1.0300E-01, 1.0300E-01, 
            1.0300E-01, 1.0300E-01, 1.0300E-01, 1.0300E-01, 1.0300E-01, 
            1.0300E-01, 1.0300E-01, 1.0300E-01, 1.0200E-01, 1.0100E-01, 
            9.9900E-02, 9.8200E-02, 9.6000E-02, 9.0300E-02, 7.8500E-02, 
            5.4100E-02, 3.1900E-02, 1.7100E-02, 9.5600E-03, 6.8600E-03, 
            6.3000E-03, 2.9000E-03, 6.6000E-04, 3.5000E-04, 2.2000E-04, 
            5.1000E-05, 4.0000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 
            1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 1.1000E-01, 
            1.1000E-01, 1.1000E-01, 1.0900E-01, 1.0900E-01, 1.0800E-01, 
            1.0600E-01, 1.0400E-01, 1.0100E-01, 9.3400E-02, 7.8700E-02, 
            5.0600E-02, 2.7600E-02, 1.4100E-02, 8.4100E-03, 6.9300E-03, 
            6.7000E-03, 2.3000E-03, 5.3000E-04, 3.8000E-04, 2.0000E-04, 
            3.3000E-05, 1.6000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {8.4200E-02, 8.4200E-02, 8.4200E-02, 8.4200E-02, 
            8.4200E-02, 8.4200E-02, 8.4200E-02, 8.4200E-02, 8.4200E-02, 
            8.4200E-02, 8.4200E-02, 8.4200E-02, 8.4100E-02, 8.4000E-02, 
            8.3800E-02, 8.3500E-02, 8.3100E-02, 8.1500E-02, 7.7100E-02, 
            6.4000E-02, 4.7000E-02, 3.0800E-02, 1.8500E-02, 1.0500E-02, 
            3.8000E-03, 2.5000E-03, 1.6000E-03, 3.3000E-04, 6.3000E-05, 
            3.7000E-06, 6.9000E-08} );

    subshell_half_profiles[13] = 
      std::vector<double>( {8.6200E-02, 8.6200E-02, 8.6200E-02, 8.6200E-02, 
            8.6200E-02, 8.6200E-02, 8.6200E-02, 8.6200E-02, 8.6200E-02, 
            8.6200E-02, 8.6200E-02, 8.6200E-02, 8.6100E-02, 8.6000E-02, 
            8.5800E-02, 8.5400E-02, 8.4900E-02, 8.3100E-02, 7.8200E-02, 
            6.4000E-02, 4.6100E-02, 2.9600E-02, 1.7400E-02, 9.6900E-03, 
            3.6000E-03, 2.5000E-03, 1.5000E-03, 2.9000E-04, 5.2000E-05, 
            2.8000E-06, 3.9000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {7.7700E-02, 7.7700E-02, 7.7700E-02, 7.7700E-02, 
            7.7700E-02, 7.7700E-02, 7.7700E-02, 7.7700E-02, 7.7700E-02, 
            7.7700E-02, 7.7700E-02, 7.7600E-02, 7.7600E-02, 7.7500E-02, 
            7.7300E-02, 7.7000E-02, 7.6500E-02, 7.5000E-02, 7.0900E-02, 
            6.0500E-02, 4.8100E-02, 3.6400E-02, 2.6700E-02, 1.9100E-02, 
            9.5000E-03, 1.6000E-03, 2.9000E-04, 1.5000E-05, 1.3000E-06, 
            2.7000E-08, 1.7000E-10} );

    subshell_half_profiles[15] = 
      std::vector<double>( {7.8200E-02, 7.8200E-02, 7.8200E-02, 7.8200E-02, 
            7.8200E-02, 7.8200E-02, 7.8200E-02, 7.8200E-02, 7.8200E-02, 
            7.8200E-02, 7.8200E-02, 7.8200E-02, 7.8200E-02, 7.8100E-02, 
            7.7900E-02, 7.7600E-02, 7.7100E-02, 7.5600E-02, 7.1500E-02, 
            6.0800E-02, 4.8100E-02, 3.6200E-02, 2.6400E-02, 1.8800E-02, 
            9.2000E-03, 1.5000E-03, 2.7000E-04, 1.3000E-05, 1.1000E-06, 
            2.2000E-08, 1.1000E-10} );

    subshell_half_profiles[16] = 
      std::vector<double>( {4.1200E-01, 4.1100E-01, 4.0800E-01, 4.0400E-01, 
            3.9800E-01, 3.8200E-01, 3.6000E-01, 3.3500E-01, 3.0600E-01, 
            2.7500E-01, 2.4400E-01, 1.8400E-01, 1.3200E-01, 9.2100E-02, 
            6.3700E-02, 4.5800E-02, 3.5900E-02, 2.9700E-02, 2.8900E-02, 
            1.8500E-02, 7.5400E-03, 3.4100E-03, 2.8000E-03, 2.7500E-03, 
            1.8000E-03, 2.8000E-04, 2.3000E-04, 4.9000E-05, 9.2000E-06, 
            6.9000E-06, 1.9000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {2.7900E-01, 2.7900E-01, 2.7900E-01, 2.7900E-01, 
            2.7900E-01, 2.7900E-01, 2.7700E-01, 2.7400E-01, 2.7000E-01, 
            2.6300E-01, 2.5500E-01, 2.3100E-01, 2.0000E-01, 1.6600E-01, 
            1.3200E-01, 1.0100E-01, 7.5100E-02, 3.8400E-02, 1.5500E-02, 
            1.1000E-02, 9.4900E-03, 5.8400E-03, 2.9100E-03, 1.4600E-03, 
            8.8000E-04, 4.9000E-04, 1.1000E-04, 4.9000E-05, 3.2000E-05, 
            7.4000E-06, 5.7000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {3.0000E-01, 3.0000E-01, 3.0000E-01, 3.0000E-01, 
            3.0000E-01, 2.9900E-01, 2.9700E-01, 2.9300E-01, 2.8700E-01, 
            2.7900E-01, 2.6700E-01, 2.3700E-01, 1.9900E-01, 1.6000E-01, 
            1.2200E-01, 8.9500E-02, 6.3400E-02, 3.0400E-02, 1.3600E-02, 
            1.1600E-02, 8.7200E-03, 4.6400E-03, 2.1300E-03, 1.1600E-03, 
            9.3000E-04, 3.9000E-04, 8.1000E-05, 5.3000E-05, 2.8000E-05, 
            4.7000E-06, 2.3000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {3.2700E-01, 3.2700E-01, 3.2700E-01, 3.2700E-01, 
            3.2700E-01, 3.2700E-01, 3.2500E-01, 3.2100E-01, 3.1300E-01, 
            3.0200E-01, 2.8600E-01, 2.4600E-01, 2.0100E-01, 1.5700E-01, 
            1.1900E-01, 8.7800E-02, 6.3200E-02, 3.1000E-02, 1.0100E-02, 
            3.2900E-03, 3.0900E-03, 2.5900E-03, 1.7600E-03, 1.0500E-03, 
            3.3000E-04, 1.6000E-04, 1.1000E-04, 2.3000E-05, 4.4000E-06, 
            2.6000E-07, 4.8000E-09} );

    subshell_half_profiles[20] = 
      std::vector<double>( {3.4600E-01, 3.4600E-01, 3.4600E-01, 3.4600E-01, 
            3.4600E-01, 3.4600E-01, 3.4300E-01, 3.3700E-01, 3.2700E-01, 
            3.1200E-01, 2.9200E-01, 2.4500E-01, 1.9500E-01, 1.4900E-01, 
            1.1000E-01, 7.9500E-02, 5.6100E-02, 2.6600E-02, 8.3800E-03, 
            3.0800E-03, 2.9400E-03, 2.3800E-03, 1.5600E-03, 9.0500E-04, 
            2.9000E-04, 1.5000E-04, 9.9000E-05, 1.9000E-05, 3.4000E-06, 
            1.8000E-07, 2.6000E-09} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.4900E+00, 1.4600E+00, 1.3600E+00, 1.2100E+00, 
            1.0300E+00, 6.6600E-01, 3.7400E-01, 1.9100E-01, 9.7800E-02, 
            5.9300E-02, 4.7600E-02, 4.5500E-02, 4.0900E-02, 3.1200E-02, 
            2.1100E-02, 1.3200E-02, 7.9200E-03, 3.3700E-03, 2.5300E-03, 
            1.9100E-03, 8.0000E-04, 3.1400E-04, 2.2800E-04, 2.2400E-04, 
            1.5000E-04, 2.2000E-05, 1.9000E-05, 4.0000E-06, 7.4000E-07, 
            5.5000E-07, 1.5000E-07} );
  }
};

//! The default Compton profile generator implementation for A=76
template<>
struct DefaultComptonProfileGeneratorImpl<76u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 22 );

    subshell_half_profiles[0] = 
      std::vector<double>( {9.8000E-03, 9.8000E-03, 9.8000E-03, 9.8000E-03, 
            9.8000E-03, 9.7900E-03, 9.7900E-03, 9.7900E-03, 9.7900E-03, 
            9.7900E-03, 9.7900E-03, 9.7900E-03, 9.7900E-03, 9.7900E-03, 
            9.7800E-03, 9.7800E-03, 9.7800E-03, 9.7700E-03, 9.7600E-03, 
            9.7300E-03, 9.6900E-03, 9.6400E-03, 9.5800E-03, 9.5200E-03, 
            9.4000E-03, 8.9000E-03, 8.2000E-03, 6.8000E-03, 5.3000E-03, 
            2.9000E-03, 8.3000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.4800E-02, 3.4800E-02, 3.4800E-02, 3.4800E-02, 
            3.4800E-02, 3.4800E-02, 3.4800E-02, 3.4800E-02, 3.4800E-02, 
            3.4700E-02, 3.4700E-02, 3.4600E-02, 3.4600E-02, 3.4500E-02, 
            3.4400E-02, 3.4300E-02, 3.4100E-02, 3.3800E-02, 3.3300E-02, 
            3.2100E-02, 3.0700E-02, 2.9100E-02, 2.7300E-02, 2.5400E-02, 
            2.1000E-02, 1.2000E-02, 5.7000E-03, 1.3000E-03, 8.6000E-04, 
            6.9000E-04, 1.9000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.7000E-02, 1.7000E-02, 1.7000E-02, 1.7000E-02, 
            1.7000E-02, 1.7000E-02, 1.7000E-02, 1.7000E-02, 1.7000E-02, 
            1.7000E-02, 1.7000E-02, 1.7000E-02, 1.7000E-02, 1.7000E-02, 
            1.7000E-02, 1.7000E-02, 1.7000E-02, 1.7000E-02, 1.7000E-02, 
            1.7000E-02, 1.7000E-02, 1.6900E-02, 1.6800E-02, 1.6700E-02, 
            1.6000E-02, 1.5000E-02, 1.2000E-02, 6.7000E-03, 3.2000E-03, 
            7.2000E-04, 6.3000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.8900E-02, 1.8900E-02, 1.8900E-02, 1.8900E-02, 
            1.8900E-02, 1.8900E-02, 1.8900E-02, 1.8900E-02, 1.8900E-02, 
            1.8900E-02, 1.8900E-02, 1.8900E-02, 1.8900E-02, 1.8900E-02, 
            1.8900E-02, 1.8900E-02, 1.8900E-02, 1.8900E-02, 1.8900E-02, 
            1.8900E-02, 1.8900E-02, 1.8800E-02, 1.8700E-02, 1.8500E-02, 
            1.8000E-02, 1.6000E-02, 1.2000E-02, 5.9000E-03, 2.5000E-03, 
            4.3000E-04, 2.4000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {7.6700E-02, 7.6700E-02, 7.6700E-02, 7.6600E-02, 
            7.6600E-02, 7.6500E-02, 7.6300E-02, 7.6100E-02, 7.5900E-02, 
            7.5600E-02, 7.5300E-02, 7.4500E-02, 7.3600E-02, 7.2500E-02, 
            7.1300E-02, 6.9900E-02, 6.8400E-02, 6.5000E-02, 5.9300E-02, 
            4.8800E-02, 3.8100E-02, 2.8500E-02, 2.0600E-02, 1.4600E-02, 
            8.0000E-03, 5.8000E-03, 4.4000E-03, 8.5000E-04, 2.1000E-04, 
            1.6000E-04, 4.7000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {4.5000E-02, 4.5000E-02, 4.5000E-02, 4.5000E-02, 
            4.5000E-02, 4.5000E-02, 4.5000E-02, 4.5000E-02, 4.5000E-02, 
            4.5000E-02, 4.5000E-02, 4.5000E-02, 4.5000E-02, 4.5000E-02, 
            4.4900E-02, 4.4900E-02, 4.4900E-02, 4.4700E-02, 4.4400E-02, 
            4.3200E-02, 4.1100E-02, 3.8100E-02, 3.4300E-02, 3.0000E-02, 
            2.1000E-02, 5.8000E-03, 1.9000E-03, 1.6000E-03, 9.4000E-04, 
            2.2000E-04, 1.8000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {4.8200E-02, 4.8200E-02, 4.8200E-02, 4.8200E-02, 
            4.8200E-02, 4.8200E-02, 4.8200E-02, 4.8200E-02, 4.8200E-02, 
            4.8200E-02, 4.8200E-02, 4.8200E-02, 4.8200E-02, 4.8200E-02, 
            4.8200E-02, 4.8100E-02, 4.8100E-02, 4.7900E-02, 4.7400E-02, 
            4.5800E-02, 4.3000E-02, 3.9200E-02, 3.4400E-02, 2.9300E-02, 
            1.9000E-02, 4.6000E-03, 2.0000E-03, 1.7000E-03, 8.2000E-04, 
            1.4000E-04, 7.2000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {3.1200E-02, 3.1200E-02, 3.1200E-02, 3.1200E-02, 
            3.1200E-02, 3.1200E-02, 3.1200E-02, 3.1200E-02, 3.1200E-02, 
            3.1200E-02, 3.1200E-02, 3.1200E-02, 3.1200E-02, 3.1200E-02, 
            3.1200E-02, 3.1200E-02, 3.1200E-02, 3.1200E-02, 3.1200E-02, 
            3.1200E-02, 3.1000E-02, 3.0500E-02, 2.9800E-02, 2.8800E-02, 
            2.6000E-02, 1.5000E-02, 7.2000E-03, 1.3000E-03, 2.5000E-04, 
            1.6000E-05, 3.1000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.2000E-02, 3.2000E-02, 3.2000E-02, 3.2000E-02, 
            3.2000E-02, 3.2000E-02, 3.2000E-02, 3.2000E-02, 3.2000E-02, 
            3.2000E-02, 3.2000E-02, 3.2000E-02, 3.2000E-02, 3.2000E-02, 
            3.2000E-02, 3.2000E-02, 3.2000E-02, 3.2000E-02, 3.1900E-02, 
            3.1900E-02, 3.1600E-02, 3.1200E-02, 3.0400E-02, 2.9200E-02, 
            2.6000E-02, 1.5000E-02, 6.8000E-03, 1.2000E-03, 2.1000E-04, 
            1.2000E-05, 1.8000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.6000E-01, 1.6000E-01, 1.6000E-01, 1.5900E-01, 
            1.5900E-01, 1.5800E-01, 1.5600E-01, 1.5400E-01, 1.5200E-01, 
            1.5000E-01, 1.4700E-01, 1.4000E-01, 1.3200E-01, 1.2300E-01, 
            1.1300E-01, 1.0400E-01, 9.3900E-02, 7.5000E-02, 5.0600E-02, 
            2.5500E-02, 1.6600E-02, 1.5300E-02, 1.5000E-02, 1.3400E-02, 
            7.7000E-03, 1.5000E-03, 1.3000E-03, 2.9000E-04, 5.5000E-05, 
            4.1000E-05, 1.2000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 
            1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 
            1.0100E-01, 1.0100E-01, 1.0000E-01, 9.9800E-02, 9.9000E-02, 
            9.7900E-02, 9.6400E-02, 9.4400E-02, 8.9200E-02, 7.8200E-02, 
            5.5000E-02, 3.3200E-02, 1.8100E-02, 1.0100E-02, 6.9900E-03, 
            6.2000E-03, 3.1000E-03, 7.2000E-04, 3.5000E-04, 2.3000E-04, 
            5.5000E-05, 4.4000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 
            1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 1.0800E-01, 
            1.0800E-01, 1.0800E-01, 1.0700E-01, 1.0700E-01, 1.0500E-01, 
            1.0400E-01, 1.0200E-01, 9.9300E-02, 9.2400E-02, 7.8600E-02, 
            5.1700E-02, 2.8800E-02, 1.4900E-02, 8.7200E-03, 6.9300E-03, 
            6.6000E-03, 2.5000E-03, 5.6000E-04, 3.9000E-04, 2.1000E-04, 
            3.6000E-05, 1.8000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {8.2200E-02, 8.2200E-02, 8.2200E-02, 8.2200E-02, 
            8.2200E-02, 8.2200E-02, 8.2200E-02, 8.2200E-02, 8.2200E-02, 
            8.2200E-02, 8.2200E-02, 8.2200E-02, 8.2100E-02, 8.2100E-02, 
            8.1900E-02, 8.1600E-02, 8.1200E-02, 7.9900E-02, 7.6000E-02, 
            6.4000E-02, 4.7900E-02, 3.2100E-02, 1.9700E-02, 1.1400E-02, 
            4.0000E-03, 2.5000E-03, 1.7000E-03, 3.5000E-04, 7.0000E-05, 
            4.2000E-06, 8.0000E-08} );

    subshell_half_profiles[13] = 
      std::vector<double>( {8.4200E-02, 8.4200E-02, 8.4200E-02, 8.4200E-02, 
            8.4200E-02, 8.4200E-02, 8.4200E-02, 8.4200E-02, 8.4200E-02, 
            8.4200E-02, 8.4100E-02, 8.4100E-02, 8.4100E-02, 8.4000E-02, 
            8.3800E-02, 8.3500E-02, 8.3000E-02, 8.1500E-02, 7.7100E-02, 
            6.4100E-02, 4.7100E-02, 3.0900E-02, 1.8500E-02, 1.0500E-02, 
            3.8000E-03, 2.5000E-03, 1.6000E-03, 3.2000E-04, 5.8000E-05, 
            3.1000E-06, 4.5000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {7.4400E-02, 7.4400E-02, 7.4400E-02, 7.4400E-02, 
            7.4400E-02, 7.4400E-02, 7.4400E-02, 7.4400E-02, 7.4400E-02, 
            7.4400E-02, 7.4400E-02, 7.4400E-02, 7.4400E-02, 7.4300E-02, 
            7.4200E-02, 7.4000E-02, 7.3700E-02, 7.2500E-02, 6.9300E-02, 
            6.0300E-02, 4.9000E-02, 3.7700E-02, 2.8100E-02, 2.0400E-02, 
            1.0000E-02, 1.8000E-03, 3.4000E-04, 1.8000E-05, 1.5000E-06, 
            3.4000E-08, 2.1000E-10} );

    subshell_half_profiles[15] = 
      std::vector<double>( {7.5100E-02, 7.5100E-02, 7.5100E-02, 7.5100E-02, 
            7.5100E-02, 7.5100E-02, 7.5100E-02, 7.5100E-02, 7.5100E-02, 
            7.5100E-02, 7.5100E-02, 7.5100E-02, 7.5100E-02, 7.5000E-02, 
            7.4900E-02, 7.4700E-02, 7.4300E-02, 7.3200E-02, 6.9900E-02, 
            6.0600E-02, 4.9000E-02, 3.7500E-02, 2.7700E-02, 2.0000E-02, 
            1.0000E-02, 1.7000E-03, 3.1000E-04, 1.6000E-05, 1.3000E-06, 
            2.7000E-08, 1.4000E-10} );

    subshell_half_profiles[16] = 
      std::vector<double>( {3.9700E-01, 3.9700E-01, 3.9400E-01, 3.9000E-01, 
            3.8500E-01, 3.7000E-01, 3.5100E-01, 3.2700E-01, 3.0100E-01, 
            2.7200E-01, 2.4300E-01, 1.8600E-01, 1.3600E-01, 9.6400E-02, 
            6.7500E-02, 4.8500E-02, 3.7400E-02, 2.9700E-02, 2.8900E-02, 
            1.9700E-02, 8.4600E-03, 3.7000E-03, 2.8500E-03, 2.8100E-03, 
            1.9000E-03, 2.9000E-04, 2.4000E-04, 5.6000E-05, 9.9000E-06, 
            7.1000E-06, 2.1000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {2.6800E-01, 2.6800E-01, 2.6800E-01, 2.6800E-01, 
            2.6800E-01, 2.6800E-01, 2.6700E-01, 2.6400E-01, 2.6100E-01, 
            2.5500E-01, 2.4700E-01, 2.2700E-01, 1.9900E-01, 1.6800E-01, 
            1.3700E-01, 1.0700E-01, 8.0700E-02, 4.2800E-02, 1.7100E-02, 
            1.1100E-02, 9.9700E-03, 6.4500E-03, 3.3400E-03, 1.6600E-03, 
            9.0000E-04, 5.5000E-04, 1.3000E-04, 5.1000E-05, 3.5000E-05, 
            8.3000E-06, 6.6000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.9000E-01, 2.9000E-01, 2.9000E-01, 2.9000E-01, 
            2.9000E-01, 2.8900E-01, 2.8700E-01, 2.8400E-01, 2.7900E-01, 
            2.7100E-01, 2.6100E-01, 2.3400E-01, 2.0000E-01, 1.6300E-01, 
            1.2700E-01, 9.4800E-02, 6.8500E-02, 3.3800E-02, 1.4500E-02, 
            1.1700E-02, 9.2800E-03, 5.1800E-03, 2.4200E-03, 1.2700E-03, 
            9.5000E-04, 4.3000E-04, 9.0000E-05, 5.6000E-05, 3.0000E-05, 
            5.2000E-06, 2.6000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {3.0700E-01, 3.0700E-01, 3.0700E-01, 3.0700E-01, 
            3.0700E-01, 3.0700E-01, 3.0600E-01, 3.0300E-01, 2.9800E-01, 
            2.8900E-01, 2.7700E-01, 2.4400E-01, 2.0500E-01, 1.6500E-01, 
            1.2800E-01, 9.7300E-02, 7.1900E-02, 3.7000E-02, 1.2600E-02, 
            3.6800E-03, 3.3200E-03, 2.9000E-03, 2.0500E-03, 1.2600E-03, 
            4.1000E-04, 1.7000E-04, 1.2000E-04, 2.7000E-05, 5.4000E-06, 
            3.3000E-07, 6.1000E-09} );

    subshell_half_profiles[20] = 
      std::vector<double>( {3.2400E-01, 3.2400E-01, 3.2400E-01, 3.2400E-01, 
            3.2400E-01, 3.2400E-01, 3.2200E-01, 3.1800E-01, 3.1100E-01, 
            2.9900E-01, 2.8400E-01, 2.4500E-01, 2.0100E-01, 1.5800E-01, 
            1.2000E-01, 8.9400E-02, 6.4700E-02, 3.2200E-02, 1.0600E-02, 
            3.4100E-03, 3.1900E-03, 2.6900E-03, 1.8400E-03, 1.0900E-03, 
            3.5000E-04, 1.7000E-04, 1.1000E-04, 2.3000E-05, 4.2000E-06, 
            2.3000E-07, 3.3000E-09} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.4400E+00, 1.4100E+00, 1.3200E+00, 1.1900E+00, 
            1.0200E+00, 6.7600E-01, 3.9200E-01, 2.0700E-01, 1.0700E-01, 
            6.2900E-02, 4.7700E-02, 4.4300E-02, 4.1200E-02, 3.2800E-02, 
            2.3100E-02, 1.4900E-02, 9.2100E-03, 3.8000E-03, 2.5500E-03, 
            2.0600E-03, 9.2900E-04, 3.5900E-04, 2.3800E-04, 2.3300E-04, 
            1.7000E-04, 2.4000E-05, 2.0000E-05, 4.7000E-06, 8.1000E-07, 
            5.8000E-07, 1.7000E-07} );
  }
};

//! The default Compton profile generator implementation for A=77
template<>
struct DefaultComptonProfileGeneratorImpl<77u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 22 );

    subshell_half_profiles[0] = 
      std::vector<double>( {9.6200E-03, 9.6200E-03, 9.6200E-03, 9.6200E-03, 
            9.6200E-03, 9.6200E-03, 9.6200E-03, 9.6200E-03, 9.6200E-03, 
            9.6200E-03, 9.6200E-03, 9.6200E-03, 9.6200E-03, 9.6200E-03, 
            9.6100E-03, 9.6100E-03, 9.6100E-03, 9.6000E-03, 9.5900E-03, 
            9.5600E-03, 9.5200E-03, 9.4800E-03, 9.4200E-03, 9.3600E-03, 
            9.2000E-03, 8.7000E-03, 8.1000E-03, 6.7000E-03, 5.3000E-03, 
            2.9000E-03, 8.6000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.4200E-02, 3.4200E-02, 3.4200E-02, 3.4200E-02, 
            3.4200E-02, 3.4200E-02, 3.4200E-02, 3.4200E-02, 3.4200E-02, 
            3.4100E-02, 3.4100E-02, 3.4100E-02, 3.4000E-02, 3.3900E-02, 
            3.3800E-02, 3.3700E-02, 3.3600E-02, 3.3300E-02, 3.2800E-02, 
            3.1700E-02, 3.0300E-02, 2.8800E-02, 2.7000E-02, 2.5200E-02, 
            2.1000E-02, 1.2000E-02, 5.9000E-03, 1.3000E-03, 8.4000E-04, 
            6.9000E-04, 2.0000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 
            1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 
            1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 
            1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 
            1.6700E-02, 1.6700E-02, 1.6600E-02, 1.6500E-02, 1.6400E-02, 
            1.6000E-02, 1.5000E-02, 1.2000E-02, 6.8000E-03, 3.3000E-03, 
            7.7000E-04, 6.9000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8700E-02, 
            1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8700E-02, 
            1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8700E-02, 
            1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8700E-02, 1.8700E-02, 
            1.8600E-02, 1.8600E-02, 1.8500E-02, 1.8400E-02, 1.8300E-02, 
            1.8000E-02, 1.6000E-02, 1.2000E-02, 6.1000E-03, 2.6000E-03, 
            4.6000E-04, 2.6000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {7.5300E-02, 7.5300E-02, 7.5300E-02, 7.5300E-02, 
            7.5200E-02, 7.5100E-02, 7.5000E-02, 7.4800E-02, 7.4600E-02, 
            7.4300E-02, 7.4000E-02, 7.3200E-02, 7.2400E-02, 7.1300E-02, 
            7.0200E-02, 6.8800E-02, 6.7400E-02, 6.4200E-02, 5.8800E-02, 
            4.8700E-02, 3.8300E-02, 2.8900E-02, 2.1000E-02, 1.5100E-02, 
            8.2000E-03, 5.7000E-03, 4.5000E-03, 9.2000E-04, 2.1000E-04, 
            1.6000E-04, 4.9000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {4.4200E-02, 4.4200E-02, 4.4200E-02, 4.4200E-02, 
            4.4200E-02, 4.4200E-02, 4.4200E-02, 4.4200E-02, 4.4200E-02, 
            4.4200E-02, 4.4200E-02, 4.4200E-02, 4.4200E-02, 4.4100E-02, 
            4.4100E-02, 4.4100E-02, 4.4000E-02, 4.3900E-02, 4.3600E-02, 
            4.2500E-02, 4.0600E-02, 3.7800E-02, 3.4200E-02, 3.0100E-02, 
            2.1000E-02, 6.1000E-03, 2.0000E-03, 1.6000E-03, 9.7000E-04, 
            2.3000E-04, 2.0000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {4.7500E-02, 4.7500E-02, 4.7500E-02, 4.7500E-02, 
            4.7500E-02, 4.7500E-02, 4.7500E-02, 4.7500E-02, 4.7500E-02, 
            4.7500E-02, 4.7500E-02, 4.7400E-02, 4.7400E-02, 4.7400E-02, 
            4.7400E-02, 4.7300E-02, 4.7300E-02, 4.7100E-02, 4.6600E-02, 
            4.5100E-02, 4.2600E-02, 3.8900E-02, 3.4400E-02, 2.9400E-02, 
            2.0000E-02, 4.8000E-03, 2.0000E-03, 1.7000E-03, 8.5000E-04, 
            1.5000E-04, 7.9000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {3.0700E-02, 3.0700E-02, 3.0700E-02, 3.0700E-02, 
            3.0700E-02, 3.0700E-02, 3.0700E-02, 3.0700E-02, 3.0700E-02, 
            3.0700E-02, 3.0700E-02, 3.0700E-02, 3.0700E-02, 3.0700E-02, 
            3.0700E-02, 3.0700E-02, 3.0700E-02, 3.0700E-02, 3.0700E-02, 
            3.0600E-02, 3.0500E-02, 3.0100E-02, 2.9400E-02, 2.8500E-02, 
            2.6000E-02, 1.5000E-02, 7.4000E-03, 1.4000E-03, 2.8000E-04, 
            1.8000E-05, 3.5000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.1400E-02, 3.1400E-02, 3.1400E-02, 3.1400E-02, 
            3.1400E-02, 3.1400E-02, 3.1400E-02, 3.1400E-02, 3.1400E-02, 
            3.1400E-02, 3.1400E-02, 3.1400E-02, 3.1400E-02, 3.1400E-02, 
            3.1400E-02, 3.1400E-02, 3.1400E-02, 3.1400E-02, 3.1400E-02, 
            3.1400E-02, 3.1200E-02, 3.0700E-02, 3.0000E-02, 2.8900E-02, 
            2.6000E-02, 1.5000E-02, 7.0000E-03, 1.2000E-03, 2.3000E-04, 
            1.3000E-05, 2.0000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.5600E-01, 1.5600E-01, 1.5600E-01, 1.5600E-01, 
            1.5600E-01, 1.5500E-01, 1.5300E-01, 1.5100E-01, 1.4900E-01, 
            1.4700E-01, 1.4400E-01, 1.3700E-01, 1.3000E-01, 1.2100E-01, 
            1.1200E-01, 1.0300E-01, 9.3800E-02, 7.5600E-02, 5.1700E-02, 
            2.6300E-02, 1.6700E-02, 1.5100E-02, 1.4900E-02, 1.3600E-02, 
            8.1000E-03, 1.5000E-03, 1.3000E-03, 3.2000E-04, 5.8000E-05, 
            4.1000E-05, 1.2000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {9.8600E-02, 9.8600E-02, 9.8600E-02, 9.8600E-02, 
            9.8600E-02, 9.8600E-02, 9.8600E-02, 9.8500E-02, 9.8500E-02, 
            9.8500E-02, 9.8400E-02, 9.8100E-02, 9.7700E-02, 9.7000E-02, 
            9.5900E-02, 9.4600E-02, 9.2800E-02, 8.8000E-02, 7.7800E-02, 
            5.5800E-02, 3.4500E-02, 1.9200E-02, 1.0700E-02, 7.1700E-03, 
            6.1000E-03, 3.3000E-03, 7.9000E-04, 3.5000E-04, 2.4000E-04, 
            5.9000E-05, 4.9000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.0600E-01, 1.0600E-01, 1.0600E-01, 1.0600E-01, 
            1.0600E-01, 1.0600E-01, 1.0600E-01, 1.0600E-01, 1.0600E-01, 
            1.0600E-01, 1.0500E-01, 1.0500E-01, 1.0400E-01, 1.0300E-01, 
            1.0200E-01, 1.0000E-01, 9.7800E-02, 9.1500E-02, 7.8500E-02, 
            5.2700E-02, 3.0100E-02, 1.5800E-02, 9.0800E-03, 6.9700E-03, 
            6.6000E-03, 2.7000E-03, 6.0000E-04, 3.9000E-04, 2.2000E-04, 
            3.8000E-05, 2.0000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {8.0300E-02, 8.0300E-02, 8.0300E-02, 8.0300E-02, 
            8.0300E-02, 8.0300E-02, 8.0300E-02, 8.0300E-02, 8.0300E-02, 
            8.0300E-02, 8.0300E-02, 8.0300E-02, 8.0200E-02, 8.0200E-02, 
            8.0000E-02, 7.9800E-02, 7.9500E-02, 7.8300E-02, 7.4800E-02, 
            6.3900E-02, 4.8700E-02, 3.3300E-02, 2.0800E-02, 1.2200E-02, 
            4.3000E-03, 2.5000E-03, 1.7000E-03, 3.8000E-04, 7.7000E-05, 
            4.8000E-06, 9.2000E-08} );

    subshell_half_profiles[13] = 
      std::vector<double>( {8.2200E-02, 8.2200E-02, 8.2200E-02, 8.2200E-02, 
            8.2200E-02, 8.2200E-02, 8.2200E-02, 8.2200E-02, 8.2200E-02, 
            8.2200E-02, 8.2200E-02, 8.2200E-02, 8.2100E-02, 8.2100E-02, 
            8.1900E-02, 8.1700E-02, 8.1300E-02, 7.9900E-02, 7.6000E-02, 
            6.4100E-02, 4.7900E-02, 3.2100E-02, 1.9600E-02, 1.1300E-02, 
            4.0000E-03, 2.5000E-03, 1.7000E-03, 3.4000E-04, 6.4000E-05, 
            3.5000E-06, 5.2000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {7.1600E-02, 7.1600E-02, 7.1600E-02, 7.1600E-02, 
            7.1600E-02, 7.1600E-02, 7.1600E-02, 7.1600E-02, 7.1600E-02, 
            7.1600E-02, 7.1600E-02, 7.1600E-02, 7.1600E-02, 7.1500E-02, 
            7.1400E-02, 7.1300E-02, 7.1000E-02, 7.0200E-02, 6.7600E-02, 
            6.0000E-02, 4.9600E-02, 3.8900E-02, 2.9400E-02, 2.1600E-02, 
            1.1000E-02, 2.0000E-03, 3.9000E-04, 2.1000E-05, 1.9000E-06, 
            4.1000E-08, 2.6000E-10} );

    subshell_half_profiles[15] = 
      std::vector<double>( {7.2300E-02, 7.2300E-02, 7.2300E-02, 7.2300E-02, 
            7.2300E-02, 7.2300E-02, 7.2300E-02, 7.2300E-02, 7.2300E-02, 
            7.2300E-02, 7.2300E-02, 7.2300E-02, 7.2300E-02, 7.2200E-02, 
            7.2200E-02, 7.2000E-02, 7.1800E-02, 7.0900E-02, 6.8200E-02, 
            6.0300E-02, 4.9600E-02, 3.8700E-02, 2.9000E-02, 2.1200E-02, 
            1.1000E-02, 1.9000E-03, 3.6000E-04, 1.9000E-05, 1.6000E-06, 
            3.3000E-08, 1.7000E-10} );

    subshell_half_profiles[16] = 
      std::vector<double>( {3.8400E-01, 3.8300E-01, 3.8100E-01, 3.7800E-01, 
            3.7300E-01, 3.6000E-01, 3.4200E-01, 3.2000E-01, 2.9500E-01, 
            2.6900E-01, 2.4200E-01, 1.8800E-01, 1.4000E-01, 1.0000E-01, 
            7.1100E-02, 5.1300E-02, 3.9100E-02, 2.9800E-02, 2.8800E-02, 
            2.0800E-02, 9.4300E-03, 4.0400E-03, 2.9000E-03, 2.8500E-03, 
            2.1000E-03, 3.1000E-04, 2.5000E-04, 6.4000E-05, 1.1000E-05, 
            7.4000E-06, 2.2000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {2.5800E-01, 2.5800E-01, 2.5800E-01, 2.5800E-01, 
            2.5800E-01, 2.5800E-01, 2.5700E-01, 2.5500E-01, 2.5200E-01, 
            2.4700E-01, 2.4100E-01, 2.2200E-01, 1.9800E-01, 1.7000E-01, 
            1.4000E-01, 1.1100E-01, 8.5800E-02, 4.7200E-02, 1.9000E-02, 
            1.1200E-02, 1.0400E-02, 7.0500E-03, 3.7900E-03, 1.9000E-03, 
            9.3000E-04, 6.0000E-04, 1.4000E-04, 5.2000E-05, 3.7000E-05, 
            9.3000E-06, 7.6000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.8100E-01, 2.8100E-01, 2.8100E-01, 2.8000E-01, 
            2.8000E-01, 2.8000E-01, 2.7800E-01, 2.7600E-01, 2.7100E-01, 
            2.6400E-01, 2.5500E-01, 2.3100E-01, 2.0000E-01, 1.6500E-01, 
            1.3100E-01, 9.9600E-02, 7.3300E-02, 3.7200E-02, 1.5500E-02, 
            1.1800E-02, 9.7800E-03, 5.7200E-03, 2.7400E-03, 1.4000E-03, 
            9.7000E-04, 4.7000E-04, 1.0000E-04, 5.8000E-05, 3.3000E-05, 
            5.8000E-06, 3.0000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {2.9100E-01, 2.9100E-01, 2.9100E-01, 2.9100E-01, 
            2.9100E-01, 2.9000E-01, 2.9000E-01, 2.8800E-01, 2.8300E-01, 
            2.7700E-01, 2.6700E-01, 2.4000E-01, 2.0700E-01, 1.7000E-01, 
            1.3600E-01, 1.0500E-01, 7.9800E-02, 4.3000E-02, 1.5400E-02, 
            4.1300E-03, 3.5000E-03, 3.1700E-03, 2.3300E-03, 1.4700E-03, 
            4.9000E-04, 1.9000E-04, 1.4000E-04, 3.2000E-05, 6.5000E-06, 
            4.0000E-07, 7.6000E-09} );

    subshell_half_profiles[20] = 
      std::vector<double>( {3.0600E-01, 3.0600E-01, 3.0600E-01, 3.0600E-01, 
            3.0600E-01, 3.0600E-01, 3.0500E-01, 3.0200E-01, 2.9600E-01, 
            2.8700E-01, 2.7500E-01, 2.4300E-01, 2.0400E-01, 1.6500E-01, 
            1.2900E-01, 9.8000E-02, 7.2700E-02, 3.7800E-02, 1.3000E-02, 
            3.7800E-03, 3.4000E-03, 2.9800E-03, 2.1100E-03, 1.2900E-03, 
            4.2000E-04, 1.8000E-04, 1.3000E-04, 2.7000E-05, 5.1000E-06, 
            2.8000E-07, 4.1000E-09} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.4000E+00, 1.3700E+00, 1.2900E+00, 1.1600E+00, 
            1.0100E+00, 6.8300E-01, 4.0700E-01, 2.2100E-01, 1.1600E-01, 
            6.7000E-02, 4.8300E-02, 4.2900E-02, 4.0900E-02, 3.3900E-02, 
            2.4700E-02, 1.6600E-02, 1.0500E-02, 4.3100E-03, 2.5700E-03, 
            2.1800E-03, 1.0600E-03, 4.1100E-04, 2.4900E-04, 2.3900E-04, 
            1.8000E-04, 2.7000E-05, 2.1000E-05, 5.3000E-06, 9.0000E-07, 
            6.1000E-07, 1.8000E-07} );
  }
};

//! The default Compton profile generator implementation for A=78
template<>
struct DefaultComptonProfileGeneratorImpl<78u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 22 );

    subshell_half_profiles[0] = 
      std::vector<double>( {9.4600E-03, 9.4600E-03, 9.4600E-03, 9.4600E-03, 
            9.4600E-03, 9.4600E-03, 9.4600E-03, 9.4600E-03, 9.4600E-03, 
            9.4500E-03, 9.4500E-03, 9.4500E-03, 9.4500E-03, 9.4500E-03, 
            9.4500E-03, 9.4400E-03, 9.4400E-03, 9.4300E-03, 9.4200E-03, 
            9.3900E-03, 9.3600E-03, 9.3200E-03, 9.2700E-03, 9.2100E-03, 
            9.1000E-03, 8.6000E-03, 8.0000E-03, 6.7000E-03, 5.3000E-03, 
            3.0000E-03, 8.9000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.3600E-02, 3.3600E-02, 3.3600E-02, 3.3600E-02, 
            3.3600E-02, 3.3600E-02, 3.3600E-02, 3.3600E-02, 3.3600E-02, 
            3.3600E-02, 3.3500E-02, 3.3500E-02, 3.3400E-02, 3.3300E-02, 
            3.3200E-02, 3.3100E-02, 3.3000E-02, 3.2700E-02, 3.2200E-02, 
            3.1200E-02, 2.9900E-02, 2.8400E-02, 2.6800E-02, 2.5000E-02, 
            2.1000E-02, 1.2000E-02, 6.1000E-03, 1.4000E-03, 8.3000E-04, 
            7.0000E-04, 2.1000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.6400E-02, 1.6400E-02, 1.6400E-02, 1.6400E-02, 
            1.6400E-02, 1.6400E-02, 1.6400E-02, 1.6400E-02, 1.6400E-02, 
            1.6400E-02, 1.6400E-02, 1.6400E-02, 1.6400E-02, 1.6400E-02, 
            1.6400E-02, 1.6400E-02, 1.6400E-02, 1.6400E-02, 1.6400E-02, 
            1.6400E-02, 1.6400E-02, 1.6300E-02, 1.6300E-02, 1.6200E-02, 
            1.6000E-02, 1.4000E-02, 1.2000E-02, 6.9000E-03, 3.5000E-03, 
            8.2000E-04, 7.5000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.8400E-02, 1.8400E-02, 1.8400E-02, 1.8400E-02, 
            1.8400E-02, 1.8400E-02, 1.8400E-02, 1.8400E-02, 1.8400E-02, 
            1.8400E-02, 1.8400E-02, 1.8400E-02, 1.8400E-02, 1.8400E-02, 
            1.8400E-02, 1.8400E-02, 1.8400E-02, 1.8400E-02, 1.8400E-02, 
            1.8400E-02, 1.8300E-02, 1.8300E-02, 1.8200E-02, 1.8000E-02, 
            1.8000E-02, 1.5000E-02, 1.2000E-02, 6.2000E-03, 2.7000E-03, 
            4.9000E-04, 2.8000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {7.4000E-02, 7.4000E-02, 7.3900E-02, 7.3900E-02, 
            7.3900E-02, 7.3800E-02, 7.3600E-02, 7.3500E-02, 7.3300E-02, 
            7.3000E-02, 7.2700E-02, 7.2000E-02, 7.1200E-02, 7.0200E-02, 
            6.9100E-02, 6.7800E-02, 6.6500E-02, 6.3400E-02, 5.8200E-02, 
            4.8500E-02, 3.8500E-02, 2.9300E-02, 2.1500E-02, 1.5500E-02, 
            8.5000E-03, 5.6000E-03, 4.6000E-03, 1.0000E-03, 2.2000E-04, 
            1.7000E-04, 5.1000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {4.3400E-02, 4.3400E-02, 4.3400E-02, 4.3400E-02, 
            4.3400E-02, 4.3400E-02, 4.3400E-02, 4.3400E-02, 4.3400E-02, 
            4.3400E-02, 4.3400E-02, 4.3400E-02, 4.3300E-02, 4.3300E-02, 
            4.3300E-02, 4.3300E-02, 4.3200E-02, 4.3100E-02, 4.2800E-02, 
            4.1800E-02, 4.0100E-02, 3.7400E-02, 3.4100E-02, 3.0200E-02, 
            2.2000E-02, 6.5000E-03, 2.0000E-03, 1.5000E-03, 1.0000E-03, 
            2.5000E-04, 2.2000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {4.6700E-02, 4.6700E-02, 4.6700E-02, 4.6700E-02, 
            4.6700E-02, 4.6700E-02, 4.6700E-02, 4.6700E-02, 4.6700E-02, 
            4.6700E-02, 4.6700E-02, 4.6700E-02, 4.6700E-02, 4.6600E-02, 
            4.6600E-02, 4.6600E-02, 4.6500E-02, 4.6400E-02, 4.5900E-02, 
            4.4500E-02, 4.2100E-02, 3.8700E-02, 3.4400E-02, 2.9600E-02, 
            2.0000E-02, 5.1000E-03, 2.0000E-03, 1.7000E-03, 8.8000E-04, 
            1.6000E-04, 8.6000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {3.0200E-02, 3.0200E-02, 3.0200E-02, 3.0200E-02, 
            3.0200E-02, 3.0200E-02, 3.0200E-02, 3.0200E-02, 3.0200E-02, 
            3.0200E-02, 3.0200E-02, 3.0200E-02, 3.0200E-02, 3.0200E-02, 
            3.0200E-02, 3.0200E-02, 3.0200E-02, 3.0200E-02, 3.0200E-02, 
            3.0100E-02, 3.0000E-02, 2.9600E-02, 2.9000E-02, 2.8100E-02, 
            2.5000E-02, 1.6000E-02, 7.7000E-03, 1.5000E-03, 3.0000E-04, 
            2.0000E-05, 3.9000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.0900E-02, 3.0900E-02, 3.0900E-02, 3.0900E-02, 
            3.0900E-02, 3.0900E-02, 3.0900E-02, 3.0900E-02, 3.0900E-02, 
            3.0900E-02, 3.0900E-02, 3.0900E-02, 3.0900E-02, 3.0900E-02, 
            3.0900E-02, 3.0900E-02, 3.0900E-02, 3.0900E-02, 3.0900E-02, 
            3.0900E-02, 3.0700E-02, 3.0300E-02, 2.9600E-02, 2.8600E-02, 
            2.6000E-02, 1.5000E-02, 7.3000E-03, 1.3000E-03, 2.5000E-04, 
            1.4000E-05, 2.2000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5300E-01, 
            1.5200E-01, 1.5100E-01, 1.5000E-01, 1.4800E-01, 1.4600E-01, 
            1.4400E-01, 1.4100E-01, 1.3500E-01, 1.2800E-01, 1.2000E-01, 
            1.1200E-01, 1.0300E-01, 9.3700E-02, 7.6100E-02, 5.2700E-02, 
            2.7100E-02, 1.6900E-02, 1.4900E-02, 1.4800E-02, 1.3600E-02, 
            8.5000E-03, 1.6000E-03, 1.4000E-03, 3.6000E-04, 6.2000E-05, 
            4.1000E-05, 1.3000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {9.6400E-02, 9.6400E-02, 9.6400E-02, 9.6400E-02, 
            9.6400E-02, 9.6400E-02, 9.6400E-02, 9.6400E-02, 9.6400E-02, 
            9.6300E-02, 9.6200E-02, 9.6000E-02, 9.5600E-02, 9.5000E-02, 
            9.4000E-02, 9.2800E-02, 9.1200E-02, 8.6700E-02, 7.7300E-02, 
            5.6500E-02, 3.5800E-02, 2.0300E-02, 1.1300E-02, 7.3800E-03, 
            6.1000E-03, 3.5000E-03, 8.7000E-04, 3.4000E-04, 2.5000E-04, 
            6.4000E-05, 5.4000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 
            1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 1.0400E-01, 
            1.0300E-01, 1.0300E-01, 1.0300E-01, 1.0200E-01, 1.0200E-01, 
            1.0000E-01, 9.8500E-02, 9.6300E-02, 9.0400E-02, 7.8300E-02, 
            5.3600E-02, 3.1300E-02, 1.6700E-02, 9.4800E-03, 7.0300E-03, 
            6.6000E-03, 2.8000E-03, 6.4000E-04, 4.0000E-04, 2.3000E-04, 
            4.1000E-05, 2.2000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {7.8400E-02, 7.8400E-02, 7.8400E-02, 7.8400E-02, 
            7.8400E-02, 7.8400E-02, 7.8400E-02, 7.8400E-02, 7.8400E-02, 
            7.8400E-02, 7.8400E-02, 7.8400E-02, 7.8400E-02, 7.8300E-02, 
            7.8200E-02, 7.8000E-02, 7.7700E-02, 7.6700E-02, 7.3600E-02, 
            6.3700E-02, 4.9400E-02, 3.4500E-02, 2.2000E-02, 1.3100E-02, 
            4.7000E-03, 2.5000E-03, 1.8000E-03, 4.2000E-04, 8.5000E-05, 
            5.4000E-06, 1.1000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {8.0300E-02, 8.0300E-02, 8.0300E-02, 8.0300E-02, 
            8.0300E-02, 8.0300E-02, 8.0300E-02, 8.0300E-02, 8.0300E-02, 
            8.0300E-02, 8.0300E-02, 8.0300E-02, 8.0300E-02, 8.0200E-02, 
            8.0100E-02, 7.9800E-02, 7.9500E-02, 7.8300E-02, 7.4800E-02, 
            6.4000E-02, 4.8700E-02, 3.3300E-02, 2.0800E-02, 1.2200E-02, 
            4.3000E-03, 2.5000E-03, 1.7000E-03, 3.7000E-04, 7.1000E-05, 
            4.0000E-06, 6.0000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {6.9000E-02, 6.9000E-02, 6.9000E-02, 6.9000E-02, 
            6.9000E-02, 6.9000E-02, 6.9000E-02, 6.9000E-02, 6.9000E-02, 
            6.9000E-02, 6.9000E-02, 6.9000E-02, 6.9000E-02, 6.9000E-02, 
            6.8900E-02, 6.8800E-02, 6.8600E-02, 6.7900E-02, 6.5900E-02, 
            5.9400E-02, 5.0000E-02, 3.9900E-02, 3.0600E-02, 2.2800E-02, 
            1.2000E-02, 2.3000E-03, 4.4000E-04, 2.5000E-05, 2.2000E-06, 
            5.0000E-08, 3.1000E-10} );

    subshell_half_profiles[15] = 
      std::vector<double>( {6.9800E-02, 6.9800E-02, 6.9800E-02, 6.9800E-02, 
            6.9800E-02, 6.9800E-02, 6.9800E-02, 6.9800E-02, 6.9800E-02, 
            6.9800E-02, 6.9800E-02, 6.9800E-02, 6.9800E-02, 6.9800E-02, 
            6.9700E-02, 6.9600E-02, 6.9400E-02, 6.8700E-02, 6.6600E-02, 
            5.9700E-02, 5.0000E-02, 3.9700E-02, 3.0200E-02, 2.2400E-02, 
            1.2000E-02, 2.1000E-03, 4.1000E-04, 2.2000E-05, 1.9000E-06, 
            3.9000E-08, 2.0000E-10} );

    subshell_half_profiles[16] = 
      std::vector<double>( {3.7500E-01, 3.7400E-01, 3.7200E-01, 3.6900E-01, 
            3.6500E-01, 3.5200E-01, 3.3500E-01, 3.1500E-01, 2.9100E-01, 
            2.6600E-01, 2.4000E-01, 1.8900E-01, 1.4200E-01, 1.0300E-01, 
            7.3900E-02, 5.3400E-02, 4.0500E-02, 2.9800E-02, 2.8400E-02, 
            2.1600E-02, 1.0300E-02, 4.3900E-03, 2.9400E-03, 2.8500E-03, 
            2.2000E-03, 3.4000E-04, 2.5000E-04, 7.1000E-05, 1.2000E-05, 
            7.5000E-06, 2.4000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {2.5000E-01, 2.5000E-01, 2.5000E-01, 2.5000E-01, 
            2.5000E-01, 2.5000E-01, 2.4900E-01, 2.4700E-01, 2.4500E-01, 
            2.4000E-01, 2.3500E-01, 2.1800E-01, 1.9600E-01, 1.7000E-01, 
            1.4200E-01, 1.1500E-01, 8.9900E-02, 5.1000E-02, 2.0800E-02, 
            1.1200E-02, 1.0600E-02, 7.5800E-03, 4.2400E-03, 2.1500E-03, 
            9.6000E-04, 6.4000E-04, 1.6000E-04, 5.3000E-05, 4.0000E-05, 
            1.0000E-05, 8.6000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.7400E-01, 2.7400E-01, 2.7400E-01, 2.7400E-01, 
            2.7400E-01, 2.7300E-01, 2.7200E-01, 2.6900E-01, 2.6500E-01, 
            2.5900E-01, 2.5100E-01, 2.2800E-01, 1.9900E-01, 1.6600E-01, 
            1.3300E-01, 1.0300E-01, 7.6900E-02, 4.0000E-02, 1.6400E-02, 
            1.1700E-02, 1.0100E-02, 6.1700E-03, 3.0500E-03, 1.5300E-03, 
            9.7000E-04, 5.1000E-04, 1.1000E-04, 5.9000E-05, 3.5000E-05, 
            6.4000E-06, 3.3000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {2.8700E-01, 2.8700E-01, 2.8700E-01, 2.8700E-01, 
            2.8700E-01, 2.8600E-01, 2.8600E-01, 2.8300E-01, 2.7900E-01, 
            2.7300E-01, 2.6300E-01, 2.3700E-01, 2.0400E-01, 1.7000E-01, 
            1.3700E-01, 1.0700E-01, 8.2400E-02, 4.5800E-02, 1.7200E-02, 
            4.3900E-03, 3.4600E-03, 3.2300E-03, 2.4600E-03, 1.6100E-03, 
            5.5000E-04, 1.9000E-04, 1.5000E-04, 3.5000E-05, 7.3000E-06, 
            4.6000E-07, 8.9000E-09} );

    subshell_half_profiles[20] = 
      std::vector<double>( {3.0400E-01, 3.0400E-01, 3.0400E-01, 3.0400E-01, 
            3.0400E-01, 3.0300E-01, 3.0200E-01, 2.9900E-01, 2.9300E-01, 
            2.8400E-01, 2.7200E-01, 2.3900E-01, 2.0200E-01, 1.6400E-01, 
            1.2900E-01, 9.9500E-02, 7.4900E-02, 4.0200E-02, 1.4500E-02, 
            3.9200E-03, 3.3300E-03, 3.0200E-03, 2.2200E-03, 1.4000E-03, 
            4.6000E-04, 1.8000E-04, 1.3000E-04, 3.0000E-05, 5.7000E-06, 
            3.2000E-07, 4.7000E-09} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.4500E+00, 1.4100E+00, 1.3200E+00, 1.1900E+00, 
            1.0300E+00, 6.8200E-01, 3.9800E-01, 2.1100E-01, 1.0800E-01, 
            6.1200E-02, 4.3700E-02, 3.8800E-02, 3.7000E-02, 3.0700E-02, 
            2.2700E-02, 1.5400E-02, 9.9400E-03, 4.1200E-03, 2.2900E-03, 
            2.0000E-03, 1.0400E-03, 4.1300E-04, 2.3200E-04, 2.1500E-04, 
            1.7000E-04, 2.6000E-05, 1.9000E-05, 5.4000E-06, 8.9000E-07, 
            5.6000E-07, 1.8000E-07} );
  }
};

//! The default Compton profile generator implementation for A=79
template<>
struct DefaultComptonProfileGeneratorImpl<79u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 22 );

    subshell_half_profiles[0] = 
      std::vector<double>( {9.2900E-03, 9.2900E-03, 9.2900E-03, 9.2900E-03, 
            9.2900E-03, 9.2900E-03, 9.2900E-03, 9.2900E-03, 9.2900E-03, 
            9.2900E-03, 9.2900E-03, 9.2900E-03, 9.2900E-03, 9.2900E-03, 
            9.2800E-03, 9.2800E-03, 9.2800E-03, 9.2700E-03, 9.2600E-03, 
            9.2300E-03, 9.2000E-03, 9.1600E-03, 9.1100E-03, 9.0600E-03, 
            8.9000E-03, 8.5000E-03, 7.9000E-03, 6.6000E-03, 5.3000E-03, 
            3.0000E-03, 9.2000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.3100E-02, 3.3100E-02, 3.3100E-02, 3.3100E-02, 
            3.3100E-02, 3.3100E-02, 3.3000E-02, 3.3000E-02, 3.3000E-02, 
            3.3000E-02, 3.3000E-02, 3.2900E-02, 3.2900E-02, 3.2800E-02, 
            3.2700E-02, 3.2600E-02, 3.2500E-02, 3.2200E-02, 3.1700E-02, 
            3.0800E-02, 2.9500E-02, 2.8100E-02, 2.6500E-02, 2.4800E-02, 
            2.1000E-02, 1.3000E-02, 6.3000E-03, 1.4000E-03, 8.2000E-04, 
            7.0000E-04, 2.2000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.6100E-02, 1.6100E-02, 1.6100E-02, 1.6100E-02, 
            1.6100E-02, 1.6100E-02, 1.6100E-02, 1.6100E-02, 1.6100E-02, 
            1.6100E-02, 1.6100E-02, 1.6100E-02, 1.6100E-02, 1.6100E-02, 
            1.6100E-02, 1.6100E-02, 1.6100E-02, 1.6100E-02, 1.6100E-02, 
            1.6100E-02, 1.6100E-02, 1.6000E-02, 1.6000E-02, 1.5900E-02, 
            1.5900E-02, 1.4000E-02, 1.2000E-02, 7.0000E-03, 3.6000E-03, 
            8.7000E-04, 8.2000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.8100E-02, 1.8100E-02, 1.8100E-02, 1.8100E-02, 
            1.8100E-02, 1.8100E-02, 1.8100E-02, 1.8100E-02, 1.8100E-02, 
            1.8100E-02, 1.8100E-02, 1.8100E-02, 1.8100E-02, 1.8100E-02, 
            1.8100E-02, 1.8100E-02, 1.8100E-02, 1.8100E-02, 1.8100E-02, 
            1.8100E-02, 1.8100E-02, 1.8000E-02, 1.7900E-02, 1.7800E-02, 
            1.7000E-02, 1.5000E-02, 1.2000E-02, 6.3000E-03, 2.8000E-03, 
            5.2000E-04, 3.1000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {7.2700E-02, 7.2700E-02, 7.2600E-02, 7.2600E-02, 
            7.2600E-02, 7.2500E-02, 7.2400E-02, 7.2200E-02, 7.2000E-02, 
            7.1700E-02, 7.1500E-02, 7.0800E-02, 7.0000E-02, 6.9100E-02, 
            6.8000E-02, 6.6800E-02, 6.5500E-02, 6.2700E-02, 5.7700E-02, 
            4.8300E-02, 3.8700E-02, 2.9700E-02, 2.2000E-02, 1.5900E-02, 
            8.7000E-03, 5.6000E-03, 4.6000E-03, 1.1000E-03, 2.3000E-04, 
            1.7000E-04, 5.4000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 
            4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 
            4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 
            4.2500E-02, 4.2500E-02, 4.2500E-02, 4.2400E-02, 4.2100E-02, 
            4.1200E-02, 3.9500E-02, 3.7100E-02, 3.3900E-02, 3.0200E-02, 
            2.2000E-02, 6.9000E-03, 2.1000E-03, 1.5000E-03, 1.0000E-03, 
            2.7000E-04, 2.4000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {4.5900E-02, 4.5900E-02, 4.5900E-02, 4.5900E-02, 
            4.5900E-02, 4.5900E-02, 4.5900E-02, 4.5900E-02, 4.5900E-02, 
            4.5900E-02, 4.5900E-02, 4.5900E-02, 4.5900E-02, 4.5900E-02, 
            4.5900E-02, 4.5800E-02, 4.5800E-02, 4.5600E-02, 4.5200E-02, 
            4.3900E-02, 4.1700E-02, 3.8400E-02, 3.4400E-02, 2.9700E-02, 
            2.0000E-02, 5.3000E-03, 2.0000E-03, 1.7000E-03, 9.2000E-04, 
            1.7000E-04, 9.4000E-06} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.9700E-02, 2.9700E-02, 2.9700E-02, 2.9700E-02, 
            2.9700E-02, 2.9700E-02, 2.9700E-02, 2.9700E-02, 2.9700E-02, 
            2.9700E-02, 2.9700E-02, 2.9700E-02, 2.9700E-02, 2.9700E-02, 
            2.9700E-02, 2.9700E-02, 2.9700E-02, 2.9700E-02, 2.9700E-02, 
            2.9600E-02, 2.9500E-02, 2.9200E-02, 2.8600E-02, 2.7800E-02, 
            2.5000E-02, 1.6000E-02, 8.0000E-03, 1.6000E-03, 3.3000E-04, 
            2.2000E-05, 4.5000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 
            3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 
            3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 
            3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 
            3.0400E-02, 3.0200E-02, 2.9900E-02, 2.9200E-02, 2.8300E-02, 
            2.6000E-02, 1.6000E-02, 7.6000E-03, 1.4000E-03, 2.7000E-04, 
            1.6000E-05, 2.5000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.5000E-01, 1.5000E-01, 1.5000E-01, 1.4900E-01, 
            1.4900E-01, 1.4800E-01, 1.4700E-01, 1.4500E-01, 1.4300E-01, 
            1.4100E-01, 1.3900E-01, 1.3300E-01, 1.2600E-01, 1.1900E-01, 
            1.1100E-01, 1.0200E-01, 9.3500E-02, 7.6500E-02, 5.3700E-02, 
            2.8000E-02, 1.7100E-02, 1.4700E-02, 1.4600E-02, 1.3700E-02, 
            8.9000E-03, 1.6000E-03, 1.4000E-03, 3.9000E-04, 6.7000E-05, 
            4.1000E-05, 1.4000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {9.4300E-02, 9.4300E-02, 9.4300E-02, 9.4300E-02, 
            9.4300E-02, 9.4300E-02, 9.4300E-02, 9.4300E-02, 9.4300E-02, 
            9.4200E-02, 9.4200E-02, 9.4000E-02, 9.3600E-02, 9.3000E-02, 
            9.2200E-02, 9.1000E-02, 8.9600E-02, 8.5500E-02, 7.6700E-02, 
            5.7100E-02, 3.6900E-02, 2.1400E-02, 1.2000E-02, 7.6500E-03, 
            6.0000E-03, 3.7000E-03, 9.5000E-04, 3.4000E-04, 2.6000E-04, 
            6.8000E-05, 6.0000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {1.0200E-01, 1.0200E-01, 1.0200E-01, 1.0200E-01, 
            1.0200E-01, 1.0200E-01, 1.0100E-01, 1.0100E-01, 1.0100E-01, 
            1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0000E-01, 9.9600E-02, 
            9.8500E-02, 9.6900E-02, 9.4800E-02, 8.9400E-02, 7.8100E-02, 
            5.4500E-02, 3.2500E-02, 1.7600E-02, 9.9200E-03, 7.1300E-03, 
            6.5000E-03, 3.0000E-03, 6.9000E-04, 4.0000E-04, 2.4000E-04, 
            4.5000E-05, 2.4000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {7.6700E-02, 7.6700E-02, 7.6700E-02, 7.6700E-02, 
            7.6700E-02, 7.6700E-02, 7.6700E-02, 7.6700E-02, 7.6700E-02, 
            7.6700E-02, 7.6700E-02, 7.6700E-02, 7.6600E-02, 7.6600E-02, 
            7.6500E-02, 7.6300E-02, 7.6100E-02, 7.5200E-02, 7.2400E-02, 
            6.3400E-02, 5.0000E-02, 3.5500E-02, 2.3100E-02, 1.4100E-02, 
            5.0000E-03, 2.5000E-03, 1.9000E-03, 4.5000E-04, 9.4000E-05, 
            6.1000E-06, 1.2000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {7.8500E-02, 7.8500E-02, 7.8500E-02, 7.8500E-02, 
            7.8500E-02, 7.8500E-02, 7.8500E-02, 7.8500E-02, 7.8500E-02, 
            7.8500E-02, 7.8500E-02, 7.8500E-02, 7.8400E-02, 7.8400E-02, 
            7.8300E-02, 7.8100E-02, 7.7800E-02, 7.6800E-02, 7.3700E-02, 
            6.3800E-02, 4.9400E-02, 3.4400E-02, 2.1900E-02, 1.3100E-02, 
            4.6000E-03, 2.5000E-03, 1.8000E-03, 4.0000E-04, 7.9000E-05, 
            4.5000E-06, 6.8000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {6.6600E-02, 6.6600E-02, 6.6600E-02, 6.6600E-02, 
            6.6600E-02, 6.6600E-02, 6.6600E-02, 6.6600E-02, 6.6600E-02, 
            6.6600E-02, 6.6600E-02, 6.6600E-02, 6.6600E-02, 6.6600E-02, 
            6.6600E-02, 6.6500E-02, 6.6400E-02, 6.5900E-02, 6.4200E-02, 
            5.8700E-02, 5.0300E-02, 4.0700E-02, 3.1700E-02, 2.3900E-02, 
            1.3000E-02, 2.5000E-03, 5.0000E-04, 2.9000E-05, 2.6000E-06, 
            6.0000E-08, 3.8000E-10} );

    subshell_half_profiles[15] = 
      std::vector<double>( {6.7500E-02, 6.7500E-02, 6.7500E-02, 6.7500E-02, 
            6.7500E-02, 6.7500E-02, 6.7500E-02, 6.7500E-02, 6.7500E-02, 
            6.7500E-02, 6.7500E-02, 6.7500E-02, 6.7500E-02, 6.7500E-02, 
            6.7400E-02, 6.7400E-02, 6.7200E-02, 6.6700E-02, 6.4900E-02, 
            5.9000E-02, 5.0300E-02, 4.0500E-02, 3.1300E-02, 2.3500E-02, 
            1.3000E-02, 2.4000E-03, 4.7000E-04, 2.6000E-05, 2.3000E-06, 
            4.7000E-08, 2.5000E-10} );

    subshell_half_profiles[16] = 
      std::vector<double>( {3.6300E-01, 3.6300E-01, 3.6100E-01, 3.5800E-01, 
            3.5400E-01, 3.4200E-01, 3.2700E-01, 3.0800E-01, 2.8600E-01, 
            2.6300E-01, 2.3900E-01, 1.9000E-01, 1.4500E-01, 1.0700E-01, 
            7.7300E-02, 5.6200E-02, 4.2400E-02, 3.0200E-02, 2.8100E-02, 
            2.2500E-02, 1.1300E-02, 4.8500E-03, 3.0300E-03, 2.8700E-03, 
            2.3000E-03, 3.7000E-04, 2.6000E-04, 7.9000E-05, 1.3000E-05, 
            7.7000E-06, 2.6000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {2.4200E-01, 2.4200E-01, 2.4200E-01, 2.4200E-01, 
            2.4200E-01, 2.4100E-01, 2.4100E-01, 2.3900E-01, 2.3700E-01, 
            2.3300E-01, 2.2800E-01, 2.1400E-01, 1.9400E-01, 1.7000E-01, 
            1.4400E-01, 1.1800E-01, 9.4200E-02, 5.5200E-02, 2.3000E-02, 
            1.1300E-02, 1.0800E-02, 8.1200E-03, 4.7400E-03, 2.4400E-03, 
            1.0000E-03, 6.9000E-04, 1.9000E-04, 5.4000E-05, 4.2000E-05, 
            1.1000E-05, 9.9000E-07} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.6600E-01, 2.6600E-01, 2.6600E-01, 2.6600E-01, 
            2.6600E-01, 2.6500E-01, 2.6400E-01, 2.6200E-01, 2.5800E-01, 
            2.5300E-01, 2.4500E-01, 2.2500E-01, 1.9800E-01, 1.6800E-01, 
            1.3600E-01, 1.0700E-01, 8.1200E-02, 4.3500E-02, 1.7800E-02, 
            1.1700E-02, 1.0500E-02, 6.7000E-03, 3.4200E-03, 1.7100E-03, 
            9.9000E-04, 5.6000E-04, 1.2000E-04, 6.1000E-05, 3.7000E-05, 
            7.0000E-06, 3.8000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {2.7300E-01, 2.7300E-01, 2.7300E-01, 2.7300E-01, 
            2.7300E-01, 2.7200E-01, 2.7200E-01, 2.7000E-01, 2.6700E-01, 
            2.6200E-01, 2.5400E-01, 2.3200E-01, 2.0400E-01, 1.7300E-01, 
            1.4200E-01, 1.1400E-01, 8.9000E-02, 5.1400E-02, 2.0300E-02, 
            5.0100E-03, 3.6000E-03, 3.4400E-03, 2.7200E-03, 1.8300E-03, 
            6.5000E-04, 2.0000E-04, 1.6000E-04, 4.1000E-05, 8.6000E-06, 
            5.5000E-07, 1.1000E-08} );

    subshell_half_profiles[20] = 
      std::vector<double>( {2.8800E-01, 2.8800E-01, 2.8800E-01, 2.8800E-01, 
            2.8800E-01, 2.8800E-01, 2.8700E-01, 2.8500E-01, 2.8100E-01, 
            2.7300E-01, 2.6300E-01, 2.3600E-01, 2.0300E-01, 1.6900E-01, 
            1.3600E-01, 1.0600E-01, 8.1700E-02, 4.5600E-02, 1.7200E-02, 
            4.4000E-03, 3.4600E-03, 3.2300E-03, 2.4600E-03, 1.6100E-03, 
            5.5000E-04, 1.9000E-04, 1.5000E-04, 3.4000E-05, 6.7000E-06, 
            3.8000E-07, 5.7000E-09} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.4100E+00, 1.3800E+00, 1.3000E+00, 1.1700E+00, 
            1.0200E+00, 6.8800E-01, 4.1000E-01, 2.2300E-01, 1.1600E-01, 
            6.4800E-02, 4.4300E-02, 3.7400E-02, 3.6300E-02, 3.1100E-02, 
            2.3700E-02, 1.6600E-02, 1.1000E-02, 4.6200E-03, 2.3100E-03, 
            2.0600E-03, 1.1500E-03, 4.7000E-04, 2.4500E-04, 2.1800E-04, 
            1.8000E-04, 2.9000E-05, 1.9000E-05, 6.0000E-06, 9.8000E-07, 
            5.8000E-07, 1.9000E-07} );
  }
};

//! The default Compton profile generator implementation for A=80
template<>
struct DefaultComptonProfileGeneratorImpl<80u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 22 );

    subshell_half_profiles[0] = 
      std::vector<double>( {9.1300E-03, 9.1300E-03, 9.1300E-03, 9.1300E-03, 
            9.1300E-03, 9.1300E-03, 9.1300E-03, 9.1300E-03, 9.1300E-03, 
            9.1300E-03, 9.1300E-03, 9.1300E-03, 9.1300E-03, 9.1300E-03, 
            9.1200E-03, 9.1200E-03, 9.1200E-03, 9.1100E-03, 9.1000E-03, 
            9.0800E-03, 9.0400E-03, 9.0000E-03, 8.9600E-03, 8.9100E-03, 
            8.8000E-03, 8.4000E-03, 7.8000E-03, 6.6000E-03, 5.2000E-03, 
            3.1000E-03, 9.5000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.2500E-02, 3.2500E-02, 3.2500E-02, 3.2500E-02, 
            3.2500E-02, 3.2500E-02, 3.2500E-02, 3.2500E-02, 3.2500E-02, 
            3.2400E-02, 3.2400E-02, 3.2400E-02, 3.2300E-02, 3.2200E-02, 
            3.2100E-02, 3.2000E-02, 3.1900E-02, 3.1700E-02, 3.1200E-02, 
            3.0300E-02, 2.9100E-02, 2.7800E-02, 2.6300E-02, 2.4600E-02, 
            2.1000E-02, 1.3000E-02, 6.5000E-03, 1.5000E-03, 8.1000E-04, 
            7.0000E-04, 2.3000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5800E-02, 
            1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5800E-02, 
            1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5800E-02, 
            1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5800E-02, 
            1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5700E-02, 1.5600E-02, 
            1.5000E-02, 1.4000E-02, 1.2000E-02, 7.1000E-03, 3.7000E-03, 
            9.2000E-04, 9.0000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.7900E-02, 1.7900E-02, 1.7900E-02, 1.7900E-02, 
            1.7900E-02, 1.7900E-02, 1.7900E-02, 1.7900E-02, 1.7900E-02, 
            1.7900E-02, 1.7900E-02, 1.7900E-02, 1.7900E-02, 1.7900E-02, 
            1.7900E-02, 1.7900E-02, 1.7900E-02, 1.7900E-02, 1.7900E-02, 
            1.7800E-02, 1.7800E-02, 1.7800E-02, 1.7700E-02, 1.7500E-02, 
            1.7000E-02, 1.5000E-02, 1.2000E-02, 6.4000E-03, 2.9000E-03, 
            5.5000E-04, 3.3000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {7.1400E-02, 7.1400E-02, 7.1400E-02, 7.1400E-02, 
            7.1300E-02, 7.1200E-02, 7.1100E-02, 7.0900E-02, 7.0800E-02, 
            7.0500E-02, 7.0300E-02, 6.9600E-02, 6.8900E-02, 6.8000E-02, 
            6.7000E-02, 6.5900E-02, 6.4600E-02, 6.1900E-02, 5.7100E-02, 
            4.8200E-02, 3.8800E-02, 3.0000E-02, 2.2400E-02, 1.6400E-02, 
            8.9000E-03, 5.5000E-03, 4.7000E-03, 1.2000E-03, 2.4000E-04, 
            1.6000E-04, 5.6000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1800E-02, 
            4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1800E-02, 
            4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1800E-02, 
            4.1800E-02, 4.1800E-02, 4.1700E-02, 4.1600E-02, 4.1400E-02, 
            4.0500E-02, 3.9000E-02, 3.6700E-02, 3.3700E-02, 3.0200E-02, 
            2.2000E-02, 7.2000E-03, 2.2000E-03, 1.5000E-03, 1.1000E-03, 
            2.8000E-04, 2.6000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 
            4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 
            4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 
            4.5200E-02, 4.5100E-02, 4.5100E-02, 4.4900E-02, 4.4600E-02, 
            4.3400E-02, 4.1200E-02, 3.8200E-02, 3.4300E-02, 2.9900E-02, 
            2.1000E-02, 5.6000E-03, 2.1000E-03, 1.7000E-03, 9.5000E-04, 
            1.8000E-04, 1.0000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.9200E-02, 2.9200E-02, 2.9200E-02, 2.9200E-02, 
            2.9200E-02, 2.9200E-02, 2.9200E-02, 2.9200E-02, 2.9200E-02, 
            2.9200E-02, 2.9200E-02, 2.9200E-02, 2.9200E-02, 2.9200E-02, 
            2.9200E-02, 2.9200E-02, 2.9200E-02, 2.9200E-02, 2.9200E-02, 
            2.9200E-02, 2.9000E-02, 2.8700E-02, 2.8200E-02, 2.7500E-02, 
            2.5000E-02, 1.6000E-02, 8.2000E-03, 1.7000E-03, 3.5000E-04, 
            2.4000E-05, 5.0000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {3.0000E-02, 3.0000E-02, 3.0000E-02, 3.0000E-02, 
            3.0000E-02, 3.0000E-02, 3.0000E-02, 3.0000E-02, 3.0000E-02, 
            3.0000E-02, 3.0000E-02, 3.0000E-02, 3.0000E-02, 3.0000E-02, 
            3.0000E-02, 3.0000E-02, 3.0000E-02, 3.0000E-02, 2.9900E-02, 
            2.9900E-02, 2.9700E-02, 2.9400E-02, 2.8900E-02, 2.8000E-02, 
            2.5000E-02, 1.6000E-02, 7.8000E-03, 1.5000E-03, 3.0000E-04, 
            1.8000E-05, 2.8000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.4700E-01, 1.4700E-01, 1.4600E-01, 1.4600E-01, 
            1.4600E-01, 1.4500E-01, 1.4400E-01, 1.4200E-01, 1.4100E-01, 
            1.3900E-01, 1.3600E-01, 1.3100E-01, 1.2400E-01, 1.1700E-01, 
            1.1000E-01, 1.0100E-01, 9.3200E-02, 7.6800E-02, 5.4600E-02, 
            2.8800E-02, 1.7400E-02, 1.4600E-02, 1.4400E-02, 1.3700E-02, 
            9.3000E-03, 1.7000E-03, 1.4000E-03, 4.2000E-04, 7.2000E-05, 
            4.1000E-05, 1.4000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {9.2300E-02, 9.2300E-02, 9.2300E-02, 9.2300E-02, 
            9.2300E-02, 9.2300E-02, 9.2300E-02, 9.2300E-02, 9.2300E-02, 
            9.2200E-02, 9.2200E-02, 9.2000E-02, 9.1600E-02, 9.1100E-02, 
            9.0400E-02, 8.9300E-02, 8.8000E-02, 8.4300E-02, 7.6100E-02, 
            5.7600E-02, 3.8000E-02, 2.2500E-02, 1.2700E-02, 7.9600E-03, 
            5.9000E-03, 3.8000E-03, 1.0000E-03, 3.4000E-04, 2.6000E-04, 
            7.3000E-05, 6.6000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {9.9500E-02, 9.9500E-02, 9.9500E-02, 9.9500E-02, 
            9.9500E-02, 9.9500E-02, 9.9500E-02, 9.9500E-02, 9.9400E-02, 
            9.9400E-02, 9.9300E-02, 9.9000E-02, 9.8500E-02, 9.7800E-02, 
            9.6700E-02, 9.5300E-02, 9.3400E-02, 8.8400E-02, 7.7700E-02, 
            5.5200E-02, 3.3600E-02, 1.8500E-02, 1.0400E-02, 7.2500E-03, 
            6.5000E-03, 3.2000E-03, 7.4000E-04, 4.0000E-04, 2.4000E-04, 
            4.8000E-05, 2.6000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {7.5000E-02, 7.5000E-02, 7.5000E-02, 7.5000E-02, 
            7.5000E-02, 7.5000E-02, 7.5000E-02, 7.5000E-02, 7.5000E-02, 
            7.5000E-02, 7.5000E-02, 7.5000E-02, 7.4900E-02, 7.4900E-02, 
            7.4800E-02, 7.4700E-02, 7.4500E-02, 7.3700E-02, 7.1200E-02, 
            6.3000E-02, 5.0400E-02, 3.6500E-02, 2.4200E-02, 1.5000E-02, 
            5.4000E-03, 2.5000E-03, 1.9000E-03, 4.8000E-04, 1.0000E-04, 
            6.9000E-06, 1.4000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {7.6800E-02, 7.6800E-02, 7.6800E-02, 7.6800E-02, 
            7.6800E-02, 7.6800E-02, 7.6800E-02, 7.6800E-02, 7.6800E-02, 
            7.6800E-02, 7.6800E-02, 7.6800E-02, 7.6700E-02, 7.6700E-02, 
            7.6600E-02, 7.6400E-02, 7.6200E-02, 7.5300E-02, 7.2500E-02, 
            6.3500E-02, 5.0000E-02, 3.5500E-02, 2.3000E-02, 1.4000E-02, 
            5.0000E-03, 2.5000E-03, 1.9000E-03, 4.3000E-04, 8.7000E-05, 
            5.1000E-06, 7.8000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {6.4500E-02, 6.4500E-02, 6.4500E-02, 6.4500E-02, 
            6.4500E-02, 6.4500E-02, 6.4500E-02, 6.4500E-02, 6.4500E-02, 
            6.4500E-02, 6.4500E-02, 6.4500E-02, 6.4500E-02, 6.4500E-02, 
            6.4400E-02, 6.4400E-02, 6.4300E-02, 6.3900E-02, 6.2600E-02, 
            5.7900E-02, 5.0300E-02, 4.1400E-02, 3.2700E-02, 2.5000E-02, 
            1.4000E-02, 2.8000E-03, 5.7000E-04, 3.3000E-05, 3.1000E-06, 
            7.2000E-08, 4.7000E-10} );

    subshell_half_profiles[15] = 
      std::vector<double>( {6.5300E-02, 6.5300E-02, 6.5300E-02, 6.5300E-02, 
            6.5300E-02, 6.5300E-02, 6.5300E-02, 6.5300E-02, 6.5300E-02, 
            6.5300E-02, 6.5300E-02, 6.5300E-02, 6.5300E-02, 6.5300E-02, 
            6.5300E-02, 6.5200E-02, 6.5100E-02, 6.4700E-02, 6.3300E-02, 
            5.8300E-02, 5.0400E-02, 4.1200E-02, 3.2300E-02, 2.4600E-02, 
            1.3000E-02, 2.6000E-03, 5.3000E-04, 3.0000E-05, 2.7000E-06, 
            5.7000E-08, 3.0000E-10} );

    subshell_half_profiles[16] = 
      std::vector<double>( {3.5000E-01, 3.4900E-01, 3.4700E-01, 3.4500E-01, 
            3.4100E-01, 3.3100E-01, 3.1700E-01, 2.9900E-01, 2.8000E-01, 
            2.5900E-01, 2.3600E-01, 1.9100E-01, 1.4800E-01, 1.1100E-01, 
            8.1300E-02, 5.9600E-02, 4.4900E-02, 3.0900E-02, 2.8000E-02, 
            2.3400E-02, 1.2500E-02, 5.4100E-03, 3.1700E-03, 2.9100E-03, 
            2.5000E-03, 4.1000E-04, 2.6000E-04, 8.9000E-05, 1.5000E-05, 
            7.9000E-06, 2.8000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {2.3300E-01, 2.3300E-01, 2.3300E-01, 2.3300E-01, 
            2.3300E-01, 2.3200E-01, 2.3200E-01, 2.3100E-01, 2.2900E-01, 
            2.2600E-01, 2.2100E-01, 2.0900E-01, 1.9200E-01, 1.7000E-01, 
            1.4600E-01, 1.2200E-01, 9.8600E-02, 5.9700E-02, 2.5600E-02, 
            1.1600E-02, 1.1100E-02, 8.6800E-03, 5.2800E-03, 2.7900E-03, 
            1.1000E-03, 7.4000E-04, 2.1000E-04, 5.6000E-05, 4.4000E-05, 
            1.3000E-05, 1.1000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.5600E-01, 2.5600E-01, 2.5600E-01, 2.5600E-01, 
            2.5600E-01, 2.5500E-01, 2.5400E-01, 2.5300E-01, 2.4900E-01, 
            2.4500E-01, 2.3900E-01, 2.2100E-01, 1.9700E-01, 1.6900E-01, 
            1.4000E-01, 1.1200E-01, 8.6200E-02, 4.7700E-02, 1.9600E-02, 
            1.1900E-02, 1.0900E-02, 7.3100E-03, 3.8600E-03, 1.9200E-03, 
            1.0000E-03, 6.1000E-04, 1.4000E-04, 6.4000E-05, 4.0000E-05, 
            7.9000E-06, 4.3000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {2.5200E-01, 2.5200E-01, 2.5200E-01, 2.5200E-01, 
            2.5200E-01, 2.5200E-01, 2.5200E-01, 2.5100E-01, 2.4900E-01, 
            2.4600E-01, 2.4100E-01, 2.2500E-01, 2.0400E-01, 1.7800E-01, 
            1.5000E-01, 1.2300E-01, 9.8900E-02, 5.9800E-02, 2.5000E-02, 
            6.0600E-03, 3.9000E-03, 3.7900E-03, 3.1100E-03, 2.1700E-03, 
            8.0000E-04, 2.2000E-04, 1.8000E-04, 4.9000E-05, 1.0000E-05, 
            6.9000E-07, 1.4000E-08} );

    subshell_half_profiles[20] = 
      std::vector<double>( {2.6500E-01, 2.6500E-01, 2.6500E-01, 2.6500E-01, 
            2.6500E-01, 2.6500E-01, 2.6400E-01, 2.6300E-01, 2.6100E-01, 
            2.5600E-01, 2.5000E-01, 2.3100E-01, 2.0500E-01, 1.7600E-01, 
            1.4600E-01, 1.1700E-01, 9.2500E-02, 5.4000E-02, 2.1500E-02, 
            5.3000E-03, 3.7900E-03, 3.6200E-03, 2.8600E-03, 1.9300E-03, 
            6.8000E-04, 2.1000E-04, 1.7000E-04, 4.1000E-05, 8.3000E-06, 
            4.8000E-07, 7.4000E-09} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.2900E+00, 1.2700E+00, 1.2100E+00, 1.1000E+00, 
            9.7600E-01, 6.9600E-01, 4.4300E-01, 2.5800E-01, 1.4300E-01, 
            8.1200E-02, 5.2600E-02, 3.9100E-02, 3.8600E-02, 3.4900E-02, 
            2.8100E-02, 2.0700E-02, 1.4200E-02, 6.1600E-03, 2.7000E-03, 
            2.3900E-03, 1.4400E-03, 6.0900E-04, 2.9800E-04, 2.4900E-04, 
            2.2000E-04, 3.6000E-05, 2.2000E-05, 7.6000E-06, 1.2000E-06, 
            6.7000E-07, 2.4000E-07} );
  }
};

//! The default Compton profile generator implementation for A=81
template<>
struct DefaultComptonProfileGeneratorImpl<81u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 23 );

    subshell_half_profiles[0] = 
      std::vector<double>( {8.9800E-03, 8.9800E-03, 8.9800E-03, 8.9800E-03, 
            8.9800E-03, 8.9800E-03, 8.9800E-03, 8.9700E-03, 8.9700E-03, 
            8.9700E-03, 8.9700E-03, 8.9700E-03, 8.9700E-03, 8.9700E-03, 
            8.9700E-03, 8.9600E-03, 8.9600E-03, 8.9600E-03, 8.9400E-03, 
            8.9200E-03, 8.8900E-03, 8.8500E-03, 8.8100E-03, 8.7600E-03, 
            8.6000E-03, 8.3000E-03, 7.7000E-03, 6.5000E-03, 5.2000E-03, 
            3.1000E-03, 9.8000E-04} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.2000E-02, 3.2000E-02, 3.2000E-02, 3.2000E-02, 
            3.2000E-02, 3.2000E-02, 3.1900E-02, 3.1900E-02, 3.1900E-02, 
            3.1900E-02, 3.1900E-02, 3.1800E-02, 3.1800E-02, 3.1700E-02, 
            3.1600E-02, 3.1500E-02, 3.1400E-02, 3.1200E-02, 3.0800E-02, 
            2.9900E-02, 2.8800E-02, 2.7500E-02, 2.6000E-02, 2.4400E-02, 
            2.1000E-02, 1.3000E-02, 6.7000E-03, 1.6000E-03, 8.0000E-04, 
            7.0000E-04, 2.4000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.5500E-02, 1.5500E-02, 1.5500E-02, 1.5500E-02, 
            1.5500E-02, 1.5500E-02, 1.5500E-02, 1.5500E-02, 1.5500E-02, 
            1.5500E-02, 1.5500E-02, 1.5500E-02, 1.5500E-02, 1.5500E-02, 
            1.5500E-02, 1.5500E-02, 1.5500E-02, 1.5500E-02, 1.5500E-02, 
            1.5500E-02, 1.5500E-02, 1.5500E-02, 1.5400E-02, 1.5400E-02, 
            1.5000E-02, 1.4000E-02, 1.2000E-02, 7.2000E-03, 3.8000E-03, 
            9.7000E-04, 9.7000E-05} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.7600E-02, 1.7600E-02, 1.7600E-02, 1.7600E-02, 
            1.7600E-02, 1.7600E-02, 1.7600E-02, 1.7600E-02, 1.7600E-02, 
            1.7600E-02, 1.7600E-02, 1.7600E-02, 1.7600E-02, 1.7600E-02, 
            1.7600E-02, 1.7600E-02, 1.7600E-02, 1.7600E-02, 1.7600E-02, 
            1.7600E-02, 1.7600E-02, 1.7500E-02, 1.7400E-02, 1.7300E-02, 
            1.7000E-02, 1.5000E-02, 1.2000E-02, 6.5000E-03, 3.0000E-03, 
            5.8000E-04, 3.6000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {7.0200E-02, 7.0100E-02, 7.0100E-02, 7.0100E-02, 
            7.0100E-02, 7.0000E-02, 6.9900E-02, 6.9700E-02, 6.9500E-02, 
            6.9300E-02, 6.9100E-02, 6.8500E-02, 6.7800E-02, 6.6900E-02, 
            6.6000E-02, 6.4900E-02, 6.3700E-02, 6.1100E-02, 5.6600E-02, 
            4.7900E-02, 3.8900E-02, 3.0300E-02, 2.2800E-02, 1.6800E-02, 
            9.2000E-03, 5.4000E-03, 4.7000E-03, 1.3000E-03, 2.5000E-04, 
            1.6000E-04, 5.9000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 
            4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 
            4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 
            4.1000E-02, 4.1000E-02, 4.1000E-02, 4.0900E-02, 4.0700E-02, 
            3.9900E-02, 3.8500E-02, 3.6300E-02, 3.3500E-02, 3.0200E-02, 
            2.3000E-02, 7.6000E-03, 2.3000E-03, 1.5000E-03, 1.1000E-03, 
            3.0000E-04, 2.8000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {4.4500E-02, 4.4500E-02, 4.4500E-02, 4.4500E-02, 
            4.4500E-02, 4.4500E-02, 4.4500E-02, 4.4500E-02, 4.4500E-02, 
            4.4500E-02, 4.4500E-02, 4.4500E-02, 4.4500E-02, 4.4500E-02, 
            4.4500E-02, 4.4400E-02, 4.4400E-02, 4.4300E-02, 4.3900E-02, 
            4.2800E-02, 4.0800E-02, 3.7900E-02, 3.4200E-02, 2.9900E-02, 
            2.1000E-02, 5.9000E-03, 2.1000E-03, 1.7000E-03, 9.8000E-04, 
            1.9000E-04, 1.1000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.8700E-02, 2.8700E-02, 2.8700E-02, 2.8700E-02, 
            2.8700E-02, 2.8700E-02, 2.8700E-02, 2.8700E-02, 2.8700E-02, 
            2.8700E-02, 2.8700E-02, 2.8700E-02, 2.8700E-02, 2.8700E-02, 
            2.8700E-02, 2.8700E-02, 2.8700E-02, 2.8700E-02, 2.8700E-02, 
            2.8700E-02, 2.8600E-02, 2.8300E-02, 2.7900E-02, 2.7100E-02, 
            2.5000E-02, 1.6000E-02, 8.5000E-03, 1.8000E-03, 3.8000E-04, 
            2.7000E-05, 5.7000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.9500E-02, 2.9500E-02, 2.9500E-02, 2.9500E-02, 
            2.9500E-02, 2.9500E-02, 2.9500E-02, 2.9500E-02, 2.9500E-02, 
            2.9500E-02, 2.9500E-02, 2.9500E-02, 2.9500E-02, 2.9500E-02, 
            2.9500E-02, 2.9500E-02, 2.9500E-02, 2.9500E-02, 2.9500E-02, 
            2.9400E-02, 2.9300E-02, 2.9000E-02, 2.8500E-02, 2.7700E-02, 
            2.5000E-02, 1.6000E-02, 8.1000E-03, 1.6000E-03, 3.2000E-04, 
            2.0000E-05, 3.2000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.4400E-01, 1.4400E-01, 1.4300E-01, 1.4300E-01, 
            1.4300E-01, 1.4200E-01, 1.4100E-01, 1.4000E-01, 1.3800E-01, 
            1.3600E-01, 1.3400E-01, 1.2900E-01, 1.2300E-01, 1.1600E-01, 
            1.0800E-01, 1.0100E-01, 9.2900E-02, 7.7100E-02, 5.5400E-02, 
            2.9700E-02, 1.7700E-02, 1.4400E-02, 1.4200E-02, 1.3700E-02, 
            9.6000E-03, 1.8000E-03, 1.3000E-03, 4.6000E-04, 7.9000E-05, 
            4.1000E-05, 1.5000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {9.0300E-02, 9.0300E-02, 9.0300E-02, 9.0300E-02, 
            9.0300E-02, 9.0300E-02, 9.0300E-02, 9.0300E-02, 9.0300E-02, 
            9.0300E-02, 9.0200E-02, 9.0100E-02, 8.9800E-02, 8.9300E-02, 
            8.8600E-02, 8.7600E-02, 8.6400E-02, 8.3000E-02, 7.5500E-02, 
            5.8000E-02, 3.9100E-02, 2.3600E-02, 1.3500E-02, 8.3200E-03, 
            5.9000E-03, 4.0000E-03, 1.1000E-03, 3.3000E-04, 2.7000E-04, 
            7.8000E-05, 7.3000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {9.7600E-02, 9.7600E-02, 9.7600E-02, 9.7600E-02, 
            9.7600E-02, 9.7600E-02, 9.7600E-02, 9.7500E-02, 9.7500E-02, 
            9.7500E-02, 9.7400E-02, 9.7100E-02, 9.6700E-02, 9.6000E-02, 
            9.5000E-02, 9.3700E-02, 9.2000E-02, 8.7300E-02, 7.7300E-02, 
            5.5800E-02, 3.4700E-02, 1.9400E-02, 1.0900E-02, 7.4100E-03, 
            6.4000E-03, 3.4000E-03, 7.9000E-04, 4.0000E-04, 2.5000E-04, 
            5.2000E-05, 2.9000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {7.3300E-02, 7.3300E-02, 7.3300E-02, 7.3300E-02, 
            7.3300E-02, 7.3300E-02, 7.3300E-02, 7.3300E-02, 7.3300E-02, 
            7.3300E-02, 7.3300E-02, 7.3300E-02, 7.3300E-02, 7.3300E-02, 
            7.3200E-02, 7.3100E-02, 7.2900E-02, 7.2200E-02, 7.0000E-02, 
            6.2600E-02, 5.0800E-02, 3.7400E-02, 2.5300E-02, 1.5900E-02, 
            5.9000E-03, 2.5000E-03, 2.0000E-03, 5.2000E-04, 1.1000E-04, 
            7.7000E-06, 1.6000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {7.5100E-02, 7.5100E-02, 7.5100E-02, 7.5100E-02, 
            7.5100E-02, 7.5100E-02, 7.5100E-02, 7.5100E-02, 7.5100E-02, 
            7.5100E-02, 7.5100E-02, 7.5100E-02, 7.5100E-02, 7.5000E-02, 
            7.5000E-02, 7.4800E-02, 7.4600E-02, 7.3800E-02, 7.1400E-02, 
            6.3100E-02, 5.0400E-02, 3.6400E-02, 2.4100E-02, 1.4900E-02, 
            5.4000E-03, 2.5000E-03, 1.9000E-03, 4.7000E-04, 9.5000E-05, 
            5.7000E-06, 8.8000E-08} );

    subshell_half_profiles[14] = 
      std::vector<double>( {6.2500E-02, 6.2500E-02, 6.2500E-02, 6.2500E-02, 
            6.2500E-02, 6.2500E-02, 6.2500E-02, 6.2500E-02, 6.2500E-02, 
            6.2500E-02, 6.2500E-02, 6.2500E-02, 6.2500E-02, 6.2500E-02, 
            6.2500E-02, 6.2400E-02, 6.2300E-02, 6.2000E-02, 6.1000E-02, 
            5.7000E-02, 5.0300E-02, 4.2000E-02, 3.3500E-02, 2.6000E-02, 
            1.5000E-02, 3.0000E-03, 6.4000E-04, 3.9000E-05, 3.6000E-06, 
            8.6000E-08, 5.6000E-10} );

    subshell_half_profiles[15] = 
      std::vector<double>( {6.3300E-02, 6.3300E-02, 6.3300E-02, 6.3300E-02, 
            6.3300E-02, 6.3300E-02, 6.3300E-02, 6.3300E-02, 6.3300E-02, 
            6.3300E-02, 6.3300E-02, 6.3300E-02, 6.3300E-02, 6.3300E-02, 
            6.3300E-02, 6.3200E-02, 6.3100E-02, 6.2800E-02, 6.1700E-02, 
            5.7500E-02, 5.0400E-02, 4.1800E-02, 3.3200E-02, 2.5600E-02, 
            1.4000E-02, 2.9000E-03, 6.0000E-04, 3.5000E-05, 3.1000E-06, 
            6.8000E-08, 3.7000E-10} );

    subshell_half_profiles[16] = 
      std::vector<double>( {3.3700E-01, 3.3700E-01, 3.3500E-01, 3.3300E-01, 
            3.2900E-01, 3.2000E-01, 3.0700E-01, 2.9200E-01, 2.7400E-01, 
            2.5400E-01, 2.3300E-01, 1.9100E-01, 1.5000E-01, 1.1400E-01, 
            8.5100E-02, 6.2900E-02, 4.7500E-02, 3.1800E-02, 2.7800E-02, 
            2.4200E-02, 1.3600E-02, 6.0300E-03, 3.3400E-03, 2.9400E-03, 
            2.6000E-03, 4.5000E-04, 2.7000E-04, 9.9000E-05, 1.6000E-05, 
            8.1000E-06, 3.0000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {2.2400E-01, 2.2400E-01, 2.2400E-01, 2.2400E-01, 
            2.2400E-01, 2.2300E-01, 2.2300E-01, 2.2200E-01, 2.2000E-01, 
            2.1800E-01, 2.1400E-01, 2.0400E-01, 1.8800E-01, 1.6900E-01, 
            1.4800E-01, 1.2500E-01, 1.0300E-01, 6.4300E-02, 2.8500E-02, 
            1.1900E-02, 1.1300E-02, 9.2200E-03, 5.8500E-03, 3.1700E-03, 
            1.1000E-03, 8.0000E-04, 2.4000E-04, 5.7000E-05, 4.7000E-05, 
            1.4000E-05, 1.3000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.4600E-01, 2.4600E-01, 2.4600E-01, 2.4600E-01, 
            2.4600E-01, 2.4600E-01, 2.4500E-01, 2.4300E-01, 2.4100E-01, 
            2.3700E-01, 2.3200E-01, 2.1600E-01, 1.9500E-01, 1.7000E-01, 
            1.4300E-01, 1.1600E-01, 9.1100E-02, 5.2100E-02, 2.1600E-02, 
            1.2000E-02, 1.1300E-02, 7.9300E-03, 4.3400E-03, 2.1800E-03, 
            1.1000E-03, 6.6000E-04, 1.6000E-04, 6.6000E-05, 4.3000E-05, 
            8.8000E-06, 4.9000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {2.3500E-01, 2.3500E-01, 2.3500E-01, 2.3500E-01, 
            2.3500E-01, 2.3500E-01, 2.3500E-01, 2.3400E-01, 2.3300E-01, 
            2.3100E-01, 2.2800E-01, 2.1700E-01, 2.0000E-01, 1.7900E-01, 
            1.5500E-01, 1.3100E-01, 1.0700E-01, 6.7800E-02, 2.9900E-02, 
            7.3100E-03, 4.2000E-03, 4.1000E-03, 3.4900E-03, 2.5100E-03, 
            9.6000E-04, 2.4000E-04, 2.1000E-04, 5.7000E-05, 1.3000E-05, 
            8.5000E-07, 1.7000E-08} );

    subshell_half_profiles[20] = 
      std::vector<double>( {2.4400E-01, 2.4400E-01, 2.4400E-01, 2.4400E-01, 
            2.4400E-01, 2.4400E-01, 2.4400E-01, 2.4300E-01, 2.4200E-01, 
            2.3900E-01, 2.3500E-01, 2.2300E-01, 2.0300E-01, 1.8000E-01, 
            1.5300E-01, 1.2700E-01, 1.0300E-01, 6.2900E-02, 2.6500E-02, 
            6.4500E-03, 4.1300E-03, 4.0100E-03, 3.2900E-03, 2.2800E-03, 
            8.3000E-04, 2.4000E-04, 1.9000E-04, 5.0000E-05, 1.0000E-05, 
            6.0000E-07, 9.4000E-09} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.1500E+00, 1.1300E+00, 1.0800E+00, 1.0100E+00, 
            9.1300E-01, 6.9300E-01, 4.7700E-01, 3.0400E-01, 1.8200E-01, 
            1.0800E-01, 6.8600E-02, 4.3700E-02, 4.2200E-02, 4.0200E-02, 
            3.4300E-02, 2.6500E-02, 1.8900E-02, 8.5500E-03, 3.3700E-03, 
            2.8600E-03, 1.8600E-03, 8.2000E-04, 3.8200E-04, 2.9700E-04, 
            2.7000E-04, 4.8000E-05, 2.7000E-05, 1.0000E-05, 1.6000E-06, 
            8.1000E-07, 3.0000E-07} );

    subshell_half_profiles[22] = 
      std::vector<double>( {9.1300E-01, 9.1300E-01, 9.1000E-01, 8.9900E-01, 
            8.7400E-01, 7.7100E-01, 6.1300E-01, 4.4400E-01, 2.9800E-01, 
            1.8900E-01, 1.1500E-01, 4.0100E-02, 1.6300E-02, 1.0600E-02, 
            1.0000E-02, 9.9000E-03, 9.2700E-03, 6.7300E-03, 3.0400E-03, 
            7.6500E-04, 6.0000E-04, 5.3100E-04, 3.5300E-04, 1.9400E-04, 
            6.4000E-05, 4.3000E-05, 1.3000E-05, 3.0000E-06, 2.5000E-06, 
            7.4000E-07, 6.8000E-08} );
  }
};

//! The default Compton profile generator implementation for A=82
template<>
struct DefaultComptonProfileGeneratorImpl<82u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 23 );

    subshell_half_profiles[0] = 
      std::vector<double>( {8.8200E-03, 8.8200E-03, 8.8200E-03, 8.8200E-03, 
            8.8200E-03, 8.8200E-03, 8.8200E-03, 8.8200E-03, 8.8200E-03, 
            8.8200E-03, 8.8200E-03, 8.8200E-03, 8.8200E-03, 8.8200E-03, 
            8.8100E-03, 8.8100E-03, 8.8100E-03, 8.8000E-03, 8.7900E-03, 
            8.7700E-03, 8.7400E-03, 8.7100E-03, 8.6600E-03, 8.6200E-03, 
            8.5000E-03, 8.1000E-03, 7.6000E-03, 6.5000E-03, 5.2000E-03, 
            3.1000E-03, 1.0000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.1400E-02, 3.1400E-02, 3.1400E-02, 3.1400E-02, 
            3.1400E-02, 3.1400E-02, 3.1400E-02, 3.1400E-02, 3.1400E-02, 
            3.1400E-02, 3.1300E-02, 3.1300E-02, 3.1200E-02, 3.1200E-02, 
            3.1100E-02, 3.1000E-02, 3.0900E-02, 3.0700E-02, 3.0300E-02, 
            2.9400E-02, 2.8400E-02, 2.7100E-02, 2.5700E-02, 2.4200E-02, 
            2.1000E-02, 1.3000E-02, 6.9000E-03, 1.6000E-03, 7.9000E-04, 
            7.0000E-04, 2.4000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.5300E-02, 1.5300E-02, 1.5300E-02, 1.5300E-02, 
            1.5300E-02, 1.5300E-02, 1.5300E-02, 1.5300E-02, 1.5300E-02, 
            1.5300E-02, 1.5300E-02, 1.5300E-02, 1.5300E-02, 1.5300E-02, 
            1.5300E-02, 1.5300E-02, 1.5300E-02, 1.5300E-02, 1.5300E-02, 
            1.5300E-02, 1.5200E-02, 1.5200E-02, 1.5200E-02, 1.5100E-02, 
            1.5000E-02, 1.4000E-02, 1.2000E-02, 7.3000E-03, 3.9000E-03, 
            1.0000E-03, 1.1000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.7400E-02, 1.7400E-02, 1.7400E-02, 1.7400E-02, 
            1.7400E-02, 1.7400E-02, 1.7400E-02, 1.7400E-02, 1.7400E-02, 
            1.7400E-02, 1.7400E-02, 1.7400E-02, 1.7400E-02, 1.7400E-02, 
            1.7400E-02, 1.7400E-02, 1.7400E-02, 1.7400E-02, 1.7400E-02, 
            1.7400E-02, 1.7300E-02, 1.7300E-02, 1.7200E-02, 1.7100E-02, 
            1.7000E-02, 1.5000E-02, 1.2000E-02, 6.7000E-03, 3.1000E-03, 
            6.1000E-04, 3.8000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {6.8900E-02, 6.8900E-02, 6.8900E-02, 6.8900E-02, 
            6.8900E-02, 6.8800E-02, 6.8700E-02, 6.8500E-02, 6.8400E-02, 
            6.8200E-02, 6.7900E-02, 6.7400E-02, 6.6700E-02, 6.5900E-02, 
            6.5000E-02, 6.4000E-02, 6.2800E-02, 6.0300E-02, 5.6000E-02, 
            4.7700E-02, 3.9000E-02, 3.0600E-02, 2.3300E-02, 1.7200E-02, 
            9.5000E-03, 5.3000E-03, 4.7000E-03, 1.4000E-03, 2.7000E-04, 
            1.6000E-04, 6.1000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {4.0300E-02, 4.0300E-02, 4.0300E-02, 4.0300E-02, 
            4.0300E-02, 4.0300E-02, 4.0300E-02, 4.0300E-02, 4.0300E-02, 
            4.0300E-02, 4.0300E-02, 4.0300E-02, 4.0300E-02, 4.0300E-02, 
            4.0300E-02, 4.0300E-02, 4.0300E-02, 4.0200E-02, 4.0000E-02, 
            3.9200E-02, 3.7900E-02, 3.5900E-02, 3.3300E-02, 3.0100E-02, 
            2.3000E-02, 8.0000E-03, 2.4000E-03, 1.5000E-03, 1.1000E-03, 
            3.2000E-04, 3.1000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {4.3800E-02, 4.3800E-02, 4.3800E-02, 4.3800E-02, 
            4.3800E-02, 4.3800E-02, 4.3800E-02, 4.3800E-02, 4.3800E-02, 
            4.3800E-02, 4.3800E-02, 4.3800E-02, 4.3800E-02, 4.3800E-02, 
            4.3800E-02, 4.3800E-02, 4.3700E-02, 4.3600E-02, 4.3300E-02, 
            4.2200E-02, 4.0300E-02, 3.7600E-02, 3.4100E-02, 3.0000E-02, 
            2.1000E-02, 6.2000E-03, 2.1000E-03, 1.7000E-03, 1.0000E-03, 
            2.1000E-04, 1.2000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.8300E-02, 2.8300E-02, 2.8300E-02, 2.8300E-02, 
            2.8300E-02, 2.8300E-02, 2.8300E-02, 2.8300E-02, 2.8300E-02, 
            2.8300E-02, 2.8300E-02, 2.8300E-02, 2.8300E-02, 2.8300E-02, 
            2.8300E-02, 2.8300E-02, 2.8300E-02, 2.8300E-02, 2.8300E-02, 
            2.8200E-02, 2.8100E-02, 2.7900E-02, 2.7500E-02, 2.6800E-02, 
            2.5000E-02, 1.6000E-02, 8.8000E-03, 1.9000E-03, 4.2000E-04, 
            2.9000E-05, 6.4000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.9000E-02, 2.9000E-02, 2.9000E-02, 2.9000E-02, 
            2.9000E-02, 2.9000E-02, 2.9000E-02, 2.9000E-02, 2.9000E-02, 
            2.9000E-02, 2.9000E-02, 2.9000E-02, 2.9000E-02, 2.9000E-02, 
            2.9000E-02, 2.9000E-02, 2.9000E-02, 2.9000E-02, 2.9000E-02, 
            2.9000E-02, 2.8900E-02, 2.8600E-02, 2.8100E-02, 2.7400E-02, 
            2.5000E-02, 1.6000E-02, 8.3000E-03, 1.7000E-03, 3.5000E-04, 
            2.2000E-05, 3.6000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.4100E-01, 1.4100E-01, 1.4000E-01, 1.4000E-01, 
            1.4000E-01, 1.3900E-01, 1.3800E-01, 1.3700E-01, 1.3500E-01, 
            1.3300E-01, 1.3100E-01, 1.2600E-01, 1.2100E-01, 1.1400E-01, 
            1.0700E-01, 1.0000E-01, 9.2500E-02, 7.7300E-02, 5.6200E-02, 
            3.0600E-02, 1.8100E-02, 1.4400E-02, 1.4000E-02, 1.3600E-02, 
            9.9000E-03, 1.9000E-03, 1.3000E-03, 5.0000E-04, 8.6000E-05, 
            4.1000E-05, 1.6000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {8.8400E-02, 8.8400E-02, 8.8400E-02, 8.8400E-02, 
            8.8400E-02, 8.8400E-02, 8.8400E-02, 8.8400E-02, 8.8400E-02, 
            8.8400E-02, 8.8300E-02, 8.8200E-02, 8.7900E-02, 8.7500E-02, 
            8.6900E-02, 8.6000E-02, 8.4900E-02, 8.1800E-02, 7.4800E-02, 
            5.8400E-02, 4.0100E-02, 2.4600E-02, 1.4300E-02, 8.7300E-03, 
            5.8000E-03, 4.2000E-03, 1.3000E-03, 3.3000E-04, 2.7000E-04, 
            8.3000E-05, 8.0000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {9.5700E-02, 9.5700E-02, 9.5700E-02, 9.5700E-02, 
            9.5700E-02, 9.5700E-02, 9.5700E-02, 9.5700E-02, 9.5600E-02, 
            9.5600E-02, 9.5500E-02, 9.5300E-02, 9.4900E-02, 9.4300E-02, 
            9.3400E-02, 9.2100E-02, 9.0500E-02, 8.6200E-02, 7.6900E-02, 
            5.6400E-02, 3.5800E-02, 2.0400E-02, 1.1500E-02, 7.6000E-03, 
            6.4000E-03, 3.5000E-03, 8.6000E-04, 4.0000E-04, 2.6000E-04, 
            5.5000E-05, 3.2000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {7.1800E-02, 7.1800E-02, 7.1800E-02, 7.1800E-02, 
            7.1800E-02, 7.1800E-02, 7.1800E-02, 7.1800E-02, 7.1800E-02, 
            7.1800E-02, 7.1800E-02, 7.1800E-02, 7.1700E-02, 7.1700E-02, 
            7.1700E-02, 7.1600E-02, 7.1400E-02, 7.0800E-02, 6.8900E-02, 
            6.2100E-02, 5.1100E-02, 3.8300E-02, 2.6300E-02, 1.6900E-02, 
            6.3000E-03, 2.4000E-03, 2.0000E-03, 5.6000E-04, 1.2000E-04, 
            8.6000E-06, 1.8000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {7.3500E-02, 7.3500E-02, 7.3500E-02, 7.3500E-02, 
            7.3500E-02, 7.3500E-02, 7.3500E-02, 7.3500E-02, 7.3500E-02, 
            7.3500E-02, 7.3500E-02, 7.3500E-02, 7.3500E-02, 7.3500E-02, 
            7.3400E-02, 7.3300E-02, 7.3100E-02, 7.2400E-02, 7.0200E-02, 
            6.2700E-02, 5.0800E-02, 3.7300E-02, 2.5100E-02, 1.5800E-02, 
            5.8000E-03, 2.5000E-03, 2.0000E-03, 5.0000E-04, 1.0000E-04, 
            6.3000E-06, 1.0000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {6.0600E-02, 6.0600E-02, 6.0600E-02, 6.0600E-02, 
            6.0600E-02, 6.0600E-02, 6.0600E-02, 6.0600E-02, 6.0600E-02, 
            6.0600E-02, 6.0600E-02, 6.0600E-02, 6.0600E-02, 6.0600E-02, 
            6.0600E-02, 6.0600E-02, 6.0500E-02, 6.0300E-02, 5.9500E-02, 
            5.6100E-02, 5.0100E-02, 4.2400E-02, 3.4300E-02, 2.6900E-02, 
            1.5000E-02, 3.3000E-03, 7.2000E-04, 4.5000E-05, 4.3000E-06, 
            1.0000E-07, 6.8000E-10} );

    subshell_half_profiles[15] = 
      std::vector<double>( {6.1400E-02, 6.1400E-02, 6.1400E-02, 6.1400E-02, 
            6.1400E-02, 6.1400E-02, 6.1400E-02, 6.1400E-02, 6.1400E-02, 
            6.1400E-02, 6.1400E-02, 6.1400E-02, 6.1400E-02, 6.1400E-02, 
            6.1400E-02, 6.1400E-02, 6.1300E-02, 6.1100E-02, 6.0200E-02, 
            5.6600E-02, 5.0200E-02, 4.2300E-02, 3.4000E-02, 2.6500E-02, 
            1.5000E-02, 3.2000E-03, 6.7000E-04, 4.0000E-05, 3.7000E-06, 
            8.1000E-08, 4.4000E-10} );

    subshell_half_profiles[16] = 
      std::vector<double>( {3.2500E-01, 3.2500E-01, 3.2300E-01, 3.2100E-01, 
            3.1800E-01, 3.1000E-01, 2.9800E-01, 2.8400E-01, 2.6700E-01, 
            2.4900E-01, 2.3000E-01, 1.9100E-01, 1.5200E-01, 1.1700E-01, 
            8.8600E-02, 6.6200E-02, 5.0100E-02, 3.2900E-02, 2.7600E-02, 
            2.4800E-02, 1.4800E-02, 6.7300E-03, 3.5500E-03, 2.9800E-03, 
            2.7000E-03, 5.0000E-04, 2.7000E-04, 1.1000E-04, 1.9000E-05, 
            8.3000E-06, 3.2000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {2.1500E-01, 2.1500E-01, 2.1500E-01, 2.1500E-01, 
            2.1500E-01, 2.1500E-01, 2.1400E-01, 2.1400E-01, 2.1200E-01, 
            2.1000E-01, 2.0700E-01, 1.9800E-01, 1.8500E-01, 1.6800E-01, 
            1.4800E-01, 1.2700E-01, 1.0600E-01, 6.8800E-02, 3.1600E-02, 
            1.2400E-02, 1.1400E-02, 9.7300E-03, 6.4400E-03, 3.6000E-03, 
            1.2000E-03, 8.5000E-04, 2.8000E-04, 5.8000E-05, 5.0000E-05, 
            1.5000E-05, 1.5000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.3700E-01, 2.3700E-01, 2.3700E-01, 2.3700E-01, 
            2.3700E-01, 2.3600E-01, 2.3600E-01, 2.3500E-01, 2.3200E-01, 
            2.2900E-01, 2.2500E-01, 2.1100E-01, 1.9300E-01, 1.7000E-01, 
            1.4500E-01, 1.2000E-01, 9.5600E-02, 5.6500E-02, 2.3900E-02, 
            1.2200E-02, 1.1600E-02, 8.5400E-03, 4.8500E-03, 2.4700E-03, 
            1.1000E-03, 7.2000E-04, 1.8000E-04, 6.9000E-05, 4.6000E-05, 
            9.7000E-06, 5.5000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {2.2100E-01, 2.2100E-01, 2.2100E-01, 2.2100E-01, 
            2.2100E-01, 2.2100E-01, 2.2100E-01, 2.2100E-01, 2.2000E-01, 
            2.1900E-01, 2.1600E-01, 2.0800E-01, 1.9600E-01, 1.7800E-01, 
            1.5800E-01, 1.3600E-01, 1.1400E-01, 7.4900E-02, 3.5000E-02, 
            8.7500E-03, 4.5100E-03, 4.3500E-03, 3.8300E-03, 2.8500E-03, 
            1.1000E-03, 2.6000E-04, 2.3000E-04, 6.7000E-05, 1.5000E-05, 
            1.0000E-06, 2.1000E-08} );

    subshell_half_profiles[20] = 
      std::vector<double>( {2.2700E-01, 2.2700E-01, 2.2700E-01, 2.2700E-01, 
            2.2700E-01, 2.2700E-01, 2.2700E-01, 2.2700E-01, 2.2600E-01, 
            2.2500E-01, 2.2200E-01, 2.1300E-01, 1.9900E-01, 1.8000E-01, 
            1.5800E-01, 1.3400E-01, 1.1100E-01, 7.1100E-02, 3.1800E-02, 
            7.7800E-03, 4.4600E-03, 4.3400E-03, 3.6900E-03, 2.6400E-03, 
            1.0000E-03, 2.6000E-04, 2.2000E-04, 5.9000E-05, 1.2000E-05, 
            7.4000E-07, 1.2000E-08} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.0400E+00, 1.0300E+00, 9.9200E-01, 9.3400E-01, 
            8.5900E-01, 6.7900E-01, 4.9400E-01, 3.3400E-01, 2.1400E-01, 
            1.3300E-01, 8.4800E-02, 4.8500E-02, 4.4200E-02, 4.3400E-02, 
            3.8900E-02, 3.1500E-02, 2.3600E-02, 1.1300E-02, 4.1200E-03, 
            3.2500E-03, 2.2700E-03, 1.0500E-03, 4.7600E-04, 3.4200E-04, 
            3.1000E-04, 6.0000E-05, 3.0000E-05, 1.2000E-05, 2.1000E-06, 
            9.3000E-07, 3.6000E-07} );

    subshell_half_profiles[22] = 
      std::vector<double>( {8.0800E-01, 8.0800E-01, 8.0600E-01, 8.0000E-01, 
            7.8500E-01, 7.1900E-01, 6.0800E-01, 4.7400E-01, 3.4500E-01, 
            2.3700E-01, 1.5600E-01, 6.2300E-02, 2.5400E-02, 1.4200E-02, 
            1.1900E-02, 1.1800E-02, 1.1500E-02, 9.0400E-03, 4.4500E-03, 
            1.0900E-03, 7.5700E-04, 6.9700E-04, 4.8900E-04, 2.7900E-04, 
            8.8000E-05, 5.7000E-05, 1.9000E-05, 3.9000E-06, 3.3000E-06, 
            1.0000E-06, 9.8000E-08} );
  }
};

//! The default Compton profile generator implementation for A=83
template<>
struct DefaultComptonProfileGeneratorImpl<83u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 24 );

    subshell_half_profiles[0] = 
      std::vector<double>( {8.6700E-03, 8.6700E-03, 8.6700E-03, 8.6700E-03, 
            8.6700E-03, 8.6700E-03, 8.6700E-03, 8.6700E-03, 8.6700E-03, 
            8.6700E-03, 8.6700E-03, 8.6700E-03, 8.6700E-03, 8.6600E-03, 
            8.6600E-03, 8.6600E-03, 8.6600E-03, 8.6500E-03, 8.6400E-03, 
            8.6200E-03, 8.5900E-03, 8.5600E-03, 8.5200E-03, 8.4700E-03, 
            8.4000E-03, 8.0000E-03, 7.5000E-03, 6.4000E-03, 5.2000E-03, 
            3.1000E-03, 1.0000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.0900E-02, 3.0900E-02, 3.0900E-02, 3.0900E-02, 
            3.0900E-02, 3.0900E-02, 3.0900E-02, 3.0900E-02, 3.0900E-02, 
            3.0800E-02, 3.0800E-02, 3.0800E-02, 3.0700E-02, 3.0700E-02, 
            3.0600E-02, 3.0500E-02, 3.0400E-02, 3.0200E-02, 2.9800E-02, 
            2.9000E-02, 2.8000E-02, 2.6800E-02, 2.5500E-02, 2.4000E-02, 
            2.1000E-02, 1.3000E-02, 7.1000E-03, 1.7000E-03, 7.9000E-04, 
            7.0000E-04, 2.5000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.5000E-02, 1.5000E-02, 1.5000E-02, 1.5000E-02, 
            1.5000E-02, 1.5000E-02, 1.5000E-02, 1.5000E-02, 1.5000E-02, 
            1.5000E-02, 1.5000E-02, 1.5000E-02, 1.5000E-02, 1.5000E-02, 
            1.5000E-02, 1.5000E-02, 1.5000E-02, 1.5000E-02, 1.5000E-02, 
            1.5000E-02, 1.5000E-02, 1.4900E-02, 1.4900E-02, 1.4800E-02, 
            1.4800E-02, 1.4000E-02, 1.2000E-02, 7.4000E-03, 4.0000E-03, 
            1.1000E-03, 1.1000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.7100E-02, 1.7100E-02, 1.7100E-02, 1.7100E-02, 
            1.7100E-02, 1.7100E-02, 1.7100E-02, 1.7100E-02, 1.7100E-02, 
            1.7100E-02, 1.7100E-02, 1.7100E-02, 1.7100E-02, 1.7100E-02, 
            1.7100E-02, 1.7100E-02, 1.7100E-02, 1.7100E-02, 1.7100E-02, 
            1.7100E-02, 1.7100E-02, 1.7000E-02, 1.7000E-02, 1.6900E-02, 
            1.6900E-02, 1.5000E-02, 1.2000E-02, 6.8000E-03, 3.2000E-03, 
            6.4000E-04, 4.1000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {6.7800E-02, 6.7800E-02, 6.7800E-02, 6.7700E-02, 
            6.7700E-02, 6.7600E-02, 6.7500E-02, 6.7400E-02, 6.7200E-02, 
            6.7000E-02, 6.6800E-02, 6.6300E-02, 6.5600E-02, 6.4900E-02, 
            6.4000E-02, 6.3000E-02, 6.2000E-02, 5.9600E-02, 5.5400E-02, 
            4.7500E-02, 3.9000E-02, 3.0900E-02, 2.3600E-02, 1.7700E-02, 
            9.8000E-03, 5.2000E-03, 4.7000E-03, 1.5000E-03, 2.9000E-04, 
            1.6000E-04, 6.4000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.9600E-02, 3.9600E-02, 3.9600E-02, 3.9600E-02, 
            3.9600E-02, 3.9600E-02, 3.9600E-02, 3.9600E-02, 3.9600E-02, 
            3.9600E-02, 3.9600E-02, 3.9600E-02, 3.9600E-02, 3.9600E-02, 
            3.9600E-02, 3.9600E-02, 3.9600E-02, 3.9500E-02, 3.9300E-02, 
            3.8600E-02, 3.7400E-02, 3.5500E-02, 3.3100E-02, 3.0100E-02, 
            2.3000E-02, 8.4000E-03, 2.5000E-03, 1.5000E-03, 1.1000E-03, 
            3.4000E-04, 3.4000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {4.3200E-02, 4.3200E-02, 4.3200E-02, 4.3200E-02, 
            4.3200E-02, 4.3200E-02, 4.3200E-02, 4.3200E-02, 4.3200E-02, 
            4.3200E-02, 4.3200E-02, 4.3200E-02, 4.3200E-02, 4.3100E-02, 
            4.3100E-02, 4.3100E-02, 4.3100E-02, 4.2900E-02, 4.2600E-02, 
            4.1700E-02, 3.9900E-02, 3.7300E-02, 3.4000E-02, 3.0100E-02, 
            2.2000E-02, 6.5000E-03, 2.2000E-03, 1.7000E-03, 1.0000E-03, 
            2.2000E-04, 1.3000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 
            2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 
            2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 
            2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 
            2.7800E-02, 2.7700E-02, 2.7500E-02, 2.7100E-02, 2.6500E-02, 
            2.5000E-02, 1.7000E-02, 9.0000E-03, 2.0000E-03, 4.5000E-04, 
            3.2000E-05, 7.1000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.8600E-02, 2.8600E-02, 2.8600E-02, 2.8600E-02, 
            2.8600E-02, 2.8600E-02, 2.8600E-02, 2.8600E-02, 2.8600E-02, 
            2.8600E-02, 2.8600E-02, 2.8600E-02, 2.8600E-02, 2.8600E-02, 
            2.8600E-02, 2.8600E-02, 2.8600E-02, 2.8600E-02, 2.8600E-02, 
            2.8600E-02, 2.8500E-02, 2.8200E-02, 2.7800E-02, 2.7100E-02, 
            2.5000E-02, 1.6000E-02, 8.6000E-03, 1.8000E-03, 3.7000E-04, 
            2.4000E-05, 4.0000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.3800E-01, 1.3800E-01, 1.3800E-01, 1.3700E-01, 
            1.3700E-01, 1.3600E-01, 1.3500E-01, 1.3400E-01, 1.3300E-01, 
            1.3100E-01, 1.2900E-01, 1.2400E-01, 1.1900E-01, 1.1300E-01, 
            1.0600E-01, 9.9300E-02, 9.2100E-02, 7.7500E-02, 5.6900E-02, 
            3.1400E-02, 1.8500E-02, 1.4300E-02, 1.3800E-02, 1.3600E-02, 
            1.0000E-02, 2.0000E-03, 1.3000E-03, 5.3000E-04, 9.5000E-05, 
            4.1000E-05, 1.7000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {8.6600E-02, 8.6600E-02, 8.6600E-02, 8.6600E-02, 
            8.6600E-02, 8.6600E-02, 8.6600E-02, 8.6600E-02, 8.6600E-02, 
            8.6500E-02, 8.6500E-02, 8.6400E-02, 8.6100E-02, 8.5700E-02, 
            8.5200E-02, 8.4400E-02, 8.3400E-02, 8.0500E-02, 7.4100E-02, 
            5.8600E-02, 4.1000E-02, 2.5700E-02, 1.5100E-02, 9.1800E-03, 
            5.8000E-03, 4.3000E-03, 1.4000E-03, 3.3000E-04, 2.8000E-04, 
            8.9000E-05, 8.8000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {9.3900E-02, 9.3900E-02, 9.3900E-02, 9.3900E-02, 
            9.3900E-02, 9.3900E-02, 9.3900E-02, 9.3800E-02, 9.3800E-02, 
            9.3800E-02, 9.3700E-02, 9.3500E-02, 9.3100E-02, 9.2600E-02, 
            9.1700E-02, 9.0600E-02, 8.9100E-02, 8.5100E-02, 7.6400E-02, 
            5.6900E-02, 3.6800E-02, 2.1300E-02, 1.2100E-02, 7.8200E-03, 
            6.3000E-03, 3.7000E-03, 9.3000E-04, 4.0000E-04, 2.7000E-04, 
            5.9000E-05, 3.5000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {7.0300E-02, 7.0300E-02, 7.0300E-02, 7.0300E-02, 
            7.0300E-02, 7.0300E-02, 7.0300E-02, 7.0300E-02, 7.0300E-02, 
            7.0300E-02, 7.0300E-02, 7.0300E-02, 7.0200E-02, 7.0200E-02, 
            7.0200E-02, 7.0100E-02, 6.9900E-02, 6.9400E-02, 6.7700E-02, 
            6.1500E-02, 5.1300E-02, 3.9000E-02, 2.7300E-02, 1.7800E-02, 
            6.8000E-03, 2.4000E-03, 2.1000E-03, 5.9000E-04, 1.4000E-04, 
            9.6000E-06, 2.0000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {7.2000E-02, 7.2000E-02, 7.2000E-02, 7.2000E-02, 
            7.2000E-02, 7.2000E-02, 7.2000E-02, 7.2000E-02, 7.2000E-02, 
            7.2000E-02, 7.2000E-02, 7.2000E-02, 7.2000E-02, 7.2000E-02, 
            7.1900E-02, 7.1800E-02, 7.1600E-02, 7.1000E-02, 6.9100E-02, 
            6.2200E-02, 5.1100E-02, 3.8100E-02, 2.6100E-02, 1.6700E-02, 
            6.2000E-03, 2.5000E-03, 2.0000E-03, 5.3000E-04, 1.1000E-04, 
            7.1000E-06, 1.1000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {5.8900E-02, 5.8900E-02, 5.8900E-02, 5.8900E-02, 
            5.8900E-02, 5.8900E-02, 5.8900E-02, 5.8900E-02, 5.8900E-02, 
            5.8900E-02, 5.8900E-02, 5.8900E-02, 5.8900E-02, 5.8900E-02, 
            5.8900E-02, 5.8900E-02, 5.8800E-02, 5.8600E-02, 5.8000E-02, 
            5.5100E-02, 4.9800E-02, 4.2700E-02, 3.5000E-02, 2.7700E-02, 
            1.6000E-02, 3.6000E-03, 8.0000E-04, 5.1000E-05, 5.0000E-06, 
            1.2000E-07, 8.1000E-10} );

    subshell_half_profiles[15] = 
      std::vector<double>( {5.9700E-02, 5.9700E-02, 5.9700E-02, 5.9700E-02, 
            5.9700E-02, 5.9700E-02, 5.9700E-02, 5.9700E-02, 5.9700E-02, 
            5.9700E-02, 5.9700E-02, 5.9700E-02, 5.9700E-02, 5.9700E-02, 
            5.9600E-02, 5.9600E-02, 5.9600E-02, 5.9400E-02, 5.8700E-02, 
            5.5600E-02, 5.0000E-02, 4.2600E-02, 3.4800E-02, 2.7400E-02, 
            1.6000E-02, 3.5000E-03, 7.5000E-04, 4.6000E-05, 4.3000E-06, 
            9.6000E-08, 5.3000E-10} );

    subshell_half_profiles[16] = 
      std::vector<double>( {3.1400E-01, 3.1300E-01, 3.1200E-01, 3.1000E-01, 
            3.0700E-01, 3.0000E-01, 2.8900E-01, 2.7600E-01, 2.6100E-01, 
            2.4500E-01, 2.2700E-01, 1.9000E-01, 1.5300E-01, 1.2000E-01, 
            9.1900E-02, 6.9500E-02, 5.2800E-02, 3.4100E-02, 2.7500E-02, 
            2.5300E-02, 1.5900E-02, 7.4800E-03, 3.8200E-03, 3.0200E-03, 
            2.8000E-03, 5.6000E-04, 2.7000E-04, 1.2000E-04, 2.1000E-05, 
            8.4000E-06, 3.5000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {2.0700E-01, 2.0700E-01, 2.0700E-01, 2.0700E-01, 
            2.0700E-01, 2.0700E-01, 2.0700E-01, 2.0600E-01, 2.0500E-01, 
            2.0300E-01, 2.0100E-01, 1.9300E-01, 1.8100E-01, 1.6600E-01, 
            1.4900E-01, 1.2900E-01, 1.0900E-01, 7.2900E-02, 3.4700E-02, 
            1.2900E-02, 1.1500E-02, 1.0200E-02, 7.0200E-03, 4.0500E-03, 
            1.3000E-03, 8.9000E-04, 3.1000E-04, 6.0000E-05, 5.2000E-05, 
            1.7000E-05, 1.7000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.2800E-01, 2.2800E-01, 2.2800E-01, 2.2800E-01, 
            2.2800E-01, 2.2800E-01, 2.2700E-01, 2.2600E-01, 2.2400E-01, 
            2.2200E-01, 2.1800E-01, 2.0600E-01, 1.9000E-01, 1.7000E-01, 
            1.4700E-01, 1.2300E-01, 9.9700E-02, 6.0900E-02, 2.6400E-02, 
            1.2500E-02, 1.1900E-02, 9.1400E-03, 5.3900E-03, 2.7900E-03, 
            1.2000E-03, 7.8000E-04, 2.0000E-04, 7.1000E-05, 4.9000E-05, 
            1.1000E-05, 6.3000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {2.0800E-01, 2.0800E-01, 2.0800E-01, 2.0800E-01, 
            2.0800E-01, 2.0800E-01, 2.0800E-01, 2.0800E-01, 2.0800E-01, 
            2.0700E-01, 2.0500E-01, 2.0000E-01, 1.9000E-01, 1.7600E-01, 
            1.5900E-01, 1.3900E-01, 1.2000E-01, 8.1900E-02, 4.0400E-02, 
            1.0500E-02, 4.8700E-03, 4.6000E-03, 4.1800E-03, 3.2100E-03, 
            1.3000E-03, 2.8000E-04, 2.5000E-04, 7.7000E-05, 1.8000E-05, 
            1.3000E-06, 2.6000E-08} );

    subshell_half_profiles[20] = 
      std::vector<double>( {2.1400E-01, 2.1400E-01, 2.1400E-01, 2.1400E-01, 
            2.1400E-01, 2.1400E-01, 2.1400E-01, 2.1400E-01, 2.1400E-01, 
            2.1300E-01, 2.1100E-01, 2.0500E-01, 1.9400E-01, 1.7800E-01, 
            1.5900E-01, 1.3900E-01, 1.1700E-01, 7.8300E-02, 3.7000E-02, 
            9.3000E-03, 4.7800E-03, 4.6100E-03, 4.0500E-03, 3.0000E-03, 
            1.2000E-03, 2.8000E-04, 2.4000E-04, 6.8000E-05, 1.5000E-05, 
            9.0000E-07, 1.4000E-08} );

    subshell_half_profiles[21] = 
      std::vector<double>( {9.5500E-01, 9.4500E-01, 9.1600E-01, 8.7000E-01, 
            8.0900E-01, 6.6100E-01, 5.0100E-01, 3.5600E-01, 2.4000E-01, 
            1.5600E-01, 1.0200E-01, 5.4400E-02, 4.5800E-02, 4.5400E-02, 
            4.2500E-02, 3.6100E-02, 2.8200E-02, 1.4300E-02, 5.0600E-03, 
            3.5900E-03, 2.6900E-03, 1.3200E-03, 5.8700E-04, 3.8900E-04, 
            3.6000E-04, 7.5000E-05, 3.4000E-05, 1.5000E-05, 2.6000E-06, 
            1.0000E-06, 4.3000E-07} );

    subshell_half_profiles[22] = 
      std::vector<double>( {7.1300E-01, 7.1300E-01, 7.1200E-01, 7.0900E-01, 
            7.0000E-01, 6.6000E-01, 5.8600E-01, 4.8700E-01, 3.8100E-01, 
            2.8200E-01, 1.9900E-01, 9.0000E-02, 3.8900E-02, 1.9700E-02, 
            1.4500E-02, 1.3800E-02, 1.3700E-02, 1.1600E-02, 6.2600E-03, 
            1.5400E-03, 9.3700E-04, 8.8900E-04, 6.5600E-04, 3.8900E-04, 
            1.2000E-04, 7.4000E-05, 2.6000E-05, 4.9000E-06, 4.3000E-06, 
            1.4000E-06, 1.4000E-07} );

    subshell_half_profiles[23] = 
      std::vector<double>( {8.3200E-01, 8.3200E-01, 8.3000E-01, 8.2300E-01, 
            8.0700E-01, 7.3300E-01, 6.1200E-01, 4.6800E-01, 3.3300E-01, 
            2.2300E-01, 1.4200E-01, 5.3800E-02, 2.2400E-02, 1.4300E-02, 
            1.3300E-02, 1.3100E-02, 1.2300E-02, 8.8000E-03, 3.7700E-03, 
            9.8100E-04, 8.3900E-04, 6.9600E-04, 4.2800E-04, 2.2100E-04, 
            8.2000E-05, 5.5000E-05, 1.4000E-05, 4.9000E-06, 3.4000E-06, 
            7.4000E-07, 4.3000E-08} );
  }
};

//! The default Compton profile generator implementation for A=84
template<>
struct DefaultComptonProfileGeneratorImpl<84u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 24 );

    subshell_half_profiles[0] = 
      std::vector<double>( {8.5200E-03, 8.5200E-03, 8.5200E-03, 8.5200E-03, 
            8.5200E-03, 8.5200E-03, 8.5200E-03, 8.5200E-03, 8.5200E-03, 
            8.5200E-03, 8.5200E-03, 8.5200E-03, 8.5200E-03, 8.5200E-03, 
            8.5100E-03, 8.5100E-03, 8.5100E-03, 8.5100E-03, 8.5000E-03, 
            8.4800E-03, 8.4500E-03, 8.4200E-03, 8.3800E-03, 8.3400E-03, 
            8.2000E-03, 7.9000E-03, 7.4000E-03, 6.4000E-03, 5.2000E-03, 
            3.2000E-03, 1.1000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 
            3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 3.0400E-02, 
            3.0300E-02, 3.0300E-02, 3.0300E-02, 3.0200E-02, 3.0200E-02, 
            3.0100E-02, 3.0000E-02, 2.9900E-02, 2.9700E-02, 2.9400E-02, 
            2.8600E-02, 2.7600E-02, 2.6500E-02, 2.5200E-02, 2.3800E-02, 
            2.1000E-02, 1.3000E-02, 7.3000E-03, 1.8000E-03, 7.9000E-04, 
            6.9000E-04, 2.6000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.4700E-02, 1.4700E-02, 1.4700E-02, 1.4700E-02, 
            1.4700E-02, 1.4700E-02, 1.4700E-02, 1.4700E-02, 1.4700E-02, 
            1.4700E-02, 1.4700E-02, 1.4700E-02, 1.4700E-02, 1.4700E-02, 
            1.4700E-02, 1.4700E-02, 1.4700E-02, 1.4700E-02, 1.4700E-02, 
            1.4700E-02, 1.4700E-02, 1.4700E-02, 1.4600E-02, 1.4600E-02, 
            1.4000E-02, 1.3000E-02, 1.2000E-02, 7.5000E-03, 4.1000E-03, 
            1.1000E-03, 1.2000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.6900E-02, 1.6900E-02, 1.6900E-02, 1.6900E-02, 
            1.6900E-02, 1.6900E-02, 1.6900E-02, 1.6900E-02, 1.6900E-02, 
            1.6900E-02, 1.6900E-02, 1.6900E-02, 1.6900E-02, 1.6900E-02, 
            1.6900E-02, 1.6900E-02, 1.6900E-02, 1.6900E-02, 1.6900E-02, 
            1.6900E-02, 1.6900E-02, 1.6800E-02, 1.6700E-02, 1.6600E-02, 
            1.6000E-02, 1.5000E-02, 1.2000E-02, 6.9000E-03, 3.3000E-03, 
            6.7000E-04, 4.4000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {6.6600E-02, 6.6600E-02, 6.6600E-02, 6.6600E-02, 
            6.6600E-02, 6.6500E-02, 6.6400E-02, 6.6300E-02, 6.6100E-02, 
            6.5900E-02, 6.5700E-02, 6.5200E-02, 6.4600E-02, 6.3900E-02, 
            6.3000E-02, 6.2100E-02, 6.1100E-02, 5.8800E-02, 5.4800E-02, 
            4.7200E-02, 3.9100E-02, 3.1100E-02, 2.4000E-02, 1.8100E-02, 
            1.0000E-02, 5.1000E-03, 4.7000E-03, 1.6000E-03, 3.1000E-04, 
            1.6000E-04, 6.7000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.9000E-02, 3.9000E-02, 3.9000E-02, 3.9000E-02, 
            3.9000E-02, 3.9000E-02, 3.9000E-02, 3.9000E-02, 3.9000E-02, 
            3.9000E-02, 3.9000E-02, 3.9000E-02, 3.8900E-02, 3.8900E-02, 
            3.8900E-02, 3.8900E-02, 3.8900E-02, 3.8800E-02, 3.8600E-02, 
            3.8000E-02, 3.6900E-02, 3.5200E-02, 3.2800E-02, 3.0000E-02, 
            2.3000E-02, 8.8000E-03, 2.7000E-03, 1.4000E-03, 1.1000E-03, 
            3.5000E-04, 3.7000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {4.2500E-02, 4.2500E-02, 4.2500E-02, 4.2500E-02, 
            4.2500E-02, 4.2500E-02, 4.2500E-02, 4.2500E-02, 4.2500E-02, 
            4.2500E-02, 4.2500E-02, 4.2500E-02, 4.2500E-02, 4.2500E-02, 
            4.2500E-02, 4.2500E-02, 4.2400E-02, 4.2300E-02, 4.2000E-02, 
            4.1100E-02, 3.9500E-02, 3.7000E-02, 3.3800E-02, 3.0100E-02, 
            2.2000E-02, 6.8000E-03, 2.2000E-03, 1.7000E-03, 1.1000E-03, 
            2.3000E-04, 1.4000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.7400E-02, 2.7400E-02, 2.7400E-02, 2.7400E-02, 
            2.7400E-02, 2.7400E-02, 2.7400E-02, 2.7400E-02, 2.7400E-02, 
            2.7400E-02, 2.7400E-02, 2.7400E-02, 2.7400E-02, 2.7400E-02, 
            2.7400E-02, 2.7400E-02, 2.7400E-02, 2.7400E-02, 2.7400E-02, 
            2.7400E-02, 2.7300E-02, 2.7100E-02, 2.6700E-02, 2.6200E-02, 
            2.4000E-02, 1.7000E-02, 9.2000E-03, 2.1000E-03, 4.8000E-04, 
            3.5000E-05, 8.0000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.8200E-02, 2.8200E-02, 2.8200E-02, 2.8200E-02, 
            2.8200E-02, 2.8200E-02, 2.8200E-02, 2.8200E-02, 2.8200E-02, 
            2.8200E-02, 2.8200E-02, 2.8200E-02, 2.8200E-02, 2.8200E-02, 
            2.8200E-02, 2.8200E-02, 2.8200E-02, 2.8200E-02, 2.8200E-02, 
            2.8100E-02, 2.8000E-02, 2.7800E-02, 2.7400E-02, 2.6800E-02, 
            2.5000E-02, 1.7000E-02, 8.8000E-03, 1.9000E-03, 4.0000E-04, 
            2.6000E-05, 4.4000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.3500E-01, 1.3500E-01, 1.3500E-01, 1.3500E-01, 
            1.3400E-01, 1.3400E-01, 1.3300E-01, 1.3200E-01, 1.3000E-01, 
            1.2900E-01, 1.2700E-01, 1.2200E-01, 1.1700E-01, 1.1100E-01, 
            1.0500E-01, 9.8500E-02, 9.1600E-02, 7.7500E-02, 5.7600E-02, 
            3.2300E-02, 1.8900E-02, 1.4300E-02, 1.3600E-02, 1.3500E-02, 
            1.0000E-02, 2.1000E-03, 1.3000E-03, 5.7000E-04, 1.0000E-04, 
            4.1000E-05, 1.8000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {8.4800E-02, 8.4800E-02, 8.4800E-02, 8.4800E-02, 
            8.4800E-02, 8.4800E-02, 8.4800E-02, 8.4800E-02, 8.4800E-02, 
            8.4800E-02, 8.4700E-02, 8.4600E-02, 8.4400E-02, 8.4000E-02, 
            8.3500E-02, 8.2800E-02, 8.1900E-02, 7.9200E-02, 7.3300E-02, 
            5.8700E-02, 4.1800E-02, 2.6700E-02, 1.6000E-02, 9.6600E-03, 
            5.8000E-03, 4.4000E-03, 1.5000E-03, 3.2000E-04, 2.8000E-04, 
            9.4000E-05, 9.7000E-06} );

    subshell_half_profiles[11] = 
      std::vector<double>( {9.2100E-02, 9.2100E-02, 9.2100E-02, 9.2100E-02, 
            9.2100E-02, 9.2100E-02, 9.2100E-02, 9.2100E-02, 9.2100E-02, 
            9.2000E-02, 9.2000E-02, 9.1800E-02, 9.1400E-02, 9.0900E-02, 
            9.0100E-02, 8.9100E-02, 8.7800E-02, 8.4000E-02, 7.5900E-02, 
            5.7300E-02, 3.7700E-02, 2.2200E-02, 1.2700E-02, 8.0800E-03, 
            6.2000E-03, 3.9000E-03, 1.0000E-03, 4.0000E-04, 2.8000E-04, 
            6.3000E-05, 3.8000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {6.8800E-02, 6.8800E-02, 6.8800E-02, 6.8800E-02, 
            6.8800E-02, 6.8800E-02, 6.8800E-02, 6.8800E-02, 6.8800E-02, 
            6.8800E-02, 6.8800E-02, 6.8800E-02, 6.8800E-02, 6.8800E-02, 
            6.8700E-02, 6.8600E-02, 6.8500E-02, 6.8000E-02, 6.6500E-02, 
            6.1000E-02, 5.1400E-02, 3.9700E-02, 2.8200E-02, 1.8700E-02, 
            7.3000E-03, 2.4000E-03, 2.1000E-03, 6.3000E-04, 1.5000E-04, 
            1.1000E-05, 2.3000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {7.0600E-02, 7.0600E-02, 7.0600E-02, 7.0600E-02, 
            7.0600E-02, 7.0600E-02, 7.0600E-02, 7.0600E-02, 7.0600E-02, 
            7.0600E-02, 7.0600E-02, 7.0500E-02, 7.0500E-02, 7.0500E-02, 
            7.0500E-02, 7.0400E-02, 7.0200E-02, 6.9700E-02, 6.8000E-02, 
            6.1700E-02, 5.1300E-02, 3.8900E-02, 2.7100E-02, 1.7600E-02, 
            6.7000E-03, 2.5000E-03, 2.1000E-03, 5.7000E-04, 1.2000E-04, 
            7.9000E-06, 1.3000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {5.7300E-02, 5.7300E-02, 5.7300E-02, 5.7300E-02, 
            5.7300E-02, 5.7300E-02, 5.7300E-02, 5.7300E-02, 5.7300E-02, 
            5.7300E-02, 5.7300E-02, 5.7300E-02, 5.7300E-02, 5.7300E-02, 
            5.7300E-02, 5.7200E-02, 5.7200E-02, 5.7100E-02, 5.6500E-02, 
            5.4100E-02, 4.9400E-02, 4.2900E-02, 3.5600E-02, 2.8500E-02, 
            1.7000E-02, 3.9000E-03, 8.9000E-04, 5.8000E-05, 5.8000E-06, 
            1.4000E-07, 9.7000E-10} );

    subshell_half_profiles[15] = 
      std::vector<double>( {5.8000E-02, 5.8000E-02, 5.8000E-02, 5.8000E-02, 
            5.8000E-02, 5.8000E-02, 5.8000E-02, 5.8000E-02, 5.8000E-02, 
            5.8000E-02, 5.8000E-02, 5.8000E-02, 5.8000E-02, 5.8000E-02, 
            5.8000E-02, 5.8000E-02, 5.8000E-02, 5.7800E-02, 5.7200E-02, 
            5.4600E-02, 4.9700E-02, 4.2900E-02, 3.5400E-02, 2.8200E-02, 
            1.7000E-02, 3.8000E-03, 8.3000E-04, 5.3000E-05, 5.0000E-06, 
            1.1000E-07, 6.3000E-10} );

    subshell_half_profiles[16] = 
      std::vector<double>( {3.0300E-01, 3.0300E-01, 3.0200E-01, 3.0000E-01, 
            2.9700E-01, 2.9000E-01, 2.8100E-01, 2.6900E-01, 2.5500E-01, 
            2.4000E-01, 2.2400E-01, 1.8900E-01, 1.5500E-01, 1.2300E-01, 
            9.5000E-02, 7.2600E-02, 5.5500E-02, 3.5500E-02, 2.7500E-02, 
            2.5700E-02, 1.7000E-02, 8.2900E-03, 4.1300E-03, 3.0800E-03, 
            2.9000E-03, 6.3000E-04, 2.8000E-04, 1.3000E-04, 2.4000E-05, 
            8.6000E-06, 3.7000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {2.0000E-01, 2.0000E-01, 2.0000E-01, 2.0000E-01, 
            2.0000E-01, 2.0000E-01, 1.9900E-01, 1.9900E-01, 1.9800E-01, 
            1.9600E-01, 1.9400E-01, 1.8800E-01, 1.7800E-01, 1.6400E-01, 
            1.4800E-01, 1.3000E-01, 1.1200E-01, 7.6700E-02, 3.8000E-02, 
            1.3700E-02, 1.1500E-02, 1.0500E-02, 7.5800E-03, 4.5200E-03, 
            1.5000E-03, 9.4000E-04, 3.5000E-04, 6.1000E-05, 5.4000E-05, 
            1.8000E-05, 1.9000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.2000E-01, 2.2000E-01, 2.2000E-01, 2.2000E-01, 
            2.2000E-01, 2.2000E-01, 2.1900E-01, 2.1800E-01, 2.1700E-01, 
            2.1500E-01, 2.1100E-01, 2.0100E-01, 1.8700E-01, 1.6900E-01, 
            1.4700E-01, 1.2500E-01, 1.0300E-01, 6.5100E-02, 2.9100E-02, 
            1.2800E-02, 1.2200E-02, 9.7100E-03, 5.9500E-03, 3.1400E-03, 
            1.2000E-03, 8.4000E-04, 2.3000E-04, 7.3000E-05, 5.3000E-05, 
            1.2000E-05, 7.1000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.9700E-01, 1.9700E-01, 1.9700E-01, 1.9700E-01, 
            1.9700E-01, 1.9700E-01, 1.9700E-01, 1.9700E-01, 1.9700E-01, 
            1.9600E-01, 1.9500E-01, 1.9100E-01, 1.8400E-01, 1.7300E-01, 
            1.5800E-01, 1.4200E-01, 1.2400E-01, 8.8000E-02, 4.5700E-02, 
            1.2500E-02, 5.2900E-03, 4.8100E-03, 4.4900E-03, 3.5600E-03, 
            1.6000E-03, 3.0000E-04, 2.7000E-04, 8.8000E-05, 2.1000E-05, 
            1.5000E-06, 3.2000E-08} );

    subshell_half_profiles[20] = 
      std::vector<double>( {2.0300E-01, 2.0300E-01, 2.0300E-01, 2.0300E-01, 
            2.0300E-01, 2.0300E-01, 2.0300E-01, 2.0300E-01, 2.0300E-01, 
            2.0200E-01, 2.0100E-01, 1.9600E-01, 1.8800E-01, 1.7500E-01, 
            1.5900E-01, 1.4100E-01, 1.2200E-01, 8.4600E-02, 4.2200E-02, 
            1.1000E-02, 5.1200E-03, 4.8400E-03, 4.3900E-03, 3.3500E-03, 
            1.4000E-03, 3.0000E-04, 2.6000E-04, 7.8000E-05, 1.7000E-05, 
            1.1000E-06, 1.7000E-08} );

    subshell_half_profiles[21] = 
      std::vector<double>( {8.8700E-01, 8.7800E-01, 8.5500E-01, 8.1700E-01, 
            7.6700E-01, 6.4100E-01, 5.0200E-01, 3.7100E-01, 2.6000E-01, 
            1.7600E-01, 1.1800E-01, 6.0900E-02, 4.7300E-02, 4.6400E-02, 
            4.4800E-02, 3.9700E-02, 3.2200E-02, 1.7600E-02, 6.1700E-03, 
            3.8600E-03, 3.1000E-03, 1.6100E-03, 7.1400E-04, 4.3700E-04, 
            4.0000E-04, 9.1000E-05, 3.7000E-05, 1.8000E-05, 3.2000E-06, 
            1.1000E-06, 5.0000E-07} );

    subshell_half_profiles[22] = 
      std::vector<double>( {6.4500E-01, 6.4500E-01, 6.4500E-01, 6.4300E-01, 
            6.3700E-01, 6.1100E-01, 5.5900E-01, 4.8500E-01, 3.9800E-01, 
            3.1000E-01, 2.3200E-01, 1.1600E-01, 5.3800E-02, 2.6600E-02, 
            1.7300E-02, 1.5300E-02, 1.5200E-02, 1.3800E-02, 8.1500E-03, 
            2.0900E-03, 1.1000E-03, 1.0600E-03, 8.2300E-04, 5.0900E-04, 
            1.6000E-04, 9.0000E-05, 3.5000E-05, 5.8000E-06, 5.2000E-06, 
            1.8000E-06, 1.8000E-07} );

    subshell_half_profiles[23] = 
      std::vector<double>( {7.5300E-01, 7.5300E-01, 7.5200E-01, 7.4700E-01, 
            7.3600E-01, 6.8700E-01, 5.9800E-01, 4.8300E-01, 3.6600E-01, 
            2.6100E-01, 1.7800E-01, 7.4700E-02, 3.1600E-02, 1.7800E-02, 
            1.5000E-02, 1.4800E-02, 1.4400E-02, 1.1100E-02, 5.1900E-03, 
            1.2800E-03, 1.0000E-03, 8.7200E-04, 5.6200E-04, 2.9900E-04, 
            1.0000E-04, 6.9000E-05, 1.9000E-05, 5.9000E-06, 4.3000E-06, 
            9.7000E-07, 5.8000E-08} );
  }
};

//! The default Compton profile generator implementation for A=85
template<>
struct DefaultComptonProfileGeneratorImpl<85u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 24 );

    subshell_half_profiles[0] = 
      std::vector<double>( {8.3800E-03, 8.3800E-03, 8.3800E-03, 8.3800E-03, 
            8.3800E-03, 8.3800E-03, 8.3800E-03, 8.3800E-03, 8.3800E-03, 
            8.3800E-03, 8.3800E-03, 8.3700E-03, 8.3700E-03, 8.3700E-03, 
            8.3700E-03, 8.3700E-03, 8.3700E-03, 8.3600E-03, 8.3500E-03, 
            8.3300E-03, 8.3100E-03, 8.2800E-03, 8.2400E-03, 8.2000E-03, 
            8.1000E-03, 7.8000E-03, 7.4000E-03, 6.3000E-03, 5.2000E-03, 
            3.2000E-03, 1.1000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.9900E-02, 2.9900E-02, 2.9900E-02, 2.9900E-02, 
            2.9900E-02, 2.9900E-02, 2.9900E-02, 2.9900E-02, 2.9900E-02, 
            2.9800E-02, 2.9800E-02, 2.9800E-02, 2.9700E-02, 2.9700E-02, 
            2.9600E-02, 2.9500E-02, 2.9500E-02, 2.9300E-02, 2.8900E-02, 
            2.8200E-02, 2.7200E-02, 2.6200E-02, 2.4900E-02, 2.3600E-02, 
            2.1000E-02, 1.3000E-02, 7.5000E-03, 1.9000E-03, 7.9000E-04, 
            6.9000E-04, 2.7000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.4500E-02, 1.4500E-02, 1.4500E-02, 1.4500E-02, 
            1.4500E-02, 1.4500E-02, 1.4500E-02, 1.4500E-02, 1.4500E-02, 
            1.4500E-02, 1.4500E-02, 1.4500E-02, 1.4500E-02, 1.4500E-02, 
            1.4500E-02, 1.4500E-02, 1.4500E-02, 1.4500E-02, 1.4500E-02, 
            1.4500E-02, 1.4500E-02, 1.4400E-02, 1.4400E-02, 1.4300E-02, 
            1.4000E-02, 1.3000E-02, 1.2000E-02, 7.6000E-03, 4.3000E-03, 
            1.2000E-03, 1.3000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 
            1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 
            1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 
            1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 1.6700E-02, 
            1.6700E-02, 1.6600E-02, 1.6600E-02, 1.6500E-02, 1.6400E-02, 
            1.6000E-02, 1.5000E-02, 1.2000E-02, 6.9000E-03, 3.4000E-03, 
            7.1000E-04, 4.8000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {6.5500E-02, 6.5500E-02, 6.5500E-02, 6.5500E-02, 
            6.5500E-02, 6.5400E-02, 6.5300E-02, 6.5200E-02, 6.5000E-02, 
            6.4800E-02, 6.4600E-02, 6.4200E-02, 6.3600E-02, 6.2900E-02, 
            6.2100E-02, 6.1200E-02, 6.0200E-02, 5.8100E-02, 5.4300E-02, 
            4.7000E-02, 3.9100E-02, 3.1400E-02, 2.4400E-02, 1.8500E-02, 
            1.0000E-02, 5.1000E-03, 4.7000E-03, 1.7000E-03, 3.3000E-04, 
            1.6000E-04, 6.9000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.8300E-02, 3.8300E-02, 3.8300E-02, 3.8300E-02, 
            3.8300E-02, 3.8300E-02, 3.8300E-02, 3.8300E-02, 3.8300E-02, 
            3.8300E-02, 3.8300E-02, 3.8300E-02, 3.8300E-02, 3.8300E-02, 
            3.8300E-02, 3.8200E-02, 3.8200E-02, 3.8200E-02, 3.8000E-02, 
            3.7400E-02, 3.6400E-02, 3.4700E-02, 3.2600E-02, 2.9900E-02, 
            2.4000E-02, 9.1000E-03, 2.8000E-03, 1.4000E-03, 1.1000E-03, 
            3.7000E-04, 4.0000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 
            4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 
            4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 
            4.1900E-02, 4.1800E-02, 4.1800E-02, 4.1700E-02, 4.1400E-02, 
            4.0600E-02, 3.9000E-02, 3.6700E-02, 3.3700E-02, 3.0100E-02, 
            2.2000E-02, 7.1000E-03, 2.3000E-03, 1.7000E-03, 1.1000E-03, 
            2.5000E-04, 1.5000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.7000E-02, 2.7000E-02, 2.7000E-02, 2.7000E-02, 
            2.7000E-02, 2.7000E-02, 2.7000E-02, 2.7000E-02, 2.7000E-02, 
            2.7000E-02, 2.7000E-02, 2.7000E-02, 2.7000E-02, 2.7000E-02, 
            2.7000E-02, 2.7000E-02, 2.7000E-02, 2.7000E-02, 2.7000E-02, 
            2.7000E-02, 2.6900E-02, 2.6700E-02, 2.6400E-02, 2.5900E-02, 
            2.4000E-02, 1.7000E-02, 9.5000E-03, 2.3000E-03, 5.2000E-04, 
            3.9000E-05, 8.9000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 
            2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 
            2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 
            2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 2.7800E-02, 
            2.7700E-02, 2.7600E-02, 2.7400E-02, 2.7100E-02, 2.6500E-02, 
            2.5000E-02, 1.7000E-02, 9.1000E-03, 2.0000E-03, 4.3000E-04, 
            2.8000E-05, 4.9000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.3200E-01, 1.3200E-01, 1.3200E-01, 1.3200E-01, 
            1.3200E-01, 1.3100E-01, 1.3000E-01, 1.2900E-01, 1.2800E-01, 
            1.2600E-01, 1.2400E-01, 1.2000E-01, 1.1500E-01, 1.1000E-01, 
            1.0400E-01, 9.7700E-02, 9.1100E-02, 7.7600E-02, 5.8200E-02, 
            3.3100E-02, 1.9400E-02, 1.4300E-02, 1.3400E-02, 1.3300E-02, 
            1.1000E-02, 2.2000E-03, 1.3000E-03, 6.1000E-04, 1.2000E-04, 
            4.0000E-05, 1.8000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {8.3100E-02, 8.3100E-02, 8.3100E-02, 8.3100E-02, 
            8.3100E-02, 8.3100E-02, 8.3100E-02, 8.3100E-02, 8.3100E-02, 
            8.3100E-02, 8.3000E-02, 8.2900E-02, 8.2700E-02, 8.2400E-02, 
            8.1900E-02, 8.1300E-02, 8.0400E-02, 7.8000E-02, 7.2500E-02, 
            5.8800E-02, 4.2600E-02, 2.7700E-02, 1.6800E-02, 1.0200E-02, 
            5.8000E-03, 4.5000E-03, 1.6000E-03, 3.2000E-04, 2.9000E-04, 
            1.0000E-04, 1.1000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {9.0400E-02, 9.0400E-02, 9.0400E-02, 9.0400E-02, 
            9.0400E-02, 9.0400E-02, 9.0400E-02, 9.0400E-02, 9.0300E-02, 
            9.0300E-02, 9.0300E-02, 9.0100E-02, 8.9800E-02, 8.9300E-02, 
            8.8600E-02, 8.7600E-02, 8.6400E-02, 8.2900E-02, 7.5300E-02, 
            5.7700E-02, 3.8600E-02, 2.3200E-02, 1.3300E-02, 8.3700E-03, 
            6.2000E-03, 4.0000E-03, 1.1000E-03, 4.0000E-04, 2.9000E-04, 
            6.7000E-05, 4.1000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {6.7400E-02, 6.7400E-02, 6.7400E-02, 6.7400E-02, 
            6.7400E-02, 6.7400E-02, 6.7400E-02, 6.7400E-02, 6.7400E-02, 
            6.7400E-02, 6.7400E-02, 6.7400E-02, 6.7400E-02, 6.7400E-02, 
            6.7300E-02, 6.7300E-02, 6.7200E-02, 6.6700E-02, 6.5400E-02, 
            6.0300E-02, 5.1500E-02, 4.0300E-02, 2.9100E-02, 1.9600E-02, 
            7.8000E-03, 2.4000E-03, 2.1000E-03, 6.7000E-04, 1.6000E-04, 
            1.2000E-05, 2.6000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {6.9100E-02, 6.9100E-02, 6.9100E-02, 6.9100E-02, 
            6.9100E-02, 6.9100E-02, 6.9100E-02, 6.9100E-02, 6.9100E-02, 
            6.9100E-02, 6.9100E-02, 6.9100E-02, 6.9100E-02, 6.9100E-02, 
            6.9100E-02, 6.9000E-02, 6.8800E-02, 6.8400E-02, 6.6800E-02, 
            6.1100E-02, 5.1500E-02, 3.9600E-02, 2.8000E-02, 1.8500E-02, 
            7.1000E-03, 2.5000E-03, 2.1000E-03, 6.1000E-04, 1.3000E-04, 
            8.7000E-06, 1.5000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {5.5800E-02, 5.5800E-02, 5.5800E-02, 5.5800E-02, 
            5.5800E-02, 5.5800E-02, 5.5800E-02, 5.5800E-02, 5.5800E-02, 
            5.5800E-02, 5.5800E-02, 5.5800E-02, 5.5800E-02, 5.5800E-02, 
            5.5700E-02, 5.5700E-02, 5.5700E-02, 5.5600E-02, 5.5200E-02, 
            5.3100E-02, 4.9000E-02, 4.3000E-02, 3.6100E-02, 2.9200E-02, 
            1.8000E-02, 4.3000E-03, 9.9000E-04, 6.7000E-05, 6.6000E-06, 
            1.7000E-07, 1.2000E-09} );

    subshell_half_profiles[15] = 
      std::vector<double>( {5.6500E-02, 5.6500E-02, 5.6500E-02, 5.6500E-02, 
            5.6500E-02, 5.6500E-02, 5.6500E-02, 5.6500E-02, 5.6500E-02, 
            5.6500E-02, 5.6500E-02, 5.6500E-02, 5.6500E-02, 5.6500E-02, 
            5.6500E-02, 5.6500E-02, 5.6400E-02, 5.6300E-02, 5.5900E-02, 
            5.3700E-02, 4.9200E-02, 4.3000E-02, 3.5900E-02, 2.8900E-02, 
            1.7000E-02, 4.1000E-03, 9.2000E-04, 6.0000E-05, 5.7000E-06, 
            1.3000E-07, 7.4000E-10} );

    subshell_half_profiles[16] = 
      std::vector<double>( {2.9300E-01, 2.9300E-01, 2.9200E-01, 2.9000E-01, 
            2.8800E-01, 2.8100E-01, 2.7300E-01, 2.6200E-01, 2.4900E-01, 
            2.3500E-01, 2.2000E-01, 1.8800E-01, 1.5500E-01, 1.2500E-01, 
            9.7800E-02, 7.5500E-02, 5.8200E-02, 3.7000E-02, 2.7500E-02, 
            2.6000E-02, 1.8000E-02, 9.1500E-03, 4.5000E-03, 3.1600E-03, 
            2.9000E-03, 7.1000E-04, 2.8000E-04, 1.4000E-04, 2.7000E-05, 
            8.7000E-06, 4.0000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.9300E-01, 1.9300E-01, 1.9300E-01, 1.9300E-01, 
            1.9300E-01, 1.9300E-01, 1.9300E-01, 1.9200E-01, 1.9100E-01, 
            1.9000E-01, 1.8800E-01, 1.8300E-01, 1.7400E-01, 1.6200E-01, 
            1.4700E-01, 1.3100E-01, 1.1400E-01, 8.0200E-02, 4.1200E-02, 
            1.4500E-02, 1.1600E-02, 1.0900E-02, 8.1200E-03, 5.0200E-03, 
            1.6000E-03, 9.8000E-04, 3.9000E-04, 6.3000E-05, 5.6000E-05, 
            2.0000E-05, 2.1000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.1200E-01, 2.1200E-01, 2.1200E-01, 2.1200E-01, 
            2.1200E-01, 2.1200E-01, 2.1200E-01, 2.1100E-01, 2.1000E-01, 
            2.0800E-01, 2.0500E-01, 1.9600E-01, 1.8400E-01, 1.6700E-01, 
            1.4800E-01, 1.2700E-01, 1.0600E-01, 6.9000E-02, 3.1900E-02, 
            1.3200E-02, 1.2400E-02, 1.0200E-02, 6.5300E-03, 3.5300E-03, 
            1.3000E-03, 8.9000E-04, 2.5000E-04, 7.5000E-05, 5.6000E-05, 
            1.3000E-05, 8.0000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.8800E-01, 1.8800E-01, 1.8800E-01, 1.8800E-01, 
            1.8800E-01, 1.8800E-01, 1.8800E-01, 1.8800E-01, 1.8700E-01, 
            1.8700E-01, 1.8600E-01, 1.8300E-01, 1.7800E-01, 1.6900E-01, 
            1.5700E-01, 1.4200E-01, 1.2600E-01, 9.3000E-02, 5.0900E-02, 
            1.4700E-02, 5.7700E-03, 4.9800E-03, 4.7600E-03, 3.8900E-03, 
            1.8000E-03, 3.2000E-04, 2.9000E-04, 9.9000E-05, 2.4000E-05, 
            1.8000E-06, 3.9000E-08} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.9400E-01, 1.9400E-01, 1.9400E-01, 1.9400E-01, 
            1.9400E-01, 1.9400E-01, 1.9400E-01, 1.9400E-01, 1.9300E-01, 
            1.9300E-01, 1.9200E-01, 1.8800E-01, 1.8200E-01, 1.7200E-01, 
            1.5800E-01, 1.4200E-01, 1.2500E-01, 8.9900E-02, 4.7200E-02, 
            1.3000E-02, 5.5200E-03, 5.0300E-03, 4.6800E-03, 3.6900E-03, 
            1.6000E-03, 3.2000E-04, 2.8000E-04, 8.8000E-05, 2.0000E-05, 
            1.3000E-06, 2.1000E-08} );

    subshell_half_profiles[21] = 
      std::vector<double>( {8.3000E-01, 8.2300E-01, 8.0300E-01, 7.7100E-01, 
            7.2900E-01, 6.2200E-01, 5.0000E-01, 3.8000E-01, 2.7600E-01, 
            1.9300E-01, 1.3200E-01, 6.8000E-02, 4.9000E-02, 4.6800E-02, 
            4.6100E-02, 4.2300E-02, 3.5700E-02, 2.0900E-02, 7.4800E-03, 
            4.0900E-03, 3.4700E-03, 1.9100E-03, 8.6000E-04, 4.9100E-04, 
            4.3000E-04, 1.1000E-04, 4.0000E-05, 2.1000E-05, 3.9000E-06, 
            1.2000E-06, 5.6000E-07} );

    subshell_half_profiles[22] = 
      std::vector<double>( {5.9300E-01, 5.9300E-01, 5.9300E-01, 5.9100E-01, 
            5.8800E-01, 5.6900E-01, 5.3200E-01, 4.7400E-01, 4.0400E-01, 
            3.2800E-01, 2.5600E-01, 1.4000E-01, 6.9500E-02, 3.4700E-02, 
            2.0900E-02, 1.6800E-02, 1.6300E-02, 1.5500E-02, 1.0100E-02, 
            2.7500E-03, 1.2700E-03, 1.2100E-03, 9.8800E-04, 6.3900E-04, 
            2.0000E-04, 1.1000E-04, 4.3000E-05, 6.7000E-06, 6.0000E-06, 
            2.2000E-06, 2.3000E-07} );

    subshell_half_profiles[23] = 
      std::vector<double>( {6.9200E-01, 6.9200E-01, 6.9200E-01, 6.8900E-01, 
            6.8100E-01, 6.4600E-01, 5.7800E-01, 4.8600E-01, 3.8500E-01, 
            2.8900E-01, 2.0700E-01, 9.5400E-02, 4.2100E-02, 2.2000E-02, 
            1.6600E-02, 1.6000E-02, 1.5800E-02, 1.3200E-02, 6.7100E-03, 
            1.6200E-03, 1.1500E-03, 1.0400E-03, 7.0000E-04, 3.8500E-04, 
            1.3000E-04, 8.4000E-05, 2.4000E-05, 6.9000E-06, 5.2000E-06, 
            1.2000E-06, 7.4000E-08} );
  }
};

//! The default Compton profile generator implementation for A=86
template<>
struct DefaultComptonProfileGeneratorImpl<86u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 24 );

    subshell_half_profiles[0] = 
      std::vector<double>( {8.2300E-03, 8.2300E-03, 8.2300E-03, 8.2300E-03, 
            8.2300E-03, 8.2300E-03, 8.2300E-03, 8.2300E-03, 8.2300E-03, 
            8.2300E-03, 8.2300E-03, 8.2300E-03, 8.2300E-03, 8.2300E-03, 
            8.2300E-03, 8.2300E-03, 8.2200E-03, 8.2200E-03, 8.2100E-03, 
            8.1900E-03, 8.1700E-03, 8.1400E-03, 8.1000E-03, 8.0600E-03, 
            8.0000E-03, 7.7000E-03, 7.3000E-03, 6.3000E-03, 5.2000E-03, 
            3.2000E-03, 1.1000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.9400E-02, 2.9400E-02, 2.9400E-02, 2.9400E-02, 
            2.9400E-02, 2.9400E-02, 2.9400E-02, 2.9400E-02, 2.9400E-02, 
            2.9400E-02, 2.9300E-02, 2.9300E-02, 2.9300E-02, 2.9200E-02, 
            2.9100E-02, 2.9100E-02, 2.9000E-02, 2.8800E-02, 2.8500E-02, 
            2.7800E-02, 2.6900E-02, 2.5800E-02, 2.4700E-02, 2.3400E-02, 
            2.1000E-02, 1.3000E-02, 7.7000E-03, 2.0000E-03, 8.0000E-04, 
            6.8000E-04, 2.8000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.4200E-02, 1.4200E-02, 1.4200E-02, 1.4200E-02, 
            1.4200E-02, 1.4200E-02, 1.4200E-02, 1.4200E-02, 1.4200E-02, 
            1.4200E-02, 1.4200E-02, 1.4200E-02, 1.4200E-02, 1.4200E-02, 
            1.4200E-02, 1.4200E-02, 1.4200E-02, 1.4200E-02, 1.4200E-02, 
            1.4200E-02, 1.4200E-02, 1.4200E-02, 1.4100E-02, 1.4100E-02, 
            1.4000E-02, 1.3000E-02, 1.2000E-02, 7.6000E-03, 4.4000E-03, 
            1.3000E-03, 1.5000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.6500E-02, 1.6500E-02, 1.6500E-02, 1.6500E-02, 
            1.6500E-02, 1.6500E-02, 1.6500E-02, 1.6500E-02, 1.6500E-02, 
            1.6500E-02, 1.6500E-02, 1.6500E-02, 1.6500E-02, 1.6500E-02, 
            1.6500E-02, 1.6500E-02, 1.6500E-02, 1.6500E-02, 1.6400E-02, 
            1.6400E-02, 1.6400E-02, 1.6400E-02, 1.6300E-02, 1.6200E-02, 
            1.6000E-02, 1.5000E-02, 1.2000E-02, 7.0000E-03, 3.4000E-03, 
            7.4000E-04, 5.1000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {6.4400E-02, 6.4400E-02, 6.4400E-02, 6.4400E-02, 
            6.4400E-02, 6.4300E-02, 6.4200E-02, 6.4100E-02, 6.4000E-02, 
            6.3800E-02, 6.3600E-02, 6.3100E-02, 6.2600E-02, 6.1900E-02, 
            6.1200E-02, 6.0300E-02, 5.9400E-02, 5.7300E-02, 5.3700E-02, 
            4.6700E-02, 3.9100E-02, 3.1600E-02, 2.4700E-02, 1.8900E-02, 
            1.1000E-02, 5.0000E-03, 4.7000E-03, 1.7000E-03, 3.6000E-04, 
            1.5000E-04, 7.2000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.7600E-02, 3.7600E-02, 3.7600E-02, 3.7600E-02, 
            3.7600E-02, 3.7600E-02, 3.7600E-02, 3.7600E-02, 3.7600E-02, 
            3.7600E-02, 3.7600E-02, 3.7600E-02, 3.7600E-02, 3.7600E-02, 
            3.7600E-02, 3.7600E-02, 3.7600E-02, 3.7500E-02, 3.7400E-02, 
            3.6800E-02, 3.5900E-02, 3.4300E-02, 3.2300E-02, 2.9700E-02, 
            2.4000E-02, 9.5000E-03, 3.0000E-03, 1.4000E-03, 1.2000E-03, 
            3.9000E-04, 4.3000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {4.1300E-02, 4.1300E-02, 4.1300E-02, 4.1300E-02, 
            4.1300E-02, 4.1300E-02, 4.1300E-02, 4.1300E-02, 4.1300E-02, 
            4.1300E-02, 4.1300E-02, 4.1300E-02, 4.1300E-02, 4.1300E-02, 
            4.1200E-02, 4.1200E-02, 4.1200E-02, 4.1100E-02, 4.0900E-02, 
            4.0000E-02, 3.8600E-02, 3.6400E-02, 3.3500E-02, 3.0100E-02, 
            2.2000E-02, 7.4000E-03, 2.4000E-03, 1.7000E-03, 1.1000E-03, 
            2.6000E-04, 1.7000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.6600E-02, 2.6600E-02, 2.6600E-02, 2.6600E-02, 
            2.6600E-02, 2.6600E-02, 2.6600E-02, 2.6600E-02, 2.6600E-02, 
            2.6600E-02, 2.6600E-02, 2.6600E-02, 2.6600E-02, 2.6600E-02, 
            2.6600E-02, 2.6600E-02, 2.6600E-02, 2.6600E-02, 2.6600E-02, 
            2.6500E-02, 2.6500E-02, 2.6300E-02, 2.6000E-02, 2.5500E-02, 
            2.4000E-02, 1.7000E-02, 9.7000E-03, 2.4000E-03, 5.6000E-04, 
            4.3000E-05, 9.9000E-07} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.7400E-02, 2.7400E-02, 2.7400E-02, 2.7400E-02, 
            2.7400E-02, 2.7400E-02, 2.7400E-02, 2.7400E-02, 2.7400E-02, 
            2.7400E-02, 2.7400E-02, 2.7400E-02, 2.7400E-02, 2.7400E-02, 
            2.7400E-02, 2.7400E-02, 2.7400E-02, 2.7400E-02, 2.7400E-02, 
            2.7300E-02, 2.7300E-02, 2.7100E-02, 2.6700E-02, 2.6200E-02, 
            2.4000E-02, 1.7000E-02, 9.3000E-03, 2.1000E-03, 4.6000E-04, 
            3.1000E-05, 5.5000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.3000E-01, 1.3000E-01, 1.2900E-01, 1.2900E-01, 
            1.2900E-01, 1.2900E-01, 1.2800E-01, 1.2700E-01, 1.2500E-01, 
            1.2400E-01, 1.2200E-01, 1.1800E-01, 1.1400E-01, 1.0900E-01, 
            1.0300E-01, 9.6800E-02, 9.0500E-02, 7.7500E-02, 5.8800E-02, 
            3.3900E-02, 1.9900E-02, 1.4400E-02, 1.3300E-02, 1.3200E-02, 
            1.1000E-02, 2.4000E-03, 1.3000E-03, 6.5000E-04, 1.3000E-04, 
            4.0000E-05, 1.9000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {8.1400E-02, 8.1400E-02, 8.1400E-02, 8.1400E-02, 
            8.1400E-02, 8.1400E-02, 8.1400E-02, 8.1400E-02, 8.1400E-02, 
            8.1400E-02, 8.1400E-02, 8.1200E-02, 8.1100E-02, 8.0800E-02, 
            8.0300E-02, 7.9800E-02, 7.9000E-02, 7.6800E-02, 7.1700E-02, 
            5.8800E-02, 4.3300E-02, 2.8700E-02, 1.7700E-02, 1.0800E-02, 
            5.8000E-03, 4.6000E-03, 1.7000E-03, 3.2000E-04, 2.9000E-04, 
            1.1000E-04, 1.2000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {8.8700E-02, 8.8700E-02, 8.8700E-02, 8.8700E-02, 
            8.8700E-02, 8.8700E-02, 8.8700E-02, 8.8700E-02, 8.8700E-02, 
            8.8700E-02, 8.8600E-02, 8.8500E-02, 8.8200E-02, 8.7700E-02, 
            8.7100E-02, 8.6200E-02, 8.5100E-02, 8.1900E-02, 7.4700E-02, 
            5.8000E-02, 3.9500E-02, 2.4100E-02, 1.4000E-02, 8.6900E-03, 
            6.2000E-03, 4.2000E-03, 1.2000E-03, 4.0000E-04, 3.0000E-04, 
            7.2000E-05, 4.5000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {6.6100E-02, 6.6100E-02, 6.6100E-02, 6.6100E-02, 
            6.6100E-02, 6.6100E-02, 6.6100E-02, 6.6100E-02, 6.6100E-02, 
            6.6100E-02, 6.6100E-02, 6.6100E-02, 6.6000E-02, 6.6000E-02, 
            6.6000E-02, 6.5900E-02, 6.5800E-02, 6.5500E-02, 6.4300E-02, 
            5.9700E-02, 5.1500E-02, 4.0900E-02, 3.0000E-02, 2.0500E-02, 
            8.4000E-03, 2.4000E-03, 2.2000E-03, 7.2000E-04, 1.7000E-04, 
            1.3000E-05, 3.0000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {6.7800E-02, 6.7800E-02, 6.7800E-02, 6.7800E-02, 
            6.7800E-02, 6.7800E-02, 6.7800E-02, 6.7800E-02, 6.7800E-02, 
            6.7800E-02, 6.7800E-02, 6.7800E-02, 6.7800E-02, 6.7800E-02, 
            6.7700E-02, 6.7600E-02, 6.7500E-02, 6.7100E-02, 6.5700E-02, 
            6.0600E-02, 5.1500E-02, 4.0200E-02, 2.8900E-02, 1.9300E-02, 
            7.6000E-03, 2.5000E-03, 2.1000E-03, 6.5000E-04, 1.5000E-04, 
            9.7000E-06, 1.6000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {5.4300E-02, 5.4300E-02, 5.4300E-02, 5.4300E-02, 
            5.4300E-02, 5.4300E-02, 5.4300E-02, 5.4300E-02, 5.4300E-02, 
            5.4300E-02, 5.4300E-02, 5.4300E-02, 5.4300E-02, 5.4300E-02, 
            5.4300E-02, 5.4300E-02, 5.4300E-02, 5.4200E-02, 5.3900E-02, 
            5.2100E-02, 4.8400E-02, 4.3000E-02, 3.6500E-02, 2.9900E-02, 
            1.9000E-02, 4.6000E-03, 1.1000E-03, 7.6000E-05, 7.7000E-06, 
            2.0000E-07, 1.4000E-09} );

    subshell_half_profiles[15] = 
      std::vector<double>( {5.5000E-02, 5.5000E-02, 5.5000E-02, 5.5000E-02, 
            5.5000E-02, 5.5000E-02, 5.5000E-02, 5.5000E-02, 5.5000E-02, 
            5.5000E-02, 5.5000E-02, 5.5000E-02, 5.5000E-02, 5.5000E-02, 
            5.5000E-02, 5.5000E-02, 5.5000E-02, 5.4900E-02, 5.4500E-02, 
            5.2700E-02, 4.8800E-02, 4.3000E-02, 3.6400E-02, 2.9600E-02, 
            1.8000E-02, 4.4000E-03, 1.0000E-03, 6.8000E-05, 6.6000E-06, 
            1.5000E-07, 8.8000E-10} );

    subshell_half_profiles[16] = 
      std::vector<double>( {2.8400E-01, 2.8300E-01, 2.8200E-01, 2.8100E-01, 
            2.7900E-01, 2.7300E-01, 2.6500E-01, 2.5500E-01, 2.4300E-01, 
            2.3000E-01, 2.1600E-01, 1.8600E-01, 1.5600E-01, 1.2600E-01, 
            1.0000E-01, 7.8300E-02, 6.0800E-02, 3.8600E-02, 2.7600E-02, 
            2.6100E-02, 1.9000E-02, 1.0000E-02, 4.9200E-03, 3.2700E-03, 
            3.0000E-03, 7.9000E-04, 2.9000E-04, 1.6000E-04, 3.1000E-05, 
            8.8000E-06, 4.2000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.8700E-01, 1.8700E-01, 1.8700E-01, 1.8700E-01, 
            1.8700E-01, 1.8700E-01, 1.8600E-01, 1.8600E-01, 1.8500E-01, 
            1.8400E-01, 1.8300E-01, 1.7800E-01, 1.7000E-01, 1.5900E-01, 
            1.4600E-01, 1.3100E-01, 1.1500E-01, 8.3300E-02, 4.4400E-02, 
            1.5500E-02, 1.1600E-02, 1.1100E-02, 8.6400E-03, 5.5200E-03, 
            1.8000E-03, 1.0000E-03, 4.3000E-04, 6.5000E-05, 5.8000E-05, 
            2.2000E-05, 2.4000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {2.0500E-01, 2.0500E-01, 2.0500E-01, 2.0500E-01, 
            2.0500E-01, 2.0500E-01, 2.0500E-01, 2.0400E-01, 2.0300E-01, 
            2.0100E-01, 1.9900E-01, 1.9100E-01, 1.8000E-01, 1.6500E-01, 
            1.4800E-01, 1.2900E-01, 1.0900E-01, 7.2700E-02, 3.4800E-02, 
            1.3700E-02, 1.2500E-02, 1.0700E-02, 7.1100E-03, 3.9500E-03, 
            1.4000E-03, 9.5000E-04, 2.8000E-04, 7.7000E-05, 5.9000E-05, 
            1.4000E-05, 9.0000E-07} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.7900E-01, 1.7900E-01, 1.7900E-01, 1.7900E-01, 
            1.7900E-01, 1.7900E-01, 1.7900E-01, 1.7900E-01, 1.7900E-01, 
            1.7900E-01, 1.7800E-01, 1.7600E-01, 1.7200E-01, 1.6400E-01, 
            1.5500E-01, 1.4200E-01, 1.2800E-01, 9.7200E-02, 5.5800E-02, 
            1.7000E-02, 6.3500E-03, 5.1400E-03, 4.9900E-03, 4.2100E-03, 
            2.1000E-03, 3.4000E-04, 3.1000E-04, 1.1000E-04, 2.7000E-05, 
            2.1000E-06, 4.6000E-08} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.8500E-01, 1.8500E-01, 1.8500E-01, 1.8500E-01, 
            1.8500E-01, 1.8500E-01, 1.8500E-01, 1.8500E-01, 1.8500E-01, 
            1.8500E-01, 1.8400E-01, 1.8100E-01, 1.7600E-01, 1.6800E-01, 
            1.5600E-01, 1.4300E-01, 1.2700E-01, 9.4300E-02, 5.2000E-02, 
            1.5100E-02, 5.9800E-03, 5.1900E-03, 4.9400E-03, 4.0100E-03, 
            1.8000E-03, 3.4000E-04, 3.0000E-04, 9.9000E-05, 2.3000E-05, 
            1.5000E-06, 2.5000E-08} );

    subshell_half_profiles[21] = 
      std::vector<double>( {7.8200E-01, 7.7600E-01, 7.5900E-01, 7.3200E-01, 
            6.9600E-01, 6.0200E-01, 4.9400E-01, 3.8600E-01, 2.8800E-01, 
            2.0700E-01, 1.4600E-01, 7.5500E-02, 5.1200E-02, 4.6900E-02, 
            4.6600E-02, 4.4100E-02, 3.8600E-02, 2.4100E-02, 8.9900E-03, 
            4.2800E-03, 3.8100E-03, 2.2300E-03, 1.0300E-03, 5.5300E-04, 
            4.6000E-04, 1.3000E-04, 4.3000E-05, 2.4000E-05, 4.7000E-06, 
            1.3000E-06, 6.3000E-07} );

    subshell_half_profiles[22] = 
      std::vector<double>( {5.5100E-01, 5.5100E-01, 5.5000E-01, 5.4900E-01, 
            5.4700E-01, 5.3400E-01, 5.0500E-01, 4.6100E-01, 4.0300E-01, 
            3.3800E-01, 2.7300E-01, 1.6000E-01, 8.5200E-02, 4.3900E-02, 
            2.5200E-02, 1.8600E-02, 1.7200E-02, 1.6700E-02, 1.1900E-02, 
            3.5300E-03, 1.4400E-03, 1.3500E-03, 1.1500E-03, 7.7500E-04, 
            2.5000E-04, 1.2000E-04, 5.3000E-05, 7.6000E-06, 6.8000E-06, 
            2.6000E-06, 2.8000E-07} );

    subshell_half_profiles[23] = 
      std::vector<double>( {6.4400E-01, 6.4400E-01, 6.4300E-01, 6.4100E-01, 
            6.3600E-01, 6.0900E-01, 5.5700E-01, 4.8300E-01, 3.9600E-01, 
            3.0800E-01, 2.3000E-01, 1.1500E-01, 5.3500E-02, 2.7100E-02, 
            1.8500E-02, 1.6900E-02, 1.6800E-02, 1.4800E-02, 8.2800E-03, 
            2.0300E-03, 1.2700E-03, 1.1900E-03, 8.4000E-04, 4.7800E-04, 
            1.5000E-04, 9.8000E-05, 3.0000E-05, 7.8000E-06, 6.0000E-06, 
            1.5000E-06, 9.1000E-08} );
  }
};

//! The default Compton profile generator implementation for A=87
template<>
struct DefaultComptonProfileGeneratorImpl<87u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 25 );

    subshell_half_profiles[0] = 
      std::vector<double>( {8.0900E-03, 8.0900E-03, 8.0900E-03, 8.0900E-03, 
            8.0900E-03, 8.0900E-03, 8.0900E-03, 8.0900E-03, 8.0900E-03, 
            8.0900E-03, 8.0900E-03, 8.0900E-03, 8.0900E-03, 8.0900E-03, 
            8.0900E-03, 8.0900E-03, 8.0800E-03, 8.0800E-03, 8.0700E-03, 
            8.0500E-03, 8.0300E-03, 8.0000E-03, 7.9700E-03, 7.9300E-03, 
            7.8000E-03, 7.5000E-03, 7.2000E-03, 6.2000E-03, 5.1000E-03, 
            3.2000E-03, 1.2000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.8900E-02, 2.8900E-02, 2.8900E-02, 2.8900E-02, 
            2.8900E-02, 2.8900E-02, 2.8900E-02, 2.8900E-02, 2.8900E-02, 
            2.8900E-02, 2.8900E-02, 2.8800E-02, 2.8800E-02, 2.8700E-02, 
            2.8700E-02, 2.8600E-02, 2.8500E-02, 2.8400E-02, 2.8000E-02, 
            2.7400E-02, 2.6500E-02, 2.5500E-02, 2.4400E-02, 2.3200E-02, 
            2.1000E-02, 1.4000E-02, 7.9000E-03, 2.1000E-03, 8.0000E-04, 
            6.8000E-04, 2.9000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 
            1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 
            1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 
            1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 
            1.4000E-02, 1.4000E-02, 1.3900E-02, 1.3900E-02, 1.3900E-02, 
            1.3900E-02, 1.3000E-02, 1.1000E-02, 7.7000E-03, 4.5000E-03, 
            1.3000E-03, 1.6000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.6200E-02, 1.6200E-02, 1.6200E-02, 1.6200E-02, 
            1.6200E-02, 1.6200E-02, 1.6200E-02, 1.6200E-02, 1.6200E-02, 
            1.6200E-02, 1.6200E-02, 1.6200E-02, 1.6200E-02, 1.6200E-02, 
            1.6200E-02, 1.6200E-02, 1.6200E-02, 1.6200E-02, 1.6200E-02, 
            1.6200E-02, 1.6200E-02, 1.6200E-02, 1.6100E-02, 1.6000E-02, 
            1.6000E-02, 1.4000E-02, 1.2000E-02, 7.1000E-03, 3.5000E-03, 
            7.8000E-04, 5.5000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {6.3400E-02, 6.3400E-02, 6.3300E-02, 6.3300E-02, 
            6.3300E-02, 6.3200E-02, 6.3200E-02, 6.3100E-02, 6.2900E-02, 
            6.2800E-02, 6.2600E-02, 6.2100E-02, 6.1600E-02, 6.1000E-02, 
            6.0300E-02, 5.9500E-02, 5.8600E-02, 5.6600E-02, 5.3100E-02, 
            4.6400E-02, 3.9000E-02, 3.1700E-02, 2.5000E-02, 1.9200E-02, 
            1.1000E-02, 4.9000E-03, 4.7000E-03, 1.8000E-03, 3.9000E-04, 
            1.5000E-04, 7.4000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.7000E-02, 3.7000E-02, 3.7000E-02, 3.7000E-02, 
            3.7000E-02, 3.7000E-02, 3.7000E-02, 3.7000E-02, 3.7000E-02, 
            3.7000E-02, 3.7000E-02, 3.7000E-02, 3.7000E-02, 3.7000E-02, 
            3.7000E-02, 3.7000E-02, 3.6900E-02, 3.6900E-02, 3.6700E-02, 
            3.6300E-02, 3.5300E-02, 3.3900E-02, 3.2000E-02, 2.9600E-02, 
            2.4000E-02, 9.9000E-03, 3.2000E-03, 1.4000E-03, 1.2000E-03, 
            4.1000E-04, 4.7000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {4.0700E-02, 4.0700E-02, 4.0700E-02, 4.0700E-02, 
            4.0700E-02, 4.0700E-02, 4.0700E-02, 4.0700E-02, 4.0700E-02, 
            4.0700E-02, 4.0700E-02, 4.0700E-02, 4.0700E-02, 4.0700E-02, 
            4.0700E-02, 4.0600E-02, 4.0600E-02, 4.0500E-02, 4.0300E-02, 
            3.9500E-02, 3.8200E-02, 3.6100E-02, 3.3300E-02, 3.0000E-02, 
            2.3000E-02, 7.7000E-03, 2.4000E-03, 1.7000E-03, 1.1000E-03, 
            2.7000E-04, 1.8000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 
            2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 
            2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 
            2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 
            2.6200E-02, 2.6100E-02, 2.5900E-02, 2.5700E-02, 2.5200E-02, 
            2.4000E-02, 1.7000E-02, 9.9000E-03, 2.5000E-03, 6.0000E-04, 
            4.7000E-05, 1.1000E-06} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.7000E-02, 2.7000E-02, 2.7000E-02, 2.7000E-02, 
            2.7000E-02, 2.7000E-02, 2.7000E-02, 2.7000E-02, 2.7000E-02, 
            2.7000E-02, 2.7000E-02, 2.7000E-02, 2.7000E-02, 2.7000E-02, 
            2.7000E-02, 2.7000E-02, 2.7000E-02, 2.7000E-02, 2.7000E-02, 
            2.7000E-02, 2.6900E-02, 2.6700E-02, 2.6400E-02, 2.5900E-02, 
            2.4000E-02, 1.7000E-02, 9.5000E-03, 2.2000E-03, 5.0000E-04, 
            3.4000E-05, 6.1000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.2700E-01, 1.2700E-01, 1.2700E-01, 1.2700E-01, 
            1.2700E-01, 1.2600E-01, 1.2500E-01, 1.2400E-01, 1.2300E-01, 
            1.2200E-01, 1.2000E-01, 1.1600E-01, 1.1200E-01, 1.0700E-01, 
            1.0200E-01, 9.5900E-02, 8.9900E-02, 7.7400E-02, 5.9200E-02, 
            3.4800E-02, 2.0400E-02, 1.4400E-02, 1.3100E-02, 1.3000E-02, 
            1.1000E-02, 2.6000E-03, 1.3000E-03, 6.8000E-04, 1.4000E-04, 
            3.9000E-05, 2.0000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {7.9800E-02, 7.9800E-02, 7.9800E-02, 7.9800E-02, 
            7.9800E-02, 7.9800E-02, 7.9800E-02, 7.9800E-02, 7.9800E-02, 
            7.9800E-02, 7.9700E-02, 7.9600E-02, 7.9500E-02, 7.9200E-02, 
            7.8800E-02, 7.8300E-02, 7.7600E-02, 7.5500E-02, 7.0800E-02, 
            5.8800E-02, 4.3900E-02, 2.9600E-02, 1.8500E-02, 1.1300E-02, 
            5.9000E-03, 4.7000E-03, 1.9000E-03, 3.2000E-04, 2.9000E-04, 
            1.1000E-04, 1.3000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {8.7100E-02, 8.7100E-02, 8.7100E-02, 8.7100E-02, 
            8.7100E-02, 8.7100E-02, 8.7100E-02, 8.7100E-02, 8.7100E-02, 
            8.7100E-02, 8.7000E-02, 8.6900E-02, 8.6600E-02, 8.6200E-02, 
            8.5600E-02, 8.4800E-02, 8.3700E-02, 8.0800E-02, 7.4100E-02, 
            5.8200E-02, 4.0300E-02, 2.5000E-02, 1.4600E-02, 9.0400E-03, 
            6.1000E-03, 4.3000E-03, 1.3000E-03, 4.0000E-04, 3.1000E-04, 
            7.6000E-05, 4.9000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {6.4800E-02, 6.4800E-02, 6.4800E-02, 6.4800E-02, 
            6.4800E-02, 6.4800E-02, 6.4800E-02, 6.4800E-02, 6.4800E-02, 
            6.4800E-02, 6.4800E-02, 6.4700E-02, 6.4700E-02, 6.4700E-02, 
            6.4700E-02, 6.4600E-02, 6.4600E-02, 6.4200E-02, 6.3200E-02, 
            5.9000E-02, 5.1400E-02, 4.1300E-02, 3.0800E-02, 2.1400E-02, 
            9.0000E-03, 2.4000E-03, 2.2000E-03, 7.6000E-04, 1.9000E-04, 
            1.5000E-05, 3.4000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {6.6500E-02, 6.6500E-02, 6.6500E-02, 6.6500E-02, 
            6.6500E-02, 6.6500E-02, 6.6500E-02, 6.6500E-02, 6.6500E-02, 
            6.6500E-02, 6.6500E-02, 6.6500E-02, 6.6500E-02, 6.6400E-02, 
            6.6400E-02, 6.6400E-02, 6.6300E-02, 6.5900E-02, 6.4700E-02, 
            5.9900E-02, 5.1500E-02, 4.0700E-02, 2.9700E-02, 2.0200E-02, 
            8.2000E-03, 2.5000E-03, 2.2000E-03, 6.9000E-04, 1.6000E-04, 
            1.1000E-05, 1.8000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {5.3000E-02, 5.3000E-02, 5.3000E-02, 5.3000E-02, 
            5.3000E-02, 5.3000E-02, 5.3000E-02, 5.3000E-02, 5.3000E-02, 
            5.3000E-02, 5.3000E-02, 5.3000E-02, 5.3000E-02, 5.3000E-02, 
            5.3000E-02, 5.3000E-02, 5.2900E-02, 5.2900E-02, 5.2600E-02, 
            5.1100E-02, 4.7900E-02, 4.2900E-02, 3.6800E-02, 3.0500E-02, 
            1.9000E-02, 5.0000E-03, 1.2000E-03, 8.5000E-05, 8.8000E-06, 
            2.3000E-07, 1.6000E-09} );

    subshell_half_profiles[15] = 
      std::vector<double>( {5.3700E-02, 5.3700E-02, 5.3700E-02, 5.3700E-02, 
            5.3700E-02, 5.3700E-02, 5.3700E-02, 5.3700E-02, 5.3700E-02, 
            5.3700E-02, 5.3700E-02, 5.3700E-02, 5.3700E-02, 5.3700E-02, 
            5.3700E-02, 5.3700E-02, 5.3600E-02, 5.3600E-02, 5.3300E-02, 
            5.1700E-02, 4.8300E-02, 4.3000E-02, 3.6700E-02, 3.0200E-02, 
            1.9000E-02, 4.7000E-03, 1.1000E-03, 7.7000E-05, 7.6000E-06, 
            1.8000E-07, 1.0000E-09} );

    subshell_half_profiles[16] = 
      std::vector<double>( {2.7500E-01, 2.7400E-01, 2.7300E-01, 2.7200E-01, 
            2.7000E-01, 2.6500E-01, 2.5800E-01, 2.4800E-01, 2.3800E-01, 
            2.2600E-01, 2.1300E-01, 1.8500E-01, 1.5600E-01, 1.2800E-01, 
            1.0300E-01, 8.0900E-02, 6.3300E-02, 4.0200E-02, 2.7700E-02, 
            2.6200E-02, 1.9900E-02, 1.1000E-02, 5.4000E-03, 3.4000E-03, 
            3.0000E-03, 8.8000E-04, 2.9000E-04, 1.7000E-04, 3.5000E-05, 
            8.8000E-06, 4.5000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.8100E-01, 1.8100E-01, 1.8100E-01, 1.8100E-01, 
            1.8100E-01, 1.8000E-01, 1.8000E-01, 1.8000E-01, 1.7900E-01, 
            1.7800E-01, 1.7700E-01, 1.7300E-01, 1.6600E-01, 1.5700E-01, 
            1.4500E-01, 1.3100E-01, 1.1600E-01, 8.6000E-02, 4.7500E-02, 
            1.6600E-02, 1.1600E-02, 1.1300E-02, 9.1200E-03, 6.0400E-03, 
            2.0000E-03, 1.0000E-03, 4.8000E-04, 6.7000E-05, 6.0000E-05, 
            2.4000E-05, 2.7000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {1.9900E-01, 1.9900E-01, 1.9900E-01, 1.9900E-01, 
            1.9900E-01, 1.9800E-01, 1.9800E-01, 1.9800E-01, 1.9700E-01, 
            1.9500E-01, 1.9300E-01, 1.8700E-01, 1.7700E-01, 1.6300E-01, 
            1.4800E-01, 1.3000E-01, 1.1100E-01, 7.6100E-02, 3.7600E-02, 
            1.4300E-02, 1.2600E-02, 1.1200E-02, 7.6700E-03, 4.3800E-03, 
            1.5000E-03, 1.0000E-03, 3.2000E-04, 7.9000E-05, 6.3000E-05, 
            1.6000E-05, 1.0000E-06} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.7200E-01, 1.7200E-01, 1.7200E-01, 1.7200E-01, 
            1.7200E-01, 1.7200E-01, 1.7200E-01, 1.7200E-01, 1.7100E-01, 
            1.7100E-01, 1.7100E-01, 1.6900E-01, 1.6600E-01, 1.6000E-01, 
            1.5200E-01, 1.4100E-01, 1.2900E-01, 1.0100E-01, 6.0300E-02, 
            1.9600E-02, 7.0300E-03, 5.2900E-03, 5.1900E-03, 4.5000E-03, 
            2.3000E-03, 3.7000E-04, 3.2000E-04, 1.2000E-04, 3.1000E-05, 
            2.4000E-06, 5.5000E-08} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.7700E-01, 1.7700E-01, 1.7700E-01, 1.7700E-01, 
            1.7700E-01, 1.7700E-01, 1.7700E-01, 1.7700E-01, 1.7700E-01, 
            1.7700E-01, 1.7600E-01, 1.7400E-01, 1.7000E-01, 1.6300E-01, 
            1.5400E-01, 1.4200E-01, 1.2800E-01, 9.8200E-02, 5.6700E-02, 
            1.7400E-02, 6.5400E-03, 5.3500E-03, 5.1800E-03, 4.3300E-03, 
            2.1000E-03, 3.6000E-04, 3.2000E-04, 1.1000E-04, 2.6000E-05, 
            1.7000E-06, 3.0000E-08} );

    subshell_half_profiles[21] = 
      std::vector<double>( {7.1400E-01, 7.0900E-01, 6.9600E-01, 6.7500E-01, 
            6.4600E-01, 5.7200E-01, 4.8300E-01, 3.9000E-01, 3.0200E-01, 
            2.2600E-01, 1.6500E-01, 8.8300E-02, 5.6700E-02, 4.8800E-02, 
            4.8300E-02, 4.7000E-02, 4.2700E-02, 2.8600E-02, 1.1300E-02, 
            4.6800E-03, 4.3000E-03, 2.6900E-03, 1.2700E-03, 6.5500E-04, 
            5.1000E-04, 1.6000E-04, 4.8000E-05, 2.8000E-05, 5.8000E-06, 
            1.4000E-06, 7.4000E-07} );

    subshell_half_profiles[22] = 
      std::vector<double>( {4.9600E-01, 4.9600E-01, 4.9600E-01, 4.9600E-01, 
            4.9400E-01, 4.8600E-01, 4.6800E-01, 4.3700E-01, 3.9500E-01, 
            3.4500E-01, 2.9100E-01, 1.8700E-01, 1.0800E-01, 5.8700E-02, 
            3.3100E-02, 2.2400E-02, 1.9200E-02, 1.8700E-02, 1.4400E-02, 
            4.7300E-03, 1.7400E-03, 1.5500E-03, 1.3800E-03, 9.7400E-04, 
            3.2000E-04, 1.4000E-04, 6.7000E-05, 9.1000E-06, 8.1000E-06, 
            3.2000E-06, 3.6000E-07} );

    subshell_half_profiles[23] = 
      std::vector<double>( {5.7100E-01, 5.7100E-01, 5.7000E-01, 5.6900E-01, 
            5.6600E-01, 5.5100E-01, 5.1800E-01, 4.6800E-01, 4.0400E-01, 
            3.3300E-01, 2.6400E-01, 1.4800E-01, 7.4800E-02, 3.8000E-02, 
            2.3500E-02, 1.9500E-02, 1.9100E-02, 1.7800E-02, 1.0900E-02, 
            2.8000E-03, 1.5300E-03, 1.4600E-03, 1.0800E-03, 6.3900E-04, 
            2.0000E-04, 1.2000E-04, 4.0000E-05, 9.5000E-06, 7.5000E-06, 
            1.9000E-06, 1.2000E-07} );

    subshell_half_profiles[24] = 
      std::vector<double>( {2.6500E+00, 2.4700E+00, 2.0100E+00, 1.4400E+00, 
            9.0800E-01, 2.7400E-01, 9.5200E-02, 7.5400E-02, 7.3200E-02, 
            6.1700E-02, 4.5800E-02, 2.0000E-02, 7.9400E-03, 4.0300E-03, 
            3.2600E-03, 3.2200E-03, 3.0900E-03, 2.2300E-03, 8.9300E-04, 
            2.9800E-04, 2.7500E-04, 1.7600E-04, 8.3700E-05, 4.2000E-05, 
            3.2000E-05, 1.0000E-05, 3.0000E-06, 1.7000E-06, 3.6000E-07, 
            9.0000E-08, 4.6000E-08} );
  }
};

//! The default Compton profile generator implementation for A=88
template<>
struct DefaultComptonProfileGeneratorImpl<88u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 25 );

    subshell_half_profiles[0] = 
      std::vector<double>( {7.9600E-03, 7.9600E-03, 7.9600E-03, 7.9600E-03, 
            7.9600E-03, 7.9600E-03, 7.9600E-03, 7.9600E-03, 7.9600E-03, 
            7.9600E-03, 7.9600E-03, 7.9500E-03, 7.9500E-03, 7.9500E-03, 
            7.9500E-03, 7.9500E-03, 7.9500E-03, 7.9400E-03, 7.9300E-03, 
            7.9200E-03, 7.9000E-03, 7.8700E-03, 7.8400E-03, 7.8000E-03, 
            7.7000E-03, 7.4000E-03, 7.1000E-03, 6.1000E-03, 5.1000E-03, 
            3.3000E-03, 1.2000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.8500E-02, 2.8500E-02, 2.8500E-02, 2.8500E-02, 
            2.8500E-02, 2.8500E-02, 2.8400E-02, 2.8400E-02, 2.8400E-02, 
            2.8400E-02, 2.8400E-02, 2.8400E-02, 2.8300E-02, 2.8300E-02, 
            2.8200E-02, 2.8100E-02, 2.8100E-02, 2.7900E-02, 2.7600E-02, 
            2.7000E-02, 2.6200E-02, 2.5200E-02, 2.4100E-02, 2.3000E-02, 
            2.0000E-02, 1.4000E-02, 8.1000E-03, 2.2000E-03, 8.2000E-04, 
            6.7000E-04, 3.0000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3700E-02, 
            1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3700E-02, 
            1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3700E-02, 
            1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3700E-02, 
            1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3700E-02, 1.3600E-02, 
            1.3000E-02, 1.3000E-02, 1.1000E-02, 7.7000E-03, 4.6000E-03, 
            1.4000E-03, 1.7000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.6000E-02, 1.6000E-02, 1.6000E-02, 1.6000E-02, 
            1.6000E-02, 1.6000E-02, 1.6000E-02, 1.6000E-02, 1.6000E-02, 
            1.6000E-02, 1.6000E-02, 1.6000E-02, 1.6000E-02, 1.6000E-02, 
            1.6000E-02, 1.6000E-02, 1.6000E-02, 1.6000E-02, 1.6000E-02, 
            1.6000E-02, 1.6000E-02, 1.6000E-02, 1.5900E-02, 1.5800E-02, 
            1.5800E-02, 1.4000E-02, 1.2000E-02, 7.2000E-03, 3.6000E-03, 
            8.2000E-04, 5.8000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {6.2300E-02, 6.2300E-02, 6.2300E-02, 6.2300E-02, 
            6.2300E-02, 6.2200E-02, 6.2100E-02, 6.2000E-02, 6.1900E-02, 
            6.1700E-02, 6.1600E-02, 6.1100E-02, 6.0600E-02, 6.0000E-02, 
            5.9400E-02, 5.8600E-02, 5.7800E-02, 5.5900E-02, 5.2500E-02, 
            4.6100E-02, 3.9000E-02, 3.1900E-02, 2.5300E-02, 1.9600E-02, 
            1.1000E-02, 4.9000E-03, 4.7000E-03, 1.9000E-03, 4.3000E-04, 
            1.5000E-04, 7.6000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.6400E-02, 3.6400E-02, 3.6400E-02, 3.6400E-02, 
            3.6400E-02, 3.6400E-02, 3.6400E-02, 3.6400E-02, 3.6400E-02, 
            3.6400E-02, 3.6400E-02, 3.6400E-02, 3.6400E-02, 3.6400E-02, 
            3.6300E-02, 3.6300E-02, 3.6300E-02, 3.6300E-02, 3.6100E-02, 
            3.5700E-02, 3.4800E-02, 3.3500E-02, 3.1700E-02, 2.9400E-02, 
            2.4000E-02, 1.0000E-02, 3.3000E-03, 1.3000E-03, 1.2000E-03, 
            4.3000E-04, 5.1000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {4.0100E-02, 4.0100E-02, 4.0100E-02, 4.0100E-02, 
            4.0100E-02, 4.0100E-02, 4.0100E-02, 4.0100E-02, 4.0100E-02, 
            4.0100E-02, 4.0100E-02, 4.0100E-02, 4.0100E-02, 4.0100E-02, 
            4.0100E-02, 4.0100E-02, 4.0000E-02, 3.9900E-02, 3.9700E-02, 
            3.9000E-02, 3.7700E-02, 3.5800E-02, 3.3200E-02, 3.0000E-02, 
            2.3000E-02, 8.0000E-03, 2.5000E-03, 1.7000E-03, 1.2000E-03, 
            2.9000E-04, 1.9000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.5800E-02, 2.5800E-02, 2.5800E-02, 2.5800E-02, 
            2.5800E-02, 2.5800E-02, 2.5800E-02, 2.5800E-02, 2.5800E-02, 
            2.5800E-02, 2.5800E-02, 2.5800E-02, 2.5800E-02, 2.5800E-02, 
            2.5800E-02, 2.5800E-02, 2.5800E-02, 2.5800E-02, 2.5800E-02, 
            2.5800E-02, 2.5700E-02, 2.5600E-02, 2.5300E-02, 2.4900E-02, 
            2.4000E-02, 1.7000E-02, 1.0000E-02, 2.6000E-03, 6.4000E-04, 
            5.1000E-05, 1.2000E-06} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.6600E-02, 2.6600E-02, 2.6600E-02, 2.6600E-02, 
            2.6600E-02, 2.6600E-02, 2.6600E-02, 2.6600E-02, 2.6600E-02, 
            2.6600E-02, 2.6600E-02, 2.6600E-02, 2.6600E-02, 2.6600E-02, 
            2.6600E-02, 2.6600E-02, 2.6600E-02, 2.6600E-02, 2.6600E-02, 
            2.6600E-02, 2.6500E-02, 2.6300E-02, 2.6100E-02, 2.5600E-02, 
            2.4000E-02, 1.7000E-02, 9.7000E-03, 2.3000E-03, 5.3000E-04, 
            3.7000E-05, 6.8000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.2500E-01, 1.2500E-01, 1.2400E-01, 1.2400E-01, 
            1.2400E-01, 1.2400E-01, 1.2300E-01, 1.2200E-01, 1.2100E-01, 
            1.2000E-01, 1.1800E-01, 1.1500E-01, 1.1000E-01, 1.0600E-01, 
            1.0100E-01, 9.5000E-02, 8.9300E-02, 7.7300E-02, 5.9700E-02, 
            3.5500E-02, 2.0900E-02, 1.4600E-02, 1.3000E-02, 1.2900E-02, 
            1.1000E-02, 2.8000E-03, 1.3000E-03, 7.2000E-04, 1.6000E-04, 
            3.9000E-05, 2.1000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {7.8200E-02, 7.8200E-02, 7.8200E-02, 7.8200E-02, 
            7.8200E-02, 7.8200E-02, 7.8200E-02, 7.8200E-02, 7.8200E-02, 
            7.8200E-02, 7.8200E-02, 7.8100E-02, 7.7900E-02, 7.7700E-02, 
            7.7300E-02, 7.6800E-02, 7.6200E-02, 7.4300E-02, 7.0000E-02, 
            5.8700E-02, 4.4500E-02, 3.0500E-02, 1.9400E-02, 1.2000E-02, 
            6.0000E-03, 4.8000E-03, 2.0000E-03, 3.2000E-04, 2.9000E-04, 
            1.2000E-04, 1.4000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {8.5600E-02, 8.5600E-02, 8.5600E-02, 8.5600E-02, 
            8.5600E-02, 8.5600E-02, 8.5600E-02, 8.5600E-02, 8.5500E-02, 
            8.5500E-02, 8.5500E-02, 8.5300E-02, 8.5100E-02, 8.4700E-02, 
            8.4200E-02, 8.3400E-02, 8.2500E-02, 7.9700E-02, 7.3500E-02, 
            5.8400E-02, 4.1000E-02, 2.5900E-02, 1.5300E-02, 9.4200E-03, 
            6.1000E-03, 4.4000E-03, 1.4000E-03, 4.0000E-04, 3.1000E-04, 
            8.1000E-05, 5.3000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {6.3500E-02, 6.3500E-02, 6.3500E-02, 6.3500E-02, 
            6.3500E-02, 6.3500E-02, 6.3500E-02, 6.3500E-02, 6.3500E-02, 
            6.3500E-02, 6.3500E-02, 6.3500E-02, 6.3500E-02, 6.3500E-02, 
            6.3400E-02, 6.3400E-02, 6.3300E-02, 6.3100E-02, 6.2100E-02, 
            5.8300E-02, 5.1300E-02, 4.1800E-02, 3.1500E-02, 2.2200E-02, 
            9.6000E-03, 2.4000E-03, 2.2000E-03, 8.0000E-04, 2.0000E-04, 
            1.6000E-05, 3.8000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {6.5200E-02, 6.5200E-02, 6.5200E-02, 6.5200E-02, 
            6.5200E-02, 6.5200E-02, 6.5200E-02, 6.5200E-02, 6.5200E-02, 
            6.5200E-02, 6.5200E-02, 6.5200E-02, 6.5200E-02, 6.5200E-02, 
            6.5200E-02, 6.5100E-02, 6.5000E-02, 6.4700E-02, 6.3600E-02, 
            5.9300E-02, 5.1500E-02, 4.1200E-02, 3.0500E-02, 2.1000E-02, 
            8.7000E-03, 2.5000E-03, 2.2000E-03, 7.3000E-04, 1.7000E-04, 
            1.2000E-05, 2.1000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {5.1700E-02, 5.1700E-02, 5.1700E-02, 5.1700E-02, 
            5.1700E-02, 5.1700E-02, 5.1700E-02, 5.1700E-02, 5.1700E-02, 
            5.1700E-02, 5.1700E-02, 5.1700E-02, 5.1700E-02, 5.1700E-02, 
            5.1700E-02, 5.1700E-02, 5.1700E-02, 5.1600E-02, 5.1400E-02, 
            5.0200E-02, 4.7300E-02, 4.2800E-02, 3.7100E-02, 3.1000E-02, 
            2.0000E-02, 5.3000E-03, 1.3000E-03, 9.6000E-05, 1.0000E-05, 
            2.7000E-07, 1.9000E-09} );

    subshell_half_profiles[15] = 
      std::vector<double>( {5.2400E-02, 5.2400E-02, 5.2400E-02, 5.2400E-02, 
            5.2400E-02, 5.2400E-02, 5.2400E-02, 5.2400E-02, 5.2400E-02, 
            5.2400E-02, 5.2400E-02, 5.2400E-02, 5.2400E-02, 5.2400E-02, 
            5.2400E-02, 5.2400E-02, 5.2400E-02, 5.2300E-02, 5.2100E-02, 
            5.0700E-02, 4.7700E-02, 4.2900E-02, 3.7000E-02, 3.0800E-02, 
            2.0000E-02, 5.1000E-03, 1.2000E-03, 8.6000E-05, 8.6000E-06, 
            2.1000E-07, 1.2000E-09} );

    subshell_half_profiles[16] = 
      std::vector<double>( {2.6600E-01, 2.6600E-01, 2.6500E-01, 2.6400E-01, 
            2.6200E-01, 2.5700E-01, 2.5000E-01, 2.4200E-01, 2.3200E-01, 
            2.2100E-01, 2.0900E-01, 1.8300E-01, 1.5500E-01, 1.2900E-01, 
            1.0500E-01, 8.3300E-02, 6.5800E-02, 4.1900E-02, 2.8000E-02, 
            2.6100E-02, 2.0700E-02, 1.1900E-02, 5.9300E-03, 3.5700E-03, 
            3.1000E-03, 9.8000E-04, 3.0000E-04, 1.8000E-04, 3.9000E-05, 
            8.9000E-06, 4.8000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.7500E-01, 1.7500E-01, 1.7500E-01, 1.7500E-01, 
            1.7500E-01, 1.7500E-01, 1.7500E-01, 1.7400E-01, 1.7400E-01, 
            1.7300E-01, 1.7200E-01, 1.6800E-01, 1.6200E-01, 1.5400E-01, 
            1.4300E-01, 1.3100E-01, 1.1700E-01, 8.8400E-02, 5.0600E-02, 
            1.7900E-02, 1.1700E-02, 1.1400E-02, 9.5500E-03, 6.5500E-03, 
            2.3000E-03, 1.1000E-03, 5.3000E-04, 7.0000E-05, 6.1000E-05, 
            2.5000E-05, 3.0000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {1.9200E-01, 1.9200E-01, 1.9200E-01, 1.9200E-01, 
            1.9200E-01, 1.9200E-01, 1.9200E-01, 1.9200E-01, 1.9100E-01, 
            1.9000E-01, 1.8800E-01, 1.8200E-01, 1.7300E-01, 1.6100E-01, 
            1.4700E-01, 1.3000E-01, 1.1300E-01, 7.9100E-02, 4.0400E-02, 
            1.5000E-02, 1.2600E-02, 1.1500E-02, 8.2200E-03, 4.8400E-03, 
            1.6000E-03, 1.1000E-03, 3.5000E-04, 8.1000E-05, 6.6000E-05, 
            1.7000E-05, 1.1000E-06} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.6500E-01, 1.6500E-01, 1.6500E-01, 1.6500E-01, 
            1.6500E-01, 1.6500E-01, 1.6500E-01, 1.6500E-01, 1.6400E-01, 
            1.6400E-01, 1.6400E-01, 1.6300E-01, 1.6000E-01, 1.5600E-01, 
            1.4900E-01, 1.4000E-01, 1.2900E-01, 1.0300E-01, 6.4600E-02, 
            2.2300E-02, 7.8200E-03, 5.4400E-03, 5.3500E-03, 4.7800E-03, 
            2.6000E-03, 3.9000E-04, 3.4000E-04, 1.4000E-04, 3.5000E-05, 
            2.8000E-06, 6.5000E-08} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.7000E-01, 1.7000E-01, 1.7000E-01, 1.7000E-01, 
            1.7000E-01, 1.7000E-01, 1.7000E-01, 1.7000E-01, 1.7000E-01, 
            1.6900E-01, 1.6900E-01, 1.6800E-01, 1.6400E-01, 1.5900E-01, 
            1.5100E-01, 1.4100E-01, 1.2900E-01, 1.0100E-01, 6.1200E-02, 
            1.9900E-02, 7.2100E-03, 5.4900E-03, 5.3800E-03, 4.6300E-03, 
            2.3000E-03, 3.8000E-04, 3.4000E-04, 1.2000E-04, 2.9000E-05, 
            2.0000E-06, 3.5000E-08} );

    subshell_half_profiles[21] = 
      std::vector<double>( {6.5700E-01, 6.5300E-01, 6.4300E-01, 6.2600E-01, 
            6.0300E-01, 5.4200E-01, 4.6800E-01, 3.8900E-01, 3.1100E-01, 
            2.4100E-01, 1.8100E-01, 1.0100E-01, 6.3000E-02, 5.1000E-02, 
            4.9400E-02, 4.8900E-02, 4.5900E-02, 3.3000E-02, 1.4000E-02, 
            5.1100E-03, 4.7600E-03, 3.1800E-03, 1.5700E-03, 7.7900E-04, 
            5.5000E-04, 1.9000E-04, 5.3000E-05, 3.3000E-05, 7.1000E-06, 
            1.6000E-06, 8.4000E-07} );

    subshell_half_profiles[22] = 
      std::vector<double>( {4.5600E-01, 4.5600E-01, 4.5600E-01, 4.5500E-01, 
            4.5400E-01, 4.4900E-01, 4.3600E-01, 4.1400E-01, 3.8200E-01, 
            3.4300E-01, 2.9800E-01, 2.0600E-01, 1.2800E-01, 7.3700E-02, 
            4.2200E-02, 2.7000E-02, 2.1400E-02, 2.0000E-02, 1.6800E-02, 
            6.1000E-03, 2.0900E-03, 1.7300E-03, 1.6000E-03, 1.1800E-03, 
            4.1000E-04, 1.6000E-04, 8.2000E-05, 1.1000E-05, 9.2000E-06, 
            3.8000E-06, 4.5000E-07} );

    subshell_half_profiles[23] = 
      std::vector<double>( {5.2000E-01, 5.2000E-01, 5.2000E-01, 5.1900E-01, 
            5.1700E-01, 5.0700E-01, 4.8400E-01, 4.4800E-01, 3.9900E-01, 
            3.4100E-01, 2.8200E-01, 1.7200E-01, 9.4600E-02, 4.9900E-02, 
            2.9300E-02, 2.2200E-02, 2.0800E-02, 2.0100E-02, 1.3500E-02, 
            3.6800E-03, 1.7700E-03, 1.7000E-03, 1.3200E-03, 8.1000E-04, 
            2.5000E-04, 1.5000E-04, 5.0000E-05, 1.1000E-05, 9.0000E-06, 
            2.4000E-06, 1.5000E-07} );

    subshell_half_profiles[24] = 
      std::vector<double>( {2.1900E+00, 2.0800E+00, 1.7900E+00, 1.4000E+00, 
            1.0000E+00, 4.0700E-01, 1.5100E-01, 8.7300E-02, 8.2000E-02, 
            7.9000E-02, 6.8000E-02, 3.7900E-02, 1.6900E-02, 7.7300E-03, 
            5.0200E-03, 4.6400E-03, 4.6000E-03, 3.6800E-03, 1.6200E-03, 
            4.6400E-04, 4.2500E-04, 2.9300E-04, 1.4500E-04, 7.0400E-05, 
            4.8000E-05, 1.7000E-05, 4.6000E-06, 2.8000E-06, 6.2000E-07, 
            1.4000E-07, 7.3000E-08} );
  }
};

//! The default Compton profile generator implementation for A=89
template<>
struct DefaultComptonProfileGeneratorImpl<89u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 26 );

    subshell_half_profiles[0] = 
      std::vector<double>( {7.8200E-03, 7.8200E-03, 7.8200E-03, 7.8200E-03, 
            7.8200E-03, 7.8200E-03, 7.8200E-03, 7.8200E-03, 7.8200E-03, 
            7.8200E-03, 7.8200E-03, 7.8200E-03, 7.8200E-03, 7.8200E-03, 
            7.8200E-03, 7.8100E-03, 7.8100E-03, 7.8100E-03, 7.8000E-03, 
            7.7800E-03, 7.7600E-03, 7.7400E-03, 7.7100E-03, 7.6700E-03, 
            7.6000E-03, 7.3000E-03, 7.0000E-03, 6.1000E-03, 5.1000E-03, 
            3.3000E-03, 1.2000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.8000E-02, 2.8000E-02, 2.8000E-02, 2.8000E-02, 
            2.8000E-02, 2.8000E-02, 2.8000E-02, 2.8000E-02, 2.8000E-02, 
            2.8000E-02, 2.7900E-02, 2.7900E-02, 2.7900E-02, 2.7800E-02, 
            2.7800E-02, 2.7700E-02, 2.7600E-02, 2.7500E-02, 2.7200E-02, 
            2.6600E-02, 2.5800E-02, 2.4900E-02, 2.3900E-02, 2.2700E-02, 
            2.0000E-02, 1.4000E-02, 8.2000E-03, 2.3000E-03, 8.3000E-04, 
            6.6000E-04, 3.1000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.3500E-02, 1.3500E-02, 1.3500E-02, 1.3500E-02, 
            1.3500E-02, 1.3500E-02, 1.3500E-02, 1.3500E-02, 1.3500E-02, 
            1.3500E-02, 1.3500E-02, 1.3500E-02, 1.3500E-02, 1.3500E-02, 
            1.3500E-02, 1.3500E-02, 1.3500E-02, 1.3500E-02, 1.3500E-02, 
            1.3500E-02, 1.3500E-02, 1.3500E-02, 1.3400E-02, 1.3400E-02, 
            1.3000E-02, 1.3000E-02, 1.1000E-02, 7.8000E-03, 4.7000E-03, 
            1.5000E-03, 1.8000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5800E-02, 
            1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5800E-02, 
            1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5800E-02, 
            1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5800E-02, 
            1.5800E-02, 1.5800E-02, 1.5800E-02, 1.5700E-02, 1.5600E-02, 
            1.5000E-02, 1.4000E-02, 1.2000E-02, 7.3000E-03, 3.7000E-03, 
            8.5000E-04, 6.2000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {6.1300E-02, 6.1300E-02, 6.1300E-02, 6.1300E-02, 
            6.1300E-02, 6.1200E-02, 6.1100E-02, 6.1000E-02, 6.0900E-02, 
            6.0800E-02, 6.0600E-02, 6.0200E-02, 5.9700E-02, 5.9100E-02, 
            5.8500E-02, 5.7800E-02, 5.7000E-02, 5.5100E-02, 5.2000E-02, 
            4.5800E-02, 3.8900E-02, 3.2100E-02, 2.5600E-02, 2.0000E-02, 
            1.2000E-02, 4.9000E-03, 4.6000E-03, 2.0000E-03, 4.6000E-04, 
            1.5000E-04, 7.9000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.5800E-02, 3.5800E-02, 3.5800E-02, 3.5800E-02, 
            3.5800E-02, 3.5800E-02, 3.5800E-02, 3.5800E-02, 3.5800E-02, 
            3.5800E-02, 3.5800E-02, 3.5800E-02, 3.5700E-02, 3.5700E-02, 
            3.5700E-02, 3.5700E-02, 3.5700E-02, 3.5700E-02, 3.5500E-02, 
            3.5100E-02, 3.4300E-02, 3.3100E-02, 3.1400E-02, 2.9300E-02, 
            2.4000E-02, 1.1000E-02, 3.5000E-03, 1.3000E-03, 1.2000E-03, 
            4.5000E-04, 5.5000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {3.9500E-02, 3.9500E-02, 3.9500E-02, 3.9500E-02, 
            3.9500E-02, 3.9500E-02, 3.9500E-02, 3.9500E-02, 3.9500E-02, 
            3.9500E-02, 3.9500E-02, 3.9500E-02, 3.9500E-02, 3.9500E-02, 
            3.9500E-02, 3.9500E-02, 3.9500E-02, 3.9400E-02, 3.9200E-02, 
            3.8500E-02, 3.7300E-02, 3.5500E-02, 3.3000E-02, 3.0000E-02, 
            2.3000E-02, 8.3000E-03, 2.6000E-03, 1.7000E-03, 1.2000E-03, 
            3.0000E-04, 2.1000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 
            2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 
            2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 
            2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 
            2.5400E-02, 2.5300E-02, 2.5200E-02, 2.5000E-02, 2.4600E-02, 
            2.3000E-02, 1.7000E-02, 1.0000E-02, 2.8000E-03, 6.8000E-04, 
            5.6000E-05, 1.4000E-06} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 
            2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 
            2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 
            2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 
            2.6200E-02, 2.6100E-02, 2.6000E-02, 2.5700E-02, 2.5300E-02, 
            2.4000E-02, 1.7000E-02, 9.9000E-03, 2.5000E-03, 5.7000E-04, 
            4.0000E-05, 7.5000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.2200E-01, 1.2200E-01, 1.2200E-01, 1.2200E-01, 
            1.2200E-01, 1.2100E-01, 1.2100E-01, 1.2000E-01, 1.1900E-01, 
            1.1700E-01, 1.1600E-01, 1.1300E-01, 1.0900E-01, 1.0400E-01, 
            9.9400E-02, 9.4100E-02, 8.8600E-02, 7.7100E-02, 6.0100E-02, 
            3.6300E-02, 2.1500E-02, 1.4700E-02, 1.2800E-02, 1.2700E-02, 
            1.1000E-02, 3.0000E-03, 1.2000E-03, 7.5000E-04, 1.7000E-04, 
            3.8000E-05, 2.1000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {7.6700E-02, 7.6700E-02, 7.6700E-02, 7.6700E-02, 
            7.6700E-02, 7.6700E-02, 7.6700E-02, 7.6700E-02, 7.6700E-02, 
            7.6700E-02, 7.6600E-02, 7.6600E-02, 7.6400E-02, 7.6200E-02, 
            7.5900E-02, 7.5400E-02, 7.4800E-02, 7.3100E-02, 6.9100E-02, 
            5.8500E-02, 4.5000E-02, 3.1400E-02, 2.0300E-02, 1.2600E-02, 
            6.1000E-03, 4.8000E-03, 2.1000E-03, 3.3000E-04, 2.9000E-04, 
            1.2000E-04, 1.5000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {8.4100E-02, 8.4100E-02, 8.4100E-02, 8.4100E-02, 
            8.4100E-02, 8.4100E-02, 8.4100E-02, 8.4100E-02, 8.4000E-02, 
            8.4000E-02, 8.4000E-02, 8.3900E-02, 8.3600E-02, 8.3300E-02, 
            8.2800E-02, 8.2100E-02, 8.1200E-02, 7.8600E-02, 7.2800E-02, 
            5.8500E-02, 4.1700E-02, 2.6700E-02, 1.6000E-02, 9.8200E-03, 
            6.1000E-03, 4.6000E-03, 1.5000E-03, 4.0000E-04, 3.2000E-04, 
            8.5000E-05, 5.8000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {6.2300E-02, 6.2300E-02, 6.2300E-02, 6.2300E-02, 
            6.2300E-02, 6.2300E-02, 6.2300E-02, 6.2300E-02, 6.2300E-02, 
            6.2300E-02, 6.2300E-02, 6.2300E-02, 6.2300E-02, 6.2300E-02, 
            6.2200E-02, 6.2200E-02, 6.2100E-02, 6.1900E-02, 6.1100E-02, 
            5.7600E-02, 5.1100E-02, 4.2100E-02, 3.2200E-02, 2.3100E-02, 
            1.0000E-02, 2.4000E-03, 2.2000E-03, 8.4000E-04, 2.2000E-04, 
            1.8000E-05, 4.2000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {6.4000E-02, 6.4000E-02, 6.4000E-02, 6.4000E-02, 
            6.4000E-02, 6.4000E-02, 6.4000E-02, 6.4000E-02, 6.4000E-02, 
            6.4000E-02, 6.4000E-02, 6.4000E-02, 6.4000E-02, 6.4000E-02, 
            6.3900E-02, 6.3900E-02, 6.3800E-02, 6.3500E-02, 6.2600E-02, 
            5.8700E-02, 5.1400E-02, 4.1600E-02, 3.1200E-02, 2.1900E-02, 
            9.3000E-03, 2.5000E-03, 2.2000E-03, 7.7000E-04, 1.8000E-04, 
            1.3000E-05, 2.3000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {5.0500E-02, 5.0500E-02, 5.0500E-02, 5.0500E-02, 
            5.0500E-02, 5.0500E-02, 5.0500E-02, 5.0500E-02, 5.0500E-02, 
            5.0500E-02, 5.0500E-02, 5.0500E-02, 5.0500E-02, 5.0500E-02, 
            5.0500E-02, 5.0500E-02, 5.0500E-02, 5.0400E-02, 5.0200E-02, 
            4.9200E-02, 4.6700E-02, 4.2600E-02, 3.7300E-02, 3.1500E-02, 
            2.1000E-02, 5.7000E-03, 1.4000E-03, 1.1000E-04, 1.1000E-05, 
            3.1000E-07, 2.2000E-09} );

    subshell_half_profiles[15] = 
      std::vector<double>( {5.1200E-02, 5.1200E-02, 5.1200E-02, 5.1200E-02, 
            5.1200E-02, 5.1200E-02, 5.1200E-02, 5.1200E-02, 5.1200E-02, 
            5.1200E-02, 5.1200E-02, 5.1200E-02, 5.1200E-02, 5.1200E-02, 
            5.1200E-02, 5.1200E-02, 5.1100E-02, 5.1100E-02, 5.0900E-02, 
            4.9800E-02, 4.7100E-02, 4.2800E-02, 3.7200E-02, 3.1300E-02, 
            2.0000E-02, 5.4000E-03, 1.3000E-03, 9.7000E-05, 9.8000E-06, 
            2.4000E-07, 1.4000E-09} );

    subshell_half_profiles[16] = 
      std::vector<double>( {2.5800E-01, 2.5800E-01, 2.5700E-01, 2.5600E-01, 
            2.5400E-01, 2.5000E-01, 2.4400E-01, 2.3600E-01, 2.2700E-01, 
            2.1700E-01, 2.0500E-01, 1.8100E-01, 1.5500E-01, 1.3000E-01, 
            1.0600E-01, 8.5500E-02, 6.8100E-02, 4.3700E-02, 2.8400E-02, 
            2.5900E-02, 2.1400E-02, 1.2900E-02, 6.5200E-03, 3.7700E-03, 
            3.1000E-03, 1.1000E-03, 3.0000E-04, 1.9000E-04, 4.4000E-05, 
            8.9000E-06, 5.0000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.6900E-01, 1.6900E-01, 1.6900E-01, 1.6900E-01, 
            1.6900E-01, 1.6900E-01, 1.6900E-01, 1.6900E-01, 1.6900E-01, 
            1.6800E-01, 1.6700E-01, 1.6400E-01, 1.5800E-01, 1.5100E-01, 
            1.4200E-01, 1.3000E-01, 1.1800E-01, 9.0500E-02, 5.3500E-02, 
            1.9300E-02, 1.1800E-02, 1.1500E-02, 9.9300E-03, 7.0600E-03, 
            2.5000E-03, 1.1000E-03, 5.7000E-04, 7.3000E-05, 6.3000E-05, 
            2.7000E-05, 3.3000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {1.8700E-01, 1.8700E-01, 1.8700E-01, 1.8700E-01, 
            1.8700E-01, 1.8600E-01, 1.8600E-01, 1.8600E-01, 1.8500E-01, 
            1.8400E-01, 1.8200E-01, 1.7700E-01, 1.7000E-01, 1.5900E-01, 
            1.4600E-01, 1.3100E-01, 1.1400E-01, 8.1900E-02, 4.3300E-02, 
            1.5700E-02, 1.2700E-02, 1.1800E-02, 8.7600E-03, 5.3100E-03, 
            1.7000E-03, 1.1000E-03, 3.9000E-04, 8.3000E-05, 6.9000E-05, 
            1.9000E-05, 1.3000E-06} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.5800E-01, 1.5800E-01, 1.5800E-01, 1.5800E-01, 
            1.5800E-01, 1.5800E-01, 1.5800E-01, 1.5800E-01, 1.5800E-01, 
            1.5800E-01, 1.5800E-01, 1.5700E-01, 1.5500E-01, 1.5100E-01, 
            1.4500E-01, 1.3800E-01, 1.2800E-01, 1.0500E-01, 6.8500E-02, 
            2.5100E-02, 8.7600E-03, 5.6200E-03, 5.4900E-03, 5.0300E-03, 
            2.9000E-03, 4.2000E-04, 3.6000E-04, 1.5000E-04, 4.0000E-05, 
            3.2000E-06, 7.6000E-08} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.6300E-01, 1.6300E-01, 1.6300E-01, 1.6300E-01, 
            1.6300E-01, 1.6300E-01, 1.6300E-01, 1.6300E-01, 1.6300E-01, 
            1.6300E-01, 1.6300E-01, 1.6100E-01, 1.5900E-01, 1.5500E-01, 
            1.4800E-01, 1.4000E-01, 1.2900E-01, 1.0400E-01, 6.5300E-02, 
            2.2600E-02, 7.9900E-03, 5.6500E-03, 5.5500E-03, 4.9100E-03, 
            2.6000E-03, 4.1000E-04, 3.6000E-04, 1.4000E-04, 3.3000E-05, 
            2.3000E-06, 4.1000E-08} );

    subshell_half_profiles[21] = 
      std::vector<double>( {6.1700E-01, 6.1400E-01, 6.0600E-01, 5.9100E-01, 
            5.7200E-01, 5.2000E-01, 4.5500E-01, 3.8400E-01, 3.1400E-01, 
            2.4900E-01, 1.9200E-01, 1.1100E-01, 6.8600E-02, 5.2800E-02, 
            4.9700E-02, 4.9500E-02, 4.7600E-02, 3.6500E-02, 1.6700E-02, 
            5.5200E-03, 5.1100E-03, 3.6300E-03, 1.8700E-03, 9.1300E-04, 
            5.9000E-04, 2.3000E-04, 5.8000E-05, 3.7000E-05, 8.5000E-06, 
            1.7000E-06, 9.4000E-07} );

    subshell_half_profiles[22] = 
      std::vector<double>( {4.2900E-01, 4.2900E-01, 4.2900E-01, 4.2900E-01, 
            4.2800E-01, 4.2400E-01, 4.1400E-01, 3.9600E-01, 3.7000E-01, 
            3.3700E-01, 2.9900E-01, 2.1600E-01, 1.4200E-01, 8.5700E-02, 
            5.0400E-02, 3.1600E-02, 2.3400E-02, 2.0600E-02, 1.8300E-02, 
            7.4400E-03, 2.4500E-03, 1.8500E-03, 1.7600E-03, 1.3500E-03, 
            5.0000E-04, 1.8000E-04, 9.6000E-05, 1.2000E-05, 1.0000E-05, 
            4.4000E-06, 5.3000E-07} );

    subshell_half_profiles[23] = 
      std::vector<double>( {4.8400E-01, 4.8400E-01, 4.8400E-01, 4.8400E-01, 
            4.8200E-01, 4.7500E-01, 4.5800E-01, 4.3000E-01, 3.9000E-01, 
            3.4300E-01, 2.9100E-01, 1.9000E-01, 1.1100E-01, 6.1200E-02, 
            3.5400E-02, 2.4900E-02, 2.2000E-02, 2.1500E-02, 1.5800E-02, 
            4.6600E-03, 1.9900E-03, 1.8900E-03, 1.5400E-03, 9.7900E-04, 
            3.0000E-04, 1.7000E-04, 6.1000E-05, 1.2000E-05, 1.0000E-05, 
            2.8000E-06, 1.9000E-07} );

    subshell_half_profiles[24] = 
      std::vector<double>( {6.0800E-01, 6.0800E-01, 6.0800E-01, 6.0700E-01, 
            6.0600E-01, 5.9200E-01, 5.5500E-01, 4.9300E-01, 4.1600E-01, 
            3.3600E-01, 2.6100E-01, 1.4600E-01, 7.5800E-02, 3.7400E-02, 
            1.8400E-02, 9.9400E-03, 6.7200E-03, 5.6500E-03, 5.1400E-03, 
            2.3600E-03, 7.5000E-04, 3.5400E-04, 3.2300E-04, 3.0700E-04, 
            1.8000E-04, 2.6000E-05, 2.1000E-05, 9.2000E-06, 2.5000E-06, 
            2.0000E-07, 4.7000E-09} );

    subshell_half_profiles[25] = 
      std::vector<double>( {1.9900E+00, 1.9100E+00, 1.6800E+00, 1.3600E+00, 
            1.0200E+00, 4.7300E-01, 1.9000E-01, 9.7300E-02, 8.2100E-02, 
            8.1300E-02, 7.5200E-02, 4.8600E-02, 2.4300E-02, 1.1300E-02, 
            6.4400E-03, 5.3300E-03, 5.2700E-03, 4.6000E-03, 2.2600E-03, 
            5.8900E-04, 5.1400E-04, 3.8100E-04, 1.9800E-04, 9.4800E-05, 
            5.8000E-05, 2.3000E-05, 5.7000E-06, 3.6000E-06, 8.4000E-07, 
            1.7000E-07, 9.3000E-08} );
  }
};

//! The default Compton profile generator implementation for A=90
template<>
struct DefaultComptonProfileGeneratorImpl<90u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 26 );

    subshell_half_profiles[0] = 
      std::vector<double>( {7.6900E-03, 7.6900E-03, 7.6900E-03, 7.6900E-03, 
            7.6900E-03, 7.6900E-03, 7.6900E-03, 7.6900E-03, 7.6900E-03, 
            7.6900E-03, 7.6900E-03, 7.6900E-03, 7.6900E-03, 7.6800E-03, 
            7.6800E-03, 7.6800E-03, 7.6800E-03, 7.6800E-03, 7.6700E-03, 
            7.6500E-03, 7.6300E-03, 7.6100E-03, 7.5800E-03, 7.5500E-03, 
            7.5000E-03, 7.2000E-03, 6.9000E-03, 6.0000E-03, 5.1000E-03, 
            3.3000E-03, 1.3000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.7500E-02, 2.7500E-02, 2.7500E-02, 2.7500E-02, 
            2.7500E-02, 2.7500E-02, 2.7500E-02, 2.7500E-02, 2.7500E-02, 
            2.7500E-02, 2.7500E-02, 2.7500E-02, 2.7400E-02, 2.7400E-02, 
            2.7300E-02, 2.7300E-02, 2.7200E-02, 2.7000E-02, 2.6800E-02, 
            2.6200E-02, 2.5400E-02, 2.4600E-02, 2.3600E-02, 2.2500E-02, 
            2.0000E-02, 1.4000E-02, 8.4000E-03, 2.4000E-03, 8.5000E-04, 
            6.5000E-04, 3.2000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.3300E-02, 1.3300E-02, 1.3300E-02, 1.3300E-02, 
            1.3300E-02, 1.3300E-02, 1.3300E-02, 1.3300E-02, 1.3300E-02, 
            1.3300E-02, 1.3300E-02, 1.3300E-02, 1.3300E-02, 1.3300E-02, 
            1.3300E-02, 1.3300E-02, 1.3300E-02, 1.3300E-02, 1.3300E-02, 
            1.3300E-02, 1.3200E-02, 1.3200E-02, 1.3200E-02, 1.3200E-02, 
            1.3000E-02, 1.2000E-02, 1.1000E-02, 7.8000E-03, 4.7000E-03, 
            1.5000E-03, 2.0000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.5600E-02, 1.5600E-02, 1.5600E-02, 1.5600E-02, 
            1.5600E-02, 1.5600E-02, 1.5600E-02, 1.5600E-02, 1.5600E-02, 
            1.5600E-02, 1.5600E-02, 1.5600E-02, 1.5600E-02, 1.5600E-02, 
            1.5600E-02, 1.5600E-02, 1.5600E-02, 1.5600E-02, 1.5600E-02, 
            1.5600E-02, 1.5600E-02, 1.5600E-02, 1.5500E-02, 1.5400E-02, 
            1.5000E-02, 1.4000E-02, 1.2000E-02, 7.4000E-03, 3.8000E-03, 
            8.9000E-04, 6.7000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {6.0300E-02, 6.0300E-02, 6.0300E-02, 6.0300E-02, 
            6.0300E-02, 6.0200E-02, 6.0100E-02, 6.0000E-02, 5.9900E-02, 
            5.9800E-02, 5.9600E-02, 5.9200E-02, 5.8800E-02, 5.8200E-02, 
            5.7600E-02, 5.6900E-02, 5.6200E-02, 5.4400E-02, 5.1400E-02, 
            4.5400E-02, 3.8900E-02, 3.2200E-02, 2.5900E-02, 2.0300E-02, 
            1.2000E-02, 4.9000E-03, 4.6000E-03, 2.1000E-03, 5.0000E-04, 
            1.4000E-04, 8.1000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.5200E-02, 3.5200E-02, 3.5200E-02, 3.5200E-02, 
            3.5200E-02, 3.5200E-02, 3.5200E-02, 3.5200E-02, 3.5200E-02, 
            3.5200E-02, 3.5200E-02, 3.5200E-02, 3.5200E-02, 3.5100E-02, 
            3.5100E-02, 3.5100E-02, 3.5100E-02, 3.5100E-02, 3.5000E-02, 
            3.4600E-02, 3.3800E-02, 3.2700E-02, 3.1100E-02, 2.9100E-02, 
            2.4000E-02, 1.1000E-02, 3.7000E-03, 1.3000E-03, 1.2000E-03, 
            4.7000E-04, 5.9000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {3.9000E-02, 3.9000E-02, 3.9000E-02, 3.9000E-02, 
            3.9000E-02, 3.9000E-02, 3.9000E-02, 3.9000E-02, 3.9000E-02, 
            3.9000E-02, 3.9000E-02, 3.9000E-02, 3.9000E-02, 3.9000E-02, 
            3.9000E-02, 3.8900E-02, 3.8900E-02, 3.8800E-02, 3.8700E-02, 
            3.8000E-02, 3.6900E-02, 3.5100E-02, 3.2800E-02, 2.9900E-02, 
            2.3000E-02, 8.6000E-03, 2.7000E-03, 1.7000E-03, 1.2000E-03, 
            3.2000E-04, 2.2000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.5000E-02, 2.5000E-02, 2.5000E-02, 2.5000E-02, 
            2.5000E-02, 2.5000E-02, 2.5000E-02, 2.5000E-02, 2.5000E-02, 
            2.5000E-02, 2.5000E-02, 2.5000E-02, 2.5000E-02, 2.5000E-02, 
            2.5000E-02, 2.5000E-02, 2.5000E-02, 2.5000E-02, 2.5000E-02, 
            2.5000E-02, 2.5000E-02, 2.4900E-02, 2.4700E-02, 2.4300E-02, 
            2.3000E-02, 1.7000E-02, 1.1000E-02, 2.9000E-03, 7.3000E-04, 
            6.1000E-05, 1.5000E-06} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.5900E-02, 2.5900E-02, 2.5900E-02, 2.5900E-02, 
            2.5900E-02, 2.5900E-02, 2.5900E-02, 2.5900E-02, 2.5900E-02, 
            2.5900E-02, 2.5900E-02, 2.5900E-02, 2.5900E-02, 2.5900E-02, 
            2.5900E-02, 2.5900E-02, 2.5900E-02, 2.5900E-02, 2.5900E-02, 
            2.5800E-02, 2.5800E-02, 2.5700E-02, 2.5400E-02, 2.5000E-02, 
            2.4000E-02, 1.7000E-02, 1.0000E-02, 2.6000E-03, 6.0000E-04, 
            4.4000E-05, 8.3000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.2000E-01, 1.2000E-01, 1.2000E-01, 1.2000E-01, 
            1.1900E-01, 1.1900E-01, 1.1800E-01, 1.1800E-01, 1.1700E-01, 
            1.1500E-01, 1.1400E-01, 1.1100E-01, 1.0700E-01, 1.0300E-01, 
            9.8200E-02, 9.3200E-02, 8.7900E-02, 7.6900E-02, 6.0400E-02, 
            3.7000E-02, 2.2000E-02, 1.4900E-02, 1.2700E-02, 1.2500E-02, 
            1.1000E-02, 3.2000E-03, 1.2000E-03, 7.9000E-04, 1.9000E-04, 
            3.8000E-05, 2.2000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {7.5200E-02, 7.5200E-02, 7.5200E-02, 7.5200E-02, 
            7.5200E-02, 7.5200E-02, 7.5200E-02, 7.5200E-02, 7.5200E-02, 
            7.5200E-02, 7.5200E-02, 7.5100E-02, 7.5000E-02, 7.4800E-02, 
            7.4500E-02, 7.4100E-02, 7.3500E-02, 7.1900E-02, 6.8200E-02, 
            5.8300E-02, 4.5400E-02, 3.2200E-02, 2.1100E-02, 1.3300E-02, 
            6.3000E-03, 4.9000E-03, 2.3000E-03, 3.3000E-04, 2.9000E-04, 
            1.3000E-04, 1.6000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {8.2600E-02, 8.2600E-02, 8.2600E-02, 8.2600E-02, 
            8.2600E-02, 8.2600E-02, 8.2600E-02, 8.2600E-02, 8.2600E-02, 
            8.2600E-02, 8.2500E-02, 8.2400E-02, 8.2200E-02, 8.1900E-02, 
            8.1400E-02, 8.0800E-02, 8.0000E-02, 7.7600E-02, 7.2100E-02, 
            5.8500E-02, 4.2300E-02, 2.7600E-02, 1.6700E-02, 1.0300E-02, 
            6.1000E-03, 4.7000E-03, 1.6000E-03, 3.9000E-04, 3.3000E-04, 
            9.0000E-05, 6.2000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {6.1100E-02, 6.1100E-02, 6.1100E-02, 6.1100E-02, 
            6.1100E-02, 6.1100E-02, 6.1100E-02, 6.1100E-02, 6.1100E-02, 
            6.1100E-02, 6.1100E-02, 6.1100E-02, 6.1100E-02, 6.1100E-02, 
            6.1100E-02, 6.1000E-02, 6.1000E-02, 6.0800E-02, 6.0000E-02, 
            5.6900E-02, 5.0900E-02, 4.2400E-02, 3.2900E-02, 2.3800E-02, 
            1.1000E-02, 2.4000E-03, 2.2000E-03, 8.9000E-04, 2.4000E-04, 
            2.0000E-05, 4.8000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {6.2800E-02, 6.2800E-02, 6.2800E-02, 6.2800E-02, 
            6.2800E-02, 6.2800E-02, 6.2800E-02, 6.2800E-02, 6.2800E-02, 
            6.2800E-02, 6.2800E-02, 6.2800E-02, 6.2800E-02, 6.2800E-02, 
            6.2800E-02, 6.2700E-02, 6.2700E-02, 6.2400E-02, 6.1500E-02, 
            5.8000E-02, 5.1200E-02, 4.2000E-02, 3.1900E-02, 2.2700E-02, 
            9.8000E-03, 2.5000E-03, 2.3000E-03, 8.1000E-04, 2.0000E-04, 
            1.4000E-05, 2.6000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {4.9300E-02, 4.9300E-02, 4.9300E-02, 4.9300E-02, 
            4.9300E-02, 4.9300E-02, 4.9300E-02, 4.9300E-02, 4.9300E-02, 
            4.9300E-02, 4.9300E-02, 4.9300E-02, 4.9300E-02, 4.9300E-02, 
            4.9300E-02, 4.9300E-02, 4.9300E-02, 4.9300E-02, 4.9100E-02, 
            4.8200E-02, 4.6000E-02, 4.2300E-02, 3.7400E-02, 3.1900E-02, 
            2.1000E-02, 6.1000E-03, 1.6000E-03, 1.2000E-04, 1.3000E-05, 
            3.6000E-07, 2.6000E-09} );

    subshell_half_profiles[15] = 
      std::vector<double>( {5.0000E-02, 5.0000E-02, 5.0000E-02, 5.0000E-02, 
            5.0000E-02, 5.0000E-02, 5.0000E-02, 5.0000E-02, 5.0000E-02, 
            5.0000E-02, 5.0000E-02, 5.0000E-02, 5.0000E-02, 5.0000E-02, 
            5.0000E-02, 5.0000E-02, 5.0000E-02, 5.0000E-02, 4.9800E-02, 
            4.8800E-02, 4.6500E-02, 4.2500E-02, 3.7400E-02, 3.1700E-02, 
            2.1000E-02, 5.8000E-03, 1.5000E-03, 1.1000E-04, 1.1000E-05, 
            2.8000E-07, 1.7000E-09} );

    subshell_half_profiles[16] = 
      std::vector<double>( {2.5100E-01, 2.5000E-01, 2.5000E-01, 2.4900E-01, 
            2.4700E-01, 2.4300E-01, 2.3700E-01, 2.3000E-01, 2.2200E-01, 
            2.1200E-01, 2.0200E-01, 1.7900E-01, 1.5400E-01, 1.3000E-01, 
            1.0800E-01, 8.7500E-02, 7.0200E-02, 4.5400E-02, 2.8800E-02, 
            2.5700E-02, 2.2000E-02, 1.3800E-02, 7.1400E-03, 4.0100E-03, 
            3.1000E-03, 1.2000E-03, 3.1000E-04, 2.0000E-04, 5.0000E-05, 
            9.0000E-06, 5.3000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.6400E-01, 1.6400E-01, 1.6400E-01, 1.6400E-01, 
            1.6400E-01, 1.6400E-01, 1.6400E-01, 1.6400E-01, 1.6400E-01, 
            1.6300E-01, 1.6200E-01, 1.5900E-01, 1.5500E-01, 1.4800E-01, 
            1.4000E-01, 1.2900E-01, 1.1800E-01, 9.2200E-02, 5.6300E-02, 
            2.0800E-02, 1.1900E-02, 1.1500E-02, 1.0300E-02, 7.5500E-03, 
            2.8000E-03, 1.1000E-03, 6.2000E-04, 7.8000E-05, 6.4000E-05, 
            2.9000E-05, 3.7000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {1.8100E-01, 1.8100E-01, 1.8100E-01, 1.8100E-01, 
            1.8100E-01, 1.8100E-01, 1.8100E-01, 1.8100E-01, 1.8000E-01, 
            1.7900E-01, 1.7800E-01, 1.7300E-01, 1.6600E-01, 1.5700E-01, 
            1.4500E-01, 1.3100E-01, 1.1500E-01, 8.4400E-02, 4.6000E-02, 
            1.6600E-02, 1.2700E-02, 1.2100E-02, 9.2600E-03, 5.8000E-03, 
            1.9000E-03, 1.1000E-03, 4.3000E-04, 8.5000E-05, 7.2000E-05, 
            2.0000E-05, 1.4000E-06} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.5200E-01, 1.5200E-01, 1.5200E-01, 1.5200E-01, 
            1.5200E-01, 1.5200E-01, 1.5200E-01, 1.5200E-01, 1.5200E-01, 
            1.5200E-01, 1.5200E-01, 1.5100E-01, 1.5000E-01, 1.4700E-01, 
            1.4200E-01, 1.3500E-01, 1.2700E-01, 1.0700E-01, 7.2000E-02, 
            2.8000E-02, 9.8400E-03, 5.8400E-03, 5.6000E-03, 5.2500E-03, 
            3.1000E-03, 4.6000E-04, 3.7000E-04, 1.6000E-04, 4.5000E-05, 
            3.7000E-06, 8.9000E-08} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.5700E-01, 1.5700E-01, 1.5700E-01, 1.5700E-01, 
            1.5700E-01, 1.5700E-01, 1.5700E-01, 1.5700E-01, 1.5700E-01, 
            1.5700E-01, 1.5700E-01, 1.5600E-01, 1.5400E-01, 1.5000E-01, 
            1.4500E-01, 1.3800E-01, 1.2800E-01, 1.0600E-01, 6.9000E-02, 
            2.5300E-02, 8.8800E-03, 5.8100E-03, 5.6900E-03, 5.1700E-03, 
            2.9000E-03, 4.4000E-04, 3.7000E-04, 1.5000E-04, 3.7000E-05, 
            2.7000E-06, 4.8000E-08} );

    subshell_half_profiles[21] = 
      std::vector<double>( {5.8500E-01, 5.8200E-01, 5.7500E-01, 5.6200E-01, 
            5.4500E-01, 5.0000E-01, 4.4300E-01, 3.7900E-01, 3.1500E-01, 
            2.5400E-01, 2.0000E-01, 1.1900E-01, 7.4000E-02, 5.4800E-02, 
            4.9800E-02, 4.9400E-02, 4.8400E-02, 3.9300E-02, 1.9500E-02, 
            5.9800E-03, 5.3700E-03, 4.0600E-03, 2.1900E-03, 1.0700E-03, 
            6.2000E-04, 2.6000E-04, 6.3000E-05, 4.1000E-05, 1.0000E-05, 
            1.8000E-06, 1.0000E-06} );

    subshell_half_profiles[22] = 
      std::vector<double>( {4.0800E-01, 4.0800E-01, 4.0800E-01, 4.0700E-01, 
            4.0700E-01, 4.0300E-01, 3.9500E-01, 3.8100E-01, 3.5900E-01, 
            3.3100E-01, 2.9700E-01, 2.2300E-01, 1.5200E-01, 9.6400E-02, 
            5.8400E-02, 3.6400E-02, 2.5700E-02, 2.0900E-02, 1.9400E-02, 
            8.7900E-03, 2.8600E-03, 1.9400E-03, 1.8800E-03, 1.5100E-03, 
            5.9000E-04, 1.9000E-04, 1.1000E-04, 1.3000E-05, 1.1000E-05, 
            5.0000E-06, 6.2000E-07} );

    subshell_half_profiles[23] = 
      std::vector<double>( {4.5600E-01, 4.5600E-01, 4.5600E-01, 4.5600E-01, 
            4.5500E-01, 4.4900E-01, 4.3600E-01, 4.1300E-01, 3.8100E-01, 
            3.4000E-01, 2.9500E-01, 2.0200E-01, 1.2500E-01, 7.1900E-02, 
            4.1800E-02, 2.7900E-02, 2.3200E-02, 2.2300E-02, 1.7700E-02, 
            5.7300E-03, 2.2100E-03, 2.0400E-03, 1.7300E-03, 1.1500E-03, 
            3.6000E-04, 1.9000E-04, 7.2000E-05, 1.4000E-05, 1.2000E-05, 
            3.3000E-06, 2.2000E-07} );

    subshell_half_profiles[24] = 
      std::vector<double>( {5.3500E-01, 5.3500E-01, 5.3500E-01, 5.3500E-01, 
            5.3400E-01, 5.2800E-01, 5.0800E-01, 4.7100E-01, 4.1800E-01, 
            3.5600E-01, 2.9300E-01, 1.8200E-01, 1.0400E-01, 5.5700E-02, 
            2.8900E-02, 1.5500E-02, 9.5300E-03, 6.8100E-03, 6.4600E-03, 
            3.3500E-03, 1.1200E-03, 4.8000E-04, 4.1200E-04, 4.0000E-04, 
            2.5000E-04, 3.6000E-05, 2.8000E-05, 1.3000E-05, 3.5000E-06, 
            2.9000E-07, 6.9000E-09} );

    subshell_half_profiles[25] = 
      std::vector<double>( {1.8600E+00, 1.7900E+00, 1.6000E+00, 1.3300E+00, 
            1.0300E+00, 5.1700E-01, 2.2200E-01, 1.0800E-01, 8.1600E-02, 
            7.9900E-02, 7.7100E-02, 5.5700E-02, 3.0800E-02, 1.5000E-02, 
            8.0200E-03, 5.9100E-03, 5.6200E-03, 5.2200E-03, 2.8800E-03, 
            7.1600E-04, 5.7800E-04, 4.5800E-04, 2.5100E-04, 1.2000E-04, 
            6.6000E-05, 2.8000E-05, 6.7000E-06, 4.4000E-06, 1.1000E-06, 
            1.9000E-07, 1.1000E-07} );
  }
};

//! The default Compton profile generator implementation for A=91
template<>
struct DefaultComptonProfileGeneratorImpl<91u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 27 );

    subshell_half_profiles[0] = 
      std::vector<double>( {7.5600E-03, 7.5600E-03, 7.5600E-03, 7.5600E-03, 
            7.5600E-03, 7.5600E-03, 7.5600E-03, 7.5600E-03, 7.5600E-03, 
            7.5600E-03, 7.5600E-03, 7.5600E-03, 7.5500E-03, 7.5500E-03, 
            7.5500E-03, 7.5500E-03, 7.5500E-03, 7.5500E-03, 7.5400E-03, 
            7.5200E-03, 7.5000E-03, 7.4800E-03, 7.4500E-03, 7.4200E-03, 
            7.3000E-03, 7.1000E-03, 6.8000E-03, 6.0000E-03, 5.0000E-03, 
            3.3000E-03, 1.3000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.7100E-02, 2.7100E-02, 2.7100E-02, 2.7100E-02, 
            2.7100E-02, 2.7100E-02, 2.7100E-02, 2.7100E-02, 2.7100E-02, 
            2.7100E-02, 2.7000E-02, 2.7000E-02, 2.7000E-02, 2.6900E-02, 
            2.6900E-02, 2.6800E-02, 2.6800E-02, 2.6600E-02, 2.6400E-02, 
            2.5800E-02, 2.5100E-02, 2.4300E-02, 2.3300E-02, 2.2300E-02, 
            2.0000E-02, 1.4000E-02, 8.5000E-03, 2.5000E-03, 8.7000E-04, 
            6.4000E-04, 3.3000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.3000E-02, 1.3000E-02, 1.3000E-02, 1.3000E-02, 
            1.3000E-02, 1.3000E-02, 1.3000E-02, 1.3000E-02, 1.3000E-02, 
            1.3000E-02, 1.3000E-02, 1.3000E-02, 1.3000E-02, 1.3000E-02, 
            1.3000E-02, 1.3000E-02, 1.3000E-02, 1.3000E-02, 1.3000E-02, 
            1.3000E-02, 1.3000E-02, 1.3000E-02, 1.3000E-02, 1.2900E-02, 
            1.2900E-02, 1.2000E-02, 1.1000E-02, 7.8000E-03, 4.8000E-03, 
            1.6000E-03, 2.1000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.5400E-02, 1.5400E-02, 1.5400E-02, 1.5400E-02, 
            1.5400E-02, 1.5400E-02, 1.5400E-02, 1.5400E-02, 1.5400E-02, 
            1.5400E-02, 1.5400E-02, 1.5400E-02, 1.5400E-02, 1.5400E-02, 
            1.5400E-02, 1.5400E-02, 1.5400E-02, 1.5400E-02, 1.5400E-02, 
            1.5400E-02, 1.5400E-02, 1.5400E-02, 1.5300E-02, 1.5300E-02, 
            1.5000E-02, 1.4000E-02, 1.2000E-02, 7.4000E-03, 3.9000E-03, 
            9.3000E-04, 7.1000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {5.9300E-02, 5.9300E-02, 5.9300E-02, 5.9300E-02, 
            5.9300E-02, 5.9200E-02, 5.9200E-02, 5.9100E-02, 5.9000E-02, 
            5.8800E-02, 5.8700E-02, 5.8300E-02, 5.7900E-02, 5.7400E-02, 
            5.6800E-02, 5.6100E-02, 5.5400E-02, 5.3700E-02, 5.0800E-02, 
            4.5100E-02, 3.8800E-02, 3.2300E-02, 2.6100E-02, 2.0600E-02, 
            1.2000E-02, 4.8000E-03, 4.5000E-03, 2.2000E-03, 5.5000E-04, 
            1.4000E-04, 8.3000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.4600E-02, 3.4600E-02, 3.4600E-02, 3.4600E-02, 
            3.4600E-02, 3.4600E-02, 3.4600E-02, 3.4600E-02, 3.4600E-02, 
            3.4600E-02, 3.4600E-02, 3.4600E-02, 3.4600E-02, 3.4600E-02, 
            3.4600E-02, 3.4500E-02, 3.4500E-02, 3.4500E-02, 3.4400E-02, 
            3.4000E-02, 3.3400E-02, 3.2300E-02, 3.0800E-02, 2.8900E-02, 
            2.4000E-02, 1.1000E-02, 4.0000E-03, 1.3000E-03, 1.2000E-03, 
            4.9000E-04, 6.4000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {3.8400E-02, 3.8400E-02, 3.8400E-02, 3.8400E-02, 
            3.8400E-02, 3.8400E-02, 3.8400E-02, 3.8400E-02, 3.8400E-02, 
            3.8400E-02, 3.8400E-02, 3.8400E-02, 3.8400E-02, 3.8400E-02, 
            3.8400E-02, 3.8400E-02, 3.8400E-02, 3.8300E-02, 3.8100E-02, 
            3.7600E-02, 3.6500E-02, 3.4800E-02, 3.2600E-02, 2.9800E-02, 
            2.3000E-02, 8.9000E-03, 2.8000E-03, 1.6000E-03, 1.2000E-03, 
            3.3000E-04, 2.4000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.4700E-02, 2.4700E-02, 2.4700E-02, 2.4700E-02, 
            2.4700E-02, 2.4700E-02, 2.4700E-02, 2.4700E-02, 2.4700E-02, 
            2.4700E-02, 2.4700E-02, 2.4700E-02, 2.4700E-02, 2.4700E-02, 
            2.4700E-02, 2.4700E-02, 2.4700E-02, 2.4700E-02, 2.4700E-02, 
            2.4700E-02, 2.4600E-02, 2.4500E-02, 2.4300E-02, 2.4000E-02, 
            2.3000E-02, 1.7000E-02, 1.1000E-02, 3.0000E-03, 7.7000E-04, 
            6.6000E-05, 1.7000E-06} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.5500E-02, 2.5500E-02, 2.5500E-02, 2.5500E-02, 
            2.5500E-02, 2.5500E-02, 2.5500E-02, 2.5500E-02, 2.5500E-02, 
            2.5500E-02, 2.5500E-02, 2.5500E-02, 2.5500E-02, 2.5500E-02, 
            2.5500E-02, 2.5500E-02, 2.5500E-02, 2.5500E-02, 2.5500E-02, 
            2.5500E-02, 2.5400E-02, 2.5300E-02, 2.5100E-02, 2.4700E-02, 
            2.3000E-02, 1.7000E-02, 1.0000E-02, 2.7000E-03, 6.4000E-04, 
            4.8000E-05, 9.1000E-07} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.1800E-01, 1.1800E-01, 1.1800E-01, 1.1700E-01, 
            1.1700E-01, 1.1700E-01, 1.1600E-01, 1.1500E-01, 1.1400E-01, 
            1.1300E-01, 1.1200E-01, 1.0900E-01, 1.0600E-01, 1.0200E-01, 
            9.7100E-02, 9.2300E-02, 8.7200E-02, 7.6600E-02, 6.0700E-02, 
            3.7700E-02, 2.2600E-02, 1.5100E-02, 1.2700E-02, 1.2300E-02, 
            1.1000E-02, 3.4000E-03, 1.2000E-03, 8.2000E-04, 2.1000E-04, 
            3.7000E-05, 2.3000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {7.3800E-02, 7.3800E-02, 7.3800E-02, 7.3800E-02, 
            7.3800E-02, 7.3800E-02, 7.3800E-02, 7.3800E-02, 7.3800E-02, 
            7.3700E-02, 7.3700E-02, 7.3700E-02, 7.3600E-02, 7.3400E-02, 
            7.3100E-02, 7.2700E-02, 7.2200E-02, 7.0800E-02, 6.7300E-02, 
            5.8100E-02, 4.5800E-02, 3.3000E-02, 2.2000E-02, 1.4000E-02, 
            6.5000E-03, 4.9000E-03, 2.4000E-03, 3.4000E-04, 2.9000E-04, 
            1.4000E-04, 1.8000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {8.1200E-02, 8.1200E-02, 8.1200E-02, 8.1200E-02, 
            8.1200E-02, 8.1200E-02, 8.1200E-02, 8.1200E-02, 8.1200E-02, 
            8.1200E-02, 8.1100E-02, 8.1000E-02, 8.0800E-02, 8.0600E-02, 
            8.0100E-02, 7.9500E-02, 7.8700E-02, 7.6500E-02, 7.1400E-02, 
            5.8500E-02, 4.2900E-02, 2.8400E-02, 1.7400E-02, 1.0700E-02, 
            6.1000E-03, 4.8000E-03, 1.7000E-03, 3.9000E-04, 3.3000E-04, 
            9.5000E-05, 6.7000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {6.0000E-02, 6.0000E-02, 6.0000E-02, 6.0000E-02, 
            6.0000E-02, 6.0000E-02, 6.0000E-02, 6.0000E-02, 6.0000E-02, 
            6.0000E-02, 6.0000E-02, 6.0000E-02, 6.0000E-02, 6.0000E-02, 
            6.0000E-02, 5.9900E-02, 5.9900E-02, 5.9700E-02, 5.9000E-02, 
            5.6200E-02, 5.0600E-02, 4.2600E-02, 3.3400E-02, 2.4600E-02, 
            1.1000E-02, 2.4000E-03, 2.2000E-03, 9.3000E-04, 2.6000E-04, 
            2.2000E-05, 5.3000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {6.1700E-02, 6.1700E-02, 6.1700E-02, 6.1700E-02, 
            6.1700E-02, 6.1700E-02, 6.1700E-02, 6.1700E-02, 6.1700E-02, 
            6.1700E-02, 6.1700E-02, 6.1700E-02, 6.1700E-02, 6.1700E-02, 
            6.1700E-02, 6.1600E-02, 6.1600E-02, 6.1300E-02, 6.0500E-02, 
            5.7300E-02, 5.1000E-02, 4.2300E-02, 3.2500E-02, 2.3400E-02, 
            1.0000E-02, 2.5000E-03, 2.3000E-03, 8.5000E-04, 2.1000E-04, 
            1.6000E-05, 2.9000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {4.8200E-02, 4.8200E-02, 4.8200E-02, 4.8200E-02, 
            4.8200E-02, 4.8200E-02, 4.8200E-02, 4.8200E-02, 4.8200E-02, 
            4.8200E-02, 4.8200E-02, 4.8200E-02, 4.8200E-02, 4.8200E-02, 
            4.8200E-02, 4.8200E-02, 4.8200E-02, 4.8200E-02, 4.8100E-02, 
            4.7300E-02, 4.5400E-02, 4.2000E-02, 3.7400E-02, 3.2200E-02, 
            2.2000E-02, 6.4000E-03, 1.7000E-03, 1.4000E-04, 1.5000E-05, 
            4.2000E-07, 3.0000E-09} );

    subshell_half_profiles[15] = 
      std::vector<double>( {4.8900E-02, 4.8900E-02, 4.8900E-02, 4.8900E-02, 
            4.8900E-02, 4.8900E-02, 4.8900E-02, 4.8900E-02, 4.8900E-02, 
            4.8900E-02, 4.8900E-02, 4.8900E-02, 4.8900E-02, 4.8900E-02, 
            4.8900E-02, 4.8900E-02, 4.8900E-02, 4.8900E-02, 4.8700E-02, 
            4.7900E-02, 4.5800E-02, 4.2300E-02, 3.7500E-02, 3.2100E-02, 
            2.2000E-02, 6.2000E-03, 1.6000E-03, 1.2000E-04, 1.3000E-05, 
            3.2000E-07, 1.9000E-09} );

    subshell_half_profiles[16] = 
      std::vector<double>( {2.4500E-01, 2.4400E-01, 2.4400E-01, 2.4300E-01, 
            2.4100E-01, 2.3800E-01, 2.3200E-01, 2.2500E-01, 2.1800E-01, 
            2.0900E-01, 1.9900E-01, 1.7700E-01, 1.5400E-01, 1.3100E-01, 
            1.0900E-01, 8.9000E-02, 7.2000E-02, 4.6900E-02, 2.9200E-02, 
            2.5400E-02, 2.2400E-02, 1.4600E-02, 7.7700E-03, 4.2800E-03, 
            3.1000E-03, 1.3000E-03, 3.2000E-04, 2.1000E-04, 5.6000E-05, 
            9.0000E-06, 5.5000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.6100E-01, 1.6100E-01, 1.6100E-01, 1.6100E-01, 
            1.6100E-01, 1.6100E-01, 1.6000E-01, 1.6000E-01, 1.6000E-01, 
            1.5900E-01, 1.5900E-01, 1.5600E-01, 1.5200E-01, 1.4600E-01, 
            1.3800E-01, 1.2800E-01, 1.1700E-01, 9.3300E-02, 5.8400E-02, 
            2.2100E-02, 1.2100E-02, 1.1400E-02, 1.0400E-02, 7.9500E-03, 
            3.1000E-03, 1.1000E-03, 6.6000E-04, 8.2000E-05, 6.4000E-05, 
            3.1000E-05, 4.0000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {1.7700E-01, 1.7700E-01, 1.7700E-01, 1.7700E-01, 
            1.7700E-01, 1.7700E-01, 1.7700E-01, 1.7700E-01, 1.7600E-01, 
            1.7500E-01, 1.7400E-01, 1.7000E-01, 1.6400E-01, 1.5500E-01, 
            1.4300E-01, 1.3000E-01, 1.1600E-01, 8.6200E-02, 4.8200E-02, 
            1.7400E-02, 1.2600E-02, 1.2200E-02, 9.6500E-03, 6.2200E-03, 
            2.1000E-03, 1.2000E-03, 4.6000E-04, 8.6000E-05, 7.4000E-05, 
            2.2000E-05, 1.5000E-06} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.4900E-01, 1.4900E-01, 1.4900E-01, 1.4900E-01, 
            1.4900E-01, 1.4900E-01, 1.4900E-01, 1.4900E-01, 1.4900E-01, 
            1.4900E-01, 1.4900E-01, 1.4800E-01, 1.4700E-01, 1.4400E-01, 
            1.4000E-01, 1.3400E-01, 1.2600E-01, 1.0700E-01, 7.3700E-02, 
            2.9900E-02, 1.0600E-02, 5.9200E-03, 5.5500E-03, 5.3000E-03, 
            3.3000E-03, 4.9000E-04, 3.7000E-04, 1.7000E-04, 4.9000E-05, 
            4.2000E-06, 1.0000E-07} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5300E-01, 
            1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5300E-01, 
            1.5300E-01, 1.5300E-01, 1.5200E-01, 1.5000E-01, 1.4700E-01, 
            1.4300E-01, 1.3600E-01, 1.2700E-01, 1.0600E-01, 7.1200E-02, 
            2.7400E-02, 9.6500E-03, 5.8900E-03, 5.7000E-03, 5.2900E-03, 
            3.1000E-03, 4.6000E-04, 3.8000E-04, 1.6000E-04, 4.1000E-05, 
            3.0000E-06, 5.5000E-08} );

    subshell_half_profiles[21] = 
      std::vector<double>( {2.0700E-01, 2.0700E-01, 2.0700E-01, 2.0700E-01, 
            2.0700E-01, 2.0700E-01, 2.0700E-01, 2.0600E-01, 2.0600E-01, 
            2.0400E-01, 2.0200E-01, 1.9400E-01, 1.8200E-01, 1.6700E-01, 
            1.5000E-01, 1.3300E-01, 1.1600E-01, 8.5200E-02, 5.0000E-02, 
            1.8100E-02, 5.9900E-03, 2.2800E-03, 1.4200E-03, 1.3200E-03, 
            1.2000E-03, 4.9000E-04, 1.4000E-04, 1.1000E-05, 1.2000E-06, 
            3.5000E-08, 2.6000E-10} );

    subshell_half_profiles[22] = 
      std::vector<double>( {5.8000E-01, 5.7800E-01, 5.7000E-01, 5.5800E-01, 
            5.4200E-01, 4.9700E-01, 4.4200E-01, 3.8000E-01, 3.1700E-01, 
            2.5700E-01, 2.0300E-01, 1.2200E-01, 7.4800E-02, 5.4200E-02, 
            4.8300E-02, 4.7700E-02, 4.7000E-02, 3.9200E-02, 2.0400E-02, 
            6.0600E-03, 5.2300E-03, 4.1600E-03, 2.3600E-03, 1.1600E-03, 
            6.1000E-04, 2.8000E-04, 6.5000E-05, 4.2000E-05, 1.1000E-05, 
            1.8000E-06, 1.1000E-06} );

    subshell_half_profiles[23] = 
      std::vector<double>( {4.0100E-01, 4.0100E-01, 4.0100E-01, 4.0100E-01, 
            4.0000E-01, 3.9700E-01, 3.9000E-01, 3.7600E-01, 3.5600E-01, 
            3.2900E-01, 2.9700E-01, 2.2600E-01, 1.5600E-01, 1.0000E-01, 
            6.1300E-02, 3.8100E-02, 2.6300E-02, 2.0200E-02, 1.9200E-02, 
            9.3900E-03, 3.1000E-03, 1.9200E-03, 1.8800E-03, 1.5700E-03, 
            6.6000E-04, 1.9000E-04, 1.2000E-04, 1.4000E-05, 1.1000E-05, 
            5.2000E-06, 6.8000E-07} );

    subshell_half_profiles[24] = 
      std::vector<double>( {4.5900E-01, 4.5900E-01, 4.5900E-01, 4.5900E-01, 
            4.5800E-01, 4.5200E-01, 4.3800E-01, 4.1500E-01, 3.8200E-01, 
            3.4100E-01, 2.9500E-01, 2.0200E-01, 1.2500E-01, 7.1800E-02, 
            4.1400E-02, 2.7100E-02, 2.2000E-02, 2.0900E-02, 1.7000E-02, 
            5.8700E-03, 2.1600E-03, 1.9200E-03, 1.6900E-03, 1.1600E-03, 
            3.7000E-04, 1.8000E-04, 7.4000E-05, 1.3000E-05, 1.1000E-05, 
            3.3000E-06, 2.3000E-07} );

    subshell_half_profiles[25] = 
      std::vector<double>( {5.5800E-01, 5.5800E-01, 5.5800E-01, 5.5800E-01, 
            5.5700E-01, 5.4800E-01, 5.2300E-01, 4.7700E-01, 4.1700E-01, 
            3.4900E-01, 2.8300E-01, 1.7100E-01, 9.6100E-02, 5.1100E-02, 
            2.6400E-02, 1.4100E-02, 8.6000E-03, 5.9400E-03, 5.6700E-03, 
            3.1200E-03, 1.0900E-03, 4.5000E-04, 3.6500E-04, 3.5800E-04, 
            2.4000E-04, 3.4000E-05, 2.5000E-05, 1.2000E-05, 3.4000E-06, 
            2.9000E-07, 7.0000E-09} );

    subshell_half_profiles[26] = 
      std::vector<double>( {1.9300E+00, 1.8600E+00, 1.6500E+00, 1.3600E+00, 
            1.0400E+00, 5.0100E-01, 2.0700E-01, 9.8600E-02, 7.5600E-02, 
            7.4400E-02, 7.1200E-02, 5.0300E-02, 2.7400E-02, 1.3300E-02, 
            6.9800E-03, 5.0500E-03, 4.7500E-03, 4.4700E-03, 2.5700E-03, 
            6.4400E-04, 4.8900E-04, 4.0600E-04, 2.3500E-04, 1.1400E-04, 
            5.7000E-05, 2.7000E-05, 6.0000E-06, 3.9000E-06, 1.0000E-06, 
            1.6000E-07, 9.9000E-08} );
  }
};

//! The default Compton profile generator implementation for A=92
template<>
struct DefaultComptonProfileGeneratorImpl<92u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 27 );

    subshell_half_profiles[0] = 
      std::vector<double>( {7.4300E-03, 7.4300E-03, 7.4300E-03, 7.4300E-03, 
            7.4300E-03, 7.4300E-03, 7.4300E-03, 7.4300E-03, 7.4300E-03, 
            7.4300E-03, 7.4300E-03, 7.4300E-03, 7.4300E-03, 7.4200E-03, 
            7.4200E-03, 7.4200E-03, 7.4200E-03, 7.4200E-03, 7.4100E-03, 
            7.4000E-03, 7.3800E-03, 7.3600E-03, 7.3300E-03, 7.3000E-03, 
            7.2000E-03, 7.0000E-03, 6.7000E-03, 5.9000E-03, 5.0000E-03, 
            3.3000E-03, 1.3000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.6700E-02, 2.6700E-02, 2.6700E-02, 2.6700E-02, 
            2.6700E-02, 2.6700E-02, 2.6700E-02, 2.6600E-02, 2.6600E-02, 
            2.6600E-02, 2.6600E-02, 2.6600E-02, 2.6500E-02, 2.6500E-02, 
            2.6500E-02, 2.6400E-02, 2.6300E-02, 2.6200E-02, 2.6000E-02, 
            2.5400E-02, 2.4800E-02, 2.4000E-02, 2.3100E-02, 2.2100E-02, 
            2.0000E-02, 1.4000E-02, 8.7000E-03, 2.6000E-03, 8.9000E-04, 
            6.3000E-04, 3.3000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.2800E-02, 1.2800E-02, 1.2800E-02, 1.2800E-02, 
            1.2800E-02, 1.2800E-02, 1.2800E-02, 1.2800E-02, 1.2800E-02, 
            1.2800E-02, 1.2800E-02, 1.2800E-02, 1.2800E-02, 1.2800E-02, 
            1.2800E-02, 1.2800E-02, 1.2800E-02, 1.2800E-02, 1.2800E-02, 
            1.2800E-02, 1.2800E-02, 1.2800E-02, 1.2800E-02, 1.2700E-02, 
            1.2700E-02, 1.2000E-02, 1.1000E-02, 7.9000E-03, 4.9000E-03, 
            1.7000E-03, 2.3000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.5200E-02, 1.5200E-02, 1.5200E-02, 1.5200E-02, 
            1.5200E-02, 1.5200E-02, 1.5200E-02, 1.5200E-02, 1.5200E-02, 
            1.5200E-02, 1.5200E-02, 1.5200E-02, 1.5200E-02, 1.5200E-02, 
            1.5200E-02, 1.5200E-02, 1.5200E-02, 1.5200E-02, 1.5200E-02, 
            1.5200E-02, 1.5200E-02, 1.5200E-02, 1.5100E-02, 1.5100E-02, 
            1.5000E-02, 1.4000E-02, 1.2000E-02, 7.5000E-03, 4.0000E-03, 
            9.7000E-04, 7.6000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {5.8400E-02, 5.8400E-02, 5.8400E-02, 5.8400E-02, 
            5.8300E-02, 5.8300E-02, 5.8200E-02, 5.8100E-02, 5.8000E-02, 
            5.7900E-02, 5.7800E-02, 5.7400E-02, 5.7000E-02, 5.6500E-02, 
            5.5900E-02, 5.5300E-02, 5.4600E-02, 5.3000E-02, 5.0300E-02, 
            4.4800E-02, 3.8600E-02, 3.2400E-02, 2.6400E-02, 2.0900E-02, 
            1.3000E-02, 4.8000E-03, 4.5000E-03, 2.3000E-03, 5.9000E-04, 
            1.4000E-04, 8.5000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.4000E-02, 3.4000E-02, 3.4000E-02, 3.4000E-02, 
            3.4000E-02, 3.4000E-02, 3.4000E-02, 3.4000E-02, 3.4000E-02, 
            3.4000E-02, 3.4000E-02, 3.4000E-02, 3.4000E-02, 3.4000E-02, 
            3.4000E-02, 3.4000E-02, 3.4000E-02, 3.3900E-02, 3.3800E-02, 
            3.3500E-02, 3.2900E-02, 3.1900E-02, 3.0500E-02, 2.8700E-02, 
            2.4000E-02, 1.2000E-02, 4.2000E-03, 1.3000E-03, 1.2000E-03, 
            5.1000E-04, 6.9000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {3.7900E-02, 3.7900E-02, 3.7900E-02, 3.7900E-02, 
            3.7900E-02, 3.7900E-02, 3.7900E-02, 3.7900E-02, 3.7900E-02, 
            3.7900E-02, 3.7900E-02, 3.7900E-02, 3.7900E-02, 3.7900E-02, 
            3.7900E-02, 3.7900E-02, 3.7900E-02, 3.7800E-02, 3.7600E-02, 
            3.7100E-02, 3.6100E-02, 3.4500E-02, 3.2400E-02, 2.9700E-02, 
            2.3000E-02, 9.2000E-03, 2.9000E-03, 1.6000E-03, 1.2000E-03, 
            3.5000E-04, 2.6000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 
            2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 
            2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 
            2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 2.4300E-02, 
            2.4300E-02, 2.4300E-02, 2.4200E-02, 2.4000E-02, 2.3700E-02, 
            2.3000E-02, 1.7000E-02, 1.1000E-02, 3.1000E-03, 8.2000E-04, 
            7.2000E-05, 1.9000E-06} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.5200E-02, 2.5200E-02, 2.5200E-02, 2.5200E-02, 
            2.5200E-02, 2.5200E-02, 2.5200E-02, 2.5200E-02, 2.5200E-02, 
            2.5200E-02, 2.5200E-02, 2.5200E-02, 2.5200E-02, 2.5200E-02, 
            2.5200E-02, 2.5200E-02, 2.5200E-02, 2.5200E-02, 2.5200E-02, 
            2.5200E-02, 2.5100E-02, 2.5000E-02, 2.4800E-02, 2.4400E-02, 
            2.3000E-02, 1.7000E-02, 1.1000E-02, 2.8000E-03, 6.8000E-04, 
            5.1000E-05, 1.0000E-06} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.1500E-01, 1.1500E-01, 1.1500E-01, 1.1500E-01, 
            1.1500E-01, 1.1500E-01, 1.1400E-01, 1.1300E-01, 1.1200E-01, 
            1.1100E-01, 1.1000E-01, 1.0700E-01, 1.0400E-01, 1.0000E-01, 
            9.5900E-02, 9.1300E-02, 8.6500E-02, 7.6400E-02, 6.0900E-02, 
            3.8400E-02, 2.3200E-02, 1.5400E-02, 1.2600E-02, 1.2200E-02, 
            1.1000E-02, 3.6000E-03, 1.2000E-03, 8.5000E-04, 2.3000E-04, 
            3.7000E-05, 2.3000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {7.2400E-02, 7.2400E-02, 7.2400E-02, 7.2400E-02, 
            7.2400E-02, 7.2400E-02, 7.2400E-02, 7.2400E-02, 7.2400E-02, 
            7.2400E-02, 7.2300E-02, 7.2300E-02, 7.2200E-02, 7.2000E-02, 
            7.1800E-02, 7.1400E-02, 7.1000E-02, 6.9600E-02, 6.6400E-02, 
            5.7800E-02, 4.6100E-02, 3.3700E-02, 2.2800E-02, 1.4600E-02, 
            6.7000E-03, 4.9000E-03, 2.6000E-03, 3.5000E-04, 2.9000E-04, 
            1.4000E-04, 1.9000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {7.9800E-02, 7.9800E-02, 7.9800E-02, 7.9800E-02, 
            7.9800E-02, 7.9800E-02, 7.9800E-02, 7.9800E-02, 7.9800E-02, 
            7.9800E-02, 7.9800E-02, 7.9700E-02, 7.9500E-02, 7.9200E-02, 
            7.8800E-02, 7.8300E-02, 7.7600E-02, 7.5500E-02, 7.0700E-02, 
            5.8500E-02, 4.3400E-02, 2.9100E-02, 1.8100E-02, 1.1200E-02, 
            6.2000E-03, 4.9000E-03, 1.8000E-03, 3.9000E-04, 3.4000E-04, 
            1.0000E-04, 7.3000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {5.8900E-02, 5.8900E-02, 5.8900E-02, 5.8900E-02, 
            5.8900E-02, 5.8900E-02, 5.8900E-02, 5.8900E-02, 5.8900E-02, 
            5.8900E-02, 5.8900E-02, 5.8900E-02, 5.8900E-02, 5.8900E-02, 
            5.8900E-02, 5.8900E-02, 5.8800E-02, 5.8600E-02, 5.8000E-02, 
            5.5500E-02, 5.0300E-02, 4.2800E-02, 3.4000E-02, 2.5300E-02, 
            1.2000E-02, 2.5000E-03, 2.2000E-03, 9.8000E-04, 2.7000E-04, 
            2.4000E-05, 6.0000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {6.0600E-02, 6.0600E-02, 6.0600E-02, 6.0600E-02, 
            6.0600E-02, 6.0600E-02, 6.0600E-02, 6.0600E-02, 6.0600E-02, 
            6.0600E-02, 6.0600E-02, 6.0600E-02, 6.0600E-02, 6.0600E-02, 
            6.0600E-02, 6.0500E-02, 6.0500E-02, 6.0300E-02, 5.9600E-02, 
            5.6600E-02, 5.0800E-02, 4.2500E-02, 3.3100E-02, 2.4200E-02, 
            1.1000E-02, 2.5000E-03, 2.3000E-03, 8.9000E-04, 2.3000E-04, 
            1.7000E-05, 3.2000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {4.7200E-02, 4.7200E-02, 4.7200E-02, 4.7200E-02, 
            4.7200E-02, 4.7200E-02, 4.7200E-02, 4.7200E-02, 4.7200E-02, 
            4.7200E-02, 4.7200E-02, 4.7200E-02, 4.7200E-02, 4.7200E-02, 
            4.7200E-02, 4.7200E-02, 4.7200E-02, 4.7200E-02, 4.7000E-02, 
            4.6400E-02, 4.4700E-02, 4.1700E-02, 3.7400E-02, 3.2500E-02, 
            2.2000E-02, 6.8000E-03, 1.8000E-03, 1.5000E-04, 1.7000E-05, 
            4.8000E-07, 3.5000E-09} );

    subshell_half_profiles[15] = 
      std::vector<double>( {4.7900E-02, 4.7900E-02, 4.7900E-02, 4.7900E-02, 
            4.7900E-02, 4.7900E-02, 4.7900E-02, 4.7900E-02, 4.7900E-02, 
            4.7900E-02, 4.7900E-02, 4.7900E-02, 4.7900E-02, 4.7900E-02, 
            4.7900E-02, 4.7900E-02, 4.7900E-02, 4.7800E-02, 4.7700E-02, 
            4.7000E-02, 4.5200E-02, 4.2000E-02, 3.7500E-02, 3.2400E-02, 
            2.2000E-02, 6.5000E-03, 1.7000E-03, 1.3000E-04, 1.4000E-05, 
            3.7000E-07, 2.2000E-09} );

    subshell_half_profiles[16] = 
      std::vector<double>( {2.3800E-01, 2.3800E-01, 2.3800E-01, 2.3700E-01, 
            2.3600E-01, 2.3200E-01, 2.2700E-01, 2.2100E-01, 2.1300E-01, 
            2.0500E-01, 1.9500E-01, 1.7500E-01, 1.5300E-01, 1.3100E-01, 
            1.1000E-01, 9.0600E-02, 7.3700E-02, 4.8500E-02, 2.9800E-02, 
            2.5100E-02, 2.2700E-02, 1.5400E-02, 8.4300E-03, 4.5900E-03, 
            3.1000E-03, 1.4000E-03, 3.4000E-04, 2.2000E-04, 6.2000E-05, 
            9.1000E-06, 5.7000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.5700E-01, 1.5700E-01, 1.5700E-01, 1.5700E-01, 
            1.5700E-01, 1.5700E-01, 1.5600E-01, 1.5600E-01, 1.5600E-01, 
            1.5500E-01, 1.5500E-01, 1.5200E-01, 1.4900E-01, 1.4300E-01, 
            1.3600E-01, 1.2700E-01, 1.1700E-01, 9.4400E-02, 6.0500E-02, 
            2.3600E-02, 1.2300E-02, 1.1300E-02, 1.0600E-02, 8.3400E-03, 
            3.4000E-03, 1.1000E-03, 7.1000E-04, 8.8000E-05, 6.4000E-05, 
            3.3000E-05, 4.4000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {1.7300E-01, 1.7300E-01, 1.7300E-01, 1.7300E-01, 
            1.7300E-01, 1.7300E-01, 1.7300E-01, 1.7200E-01, 1.7200E-01, 
            1.7100E-01, 1.7000E-01, 1.6600E-01, 1.6100E-01, 1.5200E-01, 
            1.4200E-01, 1.3000E-01, 1.1600E-01, 8.7900E-02, 5.0400E-02, 
            1.8400E-02, 1.2600E-02, 1.2300E-02, 1.0000E-02, 6.6700E-03, 
            2.2000E-03, 1.2000E-03, 5.0000E-04, 8.7000E-05, 7.7000E-05, 
            2.3000E-05, 1.7000E-06} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.4500E-01, 1.4500E-01, 1.4500E-01, 1.4500E-01, 
            1.4500E-01, 1.4500E-01, 1.4500E-01, 1.4500E-01, 1.4500E-01, 
            1.4500E-01, 1.4500E-01, 1.4500E-01, 1.4300E-01, 1.4100E-01, 
            1.3700E-01, 1.3200E-01, 1.2500E-01, 1.0700E-01, 7.5700E-02, 
            3.2200E-02, 1.1700E-02, 6.1200E-03, 5.5600E-03, 5.3900E-03, 
            3.5000E-03, 5.3000E-04, 3.8000E-04, 1.9000E-04, 5.4000E-05, 
            4.7000E-06, 1.2000E-07} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.4900E-01, 1.4900E-01, 1.4900E-01, 1.4900E-01, 
            1.4900E-01, 1.4900E-01, 1.4900E-01, 1.4900E-01, 1.4900E-01, 
            1.4900E-01, 1.4900E-01, 1.4800E-01, 1.4700E-01, 1.4400E-01, 
            1.4000E-01, 1.3400E-01, 1.2600E-01, 1.0700E-01, 7.3500E-02, 
            2.9700E-02, 1.0600E-02, 6.0400E-03, 5.7200E-03, 5.4200E-03, 
            3.3000E-03, 4.9000E-04, 3.9000E-04, 1.7000E-04, 4.5000E-05, 
            3.4000E-06, 6.3000E-08} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.9300E-01, 1.9300E-01, 1.9300E-01, 1.9300E-01, 
            1.9300E-01, 1.9300E-01, 1.9300E-01, 1.9300E-01, 1.9200E-01, 
            1.9200E-01, 1.9000E-01, 1.8500E-01, 1.7600E-01, 1.6400E-01, 
            1.5000E-01, 1.3500E-01, 1.2000E-01, 9.0700E-02, 5.5600E-02, 
            2.1400E-02, 7.4400E-03, 2.7900E-03, 1.6000E-03, 1.4300E-03, 
            1.4000E-03, 5.7000E-04, 1.7000E-04, 1.4000E-05, 1.6000E-06, 
            4.5000E-08, 3.4000E-10} );

    subshell_half_profiles[22] = 
      std::vector<double>( {5.6500E-01, 5.6300E-01, 5.5600E-01, 5.4500E-01, 
            5.2900E-01, 4.8800E-01, 4.3600E-01, 3.7700E-01, 3.1700E-01, 
            2.6000E-01, 2.0700E-01, 1.2600E-01, 7.7800E-02, 5.5100E-02, 
            4.7700E-02, 4.6700E-02, 4.6300E-02, 4.0000E-02, 2.2000E-02, 
            6.4000E-03, 5.2200E-03, 4.3600E-03, 2.5900E-03, 1.3000E-03, 
            6.2000E-04, 3.1000E-04, 6.9000E-05, 4.5000E-05, 1.2000E-05, 
            1.8000E-06, 1.1000E-06} );

    subshell_half_profiles[23] = 
      std::vector<double>( {3.9000E-01, 3.9000E-01, 3.9000E-01, 3.9000E-01, 
            3.8900E-01, 3.8600E-01, 3.8000E-01, 3.6800E-01, 3.4900E-01, 
            3.2500E-01, 2.9600E-01, 2.2900E-01, 1.6200E-01, 1.0600E-01, 
            6.6400E-02, 4.1400E-02, 2.7900E-02, 2.0100E-02, 1.9200E-02, 
            1.0300E-02, 3.4800E-03, 1.9700E-03, 1.9000E-03, 1.6500E-03, 
            7.4000E-04, 1.9000E-04, 1.3000E-04, 1.5000E-05, 1.1000E-05, 
            5.6000E-06, 7.6000E-07} );

    subshell_half_profiles[24] = 
      std::vector<double>( {4.5000E-01, 4.5000E-01, 4.5000E-01, 4.5000E-01, 
            4.4900E-01, 4.4300E-01, 4.3100E-01, 4.0900E-01, 3.7900E-01, 
            3.4000E-01, 2.9700E-01, 2.0700E-01, 1.3000E-01, 7.6300E-02, 
            4.4200E-02, 2.8200E-02, 2.2000E-02, 2.0400E-02, 1.7300E-02, 
            6.4300E-03, 2.2500E-03, 1.9100E-03, 1.7300E-03, 1.2400E-03, 
            4.1000E-04, 1.9000E-04, 8.0000E-05, 1.3000E-05, 1.2000E-05, 
            3.5000E-06, 2.6000E-07} );

    subshell_half_profiles[25] = 
      std::vector<double>( {5.4300E-01, 5.4300E-01, 5.4300E-01, 5.4300E-01, 
            5.4200E-01, 5.3500E-01, 5.1200E-01, 4.7100E-01, 4.1500E-01, 
            3.5100E-01, 2.8800E-01, 1.7900E-01, 1.0300E-01, 5.6300E-02, 
            2.9800E-02, 1.6000E-02, 9.4900E-03, 5.9500E-03, 5.6800E-03, 
            3.3900E-03, 1.2500E-03, 4.9400E-04, 3.7300E-04, 3.6700E-04, 
            2.6000E-04, 3.8000E-05, 2.6000E-05, 1.3000E-05, 3.8000E-06, 
            3.3000E-07, 8.1000E-09} );

    subshell_half_profiles[26] = 
      std::vector<double>( {1.9100E+00, 1.8400E+00, 1.6400E+00, 1.3500E+00, 
            1.0400E+00, 5.1300E-01, 2.1400E-01, 9.9800E-02, 7.3300E-02, 
            7.1300E-02, 6.9100E-02, 5.0600E-02, 2.8500E-02, 1.4100E-02, 
            7.3000E-03, 4.9700E-03, 4.5200E-03, 4.3400E-03, 2.6700E-03, 
            6.7900E-04, 4.7100E-04, 4.1000E-04, 2.5000E-04, 1.2400E-04, 
            5.6000E-05, 2.8000E-05, 6.2000E-06, 4.0000E-06, 1.1000E-06, 
            1.6000E-07, 1.0000E-07} );
  }
};

//! The default Compton profile generator implementation for A=93
template<>
struct DefaultComptonProfileGeneratorImpl<93u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 27 );

    subshell_half_profiles[0] = 
      std::vector<double>( {7.3000E-03, 7.3000E-03, 7.3000E-03, 7.3000E-03, 
            7.3000E-03, 7.3000E-03, 7.3000E-03, 7.3000E-03, 7.3000E-03, 
            7.3000E-03, 7.3000E-03, 7.3000E-03, 7.3000E-03, 7.3000E-03, 
            7.3000E-03, 7.3000E-03, 7.2900E-03, 7.2900E-03, 7.2800E-03, 
            7.2700E-03, 7.2500E-03, 7.2300E-03, 7.2100E-03, 7.1800E-03, 
            7.1000E-03, 6.9000E-03, 6.6000E-03, 5.8000E-03, 5.0000E-03, 
            3.3000E-03, 1.3000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 
            2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6200E-02, 
            2.6200E-02, 2.6200E-02, 2.6200E-02, 2.6100E-02, 2.6100E-02, 
            2.6000E-02, 2.6000E-02, 2.5900E-02, 2.5800E-02, 2.5600E-02, 
            2.5000E-02, 2.4400E-02, 2.3600E-02, 2.2800E-02, 2.1800E-02, 
            2.0000E-02, 1.4000E-02, 8.8000E-03, 2.8000E-03, 9.2000E-04, 
            6.2000E-04, 3.4000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.2600E-02, 1.2600E-02, 1.2600E-02, 1.2600E-02, 
            1.2600E-02, 1.2600E-02, 1.2600E-02, 1.2600E-02, 1.2600E-02, 
            1.2600E-02, 1.2600E-02, 1.2600E-02, 1.2600E-02, 1.2600E-02, 
            1.2600E-02, 1.2600E-02, 1.2600E-02, 1.2600E-02, 1.2600E-02, 
            1.2600E-02, 1.2600E-02, 1.2600E-02, 1.2500E-02, 1.2500E-02, 
            1.2000E-02, 1.2000E-02, 1.1000E-02, 7.9000E-03, 5.0000E-03, 
            1.7000E-03, 2.4000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.5000E-02, 1.5000E-02, 1.5000E-02, 1.5000E-02, 
            1.5000E-02, 1.5000E-02, 1.5000E-02, 1.5000E-02, 1.5000E-02, 
            1.5000E-02, 1.5000E-02, 1.5000E-02, 1.5000E-02, 1.5000E-02, 
            1.5000E-02, 1.5000E-02, 1.5000E-02, 1.5000E-02, 1.5000E-02, 
            1.5000E-02, 1.5000E-02, 1.5000E-02, 1.4900E-02, 1.4900E-02, 
            1.4900E-02, 1.4000E-02, 1.2000E-02, 7.6000E-03, 4.1000E-03, 
            1.0000E-03, 8.1000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {5.7500E-02, 5.7500E-02, 5.7400E-02, 5.7400E-02, 
            5.7400E-02, 5.7400E-02, 5.7300E-02, 5.7200E-02, 5.7100E-02, 
            5.7000E-02, 5.6900E-02, 5.6500E-02, 5.6100E-02, 5.5700E-02, 
            5.5100E-02, 5.4500E-02, 5.3900E-02, 5.2300E-02, 4.9700E-02, 
            4.4400E-02, 3.8500E-02, 3.2400E-02, 2.6600E-02, 2.1200E-02, 
            1.3000E-02, 4.9000E-03, 4.4000E-03, 2.4000E-03, 6.4000E-04, 
            1.4000E-04, 8.7000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.3400E-02, 3.3400E-02, 3.3400E-02, 3.3400E-02, 
            3.3400E-02, 3.3400E-02, 3.3400E-02, 3.3400E-02, 3.3400E-02, 
            3.3400E-02, 3.3400E-02, 3.3400E-02, 3.3400E-02, 3.3400E-02, 
            3.3400E-02, 3.3400E-02, 3.3400E-02, 3.3400E-02, 3.3300E-02, 
            3.3000E-02, 3.2400E-02, 3.1500E-02, 3.0100E-02, 2.8400E-02, 
            2.4000E-02, 1.2000E-02, 4.4000E-03, 1.2000E-03, 1.2000E-03, 
            5.3000E-04, 7.4000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {3.7400E-02, 3.7400E-02, 3.7400E-02, 3.7400E-02, 
            3.7400E-02, 3.7400E-02, 3.7400E-02, 3.7400E-02, 3.7400E-02, 
            3.7400E-02, 3.7400E-02, 3.7400E-02, 3.7400E-02, 3.7400E-02, 
            3.7400E-02, 3.7400E-02, 3.7400E-02, 3.7300E-02, 3.7100E-02, 
            3.6600E-02, 3.5700E-02, 3.4200E-02, 3.2100E-02, 2.9600E-02, 
            2.4000E-02, 9.4000E-03, 3.0000E-03, 1.6000E-03, 1.3000E-03, 
            3.6000E-04, 2.7000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.4000E-02, 2.4000E-02, 2.4000E-02, 2.4000E-02, 
            2.4000E-02, 2.4000E-02, 2.4000E-02, 2.4000E-02, 2.4000E-02, 
            2.4000E-02, 2.4000E-02, 2.4000E-02, 2.4000E-02, 2.4000E-02, 
            2.4000E-02, 2.4000E-02, 2.4000E-02, 2.4000E-02, 2.4000E-02, 
            2.4000E-02, 2.4000E-02, 2.3900E-02, 2.3700E-02, 2.3400E-02, 
            2.2000E-02, 1.7000E-02, 1.1000E-02, 3.3000E-03, 8.7000E-04, 
            7.8000E-05, 2.1000E-06} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 
            2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 
            2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 
            2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 2.4800E-02, 
            2.4800E-02, 2.4800E-02, 2.4700E-02, 2.4500E-02, 2.4200E-02, 
            2.3000E-02, 1.7000E-02, 1.1000E-02, 2.9000E-03, 7.2000E-04, 
            5.6000E-05, 1.1000E-06} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.1300E-01, 1.1300E-01, 1.1300E-01, 1.1300E-01, 
            1.1300E-01, 1.1300E-01, 1.1200E-01, 1.1100E-01, 1.1000E-01, 
            1.0900E-01, 1.0800E-01, 1.0600E-01, 1.0200E-01, 9.8800E-02, 
            9.4800E-02, 9.0400E-02, 8.5800E-02, 7.6000E-02, 6.1100E-02, 
            3.9100E-02, 2.3800E-02, 1.5700E-02, 1.2600E-02, 1.2000E-02, 
            1.1000E-02, 3.9000E-03, 1.3000E-03, 8.8000E-04, 2.5000E-04, 
            3.7000E-05, 2.4000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {7.1000E-02, 7.1000E-02, 7.1000E-02, 7.1000E-02, 
            7.1000E-02, 7.1000E-02, 7.1000E-02, 7.1000E-02, 7.1000E-02, 
            7.1000E-02, 7.1000E-02, 7.0900E-02, 7.0800E-02, 7.0700E-02, 
            7.0500E-02, 7.0100E-02, 6.9700E-02, 6.8500E-02, 6.5500E-02, 
            5.7500E-02, 4.6400E-02, 3.4300E-02, 2.3600E-02, 1.5400E-02, 
            6.9000E-03, 4.9000E-03, 2.7000E-03, 3.7000E-04, 2.8000E-04, 
            1.5000E-04, 2.1000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {7.8500E-02, 7.8500E-02, 7.8500E-02, 7.8500E-02, 
            7.8500E-02, 7.8500E-02, 7.8500E-02, 7.8500E-02, 7.8500E-02, 
            7.8500E-02, 7.8500E-02, 7.8400E-02, 7.8200E-02, 7.8000E-02, 
            7.7600E-02, 7.7100E-02, 7.6400E-02, 7.4500E-02, 7.0000E-02, 
            5.8400E-02, 4.3900E-02, 2.9900E-02, 1.8800E-02, 1.1700E-02, 
            6.2000E-03, 4.9000E-03, 1.9000E-03, 3.9000E-04, 3.4000E-04, 
            1.1000E-04, 7.9000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {5.7900E-02, 5.7900E-02, 5.7900E-02, 5.7900E-02, 
            5.7900E-02, 5.7900E-02, 5.7900E-02, 5.7900E-02, 5.7900E-02, 
            5.7900E-02, 5.7900E-02, 5.7900E-02, 5.7900E-02, 5.7900E-02, 
            5.7800E-02, 5.7800E-02, 5.7800E-02, 5.7600E-02, 5.7100E-02, 
            5.4800E-02, 5.0000E-02, 4.2900E-02, 3.4400E-02, 2.6000E-02, 
            1.3000E-02, 2.5000E-03, 2.2000E-03, 1.0000E-03, 2.9000E-04, 
            2.6000E-05, 6.7000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {5.9600E-02, 5.9600E-02, 5.9600E-02, 5.9600E-02, 
            5.9600E-02, 5.9600E-02, 5.9600E-02, 5.9600E-02, 5.9600E-02, 
            5.9600E-02, 5.9600E-02, 5.9600E-02, 5.9500E-02, 5.9500E-02, 
            5.9500E-02, 5.9500E-02, 5.9400E-02, 5.9300E-02, 5.8600E-02, 
            5.5900E-02, 5.0500E-02, 4.2700E-02, 3.3700E-02, 2.4900E-02, 
            1.2000E-02, 2.5000E-03, 2.3000E-03, 9.3000E-04, 2.5000E-04, 
            1.9000E-05, 3.6000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {4.6200E-02, 4.6200E-02, 4.6200E-02, 4.6200E-02, 
            4.6200E-02, 4.6200E-02, 4.6200E-02, 4.6200E-02, 4.6200E-02, 
            4.6200E-02, 4.6200E-02, 4.6200E-02, 4.6200E-02, 4.6200E-02, 
            4.6200E-02, 4.6200E-02, 4.6200E-02, 4.6200E-02, 4.6100E-02, 
            4.5500E-02, 4.4000E-02, 4.1300E-02, 3.7400E-02, 3.2700E-02, 
            2.3000E-02, 7.2000E-03, 2.0000E-03, 1.7000E-04, 1.9000E-05, 
            5.5000E-07, 4.1000E-09} );

    subshell_half_profiles[15] = 
      std::vector<double>( {4.6900E-02, 4.6900E-02, 4.6900E-02, 4.6900E-02, 
            4.6900E-02, 4.6900E-02, 4.6900E-02, 4.6900E-02, 4.6900E-02, 
            4.6900E-02, 4.6900E-02, 4.6900E-02, 4.6900E-02, 4.6900E-02, 
            4.6900E-02, 4.6900E-02, 4.6900E-02, 4.6900E-02, 4.6800E-02, 
            4.6200E-02, 4.4500E-02, 4.1600E-02, 3.7500E-02, 3.2600E-02, 
            2.3000E-02, 6.9000E-03, 1.9000E-03, 1.5000E-04, 1.6000E-05, 
            4.3000E-07, 2.6000E-09} );

    subshell_half_profiles[16] = 
      std::vector<double>( {2.3300E-01, 2.3300E-01, 2.3200E-01, 2.3100E-01, 
            2.3000E-01, 2.2700E-01, 2.2200E-01, 2.1600E-01, 2.0900E-01, 
            2.0100E-01, 1.9200E-01, 1.7300E-01, 1.5200E-01, 1.3100E-01, 
            1.1100E-01, 9.1900E-02, 7.5400E-02, 5.0000E-02, 3.0400E-02, 
            2.4800E-02, 2.2900E-02, 1.6100E-02, 9.1100E-03, 4.9400E-03, 
            3.1000E-03, 1.5000E-03, 3.5000E-04, 2.3000E-04, 6.8000E-05, 
            9.2000E-06, 6.0000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5300E-01, 
            1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5200E-01, 
            1.5200E-01, 1.5100E-01, 1.4900E-01, 1.4600E-01, 1.4100E-01, 
            1.3400E-01, 1.2600E-01, 1.1700E-01, 9.5200E-02, 6.2500E-02, 
            2.5200E-02, 1.2600E-02, 1.1200E-02, 1.0700E-02, 8.6900E-03, 
            3.8000E-03, 1.1000E-03, 7.5000E-04, 9.4000E-05, 6.4000E-05, 
            3.4000E-05, 4.9000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {1.6900E-01, 1.6900E-01, 1.6900E-01, 1.6900E-01, 
            1.6900E-01, 1.6900E-01, 1.6900E-01, 1.6900E-01, 1.6800E-01, 
            1.6700E-01, 1.6600E-01, 1.6300E-01, 1.5800E-01, 1.5000E-01, 
            1.4100E-01, 1.2900E-01, 1.1700E-01, 8.9300E-02, 5.2600E-02, 
            1.9300E-02, 1.2600E-02, 1.2300E-02, 1.0300E-02, 7.1000E-03, 
            2.4000E-03, 1.2000E-03, 5.4000E-04, 8.9000E-05, 7.9000E-05, 
            2.5000E-05, 1.8000E-06} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 
            1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 
            1.4200E-01, 1.4200E-01, 1.4100E-01, 1.4000E-01, 1.3800E-01, 
            1.3500E-01, 1.3000E-01, 1.2400E-01, 1.0700E-01, 7.7500E-02, 
            3.4400E-02, 1.2800E-02, 6.3600E-03, 5.5500E-03, 5.4500E-03, 
            3.8000E-03, 5.7000E-04, 3.8000E-04, 2.0000E-04, 5.8000E-05, 
            5.2000E-06, 1.3000E-07} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.4500E-01, 1.4500E-01, 1.4500E-01, 1.4500E-01, 
            1.4500E-01, 1.4500E-01, 1.4500E-01, 1.4500E-01, 1.4500E-01, 
            1.4500E-01, 1.4500E-01, 1.4500E-01, 1.4300E-01, 1.4100E-01, 
            1.3700E-01, 1.3200E-01, 1.2500E-01, 1.0700E-01, 7.5600E-02, 
            3.1900E-02, 1.1600E-02, 6.2300E-03, 5.7300E-03, 5.5200E-03, 
            3.5000E-03, 5.2000E-04, 4.0000E-04, 1.8000E-04, 4.9000E-05, 
            3.8000E-06, 7.1000E-08} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.8200E-01, 1.8200E-01, 1.8200E-01, 1.8200E-01, 
            1.8200E-01, 1.8200E-01, 1.8200E-01, 1.8200E-01, 1.8200E-01, 
            1.8100E-01, 1.8000E-01, 1.7600E-01, 1.7000E-01, 1.6000E-01, 
            1.4900E-01, 1.3600E-01, 1.2200E-01, 9.4800E-02, 6.0400E-02, 
            2.4600E-02, 8.9400E-03, 3.3600E-03, 1.7900E-03, 1.5100E-03, 
            1.5000E-03, 6.5000E-04, 2.0000E-04, 1.7000E-05, 1.9000E-06, 
            5.6000E-08, 4.3000E-10} );

    subshell_half_profiles[22] = 
      std::vector<double>( {5.5200E-01, 5.5000E-01, 5.4300E-01, 5.3300E-01, 
            5.1800E-01, 4.8000E-01, 4.3000E-01, 3.7500E-01, 3.1800E-01, 
            2.6200E-01, 2.1100E-01, 1.3100E-01, 8.0800E-02, 5.6100E-02, 
            4.7300E-02, 4.5600E-02, 4.5500E-02, 4.0400E-02, 2.3500E-02, 
            6.8000E-03, 5.1700E-03, 4.5200E-03, 2.8200E-03, 1.4500E-03, 
            6.3000E-04, 3.4000E-04, 7.4000E-05, 4.7000E-05, 1.4000E-05, 
            1.8000E-06, 1.2000E-06} );

    subshell_half_profiles[23] = 
      std::vector<double>( {3.8000E-01, 3.8000E-01, 3.8000E-01, 3.7900E-01, 
            3.7900E-01, 3.7600E-01, 3.7000E-01, 3.6000E-01, 3.4300E-01, 
            3.2100E-01, 2.9400E-01, 2.3100E-01, 1.6700E-01, 1.1200E-01, 
            7.1300E-02, 4.4800E-02, 2.9800E-02, 2.0000E-02, 1.9100E-02, 
            1.1100E-02, 3.8900E-03, 2.0200E-03, 1.9100E-03, 1.7200E-03, 
            8.2000E-04, 1.9000E-04, 1.4000E-04, 1.7000E-05, 1.1000E-05, 
            6.0000E-06, 8.5000E-07} );

    subshell_half_profiles[24] = 
      std::vector<double>( {4.4200E-01, 4.4200E-01, 4.4200E-01, 4.4200E-01, 
            4.4100E-01, 4.3600E-01, 4.2400E-01, 4.0400E-01, 3.7500E-01, 
            3.3900E-01, 2.9800E-01, 2.1100E-01, 1.3500E-01, 8.0400E-02, 
            4.6800E-02, 2.9400E-02, 2.2200E-02, 1.9800E-02, 1.7500E-02, 
            6.9500E-03, 2.3700E-03, 1.8800E-03, 1.7600E-03, 1.3100E-03, 
            4.5000E-04, 1.9000E-04, 8.6000E-05, 1.3000E-05, 1.2000E-05, 
            3.8000E-06, 2.8000E-07} );

    subshell_half_profiles[25] = 
      std::vector<double>( {5.3200E-01, 5.3200E-01, 5.3200E-01, 5.3200E-01, 
            5.3100E-01, 5.2400E-01, 5.0300E-01, 4.6500E-01, 4.1200E-01, 
            3.5200E-01, 2.9100E-01, 1.8500E-01, 1.0900E-01, 6.0800E-02, 
            3.2900E-02, 1.7800E-02, 1.0400E-02, 5.9600E-03, 5.6100E-03, 
            3.5900E-03, 1.4000E-03, 5.4100E-04, 3.7800E-04, 3.7100E-04, 
            2.8000E-04, 4.2000E-05, 2.6000E-05, 1.4000E-05, 4.1000E-06, 
            3.7000E-07, 9.3000E-09} );

    subshell_half_profiles[26] = 
      std::vector<double>( {1.8900E+00, 1.8200E+00, 1.6300E+00, 1.3500E+00, 
            1.0500E+00, 5.2400E-01, 2.2100E-01, 1.0100E-01, 7.1400E-02, 
            6.8600E-02, 6.7100E-02, 5.0700E-02, 2.9600E-02, 1.5000E-02, 
            7.6600E-03, 4.9600E-03, 4.3300E-03, 4.1900E-03, 2.7500E-03, 
            7.2000E-04, 4.5300E-04, 4.1100E-04, 2.6400E-04, 1.3500E-04, 
            5.5000E-05, 3.0000E-05, 6.4000E-06, 4.1000E-06, 1.2000E-06, 
            1.6000E-07, 1.0000E-07} );
  }
};

//! The default Compton profile generator implementation for A=94
template<>
struct DefaultComptonProfileGeneratorImpl<94u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 26 );

    subshell_half_profiles[0] = 
      std::vector<double>( {7.1800E-03, 7.1800E-03, 7.1800E-03, 7.1800E-03, 
            7.1800E-03, 7.1800E-03, 7.1800E-03, 7.1800E-03, 7.1800E-03, 
            7.1800E-03, 7.1800E-03, 7.1800E-03, 7.1700E-03, 7.1700E-03, 
            7.1700E-03, 7.1700E-03, 7.1700E-03, 7.1700E-03, 7.1600E-03, 
            7.1500E-03, 7.1300E-03, 7.1100E-03, 7.0900E-03, 7.0600E-03, 
            7.0000E-03, 6.8000E-03, 6.5000E-03, 5.8000E-03, 4.9000E-03, 
            3.4000E-03, 1.4000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.5800E-02, 2.5800E-02, 2.5800E-02, 2.5800E-02, 
            2.5800E-02, 2.5800E-02, 2.5800E-02, 2.5800E-02, 2.5800E-02, 
            2.5800E-02, 2.5800E-02, 2.5700E-02, 2.5700E-02, 2.5700E-02, 
            2.5600E-02, 2.5600E-02, 2.5500E-02, 2.5400E-02, 2.5200E-02, 
            2.4700E-02, 2.4100E-02, 2.3300E-02, 2.2500E-02, 2.1600E-02, 
            2.0000E-02, 1.4000E-02, 9.0000E-03, 2.9000E-03, 9.6000E-04, 
            6.1000E-04, 3.5000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.2400E-02, 1.2400E-02, 1.2400E-02, 1.2400E-02, 
            1.2400E-02, 1.2400E-02, 1.2400E-02, 1.2400E-02, 1.2400E-02, 
            1.2400E-02, 1.2400E-02, 1.2400E-02, 1.2400E-02, 1.2400E-02, 
            1.2400E-02, 1.2400E-02, 1.2400E-02, 1.2400E-02, 1.2400E-02, 
            1.2400E-02, 1.2300E-02, 1.2300E-02, 1.2300E-02, 1.2300E-02, 
            1.2000E-02, 1.2000E-02, 1.1000E-02, 7.9000E-03, 5.1000E-03, 
            1.8000E-03, 2.6000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.4900E-02, 1.4900E-02, 1.4900E-02, 1.4900E-02, 
            1.4900E-02, 1.4900E-02, 1.4900E-02, 1.4900E-02, 1.4900E-02, 
            1.4900E-02, 1.4900E-02, 1.4900E-02, 1.4900E-02, 1.4900E-02, 
            1.4900E-02, 1.4900E-02, 1.4900E-02, 1.4800E-02, 1.4800E-02, 
            1.4800E-02, 1.4800E-02, 1.4800E-02, 1.4800E-02, 1.4700E-02, 
            1.4700E-02, 1.4000E-02, 1.2000E-02, 7.6000E-03, 4.2000E-03, 
            1.1000E-03, 8.6000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {5.6500E-02, 5.6500E-02, 5.6500E-02, 5.6500E-02, 
            5.6500E-02, 5.6500E-02, 5.6400E-02, 5.6300E-02, 5.6200E-02, 
            5.6100E-02, 5.6000E-02, 5.5700E-02, 5.5300E-02, 5.4800E-02, 
            5.4300E-02, 5.3700E-02, 5.3100E-02, 5.1700E-02, 4.9100E-02, 
            4.4100E-02, 3.8400E-02, 3.2500E-02, 2.6800E-02, 2.1500E-02, 
            1.3000E-02, 4.9000E-03, 4.3000E-03, 2.5000E-03, 6.9000E-04, 
            1.4000E-04, 8.9000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.2900E-02, 3.2900E-02, 3.2900E-02, 3.2900E-02, 
            3.2900E-02, 3.2900E-02, 3.2900E-02, 3.2900E-02, 3.2900E-02, 
            3.2900E-02, 3.2900E-02, 3.2900E-02, 3.2900E-02, 3.2900E-02, 
            3.2900E-02, 3.2900E-02, 3.2900E-02, 3.2800E-02, 3.2700E-02, 
            3.2500E-02, 3.1900E-02, 3.1100E-02, 2.9800E-02, 2.8200E-02, 
            2.4000E-02, 1.2000E-02, 4.6000E-03, 1.2000E-03, 1.1000E-03, 
            5.5000E-04, 7.9000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {3.6900E-02, 3.6900E-02, 3.6900E-02, 3.6900E-02, 
            3.6900E-02, 3.6900E-02, 3.6900E-02, 3.6900E-02, 3.6900E-02, 
            3.6900E-02, 3.6900E-02, 3.6900E-02, 3.6900E-02, 3.6900E-02, 
            3.6900E-02, 3.6900E-02, 3.6900E-02, 3.6800E-02, 3.6700E-02, 
            3.6200E-02, 3.5300E-02, 3.3900E-02, 3.1900E-02, 2.9500E-02, 
            2.4000E-02, 9.7000E-03, 3.2000E-03, 1.6000E-03, 1.3000E-03, 
            3.8000E-04, 2.9000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.3700E-02, 2.3700E-02, 2.3700E-02, 2.3700E-02, 
            2.3700E-02, 2.3700E-02, 2.3700E-02, 2.3700E-02, 2.3700E-02, 
            2.3700E-02, 2.3700E-02, 2.3700E-02, 2.3700E-02, 2.3700E-02, 
            2.3700E-02, 2.3700E-02, 2.3700E-02, 2.3700E-02, 2.3700E-02, 
            2.3700E-02, 2.3600E-02, 2.3500E-02, 2.3400E-02, 2.3100E-02, 
            2.2000E-02, 1.7000E-02, 1.1000E-02, 3.4000E-03, 9.3000E-04, 
            8.4000E-05, 2.3000E-06} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.4500E-02, 2.4500E-02, 2.4500E-02, 2.4500E-02, 
            2.4500E-02, 2.4500E-02, 2.4500E-02, 2.4500E-02, 2.4500E-02, 
            2.4500E-02, 2.4500E-02, 2.4500E-02, 2.4500E-02, 2.4500E-02, 
            2.4500E-02, 2.4500E-02, 2.4500E-02, 2.4500E-02, 2.4500E-02, 
            2.4500E-02, 2.4500E-02, 2.4400E-02, 2.4200E-02, 2.3900E-02, 
            2.3000E-02, 1.7000E-02, 1.1000E-02, 3.0000E-03, 7.7000E-04, 
            6.0000E-05, 1.2000E-06} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.1100E-01, 1.1100E-01, 1.1100E-01, 1.1100E-01, 
            1.1100E-01, 1.1100E-01, 1.1000E-01, 1.0900E-01, 1.0900E-01, 
            1.0800E-01, 1.0700E-01, 1.0400E-01, 1.0100E-01, 9.7500E-02, 
            9.3600E-02, 8.9400E-02, 8.5000E-02, 7.5700E-02, 6.1300E-02, 
            3.9700E-02, 2.4400E-02, 1.6000E-02, 1.2600E-02, 1.1800E-02, 
            1.1000E-02, 4.1000E-03, 1.3000E-03, 9.0000E-04, 2.7000E-04, 
            3.7000E-05, 2.5000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {6.9700E-02, 6.9700E-02, 6.9700E-02, 6.9700E-02, 
            6.9700E-02, 6.9700E-02, 6.9700E-02, 6.9700E-02, 6.9700E-02, 
            6.9700E-02, 6.9700E-02, 6.9600E-02, 6.9500E-02, 6.9400E-02, 
            6.9200E-02, 6.8900E-02, 6.8500E-02, 6.7400E-02, 6.4700E-02, 
            5.7100E-02, 4.6600E-02, 3.5000E-02, 2.4400E-02, 1.6100E-02, 
            7.2000E-03, 4.8000E-03, 2.8000E-03, 3.8000E-04, 2.8000E-04, 
            1.5000E-04, 2.2000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {7.7200E-02, 7.7200E-02, 7.7200E-02, 7.7200E-02, 
            7.7200E-02, 7.7200E-02, 7.7200E-02, 7.7200E-02, 7.7200E-02, 
            7.7200E-02, 7.7200E-02, 7.7100E-02, 7.7000E-02, 7.6700E-02, 
            7.6400E-02, 7.5900E-02, 7.5300E-02, 7.3500E-02, 6.9300E-02, 
            5.8300E-02, 4.4400E-02, 3.0600E-02, 1.9500E-02, 1.2200E-02, 
            6.3000E-03, 5.0000E-03, 2.0000E-03, 3.9000E-04, 3.5000E-04, 
            1.1000E-04, 8.5000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {5.6900E-02, 5.6900E-02, 5.6900E-02, 5.6900E-02, 
            5.6900E-02, 5.6900E-02, 5.6900E-02, 5.6900E-02, 5.6900E-02, 
            5.6900E-02, 5.6900E-02, 5.6900E-02, 5.6900E-02, 5.6900E-02, 
            5.6800E-02, 5.6800E-02, 5.6800E-02, 5.6600E-02, 5.6200E-02, 
            5.4000E-02, 4.9600E-02, 4.2900E-02, 3.4900E-02, 2.6600E-02, 
            1.3000E-02, 2.6000E-03, 2.2000E-03, 1.1000E-03, 3.1000E-04, 
            2.9000E-05, 7.4000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {5.8500E-02, 5.8500E-02, 5.8500E-02, 5.8500E-02, 
            5.8500E-02, 5.8500E-02, 5.8500E-02, 5.8500E-02, 5.8500E-02, 
            5.8500E-02, 5.8500E-02, 5.8500E-02, 5.8500E-02, 5.8500E-02, 
            5.8500E-02, 5.8500E-02, 5.8400E-02, 5.8300E-02, 5.7700E-02, 
            5.5300E-02, 5.0200E-02, 4.2800E-02, 3.4100E-02, 2.5500E-02, 
            1.2000E-02, 2.5000E-03, 2.3000E-03, 9.8000E-04, 2.6000E-04, 
            2.1000E-05, 4.0000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 
            4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 
            4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 
            4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5200E-02, 4.5100E-02, 
            4.4700E-02, 4.3300E-02, 4.0900E-02, 3.7300E-02, 3.2900E-02, 
            2.4000E-02, 7.6000E-03, 2.2000E-03, 1.9000E-04, 2.1000E-05, 
            6.3000E-07, 4.7000E-09} );

    subshell_half_profiles[15] = 
      std::vector<double>( {4.6000E-02, 4.6000E-02, 4.6000E-02, 4.6000E-02, 
            4.6000E-02, 4.6000E-02, 4.6000E-02, 4.6000E-02, 4.6000E-02, 
            4.6000E-02, 4.6000E-02, 4.6000E-02, 4.6000E-02, 4.6000E-02, 
            4.5900E-02, 4.5900E-02, 4.5900E-02, 4.5900E-02, 4.5800E-02, 
            4.5300E-02, 4.3900E-02, 4.1200E-02, 3.7400E-02, 3.2800E-02, 
            2.3000E-02, 7.3000E-03, 2.0000E-03, 1.7000E-04, 1.8000E-05, 
            4.9000E-07, 3.0000E-09} );

    subshell_half_profiles[16] = 
      std::vector<double>( {2.2800E-01, 2.2700E-01, 2.2700E-01, 2.2600E-01, 
            2.2500E-01, 2.2200E-01, 2.1700E-01, 2.1200E-01, 2.0500E-01, 
            1.9800E-01, 1.9000E-01, 1.7100E-01, 1.5100E-01, 1.3100E-01, 
            1.1100E-01, 9.3100E-02, 7.6800E-02, 5.1400E-02, 3.0900E-02, 
            2.4400E-02, 2.3000E-02, 1.6800E-02, 9.7900E-03, 5.3200E-03, 
            3.1000E-03, 1.6000E-03, 3.7000E-04, 2.4000E-04, 7.5000E-05, 
            9.3000E-06, 6.2000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.5000E-01, 1.5000E-01, 1.5000E-01, 1.5000E-01, 
            1.5000E-01, 1.5000E-01, 1.4900E-01, 1.4900E-01, 1.4900E-01, 
            1.4900E-01, 1.4800E-01, 1.4600E-01, 1.4300E-01, 1.3800E-01, 
            1.3200E-01, 1.2500E-01, 1.1600E-01, 9.5700E-02, 6.4200E-02, 
            2.6600E-02, 1.2900E-02, 1.1100E-02, 1.0700E-02, 8.9700E-03, 
            4.1000E-03, 1.1000E-03, 7.9000E-04, 1.0000E-04, 6.4000E-05, 
            3.6000E-05, 5.3000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {1.6600E-01, 1.6600E-01, 1.6600E-01, 1.6600E-01, 
            1.6600E-01, 1.6600E-01, 1.6600E-01, 1.6500E-01, 1.6500E-01, 
            1.6400E-01, 1.6300E-01, 1.6000E-01, 1.5500E-01, 1.4800E-01, 
            1.3900E-01, 1.2900E-01, 1.1700E-01, 9.0500E-02, 5.4400E-02, 
            2.0300E-02, 1.2600E-02, 1.2200E-02, 1.0600E-02, 7.4800E-03, 
            2.6000E-03, 1.2000E-03, 5.8000E-04, 9.0000E-05, 8.0000E-05, 
            2.6000E-05, 2.0000E-06} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3900E-01, 
            1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3900E-01, 
            1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3800E-01, 1.3600E-01, 
            1.3300E-01, 1.2800E-01, 1.2200E-01, 1.0700E-01, 7.8500E-02, 
            3.6200E-02, 1.3700E-02, 6.5800E-03, 5.5000E-03, 5.4300E-03, 
            3.9000E-03, 6.1000E-04, 3.8000E-04, 2.1000E-04, 6.3000E-05, 
            5.8000E-06, 1.5000E-07} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 
            1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 
            1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4100E-01, 1.3800E-01, 
            1.3500E-01, 1.3000E-01, 1.2400E-01, 1.0700E-01, 7.7000E-02, 
            3.3800E-02, 1.2500E-02, 6.4000E-03, 5.7000E-03, 5.5600E-03, 
            3.7000E-03, 5.6000E-04, 4.0000E-04, 1.9000E-04, 5.3000E-05, 
            4.2000E-06, 8.0000E-08} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.8300E-01, 1.8300E-01, 1.8300E-01, 1.8300E-01, 
            1.8300E-01, 1.8300E-01, 1.8300E-01, 1.8300E-01, 1.8200E-01, 
            1.8100E-01, 1.8000E-01, 1.7500E-01, 1.6800E-01, 1.5800E-01, 
            1.4600E-01, 1.3300E-01, 1.2000E-01, 9.3900E-02, 6.0700E-02, 
            2.5700E-02, 9.7100E-03, 3.6800E-03, 1.8500E-03, 1.4700E-03, 
            1.4000E-03, 6.7000E-04, 2.1000E-04, 1.9000E-05, 2.1000E-06, 
            6.4000E-08, 5.0000E-10} );

    subshell_half_profiles[22] = 
      std::vector<double>( {5.5000E-01, 5.4800E-01, 5.4200E-01, 5.3100E-01, 
            5.1700E-01, 4.7900E-01, 4.3000E-01, 3.7600E-01, 3.1900E-01, 
            2.6400E-01, 2.1300E-01, 1.3200E-01, 8.1400E-02, 5.5700E-02, 
            4.6000E-02, 4.4000E-02, 4.3900E-02, 3.9700E-02, 2.4000E-02, 
            7.0000E-03, 4.9800E-03, 4.5000E-03, 2.9500E-03, 1.5600E-03, 
            6.3000E-04, 3.6000E-04, 7.7000E-05, 4.8000E-05, 1.5000E-05, 
            1.8000E-06, 1.2000E-06} );

    subshell_half_profiles[23] = 
      std::vector<double>( {3.7600E-01, 3.7600E-01, 3.7600E-01, 3.7500E-01, 
            3.7500E-01, 3.7300E-01, 3.6700E-01, 3.5700E-01, 3.4100E-01, 
            3.2000E-01, 2.9400E-01, 2.3300E-01, 1.6900E-01, 1.1500E-01, 
            7.3500E-02, 4.6300E-02, 3.0500E-02, 1.9600E-02, 1.8500E-02, 
            1.1400E-02, 4.1800E-03, 2.0300E-03, 1.8600E-03, 1.7300E-03, 
            8.8000E-04, 1.9000E-04, 1.4000E-04, 1.8000E-05, 1.1000E-05, 
            6.2000E-06, 9.1000E-07} );

    subshell_half_profiles[24] = 
      std::vector<double>( {4.4900E-01, 4.4900E-01, 4.4900E-01, 4.4900E-01, 
            4.4800E-01, 4.4200E-01, 4.3000E-01, 4.0900E-01, 3.7800E-01, 
            3.4000E-01, 2.9700E-01, 2.0900E-01, 1.3300E-01, 7.8800E-02, 
            4.5500E-02, 2.8200E-02, 2.0900E-02, 1.8400E-02, 1.6400E-02, 
            6.8800E-03, 2.3200E-03, 1.7400E-03, 1.6600E-03, 1.2700E-03, 
            4.6000E-04, 1.8000E-04, 8.6000E-05, 1.3000E-05, 1.1000E-05, 
            3.7000E-06, 2.8000E-07} );

    subshell_half_profiles[25] = 
      std::vector<double>( {1.9900E+00, 1.9100E+00, 1.6900E+00, 1.3900E+00, 
            1.0500E+00, 4.9900E-01, 1.9800E-01, 8.8900E-02, 6.4700E-02, 
            6.3100E-02, 6.1000E-02, 4.4400E-02, 2.5100E-02, 1.2500E-02, 
            6.3500E-03, 4.0900E-03, 3.5500E-03, 3.4400E-03, 2.3300E-03, 
            6.3100E-04, 3.7000E-04, 3.4400E-04, 2.3200E-04, 1.2300E-04, 
            4.7000E-05, 2.7000E-05, 5.7000E-06, 3.5000E-06, 1.1000E-06, 
            1.3000E-07, 8.8000E-08} );
  }
};

//! The default Compton profile generator implementation for A=95
template<>
struct DefaultComptonProfileGeneratorImpl<95u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 27 );

    subshell_half_profiles[0] = 
      std::vector<double>( {7.0500E-03, 7.0500E-03, 7.0500E-03, 7.0500E-03, 
            7.0500E-03, 7.0500E-03, 7.0500E-03, 7.0500E-03, 7.0500E-03, 
            7.0500E-03, 7.0500E-03, 7.0500E-03, 7.0500E-03, 7.0500E-03, 
            7.0500E-03, 7.0500E-03, 7.0500E-03, 7.0400E-03, 7.0400E-03, 
            7.0300E-03, 7.0100E-03, 6.9900E-03, 6.9700E-03, 6.9400E-03, 
            6.9000E-03, 6.7000E-03, 6.4000E-03, 5.7000E-03, 4.9000E-03, 
            3.4000E-03, 1.4000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 
            2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 2.5400E-02, 
            2.5400E-02, 2.5400E-02, 2.5300E-02, 2.5300E-02, 2.5300E-02, 
            2.5200E-02, 2.5200E-02, 2.5100E-02, 2.5000E-02, 2.4800E-02, 
            2.4300E-02, 2.3700E-02, 2.3000E-02, 2.2200E-02, 2.1400E-02, 
            1.9000E-02, 1.4000E-02, 9.1000E-03, 3.0000E-03, 9.9000E-04, 
            6.0000E-04, 3.6000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.2100E-02, 1.2100E-02, 1.2100E-02, 1.2100E-02, 
            1.2100E-02, 1.2100E-02, 1.2100E-02, 1.2100E-02, 1.2100E-02, 
            1.2100E-02, 1.2100E-02, 1.2100E-02, 1.2100E-02, 1.2100E-02, 
            1.2100E-02, 1.2100E-02, 1.2100E-02, 1.2100E-02, 1.2100E-02, 
            1.2100E-02, 1.2100E-02, 1.2100E-02, 1.2100E-02, 1.2100E-02, 
            1.2000E-02, 1.2000E-02, 1.1000E-02, 7.9000E-03, 5.2000E-03, 
            1.9000E-03, 2.8000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.4700E-02, 1.4700E-02, 1.4700E-02, 1.4700E-02, 
            1.4700E-02, 1.4700E-02, 1.4700E-02, 1.4700E-02, 1.4700E-02, 
            1.4700E-02, 1.4700E-02, 1.4700E-02, 1.4700E-02, 1.4700E-02, 
            1.4700E-02, 1.4700E-02, 1.4700E-02, 1.4700E-02, 1.4700E-02, 
            1.4700E-02, 1.4600E-02, 1.4600E-02, 1.4600E-02, 1.4500E-02, 
            1.4000E-02, 1.3000E-02, 1.2000E-02, 7.7000E-03, 4.2000E-03, 
            1.1000E-03, 9.1000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {5.5700E-02, 5.5700E-02, 5.5600E-02, 5.5600E-02, 
            5.5600E-02, 5.5600E-02, 5.5500E-02, 5.5400E-02, 5.5400E-02, 
            5.5200E-02, 5.5100E-02, 5.4800E-02, 5.4500E-02, 5.4000E-02, 
            5.3500E-02, 5.3000E-02, 5.2400E-02, 5.1000E-02, 4.8600E-02, 
            4.3700E-02, 3.8200E-02, 3.2500E-02, 2.6900E-02, 2.1800E-02, 
            1.4000E-02, 4.9000E-03, 4.3000E-03, 2.6000E-03, 7.5000E-04, 
            1.3000E-04, 9.1000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.2400E-02, 3.2400E-02, 3.2400E-02, 3.2400E-02, 
            3.2400E-02, 3.2400E-02, 3.2400E-02, 3.2400E-02, 3.2400E-02, 
            3.2400E-02, 3.2400E-02, 3.2300E-02, 3.2300E-02, 3.2300E-02, 
            3.2300E-02, 3.2300E-02, 3.2300E-02, 3.2300E-02, 3.2200E-02, 
            3.2000E-02, 3.1500E-02, 3.0600E-02, 2.9500E-02, 2.8000E-02, 
            2.4000E-02, 1.3000E-02, 4.9000E-03, 1.2000E-03, 1.1000E-03, 
            5.7000E-04, 8.5000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {3.6400E-02, 3.6400E-02, 3.6400E-02, 3.6400E-02, 
            3.6400E-02, 3.6400E-02, 3.6400E-02, 3.6400E-02, 3.6400E-02, 
            3.6400E-02, 3.6400E-02, 3.6400E-02, 3.6400E-02, 3.6400E-02, 
            3.6400E-02, 3.6400E-02, 3.6400E-02, 3.6300E-02, 3.6200E-02, 
            3.5700E-02, 3.4900E-02, 3.3500E-02, 3.1700E-02, 2.9400E-02, 
            2.4000E-02, 1.0000E-02, 3.3000E-03, 1.6000E-03, 1.3000E-03, 
            4.0000E-04, 3.1000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 
            2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 
            2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 
            2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 
            2.3300E-02, 2.3300E-02, 2.3200E-02, 2.3100E-02, 2.2900E-02, 
            2.2000E-02, 1.7000E-02, 1.1000E-02, 3.5000E-03, 9.8000E-04, 
            9.1000E-05, 2.5000E-06} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.4200E-02, 2.4200E-02, 2.4200E-02, 2.4200E-02, 
            2.4200E-02, 2.4200E-02, 2.4200E-02, 2.4200E-02, 2.4200E-02, 
            2.4200E-02, 2.4200E-02, 2.4200E-02, 2.4200E-02, 2.4200E-02, 
            2.4200E-02, 2.4200E-02, 2.4200E-02, 2.4200E-02, 2.4200E-02, 
            2.4200E-02, 2.4200E-02, 2.4100E-02, 2.3900E-02, 2.3600E-02, 
            2.3000E-02, 1.7000E-02, 1.1000E-02, 3.2000E-03, 8.1000E-04, 
            6.5000E-05, 1.3000E-06} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.0900E-01, 1.0900E-01, 1.0900E-01, 1.0900E-01, 
            1.0900E-01, 1.0900E-01, 1.0800E-01, 1.0700E-01, 1.0700E-01, 
            1.0600E-01, 1.0500E-01, 1.0200E-01, 9.9400E-02, 9.6100E-02, 
            9.2500E-02, 8.8500E-02, 8.4300E-02, 7.5300E-02, 6.1400E-02, 
            4.0300E-02, 2.5000E-02, 1.6300E-02, 1.2600E-02, 1.1700E-02, 
            1.1000E-02, 4.4000E-03, 1.3000E-03, 9.3000E-04, 2.9000E-04, 
            3.7000E-05, 2.5000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {6.8400E-02, 6.8400E-02, 6.8400E-02, 6.8400E-02, 
            6.8400E-02, 6.8400E-02, 6.8400E-02, 6.8400E-02, 6.8400E-02, 
            6.8400E-02, 6.8400E-02, 6.8400E-02, 6.8300E-02, 6.8100E-02, 
            6.8000E-02, 6.7700E-02, 6.7300E-02, 6.6300E-02, 6.3800E-02, 
            5.6700E-02, 4.6700E-02, 3.5500E-02, 2.5100E-02, 1.6800E-02, 
            7.5000E-03, 4.8000E-03, 2.9000E-03, 4.1000E-04, 2.8000E-04, 
            1.6000E-04, 2.4000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {7.6000E-02, 7.6000E-02, 7.6000E-02, 7.6000E-02, 
            7.6000E-02, 7.6000E-02, 7.6000E-02, 7.6000E-02, 7.6000E-02, 
            7.6000E-02, 7.5900E-02, 7.5900E-02, 7.5700E-02, 7.5500E-02, 
            7.5200E-02, 7.4800E-02, 7.4200E-02, 7.2500E-02, 6.8500E-02, 
            5.8200E-02, 4.4700E-02, 3.1300E-02, 2.0200E-02, 1.2700E-02, 
            6.4000E-03, 5.1000E-03, 2.1000E-03, 3.9000E-04, 3.5000E-04, 
            1.2000E-04, 9.1000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {5.5900E-02, 5.5900E-02, 5.5900E-02, 5.5900E-02, 
            5.5900E-02, 5.5900E-02, 5.5900E-02, 5.5900E-02, 5.5900E-02, 
            5.5900E-02, 5.5900E-02, 5.5900E-02, 5.5900E-02, 5.5900E-02, 
            5.5900E-02, 5.5800E-02, 5.5800E-02, 5.5700E-02, 5.5300E-02, 
            5.3300E-02, 4.9200E-02, 4.3000E-02, 3.5200E-02, 2.7200E-02, 
            1.4000E-02, 2.6000E-03, 2.2000E-03, 1.1000E-03, 3.3000E-04, 
            3.1000E-05, 8.3000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {5.7600E-02, 5.7600E-02, 5.7600E-02, 5.7600E-02, 
            5.7600E-02, 5.7600E-02, 5.7600E-02, 5.7600E-02, 5.7600E-02, 
            5.7600E-02, 5.7600E-02, 5.7600E-02, 5.7600E-02, 5.7600E-02, 
            5.7500E-02, 5.7500E-02, 5.7500E-02, 5.7300E-02, 5.6800E-02, 
            5.4600E-02, 4.9900E-02, 4.2900E-02, 3.4600E-02, 2.6200E-02, 
            1.3000E-02, 2.6000E-03, 2.3000E-03, 1.0000E-03, 2.8000E-04, 
            2.3000E-05, 4.4000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {4.4300E-02, 4.4300E-02, 4.4300E-02, 4.4300E-02, 
            4.4300E-02, 4.4300E-02, 4.4300E-02, 4.4300E-02, 4.4300E-02, 
            4.4300E-02, 4.4300E-02, 4.4300E-02, 4.4300E-02, 4.4300E-02, 
            4.4300E-02, 4.4300E-02, 4.4300E-02, 4.4300E-02, 4.4300E-02, 
            4.3800E-02, 4.2700E-02, 4.0500E-02, 3.7100E-02, 3.3000E-02, 
            2.4000E-02, 8.0000E-03, 2.3000E-03, 2.1000E-04, 2.4000E-05, 
            7.2000E-07, 5.5000E-09} );

    subshell_half_profiles[15] = 
      std::vector<double>( {4.5000E-02, 4.5000E-02, 4.5000E-02, 4.5000E-02, 
            4.5000E-02, 4.5000E-02, 4.5000E-02, 4.5000E-02, 4.5000E-02, 
            4.5000E-02, 4.5000E-02, 4.5000E-02, 4.5000E-02, 4.5000E-02, 
            4.5000E-02, 4.5000E-02, 4.5000E-02, 4.5000E-02, 4.5000E-02, 
            4.4500E-02, 4.3300E-02, 4.0800E-02, 3.7300E-02, 3.3000E-02, 
            2.4000E-02, 7.7000E-03, 2.2000E-03, 1.8000E-04, 2.0000E-05, 
            5.5000E-07, 3.4000E-09} );

    subshell_half_profiles[16] = 
      std::vector<double>( {2.2200E-01, 2.2200E-01, 2.2200E-01, 2.2100E-01, 
            2.2000E-01, 2.1700E-01, 2.1300E-01, 2.0800E-01, 2.0100E-01, 
            1.9400E-01, 1.8700E-01, 1.6900E-01, 1.5000E-01, 1.3100E-01, 
            1.1200E-01, 9.4200E-02, 7.8200E-02, 5.2900E-02, 3.1600E-02, 
            2.4100E-02, 2.3000E-02, 1.7400E-02, 1.0500E-02, 5.7400E-03, 
            3.1000E-03, 1.8000E-03, 4.0000E-04, 2.5000E-04, 8.3000E-05, 
            9.4000E-06, 6.4000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.4600E-01, 1.4600E-01, 1.4600E-01, 1.4600E-01, 
            1.4600E-01, 1.4600E-01, 1.4600E-01, 1.4600E-01, 1.4600E-01, 
            1.4500E-01, 1.4500E-01, 1.4300E-01, 1.4000E-01, 1.3600E-01, 
            1.3000E-01, 1.2300E-01, 1.1500E-01, 9.6200E-02, 6.6000E-02, 
            2.8300E-02, 1.3400E-02, 1.1000E-02, 1.0800E-02, 9.2500E-03, 
            4.4000E-03, 1.1000E-03, 8.3000E-04, 1.1000E-04, 6.4000E-05, 
            3.8000E-05, 5.8000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {1.6200E-01, 1.6200E-01, 1.6200E-01, 1.6200E-01, 
            1.6200E-01, 1.6200E-01, 1.6200E-01, 1.6200E-01, 1.6200E-01, 
            1.6100E-01, 1.6000E-01, 1.5700E-01, 1.5300E-01, 1.4600E-01, 
            1.3800E-01, 1.2800E-01, 1.1700E-01, 9.1600E-02, 5.6300E-02, 
            2.1300E-02, 1.2600E-02, 1.2200E-02, 1.0800E-02, 7.8700E-03, 
            2.9000E-03, 1.3000E-03, 6.2000E-04, 9.2000E-05, 8.2000E-05, 
            2.8000E-05, 2.2000E-06} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.3600E-01, 1.3600E-01, 1.3600E-01, 1.3600E-01, 
            1.3600E-01, 1.3600E-01, 1.3600E-01, 1.3600E-01, 1.3600E-01, 
            1.3600E-01, 1.3600E-01, 1.3500E-01, 1.3400E-01, 1.3300E-01, 
            1.3000E-01, 1.2600E-01, 1.2100E-01, 1.0700E-01, 8.0000E-02, 
            3.8400E-02, 1.5000E-02, 6.9400E-03, 5.5200E-03, 5.4600E-03, 
            4.1000E-03, 6.6000E-04, 3.9000E-04, 2.2000E-04, 6.9000E-05, 
            6.4000E-06, 1.7000E-07} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3900E-01, 
            1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3900E-01, 
            1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3800E-01, 1.3600E-01, 
            1.3300E-01, 1.2800E-01, 1.2200E-01, 1.0700E-01, 7.8500E-02, 
            3.5900E-02, 1.3600E-02, 6.6500E-03, 5.6900E-03, 5.6000E-03, 
            3.9000E-03, 6.0000E-04, 4.1000E-04, 2.1000E-04, 5.8000E-05, 
            4.7000E-06, 9.1000E-08} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.7400E-01, 1.7400E-01, 1.7400E-01, 1.7400E-01, 
            1.7400E-01, 1.7400E-01, 1.7400E-01, 1.7400E-01, 1.7300E-01, 
            1.7300E-01, 1.7200E-01, 1.6800E-01, 1.6300E-01, 1.5400E-01, 
            1.4400E-01, 1.3300E-01, 1.2100E-01, 9.6800E-02, 6.4600E-02, 
            2.8700E-02, 1.1300E-02, 4.3700E-03, 2.1000E-03, 1.5600E-03, 
            1.5000E-03, 7.5000E-04, 2.4000E-04, 2.2000E-05, 2.6000E-06, 
            7.8000E-08, 6.1000E-10} );

    subshell_half_profiles[22] = 
      std::vector<double>( {1.8700E-01, 1.8700E-01, 1.8700E-01, 1.8700E-01, 
            1.8700E-01, 1.8700E-01, 1.8700E-01, 1.8600E-01, 1.8600E-01, 
            1.8500E-01, 1.8300E-01, 1.7700E-01, 1.6800E-01, 1.5700E-01, 
            1.4400E-01, 1.3100E-01, 1.1700E-01, 9.1700E-02, 5.9600E-02, 
            2.5700E-02, 9.9100E-03, 3.7900E-03, 1.8800E-03, 1.4600E-03, 
            1.4000E-03, 6.8000E-04, 2.1000E-04, 1.9000E-05, 2.1000E-06, 
            5.6000E-08, 3.6000E-10} );

    subshell_half_profiles[23] = 
      std::vector<double>( {5.3800E-01, 5.3600E-01, 5.3000E-01, 5.2000E-01, 
            5.0700E-01, 4.7100E-01, 4.2500E-01, 3.7300E-01, 3.1900E-01, 
            2.6600E-01, 2.1600E-01, 1.3600E-01, 8.4600E-02, 5.7100E-02, 
            4.6000E-02, 4.3200E-02, 4.3000E-02, 3.9800E-02, 2.5300E-02, 
            7.5300E-03, 4.9400E-03, 4.5900E-03, 3.1600E-03, 1.7200E-03, 
            6.5000E-04, 3.8000E-04, 8.3000E-05, 4.9000E-05, 1.7000E-05, 
            1.8000E-06, 1.2000E-06} );

    subshell_half_profiles[24] = 
      std::vector<double>( {3.6700E-01, 3.6700E-01, 3.6700E-01, 3.6700E-01, 
            3.6600E-01, 3.6400E-01, 3.5900E-01, 3.5000E-01, 3.3600E-01, 
            3.1600E-01, 2.9200E-01, 2.3400E-01, 1.7400E-01, 1.2000E-01, 
            7.8100E-02, 4.9700E-02, 3.2600E-02, 1.9700E-02, 1.8200E-02, 
            1.2000E-02, 4.6300E-03, 2.1100E-03, 1.8500E-03, 1.7600E-03, 
            9.6000E-04, 1.9000E-04, 1.5000E-04, 2.0000E-05, 1.1000E-05, 
            6.5000E-06, 1.0000E-06} );

    subshell_half_profiles[25] = 
      std::vector<double>( {4.4100E-01, 4.4100E-01, 4.4100E-01, 4.4100E-01, 
            4.4000E-01, 4.3500E-01, 4.2300E-01, 4.0300E-01, 3.7500E-01, 
            3.3900E-01, 2.9800E-01, 2.1300E-01, 1.3800E-01, 8.2900E-02, 
            4.8400E-02, 2.9700E-02, 2.1300E-02, 1.8000E-02, 1.6500E-02, 
            7.3800E-03, 2.4700E-03, 1.7300E-03, 1.6700E-03, 1.3300E-03, 
            5.1000E-04, 1.8000E-04, 9.2000E-05, 1.3000E-05, 1.2000E-05, 
            4.0000E-06, 3.1000E-07} );

    subshell_half_profiles[26] = 
      std::vector<double>( {1.9700E+00, 1.8900E+00, 1.6800E+00, 1.3800E+00, 
            1.0600E+00, 5.1000E-01, 2.0600E-01, 9.0700E-02, 6.3200E-02, 
            6.0900E-02, 5.9400E-02, 4.4600E-02, 2.6000E-02, 1.3300E-02, 
            6.7200E-03, 4.1400E-03, 3.4300E-03, 3.3200E-03, 2.3700E-03, 
            6.7500E-04, 3.5900E-04, 3.4000E-04, 2.4200E-04, 1.3300E-04, 
            4.7000E-05, 2.8000E-05, 6.1000E-06, 3.5000E-06, 1.2000E-06, 
            1.3000E-07, 8.9000E-08} );
  }
};

//! The default Compton profile generator implementation for A=96
template<>
struct DefaultComptonProfileGeneratorImpl<96u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 28 );

    subshell_half_profiles[0] = 
      std::vector<double>( {6.9300E-03, 6.9300E-03, 6.9300E-03, 6.9300E-03, 
            6.9300E-03, 6.9300E-03, 6.9300E-03, 6.9300E-03, 6.9300E-03, 
            6.9300E-03, 6.9300E-03, 6.9300E-03, 6.9300E-03, 6.9300E-03, 
            6.9300E-03, 6.9300E-03, 6.9300E-03, 6.9200E-03, 6.9200E-03, 
            6.9100E-03, 6.8900E-03, 6.8700E-03, 6.8500E-03, 6.8300E-03, 
            6.8000E-03, 6.6000E-03, 6.3000E-03, 5.6000E-03, 4.9000E-03, 
            3.4000E-03, 1.4000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.5000E-02, 2.5000E-02, 2.5000E-02, 2.5000E-02, 
            2.5000E-02, 2.5000E-02, 2.5000E-02, 2.5000E-02, 2.5000E-02, 
            2.5000E-02, 2.5000E-02, 2.4900E-02, 2.4900E-02, 2.4900E-02, 
            2.4800E-02, 2.4800E-02, 2.4700E-02, 2.4600E-02, 2.4400E-02, 
            2.4000E-02, 2.3400E-02, 2.2700E-02, 2.2000E-02, 2.1100E-02, 
            1.9000E-02, 1.4000E-02, 9.2000E-03, 3.1000E-03, 1.0000E-03, 
            5.9000E-04, 3.6000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.1900E-02, 1.1900E-02, 1.1900E-02, 1.1900E-02, 
            1.1900E-02, 1.1900E-02, 1.1900E-02, 1.1900E-02, 1.1900E-02, 
            1.1900E-02, 1.1900E-02, 1.1900E-02, 1.1900E-02, 1.1900E-02, 
            1.1900E-02, 1.1900E-02, 1.1900E-02, 1.1900E-02, 1.1900E-02, 
            1.1900E-02, 1.1900E-02, 1.1900E-02, 1.1900E-02, 1.1900E-02, 
            1.1900E-02, 1.1000E-02, 1.1000E-02, 7.9000E-03, 5.2000E-03, 
            1.9000E-03, 3.0000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.4500E-02, 1.4500E-02, 1.4500E-02, 1.4500E-02, 
            1.4500E-02, 1.4500E-02, 1.4500E-02, 1.4500E-02, 1.4500E-02, 
            1.4500E-02, 1.4500E-02, 1.4500E-02, 1.4500E-02, 1.4500E-02, 
            1.4500E-02, 1.4500E-02, 1.4500E-02, 1.4500E-02, 1.4500E-02, 
            1.4500E-02, 1.4500E-02, 1.4500E-02, 1.4400E-02, 1.4400E-02, 
            1.4000E-02, 1.3000E-02, 1.2000E-02, 7.7000E-03, 4.3000E-03, 
            1.1000E-03, 9.6000E-05} );

    subshell_half_profiles[4] = 
      std::vector<double>( {5.4800E-02, 5.4800E-02, 5.4800E-02, 5.4800E-02, 
            5.4800E-02, 5.4700E-02, 5.4700E-02, 5.4600E-02, 5.4500E-02, 
            5.4400E-02, 5.4300E-02, 5.4000E-02, 5.3600E-02, 5.3200E-02, 
            5.2800E-02, 5.2200E-02, 5.1700E-02, 5.0300E-02, 4.8000E-02, 
            4.3300E-02, 3.8100E-02, 3.2500E-02, 2.7100E-02, 2.2100E-02, 
            1.4000E-02, 5.0000E-03, 4.2000E-03, 2.7000E-03, 8.1000E-04, 
            1.3000E-04, 9.2000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.1800E-02, 3.1800E-02, 3.1800E-02, 3.1800E-02, 
            3.1800E-02, 3.1800E-02, 3.1800E-02, 3.1800E-02, 3.1800E-02, 
            3.1800E-02, 3.1800E-02, 3.1800E-02, 3.1800E-02, 3.1800E-02, 
            3.1800E-02, 3.1800E-02, 3.1800E-02, 3.1800E-02, 3.1700E-02, 
            3.1500E-02, 3.1000E-02, 3.0200E-02, 2.9200E-02, 2.7700E-02, 
            2.4000E-02, 1.3000E-02, 5.1000E-03, 1.2000E-03, 1.1000E-03, 
            5.8000E-04, 9.1000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {3.5900E-02, 3.5900E-02, 3.5900E-02, 3.5900E-02, 
            3.5900E-02, 3.5900E-02, 3.5900E-02, 3.5900E-02, 3.5900E-02, 
            3.5900E-02, 3.5900E-02, 3.5900E-02, 3.5900E-02, 3.5900E-02, 
            3.5900E-02, 3.5900E-02, 3.5900E-02, 3.5800E-02, 3.5700E-02, 
            3.5300E-02, 3.4500E-02, 3.3200E-02, 3.1500E-02, 2.9200E-02, 
            2.4000E-02, 1.0000E-02, 3.4000E-03, 1.6000E-03, 1.3000E-03, 
            4.1000E-04, 3.3000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 
            2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 
            2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 
            2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 
            2.3000E-02, 2.3000E-02, 2.2900E-02, 2.2800E-02, 2.2600E-02, 
            2.2000E-02, 1.7000E-02, 1.2000E-02, 3.7000E-03, 1.0000E-03, 
            9.8000E-05, 2.7000E-06} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.3900E-02, 2.3900E-02, 2.3900E-02, 2.3900E-02, 
            2.3900E-02, 2.3900E-02, 2.3900E-02, 2.3900E-02, 2.3900E-02, 
            2.3900E-02, 2.3900E-02, 2.3900E-02, 2.3900E-02, 2.3900E-02, 
            2.3900E-02, 2.3900E-02, 2.3900E-02, 2.3900E-02, 2.3900E-02, 
            2.3900E-02, 2.3800E-02, 2.3800E-02, 2.3600E-02, 2.3300E-02, 
            2.2000E-02, 1.7000E-02, 1.1000E-02, 3.3000E-03, 8.6000E-04, 
            7.0000E-05, 1.5000E-06} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.0700E-01, 1.0700E-01, 1.0700E-01, 1.0700E-01, 
            1.0700E-01, 1.0700E-01, 1.0600E-01, 1.0600E-01, 1.0500E-01, 
            1.0400E-01, 1.0300E-01, 1.0100E-01, 9.8000E-02, 9.4800E-02, 
            9.1300E-02, 8.7500E-02, 8.3500E-02, 7.4900E-02, 6.1400E-02, 
            4.0800E-02, 2.5600E-02, 1.6600E-02, 1.2700E-02, 1.1600E-02, 
            1.1000E-02, 4.7000E-03, 1.3000E-03, 9.5000E-04, 3.2000E-04, 
            3.7000E-05, 2.6000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {6.7200E-02, 6.7200E-02, 6.7200E-02, 6.7200E-02, 
            6.7200E-02, 6.7200E-02, 6.7200E-02, 6.7200E-02, 6.7200E-02, 
            6.7200E-02, 6.7200E-02, 6.7100E-02, 6.7000E-02, 6.6900E-02, 
            6.6800E-02, 6.6500E-02, 6.6200E-02, 6.5200E-02, 6.2900E-02, 
            5.6300E-02, 4.6800E-02, 3.6100E-02, 2.5800E-02, 1.7500E-02, 
            7.8000E-03, 4.8000E-03, 3.1000E-03, 4.3000E-04, 2.7000E-04, 
            1.6000E-04, 2.6000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {7.4800E-02, 7.4800E-02, 7.4800E-02, 7.4800E-02, 
            7.4800E-02, 7.4800E-02, 7.4800E-02, 7.4800E-02, 7.4800E-02, 
            7.4800E-02, 7.4700E-02, 7.4700E-02, 7.4600E-02, 7.4400E-02, 
            7.4100E-02, 7.3700E-02, 7.3100E-02, 7.1500E-02, 6.7800E-02, 
            5.8000E-02, 4.5100E-02, 3.1900E-02, 2.0900E-02, 1.3200E-02, 
            6.5000E-03, 5.1000E-03, 2.2000E-03, 3.9000E-04, 3.5000E-04, 
            1.2000E-04, 9.8000E-06} );

    subshell_half_profiles[12] = 
      std::vector<double>( {5.4900E-02, 5.4900E-02, 5.4900E-02, 5.4900E-02, 
            5.4900E-02, 5.4900E-02, 5.4900E-02, 5.4900E-02, 5.4900E-02, 
            5.4900E-02, 5.4900E-02, 5.4900E-02, 5.4900E-02, 5.4900E-02, 
            5.4900E-02, 5.4900E-02, 5.4900E-02, 5.4800E-02, 5.4400E-02, 
            5.2600E-02, 4.8800E-02, 4.2900E-02, 3.5600E-02, 2.7800E-02, 
            1.5000E-02, 2.7000E-03, 2.2000E-03, 1.1000E-03, 3.6000E-04, 
            3.4000E-05, 9.2000E-07} );

    subshell_half_profiles[13] = 
      std::vector<double>( {5.6600E-02, 5.6600E-02, 5.6600E-02, 5.6600E-02, 
            5.6600E-02, 5.6600E-02, 5.6600E-02, 5.6600E-02, 5.6600E-02, 
            5.6600E-02, 5.6600E-02, 5.6600E-02, 5.6600E-02, 5.6600E-02, 
            5.6600E-02, 5.6600E-02, 5.6500E-02, 5.6400E-02, 5.5900E-02, 
            5.3900E-02, 4.9600E-02, 4.3000E-02, 3.5000E-02, 2.6800E-02, 
            1.3000E-02, 2.6000E-03, 2.3000E-03, 1.1000E-03, 3.0000E-04, 
            2.5000E-05, 4.9000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {4.3500E-02, 4.3500E-02, 4.3500E-02, 4.3500E-02, 
            4.3500E-02, 4.3500E-02, 4.3500E-02, 4.3500E-02, 4.3500E-02, 
            4.3500E-02, 4.3500E-02, 4.3500E-02, 4.3500E-02, 4.3500E-02, 
            4.3500E-02, 4.3500E-02, 4.3500E-02, 4.3500E-02, 4.3400E-02, 
            4.3100E-02, 4.2000E-02, 4.0000E-02, 3.7000E-02, 3.3100E-02, 
            2.4000E-02, 8.4000E-03, 2.5000E-03, 2.3000E-04, 2.7000E-05, 
            8.2000E-07, 6.3000E-09} );

    subshell_half_profiles[15] = 
      std::vector<double>( {4.4200E-02, 4.4200E-02, 4.4200E-02, 4.4200E-02, 
            4.4200E-02, 4.4200E-02, 4.4200E-02, 4.4200E-02, 4.4200E-02, 
            4.4200E-02, 4.4200E-02, 4.4200E-02, 4.4200E-02, 4.4200E-02, 
            4.4200E-02, 4.4200E-02, 4.4200E-02, 4.4200E-02, 4.4100E-02, 
            4.3700E-02, 4.2600E-02, 4.0400E-02, 3.7200E-02, 3.3100E-02, 
            2.4000E-02, 8.1000E-03, 2.3000E-03, 2.0000E-04, 2.3000E-05, 
            6.3000E-07, 3.9000E-09} );

    subshell_half_profiles[16] = 
      std::vector<double>( {2.1700E-01, 2.1700E-01, 2.1600E-01, 2.1600E-01, 
            2.1500E-01, 2.1200E-01, 2.0800E-01, 2.0300E-01, 1.9700E-01, 
            1.9100E-01, 1.8300E-01, 1.6700E-01, 1.4900E-01, 1.3100E-01, 
            1.1200E-01, 9.5300E-02, 7.9600E-02, 5.4400E-02, 3.2500E-02, 
            2.3800E-02, 2.3000E-02, 1.8000E-02, 1.1200E-02, 6.2100E-03, 
            3.1000E-03, 1.9000E-03, 4.3000E-04, 2.6000E-04, 9.1000E-05, 
            9.7000E-06, 6.6000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 
            1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 1.4200E-01, 
            1.4200E-01, 1.4100E-01, 1.4000E-01, 1.3700E-01, 1.3300E-01, 
            1.2800E-01, 1.2200E-01, 1.1400E-01, 9.6600E-02, 6.7600E-02, 
            3.0000E-02, 1.4000E-02, 1.0900E-02, 1.0700E-02, 9.4900E-03, 
            4.8000E-03, 1.1000E-03, 8.7000E-04, 1.2000E-04, 6.4000E-05, 
            4.0000E-05, 6.3000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {1.5900E-01, 1.5900E-01, 1.5900E-01, 1.5900E-01, 
            1.5900E-01, 1.5900E-01, 1.5900E-01, 1.5800E-01, 1.5800E-01, 
            1.5700E-01, 1.5700E-01, 1.5400E-01, 1.5000E-01, 1.4400E-01, 
            1.3600E-01, 1.2700E-01, 1.1600E-01, 9.2600E-02, 5.8200E-02, 
            2.2500E-02, 1.2800E-02, 1.2200E-02, 1.1000E-02, 8.2600E-03, 
            3.1000E-03, 1.3000E-03, 6.7000E-04, 9.5000E-05, 8.4000E-05, 
            3.0000E-05, 2.4000E-06} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.3200E-01, 1.3200E-01, 1.3200E-01, 1.3200E-01, 
            1.3200E-01, 1.3200E-01, 1.3200E-01, 1.3200E-01, 1.3200E-01, 
            1.3200E-01, 1.3200E-01, 1.3200E-01, 1.3100E-01, 1.2900E-01, 
            1.2700E-01, 1.2400E-01, 1.1900E-01, 1.0600E-01, 8.1500E-02, 
            4.0800E-02, 1.6500E-02, 7.4100E-03, 5.5900E-03, 5.5000E-03, 
            4.3000E-03, 7.3000E-04, 3.9000E-04, 2.3000E-04, 7.5000E-05, 
            7.2000E-06, 1.9000E-07} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.3600E-01, 1.3600E-01, 1.3600E-01, 1.3600E-01, 
            1.3600E-01, 1.3600E-01, 1.3600E-01, 1.3600E-01, 1.3600E-01, 
            1.3600E-01, 1.3500E-01, 1.3500E-01, 1.3400E-01, 1.3300E-01, 
            1.3000E-01, 1.2600E-01, 1.2100E-01, 1.0700E-01, 8.0100E-02, 
            3.8200E-02, 1.4800E-02, 7.0000E-03, 5.7200E-03, 5.6600E-03, 
            4.1000E-03, 6.5000E-04, 4.1000E-04, 2.2000E-04, 6.3000E-05, 
            5.2000E-06, 1.0000E-07} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.5900E-01, 1.5900E-01, 1.5900E-01, 1.5900E-01, 
            1.5900E-01, 1.5900E-01, 1.5900E-01, 1.5900E-01, 1.5900E-01, 
            1.5900E-01, 1.5900E-01, 1.5700E-01, 1.5400E-01, 1.4800E-01, 
            1.4100E-01, 1.3300E-01, 1.2300E-01, 1.0200E-01, 7.0800E-02, 
            3.3400E-02, 1.3800E-02, 5.4300E-03, 2.5100E-03, 1.7500E-03, 
            1.6000E-03, 8.7000E-04, 2.9000E-04, 2.7000E-05, 3.2000E-06, 
            1.0000E-07, 7.9000E-10} );

    subshell_half_profiles[22] = 
      std::vector<double>( {1.6600E-01, 1.6600E-01, 1.6600E-01, 1.6600E-01, 
            1.6600E-01, 1.6600E-01, 1.6600E-01, 1.6600E-01, 1.6600E-01, 
            1.6600E-01, 1.6500E-01, 1.6300E-01, 1.5800E-01, 1.5100E-01, 
            1.4300E-01, 1.3300E-01, 1.2200E-01, 9.9300E-02, 6.7800E-02, 
            3.1100E-02, 1.2500E-02, 4.8900E-03, 2.3200E-03, 1.6900E-03, 
            1.6000E-03, 8.2000E-04, 2.6000E-04, 2.4000E-05, 2.7000E-06, 
            7.4000E-08, 4.9000E-10} );

    subshell_half_profiles[23] = 
      std::vector<double>( {5.1600E-01, 5.1500E-01, 5.0900E-01, 5.0100E-01, 
            4.8900E-01, 4.5600E-01, 4.1500E-01, 3.6700E-01, 3.1700E-01, 
            2.6700E-01, 2.2100E-01, 1.4300E-01, 8.9900E-02, 6.0300E-02, 
            4.7100E-02, 4.3200E-02, 4.2700E-02, 4.0600E-02, 2.7300E-02, 
            8.4200E-03, 5.0300E-03, 4.7700E-03, 3.4500E-03, 1.9500E-03, 
            6.9000E-04, 4.2000E-04, 9.3000E-05, 5.2000E-05, 1.9000E-05, 
            1.9000E-06, 1.3000E-06} );

    subshell_half_profiles[24] = 
      std::vector<double>( {3.5300E-01, 3.5300E-01, 3.5300E-01, 3.5300E-01, 
            3.5300E-01, 3.5100E-01, 3.4700E-01, 3.3900E-01, 3.2600E-01, 
            3.0900E-01, 2.8800E-01, 2.3500E-01, 1.7900E-01, 1.2700E-01, 
            8.5100E-02, 5.5200E-02, 3.6300E-02, 2.0600E-02, 1.8300E-02, 
            1.3000E-02, 5.3000E-03, 2.2900E-03, 1.8900E-03, 1.8300E-03, 
            1.1000E-03, 2.0000E-04, 1.6000E-04, 2.3000E-05, 1.1000E-05, 
            7.0000E-06, 1.1000E-06} );

    subshell_half_profiles[25] = 
      std::vector<double>( {4.2100E-01, 4.2100E-01, 4.2100E-01, 4.2100E-01, 
            4.2000E-01, 4.1600E-01, 4.0700E-01, 3.9000E-01, 3.6600E-01, 
            3.3500E-01, 2.9900E-01, 2.2000E-01, 1.4800E-01, 9.2100E-02, 
            5.5000E-02, 3.3800E-02, 2.3400E-02, 1.8400E-02, 1.7300E-02, 
            8.4000E-03, 2.8200E-03, 1.8200E-03, 1.7700E-03, 1.4600E-03, 
            5.8000E-04, 1.9000E-04, 1.0000E-04, 1.4000E-05, 1.2000E-05, 
            4.4000E-06, 3.5000E-07} );

    subshell_half_profiles[26] = 
      std::vector<double>( {5.1600E-01, 5.1600E-01, 5.1600E-01, 5.1600E-01, 
            5.1500E-01, 5.0900E-01, 4.9000E-01, 4.5500E-01, 4.0600E-01, 
            3.5000E-01, 2.9400E-01, 1.9300E-01, 1.1800E-01, 6.9400E-02, 
            3.9400E-02, 2.2000E-02, 1.2700E-02, 5.8900E-03, 4.9400E-03, 
            3.7600E-03, 1.7300E-03, 6.6800E-04, 3.7600E-04, 3.4600E-04, 
            2.9000E-04, 5.1000E-05, 2.5000E-05, 1.5000E-05, 5.0000E-06, 
            4.8000E-07, 1.3000E-08} );

    subshell_half_profiles[27] = 
      std::vector<double>( {1.8300E+00, 1.7600E+00, 1.5900E+00, 1.3400E+00, 
            1.0600E+00, 5.5500E-01, 2.4600E-01, 1.0900E-01, 6.8400E-02, 
            6.2000E-02, 6.1600E-02, 5.0700E-02, 3.2300E-02, 1.7600E-02, 
            9.0900E-03, 5.2700E-03, 4.0000E-03, 3.7500E-03, 2.9000E-03, 
            8.8100E-04, 4.1600E-04, 3.9800E-04, 2.9800E-04, 1.7000E-04, 
            5.7000E-05, 3.5000E-05, 7.7000E-06, 4.2000E-06, 1.5000E-06, 
            1.6000E-07, 1.1000E-07} );
  }
};

//! The default Compton profile generator implementation for A=97
template<>
struct DefaultComptonProfileGeneratorImpl<97u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 27 );

    subshell_half_profiles[0] = 
      std::vector<double>( {6.8100E-03, 6.8100E-03, 6.8100E-03, 6.8100E-03, 
            6.8100E-03, 6.8100E-03, 6.8100E-03, 6.8100E-03, 6.8100E-03, 
            6.8100E-03, 6.8100E-03, 6.8100E-03, 6.8100E-03, 6.8100E-03, 
            6.8100E-03, 6.8100E-03, 6.8100E-03, 6.8000E-03, 6.8000E-03, 
            6.7900E-03, 6.7700E-03, 6.7600E-03, 6.7400E-03, 6.7100E-03, 
            6.7000E-03, 6.5000E-03, 6.2000E-03, 5.6000E-03, 4.8000E-03, 
            3.4000E-03, 1.5000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.4600E-02, 2.4600E-02, 2.4600E-02, 2.4600E-02, 
            2.4600E-02, 2.4600E-02, 2.4600E-02, 2.4600E-02, 2.4600E-02, 
            2.4600E-02, 2.4600E-02, 2.4500E-02, 2.4500E-02, 2.4500E-02, 
            2.4400E-02, 2.4400E-02, 2.4300E-02, 2.4200E-02, 2.4000E-02, 
            2.3600E-02, 2.3100E-02, 2.2400E-02, 2.1700E-02, 2.0900E-02, 
            1.9000E-02, 1.4000E-02, 9.4000E-03, 3.2000E-03, 1.1000E-03, 
            5.8000E-04, 3.7000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 
            1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 
            1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 
            1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 
            1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 1.1700E-02, 
            1.1700E-02, 1.1000E-02, 1.0000E-02, 7.9000E-03, 5.3000E-03, 
            2.0000E-03, 3.2000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.4300E-02, 1.4300E-02, 1.4300E-02, 1.4300E-02, 
            1.4300E-02, 1.4300E-02, 1.4300E-02, 1.4300E-02, 1.4300E-02, 
            1.4300E-02, 1.4300E-02, 1.4300E-02, 1.4300E-02, 1.4300E-02, 
            1.4300E-02, 1.4300E-02, 1.4300E-02, 1.4300E-02, 1.4300E-02, 
            1.4300E-02, 1.4300E-02, 1.4300E-02, 1.4200E-02, 1.4200E-02, 
            1.4000E-02, 1.3000E-02, 1.2000E-02, 7.8000E-03, 4.4000E-03, 
            1.2000E-03, 1.0000E-04} );

    subshell_half_profiles[4] = 
      std::vector<double>( {5.3900E-02, 5.3900E-02, 5.3900E-02, 5.3900E-02, 
            5.3900E-02, 5.3900E-02, 5.3800E-02, 5.3700E-02, 5.3700E-02, 
            5.3600E-02, 5.3400E-02, 5.3200E-02, 5.2800E-02, 5.2400E-02, 
            5.2000E-02, 5.1500E-02, 5.0900E-02, 4.9700E-02, 4.7400E-02, 
            4.3000E-02, 3.7900E-02, 3.2500E-02, 2.7200E-02, 2.2300E-02, 
            1.4000E-02, 5.0000E-03, 4.1000E-03, 2.7000E-03, 8.6000E-04, 
            1.3000E-04, 9.4000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.1300E-02, 3.1300E-02, 3.1300E-02, 3.1300E-02, 
            3.1300E-02, 3.1300E-02, 3.1300E-02, 3.1300E-02, 3.1300E-02, 
            3.1300E-02, 3.1300E-02, 3.1300E-02, 3.1300E-02, 3.1300E-02, 
            3.1300E-02, 3.1300E-02, 3.1300E-02, 3.1300E-02, 3.1200E-02, 
            3.1000E-02, 3.0500E-02, 2.9800E-02, 2.8800E-02, 2.7500E-02, 
            2.4000E-02, 1.3000E-02, 5.4000E-03, 1.2000E-03, 1.1000E-03, 
            6.0000E-04, 9.7000E-05} );

    subshell_half_profiles[6] = 
      std::vector<double>( {3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 
            3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 
            3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 3.5500E-02, 
            3.5500E-02, 3.5400E-02, 3.5400E-02, 3.5400E-02, 3.5300E-02, 
            3.4900E-02, 3.4100E-02, 3.2900E-02, 3.1200E-02, 2.9100E-02, 
            2.4000E-02, 1.1000E-02, 3.6000E-03, 1.5000E-03, 1.3000E-03, 
            4.3000E-04, 3.6000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 
            2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 
            2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 
            2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 
            2.2700E-02, 2.2700E-02, 2.2600E-02, 2.2500E-02, 2.2300E-02, 
            2.2000E-02, 1.7000E-02, 1.2000E-02, 3.8000E-03, 1.1000E-03, 
            1.1000E-04, 3.0000E-06} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.3600E-02, 2.3600E-02, 2.3600E-02, 2.3600E-02, 
            2.3600E-02, 2.3600E-02, 2.3600E-02, 2.3600E-02, 2.3600E-02, 
            2.3600E-02, 2.3600E-02, 2.3600E-02, 2.3600E-02, 2.3600E-02, 
            2.3600E-02, 2.3600E-02, 2.3600E-02, 2.3600E-02, 2.3600E-02, 
            2.3600E-02, 2.3600E-02, 2.3500E-02, 2.3300E-02, 2.3100E-02, 
            2.2000E-02, 1.7000E-02, 1.1000E-02, 3.4000E-03, 9.0000E-04, 
            7.5000E-05, 1.6000E-06} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.0500E-01, 1.0500E-01, 1.0500E-01, 1.0500E-01, 
            1.0500E-01, 1.0500E-01, 1.0400E-01, 1.0400E-01, 1.0300E-01, 
            1.0200E-01, 1.0100E-01, 9.9100E-02, 9.6500E-02, 9.3500E-02, 
            9.0200E-02, 8.6600E-02, 8.2700E-02, 7.4400E-02, 6.1500E-02, 
            4.1400E-02, 2.6200E-02, 1.7000E-02, 1.2800E-02, 1.1500E-02, 
            1.1000E-02, 4.9000E-03, 1.4000E-03, 9.6000E-04, 3.4000E-04, 
            3.8000E-05, 2.6000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {6.6000E-02, 6.6000E-02, 6.6000E-02, 6.6000E-02, 
            6.6000E-02, 6.6000E-02, 6.6000E-02, 6.6000E-02, 6.6000E-02, 
            6.6000E-02, 6.5900E-02, 6.5900E-02, 6.5800E-02, 6.5700E-02, 
            6.5600E-02, 6.5400E-02, 6.5100E-02, 6.4200E-02, 6.2000E-02, 
            5.5800E-02, 4.6900E-02, 3.6500E-02, 2.6500E-02, 1.8200E-02, 
            8.2000E-03, 4.7000E-03, 3.2000E-03, 4.6000E-04, 2.7000E-04, 
            1.7000E-04, 2.8000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {7.3600E-02, 7.3600E-02, 7.3600E-02, 7.3600E-02, 
            7.3600E-02, 7.3600E-02, 7.3600E-02, 7.3600E-02, 7.3600E-02, 
            7.3600E-02, 7.3600E-02, 7.3500E-02, 7.3400E-02, 7.3200E-02, 
            7.3000E-02, 7.2600E-02, 7.2100E-02, 7.0600E-02, 6.7100E-02, 
            5.7800E-02, 4.5400E-02, 3.2500E-02, 2.1600E-02, 1.3700E-02, 
            6.6000E-03, 5.2000E-03, 2.3000E-03, 4.0000E-04, 3.6000E-04, 
            1.3000E-04, 1.1000E-05} );

    subshell_half_profiles[12] = 
      std::vector<double>( {5.4000E-02, 5.4000E-02, 5.4000E-02, 5.4000E-02, 
            5.4000E-02, 5.4000E-02, 5.4000E-02, 5.4000E-02, 5.4000E-02, 
            5.4000E-02, 5.4000E-02, 5.4000E-02, 5.4000E-02, 5.4000E-02, 
            5.4000E-02, 5.4000E-02, 5.4000E-02, 5.3900E-02, 5.3500E-02, 
            5.1900E-02, 4.8400E-02, 4.2900E-02, 3.5900E-02, 2.8300E-02, 
            1.5000E-02, 2.8000E-03, 2.2000E-03, 1.2000E-03, 3.8000E-04, 
            3.7000E-05, 1.0000E-06} );

    subshell_half_profiles[13] = 
      std::vector<double>( {5.5700E-02, 5.5700E-02, 5.5700E-02, 5.5700E-02, 
            5.5700E-02, 5.5700E-02, 5.5700E-02, 5.5700E-02, 5.5700E-02, 
            5.5700E-02, 5.5700E-02, 5.5700E-02, 5.5700E-02, 5.5700E-02, 
            5.5700E-02, 5.5700E-02, 5.5600E-02, 5.5500E-02, 5.5100E-02, 
            5.3200E-02, 4.9200E-02, 4.3000E-02, 3.5300E-02, 2.7300E-02, 
            1.4000E-02, 2.7000E-03, 2.3000E-03, 1.1000E-03, 3.2000E-04, 
            2.7000E-05, 5.4000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {4.2700E-02, 4.2700E-02, 4.2700E-02, 4.2700E-02, 
            4.2700E-02, 4.2700E-02, 4.2700E-02, 4.2700E-02, 4.2700E-02, 
            4.2700E-02, 4.2700E-02, 4.2700E-02, 4.2700E-02, 4.2700E-02, 
            4.2700E-02, 4.2700E-02, 4.2700E-02, 4.2600E-02, 4.2600E-02, 
            4.2300E-02, 4.1400E-02, 3.9600E-02, 3.6800E-02, 3.3100E-02, 
            2.5000E-02, 8.8000E-03, 2.7000E-03, 2.5000E-04, 3.0000E-05, 
            9.3000E-07, 7.2000E-09} );

    subshell_half_profiles[15] = 
      std::vector<double>( {4.3400E-02, 4.3400E-02, 4.3400E-02, 4.3400E-02, 
            4.3400E-02, 4.3400E-02, 4.3400E-02, 4.3400E-02, 4.3400E-02, 
            4.3400E-02, 4.3400E-02, 4.3400E-02, 4.3400E-02, 4.3400E-02, 
            4.3400E-02, 4.3400E-02, 4.3400E-02, 4.3300E-02, 4.3300E-02, 
            4.3000E-02, 4.2000E-02, 4.0000E-02, 3.7000E-02, 3.3100E-02, 
            2.4000E-02, 8.4000E-03, 2.5000E-03, 2.2000E-04, 2.5000E-05, 
            7.1000E-07, 4.5000E-09} );

    subshell_half_profiles[16] = 
      std::vector<double>( {2.1300E-01, 2.1200E-01, 2.1200E-01, 2.1100E-01, 
            2.1000E-01, 2.0800E-01, 2.0400E-01, 2.0000E-01, 1.9400E-01, 
            1.8800E-01, 1.8100E-01, 1.6500E-01, 1.4800E-01, 1.3000E-01, 
            1.1300E-01, 9.6100E-02, 8.0800E-02, 5.5700E-02, 3.3200E-02, 
            2.3500E-02, 2.2900E-02, 1.8500E-02, 1.1800E-02, 6.6900E-03, 
            3.2000E-03, 2.0000E-03, 4.6000E-04, 2.6000E-04, 9.9000E-05, 
            1.0000E-05, 6.8000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3900E-01, 
            1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3900E-01, 1.3900E-01, 
            1.3900E-01, 1.3800E-01, 1.3700E-01, 1.3400E-01, 1.3100E-01, 
            1.2600E-01, 1.2100E-01, 1.1300E-01, 9.6800E-02, 6.9000E-02, 
            3.1600E-02, 1.4500E-02, 1.0900E-02, 1.0700E-02, 9.6700E-03, 
            5.2000E-03, 1.1000E-03, 9.0000E-04, 1.3000E-04, 6.3000E-05, 
            4.1000E-05, 6.9000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {1.5600E-01, 1.5600E-01, 1.5600E-01, 1.5600E-01, 
            1.5600E-01, 1.5600E-01, 1.5600E-01, 1.5600E-01, 1.5500E-01, 
            1.5500E-01, 1.5400E-01, 1.5200E-01, 1.4800E-01, 1.4200E-01, 
            1.3500E-01, 1.2600E-01, 1.1600E-01, 9.3300E-02, 5.9700E-02, 
            2.3600E-02, 1.2900E-02, 1.2000E-02, 1.1100E-02, 8.5700E-03, 
            3.4000E-03, 1.3000E-03, 7.1000E-04, 9.8000E-05, 8.5000E-05, 
            3.1000E-05, 2.6000E-06} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.3000E-01, 1.3000E-01, 1.3000E-01, 1.3000E-01, 
            1.3000E-01, 1.3000E-01, 1.3000E-01, 1.2900E-01, 1.2900E-01, 
            1.2900E-01, 1.2900E-01, 1.2900E-01, 1.2800E-01, 1.2700E-01, 
            1.2500E-01, 1.2200E-01, 1.1800E-01, 1.0600E-01, 8.2300E-02, 
            4.2500E-02, 1.7700E-02, 7.8400E-03, 5.6100E-03, 5.4700E-03, 
            4.5000E-03, 7.9000E-04, 3.9000E-04, 2.5000E-04, 8.0000E-05, 
            7.9000E-06, 2.2000E-07} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 
            1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 
            1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3200E-01, 1.3100E-01, 
            1.2800E-01, 1.2500E-01, 1.2000E-01, 1.0700E-01, 8.0900E-02, 
            3.9700E-02, 1.5800E-02, 7.2800E-03, 5.6900E-03, 5.6200E-03, 
            4.3000E-03, 6.9000E-04, 4.1000E-04, 2.3000E-04, 6.8000E-05, 
            5.7000E-06, 1.1000E-07} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.6000E-01, 1.6000E-01, 1.6000E-01, 1.6000E-01, 
            1.6000E-01, 1.6000E-01, 1.6000E-01, 1.6000E-01, 1.5900E-01, 
            1.5900E-01, 1.5900E-01, 1.5700E-01, 1.5300E-01, 1.4700E-01, 
            1.4000E-01, 1.3100E-01, 1.2100E-01, 1.0000E-01, 7.0600E-02, 
            3.4300E-02, 1.4600E-02, 5.9000E-03, 2.6800E-03, 1.7600E-03, 
            1.6000E-03, 9.0000E-04, 3.0000E-04, 3.0000E-05, 3.6000E-06, 
            1.1000E-07, 9.1000E-10} );

    subshell_half_profiles[22] = 
      std::vector<double>( {1.6900E-01, 1.6900E-01, 1.6900E-01, 1.6900E-01, 
            1.6900E-01, 1.6900E-01, 1.6900E-01, 1.6900E-01, 1.6900E-01, 
            1.6800E-01, 1.6700E-01, 1.6400E-01, 1.5800E-01, 1.5000E-01, 
            1.4100E-01, 1.3100E-01, 1.1900E-01, 9.7000E-02, 6.6600E-02, 
            3.1300E-02, 1.3100E-02, 5.2000E-03, 2.4000E-03, 1.6500E-03, 
            1.5000E-03, 8.3000E-04, 2.7000E-04, 2.6000E-05, 2.9000E-06, 
            8.2000E-08, 5.4000E-10} );

    subshell_half_profiles[23] = 
      std::vector<double>( {5.1500E-01, 5.1300E-01, 5.0800E-01, 4.9900E-01, 
            4.8800E-01, 4.5600E-01, 4.1500E-01, 3.6800E-01, 3.1800E-01, 
            2.6900E-01, 2.2200E-01, 1.4400E-01, 9.0800E-02, 6.0300E-02, 
            4.6400E-02, 4.1800E-02, 4.1200E-02, 3.9600E-02, 2.7500E-02, 
            8.7700E-03, 4.8700E-03, 4.6800E-03, 3.5300E-03, 2.0700E-03, 
            7.0000E-04, 4.3000E-04, 1.0000E-04, 5.2000E-05, 2.0000E-05, 
            2.0000E-06, 1.3000E-06} );

    subshell_half_profiles[24] = 
      std::vector<double>( {3.5100E-01, 3.5100E-01, 3.5100E-01, 3.5100E-01, 
            3.5100E-01, 3.4900E-01, 3.4500E-01, 3.3700E-01, 3.2500E-01, 
            3.0900E-01, 2.8800E-01, 2.3600E-01, 1.8000E-01, 1.2900E-01, 
            8.6800E-02, 5.6600E-02, 3.7000E-02, 2.0300E-02, 1.7500E-02, 
            1.3000E-02, 5.5700E-03, 2.3400E-03, 1.8200E-03, 1.7800E-03, 
            1.1000E-03, 1.9000E-04, 1.6000E-04, 2.4000E-05, 1.1000E-05, 
            7.1000E-06, 1.2000E-06} );

    subshell_half_profiles[25] = 
      std::vector<double>( {4.2700E-01, 4.2700E-01, 4.2700E-01, 4.2700E-01, 
            4.2600E-01, 4.2200E-01, 4.1200E-01, 3.9400E-01, 3.6900E-01, 
            3.3600E-01, 2.9900E-01, 2.1900E-01, 1.4600E-01, 9.0500E-02, 
            5.3900E-02, 3.2800E-02, 2.2400E-02, 1.7200E-02, 1.6300E-02, 
            8.2700E-03, 2.8200E-03, 1.7100E-03, 1.6700E-03, 1.4200E-03, 
            6.0000E-04, 1.8000E-04, 1.0000E-04, 1.4000E-05, 1.2000E-05, 
            4.4000E-06, 3.6000E-07} );

    subshell_half_profiles[26] = 
      std::vector<double>( {1.9300E+00, 1.8600E+00, 1.6600E+00, 1.3800E+00, 
            1.0700E+00, 5.3000E-01, 2.2000E-01, 9.4800E-02, 6.0900E-02, 
            5.6800E-02, 5.6100E-02, 4.4500E-02, 2.7500E-02, 1.4700E-02, 
            7.5100E-03, 4.3400E-03, 3.2800E-03, 3.0600E-03, 2.4100E-03, 
            7.7000E-04, 3.4300E-04, 3.2700E-04, 2.5500E-04, 1.5200E-04, 
            5.0000E-05, 3.0000E-05, 6.9000E-06, 3.6000E-06, 1.4000E-06, 
            1.3000E-07, 9.1000E-08} );
  }
};

//! The default Compton profile generator implementation for A=98
template<>
struct DefaultComptonProfileGeneratorImpl<98u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 27 );

    subshell_half_profiles[0] = 
      std::vector<double>( {6.7000E-03, 6.7000E-03, 6.7000E-03, 6.7000E-03, 
            6.7000E-03, 6.7000E-03, 6.7000E-03, 6.7000E-03, 6.7000E-03, 
            6.7000E-03, 6.6900E-03, 6.6900E-03, 6.6900E-03, 6.6900E-03, 
            6.6900E-03, 6.6900E-03, 6.6900E-03, 6.6900E-03, 6.6800E-03, 
            6.6700E-03, 6.6600E-03, 6.6400E-03, 6.6200E-03, 6.6000E-03, 
            6.5000E-03, 6.4000E-03, 6.1000E-03, 5.5000E-03, 4.8000E-03, 
            3.4000E-03, 1.5000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.4200E-02, 2.4200E-02, 2.4200E-02, 2.4200E-02, 
            2.4200E-02, 2.4200E-02, 2.4200E-02, 2.4200E-02, 2.4200E-02, 
            2.4200E-02, 2.4200E-02, 2.4100E-02, 2.4100E-02, 2.4100E-02, 
            2.4000E-02, 2.4000E-02, 2.4000E-02, 2.3900E-02, 2.3700E-02, 
            2.3300E-02, 2.2700E-02, 2.2100E-02, 2.1400E-02, 2.0700E-02, 
            1.9000E-02, 1.4000E-02, 9.5000E-03, 3.4000E-03, 1.1000E-03, 
            5.7000E-04, 3.8000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 
            1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 
            1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 
            1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 
            1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 1.1500E-02, 
            1.1000E-02, 1.1000E-02, 1.0000E-02, 7.9000E-03, 5.4000E-03, 
            2.1000E-03, 3.4000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.4100E-02, 1.4100E-02, 1.4100E-02, 1.4100E-02, 
            1.4100E-02, 1.4100E-02, 1.4100E-02, 1.4100E-02, 1.4100E-02, 
            1.4100E-02, 1.4100E-02, 1.4100E-02, 1.4100E-02, 1.4100E-02, 
            1.4100E-02, 1.4100E-02, 1.4100E-02, 1.4100E-02, 1.4100E-02, 
            1.4100E-02, 1.4100E-02, 1.4100E-02, 1.4100E-02, 1.4000E-02, 
            1.4000E-02, 1.3000E-02, 1.2000E-02, 7.8000E-03, 4.5000E-03, 
            1.2000E-03, 1.1000E-04} );

    subshell_half_profiles[4] = 
      std::vector<double>( {5.3100E-02, 5.3100E-02, 5.3100E-02, 5.3100E-02, 
            5.3100E-02, 5.3000E-02, 5.3000E-02, 5.2900E-02, 5.2800E-02, 
            5.2700E-02, 5.2600E-02, 5.2400E-02, 5.2000E-02, 5.1700E-02, 
            5.1200E-02, 5.0800E-02, 5.0200E-02, 4.9000E-02, 4.6900E-02, 
            4.2600E-02, 3.7700E-02, 3.2500E-02, 2.7400E-02, 2.2500E-02, 
            1.4000E-02, 5.1000E-03, 4.1000E-03, 2.8000E-03, 9.3000E-04, 
            1.3000E-04, 9.5000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.0800E-02, 3.0800E-02, 3.0800E-02, 3.0800E-02, 
            3.0800E-02, 3.0800E-02, 3.0800E-02, 3.0800E-02, 3.0800E-02, 
            3.0800E-02, 3.0800E-02, 3.0800E-02, 3.0800E-02, 3.0800E-02, 
            3.0800E-02, 3.0800E-02, 3.0800E-02, 3.0800E-02, 3.0700E-02, 
            3.0500E-02, 3.0100E-02, 2.9400E-02, 2.8500E-02, 2.7200E-02, 
            2.4000E-02, 1.3000E-02, 5.6000E-03, 1.2000E-03, 1.1000E-03, 
            6.2000E-04, 1.0000E-04} );

    subshell_half_profiles[6] = 
      std::vector<double>( {3.5000E-02, 3.5000E-02, 3.5000E-02, 3.5000E-02, 
            3.5000E-02, 3.5000E-02, 3.5000E-02, 3.5000E-02, 3.5000E-02, 
            3.5000E-02, 3.5000E-02, 3.5000E-02, 3.5000E-02, 3.5000E-02, 
            3.5000E-02, 3.5000E-02, 3.5000E-02, 3.4900E-02, 3.4800E-02, 
            3.4400E-02, 3.3700E-02, 3.2600E-02, 3.1000E-02, 2.9000E-02, 
            2.4000E-02, 1.1000E-02, 3.7000E-03, 1.5000E-03, 1.3000E-03, 
            4.5000E-04, 3.8000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.2400E-02, 2.2400E-02, 2.2400E-02, 2.2400E-02, 
            2.2400E-02, 2.2400E-02, 2.2400E-02, 2.2400E-02, 2.2400E-02, 
            2.2400E-02, 2.2400E-02, 2.2400E-02, 2.2400E-02, 2.2400E-02, 
            2.2400E-02, 2.2400E-02, 2.2400E-02, 2.2400E-02, 2.2400E-02, 
            2.2400E-02, 2.2400E-02, 2.2300E-02, 2.2200E-02, 2.2000E-02, 
            2.1000E-02, 1.7000E-02, 1.2000E-02, 4.0000E-03, 1.2000E-03, 
            1.1000E-04, 3.3000E-06} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 
            2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 
            2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 
            2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 2.3300E-02, 
            2.3300E-02, 2.3300E-02, 2.3200E-02, 2.3100E-02, 2.2800E-02, 
            2.2000E-02, 1.7000E-02, 1.2000E-02, 3.5000E-03, 9.5000E-04, 
            8.1000E-05, 1.7000E-06} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.0400E-01, 1.0300E-01, 1.0300E-01, 1.0300E-01, 
            1.0300E-01, 1.0300E-01, 1.0300E-01, 1.0200E-01, 1.0100E-01, 
            1.0100E-01, 9.9700E-02, 9.7600E-02, 9.5100E-02, 9.2300E-02, 
            8.9100E-02, 8.5600E-02, 8.1900E-02, 7.4000E-02, 6.1500E-02, 
            4.1900E-02, 2.6800E-02, 1.7400E-02, 1.2900E-02, 1.1400E-02, 
            1.1000E-02, 5.2000E-03, 1.4000E-03, 9.8000E-04, 3.7000E-04, 
            3.9000E-05, 2.6000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {6.4800E-02, 6.4800E-02, 6.4800E-02, 6.4800E-02, 
            6.4800E-02, 6.4800E-02, 6.4800E-02, 6.4800E-02, 6.4800E-02, 
            6.4800E-02, 6.4800E-02, 6.4700E-02, 6.4700E-02, 6.4600E-02, 
            6.4400E-02, 6.4200E-02, 6.3900E-02, 6.3100E-02, 6.1100E-02, 
            5.5400E-02, 4.6900E-02, 3.7000E-02, 2.7200E-02, 1.8900E-02, 
            8.6000E-03, 4.7000E-03, 3.3000E-03, 5.0000E-04, 2.6000E-04, 
            1.7000E-04, 3.0000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {7.2500E-02, 7.2500E-02, 7.2500E-02, 7.2500E-02, 
            7.2500E-02, 7.2500E-02, 7.2500E-02, 7.2500E-02, 7.2500E-02, 
            7.2500E-02, 7.2500E-02, 7.2400E-02, 7.2300E-02, 7.2100E-02, 
            7.1900E-02, 7.1500E-02, 7.1000E-02, 6.9700E-02, 6.6400E-02, 
            5.7500E-02, 4.5600E-02, 3.3100E-02, 2.2200E-02, 1.4300E-02, 
            6.8000E-03, 5.2000E-03, 2.5000E-03, 4.0000E-04, 3.6000E-04, 
            1.3000E-04, 1.1000E-05} );

    subshell_half_profiles[12] = 
      std::vector<double>( {5.3100E-02, 5.3100E-02, 5.3100E-02, 5.3100E-02, 
            5.3100E-02, 5.3100E-02, 5.3100E-02, 5.3100E-02, 5.3100E-02, 
            5.3100E-02, 5.3100E-02, 5.3100E-02, 5.3100E-02, 5.3100E-02, 
            5.3100E-02, 5.3100E-02, 5.3100E-02, 5.3000E-02, 5.2700E-02, 
            5.1200E-02, 4.8000E-02, 4.2800E-02, 3.6100E-02, 2.8800E-02, 
            1.6000E-02, 2.9000E-03, 2.2000E-03, 1.2000E-03, 4.0000E-04, 
            4.0000E-05, 1.1000E-06} );

    subshell_half_profiles[13] = 
      std::vector<double>( {5.4800E-02, 5.4800E-02, 5.4800E-02, 5.4800E-02, 
            5.4800E-02, 5.4800E-02, 5.4800E-02, 5.4800E-02, 5.4800E-02, 
            5.4800E-02, 5.4800E-02, 5.4800E-02, 5.4800E-02, 5.4800E-02, 
            5.4800E-02, 5.4800E-02, 5.4800E-02, 5.4700E-02, 5.4300E-02, 
            5.2500E-02, 4.8800E-02, 4.3000E-02, 3.5600E-02, 2.7800E-02, 
            1.5000E-02, 2.8000E-03, 2.3000E-03, 1.1000E-03, 3.4000E-04, 
            2.9000E-05, 6.0000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 
            4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 
            4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 
            4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1900E-02, 4.1800E-02, 
            4.1600E-02, 4.0800E-02, 3.9100E-02, 3.6500E-02, 3.3100E-02, 
            2.5000E-02, 9.2000E-03, 2.8000E-03, 2.7000E-04, 3.3000E-05, 
            1.1000E-06, 8.3000E-09} );

    subshell_half_profiles[15] = 
      std::vector<double>( {4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 
            4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 
            4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 
            4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2600E-02, 4.2500E-02, 
            4.2200E-02, 4.1300E-02, 3.9600E-02, 3.6800E-02, 3.3200E-02, 
            2.5000E-02, 8.8000E-03, 2.6000E-03, 2.4000E-04, 2.8000E-05, 
            8.1000E-07, 5.1000E-09} );

    subshell_half_profiles[16] = 
      std::vector<double>( {2.0800E-01, 2.0800E-01, 2.0700E-01, 2.0700E-01, 
            2.0600E-01, 2.0300E-01, 2.0000E-01, 1.9600E-01, 1.9100E-01, 
            1.8500E-01, 1.7800E-01, 1.6300E-01, 1.4700E-01, 1.3000E-01, 
            1.1300E-01, 9.6800E-02, 8.1900E-02, 5.7100E-02, 3.4100E-02, 
            2.3300E-02, 2.2700E-02, 1.8900E-02, 1.2500E-02, 7.2000E-03, 
            3.2000E-03, 2.1000E-03, 5.0000E-04, 2.7000E-04, 1.1000E-04, 
            1.0000E-05, 6.9000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.3600E-01, 1.3600E-01, 1.3600E-01, 1.3600E-01, 
            1.3600E-01, 1.3600E-01, 1.3600E-01, 1.3600E-01, 1.3600E-01, 
            1.3600E-01, 1.3500E-01, 1.3400E-01, 1.3200E-01, 1.2900E-01, 
            1.2400E-01, 1.1900E-01, 1.1200E-01, 9.6800E-02, 7.0300E-02, 
            3.3200E-02, 1.5200E-02, 1.0800E-02, 1.0600E-02, 9.8100E-03, 
            5.5000E-03, 1.1000E-03, 9.3000E-04, 1.5000E-04, 6.3000E-05, 
            4.3000E-05, 7.5000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5300E-01, 
            1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5300E-01, 1.5200E-01, 
            1.5200E-01, 1.5100E-01, 1.4900E-01, 1.4600E-01, 1.4000E-01, 
            1.3400E-01, 1.2500E-01, 1.1600E-01, 9.4000E-02, 6.1300E-02, 
            2.4700E-02, 1.3000E-02, 1.1900E-02, 1.1200E-02, 8.8700E-03, 
            3.6000E-03, 1.3000E-03, 7.5000E-04, 1.0000E-04, 8.6000E-05, 
            3.3000E-05, 2.8000E-06} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.2700E-01, 1.2700E-01, 1.2700E-01, 1.2700E-01, 
            1.2700E-01, 1.2700E-01, 1.2700E-01, 1.2700E-01, 1.2700E-01, 
            1.2700E-01, 1.2600E-01, 1.2600E-01, 1.2600E-01, 1.2400E-01, 
            1.2300E-01, 1.2000E-01, 1.1600E-01, 1.0500E-01, 8.3100E-02, 
            4.4400E-02, 1.9100E-02, 8.3700E-03, 5.6800E-03, 5.4600E-03, 
            4.6000E-03, 8.6000E-04, 4.0000E-04, 2.6000E-04, 8.7000E-05, 
            8.8000E-06, 2.4000E-07} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.3100E-01, 1.3100E-01, 1.3100E-01, 1.3100E-01, 
            1.3100E-01, 1.3100E-01, 1.3100E-01, 1.3100E-01, 1.3100E-01, 
            1.3100E-01, 1.3100E-01, 1.3000E-01, 1.3000E-01, 1.2800E-01, 
            1.2600E-01, 1.2300E-01, 1.1800E-01, 1.0600E-01, 8.1800E-02, 
            4.1500E-02, 1.7000E-02, 7.6600E-03, 5.7000E-03, 5.6000E-03, 
            4.4000E-03, 7.5000E-04, 4.1000E-04, 2.4000E-04, 7.3000E-05, 
            6.3000E-06, 1.3000E-07} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.5400E-01, 1.5400E-01, 1.5400E-01, 1.5400E-01, 
            1.5400E-01, 1.5400E-01, 1.5400E-01, 1.5400E-01, 1.5400E-01, 
            1.5300E-01, 1.5300E-01, 1.5100E-01, 1.4800E-01, 1.4300E-01, 
            1.3700E-01, 1.2900E-01, 1.2000E-01, 1.0100E-01, 7.2900E-02, 
            3.6800E-02, 1.6300E-02, 6.7500E-03, 3.0200E-03, 1.8700E-03, 
            1.6000E-03, 9.7000E-04, 3.4000E-04, 3.4000E-05, 4.2000E-06, 
            1.3000E-07, 1.1000E-09} );

    subshell_half_profiles[22] = 
      std::vector<double>( {1.6200E-01, 1.6200E-01, 1.6200E-01, 1.6200E-01, 
            1.6200E-01, 1.6200E-01, 1.6200E-01, 1.6200E-01, 1.6200E-01, 
            1.6200E-01, 1.6100E-01, 1.5800E-01, 1.5400E-01, 1.4700E-01, 
            1.3900E-01, 1.3000E-01, 1.1900E-01, 9.8600E-02, 6.9400E-02, 
            3.3900E-02, 1.4600E-02, 5.9700E-03, 2.7100E-03, 1.7500E-03, 
            1.6000E-03, 9.0000E-04, 3.0000E-04, 2.9000E-05, 3.4000E-06, 
            9.8000E-08, 6.5000E-10} );

    subshell_half_profiles[23] = 
      std::vector<double>( {5.0500E-01, 5.0300E-01, 4.9800E-01, 4.9000E-01, 
            4.7900E-01, 4.4900E-01, 4.1000E-01, 3.6500E-01, 3.1700E-01, 
            2.7000E-01, 2.2500E-01, 1.4800E-01, 9.3900E-02, 6.2100E-02, 
            4.6800E-02, 4.1400E-02, 4.0400E-02, 3.9200E-02, 2.8400E-02, 
            9.4600E-03, 4.8700E-03, 4.6800E-03, 3.6900E-03, 2.2500E-03, 
            7.4000E-04, 4.6000E-04, 1.1000E-04, 5.3000E-05, 2.2000E-05, 
            2.1000E-06, 1.4000E-06} );

    subshell_half_profiles[24] = 
      std::vector<double>( {3.4400E-01, 3.4400E-01, 3.4400E-01, 3.4400E-01, 
            3.4400E-01, 3.4200E-01, 3.3800E-01, 3.3100E-01, 3.2000E-01, 
            3.0500E-01, 2.8500E-01, 2.3700E-01, 1.8300E-01, 1.3300E-01, 
            9.1000E-02, 6.0000E-02, 3.9400E-02, 2.0800E-02, 1.7000E-02, 
            1.3400E-02, 6.0500E-03, 2.5000E-03, 1.8100E-03, 1.7700E-03, 
            1.2000E-03, 1.9000E-04, 1.6000E-04, 2.7000E-05, 1.1000E-05, 
            7.4000E-06, 1.3000E-06} );

    subshell_half_profiles[25] = 
      std::vector<double>( {4.2100E-01, 4.2100E-01, 4.2100E-01, 4.2100E-01, 
            4.2000E-01, 4.1600E-01, 4.0600E-01, 3.9000E-01, 3.6600E-01, 
            3.3500E-01, 2.9900E-01, 2.2100E-01, 1.5000E-01, 9.4000E-02, 
            5.6500E-02, 3.4400E-02, 2.3100E-02, 1.6900E-02, 1.6200E-02, 
            8.6700E-03, 3.0200E-03, 1.7100E-03, 1.6500E-03, 1.4400E-03, 
            6.4000E-04, 1.8000E-04, 1.1000E-04, 1.4000E-05, 1.2000E-05, 
            4.6000E-06, 3.9000E-07} );

    subshell_half_profiles[26] = 
      std::vector<double>( {1.9100E+00, 1.8400E+00, 1.6500E+00, 1.3700E+00, 
            1.0700E+00, 5.4000E-01, 2.2800E-01, 9.7200E-02, 6.0100E-02, 
            5.4900E-02, 5.4500E-02, 4.4300E-02, 2.8100E-02, 1.5400E-02, 
            7.9400E-03, 4.4900E-03, 3.2400E-03, 2.9300E-03, 2.4100E-03, 
            8.1900E-04, 3.3900E-04, 3.1800E-04, 2.5900E-04, 1.6100E-04, 
            5.2000E-05, 3.1000E-05, 7.4000E-06, 3.6000E-06, 1.4000E-06, 
            1.4000E-07, 9.1000E-08} );
  }
};

//! The default Compton profile generator implementation for A=99
template<>
struct DefaultComptonProfileGeneratorImpl<99u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 27 );

    subshell_half_profiles[0] = 
      std::vector<double>( {6.5800E-03, 6.5800E-03, 6.5800E-03, 6.5800E-03, 
            6.5800E-03, 6.5800E-03, 6.5800E-03, 6.5800E-03, 6.5800E-03, 
            6.5800E-03, 6.5800E-03, 6.5800E-03, 6.5800E-03, 6.5800E-03, 
            6.5800E-03, 6.5800E-03, 6.5700E-03, 6.5700E-03, 6.5700E-03, 
            6.5600E-03, 6.5400E-03, 6.5300E-03, 6.5100E-03, 6.4900E-03, 
            6.4000E-03, 6.3000E-03, 6.0000E-03, 5.4000E-03, 4.7000E-03, 
            3.4000E-03, 1.5000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.3800E-02, 2.3800E-02, 2.3800E-02, 2.3800E-02, 
            2.3800E-02, 2.3800E-02, 2.3800E-02, 2.3800E-02, 2.3800E-02, 
            2.3800E-02, 2.3800E-02, 2.3800E-02, 2.3700E-02, 2.3700E-02, 
            2.3700E-02, 2.3600E-02, 2.3600E-02, 2.3500E-02, 2.3300E-02, 
            2.2900E-02, 2.2400E-02, 2.1800E-02, 2.1200E-02, 2.0400E-02, 
            1.9000E-02, 1.4000E-02, 9.6000E-03, 3.5000E-03, 1.2000E-03, 
            5.6000E-04, 3.8000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 
            1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 
            1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 
            1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 
            1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 1.1300E-02, 
            1.1000E-02, 1.1000E-02, 1.0000E-02, 7.9000E-03, 5.4000E-03, 
            2.2000E-03, 3.6000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 
            1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 
            1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 
            1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 1.4000E-02, 
            1.4000E-02, 1.4000E-02, 1.3900E-02, 1.3900E-02, 1.3900E-02, 
            1.3900E-02, 1.3000E-02, 1.2000E-02, 7.9000E-03, 4.5000E-03, 
            1.3000E-03, 1.1000E-04} );

    subshell_half_profiles[4] = 
      std::vector<double>( {5.2300E-02, 5.2300E-02, 5.2300E-02, 5.2200E-02, 
            5.2200E-02, 5.2200E-02, 5.2200E-02, 5.2100E-02, 5.2000E-02, 
            5.1900E-02, 5.1800E-02, 5.1600E-02, 5.1300E-02, 5.0900E-02, 
            5.0500E-02, 5.0000E-02, 4.9500E-02, 4.8400E-02, 4.6300E-02, 
            4.2200E-02, 3.7500E-02, 3.2500E-02, 2.7500E-02, 2.2700E-02, 
            1.5000E-02, 5.2000E-03, 4.0000E-03, 2.8000E-03, 9.9000E-04, 
            1.3000E-04, 9.6000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {3.0300E-02, 3.0300E-02, 3.0300E-02, 3.0300E-02, 
            3.0300E-02, 3.0300E-02, 3.0300E-02, 3.0300E-02, 3.0300E-02, 
            3.0300E-02, 3.0300E-02, 3.0300E-02, 3.0300E-02, 3.0300E-02, 
            3.0300E-02, 3.0300E-02, 3.0300E-02, 3.0300E-02, 3.0200E-02, 
            3.0000E-02, 2.9600E-02, 2.9000E-02, 2.8100E-02, 2.7000E-02, 
            2.4000E-02, 1.4000E-02, 5.9000E-03, 1.2000E-03, 1.1000E-03, 
            6.3000E-04, 1.1000E-04} );

    subshell_half_profiles[6] = 
      std::vector<double>( {3.4600E-02, 3.4600E-02, 3.4600E-02, 3.4600E-02, 
            3.4600E-02, 3.4600E-02, 3.4600E-02, 3.4600E-02, 3.4600E-02, 
            3.4600E-02, 3.4600E-02, 3.4600E-02, 3.4600E-02, 3.4600E-02, 
            3.4600E-02, 3.4500E-02, 3.4500E-02, 3.4500E-02, 3.4400E-02, 
            3.4000E-02, 3.3300E-02, 3.2300E-02, 3.0800E-02, 2.8800E-02, 
            2.4000E-02, 1.1000E-02, 3.9000E-03, 1.5000E-03, 1.3000E-03, 
            4.6000E-04, 4.0000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.2100E-02, 2.2100E-02, 2.2100E-02, 2.2100E-02, 
            2.2100E-02, 2.2100E-02, 2.2100E-02, 2.2100E-02, 2.2100E-02, 
            2.2100E-02, 2.2100E-02, 2.2100E-02, 2.2100E-02, 2.2100E-02, 
            2.2100E-02, 2.2100E-02, 2.2100E-02, 2.2100E-02, 2.2100E-02, 
            2.2100E-02, 2.2100E-02, 2.2000E-02, 2.1900E-02, 2.1800E-02, 
            2.1000E-02, 1.7000E-02, 1.2000E-02, 4.1000E-03, 1.2000E-03, 
            1.2000E-04, 3.6000E-06} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 
            2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 
            2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 
            2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 2.3000E-02, 
            2.3000E-02, 2.3000E-02, 2.2900E-02, 2.2800E-02, 2.2600E-02, 
            2.2000E-02, 1.7000E-02, 1.2000E-02, 3.7000E-03, 1.0000E-03, 
            8.7000E-05, 1.9000E-06} );

    subshell_half_profiles[9] = 
      std::vector<double>( {1.0200E-01, 1.0200E-01, 1.0200E-01, 1.0200E-01, 
            1.0100E-01, 1.0100E-01, 1.0100E-01, 1.0000E-01, 9.9600E-02, 
            9.8900E-02, 9.8100E-02, 9.6100E-02, 9.3700E-02, 9.1000E-02, 
            8.8000E-02, 8.4600E-02, 8.1100E-02, 7.3500E-02, 6.1400E-02, 
            4.2300E-02, 2.7300E-02, 1.7800E-02, 1.3000E-02, 1.1300E-02, 
            1.1000E-02, 5.4000E-03, 1.5000E-03, 9.9000E-04, 4.0000E-04, 
            4.0000E-05, 2.7000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {6.3600E-02, 6.3600E-02, 6.3600E-02, 6.3600E-02, 
            6.3600E-02, 6.3600E-02, 6.3600E-02, 6.3600E-02, 6.3600E-02, 
            6.3600E-02, 6.3600E-02, 6.3600E-02, 6.3500E-02, 6.3400E-02, 
            6.3300E-02, 6.3100E-02, 6.2900E-02, 6.2100E-02, 6.0200E-02, 
            5.4900E-02, 4.6900E-02, 3.7300E-02, 2.7800E-02, 1.9600E-02, 
            9.0000E-03, 4.6000E-03, 3.4000E-03, 5.3000E-04, 2.6000E-04, 
            1.8000E-04, 3.2000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {7.1400E-02, 7.1400E-02, 7.1400E-02, 7.1400E-02, 
            7.1400E-02, 7.1400E-02, 7.1400E-02, 7.1400E-02, 7.1400E-02, 
            7.1400E-02, 7.1400E-02, 7.1300E-02, 7.1200E-02, 7.1000E-02, 
            7.0800E-02, 7.0500E-02, 7.0000E-02, 6.8800E-02, 6.5700E-02, 
            5.7300E-02, 4.5900E-02, 3.3600E-02, 2.2900E-02, 1.4800E-02, 
            6.9000E-03, 5.2000E-03, 2.6000E-03, 4.1000E-04, 3.6000E-04, 
            1.4000E-04, 1.2000E-05} );

    subshell_half_profiles[12] = 
      std::vector<double>( {5.2300E-02, 5.2300E-02, 5.2300E-02, 5.2300E-02, 
            5.2300E-02, 5.2300E-02, 5.2300E-02, 5.2300E-02, 5.2300E-02, 
            5.2300E-02, 5.2300E-02, 5.2300E-02, 5.2300E-02, 5.2300E-02, 
            5.2300E-02, 5.2300E-02, 5.2200E-02, 5.2200E-02, 5.1900E-02, 
            5.0500E-02, 4.7500E-02, 4.2700E-02, 3.6300E-02, 2.9200E-02, 
            1.6000E-02, 3.0000E-03, 2.2000E-03, 1.3000E-03, 4.2000E-04, 
            4.4000E-05, 1.2000E-06} );

    subshell_half_profiles[13] = 
      std::vector<double>( {5.4000E-02, 5.4000E-02, 5.4000E-02, 5.4000E-02, 
            5.4000E-02, 5.4000E-02, 5.4000E-02, 5.4000E-02, 5.4000E-02, 
            5.4000E-02, 5.4000E-02, 5.4000E-02, 5.4000E-02, 5.4000E-02, 
            5.4000E-02, 5.3900E-02, 5.3900E-02, 5.3800E-02, 5.3500E-02, 
            5.1900E-02, 4.8400E-02, 4.2900E-02, 3.5900E-02, 2.8300E-02, 
            1.5000E-02, 2.8000E-03, 2.3000E-03, 1.2000E-03, 3.6000E-04, 
            3.1000E-05, 6.6000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 
            4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 
            4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 
            4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 
            4.0900E-02, 4.0100E-02, 3.8700E-02, 3.6300E-02, 3.3100E-02, 
            2.5000E-02, 9.6000E-03, 3.0000E-03, 3.0000E-04, 3.7000E-05, 
            1.2000E-06, 9.5000E-09} );

    subshell_half_profiles[15] = 
      std::vector<double>( {4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1800E-02, 
            4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1800E-02, 
            4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1800E-02, 
            4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1800E-02, 4.1800E-02, 
            4.1500E-02, 4.0700E-02, 3.9100E-02, 3.6500E-02, 3.3200E-02, 
            2.5000E-02, 9.2000E-03, 2.8000E-03, 2.7000E-04, 3.1000E-05, 
            9.1000E-07, 5.8000E-09} );

    subshell_half_profiles[16] = 
      std::vector<double>( {2.0400E-01, 2.0300E-01, 2.0300E-01, 2.0200E-01, 
            2.0200E-01, 1.9900E-01, 1.9600E-01, 1.9200E-01, 1.8700E-01, 
            1.8200E-01, 1.7500E-01, 1.6100E-01, 1.4600E-01, 1.3000E-01, 
            1.1300E-01, 9.7500E-02, 8.2900E-02, 5.8400E-02, 3.4900E-02, 
            2.3100E-02, 2.2500E-02, 1.9200E-02, 1.3100E-02, 7.7300E-03, 
            3.3000E-03, 2.2000E-03, 5.5000E-04, 2.7000E-04, 1.2000E-04, 
            1.1000E-05, 7.1000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 
            1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 1.3300E-01, 
            1.3300E-01, 1.3200E-01, 1.3100E-01, 1.2900E-01, 1.2600E-01, 
            1.2200E-01, 1.1700E-01, 1.1100E-01, 9.6800E-02, 7.1500E-02, 
            3.4800E-02, 1.6000E-02, 1.0900E-02, 1.0500E-02, 9.9100E-03, 
            5.9000E-03, 1.1000E-03, 9.6000E-04, 1.6000E-04, 6.3000E-05, 
            4.4000E-05, 8.1000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {1.5000E-01, 1.5000E-01, 1.5000E-01, 1.5000E-01, 
            1.5000E-01, 1.5000E-01, 1.5000E-01, 1.5000E-01, 1.5000E-01, 
            1.4900E-01, 1.4900E-01, 1.4700E-01, 1.4300E-01, 1.3900E-01, 
            1.3200E-01, 1.2400E-01, 1.1500E-01, 9.4500E-02, 6.2700E-02, 
            2.5900E-02, 1.3200E-02, 1.1800E-02, 1.1300E-02, 9.1500E-03, 
            3.9000E-03, 1.3000E-03, 7.9000E-04, 1.0000E-04, 8.7000E-05, 
            3.5000E-05, 3.0000E-06} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.2400E-01, 1.2400E-01, 1.2400E-01, 1.2400E-01, 
            1.2400E-01, 1.2400E-01, 1.2400E-01, 1.2400E-01, 1.2400E-01, 
            1.2400E-01, 1.2400E-01, 1.2400E-01, 1.2300E-01, 1.2200E-01, 
            1.2000E-01, 1.1800E-01, 1.1400E-01, 1.0400E-01, 8.3800E-02, 
            4.6200E-02, 2.0400E-02, 8.9400E-03, 5.7700E-03, 5.4400E-03, 
            4.7000E-03, 9.4000E-04, 4.0000E-04, 2.7000E-04, 9.3000E-05, 
            9.6000E-06, 2.7000E-07} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.2800E-01, 1.2800E-01, 1.2800E-01, 1.2800E-01, 
            1.2800E-01, 1.2800E-01, 1.2800E-01, 1.2800E-01, 1.2800E-01, 
            1.2800E-01, 1.2800E-01, 1.2800E-01, 1.2700E-01, 1.2600E-01, 
            1.2400E-01, 1.2100E-01, 1.1700E-01, 1.0600E-01, 8.2600E-02, 
            4.3200E-02, 1.8200E-02, 8.0900E-03, 5.7300E-03, 5.5800E-03, 
            4.6000E-03, 8.1000E-04, 4.2000E-04, 2.5000E-04, 7.8000E-05, 
            6.9000E-06, 1.4000E-07} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.4900E-01, 1.4900E-01, 1.4900E-01, 1.4900E-01, 
            1.4900E-01, 1.4900E-01, 1.4900E-01, 1.4900E-01, 1.4900E-01, 
            1.4800E-01, 1.4800E-01, 1.4700E-01, 1.4400E-01, 1.4000E-01, 
            1.3400E-01, 1.2700E-01, 1.1900E-01, 1.0200E-01, 7.4900E-02, 
            3.9100E-02, 1.7900E-02, 7.6300E-03, 3.4000E-03, 2.0000E-03, 
            1.7000E-03, 1.0000E-03, 3.7000E-04, 3.9000E-05, 4.9000E-06, 
            1.6000E-07, 1.3000E-09} );

    subshell_half_profiles[22] = 
      std::vector<double>( {1.5600E-01, 1.5600E-01, 1.5600E-01, 1.5600E-01, 
            1.5600E-01, 1.5600E-01, 1.5600E-01, 1.5600E-01, 1.5600E-01, 
            1.5600E-01, 1.5500E-01, 1.5300E-01, 1.4900E-01, 1.4400E-01, 
            1.3700E-01, 1.2800E-01, 1.1900E-01, 9.9700E-02, 7.1700E-02, 
            3.6300E-02, 1.6200E-02, 6.7900E-03, 3.0500E-03, 1.8700E-03, 
            1.6000E-03, 9.7000E-04, 3.4000E-04, 3.4000E-05, 4.0000E-06, 
            1.2000E-07, 7.7000E-10} );

    subshell_half_profiles[23] = 
      std::vector<double>( {4.9500E-01, 4.9300E-01, 4.8800E-01, 4.8100E-01, 
            4.7000E-01, 4.4200E-01, 4.0500E-01, 3.6200E-01, 3.1700E-01, 
            2.7100E-01, 2.2700E-01, 1.5100E-01, 9.7000E-02, 6.4000E-02, 
            4.7400E-02, 4.1000E-02, 3.9600E-02, 3.8800E-02, 2.9200E-02, 
            1.0200E-02, 4.8900E-03, 4.6600E-03, 3.8300E-03, 2.4300E-03, 
            7.9000E-04, 4.8000E-04, 1.2000E-04, 5.4000E-05, 2.3000E-05, 
            2.2000E-06, 1.4000E-06} );

    subshell_half_profiles[24] = 
      std::vector<double>( {3.3700E-01, 3.3700E-01, 3.3700E-01, 3.3700E-01, 
            3.3700E-01, 3.3600E-01, 3.3200E-01, 3.2600E-01, 3.1500E-01, 
            3.0100E-01, 2.8300E-01, 2.3700E-01, 1.8600E-01, 1.3700E-01, 
            9.4900E-02, 6.3500E-02, 4.1900E-02, 2.1400E-02, 1.6700E-02, 
            1.3600E-02, 6.5300E-03, 2.6800E-03, 1.8000E-03, 1.7600E-03, 
            1.2000E-03, 2.0000E-04, 1.7000E-04, 3.0000E-05, 1.1000E-05, 
            7.6000E-06, 1.4000E-06} );

    subshell_half_profiles[25] = 
      std::vector<double>( {4.1500E-01, 4.1500E-01, 4.1500E-01, 4.1500E-01, 
            4.1400E-01, 4.1000E-01, 4.0200E-01, 3.8600E-01, 3.6300E-01, 
            3.3300E-01, 2.9900E-01, 2.2300E-01, 1.5300E-01, 9.7400E-02, 
            5.9200E-02, 3.6000E-02, 2.3800E-02, 1.6600E-02, 1.5900E-02, 
            9.0200E-03, 3.2200E-03, 1.7200E-03, 1.6300E-03, 1.4600E-03, 
            6.9000E-04, 1.8000E-04, 1.1000E-04, 1.5000E-05, 1.2000E-05, 
            4.9000E-06, 4.2000E-07} );

    subshell_half_profiles[26] = 
      std::vector<double>( {1.8900E+00, 1.8200E+00, 1.6400E+00, 1.3700E+00, 
            1.0700E+00, 5.4900E-01, 2.3500E-01, 9.9900E-02, 5.9600E-02, 
            5.3200E-02, 5.2900E-02, 4.4000E-02, 2.8700E-02, 1.6000E-02, 
            8.3800E-03, 4.6700E-03, 3.2300E-03, 2.8100E-03, 2.4000E-03, 
            8.7000E-04, 3.3900E-04, 3.0800E-04, 2.6200E-04, 1.7000E-04, 
            5.4000E-05, 3.2000E-05, 8.0000E-06, 3.5000E-06, 1.5000E-06, 
            1.4000E-07, 9.1000E-08} );
  }
};

//! The default Compton profile generator implementation for A=100
template<>
struct DefaultComptonProfileGeneratorImpl<100u> : public DefaultComptonProfileGenerator
{
  //! Generate the compton profiles for each subshell
  void generateHalfProfilesOnly( std::vector<std::vector<double> >&
                                 subshell_half_profiles ) const final override
{
    subshell_half_profiles.resize( 27 );

    subshell_half_profiles[0] = 
      std::vector<double>( {6.4600E-03, 6.4600E-03, 6.4600E-03, 6.4600E-03, 
            6.4600E-03, 6.4600E-03, 6.4600E-03, 6.4600E-03, 6.4600E-03, 
            6.4600E-03, 6.4600E-03, 6.4600E-03, 6.4600E-03, 6.4600E-03, 
            6.4600E-03, 6.4600E-03, 6.4600E-03, 6.4600E-03, 6.4500E-03, 
            6.4400E-03, 6.4300E-03, 6.4200E-03, 6.4000E-03, 6.3800E-03, 
            6.3000E-03, 6.2000E-03, 5.9000E-03, 5.4000E-03, 4.7000E-03, 
            3.4000E-03, 1.5000E-03} );

    subshell_half_profiles[1] = 
      std::vector<double>( {2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3400E-02, 
            2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3400E-02, 
            2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3400E-02, 2.3300E-02, 
            2.3300E-02, 2.3300E-02, 2.3200E-02, 2.3100E-02, 2.2900E-02, 
            2.2600E-02, 2.2100E-02, 2.1600E-02, 2.0900E-02, 2.0200E-02, 
            1.9000E-02, 1.4000E-02, 9.7000E-03, 3.6000E-03, 1.2000E-03, 
            5.4000E-04, 3.9000E-04} );

    subshell_half_profiles[2] = 
      std::vector<double>( {1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 
            1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 
            1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 
            1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 
            1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 1.1100E-02, 
            1.1000E-02, 1.1000E-02, 1.0000E-02, 7.9000E-03, 5.5000E-03, 
            2.2000E-03, 3.8000E-04} );

    subshell_half_profiles[3] = 
      std::vector<double>( {1.3800E-02, 1.3800E-02, 1.3800E-02, 1.3800E-02, 
            1.3800E-02, 1.3800E-02, 1.3800E-02, 1.3800E-02, 1.3800E-02, 
            1.3800E-02, 1.3800E-02, 1.3800E-02, 1.3800E-02, 1.3800E-02, 
            1.3800E-02, 1.3800E-02, 1.3800E-02, 1.3800E-02, 1.3800E-02, 
            1.3800E-02, 1.3800E-02, 1.3800E-02, 1.3800E-02, 1.3700E-02, 
            1.3700E-02, 1.3000E-02, 1.2000E-02, 7.9000E-03, 4.6000E-03, 
            1.3000E-03, 1.2000E-04} );

    subshell_half_profiles[4] = 
      std::vector<double>( {5.1500E-02, 5.1500E-02, 5.1400E-02, 5.1400E-02, 
            5.1400E-02, 5.1400E-02, 5.1300E-02, 5.1300E-02, 5.1200E-02, 
            5.1100E-02, 5.1000E-02, 5.0800E-02, 5.0500E-02, 5.0200E-02, 
            4.9800E-02, 4.9300E-02, 4.8800E-02, 4.7700E-02, 4.5800E-02, 
            4.1800E-02, 3.7300E-02, 3.2400E-02, 2.7600E-02, 2.2900E-02, 
            1.5000E-02, 5.3000E-03, 3.9000E-03, 2.9000E-03, 1.1000E-03, 
            1.4000E-04, 9.7000E-05} );

    subshell_half_profiles[5] = 
      std::vector<double>( {2.9800E-02, 2.9800E-02, 2.9800E-02, 2.9800E-02, 
            2.9800E-02, 2.9800E-02, 2.9800E-02, 2.9800E-02, 2.9800E-02, 
            2.9800E-02, 2.9800E-02, 2.9800E-02, 2.9800E-02, 2.9800E-02, 
            2.9800E-02, 2.9800E-02, 2.9800E-02, 2.9800E-02, 2.9700E-02, 
            2.9500E-02, 2.9200E-02, 2.8600E-02, 2.7800E-02, 2.6700E-02, 
            2.4000E-02, 1.4000E-02, 6.2000E-03, 1.3000E-03, 1.1000E-03, 
            6.5000E-04, 1.2000E-04} );

    subshell_half_profiles[6] = 
      std::vector<double>( {3.4100E-02, 3.4100E-02, 3.4100E-02, 3.4100E-02, 
            3.4100E-02, 3.4100E-02, 3.4100E-02, 3.4100E-02, 3.4100E-02, 
            3.4100E-02, 3.4100E-02, 3.4100E-02, 3.4100E-02, 3.4100E-02, 
            3.4100E-02, 3.4100E-02, 3.4100E-02, 3.4100E-02, 3.4000E-02, 
            3.3600E-02, 3.3000E-02, 3.2000E-02, 3.0500E-02, 2.8700E-02, 
            2.4000E-02, 1.1000E-02, 4.0000E-03, 1.5000E-03, 1.3000E-03, 
            4.8000E-04, 4.3000E-05} );

    subshell_half_profiles[7] = 
      std::vector<double>( {2.1800E-02, 2.1800E-02, 2.1800E-02, 2.1800E-02, 
            2.1800E-02, 2.1800E-02, 2.1800E-02, 2.1800E-02, 2.1800E-02, 
            2.1800E-02, 2.1800E-02, 2.1800E-02, 2.1800E-02, 2.1800E-02, 
            2.1800E-02, 2.1800E-02, 2.1800E-02, 2.1800E-02, 2.1800E-02, 
            2.1800E-02, 2.1800E-02, 2.1800E-02, 2.1700E-02, 2.1500E-02, 
            2.1000E-02, 1.7000E-02, 1.2000E-02, 4.2000E-03, 1.3000E-03, 
            1.3000E-04, 4.0000E-06} );

    subshell_half_profiles[8] = 
      std::vector<double>( {2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 
            2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 
            2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 
            2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 2.2700E-02, 
            2.2700E-02, 2.2700E-02, 2.2600E-02, 2.2500E-02, 2.2300E-02, 
            2.2000E-02, 1.7000E-02, 1.2000E-02, 3.8000E-03, 1.1000E-03, 
            9.3000E-05, 2.1000E-06} );

    subshell_half_profiles[9] = 
      std::vector<double>( {9.9900E-02, 9.9900E-02, 9.9900E-02, 9.9800E-02, 
            9.9700E-02, 9.9500E-02, 9.9100E-02, 9.8600E-02, 9.8000E-02, 
            9.7300E-02, 9.6500E-02, 9.4600E-02, 9.2300E-02, 8.9700E-02, 
            8.6800E-02, 8.3700E-02, 8.0300E-02, 7.3000E-02, 6.1400E-02, 
            4.2700E-02, 2.7900E-02, 1.8200E-02, 1.3200E-02, 1.1200E-02, 
            1.1000E-02, 5.7000E-03, 1.6000E-03, 9.9000E-04, 4.2000E-04, 
            4.2000E-05, 2.7000E-05} );

    subshell_half_profiles[10] = 
      std::vector<double>( {6.2500E-02, 6.2500E-02, 6.2500E-02, 6.2500E-02, 
            6.2500E-02, 6.2500E-02, 6.2500E-02, 6.2500E-02, 6.2500E-02, 
            6.2500E-02, 6.2500E-02, 6.2500E-02, 6.2400E-02, 6.2300E-02, 
            6.2200E-02, 6.2000E-02, 6.1800E-02, 6.1100E-02, 5.9400E-02, 
            5.4400E-02, 4.6800E-02, 3.7700E-02, 2.8400E-02, 2.0200E-02, 
            9.4000E-03, 4.5000E-03, 3.5000E-03, 5.8000E-04, 2.6000E-04, 
            1.8000E-04, 3.4000E-05} );

    subshell_half_profiles[11] = 
      std::vector<double>( {7.0300E-02, 7.0300E-02, 7.0300E-02, 7.0300E-02, 
            7.0300E-02, 7.0300E-02, 7.0300E-02, 7.0300E-02, 7.0300E-02, 
            7.0300E-02, 7.0300E-02, 7.0200E-02, 7.0200E-02, 7.0000E-02, 
            6.9800E-02, 6.9500E-02, 6.9100E-02, 6.7900E-02, 6.5000E-02, 
            5.7000E-02, 4.6000E-02, 3.4100E-02, 2.3500E-02, 1.5400E-02, 
            7.1000E-03, 5.2000E-03, 2.7000E-03, 4.1000E-04, 3.6000E-04, 
            1.5000E-04, 1.3000E-05} );

    subshell_half_profiles[12] = 
      std::vector<double>( {5.1500E-02, 5.1500E-02, 5.1500E-02, 5.1500E-02, 
            5.1500E-02, 5.1500E-02, 5.1500E-02, 5.1500E-02, 5.1500E-02, 
            5.1500E-02, 5.1500E-02, 5.1500E-02, 5.1500E-02, 5.1500E-02, 
            5.1400E-02, 5.1400E-02, 5.1400E-02, 5.1300E-02, 5.1100E-02, 
            4.9900E-02, 4.7100E-02, 4.2500E-02, 3.6500E-02, 2.9700E-02, 
            1.7000E-02, 3.1000E-03, 2.2000E-03, 1.3000E-03, 4.5000E-04, 
            4.7000E-05, 1.4000E-06} );

    subshell_half_profiles[13] = 
      std::vector<double>( {5.3200E-02, 5.3200E-02, 5.3200E-02, 5.3200E-02, 
            5.3200E-02, 5.3200E-02, 5.3200E-02, 5.3200E-02, 5.3200E-02, 
            5.3200E-02, 5.3200E-02, 5.3200E-02, 5.3100E-02, 5.3100E-02, 
            5.3100E-02, 5.3100E-02, 5.3100E-02, 5.3000E-02, 5.2700E-02, 
            5.1200E-02, 4.8000E-02, 4.2800E-02, 3.6100E-02, 2.8800E-02, 
            1.6000E-02, 2.9000E-03, 2.3000E-03, 1.2000E-03, 3.8000E-04, 
            3.4000E-05, 7.3000E-07} );

    subshell_half_profiles[14] = 
      std::vector<double>( {4.0400E-02, 4.0400E-02, 4.0400E-02, 4.0400E-02, 
            4.0400E-02, 4.0400E-02, 4.0400E-02, 4.0400E-02, 4.0400E-02, 
            4.0400E-02, 4.0400E-02, 4.0400E-02, 4.0400E-02, 4.0400E-02, 
            4.0400E-02, 4.0400E-02, 4.0400E-02, 4.0400E-02, 4.0400E-02, 
            4.0200E-02, 3.9500E-02, 3.8200E-02, 3.6000E-02, 3.3000E-02, 
            2.6000E-02, 1.0000E-02, 3.2000E-03, 3.2000E-04, 4.1000E-05, 
            1.3000E-06, 1.1000E-08} );

    subshell_half_profiles[15] = 
      std::vector<double>( {4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 
            4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 
            4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 
            4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1100E-02, 4.1000E-02, 
            4.0800E-02, 4.0100E-02, 3.8700E-02, 3.6300E-02, 3.3100E-02, 
            2.5000E-02, 9.6000E-03, 3.0000E-03, 2.9000E-04, 3.5000E-05, 
            1.0000E-06, 6.7000E-09} );

    subshell_half_profiles[16] = 
      std::vector<double>( {1.9900E-01, 1.9900E-01, 1.9900E-01, 1.9800E-01, 
            1.9700E-01, 1.9500E-01, 1.9200E-01, 1.8800E-01, 1.8400E-01, 
            1.7800E-01, 1.7300E-01, 1.5900E-01, 1.4500E-01, 1.2900E-01, 
            1.1300E-01, 9.8100E-02, 8.3800E-02, 5.9600E-02, 3.5800E-02, 
            2.3000E-02, 2.2300E-02, 1.9500E-02, 1.3700E-02, 8.2700E-03, 
            3.4000E-03, 2.3000E-03, 6.0000E-04, 2.7000E-04, 1.2000E-04, 
            1.2000E-05, 7.2000E-06} );

    subshell_half_profiles[17] = 
      std::vector<double>( {1.3000E-01, 1.3000E-01, 1.3000E-01, 1.3000E-01, 
            1.3000E-01, 1.3000E-01, 1.3000E-01, 1.3000E-01, 1.3000E-01, 
            1.3000E-01, 1.2900E-01, 1.2800E-01, 1.2700E-01, 1.2400E-01, 
            1.2000E-01, 1.1600E-01, 1.1000E-01, 9.6600E-02, 7.2500E-02, 
            3.6400E-02, 1.6800E-02, 1.0900E-02, 1.0400E-02, 9.9700E-03, 
            6.2000E-03, 1.1000E-03, 9.8000E-04, 1.8000E-04, 6.3000E-05, 
            4.6000E-05, 8.7000E-06} );

    subshell_half_profiles[18] = 
      std::vector<double>( {1.4800E-01, 1.4800E-01, 1.4800E-01, 1.4800E-01, 
            1.4800E-01, 1.4700E-01, 1.4700E-01, 1.4700E-01, 1.4700E-01, 
            1.4700E-01, 1.4600E-01, 1.4400E-01, 1.4100E-01, 1.3700E-01, 
            1.3100E-01, 1.2300E-01, 1.1500E-01, 9.5000E-02, 6.4100E-02, 
            2.7000E-02, 1.3500E-02, 1.1700E-02, 1.1300E-02, 9.4000E-03, 
            4.2000E-03, 1.3000E-03, 8.2000E-04, 1.1000E-04, 8.8000E-05, 
            3.7000E-05, 3.3000E-06} );

    subshell_half_profiles[19] = 
      std::vector<double>( {1.2100E-01, 1.2100E-01, 1.2100E-01, 1.2100E-01, 
            1.2100E-01, 1.2100E-01, 1.2100E-01, 1.2100E-01, 1.2100E-01, 
            1.2100E-01, 1.2100E-01, 1.2100E-01, 1.2100E-01, 1.2000E-01, 
            1.1800E-01, 1.1600E-01, 1.1300E-01, 1.0400E-01, 8.4300E-02, 
            4.7900E-02, 2.1800E-02, 9.5700E-03, 5.8900E-03, 5.4100E-03, 
            4.8000E-03, 1.0000E-03, 4.0000E-04, 2.8000E-04, 1.0000E-04, 
            1.1000E-05, 3.1000E-07} );

    subshell_half_profiles[20] = 
      std::vector<double>( {1.2600E-01, 1.2600E-01, 1.2600E-01, 1.2600E-01, 
            1.2600E-01, 1.2600E-01, 1.2600E-01, 1.2600E-01, 1.2600E-01, 
            1.2600E-01, 1.2600E-01, 1.2500E-01, 1.2500E-01, 1.2400E-01, 
            1.2200E-01, 1.1900E-01, 1.1500E-01, 1.0500E-01, 8.3200E-02, 
            4.4900E-02, 1.9400E-02, 8.5600E-03, 5.7800E-03, 5.5500E-03, 
            4.7000E-03, 8.8000E-04, 4.2000E-04, 2.6000E-04, 8.4000E-05, 
            7.5000E-06, 1.6000E-07} );

    subshell_half_profiles[21] = 
      std::vector<double>( {1.4400E-01, 1.4400E-01, 1.4400E-01, 1.4400E-01, 
            1.4400E-01, 1.4400E-01, 1.4400E-01, 1.4400E-01, 1.4400E-01, 
            1.4400E-01, 1.4400E-01, 1.4200E-01, 1.4000E-01, 1.3700E-01, 
            1.3200E-01, 1.2600E-01, 1.1800E-01, 1.0200E-01, 7.6500E-02, 
            4.1300E-02, 1.9600E-02, 8.5600E-03, 3.8200E-03, 2.1500E-03, 
            1.7000E-03, 1.1000E-03, 4.1000E-04, 4.4000E-05, 5.6000E-06, 
            1.9000E-07, 1.5000E-09} );

    subshell_half_profiles[22] = 
      std::vector<double>( {1.5100E-01, 1.5100E-01, 1.5100E-01, 1.5100E-01, 
            1.5100E-01, 1.5100E-01, 1.5100E-01, 1.5100E-01, 1.5100E-01, 
            1.5100E-01, 1.5000E-01, 1.4900E-01, 1.4500E-01, 1.4100E-01, 
            1.3400E-01, 1.2700E-01, 1.1800E-01, 1.0000E-01, 7.3600E-02, 
            3.8600E-02, 1.7800E-02, 7.6400E-03, 3.4200E-03, 2.0000E-03, 
            1.6000E-03, 1.0000E-03, 3.7000E-04, 3.8000E-05, 4.6000E-06, 
            1.4000E-07, 9.1000E-10} );

    subshell_half_profiles[23] = 
      std::vector<double>( {4.8500E-01, 4.8400E-01, 4.7900E-01, 4.7200E-01, 
            4.6200E-01, 4.3500E-01, 4.0000E-01, 3.5900E-01, 3.1600E-01, 
            2.7100E-01, 2.2900E-01, 1.5400E-01, 1.0000E-01, 6.6000E-02, 
            4.8200E-02, 4.0800E-02, 3.8800E-02, 3.8300E-02, 2.9900E-02, 
            1.1000E-02, 4.9500E-03, 4.6200E-03, 3.9400E-03, 2.6000E-03, 
            8.5000E-04, 5.0000E-04, 1.3000E-04, 5.5000E-05, 2.5000E-05, 
            2.3000E-06, 1.4000E-06} );

    subshell_half_profiles[24] = 
      std::vector<double>( {3.3100E-01, 3.3100E-01, 3.3100E-01, 3.3100E-01, 
            3.3100E-01, 3.2900E-01, 3.2600E-01, 3.2000E-01, 3.1100E-01, 
            2.9700E-01, 2.8000E-01, 2.3700E-01, 1.8800E-01, 1.4000E-01, 
            9.8800E-02, 6.6900E-02, 4.4500E-02, 2.2200E-02, 1.6300E-02, 
            1.3900E-02, 7.0100E-03, 2.8900E-03, 1.8100E-03, 1.7400E-03, 
            1.3000E-03, 2.1000E-04, 1.7000E-04, 3.3000E-05, 1.1000E-05, 
            7.9000E-06, 1.5000E-06} );

    subshell_half_profiles[25] = 
      std::vector<double>( {4.1000E-01, 4.1000E-01, 4.1000E-01, 4.1000E-01, 
            4.0900E-01, 4.0500E-01, 3.9700E-01, 3.8200E-01, 3.6000E-01, 
            3.3200E-01, 2.9900E-01, 2.2500E-01, 1.5600E-01, 1.0100E-01, 
            6.1700E-02, 3.7700E-02, 2.4600E-02, 1.6400E-02, 1.5700E-02, 
            9.3400E-03, 3.4300E-03, 1.7300E-03, 1.6100E-03, 1.4800E-03, 
            7.3000E-04, 1.8000E-04, 1.2000E-04, 1.5000E-05, 1.2000E-05, 
            5.1000E-06, 4.5000E-07} );

    subshell_half_profiles[26] = 
      std::vector<double>( {1.8700E+00, 1.8100E+00, 1.6300E+00, 1.3700E+00, 
            1.0700E+00, 5.5800E-01, 2.4200E-01, 1.0300E-01, 5.9300E-02, 
            5.1700E-02, 5.1300E-02, 4.3700E-02, 2.9200E-02, 1.6700E-02, 
            8.8400E-03, 4.8800E-03, 3.2500E-03, 2.7000E-03, 2.3800E-03, 
            9.2100E-04, 3.4200E-04, 2.9800E-04, 2.6300E-04, 1.7700E-04, 
            5.7000E-05, 3.2000E-05, 8.6000E-06, 3.5000E-06, 1.6000E-06, 
            1.5000E-07, 9.1000E-08} );
  }
};

// Get the default generator
std::shared_ptr<ComptonProfileGenerator> ComptonProfileGenerator::getDefaultGenerator( const unsigned atomic_number )
{
  switch( atomic_number )
  {
    case 1u: return std::make_shared<DefaultComptonProfileGeneratorImpl<1u> >();
    case 2u: return std::make_shared<DefaultComptonProfileGeneratorImpl<2u> >();
    case 3u: return std::make_shared<DefaultComptonProfileGeneratorImpl<3u> >();
    case 4u: return std::make_shared<DefaultComptonProfileGeneratorImpl<4u> >();
    case 5u: return std::make_shared<DefaultComptonProfileGeneratorImpl<5u> >();
    case 6u: return std::make_shared<DefaultComptonProfileGeneratorImpl<6u> >();
    case 7u: return std::make_shared<DefaultComptonProfileGeneratorImpl<7u> >();
    case 8u: return std::make_shared<DefaultComptonProfileGeneratorImpl<8u> >();
    case 9u: return std::make_shared<DefaultComptonProfileGeneratorImpl<9u> >();
    case 10u: return std::make_shared<DefaultComptonProfileGeneratorImpl<10u> >();
    case 11u: return std::make_shared<DefaultComptonProfileGeneratorImpl<11u> >();
    case 12u: return std::make_shared<DefaultComptonProfileGeneratorImpl<12u> >();
    case 13u: return std::make_shared<DefaultComptonProfileGeneratorImpl<13u> >();
    case 14u: return std::make_shared<DefaultComptonProfileGeneratorImpl<14u> >();
    case 15u: return std::make_shared<DefaultComptonProfileGeneratorImpl<15u> >();
    case 16u: return std::make_shared<DefaultComptonProfileGeneratorImpl<16u> >();
    case 17u: return std::make_shared<DefaultComptonProfileGeneratorImpl<17u> >();
    case 18u: return std::make_shared<DefaultComptonProfileGeneratorImpl<18u> >();
    case 19u: return std::make_shared<DefaultComptonProfileGeneratorImpl<19u> >();
    case 20u: return std::make_shared<DefaultComptonProfileGeneratorImpl<20u> >();
    case 21u: return std::make_shared<DefaultComptonProfileGeneratorImpl<21u> >();
    case 22u: return std::make_shared<DefaultComptonProfileGeneratorImpl<22u> >();
    case 23u: return std::make_shared<DefaultComptonProfileGeneratorImpl<23u> >();
    case 24u: return std::make_shared<DefaultComptonProfileGeneratorImpl<24u> >();
    case 25u: return std::make_shared<DefaultComptonProfileGeneratorImpl<25u> >();
    case 26u: return std::make_shared<DefaultComptonProfileGeneratorImpl<26u> >();
    case 27u: return std::make_shared<DefaultComptonProfileGeneratorImpl<27u> >();
    case 28u: return std::make_shared<DefaultComptonProfileGeneratorImpl<28u> >();
    case 29u: return std::make_shared<DefaultComptonProfileGeneratorImpl<29u> >();
    case 30u: return std::make_shared<DefaultComptonProfileGeneratorImpl<30u> >();
    case 31u: return std::make_shared<DefaultComptonProfileGeneratorImpl<31u> >();
    case 32u: return std::make_shared<DefaultComptonProfileGeneratorImpl<32u> >();
    case 33u: return std::make_shared<DefaultComptonProfileGeneratorImpl<33u> >();
    case 34u: return std::make_shared<DefaultComptonProfileGeneratorImpl<34u> >();
    case 35u: return std::make_shared<DefaultComptonProfileGeneratorImpl<35u> >();
    case 36u: return std::make_shared<DefaultComptonProfileGeneratorImpl<36u> >();
    case 37u: return std::make_shared<DefaultComptonProfileGeneratorImpl<37u> >();
    case 38u: return std::make_shared<DefaultComptonProfileGeneratorImpl<38u> >();
    case 39u: return std::make_shared<DefaultComptonProfileGeneratorImpl<39u> >();
    case 40u: return std::make_shared<DefaultComptonProfileGeneratorImpl<40u> >();
    case 41u: return std::make_shared<DefaultComptonProfileGeneratorImpl<41u> >();
    case 42u: return std::make_shared<DefaultComptonProfileGeneratorImpl<42u> >();
    case 43u: return std::make_shared<DefaultComptonProfileGeneratorImpl<43u> >();
    case 44u: return std::make_shared<DefaultComptonProfileGeneratorImpl<44u> >();
    case 45u: return std::make_shared<DefaultComptonProfileGeneratorImpl<45u> >();
    case 46u: return std::make_shared<DefaultComptonProfileGeneratorImpl<46u> >();
    case 47u: return std::make_shared<DefaultComptonProfileGeneratorImpl<47u> >();
    case 48u: return std::make_shared<DefaultComptonProfileGeneratorImpl<48u> >();
    case 49u: return std::make_shared<DefaultComptonProfileGeneratorImpl<49u> >();
    case 50u: return std::make_shared<DefaultComptonProfileGeneratorImpl<50u> >();
    case 51u: return std::make_shared<DefaultComptonProfileGeneratorImpl<51u> >();
    case 52u: return std::make_shared<DefaultComptonProfileGeneratorImpl<52u> >();
    case 53u: return std::make_shared<DefaultComptonProfileGeneratorImpl<53u> >();
    case 54u: return std::make_shared<DefaultComptonProfileGeneratorImpl<54u> >();
    case 55u: return std::make_shared<DefaultComptonProfileGeneratorImpl<55u> >();
    case 56u: return std::make_shared<DefaultComptonProfileGeneratorImpl<56u> >();
    case 57u: return std::make_shared<DefaultComptonProfileGeneratorImpl<57u> >();
    case 58u: return std::make_shared<DefaultComptonProfileGeneratorImpl<58u> >();
    case 59u: return std::make_shared<DefaultComptonProfileGeneratorImpl<59u> >();
    case 60u: return std::make_shared<DefaultComptonProfileGeneratorImpl<60u> >();
    case 61u: return std::make_shared<DefaultComptonProfileGeneratorImpl<61u> >();
    case 62u: return std::make_shared<DefaultComptonProfileGeneratorImpl<62u> >();
    case 63u: return std::make_shared<DefaultComptonProfileGeneratorImpl<63u> >();
    case 64u: return std::make_shared<DefaultComptonProfileGeneratorImpl<64u> >();
    case 65u: return std::make_shared<DefaultComptonProfileGeneratorImpl<65u> >();
    case 66u: return std::make_shared<DefaultComptonProfileGeneratorImpl<66u> >();
    case 67u: return std::make_shared<DefaultComptonProfileGeneratorImpl<67u> >();
    case 68u: return std::make_shared<DefaultComptonProfileGeneratorImpl<68u> >();
    case 69u: return std::make_shared<DefaultComptonProfileGeneratorImpl<69u> >();
    case 70u: return std::make_shared<DefaultComptonProfileGeneratorImpl<70u> >();
    case 71u: return std::make_shared<DefaultComptonProfileGeneratorImpl<71u> >();
    case 72u: return std::make_shared<DefaultComptonProfileGeneratorImpl<72u> >();
    case 73u: return std::make_shared<DefaultComptonProfileGeneratorImpl<73u> >();
    case 74u: return std::make_shared<DefaultComptonProfileGeneratorImpl<74u> >();
    case 75u: return std::make_shared<DefaultComptonProfileGeneratorImpl<75u> >();
    case 76u: return std::make_shared<DefaultComptonProfileGeneratorImpl<76u> >();
    case 77u: return std::make_shared<DefaultComptonProfileGeneratorImpl<77u> >();
    case 78u: return std::make_shared<DefaultComptonProfileGeneratorImpl<78u> >();
    case 79u: return std::make_shared<DefaultComptonProfileGeneratorImpl<79u> >();
    case 80u: return std::make_shared<DefaultComptonProfileGeneratorImpl<80u> >();
    case 81u: return std::make_shared<DefaultComptonProfileGeneratorImpl<81u> >();
    case 82u: return std::make_shared<DefaultComptonProfileGeneratorImpl<82u> >();
    case 83u: return std::make_shared<DefaultComptonProfileGeneratorImpl<83u> >();
    case 84u: return std::make_shared<DefaultComptonProfileGeneratorImpl<84u> >();
    case 85u: return std::make_shared<DefaultComptonProfileGeneratorImpl<85u> >();
    case 86u: return std::make_shared<DefaultComptonProfileGeneratorImpl<86u> >();
    case 87u: return std::make_shared<DefaultComptonProfileGeneratorImpl<87u> >();
    case 88u: return std::make_shared<DefaultComptonProfileGeneratorImpl<88u> >();
    case 89u: return std::make_shared<DefaultComptonProfileGeneratorImpl<89u> >();
    case 90u: return std::make_shared<DefaultComptonProfileGeneratorImpl<90u> >();
    case 91u: return std::make_shared<DefaultComptonProfileGeneratorImpl<91u> >();
    case 92u: return std::make_shared<DefaultComptonProfileGeneratorImpl<92u> >();
    case 93u: return std::make_shared<DefaultComptonProfileGeneratorImpl<93u> >();
    case 94u: return std::make_shared<DefaultComptonProfileGeneratorImpl<94u> >();
    case 95u: return std::make_shared<DefaultComptonProfileGeneratorImpl<95u> >();
    case 96u: return std::make_shared<DefaultComptonProfileGeneratorImpl<96u> >();
    case 97u: return std::make_shared<DefaultComptonProfileGeneratorImpl<97u> >();
    case 98u: return std::make_shared<DefaultComptonProfileGeneratorImpl<98u> >();
    case 99u: return std::make_shared<DefaultComptonProfileGeneratorImpl<99u> >();
    case 100u: return std::make_shared<DefaultComptonProfileGeneratorImpl<100u> >();
    default:
    {
      THROW_EXCEPTION( std::runtime_error,
                       "The atomic number " << atomic_number << " is not "
                       "supported!" );
    }
  }
}
  
} // end DataGen namespace

//---------------------------------------------------------------------------//
// end DataGen_ComptonProfileGenerator.cpp
//---------------------------------------------------------------------------//
