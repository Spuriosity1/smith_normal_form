project('smith_normal_form', 'cpp',
  version: '1.0.0',
  meson_version : '>= 1.4.0',
  default_options : [ 'warning_level=3', 'buildtype=debugoptimized', 'cpp_std=c++2a' ]
)

inc = include_directories('include')

libsnf_deps = []

arma_dep = dependency('Armadillo', required: false)
cpp_proj_arguments = []

add_project_arguments(cpp_proj_arguments, language : 'cpp')

# build the library
subdir('src')

snf_dep = declare_dependency(include_directories: inc, 
  link_with: libsnf)

# build tests
if get_option('enable-tests')
  #  gtest = subproject('gtest')
  subdir('tests')
endif



