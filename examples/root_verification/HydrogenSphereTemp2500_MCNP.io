          Code Name & Version = MCNP, 6.1.1b

     _/      _/        _/_/_/       _/      _/       _/_/_/         _/_/_/
    _/_/  _/_/      _/             _/_/    _/       _/    _/     _/
   _/  _/  _/      _/             _/  _/  _/       _/_/_/       _/_/_/
  _/      _/      _/             _/    _/_/       _/           _/    _/
 _/      _/        _/_/_/       _/      _/       _/             _/_/

  +---------------------------------------------------------------------+
  | Copyright 2008. Los Alamos National Security, LLC.  All rights      |
  | reserved.                                                           |
  |   This material was produced under U.S. Government contract         |
  | DE-AC52-06NA25396 for Los Alamos National Laboratory, which is      |
  | operated by Los Alamos National Security, LLC, for the U.S.         |
  | Department of Energy. The Government is granted for itself and      |
  | others acting on its behalf a paid-up, nonexclusive, irrevocable    |
  | worldwide license in this material to reproduce, prepare derivative |
  | works, and perform publicly and display publicly. Beginning five    |
  | (5) years after 2008, subject to additional five-year worldwide     |
  | renewals, the Government is granted for itself and others acting on |
  | its behalf a paid-up, nonexclusive, irrevocable worldwide license   |
  | in this material to reproduce, prepare derivative works, distribute |
  | copies to the public, perform publicly and display publicly, and to |
  | permit others to do so. NEITHER THE UNITED STATES NOR THE UNITED    |
  | STATES DEPARTMENT OF ENERGY, NOR LOS ALAMOS NATIONAL SECURITY, LLC, |
  | NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, |
  | OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY,  |
  | COMPLETENESS, OR USEFULNESS OF ANY INFORMATION, APPARATUS, PRODUCT, |
  | OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE |
  | PRIVATELY OWNED RIGHTS.                                             |
  +---------------------------------------------------------------------+

1mcnp     version 6     ld=06/19/14                     08/26/15 18:33:27
 *************************************************************************                 probid =  08/26/15 18:33:27
 n=HydrogenSphereTemp2500_MCNP.i


  warning.  Physics models disabled.
         1-       1 MeV neutrons in a sphere of hydrogen at T = 2500 K
         2-       100   1    1.0       -10         tmp=2.1543E-07     imp:n=1
         3-       999   0              +10                            imp:n=0
         4-
         5-       10   so    1.0
         6-
         7-       nps    1e6
         8-       sdef   pos = 0 0 0   erg = 1.000001
         9-       c
        10-       m1     1001.74c   1.0
        11-       c
        12-       c      neutron capture rate
        13-       f4:n   100
        14-       c
        15-       e0     1e-11  109ilog  1.0
        16-       c
        17-       prdmp  j  1e7  1  1
        18-

  comment.  total nubar used if fissionable isotopes are present.
1cells                                                                                                  print table 60

                               atom        gram                                            neutron
              cell      mat   density     density     volume       mass            pieces importance

        1      100        1  1.00000E+00 1.67356E+00 4.18879E+00 7.01019E+00           1  1.0000E+00
        2      999        0  0.00000E+00 0.00000E+00 0.00000E+00 0.00000E+00           0  0.0000E+00

 total                                               4.18879E+00 7.01019E+00

    minimum source weight = 1.0000E+00    maximum source weight = 1.0000E+00

 ***************************************************
 * Random Number Generator  =                    1 *
 * Random Number Seed       =       19073486328125 *
 * Random Number Multiplier =       19073486328125 *
 * Random Number Adder      =                    0 *
 * Random Number Bits Used  =                   48 *
 * Random Number Stride     =               152917 *
 ***************************************************


          1 warning message so far.
1cross-section tables                                                                                   print table 100
     XSDIR used: /home/software/mcnpdata/xsdir_mcnp6.1

     table    length

                        tables from file xdata/endf70a

   1001.74c    3652   1-H -  1 at 2500K  from endf/b-vii.0 njoy99.248                             mat 125      03/27/08
                     Energy range:   1.00000E-11  to  2.00000E+01 MeV.
                     particle-production data for deuterons being expunged from   1001.74c

  total        3652

1particles and energy limits                                                                            print table 101

                         particle      maximum       smallest      largest       always        always
                         cutoff        particle      table         table         use table     use model
   particle type         energy        energy        maximum       maximum       below         above

    1  n    neutron     0.0000E+00    1.0000E+36    2.0000E+01    2.0000E+01    1.0000E+36    1.0000E+36

  comment.  setting up hash-based fast table search for xsec tables

 ------------------------------------------------------------------------------------------
 =====> Set up arrays for hash-based fast table search for xsec data

    number of hash bins   =     8192
    max hash table energy =  1.00000E-11
    min hash table energy =  2.00000E+01

           nuclide      ne      emin        emax     ave_bins  min_bins  max_bins
            1001.74c     590 1.00000E-11 2.00000E+01       1.1       1.0       2.0

 ------------------------------------------------------------------------------------------


 ***********************************************************************************************************************

 dump no.    1 on file HydrogenSphereTemp2500_MCNP.ir     nps =           0     coll =              0     ctm =
 0.00   nrn =                 0

          1 warning message so far.
 warning.  tally not scored beyond last energy bin.
 nps =           1     nrn =                   3 tal =    4     erg = 1.0000E+00
1problem summary

      run terminated when     1000000  particle histories were done.
+                                                                                                    08/26/15 18:35:54
      1 MeV neutrons in a sphere of hydrogen at T = 2500 K                                 probid =  08/26/15 18:33:27

 neutron creation    tracks      weight        energy            neutron loss        tracks      weight        energy
                                 (per source particle)                                           (per source particle)

 source             1000000    1.0000E+00    1.0000E+00          escape              957001    6.8755E-01    5.4280E-02
 nucl. interaction        0    0.            0.                  energy cutoff            0    0.            0.
 particle decay           0    0.            0.                  time cutoff              0    0.            0.
 weight window            0    0.            0.                  weight window            0    0.            0.
 cell importance          0    0.            0.                  cell importance          0    0.            0.
 weight cutoff            0    1.0767E-02    3.4625E-09          weight cutoff        42999    1.0730E-02    3.4320E-09
 e or t importance        0    0.            0.                  e or t importance        0    0.            0.
 dxtran                   0    0.            0.                  dxtran                   0    0.            0.
 forced collisions        0    0.            0.                  forced collisions        0    0.            0.
 exp. transform           0    0.            0.                  exp. transform           0    0.            0.
 upscattering             0    0.            9.5439E-06          downscattering           0    0.            9.4572E-01
 photonuclear             0    0.            0.                  capture                  0    3.1249E-01    1.4619E-05
 (n,xn)                   0    0.            0.                  loss to (n,xn)           0    0.            0.
 prompt fission           0    0.            0.                  loss to fission          0    0.            0.
 delayed fission          0    0.            0.                  nucl. interaction        0    0.            0.
 prompt photofis          0    0.            0.                  particle decay           0    0.            0.
 tabular boundary         0    0.            0.                  tabular boundary         0    0.            0.
 tabular sampling         0    0.            0.                  elastic scatter          0    0.            0.
     total          1000000    1.0108E+00    1.0000E+00              total          1000000    1.0108E+00    1.0000E+00

   number of neutrons banked                       0        average time of (shakes)              cutoffs
   neutron tracks per source particle     1.0000E+00          escape            3.9623E+02          tco   1.0000E+33
   neutron collisions per source particle 1.4593E+02          capture           4.9719E+02          eco   0.0000E+00
   total neutron collisions                145929814          capture or escape 4.2778E+02          wc1  -5.0000E-01
   net multiplication              1.0000E+00 0.0000          any termination   4.4478E+02          wc2  -2.5000E-01

 computer time so far in this run     2.46 minutes            maximum number ever in bank         0
 computer time in mcrun               2.45 minutes            bank overflows to backup file       0
 source particles per minute            4.0746E+05
 random numbers generated               2358307791            most random numbers used was       24782 in history      644289

 range of sampled source weights = 1.0000E+00 to 1.0000E+00
1neutron  activity in each cell                                                                         print table 126

                       tracks     population   collisions   collisions     number        flux        average      average
              cell    entering                               * weight     weighted     weighted   track weight   track mfp
                                                          (per history)    energy       energy     (relative)      (cm)

        1      100     1000000      1000000    145929814    1.0181E+02   7.7241E-05   9.1478E-02   7.2930E-01   5.7737E-02

           total       1000000      1000000    145929814    1.0181E+02

1tally        4        nps =     1000000
           tally type 4    track length estimate of particle flux.      units   1/cm**2
           particle(s): neutrons

           volumes
                   cell:      100
                         4.18879E+00

 cell  100
      energy
    1.0000E-11   7.64010E-10 0.3149
    1.2589E-11   3.74023E-12 1.0000
    1.5849E-11   1.09090E-09 0.4177
    1.9953E-11   9.61757E-10 0.3106
    2.5119E-11   1.36245E-09 0.2618
    3.1623E-11   2.10576E-09 0.2470
    3.9811E-11   4.68555E-09 0.2147
    5.0119E-11   6.39613E-09 0.1730
    6.3096E-11   1.10397E-08 0.1574
    7.9433E-11   1.81878E-08 0.1205
    1.0000E-10   2.53927E-08 0.1091
    1.2589E-10   5.05354E-08 0.0952
    1.5849E-10   5.81501E-08 0.0759
    1.9953E-10   1.12195E-07 0.0620
    2.5119E-10   1.90612E-07 0.0531
    3.1623E-10   2.85710E-07 0.0454
    3.9811E-10   4.29678E-07 0.0372
    5.0119E-10   7.04494E-07 0.0310
    6.3096E-10   1.09138E-06 0.0259
    7.9433E-10   1.74887E-06 0.0222
    1.0000E-09   2.81858E-06 0.0188
    1.2589E-09   4.52275E-06 0.0154
    1.5849E-09   7.35695E-06 0.0130
    1.9953E-09   1.11273E-05 0.0111
    2.5119E-09   1.82035E-05 0.0092
    3.1623E-09   2.88484E-05 0.0078
    3.9811E-09   4.43696E-05 0.0066
    5.0119E-09   7.07606E-05 0.0056
    6.3096E-09   1.11274E-04 0.0048
    7.9433E-09   1.75322E-04 0.0040
    1.0000E-08   2.75433E-04 0.0034
    1.2589E-08   4.30542E-04 0.0029
    1.5849E-08   6.74136E-04 0.0025
    1.9953E-08   1.05750E-03 0.0022
    2.5119E-08   1.63584E-03 0.0019
    3.1623E-08   2.52327E-03 0.0017
    3.9811E-08   3.86274E-03 0.0015
    5.0119E-08   5.85304E-03 0.0014
    6.3096E-08   8.79618E-03 0.0013
    7.9433E-08   1.30359E-02 0.0012
    1.0000E-07   1.89621E-02 0.0011
    1.2589E-07   2.69782E-02 0.0011
    1.5849E-07   3.73369E-02 0.0010
    1.9953E-07   4.98427E-02 0.0010
    2.5119E-07   6.37786E-02 0.0010
    3.1623E-07   7.72562E-02 0.0009
    3.9811E-07   8.73137E-02 0.0009
    5.0119E-07   9.04790E-02 0.0009
    6.3096E-07   8.43643E-02 0.0009
    7.9433E-07   6.87976E-02 0.0010
    1.0000E-06   4.78339E-02 0.0010
    1.2589E-06   2.75726E-02 0.0011
    1.5849E-06   1.31416E-02 0.0014
    1.9953E-06   5.73730E-03 0.0020
    2.5119E-06   3.11397E-03 0.0028
    3.1623E-06   2.47774E-03 0.0031
    3.9811E-06   2.34178E-03 0.0032
    5.0119E-06   2.31260E-03 0.0032
    6.3096E-06   2.26946E-03 0.0032
    7.9433E-06   2.25852E-03 0.0032
    1.0000E-05   2.24741E-03 0.0032
    1.2589E-05   2.23682E-03 0.0033
    1.5849E-05   2.24292E-03 0.0032
    1.9953E-05   2.23015E-03 0.0032
    2.5119E-05   2.23892E-03 0.0032
    3.1623E-05   2.23000E-03 0.0032
    3.9811E-05   2.24326E-03 0.0032
    5.0119E-05   2.23430E-03 0.0032
    6.3096E-05   2.25964E-03 0.0032
    7.9433E-05   2.24802E-03 0.0032
    1.0000E-04   2.24565E-03 0.0032
    1.2589E-04   2.25540E-03 0.0032
    1.5849E-04   2.25157E-03 0.0032
    1.9953E-04   2.26541E-03 0.0032
    2.5119E-04   2.27605E-03 0.0032
    3.1623E-04   2.28564E-03 0.0032
    3.9811E-04   2.28918E-03 0.0032
    5.0119E-04   2.29045E-03 0.0032
    6.3096E-04   2.30021E-03 0.0032
    7.9433E-04   2.30267E-03 0.0032
    1.0000E-03   2.30615E-03 0.0032
    1.2589E-03   2.32449E-03 0.0032
    1.5849E-03   2.31286E-03 0.0032
    1.9953E-03   2.34791E-03 0.0032
    2.5119E-03   2.34903E-03 0.0032
    3.1623E-03   2.36941E-03 0.0032
    3.9811E-03   2.36937E-03 0.0032
    5.0119E-03   2.40949E-03 0.0032
    6.3096E-03   2.41471E-03 0.0032
    7.9433E-03   2.45552E-03 0.0032
    1.0000E-02   2.47538E-03 0.0032
    1.2589E-02   2.50782E-03 0.0032
    1.5849E-02   2.56193E-03 0.0031
    1.9953E-02   2.62927E-03 0.0031
    2.5119E-02   2.69603E-03 0.0031
    3.1623E-02   2.78695E-03 0.0031
    3.9811E-02   2.90353E-03 0.0031
    5.0119E-02   3.03450E-03 0.0031
    6.3096E-02   3.23188E-03 0.0031
    7.9433E-02   3.42831E-03 0.0031
    1.0000E-01   3.68604E-03 0.0031
    1.2589E-01   3.98926E-03 0.0031
    1.5849E-01   4.36957E-03 0.0031
    1.9953E-01   4.81709E-03 0.0031
    2.5119E-01   5.31103E-03 0.0031
    3.1623E-01   5.97360E-03 0.0030
    3.9811E-01   6.75455E-03 0.0030
    5.0119E-01   7.63456E-03 0.0030
    6.3096E-01   8.69289E-03 0.0029
    7.9433E-01   9.84509E-03 0.0029
    1.0000E+00   1.12438E-02 0.0028
      total      9.22198E-01 0.0007


 ===================================================================================================================================

           results of 10 statistical checks for the estimated answer for the tally fluctuation chart (tfc) bin of tally        4

 tfc bin     --mean--      ---------relative error---------      ----variance of the variance----      --figure of merit--     -pdf-
 behavior    behavior      value   decrease   decrease rate      value   decrease   decrease rate       value     behavior     slope

 desired      random       <0.10      yes      1/sqrt(nps)       <0.10      yes        1/nps           constant    random      >3.00
 observed     random        0.00      yes          yes            0.00      yes         yes            constant    random       7.13
 passed?        yes          yes      yes          yes             yes      yes         yes               yes        yes         yes

 ===================================================================================================================================


 this tally meets the statistical criteria used to form confidence intervals: check the tally fluctuation chart to verify.
 the results in other bins associated with this tally may not meet these statistical criteria.

 ----- estimated confidence intervals:  -----

 estimated asymmetric confidence interval(1,2,3 sigma): 9.2158E-01 to 9.2282E-01; 9.2096E-01 to 9.2344E-01; 9.2033E-01 to 9.2406E-01
 estimated  symmetric confidence interval(1,2,3 sigma): 9.2158E-01 to 9.2282E-01; 9.2096E-01 to 9.2344E-01; 9.2033E-01 to 9.2406E-01

1analysis of the results in the tally fluctuation chart bin (tfc) for tally        4 with nps =     1000000  print table 160


 normed average tally per history  = 9.22198E-01          unnormed average tally per history  = 3.86290E+00
 estimated tally relative error    = 0.0007               estimated variance of the variance  = 0.0000
 relative error from zero tallies  = 0.0001               relative error from nonzero scores  = 0.0007

 number of nonzero history tallies =      985557          efficiency for the nonzero tallies  = 0.9856
 history number of largest  tally  =      644289          largest  unnormalized history tally = 2.27682E+01
 (largest  tally)/(average tally)  = 5.89408E+00          (largest  tally)/(avg nonzero tally)= 5.80896E+00

 (confidence interval shift)/mean  = 0.0000               shifted confidence interval center  = 9.22199E-01


 if the largest  history score sampled so far were to occur on the next history, the tfc bin quantities would change as follows:

      estimated quantities           value at nps           value at nps+1           value(nps+1)/value(nps)-1.

      mean                            9.22198E-01             9.22203E-01                     0.000005
      relative error                  6.73920E-04             6.73934E-04                     0.000020
      variance of the variance        1.69873E-06             1.70121E-06                     0.001461
      shifted center                  9.22199E-01             9.22199E-01                     0.000000
      figure of merit                 8.97160E+05             8.97123E+05                    -0.000041

 the estimated inverse power slope of the 200 largest  tallies starting at 1.53491E+01 is 7.1266
 the large score tail of the empirical history score probability density function appears to have no unsampled regions.

 fom = (histories/minute)*(f(x) signal-to-noise ratio)**2 = (4.075E+05)*( 1.484E+00)**2 = (4.075E+05)*(2.202E+00) = 8.972E+05

1    some tally scores were not made for various reasons:

                                  beyond last bin     not in
                   tally       user  segment   mult   angle   energy   time
                      4          0       0       0       0 1000001       0

1status of the statistical checks used to form confidence intervals for the mean for each tally bin


 tally   result of statistical checks for the tfc bin (the first check not passed is listed) and error magnitude check for all bins

        4   passed the 10 statistical checks for the tally fluctuation chart bin result
         missed all bin error check:   112 tally bins had     0 bins with zeros and    11 bins with relative errors exceeding 0.10


 the 10 statistical checks are only for the tally fluctuation chart bin and do not apply to other tally bins.

 warning.       1 of the     1 tallies had bins with relative errors greater than recommended.
1tally fluctuation charts

                            tally        4
          nps      mean     error   vov  slope    fom
        64000   9.2246E-01 0.0027 0.0000 10.0  881214
       128000   9.2161E-01 0.0019 0.0000 10.0  892405
       192000   9.2159E-01 0.0015 0.0000 10.0  893732
       256000   9.2187E-01 0.0013 0.0000 10.0  895412
       320000   9.2218E-01 0.0012 0.0000 10.0  895623
       384000   9.2231E-01 0.0011 0.0000 10.0  895445
       448000   9.2285E-01 0.0010 0.0000 10.0  895032
       512000   9.2299E-01 0.0009 0.0000 10.0  896204
       576000   9.2312E-01 0.0009 0.0000 10.0  897394
       640000   9.2313E-01 0.0008 0.0000 10.0  896065
       704000   9.2318E-01 0.0008 0.0000  8.0  896791
       768000   9.2297E-01 0.0008 0.0000  6.6  896975
       832000   9.2290E-01 0.0007 0.0000  6.3  896473
       896000   9.2258E-01 0.0007 0.0000  6.2  896981
       960000   9.2243E-01 0.0007 0.0000  7.6  897207
      1000000   9.2220E-01 0.0007 0.0000  7.1  897160

 ***********************************************************************************************************************

 dump no.    2 on file HydrogenSphereTemp2500_MCNP.ir     nps =     1000000     coll =      145929814     ctm =
 2.45   nrn =        2358307791
 tally data written to file HydrogenSphereTemp2500_MCNP.im

         3 warning messages so far.


 run terminated when     1000000  particle histories were done.

 computer time =    2.46 minutes

 mcnp     version 6     06/19/14                     08/26/15 18:35:54                     probid =  08/26/15 18:33:27
