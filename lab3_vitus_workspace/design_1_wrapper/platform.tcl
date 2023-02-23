# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\nlitz88\workspace\design_1_wrapper\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\nlitz88\workspace\design_1_wrapper\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {design_1_wrapper}\
-hw {C:\Users\nlitz88\OneDrive - The Pennsylvania State University\Spring 2023\CMPEN 417\Labs\Lab 3\cmpen417lab3\lab3_part2\design_1_wrapper.xsa}\
-out {C:/Users/nlitz88/workspace}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {empty_application}
platform generate -domains 
platform active {design_1_wrapper}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
platform active {design_1_wrapper}
bsp reload
bsp write
bsp reload
bsp reload
domain active {zynq_fsbl}
bsp reload
