use strict;
use warnings;
use Image::LibRaw;
use GTop;

warn GTop->new()->proc_mem($$)->size;
for (0..100) {
    my $i = Image::LibRaw->new();
    warn GTop->new()->proc_mem($$)->size;
}

