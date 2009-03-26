#include "bindpp.h"
#include "libraw/libraw.h"
#include <cstdlib>

XS(xs_new) {
    pl::Ctx c(1);

    pl::Str * klass = c.arg(0)->as_str();
    LibRaw * self = new LibRaw();
    c.ret(pl::Pointer((void*)self, klass->to_c()));
}

XS(xs_open_file) {
    pl::Ctx c(2);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();
    pl::Str * fname = c.arg(1)->as_str();
    c.ret(pl::Int(self->open_file(fname->to_c())));
}

XS(xs_get_idata) {
    pl::Ctx c(1);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();

    pl::Hash res;
    res.store("make", pl::Str(self->imgdata.idata.make));
    res.store("model", pl::Str(self->imgdata.idata.model));
    res.store("raw_count", pl::UInt(self->imgdata.idata.raw_count));
    res.store("dng_version", pl::UInt(self->imgdata.idata.dng_version));
    res.store("is_foveon", pl::UInt(self->imgdata.idata.is_foveon));
    res.store("colors", pl::Int(self->imgdata.idata.colors));
    res.store("filters", pl::UInt(self->imgdata.idata.filters));
    res.store("cdesc", pl::Str(self->imgdata.idata.cdesc));

    c.ret(res.reference());
}

XS(xs_get_sizes) {
    pl::Ctx c(1);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();
    pl::Hash res;
    res.store("raw_height", pl::UInt(self->imgdata.sizes.raw_height));
    res.store("raw_width", pl::UInt(self->imgdata.sizes.raw_width));
    res.store("height", pl::UInt(self->imgdata.sizes.height));
    res.store("width", pl::UInt(self->imgdata.sizes.width));
    res.store("top_margin", pl::UInt(self->imgdata.sizes.top_margin));
    res.store("left_margin", pl::UInt(self->imgdata.sizes.left_margin));
    res.store("bottom_margin", pl::UInt(self->imgdata.sizes.bottom_margin));
    res.store("right_margin", pl::UInt(self->imgdata.sizes.right_margin));
    res.store("iheight", pl::UInt(self->imgdata.sizes.iheight));
    res.store("iwidth", pl::UInt(self->imgdata.sizes.iwidth));
    res.store("pixel_aspect", pl::Double(self->imgdata.sizes.pixel_aspect));
    res.store("flip", pl::Int(self->imgdata.sizes.flip));
    c.ret(res.reference());
}

XS(xs_get_other) {
    pl::Ctx c(1);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();
    pl::Hash res;
    res.store("iso_speed", pl::Double(self->imgdata.other.iso_speed));
    res.store("shutter", pl::Double(self->imgdata.other.shutter));
    res.store("aperture", pl::Double(self->imgdata.other.aperture));
    res.store("focal_len", pl::Double(self->imgdata.other.focal_len));
    res.store("timestamp", pl::UInt(self->imgdata.other.timestamp));
    res.store("shot_order", pl::UInt(self->imgdata.other.shot_order));
    // gpsdata does not handled yet
    res.store("desc", pl::Str(self->imgdata.other.desc));
    res.store("artist", pl::Str(self->imgdata.other.artist));
    c.ret(res.reference());
}

XS(xs_unpack) {
    pl::Ctx c(1);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();
    c.ret(pl::Int(self->unpack()));
}

XS(xs_unpack_thumb) {
    pl::Ctx c(1);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();
    c.ret(pl::Int(self->unpack_thumb()));
}

XS(xs_dcraw_thumb_writer) {
    pl::Ctx c(2);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();
    pl::Str * fname = c.arg(1)->as_str();
    c.ret(pl::Int(self->dcraw_thumb_writer(fname->to_c())));
}
XS(xs_dcraw_ppm_tiff_writer) {
    pl::Ctx c(2);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();
    pl::Str * fname = c.arg(1)->as_str();
    c.ret(pl::Int(self->dcraw_ppm_tiff_writer(fname->to_c())));
}

XS(xs_rotate_fuji_raw) {
    pl::Ctx c(1);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();
    c.ret(pl::Int(self->rotate_fuji_raw()));
}
XS(xs_recycle) {
    pl::Ctx c(1);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();
    self->recycle();
    c.return_true();
}
XS(xs_version) {
    pl::Ctx c(1);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();
    c.ret(pl::Str(self->version()));
}
XS(xs_version_number) {
    pl::Ctx c(1);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();
    c.ret(pl::Int(self->versionNumber()));
}
XS(xs_camera_count) {
    pl::Ctx c(1);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();
    c.ret(pl::Int(self->cameraCount()));
}
XS(xs_camera_list) {
    pl::Ctx c(1);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();

    pl::Array ary;
    const char ** list = self->cameraList();
    while (*list) {
        ary.push(pl::Str(*list));
        list++;
    }
    c.ret(ary.reference());
}
XS(xs_strerror) {
    pl::Ctx c(2);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();
    pl::Int * i = c.arg(1)->as_int();
    c.ret(pl::Str(self->strerror(i->to_c())));
}

XS(xs_destroy) {
    pl::Ctx c(1);

    pl::Pointer * p = c.arg(0)->as_pointer();
    delete p->extract<LibRaw*>();
    c.return_true();
}

extern "C" {
    XS(boot_Image__LibRaw) {
        pl::BootstrapCtx bc;

        pl::Package b("Image::LibRaw");
        b.add_method("new",                   xs_new,                   __FILE__);
        b.add_method("open_file",             xs_open_file,             __FILE__);
        b.add_method("get_idata",             xs_get_idata,             __FILE__);
        b.add_method("get_sizes",             xs_get_sizes,             __FILE__);
        b.add_method("get_other",             xs_get_other,             __FILE__);
        b.add_method("unpack",                xs_unpack,                __FILE__);
        b.add_method("unpack_thumb",          xs_unpack_thumb,          __FILE__);
        b.add_method("dcraw_thumb_writer",    xs_dcraw_thumb_writer,    __FILE__);
        b.add_method("dcraw_ppm_tiff_writer", xs_dcraw_ppm_tiff_writer, __FILE__);
        b.add_method("recycle",               xs_recycle,               __FILE__);
        b.add_method("version",               xs_version,               __FILE__);
        b.add_method("version_number",        xs_version_number,        __FILE__);
        b.add_method("camera_count",          xs_camera_count,          __FILE__);
        b.add_method("camera_list",           xs_camera_list,           __FILE__);
        b.add_method("rotate_fuji_raw",       xs_rotate_fuji_raw,       __FILE__);
        b.add_method("strerror",              xs_strerror,              __FILE__);
        b.add_method("DESTROY",               xs_destroy,               __FILE__);
    }
}

