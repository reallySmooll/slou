# Release Notes
These are the relase notes for `slou`.

## v1.2.0 | 21, mar. 2023
**Added**
- Named Parameter Idioms instead of positional arguments in the constructor (`projectName` is an exception)
- New log format variable, `moduleName` which is the module name (e.g. class name)
**Changed**
- Changeable variables initialized in the constructor are now private immutable variables only used for initialization. To change those variables, you'll have to use the NPIs

## v1.1.1 | 19, mar. 2023
**Changed**
- Changed variables `shouldLogToFile` and `shouldLogToScreen` to `logToFile` and `logToScreen`

**Added**
- `colorTerminalOutput` to check if the user wants to color the terminal output
- `USAGE.md` file as smaller documentation explaining ways of configuration for The Logger

## v1.1.0 | 17, mar. 2023
**Added**
- Custom formatting similar to the Python `logging` library

## v1.0.1 | 11, mar. 2023
**Changed**
- Changed `CurrentDateAndTime()` function to make it more cross-platform ('cause I've learned from my friend that `localtime` is not supported on Windows)

## v1.0.0 | 11, mar. 2023
- Initial release
