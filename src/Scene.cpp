#include "Scene.h"

#include "ShaderEyelight.h"
#include "ShaderPhong.h"
#include "PrimTriangle.h"
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cstdlib>

void CScene::ParseOBJ(const std::string& fileName)
{
	std::cout << "Parsing OBJFile : " << fileName << std::endl;

	std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 1, 1));
	std::vector<Vec3f> vertices;
	std::vector<int> faceindx;
	std::vector<int> faceindy;
	std::vector<int> faceindz;
	std::string line;
	std::ifstream in(fileName, std::ios::in);
	if (!in)
	{
		std::cout<<fileName<<" cannot be accessed"<<std::endl;
		exit(1);
	} 
	while(std::getline(in,line)){
		if (line.substr(0,2)=="f "){
    		std::istringstream arguments(line.substr(2));
    		int x,y,z;
        	arguments>>x;
			arguments>>y;
			arguments>>z;
        	x,y,z;
			faceindx.push_back(x);
			faceindy.push_back(y);
			faceindz.push_back(z);
			}
		else if (line.substr(0,2)=="v "){
    		std::istringstream arguments(line.substr(2));
    		double xd,yd,zd;
        	arguments>>xd;
			arguments>>yd;
			arguments>>zd;
        	vertices.push_back(Vec3f(xd,yd,zd)*100);
			}
		
		}
	
	for (int i =0;i<faceindx.size();i++)
	{
		//std::cout<<vertices[faceind[i]][0]<<" "<<vertices[faceind[i]][1]<<std::endl;
		Vec3f x = vertices[faceindx[i]-1];
		Vec3f y = vertices[faceindy[i]-1];
		Vec3f z =vertices[faceindz[i]-1];
		Add(std::make_shared<CPrimTriangle>(x,y,z,pShader));
	}
	std::cout << "Finished Parsing" << std::endl;

}

