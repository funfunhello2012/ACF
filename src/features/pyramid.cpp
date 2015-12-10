#include "pyramid.h"
#include <iostream>
using namespace std;

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
	float *scales;
	int d0=0,d1=0;
	if(sz.width==0&&sz.height==0)
		return ;
	int tmp=(sz.width/minDs.width)<(sz.height/minDs.height)?(sz.width/minDs.width):(sz.height/minDs.height);
	nScales=(int)floor(nPerOct*(nOctUp+log10((double)tmp)/log10((double)2))+1);
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

void Pyramid:: computeData(Mat image,vector<vector <Mat> >& data){
	int shrink=4;
	float *scales;
	int nScales;
	Size size;
	size.width=image.cols;
	size.height=image.rows;
	if(nApprox<0)
		nApprox=nPerOct-1;
	/*
	 * rgbconvert();
	*/


	// get scales at which to compute features and list of real/approx scales
	getScales(scales,nScales,nPerOct,nOctUp,minDs,4,size);
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

	for(int i=0;i<(int)isR.size();i++)
	{
		float s=scales[isR[i]-1];
		Size sz1((int)((size.width*s/shrink)*shrink+0.5),(int)((size.height*s/shrink)*shrink+0.5));
		//cout<<sz1.width<<"  "<<sz1.height<<endl;
		Mat I1;
		if(size.height==sz1.height&&size.width==size.width)
		{
			I1=image;
			//cout<<I1.cols<<"  "<<I1.rows<<endl;
		}
		else
		{
			resize(image,I1,sz1,0,0,CV_INTER_LINEAR);
			//cout<<I1.cols<<"  "<<I1.rows<<endl;
		}
		/*if(i==2)
		{
			imshow("WindowOrg",I1);
			waitKey(10000);
		}*/
		if(s==0.5&&(nApprox>0||nPerOct==1))
			image=I1;

		Mat d;
		
		cvtColor(I1, d, CV_BGR2GRAY);
		//data.push_back(d);
	}

	//if lambdas not specified compute image specific lambdas
	if(nScales>0&&nApprox>0)
	{
		vector<int> is,istmp;
		for(int i=1+nOctUp*nPerOct;i<=nScales;i=i+nApprox+1)
			istmp.push_back(i);
		if(istmp.size()>2)
		{
			is.push_back(istmp[1]);
			is.push_back(istmp[2]);
		}
		//cout<<is[0]<<" "<<is[1]<<endl;
	}
}

#if NOW_TESTING == TEST_PYRAMID

int main()
{
	Pyramid p;
	Mat I=imread("2.jpg");
	vector< vector <Mat> > data; // error: ‘>>’ should be ‘> >’ within a nested template argument list
	p.computeData(I,data);
	//int position =getminmax();
	return 0;
}

#endif
