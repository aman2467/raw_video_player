# ========================================================================================
#  @file    : Makefile
#
#  @description : Makefile for the raw video player.
#
#  @author  : Aman Kumar (2015)
#
#  @copyright   : The code contained herein is licensed under the GNU General Public License.
#               You may obtain a copy of the GNU General Public License Version 2 or later
#               at the following locations:
#               http://www.opensource.org/licenses/gpl-license.html
#               http://www.gnu.org/copyleft/gpl.html
# =========================================================================================*/

VERBOSE = @
BASEDIR = $(PWD)
TARGET = raw_player
CC =gcc
NONE=\033[0m
GREEN=\033[01;32m
RED=\033[01;31m
YELLOW=\033[01;33m
CYAN=\033[01;36m
SRC_DIR =$(BASEDIR)/src
BIN_DIR=$(BASEDIR)/bin
SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)
RELTARGET=$(BIN_DIR)/$(TARGET)
CFLAGS += -g -O3
LD_FLAGS += -lpthread
LD_FLAGS += -lSDL2
CPPFLAGS += -I. \
		-I./inc/ \

.PHONY: clean all paint_brush info

all: player info

player:
	${VERBOSE} ${CC} ${SRC_DIR}/*.c ${CFLAGS} ${CPPFLAGS} ${LD_FLAGS} -o ${RELTARGET}

clean:
	${VERBOSE}rm -f $(BIN_DIR)/*
	${VERBOSE}echo -e "All Binaries ${RED}removed${NONE}"

info:
	${VERBOSE}echo -e "                                         ${YELLOW}<<#|#>> "
	${VERBOSE}echo -e "                                         -(${RED}o o${YELLOW})-${NONE}"
	${VERBOSE}echo -e "${CYAN}======================================${YELLOW}oOO${CYAN}==${YELLOW}(${RED}^${YELLOW})${CYAN}==${YELLOW}OOo${CYAN}=====================================${NONE}"
	${VERBOSE}echo -e " "
	${VERBOSE}echo -e "${YELLOW}Binary Path :"
	${VERBOSE}echo -e "        ${GREEN}${BIN_DIR}/${NONE}"
	${VERBOSE}echo -e "${YELLOW}Binaries :"
	${VERBOSE}echo -e "        ${GREEN}1. ${TARGET}${NONE}"
	${VERBOSE}echo -e " "
	${VERBOSE}echo -e "${CYAN}========================================================================================"
	${VERBOSE}echo -e " "

