### README.md for Your Encryption CLI Tool

# Encryption CLI Tool

This command-line interface (CLI) tool offers a simple yet powerful means to encrypt and decrypt messages using the PP256 encryption algorithm. Designed for educational purposes, it provides insights into the workings of symmetric encryption, including options for Base64 encoding/decoding and SHA256 hashing.

## Features

- **Symmetric Encryption**: Utilize the PP256 algorithm for encrypting and decrypting messages.
- **Base64 Encoding/Decoding**: Option to encode encrypted output or decode input using Base64, making it easy to handle binary data.
- **SHA256 Hashing**: Secure your encryption keys with SHA256 hashing, ensuring they are robust and resistant to brute-force attacks.
- **Flexible Input**: Accepts input directly from the command line or from `stdin`, facilitating the use of pipes and redirection in Unix-like environments.

## Installation

Clone the repository to your local machine:

```
git clone https://github.com/yourusername/encryption-cli-tool.git
```

Compile the program (ensure you have GCC or an equivalent compiler installed):

```
gcc -o encryption-cli main.c -lencrypt -lsha256 -lbase64
```

## Usage

The tool supports several command-line options for customizing the encryption process:

```
encryption-cli [-b --base64] [-p --password] [-i --input] [-e --encryption] [-d --digest]
```

### Options

- `-b`, `--base64`: Enable Base64 encoding for the output or decoding for the input.
- `-p`, `--password`: Specify the password used for encryption or decryption.
- `-i`, `--input`: Direct input string to be encrypted or decrypted. If omitted, the program reads from `stdin`.
- `-e`, `--encryption`: Choose the encryption function (currently supports `xor` only).
- `-d`, `--digest`: Select the digest algorithm for hashing the encryption key (currently supports `SHA256` only).

### Examples

Encrypt a message:

```
echo "Hello World" | ./encryption-cli -p mypassword -b
```

Decrypt a message (assuming the encrypted message is Base64 encoded):

```
echo "SGVsbG8gV29ybGQ=" | ./encryption-cli -p mypassword -b -d
```

## Supported Encryption Functions and Digest Algorithms

### Encryption Functions

- `xor`: The only available encryption method, implementing a simple XOR cipher for educational purposes.

### Digest Algorithms

- `SHA256`: The sole supported digest algorithm, used for hashing the encryption key to enhance security.

## Contributing

We welcome contributions from the community, including bug fixes, documentation improvements, and feature enhancements. Please fork the repository and submit a pull request with your changes.

## License

This project is open-sourced under the MIT License. See the LICENSE file for more details.

## Disclaimer

This tool is intended for educational purposes only and should not be used for securing sensitive or production data.
