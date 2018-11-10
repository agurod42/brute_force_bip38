# brute_force_bip38

C++ implementation of the brute-force decoder of BIP38 encrypted private keys written by [countzero/brute_force_bip38](https://github.com/countzero/brute_force_bip38.git).

## Build

```bash
./scripts/build.sh
```

## Configuration

1. Edit the [config.txt](./config.txt) with the `publicAddressHex` (in hex format) and the `encryptedPrivateKey` (BIP38 encoded private key) you know.
2. Edit the [secrets.txt](./secrets.txt) file with all secrets you want to test.

## Start

```bash
./build/brute_force_bip38
```

The application will now utilize all available CPUs to test each secret against your BIP38 encoded private key. If a valid secret has been found it will be logged out to [valid_secret.txt](./valid_secret.txt).

## Performance

Tested with [500-worst-passwords.txt](https://github.com/danielmiessler/SecLists/raw/master/Passwords/Common-Credentials/500-worst-passwords.txt) on this computer:

```
CPUs	        Intel(R) Core(TM) i5-7360U CPU @ 2.30GHz (4 x 2300)
GPU Status      2d_canvas: enabled
                checker_imaging: disabled_off
                flash_3d: enabled
                flash_stage3d: enabled
                flash_stage3d_baseline: enabled
                gpu_compositing: enabled
                multiple_raster_threads: enabled_on
                native_gpu_memory_buffers: enabled
                rasterization: enabled
                video_decode: enabled
                video_encode: enabled
                webgl: enabled
                webgl2: enabled
Load (avg)      8, 11, 8
Memory (System)	8.00GB (0.17GB free)
VM              0%
```

### Results

implementation | total processing time | processing time per secret
---------------|-----------------------|------------------------------
C++            | 337.219 seconds       | 0.675789 seconds (2x faster)
JS             | 755.20 seconds        | 1.51 seconds
