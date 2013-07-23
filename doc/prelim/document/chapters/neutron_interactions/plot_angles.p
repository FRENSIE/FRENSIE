#set terminal post eps enh color
#set output "lab_and_cm_scattering_angles.eps"
set terminal epslatex
set output "lab_and_cm_scattering_angles.tex"
set xlabel "CM Scattering Angle Cosine"
set ylabel "Lab Scattering Angle Cosine"
set format x "%2.1f"
set format y "%2.1f"
unset key
set grid
set xrange[-1:1]
set yrange[-1:1]
set label 1 "$E^{'} < \\frac{AQ}{A-1}$" at -0.8, 0.8
set label 2 "$E^{'} = \\frac{AQ}{A-1}$" at -0.88, 0.18
set label 3 "$E^{'} > \\frac{AQ}{A-1}$" at -0.36, 0.15
f(a,x) = sqrt(1-(a+1)/(a*x))
g(a,x,u) = (a*f(a,x)*u + 1)/sqrt(a**2*f(a,x)**2+2*a*f(a,x)*u+1)
set sample 10000
plot [u = -0.999999999999:1] g(2.0,1.75,u) lc rgb"red" lt 2 lw 1, g(2.0,2.0,u) lc rgb"black" lt 1 lw 1, g(2.0,5.0,u) lc rgb"blue" lt 2 lw 1