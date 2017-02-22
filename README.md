## fs-uae-redpill v0.1
Redpill for the Commodore Amiga emulator FS-UAE

#### Platform
linux x86_64

#### Download
```bash
git clone -b fs-uae-2.8.3-redpill --depth 1 https://github.com/mathfigure/fs-uae
```

#### Build
```bash
cd fs-uae
./bootstrap
./configure LIBS=-lrt
make -j $(nproc)
```

#### Edit the config file
```bash
leafpad Config.fs-uae
```

#### Run
```bash
./fs-uae

# check the memory map
grep "K/" ~/Documents/FS-UAE/Cache/Logs/fs-uae.log.txt 
```

#### Test
```bash
ls -l /dev/shm  # check shared memory names and sizes, and use below
hexedit /dev/shm/'Chip memory'
ffplay /dev/shm/'Slow memory' -f rawvideo -video_size 1024x512 -pixel_format gray -framerate 50 -loop 0
gst-launch-1.0 multifilesrc location=/dev/shm/'Chip memory' ! videoparse width=1024 height=1024 framerate=50 format=25 ! videoconvert dither=0 ! videoscale method=0 ! ximagesink
```