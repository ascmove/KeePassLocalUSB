This project aims to backup kdbx file of [KeePass](https://keepass.info/) to your local USB device on Windows platform.You can use the Windows task schedule to automate this operation.

By participating, you are expected to uphold this code. Please report unacceptable
behavior to [ascmove@gmail.com](mailto:ascmove@gmail.com).

## Bulid

To build binaries, use [`cmake`](https://www.cmake.org/).
I offer a pre-build binary file in `/release` folder:

## Quick start
Both `config.ini` and `version.ini` should be put under the same folder with the main progeam `KeePassLocalUSB.exe`.

- `config.ini` Configuration for source file and destination file.
```sh
from=C:\Users\ching\OneDrive\PasswordsDB\PwdDB.kdbx
to=G:\KeePass\PwdDB.kdbx
```
- `version.ini` Record version change information.
```sh
2019151329
```
## Usage
You can use the Windows task schedule to automate this operation.

## License

[MIT](https://github.com/ascmove/KeePassLocalUSB/blob/master/LICENSE)