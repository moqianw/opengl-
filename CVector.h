#include<iostream>
#include<cmath>
#include<fstream>
#include<sstream>
#include<vector>
using namespace std;
class CVector {
public:
	float x, y, z;
	CVector(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;

	}
	void Set(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;

	}
	CVector operator+(CVector& p) {
		CVector q = *this;
		q.x += p.x;
		q.y += p.y;
		q.z += p.z;
		return q;
	}
	CVector operator-(CVector& p) {
		CVector q = *this;
		q.x -= p.x;
		q.y -= p.y;
		q.z -= p.z;
		return q;
	}
	CVector operator=(CVector p) {
		*this = p;
		return *this;
	}

	CVector operator*(float p) {
		CVector q = *this;
		q.x *= p;
		q.y *= p;
		q.z *= p;
		return q;
	}
	float dotMul(CVector& n) {
		return (this->x) * (n.x) + (this->y) * (n.y) + (this->z) * (n.z);
	}
	float len() {
		return sqrt(pow(this->x,2) + pow(this->y,2) + pow(this->z,2));
	}
	CVector crossMul(CVector& p){
		CVector q = *this;
		q.x = (this->y) * (p.z) - (this->z) * (p.y);
		q.y = (this->z) * (p.x) - (this->x) * (p.z);
		q.z = (this->x) * (p.y) - (this->y) * (p.x);
		return q;
	}
	void Normalize() {
		float len = this->len();
		this->x /= len;
		this->y /= len;
		this->z /= len;
	}
	CVector project(CVector& n) {
		float a = this->dotMul(n);
		float len1 = a / n.len();
		float qlen = len1/n.len();
		CVector q = n*qlen ;
		return q;
	}
	bool operator==(CVector& p) {
		if (p.x == this->x && p.y == this->y && p.z == this->z) return 1;
		return 0;
	}
	bool operator!=(CVector& p) {
		if (p.x != this->x || p.y != this->y || p.z != this->z) return 1;
		return 0;
	}
};
class RRfile {
public:

	static vector<string> split(string str, char del) {
		stringstream ss(str);
		string tmp;
		vector<string> res;
		while (getline(ss, tmp, del)) {
			res.push_back(tmp);
		}
		return res;
	}
	static void ope(ifstream& fin, ofstream& fout, char op,CVector& p, CVector& q,string& t, vector<string>& data) {
		if (op == '+') {
			fout << t << endl;
			fin >> t;
			fout << t << "\t";
			data = split(t, ',');
			p.x = stof(data[0]);
			p.y = stof(data[1]);
			p.z = stof(data[2]);
			fin >> t;
			fout << t << "\t";
			data = split(t, ',');
			q.x = stof(data[0]);
			q.y = stof(data[1]);
			q.z = stof(data[2]);
			CVector r = p + q;
			fout << r.x << "," << r.y << "," << r.z << endl;
		}
		if (op == '.') {
			fout << t << endl;
			fin >> t;
			fout << t << "\t";
			data = split(t, ',');
			p.x = stof(data[0]);
			p.y = stof(data[1]);
			p.z = stof(data[2]);
			fin >> t;
			fout << t << "\t";
			data = split(t, ',');
			q.x = stof(data[0]);
			q.y = stof(data[1]);
			q.z = stof(data[2]);
			float ans = p.dotMul(q);
			fout << ans << endl;
		}
		if (op == 'x') {
			fout << t << endl;
			fin >> t;
			fout << t << "\t";
			data = split(t, ',');
			p.x = stof(data[0]);
			p.y = stof(data[1]);
			p.z = stof(data[2]);
			fin >> t;
			fout << t << "\t";
			data = split(t, ',');
			q.x = stof(data[0]);
			q.y = stof(data[1]);
			q.z = stof(data[2]);
			CVector r = p.crossMul(q);
			fout << r.x << "," << r.y << "," << r.z << endl;
		}
		if (op == 't') {
			fout << t << endl;
			fin >> t;
			fout << t << "\t";
			data = split(t, ',');
			p.x = stof(data[0]);
			p.y = stof(data[1]);
			p.z = stof(data[2]);
			fin >> t;
			fout << t << "\t";
			data = split(t, ',');
			q.x = stof(data[0]);
			q.y = stof(data[1]);
			q.z = stof(data[2]);
			CVector r = p.project(q);
			fout << r.x << "," << r.y << "," << r.z << endl;
		}
	}
	static void Main() {
		CVector p(0,0,0);
		CVector q(0,0,0);
		ifstream fin;
		ofstream fout;
		fin.open("test.txt", ios::in);
		if (!fin.is_open())
		{
			cout << "error" << endl;
			return;
		}
		fout.open("out.txt");
		vector<string> data;
		while (!fin.eof()) {
			string t;
			fin >> t;
			if (t == "向量相加") {
				ope(fin, fout, '+', p, q, t, data);
			}
			if (t == "向量点乘") {
				ope(fin, fout, '.', p, q, t, data);
			}
			if (t == "向量叉乘") {
				ope(fin, fout, 'x', p, q, t, data);
			}
			if (t == "向量标准化") {
				fout << t << endl;
				fin >> t;
				fout << t << "\t";
				data = split(t, ',');
				p.x = stof(data[0]);
				p.y = stof(data[1]);
				p.z = stof(data[2]);
				p.Normalize();
				fout << p.x << "," << p.y << "," << p.z << endl;
			}
			if (t == "向量求模") {
				fout << t << endl;
				fin >> t;
				fout << t << "\t";
				data = split(t, ',');
				p.x = stof(data[0]);
				p.y = stof(data[1]);
				p.z = stof(data[2]);
				float ans = p.len();
				fout << ans << endl;
			}
			if (t == "向量投影") {
				ope(fin, fout, 't', p, q, t, data);
			}
		}
		fin.close();
		fout.close();
	}

};