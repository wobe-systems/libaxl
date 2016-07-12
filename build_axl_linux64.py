#!/usr/bin/env python
# -*- coding: utf-8 -*-
#-----------------------------------------------------------


from wbsbuild import *

build_tools = {
    "execPy"     : WBSPyRun,
    "mkdir"      : (WBSCmdCall, "mkdir" , "", False),
    "mv"         : (WBSCmdCall, "mv"    , "", False),
    "cd"         : (WBSCmdCall, "cd"    , "", False),
}

build_vars = {
    "AXLVER"      :"0.7.1",
}

build_steps = [    
    #cleanup

    ("del",         "build", False),
    ("mkdir",       "build"),
    ("cpy",         "build_axl_cmake_linux64.py" , "build"),
    ("execPy",      "./build/build_axl_cmake_linux64.py")
]

engine = WBSBuildEngine(gnames=globals(),
                        buildsteps=build_steps,
                        workdir=os.path.dirname(os.path.realpath(__file__)),
                        use_env=True)
engine.run()


