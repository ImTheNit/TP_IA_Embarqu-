set datafile separator ";"

set terminal pngcairo size 1280,720 enhanced font "Arial,12"
set output "dat/Exo2/plot/Exo2_noise.png"

set title "reconnaissance correcte/Pourcentage de bruit"
set xlabel "Bruit"
set ylabel "% reconnaissance correcte"
set xrange [ * : * ] noreverse writeback
set yrange [ * : * ] noreverse writeback

set border behind

plot \
    "dat/Exo2/Exo2_0_noise_output.csv" using 1:2 with linespoints title "Reconnaissance du 0" , \
    "dat/Exo2/Exo2_1_noise_output.csv" using 1:2 with linespoints title "Reconnaissance du 1" , \
    "dat/Exo2/Exo2_common_noise_output.csv" using 1:2 with linespoints title "Reconnaissance globale" 
