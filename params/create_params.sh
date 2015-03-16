for param in $(ls 2??)
do
#    cp $param m$param
    cp $param p$param
    cp $param s$param
#    sed -i '1idataset:metaphor' m$param
    sed -i '1idataset:sentiment' p$param
    sed -i '1idataset:subjectivity' s$param
done
