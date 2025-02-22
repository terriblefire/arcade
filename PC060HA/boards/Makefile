PROJECT:=pc060ha
BOARDS:=$(PROJECT)r1
.PHONY: $(BOARDS)
FOLDER:=$(PROJECT)_`date +"%Y_%m_%d"`
all: clean
	$(RM) -rf $(PROJECT)_* 	
	mkdir ./$(FOLDER)
	@- $(foreach BOARD,$(BOARDS), cd $(BOARD) ; make ; \
	cp $(BOARD)*.jed ../$(FOLDER);)
	zip $(FOLDER)_alpha.zip ./$(FOLDER)/*
	$(RM) -rf $(FOLDER)
clean:
	$(RM) -rf $(PROJECT)_* 
	@- $(foreach BOARD,$(BOARDS), make -C $(BOARD) clean;)
distclean: 
	@- $(foreach BOARD,$(BOARDS), make -C $(BOARD) distclean;)
