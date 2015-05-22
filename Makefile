CFLAGS= -g

HEADER_FILES = c_src
SOURCE_FILES = c_src/arm_usb.c c_src/erl_comm.c

OBJECT_FILES = $(SOURCE_FILES:.c=.o)

LDLIBS = -lusb-1.0

priv_dir/arm_usb: clean priv_dir $(OBJECT_FILES)
	mkdir -p priv_dir
	$(CC) -I $(HEADER_FILES) -o $@ $(LDFLAGS) $(OBJECT_FILES) $(LDLIBS)

priv_dir:
	mkdir -p priv_dir

clean:
	rm -f priv_dir/usb $(OBJECT_FILES) $(BEAM_FILES)
