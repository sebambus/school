start: Rplots.pdf
	open Rplots.pdf

Rplots.pdf: prog
	./prog
	Rscript compplot.r

prog: main.cpp slp.cpp matrix.cpp vectorops.cpp csvtools.cpp compplot.r
	g++ main.cpp slp.cpp matrix.cpp vectorops.cpp csvtools.cpp -o prog