set datafile separator ";"

set terminal pngcairo size 1280,720 enhanced font "Arial,12"
set output "dat/Exo2/plot/Exo2_train.png"

set title "Erreur/Nombre d'itérations"
set xlabel "Nombre d'itération"
set ylabel "Erreur"
set xrange [ * : * ] noreverse writeback
set yrange [ * : * ] noreverse writeback

set border behind

plot \
    "dat/Exo2/Exo2_0_train_output.csv" using 1:2 with linespoints title "Reconnaissance du 0", \
    "dat/Exo2/Exo2_1_train_output.csv" using 1:2 with linespoints title "Reconnaissance du 1"
