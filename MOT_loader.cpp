#include "MOT_loader.h"

std::vector<double> split(const std::string& s,const std::string& c) {
	using namespace std;
	vector<double> ret;
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		ret.push_back(stod(s.substr(pos1, pos2 - pos1)));
		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		ret.push_back(stod(s.substr(pos1)));
	return ret;
}

MOT_loader::MOT_loader(const std::string& in_path) :path(in_path) {
	using namespace std;
	
	//load seqInfo
	fstream seqInfo(path + "/seqinfo.ini", ios::in);
	assert(seqInfo.is_open());
	string seqHead;
	seqInfo >> seqHead;
	assert(seqHead == "[Sequence]");
	seqInfo >> name>>imdir;
	name = name.substr(5, name.size() - 5);
	imdir = imdir.substr(6, imdir.size() - 6);
	string stemp;
	seqInfo >> stemp;
	frameRate = stoi(stemp.substr(10, stemp.size() - 10));
	seqInfo >> stemp;
	seqLength = stoi(stemp.substr(10, stemp.size() - 10));
	seqInfo >> stemp;
	imWidth = stoi(stemp.substr(8, stemp.size() - 8));
	seqInfo >> stemp;
	imHeight = stoi(stemp.substr(9, stemp.size() - 9));
	seqInfo >> imExt;
	imExt = imExt.substr(6, imExt.size() - 6);
	cout << "seqName=" << name << endl;
	cout << "imdir=" << imdir << endl;
	cout << "frameRate=" << frameRate << endl;
	cout << "seqLength=" << seqLength << endl;
	cout << "imWidth=" << imWidth << endl;
	cout << "imHeight=" << imHeight << endl;
	cout << "imExt=" << imExt << endl;
	seqInfo.close();

	//load Images
	//ostringstream oss;
	//using namespace cv;
	//images.push_back(Mat(1,1,CV_16S));
	//for (int i = 1; i <= seqLength; i++) {
	//	oss.str("");
	//	oss <<setw(6)<<setfill('0')<< i << imExt;
	//	images.push_back(imread(path + "/img1/" + oss.str(), CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH));
	//}

	//load gt
	for (int i = 0; i <= seqLength; i++) {
		GtRectPerFrame.push_back(vector<gt_rect>());
	}
	for (int i = 0; i <= 600; i++) {
		GtRectPerId.push_back(vector<gt_rect>());
	}
	ifstream gtFile(path + "/gt/gt.txt");
	while (!gtFile.eof()) {
		gtFile >> stemp;
		auto gtVet = split(stemp,",");
		gt_rect gt(gtVet);
		GtRectAll.push_back(gt);
		GtRectPerFrame[gt.frame].push_back(gt);
		GtRectPerId[gt.id].push_back(gt);
		if (gt.id > trace) {
			trace = gt.id;
		}
	}
	gtFile.close();

	//load detection
	for (int i = 0; i <= seqLength; i++) {
		DetRectPerFrame.push_back(vector<det_rect>());
	}

	ifstream detFile(path + "/det/det.txt");
	while (!detFile.eof()) {
		detFile >> stemp;
		auto detVec = split(stemp, ",");
		det_rect det(detVec);
		DetRectAll.push_back(det);
		DetRectPerFrame[det.frame].push_back(det);
	}
	detFile.close();
	
	


	

}

cv::Mat MOT_loader::Img(int seqNum) {
	using namespace std;
	using namespace cv;
	assert(seqNum > 0);
	assert(seqNum <= seqLength);
	ostringstream oss;
	oss.str("");
	oss << setw(6) << setfill('0') << seqNum << imExt;
	return imread(path + "/img1/" + oss.str(), CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
}

