for i in {101..112}
do
    sed '3s/.*/lambda:0.66/' $i > $((i+24))
done
