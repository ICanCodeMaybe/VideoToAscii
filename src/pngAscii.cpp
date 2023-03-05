#include "pngAscii.h"

#include "stbi.h"
#include <cstdlib>
#include <iostream>

Picture::Picture(const char* file_path, int factor) 
	: m_file_path(file_path), m_factor(factor){
	this->load_image();
	if(!loaded_correctly)
		return;
	this->make_grayscale();
	this->scale_down(factor);
}


void Picture::load_image(){
	m_data = stbi_load(m_file_path, &m_x, &m_y, &m_channels, 3); // the last one are desired channels( 1 represents grayscale)
	
	if(!m_data){
		std::cout << "Obrázek nebyl načten správně :(\nZkontroluj jestli jsi napsala správný název. (file_path: " << m_file_path << ")\n";
	loaded_correctly = false;
	return;
	}
	
	m_size = m_x * m_y * m_channels;

}

void Picture::make_grayscale(){
	m_gray_scale_data = (unsigned char*)malloc(m_size/m_channels);

	if(m_channels == 3){
		//i predict, that there are always going to be 3 channels
		for(int i = 0; i < m_size; i += 3){
			int sum = m_data[i] + m_data[i+1] + m_data[i+2];
			m_gray_scale_data[i/3] = (unsigned char)(sum/3);
		}
	}
	else
		std::cout << "Wrong number of channels!!!\n";
}

void Picture::scale_down(int factor){
	scaled_x = m_x/factor;
	scaled_y = ((float)m_y/factor);
	scaled_size = scaled_x * scaled_y;
	
	m_scaled_data = (unsigned char*)malloc(scaled_size);

	for(int y = 0; y < scaled_y; y++){
		for(int x = 0; x < scaled_x; x++){
			//block sum
			int block_sum = 0;
			for(int i = 0; i < factor; i++){
				for(int j = 0; j < factor; j++){
					int horizontal = j + x*factor;
					int vertical = i * factor + y * factor *  m_x;

					block_sum += m_gray_scale_data[horizontal + vertical]; 
				}
			}
			m_scaled_data[x + y*scaled_x] = (unsigned char)(block_sum/(factor*factor));
		}
	}
}

void Picture::print(){
	const char* ten_levels = " .:-=+*#%@";

	for(int y = 0; y < scaled_y; y++){
		for(int x = 0; x < scaled_x; x++){
			int pixel_value = m_scaled_data[x + y*scaled_x];
			float gray_value = pixel_value / 28.33333f; // - 28.333 = 255/9, because i need to get values in interval <0, 9>

			std::cout << ten_levels[(int)gray_value];
			
		}
		std::cout << "\n";
	}

}

void Picture::print70(){
	const char* seventy_levels = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,^`'. ";

	for(int y = 0; y < scaled_y; y++){
		for(int x = 0; x < scaled_x; x++){
			int pixel_value = m_scaled_data[x + y*scaled_x];
			float gray_value = pixel_value / 3.696; // - 3.696 = 255/69, because i need to get values in interval <0, 69>

			std::cout << seventy_levels[69 - (int)gray_value];
			
		}
		std::cout << "\n";
	}


}
