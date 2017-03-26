for((i=$1; i<$2; i++))
do
	echo "File Contents" > fileNo#$i.txt
	for((j=0;j<100;j++))
	do
	echo "contents of File No ## "$i >> fileNo#$i.txt
	done
done
