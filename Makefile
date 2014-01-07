CC := g++ 
CFLAGS += -ansi -pedantic -Wall -Werror -g2
ALLDEP := Makefile
SRCDIR := src
BUILDDIR := build
OUTPUTDIR := bin
TARGET := $(OUTPUTDIR)/mfm

SRCEXT := cpp
HDRPAT := -name *.h -o -name *.tcc
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
HEADERS := $(shell find $(SRCDIR) -type f $(HDRPAT))
ALLDEP += $(HEADERS)
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
LIB := -L lib -lm -lSDL
INC := -I src/include

$(TARGET): $(OBJECTS)  
	@mkdir -p $(OUTPUTDIR)
	@echo "$(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(ALLDEP)
	@mkdir -p $(BUILDDIR)
	@echo "$(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo "Cleaning..."
	@echo "$(RM) -r $(BUILDDIR) $(TARGET) $(OUTPUTDIR)"; $(RM) -r $(BUILDDIR) $(TARGET) $(OUTPUTDIR)

.PHONY: clean
