#include <fstream>
#include <iostream>

using namespace std;

int findMandelbrotNumber(double cr, double ci, int max_iterat) {

	int i = 0;
	double zr = 0.0;
	double zi = 0.0;

	while (i < max_iterat && zr * zr + zi * zi < 4.0) {

		double temp = zr * zr - zi * zi + cr;

		zi = 2.0 * zr * zi + ci;
		zr = temp;
		i++;
	}

	return i;
}


double mapToReal(int x, int imageWidth, double minR, double maxR) {

	double range = maxR - minR;

	return x * (range / imageWidth) + minR;
}

double mapToImaginary(int y, int imageHeight, double minI, double maxI) {

	double range = maxI - minI;

	return y * (range / imageHeight) + minI;
}


int main() {

	cout << "Start 45000 X 45000 !!" << endl;

	ifstream fin("input.txt");

	int timer = 0;
	int coun = 0;
	int imageWidth, imageHeight, maxN;
	double minR, maxR, minI, maxI;

	if (!fin) {

		cout << "Couldn't open file!" << endl;
		cin.ignore();

		return 0;
	}

	fin >> imageWidth >> imageHeight >> maxN;
	fin >> minR >> maxR >> minI >> maxI;
	fin.close();

	ofstream fout("output_image_3.ppm");

	fout << "P3" << endl;
	fout << imageWidth << " " << imageHeight << endl;
	fout << "256" << endl;

	for (int y = 0; y < imageHeight; y++) {

		for (int x = 0; x < imageWidth; x++) {
			timer++;
			if (timer > 1000000) {
				timer = 0;
				coun++;
				cout << "# " << coun << endl;
			}

			double cr = mapToReal(x, imageWidth, minR, maxR);
			double ci = mapToImaginary(y, imageHeight, minI, maxI);

			int n = findMandelbrotNumber(cr, ci, maxN);

			int r = (n % 128);
			int g = (n % 84);
			int b = (n % 64);

			if (r > 256) {
				r = 256;
			}
			else {
				r = n % 128;
			}
			
			if (g > 256) {
				g = 256;
			}
			else {
				g = n % 84;
			}
			if (b > 256) {
				b = 256;
			}
			else {
				b = n % 64;
			}

			fout << r << " " << g << " " << b << " ";
		}

		fout << endl;
	}

	fout.close();

	cout << "Finish!!" << endl;

	return 0;
}