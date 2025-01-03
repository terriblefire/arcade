BOARDPREFIX=$(BOARD)r$(REVISION)
GITVERSION:=`git rev-parse --short HEAD`
DATESTRING:=`date +"%Y_%m_%d"`
SEEDSTRING:=`cat seed.txt`
ARTEFACTPREFIX:=$(BOARDPREFIX)_$(DATESTRING)_$(GITVERSION)_$(SEEDSTRING)

zip: 
	zip $(ARTEFACTPREFIX).zip *.jed

clean:	
	rm -rf work _xmsgs *.zip xlnx_auto_* 
distclean: clean
	rm -f *.jed *~ *.svf 

   
