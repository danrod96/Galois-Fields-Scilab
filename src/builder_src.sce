// ====================================================================
// Allan CORNET
// Simon LIPP
// INRIA 2008
// This file is released into the public domain
// ====================================================================

src_dir = get_absolute_file_path('builder_src.sce');

// no fortran
//tbx_builder_src_lang('fortran', src_dir);
// Run builder_(language).sce script if it exists (toolbox compilation process)
tbx_builder_src_lang('c', src_dir);

clear tbx_builder_src_lang;
clear src_dir;
