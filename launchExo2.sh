#!/bin/bash


cd src/

cp MakefileExo2 Makefile

if ! make; then
exit 1 ;
fi

echo "Purge du directory dat/"
cd ../dat/Exo2/

rm Exo2_*output.csv

cd ../../bin/
./exo2

echo "Ploting....."

cd ..
gnuplot -p gnuplot/Ex2.plot-err.gnu
gnuplot -p gnuplot/Ex2.plot-noise.gnu
gnuplot -p gnuplot/Ex2.plot-noise_common.gnu

echo "Fin du shell"

