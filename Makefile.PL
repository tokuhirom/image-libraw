use inc::Module::Install;
name 'Image-LibRaw';
all_from 'lib/Image/LibRaw.pm';

can_cc or die "This module requires a C compiler";
checklibs lib => 'raw', header => 'libraw/libraw.h';

libs '-lraw -lstdc++';

clean_files qw{
    *.stackdump
    *.gcov *.gcda *.gcno
    *.out
    nytprof
    cover_db
};

tests 't/*.t';
author_tests 'xt';

build_requires 'Test::More';
build_requires 'Devel::CheckLib';
build_requires 'YAML';
auto_set_repository;
use_test_base;
WriteAll;
