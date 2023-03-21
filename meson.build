project('slou', 'cpp',
  version : '1.2.0',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

# These arguments are only used to build the shared library
# not the executables that use the library.
lib_args = ['-DBUILDING_SLOU']

shlib_src = [ 'src/slou.cpp' ]

shlib = shared_library('slou', shlib_src,
  install : true,
  cpp_args : lib_args,
  gnu_symbol_visibility : 'hidden',
)

# This executable is used for library testing purposes
#sandbox = executable('sandbox', 'src/sandbox.cpp', link_with : shlib)

# Make this library usable as a Meson subproject.
slou_dep = declare_dependency(
  include_directories: include_directories('./src/'),
  link_with : shlib)

# Make this library usable from the system's
# package manager.
install_headers('./src/slou.hpp', subdir : 'slou')

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name : 'slou',
  filebase : 'slou',
  description : '"Smooll" LOgging Utility.',
  subdirs : 'slou',
  libraries : shlib,
  version : meson.project_version(),
)
