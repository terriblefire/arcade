PROJECT=pc060ha
BOARD=$(PROJECT)r1
GITVERSION=`git rev-parse --short HEAD`
DATESTRING=`date +"%Y_%m_%d"`
ZIPFILE=$(PROJECT)_$(DATESTRING)_$(GITVERSION).zip

all: zip
$(BOARD)/$(BOARD)_top.jed:
	cd $(BOARD) ; make 
zip: $(BOARD)/$(BOARD)_top.jed
	zip $(ZIPFILE) $<
clean:
	$(RM) -rf $(BOARD)/$(BOARD)_top.jed $(ZIPFILE)
