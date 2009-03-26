use strict;
use warnings;
use Image::LibRaw;

my $fname = shift or die "missing filename";

my $img = Image::LibRaw->new;
$img->open_file($fname);
printf "width: %d\n", $img->get_width();
printf "height: %d\n", $img->get_height();
