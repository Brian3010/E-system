//void displaySmallestNumber(vector<int>& vect1, vector<string>& vect2)
//{
//	int min = vect1[0];
//	int pos = 0;
//	if (!vect1.empty()) {
//		for (int i = 0; i < vect1.size(); i++) {
//			if (vect1[i] < min) {
//				min = vect1[i];
//				pos = i;
//			}
//		}
//
//		cout << vect2[pos] << " has the smallest vote with " << vect1[pos] << " votes";
//	}
//	else {
//		cout << "Unable to determine the smallest number - list is empty" << endl;
//	}
//
//}
//
//void displaylargestNumber(vector<int>& vect1, vector<string>& vect2)
//{
//	int max = vect1[0];
//	int pos = 0;
//	if (!vect1.empty()) {
//		for (int i = 0; i < vect1.size(); i++) {
//			if (vect1[i] > max) {
//				max = vect1[i];
//				pos = i;
//			}
//		}
//
//		cout << vect2[pos] << " has the largest vote with " << vect1[pos] << " votes";
//	}
//	else {
//		cout << "Unable to determine the largest number - list is empty" << endl;
//	}
//
//}