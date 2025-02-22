REVISION=1
BOARD=pc060ha
BOARDPREFIX=$(BOARD)r$(REVISION)

UNAME := $(shell uname)
XILINXENV:=
SRCROOT:=$(abspath $(PWD)/../../)
BRDROOT:=$(subst $(SRCROOT),,$(abspath $(PWD)))
DOCKERIMAGE:=xilinx

ifneq ($(UNAME), Linux)
      XILINXENV=docker run --rm  -v $(SRCROOT):/host -w /host/$(BRDROOT) -it $(DOCKERIMAGE) 
endif

RTLFOLDER=../../rtl/
SOURCES="$(RTLFOLDER)/pc060ha.v"

all: $(BOARD)r$(REVISION)
$(BOARD)r$(REVISION): clean
	$(XILINXENV) make -f ../Makefile.cpld BOARD=$(BOARD) SOURCES=$(SOURCES) SUBPROJ=ram REVISION=$(REVISION) OPTMODE=speed OPTIMISE=speed TOP=top PART=XC95144XL-10-TQ100
flash:
	xc3sprog -v -c ft232h -p0 $(BOARD)r$(REVISION)_top.jed:w
zip: distclean $(BOARD)r$(REVISION)
	zip $(BOARD)r$(REVISION)_`date +"%Y_%m_%d"`_alpha.zip *.jed
clean:	
	rm -rf work _xmsgs *.zip xlnx_auto_*
distclean: clean
	rm -f *.jed *~ *.svf 
