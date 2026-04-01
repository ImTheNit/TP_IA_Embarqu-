#!/bin/bash


cd src/

cp MakefileExo1 Makefile

if ! make; then
exit 1 ;
fi

echo "Purge du directory dat/"
cd ../dat/Exo1/

rm Exo1_*output.csv

cd ../../bin/
./exo1

echo "Ploting....."

cd ..
gnuplot -p gnuplot/Ex1.plot-err.gnu
gnuplot -p gnuplot/Ex1.plot-noise.gnu
gnuplot -p gnuplot/Ex1.plot-noise_common.gnu

echo "Fin du shell"

