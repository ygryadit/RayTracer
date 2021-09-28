FRAMES=180

for i in `seq 90 $FRAMES` ; do
    echo "Rendering frame $i"
    ./graphics 1 $i
done
