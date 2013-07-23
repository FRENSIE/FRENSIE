#set terminal post eps enh color
#set output "incoming_outgoing_energies_cm_angle.eps"
set terminal epslatex
set output "incoming_outgoing_energies_cm_angle.tex"
set lmargin 6
set xlabel "Incoming Energy" 
set ylabel "Outgoing Energy" offset 9.2,0 
set format x "%0.0f"
set format y "%0.0f"
unset key
set grid
b = 2.0
ulim = 3.0
llim = (b+1.0)/b
set xrange[0.0:ulim]
set xtics ("$\\frac{A+1}{A}Q$" llim, "$\\frac{A}{A-1}Q$" b/(b-1.0))
set yrange[0.0:1.0]
set ytics ("$\\frac{Q}{A(A+1)}$" 1.0/(b*(b+1.0))) offset 1,0
set label 1 "$\\mu_{cm} = -1$" at 2.7, 0.08
set label 2 "$\\mu_{cm} = -\\frac{1}{2}$" at 2.7, 0.4
set label 3 "$\\mu_{cm} = 0$" at 2.55, 0.73
set label 4 "$\\mu_{cm} = \\frac{1}{2}$" at 2.25, 0.85
set label 5 "$\\mu_{cm} = 1$" at 1.7, 0.86
set label 6 "0" at 1.46,0.01
f(a,x)	 = sqrt(1-(a+1)/(a*x))
g(a,x,u) = x*(a**2*f(a,x)**2+2*a*f(a,x)*u+1)/(a+1)**2
set samples 10000
plot [x	 = llim:ulim] g(b,x,-1.0) lc rgb"red" lt 2 lw 1, g(b,x,-0.5) lc rgb"blue" lt 4 lw 2, g(b,x,0.0) lc rgb"black" lt 1 lw 1, g(b,x,0.5) lc rgb"purple" lt 4 lw 3, g(b,x,1.0) lc rgb"green" lt 2 lw 1
