Gulbuntu OS
===========

This is an operating system kernel I wrote back in High School. Currently, the only two things you can do are display help and clear the screen, but I may begin working on this project again soon.

### Building

To build, simply type `make`. This will generate the `kernel.bin` file in the `intermediate` directory.

### Running

Before emulating the kernel, we'll first make an image file. First create an environment variable called GULBUNTU_ROOT that points to the project root directory. You may want to put this in your `.bashrc`.

`export GULBUNTU_ROOT=/path/to/root/directory/`

Then type the following command:

`scripts/package.sh`

**Note: You may have to make the Bash script executable by running `chmod +x scripts/*.sh`**

Now we should have a floppy.img file in the `bin` folder. This image can be burned onto a CD, but we'll be emulating it using Qemu.

To install Qemu using apt-get, type the following command:

`sudo apt-get install qemu`

You can see the Qemu binaries that were installed by typing `qemu` and then pushing tab. On my 64-bit system I would use qemu-system-x86_64. Run the following command, replace the Qemu binary with the appropriate one for your system.

`qemu-system-x86_64 bin/floppy.img`

Qemu should boot into Grub. In Grub, type `kernel 200+50` (Note that 50 technically isn't the correct number here, but it works. I'll figure out the actual number eventually). After this type `boot` and the OS should start.