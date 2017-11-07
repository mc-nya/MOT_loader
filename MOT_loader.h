#ifndef MOT_LOADER_H
#define MOT_LOADER_H
#include"headfile.h"

typedef struct rect {
	double x, y, w, h;
	int frame;
	rect()=default;
}rect;
typedef struct gt_rect :rect {
	int id;
	int type;
	int valid;
	double occlusion;
	gt_rect() = default;
	gt_rect(std::vector<double> vec) {
		assert(vec.size() == 9);
		frame = (int)round(vec[0]);
		id = vec[1];
		x = vec[2];
		y = vec[3];
		w = vec[4];
		h = vec[5];
		valid = (int)round(vec[6]);
		type = (int)round(vec[7]);
		occlusion = vec[8];		
	}
}gt_rect;
typedef struct det_rect :rect {
	double possiblity;
	det_rect() = default;
	det_rect(std::vector<double> vec) {
		//assert(vec.size() == 10);
		frame = (int)round(vec[0]);
		x = vec[2];
		y = vec[3];
		w = vec[4];
		h = vec[5];
		possiblity = vec[6];
	}
}det_rect;


class MOT_loader {
public:
	MOT_loader(const std::string& in_path);
	cv::Mat Img(int);



	inline const std::vector<gt_rect> GtRectFrame(int frame) {
		assert(frame > 0 && frame <= seqLength);
		return GtRectPerFrame[frame];
	}
	inline const std::vector<gt_rect> GtRectId(int id) {
		return GtRectPerId[id];
	}
	inline const std::vector<det_rect> DetRect(int frame) {
		assert(frame > 0 && frame <= seqLength);
		return DetRectPerFrame[frame];
	}
	inline const int getSeqLength() { return seqLength; }
	inline const int getFrameRate() { return frameRate; }
	inline const int getWidth() { return imWidth; }
	inline const int getHeight() { return imHeight; }

	int trace = 0;
	std::string name;
private:
	std::string path;
	
	std::string imdir;
	int frameRate;
	int seqLength;
	int imWidth;
	int imHeight;
	
	std::string imExt;
	std::vector<cv::Mat> images;
	std::vector<std::vector<gt_rect>> GtRectPerFrame;
	std::vector<std::vector<gt_rect>> GtRectPerId;
	std::vector<std::vector<det_rect>> DetRectPerFrame;
	std::vector<gt_rect> GtRectAll;
	std::vector<det_rect> DetRectAll;
};


#endif
