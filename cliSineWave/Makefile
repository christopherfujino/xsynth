APP_NAME = cliSineWave
BUILDDIR = Builds/LinuxMakefile

.PHONY: run
run: build
	./$(BUILDDIR)/build/$(APP_NAME)

.PHONY: build
build:
	make -C $(BUILDDIR)

.PHONY: clean
clean:
	make -C $(BUILDDIR) clean
