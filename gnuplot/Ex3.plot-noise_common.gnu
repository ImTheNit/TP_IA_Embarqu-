set datafile separator ";"

set terminal pngcairo size 1280,720 enhanced font "Arial,12"
set output "dat/Exo3/plot/Exo3_noise_only_common.png"

set title "reconnaissance correcte globale/Pourcentage de bruit"
set xlabel "Bruit"
set ylabel "% reconnaissance correcte"
set xrange [ * : * ] noreverse writeback
set yrange [ * : * ] noreverse writeback

set border behind

plot \
    "dat/Exo3/Exo3_common_noise_output.csv" using 1:2 with linespoints title "Reconnaissance globale" 
