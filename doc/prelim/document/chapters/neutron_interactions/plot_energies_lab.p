#set terminal post eps enh color
#set output "incoming_outgoing_energies_lab_angle.eps"
set terminal epslatex
set output "incoming_outgoing_energies_lab_angle.tex"
set lmargin 6
set xlabel "Incoming Energy" 
set ylabel "Outgoing Energy" 
set format x "%0.0f"
set format y "%0.0f"
unset key
set grid
b = 2.0
ulim = 3.0
llim = (b+1.0)/b
mlim = b/(b-1.0)
set xrange[0.0:ulim]
set xtics ("$\\frac{A+1}{A}Q$" llim, "$\\frac{A}{A-1}Q$" mlim)
set yrange[0.0:1.0]
unset ytics
set label 1 "$^{\\mu_{l} = -1}$" at 2.8, 0.015
set label 2 "$\\mu_{l} = -\\frac{1}{2}$" at 2.7, 0.16
set label 3 "$\\mu_{l} = 0$" at 2.6, 0.3
set label 4 "$\\mu_{l} = \\frac{1}{2}$" at 2.3, 0.62
set label 5 "$\\mu_{l} = 1$" at 1.7, 0.85
set label 6 "0" at 1.46,0.01
f(a,x)	     = sqrt(1-(a+1)/(a*x))
vp(a,x,u)    = -(1-u**2)/(a*f(a,x)) + u/(a*f(a,x))*sqrt(u**2 - 1 + a**2*f(a,x)**2)
vn(a,x,u)    = -(1-u**2)/(a*f(a,x)) - u/(a*f(a,x))*sqrt(u**2 - 1 + a**2*f(a,x)**2)
gp(a,x,u)    = u < 0.0 && x < mlim ? 0.0 : x*(a**2*f(a,x)**2+2*a*f(a,x)*vp(a,x,u)+1)/(a+1)**2
gn(a,x,u) = u > 0.0 && x > mlim ? 0.0 : x*(a**2*f(a,x)**2+2*a*f(a,x)*vn(a,x,u)+1)/(a+1)**2
set samples 100000
plot [x   = llim:ulim] gp(2.0,x,-1.0) lc rgb"red" lt 2 lw 1, gp(2.0,x,-0.5) lc rgb"blue" lt 4 lw 2, gp(2.0,x,0.0) lc rgb"black" lt 1 lw 1, gp(2.0,x,0.5) lc rgb"purple" lt 4 lw 3, gn(2.0,x,0.5) lc rgb"purple" lt 4 lw 3, gp(2.0,x,1.0) lc rgb"green" lt 2 lw 1, gn(2.0,x,1.0) lc rgb"green" lt 2 lw 1
#plot [x     = llim:ulim] g(b,x,-1.0) lc rgb"red" lt 2 lw 1, g(b,x,-0.5) lc rgb"blue" lt 4 lw 2, g(b,x,0.0) lc rgb"black" lt 1 lw 1, g(b,x,0.5) lc rgb"purple" lt 4 lw 3, g(b,x,1.0) lc rgb"green" lt 2 lw 1
