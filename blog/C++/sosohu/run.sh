echo "#C++ Primer 读书笔记" > README.md
for (( i=1; i<16; i++)); do
	head "chap$i.md" -n 1 >> README.md
done

cat README.md | awk '(NR < 2){print $0} (NR > 1){ print "**Chapter "NR-1".**[*"$1"*](chap"NR-1".md)\n"}' > tmp
mv tmp README.md
