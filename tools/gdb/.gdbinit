target remote localhost:3333
monitor reset halt
monitor resume
load ../../build/release/theseus.axf
symbol-file ../../build/release/theseus.axf
