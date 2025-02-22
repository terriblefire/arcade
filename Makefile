.phony: PC060HA 
all: PC060HA 
PC060HA: clean
	make -C PC060HA 
	cp PC060HA/*.zip . 
clean:
	make -C PC060HA clean
