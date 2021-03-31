# Hobby ANSI Parser
An ANSI Parser for hobbyist OS!

Making your own kernel? Want to get those legendary '\\033[1;31m'?
Hobby ANSI Parser is here to help you!

Read `src/hansi_parser.h` to implement the dependencies required for HANSIP.

## Supported ANSI escape sequences

- Color codes

Color code sequences always end with `m`

> \\033[arg1;arg2;arg3m

Where arg1, arg2, arg3 are the color codes to set.

To set foreground color value use codes ranging from 30-37.

Eg. `\033[37m` would set color foreground color to White.

To set background color value, use codes ranging from 40-47.

Eg. `\033[40m to set background color to Black.

Use 1 to make text bold. Eg. `\033[1m`

Use 0 to restore default attributes. Eg. `\033[0m`

Using all arguments at once - `\033[1;37;40m` would set foreground to white with bold, background to black

- Cursor codes

Cursor Codes sequences end with `H`

> \\033[x;yH

Where x and y are the values for the cursor to place on screen.

Eg. `\033[30H` would set cursor to 30 on X-axis on same Y-axis value.

The first argument is always X-axis value and second is Y-axis value.

A more advanced example would be - `\033[37;50H`
