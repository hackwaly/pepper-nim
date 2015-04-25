NIM_HOME := /usr/local/Cellar/nimrod/0.10.2/nim
PNACL_TC_PATH := $(NACL_SDK_ROOT)/toolchain/mac_pnacl
PNACL_FINALIZE := $(PNACL_TC_PATH)/bin/pnacl-finalize
PNACL_CREATE_NMF := $(NACL_SDK_ROOT)/tools/create_nmf.py

TARGET := main
CXX := $(PNACL_TC_PATH)/bin/pnacl-clang++

CFLAGS := -O3 -ffast-math \
	-I$(NIM_HOME)/lib \
	-I$(NACL_SDK_ROOT)/include \
	-I$(PNACL_TC_PATH)/le32-nacl/usr/include/glibc-compat \
	-L$(NACL_SDK_ROOT)/lib/pnacl/Release -lppapi

default:
	$(MAKE) clean
	$(MAKE) out/$(TARGET).nmf

out/$(TARGET).pexe: out/$(TARGET).bc
	$(PNACL_FINALIZE) $< -o $@ --compress

out/$(TARGET).nmf: out/$(TARGET).pexe
	python $(PNACL_CREATE_NMF) $< -o $@

out:
	mkdir -p out

out/$(TARGET).bc: out/nimcache
	$(CXX) $(CFLAGS) out/nimcache/system.c out/nimcache/main.c tools/module.c -o $@

out/nimcache: out
	nim c -c --nimcache:$(shell pwd)/out/nimcache --cpu:i386 src/main.nim
	patch $@/system.c < tools/system-fix.patch
	sed -i '' "s/int main[(]/int MainNim(/g" $@/main.c

clean:
	rm -rf out
