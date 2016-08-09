OUTPUT="SpriteSheetMaker"
OUTPUTDIR="bin/"
SOURCES=(
	" Main.cpp"
	" src/App.cpp"
	" src/Highlight.cpp"
	" src/InputHandler.cpp"
	" src/Utils.cpp"
	)
#SOURCES=()
#for SOURCE in $(ls src/)
#do
	#SOURCE="src/$SOURCE"
	#SOURCES="$SOURCES $SOURCE"
#done
INCLUDES=(
	" -Iinclude"
	)
LIBS=(
	" -lmsgl"
	" -lglfw" 
	" -lGL"
	" -lm"
	" -lgcc_s"
	" -lgcc"
	)
FLAGS=(
	" -L./libs/"
	" -std=c++11"
	" -Wl,-rpath=./libs/,-rpath,./"
	)
echo g++ ${FLAGS[*]} ${INCLUDES[*]} ${SOURCES[*]} ${LIBS[*]} -o $OUTPUT
g++ ${FLAGS[*]} ${INCLUDES[*]} ${SOURCES[*]} ${LIBS[*]} -o $OUTPUT
mv $OUTPUT $OUTPUTDIR
