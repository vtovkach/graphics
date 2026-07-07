all:
	$(MAKE) -C src

debug:
	$(MAKE) -C src DEBUG=1

example:
	$(MAKE) -C src
	$(MAKE) -C app

example-debug:
	$(MAKE) -C src DEBUG=1
	$(MAKE) -C app DEBUG=1

clean:
	$(MAKE) -C src clean
	$(MAKE) -C app clean

.PHONY: all debug example example-debug clean