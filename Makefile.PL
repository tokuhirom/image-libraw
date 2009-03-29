use inc::Module::Install;
use Devel::CheckLib;
name 'Image-LibRaw';
all_from 'lib/Image/LibRaw.pm';

can_cc or die "This module requires a C compiler";
check_lib_or_exit(lib => 'raw', header => 'libraw/libraw.h');
makemaker_args(
    OBJECT => '$(O_FILES)',
    LIBS => '-lraw -lstdc++',
    CCFLAGS => '-g -Wall -O0',
    clean => {
        FILES => q{
            *.stackdump
            *.gcov *.gcda *.gcno
            *.out
            nytprof
            cover_db
        },
    },
);

tests 't/*.t';
author_tests 'xt';

build_requires 'Test::More';
build_requires 'Devel::CheckLib';
build_requires 'YAML';
use_test_base;
auto_include;
WriteAll;
