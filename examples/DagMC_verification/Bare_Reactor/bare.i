Subcritical Bare Reactor Problem
c
c
c -----------------------------------------------------------------------------c
c Cell block-------------------------------------------------------------------c
c -----------------------------------------------------------------------------c
c
10  1  -18.9  -100                         IMP:n=1  IMP:p=1
20  0  -200 201 -202 203 -204 205 100      IMP:n=1  IMP:p=1
30  0  #20         IMP:n=0  IMP:p=0
c
c
c
c ----------------------------------------------------------------------------c
c MCNP necessary space--------------------------------------------------------c
c ----------------------------------------------------------------------------c

c ----------------------------------------------------------------------------c
c Surface block---------------------------------------------------------------c
c ----------------------------------------------------------------------------c
c surface 100 is the inner sphere, the 200 series is the terminal cube
100  SO   5
200  PX  10
201  PX -10
202  PY  10
203  PY -10
204  PZ  10
205  PZ -10
c
c
c
c
c
c ----------------------------------------------------------------------------c
c MCNP necessary space--------------------------------------------------------c
c ----------------------------------------------------------------------------c

c ----------------------------------------------------------------------------c
c Data block------------------------------------------------------------------c
c ----------------------------------------------------------------------------c
c
c
c Material Definition
c
m1   92235.80c 1.00
     92238.80c 0.05
c
c
c --------------------
c Source
c --------------------
c isotropic 14 MeV point source at the origin
SDEF ERG=2.0 PAR=1
c --------------------
c Job Control
c --------------------
c run in neutron only mode
mode n
c Control the physics for the photons: 
c Above 100 MeV treat as simple physics, Include
c Bremsstrahlung, include coherent scattering, don't use photonuclear 
c interactions, no Doppler broadening. 
PHYS:N 2j 1 2j      $ Line Alex had me add
c 
c run for 1000000 histories
nps 1e7
c Flux Tallies for the neutrons
f4:n 10
E4 1e-5 99ilog 4
