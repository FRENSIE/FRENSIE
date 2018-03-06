Albedo analysis of a 300cm x 300cm x 30 cm slab of Aluminum
c
c
c -----------------------------------------------------------------------------c
c Cell block-------------------------------------------------------------------c
c -----------------------------------------------------------------------------c
c
c Cell 10 is the volume of iron portland concrete that is doing the shielding
10  1  -2.6989  100 -101 102 -103 104 -105    IMP:e=1   IMP:p=1
c Cell 20 is a void
20  0  200 -201 202 -203 204 -205 #10       IMP:e=1   IMP:p=1
c Cell 30 is the graveyard 
30  0  #20 #10                              IMP:e=0   IMP:p=0
c
c
c ----------------------------------------------------------------------------c
c MCNP necessary space--------------------------------------------------------c
c ----------------------------------------------------------------------------c

c ----------------------------------------------------------------------------c
c Surface block---------------------------------------------------------------c
c ----------------------------------------------------------------------------c
c
c the 100 series define the inner cube made of iron portland concrete
c
100 PX -15.0
101 PX 15.0
102 PY -150
103 PY 150
104 PZ -150
105 PZ 150
c 
c the 200 series define the middle cube filling a void
c 
200 PX -25
201 PX 25
202 PY -160
203 PY 160
204 PZ -160
205 PZ 160
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
m1    13000.12p  1.0
c
c
c --------------------
c Source
c --------------------
c monodirectional, monoenergetic 2.45 MeV point source located
c just before the the edge of the shield
SDEF  ERG=0.005 POS=-20 0 0 DIR=1 VEC=1 0 0 PAR=e
c --------------------
c Job Control
c --------------------
c run in electron only mode
mode p e
c run for 100 histories
nps 1e6
c Surface current on front surface
f11:e 100
c11  0.99 1
c
c Surface current on back surface
f21:e 101
c21  0.99 1
c
F4:e  10
E4 1e-3 99ilog 0.005
dbcn 17j 2
CUT:P J 1.0e-02 $ Set photon cutoff to 10 eV
CUT:E J 1.5e-05 $ Set electron cutoff to 15 eV
PHYS:E 0.01 1 1 1 10J 0.1
prdmp  j  1e7  1   1
