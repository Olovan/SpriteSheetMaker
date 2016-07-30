OUTPUT="SpriteSheetMaker"
OUTPUTDIR="bin/"
SOURCES=(
	" src/SpriteSheetMaker.cpp"
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
	" -L/home/micah/Documents/Code/SpriteSheetMaker/bin/"
	" -std=c++11"
	" -Wl,-rpath=./bin/,-rpath,./"
	)
echo g++ ${FLAGS[*]} ${INCLUDES[*]} ${SOURCES[*]} ${LIBS[*]} -o $OUTPUT
g++ ${FLAGS[*]} ${INCLUDES[*]} ${SOURCES[*]} ${LIBS[*]} -o $OUTPUT
mv $OUTPUT $OUTPUTDIR
