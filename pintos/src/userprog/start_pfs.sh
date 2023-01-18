make -j4
cd build
pintos-mkdisk fs.dsk 800
dd if=/dev/urandom of=random bs=1 count=100
pintos --qemu -v -- -f -q
pintos --qemu -v -p random -a random --  -q
pintos --qemu -v -p ../../examples/pfs -a pfs --  -q
pintos --qemu -v -p ../../examples/pfs_writer -a pfs_writer --  -q
pintos --qemu -v -p ../../examples/pfs_reader -a pfs_reader --  -q
pintos --qemu -v -- run pfs
