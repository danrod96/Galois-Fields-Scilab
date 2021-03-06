// ====================================================================
// Allan CORNET
// Simon LIPP
// INRIA 2008
// This file is released into the public domain
// ====================================================================
sci_gateway_dir = get_absolute_file_path('builder_gateway.sce');

//no construir las interfaces de cpp y fortran
//tbx_builder_gateway_lang('fortran', sci_gateway_dir);
//Run builder_gateway_(language).sce script if it exists (toolbox compilation process)
tbx_builder_gateway_lang('c', sci_gateway_dir);
//tbx_builder_gateway_lang('cpp', sci_gateway_dir);
//construir el cargador
tbx_build_gateway_loader(['c'], sci_gateway_dir);

clear tbx_builder_gateway_lang tbx_build_gateway_loader;
clear sci_gateway_dir;
