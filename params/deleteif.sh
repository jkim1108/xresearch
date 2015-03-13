for i in $(ls 1??)
do 
    if [ $i -gt 112 ]
    then 
	rm $i
    fi
done
