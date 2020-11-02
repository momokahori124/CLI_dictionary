SRC = main.cpp
OUT = dictionary

main: $(SRC)
	@ g++ $(SRC) -o $(OUT)
	@ ./$(OUT)

clean:
	rm $(OUT)