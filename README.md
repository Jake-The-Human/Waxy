# Waxy

## Build
```
cmake -B build -DFAMILY=rp2040 -DBOARD=feather_rp2040_max3421
cmake --build build --config Release
```
## Future thinks
- interchangeable dac modules
- Balanced output (with custom pcb)
- coax input
- network input (AES67)? (might need to switch to rpi)