#!/bin/sh
NB_THREADS=10
RADIUS=20
DAT_FILE=ex3.dat
OUT_FILE=./TP_MPI_ex3b.out
SVG_FILE=ex3_scalability.svg

if [ -f $DAT_FILE ]
then
    rm $DAT_FILE
fi

for i in `seq $NB_THREADS`
do
    echo "calcul avec $i threads..."
    mpirun -n $i $OUT_FILE $RADIUS $i 1 >> $DAT_FILE
done

echo "generation et affichage des resultats..."
T1=`head -n 1 $DAT_FILE | awk '{print $3}'`
gnuplot -e "set out '$SVG_FILE'; \
    set terminal svg; \
    set yrange [1:$NB_THREADS]; \
    set style data linespoints; \
    set grid xtics ytics; \
    set key top left; \
    plot '$DAT_FILE' using 1:1 title 'speed-up ideal', '$DAT_FILE' using 1:($T1/\$3) title 'speed-up mesuré'"

display $SVG_FILE

