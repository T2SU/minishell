# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smun <smun@student.42seoul.kr>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/01 16:47:39 by smun              #+#    #+#              #
#    Updated: 2021/08/02 14:42:50 by smun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

READ_LINE = readline
SIGNAL = signal
PROCESS = process
FILE = file
TERMINAL = terminal

all: $(READ_LINE) $(SIGNAL) $(PROCESS) $(FILE) $(TERMINAL)

$(READ_LINE):
	$(MAKE) -C ./$(READ_LINE)
$(SIGNAL):
	$(MAKE) -C ./$(SIGNAL)
$(PROCESS):
	$(MAKE) -C ./$(PROCESS)
$(FILE):
	$(MAKE) -C ./$(FILE)
$(TERMINAL):
	$(MAKE) -C ./$(TERMINAL)
clean:
	$(MAKE) -C ./$(READ_LINE) clean
	$(MAKE) -C ./$(SIGNAL) clean
	$(MAKE) -C ./$(PROCESS) clean
	$(MAKE) -C ./$(FILE) clean
	$(MAKE) -C ./$(TERMINAL) clean


.PHONY: $(READ_LINE) $(SIGNAL) $(PROCESS) $(FILE) $(TERMINAL) clean
