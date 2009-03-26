use strict;
use warnings;
use Image::LibRaw;
use YAML;

my $fname = shift or die "missing filename";

my $img = Image::LibRaw->new;
$img->open_file($fname);
for my $meth (qw/sizes idata other/) {
    print Dump(+{ $meth => $img->can("get_$meth")->($img) });
}
$img->unpack_thumb;
$img->dcraw_thumb_writer('libraw-thumb.jpg');

$img->unpack;
$img->dcraw_ppm_tiff_writer('libraw-ppm.ppm');

print 'version: ', $img->version, "\n";
print 'version_number: ', $img->version_number, "\n";
print 'camera_count: ', $img->camera_count, "\n";
print 'camera list: ' . Dump($img->camera_list);
print 'error code test: ', $img->strerror(0), "\n";

