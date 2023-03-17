# slou
<p align="center">
    <a href="https://www.github.com/reallySmooll/slou/blob/master/LICENSE" alt="License">
        <img src="https://img.shields.io/static/v1?label=License&message=MIT&color=informational">
    </a>
    <a href="https://www.github.com/reallySmooll/slou/blob/master/CHANGELOG.md" alt="Version">
        <img src="https://img.shields.io/static/v1?label=Version&message=v1.1.0&color=informational">
    </a>
    <a href="https://www.codacy.com/gh/reallySmooll/slou/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=reallySmooll/slou&amp;utm_campaign=Badge_Grade" alt="Codacy Badge">
        <img src="https://app.codacy.com/project/badge/Grade/30c92ecea05f43a98c67c947f61bbcd3">
    </a>
</p>

"Smooll" LOgging Utility (pronounced `slew`).

`slou` is a simple logging library made in C++ that's easy to use and fast. It has moderate configuration and can be used in both small and big projects.

## Installation
slou uses the Meson build system which means that you can install your project on all platforms that are supported by Meson.

Linux users can download a binary of the library on the [Releases](https://www.github.com/reallySmooll/slou/releases) page.
Windows users can now also download a binary of the library on the [Releases](https://www.github.com/reallySmooll/slou/releases) page.

### Dependencies
- Meson
- git
- Doxygen (optional, if you want to help with documentation, install it)

### Building
Building slou is as easy as 1-2-3. The following commands are directed at Linux users but it should work for any operating system as Meson will generate the necessary files for building the project.

```bash
$ git clone https://github.com/reallySmooll/slou.git
$ cd slou/
$ meson setup build/
$ meson compile -C build/
```

If you're on Linux and want to install the library system-wide, you can use these commands (after cloning the repository and entering into the directory):

```bash
$ meson setup --prefix /usr build/
$ sudo meson install -C build
```

## Quickstart
slou was designed to be very easy to use. And as it is a small library it doesn't require anymore setup than this:

```cpp
#include <slou/slou.hpp>

int main()
{
    slou::Logger logger;

    logger.Log(logger.INFO, "Hello, world!");

    return 0;
}
```

That is the default setup for slou. The logs will be saved to a file called (by default) `slou.log` but the logs will not be displayed on the screen.

You can obviously change this and customize it to your liking. If you'd like to see more you can check out the documentation [here](https://reallysmooll.github.io/slou-docs).

## Custom formatting
As of version `1.1.0`, slou supports custom formatting similar in use to the Python `logging` library.

There are four variables you can use to customize your log format:

- `{projectName}` - Name of your project
- `{level}` - Severity level
- `{time}` - Date and/or time
- `{message}` - Your log message

### Usage
To customize your format, you need to add it as a constructor argument:

```cpp
#include <slou/slou.hpp>

int main()
{
    // You can create a new variable with your custom format, or pass it directly to the constructor.
    std::string format = "{projectName} - [{level}] ({time}): {message}";

    slou::Logger logger("slou", "%X", true, false, "slou.log", format);

    logger.Log(logger.INFO, "Hello, world!");

    return 0;
}
```

The output:

```
slou - [INFO] (22:56:40): Hello, world!
```

You can obviously change the formatting to exclude some info from the log like for example the time, which would output:

```
slou - [INFO]: Hello, world!
```

The `format` variable would look something like this:

```cpp
std::string format = "{projectName} - [{level}]: {message}";
```

And that's all you need to know to format your logs however you like. Happy formatting! :)

## Contributing
If you'd like to contribute, please refer to the [contributing guide](https://www.github.com/reallySmooll/slou/blob/master/CONTRIBUTING.md).

Here are some contributions:

- Testing on Windows - Marcel Zdziechowicz ([@marcel-zdziechowicz](https://www.github.com/marcel-zdziechowicz))

## Code of Conduct
If you'd like to see it, check out the [CODE_OF_CONDUCT.md](https://www.github.com/reallySmooll/slou/blob/master/CODE_OF_CONDUCT.md).
