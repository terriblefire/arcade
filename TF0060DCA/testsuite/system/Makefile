SOURCES:= $(shell find . -name 'test_*.v')
TARGETS=$(subst .v,.vcd,$(SOURCES))

RTLFOLDER:=../../rtl
RTLSOURCES:=$(RTLFOLDER)/tf0060dca.v

IV:=iverilog 
SUPPORT:=../rtl/
RTLFOLDER:=../../rtl

XILINXMODS:= $(SUPPORT)/FDCPE.v $(SUPPORT)/FDCP.v $(SUPPORT)/PULLUP.v $(SUPPORT)/KEEPER.v

all: $(TARGETS) 

test_load.tb: test_load.v $(RTLSOURCES) mapping.mif
	$(IV) -o $(@) -I$(RTLFOLDER) $(RTLSOURCES) $< $(XILINXMODS) 
test_load.vcd: test_load.tb
	./$< || (exit 1)


