# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

# def configure(conf):
#     conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')

def build(bld):
    module = bld.create_ns3_module('project2', ['applications','core', 'internet', 'csma', 'config-store','stats'])
    module.source = [
        'model/project2.cc',
        'model/Filter.cc',
        'model/FilterElement.cc',
        'helper/project2-helper.cc',
        ]

    module_test = bld.create_ns3_module_test_library('project2')
    module_test.source = [
        'test/project2-test-suite.cc',
        ]

    headers = bld(features='ns3header')
    headers.module = 'project2'
    headers.source = [
        'model/project2.h',
        'model/Filter.h',
        'model/FilterElement.h',
        ]
    module.use.append("ZLIB1G")
    if bld.env.ENABLE_EXAMPLES:
        bld.recurse('examples')

def configure(conf):
     conf.env['zlib1g'] = conf.check(mandatory=True, lib='z', uselib_store='ZLIB1G')

    # bld.ns3_python_bindings()

