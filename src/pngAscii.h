#ifndef PNG_ASCII
#define PNG_ASCII

#include <iostream>

class Picture{
private:
	int m_x, m_y, m_channels;
	const char* m_file_path = "../../resources/srdce.jpg";
	int m_size;
	int m_factor;
	
	int scaled_x, scaled_y, scaled_size;
	
	unsigned char* m_data;
	unsigned char* m_gray_scale_data;
	unsigned char* m_scaled_data;

	bool loaded_correctly = true;
public:
	Picture(const char* file_path, int factor = 8);
	void print70();
	void print();
private:
	void load_image();
	void make_grayscale();

	void scale_down(int factor = 8);




};


#endif
