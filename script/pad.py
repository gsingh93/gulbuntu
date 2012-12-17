import io
import os

kernelsize = os.path.getsize("Final Files/pad2")
padsize = os.path.getsize("Final Files/kernel.bin")
if(1474560-102400-kernelsize-padsize != 0):
    f = open("Final Files/pad2", "w")
    for i in range(0,1474560-1024-kernelsize):
        f.write("0")
    print "Pad Changed"	
	