#!/usr/bin/env python
# -*- coding: utf-8 -*-
#-----------------------------------------------------------


from wbsbuild import *

build_tools = {
    "CMAKE"    : (WBSCmdCall, "cmake", "", False),
    "runsh"    : (WBSCmdCall, "sh", "", False),
}

build_steps = [    

    ("CMAKE", ".. -G \"Unix Makefiles\" -DAXL_TARGET_PLATFORM=linux_x86-64"),
    ("CMAKE", "--build . --clean-first"),
    ("runsh", "../run_test.sh"),
]

engine = WBSBuildEngine(gnames=globals(),
                        buildsteps=build_steps,
                        workdir=os.path.dirname(os.path.realpath(__file__)),
                        use_env=True)
engine.run()


