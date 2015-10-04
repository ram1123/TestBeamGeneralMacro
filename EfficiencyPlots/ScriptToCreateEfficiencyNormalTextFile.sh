awk 'BEGIN {FS = "_" }; {print $6}' $1.txt | sed 's/pt/./g' > temp1.txt
awk 'BEGIN {FS = "+" }; {print $1}' $1.txt | awk '{print $2}' > temp2.txt
awk 'BEGIN {FS = "-" }; {print $2}' $1.txt | awk '{print $1}' > temp3.txt
paste -d "\t" temp1.txt temp2.txt temp3.txt > $1_GE11_IV_GIF.txt

awk 'BEGIN {FS = "_" }; {print $7}' $1.txt | sed 's/pt/./g' > temp1.txt
awk 'BEGIN {FS = "+" }; {print $2}' $1.txt | awk '{print $2}' > temp2.txt
awk 'BEGIN {FS = "-" }; {print $3}' $1.txt | awk '{print $1}' > temp3.txt
paste -d "\t" temp1.txt temp2.txt temp3.txt > $1_GE11_IV.txt

awk 'BEGIN {FS = "_" }; {print $8}' $1.txt | sed 's/pt/./g' > temp1.txt
awk 'BEGIN {FS = "+" }; {print $3}' $1.txt | awk '{print $2}' > temp2.txt
awk 'BEGIN {FS = "-" }; {print $4}' $1.txt | awk '{print $1}' > temp3.txt
paste -d "\t" temp1.txt temp2.txt temp3.txt > $1_GE11_V.txt
