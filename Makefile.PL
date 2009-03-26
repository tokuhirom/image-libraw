use inc::Module::Install;
name 'Image-LibRaw';
all_from 'lib/Image/LibRaw.pm';

can_cc or die "This module requires a C compiler";
makemaker_args(
    OBJECT => '$(O_FILES)',
    LIBS => '-lraw -lstdc++',
    CCFLAGS => '-g -Wall',
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
use_test_base;
auto_include;
WriteAll;
