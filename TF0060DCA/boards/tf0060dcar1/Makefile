REVISION=1
BOARD=tf0060dca
BOARDPREFIX=$(BOARD)r$(REVISION)

RTLFOLDER=../../rtl/
SOURCES="$(RTLFOLDER)/$(BOARD).v"
PART=XC9536XL-10-VQ44

all: $(BOARD)r$(REVISION)
$(BOARD)r$(REVISION): clean
	make -f ../Makefile.cpld BOARD=$(BOARD) SOURCES=$(SOURCES) REVISION=$(REVISION) OPTMODE=speed OPTIMISE=Area TOP=$(BOARD) PART=XC9536XL-10-VQ44
flash:
	xc3sprog -v -c ft232h -p0 $(BOARD)r$(REVISION)_top.jed:w
zip: distclean $(BOARD)r$(REVISION)
	zip $(BOARD)r$(REVISION)_`date +"%Y_%m_%d"`_alpha.zip *.jed
clean:	
	rm -rf work _xmsgs *.zip xlnx_auto_*
distclean: clean
	rm -f *.jed *~ *.svf 
