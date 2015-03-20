for param in $(ls 6??)
do
#    cp $param m$param
    cp $param p$param
    cp $param s$param
    cp $param ab$param
    cp $param ak$param
    cp $param ae$param
    cp $param ad$param
#    sed -i '1idataset:metaphor' m$param
    sed -i '1idataset:sentiment' p$param
    sed -i '1idataset:subjectivity' s$param
    sed -i '1idataset:books' ab$param
    sed -i '1idataset:kitchen_housewares' ak$param
    sed -i '1idataset:electronics' ae$param
    sed -i '1idataset:dvd' ad$param
#
done
