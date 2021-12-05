CC = g++

morse: main.cpp errorsLogging.cpp errorsHandling.cpp tasksExecution.cpp characterMaps.cpp utils.cpp
	$(CC) -o morse main.cpp errorsLogging.cpp errorsHandling.cpp tasksExecution.cpp characterMaps.cpp utils.cpp