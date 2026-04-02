set datafile separator ";"

set terminal pngcairo size 1280,720 enhanced font "Arial,12"
set output "dat/Exo3/plot/Exo3_train.png"

set title "Erreur/Nombre d'itérations"
set xlabel "Nombre d'itération"
set ylabel "Erreur"
set xrange [ * : * ] noreverse writeback
set yrange [ * : * ] noreverse writeback

set border behind

plot \
    "dat/Exo3/Exo3_0_train_output.csv" using 1:2 smooth csplines with lines title "Reconnaissance du 0", \
    "dat/Exo3/Exo3_1_train_output.csv" using 1:2 smooth csplines with lines title "Reconnaissance du 1", \
    "dat/Exo3/Exo3_2_train_output.csv" using 1:2 smooth csplines with lines title "Reconnaissance du 2", \
    "dat/Exo3/Exo3_3_train_output.csv" using 1:2 smooth csplines with lines title "Reconnaissance du 3", \
    "dat/Exo3/Exo3_4_train_output.csv" using 1:2 smooth csplines with lines title "Reconnaissance du 4", \
    "dat/Exo3/Exo3_5_train_output.csv" using 1:2 smooth csplines with lines title "Reconnaissance du 5", \
    "dat/Exo3/Exo3_6_train_output.csv" using 1:2 smooth csplines with lines title "Reconnaissance du 6", \
    "dat/Exo3/Exo3_7_train_output.csv" using 1:2 smooth csplines with lines title "Reconnaissance du 7", \
    "dat/Exo3/Exo3_8_train_output.csv" using 1:2 smooth csplines with lines title "Reconnaissance du 8", \
    "dat/Exo3/Exo3_9_train_output.csv" using 1:2 smooth csplines with lines title "Reconnaissance du 9"
