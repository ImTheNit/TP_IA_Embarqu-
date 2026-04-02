set datafile separator ";"

set terminal pngcairo size 1280,720 enhanced font "Arial,12"
set output "dat/Exo1/plot/Exo1_train.png"

set title "Erreur/Nombre d'itérations"
set xlabel "Nombre d'itération"
set ylabel "Erreur"
set xrange [ * : * ] noreverse writeback
set yrange [ * : * ] noreverse writeback

set border behind

set terminal pngcairo size 1280,720 enhanced font "Arial,12"

plot \
    "dat/Exo1/Exo1_0_train_output.csv" using 1:2 with linespoints title "Reconnaissance du 0", \
    "dat/Exo1/Exo1_1_train_output.csv" using 1:2 with linespoints title "Reconnaissance du 1"
