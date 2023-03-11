# slou

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/5b791702e9514ab4b30edc34b30f0991)](https://app.codacy.com/gh/reallySmooll/slou?utm_source=github.com&utm_medium=referral&utm_content=reallySmooll/slou&utm_campaign=Badge_Grade_Settings)

"Smooll" LOgging Utility (pronounced `slew` or `slow`).

`slou` is a simple logging library that's easy to use and fast. It has moderate configuration that can be used in both small and big projects.

## Installation
The project uses the Meson build system which means that you can install your project on all platforms that are supported by Meson.

### Dependencies
The dependencies `slou` uses are basic dependencies used by any project:

- Meson
- git
- Doxygen (optional, if you want to help with documentation, install it)

### Building
Building the project is as easy as 1-2-3. The following commands are directed at Linux users but it should work for any operating system as Meson will generate the necessary files for building the project.

```bash
$ git clone https://github.com/reallySmooll/slou.git
$ cd slou/
$ meson setup build/
$ meson compile -C build/
```

If you're on Linux and want to install the library system-wide, you can use these commands (after cloning the repository and entering the directory):

```bash
$ meson setup --prefix /usr build/
$ sudo meson install -C build
```

## Quickstart
`slou` was designed to be very easy to use. And as it is a small library it doesn't require anymore setup than this:

```cpp
#include <slou/slou.hpp>

int main()
{
    slou::Logger logger;

    logger.Log(logger.INFO, "Hello, world!");

    return 0;
}
```

And that is the default setup for `slou`. The logs will be saved to a file called (by default) `slou.log` but the logs will not be displayed on the screen.

You can obviously change this and customize it to your liking. If you'd like to see more you can check out the documentation [here](https://reallysmooll.github.io/slou-docs).
