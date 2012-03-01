BIN_FILE = bin/webcrawler
MAIN_OBJ = obj/main.o
OBJ_FILES = obj/Page.o obj/PageQueue.o obj/PageHistory.o obj/PageDownloader.o obj/URL.o obj/HTMLParser.o
TEST_BIN_FILE = bin/testProject1
TEST_OBJ_FILES = $(OBJ_FILES) obj/testProject1.o
LIBRARY = lib/libcs240utils.a
LIBRARY_OBJ_FILES = utils/obj/StringUtil.o utils/obj/URLInputStream.o utils/obj/FileInputStream.o \
					utils/obj/HTTPInputStream.o utils/obj/CommandRunner.o utils/obj/FileSystem.o \
					utils/obj/HTMLToken.o utils/obj/HTMLTokenizer.o

#Create Project 1 executable
bin: $(BIN_FILE)

#Create Project 1 test executable and run
test: $(TEST_BIN_FILE)
	@$(TEST_BIN_FILE) &

#Create CS240 Library
lib: $(LIBRARY)

#remove all library, object files, and executables
clean:
	-rm -f lib/*
	-rm -f obj/*
	-rm -f bin/*
	-rm -f utils/obj/*

#Create test executable
$(TEST_BIN_FILE): $(TEST_OBJ_FILES) $(LIBRARY)
	@g++ -o $(TEST_BIN_FILE) $(TEST_OBJ_FILES) $(LIBRARY)
	@chmod ugo+x $(TEST_BIN_FILE)
	
#Create executable
$(BIN_FILE): $(OBJ_FILES) $(MAIN_OBJ) $(LIBRARY)
	@g++ -o $(BIN_FILE) $(OBJ_FILES) $(MAIN_OBJ) $(LIBRARY)
	@chmod ugo+x $(BIN_FILE)

#Create CS240 library
$(LIBRARY): $(LIBRARY_OBJ_FILES)
	@ar r $(LIBRARY) $(LIBRARY_OBJ_FILES)


################################################
#Poject 1 Object Files

obj/main.o: src/main.cpp $(LIBRARY_OBJ_FILES)
	@g++ -c -Wall -o obj/main.o -I inc/ -I utils/inc/ src/main.cpp

obj/Page.o: src/Page.cpp inc/Page.h
	@g++ -c -Wall -o obj/Page.o -I inc/ -I utils/inc/ src/Page.cpp

obj/PageQueue.o: src/PageQueue.cpp inc/PageQueue.h inc/LinkedList.h
	@g++ -c -Wall -o obj/PageQueue.o -I inc/ -I utils/inc/ src/PageQueue.cpp

obj/PageHistory.o: src/PageHistory.cpp inc/PageHistory.h inc/BST.h
	@g++ -c -Wall -o obj/PageHistory.o -I inc/ -I utils/inc/ src/PageHistory.cpp

obj/PageDownloader.o: src/PageDownloader.cpp inc/PageDownloader.h utils/inc/URLInputStream.h
	@g++ -c -Wall -o obj/PageDownloader.o -I inc/ -I utils/inc/ src/PageDownloader.cpp

obj/URL.o: src/URL.cpp inc/URL.h
	@g++ -c -Wall -o obj/URL.o -I inc/ -I utils/inc/ src/URL.cpp

obj/HTMLParser.o: src/HTMLParser.cpp inc/HTMLParser.h inc/LinkedList.h
	@g++ -c -Wall -o obj/HTMLParser.o -I inc/ -I utils/inc/ src/HTMLParser.cpp



################################################
#Project 1 Test Object Files

obj/testProject1.o: src/testProject1.cpp $(LIBRARY)
	@g++ -c -Wall -o obj/testProject1.o -I inc/ -I utils/inc/ src/testProject1.cpp




################################################
#CS240 Library Object Files

utils/obj/StringUtil.o: utils/inc/StringUtil.h utils/src/StringUtil.cpp
	@g++ -c -Wall -o utils/obj/StringUtil.o -I utils/inc/ utils/src/StringUtil.cpp
	

utils/obj/URLInputStream.o: utils/inc/URLInputStream.h utils/src/URLInputStream.cpp
	@g++ -c -Wall -o utils/obj/URLInputStream.o -I utils/inc/ utils/src/URLInputStream.cpp

utils/obj/FileInputStream.o: utils/inc/FileInputStream.h utils/src/FileInputStream.cpp
	@g++ -c -Wall -o utils/obj/FileInputStream.o -I utils/inc/ utils/src/FileInputStream.cpp

utils/obj/HTTPInputStream.o: utils/inc/HTTPInputStream.h utils/src/HTTPInputStream.cpp
	@g++ -c -Wall -o utils/obj/HTTPInputStream.o -I utils/inc/ utils/src/HTTPInputStream.cpp

utils/obj/CommandRunner.o: utils/inc/CommandRunner.h utils/src/CommandRunner.cpp
	@g++ -c -Wall -o utils/obj/CommandRunner.o -I utils/inc/ utils/src/CommandRunner.cpp

utils/obj/FileSystem.o: utils/inc/FileSystem.h utils/src/FileSystem.cpp
	@g++ -c -Wall -o utils/obj/FileSystem.o -I utils/inc/ utils/src/FileSystem.cpp

utils/obj/HTMLToken.o: utils/inc/HTMLToken.h utils/src/HTMLToken.cpp
	@g++ -c -Wall -o utils/obj/HTMLToken.o -I utils/inc/ utils/src/HTMLToken.cpp

utils/obj/HTMLTokenizer.o: utils/inc/HTMLTokenizer.h utils/src/HTMLTokenizer.cpp
	@g++ -c -Wall -o utils/obj/HTMLTokenizer.o -I utils/inc/ utils/src/HTMLTokenizer.cpp


