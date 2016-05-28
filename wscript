# -*- Mode: python; py-indent-offset: 4; indent-tabs-mode: nil; coding: utf-8; -*-

# def options(opt):
#     pass

# def configure(conf):
#     conf.check_nonfatal(header_name='stdint.h', define_name='HAVE_STDINT_H')

def build(bld):
    module = bld.create_ns3_module('nls', ['network', 'internet','ndnSIM'])
    module.source = [
        'model/nls.cc',
        'model/nls-interface.cc',
        'model/nls-label.cc',
        'model/nls-nhlfe.cc',
        'model/nls-operations.cc',
        'model/nls-protocol.cc',
        'model/nls-fec.cc',
        'model/nls-fec-to-nhlfe.cc',
        'model/nls-forwarding-information.cc',
        'model/nls-label-stack.cc',
        'model/nls-nhlfe-policy.cc',
        'model/nls-node.cc',
        'model/nls-packet-demux.cc',
        'model/nls-incoming-label-map.cc',
        'model/nls-forwarding-strategy.cc',
        'model/nls-forwarding-protocol.cc',       
        'helper/nls-switch.cc',
        'helper/nls-ilm-helper.cc',
        'helper/nls-nhlfe-selection-policy-helper.cc',
        'helper/nls-node-helper-base.cc',
        'helper/nls-ftn-helper.cc',
        'helper/nls-network-helper-base.cc',
        'helper/nls-interface-helper.cc',
        'helper/nls-network-configurator.cc',
        'helper/nls-installer.cc',
        'helper/nls-network-discoverer.cc',
        'LDP/nldp-nodehelp.cc',
        'LDP/TopologyRead.cc',
        'LDP/nldp-pdu.cc',
        'LDP/nldp-protocol.cc',
        'LDP/nlslibEntry.cc',
        'LDP/nldp-common-hello-params-tlv.cc',
        'LDP/nldp-transport.cc'      
        ]

    module_test = bld.create_ns3_module_test_library('nls')
    module_test.source = [
        'test/nls-test-suite.cc',
        ]

    headers = bld(features='ns3header')
    headers.module = 'nls'
    headers.source = [
        'model/nls.h',
        'model/nls-interface.h',
        'model/nls-label.h',
        'model/nls-nhlfe.h',
        'model/nls-operations.h',
        'model/nls-protocol.h',
        'model/nls-fec.h',
        'model/nls-fec-to-nhlfe.h',
        'model/nls-forwarding-information.h',
        'model/nls-label-stack.h',
        'model/nls-nhlfe-policy.h',
        'model/nls-node.h',
        'model/nls-packet-demux.h',
        'model/nls-incoming-label-map.h',
        'model/nls-traces.h',
        'model/nls-forwarding-strategy.h',
        'model/nls-forwarding-protocol.h',
        'helper/nls-switch.h',
        'helper/nls-ilm-helper.h',
        'helper/nls-nhlfe-selection-policy-helper.h',
        'helper/nls-node-helper-base.h', 
        'helper/nls-ftn-helper.h',
        'helper/nls-network-helper-base.h',
        'helper/nls-interface-helper.h',
        'helper/nls-network-configurator.h',
        'helper/nls-installer.h',
        'helper/nls-network-discoverer.h',
        'LDP/nldp-nodehelp.h',
        'LDP/TopologyRead.h',
        'LDP/ospf.h',
        'LDP/nldp-pdu.h',
        'LDP/nldp-protocol.h',
        'LDP/nldp-status.h',
        'LDP/nlslibEntry.h',
        'LDP/nldp-common-hello-params-tlv.h',
        'LDP/nldp-transport.h'          
        ]

    if bld.env.ENABLE_EXAMPLES:
        bld.recurse('examples')

    # bld.ns3_python_bindings()

