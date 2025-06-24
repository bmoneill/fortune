# A simple fortune implementation

This is a simple [fortune(6)](https://linux.die.net/man/6/fortune)
implementation that supports the same file formats as the standard
Linux/BSD versions. In addition, you may specify a custom fortune file
and separator.

## Installation

```
make
sudo make install
```

## Usage

```
fortune [file] [separator]
```

Default separator is `'\n'`.

## Further Reading

* [fortune.c on UNIX V7](https://www.tuhs.org/cgi-bin/utree.pl?file=V7/usr/src/games/fortune.c)

## License

Copyright (c) 2022-2025 Ben O'Neill <ben@oneill.sh>. Licensed under the
MIT License. See LICENSE.