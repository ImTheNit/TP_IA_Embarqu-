set datafile separator ";"

set terminal pngcairo size 1280,720 enhanced font "Arial,12"
set output "dat/Exo3/plot/Exo3_noise.png"

set title "reconnaissance correcte/Pourcentage de bruit"
set xlabel "Bruit"
set ylabel "% reconnaissance correcte"
set xrange [ * : * ] noreverse writeback
set yrange [ * : * ] noreverse writeback

set border behind




plot \
    "dat/Exo3/Exo3_0_noise_output.csv" using 1:2 with linespoints title "Reconnaissance du 0" , \
    "dat/Exo3/Exo3_1_noise_output.csv" using 1:2 with linespoints title "Reconnaissance du 1" , \
    "dat/Exo3/Exo3_2_noise_output.csv" using 1:2 with linespoints title "Reconnaissance du 2" , \
    "dat/Exo3/Exo3_3_noise_output.csv" using 1:2 with linespoints title "Reconnaissance du 3" , \
    "dat/Exo3/Exo3_4_noise_output.csv" using 1:2 with linespoints title "Reconnaissance du 4" , \
    "dat/Exo3/Exo3_5_noise_output.csv" using 1:2 with linespoints title "Reconnaissance du 5" , \
    "dat/Exo3/Exo3_6_noise_output.csv" using 1:2 with linespoints title "Reconnaissance du 6" , \
    "dat/Exo3/Exo3_7_noise_output.csv" using 1:2 with linespoints title "Reconnaissance du 7" , \
    "dat/Exo3/Exo3_8_noise_output.csv" using 1:2 with linespoints title "Reconnaissance du 8" , \
    "dat/Exo3/Exo3_9_noise_output.csv" using 1:2 with linespoints title "Reconnaissance du 9" 
