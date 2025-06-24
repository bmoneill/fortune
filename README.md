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

## Bugs

If you find a bug, submit an issue, PR, or email me with a description and/or patch.

## License

Copyright (c) 2022-2025 Ben O'Neill <ben@oneill.sh>. This work is released under the
terms of the MIT License. See [LICENSE](LICENSE) for the license terms.
