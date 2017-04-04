# Interrupt-Driver

## Usage

Setup device major, minor numbers and addresses on I2C bus within source file.

Download your linux kernel: (https://www.kernel.org), where the version is `linux-x.y.z`.

Uncompress and untar the file

`$ tar xvjf linux-x.y.z.tar.bz2`

If it is compressed with GNU zip, run

`$ tar xvzf linux-x.y.z.tar.gz`

Make the max3107 driver with the kernel tree with the handy Makefile

`$ make`
