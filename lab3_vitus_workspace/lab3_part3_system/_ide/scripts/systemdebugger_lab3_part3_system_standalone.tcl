# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\nlitz88\workspace\lab3_part3_system\_ide\scripts\systemdebugger_lab3_part3_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\nlitz88\workspace\lab3_part3_system\_ide\scripts\systemdebugger_lab3_part3_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Zed 210248782930" && level==0 && jtag_device_ctx=="jsn-Zed-210248782930-23727093-0"}
fpga -file C:/Users/nlitz88/workspace/lab3_part3_design1/_ide/bitstream/design_1_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/nlitz88/workspace/zed/export/zed/hw/zed.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/Users/nlitz88/workspace/lab3_part3/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow C:/Users/nlitz88/workspace/lab3_part3/Debug/lab3_part3.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
