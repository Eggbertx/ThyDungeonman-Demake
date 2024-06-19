TARGET := apple2enh

NAME := ThyDungeonman
PRG := $(NAME)-$(TARGET).prg
DISK := $(NAME)-$(TARGET).po
DISK_BIN := tdman1
TEMPLATE_PO := tmp/template.po
AC_JAR := AppleCommander-ac-1.9.0.jar
AC := java -jar tmp/$(AC_JAR)
TARGET_PATH := $(shell cl65 --print-target-path)/$(TARGET)/util/loader.system
SOURCES := src/util.c src/commands.c src/main.c
LINAPPLE := linapple

build:
	cl65 -t $(TARGET) -o $(PRG) $(SOURCES)

disk: require-apple2 build get-template
	cp $(TEMPLATE_PO) $(DISK)
	$(AC) -p $(DISK) $(DISK_BIN).system sys < $(TARGET_PATH)
	$(AC) -as $(DISK) $(DISK_BIN) bin <$(PRG)

buildandrun: disk
	$(LINAPPLE) --d1 $(DISK) -b

clean:
	rm -rf src/*.o *.prg *.po tmp/

require-apple2:
ifneq ($(TARGET), apple2)
ifneq ($(TARGET), apple2enh)
	$(error TARGET must be 'apple2' or 'apple2enh' in order to build a ProDOS disk, got $(TARGET))
endif
endif

tmp/$(AC_JAR):
	mkdir -p tmp/
	wget -O tmp/$(AC_JAR) https://github.com/AppleCommander/AppleCommander/releases/download/1.9.0/$(AC_JAR)

get-ac: tmp/$(AC_JAR)

$(TEMPLATE_PO): tmp/$(AC_JAR)
	mkdir -p tmp/
	rm -f $(TEMPLATE_PO)
	wget -O $(TEMPLATE_PO) http://releases.prodos8.com/ProDOS_2_4_3.po
	$(AC) -d $(TEMPLATE_PO) VIEW.README
	$(AC) -d $(TEMPLATE_PO) BITSY.BOOT
	$(AC) -d $(TEMPLATE_PO) QUIT.SYSTEM
	$(AC) -d $(TEMPLATE_PO) BASIC.SYSTEM
	$(AC) -d $(TEMPLATE_PO) COPYIIPLUS.8.4
	$(AC) -d $(TEMPLATE_PO) BLOCKWARDEN
	$(AC) -d $(TEMPLATE_PO) CAT.DOCTOR
	$(AC) -d $(TEMPLATE_PO) UNSHRINK
	$(AC) -d $(TEMPLATE_PO) CD.EXT
	$(AC) -d $(TEMPLATE_PO) FASTDSK
	$(AC) -d $(TEMPLATE_PO) FASTDSK.CONF
	$(AC) -d $(TEMPLATE_PO) FASTDSK.SYSTEM
	$(AC) -d $(TEMPLATE_PO) MAKE.SMALL.P8
	$(AC) -d $(TEMPLATE_PO) MINIBAS
	$(AC) -d $(TEMPLATE_PO) MR.FIXIT.Y2K
	$(AC) -d $(TEMPLATE_PO) README

get-template: get-ac $(TEMPLATE_PO)