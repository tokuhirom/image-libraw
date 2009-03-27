use strict;
use warnings;
use Image::LibRaw;
use GTop;

warn GTop->new()->proc_mem($$)->size;
for (0..10) {
    my $i = Image::LibRaw->new();
    use Devel::Peek;
    Dump($i);
    undef $i;
    warn GTop->new()->proc_mem($$)->size;
}

