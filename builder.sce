// ====================================================================
// Copyright INRIA 2008
// Allan CORNET
// Simon LIPP
// This file is released into the public domain
// ====================================================================

//mode selecciona el modo de ejecucion de builder.sce, -1 indica que se ejecuta silenciosamente
mode(-1);
//lines especifica las filas y columnas usadas para mostrar la informacion. 0 indica que no formateo de salida es echo
lines(0);
try
 //get scilab and modules version information
 getversion('scilab');
catch
 error(gettext('Scilab 5.0 or more is required.'));  
end;
// ====================================================================
//el modulo development_tools no esta incluido, marcar error
if ~with_module('development_tools') then
  error(msprintf(gettext('%s module not installed."),'development_tools'));
end
// ====================================================================
TOOLBOX_NAME = 'campos_finitos';
TOOLBOX_TITLE = 'Campos Finitos';
// ====================================================================
//get_absolute_file_path: Given an absolute pathname of a file opened in scilab. En este caso, da el path absoluto donde se encuentra builder.sce
toolbox_dir = get_absolute_file_path('builder.sce');

//si macros
//tbx_builder_macros: ejecuta buildmacros.sce
tbx_builder_macros(toolbox_dir);
//tbx_builder_src: ejecuta builder_src.sce
tbx_builder_src(toolbox_dir);
//tbx_builder_gateway: Ejecuta builder_gateway.sce
tbx_builder_gateway(toolbox_dir);
//tampoco deseo cargar la ayuda
//tbx_builder_help(toolbox_dir);
//Generate a loader.sce script
tbx_build_loader(TOOLBOX_NAME, toolbox_dir);

clear toolbox_dir TOOLBOX_NAME TOOLBOX_TITLE;
// ====================================================================
