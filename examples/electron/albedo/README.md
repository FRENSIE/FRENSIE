## Aluminum albedo experiment ##

# Experimental
The reflection coefficient in a semi-infinite slab Al is measured at various
energies.

# Setup
Surface current estimator with cosines bin (-1.0, -0.99, 0.0, 1.0).
For Al make the infinite slab 30 cm long

## Trelis geometry commands
brick x 60.0 y 60.0 z 30.0
move volume 1 x 0.0 y 0.0 z 15.0

brick x 61.0 y 61.0 z 31.0
brick x 62.0 y 62.0 z 32.0
subtract volume 2 from volume 3
move volume 4 x 0.0 y 0.0 z 15.0

imprint body all
merge tol 5e-7
merge all
group "termination.cell" add vol 4
group "material_1_density_-2.6989" add vol 1
group "estimator_1.surface.current.e" add surface 1, 2
group "estimator_2.cell.tl.flux.e" add vol 1
group "reflecting.surface" add surface 3 to 6
export dagmc "path-to-albedo/Al/geom.h5m" faceting_tolerance 1.e-5 make_watertight

# Running the simulation

run `python -c "import albedo; albedo.runSimulation( 2, 1000, 1000 )"`

**Note**: parameter 1 = threads, parameter 2 = num particles, parameter 3 = max run time

# Plotting results