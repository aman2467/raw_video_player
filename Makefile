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
	${VERBOSE}echo "All Binaries ${RED}removed${NONE}"

info:
	${VERBOSE}echo "                                         ${YELLOW}<<#|#>> "
	${VERBOSE}echo "                                         -(${RED}o o${YELLOW})-${NONE}"
	${VERBOSE}echo "${CYAN}======================================${YELLOW}oOO${CYAN}==${YELLOW}(${RED}^${YELLOW})${CYAN}==${YELLOW}OOo${CYAN}=====================================${NONE}"
	${VERBOSE}echo " "
	${VERBOSE}echo "${YELLOW}Binary Path :" 
	${VERBOSE}echo "        ${GREEN}${BIN_DIR}/${NONE}"
	${VERBOSE}echo "${YELLOW}Binaries :"
	${VERBOSE}echo "        ${GREEN}1. ${TARGET}${NONE}"
	${VERBOSE}echo " "
	${VERBOSE}echo "${CYAN}========================================================================================"
	${VERBOSE}echo " "

