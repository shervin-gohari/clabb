set terminal png size 1024,768
set output 'resultat/kollisioner.png'
set key outside center top horizontal
set xlabel 'hashvärde'
set ylabel 'antal kollisioner'
set datafile separator '\t'
plot 'resultat/' . hashfunktion . '-kollisioner.dat' u 1:2 w p title columnheader(1)

reset

set terminal png size 1024,768
set output 'resultat/uppslagning.png'
set key left
set xlabel 'antal insatta element i hashtabellen'
set ylabel 'tid för uppslagning (s)'
set datafile separator '\t'
plot 'resultat/' . hashfunktion . '-uppslagning.dat' u 1:2 w p title columnheader(1)


reset

set terminal png size 1024,768
set output 'resultat/uppslagningar.png'
set key left
set xlabel 'antal uppslagningar'
set ylabel 'tid (s)'
set datafile separator '\t'
plot 'resultat/' . hashfunktion . '-uppslagningar.dat' u 1:2 w p title columnheader(1)
