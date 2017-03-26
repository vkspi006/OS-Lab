set output 'graph.png'
set terminal png

set xrange[0: ]
set yrange[0: ]

plot 'out.txt' with linespoints
