#!/bin/bash


cd src/

cp MakefileExo3 Makefile

if ! make; then
exit 1 ;
fi

echo "Purge du directory dat/"
cd ../dat/Exo3/

rm Exo3_*output.csv

cd ../../bin/
./exo3

echo "Ploting....."

cd ..
gnuplot -p gnuplot/Ex3.plot-err.gnu
gnuplot -p gnuplot/Ex3.plot-noise.gnu
gnuplot -p gnuplot/Ex3.plot-noise_common.gnu

echo "Fin du shell"

