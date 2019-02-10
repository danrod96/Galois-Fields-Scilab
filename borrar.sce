//
// borrar archivos temporales
//
chdir(SCI+'/modules/campos_finitos');

mdelete("loader.sce")
cd "src"
cd "c"
mdelete("*.obj")
mdelete("*.dll")
mdelete("*.lib")
mdelete("*.exp")
mdelete("*.def")
mdelete("*.mak")
mdelete("*.pdb")
mdelete("*.ilk")
mdelete("loader.sce")
chdir(SCI+'/modules/campos_finitos');
cd "sci_gateway"
cd "c"
mdelete("*.obj")
mdelete("*.dll")
mdelete("*.lib")
mdelete("*.exp")
mdelete("*.def")
mdelete("*.mak")
mdelete("*.pdb")
mdelete("*.ilk")
mdelete("campos_c.c")
chdir(SCI+'/modules/campos_finitos');
cd "macros"
mdelete("*.bin")
mdelete("lib")
mdelete("names")
chdir(SCI+'/modules/campos_finitos');
