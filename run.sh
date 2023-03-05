#! /bin/bash

echo 'Generating frames from input video'

PATH_TO_VIDEO=$1
FPS=$2
SCALE_DOWN=$3

if [ $2 -eq 0 ] 
	then
		FPS=24
fi

if [ $3 -eq 0 ] 
	then 
	SCALE_DOWN=6	
fi

ffmpeg -i $PATH_TO_VIDEO -r 24 resources/frame_%d.jpg 1>&/dev/null #this redirects stdout to /dev/null, so nothing from ffmpeg gets printed
#ffmpeg -i $1 -acodec pcm_s16le -f s16le -ac 1 -ar 48000 audio/audio.raw 1>&/dev/null


echo 'Frames were generated'
#cd resources

NUM_OF_RESOURCES=$(ls resources/ | wc -l)

cd out/build

./bad_apple $NUM_OF_RESOURCES $FPS $SCALE_DOWN

