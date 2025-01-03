IV:=iverilog 
SUPPORT:=../rtl/
RTLFOLDER:=../../rtl

XILINXMODS:= $(SUPPORT)/FDCPE.v $(SUPPORT)/FDCP.v $(SUPPORT)/PULLUP.v $(SUPPORT)/KEEPER.v

%.tb: %.v $(RTLSOURCES) $(RTLVINCS)
	$(IV) -o $(@) -I$(RTLFOLDER) $(RTLSOURCES) $< $(XILINXMODS) 
%.vcd: %.tb
	./$< || (exit 1)
clean:
	rm -f *.tb *.vcd
distclean:
	rm -f  *~
