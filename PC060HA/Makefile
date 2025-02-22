all: zip 
zip: clean
	make -C boards zip
	cp boards/*.zip . 
clean:
	make -C boards clean
	$(RM) -rf *.zip
