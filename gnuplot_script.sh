for FILE in *.txt; do
	gnuplot <<- EOF
		set xlabel "Label1"
		set ylabel "Label12"
		set term png
		set output "${FILE}.png"
		plot "${FILE}" u 1:2 title "GE11_1" w lp,\
		 "${FILE}" u 1:3 title "GE11_2" w lp,\
		 "${FILE}" u 1:4 title "GE11_3" w lp
	EOF
done
echo "congrats"
