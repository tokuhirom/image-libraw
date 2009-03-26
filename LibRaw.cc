#include "bindpp.h"
#include "libraw/libraw.h"

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
    self->open_file(fname->to_c());
    c.return_true();
}

XS(xs_get_width) {
    pl::Ctx c(1);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();
    c.ret(pl::Int(self->imgdata.sizes.width));
}
XS(xs_get_height) {
    pl::Ctx c(1);

    LibRaw * self = c.arg(0)->as_pointer()->extract<LibRaw*>();
    c.ret(pl::Int(self->imgdata.sizes.height));
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
        b.add_method("new", xs_new, __FILE__);
        b.add_method("open_file", xs_open_file, __FILE__);
        b.add_method("get_width", xs_get_width, __FILE__);
        b.add_method("get_height", xs_get_height, __FILE__);
        b.add_method("DESTROY", xs_destroy, __FILE__);
    }
}

