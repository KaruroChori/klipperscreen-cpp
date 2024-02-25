```
meson setup --cross-file arm32-glib.config build-arm32  #To organize the builddir
meson configure ./build-arm32/ -Dbuildtype=release      #(optional) to set a release profile
meson compile -C build-arm32                            #To build
```
