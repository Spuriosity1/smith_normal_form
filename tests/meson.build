
test_deps = [snf_dep, arma_dep]

snftest = executable('snftest', 'snftest.cc',
  dependencies : test_deps)



test_matrices = files(['testdata/1x1.mat',
  'testdata/1x3.mat',
  'testdata/3x1.mat',
  'testdata/2x3.mat',
  'testdata/3x2.mat',
  'testdata/3x3.mat'])

foreach matfile : test_matrices
  test('snftest', snftest, args: [matfile.full_path()])
endforeach


if get_option('build-armadillo')
  armatest = executable('armatest', 'armatest.cc', dependencies : test_deps)
  foreach matfile : test_matrices
    test('armatest', armatest, args: [matfile.full_path()])
  endforeach
endif



