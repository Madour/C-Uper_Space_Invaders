PRGM = space

all: build

#install: build
#	mv src/$(PRGM) .

build:
	$(MAKE) -C src

debug:
	$(MAKE) debug -C src

clean:
	$(MAKE) -C src clean

.PHONY: clean