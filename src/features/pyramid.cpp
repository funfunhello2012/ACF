#include "pyramid.h"
#include <iostream>
using namespace std;
using namespace cv;


//function in getScales
int getminmax(float a[],float b[])
{
	float c[101];
	int position=0;
	for(int i=0;i<101;i++)
	{
		a[i]>b[i]?c[i]=a[i]:c[i]=b[i];
		//cout<<c[i]<<endl;
	}
	for(int i=0;i<101;i++)
	{
		if(c[0]>c[i])
		{
			c[0]=c[i];
			position=i;
		}
	}
	return position;
}


void getScales(float *&scaless,int &nScales,int nPerOct,int nOctUp,Size minDs,int shrink,Size sz)
{
	OUT("Come in");
	float *scales;
	int d0=0,d1=0;
	if(sz.width==0&&sz.height==0)
		return ;
	int tmp=(sz.width/minDs.width)<(sz.height/minDs.height)?(sz.width/minDs.width):(sz.height/minDs.height);
	OUT_V(tmp);
	nScales=(int)floor(nPerOct*(nOctUp+log10((double)tmp)/log10((double)2))+1);
	OUT_V(nScales);
	scales=(float *)malloc(nScales*sizeof(float));
	for(int i=0;i<nScales;i++)
	{
		scales[i]=(float)pow(2,(((float)-i/nPerOct)+nOctUp));
		//cout<<scales[i]<<endl;
	}
	
	if(sz.width<sz.height){
		d0=sz.width;
		d1=sz.height;
		//cout<<d0<<"  "<<d1<<endl;
	}else
	{
		d0=sz.height;
		d1=sz.width;
		//cout<<d0<<"  "<<d1<<endl;
	}
	for(int i=0;i<nScales;i++){
		double s=scales[i];
		double s0=((int)(d0*s/shrink+0.5)*shrink-0.25*shrink)/d0;
		double s1=((int)(d0*s/shrink+0.5)*shrink+0.25*shrink)/d0;
		//cout<<s1<<"  "<<s0<<" "<<s1-s0<<endl;
		float k=0.0,ss[101],es0[101],es1[101];
		for(int j=0;j<=100;j++)
		{
			ss[j]=k;
			k=k+0.01;
		}
		for(int j=0;j<101;j++)
		{
			ss[j]=ss[j]*(s1-s0)+s0;
			//cout<<ss[j]<<endl;
			es0[j]=d0*ss[j];
			es0[j]=abs(es0[j]-((int)(es0[j]/shrink+0.5))*shrink);
			//cout<<es0[j]<<endl;
			es1[j]=d1*ss[j];
			es1[j]=abs(es1[j]-((int)(es1[j]/shrink+0.5))*shrink);
			//cout<<es1[j]<<endl;
		}
		int x=getminmax(es0,es1);
		//cout<<x<<endl;
		scales[i]=ss[x];
	}
	if(scales[0]>1)scales[0]=1;
	//for(int i=0;i<nScales;i++)
		//cout<<scales[i]<<endl;
	bool *kp=(bool *)malloc(nScales*sizeof(bool));
	int num=0;
	for(int i=0;i<nScales-1;i++)
	{
		if(scales[i]!=scales[i+1])
			kp[i]=true;
		else
		{
			kp[i]=false;
			num=num+1;
		}
		//cout<<kp[i]<<endl;
	}
	kp[nScales]=true;
	nScales=nScales-num;
	scaless=(float *)malloc(nScales*sizeof(float));
	for(int i=0,j=0;i<nScales+num;i++)
	{
		if(kp[i])
		{
			scaless[j]=scales[i];
			j++;
		}
	}
}

float getmat_sum(float* mat,Vec3i dims)
{
	float sum=0.0;
	for(int i=0;i<dims[0]*dims[1]*dims[2];i++)
		sum=sum+mat[i];
	sum=sum/(dims[0]*dims[1]*dims[2]);
	return sum;
}

void Pyramid:: computeData(Mat& image,vector<vector <float*> >& data, vector<vector<Vec3i> >& dataSizes){
	OUT("Pyramid::computeData");
//	vector<float*> chnsData;
////	OUT(image);
//	float* imageData = (float*)image.data;	//先旋转,在取出每个通道,
//	Vec3i imgDims = Vec3i(image.rows,image.cols,image.channels());
//	this->chnsmanager->compute(chnsData,imageData,imgDims);
//	dataSizes.push_back(this->chnsmanager->getChnSize());
//	OUT("Getting data from ChnsManager");
//	data.push_back(chnsData);

	int shrink=4;
	float *scales;
	int nScales;
	Size size;
	size.width=image.cols;
	size.height=image.rows;

	int ntypes= this->chnsmanager->getNTypes();
	if(nApprox<0)
		nApprox=nPerOct-1;

	/*
	 * rgbconvert();
	*/

	// convert image to LUV
	image.t();
	float* imgData = matconvert( image);

	OUT_V(nPerOct);
	OUT_V(nOctUp);
	OUT_V(minDs);
	OUT_V(size);

	// get scales at which to compute features and list of real/approx scales
	getScales(scales,nScales,nPerOct, nOctUp,minDs,4,size);
	OUT("pyramid::159");
	data=vector<vector <float*>>(nScales,vector<float*>(ntypes));
	dataSizes = vector<vector<Vec3i> >(nScales,vector<Vec3i>(ntypes));

	//cout<<nScales<<endl;
	//for(int i=0;i<nScales;i++)
		//cout<<scales[i]<<endl;
	vector<int> isR,isA,j,isN;
	for(int i=1;i<=nScales;i=i+nApprox+1)
		isR.push_back(i);
	for(int i=1;i<=nScales;i++)
		isA.push_back(i);
	for(int i=0;i<(int)isR.size();i++)
		isA.erase(isA.begin()+(isR[i]-1-i));
	j.push_back(0);
	for(int i=0;i<(int)isR.size()-1;i++)
		j.push_back((int)((isR[i]+isR[i+1])/2));
	j.push_back(nScales);
	for(int i=1;i<=nScales;i++)
		isN.push_back(i);
	for(int i=0;i<(int)isR.size();i++)
		for(int k=j[i];k<j[i+1];k++)
			isN[k]=isR[i];
	/*for(int i=0;i<isN.size();i++)
		cout<<isN[i]<<endl;*/
	//compute image pyramid[real scales]


	for(int i=0;i<(int)isR.size();i++)//
	{
		float s=scales[isR[i]-1];
		Size sz1((int)((size.width*s/shrink)*shrink+0.5),(int)((size.height*s/shrink)*shrink+0.5));
		//cout<<sz1.width<<"  "<<sz1.height<<endl;
		float* I1 = new float[sz1.height*sz1.width*image.channels()*sizeof(float)];
		if(size.height==sz1.height&&size.width==size.width)
		{
			I1=imgData;
		}
		else
		{
//			resize(image,I1,sz1,0,0,CV_INTER_LINEAR);
			resample(imgData,I1,size.height,sz1.height,size.width,sz1.width,image.channels(),1.0f);
			//cout<<I1.cols<<"  "<<I1.rows<<endl;
		}
		if(s==0.5&&(nApprox>0||nPerOct==1))
			imgData=I1;


			//data.push_back(d);
		vector<float*> p;
		//compute
		Vec3i curDims = Vec3i(sz1.height,sz1.width,image.channels());
		this->chnsmanager->compute(p,I1,curDims);
		OUT_V(p.size());
		OUT("pyramid.cpp::212");
		data[isR[i]-1]=p;
		OUT_V(isR[i]-1);
		dataSizes[isR[i]-1]=this->chnsmanager->getChnSize();
	}

	//if lambdas not specified compute image specific lambdas
	float lambdas[ntypes];
//	lambdas=(float*)malloc(ntypes*sizeof(float));

	if(nScales>0&&nApprox>0)
	{
		vector<int> is,istmp;
		for(int i=1+nOctUp*nPerOct;i<=nScales;i=i+nApprox+1)
			istmp.push_back(i);
		OUT("pyramid.cpp::224");
		OUT_V(istmp.size());
		if(istmp.size()>2)
		{
			is.push_back(istmp[1]);
			is.push_back(istmp[2]);
		}
		assert(is.size()>=2);
		OUT("pyramid.cpp::229");
		OUT_V(is[0]-1);OUT_V(is[1]-1);
		OUT("pyramid.cpp::231");

		vector<float*> d0=data[is[0]-1];
		vector<float*> dd0=data[is[1]-1];
		OUT("pyramid.cpp::232");
		float *matsum1=(float*)malloc(ntypes*sizeof(float));
		float *matsum2=(float*)malloc(ntypes*sizeof(float));
		OUT("pyramid.cpp::234");
		//lambdas=(float*)malloc(ntypes*sizeof(float));
		for(int i=0;i<ntypes;i++)
		{
			OUT("pyramid.cpp::244");

			matsum1[i]=getmat_sum(d0[i],dataSizes[is[0]-1][i]);

			OUT("pyramid.cpp::246");
			matsum2[i]=getmat_sum(dd0[i],dataSizes[is[1]-1][i]);
			OUT("pyramid.cpp::246");
			lambdas[i]=(float)(-log10((double)(matsum1[i]/matsum2[i]))/log10((double)2))/(log10((double)(scales[is[0]-1]/scales[is[1]-1])/log10((double)2)));
		}
	}
	OUT_V(lambdas[0]);OUT_V(lambdas[1]);OUT_V(lambdas[2]);
	//compute image pyramid [approximated scales]
	for(int i=0;i<(int)isA.size();i++)
	{
		int iR=isN[isA[i]-1];
		float s=scales[isA[i]-1];
		Size sz1((int)((size.width*s/shrink)*shrink+0.5),(int)((size.height*s/shrink)*shrink+0.5));
		vector<float*> m1=data[iR-1];
		vector<float*> approx;
		for(int j=0;j<ntypes;j++)
		{
			int ha=dataSizes[iR-1][j][0];
			int wa=dataSizes[iR-1][j][1];
			int nchannel=dataSizes[iR-1][j][2];
			float ratio=pow(scales[isA[i]-1]/scales[iR-1],-lambdas[j]);
			float* m11=new float[sz1.height*sz1.width*nchannel ];//
			resample(m1[j],m11,ha,sz1.height,wa,sz1.width,nchannel,(float)ratio);
			approx.push_back(m11);
		}
		data[isA[i]-1]=approx;
	}
	OUT("pyramid.cpp::261");

//	//smooth channels, optionally pad and concatenate channels
}



