#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <thread>
#include <unistd.h>

#include "pngAscii.h"

float get_time();
void play_audio();

float start_time = clock();
float delta_time = 0.0f;
float current_time = 0.0f;
float end_time = 0.0f;

float FPS = 24.0f;

int processed_images = 0;

int main(int argc, char** argv){
	if(argc == 0){
		std::cout << "No video was taken as input(try: ./bad_apple ~/path/to/video)";
		return -1;
	}
	else if (argv[1] == "0") {
		std::cout << "Video wasn't loaded correctly, images warent generated\n";
		return -1;
	}
	
	std::cout << "Processing images\n";
	char* from_input = argv[1];
	int num_of_files = std::atoi(from_input);//this converts char* to int

	char* from_input_fps = argv[2];
	FPS = std::atoi(from_input_fps);

	char* from_input_scale = argv[3];
	short scale_down = std::atoi(from_input_scale);

//thread starts
//	std::thread loading_bar(load_bar, num_of_files);
	
	Picture* frames = (Picture*)malloc(num_of_files * sizeof(Picture));

	for(processed_images = 1; processed_images <= num_of_files; processed_images++){
		std::stringstream ss;
		ss << "../../resources/frame_" << processed_images << ".jpg";
		frames[processed_images] = Picture(ss.str().c_str(), scale_down);
	

		//loading bar
		std::cout << "\e[1;1H\e[2J";
		float procent = procent = ((float)processed_images/num_of_files)*100;
		std::stringstream ss_bar;
		
		for(int i = 0; i < procent/10; i++){
			ss_bar << "#";
		}
		for(int i = 0; i < (100 - procent)/10; i++){
			ss_bar << "-";
		}

		std::cout << "The images are being processed into memory\n";
		std::cout << procent << "% [" << ss_bar.str().c_str() << "](" << processed_images << "/" << num_of_files <<")\n";
	}



//	loading_bar.join();
//thread ends

	std::cout << "Images were processed\n";
	
	std::thread audio(play_audio);
	int i = 0;
	while(i < num_of_files){
		current_time = get_time();
		delta_time = current_time - end_time;

		if(delta_time > 1/FPS){
			std::cout << "\e[1;1H\e[2J";
			frames[i].print();
			end_time = get_time();
			i++;
		}
	}
	delete frames;
	return 0;
}

float get_time(){
	return (float)(clock() - start_time)/CLOCKS_PER_SEC;
}



void play_audio(){
	system("ffplay -nodisp ../../audio/audio.mp3 1>&/dev/null");
}

