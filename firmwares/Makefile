include Makefile.config

CC := avr-gcc
LD := avr-gcc
OBJCOPY := avr-objcopy

SRC_DIR   := $(addprefix src/,$(MODULES))
BUILD_DIR := $(addprefix build/,$(MODULES))

DEFS	  += -DF_CPU=$(F_CPU)
LIBS	  := -lm

SRC       :=
OBJ       :=
INCLUDES  := -Isrc/
add-src   = $(eval include src/$1/Makefile.sources); \
    $(eval SRC += $(addprefix src/$1/,$(SOURCES))); \
    $(eval OBJ += $(addprefix build/$1/,$(subst .S,.o,$(subst .c,.o,$(SOURCES))))); \

$(foreach module,$(MODULES),$(call add-src,$(module)))

override CFLAGS  := -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS) -O2
override LDFLAGS := -Wl,-Map,$(PRG).map

vpath %.c $(SRC_DIR)


all: checkdirs build/flash.bin build/flash.hex

build/flash.bin: build/flash
	$(OBJCOPY) -j .text -j .data -O binary $< $@

build/flash.hex: build/flash
	$(OBJCOPY) -j .text -j .data -O ihex $< $@

build/flash: $(OBJ)
	$(CC) -g -fPIC -MMD $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

checkdirs: $(BUILD_DIR)

define make-goal
$1/%.o: $2/%.c
	$(CC) $(CFLAGS) $(DEFS) $(INCLUDES) -c $$< -o $$@

$1/%.o: $2/%.S
	$(CC) $(CFLAGS) $(DEFS) $(INCLUDES) -c $$< -o $$@
endef

$(BUILD_DIR):
	@mkdir -p $@

clean:
	@rm -rf build/*

$(foreach bdir,$(BUILD_DIR),$(eval $(call make-goal,$(bdir),$(patsubst build/%,src/%,$(bdir)))))

install:
	avrdude -c arduino -p $(MCU_TARGET) -P /dev/ttyACM0 -U flash:w:build/flash.bin:r
