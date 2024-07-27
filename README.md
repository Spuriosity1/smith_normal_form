# smith_normal_form
[![Build and Test](https://github.com/Spuriosity1/smith_normal_form/actions/workflows/main.yml/badge.svg)](https://github.com/Spuriosity1/smith_normal_form/actions/workflows/main.yml)

Computes the smith normal form of an integer matrix in C++.

See `snftest.cc`, which accepts a text file containing the matrix A 
(whose Smith Normal Form you wish to compute)
and prints its Smith Normal Form decomposition.

# BUILDING

This project is built with the [meson build system](https://mesonbuild.com).

To build the project, run
```zsh 
meson setup build
ninja -C build
# optional, runs some sanity checks
ninja -C build test
```
If you want to use armadillo, turn it on using
```zsh
meson configure build -Dbuild-armadillo=true
ninja -C build
```

To use as a [subproject](https://mesonbuild.com/Subprojects.html#using-a-subproject) of your own meson project, start with the directory structure (note that it **must** be called `subprojects`)
```
my_project -|- meson.build
            |- subprojects -|- ...
            |               |- ...
            |               |- ...
            |- ...
```

In the top-level `meson.build`, define the dependency through
```
snf_project = subproject('smith_normal_form')
snf_dep = snf_project.get_variable('snf_dep')
```
In any files using this package, add `snf_dep` as a dependency.

# TODO
- Even more unit tests
- QoL: Add converters for Eigen matrices
- Consider modifying the algorithm to make the L and R matrices simpler
- Currently uses a naive implementation, for really large matrices there are many superior algorithms e.g. https://www.isa-afp.org/browser_info/current/AFP/Smith_Normal_Form/document.pdf

