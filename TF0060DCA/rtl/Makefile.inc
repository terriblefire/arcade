.PHONY: good bad
ifdef SEED
     PREFIX:=builds/$(SEED)/
endif

BOARDPREFIX=$(BOARD)r$(REVISION)
GITVERSION:=`git rev-parse --short HEAD`
DATESTRING:=`date +"%Y_%m_%d"`
SEEDSTRING:=`cat seed.txt`
ARTEFACTPREFIX:=$(BOARDPREFIX)_$(DATESTRING)_$(GITVERSION)_$(SEEDSTRING)

RTLFOLDER=../../rtl/
ROMFOLDER=../../rom/

TOOLSFOLDER=../../tools/
DRIVERSFOLDER=../../drivers/

ifndef SERIALNO
    SERIALNO=1000
    SUFFIX=_alpha
endif

ifndef SUFFIX
    SUFFIX=_$(SERIALNO)
endif

ROMPREFIX:=bootrom
AUTOCONFIGROM:=autoconfig.mif

BOOTROMBIN:=$(ROMPREFIX).rom
BOOTROM:=$(ROMPREFIX).mif

SYNTHROMBIN:=$(ROMPREFIX)_syn.bin
SYNTHROM:=$(ROMPREFIX)_syn.mif

.PHONY: $(ROMFOLDER)/$(BOOTROMBIN)

$(SYNTHROMBIN):
	dd if=/dev/random of=$@ bs=1K count=1

$(SYNTHROM): $(SYNTHROMBIN)
	$(ROMFOLDER)/bin2mif $< > $@

$(ROMFOLDER)/$(BOOTROMBIN): $(ROMFOLDER)/*
	make -C $(ROMFOLDER) BOARD=$(BOARD) REVISION=$(REVISION) $(BOOTROMBIN)

$(BOOTROMBIN): $(ROMFOLDER)/$(BOOTROMBIN)
	cp $< $@

$(BOOTROM): $(BOOTROMBIN)
	$(ROMFOLDER)/bin2mif $< > $@

$(AUTOCONFIGROM): $(RTLFOLDER)/mkzorro
	$(RTLFOLDER)/mkzorro > $@

drivers:
	cp -r $(DRIVERSFOLDER)/ehide .
tools:
	make -C $(TOOLSFOLDER) zip

zip: 
	zip $(ARTEFACTPREFIX).zip *.jed *.bin seed.txt README.txt

dist: $(BOARDPREFIX)
	zip $(ARTEFACTPREFIX).zip *.jed *.bin seed.txt README.txt 

sdk: $(BOARDPREFIX)_ram.bin
	zip $(ARTEFACTPREFIX)_SDK.zip *.bin *.asc seed.txt $(SYNTHROM) $(SYNTHROMBIN) Makefile.sdk

good:
	mkdir -p ./good/$(SEEDSTRING)_$(GITVERSION)/
	cp * ./good/$(SEEDSTRING)_$(GITVERSION)/
bad:
	mkdir -p ./bad/$(SEEDSTRING)_$(GITVERSION)/
	cp * ./bad/$(SEEDSTRING)_$(GITVERSION)/
clean:	
	rm -rf work _xmsgs *.zip xlnx_auto_* *.json *.asc *.rpt $(SYNTHROM) $(SYNTHROMBIN)
	make -C $(ROMFOLDER) clean
distclean: clean
	rm -f *.jed *~ *.svf *.txt *.bin *.blif *.log *.mif

   
