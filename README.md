# VideoToAscii
This is my little project, that takes video and transforms it into ASCII character secquence.

## Usage
If you would like to use this project, you have to clone this repository, anf have ffmpeg and ffmplay insttalled. Then run
`` ./configure.sh `` <br/>
`` ./build.sh `` <br/>
And then to run: <br/>
`` ./run.sh [PATH_TO_VIDEO_FILE] [FPS] [VIDEO_SCALE_DOWN] ``
<br/><br/>
PATH_TO_VIDEO_FILE - relative to position of run.sh<br/>
FPS - how many fps do you want to yours video to have<br/>
VIDEO_SCALE_DOWN - intiger, that represents how many times is the video going to be scaled down, so it would fit into a terminal.
<br/> For example: video was originally 1000x1000 pixels, with scale factor of 10, its going to be 100x100 ASCII characters in the terminal

## Known problems

1. When video is finnished playing, the thread with audio is not going to stop executing, and thus not join. Because of this the program crashes at the end of a video.
