INTERMEDIATE_DIR=$GULBUNTU_ROOT/intermediate

c1="stat -c%s $INTERMEDIATE_DIR/pad2"
c2="stat -c%s $INTERMEDIATE_DIR/kernel.bin"
kernel_size=$($c1) 
pad_size=$($c2)
if [[ 1474560-102400-$kernel_size-$pad_size -ne 0 ]]; then
    for i in {0..1474560-1024-$kernel_size}; do
	echo 0 >> $INTERMEDIATE_DIR/pad2;
    done
    echo "Pad Changed"
fi