
test_deps = [snf_dep, arma_dep]

snftest = executable('snftest', 'snftest.cc',
  dependencies : test_deps)

snftest_lli = executable('snftest_lli', 'snftest_lli.cc',
  dependencies : test_deps)

inversetest = executable('inversetest', 'inversetest.cc', dependencies : test_deps)


test_matrices = files(['testdata/1x1.mat',
  'testdata/1x3.mat',
  'testdata/3x1.mat',
  'testdata/2x3.mat',
  'testdata/3x2.mat',
  'testdata/3x3_1.mat'
  'testdata/3x3_2.mat'
  'testdata/3x3_3.mat'
  'testdata/3x3_4.mat'

  ])

test_invertible_matrices = files([
'testdata/invertible_2x2_2.mat',
'testdata/invertible_3x3_5.mat',
'testdata/invertible_3x3_10.mat',
'testdata/invertible_3x3_17.mat',
'testdata/invertible_3x3_20.mat',
'testdata/invertible_4x4_10.mat',
'testdata/invertible_4x4_20.mat',
'testdata/invertible_4x4_30.mat',
'testdata/invertible_5x5_20.mat'
])

foreach matfile : test_matrices
  test('snftest', snftest, args: [matfile.full_path()])
  test('snftest_lli', snftest_lli, args: [matfile.full_path()])
endforeach

foreach matfile : test_invertible_matrices
  test('inversetest', inversetest, args: [matfile.full_path()])
endforeach

if get_option('build-armadillo')
  armatest = executable('armatest', 'armatest.cc', dependencies : test_deps)
  foreach matfile : test_matrices
    test('armatest', armatest, args: [matfile.full_path()])
  endforeach
endif



