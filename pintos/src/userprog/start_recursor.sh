make -j4
cd  build
pintos-mkdisk fs.dsk 400
pintos --qemu -v -- -f -q
pintos --qemu -v -p ../../examples/recursor_ng -a recursor_ng --  -q
pintos --qemu -v -m 128 -- run "recursor_ng pintosmaster 6 1"
