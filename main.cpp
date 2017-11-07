#include "MOT_loader.h"
#include <Windows.h>
int main() {
	using namespace std;
	using namespace cv;
	CreateDirectory("./trace", NULL);
	MOT_loader loader("Y:/MOT17/train/MOT17-13-SDP");
	for (int i = 1; i < loader.trace; i++) {
		auto img = loader.Img(1);
		auto gtVec = loader.GtRectId(i);
		CreateDirectory(string("./trace/" + loader.name).c_str(), NULL);
		ofstream traceFile("./trace/" + loader.name + "/" + to_string(i) + ".txt");
		for (unsigned int j = 0; j < gtVec.size(); j++) {
			int x = gtVec[j].x;
			int y = gtVec[j].y;
			int w = gtVec[j].w;
			int h = gtVec[j].h;
			traceFile << gtVec[j].frame << " " << x << " " << y << " " << w << " "  << h << " " <<gtVec[j].valid<<" "<<gtVec[j].type<<" "<<gtVec[j].occlusion<< endl;
			if (gtVec[j].valid) {
				

				//if (j == 1) {
				//	circle(img, Point(x + w / 2, y + h / 2), 5, cvScalar(100, 200, 100), 3);
				//}
				//rectangle(img, Point(x, y), Point(x +w, y + h), cvScalar(gtVec[j].occlusion* 200, gtVec[j].occlusion * 200, 160),0.1);
				//if (j > 1) {
				//	int px = gtVec[j - 1].x;
				//	int py = gtVec[j - 1].y;
				//	int pw = gtVec[j - 1].w;
				//	int ph = gtVec[j - 1].h;
				//	line(img, Point(x + w / 2, y + h / 2), Point(px + pw / 2, py + ph / 2), cvScalar(gtVec[j].occlusion * 200, gtVec[j].occlusion * 200, 160),1);
				//}
				
			}
			
		}
		traceFile.close();
		//imshow("test", img);
		//cvWaitKey();
	}
	
	//system("pause");
	return 0;
}