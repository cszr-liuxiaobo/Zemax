#pragma once
#include <io.h>
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <ctime>
#include <functional>
#include <assert.h>
#include <fstream>              //�ļ�����ͷ�ļ�
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <mat.h>
#include <math.h>
#include <direct.h>
#include <string>
#include "./matconvert/matPackage.h"
#include "./utils/datastructure.h"

// Note - .tlh files will be generated from the .tlb files (above) once the project is compiled.
// Visual Studio will incorrectly continue to report IntelliSense error messages however until it is restarted.
#include "zosapi.h"
using namespace std;
using namespace ZOSAPI;
using namespace ZOSAPI_Interfaces;
#define DATA struct Data

#include <QtCore/QTimer>
#include <QtCore/QCoreApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/QProgressBar>
#include "ui_zemaxqt.h"




class ZemaxProject
{
public:
	double SystemImageheightMax;
	long SystemImageheightMaxIndex;
    //�����Ա����
    IZOSAPI_ApplicationPtr TheApplication;
	string outputFolder;  //�洢mat���ݵ�·��

    IOpticalSystemPtr TheSystem;
    I_AnalysesPtr TheAnalyses;
    IWavelengthsPtr sysWave;
    IMeritFunctionEditorPtr TheMFE;
	ILensDataEditorPtr TheLDE;  //��ͷ�༭ҳ
	ISolveDataPtr Solver;       //��Ծ�ͷ��༭radius�е����ԣ�Ҳ���Ի�ȡ����ֵ��Fnumber��
	IOpticalSystemToolsPtr tools;  //��Ծ�ͷ��༭thickness�е����ԣ�Ҳ���Ի�ȡ����ֵ��thickness��

	_bstr_t sampleDir;
    _bstr_t file_name;
    _bstr_t inputFile;
    _bstr_t SaveFile;

	int max_wave=1;   //�ܹ����ٸ�������
	int initpwav=1;
    int pwav=1;       //�����ǵڼ�����
    int max_num_field=1;

	FieldType initialfieldtype;
	double initialfieldYmaxvalue=20;

    long SurfacesNum;           //��ͷ���ȫ����������
    ILDERowPtr Surface_0;       //��һ����--����
    long stopsurface;           //�������ڵ���
    ILDERowPtr Surface_stop;    //������
    ILDERowPtr Surface_Lastglass; //����ǰ���һ�㲣����
    ILDERowPtr Surface_Last;    //����

    double Object_distance;     //�������
    double EFL, paraxialWorkingFNumber, realWorkingFNumber, paraxialImageHeight, paraxialMagnification;
    string filepath_Baseparameters;

    //��Ա����
    //------------�������������Ⲣ���������--------------------
    bool handleError(std::string msg);
    bool logInfo(std::string msg);
    bool fileExists(wchar_t* name);
	int createDirectory(std::string path);
    //����zemaxӦ��
    void createApplication();
    void getabspath(string folderpath, vector<string>& filespath, string filename);
    int loadmyFile(_bstr_t inputFile);

    vector<string> split(string& src, string separate_character);

    //���㲢��ȡ��ͷ�Ļ�������
	void basicSetting();
    void propertySetting();
	unsigned int set_WL_NUM(unsigned int num);
	double set_WL_MIN(double param);
	double set_WL_MAX(double param);
	unsigned int set_IMGHT_NUM(unsigned int num);
	double set_IMGHT_MIN(double param);
	double set_IMGHT_MAX(double param);
	unsigned int set_IMGWT_NUM(unsigned int num);
	double set_IMGWT_MIN(double param);
	double set_IMGWT_MAX(double param);

	vector<ANYData> getYourSetting();
	vector<DATA> getLensProperties();
	/*
	FieldType_Angle = 0,
	FieldType_ObjectHeight = 1,
	FieldType_ParaxialImageHeight = 2,
	FieldType_RealImageHeight = 3,
	FieldType_TheodoliteAngle = 4
	*/
	vector<string> fieldtype ={"Angle", "ObjectHeight" ,"ParaxialImageHeight" ,"RealImageHeight","TheodoliteAngle"};
	/*
	Distortions_F_TanTheta = 0,
	Distortions_F_Theta = 1,
	Distortions_Cal_F_Theta = 2,
	Distortions_Cal_F_TanTheta = 3,
	Distortions_SMIA_TV = 4
	*/
	vector<string> distortiontype = {"F_TanTheta","F_Theta","Cal_F_Theta","Cal_F_TanTheta","SMIA_TV"};
	/*
	FieldScanDirections_Plus_Y = 0,
    FieldScanDirections_Plus_X = 1,
    FieldScanDirections_Minus_Y = 2,
    FieldScanDirections_Minus_X = 3
	*/
	vector<string> scantype = {"Plus_Y","Plus_X","Minus_Y","Minus_X"};
	//PsfSampling
	//{
	//	PsfSampling_PsfS_32x32 = 1,
	//	PsfSampling_PsfS_64x64 = 2,
	//	PsfSampling_PsfS_128x128 = 3,
	//	PsfSampling_PsfS_256x256 = 4,
	//	PsfSampling_PsfS_512x512 = 5,
	//	PsfSampling_PsfS_1024x1024 = 6,
	//	PsfSampling_PsfS_2048x2048 = 7,
	//	PsfSampling_PsfS_4096x4096 = 8,
	//	PsfSampling_PsfS_8192x8192 = 9,
	//	PsfSampling_PsfS_16384x16384 = 10
	//};
	vector<int> PSFSize = { 0,32,64,128,256,512,1024,2048,4096,8192,16384 };
	//FftPsfType
	//{
	//	FftPsfType_Linear = 0,
	//	FftPsfType_Log = 1,
	//	FftPsfType_Phase = 2,
	//	FftPsfType_Real = 3,
	//	FftPsfType_Imaginary = 4
	//};
	vector<string>FFTpsftype = {"Linear","Log","Phase","Real","Imaginary"};
	//HuygensPsfTypes
	//{
	//	HuygensPsfTypes_Linear = 0,
	//	HuygensPsfTypes_Log_Minus_1 = 1,
	//	HuygensPsfTypes_Log_Minus_2 = 2,
	//	HuygensPsfTypes_Log_Minus_3 = 3,
	//	HuygensPsfTypes_Log_Minus_4 = 4,
	//	HuygensPsfTypes_Log_Minus_5 = 5,
	//	HuygensPsfTypes_Real = 6,
	//	HuygensPsfTypes_Imaginary = 7,
	//	HuygensPsfTypes_Phase = 8
	//};
	vector<string> Huygenspsftype = { "Linear","Log_Minus_1","Log_Minus_2","Log_Minus_3","Log_Minus_4","Log_Minus_5","Real","Imaginary","Phase"};
	int breakflage = 0;
	void add_w_f_field(mxArray* x);
	//fstream textfile_dis;
	//string filepath_dis;
	int Distorition_ij;
	double distoritiondata[1] = {0};
	void Distorition_result(IAR_Ptr distortion_Results);
	void Distorition_setting(double WLT, double IMGHT, double IMGWT = 0.0, int whichwave = 1, int Fieldtype = 3, int Distortiontype = 0, int Scantype = 0);
	mxArray* DistortionMultiple(int whichwave = 1, int Fieldtype = 3, int Distortiontype = 0, int Scantype = 0);
	
	//fstream textfile_CRA;
	//string filepath_CRA;
	int CRA_ij;
	double CRAdata[1] = { 0 };
	void ChiefRayAngle_result(double WLT, double IMGHT, double IMGWT = 0.0, int whichwave=1, int Fieldtype = 3, int x = 0, int y = 1);
	vector<double> ChiefRayAngle_setting(double WLT, double IMGHT, double IMGWT = 0.0, int whichwave = 1, int Fieldtype = 3, int x = 0, int y = 1);
	mxArray* ChiefRayAngleMultiple(int whichwave = 1, int Fieldtype=3, int x=0, int y=1);

	//fstream textfile_RI;
	//string filepath_RI;
	int RI_ij;
	double RIdata[1] = { 0 };
	void RI_result(double WLT, double IMGHT, double IMGWT = 0.0, int whichwave=1, int Fieldtype = 3, int samplenum = 10);
    void RI_setting(double WLT, double IMGHT, double IMGWT = 0.0, int whichwave = 1, int Fieldtype = 3, int samplenum = 10);
	mxArray* RIMultiple(int whichwave=1, int Fieldtype=3);

	//fstream textfile_FFTPSF;
	//string filepath_FFTPSF;
	int FFTPSF_ij;
	void FFTPSF_Result(IAR_Ptr PSFWin_Results, int Displaysize=4, DOUBLE* input1= nullptr, int I_wav=1, int J_ht=1);
    void FFTPSF_setting(double WLT, double IMGHT, double IMGWT = 0.0, int whichwave=1, int Fieldtype = 3, int Samplingsize = 4,
		int Displaysize = 4, int fftpsftype = 0, double ImageDelta = 0.25/*um*/,  bool isNormalize = 0);
	mxArray* FFTPSFMultiple(int whichwave = 1, int Fieldtype = 2, int Samplingsizetype = 4,
		int Displaysize = 4, int fftpsftype = 0, double ImageDelta = 0.25/*um*/,  bool isNormalize = 0);

	//fstream textfile_HuygensPSF;
	//string filepath_HuygensPSF;
	int HuygensPSF_ij;
	void HuygensPSF_Result(IAR_Ptr HuygensPSF_Results, int Displaysize=4, DOUBLE* input2 = nullptr, int I_wav=1, int J_ht=1);
    void HuygensPSF_setting(double WLT, double IMGHT, double IMGWT = 0.0, int whichwave=1,int Fieldtype = 3, int Samplingsizetype = 4,
		int displaysizetype = 4, int HuygensPSFtype = 0, double ImageDelta = 0.25/*um*/, bool isNormalize = 0);
	mxArray* HuygensPSFMultiple(int whichwave = 1, int Fieldtype = 3, int Samplingsize = 4,
		int displaysize = 4, int HuygensPSFtype = 0, double ImageDelta = 0.25/*um*/,  bool isNormalize = 0);
	
    // Clean up
    void finishStandaloneApplication();
    bool saveFile(_bstr_t savepath);

	//-------------------------------------------------------------------------------------------------------------------------

	//mxArray* convertPSFToMXArray(); mxArray* saveToMXStruct();
	//��main�����жϣ�flageΪ���־�ʹ���ĸ�ʵ�������Project��
	//Project1����Projectback��
	MATFile* out_File; mxArray* oiStruct;
	string outFileName;
	mxArray* m_transmittance;

	mxArray* m_rayTrace;
	// add field 'Distorition'
	mxArray* m_Distorition;
	// add field 'CRA'
	mxArray* m_CRA;
	// add field 'RI'
	mxArray* m_RI;
	// add field 'fftpsf'
	mxArray* m_fftpsf;
	// add field 'fftpsf'
	mxArray* m_huygenspsf;

	void saveOIToMatFile(vector<ANYData> params_setting);
	void closemat();


	private:
		//���ݳ�Ա�Ժ���Ϊprivate���ֱ��ʾ��
		//Ԥ��Ĳ���ƽ���ֳ��ķ�����������Сֵ���������ֵ
		//Ԥ������ƽ���ֳ��ķ����������Сֵ��������ֵ
		unsigned int WL_NUM = 31;    double WL_MIN = 0.400;    double WL_MAX = 0.700;
		unsigned int IMGHT_NUM = 90; double IMGHT_MIN = 0.0; double IMGHT_MAX = 20.0;
		unsigned int IMGWT_NUM = 0; double IMGWT_MIN = 0.0; double IMGWT_MAX = 0.0;
};

//------------�������ݽṹ1--------------------
DATA{
	string mykey;
	int ivalue;
	double dvalue;
	string svalue;
};

