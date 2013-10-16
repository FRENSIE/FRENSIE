set terminal post eps enh color
set output "photon_spectrum_validation_comparison_difference.eps"
set xlabel "Percent Difference"
set ylabel "Frequency"
set format x "%2.1f"
set format y "%2.1f"
unset key
set grid
n = 50
max = 10.0
min = -10.0
width = (max-min)/n
hist(x,width) = width*floor(x/width)+width/2.0
set xrange[min:max]
set yrange[0:]
set boxwidth width*0.95
set style fill solid 0.5
set xtics out nomirror
plot "validation_results/comparison_data-10cm" using (hist(($5-$2)/$2*100,width)):1.0 smooth freq w boxes lc rgb"red"
