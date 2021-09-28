FRAMES=300

for i in `seq 1 $FRAMES` ; do
    echo "Rendering frame $i"
    ./graphics 0 $i
done
