# brute_force_bip38

A brute-force decoder of BIP38 encoded private keys written in C++, heavily inspired by [countzero/brute_force_bip38](https://github.com/countzero/brute_force_bip38.git).

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

The application will now utilize all available CPUs to test each secret against your BIP38 encoded private key. If a valid secret has been found it will be logged out to [valid_secret.json](./valid_secret.txt).

## Performance

