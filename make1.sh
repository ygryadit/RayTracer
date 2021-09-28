FRAMES=100

for i in `seq 1 $FRAMES` ; do
    echo "Rendering frame $i"
    ./graphics 1 $i
done
